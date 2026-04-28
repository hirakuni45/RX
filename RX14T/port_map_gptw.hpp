#pragma once
//=========================================================================//
/*!	@file
	@brief	RX14T GPTWd グループ・ポート・マッピング (GPTW0 - GPTW2)
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
		@brief  GPTWd ポート・マッピング
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_gptw : public port_map_order {

		static bool gptw0_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC0A(#):
				// P26 (LFQFP48: ) (LQFP52: ) (LFQFP64: 44)
				// P36 (LFQFP48: ) (LQFP52: ) (LFQFP64:  9)
				// P71 (LFQFP48: ) (LQFP52: ) (LFQFP64: 38)
				// P94 (LFQFP48: ) (LQFP52: ) (LFQFP64: 28)
				switch(order) {
				case ORDER::FIRST:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;  // ok
					PORT2::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B6 = 0;
					MPC::P36PFS.PSEL = sel;  // ok
					PORT3::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // ok
					PORT7::PMR.B1 = ena;
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
			case CHANNEL::B:  // GTIOC0B(#):
				// P31 (LFQFP48: ) (LQFP52: ) (LFQFP64: 42)
				// P74 (LFQFP48: ) (LQFP52: ) (LFQFP64: 35)
				// P97 (LFQFP48: ) (LQFP52: ) (LFQFP64: 25)
				switch(order) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;  // ok
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;  // ok
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT9::PMR.B7 = 0;
					MPC::P97PFS.PSEL = sel;  // ok
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

		static bool gptw1_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC1A(#):
				// P31 (LFQFP48: ) (LQFP52: ) (LFQFP64: 42)
				// P72 (LFQFP48: ) (LQFP52: ) (LFQFP64: 37)
				// P92 (LFQFP48: ) (LQFP52: ) (LFQFP64: 30)
				// P95 (LFQFP48: ) (LQFP52: ) (LFQFP64: 27)
				// PB5 (LFQFP48: ) (LQFP52: ) (LFQFP64: 19)
				// PD3 (LFQFP48: ) (LQFP52: ) (LFQFP64: 16)
				switch(order) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;  // ok
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // ok
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // ok
					PORT9::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // ok
					PORT9::PMR.B5 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;  // ok
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::SIXTH:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // ok
					PORTD::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC1B(#):
				// P75 (LFQFP48: ) (LQFP52: ) (LFQFP64: 34)
				// P93 (LFQFP48: ) (LQFP52: ) (LFQFP64: 29)
				// PB0 (LFQFP48: ) (LQFP52: ) (LFQFP64: 24)
				// PD4 (LFQFP48: ) (LQFP52: ) (LFQFP64: 15)
				switch(order) {
				case ORDER::FIRST:
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // ok
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;  // ok
					PORT9::PMR.B3 = ena;
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
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool gptw2_(CHANNEL ch, bool ena, bool neg, ORDER order) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b01'0110 : 0b01'0100) : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC2A(#):
				// P04 (LFQFP48: ) (LQFP52: ) (LFQFP64: 63)
				// P23 (LFQFP48: ) (LQFP52: ) (LFQFP64: 47)
				// P73 (LFQFP48: ) (LQFP52: ) (LFQFP64: 36)
				// P96 (LFQFP48: ) (LQFP52: ) (LFQFP64: 26)
				// PB5 (LFQFP48: ) (LQFP52: ) (LFQFP64: 19)
				// PD5 (LFQFP48: ) (LQFP52: ) (LFQFP64: 14)
				switch(order) {
				case ORDER::FIRST:
					PORT0::PMR.B4 = 0;
					MPC::P04PFS.PSEL = sel;  // ok
					PORT0::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // ok
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORT9::PMR.B6 = 0;
					MPC::P96PFS.PSEL = sel;  // ok
					PORT9::PMR.B6 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = ena ? (neg ? 0b01'0111 : 0b01'0101) : 0;  // ok
					PORTB::PMR.B5 = ena;
					break;
				case ORDER::SIXTH:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = sel;  // ok
					PORTD::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC2B(#):
				// P03 (LFQFP48: ) (LQFP52: ) (LFQFP64: 64)
				// P24 (LFQFP48: ) (LQFP52: ) (LFQFP64: 46)
				// P76 (LFQFP48: ) (LQFP52: ) (LFQFP64: 33)
				// PB1 (LFQFP48: ) (LQFP52: ) (LFQFP64: 23)
				// PB6 (LFQFP48: ) (LQFP52: ) (LFQFP64: 18)
				// PD6 (LFQFP48: ) (LQFP52: ) (LFQFP64: 13)
				switch(order) {
				case ORDER::FIRST:
					PORT0::PMR.B3 = 0;
					MPC::P03PFS.PSEL = sel;  // ok
					PORT0::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // ok
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::SIXTH:
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

		static bool trg_a_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'0111 : 0;
			// GTETRGA:
			// P25 (LFQFP48: ) (LQFP52: ) (LFQFP64: 45)
			// P97 (LFQFP48: ) (LQFP52: ) (LFQFP64: 25)
			// PE2 (LFQFP48: ) (LQFP52: ) (LFQFP64: 11)
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = sel;  // ok
				PORT2::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORT9::PMR.B7 = 0;
				MPC::P97PFS.PSEL = sel;  // ok
				PORT9::PMR.B7 = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B2 = 0;
				MPC::PE2PFS.PSEL = sel;  // ok
				PORTE::PMR.B2 = ena;
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
			uint8_t sel = ena ? 0b01'0101 : 0;
			// GTADSM0:
			// P23 (LFQFP48: ) (LQFP52: ) (LFQFP64: 47)
			// P46 (LFQFP48: ) (LQFP52: ) (LFQFP64: 50)
			// PB0 (LFQFP48: ) (LQFP52: ) (LFQFP64: 24)
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = sel;  // ok
				PORT2::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORT4::PMR.B6 = 0;
				MPC::P46PFS.PSEL = sel;  // ok
				PORT4::PMR.B6 = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = sel;  // ok
				PORTB::PMR.B0 = ena;
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
			uint8_t sel = ena ? 0b01'0101 : 0;
			// GTADSM1:
			// P22 (LFQFP48: ) (LQFP52: ) (LFQFP64: 48)
			// P44 (LFQFP48: ) (LQFP52: ) (LFQFP64: 52)
			// P97 (LFQFP48: ) (LQFP52: ) (LFQFP64: 25)
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = sel; // ok 
				PORT2::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORT4::PMR.B4 = 0;
				MPC::P44PFS.PSEL = sel;  // ok
				PORT4::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B7 = 0;
				MPC::P97PFS.PSEL = sel;  // ok
				PORT9::PMR.B7 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool ppo_0_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'0101 : 0;
			// GTCPPO0:
			// P24 (LFQFP48: ) (LQFP52: 37) (LFQFP64: 46)
			// P36 (LFQFP48: ) (LQFP52: --) (LFQFP64:  9)
			// P70 (LFQFP48: ) (LQFP52: ) (LFQFP64: 39)
			// PB6 (LFQFP48: ) (LQFP52: ) (LFQFP64: 18)
			switch(odr) {
			case ORDER::FIRST:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = sel;  // ok
				PORT2::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B6 = 0;
				MPC::P36PFS.PSEL = sel;  // ok
				PORT3::PMR.B6 = ena;
				break;
			case ORDER::THIRD:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = sel;  // ok
				PORT7::PMR.B0 = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = sel;  // ok
				PORTB::PMR.B6 = ena;
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
			@brief  GPTW[0-2]、チャネル別ポート切り替え
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
			case CHANNEL::DSM0:
				ret = dsm_0_(odr, ena);
				break;
			case CHANNEL::DSM1:
				ret = dsm_1_(odr, ena);
				break;
			case CHANNEL::PPO0:
				ret = ppo_0_(odr, ena);
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
