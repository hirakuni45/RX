#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66N/RX72N/RX72M グループ・ポート・マッピング (GPTW0 - GPTW3) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#if defined(SIG_RX66N)
#include "RX66N/peripheral.hpp"
#include "RX66N/port.hpp"
#include "RX66N/mpc.hpp"
#elif defined(SIG_RX72N)
#include "RX72N/peripheral.hpp"
#include "RX72N/port.hpp"
#include "RX72N/mpc.hpp"
#elif defined(SIG_RX72M)
#include "RX72M/peripheral.hpp"
#include "RX72N/port.hpp"
#include "RX72M/mpc.hpp"
#endif
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTW ポート・マッピング
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_gptw : public port_map_order {

		static bool gptw0_(CHANNEL ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC0A:
			// P23 (LFQFP100:  25) (LFQFP144:  34) (LFQFP176:  42)
			// P83 (LFQFP100: ---) (LFQFP144:  58) (LFQFP176:  74)
			// PA5 (LFQFP100:  65) (LFQFP144:  90) (LFQFP176: 108)
			// PD3 (LFQFP100:  83) (LFQFP144: 123) (LFQFP176: 150)
			// PE5 (LFQFP100:  73) (LFQFP144: 106) (LFQFP176: 130)
			// PH6 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B3 = 0;
					MPC::P83PFS.PSEL = sel;
					PORT8::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;
					PORTD::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;
					PORTE::PMR.B5 = ena;
					break;
				case ORDER::SIXTH:
					PORTH::PMR.B6 = 0;
					MPC::PH6PFS.PSEL = sel;
					PORTH::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC0B:
			// P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
			// P81 (LFQFP100: ---) (LFQFP144:  64) (LFQFP176:  80)
			// PA0 (LFQFP100:  70) (LFQFP144:  97) (LFQFP176: 118)
			// PD2 (LFQFP100:  84) (LFQFP144: 124) (LFQFP176: 154)
			// PE2 (LFQFP100:  76) (LFQFP144: 109) (LFQFP176: 133)
			// PH7 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
				switch(opt) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;
					PORT8::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;
					PORTE::PMR.B2 = ena;
					break;
				case ORDER::SIXTH:
					PORTH::PMR.B6 = 0;
					MPC::PH6PFS.PSEL = sel;
					PORTH::PMR.B6 = ena;
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

		static bool gptw1_(CHANNEL ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC1A:
			// P22 (LFQFP100:  26) (LFQFP144:  35) (LFQFP176:  43)
			// PA2 (LFQFP100:  68) (LFQFP144:  95) (LFQFP176: 112)
			// PC5 (LFQFP100:  47) (LFQFP144:  62) (LFQFP176:  78)
			// PD1 (LFQFP100:  85) (LFQFP144: 125) (LFQFP176: 156)
			// PE4 (LFQFP100:  74) (LFQFP144: 107) (LFQFP176: 131)
			// PK6 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;
					PORTA::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;
					PORTD::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;
					PORTE::PMR.B4 = ena;
					break;
				case ORDER::SIXTH:
					PORTK::PMR.B6 = 0;
					MPC::PK6PFS.PSEL = sel;
					PORTK::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC1B:
			// P67 (LFQFP100: ---) (LFQFP144:  98) (LFQFP176: 120)
			// P87 (LFQFP100: ---) (LFQFP144:  39) (LFQFP176:  47)
			// PC3 (LFQFP100:  49) (LFQFP144:  67) (LFQFP176:  83)
			// PD0 (LFQFP100:  86) (LFQFP144: 126) (LFQFP176: 158)
			// PE1 (LFQFP100:  77) (LFQFP144: 110) (LFQFP176: 134)
			// PK7 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
				switch(opt) {
				case ORDER::FIRST:
					PORT6::PMR.B7 = 0;
					MPC::P67PFS.PSEL = sel;
					PORT6::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = sel;
					PORT8::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::SIXTH:
					PORTK::PMR.B7 = 0;
					MPC::PK7PFS.PSEL = sel;
					PORTK::PMR.B7 = ena;
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

		static bool gptw2_(CHANNEL ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC2A:
			// P21 (LFQFP100:  27) (LFQFP144:  36) (LFQFP176:  44)
			// P82 (LFQFP100: ---) (LFQFP144:  63) (LFQFP176:  79)
			// PA1 (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
			// PE3 (LFQFP100:  75) (LFQFP144: 108) (LFQFP176: 132)
			// PL6 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
				switch(opt) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;
					PORT8::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;
					PORTE::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTL::PMR.B6 = 0;
					MPC::PL6PFS.PSEL = sel;
					PORTL::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC2B:
			// P66 (LFQFP100: ---) (LFQFP144:  99) (LFQFP176: 122)
			// P86 (LFQFP100: ---) (LFQFP144:  41) (LFQFP176:  49)
			// PC2 (LFQFP100:  50) (LFQFP144:  70) (LFQFP176:  86)
			// PE0 (LFQFP100:  78) (LFQFP144: 111) (LFQFP176: 135)
			// PL7 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
				switch(opt) {
				case ORDER::FIRST:
					PORT6::PMR.B6 = 0;
					MPC::P66PFS.PSEL = sel;
					PORT6::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = sel;
					PORT8::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;
					PORTC::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;
					PORTE::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTL::PMR.B7 = 0;
					MPC::PL7PFS.PSEL = sel;
					PORTL::PMR.B7 = ena;
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

		static bool gptw3_(CHANNEL ch, bool ena, ORDER opt) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC3A:
			// PC7 (LFQFP100:  45) (LFQFP144:  60) (LFQFP176:  76)
			// PE7 (LFQFP100:  71) (LFQFP144: 101) (LFQFP176: 125)
			// PM6 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
				switch(opt) {
				case ORDER::FIRST:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = sel;
					PORTE::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORTM::PMR.B6 = 0;
					MPC::PM6PFS.PSEL = sel;
					PORTM::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC3B:
			// PC6 (LFQFP100:  46) (LFQFP144:  61) (LFQFP176:  77)
			// PE6 (LFQFP100:  72) (LFQFP144: 102) (LFQFP176: 126)
			// PM7 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
				switch(opt) {
				case ORDER::FIRST:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = sel;
					PORTE::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTM::PMR.B7 = 0;
					MPC::PM7PFS.PSEL = sel;
					PORTM::PMR.B7 = ena;
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

		static bool dsm_0_(ORDER odr, bool ena) noexcept
		{
			// GTADSM0:
			// P12 (LFQFP100:  34) (LFQFP144:  45) (LFQFP176:  53)
			// PH4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PK4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PL4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PM4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B2 = 0;
				MPC::P12PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORT1::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B4 = 0;
				MPC::PH4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B4 = 0;
				MPC::PK4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B4 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B4 = 0;
				MPC::PL4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B4 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B4 = 0;
				MPC::PM4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B4 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool dsm_1_(ORDER odr, bool ena) noexcept
		{
			// GTADSM1:
			// P13 (LFQFP100:  33) (LFQFP144:  44) (LFQFP176:  52)
			// PH5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PK5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PL5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PM5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B3 = 0;
				MPC::P13PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORT1::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B5 = 0;
				MPC::PH5PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B5 = 0;
				MPC::PK5PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B5 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B5 = 0;
				MPC::PL5PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B5 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B5 = 0;
				MPC::PM5PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B5 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool trg_a_(ORDER odr, bool ena) noexcept
		{
			// GTETRGA:
			// P15 (LFQFP100:  31) (LFQFP144:  42) (LFQFP176:  50)
			// PH0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PK0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PL0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PM0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORT1::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B0 = 0;
				MPC::PH0PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B0 = 0;
				MPC::PK0PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B0 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B0 = 0;
				MPC::PL0PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B0 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B0 = 0;
				MPC::PM0PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B0 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool trg_b_(ORDER odr, bool ena) noexcept
		{
			// GTETRGB:
			// PA6 (LFQFP100:  64) (LFQFP144:  89) (LFQFP176: 107)
			// PH1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PK1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PL1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PM1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			switch(odr) {
			case ORDER::FIRST:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTA::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B1 = 0;
				MPC::PH1PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B1 = 0;
				MPC::PK1PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B1 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B1 = 0;
				MPC::PL1PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B1 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B1 = 0;
				MPC::PM1PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B1 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool trg_c_(ORDER odr, bool ena) noexcept
		{
			// GTETRGC:
			// PC4 (LFQFP100:  48) (LFQFP144:  66) (LFQFP176:  82)
			// PH2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PK2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PL2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PM2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			switch(odr) {
			case ORDER::FIRST:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTC::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B2 = 0;
				MPC::PH2PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B2 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B2 = 0;
				MPC::PK2PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B2 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B2 = 0;
				MPC::PL2PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B2 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B2 = 0;
				MPC::PM2PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B2 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool trg_d_(ORDER odr, bool ena) noexcept
		{
			// GTETRGD:
			// P14 (LFQFP100:  32) (LFQFP144:  43) (LFQFP176:  51)
			// PH3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PK3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PL3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			// PM3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORT1::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTH::PMR.B3 = 0;
				MPC::PH3PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTH::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B3 = 0;
				MPC::PK3PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTK::PMR.B3 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B3 = 0;
				MPC::PL3PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTL::PMR.B3 = ena;
				break;
			case ORDER::FIFTH:
				PORTM::PMR.B3 = 0;
				MPC::PM3PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTM::PMR.B3 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPTW[0-9]、チャネル別ポート切り替え
			@param[in]	per		周辺機器タイプ型
			@param[in]	ch		チャネル型
			@param[in]	ena		無効にする場合「false」
			@param[in]	order	候補を選択する場合
			@param[in]	neg		反転入出力の場合「true」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER order = ORDER::FIRST, bool neg = false) noexcept
		{
            // RX72N 系は「neg」が無い
            if(neg) return false;

			if(order == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::GPTW0:
				ret = gptw0_(ch, ena, order);
				break;
			case peripheral::GPTW1:
				ret = gptw1_(ch, ena, order);
				break;
			case peripheral::GPTW2:
				ret = gptw2_(ch, ena, order);
				break;
			case peripheral::GPTW3:
				ret = gptw3_(ch, ena, order);
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
			@param[in]	clk	クロック形
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補選択
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
			case CHANNEL::DSM0:
				ret = dsm_0_(odr, ena);
				break;
			case CHANNEL::DSM1:
				ret = dsm_1_(odr, ena);
				break;
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
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
    };
}
