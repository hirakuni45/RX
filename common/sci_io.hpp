#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・SCI I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

/// F_PCLKB はボーレートパラメーター計算に必要で、設定が無いとエラーにします。
#ifndef F_PCLKB
#  error "sci_io.hpp requires F_PCLKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI I/O 制御クラス
		@param[in]	SCI	SCI 定義クラス
		@param[in]	RBF	受信バッファクラス
		@param[in]	SBF	送信バッファクラス
		@param[in]	PSEL		ポート選択
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI, class RBF, class SBF, port_map::option PSEL = port_map::option::FIRST>
	class sci_io {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  簡易 I2C の速度タイプ @n
					※誤差が大きいので注意
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class speed {
			_50K     =  50000,	///<  50K b.p.s.
			standard = 100000,	///< 100K b.p.s. (Standard mode)
			_150K    = 150000,	///< 150K b.p.s.
			_200K    = 200000,	///< 200K b.p.s.
			_250K    = 250000,	///< 250K b.p.s.
			_300K    = 300000,	///< 300K b.p.s.
			_350K    = 350000,	///< 350K b.p.s.
			fast     = 400000,	///< 400K b.p.s. (Fast mode)
		};

	private:
		static RBF	recv_;
		static SBF	send_;
		static volatile bool send_stall_;

		uint8_t	level_;
		bool	crlf_;

		// ※必要なら、実装する
		void sleep_() { asm("nop"); }

		static INTERRUPT_FUNC void recv_task_()
		{
			bool err = false;
			if(SCI::SSR.ORER()) {	///< 受信オーバランエラー状態確認
				SCI::SSR.ORER = 0;	///< 受信オーバランエラークリア
				err = true;
			}
			///< フレーミングエラー/パリティエラー状態確認
			if(SCI::SSR() & (SCI::SSR.FER.b() | SCI::SSR.PER.b())) {
				// エラーフラグの消去
				SCI::SSR.FER = 0;
				SCI::SSR.PER = 0;
				err = true;
			}
			volatile uint8_t data = SCI::RDR();
			if(!err) {
				recv_.put(data);
			}
		}

		static INTERRUPT_FUNC void send_task_()
		{
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
			if(send_.length() > 0) {
				SCI::TDR = send_.get();
			}
			if(send_.length() == 0) {
				SCI::SCR.TIE = 0;
				send_stall_ = true;
			}
#else
			SCI::TDR = send_.get();
			if(send_.length() == 0) {
				SCI::SCR.TEIE = 0;
			}
#endif
		}

		void set_vector_(ICU::VECTOR rx_vec, ICU::VECTOR tx_vec) {
			if(level_) {
				set_interrupt_task(recv_task_, static_cast<uint32_t>(rx_vec));
				set_interrupt_task(send_task_, static_cast<uint32_t>(tx_vec));
			} else {
				set_interrupt_task(nullptr, static_cast<uint32_t>(rx_vec));
				set_interrupt_task(nullptr, static_cast<uint32_t>(tx_vec));
			}
		}

		void set_intr_() {
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
			set_vector_(SCI::get_rx_vec(), SCI::get_tx_vec());
#else
			set_vector_(SCI::get_rx_vec(), SCI::get_te_vec());
#endif
			icu_mgr::set_level(SCI::get_peripheral(), level_);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	crlf	LF 時、CR の送出をしないばあい「false」
		*/
		//-----------------------------------------------------------------//
		sci_io(bool crlf = true) : level_(0), crlf_(crlf) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  ボーレートを設定して、SCI を有効にする @n
					※RX63T では、ポーリングはサポート外
			@param[in]	baud	ボーレート
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t baud, uint8_t level = 0) {
			send_stall_ = true;
#if SIG_RX63T
			if(level == 0) return false;
#endif
			level_ = level;

			power_cfg::turn(SCI::get_peripheral());

			SCI::SCR = 0x00;			// TE, RE disable.

			port_map::turn(SCI::get_peripheral(), true, PSEL);

			uint32_t brr = F_PCLKB / baud * 16;
			uint8_t cks = 0;
			while(brr > (512 << 8)) {
				brr >>= 2;
				++cks;
			}
			if(cks > 3) return false;
			bool abcs = true;
			bool brme = false;
			if(brr > (256 << 8)) { brr /= 2; abcs = false; }
			uint32_t mddr = ((brr & 0xff00) << 8) / brr;
			brr >>= 8;

			set_intr_();

			// 8 bits, 1 stop bit, no-parrity
			SCI::SMR = cks;
			if(mddr >= 128) brme = true;
			SCI::SEMR = SCI::SEMR.ABCS.b(abcs) | SCI::SEMR.BRME.b(brme);
			if(brr) --brr;
			SCI::BRR = brr;
			SCI::MDDR = mddr;

			if(level) {
				SCI::SCR = SCI::SCR.RIE.b() | SCI::SCR.TE.b() | SCI::SCR.RE.b();
			} else {
				SCI::SCR = SCI::SCR.TE.b() | SCI::SCR.RE.b();
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  通信速度を設定して、SPI を有効にする
			@param[in]	master	マスターモードの場合「true」
			@param[in]	bps	ビットレート
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start_spi(bool master, uint32_t bps, uint8_t level = 0)
		{
			send_stall_ = true;
			level_ = level;

			power_cfg::turn(SCI::get_peripheral());

			SCI::SCR = 0x00;			// TE, RE disable.

			uint32_t brr = F_PCLKB / bps / 2;
			if(brr & 1) { brr >>= 1; ++brr; }
			else { brr >>= 1; }
			uint8_t cks = 0;
			while(brr > 256) {
				brr >>= 2;
				++cks;
			}
			if(cks > 3 || brr > 256) return false;

			set_intr_();

			// LSB(0), MSB(1) first
			SCI::SCMR.SDIR = 1;

			SCI::SIMR1.IICM = 0;
			SCI::SMR = cks | SCI::SMR.CM.b();
			SCI::SPMR.SSE = 0;		///< SS 端子制御しない「０」

			if(master) {
				SCI::SPMR.MSS = 0;
			} else {
				SCI::SPMR.MSS = 1;
			}

			// クロックタイミング種別選択
			SCI::SPMR.CKPOL = 0;
			SCI::SPMR.CKPH  = 0;

			if(brr) --brr;
			SCI::BRR = static_cast<uint8_t>(brr);

			uint8_t scr = 0;
			if(master) {
				scr = SCI::SCR.CKE.b(0b01);
			} else {
				scr = SCI::SCR.CKE.b(0b10);
			}

			if(level_) {
				SCI::SCR = SCI::SCR.RIE.b() | SCI::SCR.TE.b() | SCI::SCR.RE.b() | scr;
			} else {
				SCI::SCR = SCI::SCR.TE.b() | SCI::SCR.RE.b() | scr;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  簡易 I2C を有効にする
			@param[in]	spd		スピード・タイプ
			@param[in]	master	マスターモードの場合「true」
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start_i2c(speed spd, bool master = true, uint8_t level = 0)
		{
			// 現在の実装では、割り込みはサポートされない。
			if(level != 0) return false;

			// I2C オプションが無い場合エラー
			if(PSEL != port_map::option::FIRST_I2C) {
				return false;
			}

			uint32_t clk = static_cast<uint32_t>(spd);
			uint32_t brr = F_PCLKB / clk * 4;
			uint32_t mddr = ((brr & 0xff00) << 8) / brr;
			brr >>= 8;
			if(brr >= 256 || brr == 0) {
				return false;
			}
			--brr;

			level_ = level;

			power_cfg::turn(SCI::get_peripheral());

			SCI::SCR = 0x00;		// TE, RE disable. CKE = 0
			port_map::turn(SCI::get_peripheral(), true, PSEL);

			SCI::SIMR3 = SCI::SIMR3.IICSDAS.b(0b11) | SCI::SIMR3.IISCLSS.b(0b11);
			SCI::SMR   = 0x00;
			SCI::SCMR  = SCI::SCMR.SDIR.b(1);
			SCI::BRR   = brr;
			SCI::MDDR  = mddr;



			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	CR 自動送出
			@param[in]	f	「false」なら無効
		 */
		//-----------------------------------------------------------------//
		void auto_crlf(bool f = true) { crlf_ = f; }


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 出力バッファのサイズを返す
			@return　バッファのサイズ
		 */
		//-----------------------------------------------------------------//
		uint32_t send_length() const {
			if(level_) {
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
		void putch(char ch) {
			if(crlf_ && ch == '\n') {
				putch('\r');
			}

			if(level_) {
				volatile bool b = SCI::SSR.ORER();
				if(b) {
					SCI::SSR.ORER = 0;
				}
				/// 送信バッファの容量が７／８の場合は、空になるまで待つ。
				if(send_.length() >= (send_.size() * 7 / 8)) {
					while(send_.length() != 0) sleep_();
				}
				send_.put(ch);
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
				SCI::SCR.TIE = 0;
				if(send_stall_) {
					while(SCI::SSR.TEND() == 0) sleep_();
					SCI::TDR = send_.get();
					if(send_.length() > 0) {
						send_stall_ = false;
					}
				}
				SCI::SCR.TIE = !send_stall_;
#else
				if(SCI::SCR.TEIE() == 0) {
					SCI::SCR.TEIE = 1;
				}
#endif
			} else {
				while(SCI::SSR.TEND() == 0) sleep_();
				SCI::TDR = ch;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 入力文字数を取得
			@return	入力文字数
		 */
		//-----------------------------------------------------------------//
		uint32_t recv_length() {
			if(level_) {
				return recv_.length();
			} else {
				if(SCI::SSR.ORER()) {	///< 受信オーバランエラー状態確認
					SCI::SSR.ORER = 0;	///< 受信オーバランエラークリア
				}
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX24T) || defined(SIG_RX65N)
				auto n = SCI::SSR.RDRF();
#else
				uint32_t n = 0;
#endif
				return n;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 文字入力
			@return 文字コード
		 */
		//-----------------------------------------------------------------//
		char getch() {
			if(level_) {
				while(recv_.length() == 0) sleep_();
				return recv_.get();
			} else {
				char ch;
				while(recv_length() == 0) sleep_();
				ch = SCI::RDR();	///< 受信データ読み出し
				return ch;
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
				putch(ch);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送受信（SPI）
			@param[in]	ch	送信データ
			@return	受信データ
		*/
		//-----------------------------------------------------------------//
		inline uint8_t xchg(uint8_t ch = 0xff)
		{
			if(level_) {
				return 0;
			} else {
				SCI::TDR = ch;
				while(recv_length() == 0) sleep_();
				return SCI::RDR();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ブロック送信（SPI）
			@param[in]	src	送信ソース
			@param[in]	cnt	送信サイズ
		*/
		//-----------------------------------------------------------------//
		void send(const void* src, uint16_t size)
		{
			const uint8_t* p = static_cast<const uint8_t*>(src);
			auto end = p + size;
			while(p < end) {
				xchg(*p);
				++p;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ブロック受信（SPI）
			@param[out]	dst	受信先
			@param[in]	cnt	受信サイズ
		*/
		//-----------------------------------------------------------------//
		void recv(void* dst, uint16_t size)
		{
			uint8_t* p = static_cast<uint8_t*>(dst);
			auto end = p + size;
			while(p < end) {
				*p = xchg();
				++p;
			}
		}
	};

	template<class SCI, class RBF, class SBF, port_map::option PSEL>
		RBF sci_io<SCI, RBF, SBF, PSEL>::recv_;
	template<class SCI, class RBF, class SBF, port_map::option PSEL>
		SBF sci_io<SCI, RBF, SBF, PSEL>::send_;
	template<class SCI, class RBF, class SBF, port_map::option PSEL>
		volatile bool sci_io<SCI, RBF, SBF, PSEL>::send_stall_;
}
