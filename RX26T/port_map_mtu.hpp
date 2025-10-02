#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・ポート・マッピング (MTU3d) @n
			・MTU 型に従って、タイマー用ポートを設定 @n
			MTU0, MTU1, MTU2, MTU3, MTU4, MTU5, MTU6, MTU7, MTU8, MTU9
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
		@brief  RX26T/MTU ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {

		static bool mtu0_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b00'0011 : 0b00'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC0A[#]
			// P31 (LFQFP100:  61)
			// P70 (LFQFP100:  57)
			// PB3 (LFQFP100:  32)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;  // ok
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B0 = 0;
					MPC::P70PFS.PSEL = sel;  // ok
					PORT7::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC0B[#]
			// P30 (LFQFP100:  63)
			// PB2 (LFQFP100:  33)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;  // ok
					PORT3::PMR.B0 = ena;
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
			case CHANNEL::C:  // MTIOC0C[#]
			// P27 (LFQFP100:  64)
			// PB1 (LFQFP100:  34)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = ena ? (neg ? 0b00'0100 : 0b00'0010) : 0;  // ok
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC0D[#]
			// PB0 (LFQFP100:  35)
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
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
			uint8_t sel = ena ? (neg ? 0b00'0011 : 0b00'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC1A[#]
			// P27 (LFQFP100:  64)
			// P95 (LFQFP100:  45)
			// PA5 (LFQFP100:  36)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = ena ? (neg ? 0b00'0100 : 0b00'0010) : 0;  // ok
					PORT9::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;  // ok
					PORTA::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC1B[#]
			// PA4 (LFQFP100:  37)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = ena;
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
			uint8_t sel = ena ? (neg ? 0b00'0011 : 0b00'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC2A[#]
			// P94 (LFQFP100:  46)
			// PA3 (LFQFP100:  38)
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = ena ? (neg ? 0b00'0100 : 0b00'0010) : 0;  // ok
					PORT9::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // ok
					PORTA::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC2B[#]
			// PA2 (LFQFP100:  39)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;  // ok
					PORTA::PMR.B2 = ena;
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
			uint8_t sel = ena ? (neg ? 0b00'0011 : 0b00'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC3A[#]
			// P11 (LFQFP100:  99)
			// P33 (LFQFP100:  58)
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
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC3B[#]
			// P71 (LFQFP100:  56)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // ok
					PORT7::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC3C[#]
			// P32 (LFQFP100:  59)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC3D[#]
			// P74 (LFQFP100:  53)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;  // ok
					PORT7::PMR.B4 = ena;
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
			uint8_t sel = ena ? (neg ? 0b00'0011 : 0b00'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC4A[#]
			// P72 (LFQFP100:  55)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // ok
					PORT7::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC4B[#]
			// P73 (LFQFP100:  54)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // ok
					PORT7::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC4C[#]
			// P75 (LFQFP100:  52)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // ok
					PORT7::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC4D[#]
			// P76 (LFQFP100:  51)
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // ok
					PORT7::PMR.B6 = ena;
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
			uint8_t sel = ena ? (neg ? 0b00'0011 : 0b00'0001) : 0;
			switch(ch) {
			case CHANNEL::U:  // MTIC5U[#]
			// P24 (LFQFP100:  65)
			// P82 (LFQFP100:  96)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::V:  // MTIC5V[#]
			// P23 (LFQFP100:  66)
			// P81 (LFQFP100:  97)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;  // ok
					PORT8::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::W:  // MTIC5W[#]
			// P22 (LFQFP100:  67)
			// P80 (LFQFP100:  98)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;  // ok
					PORT8::PMR.B0 = ena;
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

		static bool mtu6_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b00'0011 : 0b00'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC6A[#]
			// P93 (LFQFP100:  47)
			// PA1 (LFQFP100:  40)
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = ena ? (neg ? 0b00'0100 : 0b00'0010) : 0;  // ok
					PORT9::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC6B[#]
			// P95 (LFQFP100:  45)
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // ok
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC6C[#]
			// P92 (LFQFP100:  48)
			// PA0 (LFQFP100:  41)
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = ena ? (neg ? 0b00'0100 : 0b00'0010) : 0;  // ok
					PORT9::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC6D[#]
			// P92 (LFQFP100:  48)
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // ok
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

		static bool mtu7_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b00'0011 : 0b00'0001) : 0;
			switch(ch) {
			case CHANNEL::A:
			// P94 (LFQFP100:  46)
				switch(odr) {  // MTIOC7A[#]
				case ORDER::FIRST:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;  // ok
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC7B[#]
			// P93 (LFQFP100:  47)  
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;  // ok
					PORT9::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC7C[#]
			// P91 (LFQFP100:  49)  
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;  // ok
					PORT9::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC7D[#]
			// P90 (LFQFP100:  50)
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;  // ok
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

		static bool mtu9_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b00'0011 : 0b00'0001) : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC9A[#]
			// P00 (LFQFP100:   4)
			// P21 (LFQFP100:  68)
			// PD7 (LFQFP100:  18)
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = sel;  // ok
					PORT0::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // ok
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC9B(#)
			// P22 (LFQFP100:  67) #:NG
			// P10 (LFQFP100: 100)
			// PE0 (LFQFP100:  17)
				switch(odr) {
				case ORDER::FIRST:
					if(neg) {
						ret = false;
						break;
					}
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;  // ok
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;  // ok
					PORTE::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC9C[#]
			// P01 (LFQFP100:   7)
			// P20 (LFQFP100:  69)
			// PD6 (LFQFP100:  19)
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = sel;  // ok
					PORT0::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B0 = ena;
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
			case CHANNEL::D:  // MTIOC9D[#]
			// P11 (LFQFP100:  99) #:NG
			// PE1 (LFQFP100:  16)
			// PE5 (LFQFP100:   1)
			// PN7 (LFQFP100:   2)
				switch(odr) {
				case ORDER::FIRST:
					if(neg) {
						ret = false;
						break;
					}
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;  // ok
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;  // ok
					PORTE::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTN::PMR.B7 = 0;
					MPC::PN7PFS.PSEL = sel;  // ok
					PORTN::PMR.B7 = ena;
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
			// MTCLKA[#]:
			// P21 (LFQFP100:  68)
			// P33 (LFQFP100:  58)
			uint8_t sel = ena ? (neg ? 0b00'0100 : 0b00'0010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = sel;  // ok
				PORT2::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = sel;  // ok
				PORT3::PMR.B3 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_b_(ORDER odr, bool ena, bool neg) noexcept
		{
			// MTCLKB[#]:
			// P20 (LFQFP100:  69)
			// P32 (LFQFP100:  59)
			uint8_t sel = ena ? (neg ? 0b00'0100 : 0b00'0010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = sel;  // ok
				PORT2::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = sel;  // ok
				PORT3::PMR.B2 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_c_(ORDER odr, bool ena, bool neg) noexcept
		{
			// MTCLKC[#]:
			// P11 (LFQFP100:  99)
			// P31 (LFQFP100:  61)
			// P70 (LFQFP100:  57)
			// PE4 (LFQFP100:   8)
			uint8_t sel = ena ? (neg ? 0b00'0100 : 0b00'0010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = sel;  // ok
				PORT1::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = sel;  // ok
				PORT3::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = sel;  // ok
				PORT7::PMR.B0 = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = sel;  // ok
				PORTE::PMR.B4 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_d_(ORDER odr, bool ena, bool neg) noexcept
		{
			// MTCLKD[#]:
			// P10 (LFQFP100: 100)
			// P22 (LFQFP100:  67)
			// P30 (LFQFP100:  63)
			// PE3 (LFQFP100:   9)
			uint8_t sel = ena ? (neg ? 0b00'0100 : 0b00'0010) : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B0 = 0;
				MPC::P10PFS.PSEL = sel;  // ok
				PORT1::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = ena;
				break;
			case ORDER::THIRD:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = sel;  // ok
				PORT3::PMR.B0 = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = sel;  // ok
				PORTE::PMR.B3 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool adsm0_(ORDER odr, bool ena, bool neg) noexcept
		{
			if(neg) return false;
			// ADSM0:
			// PB2 (LFQFP100:  33)
			uint8_t sel = ena ? 0b0'1001 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = sel;  // ok
				PORTB::PMR.B2 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool adsm1_(ORDER odr, bool ena, bool neg) noexcept
		{
			if(neg) return false;
			// ADSM1:
			// PB1 (LFQFP100:  34)
			uint8_t sel = ena ? 0b0'1001 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = sel;  // ok
				PORTB::PMR.B1 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MTU チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補選択
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
			case peripheral::MTU6:
				ret = mtu6_(ch, ena, odr, neg);
				break;
			case peripheral::MTU7:
				ret = mtu7_(ch, ena, odr, neg);
				break;
			case peripheral::MTU9:
				ret = mtu9_(ch, ena, odr, neg);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MTU クロックポート切り替え
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
				ret = adsm0_(odr, ena, neg);
				break;
			case CHANNEL::ADSM1:
				ret = adsm1_(odr, ena, neg);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
