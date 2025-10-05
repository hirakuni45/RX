#pragma once
//=========================================================================//
/*!	@file
	@brief	RX24U グループ・ポート・マッピング (TMR)
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
		@brief  RX24U TMR ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_tmr : public port_map_order {

		static bool tmr0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;
			switch(ch) {
			case CHANNEL::TMO:  // TMO0:
			// P33 (LFQFP100:  58) (LFQFP144:  83)
			// P35 (LFQFP100: ---) (LFQFP144:  59)
			// PB0 (LFQFP100:  35) (LFQFP144:  50)
			// PD3 (LFQFP100:  22) (LFQFP144:  29)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;  // ok
					PORT3::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B5 = 0;
					MPC::P35PFS.PSEL = sel;  // ok
					PORT3::PMR.B5 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B0 = 0;
					MPC::PB0PFS.PSEL = sel;  // ok
					PORTB::PMR.B0 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B3 = 0;
					MPC::PD3PFS.PSEL = sel;  // ok
					PORTD::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI0:
			// PB1 (LFQFP100:  34) (LFQFP144:  49)
			// PD4 (LFQFP100:  21) (LFQFP144:  28)
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;  // ok
					PORTB::PMR.B1 = ena;
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
			case CHANNEL::TMRI:  // TMRI0:
			// PB2 (LFQFP100:  33) (LFQFP144:  48)
			// PD5 (LFQFP100:  20) (LFQFP144:  27)
				switch(odr) {
				case ORDER::FIRST:
					PORTB::PMR.B2 = 0;
					MPC::PB2PFS.PSEL = sel;  // ok
					PORTB::PMR.B2 = ena;
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

		static bool tmr1_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;
			switch(ch) {
			case CHANNEL::TMO:  // TMO1:
			// PD6 (LFQFP100:  19) (LFQFP144:  26)
			// PF0 (LFQFP100: ---) (LFQFP144:  36)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B6 = 0;
					MPC::PD6PFS.PSEL = sel;  // ok
					PORTD::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTF::PMR.B0 = 0;
					MPC::PF0PFS.PSEL = sel;  // ok
					PORTF::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI1:
			// PD2 (LFQFP100:  23) (LFQFP144:  30)
			// PE0 (LFQFP100:  17) (LFQFP144:  24)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = sel;  // ok
					PORTD::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;  // ok
					PORTE::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI1:
			// PD7 (LFQFP100:  18) (LFQFP144:  25)
				switch(odr) {
				case ORDER::FIRST:
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
			case CHANNEL::TMO:  // TMO2:
			// P23 (LFQFP100:  66) (LFQFP144:  95)
			// PA0 (LFQFP100:  41) (LFQFP144:  58)
			// PA7 (LFQFP100: ---) (LFQFP144:  51)
			// PD1 (LFQFP100:  24) (LFQFP144:  31)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B3 = 0;
					MPC::P23PFS.PSEL = sel;  // ok
					PORT2::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORTA::PMR.B0 = 0;
					MPC::PA0PFS.PSEL = sel;  // ok
					PORTA::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B7 = 0;
					MPC::PA7PFS.PSEL = sel;  // ok
					PORTA::PMR.B7 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B1 = 0;
					MPC::PD1PFS.PSEL = sel;  // ok
					PORTD::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI2:
			// P24 (LFQFP100:  65) (LFQFP144:  94)
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
			case CHANNEL::TMRI:  // TMRI2:
			// P22 (LFQFP100:  67) (LFQFP144:  96)
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
			case CHANNEL::TMO:  // TMO3:
			// P11 (LFQFP100:  99) (LFQFP144: 140)
			// PF2 (LFQFP100: ---) (LFQFP144:  34)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;  // ok
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTF::PMR.B2 = 0;
					MPC::PF2PFS.PSEL = sel;  // ok
					PORTF::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI3:
			// PA5 (LFQFP100:  36) (LFQFP144:  53)
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
			case CHANNEL::TMRI:  // TMRI3:
			// P10 (LFQFP100: 100) (LFQFP144: 141)
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

		static bool tmr4_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;
			switch(ch) {
			case CHANNEL::TMO:  // TMO4:
			// P22 (LFQFP100:  67) (LFQFP144:  96)
			// P34 (LFQFP100: ---) (LFQFP144:  60)
			// P82 (LFQFP100:  96) (LFQFP144: 137)
			// PA1 (LFQFP100:  40) (LFQFP144:  57)
			// PD2 (LFQFP100:  23) (LFQFP144:  30)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = ena ? 0b0'0110 : 0;  // ok
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;  // ok
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORT8::PMR.B2 = 0;
					MPC::P82PFS.PSEL = sel;  // ok
					PORT8::PMR.B2 = ena;
					break;
				case ORDER::FOURTH:
					PORTA::PMR.B1 = 0;
					MPC::PA1PFS.PSEL = sel;  // ok
					PORTA::PMR.B1 = ena;
					break;
				case ORDER::FIFTH:
					PORTD::PMR.B2 = 0;
					MPC::PD2PFS.PSEL = ena ? 0b0'0110 : 0;  // ok
					PORTD::PMR.B2 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI4:
			// P21 (LFQFP100:  68) (LFQFP144:  99)
			// P81 (LFQFP100:  97) (LFQFP144: 138)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;  // ok
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B1 = 0;
					MPC::P81PFS.PSEL = sel;  // ok
					PORT8::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI4:
			// P20 (LFQFP100:  69) (LFQFP144: 100)
			// P80 (LFQFP100:  98) (LFQFP144: 139)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;  // ok
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT8::PMR.B0 = 0;
					MPC::P80PFS.PSEL = sel;  // ok
					PORT8::PMR.B0 = ena;
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

		static bool tmr5_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;
			switch(ch) {
			case CHANNEL::TMO:  // TMO5:
			// PE1 (LFQFP100:  16) (LFQFP144:  23)
			// PF1 (LFQFP100: ---) (LFQFP144:  35)
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B1 = 0;
					MPC::PE1PFS.PSEL = sel;  // ok
					PORTE::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTF::PMR.B1 = 0;
					MPC::PF1PFS.PSEL = sel;  // ok
					PORTF::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI5:
			// PE0 (LFQFP100:  17) (LFQFP144:  24)
				switch(odr) {
				case ORDER::FIRST:
					PORTE::PMR.B0 = 0;
					MPC::PE0PFS.PSEL = sel;  // ok
					PORTE::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI5:
			// PD7 (LFQFP100:  18) (LFQFP144:  25)
				switch(odr) {
				case ORDER::FIRST:
					PORTD::PMR.B7 = 0;
					MPC::PD7PFS.PSEL = ena ? 0b0'0110 : 0;  // ok
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

		static bool tmr6_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;
			switch(ch) {
			case CHANNEL::TMO:  // TMO6:
			// P24 (LFQFP100:  65) (LFQFP144:  94)
			// P32 (LFQFP100:  59) (LFQFP144:  84)
			// PA6 (LFQFP100: ---) (LFQFP144:  52)
			// PD0 (LFQFP100:  25) (LFQFP144:  31)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = ena ? 0b0'0110 : 0;  // ok
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;  // ok
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;  // ok
					PORTA::PMR.B6 = ena;
					break;
				case ORDER::FOURTH:
					PORTD::PMR.B0 = 0;
					MPC::PD0PFS.PSEL = sel;  // ok
					PORTD::PMR.B0 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI6:
			// P30 (LFQFP100:  63) (LFQFP144:  90)
			// PD4 (LFQFP100:  21) (LFQFP144:  28)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;  // ok
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = ena ? 0b0'0110 : 0;  // ok
					PORTD::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI6:
			// P31 (LFQFP100:  61) (LFQFP144:  87)
			// PD5 (LFQFP100:  20) (LFQFP144:  27)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;  // ok
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORTD::PMR.B5 = 0;
					MPC::PD5PFS.PSEL = ena ? 0b0'0110 : 0;  // ok
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

		static bool tmr7_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;
			switch(ch) {
			case CHANNEL::TMO:  // TMO7:
			// PA2 (LFQFP100:  39) (LFQFP144:  56)
			// PF3 (LFQFP100: ---) (LFQFP144:  33)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B2 = 0;
					MPC::PA2PFS.PSEL = sel;  // ok
					PORTA::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTF::PMR.B3 = 0;
					MPC::PF3PFS.PSEL = sel;  // ok
					PORTF::PMR.B3 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI7:
			// PA4 (LFQFP100:  37) (LFQFP144:  54)
				switch(odr) {
				case ORDER::FIRST:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;  // ok
					PORTA::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI7:
			// PA3 (LFQFP100:  38) (LFQFP144:  55)
				switch(odr) {
				case ORDER::FIRST:
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
			if(odr == ORDER::BYPASS) {
				return true;
			} else if(odr == ORDER::USER) {
				return false;
			}

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
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
			case peripheral::TMR4:
				ret = tmr4_(ch, ena, odr);
				break;
			case peripheral::TMR5:
				ret = tmr5_(ch, ena, odr);
				break;
			case peripheral::TMR6:
				ret = tmr6_(ch, ena, odr);
				break;
			case peripheral::TMR7:
				ret = tmr7_(ch, ena, odr);
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
