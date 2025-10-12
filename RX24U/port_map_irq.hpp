#pragma once
//=========================================================================//
/*!	@file
	@brief	RX24U グループ・ポート・マッピング (IRQ)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX24U/port.hpp"
#include "RX24U/mpc.hpp"
#include "RX24U/icu.hpp"
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
			// P10 (LFQFP100: 100) (LFQFP144: 141)
			// P52 (LFQFP100:  81) (LFQFP144: 114)
			// PE5 (LFQFP100:   1) (LFQFP144:   5)
			case ORDER::FIRST:
				PORT1::PMR.B0 = 0;
				MPC::P10PFS.PSEL = 0;
				MPC::P10PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				MPC::P52PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = 0;
				MPC::PE5PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq1_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ1:
			// P11 (LFQFP100:  99) (LFQFP144: 140)
			// P53 (LFQFP100:  80) (LFQFP144: 113)
			// PA5 (LFQFP100:  36) (LFQFP144:  53)
			// PE4 (LFQFP100:   8) (LFQFP144:  14)
			case ORDER::FIRST:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = 0;
				MPC::P11PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				MPC::P53PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = 0;
				MPC::PA5PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = 0;
				MPC::PE4PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq2_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ2:
			// P00 (LFQFP100:   4) (LFQFP144:  10)
			// P54 (LFQFP100:  79) (LFQFP144: 112)
			// PD4 (LFQFP100:  21) (LFQFP144:  28)
			// PE3 (LFQFP100:   9) (LFQFP144:  15)
			case ORDER::FIRST:
				PORT0::PMR.B0 = 0;
				MPC::P00PFS.PSEL = 0;
				MPC::P00PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				MPC::P54PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = 0;
				MPC::PD4PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = 0;
				MPC::PE3PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq3_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ3:
			// P55 (LFQFP100:  78) (LFQFP144: 111)
			// PB4 (LFQFP100:  30) (LFQFP144:  41)
			// PD5 (LFQFP100:  20) (LFQFP144:  27)
			// PE6 (LFQFP100: ---) (LFQFP144:   4)
			case ORDER::FIRST:
				MPC::P55PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = 0;
				MPC::PB4PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B5 = 0;
				MPC::PD5PFS.PSEL = 0;
				MPC::PD5PFS.ISEL = ena;
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

		static bool irq4_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ4:
			// P01 (LFQFP100:   7) (LFQFP144:  13)
			// P60 (LFQFP100:  77) (LFQFP144: 110)
			// P96 (LFQFP100:  43) (LFQFP144:  64)
			case ORDER::FIRST:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = 0;
				MPC::P01PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				MPC::P60PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = 0;
				MPC::P96PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq5_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ5:
			// P02 (LFQFP100:   2) (LFQFP144:   7)
			// P61 (LFQFP100:  76) (LFQFP144: 109)
			// P70 (LFQFP100:  57) (LFQFP144:  79)
			// PB6 (LFQFP100:  27) (LFQFP144:  38)
			// PD6 (LFQFP100:  19) (LFQFP144:  28)
			case ORDER::FIRST:
				PORT0::PMR.B2 = 0;
				MPC::P02PFS.PSEL = 0;
				MPC::P02PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				MPC::P61PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = 0;
				MPC::P70PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = 0;
				MPC::PB6PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
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
			// P21 (LFQFP100:  68) (LFQFP144:  99)
			// P31 (LFQFP100:  61) (LFQFP144:  87)
			// P62 (LFQFP100:  75) (LFQFP144: 108)
			case ORDER::FIRST:
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = 0;
				MPC::P21PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = 0;
				MPC::P31PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				MPC::P62PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq7_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ7:
			// P20 (LFQFP100:  69) (LFQFP144: 100)
			// P30 (LFQFP100:  63) (LFQFP144:  90)
			// P63 (LFQFP100:  74) (LFQFP144: 107)
			case ORDER::FIRST:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = 0;
				MPC::P20PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = 0;
				MPC::P30PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				MPC::P63PFS.ISEL = ena;
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
