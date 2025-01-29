#pragma once
//=========================================================================//
/*!	@file
	@brief	RX230/RX231/RX23W システム制御 @n
			・クロックのブースト
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX231/system.hpp"
#if defined(SIG_RX230) || defined(SIG_RX231)
#include "RX231/clock_profile.hpp"
#elif defined(SIG_RX23W)
#include "RX23W/clock_profile.hpp"
#endif

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

		static constexpr bool check_usb_clock_() noexcept
		{
			if(clock_profile::TURN_USB) {
				if((48'000'000 % clock_profile::BASE) != 0) return 0;  // 割り切れない場合
				auto n = 48'000'000 / clock_profile::BASE;
				auto m = 48'000'000 % clock_profile::BASE;
				if(m == 0 && (n == 4 || n == 6 || n == 8 || n ==12)) return true;
				return false;
			} else {
				return true;
			}
		}

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

			if(clock_profile::ICLK > 32'000'000) {
				// 動作モード切替（高速モードへ変更）
				while(device::SYSTEM::OPCCR.OPCMTSF() != 0) { asm("nop"); }
				device::SYSTEM::OPCCR.OPCM = 0b000;
				while(device::SYSTEM::OPCCR.OPCMTSF() != 0) { asm("nop"); }

				// Setup memory wait cycle register
				SYSTEM::MEMWAIT.MEMWAIT = 1;
			} else {
				SYSTEM::MEMWAIT.MEMWAIT = 0;
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

			// USB clock generate
			static_assert(check_usb_clock_(), "USB clock can't divided.");
			if(clock_profile::TURN_USB) {
				auto n = 48'000'000 / clock_profile::BASE;
				device::SYSTEM::UPLLCR = device::SYSTEM::UPLLCR.USTC.b((n << 1) - 1)
									  |  device::SYSTEM::UPLLCR.UPLIDIV.b(0) | device::SYSTEM::UPLLCR.UCKUPLLSEL.b(1);
				device::SYSTEM::UPLLCR2.UPLLEN = 0;  // UPLL 動作
				{
					volatile auto tmp = device::SYSTEM::UPLLCR2();
				}
				while(device::SYSTEM::OSCOVFSR.UPLOVF() == 0) { asm("nop"); }
			}

			if(OSCT == clock_profile::OSC_TYPE::XTAL || OSCT == clock_profile::OSC_TYPE::EXT) {
				device::SYSTEM::LOCOCR.LCSTP = 1;  // 低速オンチップオシレータ停止
				device::SYSTEM::HOCOCR.HCSTP = 1;  // 高速オンチップオシレータ停止
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {
				device::SYSTEM::LOCOCR.LCSTP = 1;  // 低速オンチップオシレータ停止
			}

			device::SYSTEM::SOSCCR.SOSTP.b(!clock_profile::TURN_SBC);

			device::SYSTEM::PRCR = 0xA500;	// クロック関係書き込み不許可

			return true;
		}
	};
}
typedef device::system_io<device::clock_profile::OSCT> SYSTEM_IO;
