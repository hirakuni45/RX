//=====================================================================//
/*! @file
    @brief  RX24T ファースト・サンプル @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/mtu_io.hpp"

namespace {

	device::cmt_mgr<device::CMT0>  cmt_;

	typedef utils::fixed_fifo<char, 128> BUFFER;
	device::sci_io<device::SCI1, BUFFER, BUFFER> sci_;

	typedef device::mtu_io<device::MTU0> MTU0;
	MTU0 	mtu0_;

	typedef device::mtu_io<device::MTU1> MTU1;
	MTU1 	mtu1_;
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
	SYSTEM_IO::boost_master_clock();

	// SCI 設定
	auto sci_level = device::ICU::LEVEL::_2;
	sci_.start(115200, sci_level);

	// タイマー設定（６０Ｈｚ）
	auto cmt_irq_level = device::ICU::LEVEL::_4;
	cmt_.start(60, cmt_irq_level);

	// MTU0 設定
	{
		uint32_t frq = 10000;
		if(!mtu0_.start_pwm2(MTU0::CHANNEL::A, frq,
			MTU0::port_t(MTU0::CHANNEL::B, MTU0::OUTPUT::L_TO_H, device::port_map_mtu::ORDER::FIRST))) {
			utils::format("MTU0 input capture start fail...\n");
		}
	}

	// MTU1 設定
	{
		uint32_t frq = 10000;
		if(!mtu1_.start_pwm2(MTU1::CHANNEL::A, frq,
			MTU1::port_t(MTU1::CHANNEL::B, MTU1::OUTPUT::H_TO_L, device::port_map_mtu::ORDER::FIRST))) {
			utils::format("MTU1 output start fail...\n");
		}
	}

	utils::format("RX24T MTU3 PWM sample: base clock: %4.2f [MHz]\n")
		% (static_cast<float>(device::clock_profile::PCLKA) * 1e-6);
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
