//=====================================================================//
/*! @file
    @brief  RX24T ファースト・サンプル @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
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

	typedef utils::fifo<uint8_t, 128> BUFFER;
	device::sci_io<device::SCI1, BUFFER, BUFFER> sci_;

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
	// 10MHz X-Tal, 80MHz
	typedef device::system_io<10000000> SYSTEM_IO;
	SYSTEM_IO::setup_system_clock();

	// SCI 設定
	static const uint8_t sci_level = 2;
	sci_.start(115200, sci_level);

	// タイマー設定（６０Ｈｚ）
	uint8_t cmt_irq_level = 4;
	cmt_.start(60, cmt_irq_level);

	// MTU0 設定
	{
		uint32_t frq = 10000;
		if(!mtu0_io_.start_pwm2(MTU0::channel::A, MTU0_IO::OUTPUT_TYPE::LOW_TO_HIGH, frq)) {
			utils::format("MTU0 input capture start fail...\n");
		}
	}

	// MTU1 設定
	{
		uint32_t frq = 10000;
		if(!mtu1_io_.start_pwm2(MTU1::channel::A, MTU1_IO::OUTPUT_TYPE::HIGH_TO_LOW, frq)) {
			utils::format("MTU1 output start fail...\n");
		}
	}

	utils::format("RX24T MTU3 PWM sample: base clock: %4.2f [MHz]\n")
		% (static_cast<float>(F_PCLKA) * 1e-6);
	utils::format("  PB3/MTIOC0A (32): Left\n");
	utils::format("  PA5/MTIOC1A (36): Right\n");

	device::PORT0::PDR.B0 = 1; // output

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B0 = (cnt < 10) ? 0 : 1;
	}
}
