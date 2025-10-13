#pragma once
//=========================================================================//
/*!	@file
	@brief	RX130 グループ・ポート・マッピング (MTU2a) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX130/peripheral.hpp"
#include "RX140/port.hpp"
#include "RX130/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX130/MTU ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {

		static bool mtu0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC0A:
			// P34 (LFQFP64: --) (LFQFP100:  16)
			// PB3 (LFQFP64: 36) (LFQFP100:  57)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;  // ok
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;  // ok
					PORTB::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC0B:
			// P13 (LFQFP64: --) (LFQFP100:  33)
			// P15 (LFQFP64: 19) (LFQFP100:  31)
			// PA1 (LFQFP64: 44) (LFQFP100:  69)
				switch(odr) {
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
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC0C:
			// P32 (LFQFP64: 12) (LFQFP100:  18)
			// PB1 (LFQFP64: 37) (LFQFP100:  59)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B2 = ena;
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
			case CHANNEL::D:  // MTIOC0D:
			// P33 (LFQFP64: --) (LFQFP100:  17)
			// PA3 (LFQFP64: 43) (LFQFP100:  67)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = ena;
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
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool mtu1_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			switch(ch) {
			case CHANNEL::A:  // MTIOC1A:
			// P20 (LFQFP64: --) (LFQFP100:  28)
			// PE4 (LFQFP64: 47) (LFQFP100:  74)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = ena ? 0b0'0001 : 0;  // ok
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC1B:
			// P21 (LFQFP64: --) (LFQFP100:  27)
			// PB5 (LFQFP64: 35) (LFQFP100:  55)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = ena ? 0b0'0001 : 0;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
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

		static bool mtu2_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC2A:
			// P26 (LFQFP64: 16) (LFQFP100:  22)
			// PB5 (LFQFP64: 35) (LFQFP100:  55)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;  // ok
					PORT2::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // ok
					PORTB::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC2B:
			// P27 (LFQFP64: 15) (LFQFP100:  21)
			// PE5 (LFQFP64: 46) (LFQFP100:  73)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
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

		static bool mtu3_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC3A:
			// P14 (LFQFP64: 20) (LFQFP100:  32)
			// P17 (LFQFP64: 17) (LFQFP100:  29)
			// PC1 (LFQFP64: 33) (LFQFP100:  51)
			// PC7 (LFQFP64: 27) (LFQFP100:  45)
			// PJ1 (LFQFP64: --) (LFQFP100:   6)
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
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = sel;  // ok
					PORTC::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;  // ok
					PORTC::PMR.B7 = ena;
					break;
				case ORDER::FIFTH:
					PORTJ::PMR.B1 = 0;
					MPC::PJ1PFS.PSEL = sel;  // ok
					PORTJ::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC3B:
			// P17 (LFQFP64: 17) (LFQFP100:  29)
			// P22 (LFQFP64: --) (LFQFP100:  26)
			// PB7 (LFQFP64: 33) (LFQFP100:  53)
			// PC5 (LFQFP64: 29) (LFQFP100:  47)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
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
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC3C:
			// P16 (LFQFP64: 18) (LFQFP100:  30)
			// PC0 (LFQFP64: 34) (LFQFP100:  52)
			// PC6 (LFQFP64: 28) (LFQFP100:  46)
			// PJ3 (LFQFP64: --) (LFQFP100:   4)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;  // ok
					PORTC::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;  // ok
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORTJ::PMR.B3 = 0;
					MPC::PJ3PFS.PSEL = sel;  // ok
					PORTJ::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC3D:
			// P16 (LFQFP64: 18) (LFQFP100:  30)
			// P23 (LFQFP64: --) (LFQFP100:  25)
			// PB6 (LFQFP64: 34) (LFQFP100:  54)
			// PC4 (LFQFP64: 30) (LFQFP100:  48)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
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

		static bool mtu4_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC4A:
			// P24 (LFQFP64: --) (LFQFP100:  24)
			// PA0 (LFQFP64: 45) (LFQFP100:  70)
			// PB3 (LFQFP64: 36) (LFQFP100:  57)
			// PE2 (LFQFP64: 49) (LFQFP100:  76)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;  // ok
					PORTE::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC4B:
			// P30 (LFQFP64: 14) (LFQFP100:  20)
			// P54 (LFQFP64: 26) (LFQFP100:  40)
			// PC2 (LFQFP64: 32) (LFQFP100:  50)
			// PD1 (LFQFP64: --) (LFQFP100:  85)
			// PE3 (LFQFP64: 48) (LFQFP100:  75)
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
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // ok
					PORTD::PMR.B1 = ena;
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
			case CHANNEL::C:  // MTIOC4C:
			// P25 (LFQFP64: --) (LFQFP100:  23)
			// PB1 (LFQFP64: 37) (LFQFP100:  59)
			// PE1 (LFQFP64: 50) (LFQFP100:  77)
			// PE5 (LFQFP64: 46) (LFQFP100:  73)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;  // ok
					PORTE::PMR.B1 = ena;
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
			case CHANNEL::D:  // MTIOC4D:
			// P31 (LFQFP64: 13) (LFQFP100:  19)
			// P55 (LFQFP64: 25) (LFQFP100:  39)
			// PC3 (LFQFP64: 31) (LFQFP100:  49)
			// PD2 (LFQFP64: --) (LFQFP100:  84)
			// PE4 (LFQFP64: 47) (LFQFP100:  74)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;  // ok
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORT5::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;  // ok
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;  // ok
					PORTE::PMR.B4 = ena;
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
			case CHANNEL::U:  // MTIOC5U:
			// PA4 (LFQFP64: 42) (LFQFP100:  66)
			// PD7 (LFQFP64: --) (LFQFP100:  79)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // ok
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::V:  // MTIOC5V:
			// PA6 (LFQFP64: 41) (LFQFP100:  64)
			// PD6 (LFQFP64: --) (LFQFP100:  80)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;  // ok
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // ok
					PORTD::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::W:  // MTIOC5W:
			// PB0 (LFQFP64: 39) (LFQFP100:  61)
			// PD5 (LFQFP64: --) (LFQFP100:  81)
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;  // ok
					PORTD::PMR.B5 = ena;
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
			// MTCLKA:
			// P14 (LFQFP64: 20) (LFQFP100:  32)
			// P24 (LFQFP64: --) (LFQFP100:  24)
			// PA4 (LFQFP64: 42) (LFQFP100:  66)
			// PC6 (LFQFP64: 28) (LFQFP100:  46)
			uint8_t sel = ena ? 0b0'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = sel;  // ok
				PORT1::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = sel;  // ok
				PORTA::PMR.B4 = ena;
				break;
			case ORDER::FOURTH:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = sel;  // ok
				PORTC::PMR.B6 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool clk_b_(ORDER odr, bool ena) noexcept
		{
			// MTCLKB:
			// P15 (LFQFP64: 19) (LFQFP100:  31)
			// P25 (LFQFP64: --) (LFQFP100:  23)
			// PA6 (LFQFP64: 41) (LFQFP100:  64)
			// PC7 (LFQFP64: 27) (LFQFP100:  45)
			uint8_t sel = ena ? 0b0'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = sel;  // ok
				PORT1::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;  // ok
				PORT2::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = sel;  // ok
				PORTA::PMR.B6 = ena;
				break;
			case ORDER::FOURTH:
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = sel;  // ok
				PORTC::PMR.B7 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool clk_c_(ORDER odr, bool ena) noexcept
		{
			// MTCLKC:
			// P22 (LFQFP64: --) (LFQFP100:  26)
			// PA1 (LFQFP64: 44) (LFQFP100:  69)
			// PC4 (LFQFP64: 30) (LFQFP100:  48)
			uint8_t sel = ena ? 0b0'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel;  // ok
				PORT2::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = sel;  // ok
				PORTA::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = sel;  // ok
				PORTC::PMR.B4 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool clk_d_(ORDER odr, bool ena) noexcept
		{
			// MTCLKD:
			// P23 (LFQFP64: --) (LFQFP100:  25)
			// PA3 (LFQFP64: 43) (LFQFP100:  67)
			// PC5 (LFQFP64: 29) (LFQFP100:  47)
			uint8_t sel = ena ? 0b0'0010 : 0;
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = sel;  // ok
				PORTA::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = sel;  // ok
				PORTC::PMR.B5 = ena;
				break;
			default:
				return false;
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
			@param[in]	neg	反転入出力の場合「true」（RX130 では未サポート）
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
			@param[in]	neg	反転入出力の場合「true」（RX130 では未サポート）
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
