#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・SCIF I/O 制御（FIFO 内臓型） @n
			※内臓のFIFOバッファを利用しない実装（扱いにくいので使わない） @n
			現状 SCIF は、RX64M/RX71M 専用となっている。 @n
			SCIF8 ～ SCIF11
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2023 Kunihito Hiramatsu @n
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
		@brief  SCIF I/O 制御クラス
		@param[in]	SCIF	SCIF 定義クラス
		@param[in]	RBF		受信バッファクラス
		@param[in]	SBF		送信バッファクラス
		@param[in]	PSEL	ポート選択
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCIF, class RBF, class SBF, port_map::ORDER PSEL = port_map::ORDER::FIRST>
	class scif_io : public sci_io_base {

		static_assert(RBF::size() > 8, "Receive buffer is too small.");
		static_assert(SBF::size() > 8, "Transmission buffer is too small.");

	public:
		typedef SCIF sci_type;
		typedef RBF  rbf_type;
		typedef SBF  sbf_type;

	private:
		static RBF	recv_;
		static SBF	send_;
		static volatile uint16_t errc_;

		ICU::LEVEL	level_;
		bool		auto_crlf_;
		uint32_t	baud_;

		// ※必要なら、実装する
		void sleep_() { asm("nop"); }

		static INTERRUPT_FUNC void rxi_task_()
		{
			bool err = false;
			///< フレーミングエラー/パリティエラー状態確認
			if(SCIF::FSR.PER()) {
				SCIF::FSR.PER = 0;
				err = true;
			}
			if(SCIF::FSR.FER()) {
				SCIF::FSR.FER = 0;
				err = true;
			}
			volatile uint8_t data = SCIF::FRDR();
			SCIF::FSR.RDF = 0;
			if(!err) {
				recv_.put(data);
				++errc_;
			}
		}

		static INTERRUPT_FUNC void txi_task_()
		{
			if(send_.length() > 0) {
				SCIF::FTDR = send_.get();
			}
			if(send_.length() == 0) {
				SCIF::SCR.TIE = 0;
			}
			SCIF::FSR.TDFE = 0;
		}

		void set_intr_() noexcept
		{
			if(level_ != ICU::LEVEL::NONE) {
				icu_mgr::set_interrupt(SCIF::RXI, rxi_task_, level_);
				icu_mgr::set_interrupt(SCIF::TXI, txi_task_, level_);
			} else {
				icu_mgr::set_interrupt(SCIF::RXI, nullptr, level_);
				icu_mgr::set_interrupt(SCIF::TXI, nullptr, level_);
			}
		}

		static constexpr bool calc_rate_(uint32_t baud,
			uint8_t& brr_, uint8_t& cks_, uint8_t& mddr_, bool& abcs_, bool& bgdm_, bool& brme_) noexcept
		{
			// BGDM が使える場合、1/8 スタート
			uint32_t mtx = 8;
			uint32_t limit = 1024;
			if(!SCIF::SEMR_BGDM) {  // BGDM が使えない場合 1/16 スタート
				mtx = 16;
				limit = 512;
			}
			uint32_t brr = SCIF::PCLK / mtx / baud;
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
			if(SCIF::SEMR_BGDM) {
				if(brr > 512) { brr >>= 1; bgdm = false; mtx <<= 1; }
			} else {
				bgdm = false;
			}
			bool abcs = true;
			if(brr > 256) { brr >>= 1; abcs = false; mtx <<= 1; }

			bool brme = false;
			if(SCIF::SEMR_BRME) {  // 微調整機能が使える場合
				uint32_t rate = SCIF::PCLK / mtx / brr / (1 << (cks * 2));
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
		scif_io(bool crlf = true) noexcept : level_(ICU::LEVEL::NONE), auto_crlf_(crlf), baud_(0)
		{
			errc_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	LF 時、CR 自動送出
			@param[in]	f	「false」なら無効
		 */
		//-----------------------------------------------------------------//
		void auto_crlf(bool f = true) noexcept { auto_crlf_ = f; }


		//-----------------------------------------------------------------//
		/*!
			@brief	エラー数の取得
			@return エラー数
		 */
		//-----------------------------------------------------------------//
		static auto get_error_count() noexcept { return errc_; }


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
			if(SCIF::SEMR_BGDM) {
				if(!bgdm) mtx <<= 1;
			} else {
				mtx <<= 1;
			}
			if(!abcs) mtx <<= 1;
			auto cbaud = SCIF::PCLK / mtx / (1 << (static_cast<uint32_t>(cks) * 2)) / static_cast<uint32_t>(brr);
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

			SCIF::SCR = 0x00;			// TE, RE disable.

			port_map::turn(SCIF::PERIPHERAL, true, PSEL);

			power_mgr::turn(SCIF::PERIPHERAL);

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

			// FIFO: しきい値
			SCIF::FTCR = SCIF::FTCR.TTRGS.b() | SCIF::FTCR.TFTC.b(1)
				| SCIF::FTCR.RTRGS.b() | SCIF::FTCR.RFTC.b(1);

			SCIF::SMR = SCIF::SMR.CKS.b(cks) | SCIF::SMR.STOP.b(stop) | SCIF::SMR.PM.b(pm) | SCIF::SMR.PE.b(pe)
					  | SCIF::SMR.CHR.b(chr);

			if(brme) {
				SCIF::SEMR.MDDRS = 1;
				SCIF::MDDR = mddr;
				SCIF::SEMR.MDDRS = 0;
			}
			SCIF::SEMR = SCIF::SEMR.ABCS0.b(abcs) | SCIF::SEMR.BRME.b(brme) | SCIF::SEMR.BGDM.b(bgdm);

			if(brr) --brr;
			SCIF::SEMR.MDDRS = 0;
			SCIF::BRR = static_cast<uint8_t>(brr);

			if(level_ != ICU::LEVEL::NONE) {
				SCIF::SCR = SCIF::SCR.RIE.b() | SCIF::SCR.TE.b() | SCIF::SCR.RE.b();
			} else {
				SCIF::SCR = SCIF::SCR.TE.b() | SCIF::SCR.RE.b();
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
		uint8_t get_brr() const noexcept {
			SCIF::SEMR.MDDRS = 0;
			return SCIF::BRR();
		}


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
				SCIF::SEMR.MDDRS = 0;
				uint32_t brr = SCIF::BRR();
				uint32_t cks = 1 << (SCIF::SMR.CKS() * 2);
				uint32_t mtx = 8;
				if(SCIF::SEMR_BGDM) {
					if(!SCIF::SEMR.BGDM()) mtx <<= 1;
				} else {
					mtx <<= 1;
				}
				if(!SCIF::SEMR.ABCS0()) mtx <<= 1;
				auto baud = SCIF::PCLK / mtx / cks / (brr + 1);
				if(SCIF::SEMR_BRME && SCIF::SEMR.BRME()) {
					SCIF::SEMR.MDDRS = 1;
					baud *= SCIF::MDDR();
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
		uint8_t get_mdrr() const noexcept {
			SCIF::SEMR.MDDRS = 1;
			return SCIF::MDDR();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 出力バッファのサイズを返す
			@return　バッファのサイズ
		 */
		//-----------------------------------------------------------------//
		uint32_t send_length() const noexcept {
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
		void putch(char ch) noexcept {
			if(auto_crlf_ && ch == '\n') {
				putch('\r');
			}

			if(level_ != ICU::LEVEL::NONE) {
//				volatile bool b = SCI::SSR.ORER();
//				if(b) {
//					SCI::SSR.ORER = 0;
//				}
				/// 送信バッファの容量が７／８の場合は、空になるまで待つ。
				if(send_.length() >= (send_.size() * 7 / 8)) {
					while(send_.length() != 0) sleep_();
				}
				send_.put(ch);
				if(SCIF::SCR.TIE() == 0) {
					while(SCIF::FSR.TDFE() == 0) sleep_();
					SCIF::FTDR = send_.get();
					SCIF::FSR.TDFE = 0;
					if(send_.length() > 0) {
						SCIF::SCR.TIE = 1;
					}
				}
			} else {
				while(SCIF::FSR.TDFE() == 0) sleep_();
				SCIF::FSR.TDFE = 0;
				SCIF::FTDR = ch;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 入力文字数を取得
			@return	入力文字数
		 */
		//-----------------------------------------------------------------//
		uint32_t recv_length() noexcept {
			if(level_ != ICU::LEVEL::NONE) {
				return recv_.length();
			} else {
				if(SCIF::FSR.PER()) {	///< パリティ・エラー状態確認
					SCIF::FSR.PER = 0;	///< パリティ・エラークリア
				}
				if(SCIF::FSR.FER()) {	///< フレーミング・エラー状態確認
					SCIF::FSR.FER = 0;	///< フレーミング・エラークリア
				}
				return SCIF::FSR.RDF();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 文字入力
			@return 文字コード
		 */
		//-----------------------------------------------------------------//
		char getch() noexcept {
			if(level_ != ICU::LEVEL::NONE) {
				while(recv_.length() == 0) sleep_();
				return recv_.get();
			} else {
				while(recv_length() == 0) sleep_();
				char ch = SCIF::FRDR();	///< 受信データ読み出し
				SCIF::FSR.RDF = 0;
				return ch;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	uart文字列出力
			@param[in]	s	出力ストリング
		 */
		//-----------------------------------------------------------------//
		void puts(const char* s) noexcept {
			char ch;
			while((ch = *s++) != 0) {
				putch(ch);
			}
		}
	};
	template<class SCIF, class RBF, class SBF, port_map::ORDER PSEL>
		RBF scif_io<SCIF, RBF, SBF, PSEL>::recv_;
	template<class SCIF, class RBF, class SBF, port_map::ORDER PSEL>
		SBF scif_io<SCIF, RBF, SBF, PSEL>::send_;
	template<class SCIF, class RBF, class SBF, port_map::ORDER PSEL>
		volatile uint16_t scif_io<SCIF, RBF, SBF, PSEL>::errc_;
}
