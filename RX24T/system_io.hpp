#pragma once
//=========================================================================//
/*!	@file
	@brief	RX13T/RX24T/RX24U システム制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX24T/system.hpp"
#include "RX24T/flash.hpp"
#if defined(SIG_RX13T)
#include "RX13T/clock_profile.hpp"
#elif defined(SIG_RX24T)
#include "RX24T/clock_profile.hpp"
#elif defined(SIG_RX24U)
#include "RX24U/clock_profile.hpp"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス
		@param[in]	OSCT	発信器タイプを設定
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
			} else if(OSCT == clock_profile::OSC_TYPE::EXT) {  // 外部入力の場合 20MHz 以下
				if(clock_profile::BASE > 20'000'000) ok = false;
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {  // 内部高速発信器は 32MHz Only (PLL input 1/4 選択)
				if(clock_profile::BASE != 8'000'000) ok = false;
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
		//-------------------------------------------------------------//
		/*!
			@brief  マスター・クロックのブースト
			@return エラーなら「false」
		*/
		//-------------------------------------------------------------//
		static bool boost_master_clock()
		{
			// ベースクロック周波数の検査
			static_assert(check_base_clock_(), "BASE out of range.");

			device::SYSTEM::PRCR = 0xA500 | 0b0111;	// クロック、低消費電力、関係書き込み許可

			while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");
			device::SYSTEM::OPCCR = 0;  // 高速モード選択
			while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");

//			device::SYSTEM::MOSCWTCR = 4;  // リセット時の値

			// メインクロック・ドライブ能力設定、内部発信
			switch(OSCT) {
			case clock_profile::OSC_TYPE::XTAL:
				device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV21.b(clock_profile::BASE >= 10'000'000);
				device::SYSTEM::MOSCCR.MOSTP = 0;  // メインクロック発振器動作
				{
					volatile auto tmp = device::SYSTEM::MOSCCR();
				}
				while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) { asm("nop"); }
				break;
			case clock_profile::OSC_TYPE::EXT:
				device::SYSTEM::MOSCCR.MOSTP = 1;  // メインクロック発振器停止
				{
					volatile auto tmp = device::SYSTEM::MOSCCR();
				}
				device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MOSEL.b(1);
				break;
			case clock_profile::OSC_TYPE::HOCO:
				device::SYSTEM::MOSCCR.MOSTP = 1;  // メインクロック発振器停止
				device::SYSTEM::PLLCR.PLIDIV = 0b10;  // 1/4
				device::SYSTEM::PLLCR.PLLSRCSEL = 1;  // HOCO 選択
				device::SYSTEM::HOCOWTCR.HSTS = 0b101;  // HOCO:32MHz の場合選択
				break;
			case clock_profile::OSC_TYPE::LOCO:
				device::SYSTEM::PRCR = 0xA500;
				break;
			}

			// Min: (x4.0) 0b000111, Max: (x15.5) 0b111110
			static_assert((clock_profile::PLL_BASE * 2 / clock_profile::BASE) >= 7, "PLL_BASE clock divider underflow.");
			static_assert((clock_profile::PLL_BASE * 2 / clock_profile::BASE) <= 31, "PLL_BASE clock divider overflow.");
			static_assert((clock_profile::PLL_BASE * 2 % clock_profile::BASE) == 0, "PLL_BASE clock can't divided.");
			device::SYSTEM::PLLCR.STC = (clock_profile::PLL_BASE * 2 / clock_profile::BASE) - 1;

			// 1/64 以上、分周出来ない設定は不可
			static_assert(check_clock_div_(clock_profile::FCLK), "FCLK can't divided.");
			static_assert(check_clock_div_(clock_profile::ICLK), "ICLK can't divided.");
#if defined(SIG_RX24T) || defined(SIG_RX24U)
			static_assert(check_clock_div_(clock_profile::PCLKA), "PCLKA can't divided.");
#endif
			static_assert(check_clock_div_(clock_profile::PCLKB), "PCLKB can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKD), "PCLKD can't divided.");

#if defined(SIG_RX13T)
			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(clock_profile::FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(clock_profile::PCLKB))
								  | device::SYSTEM::SCKCR.PCKD.b(clock_div_(clock_profile::PCLKD));
#else
			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(clock_profile::FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
								  | device::SYSTEM::SCKCR.PCKA.b(clock_div_(clock_profile::PCLKA))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(clock_profile::PCLKB))
								  | device::SYSTEM::SCKCR.PCKD.b(clock_div_(clock_profile::PCLKD))
								  | device::SYSTEM::SCKCR.PCKB_.b(clock_div_(clock_profile::PCLKB));
#endif
			device::SYSTEM::PLLCR2.PLLEN = 0;	// PLL 動作
			{
				volatile auto tmp = device::SYSTEM::PLLCR2();
			}
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

#if defined(SIG_RX24T) || defined(SIG_RX24U)
			// メモリーの WAIT 設定
			if(clock_profile::ICLK > 64'000'000) {
				device::SYSTEM::MEMWAIT = 0b10; // 64MHz 以上 wait 設定
			} else if(clock_profile::ICLK > 32'000'000) {
				device::SYSTEM::MEMWAIT = 0b01; // 32MHz 以上 64MHz 以下 wait 設定 
			} else {
				device::SYSTEM::MEMWAIT = 0b00; // wait 無し
			}
#endif
			device::SYSTEM::SCKCR3.CKSEL = 0b100;	// PLL 選択
			{  // dummy read register
				volatile auto tmp = device::SYSTEM::SCKCR3();
			}

			if(OSCT == clock_profile::OSC_TYPE::XTAL || OSCT == clock_profile::OSC_TYPE::EXT) {
				device::SYSTEM::ILOCOCR.ILCSTP = 1;  // 低速オンチップオシレータ停止
				device::SYSTEM::HOCOCR.HCSTP = 1;  // 高速オンチップオシレータ停止
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {
				device::SYSTEM::ILOCOCR.ILCSTP = 1;  // 低速オンチップオシレータ停止
			}

			// クロック関係書き込み不許可
			device::SYSTEM::PRCR = 0xA500;
#if defined(SIG_RX24T) || defined(SIG_RX24U)
			// ROM キャッシュを有効（標準）
			device::FLASH::ROMCE = 1;
#endif
			return true;
		}
	};
}
typedef device::system_io<device::clock_profile::OSCT> SYSTEM_IO;
