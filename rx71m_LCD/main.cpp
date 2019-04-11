//=====================================================================//
/*! @file
    @brief  TFT-LCD(R61505W, 320x240) サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/cmt_io.hpp"

#include "chip/bus_rw.hpp"
#include "chip/R61505.hpp"

#include "../RAYTRACER_sample/raytracer.hpp"

#include "graphics/font8x16.hpp"
#include "graphics/font.hpp"
#include "graphics/graphics.hpp"

namespace {

	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
// SCI ポートの第二候補を選択する場合
//	typedef device::sci_io<SCI_CH, RXB, TXB, device::port_map::option::SECOND> SCI;
	SCI			sci_;

	typedef device::cmt_io<device::CMT0, utils::null_task> CMT;
	CMT			cmt_;

	typedef device::PORT<device::PORTA, device::bitpos::B1> RS;
	typedef device::PORT<device::PORT5, device::bitpos::B2> RD;
	typedef device::PORT<device::PORT5, device::bitpos::B0> WR;
	typedef device::PORT<device::PORT2, device::bitpos::B4> CS;
	typedef device::PORT_BYTE<device::PORTD> DL;
	typedef device::PORT_BYTE<device::PORTE> DH;
	typedef device::bus_rw16<CS, RS, RD, WR, DL, DH> BUS;
	BUS			bus_;

	typedef device::PORT<device::PORT0, device::bitpos::B2> RES;
	typedef chip::R61505<BUS, RES> TFT;
	TFT			tft_;

	class GLC {
	public:
		static const int16_t width  = 320;
		static const int16_t height = 240;

	private:
		uint16_t	fb_[width * height];
	public:
		void* get_fbp() noexcept {
			return reinterpret_cast<void*>(fb_);
		}
	};
	GLC			glc_;

	typedef graphics::font8x16 AFONT;
	AFONT		afont_;
	typedef graphics::kfont_null KFONT;
	KFONT		kfont_;
	typedef graphics::font<AFONT, KFONT> FONT;
	FONT		font_(afont_, kfont_);

	typedef graphics::render<GLC, FONT> RENDER;
	RENDER	render_(glc_, font_);


	void copy_fb_()
	{
		const uint16_t* src = static_cast<const uint16_t*>(glc_.get_fbp());
		for(uint16_t y = 0; y < GLC::height; ++y) {
			tft_.copy(vtx::spos(0, y), src, GLC::width);
			src += GLC::width;
		}
	}
}


extern "C" {

	void draw_pixel(int x, int y, int r, int g, int b)
	{
		volatile uint16_t c = (static_cast<uint16_t>(r & 0xf8) << 8)
				   | (static_cast<uint16_t>(g & 0xfc) << 3)
				   | (static_cast<uint16_t>(b) >> 3);		
//		tft_.plot(x, y, c);
		render_.plot(vtx::spos(x, y), c);
	}


	void draw_text(int x, int y, const char* t)
	{
		render_.swap_color();
		render_.fill_box(vtx::srect(x, y, strlen(t) * 8, 16));
		render_.swap_color();
		render_.draw_text(vtx::spos(x, y), t);
	}


	uint32_t millis(void)
	{
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

	utils::format("Start TFT-LCD sample\n");

	if(tft_.start()) {
		tft_.fill_box(vtx::srect(0, 0, 320, 240), 0x0000);
	} else {
		utils::format("TFT-LCD not start...\n");
	}

	LED::DIR = 1;
	uint8_t cnt = 0;
	uint8_t delay = 60;
	while(1) {
		cmt_.sync();

		copy_fb_();

		if(delay > 0) {
			delay--;
			if(delay == 0) {
				doRaytrace(1, 320, 240);
			}
		}

		// エコーバック処理
		while(sci_length() > 0) {
			auto ch = sci_getch();
			sci_putch(ch);
		}

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
		}
		if(cnt < 25) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
