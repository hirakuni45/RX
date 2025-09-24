#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・ポート・マッピング (GPTW0 - GPTW7)  @n
			（クロック関係は実装中・・・）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2025 Kunihito Hiramatsu @n
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
				// P71 (LFQFP100:  56)
				// PD2 (LFQFP100:  23)
				// PD7 (LFQFP100:  18)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // OK
					PORT7::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // OK
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // OK
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC0B(#):
				// P74 (LFQFP100:  53)
				// PD1 (LFQFP100:  24)
				// PD6 (LFQFP100:  19)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;  // OK
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // OK
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // OK
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


		static bool gptw1_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel;
			switch(ch) {
			case CHANNEL::A:  // GTIOC1A(#):
				// P72 (LFQFP100:  55)
				// PD0 (LFQFP100:  25)
				// PD5 (LFQFP100:  20)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // OK
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b0'10111 : 0b01'0101) : 0;
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;  // OK
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;  // OK
					PORTD::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC1B(#):
				// P75 (LFQFP100:  52)
				// PB7 (LFQFP100:  26)
				// PD4 (LFQFP100:  21)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // OK
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // OK
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // OK
					PORTD::PMR.B4 = ena;
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
				// P73 (LFQFP100:  54)
				// PB6 (LFQFP100:  27)
				// PD3 (LFQFP100:  22)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // OK
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // OK
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // OK
					PORTD::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC2B(#):
				// P76 (LFQFP100:  51)
				// PB5 (LFQFP100:  28)
				// PD2 (LFQFP100:  23)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // OK
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // OK
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // OK
					PORTD::PMR.B2 = ena;
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
				// P10 (LFQFP100: 100)
				// P32 (LFQFP100:  59)
				// PB6 (LFQFP100:  27)
				// PD1 (LFQFP100:  24)
				// PD7 (LFQFP100:  18)
				// PE5 (LFQFP100:   1)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;  // OK
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // OK
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // OK
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // OK
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // OK
					PORTD::PMR.B7 = ena;
					break;
				case ORDER::SIXTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;  // OK
					PORTE::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC3B(#):
				// P11 (LFQFP100:  99)
				// P33 (LFQFP100:  58)
				// PB5 (LFQFP100:  28)
				// PD0 (LFQFP100:  25)
				// PD6 (LFQFP100:  19)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;  // OK
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // OK
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // OK
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;  // OK
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // OK
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
			case CHANNEL::A:  // GTIOC4A(#):
				// P71 (LFQFP100:  56)
				// P95 (LFQFP100:  45)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // OK
					PORT7::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // OK
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC4B(#):
				// P74 (LFQFP100:  53)
				// P92 (LFQFP100:  48)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;  // OK
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // OK
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
			case CHANNEL::A:  // GTIOC5A(#):
				// P72 (LFQFP100:  55)
				// P94 (LFQFP100:  46)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // OK
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;  // OK
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC5B(#):
				// P75 (LFQFP100:  52)
				// P91 (LFQFP100:  49)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // OK
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;  // OK
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
			case CHANNEL::A:  // GTIOC6A(#):
				// P73 (LFQFP100:  54)
				// P93 (LFQFP100:  47)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // OK
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;  // OK
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC6B(#):
				// P76 (LFQFP100:  51)
				// P90 (LFQFP100:  50)
				switch(order) {
				case ORDER::FIRST:
					sel = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // OK
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;  // OK
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
			case CHANNEL::A:
				// GTIOC7A(#): P32 (LFQFP100:  59)
				// GTIOC7A(#): P95 (LFQFP100:  45)
				// GTIOC7A(#): PB2 (LFQFP100:  33)
				// GTIOC7A(-): PD5 (LFQFP100:  20)
				switch(order) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // OK
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // OK
					PORT9::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = sel;  // OK
					PORTB::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					if(neg) {
						ret = false;
					} else {
						PORTD::PMR.B5 = 0;
						MPC::PD5PFS.PSEL = ena ? 0b01'0111 : 0;  // OK
						PORTD::PMR.B5 = ena;
					}
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:
				// GTIOC7B(#): P33 (LFQFP100:  58)
				// GTIOC7B(#): P92 (LFQFP100:  48)
				// GTIOC7B(#): PB1 (LFQFP100:  34)
				// GTIOC7B(-): PD3 (LFQFP100:  22)
				switch(order) {
				case ORDER::FIRST:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // OK
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // OK
					PORT9::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // OK
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					if(neg) {
						ret = false;
					} else {
						PORTD::PMR.B3 = 0;
						MPC::PD3PFS.PSEL = ena ? 0b01'0111 : 0;  // OK
						PORTD::PMR.B3 = ena;
					}
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
			// P01 (LFQFP100:   7)
			// P11 (LFQFP100:  99)
			// P70 (LFQFP100:  57)
			// P96 (LFQFP100:  43)
			// PB4 (LFQFP100:  30)
			// PD5 (LFQFP100:  20)
			// PE3 (LFQFP100:   9)
			// PE4 (LFQFP100:   8)
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
			// P01 (LFQFP100:   7)
			// P10 (LFQFP100: 100)
			// P70 (LFQFP100:  57)
			// P96 (LFQFP100:  43)
			// PB4 (LFQFP100:  30)
			// PD4 (LFQFP100:  21)
			// PE3 (LFQFP100:   9)
			// PE4 (LFQFP100:   8)
			// PE5 (LFQFP100:   1)
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
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = ena ? 0b01'0101 : 0;  // ok 
				PORT7::PMR.B0 = ena;
				break;
			case ORDER::FOURTH:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORT9::PMR.B6 = ena;
				break;
			case ORDER::FIFTH:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORTB::PMR.B4 = ena;
				break;
			case ORDER::SIXTH:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORTD::PMR.B4 = ena;
				break;
			case ORDER::SEVENTH:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORTE::PMR.B3 = ena;
				break;
			case ORDER::EIGHTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = ena ? 0b01'0101 : 0;  // ok
				PORTE::PMR.B4 = ena;
				break;
			case ORDER::NINTH:
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
				PORTE::PMR.B5 = ena;
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
			// P01 (LFQFP100:   7)
			// P11 (LFQFP100:  99)
			// P70 (LFQFP100:  57)
			// P96 (LFQFP100:  43)
			// PB4 (LFQFP100:  30)
			// PD3 (LFQFP100:  22)
			// PE3 (LFQFP100:   9)
			// PE4 (LFQFP100:   8)
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
			// P01 (LFQFP100:   7)
			// P10 (LFQFP100: 100)
			// P70 (LFQFP100:  57)
			// P96 (LFQFP100:  43)
			// PB4 (LFQFP100:  30)
			// PE3 (LFQFP100:   9)
			// PE4 (LFQFP100:   8)
			// PE5 (LFQFP100:   1)
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
			// P94 (LFQFP100:  46)
			// PA3 (LFQFP100:  38)
			// PB2 (LFQFP100:  33)
			switch(odr) {
			case ORDER::FIRST:
				PORT9::PMR.B4 = 0;
				MPC::P94PFS.PSEL = ena ? 0b01'0100 : 0;
				PORT9::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = ena ? 0b01'0100 : 0;
				PORTA::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = ena ? 0b01'0100 : 0;
				PORTB::PMR.B2 = ena;
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
			// PA2 (LFQFP100:  39)
			// PB1 (LFQFP100:  34)
			switch(odr) {
			case ORDER::FIRST:
				PORTA::PMR.B2 = 0;
				MPC::PA2PFS.PSEL = ena ? 0b01'0100 : 0;
				PORTA::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = ena ? 0b01'0100 : 0;
				PORTB::PMR.B1 = ena;
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
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
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
				ret = false;
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
