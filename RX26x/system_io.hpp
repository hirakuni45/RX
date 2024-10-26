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
				// HOCO の周波数は、OSFM レジスタで設定する（0xFFFF'FFFF の場合、32MHz）
				if(clock_profile::BASE != 24'000'000 && clock_profile::BASE != 32'000'000
				&& clock_profile::BASE != 48'000'000 && clock_profile::BASE != 64'000'000) ok = false;
			}
			return ok;
		}

		static constexpr uint32_t base_clock_div_() noexcept
		{
			uint32_t div = 0;
			auto base = clock_profile::BASE;
			while(base > 8'000'000) {
				++div;
				base >>= 1;
				if(div == 2) break;
			}
			return div;
		}

		static constexpr uint32_t base_clock_() noexcept
		{
			return clock_profile::BASE / (1 << base_clock_div_());
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
			if((clk << div) != (clock_profile::PLL_BASE & (0xffff'ffff << div))) {
				return false;  // 割り切れない周期
			}
			return true;
		}

		// ベースクロックは標準的には 4, 8, 16MHz を使うので、それに見合った分周と倍率を使う。
		// BASE / 4 * 12.0
		static constexpr uint8_t usb_clock_div_() noexcept
		{
			if(clock_profile::BASE > 8'000'000) return 0b10;  // 1/4
			else if(clock_profile::BASE > 4'000'000) return 0b01;  // 1/2
			else return 0b00;  // 1/1
		}

		static constexpr uint8_t usb_clock_stc_() noexcept
		{
			auto base = clock_profile::BASE / (1 << usb_clock_div_());
			if((clock_profile::BASE % (1 << usb_clock_div_())) != 0) {
				return 0;  // fail...
			}
			auto div = (48'000'000 * 2) / base;
			auto mod = (48'000'000 * 2) % base;

			if(mod != 0) return 0;  // fail...
			if(div >= (4 * 2) && div < (16 * 2)) {
				return div - 1;
			} else {
				return 0;  // fail...
			}
		}

		static constexpr bool check_usb_clock_div_() noexcept
		{
			if(clock_profile::TURN_USB) {
				auto stc = usb_clock_stc_();
				if(stc >= 4 && stc <= 31) return true;
				else return false;
			} else {
				return true;
			}
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
			static_assert(check_base_clock_(), "BASE clock out of range.");

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

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(clock_profile::FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
								  | device::SYSTEM::SCKCR.PCKA.b(clock_div_(clock_profile::PCLKA))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(clock_profile::PCLKB))
								  | device::SYSTEM::SCKCR.PCKD.b(clock_div_(clock_profile::PCLKD));
			{
				volatile auto tmp = device::SYSTEM::SCKCR();
			}

			if(clock_profile::ICLK > 32'000'000) {
				// 動作モード切替（高速モードへ変更）
				while(device::SYSTEM::OPCCR.OPCMTSF() != 0) { asm("nop"); }
				device::SYSTEM::OPCCR.OPCM = 0b000;
				while(device::SYSTEM::OPCCR.OPCMTSF() != 0) { asm("nop"); }

				// Setup memory wait cycle register
				FLASH::MEMWAITR = FLASH::MEMWAITR.MEKEY.b(0xAA) | FLASH::MEMWAITR.MEMWAIT.b(1);
			} else {
				FLASH::MEMWAITR = FLASH::MEMWAITR.MEKEY.b(0xAA) | FLASH::MEMWAITR.MEMWAIT.b(0);
			}

			// (x4.0) 0b000111, (x10.5) 0b010100, (x11.0) 0b010101, (x11.5) 0b010110
			// HOCO が選択されている場合、1/2 にする。
			static_assert((clock_profile::PLL_BASE * 2 / base_clock_()) >= 8,  "PLL_BASE clock divider underflow. (x4)");
			static_assert((clock_profile::PLL_BASE * 2 / base_clock_()) <= 31, "PLL_BASE clock divider overflow. (x15.5)");
			static_assert((clock_profile::PLL_BASE * 2 % base_clock_()) == 0,  "PLL_BASE clock can't divided.");
			auto base = base_clock_();
			device::SYSTEM::PLLCR = device::SYSTEM::PLLCR.STC.b((clock_profile::PLL_BASE * 2 / base) - 1)
								  | device::SYSTEM::PLLCR.PLIDIV.b(base_clock_div_());
			device::SYSTEM::PLLCR2.PLLEN = 0;  // PLL 動作
			{
				volatile auto tmp = device::SYSTEM::PLLCR2();
			}
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) { asm("nop"); }

			device::SYSTEM::SCKCR3.CKSEL = 0b100;   // PLL 選択
			{  // dummy read register
				volatile auto tmp = device::SYSTEM::SCKCR3();
			}

			static_assert(check_usb_clock_div_(), "USB can't divided.");
			if(clock_profile::TURN_USB) {
				device::SYSTEM::PLL2CR = device::SYSTEM::PLL2CR.STC.b(usb_clock_stc_())
								  	   | device::SYSTEM::PLL2CR.PLIDIV.b(usb_clock_div_());
				{
					volatile auto tmp = device::SYSTEM::PLL2CR();
				}
				device::SYSTEM::PLL2CR2.PLL2EN = 1;
				{
					volatile auto tmp = device::SYSTEM::PLL2CR2();
				}
				device::SYSTEM::USBCKCR.USBCKSEL = 0b110;
			}

			if(clock_profile::TURN_SBC) {
				if(clock_profile::SBCT == clock_profile::SBC_TYPE::EXT) {
					device::SYSTEM::SOMCR.SOSEL = 1;
				} else {
					device::SYSTEM::SOMCR.SODRV = static_cast<uint8_t>(clock_profile::SBCT);
				}
				{
					volatile auto tmp = device::SYSTEM::SOMCR();
				}
				device::SYSTEM::SOSCCR.SOSTP = 0;
				{
					volatile auto tmp = device::SYSTEM::SOSCCR();
				}
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
