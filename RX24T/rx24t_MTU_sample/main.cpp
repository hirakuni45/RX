//=====================================================================//
/*! @file
    @brief  RX24T MTU3 サンプル @n
			・PB3/MTIOC0A (32) 周波数測定 @n
			・PA5/MTIOC1A (36) パルス出力 @n
			・P00 (4) に赤色LED+1000オーム（VF:1.9V）を吸い込みで接続する（インジケーター）
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

	typedef utils::fixed_fifo<char, 128> buffer;
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
	SYSTEM_IO::boost_master_clock();

	// タイマー設定（６０Ｈｚ）
	{
		auto intr_level = device::ICU::LEVEL::_4;
		cmt_.start(60, intr_level);
	}

	// SCI 設定
	{
		auto intr_level = device::ICU::LEVEL::_2;
		sci_.start(115200, intr_level);
	}

	// MTU0 設定
	{
		auto intr = device::ICU::LEVEL::_3;		
		if(!mtu0_io_.start_capture(MTU0::CHANNEL::A, MTU0_IO::CAPTURE::POSITIVE, intr)) {
			utils::format("MTU0 input capture start fail...\n");
		}
	}

	// MTU1 設定
	{
		uint32_t frq = 1000;
		if(!mtu1_io_.start_normal(MTU1::CHANNEL::A, frq, MTU1_IO::OUTPUT::L_TOGGLE)) {
			utils::format("MTU1 output start fail...\n");
		}
	}

	utils::format("RX24T MTU3 sample: base clock: %u [Hz]\n") % static_cast<uint32_t>(device::clock_profile::PCLKA);
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
