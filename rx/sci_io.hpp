#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・SCI I/O 制御 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "rx63x/sci.hpp"
#include "rx63x/system.hpp"
#include "rx63x/icu.hpp"
#include "vect.h"
#include "fifo.hpp"

/// F_PCKB はボーレートパラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCKB
#  error "sci_io.hpp requires F_PCKB to be defined"
#endif

namespace device {

	static const uint32_t recv_size = 256;
	static const uint32_t send_size = 128;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI I/O 制御クラス
		@param[in]	SCI	SCIx 定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCIx>
	class sci_io {

		static utils::fifo<recv_size>	recv_;
		static utils::fifo<send_size>	send_;

		uint8_t	intr_level_;
		bool	crlf_;
		bool	polling_;

		// ※必要なら、実装する
		void sleep_() { }

		static INTERRUPT_FUNC void recv_task_()
		{
			bool err = false;
			if(SCIx::SSR.ORER()) {	///< 受信オーバランエラー状態確認
				SCIx::SSR = 0x00;	///< 受信オーバランエラークリア
				err = true;
			}
			///< フレーミングエラー/パリティエラー状態確認
			if(SCIx::SSR() & (SCIx::SSR.FER.b() | SCIx::SSR.PER.b())) {
				err = true;
			}
			if(!err) recv_.put(SCIx::RDR());
		}

