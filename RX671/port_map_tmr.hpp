#pragma once
//=========================================================================//
/*!	@file
	@brief	RX660/RX671 グループ・ポート・マッピング (TMR)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#if defined(SIG_RX660)
#include "RX660/peripheral.hpp"
#include "RX660/port.hpp"
#include "RX660/mpc.hpp"
#elif defined(SIG_RX671)
#include "RX671/peripheral.hpp"
#include "RX671/port.hpp"
#include "RX671/mpc.hpp"
#endif
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX671 TMR ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_tmr : public port_map_order {

		static bool tmr0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;  // ok
			switch(ch) {
			case CHANNEL::TMO:  // TMO0:
			// P22 (LFQFP100:  26) (LFQFP144:  )
			// PB3 (LFQFP100:  57) (LFQFP144:  )
			// PH1 (LFQFP100:  37) (LFQFP144:  )
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B2 = 0;
					MPC::P22PFS.PSEL = sel;
					PORT2::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B3 = 0;
					MPC::PB3PFS.PSEL = sel;
					PORTB::PMR.B3 = ena;
					break;
				case ORDER::THIRD:
					PORTH::PMR.B1 = 0;
					MPC::PH1PFS.PSEL = sel;
					PORTH::PMR.B1 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI0:
			// P01 (LFQFP100: ---) (LFQFP144:  )
			// P21 (LFQFP100:  27) (LFQFP144:  )
			// PB1 (LFQFP100:  59) (LFQFP144:  )
			// PH3 (LFQFP100:  35) (LFQFP144:  )
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B1 = 0;
					MPC::P01PFS.PSEL = sel;
					PORT0::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B1 = 0;
					MPC::P21PFS.PSEL = sel;
					PORT2::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTB::PMR.B1 = 0;
					MPC::PB1PFS.PSEL = sel;
					PORTB::PMR.B1 = ena;
					break;
#if defined(SIG_RX660)
				case ORDER::FOURTH:
					PORTH::PMR.B3 = 0;
					MPC::PH3PFS.PSEL = sel;
					PORTH::PMR.B3 = ena;
					break;
#endif
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI0:
			// P00 (LFQFP100: ---) (LFQFP144:  )
			// P20 (LFQFP100:  28) (LFQFP144:  )
			// PA4 (LFQFP100:  66) (LFQFP144:  )
			// PH2 (LFQFP100:  36) (LFQFP144:  )
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B0 = 0;
					MPC::P00PFS.PSEL = sel;
					PORT0::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B0 = 0;
					MPC::P20PFS.PSEL = sel;
					PORT2::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B4 = 0;
					MPC::PA4PFS.PSEL = sel;
					PORTA::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
					PORTH::PMR.B2 = 0;
					MPC::PH2PFS.PSEL = sel;
					PORTH::PMR.B2 = ena;
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
			uint8_t sel = ena ? 0b0'0101 : 0;  // ok
			switch(ch) {
			case CHANNEL::TMO:  // TMO1:
			// P17 (LFQFP100:  29) (LFQFP144:  38)
			// P26 (LFQFP100:  22) (LFQFP144:  31)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B7 = 0;
					MPC::P17PFS.PSEL = sel;
					PORT1::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B6 = 0;
					MPC::P26PFS.PSEL = sel;
					PORT2::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI1:
			// P02 (LFQFP100: ---) (LFQFP144:   6)
			// P12 (LFQFP100:  34) (LFQFP144:  45)
			// P54 (LFQFP100:  40) (LFQFP144:  52)
			// PC4 (LFQFP100:  48) (LFQFP144:  66)
				switch(odr) {
				case ORDER::FIRST:
					PORT0::PMR.B2 = 0;
					MPC::P02PFS.PSEL = sel;
					PORT0::PMR.B2 = ena;
					break;
				case ORDER::SECOND:
					PORT1::PMR.B2 = 0;
					MPC::P12PFS.PSEL = sel;
					PORT1::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORT5::PMR.B4 = 0;
					MPC::P54PFS.PSEL = sel;
					PORT5::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
					PORTC::PMR.B4 = 0;
					MPC::PC4PFS.PSEL = sel;
					PORTC::PMR.B4 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI1:
			// P24 (LFQFP100:  24) (LFQFP144:  33)
			// PB5 (LFQFP100:  55) (LFQFP144:  80)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B4 = 0;
					MPC::P24PFS.PSEL = sel;
					PORT2::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTB::PMR.B5 = 0;
					MPC::PB5PFS.PSEL = sel;
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

		static bool tmr2_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;  // ok
			switch(ch) {
			case CHANNEL::TMO:  // TMO2:
			// P16 (LFQFP100:  30) (LFQFP144:  40)
			// PC7 (LFQFP100:  45) (LFQFP144:  60)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B6 = 0;
					MPC::P16PFS.PSEL = sel;
					PORT1::PMR.B6 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B7 = 0;
					MPC::PC7PFS.PSEL = sel;
					PORTC::PMR.B7 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI2:
			// P15 (LFQFP100:  31) (LFQFP144:  42)
			// P31 (LFQFP100:  19) (LFQFP144:  28)
			// PC6 (LFQFP100:  46) (LFQFP144:  61)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B5 = 0;
					MPC::P15PFS.PSEL = sel;
					PORT1::PMR.B5 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B1 = 0;
					MPC::P31PFS.PSEL = sel;
					PORT3::PMR.B1 = ena;
					break;
				case ORDER::THIRD:
					PORTC::PMR.B6 = 0;
					MPC::PC6PFS.PSEL = sel;
					PORTC::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI2:
			// P14 (LFQFP100:  32) (LFQFP144:  43)
			// PC5 (LFQFP100:  47) (LFQFP144:  62)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B4 = 0;
					MPC::P14PFS.PSEL = sel;
					PORT1::PMR.B4 = ena;
					break;
				case ORDER::SECOND:
					PORTC::PMR.B5 = 0;
					MPC::PC5PFS.PSEL = sel;
					PORTC::PMR.B5 = ena;
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
			uint8_t sel = ena ? 0b0'0101 : 0;  // ok
			switch(ch) {
			case CHANNEL::TMO:  // TMO3:
			// P13 (LFQFP100:  33) (LFQFP144:  44)
			// P32 (LFQFP100:  18) (LFQFP144:  27)
			// P55 (LFQFP100:  39) (LFQFP144:  51)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B3 = 0;
					MPC::P13PFS.PSEL = sel;
					PORT1::PMR.B3 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B2 = 0;
					MPC::P32PFS.PSEL = sel;
					PORT3::PMR.B2 = ena;
					break;
				case ORDER::THIRD:
					PORT5::PMR.B5 = 0;
					MPC::P55PFS.PSEL = sel;
					PORT5::PMR.B5 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI3:
			// P27 (LFQFP100:  21) (LFQFP144:  30)
			// P34 (LFQFP100:  16) (LFQFP144:  25)
			// PA6 (LFQFP100:  64) (LFQFP144:  89)
				switch(odr) {
				case ORDER::FIRST:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::THIRD:
					PORTA::PMR.B6 = 0;
					MPC::PA6PFS.PSEL = sel;
					PORTA::PMR.B6 = ena;
					break;
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI3:
			// P30 (LFQFP100:  20) (LFQFP144:  29)
			// P33 (LFQFP100:  17) (LFQFP144:  26)
				switch(odr) {
				case ORDER::FIRST:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B3 = 0;
					MPC::P33PFS.PSEL = sel;
					PORT3::PMR.B3 = ena;
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
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
