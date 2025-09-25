#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66T/RX72T グループ・ポート・マッピング (GPTW0 - GPTW9) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX72T/peripheral.hpp"
#include "RX72T/port.hpp"
#include "RX72T/mpc.hpp"
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
			case CHANNEL::A:  // GTIOC0A:
			// P12 (LFQFP100: ---) (LFQFP144:   3) 
			// P71 (LFQFP100:  56) (LFQFP144:  78)
			// PD2 (LFQFP100:  23) (LFQFP144:  28)
			// PD7 (LFQFP100:  18) (LFQFP144:  23)
			// PG1 (LFQFP100: ---) (LFQFP144:  81)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;
					PORT7::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTG::PMR.B1 = 0;
					MPC::PG1PFS.PSEL = sel;
					PORTG::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC0B:
			// P15 (LFQFP100: ---) (LFQFP144: 144)
			// P74 (LFQFP100:  53) (LFQFP144:  75)
			// PD1 (LFQFP100:  24) (LFQFP144:  29)
			// PD6 (LFQFP100:  19) (LFQFP144:  24)
			// PG2 (LFQFP100: ---) (LFQFP144:  80)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTG::PMR.B2 = 0;
					MPC::PG2PFS.PSEL = sel;
					PORTG::PMR.B2 = ena;
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
			// GTIOC1A:
			// P13 (LFQFP100: ---) (LFQFP144:   2)
			// P72 (LFQFP100:  55) (LFQFP144:  77)
			// PD0 (LFQFP100:  25) (LFQFP144:  30) 
			// PD5 (LFQFP100:  20) (LFQFP144:  25)
			// PK2 (LFQFP100: ---) (LFQFP144:  83)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTK::PMR.B2 = 0;
					MPC::PK2PFS.PSEL = sel;
					PORTK::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			// GTIOC1B:
			// P16 (LFQFP100: ---) (LFQFP144: 143)
			// P75 (LFQFP100:  52) (LFQFP144:  74)
			// PB7 (LFQFP100: ---) (LFQFP144:  39)
			// PD4 (LFQFP100:  21) (LFQFP144:  26)
			// PG0 (LFQFP100: ---) (LFQFP144:  82)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTG::PMR.B0 = 0;
					MPC::PG0PFS.PSEL = sel;
					PORTG::PMR.B0 = ena;
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
			// GTIOC2A:
			// P14 (LFQFP100: ---) (LFQFP144:   1)
			// P73 (LFQFP100:  54) (LFQFP144:  76)
			// PB6 (LFQFP100:  27) (LFQFP144:  40)
			// PD3 (LFQFP100:  22) (LFQFP144:  27)
			// PK0 (LFQFP100: ---) (LFQFP144:  85)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTK::PMR.B0 = 0;
					MPC::PK0PFS.PSEL = sel;
					PORTK::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			// GTIOC2B:
			// P17 (LFQFP100: ---) (LFQFP144: 142)
			// P76 (LFQFP100:  51) (LFQFP144:  73)
			// PB5 (LFQFP100:  28) (LFQFP144:  41)
			// PD2 (LFQFP100:  23) (LFQFP144:  28)
			// PK1 (LFQFP100: ---) (LFQFP144:  84)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTK::PMR.B1 = 0;
					MPC::PK1PFS.PSEL = sel;
					PORTK::PMR.B1 = ena;
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
			// GTIOC3A:
			// P32 (LFQFP100:  59) (LFQFP144:  87)
			// PD1 (LFQFP100: ---) (LFQFP144:  29)
			// PD7 (LFQFP100:  18) (LFQFP144:  23)
			// PE5 (LFQFP100:   1) (LFQFP144:   5)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;
					PORTD::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;
					PORTE::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			// GTIOC3B:
			// P11 (LFQFP100:  99) (LFQFP144: 140)
			// P33 (LFQFP100:  58) (LFQFP144:  86)
			// PD0 (LFQFP100: ---) (LFQFP144:  30)
			// PD6 (LFQFP100:  19) (LFQFP144:  24)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;
					PORTD::PMR.B6 = ena;
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
			// GTIOC4A:
			// P71 (LFQFP100:  56) (LFQFP144:  78)
			// P95 (LFQFP100:  45) (LFQFP144:  67)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;
					PORT7::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			// GTIOC4B:
			// P74 (LFQFP100:  53) (LFQFP144:  75)
			// P92 (LFQFP100:  48) (LFQFP144:  70)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;
					PORT9::PMR.B2 = ena;
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
			// GTIOC5A:
			// P72 (LFQFP100:  55) (LFQFP144:  77)
			// P94 (LFQFP100:  46) (LFQFP144:  68)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			// GTIOC5B:
			// P75 (LFQFP100:  52) (LFQFP144:  74)
			// P91 (LFQFP100:  49) (LFQFP144:  71)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;
					PORT9::PMR.B1 = ena;
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
			// GTIOC6A:
			// P73 (LFQFP100:  54) (LFQFP144:  76)
			// P93 (LFQFP100:  47) (LFQFP144:  69)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			// GTIOC6B:
			// P76 (LFQFP100:  51) (LFQFP144:  73)
			// P90 (LFQFP100:  50) (LFQFP144:  72)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;
					PORT9::PMR.B0 = ena;
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
			uint8_t sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
			switch(ch) {
			// GTIOC7A:
			// P12 (LFQFP100: ---) (LFQFP144:   3)
			// P95 (LFQFP100:  45) (LFQFP144:  67)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			// GTIOC7B:
			// P15 (LFQFP100: ---) (LFQFP144: 144)
			// P92 (LFQFP100:  48) (LFQFP144:  70)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;
					PORT9::PMR.B2 = ena;
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


		static bool gptw8_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
			switch(ch) {
			// GTIOC8A:
			// P13 (LFQFP100: ---) (LFQFP144:   2)
			// P94 (LFQFP100:  46) (LFQFP144:  68)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			// GTIOC8B:
			// P16 (LFQFP100: ---) (LFQFP144: 143)
			// P91 (LFQFP100:  49) (LFQFP144:  71)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;
					PORT9::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			default:
				ret = false;
			}
			return ret;
		}


		static bool gptw9_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
			switch(ch) {
			// GTIOC9A:
			// P14 (LFQFP100: ---) (LFQFP144:   1)
			// P93 (LFQFP100:  47) (LFQFP144:  69)
			case CHANNEL::A:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			// GTIOC9B:
			// P17 (LFQFP100: ---) (LFQFP144: 142)
			// P90 (LFQFP100:  50) (LFQFP144:  72)
			case CHANNEL::B:
				switch(order) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;
					PORT9::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			default:
				ret = false;
			}
			return ret;
		}

		static bool trg_a_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTETRGA:
			// P01 (LFQFP100:   7) (LFQFP144:  12)
			// P11 (LFQFP100:  99) (LFQFP144: 140)
			// P70 (LFQFP100:  57) (LFQFP144:  79)
			// P96 (LFQFP100:  43) (LFQFP144:  65)
			// PB4 (LFQFP100:  30) (LFQFP144:  43)
			// PD5 (LFQFP100:  20) (LFQFP144:  25)
			// PE3 (LFQFP100:   9) (LFQFP144:  14)
			// PE4 (LFQFP100:   8) (LFQFP144:  13)
			// PE6 (LFQFP100: ---) (LFQFP144:   4)
			// PF3 (LFQFP100: ---) (LFQFP144:  31)
			// PG2 (LFQFP100: ---) (LFQFP144:  80)
			switch(odr) {
			case ORDER::FIRST:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORT0::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORT1::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORT7::PMR.B0 = ena;
				break;
			case ORDER::FOURTH:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORT9::PMR.B6 = ena;
				break;
			case ORDER::FIFTH:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTB::PMR.B4 = ena;
				break;
			case ORDER::SIXTH:
				PORTD::PMR.B5 = 0;
				MPC::PD5PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORTD::PMR.B5 = ena;
				break;
			case ORDER::SEVENTH:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTE::PMR.B3 = ena;
				break;
			case ORDER::EIGHTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTE::PMR.B4 = ena;
				break;
			case ORDER::NINTH:
				PORTE::PMR.B6 = 0;
				MPC::PE6PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTE::PMR.B6 = ena;
				break;
			case ORDER::TENTH:
				PORTF::PMR.B3 = 0;
				MPC::PF3PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTF::PMR.B3 = ena;
				break;
			case ORDER::ELEVENTH:
				PORTG::PMR.B2 = 0;
				MPC::PG2PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTG::PMR.B2 = ena;
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
			// P01 (LFQFP100:   7) (LFQFP144:  12)
			// P10 (LFQFP100: 100) (LFQFP144: 141)
			// P34 (LFQFP100: ---) (LFQFP144:  61)
			// P70 (LFQFP100:  57) (LFQFP144:  79)
			// P96 (LFQFP100:  43) (LFQFP144:  65)
			// PB4 (LFQFP100:  30) (LFQFP144:  43)
			// PD4 (LFQFP100:  21) (LFQFP144:  26)
			// PE3 (LFQFP100:   9) (LFQFP144:  14)
			// PE4 (LFQFP100:   8) (LFQFP144:  13)
			// PE5 (LFQFP100:   1) (LFQFP144:   5)
			// PE6 (LFQFP100: ---) (LFQFP144:   4)
			// PF2 (LFQFP100: ---) (LFQFP144:  32)
			switch(odr) {
			case ORDER::FIRST:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORT0::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B0 = 0;
				MPC::P10PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORT1::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORT3::PMR.B4 = 0;
				MPC::P34PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORT3::PMR.B4 = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = ena ? 0b01'0101 : 0;  // ok 
				PORT7::PMR.B0 = ena;
				break;
			case ORDER::FIFTH:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORT9::PMR.B6 = ena;
				break;
			case ORDER::SIXTH:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORTB::PMR.B4 = ena;
				break;
			case ORDER::SEVENTH:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORTD::PMR.B4 = ena;
				break;
			case ORDER::EIGHTH:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORTE::PMR.B3 = ena;
				break;
			case ORDER::NINTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORTE::PMR.B4 = ena;
				break;
			case ORDER::TENTH:
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTE::PMR.B5 = ena;
				break;
			case ORDER::ELEVENTH:
				PORTE::PMR.B6 = 0;
				MPC::PE6PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTE::PMR.B6 = ena;
				break;
			case ORDER::TWELVETH:
				PORTF::PMR.B2 = 0;
				MPC::PF2PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTF::PMR.B2 = ena;
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
			// P01 (LFQFP100:   7) (LFQFP144:  12)
			// P11 (LFQFP100:  99) (LFQFP144: 140)
			// P70 (LFQFP100:  57) (LFQFP144:  79)
			// P96 (LFQFP100:  43) (LFQFP144:  65)
			// PB4 (LFQFP100:  30) (LFQFP144:  43)
			// PD3 (LFQFP100:  22) (LFQFP144:  27)
			// PE3 (LFQFP100:   9) (LFQFP144:  14)
			// PE4 (LFQFP100:   8) (LFQFP144:  13)
			// PE6 (LFQFP100: ---) (LFQFP144:   4)
			// PF1 (LFQFP100: ---) (LFQFP144:  33)
			switch(odr) {
			case ORDER::FIRST:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
				PORT0::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
				PORT1::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
				PORT7::PMR.B0 = ena;
				break;
			case ORDER::FOURTH:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
				PORT9::PMR.B6 = ena;
				break;
			case ORDER::FIFTH:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
				PORTB::PMR.B4 = ena;
				break;
			case ORDER::SIXTH:
				PORTD::PMR.B3 = 0;
				MPC::PD3PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORTD::PMR.B3 = ena;
				break;
			case ORDER::SEVENTH:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
				PORTE::PMR.B3 = ena;
				break;
			case ORDER::EIGHTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
				PORTE::PMR.B4 = ena;
				break;
			case ORDER::NINTH:
				PORTE::PMR.B6 = 0;
				MPC::PE6PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
				PORTE::PMR.B6 = ena;
				break;
			case ORDER::TENTH:
				PORTF::PMR.B1 = 0;
				MPC::PF1PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTF::PMR.B1 = ena;
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
			// P01 (LFQFP100:   7) (LFQFP144:  12)
			// P10 (LFQFP100: 100) (LFQFP144: 141)
			// P70 (LFQFP100:  57) (LFQFP144:  79)
			// P96 (LFQFP100:  43) (LFQFP144:  65)
			// PB4 (LFQFP100:  30) (LFQFP144:  43)
			// PE3 (LFQFP100:   9) (LFQFP144:  14)
			// PE4 (LFQFP100:   8) (LFQFP144:  13)
			// PE5 (LFQFP100:   1) (LFQFP144:   5)
			// PE6 (LFQFP100: ---) (LFQFP144:   4)
			// PF0 (LFQFP100: ---) (LFQFP144:  34)
			switch(odr) {
			case ORDER::FIRST:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
				PORT0::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B0 = 0;
				MPC::P10PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
				PORT1::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
				PORT7::PMR.B0 = ena;
				break;
			case ORDER::FOURTH:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
				PORT9::PMR.B6 = ena;
				break;
			case ORDER::FIFTH:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
				PORTB::PMR.B4 = ena;
				break;
			case ORDER::SIXTH:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
				PORTE::PMR.B3 = ena;
				break;
			case ORDER::SEVENTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
				PORTE::PMR.B4 = ena;
				break;
			case ORDER::EIGHTH:
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = ena ? 0b01'0110 : 0;  // ok
				PORTE::PMR.B5 = ena;
				break;
			case ORDER::NINTH:
				PORTE::PMR.B6 = 0;
				MPC::PE6PFS.PSEL = ena ? 0b01'0111 : 0;  // ok
				PORTE::PMR.B6 = ena;
				break;
			case ORDER::TENTH:
				PORTF::PMR.B0 = 0;
				MPC::PF0PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTF::PMR.B0 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool dsm_0_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTADSM0:
			// P35 (LFQFP100: ---) (LFQFP144:  60)
			// PA3 (LFQFP100:  38) (LFQFP144:  56)
			// PA7 (LFQFP100: ---) (LFQFP144:  52)
			// PB2 (LFQFP100:  33) (LFQFP144:  49)
			// PC2 (LFQFP100: ---) (LFQFP144:  45)
			switch(odr) {
			case ORDER::FIRST:
				PORT3::PMR.B5 = 0;
				MPC::P35PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORT3::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTA::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B7 = 0;
				MPC::PA7PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTA::PMR.B7 = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTB::PMR.B2 = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTC::PMR.B2 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool dsm_1_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTADSM1:
			// P34 (LFQFP100: ---) (LFQFP144:  61)
			// PA2 (LFQFP100:  39) (LFQFP144:  57)
			// PA6 (LFQFP100: ---) (LFQFP144:  53)
			// PB1 (LFQFP100:  34) (LFQFP144:  50)
			// PC1 (LFQFP100: ---) (LFQFP144:  46)
			switch(odr) {
			case ORDER::FIRST:
				PORT3::PMR.B4 = 0;
				MPC::P34PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORT3::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B2 = 0;
				MPC::PA2PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTA::PMR.B2 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTA::PMR.B6 = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTB::PMR.B1 = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTC::PMR.B1 = ena;
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
			@brief  GPTW[0-9]、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ型
			@param[in]	ch	チャネル型
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補を選択する場合
			@param[in]	neg	反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

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
			case peripheral::GPTW8:
				ret = gptw8_(ch, ena, neg, odr);
				break;
			case peripheral::GPTW9:
				ret = gptw9_(ch, ena, neg, odr);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPTW クロック（トリガー）入出力切り替え
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
			case CHANNEL::DSM0:
				ret = dsm_0_(odr, ena);
				break;
			case CHANNEL::DSM1:
				ret = dsm_1_(odr, ena);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
