//=====================================================================//
/*! @file
    @brief  RX64M TPU サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/sci_io.hpp"
#include "common/tpu_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/delay.hpp"
#include "common/command.hpp"

namespace {

	typedef device::tpu_io<device::TPU0, utils::null_task> TPU;
	TPU		tpu_;

	typedef utils::fixed_fifo<char, 128> BUFFER;
	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
	SCI		sci_;

	utils::command<256> cmd_;
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

	void sci_puts(const char *str)
	{
		sci_.puts(str);
	}

	uint16_t sci_length(void)
	{
		return sci_.recv_length();
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::system_io<12000000>::setup_system_clock();

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}

	utils::format("RX64M TPU sample start\n");

	{  // TPU タイマー設定（６０Ｈｚ）
		uint8_t int_level = 4;
		if(!tpu_.start(60, int_level)) {
			utils::format("TPU not start...\n");
		}
	}

	cmd_.set_prompt("# ");

	device::PORT0::PDR.B5 = 1;
	device::PORT0::PDR.B7 = 1;

	uint32_t cnt = 0;
	while(1) {
		tpu_.sync();

		if(cmd_.service()) {
			utils::format("Count: %d\n") % tpu_.get_counter();
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B7 = (cnt < 10) ? 0 : 1;
	}
}
