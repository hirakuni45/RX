#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T グループ・ポート・マッピング
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX63T/peripheral.hpp"
#include "RX63T/port.hpp"
#include "RX63T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX63T ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sci0_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD0: P22
			// TXD0: P23
			// SCK0: P30
				PORT2::PMR.B2 = 0;
				PORT2::ODR.B2 = i2c;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				PORT2::PMR.B3 = 0;
				PORT2::ODR.B3 = i2c;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
				if(spi) {
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;  // ok
					PORT3::PMR.B0 = enable;
				}
				break;
			case ORDER::SECOND:  // For 64, 48 Pin Version
			// RXD0: P24
			// TXD0: P30
			// SCK0: P23
				PORT2::PMR.B4 = 0;
				PORT2::ODR.B4 = i2c;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = enable;
				PORT3::PMR.B0 = 0;
				PORT3::ODR.B0 = i2c;
				MPC::P30PFS.PSEL = sel;  // ok
				PORT3::PMR.B0 = enable;
				if(spi) {
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD0: PA5
			// TXD0: PA4
			// SCK0: PA3
				PORTA::PMR.B5 = 0;
				PORTA::ODR.B5 = i2c;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
				if(spi) {
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // ok
					PORTA::PMR.B3 = enable;
				}
				break;
			case ORDER::FOURTH:
			// RXD0: PB1
			// TXD0: PB2
			// SCK0: PB3
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
			default:
				return false;
			}
			return true;
		}

		static bool sci1_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD1: P96
			// TXD1: P95
			// SCK1: PD4
				PORT9::PMR.B6 = 0;
				PORT9::ODR.B6 = i2c;
				MPC::P96PFS.PSEL = sel;  // ok
				PORT9::PMR.B6 = enable;
				PORT9::PMR.B5 = 0;
				PORT9::ODR.B5 = i2c;
				MPC::P95PFS.PSEL = sel;  // ok
				PORT9::PMR.B5 = enable;
				if(spi) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // ok
					PORTD::PMR.B4 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD1: P96
			// TXD1: P95
			// SCK1: PD4
				PORT9::PMR.B6 = 0;
				PORT9::ODR.B6 = i2c;
				MPC::P96PFS.PSEL = sel;  // ok
				PORT9::PMR.B6 = enable;
				PORT9::PMR.B5 = 0;
				PORT9::ODR.B5 = i2c;
				MPC::P95PFS.PSEL = sel;  // ok
				PORT9::PMR.B5 = enable;
				if(spi) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // ok
					PORTD::PMR.B4 = enable;
				}
				break;
			case ORDER::THIRD:  // for BOOT serial port
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
			case ORDER::FOURTH:
			// RXD1: PF2
			// TXD1: PF3
			// SCK1: PG6
				PORTF::PMR.B2 = 0;
				PORTF::ODR.B2 = i2c;
				MPC::PF2PFS.PSEL = sel;  // ok
				PORTF::PMR.B2 = enable;
				PORTF::PMR.B3 = 0;
				PORTF::ODR.B3 = i2c;
				MPC::PF3PFS.PSEL = sel;  // ok
				PORTF::PMR.B3 = enable;
				if(spi) {
					PORTG::PMR.B6 = 0;
					MPC::PG6PFS.PSEL = sel;  // ok
					PORTG::PMR.B6 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci2_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b00'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD2: P03
			// TXD2: P02
			// SCK2: P14
				PORT0::PMR.B3 = 0;
				PORT0::ODR.B3 = i2c;
				MPC::P03PFS.PSEL = sel;  // ok
				PORT0::PMR.B3 = enable;
				PORT0::PMR.B2 = 0;
				PORT0::ODR.B2 = i2c;
				MPC::P02PFS.PSEL = sel;  // ok
				PORT0::PMR.B2 = enable;
				if(spi) {
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // ok
					PORT1::PMR.B4 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD2: PA2
			// TXD2: PA1
			// SCK2: PA0
				PORTA::PMR.B2 = 0;
				PORTA::ODR.B2 = i2c;
				MPC::PA2PFS.PSEL = sel;  // ok
				PORTA::PMR.B2 = enable;
				PORTA::PMR.B1 = 0;
				PORTA::ODR.B1 = i2c;
				MPC::PA1PFS.PSEL = sel;  // ok
				PORTA::PMR.B1 = enable;
				if(spi) {
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD2: PG1
			// TXD2: PG0
			// SCK2: PG2
				PORTG::PMR.B1 = 0;
				PORTG::ODR.B1 = i2c;
				MPC::PG1PFS.PSEL = sel;  // ok
				PORTG::PMR.B1 = enable;
				PORTG::PMR.B0 = 0;
				PORTG::ODR.B0 = i2c;
				MPC::PG0PFS.PSEL = sel;  // ok
				PORTG::PMR.B0 = enable;
				if(spi) {
					PORTG::PMR.B2 = 0;
					MPC::PG2PFS.PSEL = sel;  // ok
					PORTG::PMR.B2 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci3_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD3: P34
			// TXD3: P35
			// SCK3: PG5
				PORT3::PMR.B4 = 0;
				PORT3::ODR.B4 = i2c;
				MPC::P34PFS.PSEL = sel;  // ok
				PORT3::PMR.B4 = enable;
				PORT3::PMR.B5 = 0;
				PORT3::ODR.B5 = i2c;
				MPC::P35PFS.PSEL = sel;  // ok
				PORT3::PMR.B5 = enable;
				if(spi) {
					PORTG::PMR.B5 = 0;
					MPC::PG5PFS.PSEL = sel;  // ok
					PORTG::PMR.B5 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD3: PG4
			// TXD3: PG3
			// SCK3: PG5
				PORTG::PMR.B4 = 0;
				PORTG::ODR.B4 = i2c;
				MPC::PG4PFS.PSEL = sel;  // ok
				PORTG::PMR.B4 = enable;
				PORTG::PMR.B3 = 0;
				PORTG::ODR.B3 = i2c;
				MPC::PG3PFS.PSEL = sel;  // ok
				PORTG::PMR.B3 = enable;
				if(spi) {
					PORTG::PMR.B5 = 0;
					MPC::PG5PFS.PSEL = sel;  // ok
					PORTG::PMR.B5 = enable;
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
			// RXD12: P80
			// TXD12: P81
			// SCK12: P82
				PORT8::PMR.B0 = 0;
				PORT8::ODR.B0 = i2c;
				MPC::P80PFS.PSEL = sel;  // ok
				PORT8::PMR.B0 = enable;
				PORT8::PMR.B1 = 0;
				PORT8::ODR.B1 = i2c;
				MPC::P81PFS.PSEL = sel;  // ok
				PORT8::PMR.B1 = enable;
				if(spi) {
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B2 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD12: PB6
			// TXD12: PB5
			// SCK12: PB7
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = 0;
				PORTB::ODR.B5 = i2c;
				MPC::PB5PFS.PSEL = sel;  // ok
				PORTB::PMR.B5 = enable;
				if(spi) {
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // ok
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

		static bool riic1_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1111 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// SCL1: P25
			// SDA1: P26
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;  // ok
				PORT2::PMR.B5 = enable;
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = sel;  // ok
				PORT2::PMR.B6 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool can1_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b1'0000 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// CRX1: P22
			// CTX1: P23
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
				break;
			case ORDER::SECOND:
			// CRX1: PB6
			// CTX1: PB5
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;  // ok
				PORTB::PMR.B5 = enable;
				break;
			case ORDER::THIRD:
			// CRX1: PE0
			// CTX1: PD7
				PORTE::PMR.B0 = 0;
				MPC::PE0PFS.PSEL = sel;  // ok
				PORTE::PMR.B0 = enable;
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = sel;  // ok
				PORTD::PMR.B7 = enable;
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
			// RSPCKA: P24
			// MOSIA:  P23
			// MISOA:  P22
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = enable;
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::SECOND:
			// RSPCKA: PA4
			// MOSIA:  PB0
			// MISOA:  PA5
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				break;
			case ORDER::THIRD:
			// RSPCKA: PD0
			// MOSIA:  PD2
			// MISOA:  PD1
				PORTD::PMR.B0 = 0;
				MPC::PD0PFS.PSEL = sel;  // ok
				PORTD::PMR.B0 = enable;
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = sel;  // ok
				PORTD::PMR.B2 = enable;
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = sel;  // ok
				PORTD::PMR.B1 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi1_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1110 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RSPCKB: P24
			// MOSIB:  P23
			// MISOB:  P22
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = enable;
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::SECOND:
			// RSPCKB: PA4
			// MOSIB:  PB0
			// MISOB:  PA5
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				break;
			case ORDER::THIRD:
			// RSPCKB: PD0
			// MOSIB:  PD2
			// MISOB:  PD1
				PORTD::PMR.B0 = 0;
				MPC::PD0PFS.PSEL = sel;  // ok
				PORTD::PMR.B0 = enable;
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = sel;  // ok
				PORTD::PMR.B2 = enable;
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = sel;  // ok
				PORTD::PMR.B1 = enable;
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
				case peripheral::SCI0:
					ret = sci0_(odr, ena, opt);
					break;
				case peripheral::SCI1:
					ret = sci1_(odr, ena, opt);
					break;
				case peripheral::SCI2:
					ret = sci2_(odr, ena, opt);
					break;
				case peripheral::SCI3:
					ret = sci3_(odr, ena, opt);
					break;
				case peripheral::SCI12:
					ret = sci12_(odr, ena, opt);
					break;
				case peripheral::RIIC0:
					ret = riic0_(odr, ena);
					break;
				case peripheral::RIIC1:
					ret = riic1_(odr, ena);
					break;
				case peripheral::CAN1:
					ret = can1_(odr, ena);
					break;
				case peripheral::RSPI0:
					ret = rspi0_(odr, ena);
					break;
				case peripheral::RSPI1:
					ret = rspi1_(odr, ena);
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
