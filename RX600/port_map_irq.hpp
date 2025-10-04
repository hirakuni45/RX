#pragma once
//=============================================================================//
/*!	@file
	@brief	ポート・マッピング (IRQ) @n
			RX63N/RX631 @n
			RX64M/RX71M @n
			RX65N/RX651 @n
			RX66N @n
			RX72N @n
			RX72M
			IRQx-DS 端子は、ディープスタンバイからの復帰が有効な端子 @n
			  通常割り込み入力としても使え、通常「ORDER::FIRST」で選択する。 @n
			  詳しくは、MPC の解説を参照する事。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IRQ ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_irq : public port_map_order {

		static bool irq0_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ0:
			// P30 (DS) (LFQFP100:  20) (LFQFP144:  29) (LFQFP176:  33)
			// P10      (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  56)
			// PD0      (LFQFP100:  86) (LFQFP144: 126) (LFQFP176: 158)
			case ORDER::FIRST:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = 0;
				MPC::P30PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B0 = 0;
				MPC::P10PFS.PSEL = 0;
				MPC::P10PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B0 = 0;
				MPC::PD0PFS.PSEL = 0;
				MPC::PD0PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq1_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ1:
			// P31 (DS) (LFQFP100:  19) (LFQFP144:  28) (LFQFP176:  32)
			// P11      (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  55)
			// PD1      (LFQFP100:  85) (LFQFP144: 125) (LFQFP176: 156)
			case ORDER::FIRST:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = 0;
				MPC::P31PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B1 = 0;
				MPC::P11PFS.PSEL = 0;
				MPC::P11PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = 0;
				MPC::PD1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq2_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ2:
			// P32 (DS) (LFQFP100:  18) (LFQFP144:  27) (LFQFP176:  29)
			// P12      (LFQFP100:  34) (LFQFP144:  45) (LFQFP176:  54)
			// PD2      (LFQFP100:  84) (LFQFP144: 124) (LFQFP176: 154)
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
			// P33 (DS) (LFQFP100:  17) (LFQFP144:  26) (LFQFP176:  28)
			// P13      (LFQFP100:  33) (LFQFP144:  44) (LFQFP176:  53)
			// PD3      (LFQFP100:  83) (LFQFP144: 123) (LFQFP176: 150)
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
			// PB1 (DS) (LFQFP100:  59) (LFQFP144:  84) (LFQFP176: 100)
			// P14      (LFQFP100:  32) (LFQFP144:  43) (LFQFP176:  51)
			// P34      (LFQFP100:  16) (LFQFP144:  25) (LFQFP176:  27)
			// PD4      (LFQFP100:  82) (LFQFP144: 122) (LFQFP176: 148)
			// PF5      (LFQFP100: ---) (LFQFP144:   9) (LFQFP176:   9)
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
			case ORDER::FIFTH:
				PORTF::PMR.B5 = 0;
				MPC::PF5PFS.PSEL = 0;
				MPC::PF5PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq5_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ5:
			// PA4 (DS) (LFQFP100:  66) (LFQFP144:  92) (LFQFP176: 109)
			// P15      (LFQFP100:  31) (LFQFP144:  42) (LFQFP176:  50)
			// PD5      (LFQFP100:  81) (LFQFP144: 121) (LFQFP176: 147)
			// PE5      (LFQFP100:  73) (LFQFP144: 106) (LFQFP176: 130)
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
			// PA3 (DS) (LFQFP100:  67) (LFQFP144:  94) (LFQFP176: 110)
			// P16      (LFQFP100:  30) (LFQFP144:  40) (LFQFP176:  48)
			// PD6      (LFQFP100:  80) (LFQFP144: 120) (LFQFP176: 145)
			// PE6      (LFQFP100:  72) (LFQFP144: 102) (LFQFP176: 126)
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
			// PE2 (DS) (LFQFP100:  76) (LFQFP144: 109) (LFQFP176: 133)
			// P17      (LFQFP100:  29) (LFQFP144:  38) (LFQFP176:  46)
			// PD7      (LFQFP100:  79) (LFQFP144: 119) (LFQFP176: 143)
			// PE7      (LFQFP100:  71) (LFQFP144: 101) (LFQFP176: 125)
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

		static bool irq8_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ8:
			// P40 (DS) (LFQFP100:  95) (LFQFP144: 141) (LFQFP176: 173)
			// P00      (LFQFP100: ---) (LFQFP144:   8) (LFQFP176:   8)
			// P20      (LFQFP100:  28) (LFQFP144:  37) (LFQFP176:  45)
			case ORDER::FIRST:
				MPC::P40PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B0 = 0;
				MPC::P00PFS.PSEL = 0;
				MPC::P00PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B0 = 0;
				MPC::P20PFS.PSEL = 0;
				MPC::P20PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq9_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ9:
			// P41 (DS) (LFQFP100:  93) (LFQFP144: 139) (LFQFP176: 171)
			// P01      (LFQFP100: ---) (LFQFP144:   7) (LFQFP176:   7)
			// P21      (LFQFP100:  27) (LFQFP144:  36) (LFQFP176:  44)
			case ORDER::FIRST:
				MPC::P41PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = 0;
				MPC::P01PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B1 = 0;
				MPC::P21PFS.PSEL = 0;
				MPC::P21PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq10_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ10:
			// P42 (DS) (LFQFP100:  92) (LFQFP144: 138) (LFQFP176: 170)
			// P02      (LFQFP100: ---) (LFQFP144:   6) (LFQFP176:   6)
			// P55      (LFQFP100:  39) (LFQFP144:  51) (LFQFP176:  66)
			case ORDER::FIRST:
				MPC::P42PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B2 = 0;
				MPC::P02PFS.PSEL = 0;
				MPC::P02PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT5::PMR.B5 = 0;
				MPC::P55PFS.PSEL = 0;
				MPC::P55PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq11_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ11:
			// P43 (DS) (LFQFP100:  91) (LFQFP144: 137) (LFQFP176: 169)
			// P03      (LFQFP100: ---) (LFQFP144:   4) (LFQFP176:   4)
			// PA1      (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
			case ORDER::FIRST:
				MPC::P43PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B3 = 0;
				MPC::P03PFS.PSEL = 0;
				MPC::P03PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = 0;
				MPC::PA1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq12_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ12:
			// P44 (DS) (LFQFP100:  90) (LFQFP144: 136) (LFQFP176: 168)
			// PB0      (LFQFP100:  61) (LFQFP144:  87) (LFQFP176: 104)
			// PC1      (LFQFP100:  51) (LFQFP144:  73) (LFQFP176:  89)
			case ORDER::FIRST:
				MPC::P44PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = 0;
				MPC::PB0PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = 0;
				MPC::PC1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq13_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ13:
			// P45 (DS) (LFQFP100:  89) (LFQFP144: 135) (LFQFP176: 167)
			// P05      (LFQFP100: 100) (LFQFP144:   2) (LFQFP176:   2)
			// PC6      (LFQFP100:  46) (LFQFP144:  61) (LFQFP176:  77)
			case ORDER::FIRST:
				MPC::P45PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B5 = 0;
				MPC::P05PFS.PSEL = 0;
				MPC::P05PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = 0;
				MPC::PC6PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq14_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ14:
			// P46 (DS) (LFQFP100:  88) (LFQFP144: 134) (LFQFP176: 166)
			// PC0      (LFQFP100:  52) (LFQFP144:  75) (LFQFP176:  91)
			// PC7      (LFQFP100:  45) (LFQFP144:  60) (LFQFP176:  76)
			case ORDER::FIRST:
				MPC::P46PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORTC::PMR.B0 = 0;
				MPC::PC0PFS.PSEL = 0;
				MPC::PC0PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = 0;
				MPC::PC7PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq15_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ15:
			// P47 (DS) (LFQFP100:  87) (LFQFP144: 133) (LFQFP176: 165)
			// P07      (LFQFP100:  98) (LFQFP144: 144) (LFQFP176: 176)
			// P67      (LFQFP100: ---) (LFQFP144:  98) (LFQFP176: 120)
			case ORDER::FIRST:
				MPC::P47PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B7 = 0;
				MPC::P07PFS.PSEL = 0;
				MPC::P07PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT6::PMR.B7 = 0;
				MPC::P67PFS.PSEL = 0;
				MPC::P67PFS.ISEL = ena;
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
