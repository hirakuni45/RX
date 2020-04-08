#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX651/RX65N/RX66T/RX72T/RX72N/RX72M グループ・システム制御 @n
			※RX24T は構成が大きく異なるので、RX24T/system_io.hpp に分離しています。@n
			※ USB を使う場合：96MHz, 144MHz, 192MHz, 240MHz のいづれか @n
			※ 通常ベースクロックは、12MHz、24MHz を使います。@n
			RX72x 系では、内部 PLL 回路が追加され、Ethernet などに必要な 25MHz を得る為 @n
			16MHz を使います。@n
			(16MHz x 12.5 -> 200MHz, 16MHz x 15 -> 240MHz)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/system.hpp"

#if defined(F_ICLK) && defined(F_PCLKA) && defined(F_PCLKB) && defined(F_PCLKC) && defined(F_PCLKD) && defined(F_FCLK) && defined(F_BCLK) 
#else  
#  error "system_io.hpp requires F_[IFB]CLK and F_PCLK[ABCD] to be defined"
#endif

#if defined(SIG_RX24T)
#  error "system_io.hpp: Not available on RX24T"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス @n
				INTR_CLOCK は、内部 PLL で扱える最大速度です、@n
				外部クリスタルを微妙な周波数にする場合、その整数倍にしなければなりません。@n
		@param[in]	BASE_CLOCK	ベース・クロック周波数（１２ＭＨｚ）
		@param[in]	INTR_CLOCK	内臓クロック周波数（２４０ＭＨｚ）@n
								※USB を使う場合、「INTR_CLOCK」は48の倍数である事
		@param[in]	EXT_CLOCK	外部クロックに入力を行う場合「true」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t BASE_CLOCK = 12'000'000, uint32_t INTR_CLOCK = 240'000'000, bool EXT_CLOCK = false>
	struct system_io {

		static uint8_t clock_div_(uint32_t clk) noexcept
		{
			uint8_t div = 0;
			while(clk < INTR_CLOCK) {
				++div;
				clk <<= 1;
			}
			return div;
		}

		//-------------------------------------------------------------//
		/*!
			@brief  システム・クロックの設定
		*/
		//-------------------------------------------------------------//
		static void setup_system_clock() noexcept
		{
			device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

			device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
			// メインクロック強制発振とドライブ能力設定
			uint8_t modrv2 = 0b11;
			if(BASE_CLOCK > 20'000'000) modrv2 = 0b00;
			else if(BASE_CLOCK > 16'000'000) modrv2 = 0b01;
			else if(BASE_CLOCK > 8'000'000) modrv2 = 0b10;
			device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(modrv2)
						  | device::SYSTEM::MOFCR.MOSEL.b(EXT_CLOCK);
///						  device::SYSTEM::MOFCR.MOFXIN.b(1)
			device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
			while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) { asm("nop"); }

			// RX71M、240MHz 時の MEMWAIT はスーパーバイザモードでの設定が必須なので、
			// device::SYSTEM::MEMWAIT = 1; は、start.s で設定される。

#if defined(SIG_RX65N)
			if(F_ICLK >= 120'000'000) {  // 120MHz 以上の場合設定
				device::SYSTEM::ROMWT = 0b10;
			} else if(F_ICLK >= 100'000'000) {
				device::SYSTEM::ROMWT = 0b01;
			} else if(F_ICLK >= 50'000'000) {
				device::SYSTEM::ROMWT = 0b00;
			}
#endif
#if defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72T) || defined(SIG_RX72N)
			if(F_ICLK > 120'000'000) {  // 120MHz 以上の場合設定
				device::SYSTEM::MEMWAIT = 1;
			}
#endif
			// (x10.0) 0b010011, (x10.5) 0b010100, (x11.0) 0b010101, (x11.5) 0b010110
			// ... MAX x30.0
			uint32_t n = INTR_CLOCK * 2 / BASE_CLOCK;
			if(n < 20) n = 20;
			else if(n > 60) n = 60;
			n -= 20;
			device::SYSTEM::PLLCR.STC = n + 0b010011;  // base x10
			device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) { asm("nop"); }

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(F_FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(F_ICLK))
								  | device::SYSTEM::SCKCR.BCK.b(clock_div_(F_BCLK))
								  | device::SYSTEM::SCKCR.PCKA.b(clock_div_(F_PCLKA))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(F_PCLKB))
								  | device::SYSTEM::SCKCR.PCKC.b(clock_div_(F_PCLKC))
								  | device::SYSTEM::SCKCR.PCKD.b(clock_div_(F_PCLKD));
			{  // USB Master Clock の設定
				auto usb_div = INTR_CLOCK / 48000000;
				if(usb_div >= 2 && usb_div <= 5) {
					// 1/2, 1/3, 1/4, 1/5
					device::SYSTEM::SCKCR2.UCK = usb_div - 1;
				}
			}
			device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

			device::SYSTEM::LOCOCR.LCSTP = 1;  ///< 低速オンチップオシレータ停止
			device::SYSTEM::HOCOCR.HCSTP = 1;  ///< 高速オンチップオシレータ停止

			// クロック関係書き込み不許可
			device::SYSTEM::PRCR = 0xA500;

#if defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72T) || defined(SIG_RX72N)
			// ROM キャッシュを有効（標準）
			device::SYSTEM::ROMCE = 1;
#endif
		}
	};


	//-------------------------------------------------------------//
	/*!
		@brief  ソフト・リセットの起動
	*/
	//-------------------------------------------------------------//
	inline void assert_soft_reset()
	{
		device::SYSTEM::PRCR = 0xA502;
		device::SYSTEM::SWRR = 0xA501;
		device::SYSTEM::PRCR = 0xA500;
	}


	//-------------------------------------------------------------//
	/*!
		@brief  SCI マスタークロック取得
		@param[in]	per		ペリフェラル型
		@return SCI マスタークロック
	*/
	//-------------------------------------------------------------//
	inline uint32_t get_sci_master_clock(peripheral per) noexcept
	{
#if defined(SIG_RX66T)
		if(per == peripheral::SCI11 || per == peripheral::SCI11C) {
			return F_PCLKA;
		}
#endif
		return F_PCLKB;
	}


	//-------------------------------------------------------------//
	/*!
		@brief  MTU マスタークロック取得
		@return MTU マスタークロック
	*/
	//-------------------------------------------------------------//
	inline uint32_t get_mtu_master_clock() noexcept
	{
#if defined(SIG_RX66T)
		return F_PCLKC;
#else
		return F_PCLKA;
#endif
	}
}
