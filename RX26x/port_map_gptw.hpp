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
			case CHANNEL::A:  // GTIOC0A / GTIOC0A#:
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P17
				// P22
				// PA0
				// PA1
				// PB7
				// PC5
				// PH0
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
			case CHANNEL::B:  // GTIOC0B / GTIOC0B#:
				// P16
				// P17
				// P23
				// PA1
				// PA6
				// PB0
				// PB6
				// PC4
				// PH1
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
			case CHANNEL::A:  // GTIOC1A / GTIOC1A#:
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P24
				// P32
				// P55
				// PA0
				// PB3
				// PE2
				// PE4
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
			case CHANNEL::B:  // GTIOC1B / GTIOC1B#:
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P25
				// P33
				// PA3
				// PA4
				// PB1
				// PE1
				// PE5
				// PH2
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
			case CHANNEL::A:  // GTIOC2A / GTIOC2A#:
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P21
				// P30
				// P54
				// PB0
				// PC2
				// PD1
				// PE3
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
			case CHANNEL::B:  // GTIOC2B / GTIOC2B#:
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P20
				// P31
				// P55
				// PA3
				// PB1
				// PC3
				// PD2
				// PE4
				// PH3
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
			case CHANNEL::A:  // GTIOC3A / GTIOC3A#:
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P22
				// P34
				// PB2
				// PB3
				// PC4
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
			case CHANNEL::B:  // GTIOC3B / GTIOC3B#:
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P13
				// P15
				// P23
				// PA1
				// PB3
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
			case CHANNEL::A:  // GTIOC4A / GTIOC4A#:
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P20
				// PA4
				// PE4
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
			case CHANNEL::B:  // GTIOC4B / GTIOC4B#:
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P16
				// P21
				// PA5
				// PB5
				// PE3
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
			case CHANNEL::A:  // GTIOC5A / GTIOC5A#:
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P26
				// PA6
				// PB5
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
			case CHANNEL::B:  // GTIOC5B / GTIOC5B#:
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P15
				// P27
				// PA7
				// PE5
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
			case CHANNEL::A:  // GTIOC6A / GTIOC6A#:
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P14
				// P17
				// P25
				// PB4
				// PC1
				// PC7
				// PJ1
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
			case CHANNEL::B:  // GTIOC6B / GTIOC6B#:
				sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
				// P16
				// P24
				// PB5
				// PC0
				// PC6
				// PJ3
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
			case CHANNEL::A:  // GTIOC7A / GTIOC7A#:
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P13
				// P32
				// PB1
				// PB6
				// PC5
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
			case CHANNEL::B:  // GTIOC7B / GTIOC7B#:
				sel = ena ? (neg ? 0b1'0111 : 0b1'0101) : 0;
				// P14
				// P33
				// PA3
				// PB7
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
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(clk) {
			case CHANNEL::TRGA:  // GTETRGA
				// P14
				// P24
				// PA4
				// PC2
				// PC6
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
				break;
			case CHANNEL::TRGB:  // GTETRGB
				// P15
				// P25
				// PA3
				// PA6
				// PC3
				// PC7
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
				break;
			case CHANNEL::TRGC:  // GTETRGC
				// P16
				// P22
				// PA1
				// PB2
				// PC0
				// PC4
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
				break;
			case CHANNEL::TRGD:  // GTETRGD
				// P17
				// P23
				// PA3
				// PB3
				// PC1
				// PC5
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
				break;
			case CHANNEL::PPO0:  // GTCPPO0
				// P14
				// P17
				// PC1
				// PC7
				// PJ1
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
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
