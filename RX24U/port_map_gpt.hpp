#pragma once
//=========================================================================//
/*!	@file
	@brief	RX24U グループ・ポート・マッピング (GPTB)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX24U/peripheral.hpp"
#include "RX24U/port.hpp"
#include "RX24U/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX24T/GPTB ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_gpt : public port_map_order {

		static bool gpt0_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC0A
			// P12
			// P71
			// PD7
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;  // ok
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // ok
					PORT7::PMR.B1 = ena;
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
			case CHANNEL::B:  // GTIOC0B
			// P15
			// P74
			// PD1
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;  // ok
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;  // ok
					PORT7::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // ok
					PORTD::PMR.B1 = ena;
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


		static bool gpt1_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC1A
			// P13
			// P72
			// PD0
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;  // ok
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:	
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // ok
					PORT7::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;  // ok
					PORTD::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC1B
			// P16
			// P75
			// PB7
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;  // ok
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // ok
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // ok
					PORTB::PMR.B7 = ena;
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


		static bool gpt2_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC2A
			// P14
			// P73
			// PB6
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;  // ok
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // ok
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC2B
			// P17
			// P76
			// PB5
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // ok
					PORT7::PMR.B6 = ena;
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


		static bool gpt3_(CHANNEL ch, bool ena, ORDER odr, bool neg) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? (neg ? 0b1'0110 : 0b1'0100) : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC3A
			// PD7
				switch(odr) {
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = sel;  // ok
					PORTD::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC3B
			// PD6
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
			default:
				ret = false;
				break;
			}
			return ret;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  GPT 関係、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」（サポートしない）
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(per) {
			case peripheral::GPT0:
				ret = gpt0_(ch, ena, odr, neg);
				break;
			case peripheral::GPT1:
				ret = gpt1_(ch, ena, odr, neg);
				break;
			case peripheral::GPT2:
				ret = gpt2_(ch, ena, odr, neg);
				break;
			case peripheral::GPT3:
				ret = gpt3_(ch, ena, odr, neg);
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

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
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(clk) {
			case CHANNEL::CLKA:  // GTECLKA
				// PD5
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = ena ? 0b1'0101 : 0;  // ok
					PORTD::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
			case CHANNEL::CLKB:  // GTECLKB
				// PD4
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = ena ? 0b1'0101 : 0;  // ok
					PORTD::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
			case CHANNEL::CLKC:  // GTECLKC
				// PD3
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = ena ? 0b1'0101 : 0;  // ok
					PORTD::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
			case CHANNEL::CLKD:  // GTECLKD
				// PB4
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b1'0101 : 0;  // ok
					PORTB::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
			case CHANNEL::TRG:  // GTETRG
				// PB4
				// PG2
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B4 = 0;
					MPC::PB4PFS.PSEL = ena ? 0b1'0100 : 0;  // ok
					PORTB::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTG::PMR.B2 = 0;
					MPC::PG2PFS.PSEL = ena ? 0b1'0100 : 0;  // ok
					PORTG::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
			case CHANNEL::DSM0:  // GTADSM0
				// P35
				// PA3
				// PC2
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B5 = 0;
					MPC::P35PFS.PSEL = ena ? 0b1'0100 : 0;  // ok
					PORT3::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B3 = 0;
					MPC::PA3PFS.PSEL = ena ? 0b1'0100 : 0;  // ok
					PORTA::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = ena ? 0b1'0100 : 0;  // ok
					PORTC::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
			case CHANNEL::DSM1:  // GTADSM1
				// P34
				// PA2
				// PC1
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
					PORTA::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B1 = 0;
					MPC::PC1PFS.PSEL = ena ? 0b01'0100 : 0;  // ok
					PORTC::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
			default:
				ret = false;
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
