#pragma once
//=========================================================================//
/*!	@file
	@brief	RX14T グループ・ポート・マッピング (IRQ)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX14T/port.hpp"
#include "RX14T/mpc.hpp"
#include "RX14T/icu.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX14T IRQ ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_irq : public port_map_order {

		static bool irq0_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ0:
			// P10 (LFQFP48: 48) (LQFP52: 51) (LFQFP64: 62)
			// P37 (LFQFP48:  4) (LQFP52:  5) (LFQFP64:  7)
			// P92 (LFQFP48: 24) (LQFP52: 26) (LFQFP64: 30)
			// PE2 (LFQFP48:  8) (LQFP52:  9) (LFQFP64: 11)
			case ORDER::FIRST:
				PORT1::PMR.B0 = 0;
				MPC::P10PFS.PSEL = 0;
				MPC::P10PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B7 = 0;
				MPC::P37PFS.PSEL = 0;
				MPC::P37PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B2 = 0;
				MPC::P92PFS.PSEL = 0;
				MPC::P92PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B2 = 0;
				MPC::PE2PFS.PSEL = 0;
				MPC::PE2PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq1_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ1:
			// P11 (LFQFP48: 47) (LQFP52: 50) (LFQFP64: 61)
			// P26 (LFQFP48: 33) (LQFP52: 36) (LFQFP64: 44)
			// P93 (LFQFP48: 23) (LQFP52: 25) (LFQFP64: 29)
			case ORDER::FIRST:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = 0;
				MPC::P11PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = 0;
				MPC::P26PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = 0;
				MPC::P93PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq2_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ2:
			// P01 (LFQFP48: --) (LQFP52: --) (LFQFP64:  2)
			// P22 (LFQFP48: 36) (LQFP52: 39) (LFQFP64: 48)
			// P97 (LFQFP48: 19) (LQFP52: 21) (LFQFP64: 25)
			// PB1 (LFQFP48: 17) (LQFP52: 19) (LFQFP64: 23)
			// PD4 (LFQFP48: 11) (LQFP52: 12) (LFQFP64: 15)
			case ORDER::FIRST:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = 0;
				MPC::P01PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = 0;
				MPC::P22PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B7 = 0;
				MPC::P97PFS.PSEL = 0;
				MPC::P97PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = 0;
				MPC::PB1PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = 0;
				MPC::PD4PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq3_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ3:
			// P24 (LFQFP48: 34) (LQFP52: 37) (LFQFP64: 46)
			// P36 (LFQFP48:  6) (LQFP52:  7) (LFQFP64:  9)
			// PB3 (LFQFP48: 16) (LQFP52: 18) (LFQFP64: 21)
			// PD5 (LFQFP48: 10) (LQFP52: 11) (LFQFP64: 14)
			case ORDER::FIRST:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = 0;
				MPC::P24PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B6 = 0;
				MPC::P36PFS.PSEL = 0;
				MPC::P36PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = 0;
				MPC::PB3PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTD::PMR.B5 = 0;
				MPC::PD5PFS.PSEL = 0;
				MPC::PD5PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq4_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ4:
			// P00 (LFQFP48: --) (LQFP52: --) (LFQFP64:  4)
			// P23 (LFQFP48: 35) (LQFP52: 38) (LFQFP64: 47)
			// P13 (LFQFP48: 46) (LQFP52: --) (LFQFP64: 59)
			// P94 (LFQFP48: 22) (LQFP52: 24) (LFQFP64: 28)
			case ORDER::FIRST:
				PORT0::PMR.B0 = 0;
				MPC::P00PFS.PSEL = 0;
				MPC::P00PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = 0;
				MPC::P23PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT1::PMR.B3 = 0;
				MPC::P13PFS.PSEL = 0;
				MPC::P13PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT9::PMR.B4 = 0;
				MPC::P94PFS.PSEL = 0;
				MPC::P94PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq5_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ5:
			// P02 (LFQFP48: --) (LQFP52:  1) (LFQFP64:  1)
			// P70 (LFQFP48: 31) (LQFP52: 33) (LFQFP64: 39)
			// PB6 (LFQFP48: 13) (LQFP52: 15) (LFQFP64: 18)
			// PD6 (LFQFP48:  9) (LQFP52: 10) (LFQFP64: 13)
			case ORDER::FIRST:
				PORT0::PMR.B2 = 0;
				MPC::P02PFS.PSEL = 0;
				MPC::P02PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = 0;
				MPC::P70PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = 0;
				MPC::PB6PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTD::PMR.B6 = 0;
				MPC::PD6PFS.PSEL = 0;
				MPC::PD6PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq6_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ6:
			// P14 (LFQFP48: 45) (LQFP52: 48) (LFQFP64: 58)
			// P71 (LFQFP48: 30) (LQFP52: 32) (LFQFP64: 38)
			// P90 (LFQFP48: --) (LQFP52: --) (LFQFP64: 32)
			case ORDER::FIRST:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = 0;
				MPC::P14PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT7::PMR.B1 = 0;
				MPC::P71PFS.PSEL = 0;
				MPC::P71PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B0 = 0;
				MPC::P90PFS.PSEL = 0;
				MPC::P90PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq7_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ7:
			// P12 (LFQFP48: --) (LQFP52: --) (LFQFP64: 60)
			// P72 (LFQFP48: 29) (LQFP52: 31) (LFQFP64: 37)
			// PB5 (LFQFP48: 14) (LQFP52: 16) (LFQFP64: 19)
			case ORDER::FIRST:
				PORT1::PMR.B2 = 0;
				MPC::P12PFS.PSEL = 0;
				MPC::P12PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT7::PMR.B2 = 0;
				MPC::P72PFS.PSEL = 0;
				MPC::P72PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = 0;
				MPC::PB5PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  IRQ ポート切り替え
			@param[in]	irqv	IRQ ベクター
			@param[in]	ena		無効にする場合「false」
			@param[in]	odr		候補選択
			@return 無効な周辺機器の場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(ICU::VECTOR irqv, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			switch(irqv) {
			case ICU::VECTOR::IRQ0:
				ret = irq0_(ena, odr);
				break;
			case ICU::VECTOR::IRQ1:
				ret = irq1_(ena, odr);
				break;
			case ICU::VECTOR::IRQ2:
				ret = irq2_(ena, odr);
				break;
			case ICU::VECTOR::IRQ3:
				ret = irq3_(ena, odr);
				break;
			case ICU::VECTOR::IRQ4:
				ret = irq4_(ena, odr);
				break;
			case ICU::VECTOR::IRQ5:
				ret = irq5_(ena, odr);
				break;
			case ICU::VECTOR::IRQ6:
				ret = irq6_(ena, odr);
				break;
			case ICU::VECTOR::IRQ7:
				ret = irq7_(ena, odr);
				break;
			default:
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
