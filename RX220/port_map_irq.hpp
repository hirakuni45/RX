#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220 グループ・ポート・マッピング (IRQ)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX220/port.hpp"
#include "RX220/mpc.hpp"
#include "RX220/icu.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IRQ ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_irq : public port_map_order {

		static bool irq0_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ0:
			// P30 (LFQFP64: 14) (LFQFP100:  20)
			// PD0 (LFQFP64: --) (LFQFP100:  86)
			// PH1 (LFQFP64: 23) (LFQFP100:  37)
			case ORDER::FIRST:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = 0;
				MPC::P30PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B0 = 0;
				MPC::PD0PFS.PSEL = 0;
				MPC::PD0PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTH::PMR.B1 = 0;
				MPC::PH1PFS.PSEL = 0;
				MPC::PH1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq1_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ1:
			// P31 (LFQFP64: 13) (LFQFP100:  19)
			// PD1 (LFQFP64: --) (LFQFP100:  85)
			// PH2 (LFQFP64: 22) (LFQFP100:  36)
			case ORDER::FIRST:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = 0;
				MPC::P31PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = 0;
				MPC::PD1PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTH::PMR.B2 = 0;
				MPC::PH2PFS.PSEL = 0;
				MPC::PH2PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq2_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ2:
			// P32 (LFQFP64: 12) (LFQFP100:  18)
			// P12 (LFQFP64: --) (LFQFP100:  34)
			// PD2 (LFQFP64: --) (LFQFP100:  84)
			case ORDER::FIRST:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = 0;
				MPC::P32PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B2 = 0;
				MPC::P12PFS.PSEL = 0;
				MPC::P12PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = 0;
				MPC::PD2PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq3_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ3:
			// P33 (LFQFP64: --) (LFQFP100:  17)
			// P13 (LFQFP64: --) (LFQFP100:  33)
			// PD3 (LFQFP64: --) (LFQFP100:  83)
			case ORDER::FIRST:
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = 0;
				MPC::P33PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B3 = 0;
				MPC::P13PFS.PSEL = 0;
				MPC::P13PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B3 = 0;
				MPC::PD3PFS.PSEL = 0;
				MPC::PD3PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq4_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ4:
			// PB1 (LFQFP64: 37) (LFQFP100:  59)
			// P14 (LFQFP64: 20) (LFQFP100:  32)
			// P34 (LFQFP64: --) (LFQFP100:  16)
			// PD4 (LFQFP64: --) (LFQFP100:  82)
			case ORDER::FIRST:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = 0;
				MPC::PB1PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = 0;
				MPC::P14PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT3::PMR.B4 = 0;
				MPC::P34PFS.PSEL = 0;
				MPC::P34PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = 0;
				MPC::PD4PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq5_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ5:
			// PA4 (LFQFP64: 42) (LFQFP100:  66)
			// P15 (LFQFP64: 19) (LFQFP100:  31)
			// PD5 (LFQFP64: --) (LFQFP100:  81)
			// PE5 (LFQFP64: 46) (LFQFP100:  73)
			case ORDER::FIRST:
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = 0;
				MPC::PA4PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = 0;
				MPC::P15PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B5 = 0;
				MPC::PD5PFS.PSEL = 0;
				MPC::PD5PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = 0;
				MPC::PE5PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq6_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ6:
			// PA3 (LFQFP64: 43) (LFQFP100:  67)
			// P16 (LFQFP64: 18) (LFQFP100:  30)
			// PD6 (LFQFP64: --) (LFQFP100:  80)
			// PE6 (LFQFP64: --) (LFQFP100:  72)
			case ORDER::FIRST:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = 0;
				MPC::PA3PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = 0;
				MPC::P16PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B6 = 0;
				MPC::PD6PFS.PSEL = 0;
				MPC::PD6PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B6 = 0;
				MPC::PE6PFS.PSEL = 0;
				MPC::PE6PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq7_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ7:
			// PE2 (LFQFP64: 49) (LFQFP100:  76)
			// P17 (LFQFP64: 17) (LFQFP100:  29)
			// PD7 (LFQFP64: --) (LFQFP100:  79)
			// PE7 (LFQFP64: --) (LFQFP100:  71)
			case ORDER::FIRST:
				PORTE::PMR.B2 = 0;
				MPC::PE2PFS.PSEL = 0;
				MPC::PE2PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = 0;
				MPC::P17PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = 0;
				MPC::PD7PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B7 = 0;
				MPC::PE7PFS.PSEL = 0;
				MPC::PE7PFS.ISEL = ena;
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
