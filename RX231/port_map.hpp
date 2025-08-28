#pragma once
//=========================================================================//
/*!	@file
	@brief	RX231 グループ・ポート・マッピング
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX231/peripheral.hpp"
#include "RX231/port.hpp"
#include "RX231/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX231 ポート・マッピング・ユーティリティー
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
				// RXD0: P21 (LFQFP64: --)
				// TXD0: P20 (LFQFP64: --)
				// SCK0: P22 (LFQFP64: --)
				PORT2::PMR.B1 = 0;
				PORT2::ODR.B1 = i2c;
				MPC::P21PFS.PSEL = sel;  // ok
				PORT2::PMR.B1 = enable;
				PORT2::PMR.B0 = 0;
				PORT2::ODR.B0 = i2c;
				MPC::P20PFS.PSEL = sel;  // ok
				PORT2::PMR.B0 = enable;
				if(spi) {
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = enable;
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
				// RXD1: P15 (LFQFP64: 19)
				// TXD1: P16 (LFQFP64: 18)
				// SCK1: P17 (LFQFP64: 17)
				PORT1::PMR.B5 = 0;
				PORT1::ODR.B5 = i2c;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = enable;
				PORT1::PMR.B6 = 0;
				PORT1::ODR.B6 = i2c;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				if(spi) {
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = enable;
				}
				break;
			case ORDER::SECOND:  // for BOOT serial port
				// RXD1: P30 (LFQFP64: 14)
				// TXD1: P26 (LFQFP64: 16)
				// SCK1: P27 (LFQFP64: 15)
				PORT3::PMR.B0 = 0;
				PORT3::ODR.B0 = i2c;
				MPC::P30PFS.PSEL = sel;  // ok
				PORT3::PMR.B0 = enable;
				PORT2::PMR.B6 = 0;
				PORT2::ODR.B6 = i2c;
				MPC::P26PFS.PSEL = sel;  // ok
				PORT2::PMR.B6 = enable;
				if(spi) {
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = enable;
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
				// RXD5: PA2 (LFQFP64: --)
				// TXD5: PA4 (LFQFP64: 42)
				// SCK5: PA1 (LFQFP64: 44)
				PORTA::PMR.B2 = 0;
				PORTA::ODR.B2 = i2c;
				MPC::PA2PFS.PSEL = sel;  // ok
				PORTA::PMR.B2 = enable;
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
				if(spi) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD5: PA3 (LFQFP64: 43)
				// TXD5: PA4 (LFQFP64: 42)
				// SCK5: PA1 (LFQFP64: 44)
				PORTA::PMR.B3 = 0;
				PORTA::ODR.B3 = i2c;
				MPC::PA3PFS.PSEL = sel;  // ok
				PORTA::PMR.B3 = enable;
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
				if(spi) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = enable;
				}
				break;
			case ORDER::THIRD:
				// RXD5: PC2 (LFQFP64: 32)
				// TXD5: PC3 (LFQFP64: 31)
				// SCK5: PC1 (LFQFP64: --)
				PORTC::PMR.B2 = 0;
				PORTC::ODR.B2 = i2c;
				MPC::PC2PFS.PSEL = sel;  // ok
				PORTC::PMR.B2 = enable;
				PORTC::PMR.B3 = 0;
				PORTC::ODR.B3 = i2c;
				MPC::PC3PFS.PSEL = sel;  // ok
				PORTC::PMR.B3 = enable;
				if(spi) {
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;  // ok
					PORTC::PMR.B1 = enable;
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
			uint8_t sel = enable ? 0b0'1011 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD6: P33 (LFQFP64: --)
				// TXD6: P32 (LFQFP64: --)
				// SCK6: P34 (LFQFP64: 17)
				PORT3::PMR.B3 = 0;
				PORT3::ODR.B3 = i2c;
				MPC::P33PFS.PSEL = sel;  // ok
				PORT3::PMR.B3 = enable;
				PORT3::PMR.B2 = 0;
				PORT3::ODR.B2 = i2c;
				MPC::P32PFS.PSEL = sel;  // ok
				PORT3::PMR.B2 = enable;
				if(spi) {
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;  // ok
					PORT3::PMR.B4 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD6: PB0 (LFQFP64: 39)
				// TXD6: PB1 (LFQFP64: 37)
				// SCK6: PB3 (LFQFP64: 36)
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				PORTB::PMR.B1 = 0;
				PORTB::ODR.B1 = i2c;
				MPC::PB1PFS.PSEL = sel;  // ok
				PORTB::PMR.B1 = enable;
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

		static bool sci8_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD8: PC6 (LFQFP64: 28)
				// TXD8: PC7 (LFQFP64: 27)
				// SCK8: PC5 (LFQFP64: 29)
				PORTC::PMR.B6 = 0;
				PORTC::ODR.B6 = i2c;
				MPC::PC6PFS.PSEL = sel;  // ok
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B7 = 0;
				PORTC::ODR.B7 = i2c;
				MPC::PC7PFS.PSEL = sel;  // ok
				PORTC::PMR.B7 = enable;
				if(spi) {
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;  // ok
					PORTC::PMR.B5 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci9_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD9: PB6 (LFQFP64: 34)
				// TXD9: PB7 (LFQFP64: 33)
				// SCK9: PB5 (LFQFP64: 35)
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B7 = 0;
				PORTB::ODR.B7 = i2c;
				MPC::PB7PFS.PSEL = sel;  // ok
				PORTB::PMR.B7 = enable;
				if(spi) {
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // ok
					PORTB::PMR.B5 = enable;
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
				// RXD12: PE2 (LFQFP64: 49)
				// TXD12: PE1 (LFQFP64: 50)
				// SCK12: PE0 (LFQFP64: 51)
				PORTE::PMR.B2 = 0;
				PORTE::ODR.B2 = i2c;
				MPC::PE2PFS.PSEL = sel;  // ok
				PORTE::PMR.B2 = enable;
				PORTE::PMR.B1 = 0;
				PORTE::ODR.B1 = i2c;
				MPC::PE1PFS.PSEL = sel;  // ok
				PORTE::PMR.B1 = enable;
				if(spi) {
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;  // ok
					PORTE::PMR.B0 = enable;
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
				// SCL0: P16 (LFQFP64: 18)
				// SDA0: P17 (LFQFP64: 17)
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
				// SCL0: P12 (LFQFP64: --)
				// SDA0: P13 (LFQFP64: --)
				PORT1::PMR.B2 = 0;
				MPC::P12PFS.PSEL = sel;  // ok
				PORT1::PMR.B2 = enable;
				PORT1::PMR.B3 = 0;
				MPC::P13PFS.PSEL = sel;  // ok
				PORT1::PMR.B3 = enable;
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
				// RSPCKA: PA5 (LFQFP64: --)
				// MOSIA:  PA6 (LFQFP64: 41)
				// MISOA:  PA7 (LFQFP64: --)
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;  // ok
				PORTA::PMR.B6 = enable;
				PORTA::PMR.B7 = 0;
				MPC::PA7PFS.PSEL = sel;  // ok
				PORTA::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
				// RSPCKA: PB0 (LFQFP64: 39)
				// MOSIA:  P16 (LFQFP64: 18)
				// MISOA:  P17 (LFQFP64: 17)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				break;
			case ORDER::THIRD:
				// RSPCKA: PC5 (LFQFP64: 29)
				// MOSIA:  PC6 (LFQFP64: 28)
				// MISOA:  PC7 (LFQFP64: 27)
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;  // ok
				PORTC::PMR.B5 = enable;
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;  // ok
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = sel;  // ok
				PORTC::PMR.B7 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sdhi_1st_(SDHI_STATE state, bool wp) noexcept
		{
			// CLK: PB1
			// CMD: PB0
			// D0:  PC3
			// D1:  PB6
			// D2:  PB7
			// D3:  PC2
			// CD:  PB5
			// WP:  PB3
			bool ret = true;
			bool enable = true;
			uint8_t sel = enable ? 0b01'1010 : 0;
			switch(state) {
			case SDHI_STATE::START:
				if(wp) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // SDHI_WP
					PORTB::PMR.B3 = enable;
				}
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;  // SDHI_CD
				PORTB::PMR.B5 = enable;
				break;

			case SDHI_STATE::INSERT:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;  // SDHI_CLK
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // SDHI_CMD
				PORTB::PMR.B0 = enable;
				break;
			case SDHI_STATE::BUS:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = sel;  // SDHI_D0
				PORTC::PMR.B3 = enable;
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;  // SDHI_D1
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = sel;  // SDHI_D2
				PORTB::PMR.B7 = enable;
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = sel;  // SDHI_D3
				PORTC::PMR.B2 = enable;
				break;

			case SDHI_STATE::DESTROY:
				sel = 0;
				enable = 0;
				if(wp) {
					MPC::PB3PFS.PSEL = sel;  // SDHI_WP
					PORTB::PMR.B3 = enable;
				}
				MPC::PB5PFS.PSEL = sel;  // SDHI_CD
				PORTB::PMR.B5 = enable;
			case SDHI_STATE::EJECT:
				sel = 0;
				enable = 0;
				MPC::PB1PFS.PSEL = sel;  // SDHI_CLK
				PORTB::PMR.B1 = enable;
				MPC::PB0PFS.PSEL = sel;  // SDHI_CMD
				PORTB::PMR.B0 = enable;
				MPC::PC3PFS.PSEL = sel;  // SDHI_D0
				PORTB::PMR.B6 = enable;
				MPC::PB6PFS.PSEL = sel;  // SDHI_D1
				PORTB::PMR.B6 = enable;
				MPC::PB7PFS.PSEL = sel;  // SDHI_D2
				PORTB::PMR.B7 = enable;
				MPC::PC2PFS.PSEL = sel;  // SDHI_D3
				PORTC::PMR.B2 = enable;
				break;
			default:
				ret = false;
			}
			return ret;
		}


		static bool sdhi_2nd_(SDHI_STATE state, bool wp) noexcept
		{
			// CLK: PB1
			// CMD: PB0
			// D0:  PC3
			// D1:  PC4
			// D2:  PB7
			// D3:  PC2
			// CD:  PB5
			// WP:  PB3
			bool ret = true;
			bool enable = true;
			uint8_t sel = enable ? 0b01'1010 : 0;
			switch(state) {
			case SDHI_STATE::START:
				if(wp) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // SDHI_WP
					PORTB::PMR.B3 = enable;
				}
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;  // SDHI_CD
				PORTB::PMR.B5 = enable;
				break;

			case SDHI_STATE::INSERT:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;  // SDHI_CLK
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // SDHI_CMD
				PORTB::PMR.B0 = enable;
				break;
			case SDHI_STATE::BUS:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = sel;  // SDHI_D0
				PORTC::PMR.B3 = enable;
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = sel;  // SDHI_D1
				PORTC::PMR.B4 = enable;
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = sel;  // SDHI_D2
				PORTB::PMR.B7 = enable;
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = sel;  // SDHI_D3
				PORTC::PMR.B2 = enable;
				break;

			case SDHI_STATE::DESTROY:
				sel = 0;
				enable = 0;
				if(wp) {
					MPC::PB3PFS.PSEL = sel;  // SDHI_WP
					PORTB::PMR.B3 = enable;
				}
				MPC::PB5PFS.PSEL = sel;  // SDHI_CD
				PORTB::PMR.B5 = enable;
			case SDHI_STATE::EJECT:
				sel = 0;
				enable = 0;
				MPC::PB1PFS.PSEL = sel;  // SDHI_CLK
				PORTB::PMR.B1 = enable;
				MPC::PB0PFS.PSEL = sel;  // SDHI_CMD
				PORTB::PMR.B0 = enable;
				MPC::PC3PFS.PSEL = sel;  // SDHI_D0
				PORTC::PMR.B3 = enable;
				MPC::PC4PFS.PSEL = sel;  // SDHI_D1
				PORTC::PMR.B4 = enable;
				MPC::PB7PFS.PSEL = sel;  // SDHI_D2
				PORTB::PMR.B7 = enable;
				MPC::PC2PFS.PSEL = sel;  // SDHI_D3
				PORTC::PMR.B2 = enable;
				break;

			default:
				ret = false;
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
				case peripheral::SCI5:
					ret = sci5_(odr, ena, opt);
					break;
				case peripheral::SCI6:
					ret = sci6_(odr, ena, opt);
					break;
				case peripheral::SCI8:
					ret = sci8_(odr, ena, opt);
					break;
				case peripheral::SCI9:
					ret = sci9_(odr, ena, opt);
					break;
				case peripheral::SCI12:
					ret = sci12_(odr, ena, opt);
					break;
				case peripheral::IrDA:
					ret = sci5_(odr, ena, OPTIONAL::NONE);
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


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI ポート専用切り替え
			@param[in]	state	SHDI シチュエーション
			@param[in]	odr		ポート・マップ・オーダー
			@param[in]	wp		WP 端子を利用する場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn_sdhi(SDHI_STATE state, ORDER odr = ORDER::FIRST, bool wp = false) noexcept
		{
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = 0;
			switch(odr) {
			case ORDER::FIRST:
				ret = sdhi_1st_(state, wp);
				break;
			case ORDER::SECOND:
				ret = sdhi_2nd_(state, wp);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI クロック・ポートの状態を取得
			@param[in]	odr		ポート・マップ・オーダー
			@return SDHI クロック・ポートの状態
		*/
		//-----------------------------------------------------------------//
		static bool probe_sdhi_clock(ORDER odr) noexcept
		{
			bool ret = 0;
			switch(odr) {
			case ORDER::FIRST:
				ret = PORTB::PIDR.B1();
				break;
			default:
				break;
			}
			return ret;
		}
	};
}
