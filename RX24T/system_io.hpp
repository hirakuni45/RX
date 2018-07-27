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

#ifndef F_ICLK
#  error "system_io.hpp requires F_ICLK to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス
		@param[in]	base_clock	ベース・クロック周波数（標準：１０ＭＨｚ）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base_clock = 10000000>
	struct system_io {

		//-------------------------------------------------------------//
		/*!
			@brief  システム・クロックの設定
			@return エラーなら「false」
		*/
		//-------------------------------------------------------------//
		static bool setup_system_clock()
		{
			device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

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
			device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV21.b(1);
			device::SYSTEM::MOSCCR.MOSTP = 0;  // メインクロック発振器動作
			while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

			// ベースクロックからマルチプライヤを計算
			uint8_t x = F_ICLK * 2 / base_clock;
			if(x < (4 * 2) || x >= (16 * 2)) return false;
			x -= 1;
			device::SYSTEM::PLLCR.STC = x;

			uint32_t sysclk = ((static_cast<uint32_t>(x) + 1) * base_clock) / 2;

			// Max: 32MHz
			uint8_t fck = (sysclk / F_FCLK) - 1;
			if(fck > 6) return false;

			uint8_t ick = (sysclk / F_ICLK) - 1;
			if(ick > 6) return false;

			uint8_t pcka = (sysclk / F_PCLKA) - 1;
			if(pcka > 6) return false;
			uint8_t pckb = (sysclk / F_PCLKB) - 1;
			if(pckb > 6) return false;
			uint8_t pckd = (sysclk / F_PCLKD) - 1;
			if(pckd > 6) return false;

			device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(fck)
								  | device::SYSTEM::SCKCR.ICK.b(ick)     // Max: 80MHz
								  | device::SYSTEM::SCKCR.PCKA.b(pcka)	 // Max: 80MHz
								  | device::SYSTEM::SCKCR.PCKB.b(pckb)	 // Max: 40MHz
								  | device::SYSTEM::SCKCR.PCKD.b(pckd);	 // Max: 40MHz

			device::SYSTEM::SCKCR3.CKSEL = 0b100;	// PLL 選択

			return true;
		}
	};
}
