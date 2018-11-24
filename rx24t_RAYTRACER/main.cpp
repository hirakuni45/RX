//=====================================================================//
/*! @file
    @brief  RX24T RAYTRACER サンプル
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
#include "common/format.hpp"
#include "common/command.hpp"

#include "RTK5_RAYTRACER/raytracer.hpp"

namespace {

    typedef device::system_io<10000000> SYSTEM_IO;

	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;

	typedef device::cmt_io<device::CMT0, utils::null_task> CMT;
	CMT		cmt_;

	// 標準シリアルポート設定
	typedef utils::fixed_fifo<char, 1024> RBF;
	typedef utils::fixed_fifo<char,  128> SBF;
	typedef device::sci_io<device::SCI1, RBF, SBF> SCI;
	SCI		sci_;

	typedef utils::command<256> COMMAND;
	COMMAND command_;	
}

extern "C" {

	void draw_pixel(int x, int y, int r, int g, int b)
	{
		volatile uint16_t c = (static_cast<uint16_t>(r & 0xf8) << 8)
				   | (static_cast<uint16_t>(g & 0xfc) << 3)
				   | (static_cast<uint16_t>(b & 0xf8) >> 3);
		utils::delay::micro_second(5);
//		render_.plot(x, y, c);
	}


	void draw_text(int x, int y, const char* t)
	{
//		render_.fill_box(x, y, strlen(t) * 8, 16, render_.get_back_color());
//		render_.draw_text(x, y, t);
	}


	uint32_t millis(void)
	{
		return cmt_.get_counter() * 10;
	}


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

	// タイマー設定（１００Ｈｚ）
	{
		uint8_t intr = 1;
		cmt_.start(100, intr);
	}

	// SCI 設定
	{
		uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	utils::format("RX24T Raytracer\n");

	command_.set_prompt("# ");

	LED::DIR = 1;

	doRaytrace(1, 320, 240);

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		// コマンド入力と、コマンド解析
		if(command_.service()) {
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
