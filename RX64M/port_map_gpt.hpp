#pragma once
//=========================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ・ポート・マッピング (GPT)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX64M/peripheral.hpp"
#include "RX64M/port.hpp"
#include "RX64M/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_gpt : public port_map_order {

		static bool gpt0_(CHANNEL ch, bool ena, ORDER odr) noexcept
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
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B3 = 0;
					MPC::P83PFS.PSEL = sel;
					PORT8::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;  // ok
					PORTA::PMR.B5 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // ok
					PORTD::PMR.B3 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B5 = 0;
					MPC::PE5PFS.PSEL = sel;  // ok
					PORTE::PMR.B5 = ena;
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
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;  // ok
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;  // ok
					PORT8::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B2 = 0;
					MPC::PE2PFS.PSEL = sel;  // ok
					PORTE::PMR.B2 = ena;
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

		static bool gpt1_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC1A:
			// P22 (LFQFP100:  26) (LFQFP144:  35) (LFQFP176:  43)
			// PC5 (LFQFP100:  47) (LFQFP144:  62) (LFQFP176:  78)
			// PA2 (LFQFP100:  68) (LFQFP144:  95) (LFQFP176: 112)
			// PE4 (LFQFP100:  74) (LFQFP144: 107) (LFQFP176: 131)
			// PD1 (LFQFP100:  85) (LFQFP144: 125) (LFQFP176: 156)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;  // ok
					PORTC::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;  // ok
					PORTA::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B4 = 0;
					MPC::PE4PFS.PSEL = sel;  // ok
					PORTE::PMR.B4 = ena;
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
			case CHANNEL::B:  // GTIOC1B:
			// P67 (LFQFP100: ---) (LFQFP144:  98) (LFQFP176: 120)
			// P87 (LFQFP100: ---) (LFQFP144:  39) (LFQFP176:  47)
			// PC3 (LFQFP100:  49) (LFQFP144:  67) (LFQFP176:  83)
			// PD0 (LFQFP100:  86) (LFQFP144: 126) (LFQFP176: 158)
			// PE1 (LFQFP100:  77) (LFQFP144: 110) (LFQFP176: 134)
				switch(odr) {
				case ORDER::FIRST:
					PORT6::PMR.B7 = 0;
					MPC::P67PFS.PSEL = sel;  // ok
					PORT6::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B7 = 0;
					MPC::P87PFS.PSEL = sel;  // ok
					PORT8::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B3 = 0;
					MPC::PC3PFS.PSEL = sel;  // ok
					PORTC::PMR.B3 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;  // ok
					PORTD::PMR.B0 = ena;
					break;
				case ORDER::FIFTH:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;  // ok
					PORTE::PMR.B1 = ena;
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

		static bool gpt2_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC2A:
			// P21 (LFQFP100:  27) (LFQFP144:  36) (LFQFP176:  44)
			// P82 (LFQFP100: ---) (LFQFP144:  63) (LFQFP176:  79)
			// PA1 (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
			// PE3 (LFQFP100:  75) (LFQFP144: 108) (LFQFP176: 132)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B3 = 0;
					MPC::PE3PFS.PSEL = sel;  // ok
					PORTE::PMR.B3 = ena;
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
				switch(odr) {
				case ORDER::FIRST:
					PORT6::PMR.B6 = 0;
					MPC::P66PFS.PSEL = sel;  // ok
					PORT6::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B6 = 0;
					MPC::P86PFS.PSEL = sel;  // ok
					PORT8::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B2 = 0;
					MPC::PC2PFS.PSEL = sel;  // ok
					PORTC::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;  // ok
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

		static bool gpt3_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC3A:
			// PC7 (LFQFP100:  45) (LFQFP144:  60) (LFQFP176:  76)
			// PE7 (LFQFP100:  71) (LFQFP144: 101) (LFQFP176: 125)
				switch(odr) {
				case ORDER::FIRST:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;  // ok
					PORTC::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B7 = 0;
					MPC::PE7PFS.PSEL = sel;  // ok
					PORTE::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC3B:
			// PC6 (LFQFP100:  46) (LFQFP144:  61) (LFQFP176:  77)
			// PE6 (LFQFP100:  72) (LFQFP144: 102) (LFQFP176: 126)
				switch(odr) {
				case ORDER::FIRST:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;  // ok
					PORTC::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B6 = 0;
					MPC::PE6PFS.PSEL = sel;  // ok
					PORTE::PMR.B6 = ena;
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

		static bool trg_(ORDER odr, bool ena) noexcept
		{
			bool ret = true;
			// GTETRG:
			// P15 (LFQFP100:  31) (LFQFP144:  42) (LFQFP176:  50)
			// PA6 (LFQFP100:  64) (LFQFP144:  89) (LFQFP176: 107)
			// PC4 (LFQFP100:  48) (LFQFP144:  66) (LFQFP176:  82)
			switch(odr) {
			case ORDER::FIRST:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORT1::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTA::PMR.B6 = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = ena ? 0b01'1110 : 0;  // ok
				PORTC::PMR.B4 = ena;
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
			if(neg) return false;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(per) {
			case peripheral::GPT0:
				ret = gpt0_(ch, ena, odr);
				break;
			case peripheral::GPT1:
				ret = gpt1_(ch, ena, odr);
				break;
			case peripheral::GPT2:
				ret = gpt2_(ch, ena, odr);
				break;
			case peripheral::GPT3:
				ret = gpt3_(ch, ena, odr);
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPT トリガー入力切り替え
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
			case CHANNEL::TRG:
				ret = trg_(odr, ena);
				break;
			default:
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
