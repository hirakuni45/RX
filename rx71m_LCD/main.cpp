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

#include "chip/R61505.hpp"

#include "../RTK5_RAYTRACER/raytracer.hpp"

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

	device::cmt_io<device::CMT0, utils::null_task>  cmt_;

	struct tft_rw {

		typedef device::PORT<device::PORT0, device::bitpos::B2> RES;
		typedef device::PORT<device::PORTA, device::bitpos::B1> RS;
		typedef device::PORT<device::PORT5, device::bitpos::B2> RD;
		typedef device::PORT<device::PORT5, device::bitpos::B0> WR;
		typedef device::PORT<device::PORT2, device::bitpos::B4> CS;
		typedef device::PORT_BYTE<device::PORTD> DL;
		typedef device::PORT_BYTE<device::PORTE> DH;

		static void start() noexcept
		{
			RES::DIR = 1;
			RS::DIR = 1;
			RD::DIR = 1;
			WR::DIR = 1;
			CS::DIR = 1;

			CS::P = 1;
			RES::P = 0;
			RS::P = 0;
			RD::P = 1;
			WR::P = 1;

			DL::DIR = 0xff;
			DH::DIR = 0xff;

			utils::delay::milli_second(10);
			RES::P = 1;
			utils::delay::milli_second(10);
		}

		static void write16(uint16_t val) noexcept {
			DH::P = val >> 8;
			DL::P = val & 0xff;
			WR::P = 0;
			CS::P = 0;
			utils::delay::loop(10);
			WR::P = 1;
			CS::P = 1;
		}

		static uint16_t read16() noexcept {
			RD::P = 0;
			CS::P = 0;
			utils::delay::micro_second(1);
			uint16_t val = static_cast<uint16_t>(DH::P());
			val <<= 8;
			val |= static_cast<uint16_t>(DL::P());
			CS::P = 1;
			RD::P = 1;
			return val;
		}

		static void write(uint16_t val, bool rs) noexcept {
			RS::P = rs;
			write16(val);
		}

		static uint16_t read() noexcept {
			RS::P = 1;
			DL::DIR = 0x00;
			DH::DIR = 0x00;
			auto dat = read16();
			DL::DIR = 0xff;
			DH::DIR = 0xff;
			return dat;
		}
	};

	tft_rw	tft_rw_;

	typedef chip::R61505<tft_rw> TFT;
	TFT		tft_(tft_rw_);
}


extern "C" {

	void draw_pixel(int x, int y, int r, int g, int b)
	{
		volatile uint16_t c = (static_cast<uint16_t>(r & 0xf8) << 8)
				   | (static_cast<uint16_t>(g & 0xfc) << 3)
				   | (static_cast<uint16_t>(b & 0xf8) >> 3);		
		tft_.plot(x, y, c);
	}

	void draw_text(int x, int y, const char* t)
	{
//		tft_.fill_box(x, y, strlen(t) * 8, 16, render_.get_back_color());
//		tft_.draw_text(x, y, t);
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

	utils::format("Start TFT sample\n");

	tft_rw_.start();
	if(tft_.start()) {
		utils::format("Probe TFT OK to start...\n");
		for(int y = 0; y < 240; ++y) {
			for(int x = 0; x < 320; ++x) {
				tft_.plot(x, y, 0x0);
			}
		}

		doRaytrace(1, 320, 240);

	} else {
		utils::format("Probe TFT NG not start...\n");
	}

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
