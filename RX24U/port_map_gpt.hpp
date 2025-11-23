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
			case CHANNEL::A:  // GTIOC0A:
			// P12 (LFQFP100: ---) (LFQFP144:   3)
			// P71 (LFQFP100:  56) (LFQFP144:  78)
			// PD7 (LFQFP100:  18) (LFQFP144:  25)
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
			case CHANNEL::B:  // GTIOC0B:
			// P15 (LFQFP100: ---) (LFQFP144: 144)
			// P74 (LFQFP100:  53) (LFQFP144:  75)
			// PD1 (LFQFP100:  24) (LFQFP144:  31)
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
			// P13 (LFQFP100: ---) (LFQFP144:   2)
			// P72 (LFQFP100:  55) (LFQFP144:  76)
			// PD0 (LFQFP100:  25) (LFQFP144:  32)
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
			// P16 (LFQFP100: ---) (LFQFP144: 143)
			// P75 (LFQFP100:  52) (LFQFP144:  74)
			// PB7 (LFQFP100:  26) (LFQFP144:  37)
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
			// P14 (LFQFP100: ---) (LFQFP144:   1)
			// P73 (LFQFP100:  54) (LFQFP144:  76)
			// PB6 (LFQFP100:  27) (LFQFP144:  38)
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
			// P17 (LFQFP100: ---) (LFQFP144: 142)
			// P76 (LFQFP100:  51) (LFQFP144:  73)
			// PB5 (LFQFP100:  28) (LFQFP144:  39)
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
			// PD7 (LFQFP100:  18) (LFQFP144:  25)
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
			// PD6 (LFQFP100:  19) (LFQFP144:  26)
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

		static bool clk_a_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTECLKA:
			// PD5 (LFQFP100:  20) (LFQFP144:  27)
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
			return ret;
		}

		static bool clk_b_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTECLKB:
			// PD4 (LFQFP100:  21) (LFQFP144:  28)
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
			return ret;
		}

		static bool clk_c_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTECLKC:
			// PD3 (LFQFP100:  22) (LFQFP144:  29)
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
			return ret;
		}

		static bool clk_d_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTECLKD:
			// PB4 (LFQFP100:  30) (LFQFP144:  41)
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
			return ret;
		}

		static bool trg_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTETRG:
			// PB4 (LFQFP100:  30) (LFQFP144:  41)
			// PG2 (LFQFP100: ---) (LFQFP144:  80)
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
			return ret;
		}

		static bool dsm_0_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTADSM0
			// P35 (LFQFP100: ---) (LFQFP144:  59)
			// PA3 (LFQFP100:  38) (LFQFP144:  55)
			// PC2 (LFQFP100: ---) (LFQFP144:  44)
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
			return ret;
		}

		static bool dsm_1_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTADSM1:
			// P34 (LFQFP100: ---) (LFQFP144:  60)
			// PA2 (LFQFP100:  39) (LFQFP144:  56)
			// PC1 (LFQFP100: ---) (LFQFP144:  45)
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

			bool ret = false;
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
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(clk) {
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
			case CHANNEL::TRG:
				ret = trg_(odr, ena);
				break;
			case CHANNEL::DSM0:
				ret = dsm_0_(odr, ena);
				break;
			case CHANNEL::DSM1:
				ret = dsm_1_(odr, ena);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
