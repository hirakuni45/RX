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
#include "RX600/ssie.hpp"
#include "common/delay.hpp"
#include "sound/sound_out.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SSIE（シリアルサウンドインターフェース）基本クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct ssie_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ビット列フォーマット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class FORM : uint8_t {
			I2S,	///< I2S
			LEFT,	///< 左詰め
			RIGHT,	///< 右詰め
			TDM2,	///< TDM 2 ワード・フォーマット
			TDM4,	///< TDM 4 ワード・フォーマット
			TDM6,	///< TDM 6 ワード・フォーマット
			TDM8,	///< TDM 8 ワード・フォーマット
			MONO,	///< モノラル・フォーマット
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データ・ワード長数
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class D_NUM : uint8_t {
			_8,		///< 8 ビット
			_16,	///< 16 ビット
			_18,	///< 18 ビット
			_20,	///< 20 ビット
			_22,	///< 22 ビット
			_24,	///< 24 ビット
			_32		///< 32 ビット
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システム・ワード長数
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class S_NUM : uint8_t {
			_8,		///<  8 ビット   16Fs
			_16,	///<  16 ビット  32Fs
			_24,	///<  24 ビット  48Fs
			_32,	///<  32 ビット  64Fs
			_48,	///<  48 ビット  96Fs
			_64,	///<  64 ビット 128Fs
			_128,	///< 128 ビット 256Fs
			_256	///< 256 ビット 512Fs
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SSIE（シリアルサウンドインターフェース）制御クラス
		@param[in]	SSIE	ハードウェアー・コンテキスト
		@param[in]	DMAC	DMAC デバイス・コンテキスト(DMAC0 - DMAC7)
		@param[in]	BFS		fifo バッファのサイズ
		@param[in]	OUTS	出力バッファのサイズ（１６の倍数で１２８以上）
		@param[in]	MASTER	スレーブの場合「false」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SSIE, class DMAC, uint32_t BFS, uint32_t OUTS, bool MASTER = true>
	class ssie_io : public ssie_t {
	public:

		typedef SSIE value_type;
		typedef DMAC dmac_type;
		typedef sound_out<BFS, OUTS> SOUND_OUT;

	private:

		SOUND_OUT	sound_out_;

		struct sound_task_t {
			SOUND_OUT&	sound_out_;
			uint32_t	ref_freq_;
			uint32_t	rsmp_freq_;
			uint32_t	timebase_;
			sound_task_t(SOUND_OUT& sound_out, uint32_t ref) : sound_out_(sound_out),
				ref_freq_(ref), rsmp_freq_(ref), timebase_(0) { }
		};
		sound_task_t	sound_task_t_;

		static void* sound_task_ptr_;

		static INTERRUPT_FUNC void send_task_()
		{
			auto p = static_cast<sound_task_t*>(sound_task_ptr_);
			uint32_t wpos = p->sound_out_.get_wave_pos();
			wpos += 8 * 2;  // オフセット
			wpos &= (OUTS - 1);
			uint32_t l = 0;
			for(uint32_t i = 0; i < 8; ++i) {
				auto w = p->sound_out_.get_wave(wpos);
				SSIE::SSIFTDR32 = (static_cast<int32_t>(w->l_ch) - 32767) << 16;
				SSIE::SSIFTDR32 = (static_cast<int32_t>(w->r_ch) - 32767) << 16;
				uint32_t base_freq = 48000;
				p->timebase_ += p->rsmp_freq_;
				if(p->timebase_ >= p->ref_freq_) {
					p->timebase_ -= p->ref_freq_;
					++wpos;
					wpos &= (OUTS - 1);
					++l;
				}
			}
			p->sound_out_.service(l);

			SSIE::SSIFSR.TDE = 0;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ssie_io() noexcept : 
			sound_out_(), sound_task_t_(sound_out_, 48'000) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サンプリング周波数設定
			@param[in]	freq	サンプリング周期
			@return 不正な場合「false」
		*/
		//-----------------------------------------------------------------//
		bool set_sampling_freq(uint32_t freq) noexcept
		{
			if(freq > sound_task_t_.ref_freq_) {
				return false;
			}
			if(freq < 11025) {
				return false;
			}
			sound_task_t_.rsmp_freq_ = freq;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始 @n
					※送信動作、受信動作、ミュート、初期状態を維持
			@param[in]	adiv	AUDIO_CLK の分周値
			@param[in]	form	フォーマット
			@param[in]	dnum	データ数
			@param[in]	snum	システム数
			@param[in]	intl	割り込みレベル
			@return 初期化出来ない場合「false」（パラメータの異常など）
		*/
		//-----------------------------------------------------------------//
		bool start(uint8_t adiv, FORM form, D_NUM dnum, S_NUM snum, uint8_t intl) noexcept
		{
			device::power_mgr::turn(SSIE::PERIPHERAL);

			if(!device::port_map::turn(SSIE::PERIPHERAL, true)) {
				return false;
			}

			sound_task_ptr_ = static_cast<void*>(&sound_task_t_);

			// ソフトリセット
			SSIE::SSIFCR.SSIRST = 1;
			SSIE::SSIFCR.SSIRST = 0;
			while(SSIE::SSIFCR.SSIRST() != 0) {
				utils::delay::loop(1);
			}

			SSIE::SSICR.MST = MASTER;

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
				device::icu_mgr::set_level(SSIE::TX_VEC, intl);
				device::icu_mgr::set_task(SSIE::TX_VEC, send_task_);
				SSIE::SSIFCR.TIE = 1;
			} else {
				device::icu_mgr::set_task(SSIE::TX_VEC, nullptr);
				SSIE::SSIFCR.TIE = 0;
			}

			uint8_t word = 0b00;
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
			case FORM::TDM2:
			case FORM::TDM4:
			case FORM::TDM6:
			case FORM::TDM8:
				SSIE::SSIOFR.OMOD = 0b01;
				SSIE::SSICR.DEL   = 0;
				SSIE::SSICR.LRCKP = 1;
				SSIE::SSICR.SDTA  = 0;
				word = static_cast<uint8_t>(form) - static_cast<uint8_t>(FORM::TDM2);
				break;
			case FORM::MONO:
				SSIE::SSIOFR.OMOD = 0b10;
				SSIE::SSICR.DEL   = 0;
				SSIE::SSICR.LRCKP = 1;
				SSIE::SSICR.SDTA  = 0;
				break;
			}

//			SSIE::SSICR.BCKP = 1;

			// フレームのワード数設定
			SSIE::SSICR.FRM = word;

			SSIE::SSICR.DWL = static_cast<uint8_t>(dnum);
			SSIE::SSICR.SWL = static_cast<uint8_t>(snum);

			SSIE::SSIOFR.LRCONT = 1;  // アイドル時にも LRCNT を出力

			// 32 ワード FIFO のバッファリミット値
			SSIE::SSISCR = SSIE::SSISCR.TDES.b(16 - 1) | SSIE::SSISCR.RDFS.b(16 - 1);

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
				for(uint32_t i = 0; i < 16; ++i) {  // ダミーデータで半分埋める
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


		//-----------------------------------------------------------------//
		/*!
			@brief  SOUND_OUT オブジェクトの参照
			@return	SOUND_OUT オブジェクト
		*/
		//-----------------------------------------------------------------//
		auto& at_sound_out() { return sound_out_; }
	};

	// テンプレート関数内、実態の定義
	template <class SSIE, class DMAC, uint32_t BFS, uint32_t OUTS, bool MASTER>
		void* ssie_io<SSIE, DMAC, BFS, OUTS, MASTER>::sound_task_ptr_;
}

