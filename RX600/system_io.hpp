#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX651/RX65N/RX66T グループ・システム制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/system.hpp"

#ifndef F_ICLK
#  error "system_io.hpp requires F_ICLK to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス
		@param[in]	BASE_CLOCK	ベース・クロック周波数（１２ＭＨｚ）
		@param[in]	INTR_CLOCK	内臓クロック周波数（２４０ＭＨｚ）
		@param[in]	EXT_CLOCK	外部クロックに入力を行う場合「true」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t BASE_CLOCK = 12000000, uint32_t INTR_CLOCK = 240000000,
		bool EXT_CLOCK = false>
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
			if(BASE_CLOCK > 20000000) modrv2 = 0b00;
			else if(BASE_CLOCK > 16000000) modrv2 = 0b01;
			else if(BASE_CLOCK > 8000000) modrv2 = 0b10;
			device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(modrv2)
						  | device::SYSTEM::MOFCR.MOSEL.b(EXT_CLOCK);
///						  device::SYSTEM::MOFCR.MOFXIN.b(1)
			device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
			while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) { asm("nop"); }

			// RX71M、240MHz 時の MEMWAIT はスーパーバイザモードでの設定が必須なので、
			// device::SYSTEM::MEMWAIT = 1; は、start.s で設定される。

#if defined(SIG_RX65N)
			if(F_ICLK >= 120000000) {  // 120MHz 以上の場合設定
				device::SYSTEM::ROMWT = 0b10;
			} else if(F_ICLK >= 100000000) {
				device::SYSTEM::ROMWT = 0b01;
			} else if(F_ICLK >= 50000000) {
				device::SYSTEM::ROMWT = 0b00;
			}
#endif
#if defined(SIG_RX66T)
			if(F_ICLK > 120000000) {  // 120MHz 以上の場合設定
				device::SYSTEM::MEMWAIT = 1;
			}
#endif
			// (x10.0) 0b010011, (x10.5) 0b010100, (x11.0) 0b010101, (x11.5) 0b010110
			// ... MAX x30.0
			uint32_t n = INTR_CLOCK * 2 / BASE_CLOCK;
			if(n < 20) n = 20;
			else if(n > 60) n = 60;
			n -= 20;
			device::SYSTEM::PLLCR.STC = n + 0b010011;  // base 240MHz(12MHz)
			device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) { asm("nop"); }

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(F_FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(F_ICLK))
								  | device::SYSTEM::SCKCR.BCK.b(clock_div_(F_BCLK))
								  | device::SYSTEM::SCKCR.PCKA.b(clock_div_(F_PCLKA))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(F_PCLKB))
								  | device::SYSTEM::SCKCR.PCKC.b(clock_div_(F_PCLKC))
								  | device::SYSTEM::SCKCR.PCKD.b(clock_div_(F_PCLKD));
			device::SYSTEM::SCKCR2.UCK = 0b0100;  // USB Clock: 1/5 (120/5=24)
			device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

			// クロック関係書き込み不許可
			device::SYSTEM::PRCR = 0xA500;

#if defined(SIG_RX65N) || defined(SIG_RX66T)
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
}
