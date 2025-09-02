#pragma once
//=========================================================================//
/*!	@file
	@brief	RX113 グループ・ポート・マッピング
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX113/peripheral.hpp"
#include "RX113/port.hpp"
#include "RX113/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX113 ポート・マッピング・ユーティリティー
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
				// RXD0: P21 (LFQFP64: --) (LFQFP100:   9)
				// TXD0: P20 (LFQFP64: --) (LFQFP100:  10)
				// SCK0: P22 (LFQFP64: --) (LFQFP100:   8)
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
				// RXD0: P11 (LFQFP64: --) (LFQFP100:  36)
				// TXD0: P10 (LFQFP64: --) (LFQFP100:  37)
				// SCK0: P12 (LFQFP64: --) (LFQFP100:  35)
				PORT1::PMR.B1 = 0;
				PORT1::ODR.B1 = i2c;
				MPC::P11PFS.PSEL = sel;  // ok
				PORT1::PMR.B1 = enable;
				PORT1::PMR.B0 = 0;
				PORT1::ODR.B0 = i2c;
				MPC::P10PFS.PSEL = sel;  // ok
				PORT1::PMR.B0 = enable;
				if(spi) {
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = enable ? 0b0'1011 : 0;  // ok
					PORT1::PMR.B2 = enable;
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
			case ORDER::FIRST:  // for BOOT serial port
				// RXD1: P15 (LFQFP64: 19) (LFQFP100:  28)
				// TXD1: P16 (LFQFP64: 18) (LFQFP100:  27)
				// SCK1: P17 (LFQFP64: 17) (LFQFP100:  26)
				PORT1::PMR.B5 = 0;
				PORT1::ODR.B5 = i2c;
				MPC::P15PFS.PSEL = sel;
				PORT1::PMR.B5 = enable;
				PORT1::PMR.B6 = 0;
				PORT1::ODR.B6 = i2c;
				MPC::P16PFS.PSEL = sel;
				PORT1::PMR.B6 = enable;
				if(spi) {
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD1: P30 (LFQFP64:  4) (LFQFP100:  13)
				// TXD1: P26 (LFQFP64:  3) (LFQFP100:  12)
				// SCK1: P27 (LFQFP64:  2) (LFQFP100:  11)
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
			case ORDER::THIRD:
				// RXD1: PC6 (LFQFP64: 28) (LFQFP100:  46)
				// TXD1: PC7 (LFQFP64: 27) (LFQFP100:  45)
				// SCK1: PC5 (LFQFP64: 29) (LFQFP100:  47)
				sel = enable ? 0b0'1011 : 0;
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

		static bool sci2_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD2: P52 (LFQFP64: --) (LFQFP100:  40)
				// TXD2: P50 (LFQFP64: --) (LFQFP100:  42)
				// SCK2: P51 (LFQFP64: --) (LFQFP100:  41)
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

		static bool sci5_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD5: PA2 (LFQFP64: --) (LFQFP100:  68)
				// TXD5: PA4 (LFQFP64: 42) (LFQFP100:  66)
				// SCK5: PA1 (LFQFP64: 44) (LFQFP100:  69)
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
				// RXD5: PA3 (LFQFP64: 43) (LFQFP100:  67)
				// TXD5: PA4 (LFQFP64: 42) (LFQFP100:  66)
				// SCK5: PA1 (LFQFP64: 44) (LFQFP100:  69)
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
				// RXD5: PC2 (LFQFP64: 32) (LFQFP100:  50)
				// TXD5: PC3 (LFQFP64: 31) (LFQFP100:  49)
				// SCK5: PC4 (LFQFP64: 30) (LFQFP100:  48)
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
				// PB7/PC1, PB6/PC0 は共有端子
				// RXD5: PC2 (LFQFP64: 32) (LFQFP100:  50)
				// TXD5: PC3 (LFQFP64: 31) (LFQFP100:  49)
				// SCK5: PC1 (LFQFP64: 33) (LFQFP100:  51)
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
				// RXD6: P02 (LFQFP64: --) (LFQFP100:   3)
				// TXD6: P07 (LFQFP64: --) (LFQFP100:  99)
				// SCK6: P04 (LFQFP64: --) (LFQFP100:   1)
				PORT0::PMR.B2 = 0;
				PORT0::ODR.B2 = i2c;
				MPC::P02PFS.PSEL = sel;  // ok
				PORT0::PMR.B2 = enable;
				PORT0::PMR.B7 = 0;
				PORT0::ODR.B7 = i2c;
				MPC::P07PFS.PSEL = sel;  // ok
				PORT0::PMR.B7 = enable;
				if(spi) {
					PORT0::PMR.B4 = 0;
					MPC::P04PFS.PSEL = sel;  // ok
					PORT0::PMR.B4 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD6: P27 (LFQFP64:  2) (LFQFP100:  11)
				// TXD6: P26 (LFQFP64:  3) (LFQFP100:  12)
				// SCK6: P04 (LFQFP64: --) (LFQFP100:   1)
				PORT2::PMR.B7 = 0;
				PORT2::ODR.B7 = i2c;
				MPC::P27PFS.PSEL = sel;  // ok
				PORT2::PMR.B7 = enable;
				PORT2::PMR.B6 = 0;
				PORT2::ODR.B6 = i2c;
				MPC::P26PFS.PSEL = enable ? 0b0'1100 : 0;  // ok
				PORT2::PMR.B6 = enable;
				if(spi) {
					PORT0::PMR.B4 = 0;
					MPC::P04PFS.PSEL = sel;  // ok
					PORT0::PMR.B4 = enable;
				}
				break;
			case ORDER::THIRD:
				// RXD6: PB0 (LFQFP64: 39) (LFQFP100:  61)
				// TXD6: PB1 (LFQFP64: 37) (LFQFP100:  59)
				// SCK6: PB3 (LFQFP64: 36) (LFQFP100:  57)
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
				// RXD8: PC6 (LFQFP64: 28) (LFQFP100:  46)
				// TXD8: PC7 (LFQFP64: 27) (LFQFP100:  45)
				// SCK8: PC5 (LFQFP64: 29) (LFQFP100:  47)
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
			case ORDER::SECOND:
				// RXD8: PA6 (LFQFP64: 41) (LFQFP100:  63)
				// TXD8: PA7 (LFQFP64: --) (LFQFP100:  64)
				// SCK8: PA5 (LFQFP64: --) (LFQFP100:  65)
				PORTA::PMR.B6 = 0;
				PORTA::ODR.B6 = i2c;
				MPC::PA6PFS.PSEL = sel;  // ok
				PORTA::PMR.B6 = enable;
				PORTA::PMR.B7 = 0;
				PORTA::ODR.B7 = i2c;
				MPC::PA7PFS.PSEL = sel;  // ok
				PORTA::PMR.B7 = enable;
				if(spi) {
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;  // ok
					PORTA::PMR.B5 = enable;
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
				// PB7/PC1, PB6/PC0 は共有端子
				// RXD9: PB6 (LFQFP64: 34) (LFQFP100:  54)
				// TXD9: PB7 (LFQFP64: 33) (LFQFP100:  53)
				// SCK9: PB5 (LFQFP64: 35) (LFQFP100:  55)
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
				// RXD9: PE4 (LFQFP64: 47) (LFQFP100:  74)
				// TXD9: PE5 (LFQFP64: 46) (LFQFP100:  73)
				// SCK9: PE3 (LFQFP64: 48) (LFQFP100:  75)
				PORTE::PMR.B4 = 0;
				PORTE::ODR.B4 = i2c;
				MPC::PE4PFS.PSEL = sel;  // ok
				PORTE::PMR.B4 = enable;
				PORTE::PMR.B5 = 0;
				PORTE::ODR.B5 = i2c;
				MPC::PE5PFS.PSEL = sel;  // ok
				PORTE::PMR.B5 = enable;
				if(spi) {
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;  // ok
					PORTE::PMR.B3 = enable;
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
				// RXD12: PE2 (LFQFP64: 49) (LFQFP100:  76)
				// TXD12: PE1 (LFQFP64: 50) (LFQFP100:  77)
				// SCK12: PE0 (LFQFP64: 51) (LFQFP100:  78)
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
			case ORDER::SECOND:
				// RXD12: P17 (LFQFP64: 17) (LFQFP100:  26)
				// TXD12: P14 (LFQFP64: 20) (LFQFP100:  29)
				// SCK12: P27 (LFQFP64:  2) (LFQFP100:  11)
				PORT1::PMR.B7 = 0;
				PORT1::ODR.B7 = i2c;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				PORT1::PMR.B4 = 0;
				PORT1::ODR.B4 = i2c;
				MPC::P14PFS.PSEL = sel;  // ok
				PORT1::PMR.B4 = enable;
				if(spi) {
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = enable;
				}
				break;
			case ORDER::THIRD:
				// RXD12: P11 (LFQFP64: --) (LFQFP100:  36)
				// TXD12: P10 (LFQFP64: --) (LFQFP100:  37)
				// SCK12: P12 (LFQFP64: --) (LFQFP100:  35)
				PORT1::PMR.B1 = 0;
				PORT1::ODR.B1 = i2c;
				MPC::P11PFS.PSEL = sel;  // ok
				PORT1::PMR.B1 = enable;
				PORT1::PMR.B0 = 0;
				PORT1::ODR.B0 = i2c;
				MPC::P10PFS.PSEL = sel;  // ok
				PORT1::PMR.B0 = enable;
				if(spi) {
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;  // ok
					PORT1::PMR.B2 = enable;
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
				// SCL0: P16 (LFQFP64: 18) (LFQFP100:  27)
				// SDA0: P17 (LFQFP64: 17) (LFQFP100:  26)
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
				// SCL0: PB0 (LFQFP64: 39) (LFQFP100:  61)
				// SDA0: PA6 (LFQFP64: 41) (LFQFP100:  63)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;  // ok
				PORTA::PMR.B6 = enable;
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
				// RSPCKA: P15 (LFQFP64: 19) (LFQFP100:  28)
				// MOSIA:  P16 (LFQFP64: 18) (LFQFP100:  27)
				// MISOA:  P17 (LFQFP64: 17) (LFQFP100:  26)
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = enable;
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
				// RSPCKA: PB0 (LFQFP64: 39) (LFQFP100:  61)
				// MOSIA:  PA6 (LFQFP64: 41) (LFQFP100:  63)
				// MISOA:  PA3 (LFQFP64: 43) (LFQFP100:  67)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;  // ok
				PORTA::PMR.B6 = enable;
				PORTA::PMR.B3 = 0;		
				MPC::PA3PFS.PSEL = sel;  // ok
				PORTA::PMR.B3 = enable;
				break;
			case ORDER::THIRD:
				// RSPCKA: PC5 (LFQFP64: 29) (LFQFP100:  47)
				// MOSIA:  PC6 (LFQFP64: 28) (LFQFP100:  46)
				// MISOA:  PC7 (LFQFP64: 27) (LFQFP100:  45)
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
			case ORDER::FOURTH:
				// RSPCKA: PE3 (LFQFP64: 48) (LFQFP100:  75)
				// MOSIA:  PE4 (LFQFP64: 47) (LFQFP100:  74)
				// MISOA:  PE5 (LFQFP64: 46) (LFQFP100:  73)
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = sel;  // ok
				PORTE::PMR.B3 = enable;
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = sel;  // ok
				PORTE::PMR.B4 = enable;
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = sel;  // ok
				PORTE::PMR.B5 = enable;
				break;
			case ORDER::FIFTH:
				// RSPCKA: P51 (LFQFP64: --) (LFQFP100:  41)
				// MOSIA:  P50 (LFQFP64: --) (LFQFP100:  42)
				// MISOA:  P52 (LFQFP64: --) (LFQFP100:  40)
				PORT5::PMR.B1 = 0;
				MPC::P51PFS.PSEL = sel;  // ok
				PORT5::PMR.B1 = enable;
				PORT5::PMR.B0 = 0;
				MPC::P50PFS.PSEL = sel;  // ok
				PORT5::PMR.B0 = enable;
				PORT5::PMR.B2 = 0;
				MPC::P52PFS.PSEL = sel;  // ok
				PORT5::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi0_ssl_(RSPI ssl, ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1101 : 0;
			bool ret = true;
			switch(ssl) {
			case RSPI::SSL0:
				// SSLA0: P14 (LFQFP64: 20) (LFQFP100:  29)
				// SSLA0: PA4 (LFQFP64: 42) (LFQFP100:  66)
				// SSLA0: PC4 (LFQFP64: 30) (LFQFP100:  48)
				// SSLA0: P53 (LFQFP64: --) (LFQFP100:  39)
				if(odr == ORDER::FIRST) {
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // ok
					PORT1::PMR.B4 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = enable;
				} else if(odr == ORDER::FOURTH) {
					PORT5::PMR.B3 = 0;
					MPC::P53PFS.PSEL = sel;  // ok
					PORT5::PMR.B3 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL1:
				// PB6/PC0 は共有端子
				// SSL1: PA0 (LFQFP64: 45) (LFQFP100:  70)
				// SSL1: PC0 (LFQFP64: 34) (LFQFP100:  52)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;  // ok
					PORTC::PMR.B0 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL2:
				// PB7/PC1 は共有端子
				// SSL2: PA1 (LFQFP64: 44) (LFQFP100:  69)
				// SSL2: PC1 (LFQFP64: 33) (LFQFP100:  51)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;  // ok
					PORTC::PMR.B1 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL3:
				// SSL3: PA2 (LFQFP64: --) (LFQFP100:  68)
				// SSL3: PC2 (LFQFP64: 32) (LFQFP100:  50)
				if(odr == ORDER::FIRST) {
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;  // ok
					PORTA::PMR.B2 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;  // ok
					PORTC::PMR.B2 = enable;
				} else {
					ret = false;
				}
				break;
			default:
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
