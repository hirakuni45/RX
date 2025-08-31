#pragma once
//=========================================================================//
/*!	@file
	@brief	RX210 グループ・ポート・マッピング
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX210/peripheral.hpp"
#include "RX210/port.hpp"
#include "RX210/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX210 ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sci0_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD0: P21 (LQFP64: --) (LQFP100:  27)
				// TXD0: P20 (LQFP64: --) (LQFP100:  28)
				// SCK0: P22 (LQFP64: --) (LQFP100:  26)
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
			case ORDER::SECOND:
				// RXD0: P33 (LQFP64: --) (LQFP100:  17)
				// TXD0: P32 (LQFP64: 12) (LQFP100:  18)
				// SCK0: P34 (LQFP64: --) (LQFP100:  16)
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
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD1: P15 (LQFP64: 19) (LQFP100:  31)
				// TXD1: P16 (LQFP64: 18) (LQFP100:  30)
				// SCK1: P17 (LQFP64: 17) (LQFP100:  29)
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
				// RXD1: P30 (LQFP64: 14) (LQFP100:  20)
				// TXD1: P26 (LQFP64: 16) (LQFP100:  22)
				// SCK1: P27 (LQFP64: 15) (LQFP100:  21)
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

		static bool sci2_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD2: P12 (LQFP64: --) (LQFP100:  34)
				// TXD2: P13 (LQFP64: --) (LQFP100:  33)
				// SCK2: P51 (LQFP64: --) (LQFP100:  43)
				PORT1::PMR.B2 = 0;
				PORT1::ODR.B2 = i2c;
				MPC::P12PFS.PSEL = sel;  // ok
				PORT1::PMR.B2 = enable;
				PORT1::PMR.B3 = 0;
				PORT1::ODR.B3 = i2c;
				MPC::P13PFS.PSEL = sel;  // ok
				PORT1::PMR.B3 = enable;
				if(spi) {
					PORT5::PMR.B1 = 0;
					MPC::P51PFS.PSEL = sel;  // ok
					PORT5::PMR.B1 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD2: P52 (LQFP64: --) (LQFP100:  42)
				// TXD2: P50 (LQFP64: --) (LQFP100:  44)
				// SCK2: P51 (LQFP64: --) (LQFP100:  43)
				PORT5::PMR.B2 = 0;
				PORT5::ODR.B2 = i2c;
				MPC::P52PFS.PSEL = sel;  // ok
				PORT5::PMR.B2 = enable;
				PORT5::PMR.B0 = 0;
				PORT5::ODR.B0 = i2c;
				MPC::P50PFS.PSEL = sel;  // ok
				PORT5::PMR.B0 = enable;
				if(spi) {
					PORT5::PMR.B1 = 0;
					MPC::P51PFS.PSEL = sel;  // ok
					PORT5::PMR.B1 = enable;
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
			uint8_t sel = enable ? 0b1011 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD3: P16 (LQFP64: 18) (LQFP100:  30)
				// TXD3: P17 (LQFP64: 17) (LQFP100:  29)
				// SCK3: P15 (LQFP64: 19) (LQFP100:  31)
				PORT1::PMR.B6 = 0;
				PORT1::ODR.B6 = i2c;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;
				PORT1::ODR.B7 = i2c;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				if(spi) {
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;  // ok
					PORT1::PMR.B5 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD3: P25 (LQFP64: --) (LQFP100:  23)
				// TXD3: P23 (LQFP64: --) (LQFP100:  25)
				// SCK3: P24 (LQFP64: --) (LQFP100:  24)
				sel = enable ? 0b1010 : 0;
				PORT2::PMR.B5 = 0;
				PORT2::ODR.B5 = i2c;
				MPC::P25PFS.PSEL = sel;  // ok
				PORT2::PMR.B5 = enable;
				PORT2::PMR.B3 = 0;
				PORT2::ODR.B3 = i2c;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
				if(spi) {
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci4_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD4: PB0 (LQFP64: 39) (LQFP100:  61)
				// TXD4: PB1 (LQFP64: 37) (LQFP100:  59)
				// SCK4: PB3 (LQFP64: 36) (LQFP100:  57)
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
			case ORDER::SECOND:
				// RXD4: PK4 (LQFP64: --) (LQFP100: ---)
				// TXD4: PK5 (LQFP64: --) (LQFP100: ---)
				// SCK4: P70 (LQFP64: --) (LQFP100: ---)
				PORTK::PMR.B4 = 0;
				PORTK::ODR.B4 = i2c;
				MPC::PK4PFS.PSEL = sel;  // ok
				PORTK::PMR.B4 = enable;
				PORTK::PMR.B5 = 0;
				PORTK::ODR.B5 = i2c;
				MPC::PK5PFS.PSEL = sel;  // ok
				PORTK::PMR.B5 = enable;
				if(spi) {
					PORT7::PMR.B0 = 0;
					MPC::P70PFS.PSEL = sel;  // ok
					PORT7::PMR.B0 = enable;
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
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD5: PA2 (LQFP64: --) (LQFP100:  68)
				// TXD5: PA4 (LQFP64: 42) (LQFP100:  66)
				// SCK5: PA1 (LQFP64: 44) (LQFP100:  69)
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
				// RXD5: PA3 (LQFP64: 43) (LQFP100:  67)
				// TXD5: PA4 (LQFP64: 42) (LQFP100:  66)
				// SCK5: PA1 (LQFP64: 44) (LQFP100:  69)
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
				// RXD5: PC2 (LQFP64: 32) (LQFP100:  50)
				// TXD5: PC3 (LQFP64: 31) (LQFP100:  49)
				// SCK5: PC4 (LQFP64: 30) (LQFP100:  48)
				PORTC::PMR.B2 = 0;
				PORTC::ODR.B2 = i2c;
				MPC::PC2PFS.PSEL = sel;  // ok
				PORTC::PMR.B2 = enable;
				PORTC::PMR.B3 = 0;
				PORTC::ODR.B3 = i2c;
				MPC::PC3PFS.PSEL = sel;  // ok
				PORTC::PMR.B3 = enable;
				if(spi) {
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = enable;
				}
				break;
			case ORDER::FOURTH:
				// RXD5: PC2 (LQFP64: 32) (LQFP100:  50)
				// TXD5: PC3 (LQFP64: 31) (LQFP100:  49)
				// SCK5: PC1 (LQFP64: --) (LQFP100:  51)				
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
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD6: P01 (LQFP64: --) (LQFP100: ---)
				// TXD6: P00 (LQFP64: --) (LQFP100: ---)
				// SCK6: P02 (LQFP64: --) (LQFP100: ---)
				PORT0::PMR.B1 = 0;
				PORT0::ODR.B1 = i2c;
				MPC::P01PFS.PSEL = sel;  // ok
				PORT0::PMR.B1 = enable;
				PORT0::PMR.B0 = 0;
				PORT0::ODR.B0 = i2c;
				MPC::P00PFS.PSEL = sel;  // ok
				PORT0::PMR.B0 = enable;
				if(spi) {
					PORT0::PMR.B2 = 0;
					MPC::P02PFS.PSEL = sel;  // ok
					PORT0::PMR.B2 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD6: P33 (LQFP64: --) (LQFP100:  17)
				// TXD6: P32 (LQFP64: 12) (LQFP100:  18)
				// SCK6: P34 (LQFP64: --) (LQFP100:  16)
				sel = enable ? 0b1011 : 0;
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
			case ORDER::THIRD:
				// RXD6: PB0 (LQFP64: 39) (LQFP100:  61)
				// TXD6: PB1 (LQFP64: 37) (LQFP100:  59)
				// SCK6: PB3 (LQFP64: 36) (LQFP100:  57)
				sel = enable ? 0b1011 : 0;
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

		static bool sci7_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD7: P92 (LQFP64: --) (LQFP100: ---)
				// TXD7: P90 (LQFP64: --) (LQFP100: ---)
				// SCK7: P91 (LQFP64: --) (LQFP100: ---)
				PORT9::PMR.B2 = 0;
				PORT9::ODR.B2 = i2c;
				MPC::P92PFS.PSEL = sel;  // ok
				PORT9::PMR.B2 = enable;
				PORT9::PMR.B0 = 0;
				PORT9::ODR.B0 = i2c;
				MPC::P90PFS.PSEL = sel;  // ok
				PORT9::PMR.B0 = enable;
				if(spi) {
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;  // ok
					PORT9::PMR.B1 = enable;
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
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD8: PC6 (LQFP64: 28) (LQFP100:  46)
				// TXD8: PC7 (LQFP64: 27) (LQFP100:  45)
				// SCK8: PC5 (LQFP64: 29) (LQFP100:  47)
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
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD9: PB6 (LQFP64: 34) (LQFP100:  54)
				// TXD9: PB7 (LQFP64: 33) (LQFP100:  53)
				// SCK9: PB5 (LQFP64: 35) (LQFP100:  55)
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
			case ORDER::SECOND:
				// RXD9: PK3 (LQFP64: --) (LQFP100: ---)
				// TXD9: PK2 (LQFP64: --) (LQFP100: ---)
				// SCK9: P60 (LQFP64: --) (LQFP100: ---)
				PORTK::PMR.B3 = 0;
				PORTK::ODR.B3 = i2c;
				MPC::PK3PFS.PSEL = sel;  // ok
				PORTK::PMR.B3 = enable;
				PORTK::PMR.B2 = 0;
				PORTK::ODR.B2 = i2c;
				MPC::PK2PFS.PSEL = sel;  // ok
				PORTK::PMR.B2 = enable;
				if(spi) {
					PORT6::PMR.B0 = 0;
					MPC::P60PFS.PSEL = sel;  // ok
					PORT6::PMR.B0 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci10_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD10: P81 (LQFP64: --) (LQFP100: ---)
				// TXD10: P82 (LQFP64: --) (LQFP100: ---)
				// SCK10: P80 (LQFP64: --) (LQFP100: ---)
				PORT8::PMR.B1 = 0;
				PORT8::ODR.B1 = i2c;
				MPC::P81PFS.PSEL = sel;  // ok
				PORT8::PMR.B1 = enable;
				PORT8::PMR.B1 = 0;
				PORT8::ODR.B1 = i2c;
				MPC::P81PFS.PSEL = sel;  // ok
				PORT8::PMR.B1 = enable;
				if(spi) {
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;  // ok
					PORT8::PMR.B0 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci11_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD11: P76 (LQFP64: --) (LQFP100: ---)
				// TXD11: P77 (LQFP64: --) (LQFP100: ---)
				// SCK11: P75 (LQFP64: --) (LQFP100: ---)
				PORT7::PMR.B6 = 0;
				PORT7::ODR.B6 = i2c;
				MPC::P76PFS.PSEL = sel;  // ok
				PORT7::PMR.B6 = enable;
				PORT7::PMR.B7 = 0;
				PORT7::ODR.B7 = i2c;
				MPC::P77PFS.PSEL = sel;  // ok
				PORT7::PMR.B7 = enable;
				if(spi) {
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // ok
					PORT7::PMR.B5 = enable;
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
				// RXD12: PE2 (LQFP64: 49) (LQFP100:  76)
				// TXD12: PE1 (LQFP64: 50) (LQFP100:  77)
				// SCK12: PE0 (LQFP64: 51) (LQFP100:  78)
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
				// SCL0: P16 (LQFP64: 18) (LQFP100:  30)
				// SDA0: P17 (LQFP64: 17) (LQFP100:  29)
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
				// SCL0: P12 (LQFP64: --) (LQFP100:  34)
				// SDA0: P13 (LQFP64: --) (LQFP100:  33)
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
				// RSPCKA: PA5 (LQFP64: --) (LQFP100:  65)
				// MOSIA:  PA6 (LQFP64: 41) (LQFP100:  64)
				// MISOA:  PA7 (LQFP64: --) (LQFP100:  63)
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
				// RSPCKA: PB0 (LQFP64: 39) (LQFP100:  61)
				// MOSIA:  P16 (LQFP64: 18) (LQFP100:  30)
				// MISOA:  P17 (LQFP64: 17) (LQFP100:  29)
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
				// RSPCKA: PC5 (LQFP64: 29) (LQFP100:  47)
				// MOSIA:  PC6 (LQFP64: 28) (LQFP100:  46)
				// MISOA:  PC7 (LQFP64: 27) (LQFP100:  45)
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

		static bool rspi0_ssl_(RSPI ssl, ORDER odr, bool enable) noexcept
		{
			bool ret = true;
			uint8_t sel = enable ? 0b0'1101 : 0;  // ok
			switch(ssl) {
			case RSPI::SSL0:
				// SSLA0: PA4 (LQFP64: 42) (LQFP100:  66)
				// SSLA0: PC4 (LQFP64: 30) (LQFP100:  48)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL1:
				// SSLA1: PA0 (LQFP64: 45) (LQFP100:  70)
				// SSLA1: PC0 (LQFP64: --) (LQFP100:  52)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;
					PORTC::PMR.B0 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL2:
				// SSLA2: PA1 (LQFP64: 44) (LQFP100:  69)
				// SSLA2: PC1 (LQFP64: --) (LQFP100:  51)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;
					PORTC::PMR.B1 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL3:
				// SSLA3: PA2 (LQFP64: --) (LQFP100:  68)
				// SSLA3: PC2 (LQFP64: 32) (LQFP100:  50)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = enable;
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
				case peripheral::SCI4:
					ret = sci4_(odr, ena, opt);
					break;
				case peripheral::SCI5:
					ret = sci5_(odr, ena, opt);
					break;
				case peripheral::SCI6:
					ret = sci6_(odr, ena, opt);
					break;
				case peripheral::SCI7:
					ret = sci7_(odr, ena, opt);
					break;
				case peripheral::SCI8:
					ret = sci8_(odr, ena, opt);
					break;
				case peripheral::SCI9:
					ret = sci9_(odr, ena, opt);
					break;
				case peripheral::SCI10:
					ret = sci10_(odr, ena, opt);
					break;
				case peripheral::SCI11:
					ret = sci11_(odr, ena, opt);
					break;
				case peripheral::SCI12:
					ret = sci12_(odr, ena, opt);
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
