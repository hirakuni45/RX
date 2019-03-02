#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T システム制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX24T/system.hpp"
#include "RX24T/flash.hpp"

#ifndef F_ICLK
#  error "system_io.hpp requires F_ICLK to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス
		@param[in]	BASE_CLOCK	ベース・クロック周波数（１０ＭＨｚ）
		@param[in]	INTR_CLOCK	内臓クロック周波数（８０ＭＨｚ）
		@param[in]	EXT_CLOCK	外部クロック入力を使う場合「true」@n
								※クリスタル利用は「false」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t BASE_CLOCK = 10000000, uint32_t INTR_CLOCK = 80000000,
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
			@return エラーなら「false」
		*/
		//-------------------------------------------------------------//
		static bool setup_system_clock()
		{
			device::SYSTEM::PRCR = 0xA500 | 0b0111;	// クロック、低消費電力、関係書き込み許可

			// メモリーの WAIT 設定
			if(F_ICLK > 64000000) {
				device::SYSTEM::MEMWAIT = 0b10; // 64MHz 以上 wait 設定
			} else if(F_ICLK > 32000000) {
				device::SYSTEM::MEMWAIT = 0b01; // 32MHz 以上 64MHz 以下 wait 設定 
			} else {
				device::SYSTEM::MEMWAIT = 0b00; // wait 無し
			}

			while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");
			device::SYSTEM::OPCCR = 0;  // 高速モード選択
			while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");

			device::SYSTEM::MOSCWTCR = 9;	// 4ms wait
			// メインクロック・ドライブ能力設定、内部発信
			bool xtal = BASE_CLOCK >= 10000000;
			device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV21.b(xtal)
				| device::SYSTEM::MOFCR.MOSEL.b(EXT_CLOCK);
			device::SYSTEM::MOSCCR.MOSTP = 0;  // メインクロック発振器動作
			while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

			// Min: (x4.0) 0b000111, Max: (x15.5) 0b111110
			uint32_t n = INTR_CLOCK * 2 / BASE_CLOCK;
			if(n < 8) n = 8;
			else if(n > 31) n = 31;
			device::SYSTEM::PLLCR.STC = n - 1;

			device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(clock_div_(F_FCLK))
								  | device::SYSTEM::SCKCR.ICK.b(clock_div_(F_ICLK))
								  | device::SYSTEM::SCKCR.PCKA.b(clock_div_(F_PCLKA))
								  | device::SYSTEM::SCKCR.PCKB.b(clock_div_(F_PCLKB))
								  | device::SYSTEM::SCKCR.PCKD.b(clock_div_(F_PCLKD));

			device::SYSTEM::SCKCR3.CKSEL = 0b100;	// PLL 選択

			// クロック関係書き込み不許可
			device::SYSTEM::PRCR = 0xA500;

			// ROM キャッシュを有効（標準）
			device::FLASH::ROMCE = 1;

			return true;
		}
	};
}
