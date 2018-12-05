//=====================================================================//
/*! @file
    @brief  RX24T/RX64M/RX71M/RX65N/RX66T RayTracer
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

#if defined(SIG_RX65N)
#include "graphics/font8x16.hpp"
#include "graphics/graphics.hpp"
#endif

#include "raytracer.hpp"

namespace {

#if defined(SIG_RX71M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX71M" };
#elif defined(SIG_RX64M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX64M" };
#elif defined(SIG_RX65N)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B5> SW2;
	typedef device::SCI9 SCI_CH;
	static const char* system_str_ = { "RX65N" };
#elif defined(SIG_RX24T)
	typedef device::system_io<10000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX24T" };
#elif defined(SIG_RX66T)
	typedef device::system_io<10000000, 16000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX66T" };
#endif

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<SCI_CH, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

#if defined(RX65_LCD)
	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	typedef device::glcdc_io<device::GLCDC, 480, 272,
		device::glcdc_def::PIX_TYPE::RGB565> GLCDC_IO;
	GLCDC_IO	glcdc_io_;

	typedef graphics::font8x16 AFONT;

	typedef graphics::render<uint16_t, 480, 272, AFONT> RENDER;
	RENDER		render_(reinterpret_cast<uint16_t*>(0x00000000));
#endif

	typedef utils::command<256> CMD;
	CMD 	cmd_;

	typedef device::cmt_io<device::CMT0> CMT;
	CMT		cmt_;

	bool	run_ = false;
	int		sampling_ = 1;
	int		render_width_  = 320;
	int		render_height_ = 240;

	void command_()
	{
		if(!cmd_.service()) {
			return;
		}
#if 0
		uint8_t cmdn = cmd_.get_words();
		if(cmdn >= 1) {
			bool f = false;
			if(cmd_.cmp_word(0, "clear")) {
				render_.clear(0x0000);
				f = true;
			} else if(cmd_.cmp_word(0, "render")) {
				render_.clear(0x0000);
				render_width_  = 320;
				render_height_ = 240;
				run_ = false;
				f = true;
			} else if(cmd_.cmp_word(0, "full")) {
				render_.clear(0x0000);
				render_width_  = 480;
				render_height_ = 272;
				run_ = false;
				f = true;
			} else if(cmd_.cmp_word(0, "help")) {
				utils::format("    clear     clear screen\n");
				utils::format("    render    renderring 320x240\n");
				utils::format("    full      renderring 480x272\n");
				f = true;
			}
			if(!f) {
				char tmp[128];
				if(cmd_.get_word(0, tmp, sizeof(tmp))) {
					utils::format("Command error: '%s'\n") % tmp;
				}
			}
		}
#endif
	}
}


extern "C" {

	void draw_pixel(int x, int y, int r, int g, int b)
	{
#if defined(RX65_LCD)
		auto c = RENDER::COLOR::rgb(r, g, b);
		render_.plot(x, y, c);
#else
		volatile uint16_t c = (static_cast<uint16_t>(r & 0xf8) << 8)
				   | (static_cast<uint16_t>(g & 0xfc) << 3)
				   | (static_cast<uint16_t>(b) >> 3);
		utils::delay::micro_second(5);  // dummy draw pixel
#endif
	}


	void draw_text(int x, int y, const char* t)
	{
#if defined(RX65_LCD)
		render_.fill_box(x, y, strlen(t) * 8, 16, render_.get_back_color());
		render_.draw_text(x, y, t);
#endif
	}


	uint32_t millis(void)
	{
		return cmt_.get_counter();
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

	{  // SCI 設定
		uint8_t intr_lvl = 2;
		sci_.start(115200, intr_lvl);
	}

	{  // 時間計測タイマー（1000Hz）
		uint8_t intr_lvl = 4;
		cmt_.start(1000, intr_lvl);
	}

	utils::format("\r%s Start for Ray Trace\n") % system_str_;

	cmd_.set_prompt("# ");

#if defined(RX65_LCD)
	{  // GLCDC 初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 0;  // DISP Disable
		LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
		if(glcdc_io_.start()) {
			utils::format("Start GLCDC\n");
			LCD_DISP::P  = 1;  // DISP Enable
			LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
			if(!glcdc_io_.control(GLCDC_IO::CONTROL_CMD::START_DISPLAY)) {
				utils::format("GLCDC ctrl fail...\n");
			}
		} else {
			utils::format("Fail GLCDC\n");
		}
	}
	SW2::DIR = 0;
#endif

	LED::DIR = 1;

	doRaytrace(sampling_, render_width_, render_height_);

	uint8_t n = 0;
	bool sw = false;
	while(1) {
#if defined(RX65_LCD)
		glcdc_io_.sync_vpos();
#endif

#if 0
		bool v = !SW2::P();
		if(!sw && v) {
			render_.clear(0x0);
			if(render_width_ == 320) {
				render_width_ = 480;
				render_height_ = 272;
			} else {
				render_width_ = 320;
				render_height_ = 240;
				++asq;
				if(asq > 4) asq = 1;
			}
			run_ = false;
		}
		sw = v;
#endif

		command_();

//		if(!run_) {
//			doRaytrace(sampling_, render_width_, render_height_);
//			run_ = true;
//		}

		++n;
		if(n >= 30) {
			n = 0;
		}
		if(n < 10) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
