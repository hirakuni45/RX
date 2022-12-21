#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・SCIF I/O 制御（FIFO 内臓型）@n
			※内臓のFIFOバッファを利用しない実装（扱いにくいので使わない） @n
			SCIF は、RX64M/RX71M 専用となっている。 @n
			SCIF8 ～ SCIF11
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIF I/O 制御クラス
		@param[in]	SCIF		SCIF 定義クラス
		@param[in]	RECV_BUFF	受信バッファクラス
		@param[in]	SEND_BUFF	送信バッファクラス
		@param[in]	PSEL		ポート選択
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCIF, class RECV_BUFF, class SEND_BUFF,
		port_map::ORDER PSEL = port_map::ORDER::FIRST>
	class scif_io {

		static RECV_BUFF recv_;
		static SEND_BUFF send_;
		static volatile bool send_stall_;

		uint8_t	level_;
		bool	crlf_;

		// ※必要なら、実装する
		void sleep_() { asm("nop"); }

		static INTERRUPT_FUNC void recv_task_()
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
			}
		}

		static INTERRUPT_FUNC void send_task_()
		{
			if(send_.length() > 0) {
				SCIF::FTDR = send_.get();
			}
			if(send_.length() == 0) {
				SCIF::SCR.TIE = 0;
				send_stall_ = true;
			}
			SCIF::FSR.TDFE = 0;
		}

		void set_vector_(ICU::VECTOR rx_vec, ICU::VECTOR tx_vec) noexcept
		{
			if(level_) {
				icu_mgr::set_task(rx_vec, recv_task_);
				icu_mgr::set_task(tx_vec, send_task_);
			} else {
				icu_mgr::set_task(rx_vec, nullptr);
				icu_mgr::set_task(tx_vec, nullptr);
			}
		}

		void set_intr_() noexcept
		{
			set_vector_(SCIF::get_rx_vec(), SCIF::get_tx_vec());
			icu_mgr::set_level(SCIF::PERIPHERAL, level_);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	crlf	LF 時、CR の送出をしない場合「false」
		*/
		//-----------------------------------------------------------------//
		scif_io(bool crlf = true) noexcept : level_(0), crlf_(crlf) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  ボーレートを設定して、SCI を有効にする
			@param[in]	baud	ボーレート
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t baud, ICU::LEVEL level = ICU::LEVEL::NONE) noexcept
		{
			send_stall_ = true;

			level_ = level;

			SCIF::SCR = 0x00;			// TE, RE disable.

			port_map::turn(SCIF::PERIPHERAL, true, PSEL);

			uint32_t brr = F_PCLKA / baud / 32;
			uint8_t cks = 0;
			while(brr > 512) {
				brr >>= 2;
				++cks;
			}
			if(cks > 3) return false;
			bool abcs0 = 0;
			if(brr > 256) { brr /= 2; abcs0 = 1; }

			power_mgr::turn(SCIF::PERIPHERAL);

			set_intr_();

			// FIFO: しきい値
			SCIF::FTCR = SCIF::FTCR.TTRGS.b() | SCIF::FTCR.TFTC.b(1)
				| SCIF::FTCR.RTRGS.b() | SCIF::FTCR.RFTC.b(1);

			// 8 bits, 1 stop bit, no-parrity
			SCIF::SMR = cks;
			SCIF::SEMR.ABCS0 = abcs0;
			if(brr) --brr;

			SCIF::BRR = static_cast<uint8_t>(brr);

			if(level) {
				SCIF::SCR = SCIF::SCR.RIE.b() | SCIF::SCR.TE.b() | SCIF::SCR.RE.b();
			} else {
				SCIF::SCR = SCIF::SCR.TE.b() | SCIF::SCR.RE.b();
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	CRLF 自動送出
			@param[in]	f	「false」なら無効
		 */
		//-----------------------------------------------------------------//
		void auto_crlf(bool f = true) noexcept { crlf_ = f; }


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
			if(crlf_ && ch == '\n') {
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

				SCIF::SCR.TIE = 0;
				if(send_stall_) {
					while(SCIF::FSR.TDFE() == 0) sleep_();
					SCIF::FTDR = send_.get();
					SCIF::FSR.TDFE = 0;
					if(send_.length() > 0) {
						send_stall_ = false;
					}
				}
				SCIF::SCR.TIE = !send_stall_;
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

	template<class SCI, class RECV_BUFF, class SEND_BUFF, port_map::ORDER PSEL>
		RECV_BUFF scif_io<SCI, RECV_BUFF, SEND_BUFF, PSEL>::recv_;
	template<class SCI, class RECV_BUFF, class SEND_BUFF, port_map::ORDER PSEL>
		SEND_BUFF scif_io<SCI, RECV_BUFF, SEND_BUFF, PSEL>::send_;
	template<class SCI, class RECV_BUFF, class SEND_BUFF, port_map::ORDER PSEL>
		volatile bool scif_io<SCI, RECV_BUFF, SEND_BUFF, PSEL>::send_stall_;
}
