//=====================================================================//
/*! @file
    @brief  RX64M ファースト・サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX64M/system.hpp"
#include "RX600/port.hpp"

namespace {

	void wait_delay_(uint32_t n)
	{
		// とりあえず無駄ループ
		for(uint32_t i = 0; i < n; ++i) {
			asm("nop");
		}
	}

}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

#if 0
	device::SYSTEM::MOSCWTCR.MSTS = 0b01101;	// 131072 サイクル待ち
	device::SYSTEM::MOSCCR.MOSTP = 0;			// メインクロック発振器動作
	dummy_ = device::SYSTEM::MOSCCR.MOSTP();
	device::SYSTEM::MOFCR.MOFXIN = 1;			// メインクロック強制発振
	dummy_ = device::SYSTEM::MOFCR.MOFXIN();
	wait_delay(5000);

	device::SYSTEM::PLLCR.STC = 0xf;			// PLL 16 倍(192MHz)
	device::SYSTEM::PLLWTCR.PSTS = 0b01010;		// 131072 サイクル待ち
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	wait_delay(5000);

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(3)		// 1/8 (192/8=24)
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2 (192/2=96)
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/4 (192/4=48)
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2 (192/2=96)
						  | device::SYSTEM::SCKCR.PCKB.b(2)		// 1/4 (192/4=48)
						  | device::SYSTEM::SCKCR.PCKC.b(2)		// 1/4 (192/8=48)
						  | device::SYSTEM::SCKCR.PCKD.b(2);	// 1/4 (192/8=48)
	device::SYSTEM::SCKCR3.CKSEL = 4;	///< PLL 回路選択
#endif


	uint32_t wait = 10000;
	device::PORT0.PDR.B7 = 1; // output
	while(1) {
		wait_delay_(wait);
		device::PORT0.PODR.B7 = 0;
		wait_delay_(wait);
		device::PORT0.PODR.B7 = 1;
	}
}
