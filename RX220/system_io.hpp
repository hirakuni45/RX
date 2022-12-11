#pragma once
//=====================================================================//
/*!	@file
	@brief	RX220 システム制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX220/system.hpp"
#include "RX220/clock_profile.hpp"

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
			while(clk < clock_profile::BASE) {
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
			if((clk << div) != ((clock_profile::BASE) & (0xffffffff << div))) {
				return false;  // 割り切れない周期
			}
			return true;
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
			SYSTEM::PRCR = SYSTEM::PRCR.PRKEY.b(0xA5) | SYSTEM::PRCR.PRC0.b(1);

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

			SYSTEM::PRCR = SYSTEM::PRCR.PRKEY.b(0xA5);

			return true;
		}
	};
}
typedef device::system_io<device::clock_profile::OSCT> SYSTEM_IO;
