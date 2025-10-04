#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T ポート・マッピング (IRQ) @n
			IRQx-DS 端子は、ディープスタンバイからの復帰が有効な端子 @n
			  通常割り込み入力としても使え、通常「ORDER::FIRST」で選択する。 @n
			  詳しくは、MPC の解説を参照する事。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX26T/peripheral.hpp"
#include "RX26T/port.hpp"
#include "RX26T/mpc.hpp"
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
			// P10 (DS) (LFQFP100: 100)
			// P52      (LFQFP100:  81)
			// PE2      (LFQFP100:  15)
			// PE5      (LFQFP100:   1)
			case ORDER::FIRST:
				PORT1::PMR.B0 = 0;
				MPC::P10PFS.PSEL = 0;
				MPC::P10PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				MPC::P52PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B2 = 0;
				MPC::PE2PFS.PSEL = 0;
				MPC::PE2PFS.ISEL = ena;
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

		static bool irq1_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ1:
			// P11 (DS) (LFQFP100:  99)
			// P53      (LFQFP100:  80)
			// P95      (LFQFP100:  45)
			// PA5      (LFQFP100:  36)
			// PE4      (LFQFP100:   8)
			case ORDER::FIRST:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = 0;
				MPC::P11PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				MPC::P53PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B5 = 0;
				MPC::P95PFS.PSEL = 0;
				MPC::P95PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = 0;
				MPC::PA5PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
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
			// P00 (LFQFP100:   4)
			// P54 (LFQFP100:  79)
			// PB6 (LFQFP100:  27)
			// PD4 (LFQFP100:  21)
			// PE3 (LFQFP100:   9)
			case ORDER::FIRST:
				PORT0::PMR.B0 = 0;
				MPC::P00PFS.PSEL = 0;
				MPC::P00PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				MPC::P54PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = 0;
				MPC::PB6PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = 0;
				MPC::PD4PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
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
			// P55 (LFQFP100:  78)
			// P82 (LFQFP100:  96)
			// PB4 (LFQFP100:  30)
			case ORDER::FIRST:
				MPC::P55PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT8::PMR.B2 = 0;
				MPC::P82PFS.PSEL = 0;
				MPC::P82PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = 0;
				MPC::PB4PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq4_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ4:
			// P01 (LFQFP100:   7)
			// P24 (LFQFP100:  65)
			// P60 (LFQFP100:  77)
			// P96 (LFQFP100:  43)
			// PB1 (LFQFP100:  34)
			case ORDER::FIRST:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = 0;
				MPC::P01PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = 0;
				MPC::P24PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				MPC::P60PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = 0;
				MPC::P96PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
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
			// P61 (LFQFP100:  76)
			// P70 (LFQFP100:  57)
			// P80 (LFQFP100:  98)
			// PD6 (LFQFP100:  19)
			// PN7 (LFQFP100:   2)
			case ORDER::FIRST:
				MPC::P61PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = 0;
				MPC::P70PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT8::PMR.B0 = 0;
				MPC::P80PFS.PSEL = 0;
				MPC::P80PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTD::PMR.B6 = 0;
				MPC::PD6PFS.PSEL = 0;
				MPC::PD6PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTN::PMR.B7 = 0;
				MPC::PN7PFS.PSEL = 0;
				MPC::PN7PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq6_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ6:
			// P21 (LFQFP100:  68)
			// P31 (LFQFP100:  61)
			// P62 (LFQFP100:  75)
			// PD5 (LFQFP100:  20)
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

		static bool irq7_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ7:
			// P20 (LFQFP100:  69)
			// P30 (LFQFP100:  63)
			// P63 (LFQFP100:  74)
			// PE0 (LFQFP100:  17)
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
			case ORDER::FOURTH:
				PORTE::PMR.B0 = 0;
				MPC::PE0PFS.PSEL = 0;
				MPC::PE0PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq8_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ8:
			// P64 (LFQFP100:  71)
			// PB0 (LFQFP100:  35)
			// PD7 (LFQFP100:  18)
			case ORDER::FIRST:
				MPC::P64PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = 0;
				MPC::PB0PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = 0;
				MPC::PD7PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq9_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ9:
			// P65 (LFQFP100:  70)
			// PB3 (LFQFP100:  32)
			case ORDER::FIRST:
				MPC::P65PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = 0;
				MPC::PB3PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq10_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ10:
			// P22 (LFQFP100:  67)
			case ORDER::FIRST:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = 0;
				MPC::P22PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq11_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ11:
			// P23 (LFQFP100:  66)
			case ORDER::FIRST:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = 0;
				MPC::P23PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq12_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ12:
			// P32 (LFQFP100:  59)
			case ORDER::FIRST:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = 0;
				MPC::P32PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq13_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ13:
			// P33 (LFQFP100:  58)
			case ORDER::FIRST:
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = 0;
				MPC::P33PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq14_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ14:
			// P93 (LFQFP100:  47)
			// PA1 (LFQFP100:  40)
			case ORDER::FIRST:
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = 0;
				MPC::P93PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = 0;
				MPC::PA1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq15_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ15:
			// P27 (LFQFP100:  64)
			// PE1 (LFQFP100:  16)
			case ORDER::FIRST:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = 0;
				MPC::P27PFS.ISEL = ena;
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
			case ICU::VECTOR::IRQ8:
				ret = irq8_(ena, odr);
				break;
			case ICU::VECTOR::IRQ9:
				ret = irq9_(ena, odr);
				break;
			case ICU::VECTOR::IRQ10:
				ret = irq10_(ena, odr);
				break;
			case ICU::VECTOR::IRQ11:
				ret = irq11_(ena, odr);
				break;
			case ICU::VECTOR::IRQ12:
				ret = irq12_(ena, odr);
				break;
			case ICU::VECTOR::IRQ13:
				ret = irq13_(ena, odr);
				break;
			case ICU::VECTOR::IRQ14:
				ret = irq14_(ena, odr);
				break;
			case ICU::VECTOR::IRQ15:
				ret = irq15_(ena, odr);
				break;
			default:
				break;
			}


			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
