#pragma once
//=========================================================================//
/*!	@file
	@brief	RX660 グループ・ポート・マッピング @n
			・ペリフェラル型に従って、ポートの設定をグループ化して設定 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX660/peripheral.hpp"
#include "RX660/port.hpp"
#include "RX660/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX660 ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sci0_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD0: P21 (LFQFP100:  27) (LFQFP144:  36)
				// TXD0: P20 (LFQFP100:  28) (LFQFP144:  37)
				// SCK0: P22 (LFQFP100:  26) (LFQFP144:  35)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORT2::PMR.B1 = 0;
				PORT2::PDR.B1 = i2c;
				MPC::P21PFS.PSEL = sel;
				PORT2::PMR.B1 = enable;
				PORT2::PMR.B0 = 0;
				PORT2::ODR.B0 = i2c;
				MPC::P20PFS.PSEL = sel;
				PORT2::PMR.B0 = enable;
				if(spi) {
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD0: P33 (LFQFP100:  17) (LFQFP144:  26)
				// TXD0: P32 (LFQFP100:  18) (LFQFP144:  27)
				// SCK0: P34 (LFQFP100:  16) (LFQFP144:  25)
				sel = enable ? 0b00'1011 : 0;  // ok
				PORT3::PMR.B3 = 0;
				PORT3::ODR.B3 = i2c;
				MPC::P33PFS.PSEL = sel;
				PORT3::PMR.B3 = enable;
				PORT3::PMR.B2 = 0;
				PORT3::ODR.B2 = i2c;
				MPC::P32PFS.PSEL = sel;
				PORT3::PMR.B2 = enable;
				if(spi) {
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD1: P15 (LFQFP100:  31) (LFQFP144:  42)
				// TXD1: P16 (LFQFP100:  30) (LFQFP144:  40)
				// SCK1: P17 (LFQFP100:  29) (LFQFP144:  38)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORT1::PMR.B5 = 0;
				PORT1::PDR.B5 = i2c;
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
				// RXD1: P30 (LFQFP100:  20) (LFQFP144:  29)
				// TXD1: P26 (LFQFP100:  22) (LFQFP144:  31)
				// SCK1: P27 (LFQFP100:  21) (LFQFP144:  30)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORT3::PMR.B0 = 0;
				PORT3::ODR.B0 = i2c;
				MPC::P30PFS.PSEL = sel;
				PORT3::PMR.B0 = enable;
				PORT2::PMR.B6 = 0;
				PORT2::ODR.B6 = i2c;
				MPC::P26PFS.PSEL = sel;
				PORT2::PMR.B6 = enable;
				if(spi) {
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD2: P12 (LFQFP100:  34) (LFQFP144:  45)
				// TXD2: P13 (LFQFP100:  33) (LFQFP144:  44)
				// SCK2: P51 (LFQFP100:  43) (LFQFP144:  55)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORT1::PMR.B2 = 0;
				PORT1::ODR.B2 = i2c;
				MPC::P12PFS.PSEL = sel;
				PORT1::PMR.B2 = enable;
				PORT1::PMR.B3 = 0;
				PORT1::ODR.B3 = i2c;
				MPC::P13PFS.PSEL = sel;
				PORT1::PMR.B3 = enable;
				if(spi) {
					PORT5::PMR.B1 = 0;
					MPC::P51PFS.PSEL = sel;
					PORT5::PMR.B1 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD2: P52 (LFQFP100:  42) (LFQFP144:  54)
				// TXD2: P50 (LFQFP100:  44) (LFQFP144:  56)
				// SCK2: P51 (LFQFP100:  43) (LFQFP144:  55)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORT5::PMR.B2 = 0;
				PORT5::ODR.B2 = i2c;
				MPC::P52PFS.PSEL = sel;
				PORT5::PMR.B2 = enable;
				PORT5::PMR.B0 = 0;
				PORT5::ODR.B0 = i2c;
				MPC::P50PFS.PSEL = sel;
				PORT5::PMR.B0 = enable;
				if(spi) {
					PORT5::PMR.B1 = 0;
					MPC::P51PFS.PSEL = sel;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD3: P16 (LFQFP100:  30) (LFQFP144:  40)
				// TXD3: P17 (LFQFP100:  29) (LFQFP144:  38)
				// SCK3: P15 (LFQFP100:  31) (LFQFP144:  42)
				sel = enable ? 0b00'1011 : 0;  // ok
				PORT1::PMR.B6 = 0;
				PORT1::ODR.B6 = i2c;
				MPC::P16PFS.PSEL = sel;
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;
				PORT1::ODR.B7 = i2c;
				MPC::P17PFS.PSEL = sel;
				PORT1::PMR.B7 = enable;
				if(spi) {
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;  // SCK3 (P15 LQFP176: 50)
					PORT1::PMR.B5 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD3: P25 (LFQFP100:  23) (LFQFP144:  32)
				// TXD3: P23 (LFQFP100:  25) (LFQFP144:  34)
				// SCK3: P24 (LFQFP100:  24) (LFQFP144:  33)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORT2::PMR.B5 = 0;
				PORT2::ODR.B5 = i2c;
				MPC::P25PFS.PSEL = sel;
				PORT2::PMR.B5 = enable;
				PORT2::PMR.B3 = 0;
				PORT2::ODR.B3 = i2c;
				MPC::P23PFS.PSEL = sel;
				PORT2::PMR.B3 = enable;
				if(spi) {
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
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
			uint8_t sel = enable ? 0b00'1010 : 0;  // ok
			switch(odr) {
			case ORDER::FIRST:
				// RXD4: PB0 (LFQFP100:  61) (LFQFP144:  87)
				// TXD4: PB1 (LFQFP100:  59) (LFQFP144:  84)
				// SCK4: PB3 (LFQFP100:  57) (LFQFP144:  82)
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;
				PORTB::PMR.B0 = enable;
				PORTB::PMR.B1 = 0;
				PORTB::ODR.B1 = i2c;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
				if(spi) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;
					PORTB::PMR.B3 = enable;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD5: PA2 (LFQFP100:  68) (LFQFP144:  95)
				// TXD5: PA4 (LFQFP100:  66) (LFQFP144:  92)
				// SCK5: PA1 (LFQFP100:  69) (LFQFP144:  96)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORTA::PMR.B2 = 0;
				PORTA::ODR.B2 = i2c;
				MPC::PA2PFS.PSEL = sel;
				PORTA::PMR.B2 = enable;
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;
				PORTA::PMR.B4 = enable;
				if(spi) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD5: PA3 (LFQFP100:  67) (LFQFP144:  94)
				// TXD5: PA4 (LFQFP100:  66) (LFQFP144:  92)
				// SCK5: PA1 (LFQFP100:  69) (LFQFP144:  96)
				sel = enable ? 0b0'1010 : 0;
				PORTA::PMR.B3 = 0;
				PORTA::ODR.B3 = i2c;
				MPC::PA3PFS.PSEL = sel;
				PORTA::PMR.B3 = enable;
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;
				PORTA::PMR.B4 = enable;
				if(spi) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = enable;
				}
				break;
			case ORDER::THIRD:
				// RXD5: PC2 (LFQFP100:  50) (LFQFP144:  70)
				// TXD5: PC3 (LFQFP100:  49) (LFQFP144:  67)
				// SCK5: PC1 (LFQFP100:  51) (LFQFP144:  73)
				sel = enable ? 0b0'1010 : 0;
				PORTC::PMR.B2 = 0;
				PORTC::ODR.B2 = i2c;
				MPC::PC2PFS.PSEL = sel;
				PORTC::PMR.B2 = enable;
				PORTC::PMR.B3 = 0;
				PORTC::ODR.B3 = i2c;
				MPC::PC3PFS.PSEL = sel;
				PORTC::PMR.B3 = enable;
				if(spi) {
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;
					PORTC::PMR.B1 = enable;
				}
				break;
			case ORDER::FOURTH:
				// RXD5: PC2 (LFQFP100:  50) (LFQFP144:  70)
				// TXD5: PC3 (LFQFP100:  49) (LFQFP144:  67)
				// SCK5: PC4 (LFQFP100:  48) (LFQFP144:  66)
				sel = enable ? 0b0'1010 : 0;  // ok
				PORTC::PMR.B2 = 0;
				PORTC::ODR.B2 = i2c;
				MPC::PC2PFS.PSEL = sel;
				PORTC::PMR.B2 = enable;
				PORTC::PMR.B3 = 0;
				PORTC::ODR.B3 = i2c;
				MPC::PC3PFS.PSEL = sel;
				PORTC::PMR.B3 = enable;
				if(spi) {
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = enable;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD6: P01 (LFQFP100: ---) (LFQFP144:   7)
				// TXD6: P00 (LFQFP100: ---) (LFQFP144:   8)
				// SCK6: P02 (LFQFP100: ---) (LFQFP144:   6)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORT0::PMR.B1 = 0;
				PORT0::ODR.B1 = i2c;
				MPC::P01PFS.PSEL = sel;
				PORT0::PMR.B1 = enable;
				PORT0::PMR.B0 = 0;
				PORT0::ODR.B0 = i2c;
				MPC::P00PFS.PSEL = sel;
				PORT0::PMR.B0 = enable;
				if(spi) {
					PORT0::PMR.B2 = 0;
					MPC::P02PFS.PSEL = sel;
					PORT0::PMR.B2 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD6: P33 (LFQFP100:  17) (LFQFP144:  26)
				// TXD6: P32 (LFQFP100:  18) (LFQFP144:  27)
				// SCK6: P34 (LFQFP100:  16) (LFQFP144:  25)
				sel = enable ? 0b0'1010 : 0;  // ok
				PORT3::PMR.B3 = 0;
				PORT3::ODR.B3 = i2c;
				MPC::P33PFS.PSEL = sel;
				PORT3::PMR.B3 = enable;
				PORT3::PMR.B2 = 0;
				PORT3::ODR.B2 = i2c;
				MPC::P32PFS.PSEL = sel;
				PORT3::PMR.B2 = enable;
				if(spi) {
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;
					PORT3::PMR.B4 = enable;
				}
				break;
			case ORDER::THIRD:
				// RXD6: PB0 (LFQFP100:  61) (LFQFP144:  87)
				// TXD6: PB1 (LFQFP100:  59) (LFQFP144:  84)
				// SCK6: PB3 (LFQFP100:  57) (LFQFP144:  82)
				sel = enable ? 0b00'1011 : 0;  // ok
				PORTB::PMR.B1 = 0;
				PORTB::ODR.B1 = i2c;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;
				PORTB::PMR.B0 = enable;
				if(spi) {
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD7: P92 (LFQFP100: ---) (LFQFP144: 128)
				// TXD7: P90 (LFQFP100: ---) (LFQFP144: 131)
				// SCK7: P91 (LFQFP100: ---) (LFQFP144: 129)
				sel = enable ? 0b00'1010 : 0;
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
					MPC::P91PFS.PSEL = sel;
					PORT9::PMR.B1 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD7: P92 (LFQFP100: ---) (LFQFP144: 128)
				// TXD7: P55 (LFQFP100:  39) (LFQFP144:  51)
				// SCK7: P56 (LFQFP100: ---) (LFQFP144:  50)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORT9::PMR.B2 = 0;
				PORT9::ODR.B2 = i2c;
				MPC::P92PFS.PSEL = sel;
				PORT9::PMR.B2 = enable;
				PORT5::PMR.B5 = 0;
				PORT5::ODR.B5 = i2c;
				MPC::P55PFS.PSEL = sel;
				PORT5::PMR.B5 = enable;
				if(spi) {
					PORT5::PMR.B6 = 0;
					MPC::P56PFS.PSEL = sel;
					PORT5::PMR.B6 = enable;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD8: PC6 (LFQFP100:  46) (LFQFP144:  61)
				// TXD8: PC7 (LFQFP100:  45) (LFQFP144:  60)
				// SCK8: PC5 (LFQFP100:  47) (LFQFP144:  62)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORTC::PMR.B6 = 0;
				PORTC::ODR.B6 = i2c;
				MPC::PC6PFS.PSEL = sel;
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B7 = 0;
				PORTC::ODR.B7 = i2c;
				MPC::PC7PFS.PSEL = sel;
				PORTC::PMR.B7 = enable;
				if(spi) {
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD9: PB6 (LFQFP100:  54) (LFQFP144:  79)
				// TXD9: PB7 (LFQFP100:  53) (LFQFP144:  78)
				// SCK9: PB5 (LFQFP100:  55) (LFQFP144:  80)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B7 = 0;
				PORTB::ODR.B7 = i2c;
				MPC::PB7PFS.PSEL = sel;
				PORTB::PMR.B7 = enable;
				if(spi) {
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;
					PORTB::PMR.B5 = enable;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD10: P81 (LFQFP100: ---) (LFQFP144:  64)
				// TXD10: P82 (LFQFP100: ---) (LFQFP144:  63)
				// SCK10: P80 (LFQFP100: ---) (LFQFP144:  65)
				sel = enable ? 0b00'1010 : 0;
				PORTB::PMR.B1 = 0;
				PORTB::ODR.B1 = i2c;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B2 = 0;
				PORTB::ODR.B2 = i2c;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B2 = enable;
				if(spi) {
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;
					PORT8::PMR.B0 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD10: P86 (LFQFP100: ---) (LFQFP144:  41)
				// TXD10: P87 (LFQFP100: ---) (LFQFP144:  39)
				// SCK10: P83 (LFQFP100: ---) (LFQFP144:  58)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORT8::PMR.B6 = 0;
				PORT8::ODR.B6 = i2c;
				MPC::P86PFS.PSEL = sel;
				PORT8::PMR.B6 = enable;
				PORT8::PMR.B7 = 0;
				PORT8::ODR.B7 = i2c;
				MPC::P87PFS.PSEL = sel;
				PORT8::PMR.B7 = enable;
				if(spi) {
					PORT8::PMR.B3 = 0;
					MPC::P83PFS.PSEL = sel;
					PORT8::PMR.B3 = enable;
				}
				break;
			case ORDER::THIRD:
				// RXD10: PC6 (LFQFP100:  46) (LFQFP144:  61)
				// TXD10: PC7 (LFQFP100:  45) (LFQFP144:  60)
				// SCK10: PC5 (LFQFP100:  47) (LFQFP144:  62)
				sel = enable ? 0b01'0100 : 0;  // ok
				PORTC::PMR.B6 = 0;
				PORTC::ODR.B6 = i2c;
				MPC::PC6PFS.PSEL = sel;
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B7 = 0;
				PORTC::ODR.B7 = i2c;
				MPC::PC7PFS.PSEL = sel;
				PORTC::PMR.B7 = enable;
				if(spi) {
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = enable;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD11: P76 (LFQFP100: ---) (LFQFP144:  69)
				// TXD11: P77 (LFQFP100: ---) (LFQFP144:  68)
				// SCK11: P75 (LFQFP100: ---) (LFQFP144:  71)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORT7::PMR.B6 = 0;
				PORT7::ODR.B6 = i2c;
				MPC::P76PFS.PSEL = sel;
				PORT7::PMR.B6 = enable;
				PORT7::PMR.B7 = 0;
				PORT7::ODR.B7 = i2c;
				MPC::P77PFS.PSEL = sel;
				PORT7::PMR.B7 = enable;
				if(spi) {
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;
					PORT7::PMR.B5 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD11: PB6 (LFQFP100:  54) (LFQFP144:  79)
				// TXD11: PB7 (LFQFP100:  53) (LFQFP144:  78)
				// SCK11: PB5 (LFQFP100:  55) (LFQFP144:  80)
				sel = enable ? 0b10'0100 : 0;  // ok
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B7 = 0;
				PORTB::ODR.B7 = i2c;
				MPC::PB7PFS.PSEL = sel;
				PORTB::PMR.B7 = enable;
				if(spi) {
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;
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
			uint8_t sel = 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD12: PE2 (LFQFP100:  76) (LFQFP144: 109)
				// TXD12: PE1 (LFQFP100:  77) (LFQFP144: 110)
				// SCK12: PE0 (LFQFP100:  78) (LFQFP144: 111)
				sel = enable ? 0b00'1100 : 0;  // ok
				PORTE::PMR.B2 = 0;
				PORTE::ODR.B2 = i2c;
				MPC::PE2PFS.PSEL = sel;
				PORTE::PMR.B2 = enable;
				PORTE::PMR.B1 = 0;
				PORTE::ODR.B1 = i2c;
				MPC::PE1PFS.PSEL = sel;
				PORTE::PMR.B1 = enable;
				if(spi) {
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD12: PA2 (LFQFP100:  68) (LFQFP144:  95)
				// TXD12: PA4 (LFQFP100:  66) (LFQFP144:  92)
				// SCK12: PA1 (LFQFP100:  69) (LFQFP144:  96)
				sel = enable ? 0b00'1010 : 0;  // ok
				PORTA::PMR.B2 = 0;
				PORTA::ODR.B2 = i2c;
				MPC::PA2PFS.PSEL = sel;
				PORTA::PMR.B2 = enable;
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;
				PORTA::PMR.B4 = enable;
				if(spi) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rsci10_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b10'1100 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD010: P81 (LFQFP100: ---) (LFQFP144:  64)
				// TXD010: P82 (LFQFP100: ---) (LFQFP144:  63)
				// SCK010: P80 (LFQFP100: ---) (LFQFP144:  65)
				PORT8::PMR.B1 = 0;
				PORT8::ODR.B1 = i2c;
				MPC::P81PFS.PSEL = sel;  // ok
				PORT8::PMR.B1 = enable;
				PORT8::PMR.B2 = 0;
				PORT8::ODR.B2 = i2c;
				MPC::P82PFS.PSEL = sel;  // ok
				PORT8::PMR.B2 = enable;
				if(spi) {
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;  // ok
					PORT8::PMR.B0 = enable;
				}
				break;
			case ORDER::SECOND:
				// RXD010: P86 (LFQFP100: ---) (LFQFP144:  41)
				// TXD010: P87 (LFQFP100: ---) (LFQFP144:  39)
				// SCK010: P83 (LFQFP100: ---) (LFQFP144:  58)
				PORT8::PMR.B6 = 0;
				PORT8::ODR.B6 = i2c;
				MPC::P86PFS.PSEL = sel;  // ok
				PORT8::PMR.B6 = enable;
				PORT8::PMR.B7 = 0;
				PORT8::ODR.B7 = i2c;
				MPC::P87PFS.PSEL = sel;  // ok
				PORT8::PMR.B7 = enable;
				if(spi) {
					PORT8::PMR.B3 = 0;
					MPC::P83PFS.PSEL = sel;  // ok
					PORT8::PMR.B3 = enable;
				}
				break;
			case ORDER::THIRD:
				// RXD010: PC6 (LFQFP100:  46) (LFQFP144:  61)
				// TXD010: PC7 (LFQFP100:  45) (LFQFP144:  60)
				// SCK010: PC5 (LFQFP100:  47) (LFQFP144:  62)
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

		static bool rsci10_de_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b10'1110 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// DE010: P80 (LFQFP100: ---) (LFQFP144:  65)
				PORT8::PMR.B0 = 0;
				MPC::P80PFS.PSEL = sel;  // ok
				PORT8::PMR.B0 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rsci11_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b10'1100 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// RXD011: P76 (LFQFP100: ---) (LFQFP144:  69)
				// TXD011: P77 (LFQFP100: ---) (LFQFP144:  68)
				// SCK011: P75 (LFQFP100: ---) (LFQFP144:  71)
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
			case ORDER::SECOND:
				// RXD011: PB6 (LFQFP100:  54) (LFQFP144:  79)
				// TXD011: PB7 (LFQFP100:  53) (LFQFP144:  78)
				// SCK011: PB5 (LFQFP100:  55) (LFQFP144:  80)
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
			case ORDER::THIRD:
				// RXD011: PC0 (LFQFP100:  52) (LFQFP144:  75)
				// TXD011: PC1 (LFQFP100:  51) (LFQFP144:  73)
				// SCK011: PB5 (LFQFP100:  55) (LFQFP144:  80)
				PORTC::PMR.B0 = 0;
				PORTC::ODR.B0 = i2c;
				MPC::PC0PFS.PSEL = sel;  // ok
				PORTC::PMR.B0 = enable;
				PORTC::PMR.B1 = 0;
				PORTC::ODR.B1 = i2c;
				MPC::PC1PFS.PSEL = sel;  // ok
				PORTC::PMR.B1 = enable;
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

		static bool rsci11_de_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b10'1110 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// DE011: P75 (LFQFP100: ---) (LFQFP144:  71)
				PORT7::PMR.B5 = 0;
				MPC::P75PFS.PSEL = sel;  // ok
				PORT7::PMR.B5 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool riic0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b00'1111 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// SCL0: P12 (LFQFP100:  34) (LFQFP144:  45)
				// SDA0: P13 (LFQFP100:  33) (LFQFP144:  44)
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

		static bool riic2_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b00'1111 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// SCL2: P16 (LFQFP100:  30) (LFQFP144:  40)
				// SDA2: P17 (LFQFP100:  29) (LFQFP144:  38)
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool canfd0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b01'0000 : 0;
			switch(odr) {
			case ORDER::FIRST:
				// CRX0: P15 (LFQFP100:  31) (LFQFP144:  42)
				// CTX0: P14 (LFQFP100:  32) (LFQFP144:  43)
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = enable;
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = sel;  // ok
				PORT1::PMR.B4 = enable;
				break;
			case ORDER::SECOND:
				// CRX0: P33 (LFQFP100:  17) (LFQFP144:  26)
				// CTX0: P32 (LFQFP100:  18) (LFQFP144:  27)
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = sel;  // ok
				PORT3::PMR.B3 = enable;
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = sel;  // ok
				PORT3::PMR.B2 = enable;
				break;
			case ORDER::THIRD:
				// CRX1: P55 (LFQFP100:  39) (LFQFP144:  51)
				// CTX1: P54 (LFQFP100:  40) (LFQFP144:  52)
				PORT5::PMR.B5 = 0;
				MPC::P55PFS.PSEL = sel;  // ok
				PORT5::PMR.B5 = enable;
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = sel;  // ok
				PORT5::PMR.B4 = enable;
				break;
			case ORDER::FOURTH:
				// CRX0: PD2 (LFQFP100:  84) (LFQFP144: 124)
				// CTX0: PD1 (LFQFP100:  85) (LFQFP144: 125)
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

		static bool rspi0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b00'1101 : 0;  // ok
			switch(odr) {
			case ORDER::FIRST:
				// RSPCKA: PA5 (LFQFP100:  65) (LFQFP144:  90)
				// MOSIA:  PA6 (LFQFP100:  64) (LFQFP144:  89)
				// MISOA:  PA7 (LFQFP100:  63) (LFQFP144:  88)
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;
				PORTA::PMR.B5 = enable;
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;
				PORTA::PMR.B6 = enable;
				PORTA::PMR.B7 = 0;
				MPC::PA7PFS.PSEL = sel;
				PORTA::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
				// RSPCKA: PC5 (LFQFP100:  47) (LFQFP144:  62)
				// MOSIA:  PC6 (LFQFP100:  46) (LFQFP144:  61)
				// MISOA:  PC7 (LFQFP100:  45) (LFQFP144:  60)
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;
				PORTC::PMR.B5 = enable;
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = sel;
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
				// SSLA0: PA4 (LFQFP100:  66) (LFQFP144:  92)
				// SSLA0: PC4 (LFQFP100:  48) (LFQFP144:  66)
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
				// SSLA1: PA0 (LFQFP100:  70) (LFQFP144:  97)
				// SSLA1: PC0 (LFQFP100:  52) (LFQFP144:  75)
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
				// SSLA2: PA1 (LFQFP100:  69) (LFQFP144:  96)
				// SSLA2: PC1 (LFQFP100:  51) (LFQFP144:  73)
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
				// SSLA3: PA2 (LFQFP100:  68) (LFQFP144:  95)
				// SSLA3: PC2 (LFQFP100:  50) (LFQFP144:  70)
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

		static bool cmtw0_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
				if(opt == OPTIONAL::CMTW_TOC0) {
					// TOC0: PC7 (LFQFP100:  45) (LFQFP144:  60)
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTC::PMR.B7 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC0) {
					// TIC0: PC6 (LFQFP100:  46) (LFQFP144:  61)
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTC::PMR.B6 = enable;
				} else if(opt == OPTIONAL::CMTW_TOC1) {
					// TOC1: PE7 (LFQFP100:  71) (LFQFP144: 101)
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTE::PMR.B7 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC1) {
					// TIC1: PE6 (LFQFP100:  72) (LFQFP144: 102)
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTE::PMR.B6 = enable;
				} else {
					return false;
				}
			default:
				return false;
			}
			return true;
		}

		static bool cmtw1_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
				if(opt == OPTIONAL::CMTW_TOC0) {
					// TOC2: PD3 (LFQFP100:  83) (LFQFP144: 123)
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTD::PMR.B3 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC0) {
					// TIC2: PD2 (LFQFP100:  84) (LFQFP144: 124)
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTD::PMR.B2 = enable;
				} else if(opt == OPTIONAL::CMTW_TOC1) {
					// TOC3: PE3 (LFQFP100:  75) (LFQFP144: 108)
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTE::PMR.B3 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC1) {
					// TIC3: PE2 (LFQFP100:  76) (LFQFP144: 109)
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTE::PMR.B2 = enable;
				} else {
					return false;
				}
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
			@brief  RSCI 専用ポート切り替え
			@param[in]	per		周辺機器タイプ
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		候補を選択する場合
			@param[in]	opt		オプショナル設定を行う場合	
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn_rsci(peripheral per, bool ena = true, ORDER odr = ORDER::FIRST, OPTIONAL opt = OPTIONAL::NONE) noexcept
		{
			if(odr == ORDER::BYPASS) return false;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::RSCI10:
				if(opt == OPTIONAL::RSCI_DE) {
					ret = rsci10_de_(odr, ena);
				}
				break;
			case peripheral::RSCI11:
				if(opt == OPTIONAL::RSCI_DE) {
					ret = rsci11_de_(odr, ena);
				}
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


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
			@brief  周辺機器に切り替える
			@param[in]	per		周辺機器タイプ
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		ポート・マップ・オーダー
			@param[in]	opt		オプショナル設定を行う場合
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, bool ena = true, ORDER odr = ORDER::FIRST, OPTIONAL opt = OPTIONAL::NONE) noexcept
		{
			if(odr == ORDER::BYPASS) return false;

			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
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
				case peripheral::RSCI10:
					ret = rsci10_(odr, ena, opt);
					break;
				case peripheral::RSCI11:
					ret = rsci11_(odr, ena, opt);
					break;
				case peripheral::RIIC0:
					ret = riic0_(odr, ena);
					break;
				case peripheral::RIIC2:
					ret = riic2_(odr, ena);
					break;
				case peripheral::CANFD0:
					ret = canfd0_(odr, ena);
					break;
				case peripheral::RSPI0:
					ret = rspi0_(odr, ena);
					break;
				case peripheral::CMTW0:
					ret = cmtw0_(odr, ena, opt);
					break;
				case peripheral::CMTW1:
					ret = cmtw1_(odr, ena, opt);
					break;
				default:
					break;
				}
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
