#pragma once
//=========================================================================//
/*!	@file
	@brief	RX13T グループ・ポート・マッピング @n
			コメントのピン番号は、LQFP100 パッケージの場合
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX13T/peripheral.hpp"
#include "RX13T/port.hpp"
#include "RX13T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX24T ポート・マッピング・ユーティリティー
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
			case ORDER::FIRST:
				// RXD1: PD5
				// TXD1: PD3
				// SCK1: PD4
				PORTD::PMR.B5 = 0;
				PORTD::ODR.B5 = i2c;
				MPC::PD5PFS.PSEL = sel;  // ok
				PORTD::PMR.B5 = enable;
				PORTD::PMR.B3 = 0;
				PORTD::ODR.B3 = i2c;
				MPC::PD3PFS.PSEL = sel;  // ok
				PORTD::PMR.B3 = enable;
				if(spi) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // ok
					PORTD::PMR.B4 = enable;
				}
				break;
			case ORDER::SECOND:  // for Serial BOOT interface
				// RXD1: PB7
				// TXD1: PB6
				// SCK1: PD4
				sel = enable ? 0b0'1011 : 0;
				PORTB::PMR.B7 = 0;
				PORTB::ODR.B7 = i2c;
				MPC::PB7PFS.PSEL = sel;  // ok
				PORTB::PMR.B7 = enable;
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
				if(spi) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = enable ? 0b0'1010 : 0;  // ok
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
				// RXD5: PB1
				// TXD5: PB2
				// SCK5: PB3
				PORTB::PMR.B1 = 0;
				PORTB::ODR.B1 = i2c;
				MPC::PB1PFS.PSEL = sel;  // ok
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B2 = 0;
				PORTB::ODR.B2 = i2c;
				MPC::PB2PFS.PSEL = sel;  // ok
				PORTB::PMR.B2 = enable;
				if(spi) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD5: PB7
				// TXD5: PB6
				// SCK5: PB3
				PORTB::PMR.B7 = 0;
				PORTB::ODR.B7 = i2c;
				MPC::PB7PFS.PSEL = sel;  // ok
				PORTB::PMR.B7 = enable;
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
				if(spi) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = enable;
				}
				break;
			case ORDER::THIRD:
				// RXD5: P24
				// TXD5: P23
				// SCK5: PB3
				PORT2::PMR.B4 = 0;
				PORT2::ODR.B4 = i2c;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = enable;
				PORT2::PMR.B3 = 0;
				PORT2::ODR.B3 = i2c;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
				if(spi) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci12_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1100 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD12: P94
				// TXD12: PB0
				// SCK12: PB3
				PORT9::PMR.B4 = 0;
				PORT9::ODR.B4 = i2c;
				MPC::P94PFS.PSEL = sel;  // ok
				PORT9::PMR.B4 = enable;
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				if(spi) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD12: P94
				// TXD12: PB0
				// SCK12: P93
				PORT9::PMR.B4 = 0;
				PORT9::ODR.B4 = i2c;
				MPC::P94PFS.PSEL = sel;  // ok
				PORT9::PMR.B4 = enable;
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				if(spi) {
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;  // ok
					PORT9::PMR.B3 = enable;
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
				// SCL0: PB1
				// SDA0: PB2
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;  // ok
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;  // ok
				PORTB::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
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
				case peripheral::SCI12:
					ret = sci12_(odr, ena, opt);
					break;
				case peripheral::RIIC0:
					ret = riic0_(odr, ena);
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
