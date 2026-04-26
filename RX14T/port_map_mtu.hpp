#pragma once
//=========================================================================//
/*!	@file
	@brief	RX14T グループ・ポート・マッピング (MTU3c) @n
			・MTU 型に従って、タイマー用ポートを設定 @n
			MTU0, MTU1, MTU2, MTU3, MTU4, MTU5, MTU
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX14T/peripheral.hpp"
#include "RX14T/port.hpp"
#include "RX14T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX14T/MTU ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {

		static bool mtu0_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b0'0011 : 0b0'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC0A(#):
			// P30
			// P36
			// PB1 (LFQFP48: )
			// PD3 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;  // ok
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B6 = 0;
					MPC::P36PFS.PSEL = sel;  // ok
					PORT3::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // ok
					PORTD::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC0B(#):
			// P25
			// P92
			// PB0 (LFQFP48: )
			// PD4 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // ok
					PORT9::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // ok
					PORTD::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC0C(#):
			// P33
			// P93
			// P97 (LFQFP48: )
			// PD5 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;  // ok
					PORT9::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORT9::PMR.B7 = 0;
					MPC::P97PFS.PSEL = sel;  // ok
					PORT9::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;  // ok
					PORTD::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC0D(#):
			// P32
			// P96 (LFQFP48: )
			// PD6 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B6 = 0;
					MPC::P96PFS.PSEL = sel;  // ok
					PORT9::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // ok
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

		static bool mtu1_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b0'0011 : 0b0'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC1A(#):
			// P04
			// P36
			// P92 (LFQFP48: )
			// P94 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B4 = 0;
					MPC::P04PFS.PSEL = sel; // ok
					PORT0::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B6 = 0;
					MPC::P36PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORT3::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;  // ok
					PORT9::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;  // ok
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC1B(#):
			// P03
			// P95 (LFQFP48: )
			// PB5 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B3 = 0;
					MPC::P03PFS.PSEL = sel;  // ok
					PORT0::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // ok
					PORT9::PMR.B5 = ena;
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
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool mtu2_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC2A(#):
			// P95 (LFQFP48: )
			// PB5 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // ok
					PORT9::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORTB::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC2B(#):
			// P93
			// P94 (LFQFP48: )
			// PB6 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;  // ok
					PORT9::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;  // ok
					PORT9::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORTB::PMR.B6 = ena;
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

		static bool mtu3_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b0'0011 : 0b0'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC3A(#):
			// P11 (LFQFP48: )
			// P33
			// PB5 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;  // ok
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? (neg ? 0b0'0100 : 0b0'0100) : 0;  // ok
					PORTB::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC3B(#):
			// P26
			// P71 (LFQFP48: )
			// P94
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;  // ok
					PORT2::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // ok
					PORT7::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC3C(#):
			// P32
			// PB6 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC3D(#):
			// P74 (LFQFP48: )
			// P97
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;  // ok
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B7 = 0;
					MPC::P97PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORT9::PMR.B7 = ena;
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

		static bool mtu4_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b0'0011 : 0b0'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC4A(#):
			// P31
			// P36
			// P72 (LFQFP48: )
			// P95
			// PD3
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;  // ok
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B6 = 0;
					MPC::P36PFS.PSEL = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;  // ok
					PORT3::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // ok
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORT9::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;  // ok
					PORTD::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC4B(#):
			// P25
			// P73 (LFQFP48: )
			// P96
			// PD4
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // ok
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORT9::PMR.B6 = 0;
					MPC::P96PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORT9::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;  // ok
					PORTD::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC4C(#):
			// P11
			// P75 (LFQFP48: )
			// PB0
			// PD5
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // ok
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;  // ok
					PORTD::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC4D(#):
			// P76 (LFQFP48: )
			// PB1
			// PD6
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // ok
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;  // ok
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

		static bool mtu5_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b0'0011 : 0b0'0001) : 0;
			switch(ch) {
			case CHANNEL::U:  // MTIOC5U(#):
			// P24 (LFQFP48: )
			// P91 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;  // ok
					PORT9::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::V:  // MTIOC5V(#):
			// P23 (LFQFP48: )
			// P90 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;  // ok
					PORT9::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::W:  // MTIOC5W(#):
			// P22 (LFQFP48: )
			// PB2 (LFQFP48: )
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = sel;  // ok
					PORTB::PMR.B2 = ena;
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

		static bool clk_a_(ORDER odr, bool ena, bool neg) noexcept
		{
			// MTCLKA(#):
			// P23
			// P33 (LFQFP48: )
			// P93 (LFQFP48: )
			// P97 (LFQFP48: )
			uint8_t sel = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = sel;  // ok
				PORT3::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = ena ? (neg ? 0b0'1110 : 0b0'1000) : 0;  // ok
				PORT9::PMR.B3 = ena;
				break;
			case ORDER::FOURTH:
				PORT9::PMR.B7 = 0;
				MPC::P97PFS.PSEL = sel;  // ok
				PORT9::PMR.B7 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool clk_b_(ORDER odr, bool ena, bool neg) noexcept
		{
			// MTCLKB(#):
			// P22
			// P32 (LFQFP48: )
			// P96 (LFQFP48: )
			uint8_t sel = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = sel;  // ok
				PORT3::PMR.B2 = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = sel;  // ok
				PORT9::PMR.B6 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool clk_c_(ORDER odr, bool ena, bool neg) noexcept
		{
			// MTCLKC(#):
			// P11
			// P30
			// PB0 (LFQFP48: )
			uint8_t sel = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = sel;  // ok
				PORT1::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = sel;  // ok
				PORT3::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool clk_d_(ORDER odr, bool ena, bool neg) noexcept
		{
			// MTCLKD(#):
			// P10
			// P25
			// PB6 (LFQFP48: )
			uint8_t sel = ena ? (neg ? 0b0'0100 : 0b0'0010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B0 = 0;
				MPC::P10PFS.PSEL = sel;  // ok
				PORT1::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;  // ok
				PORT2::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool adsm0_(ORDER odr, bool ena) noexcept
		{
			// ADSM0:
			// PB0 (LFQFP48: )
			uint8_t sel = ena ? 0b0'1001 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool adsm1_(ORDER odr, bool ena) noexcept
		{
			// ADSM1:
			// P97 (LFQFP48: )
			uint8_t sel = ena ? 0b0'1001 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT9::PMR.B7 = 0;
				MPC::P97PFS.PSEL = sel;  // ok
				PORT9::PMR.B7 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

	public:
		//---------------------------------------------------------------------//
		/*!
			@brief  MTU 関係、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//---------------------------------------------------------------------//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::MTU0:
				ret = mtu0_(ch, ena, odr, neg);
				break;
			case peripheral::MTU1:
				ret = mtu1_(ch, ena, odr, neg);
				break;
			case peripheral::MTU2:
				ret = mtu2_(ch, ena, odr, neg);
				break;
			case peripheral::MTU3:
				ret = mtu3_(ch, ena, odr, neg);
				break;
			case peripheral::MTU4:
				ret = mtu4_(ch, ena, odr, neg);
				break;
			case peripheral::MTU5:
				ret = mtu5_(ch, ena, odr, neg);
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MTU クロックポート切り替え
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_clock(CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(ch) {
			case CHANNEL::CLKA:
				ret = clk_a_(odr, ena, neg);
				break;
			case CHANNEL::CLKB:
				ret = clk_b_(odr, ena, neg);
				break;
			case CHANNEL::CLKC:
				ret = clk_c_(odr, ena, neg);
				break;
			case CHANNEL::CLKD:
				ret = clk_d_(odr, ena, neg);
				break;
			case CHANNEL::ADSM0:
				ret = adsm0_(odr, ena);
				break;
			case CHANNEL::ADSM1:
				ret = adsm1_(odr, ena);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
