#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N ポート・マッピング (IRQ) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX62x/port.hpp"
#include "RX62x/mpc.hpp"
#include "RX62x/icu.hpp"
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
			// P30 (LFQFP100:  20) (LFQFP144:  29)
			// P10 (LFQFP100: ---) (LFQFP144: ---)
			case ORDER::FIRST:
				MPC::PF9IRQ.ITS0 = 0;
				PORT3::ICR.B0 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF9IRQ.ITS0 = 1;
				PORT1::ICR.B0 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq1_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ1:
			// P31 (LFQFP100:  19) (LFQFP144:  28)
			// P11 (LFQFP100: ---) (LFQFP144: ---)
			case ORDER::FIRST:
				MPC::PF9IRQ.ITS1 = 0;
				PORT3::ICR.B1 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF9IRQ.ITS1 = 1;
				PORT1::ICR.B1 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq2_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ2:
			// P32 (LFQFP100:  18) (LFQFP144:  27)
			// P12 (LFQFP100:  34) (LFQFP144:  45)
			case ORDER::FIRST:
				MPC::PF9IRQ.ITS2 = 0;
				PORT3::ICR.B2 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF9IRQ.ITS2 = 1;
				PORT1::ICR.B2 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq3_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ3:
			// P33 (LFQFP100:  17) (LFQFP144:  26)
			// P13 (LFQFP100:  33) (LFQFP144:  44)
			case ORDER::FIRST:
				MPC::PF9IRQ.ITS3 = 0;
				PORT3::ICR.B3 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF9IRQ.ITS3 = 1;
				PORT1::ICR.B3 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq4_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ4:
			// P34 (LFQFP100:  16) (LFQFP144:  25)
			// P14 (LFQFP100:  32) (LFQFP144:  43)
			case ORDER::FIRST:
				MPC::PF9IRQ.ITS4 = 0;
				PORT3::ICR.B4 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF9IRQ.ITS4 = 1;
				PORT1::ICR.B4 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq5_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ5:
			// PE5 (LFQFP100:  73) (LFQFP144: 106)
			// P15 (LFQFP100: ---) (LFQFP144:  42)
			case ORDER::FIRST:
				MPC::PF9IRQ.ITS5 = 0;
				PORTE::ICR.B5 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF9IRQ.ITS5 = 1;
				PORT1::ICR.B5 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq6_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ6:
			// PE6 (LFQFP100:  72) (LFQFP144: 102)
			// P16 (LFQFP100:  30) (LFQFP144:  40)
			case ORDER::FIRST:
				MPC::PF9IRQ.ITS6 = 0;
				PORTE::ICR.B6 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF9IRQ.ITS6 = 1;
				PORT1::ICR.B6 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq7_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ7:
			// PE7 (LFQFP100:  71) (LFQFP144: 101)
			// P17 (LFQFP100: ---) (LFQFP144:  38)
			case ORDER::FIRST:
				MPC::PF9IRQ.ITS7 = 0;
				PORTE::ICR.B7 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF9IRQ.ITS7 = 1;
				PORT1::ICR.B7 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq8_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ8:
			// P00 (LFQFP100: ---) (LFQFP144:   8)
			// P40 (LFQFP100:  95) (LFQFP144: 141)
			case ORDER::FIRST:
				MPC::PF8IRQ.ITS8 = 0;
				PORT0::ICR.B0 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF8IRQ.ITS8 = 1;
				PORT4::ICR.B0 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq9_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ9:
			// P01 (LFQFP100: ---) (LFQFP144:   7)
			// P41 (LFQFP100:  93) (LFQFP144: 139)
			case ORDER::FIRST:
				MPC::PF8IRQ.ITS9 = 0;
				PORT0::ICR.B1 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF8IRQ.ITS9 = 1;
				PORT4::ICR.B1 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq10_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ10:
			// P02 (LFQFP100: ---) (LFQFP144:   6)
			// P42 (LFQFP100:  92) (LFQFP144: 138)
			case ORDER::FIRST:
				MPC::PF8IRQ.ITS10 = 0;
				PORT0::ICR.B2 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF8IRQ.ITS10 = 1;
				PORT4::ICR.B2 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq11_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ11:
			// P03 (LFQFP100: ---) (LFQFP144:   4)
			// P43 (LFQFP100:  91) (LFQFP144: 137)
			case ORDER::FIRST:
				MPC::PF8IRQ.ITS11 = 0;
				PORT0::ICR.B3 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF8IRQ.ITS11 = 1;
				PORT4::ICR.B3 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq12_(bool ena, ORDER odr) noexcept
		{
			// 端子無し
#if 0
			switch(odr) {
			// PC0
			// PF0
			case ORDER::FIRST:
				break;
			case ORDER::SECOND:
				break;
			default:
				return false;
			}
			return true;
#endif
			return false;
		}

		static bool irq13_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ13:
			// P05 (LFQFP100: 100) (LFQFP144:   2)
			// P45 (LFQFP100:  89) (LFQFP144: 135)
			case ORDER::FIRST:
				MPC::PF8IRQ.ITS13 = 0;
				PORT0::ICR.B5 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF8IRQ.ITS13 = 1;
				PORT4::ICR.B5 = ena;
				break;
			default:
				return false;
			}
			return true;
		}

		static bool irq14_(bool ena, ORDER odr) noexcept
		{
			// 端子無し
#if 0
			switch(odr) {
			// PC3
			// PF3
			case ORDER::FIRST:
				break;
			case ORDER::SECOND:
				break;
			default:
				return false;
			}
			return true;
#endif
			return false;
		}

		static bool irq15_(bool ena, ORDER odr) noexcept
		{
			switch(odr) {  // IRQ15:
			// P07 (LFQFP100:  98) (LFQFP144: 144)
			// P47 (LFQFP100:  87) (LFQFP144: 133)
			case ORDER::FIRST:
				MPC::PF8IRQ.ITS15 = 0;
				PORT0::ICR.B7 = ena;
				break;
			case ORDER::SECOND:
				MPC::PF8IRQ.ITS15 = 1;
				PORT4::ICR.B7 = ena;
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

			return ret;
		}
	};
}
