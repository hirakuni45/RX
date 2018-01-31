//=====================================================================//
/*! @file
    @brief  RX64M UART(SCI1)サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/sci_io.hpp"
#include "common/cmt_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/delay.hpp"
#include "common/command.hpp"

namespace {

	typedef device::cmt_io<device::CMT0, utils::null_task> CMT;
	CMT		cmt_;

//	typedef utils::fifo<uint8_t, 128> BUFFER;
//	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
//	SCI		sci_;

	typedef utils::fifo<uint8_t, 128> RX_BUF;
	typedef utils::fifo<uint8_t, 256> TX_BUF;

	// DC2 interface (SCI2, SECOND)
	typedef device::sci_io<device::SCI2, RX_BUF, TX_BUF, device::port_map::option::SECOND> SCI2;

	// DC1 interface (SCI6, FIRST)
	typedef device::sci_io<device::SCI6, RX_BUF, TX_BUF> SCI6;

	SCI6	sci_;

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

	utils::format("Start RX71M Ignitor\n");

#if 0
	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}
#endif

	cmd_.set_prompt("# ");

	device::PORTC::PDR.B0 = 1; // output
	device::PORTC::PDR.B1 = 1; // output
	device::PORT0::PDR.B2 = 1; // output
	device::PORT0::PDR.B3 = 1; // output

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		if(cmd_.service()) {
		}

		++cnt;
		if(cnt >= 32) {
			cnt = 0;
		}
		device::PORTC::PODR.B0 = (((cnt + 0)  & 31) < 8) ? 1 : 0;
		device::PORTC::PODR.B1 = (((cnt + 8)  & 31) < 8) ? 1 : 0;
		device::PORT0::PODR.B2 = (((cnt + 16) & 31) < 8) ? 1 : 0;
		device::PORT0::PODR.B3 = (((cnt + 24) & 31) < 8) ? 1 : 0;
	}
}
