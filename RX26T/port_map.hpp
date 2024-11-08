#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・ポート・マッピング @n
			・ポートの選択は「候補」に従うポリシーを採用している。 @n
			・単独で指定する場合や、グループで指定する場合などがある。 @n
			・独自に指定する場合、「BYPASS」を選択する事が出来る。 @n
			・「候補」の順番は、ハードウェアーマニュアル MPC の解説に準拠している。 @n
			※上記ルールに従っていない場合もあるので注意が必要（工事中）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX26T/peripheral.hpp"
#include "RX26T/port.hpp"
#include "RX26T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sci1_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b00'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:  // Serial BOOT
			// RXD1: PD5
				PORTD::PMR.B3 = 0;
				PORTD::ODR.B3 = i2c;
				MPC::PD3PFS.PSEL = sel;
				PORTD::PMR.B3 = enable;
			// TXD1: PD3
				PORTD::PMR.B5 = 0;
				PORTD::ODR.B5 = i2c;
				MPC::PD5PFS.PSEL = sel;
				PORTD::PMR.B5 = enable;
			// SCK1: PD4
				if(spi) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
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
			uint8_t sel = enable ? 0b00'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD5: P37
				PORT3::PMR.B7 = 0;
				PORT3::ODR.B7 = i2c;
				MPC::P37PFS.PSEL = sel;
				PORT3::PMR.B7 = enable;
			// TXD5: P36
				PORT3::PMR.B6 = 0;
				PORT3::ODR.B6 = i2c;
				MPC::P36PFS.PSEL = sel;
				PORT3::PMR.B6 = enable;
			// SCK5: P70
				if(spi) {
					PORT7::PMR.B0 = 0;
					MPC::P70PFS.PSEL = sel;
					PORT7::PMR.B0 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD5: P91
				PORT9::PMR.B1 = 0;
				PORT9::ODR.B1 = i2c;
				MPC::P91PFS.PSEL = sel;
				PORT9::PMR.B1 = enable;
			// TXD5: P90
				PORT9::PMR.B0 = 0;
				PORT9::ODR.B0 = i2c;
				MPC::P90PFS.PSEL = sel;
				PORT9::PMR.B0 = enable;
			// SCK5: P70
				if(spi) {
					PORT7::PMR.B0 = 0;
					MPC::P70PFS.PSEL = sel;
					PORT7::PMR.B0 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD5: PB6
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
			// TXD5: PB5
				PORTB::PMR.B5 = 0;
				PORTB::ODR.B5 = i2c;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = enable;
			// SCK5: PB7
				if(spi) {
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = enable;
				}
				break;
			case ORDER::FOURTH:
			// RXD5: PE0
				PORTE::PMR.B0 = 0;
				PORTE::ODR.B0 = i2c;
				MPC::PE0PFS.PSEL = sel;
				PORTE::PMR.B0 = enable;
			// TXD5: PD7
				PORTD::PMR.B7 = 0;
				PORTD::ODR.B7 = i2c;
				MPC::PD7PFS.PSEL = sel;
				PORTD::PMR.B7 = enable;
			// SCK5: PD2
				if(spi) {
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = enable;
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
			uint8_t sel = enable ? 0b00'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD6: P80
				PORT8::PMR.B0 = 0;
				PORT8::ODR.B0 = i2c;
				MPC::P80PFS.PSEL = sel;
				PORT8::PMR.B0 = enable;
			// TXD6: P81
				PORT8::PMR.B1 = 0;
				PORT8::PMR.B1 = 0;
				MPC::P81PFS.PSEL = sel;
				PORT8::PMR.B1 = enable;
			// SCK6: P82
				if(spi) {
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD5: P95
				PORT9::PMR.B5 = 0;
				PORT9::ODR.B5 = i2c;
				MPC::P95PFS.PSEL = sel;
				PORT9::PMR.B5 = enable;
			// TXD5: PB0
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;
				PORTB::PMR.B0 = enable;
			// SCK5: PA4
				if(spi) {
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD5: PB1
				PORTB::PMR.B1 = 0;
				PORTB::ODR.B1 = i2c;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
			// TXD5: PB2
				PORTB::PMR.B2 = 0;
				PORTB::ODR.B2 = i2c;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B2 = enable;
			// SCK5: PB3
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

		static bool rsci8_de_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b10'1110 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// DE008: P20
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // ok
				PORT2::PMR.B0 = enable;
				break;
			case ORDER::SECOND:
			// DE008: P24
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = enable;
				break;
			case ORDER::THIRD:
			// DE008: P30
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = sel;  // ok
				PORT3::PMR.B0 = enable;
				break;
			case ORDER::FOURTH:
			// DE008: P96
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = sel;  // ok
				PORT9::PMR.B6 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rsci8_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			switch(odr) {
			case ORDER::FIRST:
			// RXD008: P20 ( 69/100)
				PORT2::PMR.B0 = 0;
				PORT2::ODR.B0 = i2c;
				MPC::P20PFS.PSEL = enable ? 0b10'1101 : 0;
				PORT2::PMR.B0 = enable;
			// TXD008: P21 ( 68/100)
				PORT2::PMR.B1 = 0;
				PORT2::ODR.B1 = i2c;
				MPC::P21PFS.PSEL = enable ? 0b10'1100 : 0;
				PORT2::PMR.B1 = enable;
			// SCK008: P11
				if(spi) {
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = enable ? 0b10'1101 : 0;
					PORT1::PMR.B1 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rsci9_de_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b10'1110 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// DE009: P70
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = sel;  // ok
				PORT7::PMR.B0 = enable;
				break;
			case ORDER::SECOND:
			// DE009: PB3
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;  // ok
				PORTB::PMR.B3 = enable;
				break;
			case ORDER::THIRD:
			// DE009: PE3
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = sel;  // ok
				PORTE::PMR.B3 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rsci9_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			switch(odr) {
			case ORDER::FIRST:
			// RXD009: P00
				PORT0::PMR.B0 = 0;
				PORT0::ODR.B0 = i2c;
				MPC::P00PFS.PSEL = enable ? 0b10'1100 : 0;
				PORT0::PMR.B0 = enable;
			// TXD009: P01
				PORT0::PMR.B1 = 0;
				PORT0::ODR.B1 = i2c;
				MPC::P01PFS.PSEL = enable ? 0b10'1100 : 0;
				PORT0::PMR.B1 = enable;
			// SCK009: P11 ( 99/100)
				if(spi) {
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = enable ? 0b10'1100 : 0;
					PORT1::PMR.B1 = enable;
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
			// DE011: PB0
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
				break;
			case ORDER::SECOND:
			// DE011: PD6
				PORTD::PMR.B6 = 0;
				MPC::PD6PFS.PSEL = sel;  // ok
				PORTD::PMR.B6 = enable;
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
			switch(odr) {
			case ORDER::FIRST:
			// RXD011: P93 ( 47/100)
				PORT9::PMR.B3 = 0;
				PORT9::ODR.B3 = i2c;
				MPC::P93PFS.PSEL = enable ? 0b10'1101 : 0;
				PORT9::PMR.B3 = enable;
			// TXD011: P92 ( 48/100)
				PORT9::PMR.B2 = 0;
				PORT9::ODR.B2 = i2c;
				MPC::P92PFS.PSEL = enable ? 0b10'1101 : 0;
				PORT9::PMR.B2 = enable;
			// SCK011: PB4 ( 30/100)
				if(spi) {
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = enable ? 0b10'1101 : 0;
					PORTB::PMR.B4 = enable;
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
			uint8_t sel = enable ? 0b00'1100 : 0; 
			switch(odr) {
			case ORDER::FIRST:
			// RXD12: P00 (  4/100)
				PORT0::PMR.B0 = 0;
				PORT0::ODR.B0 = i2c;
				MPC::P00PFS.PSEL = sel;
				PORT0::PMR.B0 = enable;
			// TXD12: P01 (  7/100)
				PORT0::PMR.B1 = 0;
				PORT0::ODR.B1 = i2c;
				MPC::P01PFS.PSEL = sel;
				PORT0::PMR.B1 = enable;
			// SCK6: P82 ( 96/100)
				if(spi) {
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b00'1101 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RSPCKA: P20 ( 69/100)
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // ok
				PORT2::PMR.B0 = enable;
			// MOSIA:  P21 ( 68/100)
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;  // ok
				PORT2::PMR.B1 = enable;
			// MISOA:  P22 ( 67/100)
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::SECOND:
			// RSPCKA: P24 ( 65/100)
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = enable;
			// MOSIA:  P23 ( 66/100)
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
			// MISOA:  P22 ( 67/100)
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::THIRD:
			// RSPCKA: P27 ( 64/100)
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = sel;  // ok
				PORT2::PMR.B7 = enable;
			// MOSIA:  P23 ( 66/100)
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
			// MISOA:  P22 ( 67/100)
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::FOURTH:
			// RSPCKA: PA4 ( 37/100)
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
			// MOSIA:  PB0 ( 35/100)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
			// MISOA:  PA5 ( 36/100)
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				break;
			case ORDER::FIFTH:
			// RSPCKA: PB3 ( 32/100)
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;  // ok
				PORTB::PMR.B3 = enable;
			// MOSIA:  PB0 ( 35/100)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
			// MISOA:  PA5 ( 36/100)
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = sel;  // ok
				PORTB::PMR.B4 = enable;
				break;
			case ORDER::SIXTH:
			// RSPCKA: PD0 ( 25/100)
				PORTD::PMR.B0 = 0;
				MPC::PD0PFS.PSEL = sel;  // ok
				PORTD::PMR.B0 = enable;
			// MOSIA:  PD2 ( 23/100)
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = sel;  // ok
				PORTD::PMR.B2 = enable;
			// MISOA:  PD1 ( 24/100)
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = sel;  // ok
				PORTD::PMR.B1 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspia0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b00'1110 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RSPCK0: P20 ( 69/100)
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // ok
				PORT2::PMR.B0 = enable;
			// MOSI0:  P21 ( 68/100)
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;  // ok
				PORT2::PMR.B1 = enable;
			// MISO0:  P22 ( 67/100)
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::SECOND:
			// RSPCK0: P24 ( 65/100)
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = enable;
			// MOSI0:  P23 ( 66/100)
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
			// MISO0:  P22 ( 67/100)
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::THIRD:
			// RSPCK0: P27 ( 64/100)
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = sel;  // ok
				PORT2::PMR.B7 = enable;
			// MOSI0:  P23 ( 66/100)
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
			// MISO0:  P22 ( 67/100)
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = enable;
				break;
			case ORDER::FOURTH:
			// RSPCK0: P70 ( 57/100)
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = sel;  // ok
				PORT7::PMR.B0 = enable;
			// MOSI0:  P72 ( 55/100)
				PORT7::PMR.B2 = 0;
				MPC::P72PFS.PSEL = sel;  // ok
				PORT7::PMR.B2 = enable;
			// MISO0:  P71 ( 56/100)
				PORT7::PMR.B1 = 0;
				MPC::P71PFS.PSEL = sel;  // ok
				PORT7::PMR.B1 = enable;
				break;
			case ORDER::FIFTH:
			// RSPCK0: P91 ( 49/100)
				PORT9::PMR.B1 = 0;
				MPC::P91PFS.PSEL = sel;  // ok
				PORT9::PMR.B1 = enable;
			// MOSI0:  P93 ( 47/100)
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = sel;  // ok
				PORT9::PMR.B3 = enable;
			// MISO0:  P92 ( 48/100)
				PORT9::PMR.B2 = 0;
				MPC::P92PFS.PSEL = sel;  // ok
				PORT9::PMR.B2 = enable;
				break;
			case ORDER::SIXTH:
			// RSPCK0: P96 ( 43/100)
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = sel;  // ok
				PORT9::PMR.B6 = enable;
			// MOSI0:  P93 ( 47/100)
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = sel;  // ok
				PORT9::PMR.B3 = enable;
			// MISO0:  P95 ( 45/100)
				PORT9::PMR.B5 = 0;
				MPC::P95PFS.PSEL = sel;  // ok
				PORT9::PMR.B5 = enable;
				break;
			case ORDER::SEVENTH:
			// RSPCK0: PA4 ( 37/100)
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
			// MOSI0:  PB0 ( 35/100)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
			// MISO0:  PA5 ( 36/100)
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
				break;
			case ORDER::EIGHTH:
			// RSPCK0: PB5 ( 28/100)
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;  // ok
				PORTB::PMR.B5 = enable;
			// MOSI0:  PB0 ( 35/100)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
			// MISO0:  PB6 ( 27/100)
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
				break;
			case ORDER::NINTH:
			// RSPCK0: PD0 ( 25/100)
				PORTD::PMR.B0 = 0;
				MPC::PD0PFS.PSEL = sel;  // ok
				PORTD::PMR.B0 = enable;
			// MOSI0:  PD2  ( 23/100)
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = sel;  // ok
				PORTD::PMR.B2 = enable;
			// MISO0:  PD1 ( 24/100)
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = sel;  // ok
				PORTD::PMR.B1 = enable;
				break;
			case ORDER::TENTH:
			// RSPCK0: PD0 ( 25/100)
				PORTD::PMR.B0 = 0;
				MPC::PD0PFS.PSEL = sel;  // ok
				PORTD::PMR.B0 = enable;
			// MOSI0:  PD3 ( 22/100)
				PORTD::PMR.B3 = 0;
				MPC::PD3PFS.PSEL = sel;  // ok
				PORTD::PMR.B3 = enable;
			// MISO0:  PD1 ( 24/100)
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = sel;  // ok
				PORTD::PMR.B1 = enable;
				break;
			default:
				return false;
			}
			return true;
		}


		/// RIIC0 ポート候補（順番は、MPC の解説に準拠）
		static bool riic0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b00'1111 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// SCL0: PB1
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
			// SDA0: PB2
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		/// RIIC0 ポート候補（順番は、MPC の解説に準拠）
		static bool ri3c0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b11'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// SCL0: PB1
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
			// SDA0: PB2
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		/// CANFD ポート候補（順番は、MPC の解説に準拠）
		static bool canfd0_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b01'0000 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// CRX0: P22
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;
				PORT2::PMR.B2 = enable;
			// CTX0: P23
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;
				PORT2::PMR.B3 = enable;
				break;
			case ORDER::SECOND:
			// CRX0: P93
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = sel;
				PORT9::PMR.B3 = enable;
			// CTX0: P92
				PORT9::PMR.B2 = 0;
				MPC::P92PFS.PSEL = sel;
				PORT9::PMR.B2 = enable;
				break;
			case ORDER::THIRD:
			// CRX0: PA1
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = sel;
				PORTA::PMR.B1 = enable;
			// CTX0: PA0
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = sel;
				PORTA::PMR.B0 = enable;
				break;
			case ORDER::FOURTH:
			// CRX0: PB4
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = sel;
				PORTB::PMR.B4 = enable;
			// CTX0: PB3
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;
				PORTB::PMR.B3 = enable;
				break;
			case ORDER::FIFTH:
			// CRX0: PB6
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
			// CTX0: PB5
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = enable;
				break;
			case ORDER::SIXTH:
			// CRX0: PE0
				PORTE::PMR.B0 = 0;
				MPC::PE0PFS.PSEL = sel;
				PORTE::PMR.B0 = enable;
			// CTX0: PD7
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = sel;
				PORTD::PMR.B7 = enable;
				break;
			default:
				return false;
			}
			return true;
		}


		static bool cmtw0_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			switch(odr) {
			case ORDER::FIRST:
				if(opt == OPTIONAL::CMTW_TOC0) {
				// TOC0: PB6
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTB::PMR.B6 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC0) {
				// TIC0: PB5
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTB::PMR.B5 = enable;
				} else if(opt == OPTIONAL::CMTW_TOC1) {
				// TOC1: PB3
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTB::PMR.B3 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC1) {
				// TIC1: PB2
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTB::PMR.B2 = enable;
				} else {
					return false;
				}
				break;
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
				// TOC2: PB1
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTB::PMR.B1 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC0) {
				// TIC2: PB0
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = enable ? 0b01'1101 : 0;
					PORTB::PMR.B0 = enable;
				} else if(opt == OPTIONAL::CMTW_TOC1) {
				// TOC3: P11
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = enable ? 0b01'1101 : 0;
					PORT1::PMR.B1 = enable;
				} else if(opt == OPTIONAL::CMTW_TIC1) {
				// TIC3: P00
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = enable ? 0b01'1101 : 0;
					PORT0::PMR.B0 = enable;
				} else {
					return false;
				}
				break;
			case ORDER::SECOND:
				if(opt == OPTIONAL::CMTW_TIC1) {
				// TIC3: P10
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = enable ? 0b01'1101 : 0;
					PORT1::PMR.B0 = enable;
				} else {
					return false;
				}
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
			case peripheral::RSCI8:
				if(opt == OPTIONAL::RSCI_DE) {
					ret = rsci8_de_(odr, ena);
				}
				break;
			case peripheral::RSCI9:
				if(opt == OPTIONAL::RSCI_DE) {
					ret = rsci9_de_(odr, ena);
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
			if(odr == ORDER::BYPASS) return false;

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
				case peripheral::RSCI8:
					ret = rsci8_(odr, ena, opt);
					break;
				case peripheral::RSCI9:
					ret = rsci9_(odr, ena, opt);
					break;
				case peripheral::RSCI11:
					ret = rsci11_(odr, ena, opt);
					break;
				case peripheral::SCI12:
					ret = sci12_(odr, ena, opt);
					break;
				case peripheral::RSPI0:
					ret = rspi0_(odr, ena);
					break;
				case peripheral::RSPIA0:
					ret = rspia0_(odr, ena);
					break;
				case peripheral::RIIC0:
					ret = riic0_(odr, ena);
					break;
				case peripheral::RI3C0:
					ret = ri3c0_(odr, ena);
					break;
				case peripheral::CANFD0:
					ret = canfd0_(odr, ena);
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

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
