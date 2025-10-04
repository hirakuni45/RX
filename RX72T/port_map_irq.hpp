#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66T/RX72T ポート・マッピング (IRQ) @n
			IRQx-DS 端子は、ディープスタンバイからの復帰が有効な端子 @n
			  通常割り込み入力としても使え、通常「ORDER::FIRST」で選択する。 @n
			  詳しくは、MPC の解説を参照する事。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX72T/peripheral.hpp"
#include "RX72T/port.hpp"
#include "RX72T/mpc.hpp"
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
			// P10 (DS) (LFQFP100: 100) (LFQFP144: 141)
			// P52      (LFQFP100:  81) (LFQFP144: 114)
			// PE5      (LFQFP100:   1) (LFQFP144:   5)
			// PG0      (LFQFP100: ---) (LFQFP144:  82)
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
			// P11 (DS) (LFQFP100:  99) (LFQFP144: 140)
			// P53      (LFQFP100:  80) (LFQFP144: 113)
			// PA5      (LFQFP100:  36) (LFQFP144:  54)
			// PE4      (LFQFP100:   8) (LFQFP144:  13)
			// PG1      (LFQFP100: ---) (LFQFP144:  81)
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
			case ORDER::FIFTH:
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
			// PE3 (DS) (LFQFP100:   9) (LFQFP144:  14)
			// P00      (LFQFP100:   4) (LFQFP144:   9)
			// P54      (LFQFP100:  79) (LFQFP144: 112)
			// PB6      (LFQFP100:  27) (LFQFP144:  40)
			// PD4      (LFQFP100:  21) (LFQFP144:  26)
			// PG2      (LFQFP100: ---) (LFQFP144:  80)
			case ORDER::FIRST:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = 0;
				MPC::PE3PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B0 = 0;
				MPC::P00PFS.PSEL = 0;
				MPC::P00PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				MPC::P54PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = 0;
				MPC::PB6PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = 0;
				MPC::PD4PFS.ISEL = ena;
				break;
			case ORDER::SIXTH:
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
			// PB4 (DS) (LFQFP100:  30) (LFQFP144:  43)
			// P34      (LFQFP100: ---) (LFQFP144:  61)
			// P55      (LFQFP100:  78) (LFQFP144: 111)
			// P82      (LFQFP100:  96) (LFQFP144: 137)
			// PE6      (LFQFP100: ---) (LFQFP144:   4)
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
				MPC::P55PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT8::PMR.B2 = 0;
				MPC::P82PFS.PSEL = 0;
				MPC::P82PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
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
			// P96 (DS) (LFQFP100:  43) (LFQFP144:  65)
			// P01      (LFQFP100:   7) (LFQFP144:  12)
			// P24      (LFQFP100:  65) (LFQFP144:  95)
			// P60      (LFQFP100:  77) (LFQFP144: 110)
			// PB1      (LFQFP100:  34) (LFQFP144:  50)
			case ORDER::FIRST:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = 0;
				MPC::P96PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = 0;
				MPC::P01PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B4 = 0;
				MPC::P24PFS.PSEL = 0;
				MPC::P24PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				MPC::P60PFS.ISEL = ena;
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
			// P70 (DS) (LFQFP100:  57) (LFQFP144:  79)
			// P61      (LFQFP100:  76) (LFQFP144: 109)
			// P80      (LFQFP100:  98) (LFQFP144: 139)
			// PD6      (LFQFP100:  19) (LFQFP144:  24)
			// PF2      (LFQFP100: ---) (LFQFP144:  32)
			case ORDER::FIRST:
				PORT7::PMR.B0 = 0;
				MPC::P70PFS.PSEL = 0;
				MPC::P70PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				MPC::P61PFS.ISEL = ena;
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
			// P21 (DS) (LFQFP100:  68) (LFQFP144: 100)
			// P31      (LFQFP100:  61) (LFQFP144:  89)
			// P35      (LFQFP100: ---) (LFQFP144:  60)
			// P62      (LFQFP100:  75) (LFQFP144: 108)
			// PD5      (LFQFP100:  20) (LFQFP144:  25)
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
				PORT3::PMR.B5 = 0;
				MPC::P35PFS.PSEL = 0;
				MPC::P35PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				MPC::P62PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
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
			// P20 (DS) (LFQFP100:  69) (LFQFP144: 101)
			// P30      (LFQFP100:  63) (LFQFP144:  91)
			// P63      (LFQFP100:  74) (LFQFP144: 107)
			// PA6      (LFQFP100: ---) (LFQFP144:  53)
			// PE0      (LFQFP100:  17) (LFQFP144:  22)
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
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = 0;
				MPC::PA6PFS.ISEL = ena;
				break;
			case ORDER::FIFTH:
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
			// PK1 (DS) (LFQFP100: ---) (LFQFP144:  84)
			// P64      (LFQFP100:  71) (LFQFP144: 103)
			// PB0      (LFQFP100:  35) (LFQFP144:  51)
			// PD7      (LFQFP100:  18) (LFQFP144:  23)
			case ORDER::FIRST:
				PORTK::PMR.B1 = 0;
				MPC::PK1PFS.PSEL = 0;
				MPC::PK1PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				MPC::P64PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = 0;
				MPC::PB0PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
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
			// PK2 (DS) (LFQFP100: ---) (LFQFP144:  83)
			// P12      (LFQFP100: ---) (LFQFP144:   3)
			// P65      (LFQFP100:  70) (LFQFP144: 102)
			// PB3      (LFQFP100:  32) (LFQFP144:  48)
			case ORDER::FIRST:
				PORTK::PMR.B2 = 0;
				MPC::PK2PFS.PSEL = 0;
				MPC::PK2PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B2 = 0;
				MPC::P12PFS.PSEL = 0;
				MPC::P12PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				MPC::P65PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
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
			// PC5 (DS) (LFQFP100: ---) (LFQFP144:  63)
			// P13      (LFQFP100: ---) (LFQFP144:   2)
			// P22      (LFQFP100:  67) (LFQFP144:  97)
			// P25      (LFQFP100: ---) (LFQFP144:  94)
			case ORDER::FIRST:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = 0;
				MPC::PC5PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B3 = 0;
				MPC::P13PFS.PSEL = 0;
				MPC::P13PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B2 = 0;
				MPC::P22PFS.PSEL = 0;
				MPC::P22PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT2::PMR.B5 = 0;
				MPC::P25PFS.PSEL = 0;
				MPC::P25PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq11_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ11:
			// PC6 (DS) (LFQFP100: ---) (LFQFP144:  62)
			// P14      (LFQFP100: ---) (LFQFP144:   1)
			// P23      (LFQFP100:  66) (LFQFP144:  96)
			// P26      (LFQFP100: ---) (LFQFP144:  93)
			case ORDER::FIRST:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = 0;
				MPC::PC6PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B4 = 0;
				MPC::P14PFS.PSEL = 0;
				MPC::P14PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORT2::PMR.B3 = 0;
				MPC::P23PFS.PSEL = 0;
				MPC::P23PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = 0;
				MPC::P26PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq12_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ12:
			// P32 (DS) (LFQFP100:  59) (LFQFP144:  87)
			// P15      (LFQFP100: ---) (LFQFP144: 144)
			// PC0      (LFQFP100: ---) (LFQFP144:  47)
			// PF0      (LFQFP100: ---) (LFQFP144:  34)
			case ORDER::FIRST:
				PORT3::PMR.B2 = 0;
				MPC::P32PFS.PSEL = 0;
				MPC::P32PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B5 = 0;
				MPC::P15PFS.PSEL = 0;
				MPC::P15PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B0 = 0;
				MPC::PC0PFS.PSEL = 0;
				MPC::PC0PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTF::PMR.B0 = 0;
				MPC::PF0PFS.PSEL = 0;
				MPC::PF0PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq13_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ13:
			// P33 (DS) (LFQFP100:  58) (LFQFP144:  86)
			// P16      (LFQFP100: ---) (LFQFP144: 143)
			// PC1      (LFQFP100: ---) (LFQFP144:  46)
			// PF1      (LFQFP100: ---) (LFQFP144:  33)
			case ORDER::FIRST:
				PORT3::PMR.B3 = 0;
				MPC::P33PFS.PSEL = 0;
				MPC::P33PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B6 = 0;
				MPC::P16PFS.PSEL = 0;
				MPC::P16PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = 0;
				MPC::PC1PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTF::PMR.B1 = 0;
				MPC::PF1PFS.PSEL = 0;
				MPC::PF1PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq14_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ14:
			// PA1 (DS) (LFQFP100:  40) (LFQFP144:  58)
			// P17      (LFQFP100: ---) (LFQFP144: 142)
			// PC3      (LFQFP100: ---) (LFQFP144:  99)
			// PF3      (LFQFP100: ---) (LFQFP144:  31)
			case ORDER::FIRST:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = 0;
				MPC::PA1PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT1::PMR.B7 = 0;
				MPC::P17PFS.PSEL = 0;
				MPC::P17PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = 0;
				MPC::PC3PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
				PORTF::PMR.B3 = 0;
				MPC::PF3PFS.PSEL = 0;
				MPC::PF3PFS.ISEL = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq15_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ15:
			// PK0 (DS) (LFQFP100: ---) (LFQFP144:  85)
			// P27      (LFQFP100:  64) (LFQFP144:  92)
			// PC2      (LFQFP100: ---) (LFQFP144:  45)
			// PE1      (LFQFP100:  16) (LFQFP144:  21)
			case ORDER::FIRST:
				PORTK::PMR.B0 = 0;
				MPC::PK0PFS.PSEL = 0;
				MPC::PK0PFS.ISEL = ena;
				break;
			case ORDER::SECOND:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = 0;
				MPC::P27PFS.ISEL = ena;
				break;
			case ORDER::THIRD:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = 0;
				MPC::PC2PFS.ISEL = ena;
				break;
			case ORDER::FOURTH:
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
