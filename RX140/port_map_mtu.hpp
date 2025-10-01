#pragma once
//=========================================================================//
/*!	@file
	@brief	RX140 グループ・ポート・マッピング (MTU2a) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX140/peripheral.hpp"
#include "RX140/port.hpp"
#include "RX140/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_mtu : public port_map_order {

		static bool mtu0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC0A:
			// MTIOC0A: P34 (LFQFP64: --) (LFQFP80: 15)
			// MTIOC0A: PB3 (LFQFP64: 36) (LFQFP80: 45)
			// MTIOC0A: PC4 (LFQFP64: 30) (LFQFP80: 38)
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
				case ORDER::THIRD:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTC::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC0B:
			// MTIOC0B: P13 (LFQFP64: --) (LFQFP80: 27)
			// MTIOC0B: P15 (LFQFP64: 19) (LFQFP80: 25)
			// MTIOC0B: PA1 (LFQFP64: 44) (LFQFP80: 56)
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
			// MTIOC0C: P32 (LFQFP64: 12) (LFQFP80: 16)
			// MTIOC0C: PB1 (LFQFP64: 37) (LFQFP80: 47)
			// MTIOC0C: PC5 (LFQFP64: 29) (LFQFP80: 37)
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
				case ORDER::THIRD:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTC::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC0D:
			// MTIOC0D: PA3 (LFQFP64: 43) (LFQFP80: 54)
				switch(odr) {
				case ORDER::FIRST:
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
			// MTIOC1A: P20 (LFQFP64: --) (LFQFP80: 22)
			// MTIOC1A: PE4 (LFQFP64: 47) (LFQFP80: 59)
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
			// MTIOC1B: P21 (LFQFP64: --) (LFQFP80: 21)
			// MTIOC1B: PB5 (LFQFP64: 35) (LFQFP80: 43)
			// MTIOC1B: PE3 (LFQFP64: 48) (LFQFP80: 60)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = ena ? 0b0001 : 0;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b0010 : 0;  // ok
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = ena ? 0b0010 : 0;  // ok
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

		static bool mtu2_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC2A:
			// MTIOC2A: P26 (LFQFP64: 16) (LFQFP80: 20)
			// MTIOC2A: PB5 (LFQFP64: 35) (LFQFP80: 43)
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
			// MTIOC2B: P27 (LFQFP64: 15) (LFQFP80: 19)
			// MTIOC2B: PE5 (LFQFP64: 46) (LFQFP80: 58)
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
			// MTIOC3A: P14 (LFQFP64: 20) (LFQFP80: 26)
			// MTIOC3A: P17 (LFQFP64: 17) (LFQFP80: 23)
			// MTIOC3A: PC7 (LFQFP64: 27) (LFQFP80: 35)
			// MTIOC3A: PJ1 (LFQFP64: --) (LFQFP80:  5)
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
			// MTIOC3B: P17 (LFQFP64: 17) (LFQFP80: 23)
			// MTIOC3B: PA1 (LFQFP64: 44) (LFQFP80: 56)
			// MTIOC3B: PB7 (LFQFP64: 33) (LFQFP80: 41)
			// MTIOC3B: PC5 (LFQFP64: 29) (LFQFP80: 37)
			// MTIOC3B: PH0 (LFQFP64: 24) (LFQFP80: 32)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTA::PMR.B1 = ena;
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
					PORTH::PMR.B0 = 0;
					MPC::PH0PFS.PSEL = sel;  // ok
					PORTH::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC3C:
			// MTIOC3C: P16 (LFQFP64: 18) (LFQFP80: 24)
			// MTIOC3C: PC6 (LFQFP64: 28) (LFQFP80: 36)
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
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC3D:
			// MTIOC3D: P16 (LFQFP64: 18) (LFQFP80: 24)
			// MTIOC3D: PA6 (LFQFP64: 41) (LFQFP80: 51)
			// MTIOC3D: PB0 (LFQFP64: 39) (LFQFP80: 49)
			// MTIOC3D: PB6 (LFQFP64: 34) (LFQFP80: 42)
			// MTIOC3D: PC4 (LFQFP64: 30) (LFQFP80: 38)
			// MTIOC3D: PH1 (LFQFP64: 23) (LFQFP80: 31)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = ena ? 0b0'0010 : 0;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = ena;
					break;
				case ORDER::SIXTH:
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
			// MTIOC4A: P55 (LFQFP64: 25) (LFQFP80: 33)
			// MTIOC4A: PA0 (LFQFP64: 45) (LFQFP80: 57)
			// MTIOC4A: PB3 (LFQFP64: 36) (LFQFP80: 45)
			// MTIOC4A: PE2 (LFQFP64: 49) (LFQFP80: 61)
			// MTIOC4A: PE4 (LFQFP64: 47) (LFQFP80: 59)
				switch(odr) {
				case ORDER::FIRST:
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = ena ? 0b0'0010 : 0;  // OK
					PORT5::PMR.B5 = ena;
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
				case ORDER::FIFTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC4B:
			// MTIOC4B: P30 (LFQFP64: 14) (LFQFP80: 18)
			// MTIOC4B: P54 (LFQFP64: 26) (LFQFP80: 34)
			// MTIOC4B: PC2 (LFQFP64: 32) (LFQFP80: 40)
			// MTIOC4B: PD1 (LFQFP64: --) (LFQFP80: 65)
			// MTIOC4B: PE3 (LFQFP64: 48) (LFQFP80: 60)
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
			// MTIOC4C: PA4 (LFQFP64: 42) (LFQFP80: 53)
			// MTIOC4C: PB1 (LFQFP64: 37) (LFQFP80: 47)
			// MTIOC4C: PE1 (LFQFP64: 50) (LFQFP80: 62)
			// MTIOC4C: PE5 (LFQFP64: 46) (LFQFP80: 58)
			// MTIOC4C: PH2 (LFQFP64: 22) (LFQFP80: 30)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTA::PMR.B4 = ena;
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
				case ORDER::FIFTH:
					PORTH::PMR.B2 = 0;
					MPC::PH2PFS.PSEL = sel;  // ok
					PORTH::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC4D:
			// MTIOC4D: P31 (LFQFP64: 13) (LFQFP80: 17)
			// MTIOC4D: P55 (LFQFP64: 25) (LFQFP80: 33)
			// MTIOC4D: PA3 (LFQFP64: 43) (LFQFP80: 54)
			// MTIOC4D: PC3 (LFQFP64: 31) (LFQFP80: 39)
			// MTIOC4D: PD2 (LFQFP64: --) (LFQFP80: 64)
			// MTIOC4D: PE4 (LFQFP64: 47) (LFQFP80: 59)
			// MTIOC4D: PH3 (LFQFP64: 21) (LFQFP80: 29)
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
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = ena ? 0b0'0011 : 0;  // ok
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;  // ok
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;  // ok
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::SEVENTH:
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

		static bool mtu5_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0001 : 0;
			switch(ch) {
			case CHANNEL::U:  // MTIOC5U:
			// MTIOC5U: PA4 (LFQFP64: 42) (LFQFP80: 53)
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
			case CHANNEL::V: // MTIOC5V:
			// MTIOC5V: PA3 (LFQFP64: 43) (LFQFP80: 54)
			// MTIOC5V: PA6 (LFQFP64: 41) (LFQFP80: 51)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = sel;  // ok
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;  // ok
					PORTA::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::W: // MTIOC5W:
			// MTIOC5W: PB0 (LFQFP64: 39) (LFQFP80: 49)
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

		static bool clk_a_(ORDER odr, bool ena) noexcept
		{
			// MTCLKA: P14 (LFQFP64: 20) (LFQFP80: 26)
			// MTCLKA: PA4 (LFQFP64: 42) (LFQFP80: 53)
			// MTCLKA: PC6 (LFQFP64: 28) (LFQFP80: 36)
			uint8_t sel = ena ? 0b00010 : 0;
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
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_b_(ORDER odr, bool ena) noexcept
		{
			// MTCLKB: P15 (LFQFP64: 19) (LFQFP80: 25)
			// MTCLKB: PA6 (LFQFP64: 41) (LFQFP80: 51)
			// MTCLKB: PC7 (LFQFP64: 27) (LFQFP80: 35)
			uint8_t sel = ena ? 0b00010 : 0;
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
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_c_(ORDER odr, bool ena) noexcept
		{
			// MTCLKC: PA1 (LFQFP64: 44) (LFQFP80: 56)
			// MTCLKC: PC4 (LFQFP64: 30) (LFQFP80: 38)
			uint8_t sel = ena ? 0b00010 : 0;
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
			default:
				return false;
				break;
			}
			return true;
		}

		static bool clk_d_(ORDER odr, bool ena) noexcept
		{
			// MTCLKD: PA3 (LFQFP64: 43) (LFQFP80: 54)
			// MTCLKD: PC5 (LFQFP64: 29) (LFQFP80: 37)
			uint8_t sel = ena ? 0b00010 : 0;
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
			default:
				return false;
				break;
			}
			return true;
		}

	public:
		//---------------------------------------------------------------------//
		/*!
			@brief  MTU2 関係、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」（RX140 は未サポート）
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
			@param[in]	neg	反転入出力の場合「true」（RX140 は未サポート）
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
