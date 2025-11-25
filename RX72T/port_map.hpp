#pragma once
//=============================================================================//
/*!	@file
	@brief	RX66T/RX72T グループ・ポート・マッピング @n
			・ポートの選択は「候補」に従うポリシーを採用している。 @n
			・単独で指定する場合や、グループで指定する場合などがある。 @n
			・独自に指定する場合、「BYPASS」を選択する事が出来る。 @n
			・又、「USER」を指定すると、設定された外部関数が呼ばれる。 @n
			・「候補」の順番は、ハードウェアーマニュアル MPC の解説に準拠している。 @n
			※上記ルールに従っていない場合もあるので注意が必要（工事中）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "RX72T/peripheral.hpp"
#include "RX72T/port.hpp"
#include "RX72T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map : public port_map_order {

		static bool sci1_(ORDER odr, bool enable, OPTIONAL opt) noexcept
		{
			uint8_t i2c = 0;
			bool spi = false;
			if(opt == OPTIONAL::SCI_I2C) { i2c = 1; }
			else if(opt == OPTIONAL::SCI_SPI) { spi = true; }
			switch(odr) {
			case ORDER::FIRST:
				{
				// RXD1: P34 (LFQFP100: ---) (LFQFP144:  61)
				// TXD1: P35 (LFQFP100: ---) (LFQFP144:  60)
				// SCK1: P25 (LFQFP100: ---) (LFQFP144:  94)
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORT3::PMR.B4 = 0;
					PORT3::ODR.B4 = i2c;
					MPC::P34PFS.PSEL = sel;
					PORT3::PMR.B4 = enable;
					PORT3::PMR.B5 = 0;
					PORT3::ODR.B5 = i2c;
					MPC::P35PFS.PSEL = sel;
					PORT3::PMR.B5 = enable;
					if(spi) {
						PORT2::PMR.B5 = 0;
						MPC::P25PFS.PSEL = enable ? 0b00'1010 : 0;  // ok
						PORT2::PMR.B5 = enable;
					}
				}
				break;
			case ORDER::SECOND:
				{
				// RXD1: PC3 (LFQFP100: ---) (LFQFP144:  99)
				// TXD1: PC4 (LFQFP100: ---) (LFQFP144:  98)
				// SCK1: P25 (LFQFP100: ---) (LFQFP144:  94)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTC::PMR.B3 = 0;
					PORTC::ODR.B3 = i2c;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = enable;
					PORTC::PMR.B4 = 0;
					PORTC::ODR.B4 = i2c;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = enable;
					if(spi) {
						PORT2::PMR.B5 = 0;
						MPC::P25PFS.PSEL = sel;
						PORT2::PMR.B5 = enable;
					}
				}
				break;
			case ORDER::THIRD:
				{	// Serial BOOT interface
				// RXD1: PD5 (LFQFP100:  20) (LFQFP144:  25)
				// TXD1: PD3 (LFQFP100:  22) (LFQFP144:  27)
				// SCK1: PD4 (LFQFP100:  21) (LFQFP144:  26)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTD::PMR.B5 = 0;
					PORTD::ODR.B5 = i2c;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B5 = enable;
					PORTD::PMR.B3 = 0;
					PORTD::ODR.B3 = i2c;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = enable;
					if(spi) {
						PORTD::PMR.B4 = 0;
						MPC::PD4PFS.PSEL = sel;
						PORTD::PMR.B4 = enable;
					}
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
			switch(odr) {
			case ORDER::FIRST:
				{
				// RXD5: PB6 (LFQFP100:  27) (LFQFP144:  40)
				// TXD5: PB5 (LFQFP100:  28) (LFQFP144:  41)
				// SCK5: PB7 (LFQFP100:  26) (LFQFP144:  39)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
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
				}
				break;
			case ORDER::SECOND:
				{
				// RXD5: PE0 (LFQFP100:  17) (LFQFP144:  22)
				// TXD5: PD7 (LFQFP100:  18) (LFQFP144:  23)
				// SCK5: PD2 (LFQFP100:  23) (LFQFP144:  28)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTE::PMR.B0 = 0;
					PORTE::ODR.B0 = i2c;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = enable;
					PORTD::PMR.B7 = 0;
					PORTD::ODR.B7 = i2c;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = enable;
					if(spi) {
						PORTD::PMR.B2 = 0;
						MPC::PD2PFS.PSEL = sel;
						PORTD::PMR.B2 = enable;
					}
				}
				break;
			case ORDER::THIRD:
				{
				// RXD5: PK0 (LFQFP100: ---) (LFQFP144:  85)
				// TXD5: PK1 (LFQFP100: ---) (LFQFP144:  84)
				// SCK5: PK2 (LFQFP100: ---) (LFQFP144:  83)
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTK::PMR.B0 = 0;
					PORTK::ODR.B0 = i2c;
					MPC::PK0PFS.PSEL = sel;
					PORTK::PMR.B0 = enable;
					PORTK::PMR.B1 = 0;
					PORTK::ODR.B1 = i2c;
					MPC::PK1PFS.PSEL = sel;
					PORTK::PMR.B1 = enable;
					if(spi) {
						PORTK::PMR.B2 = 0;
						MPC::PK2PFS.PSEL = sel;
						PORTK::PMR.B2 = enable;
					}
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
			switch(odr) {
			case ORDER::FIRST:
				{
				// RXD6: P80 (LFQFP100:  98) (LFQFP144: 139)
				// TXD6: P81 (LFQFP100:  97) (LFQFP144: 138)
				// SCK6: P82 (LFQFP100:  96) (LFQFP144: 137)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT8::PMR.B0 = 0;
					PORT8::ODR.B0 = i2c;
					MPC::P80PFS.PSEL = sel;
					PORT8::PMR.B0 = enable;
					PORT8::PMR.B1 = 0;
					PORT8::ODR.B1 = i2c;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = enable;
					if(spi) {
						PORT8::PMR.B2 = 0;
						MPC::P82PFS.PSEL = sel;
						PORT8::PMR.B2 = enable;
					}
				}
				break;
			case ORDER::SECOND:
				{
				// RXD6: PA5 (LFQFP100:  36) (LFQFP144:  54)
				// TXD6: PB0 (LFQFP100:  35) (LFQFP144:  51)
				// SCK6: PA4 (LFQFP100:  37) (LFQFP144:  55)
					uint8_t sel = enable ? 0b00'1011 : 0;
					PORTA::PMR.B5 = 0;
					PORTA::ODR.B5 = i2c;
					MPC::PA5PFS.PSEL = sel;  // ok
					PORTA::PMR.B5 = enable;
					PORTB::PMR.B0 = 0;
					PORTB::ODR.B0 = i2c;
					MPC::PB0PFS.PSEL = enable ? 0b00'1010 : 0;
					PORTB::PMR.B0 = enable;
					if(spi) {
						PORTA::PMR.B4 = 0;
						MPC::PA4PFS.PSEL = sel;  // ok
						PORTA::PMR.B4 = enable;
					}
				}
				break;
			case ORDER::THIRD:
				{
				// RXD6: PB1 (LFQFP100:  34) (LFQFP144:  50)
				// TXD6: PB2 (LFQFP100:  33) (LFQFP144:  49)
				// SCK6: PB3 (LFQFP100:  32) (LFQFP144:  48)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTB::PMR.B1 = 0;
					PORTB::ODR.B1 = i2c;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B2 = 0;
					PORTB::ODR.B2 = i2c;
					MPC::PB2PFS.PSEL = sel;
					PORTB::PMR.B2 = enable;
					if(spi) {
						PORTB::PMR.B3 = 0;
						MPC::PB3PFS.PSEL = sel;
						PORTB::PMR.B3 = enable;
					}
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
			switch(odr) {
			case ORDER::FIRST:
				{
				// RXD8: P22 (LFQFP100:  67) (LFQFP144:  97)
				// TXD8: P21 (LFQFP100:  68) (LFQFP144: 100)
				// SCK8: P20 (LFQFP100:  69) (LFQFP144: 101)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT2::PMR.B2 = 0;
					PORT2::ODR.B2 = i2c;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B1 = 0;
					PORT2::ODR.B1 = i2c;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = enable;
					if(spi) {
						PORT2::PMR.B0 = 0;
						MPC::P20PFS.PSEL = enable ? 0b00'1011 : 0;  // ok
						PORT2::PMR.B0 = enable;
					}
				}
				break;
			case ORDER::SECOND:
				{
				// RXD8: PA5 (LFQFP100:  36) (LFQFP144:  54)
				// TXD8: PA4 (LFQFP100:  37) (LFQFP144:  55)
				// SCK8: PA3 (LFQFP100:  38) (LFQFP144:  56)
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTA::PMR.B5 = 0;
					PORTA::ODR.B5 = i2c;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = enable;
					PORTA::PMR.B4 = 0;
					PORTA::ODR.B4 = i2c;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
					if(spi) {
						PORTA::PMR.B3 = 0;
						MPC::PA3PFS.PSEL = sel;
						PORTA::PMR.B3 = enable;
					}
				}
				break;
			case ORDER::THIRD:
				{
				// RXD8: PC0 (LFQFP100: ---) (LFQFP144:  47)
				// TXD8: PC1 (LFQFP100: ---) (LFQFP144:  46)
				// SCK8: PC2 (LFQFP100: ---) (LFQFP144:  45)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORTC::PMR.B0 = 0;
					PORTC::ODR.B0 = i2c;
					MPC::PC0PFS.PSEL = sel;
					PORTC::PMR.B0 = enable;
					PORTC::PMR.B1 = 0;
					PORTC::ODR.B1 = i2c;
					MPC::PC1PFS.PSEL = sel;
					PORTC::PMR.B1 = enable;
					if(spi) {
						PORTC::PMR.B2 = 0;
						MPC::PC2PFS.PSEL = sel;
						PORTC::PMR.B2 = enable;
					}
				}
				break;
			case ORDER::FOURTH:
				{
				// RXD8: PD1 (LFQFP100:  24) (LFQFP144:  29) 
				// TXD8: PD0 (LFQFP100:  25) (LFQFP144:  30)
				// SCK8: PD2 (LFQFP100:  23) (LFQFP144:  28)
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTD::PMR.B1 = 0;
					PORTD::ODR.B1 = i2c;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = enable;
					PORTD::PMR.B0 = 0;
					PORTD::ODR.B0 = i2c;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = enable;
					if(spi) {
						PORTD::PMR.B2 = 0;
						MPC::PD2PFS.PSEL = sel;
						PORTD::PMR.B2 = enable;
					}
				}
				break;
			case ORDER::FIFTH:
				{
				// RXD8: P22 (LFQFP100:  67) (LFQFP144:  97)
				// TXD8: P23 (LFQFP100:  66) (LFQFP144:  96)
				// SCK8: P24 (LFQFP100:  65) (LFQFP144:  95)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT2::PMR.B2 = 0;
					PORT2::ODR.B2 = i2c;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B3 = 0;
					PORT2::ODR.B3 = i2c;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = enable;
					if(spi) {
						PORT2::PMR.B4 = 0;
						MPC::P24PFS.PSEL = enable ? 0b00'1011 : 0;  // ok
						PORT2::PMR.B4 = enable;
					}
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
			uint8_t sel;
			switch(odr) {
			case ORDER::FIRST:
				{
				// RXD9: P00 (LFQFP100:   4) (LFQFP144:   9)
				// TXD9: P01 (LFQFP100:   7) (LFQFP144:  12)
				// SCK9: PE4 (LFQFP100:   8) (LFQFP144:  13)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT0::PMR.B0 = 0;
					PORT0::ODR.B0 = i2c;
					MPC::P00PFS.PSEL = sel;
					PORT0::PMR.B0 = enable;
					PORT0::PMR.B1 = 0;
					PORT0::ODR.B1 = i2c;
					MPC::P01PFS.PSEL = sel;
					PORT0::PMR.B1 = enable;
					if(spi) {
						PORTE::PMR.B4 = 0;
						MPC::PE4PFS.PSEL = sel;
						PORTE::PMR.B4 = enable;
					}
				}
				break;
			case ORDER::SECOND:
				{
				// RXD9: PA2 (LFQFP100:  39) (LFQFP144:  57)
				// TXD9: PA1 (LFQFP100:  40) (LFQFP144:  58)
				// SCK9: PA0 (LFQFP100:  41) (LFQFP144:  59)
					PORTA::PMR.B2 = 0;
					PORTA::ODR.B2 = i2c;
					MPC::PA2PFS.PSEL = enable ? 0b00'1011 : 0;
					PORTA::PMR.B2 = enable;
					PORTA::PMR.B1 = 0;
					PORTA::ODR.B1 = i2c;
					MPC::PA1PFS.PSEL = enable ? 0b00'1010 : 0;
					PORTA::PMR.B1 = enable;
					if(spi) {
						PORTA::PMR.B0 = 0;
						MPC::PA0PFS.PSEL = enable ? 0b00'1010 : 0;
						PORTA::PMR.B0 = enable;
					}
				}
				break;
			case ORDER::THIRD:
				{
				// RXD9: PG0 (LFQFP100: ---) (LFQFP144:  82)
				// TXD9: PG1 (LFQFP100: ---) (LFQFP144:  81)
				// SCK9: PG2 (LFQFP100: ---) (LFQFP144:  80)
					uint8_t sel = enable ? 0b00'1010 : 0;  // ok
					PORT0::PMR.B0 = 0;
					PORT0::ODR.B0 = i2c;
					MPC::P00PFS.PSEL = sel;
					PORT0::PMR.B0 = enable;
					PORT0::PMR.B1 = 0;
					PORT0::ODR.B1 = i2c;
					MPC::P01PFS.PSEL = sel;
					PORT0::PMR.B1 = enable;
					if(spi) {
						PORTE::PMR.B4 = 0;
						MPC::PE4PFS.PSEL = sel;
						PORTE::PMR.B4 = enable;
					}
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
			uint8_t sel;
			switch(odr) {
			case ORDER::FIRST:
				{
				// RXD11: PA1 (LFQFP100:  40) (LFQFP144:  58)
				// TXD11: PA0 (LFQFP100:  41) (LFQFP144:  59)
				// SCK11: PA2 (LFQFP100:  39) (LFQFP144:  57)
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTA::PMR.B1 = 0;
					PORTA::ODR.B1 = i2c;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = enable;
					PORTA::PMR.B0 = 0;
					PORTA::ODR.B0 = i2c;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = enable;
					if(spi) {
						PORTA::PMR.B2 = 0;
						MPC::PA2PFS.PSEL = enable ? 0b00'1100 : 0;  // ok
						PORTA::PMR.B2 = enable;
					}
				}
				break;
			case ORDER::SECOND:
				{
				// RXD11: PA7 (LFQFP100: ---) (LFQFP144:  52)
				// TXD11: PA6 (LFQFP100: ---) (LFQFP144:  53)
				// SCK11: PA2 (LFQFP100: ---) (LFQFP144:  57)
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTA::PMR.B7 = 0;
					PORTA::ODR.B7 = i2c;
					MPC::PA7PFS.PSEL = sel;
					PORTA::PMR.B7 = enable;
					PORTA::PMR.B6 = 0;
					PORTA::ODR.B6 = i2c;
					MPC::PA6PFS.PSEL = sel;
					PORTA::PMR.B6 = enable;
					if(spi) {
						PORTA::PMR.B2 = 0;
						MPC::PA2PFS.PSEL = enable ? 0b00'1100 : 0;  // ok
						PORTA::PMR.B2 = enable;
					}
				}
				break;
			case ORDER::THIRD:
				{
				// RXD11: PB6 (LFQFP100:  27) (LFQFP144:  40)
				// TXD11: PB5 (LFQFP100:  28) (LFQFP144:  41)
				// SCK11: PB4 (LFQFP100:  30) (LFQFP144:  43)
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTB::PMR.B6 = 0;
					PORTB::ODR.B6 = i2c;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B5 = 0;
					PORTB::ODR.B5 = i2c;
					MPC::PB5PFS.PSEL = sel;
					PORTB::PMR.B5 = enable;
					if(spi) {
						PORTB::PMR.B4 = 0;
						MPC::PB4PFS.PSEL = sel;
						PORTB::PMR.B4 = enable;
					}
				}
				break;
			case ORDER::FOURTH:
				{
				// RXD11: PC6 (LFQFP100: ---) (LFQFP144:  62)
				// TXD11: PC5 (LFQFP100: ---) (LFQFP144:  63)
				// SCK11: PB7 (LFQFP100: ---) (LFQFP144:  39)
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTC::PMR.B6 = 0;
					PORTC::ODR.B6 = i2c;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B5 = 0;
					PORTC::ODR.B5 = i2c;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = enable;
					if(spi) {
						PORTB::PMR.B7 = 0;
						MPC::PB7PFS.PSEL = sel;
						PORTB::PMR.B7 = enable;
					}
				}
				break;
			case ORDER::FIFTH:
				{
				// RXD11: PD5 (LFQFP100:  20) (LFQFP144:  25)
				// TXD11: PD3 (LFQFP100:  22) (LFQFP144:  27)
				// SCK11: PD4 (LFQFP100:  21) (LFQFP144:  26)
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTD::PMR.B5 = 0;
					PORTD::ODR.B5 = i2c;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B5 = enable;
					PORTD::PMR.B3 = 0;
					PORTD::ODR.B3 = i2c;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = enable;
					if(spi) {
						PORTD::PMR.B4 = 0;
						MPC::PD4PFS.PSEL = sel;
						PORTD::PMR.B4 = enable;
					}
				}
				break;
			case ORDER::SIXTH:
				{
				// RXD11: PF1 (LFQFP100: ---) (LFQFP144:  33)
				// TXD11: PF0 (LFQFP100: ---) (LFQFP144:  34)
				// SCK11: PF2 (LFQFP100: ---) (LFQFP144:  32)
					uint8_t sel = enable ? 0b00'1011 : 0;  // ok
					PORTF::PMR.B1 = 0;
					PORTF::ODR.B1 = i2c;
					MPC::PF1PFS.PSEL = sel;
					PORTF::PMR.B1 = enable;
					PORTF::PMR.B0 = 0;
					PORTF::ODR.B0 = i2c;
					MPC::PF0PFS.PSEL = sel;
					PORTF::PMR.B0 = enable;
					if(spi) {
						PORTF::PMR.B2 = 0;
						MPC::PF2PFS.PSEL = sel;
						PORTF::PMR.B2 = enable;
					}
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
			uint8_t sel;
			switch(odr) {
			case ORDER::FIRST:
				{
				// RXD12: P00 (LFQFP100:   4) (LFQFP144:   9)
				// TXD12: P01 (LFQFP100:   7) (LFQFP144:  12)
				// SCK12: P82 (LFQFP100:  96) (LFQFP144: 137)
					uint8_t sel = enable ? 0b00'1100 : 0;  // ok
					PORT0::PMR.B0 = 0;
					PORT0::ODR.B0 = i2c;
					MPC::P00PFS.PSEL = sel;
					PORT0::PMR.B0 = enable;
					PORT0::PMR.B1 = 0;
					PORT0::ODR.B1 = i2c;
					MPC::P01PFS.PSEL = sel;
					PORT0::PMR.B1 = enable;
					if(spi) {
						PORT8::PMR.B2 = 0;
						MPC::P82PFS.PSEL = sel;
						PORT8::PMR.B2 = enable;
					}
				}
				break;
			case ORDER::SECOND:
				{
				// RXD12: P22 (LFQFP100:  67) (LFQFP144:  97)
				// TXD12: P21 (LFQFP100:  68) (LFQFP144: 100)
				// SCK12: P82 (LFQFP100:  96) (LFQFP144: 137)
					uint8_t sel = enable ? 0b00'1100 : 0;  // ok
					PORT2::PMR.B2 = 0;
					PORT2::ODR.B2 = i2c;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B1 = 0;
					PORT2::ODR.B1 = i2c;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = enable;
					if(spi) {
						PORT8::PMR.B2 = 0;
						MPC::P82PFS.PSEL = sel;
						PORT8::PMR.B2 = enable;
					}
				}
				break;
			case ORDER::THIRD:
				{
				// RXD12: P80 (LFQFP100:  98) (LFQFP144: 139)
				// TXD12: P81 (LFQFP100:  97) (LFQFP144: 138)
				// SCK12: P82 (LFQFP100:  96) (LFQFP144: 137)
					uint8_t sel = enable ? 0b00'1100 : 0;  // ok
					PORT8::PMR.B0 = 0;
					PORT8::ODR.B0 = i2c;
					MPC::P80PFS.PSEL = sel;
					PORT8::PMR.B0 = enable;
					PORT8::PMR.B1 = 0;
					PORT8::ODR.B1 = i2c;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = enable;
					if(spi) {
						PORT8::PMR.B2 = 0;
						MPC::P82PFS.PSEL = sel;
						PORT8::PMR.B2 = enable;
					}
				}
				break;
			case ORDER::FOURTH:
				{
				// RXD12: PA7 (LFQFP100: ---) (LFQFP144:  52)
				// TXD12: PA6 (LFQFP100: ---) (LFQFP144:  53)
				// SCK12: P82 (LFQFP100:  96) (LFQFP144: 137)
					uint8_t sel = enable ? 0b00'1100 : 0;  // ok
					PORTA::PMR.B7 = 0;
					PORTA::ODR.B7 = i2c;
					MPC::PA7PFS.PSEL = sel;
					PORTA::PMR.B7 = enable;
					PORTA::PMR.B6 = 0;
					PORTA::ODR.B6 = i2c;
					MPC::PA6PFS.PSEL = sel;
					PORTA::PMR.B6 = enable;
					if(spi) {
						PORT8::PMR.B2 = 0;
						MPC::P82PFS.PSEL = sel;
						PORT8::PMR.B2 = enable;
					}
				}
				break;
			case ORDER::FIFTH:
				{
				// RXD12: PB6 (LFQFP100:  27) (LFQFP144:  40)
				// TXD12: PB5 (LFQFP100:  28) (LFQFP144:  41)
				// SCK12: PB7 (LFQFP100:  26) (LFQFP144:  39)
					uint8_t sel = enable ? 0b00'1100 : 0;  // ok
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
				}
				break;
			case ORDER::SIXTH:
				{
				// RXD12: PC3 (LFQFP100: ---) (LFQFP144:  99)
				// TXD12: PC4 (LFQFP100: ---) (LFQFP144:  98)
				// SCK12: PB7 (LFQFP100: ---) (LFQFP144:  39)
					uint8_t sel = enable ? 0b00'1100 : 0;  // ok
					PORTC::PMR.B3 = 0;
					PORTC::ODR.B3 = i2c;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = enable;
					PORTC::PMR.B4 = 0;
					PORTC::ODR.B4 = i2c;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = enable;
					if(spi) {
						PORTB::PMR.B7 = 0;
						MPC::PB7PFS.PSEL = sel;
						PORTB::PMR.B7 = enable;
					}
				}
				break;
			default:
				return false;
			}
			return true;
		}


		static bool riic0_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b00'1111 : 0;
			switch(opt) {
			case ORDER::FIRST:
			// SCL0: PB1 (LFQFP100:  34) (LFQFP144:  50)
			// SDA0: PB2 (LFQFP100:  33) (LFQFP144:  49)
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;
				PORTB::PMR.B1 = enable;
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;
				PORTB::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}


		static bool can0_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b01'0000 : 0;
			switch(opt) {
			case ORDER::FIRST:
			// CRX0: P22 (LFQFP100:  67) (LFQFP144:  97)
			// CTX0: P23 (LFQFP100:  66) (LFQFP144:  96)
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;
				PORT2::PMR.B2 = enable;
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;
				PORT2::PMR.B3 = enable;
				break;
			case ORDER::SECOND:
			// CRX0: PA1 (LFQFP100:  40) (LFQFP144:  58)
			// CTX0: PA0 (LFQFP100:  41) (LFQFP144:  59)
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = sel;
				PORTA::PMR.B0 = enable;
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = sel;
				PORTA::PMR.B1 = enable;
				break;
			case ORDER::THIRD:
			// CRX0: PA7 (LFQFP100: ---) (LFQFP144:  52)
			// CTX0: PA6 (LFQFP100: ---) (LFQFP144:  53)
				PORTA::PMR.B7 = 0;
				MPC::PA7PFS.PSEL = sel;
				PORTA::PMR.B7 = enable;
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;
				PORTA::PMR.B6 = enable;
				break;
			case ORDER::FOURTH:
			// CRX0: PB6 (LFQFP100:  27) (LFQFP144:  40)
			// CTX0: PB5 (LFQFP100:  28) (LFQFP144:  41)
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;
				PORTB::PMR.B6 = enable;
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = sel;
				PORTB::PMR.B5 = enable;
				break;
			case ORDER::FIFTH:
			// CRX0: PC6 (LFQFP100: ---) (LFQFP144:  62)
			// CTX0: PC5 (LFQFP100: ---) (LFQFP144:  63)
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;
				PORTC::PMR.B6 = enable;
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;
				PORTC::PMR.B5 = enable;
				break;
			case ORDER::SIXTH:
			// CRX0: PE0 (LFQFP100:  17) (LFQFP144:  22)
			// CTX0: PD7 (LFQFP100:  18) (LFQFP144:  23)
				PORTE::PMR.B0 = 0;
				MPC::PE0PFS.PSEL = sel;
				PORTE::PMR.B0 = enable;
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = sel;
				PORTD::PMR.B7 = enable;
				break;
			case ORDER::SEVENTH:
			// CRX0: PF3 (LFQFP100: ---) (LFQFP144:  31)
			// CTX0: PF2 (LFQFP100: ---) (LFQFP144:  32)
				PORTF::PMR.B3 = 0;
				MPC::PF3PFS.PSEL = sel;
				PORTF::PMR.B3 = enable;
				PORTF::PMR.B2 = 0;
				MPC::PF3PFS.PSEL = sel;
				PORTF::PMR.B2 = enable;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool rspi0_(ORDER opt, bool enable)
		{
			uint8_t sel = enable ? 0b00'1101 : 0;
			switch(opt) {

			case ORDER::FIRST:
			// RSPCKA: P20 (LFQFP100:  69) (LFQFP144: 101)
			// MOSIA:  P21 (LFQFP100:  68) (LFQFP144: 100)
			// MISOA:  P22 (LFQFP100:  67) (LFQFP144:  97)
				{
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = enable;
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = enable;				
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
				}
				break;
			case ORDER::SECOND:
			// RSPCKA: P24 (LFQFP100:  65) (LFQFP144:  95)
			// MOSIA:  P23 (LFQFP100:  66) (LFQFP144:  96)
			// MISOA:  P22 (LFQFP100:  67) (LFQFP144:  97)
				{
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = enable;
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = enable;
				}
				break;
			case ORDER::THIRD:
			// RSPCKA: PA4 (LFQFP100:  37) (LFQFP144:  55)
			// MOSIA:  PB0 (LFQFP100:  35) (LFQFP144:  51)
			// MISOA:  PA5 (LFQFP100:  36) (LFQFP144:  54)
				{
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = enable;
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = enable;
				}
				break;
			case ORDER::FOURTH:
			// RSPCKA: PB3 (LFQFP100:  32) (LFQFP144:  48)
			// MOSIA:  PB0 (LFQFP100:  35) (LFQFP144:  51)
			// MISOA:  PA5 (LFQFP100:  36) (LFQFP144:  54)
				{
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;
					PORTB::PMR.B3 = enable;
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;
					PORTB::PMR.B0 = enable;
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = enable;
				}
				break;
			case ORDER::FIFTH:
			// RSPCKA: PD0 (LFQFP100:  25) (LFQFP144:  30)
			// MOSIA:  PD2 (LFQFP100:  23) (LFQFP144:  28)
			// MISOA:  PD1 (LFQFP100:  24) (LFQFP144:  29)
				{
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = enable;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = enable;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = enable;
				}
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
				// SSLA0: P30 (LFQFP100:  63) (LFQFP144:  91)
				// SSLA0: PA3 (LFQFP100:  38) (LFQFP144:  56)
				// SSLA0: PD6 (LFQFP100:  19) (LFQFP144:  24)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;
					PORTA::PMR.B3 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL1:
				// SSLA1: P31 (LFQFP100:  61) (LFQFP144:  89)
				// SSLA1: PA2 (LFQFP100:  39) (LFQFP144:  57)
				// SSLA1: PD7 (LFQFP100:  18) (LFQFP144:  23)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;
					PORT3::PMR.B1 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL2:
				// SSLA2: P32 (LFQFP100:  59) (LFQFP144:  87)
				// SSLA2: PA1 (LFQFP100:  40) (LFQFP144:  58)
				// SSLA2: PE0 (LFQFP100:  17) (LFQFP144:  22)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = enable;
				} else {
					ret = false;
				}
				break;
			case RSPI::SSL3:
				// SSLA3: P33 (LFQFP100:  58) (LFQFP144:  86)
				// SSLA3: PA0 (LFQFP100:  41) (LFQFP144:  59)
				// SSLA3: PE1 (LFQFP100:  16) (LFQFP144:  21)
				if(odr == ORDER::FIRST) {
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = enable;
				} else if(odr == ORDER::SECOND) {
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = enable;
				} else if(odr == ORDER::THIRD) {
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = enable;
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
			@brief  USB ポート専用切り替え
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
				// PC0 (LFQFP100: ---) (LFQFP144:  47)
				// PD2 (LFQFP100:  23) (LFQFP144:  28)
				case ORDER::FIRST:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTC::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTD::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::EXICEN:
				// PA0 (LFQFP100:  41) (LFQFP144:  59)
				// PC1 (LFQFP100: ---) (LFQFP144:  46)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTC::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::VBUSEN:
				// PA0 (LFQFP100:  41) (LFQFP144:  59)
				// PC1 (LFQFP100: ---) (LFQFP144:  46)
				// PB5 (LFQFP100:  28) (LFQFP144:  41)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b01'0010 : 0;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = ena ? 0b01'0010 : 0;  // ok
					PORTC::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTB::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURA:
				// PA1 (LFQFP100:  40) (LFQFP144:  58)
				// PB6 (LFQFP100:  27) (LFQFP144:  40)
				// PC2 (LFQFP100: ---) (LFQFP144:  45)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b01'0010 : 0;  // ok
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = ena ? 0b01'0010 : 0;  // ok
					PORTC::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::OVRCURB:
				// P34 (LFQFP100: ---) (LFQFP144:  61)
				// PB4 (LFQFP100:  30) (LFQFP144:  43)
				// PB7 (LFQFP100: ---) (LFQFP144:  39)
				// PE0 (LFQFP100:  17) (LFQFP144:  22)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTE::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case USB_PORT::ID:
				// PA1 (LFQFP100:  40) (LFQFP144:  58)
				// PC2 (LFQFP100: ---) (LFQFP144:  45)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = ena ? 0b01'0001 : 0;  // ok
					PORTC::PMR.B2 = ena;
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
				case peripheral::SCI8:
					ret = sci8_(odr, ena, opt);
					break;
				case peripheral::SCI9:
					ret = sci9_(odr, ena, opt);
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
				case peripheral::CAN0:
					ret = can0_(odr, ena);
					break;
				case peripheral::RSPI0:
					ret = rspi0_(odr, ena);
					break;
				case peripheral::USB0:
					if(odr == ORDER::FIRST) {  // RX72N hira_kuni_board
						ret = turn_usb(USB_PORT::VBUSEN,  ena, ORDER::THIRD);  // PB5
						if(ret) {
							ret = turn_usb(USB_PORT::OVRCURB, ena, ORDER::SECOND);  // PB6
						}
					}
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
