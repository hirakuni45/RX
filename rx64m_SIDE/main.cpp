//=====================================================================//
/*! @file
    @brief  RX64M SIDE sample @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"

#include "side/arcade.h"

#include "../RAYTRACER_sample/raytracer.hpp"

namespace {

	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
// SCI ポートの第二候補を選択する場合
//	typedef device::sci_io<SCI_CH, RXB, TXB, device::port_map::option::SECOND> SCI;
	SCI		sci_;

	typedef device::cmt_io<device::CMT0> CMT;
	CMT		cmt_;

	InvadersMachine side_;
}

extern "C" {

	void draw_pixel(int x, int y, int r, int g, int b)
	{
		volatile uint16_t c = (static_cast<uint16_t>(r & 0xf8) << 8)
				   | (static_cast<uint16_t>(g & 0xfc) << 3)
				   | (static_cast<uint16_t>(b & 0xf8) >> 3);
//		tft_.plot(x, y, c);
	}

	void draw_text(int x, int y, const char* t)
	{
//		render_.fill_box(x, y, strlen(t) * 8, 16, render_.get_back_color());
//		render_.draw_text(x, y, t);
	}

	uint32_t millis(void)
	{
		// x 16.6667
//		return (glcdc_io_.get_vpos_count() * 4267) >> 8;
		return cmt_.get_counter() * 10;
	}

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	// syscalls.c から呼ばれる、標準入力（stdin）
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

	{  // タイマー設定（100Hz）
		uint8_t intr = 4;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		uint8_t intr = 2;        // 割り込みレベル
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	utils::format("Start SIDE sample\n");	

	utils::format("PLLCR.STC: %d\n") % static_cast<uint16_t>(device::SYSTEM::PLLCR.STC());
	utils::format("ICK: %d\n") % static_cast<uint16_t>(device::SYSTEM::SCKCR.ICK());

	doRaytrace(4, 320, 240);


	LED::DIR = 1;
	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
		}
		if(cnt < 25) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}

		// エコーバック処理
		while(sci_length() > 0) {
			auto ch = sci_getch();
			sci_putch(ch);
		}
	}
}
