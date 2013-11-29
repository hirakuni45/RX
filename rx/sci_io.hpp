#pragma once
//=====================================================================//
/*!	@file
	@brief	RX62N, RX621 グループ・SCI I/O 制御 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "sci.hpp"
#include "fifo.hpp"
#include "system.hpp"
#include "icu.hpp"
#include "port.hpp"
#include "vect.h"

/// F_PCK はボーレートパラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCKB
#  error "sci_io.hpp requires F_PCKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI 割り込みタスク受け渡し構造体
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct sci_task_t {
		utility::fifo* send;
		utility::fifo* recv;
	};

	extern sci_task_t sci_task_[];

	INTERRUPT_FUNC void task_SCI0_RXI_();
	INTERRUPT_FUNC void task_SCI0_TEI_();
	INTERRUPT_FUNC void task_SCI1_RXI_();
	INTERRUPT_FUNC void task_SCI1_TEI_();
	INTERRUPT_FUNC void task_SCI2_RXI_();
	INTERRUPT_FUNC void task_SCI2_TEI_();
	INTERRUPT_FUNC void task_SCI3_RXI_();
	INTERRUPT_FUNC void task_SCI3_TEI_();
//	INTERRUPT_FUNC void task_SCI5_RXI_();
//	INTERRUPT_FUNC void task_SCI5_TEI_();
//	INTERRUPT_FUNC void task_SCI6_RXI_();
//	INTERRUPT_FUNC void task_SCI6_TEI_();


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI I/O 制御クラス
		@param[in]	T	SCIx I/O クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI>
	class sci_io {

		SCI	sci_;

		utility::fifo	recv_;
		utility::fifo	send_;

		uint8_t	intr_level_;
		bool	crlf_;
		bool	polling_;

		// ※必要なら、実装する
		void sleep_() { }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		sci_io() : intr_level_(2), crlf_(true), polling_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化 @n
					※ポーリングの場合は設定しなくても良い
			@param[in]	recv_size	受信バッファサイズ
			@param[in]	send_size	送信バッファサイズ
			@param[in]	level	割り込みレベル
		*/
		//-----------------------------------------------------------------//
		void initialize(uint32_t recv_size, uint32_t send_size, uint32_t level) {
			recv_.initialize(recv_size);
			send_.initialize(send_size);
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
		bool set_baud(uint32_t baud, bool polling = false) {
			uint32_t brr = F_PCKB / baud / 16;
			uint8_t cks = 0;
			while(brr > 512) {
				brr >>= 2;
				++cks;
			}
			if(cks > 3 || brr == 0) return false;
			bool abcs = true;
			if(brr > 256) { brr /= 2; abcs = false; }

			polling_ = polling;

			sci_.SCR = 0x00;			// TE, RE disable.

			uint32_t chanel = sci_.get_chanel();
			if(polling_) {
//				ICU::IER.TEI0 = false;	// TEI0 Disable
//				ICU::IER.RXI0 = false;	// RXI0 Disable
			} else {
				sci_task_[chanel].recv = &recv_;
				sci_task_[chanel].send = &send_;
				switch(chanel) {
				case 0:
					set_interrupt_task(task_SCI0_RXI_, ICU::VECTOR::RXI0);
					set_interrupt_task(task_SCI0_TEI_, ICU::VECTOR::TEI0);
//					ICU::IER.TEI0 = true;
//					ICU::IER.RXI0 = true;
//					ICU::IPR.SCI0 = intr_level_;
					break;
				case 1:
					set_interrupt_task(task_SCI1_RXI_, ICU::VECTOR::RXI1);
					set_interrupt_task(task_SCI1_TEI_, ICU::VECTOR::TEI1);
//					ICU::IER.TEI1 = true;
//					ICU::IER.RXI1 = true;
//					ICU::IPR.SCI1 = intr_level_;
					break;
				case 2:
					set_interrupt_task(task_SCI2_RXI_, ICU::VECTOR::RXI2);
					set_interrupt_task(task_SCI2_TEI_, ICU::VECTOR::TEI2);
//					ICU::IER.TEI2 = true;
//					ICU::IER.RXI2 = true;
//					ICU::IPR.SCI2 = intr_level_;
					break;
				case 3:
					set_interrupt_task(task_SCI3_RXI_, ICU::VECTOR::RXI3);
					set_interrupt_task(task_SCI3_TEI_, ICU::VECTOR::TEI3);
//					ICU::IER.TEI3 = true;
//					ICU::IER.RXI3 = true;
//					ICU::IPR.SCI3 = intr_level_;
					break;
#if 0
				case 5:
					set_interrupt_task(task_SCI5_RXI_, ICU::VECTOR::RXI5);
					set_interrupt_task(task_SCI5_TEI_, ICU::VECTOR::TEI5);
					ICU::IER.TEI5 = true;
					ICU::IER.RXI5 = true;
					ICU::IPR.SCI5 = intr_level_;
					break;
				case 6:
					set_interrupt_task(task_SCI6_RXI_, ICU::VECTOR::RXI6);
					set_interrupt_task(task_SCI6_TEI_, ICU::VECTOR::TEI6);
					ICU::IER.TEI6 = true;
					ICU::IER.RXI6 = true;
					ICU::IPR.SCI6 = intr_level_;
					break;
#endif
				default:
					return false;
				}
			}

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
#if 0
			case 5:
				SYSTEM::MSTPCRB.MSTPB26 = 0;	// B26 (SCI5)のストップ状態解除
				break;
			case 6:
				SYSTEM::MSTPCRB.MSTPB25 = 0;	// B25 (SCI6)のストップ状態解除
				break;
#endif
			}

			// 8 bits, 1 stop bit, no parrity
			sci_.SMR = cks;
			sci_.SEMR.ABCS = abcs;
			sci_.BRR = static_cast<uint8_t>(brr - 1);

			if(polling_) {
				sci_.SCR = sci_.SCR.TE.b() | sci_.SCR.RE.b();
			} else {
				sci_.SCR = sci_.SCR.RIE.b() | sci_.SCR.TE.b() | sci_.SCR.RE.b();
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
				while(sci_.SSR.TEND() == 0) sleep_();
				sci_.TDR = ch;
			} else {
				/// ７／８ を超えてた場合は、バッファが空になるまで待つ。
				if(send_.length() >= (send_.size() * 7 / 8)) {
					while(send_.length() != 0) sleep_();
				}
				send_.put(ch);
				sci_.SCR.TEIE = 1;
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
				if(sci_.SSR.ORER()) {		///< 受信オーバランエラー状態確認
					sci_.SSR.ORER = 0;	///< 受信オーバランエラークリア
					err = true;
				}
				uint8_t sts = sci_.SSR();	///< 受信ステータス取得
				///< フレーミングエラー、パリティエラー状態確認
				if(sts & (sci_.SSR.FER.b() | sci_.SSR.PER.b())) {
					err = true;
				}
				if((sts & sci_.SSR.RDRF.b()) != 0 && err == 0) {
					return 1;	///< 受信データあり
				} else {
					return 0;	///< 受信データなし
				}
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
				ch = sci_.RDR();		///< 受信データ読み出し
				sci_.SSR.RDRF = 0;	///< 受信フラグクリア
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
}
