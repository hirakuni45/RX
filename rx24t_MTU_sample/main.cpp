//=====================================================================//
/*! @file
    @brief  RX24T MTU3 サンプル @n
			・PB3/MTIOC0A (32) 周波数測定 @n
			・PA5/MTIOC1A (36) パルス出力 @n
			・P00 (4) に赤色LED+1000オーム（VF:1.9V）を吸い込みで接続する（インジケーター）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/mtu_io.hpp"

namespace {

	device::cmt_io<device::CMT0>  cmt_;

	typedef utils::fifo<uint8_t, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

	typedef device::MTU0 MTU0;
	typedef device::mtu_io<MTU0> MTU0_IO;
	MTU0_IO mtu0_io_;

	typedef device::MTU1 MTU1;
	typedef device::mtu_io<MTU1> MTU1_IO;
	MTU1_IO mtu1_io_;
}

extern "C" {

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	char sci_getch(void)
	{
		return sci_.getch();
	}

}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MEMWAIT = 0b10; // 80MHz 動作 wait 設定

	while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");
	device::SYSTEM::OPCCR = 0;  // 高速モード選択
	while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");

	// clock osc 10MHz
	device::SYSTEM::MOSCWTCR = 9;	// 4ms wait
	// メインクロック・ドライブ能力設定、内部発信
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV21.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;  // メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	device::SYSTEM::PLLCR.STC = 0b001111;		// PLL input: 1, PLL 8 倍(80MHz)
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/4 (80/4=20)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (80/1=80)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (80/1=80)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (80/2=40)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	// タイマー設定（６０Ｈｚ）
	{
		uint8_t intr_level = 4;
		cmt_.start(60, intr_level);
	}

	// SCI 設定
	{
		uint8_t intr_level = 2;
		sci_.start(115200, intr_level);
	}

	// MTU0 設定
	{
		uint8_t intr = 3;		
		if(!mtu0_io_.start_capture(MTU0::channel::A, MTU0_IO::CAPTURE_TYPE::POSITIVE, intr)) {
			utils::format("MTU0 input capture start fail...\n");
		}
	}

	// MTU1 設定
	{
		uint32_t frq = 1000;
		if(!mtu1_io_.start_normal(MTU1::channel::A, MTU1_IO::OUTPUT_TYPE::TOGGLE, frq)) {
			utils::format("MTU1 output start fail...\n");
		}
	}

	utils::format("RX24T MTU3 sample: base clock: %u [Hz]\n") % static_cast<uint32_t>(F_PCLKA);
	utils::format("  PB3/MTIOC0A (32): Input Capture\n");
	utils::format("  PA5/MTIOC1A (36): Pluse Output (Compare Match Timer)\n");

	device::PORT0::PDR.B0 = 1; // output

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

//		auto n = mtu0_io_.get_capture_tick();
//		if(cap != n) {
//			cap = n;
//			capcnt = mtu0_io_.get_capture();
//		}

		++cnt;
		if(cnt >= 30) {
			const auto& cap = mtu0_io_.get_capture();

			float a = static_cast<float>(mtu0_io_.get_base_clock()) / static_cast<float>(cap.all_count_);
			utils::format("Capture: %7.2f [Hz]\n") % a;
			cnt = 0;
		}
		device::PORT0::PODR.B0 = (cnt < 10) ? 0 : 1;

	}
}
