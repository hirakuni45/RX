#pragma once
//=========================================================================//
/*!	@file
	@brief	RX14T グループ・ポート・マッピング @n
			コメントのピン番号は、LQFP100 パッケージの場合
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX14T/peripheral.hpp"
#include "RX14T/port.hpp"
#include "RX14T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX14T ポート・マッピング・ユーティリティー
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
			// RXD1: P72 (LFQFP48: )
			// TXD1: P71 (LFQFP48: )
			// SCK1: P70 (LFQFP48: )
				PORT7::PMR.B2 = 0;
				PORT7::ODR.B2 = i2c;
				MPC::P72PFS.PSEL = sel;
				PORT7::PMR.B2 = enable;
				PORT7::PMR.B1 = 0;
				PORT7::ODR.B1 = i2c;
				MPC::P71PFS.PSEL = sel;
				PORT7::PMR.B1 = enable;
				if(spi) {
					PORT7::PMR.B0 = 0;
					MPC::P70PFS.PSEL = sel;
					PORT7::PMR.B0 = enable;
				}
				break;
			case ORDER::SECOND:  // for Serial BOOT interface
			// RXD1: PB6 (LFQFP48: )
			// TXD1: PB5 (LFQFP48: )
			// SCK1: PB0 (LFQFP48: )
				sel = enable ? 0b0'1011 : 0;
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = 0;
				PORTB::ODR.B5 = i2c;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = enable;
				if(spi) {
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = enable ? 0b0'1010 : 0;
					PORTB::PMR.B0 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD1: PD5 (LFQFP48: )
			// TXD1: PD4 (LFQFP48: )
			// SCK1: PD6 (LFQFP48: )
				PORTD::PMR.B5 = 0;
				PORTD::ODR.B5 = i2c;
				MPC::PD5PFS.PSEL = sel;
				PORTD::PMR.B5 = enable;
				PORTD::PMR.B4 = 0;
				PORTD::ODR.B4 = i2c;
				MPC::PD4PFS.PSEL = sel;
				PORTD::PMR.B4 = enable;
				if(spi) {
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = enable;
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
			// RXD5: P24 (LFQFP48: )
			// TXD5: P23 (LFQFP48: )
			// SCK5: P22 (LFQFP48: )
				PORT2::PMR.B4 = 0;
				PORT2::ODR.B4 = i2c;
				MPC::P24PFS.PSEL = sel;
				PORT2::PMR.B4 = enable;
				PORT2::PMR.B3 = 0;
				PORT2::ODR.B3 = i2c;
				MPC::P23PFS.PSEL = sel;
				PORT2::PMR.B3 = enable;
				if(spi) {
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD5: P97 (LFQFP48: )
			// TXD5: PB0 (LFQFP48: )
			// SCK5: P92 (LFQFP48: )
				PORT9::PMR.B7 = 0;
				PORT9::ODR.B7 = i2c;
				MPC::P97PFS.PSEL = sel;
				PORT9::PMR.B7 = enable;
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;
				PORTB::PMR.B0 = enable;
				if(spi) {
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;
					PORT9::PMR.B2 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD5: P97 (LFQFP48: )
			// TXD5: PB0 (LFQFP48: )
			// SCK5: P96 (LFQFP48: )
				PORT9::PMR.B7 = 0;
				PORT9::ODR.B7 = i2c;
				MPC::P97PFS.PSEL = sel;
				PORT9::PMR.B7 = enable;
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;
				PORTB::PMR.B0 = enable;
				if(spi) {
					PORT9::PMR.B6 = 0;
					MPC::P96PFS.PSEL = sel;
					PORT9::PMR.B6 = enable;
				}
				break;
			case ORDER::FOURTH:
			// RXD5: PB6 (LFQFP48: )
			// TXD5: PB5 (LFQFP48: )
			// SCK5: PB1 (LFQFP48: )
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = 0;
				PORTB::ODR.B5 = i2c;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = enable;
				if(spi) {
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
				}
				break;
			case ORDER::FIFTH:
			// RXD5: PB6 (LFQFP48: )
			// TXD5: PB5 (LFQFP48: )
			// SCK5: PB7 (LFQFP48: )
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = 0;
				PORTB::ODR.B5 = i2c;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = enable;
				if(spi) {
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci6_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD6: P26 (LFQFP48: )
			// TXD6: P11 (LFQFP48: )
			// SCK6: P30 (LFQFP48: )
				PORT2::PMR.B6 = 0;
				PORT2::ODR.B6 = i2c;
				MPC::P26PFS.PSEL = sel;
				PORT2::PMR.B6 = enable;
				PORT1::PMR.B1 = 0;
				PORT1::ODR.B1 = i2c;
				MPC::P11PFS.PSEL = sel;
				PORT1::PMR.B1 = enable;
				if(spi) {
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD6: P36 (LFQFP48: )
			// TXD6: P31 (LFQFP48: )
			// SCK6: P30 (LFQFP48: )
				PORT3::PMR.B6 = 0;
				PORT3::ODR.B6 = i2c;
				MPC::P36PFS.PSEL = sel;
				PORT3::PMR.B6 = enable;
				PORT3::PMR.B1 = 0;
				PORT3::ODR.B1 = i2c;
				MPC::P31PFS.PSEL = sel;
				PORT3::PMR.B1 = enable;
				if(spi) {
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD6: P97 (LFQFP48: )
			// TXD6: PB0 (LFQFP48: )
			// SCK6: P96 (LFQFP48: )
				PORT9::PMR.B7 = 0;
				PORT9::ODR.B7 = i2c;
				MPC::P97PFS.PSEL = sel;
				PORT9::PMR.B7 = enable;
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;
				PORTB::PMR.B0 = enable;
				if(spi) {
					PORT9::PMR.B6 = 0;
					MPC::P96PFS.PSEL = sel;
					PORT9::PMR.B6 = enable;
				}
				break;




			case ORDER::FOURTH:
			// RXD6: PB6 (LFQFP48: )
			// TXD6: PB5 (LFQFP48: )
			// SCK6: PB1 (LFQFP48: )
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = 0;
				PORTB::ODR.B5 = i2c;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = enable;
				if(spi) {
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
				}
				break;
			case ORDER::FIFTH:
			// RXD6: PB6 (LFQFP48: )
			// TXD6: PB5 (LFQFP48: )
			// SCK6: PB7 (LFQFP48: )
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = 0;
				PORTB::ODR.B5 = i2c;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = enable;
				if(spi) {
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = enable;
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
			// RXD12: P36 (LFQFP48: )
			// TXD12: P11 (LFQFP48: )
			// SCK12: P75 (LFQFP48: )
				PORT3::PMR.B6 = 0;
				PORT3::ODR.B6 = i2c;
				MPC::P36PFS.PSEL = sel;
				PORT3::PMR.B6 = enable;
				PORT1::PMR.B1 = 0;
				PORT1::ODR.B1 = i2c;
				MPC::P11PFS.PSEL = sel;
				PORT1::PMR.B1 = enable;
				if(spi) {
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;
					PORT7::PMR.B5 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD12: P36 (LFQFP48: )
			// TXD12: P37 (LFQFP48: )
			// SCK12: P92 (LFQFP48: )
				PORT9::PMR.B4 = 0;
				PORT9::ODR.B4 = i2c;
				MPC::P94PFS.PSEL = sel;
				PORT9::PMR.B4 = enable;
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;
				PORTB::PMR.B0 = enable;
				if(spi) {
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;
					PORT9::PMR.B3 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD12: P76
			// TXD12: P37
			// SCK12: PB1
				PORT7::PMR.B6 = 0;
				PORT7::ODR.B6 = i2c;
				MPC::P76PFS.PSEL = sel;
				PORT7::PMR.B6 = enable;
				PORT3::PMR.B7 = 0;
				PORT3::ODR.B7 = i2c;
				MPC::P37PFS.PSEL = sel;
				PORT3::PMR.B7 = enable;
				if(spi) {
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
				}
				break;
			case ORDER::FOURTH:
			// RXD12: P93
			// TXD12: P94
			// SCK12: P92
				PORT9::PMR.B3 = 0;
				PORT9::ODR.B3 = i2c;
				MPC::P93PFS.PSEL = sel;
				PORT9::PMR.B3 = enable;
				PORT9::PMR.B4 = 0;
				PORT9::ODR.B4 = i2c;
				MPC::P94PFS.PSEL = sel;
				PORT9::PMR.B4 = enable;
				if(spi) {
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;
					PORT9::PMR.B2 = enable;
				}
				break;
			case ORDER::FIFTH:
			// RXD12: P93
			// TXD12: P96
			// SCK12: PG7
				PORT9::PMR.B3 = 0;
				PORT9::ODR.B3 = i2c;
				MPC::P93PFS.PSEL = sel;
				PORT9::PMR.B3 = enable;
				PORT9::PMR.B6 = 0;
				PORT9::ODR.B6 = i2c;
				MPC::P96PFS.PSEL = sel;
				PORT9::PMR.B6 = enable;
				if(spi) {
					PORTG::PMR.B7 = 0;
					MPC::PG7PFS.PSEL = sel;
					PORTG::PMR.B7 = enable;
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
			// SCL0: P97 (LFQFP48: )
			// SDA0: PB0 (LFQFP48: )
				PORT9::PMR.B7 = 0;
				MPC::P97PFS.PSEL = sel;  // ok
				PORT9::PMR.B7 = enable;
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				break;
			case ORDER::SECOND:
			// SCL0: P26 (LFQFP48: )
			// SDA0: P31 (LFQFP48: )
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = sel;  // ok
				PORT2::PMR.B6 = enable;
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = sel;  // ok
				PORT3::PMR.B1 = enable;
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
				case peripheral::SCI6:
					ret = sci6_(odr, ena, opt);
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
