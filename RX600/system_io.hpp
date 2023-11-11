#pragma once
//=========================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX651/RX65N/RX66T/RX72T/RX72N/RX72M グループ・システム制御 @n
			※ USB を使う場合：96MHz, 144MHz, 192MHz, 240MHz のいづれか @n
			RX72x 系では、内部 PLL2 回路が追加され、Ethernet などに必要な 25MHz を得る為 @n
			16MHz を使います。 @n
			(16MHz x 12.5 -> 200MHz, 16MHz x 15 -> 240MHz) @n
			現状の実装では、PLL2 を USB のクロック源として利用する事は出来ません。 @n
			clock_profile::TURN_USB = true; の場合、48MHz を作る事が出来ない場合、コンパイルエラーとなります。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/system.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス @n
				RX71M はスーパーバイザモードでの変更が必要なので、 @n
				部分的な設定を「start.s」内で行います。 @n
				RX71M の場合、アセンブラにオプション「--defsym MEMWAIT=1」を渡す。
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


		static constexpr uint8_t clock_div_bus_(uint32_t clk) noexcept
		{
#if defined(SIG_RX72N) || defined(SIG_RX72M)
			if((clock_profile::PLL_BASE - (clk * 3)) < 3) {  // 1/3 設定の検出
				return 0b1001;
			}
#endif
			return clock_div_(clk);
		}


		static constexpr bool check_clock_div_bus_(uint32_t clk) noexcept
		{
			auto div = clock_div_bus_(clk);
			if((div & 0b0111) > 0b0110) {
				return false;  // overflow
			}
			if(div == 0b1001) {  // 1/3
				return true;
			} else {
				if((clk << div) != (clock_profile::PLL_BASE & (0xffffffff << div))) {
					return false;
				} else {
					return true;
				}
			}
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
			@brief  マスター・クロックのブースト @n
					インストラクション・クロックを最大速度にブーストする。
		*/
		//-----------------------------------------------------------------//
		static void boost_master_clock() noexcept
		{
			device::SYSTEM::PRCR = 0xA500 | device::SYSTEM::PRCR.PRC0.b() | device::SYSTEM::PRCR.PRC1.b();

			// ベースクロック周波数の検査
			static_assert(check_base_clock_(), "BASE out of range.");

//			device::SYSTEM::MOSCWTCR = 0x53;

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
				device::SYSTEM::MOSCCR.MOSTP = 1;  // メインクロック発振器停止
				{
					volatile auto tmp = device::SYSTEM::MOSCCR();
				}
				device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MOSEL.b();
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {  // 高速オンチップオシレータ
				uint8_t frq;
				if(clock_profile::BASE == 16'000'000) frq = 0b00;
				else if(clock_profile::BASE == 18'000'000) frq = 0b01;
				else if(clock_profile::BASE == 20'000'000) frq = 0b10;
				else frq = 0b00;
				device::SYSTEM::HOCOCR2.HCFRQ = frq;
				device::SYSTEM::HOCOCR.HCSTP = 0;  // 動作
				{
					volatile auto tmp = device::SYSTEM::HOCOCR();
				}
				while(device::SYSTEM::OSCOVFSR.HCOVF() == 0) { asm("nop"); }
				device::SYSTEM::PLLCR.PLLSRCSEL = 1;
			} else {
				device::SYSTEM::PRCR = 0xA500;
				return;
			}

#if defined(SIG_RX65N)
			if(clock_profile::ICLK >= 120'000'000) {  // 120MHz 以上の場合設定
				device::SYSTEM::ROMWT = 0b10;
			} else if(clock_profile::ICLK >= 100'000'000) {
				device::SYSTEM::ROMWT = 0b01;
			} else if(clock_profile::ICLK >= 50'000'000) {
				device::SYSTEM::ROMWT = 0b00;
			}
#endif
			// RX71M はスーパーバイザモードでの変更が必要なので、「start.s」内で行う。
			// RX71M の場合、アセンブラにオプション「--defsym MEMWAIT=1」を渡す。
#if defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX72N) || defined(SIG_RX72M)
			if(clock_profile::ICLK > 120'000'000) {  // 120MHz 以上の場合設定
				device::SYSTEM::MEMWAIT = 1;
				volatile auto tmp = device::SYSTEM::MEMWAIT();  // 読み出しを行う
			}
#endif
			// 1/64 以上、分周出来ない設定は不可
			// ※RX72N, RX72M などは BCLK: 1/3 を選択する事が出来る。
			static_assert(check_clock_div_(clock_profile::FCLK), "FCLK can't divided.");
			static_assert(check_clock_div_(clock_profile::ICLK), "ICLK can't divided.");
			static_assert(check_clock_div_bus_(clock_profile::BCLK), "BCLK can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKA), "PCLKA can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKB), "PCLKB can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKC), "PCLKC can't divided.");
			static_assert(check_clock_div_(clock_profile::PCLKD), "PCLKD can't divided.");

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(clock_profile::FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(clock_profile::ICLK))
								  | device::SYSTEM::SCKCR.BCK.b(clock_div_bus_(clock_profile::BCLK))
								  | device::SYSTEM::SCKCR.PCKA.b(clock_div_(clock_profile::PCLKA))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(clock_profile::PCLKB))
								  | device::SYSTEM::SCKCR.PCKC.b(clock_div_(clock_profile::PCLKC))
								  | device::SYSTEM::SCKCR.PCKD.b(clock_div_(clock_profile::PCLKD));
			{
				volatile auto tmp = device::SYSTEM::SCKCR();
			}

			// (x10.0) 0b010011, (x10.5) 0b010100, (x11.0) 0b010101, (x11.5) 0b010110
			// ... MAX x30.0
			static_assert((clock_profile::PLL_BASE * 2 / clock_profile::BASE) >= 20, "PLL_BASE clock divider underflow.");
			static_assert((clock_profile::PLL_BASE * 2 / clock_profile::BASE) <= 60, "PLL_BASE clock divider overflow.");
			static_assert((clock_profile::PLL_BASE * 2 % clock_profile::BASE) == 0, "PLL_BASE clock can't divided.");
			device::SYSTEM::PLLCR.STC = (clock_profile::PLL_BASE * 2 / clock_profile::BASE) - 1;
			device::SYSTEM::PLLCR2.PLLEN = 0;  // PLL 動作
			{
				volatile auto tmp = device::SYSTEM::PLLCR2();
			}
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) { asm("nop"); }

			static_assert(usb_div_() >= 2 && usb_div_() <= 5, "USB Clock can't divided.");
			// 1/2:0b0001, 1/3:0b0010, 1/4:0b0011, 1/5:0b0100
			device::SYSTEM::SCKCR2.UCK = usb_div_() - 1;

			// マイクロコントローラによっては、ICLK をブーストする前に FCLK 周期を設定する必要がある。
			device::FLASH::set_eepfclk(clock_profile::FCLK);

			device::SYSTEM::SCKCR3.CKSEL = 0b100;  // PLL 選択
			{  // dummy read register
				volatile auto tmp = device::SYSTEM::SCKCR3();
			}

			if(OSCT == clock_profile::OSC_TYPE::XTAL || OSCT == clock_profile::OSC_TYPE::EXT) {
				device::SYSTEM::LOCOCR.LCSTP = 1;  ///< 低速オンチップオシレータ停止
				device::SYSTEM::HOCOCR.HCSTP = 1;  ///< 高速オンチップオシレータ停止
				device::SYSTEM::HOCOPCR.HOCOPCNT = 1;  ///< 高速オンチップオシレーター電源 OFF
			} else if(OSCT == clock_profile::OSC_TYPE::HOCO) {
				device::SYSTEM::LOCOCR.LCSTP = 1;  ///< 低速オンチップオシレータ停止
			}

