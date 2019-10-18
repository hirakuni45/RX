//=====================================================================//
/*! @file
    @brief  RX64M CAN サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/sci_io.hpp"
#include "common/cmt_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/delay.hpp"
#include "common/command.hpp"


namespace {

	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;

	typedef device::cmt_io<device::CMT0> CMT;
	CMT		cmt_;

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

	{  // タイマー設定（６０Ｈｚ）
		uint8_t int_level = 4;
		cmt_.start(60, int_level);
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}

	utils::format("RX64M DMAC sample start\n");

	cmd_.set_prompt("# ");

	LED::DIR = 1;

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		if(cmd_.service()) {

		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
