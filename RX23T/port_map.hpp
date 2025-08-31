#pragma once
//=========================================================================//
/*!	@file
	@brief	RX23T グループ・ポート・マッピング @n
			コメントのピン番号は、LQFP100 パッケージの場合
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX23T/peripheral.hpp"
#include "RX23T/port.hpp"
#include "RX23T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX23T ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sci1_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:  // for Serial BOOT interface
			// RXD1: PD5 (LFQFP64: 14)
				PORTD::PMR.B5 = 0;
				PORTD::ODR.B5 = i2c;
				MPC::PD5PFS.PSEL = sel;  // ok
				PORTD::PMR.B5 = enable;
			// TXD1: PD3 (LFQFP64: 16)
				PORTD::PMR.B3 = 0;
				PORTD::ODR.B3 = i2c;
				MPC::PD3PFS.PSEL = sel;  // ok
				PORTD::PMR.B3 = enable;
			// SCK1: PD4 (LFQFP64: 15)
				if(spi) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // ok
					PORTD::PMR.B4 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci5_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD5: PB1 (LFQFP64: 25)
				PORTB::PMR.B1 = 0;
				PORTB::ODR.B1 = i2c;
				MPC::PB1PFS.PSEL = sel;  // ok
				PORTB::PMR.B1 = enable;
			// TXD5: PB2 (LFQFP64: 24)
				PORTB::PMR.B2 = 0;
				PORTB::ODR.B2 = i2c;
				MPC::PB2PFS.PSEL = sel;  // ok
				PORTB::PMR.B2 = enable;
			// SCK5: PB3 (LFQFP64: 23)
				if(spi) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD5: PB6 (LFQFP64: 18)
				sel = enable ? 0b0'1011 : 0;
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
			// TXD5: PB5 (LFQFP64: 19)
				PORTB::PMR.B5 = 0;
				PORTB::ODR.B5 = i2c;
				MPC::PB5PFS.PSEL = sel;  // ok
				PORTB::PMR.B5 = enable;
			// SCK5: PB3 (LFQFP64: 23)
				if(spi) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = enable ? 0b0'1010 : 0;  // ok
					PORTB::PMR.B3 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD5: PB6 (LFQFP64: 18)
				sel = enable ? 0b0'1011 : 0;
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
			// TXD5: PB5 (LFQFP64: 19)
				PORTB::PMR.B5 = 0;
				PORTB::ODR.B5 = i2c;
				MPC::PB5PFS.PSEL = sel;  // ok
				PORTB::PMR.B5 = enable;
			// SCK5: PB7 (LFQFP64: 17)
				if(spi) {
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = enable ? 0b0'1010 : 0;  // ok
					PORTB::PMR.B7 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool riic0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1111 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// SCL0: PB1 (LFQFP64: 25)
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;  // ok
				PORTB::PMR.B1 = enable;
			// SDA0: PB2 (LFQFP64: 24)
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;  // ok
				PORTB::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1101 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RSPCKA: P24 (LFQFP64: 46)
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = enable;
			// MOSIA:  P23 (LFQFP64: 47)
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
			// MISOA:  P22 (LFQFP64: 48)
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::SECOND:
			// RSPCKA: P93 (LFQFP64: 30)
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = sel;  // ok
				PORT9::PMR.B3 = enable;
			// MOSIA:  P23 (LFQFP64: 47)
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
			// MISOA:  P94 (LFQFP64: 29)
				PORT9::PMR.B4 = 0;
				MPC::P94PFS.PSEL = sel;  // ok
				PORT9::PMR.B4 = enable;
				break;
			case ORDER::THIRD:
			// RSPCKA: PA4 (LFQFP64: 64)
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
			// MOSIA:  PB0 (LFQFP64: 26)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
			// MISOA:  PA5 (LFQFP64: 63)
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				break;
			case ORDER::FOURTH:
			// RSPCKA: PB3 (LFQFP64: 23)
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;  // ok
				PORTB::PMR.B3 = enable;
			// MOSIA:  PB0 (LFQFP64: 26)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
			// MISOA:  PA5 (LFQFP64: 63)
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi0_ssl_(RSPI ssl, ORDER odr, bool enable) noexcept
		{
			bool ret = true;
			uint8_t sel = enable ? 0b00'1101 : 0;  // ok
			switch(ssl) {
			case RSPI::SSL0:
				// SSLA0: P30 (LFQFP64: 45)
				// SSLA0: PA3 (LFQFP64: 27)
				// SSLA0: PD6 (LFQFP64: 13)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B3 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL1:
				// SSLA1: P31 (LFQFP64: 43)
				// SSLA1: PA2 (LFQFP64: 28)
				// SSLA1: PD7 (LFQFP64: 12)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;
					PORT3::PMR.B1 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL2:
				// SSLA2: P32 (LFQFP64: 41)
				// SSLA2: P92 (LFQFP64: 31)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = enable;
				} else if(odr == ORDER::SECOND) {
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;
					PORT9::PMR.B2 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL3:
				// SSLA3: P33 (LFQFP64: 40)
				// SSLA3: P91 (LFQFP64: 32)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = enable;
				} else if(odr == ORDER::SECOND) {
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;
					PORT9::PMR.B1 = enable;
				} else {
					ret = false;
				}
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static inline USER_FUNC_TYPE	user_func_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  ユーザー設定関数設定
			@param[in]	func	ユーザー設定関数
		*/
		//-----------------------------------------------------------------//
		static void set_user_func(USER_FUNC_TYPE func) noexcept { user_func_ = func; }


		//-----------------------------------------------------------------//
		/*!
			@brief  RSPIx/SSL ポート有効／無効
			@param[in]	per		周辺機器タイプ
			@param[in]	ssl		SSLx 選択
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, RSPI ssl, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			if(per == peripheral::RSPI0) {
				ret = rspi0_ssl_(ssl, odr, ena);
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器別ポート切り替え
			@param[in]	per		周辺機器タイプ
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		候補を選択する場合
			@param[in]	opt		オプショナル設定を行う場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, bool ena = true, ORDER odr = ORDER::FIRST, OPTIONAL opt = OPTIONAL::NONE) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			if(odr == ORDER::USER) {
				ret = user_func_(per, ena);
			} else {
				switch(per) {
				case peripheral::SCI1:
					ret = sci1_(odr, ena, opt);
					break;
				case peripheral::SCI5:
					ret = sci5_(odr, ena, opt);
					break;
				case peripheral::RIIC0:
					ret = riic0_(odr, ena);
					break;
				case peripheral::RSPI0:
					ret = rspi0_(odr, ena);
					break;
				default:
					break;
				}
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}

	};
}
