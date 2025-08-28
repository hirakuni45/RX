#pragma once
//=============================================================================//
/*!	@file
	@brief	RX260/RX261 グループ・ポート・マッピング @n
			・ポートの選択は「候補」に従うポリシーを採用している。 @n
			・単独で指定する場合や、グループで指定する場合などがある。 @n
			・独自に指定する場合、「BYPASS」を選択する事が出来る。 @n
			・「候補」の順番は、ハードウェアーマニュアル MPC の解説に準拠している。 @n
			※上記ルールに従っていない場合もあるので注意が必要（工事中）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "RX26x/peripheral.hpp"
#include "RX26x/port.hpp"
#include "RX26x/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sci1_(ORDER odr, bool enable, OPTIONAL opt)
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD1: P15 (LFQFP100:  31)
				PORT1::PMR.B5 = 0;
				PORT1::ODR.B5 = i2c;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = enable;
			// TXD1: P16 (LFQFP100:  30)
				PORT1::PMR.B6 = 0;
				PORT1::ODR.B6 = i2c;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
			// SCK1: P17 (LFQFP100:  29)
				if(spi) {
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = enable;
				}
				break;
			case ORDER::SECOND:  // Serial BOOT
			// RXD1: P30 (LFQFP100:  20)
				PORT3::PMR.B0 = 0;
				PORT3::ODR.B0 = i2c;
				MPC::P30PFS.PSEL = sel;  // ok
				PORT3::PMR.B0 = enable;
			// TXD1: P26 (LFQFP100:  22)
				PORT2::PMR.B6 = 0;
				PORT2::ODR.B6 = i2c;
				MPC::P26PFS.PSEL = sel;  // ok
				PORT2::PMR.B6 = enable;
			// SCK1: P27 (LFQFP100:  21)
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

		static bool sci5_(ORDER odr, bool enable, OPTIONAL opt)
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD5: PA2 (LFQFP100:  68)
				PORTA::PMR.B2 = 0;
				PORTA::ODR.B2 = i2c;
				MPC::PA2PFS.PSEL = sel;  // ok
				PORTA::PMR.B2 = enable;
			// TXD5: PA4 (LFQFP100:  66)
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
			// SCK5: PA1 (LFQFP100:  69)
				if(spi) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD5: PA3 (LFQFP100:  67)
				PORTA::PMR.B3 = 0;
				PORTA::ODR.B3 = i2c;
				MPC::PA3PFS.PSEL = sel;  // ok
				PORTA::PMR.B3 = enable;
			// TXD5: PA4 (LFQFP100:  66)
				PORTA::PMR.B4 = 0;
				PORTA::ODR.B4 = i2c;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = enable;
			// SCK5: PA1 (LFQFP100:  69)
				if(spi) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD5: PC2 (LFQFP100:  50)
				PORTC::PMR.B2 = 0;
				PORTC::ODR.B2 = i2c;
				MPC::PC2PFS.PSEL = sel;  // ok
				PORTC::PMR.B2 = enable;
			// TXD5: PC3 (LFQFP100:  49)
				PORTC::PMR.B3 = 0;
				PORTC::ODR.B3 = i2c;
				MPC::PC3PFS.PSEL = sel;  // ok
				PORTC::PMR.B3 = enable;
			// SCK5: PC1 (LFQFP100:  51)
				if(spi) {
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;  // ok
					PORTC::PMR.B1 = enable;
				}
				break;
			case ORDER::FOURTH:
			// RXD5: PC2 (LFQFP100:  50)
				PORTC::PMR.B2 = 0;
				PORTC::ODR.B2 = i2c;
				MPC::PC2PFS.PSEL = sel;  // ok
				PORTC::PMR.B2 = enable;
			// TXD5: PC3 (LFQFP100:  49)
				PORTC::PMR.B3 = 0;
				PORTC::ODR.B3 = i2c;
				MPC::PC3PFS.PSEL = sel;  // ok
				PORTC::PMR.B3 = enable;
			// SCK5: PC4 (LFQFP100:  48)
				if(spi) {
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool sci6_(ORDER odr, bool enable, OPTIONAL opt)
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1011 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD6: P33 (LFQFP100:  17)
				PORT3::PMR.B3 = 0;
				PORT3::ODR.B3 = i2c;
				MPC::P33PFS.PSEL = sel;  // ok
				PORT3::PMR.B3 = enable;
			// TXD6: P32 (LFQFP100:  18)
				PORT3::PMR.B2 = 0;
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = sel;  // ok
				PORT3::PMR.B2 = enable;
			// SCK6: P34 (LFQFP100:  16)
				if(spi) {
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;  // ok
					PORT3::PMR.B4 = enable;
				}
				break;
			case ORDER::SECOND:
			// RXD5: PB0 (LFQFP100:  61)
				PORTB::PMR.B0 = 0;
				PORTB::ODR.B0 = i2c;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
			// TXD5: PB1 (LFQFP100:  59)
				PORTB::PMR.B1 = 0;
				PORTB::ODR.B1 = i2c;
				MPC::PB1PFS.PSEL = sel;  // ok
				PORTB::PMR.B1 = enable;
			// SCK5: PB3 (LFQFP100:  57)
				if(spi) {
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // ok
					PORTA::PMR.B3 = enable;
				}
				break;
			case ORDER::THIRD:
			// RXD5: PD1 (LFQFP100:  85)
				PORTD::PMR.B1 = 0;
				PORTD::ODR.B1 = i2c;
				MPC::PD1PFS.PSEL = sel;  // ok
				PORTD::PMR.B1 = enable;
			// TXD5: PD0 (LFQFP100:  86)
				PORTD::PMR.B0 = 0;
				PORTD::ODR.B0 = i2c;
				MPC::PD0PFS.PSEL = sel;  // ok
				PORTD::PMR.B0 = enable;
			// SCK5: PD2 (LFQFP100:  84)
				if(spi) {
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = enable;
				}
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rsci0_de_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1100 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// DE000: P23 (LFQFP100:  25)
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rsci0_(ORDER odr, bool enable, OPTIONAL opt)
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD000: P21 (LFQFP100:  27)
				PORT2::PMR.B1 = 0;
				PORT2::ODR.B1 = i2c;
				MPC::P21PFS.PSEL = sel;  // ok
				PORT2::PMR.B1 = enable;
			// TXD000: P20 (LFQFP100:  28)
				PORT2::PMR.B0 = 0;
				PORT2::ODR.B0 = i2c;
				MPC::P20PFS.PSEL = sel;  // ok
				PORT2::PMR.B0 = enable;
			// SCK000: P22 (LFQFP100:  26)
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

		static bool rsci8_de_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1100 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// DE008: PC4 (LFQFP100:  48)
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = sel;  // ok
				PORTC::PMR.B4 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rsci8_(ORDER odr, bool enable, OPTIONAL opt)
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD008: PC6 (LFQFP100:  46)
				PORTC::PMR.B6 = 0;
				PORTC::ODR.B6 = i2c;
				MPC::PC6PFS.PSEL = sel;  // ok
				PORTC::PMR.B6 = enable;
			// TXD008: PC7 (LFQFP100:  45)
				PORTC::PMR.B7 = 0;
				PORTC::ODR.B7 = i2c;
				MPC::PC7PFS.PSEL = sel;  // ok
				PORTC::PMR.B7 = enable;
			// SCK008: PC5 (LFQFP100:  47)
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

		static bool rsci9_de_(ORDER odr, bool enable) noexcept
		{
			uint8_t sel = enable ? 0b0'1100 : 0;
			switch(odr) {
			case ORDER::FIRST: 
			// DE009: PB4 (LFQFP100:  56)
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = sel;  // ok
				PORTB::PMR.B4 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rsci9_(ORDER odr, bool enable, OPTIONAL opt)
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1010 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// RXD009: PB6 (LFQFP100:  54)
				PORTB::PMR.B6 = 0;
				PORTB::ODR.B6 = i2c;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = enable;
			// TXD009: PB7 (LFQFP100:  53)
				PORTB::PMR.B7 = 0;
				PORTB::ODR.B7 = i2c;
				MPC::PB7PFS.PSEL = sel;  // ok
				PORTB::PMR.B7 = enable;
			// SCK009: PB5 (LFQFP100:  55)
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

		static bool sci12_(ORDER odr, bool enable, OPTIONAL opt)
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			uint8_t sel = enable ? 0b0'1100 : 0; 
			switch(odr) {
			case ORDER::FIRST:
			// RXD12: PE2 (LFQFP100:  76)
				PORTE::PMR.B2 = 0;
				PORTE::ODR.B2 = i2c;
				MPC::PE2PFS.PSEL = sel;  // ok
				PORTE::PMR.B2 = enable;
			// TXD12: PE1 (LFQFP100:  77)
				PORTE::PMR.B1 = 0;
				PORTE::ODR.B1 = i2c;
				MPC::PE1PFS.PSEL = sel;  // ok
				PORTE::PMR.B1 = enable;
			// SCK6: PE0 (LFQFP100:  78)
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

		static bool riic0_(ORDER odr, bool enable)
		{
			uint8_t sel = enable ? 0b0'1111 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// SCL0: P12 (LFQFP100:  34)
				PORT1::PMR.B2 = 0;
				MPC::P12PFS.PSEL = sel;  // ok
				PORT1::PMR.B2 = enable;
			// SDA0: P13 (LFQFP100:  33)
				PORT1::PMR.B3 = 0;
				MPC::P13PFS.PSEL = sel;  // ok
				PORT1::PMR.B3 = enable;
				break;
			case ORDER::SECOND:
			// SCL0: P16 (LFQFP100:  30)
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
			// SDA0: P17 (LFQFP100:  29)
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
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
			// RSPCKA: PA5 (LFQFP100:  65)
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
			// MOSIA:  P16 (LFQFP100:  31)
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
			// MISOA:  P17 (LFQFP100:  29)
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				break;
			case ORDER::SECOND:
			// RSPCKA: PA5 (LFQFP100:  65)
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = sel;  // ok
				PORTA::PMR.B5 = enable;
			// MOSIA:  PA6 (LFQFP100:  64)
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;  // ok
				PORTA::PMR.B6 = enable;
			// MISOA:  PA7 (LFQFP100:  63)
				PORTA::PMR.B7 = 0;
				MPC::PA7PFS.PSEL = sel;  // ok
				PORTA::PMR.B7 = enable;
				break;
			case ORDER::THIRD:
			// RSPCKA: PB0 (LFQFP100:  61)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
			// MOSIA:  P16 (LFQFP100:  30)
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = sel;  // ok
				PORT1::PMR.B6 = enable;
			// MISOA:  P17 (LFQFP100:  29)
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = sel;  // ok
				PORT1::PMR.B7 = enable;
				break;
			case ORDER::FOURTH:
			// RSPCKA: PB0 (LFQFP100:  61)
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = enable;
			// MOSIA:  PA6 (LFQFP100:  64)
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;  // ok
				PORTA::PMR.B6 = enable;
			// MISOA:  PA7 (LFQFP100:  63)
				PORTA::PMR.B7 = 0;
				MPC::PA7PFS.PSEL = sel;  // ok
				PORTA::PMR.B7 = enable;
				break;
			case ORDER::FIFTH:
			// RSPCKA: PC5 (LFQFP100:  47)
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;  // ok
				PORTC::PMR.B5 = enable;
			// MOSIA:  PC6 (LFQFP100:  46)
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;  // ok
				PORTC::PMR.B6 = enable;
			// MISOA:  PC7 (LFQFP100:  45)
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
			uint8_t sel = enable ? 0b00'1101 : 0;  // ok
			switch(ssl) {
			case RSPI::SSL0:
				// SSLA0: PA4 (LFQFP100:  66)
				// SSLA0: PC4 (LFQFP100:  48)
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
				// SSLA1: PA0 (LFQFP100:  70)
				// SSLA1: PC0 (LFQFP100:  52)
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
				// SSLA2: PA1 (LFQFP100:  69)
				// SSLA2: PC1 (LFQFP100:  51)
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
				// SSLA3: PA2 (LFQFP100:  68)
				// SSLA3: PC2 (LFQFP100:  50)
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

		static bool lpt_(ORDER odr, bool enable)
		{
			uint8_t sel = enable ? 0b1'1011 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// LPTO: P26 (LFQFP100:  22)
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = sel;  // ok
				PORT2::PMR.B6 = enable;
				break;
			case ORDER::SECOND:
			// LPTO: PB3 (LFQFP100:  57)
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = sel;  // ok
				PORTB::PMR.B3 = enable;
				break;
			case ORDER::THIRD:
			// LPTO: PC7 (LFQFP100:  45)
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = sel;  // ok
				PORTC::PMR.B7 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool canfd0_(ORDER odr, bool enable)
		{
			uint8_t sel = enable ? 0b1'0000 : 0;
			switch(odr) {
			case ORDER::FIRST:
			// CTX0: P14 (LFQFP100:  32)
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = sel;  // ok
				PORT1::PMR.B4 = enable;
			// CRX0: P15 (LFQFP100:  31)
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = enable;
				break;
			case ORDER::SECOND:
			// CTX0: P32 (LFQFP100:  18)
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = sel;  // ok
				PORT3::PMR.B2 = enable;
			// CRX0: P33 (LFQFP100:  17)
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = sel;  // ok
				PORT3::PMR.B3 = enable;
				break;
			case ORDER::THIRD:
			// CTX0: P54 (LFQFP100:  40)
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = sel;  // ok
				PORT5::PMR.B4 = enable;
			// CRX0: P55 (LFQFP100:  39)
				PORT5::PMR.B5 = 0;
				MPC::P55PFS.PSEL = sel;  // ok
				PORT5::PMR.B5 = enable;
				break;
			case ORDER::FOURTH:
			// CTX0: PD1 (LFQFP100:  85)
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = sel;  // ok
				PORTD::PMR.B1 = enable;
			// CRX0: PD2 (LFQFP100:  84)
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = sel;  // ok
				PORTD::PMR.B2 = enable;
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
			case peripheral::RSCI0:
				if(opt == OPTIONAL::RSCI_DE) {
					ret = rsci0_de_(odr, ena);
				}
				break;
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
				case peripheral::RSCI0:
					ret = rsci0_(odr, ena, opt);
					break;
				case peripheral::RSCI8:
					ret = rsci8_(odr, ena, opt);
					break;
				case peripheral::RSCI9:
					ret = rsci9_(odr, ena, opt);
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
				case peripheral::LPT:
					ret = lpt_(odr, ena);
					break;
				case peripheral::CANFD0:
					ret = canfd0_(odr, ena);
					break;
//				case peripheral::USB0:
//					ret = usb0_(odr, ena);
//					break;
				default:
					break;
				}
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  USB ポート専用切り替え
			@param[in]	sel		USB ポート選択
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		ポート・マップ・オプション（ポート候補）
			@return 無効な場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn_usb(USB_PORT sel, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return false;

			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
#if 0
			switch(sel) {
			case USB_PORT::VBUS:
				// P16 o
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b010001 : 0;
					PORT1::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::EXICEN:
				// P21 o
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = ena ? 0b010011 : 0;
					PORT2::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::VBUSEN:
				// P16 o
				// P24 o
				// P32 o
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b010010 : 0;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = ena ? 0b010011 : 0;
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = ena ? 0b010011 : 0;
					PORT3::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURA:
				// P14 o
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = ena ? 0b010010 : 0;
					PORT1::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURB:
				// P16 o
				// P22 o
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b010011 : 0;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = ena ? 0b010011 : 0;
					PORT2::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::ID:
				// P20 o
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = ena ? 0b010011 : 0;
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
#endif
			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
