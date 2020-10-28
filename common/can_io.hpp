#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・CAN I/O 制御 @n
			・CAN クロックは、正確に一致しない場合、エラーとなる。@n
			・CAN ポートに、CAN バス・トランシーバーを接続する。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

#ifndef F_PCLKB
#  error "can_io.hpp requires F_PCLKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CAN 制御定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class can_io_def {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CAN スピード型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SPEED {
			_50K  =    50'000,	///<  50 Kbps（標準ではない）
			_100K =   100'000,	///< 100 Kbps（標準ではない）
			_125K =   125'000,	///< 125 Kbps
			_250K =   250'000,	///< 250 Kbps
			_500K =   500'000,	///< 500 Kbps
			_750K =   750'000,	///< 750 Kbps（標準ではない）
			_1M   = 1'000'000	///< 1 Mbps
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CAN モード型（動作モード）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class MODE : uint8_t {
			RESET,		///< リセット・モード
			HALT,		///< Halt モード
			OPERATION,	///< オペレーション・モード
			SLEEP		///< スリープ・モード
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み設定
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct interrupt_t {
			uint8_t		error_level;	///< エラー割り込みレベル
			uint8_t		rxf_level;		///< RXF 割り込みレベル
			uint8_t		txf_level;		///< TXF 割り込みレベル
			uint8_t		rxm_level;		///< RXM 割り込みレベル
			uint8_t		txm_level;		///< TXM 割り込みレベル
			interrupt_t() :
				error_level(0), rxf_level(0), txf_level(0), rxm_level(0), txm_level(0)
			{ }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CAN フレーム・クラス @n
					・データフレームはデータ転送、DLC が０以外 @n
					・リモートフレームは、データ転送要求フレーム、DLC が０
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct frame {

			uint32_t	id;			// SID(11 bits) + EID(29 bits)

			bool		rtr;		// RTR 0:データフレーム、1:リモートフレーム
			bool		ide;		// IDE 0:標準 ID、1:拡張 ID

			uint8_t		dlc;		// DLC 0 - 8 データ長コード
			uint8_t		data[8];	// DATA0 - DATA8 データバイト
			uint16_t	ts;			// TS タイムスタンプ

			frame() noexcept : id(0), rtr(0), ide(0), data{ 0 }, ts(0)
			{ }


			//-------------------------------------------------------------//
			/*!
				@brief  メールボックス型から取得
				@param[in]	src	ソース
			*/
			//-------------------------------------------------------------//
			void get(volatile const uint32_t* src) noexcept
			{
				id = ((src[0] & 0x1ffc0000) >> 18) | (src[0] & 0x0003ffff) << 18;
				rtr = (src[0] >> 30) & 1;
				ide = (src[0] >> 31) & 1;
				dlc = (src[1] >> 16) & 15;
				data[0] = src[1] >> 8;
				data[1] = src[1];
				data[2] = src[2] >> 24;
				data[3] = src[2] >> 16;
				data[4] = src[2] >> 8;
				data[5] = src[2];
				data[6] = src[3] >> 24;
				data[7] = src[3] >> 16;
				ts = src[3];
			}


			//-------------------------------------------------------------//
			/*!
				@brief  メールボックス型へ設定
				@param[in]	dst	先
			*/
			//-------------------------------------------------------------//
			void put(volatile uint32_t* dst) const noexcept
			{
				dst[0] = (ide << 31) | (rtr << 30) | ((id & 0x7ff) << 18) | (id >> 18);
				dst[1] = (dlc << 16) | (data[0] << 8) | data[1];
				dst[2] = (data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5];
				dst[3] = (data[6] << 24) | (data[7] << 16) | ts;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  フレーム内容表示
			*/
			//-------------------------------------------------------------//
			void list() noexcept
			{
				if(ide) {
					utils::format("ID: ext 0x%08X (%u)\n") % id % id;
				} else {
					utils::format("ID: std 0x%03X (%u)\n") % id % id;
				}
				if(!rtr) {  // data frame
					utils::format("DATA(%u):") % static_cast<uint16_t>(dlc & 0xf);
					for(uint8_t i = 0; i < (dlc & 0xf); ++i) {
						utils::format(" %02X") % static_cast<uint16_t>(data[i]);
					}
					utils::format("\n");
				} else {
					utils::format("DATA(0):\n");
				}
				utils::format("TS: %u\n") % ts;
			}		
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class INTR_TYPE : uint8_t {
			RXM,	///< RXM 割り込み型
			TXM,	///< TXM 割り込み型
			RXF,	///< RXF 割り込み型
			TXF,	///< TXF 割り込み型
			ERS,	///< ERS 割り込み型
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  無効・割り込みタスククラス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		class null_task {
		public:
			//-------------------------------------------------------------//
			/*!
				@brief  ファンクタ定義
				@param[in]	per		CAN ペリフェラル型
				@param[in]	it		割り込み型
			*/
			//-------------------------------------------------------------//
			void operator () (peripheral per, INTR_TYPE it) { }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CAN メールボックス・プロパティ・クラス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct mb_property {

			uint32_t	match_num_;
			uint32_t	send_num_;
			uint32_t	match_id_[32];

			//-------------------------------------------------------------//
			/*!
				@brief  コンストラクタ
				@param[in]	match_num	受信マッチメールボックス数（標準０個）
				@param[in]	send_num	送信メールボックス数（標準４個）
			*/
			//-------------------------------------------------------------//
			mb_property(uint32_t match_num = 0, uint32_t send_num = 4) :
				match_num_(match_num), send_num_(send_num), match_id_{ 0 } { } 
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CAN 制御クラス
		@param[in]	CAN		CAN 定義クラス
		@param[in]	PSEL	ポート候補
		@param[in]	ITASK	割り込みタスク
		@param[in]	EXTAL	EXTAL クロックを選択する場合「true」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CAN, port_map::option PSEL = port_map::option::FIRST,
		class ITASK = can_io_def::null_task, bool EXTAL = false>
	class can_io : public can_io_def {
	public:

	private:

//		typedef utils::null_format	format;
		typedef utils::format		format;

		MODE			mode_;
		bool			ext_id_;

		static ITASK	itask_;

		void sleep_() const { asm("nop"); }

		static INTERRUPT_FUNC void rxf_task_() {
			itask_(CAN::PERIPHERAL, INTR_TYPE::RXF);
		}

		static INTERRUPT_FUNC void txf_task_() {
			itask_(CAN::PERIPHERAL, INTR_TYPE::TXF);
		}

		static INTERRUPT_FUNC void rxm_task_() {
			itask_(CAN::PERIPHERAL, INTR_TYPE::RXM);
		}

		static INTERRUPT_FUNC void txm_task_() {
			itask_(CAN::PERIPHERAL, INTR_TYPE::TXM);
		}

		// ERS 割り込みは、グループ割り込みなので、通常関数とする
		static void ers_task_() {
			itask_(CAN::PERIPHERAL, INTR_TYPE::ERS);
		}

		static uint32_t get_can_clock_()
		{
			if(EXTAL) {
				// 外部接続周波数を取得する機構が必要・・・
				return 12'000'000;
			} else {
				return F_PCLKB;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		can_io() noexcept : mode_(MODE::RESET), ext_id_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  通信速度を設定して、CAN デバイスを「OPERATION」モードにする @n
					正確な通信速度を設定出来ない場合「false」を返して失敗する。
			@param[in]	speed	通信速度
			@param[in]	prop	メールボックスのプロパティ定義
			@param[in]	intr	割り込み設定
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(SPEED speed, const mb_property& prop = mb_property(), const interrupt_t& intr = interrupt_t()) noexcept
		{
			// 通信速度に対する、TQ 値 8 to 25 で適切な値を選ぶ
			// より大きい値で適合した値を選択
			uint32_t tq = 25;
			while(1) {
				if((get_can_clock_() % (static_cast<uint32_t>(speed) * tq)) == 0) {
					break;
				}
				tq--;
				if(tq < 8) {  // 割り切れない場合エラーとする
					format("(1)BRP divider indivisible...\n");
					return false;
				}
			}

			power_mgr::turn(CAN::PERIPHERAL);
			if(!port_map::turn(CAN::PERIPHERAL, true, PSEL)) {
				power_mgr::turn(CAN::PERIPHERAL, false);
				format("(2)fail port mapping...\n");
				return false;
			}

			// 動作クロックの設定
			uint32_t brp = get_can_clock_() / (static_cast<uint32_t>(speed) * tq);
			uint32_t tseg1 = 16;
			uint32_t tseg2 = 8;
			uint32_t sjw = 4;  // とりあえず固定
			// TSEG1(4 to 16) > TSEG2(2 to 8) ≧ SJW(1 to 4)
			// TQ = 1 + TSEG1 + TSEG2;
			// 上記の関係性から、それぞれ選択
			while(1) {
				if(tq == (1 + tseg1 + tseg2)) break;

				tseg1--;
				if(tq == (1 + tseg1 + tseg2)) break;
				else if(tseg1 < 4) {
					format("(3)TSEG1 value indivisible...\n");
					return false;
				}

				tseg1--;
				if(tq == (1 + tseg1 + tseg2)) break;
				else if(tseg1 < 4) {
					format("(4)TSEG1 value indivisible...\n");
					return false;
				}

				tseg2--;
				if(tq == (1 + tseg1 + tseg2)) break;
				else if(tseg2 < 2) {
					format("(5)TSEG2 value indivisible...\n");
					return false;
				}
			}
			// • SJW (リシンクロナイゼーションジャンプ幅)：
			// フェーズエラーによっておこる位相誤差を補償するために、
			// タイムセグメントを延長または短縮する長さです。
			if(sjw >= tseg2) sjw = tseg2 - 1;  // SJW はなるべく大きい値にする。 

			// format("BRP: %u, TSEG1: %u, TESG2: %u\n") % brp % tseg1 % tseg2;
			CAN::CTLR.SLPM = 0;  // BCR レジスタを設定するので、スリープモードを解除
			CAN::BCR = CAN::BCR.TSEG1.b(tseg1 - 1) | CAN::BCR.TSEG2.b(tseg2 - 1)
				| CAN::BCR.BRP.b(brp - 1) | CAN::BCR.SJW.b(sjw - 1) | CAN::BCR.CCLKS.b(EXTAL);

			for(uint32_t i = 0; i < 8; ++i) {
				CAN::MKR[i] = 0;
			}
			CAN::MKIVLR = 0;  // マスク有効

			CAN::MIER = 0;  // 割り込み許可
			if(intr.error_level > 0) {
				auto gvec = icu_mgr::get_group_vector(CAN::ERS_VEC);
				if(icu_mgr::get_level(gvec) < intr.error_level) {
					// グループベクタの割り込みレベルがより高い場合は設定する。
					icu_mgr::set_level(gvec, intr.error_level);
				}
				icu_mgr::install_group_task(CAN::ERS_VEC, ers_task_);
			    CAN::EIER = CAN::EIER.ORIE.b(1);
			}
			if(intr.rxf_level > 0) {
				icu_mgr::set_interrupt(CAN::RXF_VEC, rxf_task_, intr.rxf_level);
			}
			if(intr.txf_level > 0) {
				icu_mgr::set_interrupt(CAN::TXF_VEC, txf_task_, intr.txf_level);
			}
			if(intr.rxm_level > 0) {
				icu_mgr::set_interrupt(CAN::RXM_VEC, rxm_task_, intr.rxm_level);
			}
			if(intr.txm_level > 0) {
				icu_mgr::set_interrupt(CAN::TXM_VEC, txm_task_, intr.txm_level);
			}

			// CAN オペレーションモードに移行
			uint8_t idfm = 0b10;  // 標準 ID モード、拡張 ID モード、ミックス
			uint8_t bom  = 0b00;  // ISO 11898-1 規格、バスオフ復帰モード
			CAN::CTLR = CAN::CTLR.CANM.b(0b00) | CAN::CTLR.SLPM.b(0) | CAN::CTLR.IDFM.b(idfm)
				| CAN::CTLR.BOM.b(bom);

			// メールボックスをクリア
			for(uint32_t i = 0; i < (4 * 32); ++i) {
				CAN::MB[i] = 0;
			}

			// 受信 FIFO 開始
			// CAN::RFCR.RFE = 1;

			// 送信 FIFO 開始
			// CAN::TFCR.TFE = 1;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  動作モードを返す。
			@return 動作モード
		*/
		//-----------------------------------------------------------------//
		auto get_mode() const noexcept { return mode_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  BRP カウントを返す（レジスタの値ではない）
			@return TSEG1 カウント
		*/
		//-----------------------------------------------------------------//
		uint32_t get_bcr_brp() const noexcept { return CAN::BCR.BRP() + 1; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TSEG1 カウントを返す（レジスタの値ではない）
			@return TSEG1 カウント
		*/
		//-----------------------------------------------------------------//
		uint32_t get_bcr_tseg1() const noexcept { return CAN::BCR.TSEG1() + 1; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TSEG2 カウントを返す（レジスタの値ではない）
			@return TSEG2 カウント
		*/
		//-----------------------------------------------------------------//
		uint32_t get_bcr_tseg2() const noexcept { return CAN::BCR.TSEG2() + 1; }


		//-----------------------------------------------------------------//
		/*!
			@brief  SJW カウントを返す（レジスタの値ではない）
			@return SJW カウント
		*/
		//-----------------------------------------------------------------//
		uint32_t get_bcr_sjw() const noexcept { return CAN::BCR.SJW() + 1; }


		//-----------------------------------------------------------------//
		/*!
			@brief  通信速度を返す
			@return 通信速度
		*/
		//-----------------------------------------------------------------//
		uint32_t get_speed() const noexcept {
			return get_can_clock_()
				/ (get_bcr_brp() * (1 + get_bcr_tseg1() + get_bcr_tseg2()));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  受信エラーカウントを返す
			@return 受信エラーカウント
		*/
		//-----------------------------------------------------------------//
		uint8_t get_recv_error_count() const noexcept {
			return CAN::RECR();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信エラーカウントを返す
			@return 送信エラーカウント
		*/
		//-----------------------------------------------------------------//
		uint8_t get_send_error_count() const noexcept {
			return CAN::TECR();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  フレームを取得
			@param[in]	idx		メールボックス番号（０～３１）
			@param[in]	dst		ディストネーションフレームの参照
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool get_frame(uint32_t idx, frame& dst) noexcept
		{
			if(idx < 32) {
				dst.get(const_cast<const uint32_t*>(&CAN::MB[idx * 4]));
				return true;
			} else {
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  フレームを設定
			@param[in]	idx		メールボックス番号（０～３１）
			@param[in]	src		ソースフレームの参照
			@return メールボックス
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool put_frame(uint32_t idx, const frame& src) noexcept
		{
			if(idx < 32) {
				src.put(&CAN::MB[idx * 4]);
				return true;
			} else {
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  拡張 ID モードを有効にする
			@param[in]	ena		無効なら「false」
		*/
		//-----------------------------------------------------------------//
		void enable_ext(bool ena = true) noexcept { ext_id_ = ena; }


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックス制御をリセットする
			@param[in]	idx		メールボックス番号（０～３１）
		*/
		//-----------------------------------------------------------------//
		void reset_box(uint32_t idx) noexcept
		{
			CAN::MCTL[idx] = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックス制御の状態を検査
			@param[in]	idx		メールボックス番号（０～３１）
			@return メールボックスが有効なら「true」
		*/
		//-----------------------------------------------------------------//
		bool probe_box(uint32_t idx) noexcept
		{
			return CAN::MCTL[idx].TRMREQ() | CAN::MCTL[idx].RECREQ();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックスを送信設定
			@param[in]	idx		メールボックス番号（０～３１）
			@param[in]	one		ワンショット送信の場合「true」
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool send_box(uint32_t idx, bool one = 0) noexcept
		{
//			CAN::MCTL[idx].TRMREQ = 0;
			CAN::MCTL[idx] = 0;
			while(CAN::MCTL[idx]() != 0) sleep_();
			CAN::MCTL[idx] = CAN::MCTL.TRMREQ.b(1) | CAN::MCTL.ONESHOT.b(one);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックスを受信設定
			@param[in]	idx		メールボックス番号（０～３１）
			@param[in]	one		ワンショット受信の場合「true」
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool recv_box(uint32_t idx, bool one = 0) noexcept
		{
//			CAN::MCTL[idx].RECREQ = 0;
			CAN::MCTL[idx] = 0;
			while(CAN::MCTL[idx]() != 0) sleep_();
			CAN::MCTL[idx] = CAN::MCTL.RECREQ.b(1) | CAN::MCTL.ONESHOT.b(one);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックス制御の状態を取得
			@param[in]	idx		メールボックス番号（０～３１）
			@return 状態
		*/
		//-----------------------------------------------------------------//
		uint8_t stat_box(uint32_t idx) noexcept
		{
			return CAN::MCTL[idx]();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックス制御の参照
			@param[in]	idx		メールボックス番号（０～３１）
			@return メールボックス制御
		*/
		//-----------------------------------------------------------------//
		auto& at_box_ctrl(uint32_t idx) noexcept
		{
			return CAN::MCTL[idx];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CAN を無効にしてパワーダウンする @n
					・割り込みを解除する
			@param[in]	power パワーダウンをしない場合「false」
		*/
		//-----------------------------------------------------------------//
		void destroy(bool power = true) noexcept
		{


			if(power) {
				power_mgr::turn(CAN::PERIPHERAL, false);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み TASK クラスの参照
			@return 割り込み TASK クラス
		*/
		//-----------------------------------------------------------------//
		static ITASK& at_itask() noexcept { return itask_; }
	};

	template <class CAN, port_map::option PSEL, class ITASK, bool EXTAL> ITASK
		can_io<CAN, PSEL, ITASK, EXTAL>::itask_;
}
