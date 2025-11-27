#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T グループ・ポート・マッピング (IRQ)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX63T/port.hpp"
#include "RX63T/mpc.hpp"
#include "RX63T/icu.hpp"
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
			// P30 (DS) (LFQFP64: 45) (LFQFP100:  63)
			// PB5      (LFQFP64: 19) (LFQFP100:  28)
			// PE5      (LFQFP64: --) (LFQFP100:   1)
			// PG0      (LFQFP64: --) (LFQFP100: ---)
			case ORDER::FIRST:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = 0;
				MPC::P30PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = 0;
				MPC::PB5PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = 0;
				MPC::PE5PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTG::PMR.B0 = 0;
				MPC::PG0PFS.PSEL = 0;
				MPC::PG0PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq1_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ1:
			// P11 (DS) (LFQFP64: 61) (LFQFP100:  99)
			// P93      (LFQFP64: 30) (LFQFP100:  47)
			// PE4      (LFQFP64: --) (LFQFP100:   8)
			// PG1      (LFQFP64: --) (LFQFP100: ---)
			case ORDER::FIRST:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = 0;
				MPC::P11PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = 0;
				MPC::P93PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = 0;
				MPC::PE4PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTG::PMR.B1 = 0;
				MPC::PG1PFS.PSEL = 0;
				MPC::PG1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq2_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ2:
			// P00 (DS) (LFQFP64:  2) (LFQFP100:   6)
			// PE3 (DS) (LFQFP64: --) (LFQFP100:   9)
			// PB6      (LFQFP64: 18) (LFQFP100:  27)
			// PG2      (LFQFP64: --) (LFQFP100: ---)
			case ORDER::FIRST:
				PORT0::PMR.B0 = 0;
				MPC::P00PFS.PSEL = 0;
				MPC::P00PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = 0;
				MPC::PE3PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = 0;
				MPC::PB6PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTG::PMR.B2 = 0;
				MPC::PG2PFS.PSEL = 0;
				MPC::PG2PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq3_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ3:
			// PB4 (DS) (LFQFP64: 21) (LFQFP100:  30)
			// P34      (LFQFP64: --) (LFQFP100: ---)
			// P82      (LFQFP64: --) (LFQFP100:  96)
			case ORDER::FIRST:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = 0;
				MPC::PB4PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT3::PMR.B4 = 0;
				MPC::P34PFS.PSEL = 0;
				MPC::P34PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT8::PMR.B2 = 0;
				MPC::P82PFS.PSEL = 0;
				MPC::P82PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq4_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ4:
			// P01 (DS) (LFQFP64:  4) (LFQFP100:   4)
			// P96 (DS) (LFQFP64: --) (LFQFP100:  43)
			// P24      (LFQFP64: 46) (LFQFP100:  64)
			// PB1      (LFQFP64: 25) (LFQFP100:  34)
			case ORDER::FIRST:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = 0;
				MPC::P01PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = 0;
				MPC::P96PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = 0;
				MPC::P24PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = 0;
				MPC::PB1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq5_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ5:
			// P70 (DS) (LFQFP64: 39) (LFQFP100:  57)
			// P80      (LFQFP64: --) (LFQFP100:  98)
			// PF2      (LFQFP64: --) (LFQFP100: ---)
			case ORDER::FIRST:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = 0;
				MPC::P70PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT8::PMR.B0 = 0;
				MPC::P80PFS.PSEL = 0;
				MPC::P80PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTF::PMR.B2 = 0;
				MPC::PF2PFS.PSEL = 0;
				MPC::PF2PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq6_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ6:
			// P21 (DS) (LFQFP64: --) (LFQFP100:  67)
			// PD5      (LFQFP64: 14) (LFQFP100:  20)
			// PG4      (LFQFP64: --) (LFQFP100: ---)
			case ORDER::FIRST:
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = 0;
				MPC::P21PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B5 = 0;
				MPC::PD5PFS.PSEL = 0;
				MPC::PD5PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTG::PMR.B4 = 0;
				MPC::PG4PFS.PSEL = 0;
				MPC::PG4PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq7_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ7:
			// P20 (DS) (LFQFP64: --) (LFQFP100:  68)
			// P03      (LFQFP64: --) (LFQFP100: ---)
			// PE0      (LFQFP64: --) (LFQFP100:  17)
			case ORDER::FIRST:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = 0;
				MPC::P20PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B3 = 0;
				MPC::P03PFS.PSEL = 0;
				MPC::P03PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B0 = 0;
				MPC::PE0PFS.PSEL = 0;
				MPC::PE0PFS.ISEL = ena;
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
