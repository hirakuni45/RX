#pragma once
//=========================================================================//
/*!	@file
	@brief	RX210 システム制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX210/system.hpp"
#include "RX210/clock_profile.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス
		@param[in]	OSCT	発信器タイプを設定
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <clock_profile::OSC_TYPE OSCT>
	class system_io {

		static constexpr bool check_base_clock_() noexcept
		{
			bool ret = false;
			switch(OSCT) {
			case clock_profile::OSC_TYPE::XTAL:
				if(clock_profile::BASE >= 1'000'000 && clock_profile::BASE <= 20'000'000) {
					ret = true;
				}
				break;
			case clock_profile::OSC_TYPE::CERA:  // 16MHz to 20MHz lead parts
				if(clock_profile::BASE >= 16'000'000 && clock_profile::BASE <= 20'000'000) {
					ret = true;
				}
				break;
			case clock_profile::OSC_TYPE::EXT:
				if(clock_profile::BASE > 0 && clock_profile::BASE <= 20'000'000) {
					ret = true;
				}
				break;
			case clock_profile::OSC_TYPE::HOCO:
				// 32MHz, 36.864MHz, 40MHz, 50MH
				if(clock_profile::BASE == 32'000'000) {
					ret = true;
				} else if(clock_profile::BASE == 36'864'000) {
					ret = true;
				} else if(clock_profile::BASE == 40'000'000) {
					ret = true;
				} else if(clock_profile::BASE == 50'000'000) {
					ret = true;
				}
				break;
			default:
				ret = true;
				break;
			}
			return ret;
		}

		static constexpr uint8_t clock_div_(uint32_t clk) noexcept
		{
			uint8_t div = 0;
			while(clk < clock_profile::PLL_BASE) {
				++div;
				clk <<= 1;
			}
			if(div > 0b0110) div = 0b111;
			return div;
		}

		static constexpr bool check_clock_div_(uint32_t clk) noexcept
		{
			auto div = clock_div_(clk);
			if(div > 0b0110) {
				return false;  // overflow
			}
			if((clk << div) != ((clock_profile::PLL_BASE) & (0xffffffff << div))) {
				return false;  // 割り切れない周期
			}
			return true;
		}

		static constexpr bool check_pll_multiply_() noexcept
		{
			auto n = clock_profile::PLL_BASE * 2 / clock_profile::BASE;
			if(n == 8 || n == 10 || n == 12 || n == 16 || n == 20 || n == 24 || n == 25) return true;
			else return false;
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  システム・クロックの設定
			@return エラーなら「false」
		*/
		//-------------------------------------------------------------//
		static bool boost_master_clock()
		{
			static_assert(check_base_clock_(), "BASE to overflow.");
			static_assert(check_clock_div_(clock_profile::ICLK),  "ICLK can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKB), "PCLKB can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKD), "PCLKD can't divided.");
			static_assert(check_clock_div_(clock_profile::FCLK),  "FCLK can't divided.");

			// クロック関係書き込み許可
			SYSTEM::PRCR = SYSTEM::PRCR.PRKEY.b(0xA5) | SYSTEM::PRCR.PRC0.b(1) | SYSTEM::PRCR.PRC2.b(1);

			// 電圧レギュレータ制御レジスタの設定（クロックソースを変更する前に設定）
			SYSTEM::VRCR = 0x00;

			switch(OSCT) {
			case clock_profile::OSC_TYPE::XTAL:
				{
					SYSTEM::MOSCCR.MOSTP = 0;  // enable
					uint8_t drv2 = 0b11;
					if(clock_profile::BASE >= 1'000'000 && clock_profile::BASE <= 8'000'000) {
						drv2 = 0b01;
					} else if(clock_profile::BASE > 8'000'000 && clock_profile::BASE < 16'000'000) {
						drv2 = 0b10;
					} else {
						drv2 = 0b11;
					}
					SYSTEM::MOFCR = SYSTEM::MOFCR.MOSEL.b(0) | SYSTEM::MOFCR.MODRV2.b(drv2) | SYSTEM::MOFCR.MODRV.b(0b000);
					// wait
					SYSTEM::SCKCR3.CKSEL = 0b010;
				}
				break;
			case clock_profile::OSC_TYPE::CERA:
				SYSTEM::MOSCCR.MOSTP = 0;  // enable
				SYSTEM::MOFCR = SYSTEM::MOFCR.MOSEL.b(0) | SYSTEM::MOFCR.MODRV2.b(0b11) | SYSTEM::MOFCR.MODRV.b(0b111);
				// wait
				SYSTEM::SCKCR3.CKSEL = 0b010;
				break;
			case clock_profile::OSC_TYPE::EXT:
				SYSTEM::SCKCR3.CKSEL = 0b010;
				SYSTEM::MOFCR = SYSTEM::MOFCR.MOSEL.b(1) | SYSTEM::MOFCR.MODRV2.b(0b01);
				SYSTEM::MOSCWTCR.MSTS = 0;
				SYSTEM::MOSCCR = 1;
				// wait
				SYSTEM::SCKCR3.CKSEL = 0b010;
				break;
			case clock_profile::OSC_TYPE::HOCO:
				if(clock_profile::BASE == 32'000'000) {
					SYSTEM::HOCOCR2.HCFRQ = 0b00;
				} else if(clock_profile::BASE == 36'864'000) {
					SYSTEM::HOCOCR2.HCFRQ = 0b01;
				} else if(clock_profile::BASE == 40'000'000) {
					SYSTEM::HOCOCR2.HCFRQ = 0b10;
				} else if(clock_profile::BASE == 50'000'000) {
					SYSTEM::HOCOCR2.HCFRQ = 0b11;
				}
				SYSTEM::HOCOCR.HCSTP = 0;
				// wait
				SYSTEM::SCKCR3.CKSEL = 0b001;
				break;
			default:
				SYSTEM::PRCR = SYSTEM::PRCR.PRKEY.b(0xA5);
				return true;  // LOCO (125KHz)
			}

			SYSTEM::SCKCR = SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
						  | SYSTEM::SCKCR.PCKB.b(clock_div_(clock_profile::PCLKB))
						  | SYSTEM::SCKCR.PCKD.b(clock_div_(clock_profile::PCLKD))
						  | SYSTEM::SCKCR.FCK.b(clock_div_(clock_profile::FCLK));

			// Master PLL settings
			static_assert(check_pll_multiply_(), "PLL_BASE multplyer rate");
			device::SYSTEM::PLLCR.STC = (clock_profile::PLL_BASE * 2 / clock_profile::BASE) - 1;
			device::SYSTEM::PLLCR2.PLLEN = 0;  // PLL 動作
			{  // dummy read register
				volatile auto tmp = device::SYSTEM::PLLCR2();
			}

			device::SYSTEM::SCKCR3.CKSEL = 0b100;   // PLL 選択
			{  // dummy read register
				volatile auto tmp = device::SYSTEM::SCKCR3();
			}

			device::SYSTEM::SOSCWTCR = 0b01011;
			device::SYSTEM::SOSCCR = device::SYSTEM::SOSCCR.SOSTP.b(!clock_profile::TURN_SBC);

			SYSTEM::PRCR = SYSTEM::PRCR.PRKEY.b(0xA5);

			return true;
		}
	};
}
typedef device::system_io<device::clock_profile::OSCT> SYSTEM_IO;
