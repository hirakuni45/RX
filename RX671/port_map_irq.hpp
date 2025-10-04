#pragma once
//=========================================================================//
/*!	@file
	@brief	RX660/RX671 ポート・マッピング (IRQ) @n
			IRQx-DS 端子は、ディープスタンバイからの復帰が有効な端子 @n
			  通常割り込み入力としても使え、通常「ORDER::FIRST」で選択する。 @n
			  詳しくは、MPC の解説を参照する事。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
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
			// P30 (DS) (LFQFP100:  20) (LFQFP144:  29)
			// P50      (LFQFP100:  44) (LFQFP144:  56)
			// P60      (LFQFP100: ---) (LFQFP144: 117)
			// P70      (LFQFP100: ---) (LFQFP144: 104)
			// P90      (LFQFP100: ---) (LFQFP144: 131)
			// PA0      (LFQFP100:  70) (LFQFP144:  97)
			// PD0      (LFQFP100:  86) (LFQFP144: 126)
			// PH1      (LFQFP100:  37) (LFQFP144:  48)
			case ORDER::FIRST:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = 0;
				MPC::P30PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT5::PMR.B0 = 0;
				MPC::P50PFS.PSEL = 0;
				MPC::P50PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT6::PMR.B0 = 0;
				MPC::P60PFS.PSEL = 0;
				MPC::P60PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = 0;
				MPC::P70PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT9::PMR.B0 = 0;
				MPC::P90PFS.PSEL = 0;
				MPC::P90PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = 0;
				MPC::PA0PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTD::PMR.B0 = 0;
				MPC::PD0PFS.PSEL = 0;
				MPC::PD0PFS.ISEL = ena;
				break;
			case ORDER::EIGHTH:
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
			// P31 (DS) (LFQFP100:  19) (LFQFP144:  28)
			// P51      (LFQFP100:  43) (LFQFP144:  55)
			// P61      (LFQFP100: ---) (LFQFP144: 115)
			// P71      (LFQFP100: ---) (LFQFP144:  86)
			// PD1      (LFQFP100:  85) (LFQFP144: 125)
			// PH2      (LFQFP100:  36) (LFQFP144:  47)
			case ORDER::FIRST:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = 0;
				MPC::P31PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT5::PMR.B1 = 0;
				MPC::P51PFS.PSEL = 0;
				MPC::P51PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT6::PMR.B1 = 0;
				MPC::P61PFS.PSEL = 0;
				MPC::P61PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B1 = 0;
				MPC::P71PFS.PSEL = 0;
				MPC::P71PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTD::PMR.B1 = 0;
				MPC::PD1PFS.PSEL = 0;
				MPC::PD1PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
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
			// P32 (DS) (LFQFP100:  18) (LFQFP144:  27)
			// P12      (LFQFP100:  34) (LFQFP144:  45)
			// P52      (LFQFP100:  42) (LFQFP144:  54)
			// P62      (LFQFP100: ---) (LFQFP144: 114)
			// P82      (LFQFP100: ---) (LFQFP144:  63)
			// PB2      (LFQFP100:  58) (LFQFP144:  83)
			// PD2      (LFQFP100:  84) (LFQFP144: 124)
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
				PORT5::PMR.B2 = 0;
				MPC::P52PFS.PSEL = 0;
				MPC::P52PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT6::PMR.B2 = 0;
				MPC::P62PFS.PSEL = 0;
				MPC::P62PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT8::PMR.B2 = 0;
				MPC::P82PFS.PSEL = 0;
				MPC::P82PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = 0;
				MPC::PB2PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
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
			// P33 (DS) (LFQFP100:  17) (LFQFP144:  26)
			// P13      (LFQFP100:  33) (LFQFP144:  44)
			// P23      (LFQFP100:  25) (LFQFP144:  34)
			// P53      (LFQFP100:  41) (LFQFP144:  53)
			// P63      (LFQFP100: ---) (LFQFP144: 113)
			// P83      (LFQFP100: ---) (LFQFP144:  58)
			// PB3      (LFQFP100:  57) (LFQFP144:  82)
			// PD3      (LFQFP100:  83) (LFQFP144: 123)
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
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = 0;
				MPC::P23PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT5::PMR.B3 = 0;
				MPC::P53PFS.PSEL = 0;
				MPC::P53PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT6::PMR.B3 = 0;
				MPC::P63PFS.PSEL = 0;
				MPC::P63PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORT8::PMR.B3 = 0;
				MPC::P83PFS.PSEL = 0;
				MPC::P83PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = 0;
				MPC::PB3PFS.ISEL = ena;
				break;
			case ORDER::EIGHTH:
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
			// PB1 (DS) (LFQFP100:  59) (LFQFP144:  84)
			// P14      (LFQFP100:  32) (LFQFP144:  43)
			// P34      (LFQFP100:  16) (LFQFP144:  25)
			// P54      (LFQFP100: ---) (LFQFP144:  52)
			// P64      (LFQFP100: ---) (LFQFP144: 112)
			// PB4      (LFQFP100:  56) (LFQFP144:  81)
			// PD4      (LFQFP100:  82) (LFQFP144: 122)
			// PF5      (LFQFP100: ---) (LFQFP144:   9)
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
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = 0;
				MPC::P54PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT6::PMR.B4 = 0;
				MPC::P64PFS.PSEL = 0;
				MPC::P64PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = 0;
				MPC::PB4PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = 0;
				MPC::PD4PFS.ISEL = ena;
				break;
			case ORDER::EIGHTH:
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
			// PA4 (DS) (LFQFP100:  66) (LFQFP144:  92)
			// P15      (LFQFP100:  31) (LFQFP144:  42)
			// P25      (LFQFP100:  23) (LFQFP144:  32)
			// PA5      (LFQFP100:  65) (LFQFP144:  90)
			// PC5      (LFQFP100:  47) (LFQFP144:  62)
			// PD5      (LFQFP100:  81) (LFQFP144: 121)
			// PE5      (LFQFP100:  73) (LFQFP144: 106)
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
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = 0;
				MPC::P25PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = 0;
				MPC::PA5PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = 0;
				MPC::PC5PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTD::PMR.B5 = 0;
				MPC::PD5PFS.PSEL = 0;
				MPC::PD5PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
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
			// PA3 (DS) (LFQFP100:  67) (LFQFP144:  94)
			// P16      (LFQFP100:  30) (LFQFP144:  40)
			// P26      (LFQFP100:  22) (LFQFP144:  31)
			// P56      (LFQFP100: ---) (LFQFP144:  50)
			// PB6      (LFQFP100:  54) (LFQFP144:  79)
			// PD6      (LFQFP100:  80) (LFQFP144: 120)
			// PE6      (LFQFP100:  72) (LFQFP144: 102)
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
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = 0;
				MPC::P26PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT5::PMR.B6 = 0;
				MPC::P56PFS.PSEL = 0;
				MPC::P56PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = 0;
				MPC::PB6PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTD::PMR.B6 = 0;
				MPC::PD6PFS.PSEL = 0;
				MPC::PD6PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
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
			// PE2 (DS) (LFQFP100:  76) (LFQFP144: 109)
			// P17      (LFQFP100:  29) (LFQFP144:  38)
			// P27      (LFQFP100:  21) (LFQFP144:  30)
			// P77      (LFQFP100: ---) (LFQFP144:  68)
			// PA7      (LFQFP100:  63) (LFQFP144:  88)
			// PD7      (LFQFP100:  79) (LFQFP144: 119)
			// PE7      (LFQFP100:  71) (LFQFP144: 101)
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
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = 0;
				MPC::P27PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B7 = 0;
				MPC::P77PFS.PSEL = 0;
				MPC::P77PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTA::PMR.B7 = 0;
				MPC::PA7PFS.PSEL = 0;
				MPC::PA7PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = 0;
				MPC::PD7PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
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
			// P40 (DS) (LFQFP100:  95) (LFQFP144: 141)
			// P00      (LFQFP100: ---) (LFQFP144:   8)
			// P20      (LFQFP100:  28) (LFQFP144:  37)
			// P73      (LFQFP100: ---) (LFQFP144:  77)
			// P80      (LFQFP100: ---) (LFQFP144:  65)
			// PE0      (LFQFP100:  78) (LFQFP144: 111)
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
			case ORDER::FOURTH:
				PORT7::PMR.B3 = 0;
				MPC::P73PFS.PSEL = 0;
				MPC::P73PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT8::PMR.B0 = 0;
				MPC::P80PFS.PSEL = 0;
				MPC::P80PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTE::PMR.B0 = 0;
				MPC::PE0PFS.PSEL = 0;
				MPC::PE0PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq9_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ9:
			// P41 (DS) (LFQFP100:  93) (LFQFP144: 139)
			// P01      (LFQFP100: ---) (LFQFP144:   7)
			// P21      (LFQFP100:  27) (LFQFP144:  36)
			// P81      (LFQFP100: ---) (LFQFP144:  64)
			// P91      (LFQFP100: ---) (LFQFP144: 129)
			// PE1      (LFQFP100:  77) (LFQFP144: 110)
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
			case ORDER::FOURTH:
				PORT8::PMR.B1 = 0;
				MPC::P81PFS.PSEL = 0;
				MPC::P81PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT9::PMR.B1 = 0;
				MPC::P91PFS.PSEL = 0;
				MPC::P91PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTE::PMR.B1 = 0;
				MPC::PE1PFS.PSEL = 0;
				MPC::PE1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq10_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ10:
			// P42 (DS) (LFQFP100:  92) (LFQFP144: 138)
			// P02      (LFQFP100: ---) (LFQFP144:   6)
			// P55      (LFQFP100:  39) (LFQFP144:  51)
			// P72      (LFQFP100: ---) (LFQFP144:  85)
			// P92      (LFQFP100: ---) (LFQFP144: 128)
			// PA2      (LFQFP100:  68) (LFQFP144:  95)
			// PC2      (LFQFP100:  50) (LFQFP144:  70)
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
			case ORDER::FOURTH:
				PORT7::PMR.B2 = 0;
				MPC::P72PFS.PSEL = 0;
				MPC::P72PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT9::PMR.B2 = 0;
				MPC::P92PFS.PSEL = 0;
				MPC::P92PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTA::PMR.B2 = 0;
				MPC::PA2PFS.PSEL = 0;
				MPC::PA2PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = 0;
				MPC::PC2PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq11_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ11:
			// P43 (DS) (LFQFP100:  91) (LFQFP144: 137)
			// P03      (LFQFP100: ---) (LFQFP144:   4)
			// P93      (LFQFP100: ---) (LFQFP144: 127)
			// PA1      (LFQFP100:  69) (LFQFP144:  96)
			// PC3      (LFQFP100:  49) (LFQFP144:  67)
			// PE3      (LFQFP100:  75) (LFQFP144: 108)
			// PJ3      (LFQFP100:   4) (LFQFP144:  13)
			case ORDER::FIRST:
				MPC::P43PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B3 = 0;
				MPC::P03PFS.PSEL = 0;
				MPC::P03PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = 0;
				MPC::P93PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = 0;
				MPC::PA1PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = 0;
				MPC::PC3PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = 0;
				MPC::PE3PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTJ::PMR.B3 = 0;
				MPC::PJ3PFS.PSEL = 0;
				MPC::PJ3PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq12_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ12:
			// P44 (DS) (LFQFP100:  90) (LFQFP144: 136)
			// P24      (LFQFP100:  24) (LFQFP144:  33)
			// P74      (LFQFP100: ---) (LFQFP144:  72)
			// PB0      (LFQFP100:  61) (LFQFP144:  87)
			// PC1      (LFQFP100:  51) (LFQFP144:  73)
			// PC4      (LFQFP100:  48) (LFQFP144:  66)
			// PE4      (LFQFP100:  74) (LFQFP144: 107)
			case ORDER::FIRST:
				MPC::P44PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = 0;
				MPC::P24PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT7::PMR.B4 = 0;
				MPC::P74PFS.PSEL = 0;
				MPC::P74PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = 0;
				MPC::PB0PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = 0;
				MPC::PC1PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = 0;
				MPC::PC4PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = 0;
				MPC::PE4PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq13_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ13:
			// P45 (DS) (LFQFP100:  89) (LFQFP144: 135)
			// P05      (LFQFP100: 100) (LFQFP144:   2)
			// P65      (LFQFP100: ---) (LFQFP144: 100)
			// P75      (LFQFP100: ---) (LFQFP144:  71)
			// PB5      (LFQFP100:  55) (LFQFP144:  80)
			// PC6      (LFQFP100:  46) (LFQFP144:  61)
			// PJ5      (LFQFP100: ---) (LFQFP144:  11)
			case ORDER::FIRST:
				MPC::P45PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B5 = 0;
				MPC::P05PFS.PSEL = 0;
				MPC::P05PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT6::PMR.B5 = 0;
				MPC::P65PFS.PSEL = 0;
				MPC::P65PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT7::PMR.B5 = 0;
				MPC::P75PFS.PSEL = 0;
				MPC::P75PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = 0;
				MPC::PB5PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = 0;
				MPC::PC6PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
				PORTJ::PMR.B5 = 0;
				MPC::PJ5PFS.PSEL = 0;
				MPC::PJ5PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq14_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ14:
			// P46 (DS) (LFQFP100:  88) (LFQFP144: 134)
			// P66      (LFQFP100: ---) (LFQFP144:  99)
			// P76      (LFQFP100: ---) (LFQFP144:  69)
			// P86      (LFQFP100: ---) (LFQFP144:  41)
			// PA6      (LFQFP100:  64) (LFQFP144:  89)
			// PC0      (LFQFP100:  52) (LFQFP144:  75)
			// PC7      (LFQFP100:  45) (LFQFP144:  68)
			case ORDER::FIRST:
				MPC::P46PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT6::PMR.B6 = 0;
				MPC::P66PFS.PSEL = 0;
				MPC::P66PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT7::PMR.B6 = 0;
				MPC::P76PFS.PSEL = 0;
				MPC::P76PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT8::PMR.B6 = 0;
				MPC::P86PFS.PSEL = 0;
				MPC::P86PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = 0;
				MPC::PA6PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTC::PMR.B0 = 0;
				MPC::PC0PFS.PSEL = 0;
				MPC::PC0PFS.ISEL = ena;
				break;
			case ORDER::SEVENTH:
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
			// P47 (DS) (LFQFP100:  87) (LFQFP144: 133)
			// P07      (LFQFP100:  98) (LFQFP144: 144)
			// P22      (LFQFP100:  26) (LFQFP144:  35)
			// P67      (LFQFP100: ---) (LFQFP144:  98)
			// P87      (LFQFP100: ---) (LFQFP144:  39)
			// PB7      (LFQFP100:  53) (LFQFP144:  78)
			case ORDER::FIRST:
				MPC::P47PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B7 = 0;
				MPC::P07PFS.PSEL = 0;
				MPC::P07PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = 0;
				MPC::P22PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT6::PMR.B7 = 0;
				MPC::P67PFS.PSEL = 0;
				MPC::P67PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORT8::PMR.B7 = 0;
				MPC::P87PFS.PSEL = 0;
				MPC::P87PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = 0;
				MPC::PB7PFS.ISEL = ena;
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

			bool ret = true;
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
				ret = false;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
	};
}
