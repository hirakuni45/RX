#pragma once
//=========================================================================//
/*!	@file
	@brief	RX231 システム制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX231/system.hpp"
#include "RX231/clock_profile.hpp"

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
				// 32MHz, `54MHz
				if(clock_profile::BASE == 32'000'000) {
					ret = true;
				} else if(clock_profile::BASE == 54'000'000) {
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

#if 0
		static constexpr uint32_t usb_div_() noexcept
		{
			if(clock_profile::TURN_USB) {
				if((clock_profile::PLL_BASE % 48'000'000) != 0) return 0;  // 割り切れない場合
				return (clock_profile::PLL_BASE / 48'000'000);
			} else {  // USB を使わない場合は、常に「２」（リセット時の値）を返す
				return 0b0001 + 1;
			}
		}
#endif

	public:
		//---------------------------------------------------------------------//
		/*!
			@brief  システム・クロックの設定
			@return エラーなら「false」
		*/
		//---------------------------------------------------------------------//
		static bool boost_master_clock()
		{
			static_assert(check_base_clock_(), "BASE to overflow.");

			// クロック関係書き込み許可
			SYSTEM::PRCR = SYSTEM::PRCR.PRKEY.b(0xA5) | SYSTEM::PRCR.PRC0.b(1);

			switch(OSCT) {
			case clock_profile::OSC_TYPE::XTAL:
				{
					SYSTEM::MOSCCR.MOSTP = 0;  // enable
					uint8_t drv21 = clock_profile::BASE >= 10'000'000;
					SYSTEM::MOFCR = SYSTEM::MOFCR.MOSEL.b(0) | SYSTEM::MOFCR.MODRV21.b(drv21);
					// wait
					SYSTEM::SCKCR3.CKSEL = 0b010;
				}
				break;
			case clock_profile::OSC_TYPE::CERA:
				SYSTEM::MOSCCR.MOSTP = 0;  // enable
				SYSTEM::MOFCR = SYSTEM::MOFCR.MOSEL.b(0);
				// wait
				SYSTEM::SCKCR3.CKSEL = 0b010;
				break;
			case clock_profile::OSC_TYPE::EXT:
				SYSTEM::SCKCR3.CKSEL = 0b010;
				SYSTEM::MOFCR = SYSTEM::MOFCR.MOSEL.b(1);
				SYSTEM::MOSCWTCR.MSTS = 0;
				SYSTEM::MOSCCR = 1;
				// wait
				SYSTEM::SCKCR3.CKSEL = 0b010;
				break;
			case clock_profile::OSC_TYPE::HOCO:
				if(clock_profile::BASE == 32'000'000) {
					SYSTEM::HOCOCR2.HCFRQ = 0b00;
				} else if(clock_profile::BASE == 54'000'000) {
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

			static_assert(check_clock_div_(clock_profile::ICLK),  "ICLK can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKA), "PCLKA can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKB), "PCLKB can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKD), "PCLKD can't divided.");
			static_assert(check_clock_div_(clock_profile::FCLK),  "FCLK can't divided.");
			static_assert(check_clock_div_(clock_profile::BCLK),  "BCLK can't divided.");

			SYSTEM::SCKCR = SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
						  | SYSTEM::SCKCR.PCKA.b(clock_div_(clock_profile::PCLKA))
						  | SYSTEM::SCKCR.PCKB.b(clock_div_(clock_profile::PCLKB))
						  | SYSTEM::SCKCR.PCKD.b(clock_div_(clock_profile::PCLKD))
						  | SYSTEM::SCKCR.FCK.b(clock_div_(clock_profile::FCLK))
						  | SYSTEM::SCKCR.BCK.b(clock_div_(clock_profile::BCLK));

			{
				volatile auto tmp = device::SYSTEM::SCKCR();  // dummy read
			}

			// Master PLL settings
			// Min: x4 (0b000111), Max: 13.5 (0b011010)
			static_assert((clock_profile::PLL_BASE * 2 / clock_profile::BASE) >= 8, "PLL_BASE clock divider underflow. (x10)");
			static_assert((clock_profile::PLL_BASE * 2 / clock_profile::BASE) <= 27, "PLL_BASE clock divider overflow. (x30)");
			static_assert((clock_profile::PLL_BASE * 2 % clock_profile::BASE) == 0, "PLL_BASE clock can't divided.");
			device::SYSTEM::PLLCR.STC = (clock_profile::PLL_BASE * 2 / clock_profile::BASE) - 1;
			device::SYSTEM::PLLCR2.PLLEN = 0;  // PLL 動作
			{
				volatile auto tmp = device::SYSTEM::PLLCR2();
			}
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) { asm("nop"); }

			device::SYSTEM::SCKCR3.CKSEL = 0b100;   // PLL 選択
			{  // dummy read register
				volatile auto tmp = device::SYSTEM::SCKCR3();
			}

			if(OSCT == clock_profile::OSC_TYPE::XTAL || OSCT == clock_profile::OSC_TYPE::EXT) {
				device::SYSTEM::LOCOCR.LCSTP = 1;  // 低速オンチップオシレータ停止
				device::SYSTEM::HOCOCR.HCSTP = 1;  // 高速オンチップオシレータ停止
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {
				device::SYSTEM::LOCOCR.LCSTP = 1;  // 低速オンチップオシレータ停止
			}

			device::SYSTEM::PRCR = 0xA500;	// クロック関係書き込み不許可

			return true;
		}
	};
}
typedef device::system_io<device::clock_profile::OSCT> SYSTEM_IO;
