#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・SCI 簡易 I2C I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

/// F_PCLKB はボーレートパラメーター計算に必要で、設定が無いとエラーにします。
#ifndef F_PCLKB
#  error "sci_i2c_io.hpp requires F_PCLKB to be defined"
#endif

namespace device {

	// SCI/I2C task type
	enum class sci_i2c_task : uint8_t {
		start,		// start condition
		slave_adr,	// Slave Address Send
		send,		// send data
		recv,		// recv data
		stop,		// stop condition
	};

	// SCI/I2C pad
	struct sci_i2c_pad {
		uint8_t		adr_;
		uint16_t	len_;
		sci_i2c_pad(uint8_t adr = 0) noexcept : adr_(adr), len_(0) { }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI I2C I/O 制御クラス
		@param[in]	SCI		SCI 定義クラス
		@param[in]	RBF		受信バッファクラス
		@param[in]	SBF		送信バッファクラス
		@param[in]	PSEL	ポート選択
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI, class RBF, class SBF, port_map::option PSEL = port_map::option::FIRST>
	class sci_i2c_io {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  速度タイプ型 @n
					※簡易 I2C では誤差が大きいので注意
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SPEED {
			_50K     =  50000,	///<  50K b.p.s.
			STANDARD = 100000,	///< 100K b.p.s. (Standard mode)
			_150K    = 150000,	///< 150K b.p.s.
			_200K    = 200000,	///< 200K b.p.s.
			_250K    = 250000,	///< 250K b.p.s.
			_300K    = 300000,	///< 300K b.p.s.
			_350K    = 350000,	///< 350K b.p.s.
			FAST     = 400000,	///< 400K b.p.s. (Fast mode) 60MHz では、対応していません。
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エラー型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ERROR : uint8_t {
			NONE,		///< エラー無し
			I2C_START,	///< I2C Start コンディション・エラー
			I2C_ACK,	///< I2C ACK エラー
			I2C_STOP,	///< I2C Stop コンディション・エラー
		};

	private:
		static RBF	recv_;
		static SBF	send_;

		uint8_t		level_;
		ERROR		error_;
		uint16_t	i2c_loop_;

		static volatile sci_i2c_task	i2c_task_;
		static sci_i2c_pad	i2c_pad_;

		// ※マルチタスクの場合適切な実装をする
		void sleep_() noexcept { asm("nop"); }


		static INTERRUPT_FUNC void recv_task_()
		{
		}


		static INTERRUPT_FUNC void send_task_()
		{
		}


		static void i2c_service_()
		{
			switch(i2c_task_) {
			case sci_i2c_task::start:
				break;
			default:
				break;
			}
		}


		static void i2c_condition_task_()
		{
			i2c_service_();
		}


#if 0
		void set_vector_(ICU::VECTOR rx_vec, ICU::VECTOR tx_vec) noexcept
		{
			if(level_) {
				set_interrupt_task(recv_task_, static_cast<uint32_t>(rx_vec));
				set_interrupt_task(send_task_, static_cast<uint32_t>(tx_vec));
			} else {
				set_interrupt_task(nullptr, static_cast<uint32_t>(rx_vec));
				set_interrupt_task(nullptr, static_cast<uint32_t>(tx_vec));
			}
		}

		void set_intr_() noexcept
		{
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
			set_vector_(SCI::get_rx_vec(), SCI::get_tx_vec());
#else
			set_vector_(SCI::get_rx_vec(), SCI::get_te_vec());
#endif
			icu_mgr::set_level(SCI::get_peripheral(), level_);
		}
#endif

		bool i2c_start_() noexcept
		{
			SCI::SIMR3 = SCI::SIMR3.IICSTAREQ.b() |
						 SCI::SIMR3.IICSCLS.b(0b01) | SCI::SIMR3.IICSDAS.b(0b01);
			uint32_t n = 0;
			bool ret = true;
			while(SCI::SIMR3.IICSTIF() == 0) {
				++n;
				if(n >= i2c_loop_) {
					ret = false;
					break;
				}
			}
			SCI::SIMR3 = SCI::SIMR3.IICSCLS.b(0b00) | SCI::SIMR3.IICSDAS.b(0b00);
			return ret;
		}


		bool i2c_stop_() noexcept
		{
			SCI::SIMR3 = SCI::SIMR3.IICSTPREQ.b() |
						 SCI::SIMR3.IICSCLS.b(0b01) | SCI::SIMR3.IICSDAS.b(0b01);
			uint32_t n = 0;
			bool ret = true;
			while(SCI::SIMR3.IICSTIF() == 0) {
				++n;
				if(n >= i2c_loop_) {
					ret = false;
					break;
				}
			}
			SCI::SIMR3 = SCI::SIMR3.IICSCLS.b(0b11) | SCI::SIMR3.IICSDAS.b(0b11);
			return ret;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		sci_i2c_io() noexcept : level_(0), error_(ERROR::NONE), i2c_loop_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  最終エラーコードを取得
			@return 最終エラーコード
		*/
		//-----------------------------------------------------------------//
		ERROR get_last_error() const noexcept { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C を有効にする
			@param[in]	spd		スピード・タイプ
			@param[in]	master	マスターモードの場合「true」（現在はマスターモードのみ実装）
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(SPEED spd, bool master = true, uint8_t level = 0) noexcept
		{
			// I2C オプションが無い場合エラー
			if(PSEL != port_map::option::FIRST_I2C) {
				return false;
			}

			uint32_t clk = static_cast<uint32_t>(spd);
			uint32_t brr = F_PCLKB * 8 / clk;
			uint32_t mddr = ((brr & 0xff00) << 8) / brr;
			brr >>= 8;
			if(brr >= 256 || brr <= 1) {
				return false;
			}
			--brr;
//			utils::format("BRR: %d, MDDR: %d\n")
//				% static_cast<uint16_t>(brr) % static_cast<uint16_t>(mddr);

			// 200 ---> I2C Start/Stop loop for STANDARD
			// 5 ---> マージン倍率
			i2c_loop_ = 200 * 5;

			level_ = level;

			power_cfg::turn(SCI::get_peripheral());

			SCI::SCR = 0x00;		// TE, RE disable. CKE = 0
			port_map::turn(SCI::get_peripheral(), true, PSEL);

			SCI::SIMR3 = SCI::SIMR3.IICSDAS.b(0b11) | SCI::SIMR3.IICSCLS.b(0b11);
			SCI::SMR   = 0x00;
			SCI::SCMR  = SCI::SCMR.SDIR.b();
			SCI::BRR   = brr;
			SCI::MDDR  = mddr;

			bool brme = false;
			if(mddr >= 128) brme = true;
			// NFEN: ノイズ除去有効の場合「１」
			SCI::SEMR = SCI::SEMR.NFEN.b(0) | SCI::SEMR.BRME.b(brme);
			SCI::SNFR = SCI::SNFR.NFCS.b(0b001);  // 1/1
			SCI::SIMR1 = SCI::SIMR1.IICM.b() | SCI::SIMR1.IICDL.b(0b00000);
			SCI::SIMR2 = SCI::SIMR2.IICACKT.b() | SCI::SIMR2.IICCSC.b() | SCI::SIMR2.IICINTM.b();
			SCI::SPMR = 0x00;
			SCI::SCR = SCI::SCR.TE.b() | SCI::SCR.RE.b();

			if(level_ > 0) {
				// TEIx (STI)
				icu_mgr::install_group_task(SCI::get_te_vec(), i2c_condition_task_);
			}

			error_ = ERROR::NONE;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C 送信
			@param[in]	adr	I2C アドレス（下位７ビット）
			@param[in]	src	送信データ
			@param[in]	len	送信長
			@return 送信正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		bool send(uint8_t adr, const void* src, uint32_t len) noexcept
		{
			if(src == nullptr || len == 0) return false;

			if(level_ == 0) {
				if(!i2c_start_()) {
					error_ = ERROR::I2C_START;
					i2c_stop_();
					return false;
				}

				SCI::TDR = adr << 1;  // R/W = 0 (write)
				while(SCI::SSR.TDRE() == 0) {
					sleep_();
				}
				while(SCI::SSR.TEND() == 0) {
					sleep_();
				}

				const uint8_t* p = static_cast<const uint8_t*>(src);
				while(len > 0) {
					if(SCI::SISR.IICACKR()) {
						break;
					}
					SCI::TDR = *p++;
					--len;

					while(SCI::SSR.TDRE() == 0) {
						sleep_();
					}
					while(SCI::SSR.TEND() == 0) {
						sleep_();
					}
				}

				if(!i2c_stop_()) {
					error_ = ERROR::I2C_STOP;
					return false;
				}
				error_ = ERROR::NONE;
			} else {

				i2c_task_ = sci_i2c_task::start;
				i2c_pad_.adr_ = adr;
				i2c_pad_.len_ = len;
//				i2c_src_ = src;
				SCI::SCR.TEIE = 1;

			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C 受信
			@param[in]	adr	I2C アドレス（下位７ビット）
			@param[in]	dst	受信データ
			@param[in]	len	受信長
			@return 送信正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		bool recv(uint8_t adr, void* dst, uint32_t len) noexcept
		{
			if(dst == nullptr || len == 0) return false;

			if(level_ == 0) {
				if(!i2c_start_()) {
					error_ = ERROR::I2C_START;
					i2c_stop_();
					return false;
				}

				SCI::TDR = (adr << 1) | 1;  // R/W = 1 (read)
				while(SCI::SSR.TDRE() == 0) {
					sleep_();
				}
				while(SCI::SSR.TEND() == 0) {
					sleep_();
				}
				volatile uint8_t tmp = SCI::RDR();  // ダミーリード

				if(SCI::SISR.IICACKR() != 0) {
					error_ = ERROR::I2C_ACK;
					i2c_stop_();
					return false;
				}

				if(len > 1) {
					SCI::SIMR2.IICACKT = 0;
				}
				uint8_t* p = static_cast<uint8_t*>(dst);
				while(len > 0) {
					if(len == 1) {
						SCI::SIMR2.IICACKT = 1;
					}
					SCI::TDR = 0xff;  // dummy data
					while(SCI::SSR.RDRF() == 0) {
						sleep_();
					}
					*p++ = SCI::RDR();
					--len;
					while(SCI::SSR.TEND() == 0) {
						sleep_();
					}
				}

				if(!i2c_stop_()) {
					error_ = ERROR::I2C_STOP;
					return false;
				}
				error_ = ERROR::NONE;
			} else {

				i2c_task_ = sci_i2c_task::start;
				i2c_pad_.adr_ = adr;
				i2c_pad_.len_ = len;
				SCI::SCR.TEIE = 1;

			}
			return true;
		}
	};

	// テンプレート関数、実態の定義
	template<class SCI, class RBF, class SBF, port_map::option PSEL>
		RBF sci_i2c_io<SCI, RBF, SBF, PSEL>::recv_;
	template<class SCI, class RBF, class SBF, port_map::option PSEL>
		SBF sci_i2c_io<SCI, RBF, SBF, PSEL>::send_;
	template<class SCI, class RBF, class SBF, port_map::option PSEL>
		volatile sci_i2c_task sci_i2c_io<SCI, RBF, SBF, PSEL>::i2c_task_;
	template<class SCI, class RBF, class SBF, port_map::option PSEL>
		sci_i2c_pad sci_i2c_io<SCI, RBF, SBF, PSEL>::i2c_pad_;
}
