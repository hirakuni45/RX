#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M システム制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX64M/system.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス
		@param[in]	base_clock	ベース・クロック周波数（１２ＭＨｚ）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base_clock = 12000000>
	struct system_io {

		//-------------------------------------------------------------//
		/*!
			@brief  システム・クロックの設定
		*/
		//-------------------------------------------------------------//
		static void setup_system_clock()
		{
			device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

			device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
			// メインクロック強制発振とドライブ能力設定
			device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);
			device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
			while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

			// Base Clock 12MHz
			device::SYSTEM::PLLCR.STC = 0b010011;		// PLL 10 倍(120MHz)
			device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
			while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) { asm("nop"); }

			device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(1)    // 1/2 (120/2=60)
								  | device::SYSTEM::SCKCR.ICK.b(0)    // 1/1 (120/1=120)
								  | device::SYSTEM::SCKCR.BCK.b(1)    // 1/2 (120/2=60)
								  | device::SYSTEM::SCKCR.PCKA.b(0)   // 1/1 (120/1=120)
								  | device::SYSTEM::SCKCR.PCKB.b(1)   // 1/2 (120/2=60)
								  | device::SYSTEM::SCKCR.PCKC.b(1)   // 1/2 (120/2=60)
								  | device::SYSTEM::SCKCR.PCKD.b(1);  // 1/2 (120/2=60)
			device::SYSTEM::SCKCR2.UCK = 0b0100;  // USB Clock: 1/5 (120/5=24)
			device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択
		}
	};
}
