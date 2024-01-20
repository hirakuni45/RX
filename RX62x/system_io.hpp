#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N システム制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX62x/system.hpp"
#include "RX62x/clock_profile.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス
		@param[in]	OSCT	発信器タイプを設定
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <clock_profile::OSC_TYPE OSCT>
	class system_io {

		static constexpr uint8_t clock_div_(uint32_t clk) noexcept
		{
			uint8_t div = 0;
			while(clk < (clock_profile::BASE * 8)) {
				++div;
				clk <<= 1;
			}
			if(div > 0b0011) div = 0b111;
			return div;
		}

		static constexpr bool check_clock_div_(uint32_t clk) noexcept
		{
			auto div = clock_div_(clk);
			if(div > 0b0110) {
				return false;  // overflow
			}
			if((clk << div) != ((clock_profile::BASE * 8) & (0xffffffff << div))) {
				return false;  // 割り切れない周期
			}
			return true;
		}

		static constexpr bool check_usb_()
		{
			if(clock_profile::TURN_USB) {
				return (clock_profile::BASE == 12'000'000);
			} else {
				return true;
			}
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
			static_assert((clock_profile::BASE >= 8'000'000 && clock_profile::BASE <= 14'000'000), "BASE to overflow.");

			static_assert(check_usb_(), "UCLK(USB) can't divided.");

			static_assert(check_clock_div_(clock_profile::ICLK), "ICLK can't divided.");
			static_assert(check_clock_div_(clock_profile::BCLK), "BCLK can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLK), "PCLK can't divided.");

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
								  | device::SYSTEM::SCKCR.BCK.b(clock_div_(clock_profile::BCLK))
								  | device::SYSTEM::SCKCR.PCK.b(clock_div_(clock_profile::PCLK));

			device::SYSTEM::SUBOSCCR = device::SYSTEM::SUBOSCCR.SUBSTOP.b(!clock_profile::TURN_SBC);

			return true;
		}
	};
}
typedef device::system_io<device::clock_profile::OSCT> SYSTEM_IO;
