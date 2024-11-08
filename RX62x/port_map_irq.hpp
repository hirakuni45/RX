#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N ポート・マッピング (IRQ) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
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
			switch(odr) {
			// P30
			// P10
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
			switch(odr) {
			// P31
			// P11
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
			switch(odr) {
			// P32
			// P12
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
			switch(odr) {
			// P33
			// P13
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
			switch(odr) {
			// P34
			// P14
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
			switch(odr) {
			// PE5
			// P15
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
			switch(odr) {
			// PE6
			// P16
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
			switch(odr) {
			// PE7
			// P17
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
			switch(odr) {
			// P00
			// P40
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
			switch(odr) {
			// P01
			// P41
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
			switch(odr) {
			// P02
			// P42
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
			switch(odr) {
			// P03
			// P43
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
			switch(odr) {
			// P05
			// P45
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
			switch(odr) {
			// P07
			// P47
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

			return ret;
		}
	};
}
