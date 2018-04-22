//=====================================================================//
/*! @file
    @brief  RTK5RX65N ファースト・サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/cmt_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/command.hpp"

namespace {

	typedef device::system_io<12000000> SYSTEM_IO;

	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;

	typedef device::cmt_io<device::CMT0, utils::null_task> CMT;
	CMT		cmt_;

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<device::SCI9, RECV_BUFF, SEND_BUFF> SCI;
	SCI		sci_;

	utils::command<64> command_;

}


extern "C" {

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length()
	{
		return sci_.recv_length();
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	{  // タイマー設定 100Hz
		uint8_t cmt_irq_level = 4;
		cmt_.start(100, cmt_irq_level);
	}

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	utils::format("RTK5RX65N Start\n");

	command_.set_prompt("# ");

	LED::DIR = 1;
	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		if(command_.service()) {
			auto cmdn = command_.get_words();
			if(cmdn >= 1) {
			}
		}

		++cnt;
		if((cnt % 50) < 15) LED::P = 0;
		else LED::P = 1; 

//		utils::delay::milli_second(250);
//		LED::P = 0;
//		utils::delay::milli_second(250);
//		LED::P = 1;
	}
}
