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
			// PG2 (LFQFP100: ---) (LFQFP144:  81)
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
			/// GTIOC1A:
			/// P13[0] ( 2/144) (--/100)
			/// P72[0] (77/144) (55/100)
			/// PD0[1] (30/144) (--/100) (25/100) 
			/// PD5[0] (25/144) (20/100)
			/// PK2[1] (83/144) (--/100)
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
			/// GTIOC1B:
			/// P16[0] (143/144) (111/112)
			/// P75[0] ( 74/144)
			/// PB7[0] ( 39/144)
			/// PD4[0] ( 26/144)
			/// PG0[1] ( 82/144)
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
			/// GTIOC2A:
			/// P14[0] ( 1/144)
			/// P73[0] (76/144)
			/// PB6[0] (40/144)
			/// PD3[0] (27/144)
			/// PK0[1] (85/144)
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
			/// GTIOC2B:
			/// P17[0] (142/144)
			/// P76[0] ( 73/144)
			/// PB5[0] ( 41/144)
			/// PD2[0] ( 28/144)
			/// PK1[1] ( 84/144)
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
			/// GTIOC3A:
			/// P32[0] (87/144)
			/// PD1[0] (29/144)
			/// PD7[1] (23/144)
			/// PE5[0] ( 5/144)
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
			/// GTIOC3B:
			/// P11[0] (140/144)
			/// P33[0] ( 86/144)
			/// PD0[0] ( 30/144)
			/// PD6[1] ( 24/144)
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
			/// GTIOC4A:
			/// P71[1] (78/144)
			/// P95[0] (67/144)
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
			/// GTIOC4B:
			/// P74[1] (75/144)
			/// P92[0] (70/144)
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
			/// GTIOC5A:
			/// P72[1] (77/144)
			/// P94[0] (68/144)
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
			/// GTIOC5B:
			/// P75[1] (74/144)
			/// P91[0] (71/144)
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
			/// GTIOC6A:
			/// P73[1] (76/144)
			/// P93[0] (69/144)
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
			/// GTIOC6B:
			/// P76[1] (73/144)
			/// P90[0] (72/144)
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
			/// GTIOC7A:
			/// P12[1] ( 3/144)
			/// P95[1] (67/144)
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
			/// GTIOC7B:
			/// P15[1]
			/// P92[1]
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
			/// GTIOC8A:
			/// P13[1] ( 2/144)
			/// P94[1] (68/144)
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
			/// GTIOC8B:
			/// P16[1] (143/144)
			/// P91[1] ( 71/144)
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
			/// GTIOC9A:
			/// P14[1] ( 1/144)
			/// P93[1] (69/144)
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
			/// GTIOC9B:
			/// P17[1] (142/144)
			/// P90[1] ( 72/144)
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
			// P01
			// P11
			// P70
			// P96
			// PB4
			// PD5
			// PE3
			// PE4
			// PE6
			// PF3
			// PG2
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
			// P01
			// P10
			// P34
			// P70
			// P96
			// PB4
			// PD4
			// PE3
			// PE4
			// PE5
			// PE6
			// PF2
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
			// P01
			// P11
			// P70
			// P96
			// PB4
			// PD3
			// PE3
			// PE4
			// PE6
			// PF1
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
			// P01
			// P10
			// P70
			// P96
			// PB4
			// PE3
			// PE4
			// PE5
			// PE6
			// PF0
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
			// P35
			// PA3
			// PA7
			// PB2
			// PC2
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
			// P34
			// PA2
			// PA6
			// PB1
			// PC1
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
