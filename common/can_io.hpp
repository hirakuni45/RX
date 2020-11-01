#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・CAN I/O 制御 @n
			・CAN クロックは、正確に一致しない場合、エラーとする。@n
			・CAN ポートに、CAN バス・トランシーバーを接続する。@n
			・CAN ペリフェラル内蔵 FIFO 機能は使わない設計とする。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"
#include "common/format.hpp"

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
			uint8_t		rxm_level;		///< RXM 割り込みレベル
			uint8_t		txm_level;		///< TXM 割り込みレベル
			interrupt_t() :
				error_level(0), rxm_level(1), txm_level(1)
			{ }
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  CAN フレームの表示
			@param[in]	src		フレーム
			@param[in]	ht		ヘッダー文字列
		*/
		//-----------------------------------------------------------------//
		static void list(const can_frame& src, const char* ht = "") noexcept
		{
			if(src.get_RTR()) {
				utils::format("%sR: ") % ht;
			} else {
				utils::format("%sD: ") % ht;
			}
			if(src.get_IDE()) {
				uint32_t id = src.get_id();
				utils::format("ID: ext 0x%08X (%u)\n") % id % id;
			} else {
				utils::format("ID: std 0x%03X (%u)\n") % src.get_SID() % src.get_SID();
			}

			auto dlc = src.get_DLC();
			utils::format("%s(%u):") % ht % dlc;
			for(uint32_t i = 0; i < dlc; ++i) {
				utils::format(" %02X") % static_cast<uint16_t>(src.get_DATA(i));
			}
			utils::format("\n");
			utils::format("%sTS: %u\n") % ht % src.get_TS();
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CAN 制御クラス
		@param[in]	CAN		CAN 定義クラス
		@param[in]	RBF		受信バッファクラス (utils::fixed_fifo<can_frame, N>)
		@param[in]	TBF		送信バッファクラス (utils::fixed_fifo<can_frame, N>)
		@param[in]	PSEL	ポート候補
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CAN, class RBF, class TBF, port_map::option PSEL = port_map::option::FIRST>
	class can_io : public can_io_def {
	public:

		static const uint32_t RX_MB_TOP = 0;	///< 受信用メールボックス先頭番号
		static const uint32_t RX_MB_NUM = 8;	///< 受信用メールボックス数（最小８）
		static const uint32_t TX_MB_TOP = 8;	///< 送信用メールボックス先頭番号
		static const uint32_t TX_MB_NUM = 4;	///< 送信用メールボックス数（最小４）

	private:

//		typedef utils::null_format	format;
		typedef utils::format		format;

		interrupt_t		intr_;
		MODE			mode_;

		static RBF		rbf_;
		static TBF		tbf_;

		void sleep_() const { asm("nop"); }


		static INTERRUPT_FUNC void rxm_task_()
		{
			for(uint32_t i = RX_MB_TOP; i < (RX_MB_TOP + RX_MB_NUM); ++i) {
				if(CAN::MCTL[i].NEWDATA() != 0) {
					auto& t = rbf_.put_at();
					CAN::MB[i].get(t);
					rbf_.put_go();
				}
				CAN::MCTL[i] = 0;  // RECREQ を落とす
				CAN::MCTL[i] = 0;  // NEWDATA を落とす
				CAN::MCTL[i] = CAN::MCTL.RECREQ.b(1);  // 再度受信リクエスト
			}
		}

		// 送信完了割り込みエントリー
		static INTERRUPT_FUNC void txm_task_()
		{
			uint32_t i;
			for(i = TX_MB_TOP; i < (TX_MB_TOP + TX_MB_NUM); ++i) {
				if(CAN::MCTL[i].SENTDATA() != 0) {
		   			CAN::MCTL[i] = 0;  // SENTDATA=0 にするには、TRMREQ=0 にして
					CAN::MCTL[i] = 0;  // SENTDATA=0
					break;
				}
			}
			if(tbf_.length() > 0) {
				++i;
				if(i >= (TX_MB_TOP + TX_MB_NUM)) i = TX_MB_TOP;
				const auto& t = tbf_.get_at();
				CAN::MB[i].set(t);
				tbf_.get_go();
				CAN::MCTL[i] = CAN::MCTL.TRMREQ.b(1);
			}
		}

		// ERS 割り込みは、グループ割り込みなので、通常関数とする
		static void ers_task_() {
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		can_io() noexcept : intr_(), mode_(MODE::RESET) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  通信速度を設定して、CAN デバイスを「OPERATION」モードにする @n
					正確な通信速度を設定出来ない場合「false」を返して失敗する。
			@param[in]	speed	通信速度
			@param[in]	intr	割り込み設定
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(SPEED speed, const interrupt_t& intr = interrupt_t()) noexcept
		{
			// 通信速度に対する、TQ 値 8 to 25 で適切な値を選ぶ
			// より大きい値で適合した値を選択
			uint32_t tq = 25;
			while(1) {
				if((F_PCLKB % (static_cast<uint32_t>(speed) * tq)) == 0) {
					break;
				}
				tq--;
				if(tq < 8) {  // 割り切れない場合エラーとする
					format("(1)BRP divider indivisible...\n");
					return false;
				}
			}

			if(!power_mgr::turn(CAN::PERIPHERAL)) {
				format("(2)fail power manager...\n");
				return false;
			}
			if(!port_map::turn(CAN::PERIPHERAL, true, PSEL)) {
				power_mgr::turn(CAN::PERIPHERAL, false);
				format("(3)fail port mapping...\n");
				return false;
			}

			// 動作クロックの設定
			uint32_t brp = F_PCLKB / (static_cast<uint32_t>(speed) * tq);
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
					format("(4)TSEG1 value indivisible...\n");
					return false;
				}

				tseg1--;
				if(tq == (1 + tseg1 + tseg2)) break;
				else if(tseg1 < 4) {
					format("(5)TSEG1 value indivisible...\n");
					return false;
				}

				tseg2--;
				if(tq == (1 + tseg1 + tseg2)) break;
				else if(tseg2 < 2) {
					format("(6)TSEG2 value indivisible...\n");
					return false;
				}
			}
			// SJW (リシンクロナイゼーションジャンプ幅)：
			// フェーズエラーによっておこる位相誤差を補償するために、
			// タイムセグメントを延長または短縮する長さです。
			if(sjw >= tseg2) sjw = tseg2 - 1;  // SJW はなるべく大きい値を維持する。 

			// format("BRP: %u, TSEG1: %u, TESG2: %u\n") % brp % tseg1 % tseg2;
			CAN::CTLR.SLPM = 0;  // BCR レジスタを設定するので、スリープモードを解除
			while(CAN::STR.SLPST() != 0) sleep_();  // スリープモードを抜けた事を確認
			CAN::BCR = CAN::BCR.TSEG1.b(tseg1 - 1) | CAN::BCR.TSEG2.b(tseg2 - 1)
				| CAN::BCR.BRP.b(brp - 1) | CAN::BCR.SJW.b(sjw - 1) | CAN::BCR.CCLKS.b(0);

			for(uint32_t i = 0; i < 8; ++i) {
				CAN::MKR[i] = 0;
			}
			CAN::MKIVLR = 0;  // マスク有効

			// FIFO モードの場合： リモートフレーム、標準ID、拡張ID 受信可能設定
			CAN::CTLR.MBM = 1;
			CAN::FIDCR0 = CAN::FIDCR0.RTR.b(0) | CAN::FIDCR0.IDE.b(0);
			CAN::FIDCR1 = CAN::FIDCR1.RTR.b(1) | CAN::FIDCR1.IDE.b(1);
			CAN::CTLR.MBM = 0;

			// メールボックスを初期化
			for(uint32_t i = 0; i < 32; ++i) {
				CAN::MCTL[i] = 0;  // 一応、MCTL も「０」クリア
				CAN::MCTL[i] = 0;  // 完全にクリアするには、２度書く事が必要
				CAN::MB[i].clear();
				if(i >= RX_MB_TOP && i < (RX_MB_TOP + RX_MB_NUM)) {
					// データフレーム、リモートフレーム受信用
					// 標準ID、拡張ID 受信用
					CAN::MB[i].RTR = i & 1;
					CAN::MB[i].IDE = (i >> 1) & 1;
				}
			}

			intr_ = intr;
			CAN::MIER = 0;
			if(intr.error_level > 0) {
				auto gvec = icu_mgr::get_group_vector(CAN::ERS_VEC);
				if(icu_mgr::get_level(gvec) < intr.error_level) {
					// グループベクタの割り込みレベルがより高い場合は設定する。
					icu_mgr::set_level(gvec, intr.error_level);
				}
				icu_mgr::install_group_task(CAN::ERS_VEC, ers_task_);
			    CAN::EIER = CAN::EIER.ORIE.b(1);
			}
			if(intr.rxm_level > 0) {  // 受信割り込み設定
				icu_mgr::set_interrupt(CAN::RXM_VEC, rxm_task_, intr.rxm_level);
				for(uint32_t i = RX_MB_TOP; i < (RX_MB_TOP + RX_MB_NUM); ++i) {
					CAN::MIER.set(i);
				}
			}
			if(intr.txm_level > 0) {  // 送信割り込み設定
				icu_mgr::set_interrupt(CAN::TXM_VEC, txm_task_, intr.txm_level);
				for(uint32_t i = TX_MB_TOP; i < (TX_MB_TOP + TX_MB_NUM); ++i) {
					CAN::MIER.set(i);
				}
			}

			// CAN オペレーションモードに移行
			uint8_t idfm = 0b10;  // 標準 ID モード、拡張 ID モード、ミックス
			uint8_t bom  = 0b00;  // ISO 11898-1 規格、バスオフ復帰モード
			bool tpm = 1;  // メールボックス番号優先送信モード
			CAN::CTLR = CAN::CTLR.CANM.b(0b00) | CAN::CTLR.SLPM.b(0) | CAN::CTLR.IDFM.b(idfm)
				| CAN::CTLR.BOM.b(bom) | CAN::CTLR.TPM.b(tpm);

			// CAN オペレーションモードに移行するまで待機
			while(CAN::STR.RSTST() != 0 || CAN::STR.HLTST() != 0) {
				sleep_();
			} 
			mode_ = MODE::OPERATION;

			// 受信メールボックス設定
			for(uint32_t i = RX_MB_TOP; i < (RX_MB_TOP + RX_MB_NUM); ++i) {
				CAN::MCTL[i].RECREQ = 1;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み設定を返す
			@return 割り込み設定
		*/
		//-----------------------------------------------------------------//
		auto get_interrupt() const noexcept { return intr_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  動作モードを返す
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
			return F_PCLKB
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
			@brief  メールボックス制御をリセットする
			@param[in]	idx		メールボックス番号（０～３１）
		*/
		//-----------------------------------------------------------------//
		void reset_mb(uint32_t idx) noexcept
		{
			CAN::MCTL[idx] = 0;
			CAN::MCTL[idx] = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックス制御の状態を検査
			@param[in]	idx		メールボックス番号（０～３１）
			@return メールボックスが有効なら「true」
		*/
		//-----------------------------------------------------------------//
		bool probe_mb(uint32_t idx) noexcept
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
		bool send_mb(uint32_t idx, bool one = 0) noexcept
		{
			reset_mb(idx);
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
		bool recv_mb(uint32_t idx, bool one = 0) noexcept
		{
			reset_mb(idx);
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
		uint8_t stat_mb(uint32_t idx) noexcept
		{
			return CAN::MCTL[idx]();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックスを設定
			@param[in]	idx		メールボックス番号（０～３１）
			@param[in]	frm		フレーム
		*/
		//-----------------------------------------------------------------//
		void set_mb(uint32_t idx, const can_frame& frm) noexcept
		{
			auto& mb = CAN::MB[idx];
			mb.set(frm);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックスの参照
			@param[in]	idx		メールボックス番号（０～３１）
			@return メールボックス
		*/
		//-----------------------------------------------------------------//
		auto& at_mb(uint32_t idx) noexcept
		{
			return CAN::MB[idx];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックスの表示
			@param[in]	idx		メールボックス番号（０～３１）
			@param[in]	ht		ヘッダー文字列
		*/
		//-----------------------------------------------------------------//
		void list_mb(uint32_t idx, const char* ht = "") noexcept
		{
			can_frame src;
			CAN::MB[idx].get(src);
			list(src, ht);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メールボックス制御の参照
			@param[in]	idx		メールボックス番号（０～３１）
			@return メールボックス制御
		*/
		//-----------------------------------------------------------------//
		auto& at_mb_ctrl(uint32_t idx) noexcept
		{
			return CAN::MCTL[idx];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  データ送信 @n
					送信割り込みレベルを必ず設定する事（割り込み無しでは動作しない） @n
					src が「nullptr」、又は「len」が「０」の場合、リモートフレーム送信。
			@param[in]	id		SID+EID の ID
			@param[in]	src		送信データポインター
			@param[in]	len		送信データ数
			@param[in]	ide		拡張モードの場合「true」
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool send(uint32_t id, const void* src, uint32_t len, bool ide = false) noexcept
		{
			// バッファサイズが、最大容量の 15/16 を超えたら、「1」に戻るまで待つ。
			if(tbf_.length() > (tbf_.size() - (tbf_.size() / 16))) {
				while(tbf_.length() > 1) sleep_();
			}

			auto& t = tbf_.put_at();
			t.set_id(id);
			t.set_IDE(ide);
			if(src != nullptr && len > 0 && len <= 8) {
				t.set_RTR(0);
				t.set_DLC(len);
				auto* p = static_cast<const uint8_t*>(src);
				for(uint32_t i = 0; i < len; ++i) {
					t.set_DATA(i, p[i]);
				}
			} else {
				t.set_RTR(1);
				t.set_DLC(0);
			}
			tbf_.put_go();

			uint32_t n = 0;
			for(uint32_t i = TX_MB_TOP; i < (TX_MB_TOP + TX_MB_NUM); ++i) {
				if(CAN::MCTL[i]() == 0) ++n;
			}
			if(n == TX_MB_NUM) {  // 送信が完全に停止中なら送信トリガを出す
				const auto& t = tbf_.get_at();
				CAN::MB[TX_MB_TOP].set(t);
				tbf_.get_go();
				CAN::MCTL[TX_MB_TOP] = CAN::MCTL.TRMREQ.b(1);
			}

			return true;
		} 


		//-----------------------------------------------------------------//
		/*!
			@brief  受信数の取得
			@return 受信数
		*/
		//-----------------------------------------------------------------//
		uint32_t get_recv_num() const { return rbf_.length(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  受信データの取得
			@return 受信データ
		*/
		//-----------------------------------------------------------------//
		auto get_recv_frame() { return rbf_.get(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  CAN を無効にしてパワーダウンする @n
					・割り込みを解除する
			@param[in]	power パワーダウンをしない場合「false」
		*/
		//-----------------------------------------------------------------//
		void destroy(bool power = true) noexcept
		{
			CAN::MIER = 0;
			icu_mgr::set_interrupt(CAN::RXM_VEC, nullptr, 0);
			icu_mgr::set_interrupt(CAN::TXM_VEC, nullptr, 0);

			CAN::CTLR = CAN::CTLR.CANM.b(0b11);  // CAN リセットモード（強制） 

			if(power) {
				power_mgr::turn(CAN::PERIPHERAL, false);
			}
		}
	};

	template <class CAN, class RBF, class TBF, port_map::option PSEL>
		RBF can_io<CAN, RBF, TBF, PSEL>::rbf_;
	template <class CAN, class RBF, class TBF, port_map::option PSEL>
		TBF can_io<CAN, RBF, TBF, PSEL>::tbf_;
}
