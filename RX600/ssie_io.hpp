#pragma once
//=========================================================================//
/*!	@file
	@brief	RX72M/RX72N/RX66N SSIE I/O 制御 @n
			SSIE 内 FIFO では容量が足りないので、バッファリングを行う。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SSIE（シリアルサウンドインターフェース）基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct ssie_io_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ビット列フォーマット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class BFORM : uint8_t {
			I2S_16,		///< I2S 16 ビットフォーマット
			I2S_24,		///< I2S 24 ビットフォーマット
			I2S_32,		///< I2S 32 ビットフォーマット
			LEFT_16,	///< 左詰め 16 ビットフォーマット
			LEFT_24,	///< 左詰め 24 ビットフォーマット
			LEFT_32,	///< 左詰め 32 ビットフォーマット
			RIGHT_16,	///< 右詰め 16 ビットフォーマット
			RIGHT_24,	///< 右詰め 24 ビットフォーマット
			RIGHT_32,	///< 右詰め 32 ビットフォーマット
			TDM_2,		///< TDM 2(16x2) ワード・フォーマット
			TDM_4,		///< TDM 4(16x4) ワード・フォーマット
			TDM_6,		///< TDM 6(16x6) ワード・フォーマット
			TDM_8,		///< TDM 8(16x8) ワード・フォーマット
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SSIE（シリアルサウンドインターフェース）制御クラス
		@param[in]	SSIE		ハードウェアー・コンテキスト
		@param[in]	DMAC		DMAC デバイス・コンテキスト(DMAC0 - DMAC7)
		@param[in]	SOUND_OUT	サウンド出力オブジェクト型
		@param[in]	MASTER		スレーブの場合「false」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SSIE, class DMAC, class SOUND_OUT, bool MASTER = true>
	class ssie_io : public ssie_io_base {
	public:

		typedef SSIE value_type;
		typedef DMAC dmac_type;

	private:

		// SSIE の FIFO は 32 段なので、半分の 16 段で割り込み
		static const uint32_t FIFO_TH = 16;

		SOUND_OUT&	sound_out_;

		enum class FORM : uint8_t {
			I2S,
			LEFT,
			RIGHT,
			TDM,
			MONO
		};

		struct sound_task_t {
			SOUND_OUT&	sound_out_;
			uint32_t	ref_freq_;
			sound_task_t(SOUND_OUT& sound_out, uint32_t ref) : sound_out_(sound_out),
				ref_freq_(ref) { }
		};
		sound_task_t	sound_task_t_;

		static void* sound_task_ptr_;

		static INTERRUPT_FUNC void send_task_()
		{
			auto p = static_cast<sound_task_t*>(sound_task_ptr_);
			uint32_t wpos = p->sound_out_.get_wave_pos();
			wpos += FIFO_TH / 2 * 2;  // オフセット
			wpos &= (p->sound_out_.size() - 1);
			// FIFO の L/R 出２段消費するので８段
			for(uint32_t i = 0; i < (FIFO_TH / 2); ++i) {
				auto w = p->sound_out_.get_wave(wpos);
				SSIE::SSIFTDR16 = w->l_ch;
				SSIE::SSIFTDR16 = w->r_ch;
				++wpos;
				wpos &= (p->sound_out_.size() - 1);
			}
			p->sound_out_.service(FIFO_TH / 2);

			SSIE::SSIFSR.TDE = 0;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	SOUND_OUT	サウンド出力オブジェクト
		*/
		//-----------------------------------------------------------------//
		ssie_io(SOUND_OUT& sound_out) noexcept : 
			sound_out_(sound_out), sound_task_t_(sound_out_, 48'000)
		{
			sound_task_ptr_ = static_cast<void*>(&sound_task_t_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始 @n
					※送信動作、受信動作、ミュート、初期状態を維持
			@param[in]	aclk	オーディオ入力周波数
			@param[in]	lrclk	LR クロック周波数（サンプルレート）
			@param[in]	bform	ビット列フォーマット
			@param[in]	intl	割り込みレベル
			@return 初期化出来ない場合「false」（パラメータの異常など）
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t aclk, uint32_t lrclk, BFORM bform, uint8_t intl) noexcept
		{
			power_mgr::turn(SSIE::PERIPHERAL);

			if(!port_map::turn(SSIE::PERIPHERAL, true)) {
				return false;
			}

			// ソフトリセット
			SSIE::SSIFCR.SSIRST = 1;
			SSIE::SSIFCR.SSIRST = 0;
			while(SSIE::SSIFCR.SSIRST() != 0) {
				utils::delay::loop(1);
			}

			SSIE::SSICR.MST = MASTER;

			uint32_t bits = 0;
			FORM form;
			uint8_t dwl = 0;
			uint8_t swl = 0;
			uint8_t word = 0;
			switch(bform) {
			case BFORM::I2S_16:
				bits = 16 * 2;
				form = FORM::I2S;
				swl = 0b001;  // S:16
				dwl = 0b001;  // D:16
				break;
			case BFORM::I2S_24:
				bits = 32 * 2;
				form = FORM::I2S;
				swl = 0b011;  // S:32
				dwl = 0b101;  // D:24
				break;
			case BFORM::I2S_32:
				bits = 32 * 2;
				form = FORM::I2S;
				swl = 0b011;  // S:32
				dwl = 0b110;  // D:32
				break;
			case BFORM::LEFT_16:
				bits = 16 * 2;
				form = FORM::LEFT;
				swl = 0b001;
				dwl = 0b001;
				break;
			case BFORM::LEFT_24:
				bits = 32 * 2;
				form = FORM::LEFT;
				swl = 0b011;
				dwl = 0b101;
				break;
			case BFORM::LEFT_32:
				bits = 32 * 2;
				form = FORM::LEFT;
				swl = 0b011;
				dwl = 0b110;
				break;
			case BFORM::RIGHT_16:
				bits = 16 * 2;
				form = FORM::RIGHT;
				swl = 0b001;
				dwl = 0b001;
				break;
			case BFORM::RIGHT_24:
				bits = 32 * 2;
				form = FORM::RIGHT;
				swl = 0b011;
				dwl = 0b101;
				break;
			case BFORM::RIGHT_32:
				bits = 32 * 2;
				form = FORM::RIGHT;
				swl = 0b011;
				dwl = 0b110;
				break;
			case BFORM::TDM_2:
				bits = 16 * 2;
				word = 2;
				form = FORM::TDM;
				swl = 0b001;
				dwl = 0b001;
				break;
			case BFORM::TDM_4:
				bits = 16 * 4;
				word = 4;
				form = FORM::TDM;
				swl = 0b001;
				dwl = 0b001;
				break;
			case BFORM::TDM_6:
				bits = 16 * 6;
				word = 6;
				form = FORM::TDM;
				swl = 0b001;
				dwl = 0b001;
				break;
			case BFORM::TDM_8:
				bits = 16 * 8;
				word = 8;
				form = FORM::TDM;
				swl = 0b001;
				dwl = 0b001;
				break;
			default:
				return false;
			}

			auto adiv = aclk / lrclk / bits;
			uint8_t ckdv = 0;
			switch(adiv) {
			case 1:   ckdv = 0b0000; break;
			case 2:   ckdv = 0b0001; break;
			case 4:   ckdv = 0b0010; break;
			case 6:   ckdv = 0b1000; break;
			case 8:   ckdv = 0b0011; break;
			case 12:  ckdv = 0b1001; break;
			case 16:  ckdv = 0b0100; break;
			case 24:  ckdv = 0b1010; break;
			case 32:  ckdv = 0b0101; break;
			case 48:  ckdv = 0b1011; break;
			case 64:  ckdv = 0b0110; break;
			case 96:  ckdv = 0b1100; break;
			case 128: ckdv = 0b0111; break;
			default:
				return false;
			}
			SSIE::SSICR.CKDV = ckdv;

			// Recv/FIFO リセット
			SSIE::SSIFCR.RFRST = 1;
			SSIE::SSIFCR.RFRST = 0;
			while(SSIE::SSIFCR.RFRST() != 0) {
				utils::delay::loop(1);
			}
			// Send/FIFO リセット
			SSIE::SSIFCR.TFRST = 1;
			SSIE::SSIFCR.TFRST = 0;
			while(SSIE::SSIFCR.TFRST() != 0) {
				utils::delay::loop(1);
			}

			// AUDIO_CLK 入力有効（マスター時）
			if(MASTER) {
				SSIE::SSIFCR.AUCKE = 1;
			}

			// 割り込み設定
			if(intl > 0) {
				icu_mgr::set_level(SSIE::TX_VEC, intl);
				icu_mgr::set_task(SSIE::TX_VEC, send_task_);
				SSIE::SSIFCR.TIE = 1;
			} else {
				icu_mgr::set_task(SSIE::TX_VEC, nullptr);
				SSIE::SSIFCR.TIE = 0;
			}

			switch(form) {
			case FORM::I2S:
				SSIE::SSIOFR.OMOD = 0b00;
				SSIE::SSICR.DEL   = 0;
				SSIE::SSICR.LRCKP = 0;
				SSIE::SSICR.SDTA  = 0;
				break;
			case FORM::LEFT:
				SSIE::SSIOFR.OMOD = 0b00;
				SSIE::SSICR.DEL   = 1;
				SSIE::SSICR.LRCKP = 1;
				SSIE::SSICR.SDTA  = 0;
				break;
			case FORM::RIGHT:
				SSIE::SSIOFR.OMOD = 0b00;
				SSIE::SSICR.DEL   = 1;
				SSIE::SSICR.LRCKP = 1;
				SSIE::SSICR.SDTA  = 1;
				break;
			case FORM::TDM:
				SSIE::SSIOFR.OMOD = 0b01;
				SSIE::SSICR.DEL   = 0;
				SSIE::SSICR.LRCKP = 1;
				SSIE::SSICR.SDTA  = 0;
				break;
			case FORM::MONO:
				SSIE::SSIOFR.OMOD = 0b10;
				SSIE::SSICR.DEL   = 0;
				SSIE::SSICR.LRCKP = 1;
				SSIE::SSICR.SDTA  = 0;
				break;
			default:
				return false;
			}

			sound_task_t_.ref_freq_ = lrclk;			

//			SSIE::SSICR.BCKP = 1;

			// フレームのワード数設定 (TDM)
			SSIE::SSICR.FRM = word;

			SSIE::SSICR.DWL = dwl;
			SSIE::SSICR.SWL = swl;

			SSIE::SSIOFR.LRCONT = 1;  // アイドル時にも LRCNT を出力

			// 32 ワード FIFO のバッファリミット値
			SSIE::SSISCR = SSIE::SSISCR.TDES.b(FIFO_TH - 1) | SSIE::SSISCR.RDFS.b(FIFO_TH - 1);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信許可
			@param[in]	ena		「false」なら不許可
			@param[in]	ival	イニシャル値（通常は０）
		*/
		//-----------------------------------------------------------------//
		void enable_send(bool ena = true, int32_t ival = 0) noexcept {
			if(ena && !SSIE::SSICR.TEN()) {  // 送信開始
				for(uint32_t i = 0; i < FIFO_TH; ++i) {  // ダミーデータで半分埋める
					SSIE::SSIFTDR32 = ival;
				}
			}
			SSIE::SSICR.TEN = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  受信許可
			@param[in]	ena		「false」なら不許可
		*/
		//-----------------------------------------------------------------//
		void enable_recv(bool ena = true) noexcept { SSIE::SSICR.REN = ena; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ミュート許可
			@param[in]	ena		「false」ならミュート解除
		*/
		//-----------------------------------------------------------------//
		void enable_mute(bool ena = true) noexcept { SSIE::SSICR.MUEN = ena; }


		//-----------------------------------------------------------------//
		/*!
			@brief  送信数がリミットを超えたか
			@return	送信数がリミットを超えた場合「true」
		*/
		//-----------------------------------------------------------------//
		bool get_send_limit() const noexcept { return SSIE::SSIFSR.TDE(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  TDE を設定
			@param[in]	val		TDE の設定値
		*/
		//-----------------------------------------------------------------//
		void set_send_limit(bool val) const noexcept { SSIE::SSIFSR.TDE = val; }


		//-----------------------------------------------------------------//
		/*!
			@brief  送信数を取得（送信バッファにあるデータ数）
			@return	送信数
		*/
		//-----------------------------------------------------------------//
		uint32_t get_send_num() const noexcept { return SSIE::SSIFSR.TDC(); } 


		//-----------------------------------------------------------------//
		/*!
			@brief  データ送信
			@param[in]	data	送信データ
		*/
		//-----------------------------------------------------------------//
		void send(uint32_t data) noexcept { SSIE::SSIFTDR32 = data; }


		//-----------------------------------------------------------------//
		/*!
			@brief  受信数がリミットを超えたか
			@return	受信数がリミットを超えた場合「true」
		*/
		//-----------------------------------------------------------------//
		bool get_recv_limit() const noexcept { return SSIE::SSIFSR.RDF(); } 


		//-----------------------------------------------------------------//
		/*!
			@brief  受信数を取得（受信バッファにあるデータ数）
			@return	受信数
		*/
		//-----------------------------------------------------------------//
		uint32_t get_recv_num() const noexcept { return SSIE::SSIFSR.RDC(); } 


		//-----------------------------------------------------------------//
		/*!
			@brief  データ受信
			@return	受信データ
		*/
		//-----------------------------------------------------------------//
		auto recv() const noexcept { return SSIE::SSIFRDR32(); }
	};

	// テンプレート関数内、実態の定義
	template <class SSIE, class DMAC, class SOUND_OUT, bool MASTER>
		void* ssie_io<SSIE, DMAC, SOUND_OUT, MASTER>::sound_task_ptr_;
}
