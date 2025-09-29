#pragma once
//=========================================================================//
/*!	@file
	@brief	RX660 グループ・ポート・マッピング (MTU3a) @n
			MTU 型に従って、タイマー用ポートを設定 @n
			オーダーの順番は、MPC の端子一覧に準拠している。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX660/peripheral.hpp"
#include "RX660/port.hpp"
#include "RX660/mpc.hpp"
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
			// P34 (LFQFP100:  16) (LFQFP144:  25)
			// PB3 (LFQFP100:  57) (LFQFP144:  82)
			// PC4 (LFQFP100:  48) (LFQFP144:  66)
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
					MPC::PC4PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTC::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC0B:
			// P13 (LFQFP100:  33) (LFQFP144:  44)
			// P15 (LFQFP100:  31) (LFQFP144:  42)
			// PA1 (LFQFP100:  69) (LFQFP144:  96)
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
			// P32 (LFQFP100:  18) (LFQFP144:  27)
			// PB1 (LFQFP100:  59) (LFQFP144:  84)
			// PC5 (LFQFP100:  47) (LFQFP144:  62)
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
					MPC::PC5PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTC::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC0D:
			// P33 (LFQFP100:  17) (LFQFP144:  26)
			// PA3 (LFQFP100:  67) (LFQFP144:  94)
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
			// P20 (LFQFP100:  28) (LFQFP144:  37)
			// PE4 (LFQFP100:  74) (LFQFP144: 107)
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
			// P21 (LFQFP100:  27) (LFQFP144:  36)
			// PB5 (LFQFP100:  55) (LFQFP144:  80)
			// PE3 (LFQFP100:  75) (LFQFP144: 108)
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
				case ORDER::THIRD:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
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
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC2A:
			// P26 (LFQFP100:  22) (LFQFP144:  31)
			// PB5 (LFQFP100:  55) (LFQFP144:  80)
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
			// P27 (LFQFP100:  21) (LFQFP144:  30)
			// PE5 (LFQFP100:  73) (LFQFP144: 106)
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
			// P14 (LFQFP100:  32) (LFQFP144:  43)
			// P17 (LFQFP100:  29) (LFQFP144:  38)
			// PC1 (LFQFP100:  51) (LFQFP144:  73)
			// PC7 (LFQFP100:  45) (LFQFP144:  60)
			// PJ1 (LFQFP100:   6) (LFQFP144:  15)
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
			// P17 (LFQFP100:  29) (LFQFP144:  38)
			// P22 (LFQFP100:  26) (LFQFP144:  35)
			// P80 (LFQFP100: ---) (LFQFP144:  65)
			// PA1 (LFQFP100:  69) (LFQFP144:  96)
			// PB7 (LFQFP100:  53) (LFQFP144:  78)
			// PC5 (LFQFP100:  47) (LFQFP144:  62)
			// PE1 (LFQFP100:  77) (LFQFP144: 110)
			// PH0 (LFQFP100: ---) (LFQFP144:  49)
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
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = ena ? 0b10'0111 : 0;  // ok
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
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::EIGHTH:
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
			// P16 (LFQFP100:  30) (LFQFP144:  40)
			// P56 (LFQFP100: ---) (LFQFP144:  50)
			// PC0 (LFQFP100:  52) (LFQFP144:  75)
			// PC6 (LFQFP100:  46) (LFQFP144:  61)
			// PJ3 (LFQFP100:   4) (LFQFP144:  13)
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
			// P16 (LFQFP100:  30) (LFQFP144:  40)
			// P23 (LFQFP100:  25) (LFQFP144:  34)
			// P81 (LFQFP100: ---) (LFQFP144:  64)
			// PA6 (LFQFP100:  64) (LFQFP144:  89)
			// PB6 (LFQFP100:  54) (LFQFP144:  79)
			// PC4 (LFQFP100:  48) (LFQFP144:  66)
			// PE0 (LFQFP100:  78) (LFQFP144: 111)
			// PH1 (LFQFP100: ---) (LFQFP144:  48)
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
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::SIXTH:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;  // ok
					PORTC::PMR.B4 = ena;
					break;
				case ORDER::SEVENTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTE::PMR.B0 = ena;
					break;
				case ORDER::EIGHTH:
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
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC4A:
			// P21 (LFQFP100:  27) (LFQFP144:  36)
			// P24 (LFQFP100:  24) (LFQFP144:  33)
			// P55 (LFQFP100:  39) (LFQFP144:  51)
			// P82 (LFQFP100: ---) (LFQFP144:  63)
			// PA0 (LFQFP100:  70) (LFQFP144:  97)
			// PB3 (LFQFP100:  57) (LFQFP144:  82)
			// PE2 (LFQFP100:  76) (LFQFP144: 109)
			// PE4 (LFQFP100:  74) (LFQFP144: 107)
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
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
					PORT5::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B2 = ena;
					break;
				case ORDER::FIFTH:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::SIXTH:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::SEVENTH:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;  // ok
					PORTE::PMR.B2 = ena;
					break;
				case ORDER::EIGHTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTE::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC4B:
			// P17 (LFQFP100:  29) (LFQFP144:  38)
			// P30 (LFQFP100:  20) (LFQFP144:  29)
			// P54 (LFQFP100:  40) (LFQFP144:  52)
			// PC2 (LFQFP100:  50) (LFQFP144:  70)
			// PD1 (LFQFP100:  85) (LFQFP144: 125)
			// PE3 (LFQFP100:  75) (LFQFP144: 108)
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
			// P25 (LFQFP100:  23) (LFQFP144:  32)
			// P83 (LFQFP100: ---) (LFQFP144:  58)
			// P87 (LFQFP100: ---) (LFQFP144:  39)
			// PA4 (LFQFP100:  63) (LFQFP144:  92)
			// PB1 (LFQFP100:  59) (LFQFP144:  84)
			// PE1 (LFQFP100:  77) (LFQFP144: 110)
			// PE5 (LFQFP100:  73) (LFQFP144: 106)
			// PH2 (LFQFP100: ---) (LFQFP144:  47)
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
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = ena ? 0b00'0010 : 0;  // ok
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
			case CHANNEL::D:  // MTIOC4D:
			// P31 (LFQFP100:  19) (LFQFP144:  28)
			// P55 (LFQFP100:  39) (LFQFP144:  51)
			// P86 (LFQFP100: ---) (LFQFP144:  41)
			// PA3 (LFQFP100:  67) (LFQFP144:  94)
			// PC3 (LFQFP100:  49) (LFQFP144:  67)
			// PD2 (LFQFP100:  84) (LFQFP144: 124)
			// PE4 (LFQFP100:  74) (LFQFP144: 107)
			// PH3 (LFQFP100: ---) (LFQFP144:  46)
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
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = ena ? 0b10'0111 : 0;  // ok
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;  // ok
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::SIXTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::SEVENTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;  // ok
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::EIGHTH:
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
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::U:  // MTIC5U:
			// P12 (LFQFP100:  34) (LFQFP144:  45)
			// PA4 (LFQFP100:  66) (LFQFP144:  92)
			// PD7 (LFQFP100:  79) (LFQFP144: 119)
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
			// PA3 (LFQFP100:  67) (LFQFP144:  94)
			// PA6 (LFQFP100:  64) (LFQFP144:  89)
			// PD6 (LFQFP100:  80) (LFQFP144: 120)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTA::PMR.B3 = ena;
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
			// PB0 (LFQFP100:  61) (LFQFP144:  87)
			// PD5 (LFQFP100:  81) (LFQFP144: 121)
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

		static bool mtu6_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'0001 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC6A:
			// PE7 (LFQFP100:  71) (LFQFP144: 101)
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTE::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC6B:
			// PA5 (LFQFP100:  65) (LFQFP144:  90)
			// PA6 (LFQFP100:  64) (LFQFP144:  89)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTA::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::C:  // MTIOC6C:
			// PE6 (LFQFP100:  72) (LFQFP144: 102)
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTE::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC6D:
			// PA0 (LFQFP100:  70) (LFQFP144:  97)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = ena ? 0b00'1000 : 0;  // ok
					PORTA::PMR.B0 = ena;
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
			// PA2 (LFQFP100:  68) (LFQFP144:  95)
			// PE2 (LFQFP100:  76) (LFQFP144: 109)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = ena;  // ok
					PORTA::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;  // ok
					PORTE::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // MTIOC7B:
			// PA1 (LFQFP100:  69) (LFQFP144:  96)
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
			// P67 (LFQFP100: ---) (LFQFP144:  98)
			// PA4 (LFQFP100:  66) (LFQFP144:  92)
				switch(odr) {
				case ORDER::FIRST:
					PORT6::PMR.B7 = 0;
					MPC::P67PFS.PSEL = ena;  // ok
					PORT6::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = ena ? 0b10'0111 : 0;  // ok
					PORTA::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::D:  // MTIOC7D:
			// P66 (LFQFP100: ---) (LFQFP144:  99)
			// PE4 (LFQFP100:  74) (LFQFP144: 107)
				switch(odr) {
				case ORDER::FIRST:
					PORT6::PMR.B6 = 0;
					MPC::P66PFS.PSEL = ena;  // ok
					PORT6::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = ena ? 0b10'0111 : 0;  // ok
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

		static bool mtu8_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00'1000 : 0;
			switch(ch) {
			case CHANNEL::A:  // MTIOC8A:
			// PD6 (LFQFP100:  80) (LFQFP144: 120)
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
			// PD4 (LFQFP100:  82) (LFQFP144: 122)
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
			// PD5 (LFQFP100:  81) (LFQFP144: 121)
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
			// PD3 (LFQFP100:  83) (LFQFP144: 123)
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
			// P14 (LFQFP100:  32) (LFQFP144:  43)
			// P24 (LFQFP100:  24) (LFQFP144:  33)
			// PA4 (LFQFP100:  66) (LFQFP144:  92)
			// PC6 (LFQFP100:  46) (LFQFP144:  61)
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
			// P15 (LFQFP100:  31) (LFQFP144:  42)
			// P25 (LFQFP100:  23) (LFQFP144:  32)
			// PA6 (LFQFP100:  64) (LFQFP144:  89)
			// PC7 (LFQFP100:  45) (LFQFP144:  60)
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
			// P22 (LFQFP100:  26) (LFQFP144:  35)
			// PA1 (LFQFP100:  69) (LFQFP144:  96)
			// PC4 (LFQFP100:  48) (LFQFP144:  66)
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
			// P23 (LFQFP100:  25) (LFQFP144:  34)
			// PA3 (LFQFP100:  67) (LFQFP144:  94)
			// PC5 (LFQFP100:  47) (LFQFP144:  62)
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
			@brief  タイマー系、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補を選択する場合
			@param[in]	neg	反転入出力の場合「true」（RX66[01] では未サポート）
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
			@brief  タイマー系、クロックポート切り替え
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」（RX66[01] では未サポート）
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

