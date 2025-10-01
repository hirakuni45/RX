#pragma once
//=========================================================================//
/*!	@file
	@brief	RX113 グループ・ポート・マッピング (MTU2a) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX113/peripheral.hpp"
#include "RX113/port.hpp"
#include "RX113/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX113 / MTU2 ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {

		static bool mtu0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:
			// MTIOC0A: P14 (LFQFP64: 20) (LFQFP100:  29)
			// MTIOC0A: PB3 (LFQFP64: 36) (LFQFP100:  57)
			// MTIOC0A: PE3 (LFQFP64: 48) (LFQFP100:  75)
			// MTIOC0A: P04 (LFQFP64: --) (LFQFP100:   1)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTE::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORT0::PMR.B4 = 0;
					MPC::P04PFS.PSEL = sel;  // ok
					PORT0::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:
			// MTIOC0B: P15 (LFQFP64: 19) (LFQFP100:  28)
			// MTIOC0B: PA1 (LFQFP64: 44) (LFQFP100:  69)
			// MTIOC0B: P13 (LFQFP64: --) (LFQFP100:  34)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;  // ok
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;  // ok
					PORT1::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:
			// MTIOC0C: P17 (LFQFP64: 17) (LFQFP100:  26)
			// MTIOC0C: P32 (LFQFP64: 16) (LFQFP100:  25)
			// MTIOC0C: PB0 (LFQFP64: 39) (LFQFP100:  61)
			// MTIOC0C: PB1 (LFQFP64: 37) (LFQFP100:  59)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:
			// MTIOC0D: PA3 (LFQFP64: 43) (LFQFP100:  67)
			// MTIOC0D: P02 (LFQFP64: --) (LFQFP100:   3)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // ok
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT0::PMR.B2 = 0;
					MPC::P02PFS.PSEL = sel;  // ok
					PORT0::PMR.B2 = ena;
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

		static bool mtu1_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:
			// MTIOC1A: PE4 (LFQFP64: 47) (LFQFP100:  74)
			// MTIOC1A: P20 (LFQFP64: --) (LFQFP100:  10)
			// MTIOC1A: P56 (LFQFP64: --) (LFQFP100:  38)
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORT5::PMR.B6 = 0;
					MPC::P56PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORT5::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:
			// MTIOC1B: PA3 (LFQFP64: 43) (LFQFP100:  67)
			// MTIOC1B: PB5 (LFQFP64: 35) (LFQFP100:  55)
			// MTIOC1B: PE3 (LFQFP64: 48) (LFQFP100:  75)
			// MTIOC1B: P21 (LFQFP64: --) (LFQFP100:   9)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTE::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = ena;
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

		static bool mtu2_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:
			// MTIOC2A: P26 (LFQFP64:  3) (LFQFP100:  12)
			// MTIOC2A: PA6 (LFQFP64: 41) (LFQFP100:  63)
			// MTIOC2A: PB5 (LFQFP64: 35) (LFQFP100:  55)
			// MTIOC2A: PE0 (LFQFP64: 51) (LFQFP100:  78)
			// MTIOC2A: P50 (LFQFP64: --) (LFQFP100:  42)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;  // ok
					PORT2::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // ok
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTE::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORT5::PMR.B0 = 0;
					MPC::P50PFS.PSEL = sel;  // ok
					PORT5::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:
			// MTIOC2B: P27 (LFQFP64:  2) (LFQFP100:  11)
			// MTIOC2B: PA4 (LFQFP64: 42) (LFQFP100:  68)
			// MTIOC2B: PE5 (LFQFP64: 46) (LFQFP100:  73)
			// MTIOC2B: P53 (LFQFP64: --) (LFQFP100:  39)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTE::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORT5::PMR.B3 = 0;
					MPC::P53PFS.PSEL = sel;  // ok
					PORT5::PMR.B3 = ena;
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

		static bool mtu3_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:
			// MTIOC3A: P14 (LFQFP64: 20) (LFQFP100:  29)
			// MTIOC3A: P17 (LFQFP64: 17) (LFQFP100:  26)
			// MTIOC3A: PC7 (LFQFP64: 27) (LFQFP100:  45)
			// MTIOC3A: PE4 (LFQFP64: 47) (LFQFP100:  74)
			// MTIOC3A: PC1 (LFQFP64: 33) (LFQFP100:  51)
			// MTIOC3A: PF7 (LFQFP64: --) (LFQFP100:  71)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // ok
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;  // ok
					PORTC::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;  // ok
					PORTC::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
					PORTF::PMR.B7 = 0;
					MPC::PF7PFS.PSEL = sel;  // ok
					PORTF::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:
			// MTIOC3B: P17 (LFQFP64: 17) (LFQFP100:  26)
			// MTIOC3B: PB3 (LFQFP64: 36) (LFQFP100:  57)
			// MTIOC3B: PB7 (LFQFP64: 33) (LFQFP100:  53)
			// MTIOC3B: PC5 (LFQFP64: 29) (LFQFP100:  47)
			// MTIOC3B: P22 (LFQFP64: --) (LFQFP100:   8)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // ok
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;  // ok
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:
			// MTIOC3C: P16 (LFQFP64: 18) (LFQFP100:  27)
			// MTIOC3C: PC6 (LFQFP64: 28) (LFQFP100:  46)
			// MTIOC3C: PJ3 (LFQFP64: --) (LFQFP100:   4)
			// MTIOC3C: PC0 (LFQFP64: 34) (LFQFP100:  52)
			// MTIOC3C: PF6 (LFQFP64: --) (LFQFP100:  72)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;  // ok
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTJ::PMR.B3 = 0;
					MPC::PJ3PFS.PSEL = sel;  // ok
					PORTJ::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;  // ok
					PORTC::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTF::PMR.B6 = 0;
					MPC::PF6PFS.PSEL = sel;  // ok
					PORTF::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:
			// MTIOC3D: P16 (LFQFP64: 18) (LFQFP100:  27)
			// MTIOC3D: PB6 (LFQFP64: 34) (LFQFP100:  54)
			// MTIOC3D: PC4 (LFQFP64: 30) (LFQFP100:  48)
			// MTIOC3D: P23 (LFQFP64: --) (LFQFP100:   7)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
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

		static bool mtu4_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:
			// MTIOC4A: PA0 (LFQFP64: 45) (LFQFP100:  70)
			// MTIOC4A: PB3 (LFQFP64: 36) (LFQFP100:  57)
			// MTIOC4A: PE2 (LFQFP64: 49) (LFQFP100:  76)
			// MTIOC4A: P24 (LFQFP64: --) (LFQFP100:   6)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;  // ok
					PORTE::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:
			// MTIOC4B: P30 (LFQFP64:  4) (LFQFP100:  13)
			// MTIOC4B: P54 (LFQFP64: 26) (LFQFP100:  44)
			// MTIOC4B: PC2 (LFQFP64: 32) (LFQFP100:  50)
			// MTIOC4B: PE3 (LFQFP64: 48) (LFQFP100:  75)
			// MTIOC4B: PD1 (LFQFP64: 55) (LFQFP100:  84)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;  // ok
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT5::PMR.B4 = 0;
					MPC::P54PFS.PSEL = sel;  // ok
					PORT5::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;  // ok
					PORTC::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;  // ok
					PORTE::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // ok
					PORTD::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:
			// MTIOC4C: PB1 (LFQFP64: 37) (LFQFP100:  59)
			// MTIOC4C: PE1 (LFQFP64: 50) (LFQFP100:  77)
			// MTIOC4C: PE5 (LFQFP64: 46) (LFQFP100:  73)
			// MTIOC4C: P25 (LFQFP64: --) (LFQFP100:   5)
			// MTIOC4C: P51 (LFQFP64: --) (LFQFP100:  41)
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTB::PMR.B1 = ena;
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
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORT5::PMR.B1 = 0;
					MPC::P51PFS.PSEL = sel;  // ok
					PORT5::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:
			// MTIOC4D: P31 (LFQFP64:  5) (LFQFP100:  14)
			// MTIOC4D: P55 (LFQFP64: 25) (LFQFP100:  43)
			// MTIOC4D: PC3 (LFQFP64: 31) (LFQFP100:  49)
			// MTIOC4D: PE4 (LFQFP64: 47) (LFQFP100:  74)
			// MTIOC4D: PD2 (LFQFP64: 54) (LFQFP100:  83)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;  // ok
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;  // ok
					PORT5::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;  // ok
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;  // ok
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
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

		static bool mtu5_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::U:
			// MTIOC5U: PA4 (LFQFP64: 42) (LFQFP100:  66)
			// MTIOC5U: P11 (LFQFP64: --) (LFQFP100:  36)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;  // ok
					PORT1::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::V:
			// MTIOC5V: PA6 (LFQFP64: 41) (LFQFP100:  63)
			// MTIOC5V: P10 (LFQFP64: --) (LFQFP100:  37)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;  // ok
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;  // ok
					PORT1::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::W:
			// MTIOC5W: PB0 (LFQFP64: 39) (LFQFP100:  61)
			// MTIOC5W: P56 (LFQFP64: --) (LFQFP100:  38)
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT5::PMR.B6 = 0;
					MPC::P56PFS.PSEL = sel;  // ok
					PORT5::PMR.B6 = ena;
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

		static bool clk_a_(ORDER odr, bool ena) noexcept
		{
			// MTCLKA: P14 (LFQFP64: 20) (LFQFP100:  29)
			// MTCLKA: PA4 (LFQFP64: 42) (LFQFP100:  66)
			// MTCLKA: PC6 (LFQFP64: 28) (LFQFP100:  46)
			// MTCLKA: P24 (LFQFP64: --) (LFQFP100:   6)
			uint8_t sel = ena ? 0b0'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = sel;  // ok
				PORT1::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;  // ok
				PORTC::PMR.B6 = ena;
				break;
			case ORDER::FOURTH:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_b_(ORDER odr, bool ena) noexcept
		{
			// MTCLKB: P15 (LFQFP64: 19) (LFQFP100:  28)
			// MTCLKB: PA6 (LFQFP64: 41) (LFQFP100:  63)
			// MTCLKB: PC7 (LFQFP64: 27) (LFQFP100:  45)
			// MTCLKB: P25 (LFQFP64: --) (LFQFP100:   5)
			uint8_t sel = ena ? 0b0'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;  // ok
				PORTA::PMR.B6 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = sel;  // ok
				PORTC::PMR.B7 = ena;
				break;
			case ORDER::FOURTH:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;  // ok
				PORT2::PMR.B5 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_c_(ORDER odr, bool ena) noexcept
		{
			// MTCLKC: PA1 (LFQFP64: 44) (LFQFP100:  69)
			// MTCLKC: PC4 (LFQFP64: 30) (LFQFP100:  48)
			// MTCLKC: P22 (LFQFP64: --) (LFQFP100:   8)
			uint8_t sel = ena ? 0b0'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = sel;  // ok
				PORTA::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = sel;  // ok
				PORTC::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_d_(ORDER odr, bool ena) noexcept
		{
			// MTCLKD: PA3 (LFQFP64: 43) (LFQFP100:  67)
			// MTCLKD: PC5 (LFQFP64: 29) (LFQFP100:  47)
			// MTCLKD: P23 (LFQFP64: --) (LFQFP100:   7)
			uint8_t sel = ena ? 0b0'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = sel;  // ok
				PORTA::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;  // ok
				PORTC::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = ena;
				break;
			default:
				return false;
				break;
			}
			return true;
		}

	public:
		//---------------------------------------------------------------------//
		/*!
			@brief  MTU チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」（RX113 では未サポート）
			@return 無効な周辺機器の場合「false」
		*/
		//---------------------------------------------------------------------//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			if(odr == ORDER::BYPASS) return true;
			if(neg) return false;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::MTU0:
				ret = mtu0_(ch, ena, odr);
				break;
			case peripheral::MTU1:
				ret = mtu1_(ch, ena, odr);
				break;
			case peripheral::MTU2:
				ret = mtu2_(ch, ena, odr);
				break;
			case peripheral::MTU3:
				ret = mtu3_(ch, ena, odr);
				break;
			case peripheral::MTU4:
				ret = mtu4_(ch, ena, odr);
				break;
			case peripheral::MTU5:
				ret = mtu5_(ch, ena, odr);
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//---------------------------------------------------------------------//
		/*!
			@brief  MTU クロックポート切り替え
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」（RX113 では未サポート）
			@return 無効な周辺機器の場合「false」
		*/
		//---------------------------------------------------------------------//
		static bool turn_clock(CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			if(odr == ORDER::BYPASS) return true;
			if(neg) return false;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(ch) {
			case CHANNEL::CLKA:
				ret = clk_a_(odr, ena);
				break;
			case CHANNEL::CLKB:
				ret = clk_b_(odr, ena);
				break;
			case CHANNEL::CLKC:
				ret = clk_c_(odr, ena);
				break;
			case CHANNEL::CLKD:
				ret = clk_d_(odr, ena);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
