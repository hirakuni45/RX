#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・RSCI I/O 制御（調歩同期モード） @n
			※内臓の FIFO バッファを利用しない実装（扱いにくいので利用しない）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"
#include "common/sci_io_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSCI I/O 制御クラス
		@param[in]	RSCI	RSCI 定義クラス
		@param[in]	RBF		受信バッファクラス
		@param[in]	SBF		送信バッファクラス
		@param[in]	PSEL	ポート選択
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RSCI, class RBF, class SBF, port_map::ORDER PSEL = port_map::ORDER::FIRST>
	class rsci_io : public sci_io_base {

		static_assert(RBF::size() > 8, "Receive buffer is too small.");
		static_assert(SBF::size() > 8, "Transmission buffer is too small.");

	public:
		typedef RSCI sci_type;
		typedef RBF  rbf_type;
		typedef SBF  sbf_type;

	private:
		static inline RBF	recv_;
		static inline SBF	send_;
		static inline volatile uint8_t	orer_cnt_;
		static inline volatile uint8_t	per_cnt_;
		static inline volatile uint8_t	fer_cnt_;

		ICU::LEVEL	level_;
		bool		auto_crlf_;
		uint32_t	baud_;

		// ※必要なら、実装する
		void sleep_() { asm("nop"); }

		static inline void eri_task_()
		{
			// オーバランエラー状態確認
			if(RSCI::SSR.ORER()) {
				RSCI::SSCR.ORERC = 1;
				++orer_cnt_;
			}
			// フレーミングエラー
			if(RSCI::SSR.DFER()) {
				RSCI::SSCR.DFERC = 1;
				++fer_cnt_;
			}
			// パリティエラー状態確認
			if(RSCI::SSR.DPER()) {
				RSCI::SSCR.DPERC = 1;
				++per_cnt_;
			}
			volatile uint8_t rd = RSCI::RDR();
		}

		static INTERRUPT_FUNC void eri_itask_()
		{
			eri_task_();
		}

		static INTERRUPT_FUNC void rxi_task_()
		{
			volatile uint8_t rd = RSCI::RDR.RDAT();
			recv_.put(rd);
		}

		static INTERRUPT_FUNC void txi_task_()
		{
			if(send_.length() > 0) {
				RSCI::TDR.TDAT = send_.get();
			} else {
				RSCI::SCR0.TIE = 0;
			}
		}

		void set_intr_() noexcept
		{
			if(level_ != ICU::LEVEL::NONE) {
				icu_mgr::set_interrupt(RSCI::RXI, rxi_task_, level_);
				icu_mgr::set_interrupt(RSCI::TXI, txi_task_, level_);
				{  // エラー割り込みの設定
					auto gv = icu_mgr::get_group_vector(RSCI::ERI);
					if(gv == ICU::VECTOR::NONE) {  // not group vector
						icu_mgr::set_interrupt(RSCI::ERI, eri_itask_, level_);
					} else {  // for group vector
						icu_mgr::set_interrupt(RSCI::ERI, eri_task_, level_);
					}
				}
			} else {
				icu_mgr::set_interrupt(RSCI::RXI, nullptr, level_);
				icu_mgr::set_interrupt(RSCI::TXI, nullptr, level_);
				icu_mgr::set_interrupt(RSCI::ERI, nullptr, level_);
			}
		}

		static constexpr bool calc_rate_(uint32_t baud,
			uint8_t& brr_, uint8_t& cks_, uint8_t& mddr_, bool& abcs_, bool& bgdm_, bool& brme_) noexcept
		{
			// BGDM が使える場合、1/8 スタート
			uint32_t mtx = 8;
			uint32_t limit = 1024;
			if(!RSCI::SEMR_BGDM) {  // BGDM が使えない場合 1/16 スタート
				mtx = 16;
				limit = 512;
			}
			uint32_t brr = RSCI::PCLK / mtx / baud;
			uint8_t cks = 0;
			while(brr > limit) {
				brr >>= 2;
				++cks;
				if(cks >= 4) {  // 範囲外の速度（低速）
					return false;
				}
			}

			// BGDM フラグの設定
			bool bgdm = true;
			if(RSCI::SEMR_BGDM) {
				if(brr > 512) { brr >>= 1; bgdm = false; mtx <<= 1; }
			} else {
				bgdm = false;
			}
			bool abcs = true;
			if(brr > 256) { brr >>= 1; abcs = false; mtx <<= 1; }

			bool brme = false;
			mddr_ = 0xff;
			if(RSCI::SEMR_BRME) {  // 微調整機能が使える場合
				uint32_t rate = RSCI::PCLK / mtx / brr / (1 << (cks * 2));
				uint32_t mddr = (baud << 9) / rate;
				++mddr;
				mddr >>= 1;
				if(mddr >= 128 && mddr < 256) {  // 微調整を行う場合
					mddr_ = mddr;
					brme = true;
				}
			}

			brr_ = brr;
			cks_ = cks;
			abcs_ = abcs;
			bgdm_ = bgdm;
			brme_ = brme;
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	crlf	LF 時、CR の送出をしない場合「false」
		*/
		//-----------------------------------------------------------------//
		rsci_io(bool crlf = true) noexcept : level_(ICU::LEVEL::NONE), auto_crlf_(crlf), baud_(0)
		{
			orer_cnt_ = 0;
			fer_cnt_ = 0;
			per_cnt_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ORER エラー数の取得
			@return ORER エラー数
		 */
		//-----------------------------------------------------------------//
		static auto get_orer_count() noexcept { return orer_cnt_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	FER エラー数の取得
			@return FER エラー数
		 */
		//-----------------------------------------------------------------//
		static auto get_fer_count() noexcept { return fer_cnt_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	PER エラー数の取得
			@return PER エラー数
		 */
		//-----------------------------------------------------------------//
		static auto get_per_count() noexcept { return per_cnt_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	LF 時、CR 自動送出
			@param[in]	f	「false」なら無効
		 */
		//-----------------------------------------------------------------//
		void auto_crlf(bool f = true) noexcept { auto_crlf_ = f; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ボーレートの設定誤差を検証 @n
					8 ビット 1 ストップビット、パリティ無しの場合、限界は 3.9% 程度
			@param[in]	baud	ボーレート
			@param[in]	thper	許容誤差（標準値は 3.2%） @n
						100 分率を 10 倍した値を設定
			@return 誤差範囲なら「true」
		 */
		//-----------------------------------------------------------------//
		static constexpr bool probe_baud(uint32_t baud, uint32_t thper = 32) noexcept
		{
			uint8_t brr = 0;
			uint8_t cks = 0;
			uint8_t mddr = 0;
			bool abcs = false;
			bool bgdm = false;
			bool brme = false;
			if(!calc_rate_(baud, brr, cks, mddr, abcs, bgdm, brme)) {
				return false;
			}

			uint32_t mtx = 8;
			if(RSCI::SEMR_BGDM) {
				if(!bgdm) mtx <<= 1;
			} else {
				mtx <<= 1;
			}
			if(!abcs) mtx <<= 1;
			auto cbaud = RSCI::PCLK / mtx / (1 << (static_cast<uint32_t>(cks) * 2)) / static_cast<uint32_t>(brr);
			if(brme) {
				cbaud *= mddr;
				cbaud /= 256;
			}

			auto d = baud * thper;
			if((cbaud * 1000) < (baud * 1000 - d) || (baud * 1000 + d) < (cbaud * 1000)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ボーレートを設定して、SCI を有効にする
			@param[in]	baud	ボーレート
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@param[in]	prot	通信プロトコル（指定無しの場合、８ビット、パリティ無し、１ストップビット）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t baud, ICU::LEVEL level = ICU::LEVEL::NONE, PROTOCOL prot = PROTOCOL::B8_N_1S) noexcept
		{
			uint8_t brr;
			uint8_t cks;
			uint8_t mddr;
			bool abcs;
			bool bgdm;
			bool brme;
			if(!calc_rate_(baud, brr, cks, mddr, abcs, bgdm, brme)) {
				return false;
			}

			level_ = level;

			RSCI::SCR0 = 0x0000;	// TE, RE disable.

			port_map::turn(RSCI::PERIPHERAL, true, PSEL);

			power_mgr::turn(RSCI::PERIPHERAL);

			set_intr_();

			bool stop = 0;  // STOP
			bool pm = 0;  // PM
			bool pe = 0;  // PE
			bool chr = 0;  // CHR
			switch(prot) {
			case PROTOCOL::B7_N_1S:
				chr = 1;
			case PROTOCOL::B8_N_1S:
				stop = 0;
				pm = 0;
				pe = 0;
				break;
			case PROTOCOL::B7_E_1S:
				chr = 1;
			case PROTOCOL::B8_E_1S:
				stop = 0;
				pm = 0;
				pe = 1;
				break;
			case PROTOCOL::B7_O_1S:
				chr = 1;
			case PROTOCOL::B8_O_1S:
				stop = 0;
				pm = 1;
				pe = 1;
				break;
			case PROTOCOL::B7_N_2S:
				chr = 1;
			case PROTOCOL::B8_N_2S:
				stop = 1;
				pm = 0;
				pe = 0;
				break;
			case PROTOCOL::B7_E_2S:
				chr = 1;
			case PROTOCOL::B8_E_2S:
				stop = 1;
				pm = 0;
				pe = 1;
				break;
			case PROTOCOL::B7_O_2S:
				chr = 1;
			case PROTOCOL::B8_O_2S:
				stop = 1;
				pm = 1;
				pe = 1;
				break;
			default:
				return false;
			}
			RSCI::SCR1.PE = pe;
			RSCI::SCR1.PM = pm;
			RSCI::SCR3.CHR = chr;
			RSCI::SCR3.STOP = stop;

			if(brr) --brr;
			RSCI::SCR2 = RSCI::SCR2.CKS.b(cks) | RSCI::SCR2.MDDR.b(mddr) | RSCI::SCR2.BRR.b(brr)
					   | RSCI::SCR2.ABCS.b(abcs) | RSCI::SCR2.BGDM.b(bgdm) | RSCI::SCR2.BRME.b(brme);

			if(level_ != ICU::LEVEL::NONE) {
				RSCI::SCR0 = RSCI::SCR0.RIE.b() | RSCI::SCR0.TE.b() | RSCI::SCR0.RE.b();
			} else {
				RSCI::SCR0 = RSCI::SCR0.TE.b() | RSCI::SCR0.RE.b();
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ボーレート型を使い SCI を有効にする
			@param[in]	baud	ボーレート型
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@param[in]	prot	通信プロトコル（標準は、８ビット、パリティ無し、１ストップ）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(BAUDRATE baud, ICU::LEVEL level = ICU::LEVEL::NONE, PROTOCOL prot = PROTOCOL::B8_N_1S) noexcept
		{
			return start(static_cast<uint32_t>(baud), level, prot);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	BRR レジスタ値を取得
			@return BRR レジスタ値
		 */
		//-----------------------------------------------------------------//
		uint8_t get_brr() const noexcept { return RSCI::SCR2.BRR(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	設定ボーレートを取得
			@param[in]	real	「true」にした場合、内部で設定された実際の値
			@return ボーレート
		 */
		//-----------------------------------------------------------------//
		uint32_t get_baud_rate(bool real = false) const noexcept
		{
			if(real) {
				uint32_t brr = RSCI::SCR2.BRR();
				uint32_t cks = 1 << (RSCI::SCR2.CKS() * 2);
				uint32_t mtx = 8;
				if(RSCI::SEMR_BGDM) {
					if(!RSCI::SCR2.BGDM()) mtx <<= 1;
				} else {
					mtx <<= 1;
				}
				if(!RSCI::SCR2.ABCS()) mtx <<= 1;
				auto baud = RSCI::PCLK / mtx / cks / (brr + 1);
				if(RSCI::SEMR_BRME && RSCI::SCR2.BRME()) {
					baud *= RSCI::SCR2.MDDR();
					baud /= 256;
				}
				return baud;
			} else {
				return baud_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	MDDR レジスタ値を取得（ボーレート周期補正）
			@return MDRR レジスタ値
		 */
		//-----------------------------------------------------------------//
		uint8_t get_mdrr() const noexcept { return RSCI::SCR2.MDDR(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 出力バッファのサイズを返す
			@return　バッファのサイズ
		 */
		//-----------------------------------------------------------------//
		uint32_t send_length() const noexcept
		{
			if(level_ != ICU::LEVEL::NONE) {
				return send_.length();
			} else {
				return 0;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 文字出力
			@param[in]	ch	文字コード
		 */
		//-----------------------------------------------------------------//
		void putch(char ch) noexcept
		{
			if(auto_crlf_ && ch == '\n') {
				putch('\r');
			}

			if(level_ != ICU::LEVEL::NONE) {
				/// 送信バッファの容量が７／８の場合は、空になるまで待つ。
				if(send_.length() >= (send_.size() * 7 / 8)) {
					while(send_.length() != 0) sleep_();
				}
				send_.put(ch);
				if(RSCI::SCR0.TIE() == 0) {
					RSCI::SCR0.TIE = 1;
					RSCI::TDR.TDAT = send_.get();
				}
			} else {
				while(RSCI::SSR.TDRE() == 0) sleep_();
				RSCI::TDR.TDAT = ch;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 入力文字数を取得
			@return	入力文字数
		 */
		//-----------------------------------------------------------------//
		uint32_t recv_length() noexcept
		{
			if(level_ != ICU::LEVEL::NONE) {
				return recv_.length();
			} else {
				if(RSCI::RDR.PER()) {	///< パリティ・エラー状態確認
				}
				if(RSCI::RDR.FER()) {	///< フレーミング・エラー状態確認
				}
				return RSCI::SSR.RDRF();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	入力文字を捨てる
		 */
		//-----------------------------------------------------------------//
		void flush_recv() noexcept
		{
			if(recv_length() > 0) {
				recv_.clear();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 文字入力
			@return 文字コード
		 */
		//-----------------------------------------------------------------//
		char getch() noexcept
		{
			if(level_ != ICU::LEVEL::NONE) {
				while(recv_.length() == 0) sleep_();
				return recv_.get();
			} else {
				while(recv_length() == 0) sleep_();
				char ch = RSCI::RDR.RDAT();	///< 受信データ読み出し
				return ch;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	uart文字列出力
			@param[in]	s	出力ストリング
		 */
		//-----------------------------------------------------------------//
		void puts(const char* s) noexcept
		{
			char ch;
			while((ch = *s++) != 0) {
				putch(ch);
			}
		}


		char operator () () noexcept { return getch(); }
		void operator = (char ch) noexcept { putch(ch); }
		void operator = (const char* str) noexcept { puts(str); }
	};
}
