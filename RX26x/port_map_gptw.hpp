#pragma once
//=========================================================================//
/*!	@file
	@brief	RX260/RX261 グループ・ポート・マッピング (GPTW0 - GPTW7)  @n
			（クロック関係は実装中・・・）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX26x/peripheral.hpp"
#include "RX26x/port.hpp"
#include "RX26x/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTW ポート・マッピング
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_gptw : public port_map_order {

		static bool gptw0_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC0A(#):
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P17 (LFQFP100:  29)
				// P22 (LFQFP100:  26)
				// PA0 (LFQFP100:  70)
				// PA1 (LFQFP100:  69)
				// PB7 (LFQFP100:  53)
				// PC5 (LFQFP100:  47)
				// PH0 (LFQFP100:  38)
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // ok
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::SIXTH:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;  // ok
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::SEVENTH:
					PORTH::PMR.B0 = 0;
					MPC::PH0PFS.PSEL = sel;  // ok
					PORTH::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC0B(#):
				// P16 (LFQFP100:  30)
				// P17 (LFQFP100:  29)
				// P23 (LFQFP100:  25)
				// PA1 (LFQFP100:  69)
				// PA6 (LFQFP100:  64)
				// PB0 (LFQFP100:  61)
				// PB6 (LFQFP100:  54)
				// PC4 (LFQFP100:  48)
				// PH1 (LFQFP100:  37)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;  // ok
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::SIXTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::SEVENTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::EIGHTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = ena;
					break;
				case ORDER::NINTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTH::PMR.B1 = 0;
					MPC::PH1PFS.PSEL = sel;  // ok
					PORTH::PMR.B1 = ena;
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
			return ret;
		}

		static bool gptw1_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC1A(#):
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P24 (LFQFP100:  24)
				// P32 (LFQFP100:  18)
				// P55 (LFQFP100:  39)
				// PA0 (LFQFP100:  70)
				// PB3 (LFQFP100:  57)
				// PE2 (LFQFP100:  76)
				// PE4 (LFQFP100:  74)
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;  // ok
					PORT5::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;  // ok
					PORTE::PMR.B2 = ena;
					break;
				case ORDER::SEVENTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;  // ok
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC1B(#):
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P25 (LFQFP100:  23)
				// P33 (LFQFP100:  17)
				// PA3 (LFQFP100:  67)
				// PA4 (LFQFP100:  66)
				// PB1 (LFQFP100:  59)
				// PE1 (LFQFP100:  77)
				// PE5 (LFQFP100:  73)
				// PH2 (LFQFP100:  36)
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // ok
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;  // ok
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::SEVENTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;  // ok
					PORTE::PMR.B5 = ena;
					break;
				case ORDER::EIGHTH:
					PORTH::PMR.B2 = 0;
					MPC::PH2PFS.PSEL = sel;  // ok
					PORTH::PMR.B2 = ena;
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
			return ret;
		}

		static bool gptw2_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC2A(#):
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P21 (LFQFP100:  27)
				// P30 (LFQFP100:  20)
				// P54 (LFQFP100:  40)
				// PB0 (LFQFP100:  61)
				// PC2 (LFQFP100:  50)
				// PD1 (LFQFP100:  85)
				// PE3 (LFQFP100:  75)
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;  // ok
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORT5::PMR.B4 = 0;
					MPC::P54PFS.PSEL = sel;  // ok
					PORT5::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;  // ok
					PORTC::PMR.B2 = ena;
					break;
				case ORDER::SIXTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // ok
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::SEVENTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;  // ok
					PORTE::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC2B(#):
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P20 (LFQFP100:  28)
				// P31 (LFQFP100:  19)
				// P55 (LFQFP100:  39)
				// PA3 (LFQFP100:  67)
				// PB1 (LFQFP100:  59)
				// PC3 (LFQFP100:  49)
				// PD2 (LFQFP100:  84)
				// PE4 (LFQFP100:  74)
				// PH3 (LFQFP100:  35)
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;  // ok
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;  // ok 
					PORT5::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // ok
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;  // ok
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::SEVENTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::EIGHTH:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;  // ok
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::NINTH:
					PORTH::PMR.B3 = 0;
					MPC::PH3PFS.PSEL = sel;  // ok
					PORTH::PMR.B3 = ena;
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
			return ret;
		}

		static bool gptw3_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC3A(#):
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P22 (LFQFP100:  26)
				// P34 (LFQFP100:  16)
				// PB2 (LFQFP100:  58)
				// PB3 (LFQFP100:  57)
				// PC4 (LFQFP100:  48)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;  // ok
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = sel;  // ok
					PORTB::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC3B(#):
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P13 (LFQFP100:  33)
				// P15 (LFQFP100:  31)
				// P23 (LFQFP100:  25)
				// PA1 (LFQFP100:  69)
				// PB3 (LFQFP100:  57)
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;  // ok
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;  // ok
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					if(neg) return false;
					sel = ena ? 0b1'1000 : 0;
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					if(neg) return false;
					sel = ena ? 0b1'1000 : 0;
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = ena;
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
			return ret;
		}

		static bool gptw4_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC4A(#):
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P20 (LFQFP100:  28)
				// PA4 (LFQFP100:  66)
				// PE4 (LFQFP100:  74)
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					if(neg) return false;
					sel = ena ? 0b1'1000 : 0;
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;  // ok
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC4B(#):
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P16 (LFQFP100:  30)
				// P21 (LFQFP100:  27)
				// PA5 (LFQFP100:  65)
				// PB5 (LFQFP100:  55)
				// PE3 (LFQFP100:  75)
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;  // ok
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // ok
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;  // ok
					PORTE::PMR.B3 = ena;
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
			return ret;
		}

		static bool gptw5_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC5A(#):
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P26 (LFQFP100:  22)
				// PA6 (LFQFP100:  64)
				// PB5 (LFQFP100:  55)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;  // ok
					PORT2::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;  // ok
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // ok
					PORTB::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC5B(#):
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P15 (LFQFP100:  31)
				// P27 (LFQFP100:  21)
				// PA7 (LFQFP100:  63)
				// PE5 (LFQFP100:  73)
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;  // ok
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
					PORTA::PMR.B7 = 0;
					MPC::PA7PFS.PSEL = sel;  // ok
					PORTA::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;  // ok
					PORTE::PMR.B5 = ena;
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
			return ret;
		}

		static bool gptw6_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC6A(#):
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P14 (LFQFP100:  32)
				// P17 (LFQFP100:  29)
				// P25 (LFQFP100:  23)
				// PB4 (LFQFP100:  56)
				// PC1 (LFQFP100:  51)
				// PC7 (LFQFP100:  45)
				// PJ1 (LFQFP100:   6)
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // ok
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					if(neg) return false;
					sel = ena ? 0b1'1000 : 0;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = sel;  // ok
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;  // ok
					PORTC::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;  // ok
					PORTC::PMR.B7 = ena;
					break;
				case ORDER::SEVENTH:
					PORTJ::PMR.B1 = 0;
					MPC::PJ1PFS.PSEL = sel;  // ok
					PORTJ::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC6B(#):
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P16 (LFQFP100:  30)
				// P24 (LFQFP100:  24)
				// PB5 (LFQFP100:  55)
				// PC0 (LFQFP100:  52)
				// PC6 (LFQFP100:  46)
				// PJ3 (LFQFP100:   4)
				switch(order) {
				case ORDER::FIRST:
					if(neg) return false;
					sel = ena ? 0b1'1000 : 0;
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					if(neg) return false;
					sel = ena ? 0b1'1000 : 0;
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // ok
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;  // ok
					PORTC::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;  // ok
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::SIXTH:
					PORTJ::PMR.B3 = 0;
					MPC::PJ3PFS.PSEL = sel;  // ok
					PORTJ::PMR.B3 = ena;
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
			return ret;
		}

		static bool gptw7_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC7A(#):
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P13 (LFQFP100:  33)
				// P32 (LFQFP100:  18)
				// PB1 (LFQFP100:  59)
				// PB6 (LFQFP100:  54)
				// PC5 (LFQFP100:  47)
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;  // ok
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					if(neg) return false;
					sel = ena ? 0b1'1000 : 0;
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;  // ok
					PORTC::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC7B(#):
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P14 (LFQFP100:  32)
				// P33 (LFQFP100:  17)
				// PA3 (LFQFP100:  67)
				// PB7 (LFQFP100:  53)
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // ok
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					if(neg) return false;
					sel = ena ? 0b1'1000 : 0;
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // ok
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // ok
					PORTB::PMR.B7 = ena;
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
			return ret;
		}

		static bool trg_a_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTETRGA:
			// P14 (LFQFP100:  32)
			// P24 (LFQFP100:  24)
			// PA4 (LFQFP100:  66)
			// PC2 (LFQFP100:  50)
			// PC6 (LFQFP100:  46)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORT1::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORT2::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTA::PMR.B4 = ena;
				break;
			case ORDER::FOURTH:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTC::PMR.B2 = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTC::PMR.B6 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool trg_b_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTETRGB:
			// P15 (LFQFP100:  31)
			// P25 (LFQFP100:  23)
			// PA3 (LFQFP100:  67)
			// PA6 (LFQFP100:  64)
			// PC3 (LFQFP100:  49)
			// PC7 (LFQFP100:  45)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORT1::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORT2::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORTA::PMR.B3 = ena;
				break;
			case ORDER::FOURTH:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTA::PMR.B6 = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTC::PMR.B3 = ena;
				break;
			case ORDER::SIXTH:
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTC::PMR.B7 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool trg_c_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTETRGC:
			// P16 (LFQFP100:  30)
			// P22 (LFQFP100:  26)
			// PA1 (LFQFP100:  69)
			// PB2 (LFQFP100:  58)
			// PC0 (LFQFP100:  52)
			// PC4 (LFQFP100:  48)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORT1::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORT2::PMR.B2 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORTA::PMR.B1 = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTB::PMR.B2 = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B0 = 0;
				MPC::PC0PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTC::PMR.B0 = ena;
				break;
			case ORDER::SIXTH:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTC::PMR.B4 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool trg_d_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTETRGD:
			// P17 (LFQFP100:  29)
			// P23 (LFQFP100:  25)
			// PA3 (LFQFP100:  67)
			// PB3 (LFQFP100:  57)
			// PC1 (LFQFP100:  51)
			// PC5 (LFQFP100:  47)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORT1::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORT2::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTA::PMR.B3 = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORTB::PMR.B3 = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTC::PMR.B1 = ena;
				break;
			case ORDER::SIXTH:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = ena ? 0b01'1000 : 0;  // ok
				PORTC::PMR.B5 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool ppo_0_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTCPPO0:
			// P14 (LFQFP100:  32)
			// P17 (LFQFP100:  29)
			// PC1 (LFQFP100:  51)
			// PC7 (LFQFP100:  45)
			// PJ1 (LFQFP100:   6)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = ena ? 0b00'0001 : 0;  // ok
				PORT1::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORT1::PMR.B7 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = ena ? 0b00'0001 : 0;  // ok
				PORTC::PMR.B1 = ena;
				break;
			case ORDER::FOURTH:
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = ena ? 0b00'0001 : 0;  // ok
				PORTC::PMR.B7 = ena;
				break;
			case ORDER::FIFTH:
				PORTJ::PMR.B1 = 0;
				MPC::PJ1PFS.PSEL = ena ? 0b00'0001 : 0;  // ok
				PORTJ::PMR.B1 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool clock_u_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTIU:
			// P34 (LFQFP100:  16)
			// PB3 (LFQFP100:  57)
			// PC4 (LFQFP100:  48)
			switch(odr) {
			case ORDER::FIRST:
				PORT3::PMR.B4 = 0;
				MPC::P34PFS.PSEL = ena ? 0b00'0001 : 0;  // ok
				PORT3::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTB::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = ena ? 0b00'0001 : 0;  // ok
				PORTC::PMR.B4 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool clock_v_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTIV:
			// P13 (LFQFP100:  33)
			// P15 (LFQFP100:  31)
			// PA1 (LFQFP100:  69)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B3 = 0;
				MPC::P13PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORT1::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORT1::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTA::PMR.B1 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool clock_w_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTIW:
			// P32 (LFQFP100:  18)
			// PB1 (LFQFP100:  59)
			// PC5 (LFQFP100:  47)
			switch(odr) {
			case ORDER::FIRST:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORT3::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTB::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTC::PMR.B5 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool clock_ulo_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTOULO:
			// P16 (LFQFP100:  30)
			// PA6 (LFQFP100:  64)
			// PC4 (LFQFP100:  48)
			// PH1 (LFQFP100:  37)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORT1::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTA::PMR.B6 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTC::PMR.B4 = ena;
				break;
			case ORDER::FOURTH:
				PORTH::PMR.B1 = 0;
				MPC::PH1PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTH::PMR.B1 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool clock_uup_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTOUUP:
			// P17 (LFQFP100:  29)
			// PA1 (LFQFP100:  69)
			// PC5 (LFQFP100:  47)
			// PH0 (LFQFP100:  38)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = ena ? 0b00'0100 : 0;  //  ok 
				PORT1::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = ena ? 0b00'0100 : 0;  // ok 
				PORTA::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = ena ? 0b00'0010 : 0;  // ok 
				PORTC::PMR.B5 = ena;
				break;
			case ORDER::FOURTH:
				PORTH::PMR.B0 = 0;
				MPC::PH0PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORTH::PMR.B0 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool clock_vlo_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTOVLO:
			// PA3 (LFQFP100:  67)
			// PA4 (LFQFP100:  66)
			// PB1 (LFQFP100:  59)
			// PE1 (LFQFP100:  77)
			switch(odr) {
			case ORDER::FIRST:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = ena ? 0b00'0100 : 0;  // ok
				PORTA::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORTA::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORTB::PMR.B1 = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B1 = 0;
				MPC::PE1PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORTE::PMR.B1 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool clock_vup_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTOVUP:
			// PA0 (LFQFP100:  70)
			// PB3 (LFQFP100:  57)
			// PE2 (LFQFP100:  76)
			// PE4 (LFQFP100:  74)
			switch(odr) {
			case ORDER::FIRST:
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = ena ? 0b00'0010 : 0;  // ok 
				PORTA::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = ena ? 0b00'0100 : 0;  // ok
				PORTB::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B2 = 0;
				MPC::PE2PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORTE::PMR.B2 = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
				PORTE::PMR.B4 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool clock_wlo_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTOWLO:
			// P31 (LFQFP100:  19)
			// PA3 (LFQFP100:  67)
			// PB1 (LFQFP100:  59)
			// PE4 (LFQFP100:  74)
			switch(odr) {
			case ORDER::FIRST:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORT3::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
				PORTA::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = ena ? 0b00'0100 : 0;  // ok
				PORTB::PMR.B1 = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTE::PMR.B4 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool clock_wup_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTOWUP:
			// P30 (LFQFP100:  20)
			// PB0 (LFQFP100:  61)
			// PC2 (LFQFP100:  50)
			// PE3 (LFQFP100:  75)
			switch(odr) {
			case ORDER::FIRST:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORT3::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTB::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTC::PMR.B2 = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = ena ? 0b00'0011 : 0;  // ok
				PORTE::PMR.B3 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPTW[0-7]、チャネル別ポート切り替え
			@param[in]	per		周辺機器タイプ
			@param[in]	ch		チャネル
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		候補を選択する場合
			@param[in]	neg		反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			if(odr == ORDER::BYPASS) {
				return true;
			} else if(odr == ORDER::USER) {
				return false;
			}

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::GPTW0:
				ret = gptw0_(ch, ena, neg, odr);
				break;
			case peripheral::GPTW1:
				ret = gptw1_(ch, ena, neg, odr);
				break;
			case peripheral::GPTW2:
				ret = gptw2_(ch, ena, neg, odr);
				break;
			case peripheral::GPTW3:
				ret = gptw3_(ch, ena, neg, odr);
				break;
			case peripheral::GPTW4:
				ret = gptw4_(ch, ena, neg, odr);
				break;
			case peripheral::GPTW5:
				ret = gptw5_(ch, ena, neg, odr);
				break;
			case peripheral::GPTW6:
				ret = gptw6_(ch, ena, neg, odr);
				break;
			case peripheral::GPTW7:
				ret = gptw7_(ch, ena, neg, odr);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPTW クロック入出力切り替え
			@param[in]	clk	クロック型
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_clock(CHANNEL clk, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(clk) {
			case CHANNEL::U:
				ret = clock_u_(odr, ena);
				break;
			case CHANNEL::V:
				ret = clock_v_(odr, ena);
				break;
			case CHANNEL::W:
				ret = clock_w_(odr, ena);
				break;
			case CHANNEL::ULO:
				ret = clock_ulo_(odr, ena);
				break;
			case CHANNEL::UUP:
				ret = clock_uup_(odr, ena);
				break;
			case CHANNEL::VLO:
				ret = clock_vlo_(odr, ena);
				break;
			case CHANNEL::VUP:
				ret = clock_vup_(odr, ena);
				break;
			case CHANNEL::WLO:
				ret = clock_wlo_(odr, ena);
				break;
			case CHANNEL::WUP:
				ret = clock_wup_(odr, ena);
				break;
			case CHANNEL::TRGA:
				ret = trg_a_(odr, ena);
				break;
			case CHANNEL::TRGB:
				ret = trg_b_(odr, ena);
				break;
			case CHANNEL::TRGC:
				ret = trg_c_(odr, ena);
				break;
			case CHANNEL::TRGD:
				ret = trg_d_(odr, ena);
				break;
			case CHANNEL::PPO0:
				ret = ppo_0_(odr, ena);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
