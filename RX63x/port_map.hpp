#pragma once
//=========================================================================//
/*!	@file
	@brief	RX631/RX63N グループ・ポート・マッピング @n
			BOOT Mode Serial: @n
			PF2/RXD1 (177/176 Pin), P30/RXD1(145, 144, 100, 64, 48 Pin)  @n
			PF0/TXD1 (177/176 Pin), P26/RXD1(145, 144, 100, 64, 48 Pin) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX63x/peripheral.hpp"
#include "RX63x/port.hpp"
#include "RX63x/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX631/RX63N ポート・マッピング・ユーティリティー
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
			// RXD0: P21 (LFQFP100:  27) (LFQFP144:  36) (LFQFP176:  44)
			// TXD0: P20 (LFQFP100:  28) (LFQFP144:  37) (LFQFP176:  45)
			// SCK0: P22 (LFQFP100:  26) (LFQFP144:  35) (LFQFP176:  43)
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
			// RXD0: P33 (LFQFP100:  17) (LFQFP144:  26) (LFQFP176:  28)
			// TXD0: P32 (LFQFP100:  18) (LFQFP144:  27) (LFQFP176:  29)
			// SCK0: P34 (LFQFP100:  16) (LFQFP144:  25) (LFQFP176:  27)
				sel = enable ? 0b0'1011 : 0;
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
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD1: P15 (LFQFP100:  31) (LFQFP144:  42) (LFQFP176:  50)
			// TXD1: P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
			// SCK1: P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
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
			case ORDER::SECOND:  // for Serial BOOT (145/144/100/64/48 pin)
			// RXD1: P30 (LFQFP100:  20) (LFQFP144:  29) (LFQFP176:  33)
			// TXD1: P26 (LFQFP100:  22) (LFQFP144:  31) (LFQFP176:  37)
			// SCK1: P27 (LFQFP100:  21) (LFQFP144:  30) (LFQFP176:  36)
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
			case ORDER::THIRD:  // Serial Boot Mode (177/176 pin)
			// RXD1: PF2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  31)
			// TXD1: PF0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  35)
			// SCK1: PF1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  34)
				PORTF::PMR.B2 = 0;
				PORTF::ODR.B2 = i2c;
				MPC::PF2PFS.PSEL = sel;  // ok
				PORTF::PMR.B2 = enable;
				PORTF::PMR.B0 = 0;
				PORTF::ODR.B0 = i2c;
				MPC::PF0PFS.PSEL = sel;  // ok
				PORTF::PMR.B0 = enable;
				if(spi) {
					PORTF::PMR.B1 = 0;
					MPC::PF1PFS.PSEL = sel;
					PORTF::PMR.B1 = enable;
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
			// RXD2: P12 (LFQFP100:  34) (LFQFP144:  45) (LFQFP176:  54)
			// TXD2: P13 (LFQFP100:  33) (LFQFP144:  44) (LFQFP176:  53)
			// SCK2: P11 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  55)
				PORT1::PMR.B2 = 0;
				PORT1::ODR.B2 = i2c;
				MPC::P12PFS.PSEL = sel;  // ok
				PORT1::PMR.B2 = enable;
				PORT1::PMR.B3 = 0;
				PORT1::ODR.B3 = i2c;
				MPC::P13PFS.PSEL = sel;  // ok
				PORT1::PMR.B3 = enable;
				if(spi) {
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;  // ok
					PORT1::PMR.B1 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD2: P52 (LFQFP100:  42) (LFQFP144:  54) (LFQFP176:  70)
			// TXD2: P50 (LFQFP100:  44) (LFQFP144:  56) (LFQFP176:  72)
			// SCK2: P51 (LFQFP100:  43) (LFQFP144:  55) (LFQFP176:  71)
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
			uint8_t sel = enable ? 0b0'1011 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD3: P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
			// TXD3: P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
			// SCK3: P15 (LFQFP100:  31) (LFQFP144:  42) (LFQFP176:  50)
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
			// RXD3: P25 (LFQFP100:  23) (LFQFP144:  32) (LFQFP176:  38)
			// TXD3: P23 (LFQFP100:  25) (LFQFP144:  34) (LFQFP176:  42)
			// SCK3: P24 (LFQFP100:  24) (LFQFP144:  33) (LFQFP176:  40)
				sel = enable ? 0b0'1010 : 0;
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
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD4: PB0 (LFQFP100:  61) (LFQFP144:  87) (LFQFP176: 104)
			// TXD4: PB1 (LFQFP100:  59) (LFQFP144:  84) (LFQFP176: 100)
			// SCK4: PB3 (LFQFP100:  57) (LFQFP144:  82) (LFQFP176:  98)
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

		static bool sci5_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD5: PA2 (LFQFP100:  68) (LFQFP144:  95) (LFQFP176: 112)
			// TXD5: PA4 (LFQFP100:  66) (LFQFP144:  92) (LFQFP176: 109)
			// SCK5: PA1 (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
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
			// RXD5: PA3 (LFQFP100:  67) (LFQFP144:  94) (LFQFP176: 110)
			// TXD5: PA4 (LFQFP100:  66) (LFQFP144:  92) (LFQFP176: 109)
			// SCK5: PA1 (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
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
			// RXD5: PC2 (LFQFP100:  50) (LFQFP144:  70) (LFQFP176:  86)
			// TXD5: PC3 (LFQFP100:  49) (LFQFP144:  67) (LFQFP176:  83)
			// SCK5: PC1 (LFQFP100:  51) (LFQFP144:  73) (LFQFP176:  89)
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
			case ORDER::FOURTH:
			// RXD5: PC2 (LFQFP100:  50) (LFQFP144:  70) (LFQFP176:  86)
			// TXD5: PC3 (LFQFP100:  49) (LFQFP144:  67) (LFQFP176:  83)
			// SCK5: PC4 (LFQFP100:  48) (LFQFP144:  66) (LFQFP176:  82)
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
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD6: P01 (LFQFP100: ---) (LFQFP144:   7) (LFQFP176:   7)
			// TXD6: P00 (LFQFP100: ---) (LFQFP144:   8) (LFQFP176:   8)
			// SCK6: P02 (LFQFP100: ---) (LFQFP144:   6) (LFQFP176:   6)
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
			// RXD6: P33 (LFQFP100:  17) (LFQFP144:  26) (LFQFP176:  28)
			// TXD6: P32 (LFQFP100:  18) (LFQFP144:  27) (LFQFP176:  29)
			// SCK6: P34 (LFQFP100:  16) (LFQFP144:  25) (LFQFP176:  27)
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
			// RXD6: PB0 (LFQFP100:  61) (LFQFP144:  87) (LFQFP176: 104)
			// TXD6: PB1 (LFQFP100:  59) (LFQFP144:  84) (LFQFP176: 100)
			// SCK6: PB3 (LFQFP100:  57) (LFQFP144:  82) (LFQFP176:  98)
				sel = enable ? 0b0'1011 : 0;
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
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD7: P92 (LFQFP100: ---) (LFQFP144: 128) (LFQFP176: 160)
			// TXD7: P90 (LFQFP100: ---) (LFQFP144: 131) (LFQFP176: 163)
			// SCK7: P91 (LFQFP100: ---) (LFQFP144: 129) (LFQFP176: 161)
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
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD8: PC6 (LFQFP100:  46) (LFQFP144:  61) (LFQFP176:  77)
			// TXD8: PC7 (LFQFP100:  45) (LFQFP144:  60) (LFQFP176:  76)
			// SCK8: PC5 (LFQFP100:  47) (LFQFP144:  62) (LFQFP176:  78)
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
			// RXD9: PB6 (LFQFP100:  54) (LFQFP144:  79) (LFQFP176:  95)
			// TXD9: PB7 (LFQFP100:  53) (LFQFP144:  78) (LFQFP176:  94)
			// SCK9: PB5 (LFQFP100:  55) (LFQFP144:  80) (LFQFP176:  96)
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

		static bool sci10_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD10: P81 (LFQFP100: ---) (LFQFP144:  64) (LFQFP176:  80)
			// TXD10: P82 (LFQFP100: ---) (LFQFP144:  63) (LFQFP176:  79)
			// SCK10: P80 (LFQFP100: ---) (LFQFP144:  65) (LFQFP176:  81)
				PORT8::PMR.B1 = 0;
				PORTB::ODR.B1 = i2c;
				MPC::P81PFS.PSEL = sel;  // ok
				PORT8::PMR.B1 = enable;
				PORT8::PMR.B2 = 0;
				PORTB::ODR.B2 = i2c;
				MPC::P82PFS.PSEL = sel;  // ok
				PORT8::PMR.B2 = enable;
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
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD11: P76 (LFQFP100: ---) (LFQFP144:  69) (LFQFP176:  85)
			// TXD11: P77 (LFQFP100: ---) (LFQFP144:  68) (LFQFP176:  84)
			// SCK11: P75 (LFQFP100: ---) (LFQFP144:  71) (LFQFP176:  87)
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
			// RXD12: PE2 (LFQFP100:  76) (LFQFP144: 109) (LFQFP176: 133)
			// TXD12: PE1 (LFQFP100:  77) (LFQFP144: 110) (LFQFP176: 134)
			// SCK12: PE0 (LFQFP100:  78) (LFQFP144: 111) (LFQFP176: 135)
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
			// SCL0: P12 (LFQFP100:  34) (LFQFP144:  45) (LFQFP176:  54)
			// SDA0: P13 (LFQFP100:  33) (LFQFP144:  44) (LFQFP176:  53)
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

		static bool riic1_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1111 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// SCL1: P21 (LFQFP100:  27) (LFQFP144:  36) (LFQFP176:  44)
			// SDA1: P20 (LFQFP100:  28) (LFQFP144:  37) (LFQFP176:  45)
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;  // ok
				PORT2::PMR.B1 = enable;
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // ok
				PORT2::PMR.B0 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool riic2_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1111 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// SCL2: P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
			// SDA2: P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
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

		static bool riic3_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1111 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// SCL3: PC0 (LFQFP100:  52) (LFQFP144:  75) (LFQFP176:  91)
			// SDA3: PC1 (LFQFP100:  51) (LFQFP144:  73) (LFQFP176:  89)
				PORTC::PMR.B0 = 0;
				MPC::PC0PFS.PSEL = sel;  // ok
				PORTC::PMR.B0 = enable;
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = sel;  // ok
				PORTC::PMR.B1 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool can0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b1'0000 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// CRX0: P33 (LFQFP100:  17) (LFQFP144:  26) (LFQFP176:  28)
			// CTX0: P32 (LFQFP100:  18) (LFQFP144:  27) (LFQFP176:  29)
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = sel;  // ok
				PORT3::PMR.B3 = enable;
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = sel;  // ok
				PORT3::PMR.B2 = enable;
				break;
			case ORDER::SECOND:
			// CRX0: PD2 (LFQFP100:  84) (LFQFP144: 124) (LFQFP176: 154)
			// CTX0: PD1 (LFQFP100:  85) (LFQFP144: 125) (LFQFP176: 156)
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

		static bool can1_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b1'0000 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// CRX1: P15 (LFQFP100:  31) (LFQFP144:  42) (LFQFP176:  50)
			// CTX1: P14 (LFQFP100:  32) (LFQFP144:  43) (LFQFP176:  51)
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = enable;
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = sel;  // ok
				PORT1::PMR.B4 = enable;
				break;
			case ORDER::SECOND:
			// CRX1: P55 (LFQFP100:  39) (LFQFP144:  51) (LFQFP176:  66)
			// CTX1: P54 (LFQFP100:  40) (LFQFP144:  52) (LFQFP176:  67)
				PORT5::PMR.B5 = 0;
				MPC::P55PFS.PSEL = sel;  // ok
				PORT5::PMR.B5 = enable;
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = sel;  // ok
				PORT5::PMR.B4 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool can2_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b1'0000 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// ※ ROM 容量 1M バイト以下の製品には含まれない
			// CRX2: P67 (LFQFP100: ---) (LFQFP144:  98) (LFQFP176: 120)
			// CTX2: P66 (LFQFP100: ---) (LFQFP144:  99) (LFQFP176: 122)
				PORT6::PMR.B7 = 0;
				MPC::P67PFS.PSEL = sel;  // ok
				PORT6::PMR.B7 = enable;
				PORT6::PMR.B6 = 0;
				MPC::P66PFS.PSEL = sel;  // ok
				PORT6::PMR.B6 = enable;
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
			// RSPCKA: PA5 (LFQFP100:  65) (LFQFP144:  90) (LFQFP176: 108)
			// MOSIA:  PA6 (LFQFP100:  64) (LFQFP144:  89) (LFQFP176: 107)
			// MISOA:  PA7 (LFQFP100:  63) (LFQFP144:  88) (LFQFP176: 106)
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
			// RSPCKA: PB0 (LFQFP100:  61) (LFQFP144:  87) (LFQFP176: 104)
			// MOSIA:  P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
			// MISOA:  P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
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
			// RSPCKA: PC5 (LFQFP100:  47) (LFQFP144:  62) (LFQFP176:  78)
			// MOSIA:  PC6 (LFQFP100:  46) (LFQFP144:  61) (LFQFP176:  77)
			// MISOA:  PC7 (LFQFP100:  45) (LFQFP144:  60) (LFQFP176:  76)
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
				// SSLA0: PA4 (LFQFP100:  66) (LFQFP144:  92) (LFQFP176: 109)
				// SSLA0: PC4 (LFQFP100:  48) (LFQFP144:  66) (LFQFP176:  82)
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
				// SSLA1: PA0 (LFQFP100:  70) (LFQFP144:  97) (LFQFP176: 118)
				// SSLA1: PC0 (LFQFP100:  52) (LFQFP144:  75) (LFQFP176:  91)
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
				// SSLA2: PA1 (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
				// SSLA2: PC1 (LFQFP100:  51) (LFQFP144:  73) (LFQFP176:  89)
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
				// SSLA3: PA2 (LFQFP100:  68) (LFQFP144:  95) (LFQFP176: 112)
				// SSLA3: PC2 (LFQFP100:  50) (LFQFP144:  70) (LFQFP176:  86)
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

		static bool rspi1_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1110 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RSPCKB: P27 (LFQFP100:  21) (LFQFP144:  30) (LFQFP176:  36)
			// MOSIB:  P26 (LFQFP100:  22) (LFQFP144:  31) (LFQFP176:  37)
			// MISOB:  P30 (LFQFP100:  20) (LFQFP144:  29) (LFQFP176:  33)
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = sel;  // ok
				PORT2::PMR.B7 = enable;
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = sel;  // ok
				PORT2::PMR.B6 = enable;
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = sel;  // ok
				PORT3::PMR.B0 = enable;
				break;
			case ORDER::SECOND:
			// RSPCKB: PE1 (LFQFP100:  77) (LFQFP144: 110) (LFQFP176: 134)
			// MOSIB:  PE2 (LFQFP100:  76) (LFQFP144: 109) (LFQFP176: 133)
			// MISOB:  PE3 (LFQFP100:  75) (LFQFP144: 108) (LFQFP176: 132)
				PORTE::PMR.B1 = 0;
				MPC::PE1PFS.PSEL = sel;  // ok
				PORTE::PMR.B1 = enable;
				PORTE::PMR.B2 = 0;
				MPC::PE2PFS.PSEL = sel;  // ok
				PORTE::PMR.B2 = enable;
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = sel;  // ok
				PORTE::PMR.B3 = enable;
				break;
			case ORDER::THIRD:
			// RSPCKB: PE5 (LFQFP100:  73) (LFQFP144: 106) (LFQFP176: 130)
			// MOSIB:  PE6 (LFQFP100:  72) (LFQFP144: 102) (LFQFP176: 126)
			// MISOB:  PE7 (LFQFP100:  71) (LFQFP144: 101) (LFQFP176: 125)
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = sel;  // ok
				PORTE::PMR.B5 = enable;
				PORTE::PMR.B6 = 0;
				MPC::PE6PFS.PSEL = sel;  // ok
				PORTE::PMR.B6 = enable;
				PORTE::PMR.B7 = 0;
				MPC::PE7PFS.PSEL = sel;  // ok
				PORTE::PMR.B7 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi1_ssl_(RSPI ssl, ORDER odr, bool enable) noexcept
		{
			bool ret = true;
			uint8_t sel = enable ? 0b0'1101 : 0;  // ok
			switch(ssl) {
			case RSPI::SSL0:
				// SSLB0: P31 (LFQFP100:  19) (LFQFP144:  28) (LFQFP176:  32)
				// SSLB0: PE4 (LFQFP100:  74) (LFQFP144: 107) (LFQFP176: 131)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;
					PORT3::PMR.B1 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;
					PORTE::PMR.B4 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL1:
				// SSLB1: P50 (LFQFP100:  44) (LFQFP144:  56) (LFQFP176:  72)
				// SSLB1: PE0 (LFQFP100:  78) (LFQFP144: 111) (LFQFP176: 135)
				if(odr == ORDER::FIRST) {
					PORT5::PMR.B0 = 0;
					MPC::P50PFS.PSEL = sel;
					PORT5::PMR.B0 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL2:
				// SSLB2: P51 (LFQFP100:  43) (LFQFP144:  55) (LFQFP176:  71)
				// SSLB2: PE1 (LFQFP100:  77) (LFQFP144: 110) (LFQFP176: 134)
				if(odr == ORDER::FIRST) {
					PORT5::PMR.B1 = 0;
					MPC::P51PFS.PSEL = sel;
					PORT5::PMR.B1 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL3:
				// SSLB3: P52 (LFQFP100:  42) (LFQFP144:  54) (LFQFP176:  70)
				// SSLB3: PE2 (LFQFP100:  76) (LFQFP144: 109) (LFQFP176: 133)
				if(odr == ORDER::FIRST) {
					PORT5::PMR.B2 = 0;
					MPC::P52PFS.PSEL = sel;
					PORT5::PMR.B2 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;
					PORTE::PMR.B2 = enable;
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

		static bool rspi2_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1101 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RSPCKC: PD3 (LFQFP100:  83) (LFQFP144: 123) (LFQFP176: 150)
			// MOSIC:  PD1 (LFQFP100:  85) (LFQFP144: 125) (LFQFP176: 156)
			// MISOC:  PD2 (LFQFP100:  84) (LFQFP144: 124) (LFQFP176: 154)
				PORTD::PMR.B3 = 0;
				MPC::PD3PFS.PSEL = sel;  // ok
				PORTD::PMR.B3 = enable;
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = sel;  // ok
				PORTD::PMR.B1 = enable;
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = sel;  // ok
				PORTD::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi2_ssl_(RSPI ssl, ORDER odr, bool enable) noexcept
		{
			bool ret = true;
			uint8_t sel = enable ? 0b0'1101 : 0;  // ok
			switch(ssl) {
			case RSPI::SSL0:
				// SSLC0: PD4 (LFQFP100:  82) (LFQFP144: 122) (LFQFP176: 148)
				if(odr == ORDER::FIRST) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL1:
				// SSLC1: PD5 (LFQFP100:  81) (LFQFP144: 121) (LFQFP176: 147)
				if(odr == ORDER::FIRST) {
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B5 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL2:
				// SSLC2: PD6 (LFQFP100:  80) (LFQFP144: 120) (LFQFP176: 145)
				if(odr == ORDER::FIRST) {
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL3:
				// SSLC3: PD7 (LFQFP100:  79) (LFQFP144: 119) (LFQFP176: 143)
				if(odr == ORDER::FIRST) {
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = enable;
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  USB0 ポート専用切り替え
			@param[in]	sel		USB ポート選択
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		ポート・マップ・オプション（ポート候補）
			@return 無効な場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_usb(USB_PORT sel, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(sel) {
			case USB_PORT::VBUS:
				switch(odr) {
				// P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b01'0001 : 0;
					PORT1::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::EXICEN:
				// P21 (LFQFP100:  27) (LFQFP144:  36) (LFQFP176:  44)
				// PC6
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = ena ? 0b01'0011 : 0;
					PORT2::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::VBUSEN:
				// P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
				// P24 (LFQFP100:  24) (LFQFP144:  33) (LFQFP176:  40)
				// P32 (LFQFP100:  18) (LFQFP144:  27) (LFQFP176:  29)
				// P26
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b01'0010 : 0;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = ena ? 0b01'0011 : 0;
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = ena ? 0b01'0011 : 0;
					PORT3::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURA:
				// P14 (LFQFP100:  32) (LFQFP144:  43) (LFQFP176:  51)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = ena ? 0b01'0010 : 0;
					PORT1::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURB:
				// P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b01'0011 : 0;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = ena ? 0b01'0011 : 0;
					PORT2::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::ID:
				// P20 (LFQFP100:  28) (LFQFP144:  37) (LFQFP176:  45)
				// PC5
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = ena ? 0b01'0011 : 0;
					PORT2::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

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
			switch(per) {
			case peripheral::RSPI0:
				ret = rspi0_ssl_(ssl, odr, ena);
				break;
			case peripheral::RSPI1:
				ret = rspi1_ssl_(ssl, odr, ena);
				break;
			case peripheral::RSPI2:
				ret = rspi2_ssl_(ssl, odr, ena);
				break;
			default:
				break;
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
				case peripheral::RIIC1:
					ret = riic1_(odr, ena);
					break;
				case peripheral::RIIC2:
					ret = riic2_(odr, ena);
					break;
				case peripheral::RIIC3:
					ret = riic3_(odr, ena);
					break;
				case peripheral::CAN0:
					ret = can0_(odr, ena);
					break;
				case peripheral::CAN1:
					ret = can1_(odr, ena);
					break;
				case peripheral::CAN2:
					ret = can2_(odr, ena);
					break;
				case peripheral::RSPI0:
					ret = rspi0_(odr, ena);
					break;
				case peripheral::RSPI1:
					ret = rspi1_(odr, ena);
					break;
				case peripheral::RSPI2:
					ret = rspi2_(odr, ena);
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
