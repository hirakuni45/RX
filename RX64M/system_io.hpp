#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M システム制御 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX64M/system.hpp"

namespace device {

	//-------------------------------------------------------------//
	/*!
		@brief  ポートの初期設定
	*/
	//-------------------------------------------------------------//
	static void init_port()
	{
		PORT0::PCR = 0xff;
		PORT1::PCR = 0xff;
		PORT2::PCR = 0xff;
		PORT3::PCR = 0xff;
		PORT4::PCR = 0xff;
		PORT5::PCR = 0xff;
		PORT6::PCR = 0xff;
		PORT7::PCR = 0xff;
		PORT8::PCR = 0xff;
		PORT9::PCR = 0xff;
		PORTA::PCR = 0xff;
		PORTB::PCR = 0xff;
		PORTC::PCR = 0xff;
		PORTD::PCR = 0xff;
		PORTE::PCR = 0xff;
		PORTF::PCR = 0xff;
		PORTG::PCR = 0xff;
		PORTJ::PCR = 0xff;
	}


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
