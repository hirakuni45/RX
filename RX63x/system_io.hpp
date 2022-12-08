#pragma once
//=========================================================================//
/*!	@file
	@brief	RX631/RX63N グループ・システム制御 @n
			ROM 領域、100MHz、ノーウェイトアクセス @n
			RAM 領域、100MHz、ノーウェイトアクセス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX63x/clock_profile.hpp"
#include "common/delay.hpp"
#include "RX63x/system.hpp"

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
			switch(OSCT) {
			case clock_profile::OSC_TYPE::XTAL:
				if(clock_profile::BASE > 4'000'000 && clock_profile::BASE <= 20'000'000) {
				} else {
					return false;
				}
				break;
			case clock_profile::OSC_TYPE::EXT:
				if(clock_profile::BASE <= 20'000'000) {
				} else {
					return false;
				}
				break;
			case clock_profile::OSC_TYPE::HOCO:
				if(clock_profile::BASE != 50'000'000) {
					return false;
				}
				break;
			default:
				break;
			}
			return true;
		}

		static constexpr uint8_t multi_[] = { 8, 10, 12, 16, 20, 24, 25, 50 };

		static constexpr bool check_pll_base_() noexcept
		{
			if(clock_profile::PLL_BASE <= 104'000'000) return false;
			if(clock_profile::PLL_BASE >= 200'000'000) return false;
			bool ok = false;
			for(auto n : multi_) {
				auto ck = clock_profile::BASE * n;
				if(ck == clock_profile::PLL_BASE) {
					ok = true;
					break;
				}
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

		static constexpr uint32_t usb_div_() noexcept
		{
			if(clock_profile::TURN_USB) {
				if((clock_profile::PLL_BASE % 48'000'000) != 0) return 0;  // 割り切れない場合
				return (clock_profile::PLL_BASE / 48'000'000);
			} else {  // USB を使わない場合は、常に「２」（リセット時の値）を返す
				return 0b0001 + 1;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  ・clock_profile に沿ったマスター・クロックのブースト @n
					・インストラクション・クロックの設定。 @n
					・周辺クロック周期を設定。 @n
					・設定出来ない場合を検出（コンパイル時エラーによる停止）
		*/
		//-----------------------------------------------------------------//
		static void boost_master_clock() noexcept
		{
			// ベースクロック周波数の検査
			static_assert(check_base_clock_(), "BASE clock out of range.");
			static_assert(check_pll_base_(), "PLL_BASE out of range.");

			// 起動時 LOCO
			if(OSCT == clock_profile::OSC_TYPE::LOCO) {
				return;
			}

			device::SYSTEM::PRCR = 0xA500 | device::SYSTEM::PRCR.PRC0.b();

			// メインクロック強制発振とドライブ能力設定
			switch(OSCT) {
			case clock_profile::OSC_TYPE::XTAL:
				device::SYSTEM::MOSCWTCR = 13;  // for 12MHz OSC
				device::SYSTEM::PLLWTCR = 9;  // for 12MHz OSC

				device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
				while(device::SYSTEM::MOSCCR.MOSTP() != 0) {  // 「0」に書き換えた事を確認
					asm("nop");
				}
				break;
			case clock_profile::OSC_TYPE::EXT:
				device::SYSTEM::MOSCCR.MOSTP = 1;		// メインクロック発振器停止
				while(device::SYSTEM::MOSCCR.MOSTP() == 0) {  // 「1」に書き換えた事を確認
					asm("nop");
				}
				break;
			case clock_profile::OSC_TYPE::HOCO:
				device::SYSTEM::HOCOCR.HCSTP = 0;
				utils::delay::loop(1000);  // 安定動作待ち
				break;
			default:
				break;
			}

			uint32_t n = clock_profile::PLL_BASE / clock_profile::BASE;
			device::SYSTEM::PLLCR.STC = n - 1;
			device::SYSTEM::PLLCR2.PLLEN = 0; // PLL 動作
			utils::delay::loop(1500);  // PLL 起動待ち(CPU speed: LOCO: 125KHz)

			// 1/64 以上、分周出来ない設定は不可
			static_assert(check_clock_div_(clock_profile::FCLK), "FCLK can't divided.");
			static_assert(check_clock_div_(clock_profile::ICLK), "ICLK can't divided.");
			static_assert(check_clock_div_(clock_profile::BCLK), "BCLK can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKA), "PCLKA can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKB), "PCLKB can't divided.");

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(clock_profile::FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
								  | device::SYSTEM::SCKCR.BCK.b(clock_div_(clock_profile::BCLK))
								  | device::SYSTEM::SCKCR.PCKA.b(clock_div_(clock_profile::PCLKA))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(clock_profile::PCLKB));

			static_assert(usb_div_() >= 2 && usb_div_() <= 5, "USB Clock can't divided.");
			// 1/2:0b0001, 1/3:0b0010, 1/4:0b0011, 1/5:0b0100
			device::SYSTEM::SCKCR2.UCK = usb_div_() - 1;

			device::SYSTEM::SCKCR3.CKSEL = 0b100;   // PLL 選択

			if(OSCT == clock_profile::OSC_TYPE::XTAL || OSCT == clock_profile::OSC_TYPE::EXT) {
				device::SYSTEM::LOCOCR.LCSTP = 1;  // 低速オンチップオシレータ停止
				device::SYSTEM::HOCOPCR.HOCOPCNT = 1;	// HOCO 電源 OFF
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
