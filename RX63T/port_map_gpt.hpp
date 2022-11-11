#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・ポート・マッピング (GPT)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX63T/peripheral.hpp"
#include "RX63T/port.hpp"
#include "RX63T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX63T/GPT ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_gpt : public port_map_order {

		static bool gpt0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC0A
			// P71
			// PD7
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B1 = 0;
					MPC::P71PFS.PSEL = sel;  // ok
					PORT7::PMR.B1 = ena;
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
			case CHANNEL::B:  // GTIOC0B
			// P74
			// PD6
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B4 = 0;
					MPC::P74PFS.PSEL = sel;  // ok
					PORT7::PMR.B4 = ena;
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
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool gpt1_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC1A
			// P72
			// PD5
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B2 = 0;
					MPC::P72PFS.PSEL = sel;  // ok
					PORT7::PMR.B2 = ena;
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
			case CHANNEL::B:  // GTIOC1B
			// P75
			// PD4
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B5 = 0;
					MPC::P75PFS.PSEL = sel;  // ok
					PORT7::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
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


		static bool gpt2_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC2A
			// P73
			// PD3
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B3 = 0;
					MPC::P73PFS.PSEL = sel;  // ok
					PORT7::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // ok
					PORTD::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC2B
			// P76
			// PB6
			// PB7
			// PD2
				switch(odr) {
				case ORDER::FIRST:
					PORT7::PMR.B6 = 0;
					MPC::P76PFS.PSEL = sel;  // ok
					PORT7::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B6 = 0;
					MPC::PB6PFS.PSEL = sel;  // ok
					PORTB::PMR.B6 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B7 = 0;
					MPC::PB7PFS.PSEL = sel;  // ok
					PORTB::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = ena;
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
			uint8_t sel = ena ? 0b00110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC3A
			// P00
			// PD1
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = sel;  // ok
					PORT0::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // ok
					PORTD::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC3B
			// P01
			// PD0
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = sel;  // ok
					PORT0::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;  // ok
					PORTD::PMR.B0 = ena;
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


		static bool gpt4_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC4A
			// P95
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B5 = 0;
					MPC::P95PFS.PSEL = sel;  // ok
					PORT9::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC4B
			// P92
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;  // ok
					PORT9::PMR.B2 = ena;
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


		static bool gpt5_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC5A
			// P94
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;  // ok
					PORT9::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC5B
			// P91
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B1 = 0;
					MPC::P91PFS.PSEL = sel;  // ok
					PORT9::PMR.B1 = ena;
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


		static bool gpt6_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC6A
			// P93
			// PG3
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;  // ok
					PORT9::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTG::PMR.B3 = 0;
					MPC::PG3PFS.PSEL = sel;  // ok
					PORTG::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC6B
			// P90
			// PG4
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B0 = 0;
					MPC::P90PFS.PSEL = sel;  // ok
					PORT9::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTG::PMR.B4 = 0;
					MPC::PG4PFS.PSEL = sel;  // ok
					PORTG::PMR.B4 = ena;
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


		static bool gpt7_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b00110 : 0;
			switch(ch) {
			case CHANNEL::A:  // GTIOC7A
			// PG0
				switch(odr) {
				case ORDER::FIRST:
					PORTG::PMR.B0 = 0;
					MPC::PG0PFS.PSEL = sel;  // ok
					PORTG::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::B:  // GTIOC7B
			// PG1
				switch(odr) {
				case ORDER::FIRST:
					PORTG::PMR.B1 = 0;
					MPC::PG1PFS.PSEL = sel;  // ok
					PORTG::PMR.B1 = ena;
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
			case peripheral::GPT4:
				ret = gpt4_(ch, ena, odr);
				break;
			case peripheral::GPT5:
				ret = gpt5_(ch, ena, odr);
				break;
			case peripheral::GPT6:
				ret = gpt6_(ch, ena, odr);
				break;
			case peripheral::GPT7:
				ret = gpt7_(ch, ena, odr);
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
