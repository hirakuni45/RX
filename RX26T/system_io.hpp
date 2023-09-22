#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T システム制御 @n
			クロックのブースト
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX26T/system.hpp"

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
				if(clock_profile::BASE < 8'000'000 || clock_profile::BASE > 24'000'000) ok = false;
			} else if(OSCT == clock_profile::OSC_TYPE::EXT) {
				if(clock_profile::BASE > clock_profile::EXT_LIMIT) ok = false;
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {  // 16MHz, 18MHz, 20MHz
				if(clock_profile::BASE != 16'000'000 && clock_profile::BASE != 18'000'000 && clock_profile::BASE != 20'000'000) ok = false;
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

///			device::SYSTEM::MOSCWTCR = 9;	// 1ms wait

			// ベースクロック周波数の検査
			static_assert(check_base_clock_(), "BASE out of range.");

			// メインクロック強制発振とドライブ能力設定
			if(OSCT == clock_profile::OSC_TYPE::XTAL) {
				uint8_t modrv2 = 0b11;
				if(clock_profile::BASE > 20'000'000) modrv2 = 0b00;
				else if(clock_profile::BASE > 16'000'000) modrv2 = 0b01;
				else if(clock_profile::BASE > 8'000'000) modrv2 = 0b10;
				device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(modrv2);
				device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
				while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) { asm("nop"); }
			} else if(OSCT == clock_profile::OSC_TYPE::EXT) {
				device::SYSTEM::MOSCCR.MOSTP = 1;		// メインクロック発振器停止
				device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MOSEL.b();
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {  // 高速オンチップオシレータ
				uint8_t frq = 0b00;
				if(clock_profile::BASE == 16'000'000) frq = 0b00;
				else if(clock_profile::BASE == 18'000'000) frq = 0b01;
				else if(clock_profile::BASE == 20'000'000) frq = 0b10;
				device::SYSTEM::HOCOCR2.HCFRQ = frq;
				device::SYSTEM::HOCOCR.HCSTP = 0;  // 動作
				while(device::SYSTEM::OSCOVFSR.HCOVF() == 0) { asm("nop"); }
				device::SYSTEM::PLLCR.PLLSRCSEL = 1;
			} else {
				device::SYSTEM::PRCR = 0xA500;
				return;
			}

			// (x10.0) 0b010011, (x10.5) 0b010100, (x11.0) 0b010101, (x11.5) 0b010110
			// ... MAX x30.0
			static_assert((clock_profile::PLL_BASE * 2 / clock_profile::BASE) >= 20, "PLL_BASE clock divider underflow.");
			static_assert((clock_profile::PLL_BASE * 2 / clock_profile::BASE) <= 60, "PLL_BASE clock divider overflow.");
			static_assert((clock_profile::PLL_BASE * 2 % clock_profile::BASE) == 0, "PLL_BASE clock can't divided.");
			uint32_t n = clock_profile::PLL_BASE * 2 / clock_profile::BASE;
			n -= 20;
			device::SYSTEM::PLLCR.STC = n + 0b01'0011;  // base x10
			device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) { asm("nop"); }

			// 1/64 以上、分周出来ない設定は不可
			// ※RX72N, RX72M などは BCLK: 1/3 を選択する事が出来る。
			static_assert(check_clock_div_(clock_profile::FCLK), "FCLK can't divided.");
			static_assert(check_clock_div_(clock_profile::ICLK), "ICLK can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKA), "PCLKA can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKB), "PCLKB can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKC), "PCLKC can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKD), "PCLKD can't divided.");

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(clock_profile::FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
								  | device::SYSTEM::SCKCR.PCKA.b(clock_div_(clock_profile::PCLKA))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(clock_profile::PCLKB))
								  | device::SYSTEM::SCKCR.PCKC.b(clock_div_(clock_profile::PCLKC))
								  | device::SYSTEM::SCKCR.PCKD.b(clock_div_(clock_profile::PCLKD));

			device::SYSTEM::SCKCR3.CKSEL = 0b100;   ///< PLL 選択

			if(OSCT == clock_profile::OSC_TYPE::XTAL || OSCT == clock_profile::OSC_TYPE::EXT) {
				device::SYSTEM::LOCOCR.LCSTP = 1;  ///< 低速オンチップオシレータ停止
				device::SYSTEM::HOCOCR.HCSTP = 1;  ///< 高速オンチップオシレータ停止
				device::SYSTEM::HOCOPCR.HOCOPCNT = 1;  ///< 高速オンチップオシレーター電源 OFF
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {
				device::SYSTEM::LOCOCR.LCSTP = 1;  ///< 低速オンチップオシレータ停止
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
