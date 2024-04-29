#pragma once
//=========================================================================//
/*!	@file
	@brief	RX23T グループ・ポート・マッピング (TMR)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX23T/peripheral.hpp"
#include "RX23T/port.hpp"
#include "RX23T/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX23T TMR ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_tmr : public port_map_order {

		static bool tmr0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;
			switch(ch) {
			case CHANNEL::TMO:  // TMO0
			// PD3
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
			case CHANNEL::TMCI:  // TMCI0 
			// PD4
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
			case CHANNEL::TMRI:  // TMRI0 
			// PD5
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
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool tmr1_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;
			switch(ch) {
			case CHANNEL::TMO:  // TMO1
			// P94
			// PD6
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B4 = 0;
					MPC::P94PFS.PSEL = sel;
					PORT9::PMR.B4 = ena;
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
			case CHANNEL::TMCI:  // TMCI1
			// P92
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B2 = 0;
					MPC::P92PFS.PSEL = sel;
					PORT9::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI1
			// P93
			// PD7
				switch(odr) {
				case ORDER::FIRST:
					PORT9::PMR.B3 = 0;
					MPC::P93PFS.PSEL = sel;
					PORT9::PMR.B3 = ena;
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
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool tmr2_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;
			switch(ch) {
			case CHANNEL::TMO:  // TMO2
			// P23
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI2
			// P24
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;  // ok
					PORT2::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI2
			// P22
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;  // ok
					PORT2::PMR.B2 = ena;
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


		static bool tmr3_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;
			switch(ch) {
			case CHANNEL::TMO:  // TMO3
			// P11
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;  // ok
					PORT1::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI3 
			// PA5
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B5 = 0;
					MPC::PA5PFS.PSEL = sel;  // ok
					PORTA::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI3 
			// P10
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;  // ok
					PORT1::PMR.B0 = ena;
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
			@brief  TMR 関係、チャネル別ポート切り替え
			@param[in]	per	周辺機器タイプ
			@param[in]	ch	チャネル
			@param[in]	ena	無効にする場合「false」
			@param[in]	odr	候補選択
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(per) {
			case peripheral::TMR0:
				ret = tmr0_(ch, ena, odr);
				break;
			case peripheral::TMR1:
				ret = tmr1_(ch, ena, odr);
				break;
			case peripheral::TMR2:
				ret = tmr2_(ch, ena, odr);
				break;
			case peripheral::TMR3:
				ret = tmr3_(ch, ena, odr);
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