		static INTERRUPT_FUNC void send_task_()
		{
			SCIx::TDR = send_.get();
			if(send_.length() == 0) {
				SCIx::SCR.TEIE = 0;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		sci_io() : intr_level_(1), crlf_(true), polling_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化 @n
					※ポーリングの場合は設定しなくても良い
			@param[in]	level	割り込みレベル
		*/
		//-----------------------------------------------------------------//
		void initialize(uint32_t level) {
			intr_level_ = level;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ボーレートを設定して、SCI を有効にする
			@param[in]	baud	ボーレート
			@param[in]	polling	ポーリングの場合「true」
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t baud, bool polling = false) {
			polling_ = polling;

			uint32_t brr = F_PCKB / baud / 16;
			uint8_t cks = 0;
			while(brr > 512) {
				brr >>= 2;
				++cks;
			}
			if(cks > 3 || brr == 0) return false;
			bool abcs = true;
			if(brr > 256) { brr /= 2; abcs = false; }

			uint32_t chanel = SCIx::get_chanel();
			switch(chanel) {
			case 0:
				SYSTEM::MSTPCRB.MSTPB31 = 0;	// B31 (SCI0)のストップ状態解除
				break;
			case 1:
				SYSTEM::MSTPCRB.MSTPB30 = 0;	// B30 (SCI1)のストップ状態解除
				break;
			case 2:
				SYSTEM::MSTPCRB.MSTPB29 = 0;	// B29 (SCI2)のストップ状態解除
				break;
			case 3:
				SYSTEM::MSTPCRB.MSTPB28 = 0;	// B28 (SCI3)のストップ状態解除
				break;
			}

			SCIx::SCR = 0x00;			// TE, RE disable.

			if(polling_) {
				switch(chanel) {
				case 0:
					ICU::IER.TEI0 = false;
					ICU::IER.RXI0 = false;
					break;
				case 1:
					ICU::IER.TEI1 = false;
					ICU::IER.RXI1 = false;
					break;
				case 2:
					ICU::IER.TEI2 = false;
					ICU::IER.RXI2 = false;
					break;
				case 3:
					ICU::IER.TEI3 = false;
					ICU::IER.RXI3 = false;
					break;
				default:
					return false;
				}
			} else {
				switch(chanel) {
				case 0:
					set_interrupt_task(recv_task_, ICU::VECTOR::RXI0);
					set_interrupt_task(send_task_, ICU::VECTOR::TEI0);
					ICU::IER.RXI0 = true;
					ICU::IER.TEI0 = true;
					ICU::IPR.SCI0 = intr_level_;
					break;
				case 1:
					set_interrupt_task(recv_task_, ICU::VECTOR::RXI1);
					set_interrupt_task(send_task_, ICU::VECTOR::TEI1);
					ICU::IER.RXI1 = true;
					ICU::IER.TEI1 = true;
					ICU::IPR.SCI1 = intr_level_;
					break;
				case 2:
					set_interrupt_task(recv_task_, ICU::VECTOR::RXI2);
					set_interrupt_task(send_task_, ICU::VECTOR::TEI2);
					ICU::IER.RXI2 = true;
					ICU::IER.TEI2 = true;
					ICU::IPR.SCI2 = intr_level_;
					break;
				case 3:
					set_interrupt_task(recv_task_, ICU::VECTOR::RXI3);
					set_interrupt_task(send_task_, ICU::VECTOR::TEI3);
					ICU::IER.RXI3 = true;
					ICU::IER.TEI3 = true;
					ICU::IPR.SCI3 = intr_level_;
					break;
				default:
					return false;
				}
			}

			// 8 bits, 1 stop bit, no-parrity
			SCIx::SMR = cks;
			SCIx::SEMR.ABCS = abcs;
			SCIx::BRR = static_cast<uint8_t>(brr - 1);

			if(polling_) {
				SCIx::SCR = SCIx::SCR.TE.b() | SCIx::SCR.RE.b();
			} else {
				SCIx::SCR = SCIx::SCR.RIE.b() | SCIx::SCR.TE.b() | SCIx::SCR.RE.b();
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	CRLF 自動送出
			@param[in]	f	「false」なら無効
		 */
		//-----------------------------------------------------------------//
		void auto_crlf(bool f = true) { crlf_ = f; }


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 文字出力
			@param[in]	ch	文字コード
		 */
		//-----------------------------------------------------------------//
		void putch(char ch) {
			if(polling_) {
				while(SCIx::SSR.TEND() == 0) sleep_();
				SCIx::TDR = ch;
			} else {
				/// ７／８ を超えてた場合は、バッファが空になるまで待つ。
				if(send_.length() >= (send_.size() * 7 / 8)) {
					while(send_.length() != 0) sleep_();
				}
				send_.put(ch);
				SCIx::SCR.TEIE = 1;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 入力文字数を取得
			@return	入力文字数
		 */
		//-----------------------------------------------------------------//
		uint32_t length() {
			if(polling_) {
				bool err = false;
				if(SCIx::SSR.ORER()) {		///< 受信オーバランエラー状態確認
					SCIx::SSR.ORER = 0;	///< 受信オーバランエラークリア
					err = true;
				}
				uint8_t sts = SCIx::SSR();	///< 受信ステータス取得
				///< フレーミングエラー、パリティエラー状態確認
				if(sts & (SCIx::SSR.FER.b() | SCIx::SSR.PER.b())) {
					err = true;
				}
//				if((sts & sci_.SSR.RDRF.b()) != 0 && err == 0) {
					return 1;	///< 受信データあり
//				} else {
//					return 0;	///< 受信データなし
//				}
			} else {
				return recv_.length();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 文字入力
			@return 文字コード
		 */
		//-----------------------------------------------------------------//
		char getch() {
			if(polling_) {
				char ch;
				while(length() == 0) sleep_();
				ch = SCIx::RDR();		///< 受信データ読み出し
///				sci_.SSR.RDRF = 0;	///< 受信フラグクリア
				return ch;
			} else {
				while(recv_.length() == 0) sleep_();
				return recv_.get();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	uart文字列出力
			@param[in]	s	出力ストリング
		 */
		//-----------------------------------------------------------------//
		void puts(const char* s) {
			char ch;
			while((ch = *s++) != 0) {
				if(crlf_ && ch == '\n') {
					putch('\r');
				}
				putch(ch);
			}
		}
	};

	template<class SCIx> utils::fifo<recv_size> sci_io<SCIx>::recv_;
	template<class SCIx> utils::fifo<send_size> sci_io<SCIx>::send_;
}
