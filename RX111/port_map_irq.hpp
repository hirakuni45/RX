#pragma once
//=========================================================================//
/*!	@file
	@brief	RX111 グループ・ポート・マッピング (IRQ)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX111/port.hpp"
#include "RX111/mpc.hpp"
#include "RX111/icu.hpp"
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
			// P30 (LFQFP64:  4)
			// PE0 (LFQFP64: 51)
			case ORDER::FIRST:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = 0;
				MPC::P30PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTE::PMR.B0 = 0;
				MPC::PE0PFS.PSEL = 0;
				MPC::PE0PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq1_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ1:
			// P31 (LFQFP64:  5)
			// PE1 (LFQFP64: 50)
			case ORDER::FIRST:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = 0;
				MPC::P31PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTE::PMR.B1 = 0;
				MPC::PE1PFS.PSEL = 0;
				MPC::PE1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq2_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ2:
			// P32 (LFQFP64: 16)
			// PB0 (LFQFP64: 39)
			// PC4 (LFQFP64: 30)
			case ORDER::FIRST:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = 0;
				MPC::P32PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = 0;
				MPC::PB0PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = 0;
				MPC::PC4PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq3_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ3:
			// P27 (LFQFP64:  2)
			// PE3 (LFQFP64: 48)
			// PA6 (LFQFP64: 41)
			case ORDER::FIRST:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = 0;
				MPC::P27PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = 0;
				MPC::PE3PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = 0;
				MPC::PA6PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq4_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ4:
			// P14 (LFQFP64: 20)
			// PB1 (LFQFP64: 37)
			// PE4 (LFQFP64: 47)
			case ORDER::FIRST:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = 0;
				MPC::P14PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = 0;
				MPC::PB1PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = 0;
				MPC::PE4PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq5_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ5:
			// P15 (LFQFP64: 19)
			// PA4 (LFQFP64: 42)
			// PE5 (LFQFP64: 46)
			case ORDER::FIRST:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = 0;
				MPC::P15PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = 0;
				MPC::PA4PFS.ISEL = ena;
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

		static bool irq6_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ6:
			// P16 (LFQFP64: 18)
			// PA3 (LFQFP64: 43)
			// PE6 (LFQFP64: 53)
			case ORDER::FIRST:
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = 0;
				MPC::P16PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = 0;
				MPC::PA3PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
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
			// P17 (LFQFP64: 17)
			// PE2 (LFQFP64: 49)
			// PE7 (LFQFP64: 52)
			case ORDER::FIRST:
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = 0;
				MPC::P17PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTE::PMR.B2 = 0;
				MPC::PE2PFS.PSEL = 0;
				MPC::PE2PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
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
