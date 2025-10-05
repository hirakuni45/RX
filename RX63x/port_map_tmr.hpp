#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・ポート・マッピング (TMR) @n
			RX631/RX63N @n
			RX64M/RX71M @n
			RX651/RX65N @n
			RX66N @n
			RX72N/RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#if defined(SIG_RX631) || defined(SIG_RX63N)
#include "RX63x/peripheral.hpp"
#include "RX63x/port.hpp"
#include "RX63x/mpc.hpp"
#elif defined(SIG_RX64M) || defined(SIG_RX71M)
#include "RX64M/peripheral.hpp"
#include "RX64M/port.hpp"
#include "RX64M/mpc.hpp"
#elif defined(SIG_RX651) || defined(SIG_RX65N)
#include "RX65x/peripheral.hpp"
#include "RX64M/port.hpp"
#include "RX65x/mpc.hpp"
#elif defined(SIG_RX66N)
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
		@brief  TMR ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_tmr : public port_map_order {

		static bool tmr0_(CHANNEL ch, bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b0'0101 : 0;  // ok
			switch(ch) {
			case CHANNEL::TMO:  // TMO0:
			// P22 (LFQFP100:  26) (LFQFP144:  35) (LFQFP176:  43)
			// PB3 (LFQFP100:  57) (LFQFP144:  82) (LFQFP176:  98)
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
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMCI:  // TMCI0:
			// P01 (LFQFP100: ---) (LFQFP144:   7) (LFQFP176:   7)
			// P21 (LFQFP100:  27) (LFQFP144:  36) (LFQFP176:  44)
			// PB1 (LFQFP100:  59) (LFQFP144:  84) (LFQFP176: 100)
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
				default:
					ret = false;
					break;
				}
				break;
			case CHANNEL::TMRI:  // TMRI0:
			// P00 (LFQFP100: ---) (LFQFP144:   8) (LFQFP176:   8)
			// P20 (LFQFP100:  28) (LFQFP144:  37) (LFQFP176:  45)
			// PA4 (LFQFP100:  66) (LFQFP144:  92) (LFQFP176: 109)
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
			// P17 (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
			// P26 (LFQFP100:  22) (LFQFP144:  31) (LFQFP176:  37)
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
			// P02 (LFQFP100: ---) (LFQFP144:   6) (LFQFP176:   6)
			// P12 (LFQFP100:  34) (LFQFP144:  45) (LFQFP176:  54)
			// P54 (LFQFP100:  40) (LFQFP144:  52) (LFQFP176:  67)
			// PC4 (LFQFP100:  48) (LFQFP144:  66) (LFQFP176:  82)
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
			// P24 (LFQFP100:  24) (LFQFP144:  33) (LFQFP176:  40)
			// PB5 (LFQFP100:  55) (LFQFP144:  80) (LFQFP176:  96)
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
			// P16 (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
			// PC7 (LFQFP100:  45) (LFQFP144:  60) (LFQFP176:  76)
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
			// P15 (LFQFP100:  31) (LFQFP144:  42) (LFQFP176:  50)
			// P31 (LFQFP100:  19) (LFQFP144:  28) (LFQFP176:  32)
			// PC6 (LFQFP100:  46) (LFQFP144:  61) (LFQFP176:  77)
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
			// P14 (LFQFP100:  32) (LFQFP144:  43) (LFQFP176:  51)
			// PC5 (LFQFP100:  47) (LFQFP144:  62) (LFQFP176:  78)
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
			// P13 (LFQFP100:  33) (LFQFP144:  44) (LFQFP176:  53)
			// P32 (LFQFP100:  18) (LFQFP144:  27) (LFQFP176:  29)
			// P55 (LFQFP100:  39) (LFQFP144:  51) (LFQFP176:  66)
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
			// P11 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  55)
			// P27 (LFQFP100:  21) (LFQFP144:  30) (LFQFP176:  36)
			// P34 (LFQFP100:  16) (LFQFP144:  25) (LFQFP176:  27)
			// PA6 (LFQFP100:  64) (LFQFP144:  89) (LFQFP176: 107)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B1 = 0;
					MPC::P11PFS.PSEL = sel;
					PORT1::PMR.B1 = ena;
					break;
				case ORDER::SECOND:
					PORT2::PMR.B7 = 0;
					MPC::P27PFS.PSEL = sel;
					PORT2::PMR.B7 = ena;
					break;
				case ORDER::THIRD:
					PORT3::PMR.B4 = 0;
					MPC::P34PFS.PSEL = sel;
					PORT3::PMR.B4 = ena;
					break;
				case ORDER::FOURTH:
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
			// P10 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  56)
			// P30 (LFQFP100:  20) (LFQFP144:  29) (LFQFP176:  33)
			// P33 (LFQFP100:  17) (LFQFP144:  26) (LFQFP176:  28)
				switch(odr) {
				case ORDER::FIRST:
					PORT1::PMR.B0 = 0;
					MPC::P10PFS.PSEL = sel;
					PORT1::PMR.B0 = ena;
					break;
				case ORDER::SECOND:
					PORT3::PMR.B0 = 0;
					MPC::P30PFS.PSEL = sel;
					PORT3::PMR.B0 = ena;
					break;
				case ORDER::THIRD:
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
