#pragma once
//=========================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ・ポート・マッピング (GPT)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
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
			case CHANNEL::A:  // GTIOC0A
			// P23
			// P81
			// PA5
			// PD3
			// PE5
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;  // ok
					PORT8::PMR.B1 = ena;
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
			case CHANNEL::B:  // GTIOC0B
			// P17
			// P81
			// PA0
			// PD2
			// PE2
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
			case CHANNEL::A:  // GTIOC1A
			// P22
			// PC5
			// PA2
			// PE4
			// PD1
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
			case CHANNEL::B:  // GTIOC1B
			// P67
			// P87
			// PC3
			// PD0
			// PE1
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
			case CHANNEL::A:  // GTIOC2A
			// P21
			// P82
			// PA1
			// PE3
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
			case CHANNEL::B:  // GTIOC2B
			// P66
			// P86
			// PC2
			// PE0
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
			case CHANNEL::A:  // GTIOC3A
			// PC7
			// PE7
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
			case CHANNEL::B:  // GTIOC3B
			// PC6
			// PE6
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

			bool ret = true;
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
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}

#if 0
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  GPT 系、トリガーポート切り替え
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合場合「false」
			@param[in]	odr	候補選択
			@param[in]	neg	反転入出力の場合「true」（サポートしない）
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn_trigger(CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST, bool neg = false) noexcept
		{
			bool ret = true;

			if(odr == ORDER::BYPASS) return true;
			if(neg) return false;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(ch) {
			case CHANNEL::CLK_A:
//				ret = trg0_(odr, ena);
				break;
			case CHANNEL::CLK_B:
//				ret = trg1_(odr, ena);
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}
#endif
	};
}
