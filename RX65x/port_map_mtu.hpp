#pragma once
//=========================================================================//
/*!	@file
	@brief	RX651/RX65N グループ・ポート・マッピング (MTU3a) @n
			・MTU 型に従って、タイマー用ポートを設定 @n
			MTU0, MTU1, MTU2, MTU3, MTU4, MTU5, MTU6, MTU7, MTU8
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX65x/peripheral.hpp"
#include "RX64M/port.hpp"
#include "RX65x/mpc.hpp"
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
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC0A:
			// P34 (LFQFP100:  16) (LFQFP144:  25) (LFQFP176:  27)
			// PB3 (LFQFP100:  57) (LFQFP144:  82) (LFQFP176:  98)
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
			// P13 (LFQFP100:  33) (LFQFP144:  44) (LFQFP176:  52)
			// P15 (LFQFP100:  31) (LFQFP144:  42) (LFQFP176:  50)
			// PA1 (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
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
			// P32 (LFQFP100:  18) (LFQFP144:  27) (LFQFP176:  29)
			// PB1 (LFQFP100:  59) (LFQFP144:  84) (LFQFP176: 100)
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
			// P33 (LFQFP100:  17) (LFQFP144:  26) (LFQFP176:  28)
			// PA3 (LFQFP100:  67) (LFQFP144:  94) (LFQFP176: 110)
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
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC1A:
			// P20 (LFQFP100:  28) (LFQFP144:  37) (LFQFP176:  45)
			// PE4 (LFQFP100:  74) (LFQFP144: 107) (LFQFP176: 131)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC1B:
			// P21 (LFQFP100:  27) (LFQFP144:  36) (LFQFP176:  44)
			// PB5 (LFQFP100:  55) (LFQFP144:  80) (LFQFP176:  96)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
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
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC2A:
			// P26 (LFQFP100:  22) (LFQFP144:  31) (LFQFP176:  37)
			// PB5 (LFQFP100:  55) (LFQFP144:  80) (LFQFP176:  96)
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
			// P27 (LFQFP100:  21) (LFQFP144:  30) (LFQFP176:  36)
			// PE5 (LFQFP100:  73) (LFQFP144: 106) (LFQFP176: 130)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;  // ok
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
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
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC3A:
			// P14 (LFQFP100:  32) (LFQFP144:  43) (LFQFP176:  51) 
			// P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
			// PC1 (LFQFP100:  51) (LFQFP144:  73) (LFQFP176:  89)
			// PC7 (LFQFP100:  45) (LFQFP144:  60) (LFQFP176:  76)
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
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC3B:
			// P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
			// P22 (LFQFP100:  26) (LFQFP144:  35) (LFQFP176:  43)
			// P80 (LFQFP100: ---) (LFQFP144:  65) (LFQFP176:  81)
			// PB7 (LFQFP100:  53) (LFQFP144:  78) (LFQFP176:  94)
			// PC5 (LFQFP100:  47) (LFQFP144:  62) (LFQFP176:  78)
			// PE1 (LFQFP100:  77) (LFQFP144: 110) (LFQFP176: 134)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;  // ok
					PORT8::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // ok
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;  // ok
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTE::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC3C:
			// P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
			// P56 (LFQFP100: ---) (LFQFP144:  50) (LFQFP176:  64)
			// PC0 (LFQFP100:  52) (LFQFP144:  75) (LFQFP176:  91)
			// PC6 (LFQFP100:  46) (LFQFP144:  61) (LFQFP176:  77)
			// PJ3 (LFQFP100:   4) (LFQFP144:  13) (LFQFP176:  13)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT5::PMR.B6 = 0;
					MPC::P56PFS.PSEL = sel;  // ok
					PORT5::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B0 = 0;
					MPC::PC0PFS.PSEL = sel;  // ok
					PORTC::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;  // ok
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
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
			// P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
			// P23 (LFQFP100:  25) (LFQFP144:  34) (LFQFP176:  42)
			// P81 (LFQFP100: ---) (LFQFP144:  64) (LFQFP176:  80)
			// PC4 (LFQFP100:  48) (LFQFP144:  66) (LFQFP176:  82)
			// PB6 (LFQFP100:  54) (LFQFP144:  79) (LFQFP176:  95)
			// PE0 (LFQFP100:  78) (LFQFP144: 111) (LFQFP176: 135)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;  // ok
					PORT8::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::SIXTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTE::PMR.B0 = ena;
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
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC4A:
			// P21 (LFQFP100:  27) (LFQFP144:  36) (LFQFP176:  44)
			// P24 (LFQFP100:  24) (LFQFP144:  33) (LFQFP176:  40)
			// P82 (LFQFP100: ---) (LFQFP144:  63) (LFQFP176:  79)
			// PA0 (LFQFP100:  70) (LFQFP144:  97) (LFQFP176: 118)
			// PB3 (LFQFP100:  57) (LFQFP144:  82) (LFQFP176:  98)
			// PE2 (LFQFP100:  76) (LFQFP144: 109) (LFQFP176: 133)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::SIXTH:
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
			// P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
			// P30 (LFQFP100:  20) (LFQFP144:  29) (LFQFP176:  33)
			// P54 (LFQFP100:  40) (LFQFP144:  52) (LFQFP176:  66)
			// PC2 (LFQFP100:  50) (LFQFP144:  70) (LFQFP176:  86)
			// PD1 (LFQFP100:  85) (LFQFP144: 125) (LFQFP176: 156)
			// PE3 (LFQFP100:  75) (LFQFP144: 108) (LFQFP176: 132)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORT1::PMR.B7 = ena;
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
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;  // ok
					PORTC::PMR.B2 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // ok
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
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
			// P25 (LFQFP100:  23) (LFQFP144:  32) (LFQFP176:  38)
			// P83 (LFQFP100: ---) (LFQFP144:  58) (LFQFP176:  74)
			// P87 (LFQFP100: ---) (LFQFP144:  39) (LFQFP176:  47)
			// PB1 (LFQFP100:  59) (LFQFP144:  84) (LFQFP176: 100)
			// PE1 (LFQFP100:  77) (LFQFP144: 110) (LFQFP176: 134)
			// PE5 (LFQFP100:  73) (LFQFP144: 106) (LFQFP176: 130)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;  // ok
					PORT2::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B3 = 0;
					MPC::P83PFS.PSEL = sel;  // ok
					PORT8::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
					PORT8::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;  // ok
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
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
			// P31 (LFQFP100:  19) (LFQFP144:  28) (LFQFP176:  32)
			// P55 (LFQFP100:  39) (LFQFP144:  51) (LFQFP176:  65)
			// P86 (LFQFP100: ---) (LFQFP144:  41) (LFQFP176:  49)
			// PC3 (LFQFP100:  49) (LFQFP144:  67) (LFQFP176:  83)
			// PD2 (LFQFP100:  84) (LFQFP144: 124) (LFQFP176: 154)
			// PE4 (LFQFP100:  74) (LFQFP144: 107) (LFQFP176: 131)
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
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
					PORT8::PMR.B6 = ena;
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
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::U:  // MTIC5U:
			// P12 (LFQFP100:  34) (LFQFP144:  45) (LFQFP176:  53)
			// PA4 (LFQFP100:  66) (LFQFP144:  92) (LFQFP176: 109)
			// PD7 (LFQFP100:  79) (LFQFP144: 119) (LFQFP176: 143)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;  // ok
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = ena;
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
			case CHANNEL::V:  // MTIC5V:
			// P11 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  67)
			// PA6 (LFQFP100:  64) (LFQFP144:  89) (LFQFP176: 107)
			// PD6 (LFQFP100:  80) (LFQFP144: 120) (LFQFP176: 145)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;  // ok
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;  // ok
					PORTA::PMR.B6 = ena;
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
			case CHANNEL::W:  // MTIC5W:
			// P10 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  68)
			// PB0 (LFQFP100:  61) (LFQFP144:  87) (LFQFP176: 104)
			// PD5 (LFQFP100:  81) (LFQFP144: 121) (LFQFP176: 147)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;  // ok
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
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

		static bool mtu6_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC6A:
			// PE7 (LFQFP100:  71) (LFQFP144: 101) (LFQFP176: 125)
			// PJ1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  59)
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTE::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTJ::PMR.B1 = 0;
					MPC::PJ1PFS.PSEL = sel;  // ok
					PORTJ::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC6B:
			// PA5 (LFQFP100:  65) (LFQFP144:  90) (LFQFP176: 108)
			// PJ0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  60)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTJ::PMR.B0 = 0;
					MPC::PJ0PFS.PSEL = sel;  // ok
					PORTJ::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC6C:
			// PE6 (LFQFP100:  72) (LFQFP144: 102) (LFQFP176: 126)
			// P85 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  61)
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTE::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B5 = 0;
					MPC::P85PFS.PSEL = sel;  // ok
					PORT8::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC6D:
			// PA0 (LFQFP100:  70) (LFQFP144:  97) (LFQFP176: 118)
			// P84 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  62)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B4 = 0;
					MPC::P84PFS.PSEL = sel;  // ok
					PORT8::PMR.B4 = ena;
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

		static bool mtu7_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'1000 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC7A:
			// PA2 (LFQFP100:  68) (LFQFP144:  95) (LFQFP176: 112)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = ena;  // ok
					PORTA::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC7B:
			// PA1 (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena;  // ok
					PORTA::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC7C:
			// P67 (LFQFP100: ---) (LFQFP144:  98) (LFQFP176: 120)
				switch(odr) {
				case ORDER::FIRST:
					PORT6::PMR.B7 = 0;
					MPC::P67PFS.PSEL = ena;  // ok
					PORT6::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC7D:
			// P66 (LFQFP100: ---) (LFQFP144:  99) (LFQFP176: 122)
				switch(odr) {
				case ORDER::FIRST:
					PORT6::PMR.B6 = 0;
					MPC::P66PFS.PSEL = ena;  // ok
					PORT6::PMR.B6 = ena;
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

		static bool mtu8_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'1000 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC8A:
			// PD6 (LFQFP100:  80) (LFQFP144: 120) (LFQFP176: 145)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // ok
					PORTD::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC8B:
			// PD4 (LFQFP100:  82) (LFQFP144: 122) (LFQFP176: 148)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;  // ok
					PORTD::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC8C:
			// PD5 (LFQFP100:  81) (LFQFP144: 121) (LFQFP176: 147)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;  // ok
					PORTD::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC8D:
			// PD3 (LFQFP100:  83) (LFQFP144: 123) (LFQFP176: 150)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // ok
					PORTD::PMR.B3 = ena;
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
			// P14 (LFQFP100:  32) (LFQFP144:  43) (LFQFP176:  51)
			// P24 (LFQFP100:  24) (LFQFP144:  33) (LFQFP176:  40)
			// PA4 (LFQFP100:  66) (LFQFP144:  92) (LFQFP176: 109)
			// PC6 (LFQFP100:  46) (LFQFP144:  61) (LFQFP176:  77)
			uint8_t sel = ena ? 0b00'0010 : 0;
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
				break;
			}
			return true;
		}

		static bool clk_b_(ORDER odr, bool ena) noexcept
		{
			// MTCLKB:
			// P15 (LFQFP100:  31) (LFQFP144:  42) (LFQFP176:  50)
			// P25 (LFQFP100:  23) (LFQFP144:  32) (LFQFP176:  38)
			// PA6 (LFQFP100:  64) (LFQFP144:  89) (LFQFP176: 107)
			// PC7 (LFQFP100:  45) (LFQFP144:  60) (LFQFP176:  76)
			uint8_t sel = ena ? 0b00'0010 : 0;
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
			case ORDER::FIFTH:
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
			// MTCLKC:
			// P22 (LFQFP100:  26) (LFQFP144:  35) (LFQFP176:  43)
			// PA1 (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
			// PC4 (LFQFP100:  48) (LFQFP144:  66) (LFQFP176:  82)
			uint8_t sel = ena ? 0b00'0010 : 0;
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
				break;
			}
			return true;
		}

		static bool clk_d_(ORDER odr, bool ena) noexcept
		{
			// MTCLKD:
			// P23 (LFQFP100:  25) (LFQFP144:  34) (LFQFP176:  42)
			// PA3 (LFQFP100:  67) (LFQFP144:  94) (LFQFP176: 110)
			// PC5 (LFQFP100:  47) (LFQFP144:  62) (LFQFP176:  78)
			uint8_t sel = ena ? 0b00'0010 : 0;
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
				break;
			}
			return true;
		}

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MTU チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補を選択する場合
			@param[in]	neg	反転入出力の場合「true」（RX65x では未サポート）
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
			case peripheral::MTU6:
				ret = mtu6_(ch, ena, odr);
				break;
			case peripheral::MTU7:
				ret = mtu7_(ch, ena, odr);
				break;
			case peripheral::MTU8:
				ret = mtu8_(ch, ena, odr);
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
			@param[in]	neg	反転入出力の場合「true」（RX65x では未サポート）
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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

