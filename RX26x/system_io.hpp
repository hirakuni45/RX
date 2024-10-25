#pragma once
//=========================================================================//
/*!	@file
	@brief	RX260/RX261 システム制御 @n
			クロックのブースト
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX26x/system.hpp"
#include "RX26x/clock_profile.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス
		@param[in]	OSCT	発信器種別型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <clock_profile::OSC_TYPE OSCT>
	class system_io
	{
		static constexpr bool check_base_clock_() noexcept
		{
			bool ok = true;
			if(OSCT == clock_profile::OSC_TYPE::XTAL) {
				if(clock_profile::BASE < 1'000'000 || clock_profile::BASE > 20'000'000) ok = false;
			} else if(OSCT == clock_profile::OSC_TYPE::EXT) {
				if(clock_profile::BASE > clock_profile::EXT_LIMIT) ok = false;
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {  // 24MHz, 32MHz, 48MHz, 64MHz
				if(clock_profile::BASE != 24'000'000 && clock_profile::BASE != 32'000'000
				&& clock_profile::BASE != 48'000'000 && clock_profile::BASE != 64'000'000) ok = false;
			}
			return ok;
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
			if((clk << div) != (clock_profile::PLL_BASE & (0xffffffff << div))) {
				return false;  // 割り切れない周期
			}
			return true;
		}

		static constexpr uint8_t canfd_clock_div_() noexcept
		{
			auto div = clock_profile::PLL_BASE / clock_profile::CANFDCLK;
			auto mod = clock_profile::PLL_BASE % clock_profile::CANFDCLK;

			if(mod != 0) return 0;  // fail
			if(div == 2) return 0b0001;
			else if(div == 4) return 0b0010;
			else if(div == 8) return 0b0011;
			else return 0;  // fail
		}

		static constexpr bool check_canfd_clock_div_() noexcept
		{
			return canfd_clock_div_() != 0;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  マスター・クロックのブースト @n
					インストラクション・クロックを最大速度にブーストする。
		*/
		//-----------------------------------------------------------------//
		static void boost_master_clock() noexcept
		{
			device::SYSTEM::PRCR = 0xA500 | device::SYSTEM::PRCR.PRC0.b() | device::SYSTEM::PRCR.PRC1.b();

			// ベースクロック周波数の検査
			static_assert(check_base_clock_(), "BASE out of range.");

//			device::SYSTEM::MOSCWTCR = 0x53;  // リセット時、初期値を利用

			// メインクロック強制発振とドライブ能力設定
			if(OSCT == clock_profile::OSC_TYPE::XTAL) {
				uint8_t modrv2 = 0b11;
				if(clock_profile::BASE > 20'000'000) modrv2 = 0b00;
				else if(clock_profile::BASE > 16'000'000) modrv2 = 0b01;
				else if(clock_profile::BASE > 8'000'000) modrv2 = 0b10;
				device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(modrv2);
				device::SYSTEM::MOSCCR.MOSTP = 0;  // メインクロック発振器動作
				{
					volatile auto tmp = device::SYSTEM::MOSCCR();
				}
				while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) { asm("nop"); }
			} else if(OSCT == clock_profile::OSC_TYPE::EXT) {
				device::SYSTEM::MOSCCR.MOSTP = 1;		// メインクロック発振器停止
				{
					volatile auto tmp = device::SYSTEM::MOSCCR();
				}
				device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MOSEL.b();
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {  // 高速オンチップオシレータ
				device::SYSTEM::HOCOCR.HCSTP = 0;  // 動作
				{
					volatile auto tmp = device::SYSTEM::HOCOCR();
				}
				while(device::SYSTEM::OSCOVFSR.HCOVF() == 0) { asm("nop"); }
//				device::SYSTEM::PLLCR.PLLSRCSEL = 1;
			} else {
				device::SYSTEM::PRCR = 0xA500;
				return;
			}

			// 1/64 以上、分周出来ない設定は不可
			static_assert(check_clock_div_(clock_profile::FCLK), "FCLK can't divided.");
			static_assert(check_clock_div_(clock_profile::ICLK), "ICLK can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKA), "PCLKA can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKB), "PCLKB can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKD), "PCLKD can't divided.");

			// 未定義ビット B16 ～ B19 (ICKS) に ICK と同じ値をセット。
			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(clock_profile::FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
								  | device::SYSTEM::SCKCR.PCKA.b(clock_div_(clock_profile::PCLKA))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(clock_profile::PCLKB))
								  | device::SYSTEM::SCKCR.PCKD.b(clock_div_(clock_profile::PCLKD));
			{
				volatile auto tmp = device::SYSTEM::SCKCR();
			}

//			static_assert(check_canfd_clock_div_(), "CANFD can't divided.");
//			device::SYSTEM::SCKCR2 = device::SYSTEM::SCKCR2.CFDCK.b(canfd_clock_div_())
//								   | 0b0001'0001;
//			{
//				volatile auto tmp = device::SYSTEM::SCKCR2();
//			}

			// (x4.0) 0b000111, (x10.5) 0b010100, (x11.0) 0b010101, (x11.5) 0b010110
			// ... MAX x30.0
			static_assert((clock_profile::PLL_BASE * 2 / clock_profile::BASE) >= 8, "PLL_BASE clock divider underflow. (x4)");
			static_assert((clock_profile::PLL_BASE * 2 / clock_profile::BASE) <= 31, "PLL_BASE clock divider overflow. (x15.5)");
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
		}
	};


	//---------------------------------------------------------------------//
	/*!
		@brief  ソフト・リセットの起動
	*/
	//---------------------------------------------------------------------//
	inline void assert_soft_reset()
	{
		device::SYSTEM::PRCR = 0xA502;
		device::SYSTEM::SWRR = 0xA501;
		device::SYSTEM::PRCR = 0xA500;
	}
}
typedef device::system_io<device::clock_profile::OSCT> SYSTEM_IO;