#if defined(SIG_RX66T) || defined(SIG_RX72T)
#else
			device::SYSTEM::SOSCWTCR = 0b01010;
			device::SYSTEM::SOSCCR = device::SYSTEM::SOSCCR.SOSTP.b(!clock_profile::TURN_SBC);
#endif
			device::SYSTEM::PRCR = 0xA500;	// クロック関係書き込み不許可

#if defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX72N) || defined(SIG_RX72M)
			// ROM キャッシュを有効（標準）
			device::SYSTEM::ROMCE = 1;
#endif
#if defined(__TFU)
			__init_tfu();
#endif
		}


#if defined(SIG_RX72N) || defined(SIG_RX72M)
		//-----------------------------------------------------------------//
		/*!
			@brief  PPLL 制御を使って PHY 向け 25MHz を出力する。
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool setup_phy25() noexcept
		{
			if(clock_profile::BASE != 16'000'000) {  // ベースクロックが 16MHz 以外は、生成不可とする。 
				return false;
			}

			bool ret = true;
			device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

			device::SYSTEM::PACKCR.OUTCKSEL = 1;

			// PPLIDIV: 1/2, PPLSTC: x12.5 (100MHz)
			device::SYSTEM::PPLLCR  = device::SYSTEM::PPLLCR.PPLIDIV.b(0b01)
								    | device::SYSTEM::PPLLCR.PPLSTC.b(0b011000);
			device::SYSTEM::PPLLCR2 = device::SYSTEM::PPLLCR2.PPLLEN.b(1);  // 発信許可

			// PPLL 安定待ち
			while(device::SYSTEM::OSCOVFSR.PPLOVF() == 0) { asm("nop"); }

			// PPLLCR3: 1/4 (25MHz)
			device::SYSTEM::PPLLCR3 = device::SYSTEM::PPLLCR3.PPLCK.b(0b0011);

			// クロック関係書き込み不許可
			device::SYSTEM::PRCR = 0xA500;

			// ポート・マッピングを行う必要があるが、あえて、ここでは許可しない。
			// ※このヘッダーに、port_map.hpp の依存を無くす為。
			// deveice::port_map::turn_CLKOUT25M();

			return true;
		}
#endif
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
