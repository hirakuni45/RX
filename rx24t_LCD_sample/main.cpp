//=====================================================================//
/*! @file
    @brief  RX24T LCD サンプル @n
			・（インジケーター）P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/rspi_io.hpp"

// LCD を選択する
// #define LCD_ST7565
// #define LCD_UC1701
#define LCD_R61505

#if defined(LCD_ST7565)
#include "chip/ST7565.hpp"
#include "graphics/monograph.hpp"
#define LCD_SPI
#define LCD_MONO
#elif defined(LCD_UC1701)
#include "chip/UC1701.hpp"
#include "graphics/monograph.hpp"
#define LCD_SPI
#define LCD_MONO
#elif defined(LCD_R61505)
#include "chip/R61505.hpp"
#include "chip/bus_rw.hpp"
#include "../RAYTRACER_sample/raytracer.hpp"
#define LCD_BUS
#endif

namespace {

	// 外部 10MHz クリスタル
	typedef device::system_io<10000000> SYSTEM_IO;

	// LED インジケーター
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

	typedef utils::fixed_fifo<char, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

#if defined(LCD_SPI)
	typedef device::PORT<device::PORT6, device::bitpos::B1> LCD_SEL;	///< LCD 選択信号
	typedef device::PORT<device::PORT6, device::bitpos::B2> LCD_A0;	    ///< LCD レジスター選択

	// SPI 定義（RSPI0）
	typedef device::rspi_io<device::RSPI0> SPI;
	SPI		spi_;
#endif

#if defined(LCD_ST7565)

	static const char* LCD_NAME = { "ST7565" };
	chip::ST7565<SPI, LCD_SEL, LCD_A0> lcd_(spi_);

#elif defined(LCD_UC1701)

	static const char* LCD_NAME = { "UC1701" };
	chip::UC1701<SPI, LCD_SEL, LCD_A0> lcd_(spi_);

#elif defined(LCD_R61505)

	static const char* LCD_NAME = { "R61505" };
	// LCD connection connector
	// DB0, DB1, DB2, DB3, GND, DB4, DB5, DB6, DB7
	// RST, /CS, RS , /WR, /RD, GND, GND, 3.3, 3.3
	typedef device::PORT<device::PORT5, device::bitpos::B2> RS;
	typedef device::PORT<device::PORT5, device::bitpos::B4> RD;
	typedef device::PORT<device::PORT5, device::bitpos::B3> WR;
	typedef device::PORT<device::PORT5, device::bitpos::B1> CS;
	typedef device::PORT_BYTE<device::PORT4> DATA;
	typedef device::bus_rw8<CS, RS, RD, WR, DATA> BUS;
	typedef device::PORT<device::PORT5, device::bitpos::B0> RES;
	typedef chip::R61505<BUS, RES> LCD;
	LCD		lcd_;

#endif

#if defined(LCD_MONO)
	// モノクロ・グラフィックス
	graphics::kfont_null kfont_;
	graphics::monograph<128, 64> bitmap_(kfont_);

	uint8_t v_ = 91;
	uint8_t m_ = 123;
	uint8_t rand_()
	{
		v_ += v_ << 2;
		++v_;
		uint8_t n = 0;
		if(m_ & 0x02) n = 1;
		if(m_ & 0x40) n ^= 1;
		m_ += m_;
		if(n == 0) ++m_;
		return v_ ^ m_;
	}
#endif
}

extern "C" {

#if defined(LCD_R61505)
	void draw_pixel(int x, int y, int r, int g, int b)
	{
		volatile uint16_t c = (static_cast<uint16_t>(r & 0xf8) << 8)
				   | (static_cast<uint16_t>(g & 0xfc) << 3)
				   | (static_cast<uint16_t>(b) >> 3);		
		lcd_.plot(vtx::spos(x, y), c);
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
#endif

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}


	char sci_getch()
	{
		return sci_.getch();
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	// タイマー設定（100Hz）
	{
		uint8_t cmt_irq_level = 4;
		cmt_.start(100, cmt_irq_level);
	}

	// SCI 設定
	{
		uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	utils::format("RX24T LCD %s sample\n") % LCD_NAME;

#ifdef LCD_SPI
	// RSPI 開始
	{
		uint32_t clk = 8000000;
		if(!spi_.start(clk, SPI::PHASE::TYPE4, SPI::DLEN::W8)) {
			utils::format("RSPI speed fail...\n");
		}
	}
#endif

#ifdef LCD_MONO
	// LCD 開始
	{
		lcd_.start(0x00);
		bitmap_.clear(0);

		uint16_t x = rand_() & 127;
		uint16_t y = rand_() & 63;
		uint16_t xx;
		uint16_t yy;
		uint8_t	nn = 0;
		uint8_t loop = 0;
	}
#endif

#if defined(LCD_R61505)
	// TFT/BUS 開始
	{
		if(!lcd_.start()) {
			utils::format("R61505 not start\n");
		} else {
			lcd_.fill_box(vtx::srect(0, 0, 320, 240), 0x0000);
			doRaytrace(1, 320, 240);
		}
	}
#endif

	LED::DIR = 1;

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

#ifdef LCD_MONO
		if(nn >= 4) {
			lcd_.copy(bitmap_.fb(), bitmap_.page_num());
			nn = 0;
		}
		++nn;

		if(loop >= 20) {
			loop = 0;
			bitmap_.clear(0);
			bitmap_.frame(0, 0, 128, 64, 1);
		}
		xx = rand_() & 127;
		yy = rand_() & 63;
		bitmap_.line(x, y, xx, yy, 1);
		x = xx;
		y = yy;
		++loop;
#endif

		if(sci_.recv_length()) {
			auto ch = sci_.getch();
			sci_.putch(ch);
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
