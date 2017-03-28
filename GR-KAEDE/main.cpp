//=====================================================================//
/*! @file
    @brief  GR-KAEDE(RX64M) ファースト・サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"

namespace {

	void wait_delay_(uint32_t n)
	{
		// とりあえず無駄ループ
		for(uint32_t i = 0; i < n; ++i) {
			asm("nop");
		}
	}

}

extern "C" {
	void sci_putch(char ch)
	{
//		sci_.putch(ch);
	}

	char sci_getch(void)
	{
//		return sci_.getch();
		return 0;
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);			
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	// Base Clock 12MHz
	// PLLDIV: 1/2, STC: 16 倍(96MHz)
	device::SYSTEM::PLLCR = device::SYSTEM::PLLCR.PLIDIV.b(1) |
							device::SYSTEM::PLLCR.STC.b(0b011111);
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(1)		// 1/2 (96/2=48)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (96/1=96)
						  | device::SYSTEM::SCKCR.BCK.b(1)		// 1/2 (96/2=48)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (96/1=96)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (96/2=48)
						  | device::SYSTEM::SCKCR.PCKC.b(1)		// 1/2 (96/2=48)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (96/2=48)
	device::SYSTEM::SCKCR2.UCK = 0b0011;  // USB Clock: 1/4 (96/4=24)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	uint32_t wait = 10000000;
	device::PORTC::PDR.B0 = 1; // output
	while(1) {
		wait_delay_(wait);
		device::PORTC::PODR.B0 = 0;
		wait_delay_(wait);
		device::PORTC::PODR.B0 = 1;
	}
}
