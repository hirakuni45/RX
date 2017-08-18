#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T システム制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/port.hpp"
#include "RX24T/system.hpp"

namespace device {

	//-------------------------------------------------------------//
	/*!
		@brief  ポートの初期設定
	*/
	//-------------------------------------------------------------//
	static void init_port()
	{
		// LFQFP:100
		PORT0::PCR = 0b00000000;	// P00,P01,P02
		PORT1::PCR = 0b00000000;	// P10,P11
		PORT2::PCR = 0b00000000;	// P20,P21,P22,P23,P24
		PORT3::PCR = 0b00000000;	// P30,P31,P32,P33
		PORT4::PCR = 0b00000000;	// P40,P41,P42,P43,P44,P45,P46,P47 (analog input)
		PORT5::PCR = 0b00000000;	// P50,P51,P52,P53,P54,P55 (analog input)
		PORT6::PCR = 0b00000000;	// P60,P61,P62,P63,P64,P65 (analog input)
		PORT7::PCR = 0b00000000;	// P70,P71,P72,P73,P74,P75,P76
		PORT8::PCR = 0b00000000;	// P80,P81,P82
		PORT9::PCR = 0b00000000;	// P90,P91,P92,P93,P94,P95,P96
		PORTA::PCR = 0b00000000;	// PA0,PA1,PA2,PA3,PA4,PA5
		PORTB::PCR = 0b00000000;	// PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7
//		PORTC::PCR = 0b00000000;
		PORTD::PCR = 0b00000000;	// PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7
		PORTE::PCR = 0b00000000;	// PE0,PE1,PE2,PE3,PE4,PE5
//		PORTF::PCR = 0b00000000;
//		PORTG::PCR = 0b00000000;
//		PORTJ::PCR = 0b00000000;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  systen_io クラス
		@param[in]	base_clock	ベース・クロック周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base_clock>
	struct system_io {

		//-------------------------------------------------------------//
		/*!
			@brief  システム・クロックの設定
			@param[in]	system_clock	システム・クロック @n
						※内部ＰＬＬの最大周波数（８０ＭＨｚ）
			@return エラーなら「false」
		*/
		//-------------------------------------------------------------//
		static bool setup_system_clock(uint32_t system_clock = 80000000)
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

			uint8_t x = system_clock * 2 / base_clock;
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
