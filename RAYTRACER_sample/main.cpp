//=====================================================================//
/*! @file
    @brief  RX24T/RX64M/RX71M/RX65N/RX66T/RX72N RayTracer サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"

#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/font.hpp"
#include "graphics/graphics.hpp"

#include "chip/bus_rw.hpp"
#include "chip/R61505.hpp"

#include "raytracer.hpp"

namespace {

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT			cmt_;

	typedef graphics::font8x16 AFONT;
	typedef graphics::kfont_null KFONT;
	typedef graphics::font<AFONT, KFONT> FONT;
	AFONT		afont_;
	KFONT		kfont_;
	FONT		font_(afont_, kfont_);

#if defined(SIG_RX71M)
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX71M" };
	static const uint16_t LCD_X = 320;
	static const uint16_t LCD_Y = 240;

	typedef device::PORT<device::PORTA, device::bitpos::B1> RS;
	typedef device::PORT<device::PORT5, device::bitpos::B2> RD;
	typedef device::PORT<device::PORT5, device::bitpos::B0> WR;
	typedef device::PORT<device::PORT2, device::bitpos::B4> CS;
	typedef device::PORT_BYTE<device::PORTD> DL;
	typedef device::PORT_BYTE<device::PORTE> DH;
	typedef device::bus_rw16<CS, RS, RD, WR, DL, DH> BUS;
	typedef device::PORT<device::PORT0, device::bitpos::B2> RES;
	typedef chip::R61505<BUS, RES> TFT;
	TFT         tft_;

#elif defined(SIG_RX64M)
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX64M" };
	static const uint16_t LCD_X = 320;
	static const uint16_t LCD_Y = 240;

	typedef device::PORT<device::PORTA, device::bitpos::B1> RS;
	typedef device::PORT<device::PORT5, device::bitpos::B2> RD;
	typedef device::PORT<device::PORT5, device::bitpos::B0> WR;
	typedef device::PORT<device::PORT2, device::bitpos::B4> CS;
	typedef device::PORT_BYTE<device::PORTD> DL;
	typedef device::PORT_BYTE<device::PORTE> DH;
	typedef device::bus_rw16<CS, RS, RD, WR, DL, DH> BUS;
	typedef device::PORT<device::PORT0, device::bitpos::B2> RES;
	typedef chip::R61505<BUS, RES> TFT;
	TFT         tft_;

#elif defined(SIG_RX65N)
	/// for RX65N Envision Kit
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B5> SW2;
	typedef device::SCI9 SCI_CH;
	static const char* system_str_ = { "RX65N" };
	static const uint16_t LCD_X = 480;
	static const uint16_t LCD_Y = 272;
	/// フレームバッファ開始アドレスは null_ptr の関係で０から開始出来ない
	/// RX65N では、RAM は２ブロックあり、前半の 256K 領域をフレームバッファに設定する
	uint16_t*	fb_ = reinterpret_cast<uint16_t*>(0x0000'0100);
	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, graphics::pixel::TYPE::RGB565> GLCDC_MGR;
	typedef graphics::render<GLCDC_MGR, FONT> RENDER;
	GLCDC_MGR	glcdc_mgr_(nullptr, fb_);
	RENDER		render_(glcdc_mgr_, font_);

	#define USE_GLCDC

#elif defined(SIG_RX24T)
	typedef device::system_io<10'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX24T" };
	static const uint16_t LCD_X = 320;
	static const uint16_t LCD_Y = 240;
	typedef device::PORT<device::PORT5, device::bitpos::B4> RD;
	typedef device::PORT<device::PORT5, device::bitpos::B3> WR;
	typedef device::PORT<device::PORT5, device::bitpos::B2> RS;
	typedef device::PORT<device::PORT5, device::bitpos::B1> CS;
	typedef device::PORT_BYTE<device::PORT4> DA;
	typedef device::bus_rw8<CS, RS, RD, WR, DA> BUS;
	typedef device::PORT<device::PORT5, device::bitpos::B0> RES;
	typedef chip::R61505<BUS, RES> TFT;
	TFT         tft_;

#elif defined(SIG_RX66T)
	typedef device::system_io<10'000'000, 160'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX66T" };
	static const uint16_t LCD_X = 320;
	static const uint16_t LCD_Y = 240;
	typedef device::PORT<device::PORT5, device::bitpos::B4> RD;
	typedef device::PORT<device::PORT5, device::bitpos::B3> WR;
	typedef device::PORT<device::PORT5, device::bitpos::B2> RS;
	typedef device::PORT<device::PORT5, device::bitpos::B1> CS;
	typedef device::PORT_BYTE<device::PORT4> DA;
	typedef device::bus_rw8<CS, RS, RD, WR, DA> BUS;
	typedef device::PORT<device::PORT5, device::bitpos::B0> RES;
	typedef chip::R61505<BUS, RES> TFT;
	TFT         tft_;

#elif defined(SIG_RX72N)
	/// for RX72N Envision Kit
	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B7> SW2;
	typedef device::SCI2 SCI_CH;
	static const char* system_str_ = { "RX72N" };
	static const uint16_t LCD_X = 480;
	static const uint16_t LCD_Y = 272;
	uint16_t*	fb_ = reinterpret_cast<uint16_t*>(0x0080'0000);
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, graphics::pixel::TYPE::RGB565> GLCDC_MGR;
	typedef graphics::render<GLCDC_MGR, FONT> RENDER;
	GLCDC_MGR	glcdc_mgr_(nullptr, fb_);
	RENDER		render_(glcdc_mgr_, font_);

	#define USE_GLCDC

#endif

#ifndef USE_GLCDC
	uint16_t line_[LCD_X];

	template <uint32_t X, uint32_t Y>
	class glc {

		uint16_t	fb_[X * Y];

	public:
		static const uint16_t width  = X;
		static const uint16_t height = Y;

		glc() { }

		void* get_fbp() { return fb_; }
	};
	typedef glc<8 * 16, 16> GLC;
	GLC			glc_;
	typedef graphics::render<GLC, FONT> RENDER;
	RENDER		render_(glc_, font_);
#endif

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<SCI_CH, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

	bool		run_ = false;
	int			sampling_ = 1;
	int			render_width_  = 320;
	int			render_height_ = 240;

	typedef utils::command<256> CMD;
	CMD 		cmd_;


	void clear_screen_()
	{
#ifdef USE_GLCDC
		render_.clear(graphics::def_color::Black);
#else
		tft_.fill_box(vtx::srect(0, 0, LCD_X, LCD_Y), 0x0000);
#endif
	}


	void command_()
	{
		if(!cmd_.service()) {
			return;
		}
		uint8_t cmdn = cmd_.get_words();
		if(cmdn >= 1) {
			bool f = false;
			if(cmd_.cmp_word(0, "clear")) {
				clear_screen_();
				f = true;
			} else if(cmd_.cmp_word(0, "render")) {
				clear_screen_();
				render_width_  = 320;
				render_height_ = 240;
				run_ = false;
				f = true;
			} else if(cmd_.cmp_word(0, "full")) {
				clear_screen_();
				render_width_  = LCD_X;
				render_height_ = LCD_Y;
				run_ = false;
				f = true;
			} else if(cmd_.cmp_word(0, "help")) {
				utils::format("    clear     clear screen\n");
				utils::format("    render    renderring 320x240\n");
				utils::format("    full      renderring %ux%u\n") % LCD_X % LCD_Y;
				f = true;
			}
			if(!f) {
				char tmp[128];
				if(cmd_.get_word(0, tmp, sizeof(tmp))) {
					utils::format("Command error: '%s'\n") % tmp;
				}
			}
		}
	}
}


extern "C" {

	void draw_pixel(int x, int y, int r, int g, int b)
	{
		auto c = graphics::share_color::to_565(r, g, b);
#ifdef USE_GLCDC
		render_.plot(vtx::spos(x, y), c);
#else
		line_[x] = c;
		if(x == (render_width_ - 1)) {
			tft_.copy(vtx::spos(0, y), line_, LCD_X);
		}
#endif
	}


	void draw_text(int x, int y, const char* t)
	{
#ifdef USE_GLCDC
		render_.set_fore_color(graphics::def_color::Black);
		render_.fill_box(vtx::srect(x, y, strlen(t) * AFONT::width, AFONT::height));
		render_.set_fore_color(graphics::def_color::White);
		render_.draw_text(vtx::spos(x, y), t);
#else
		render_.set_fore_color(graphics::def_color::Black);
		auto len = strlen(t) * AFONT::width;
		render_.fill_box(vtx::srect(0, 0, len, AFONT::height));
		render_.set_fore_color(graphics::def_color::White);
		render_.draw_text(vtx::spos(0, 0), t);
		const uint16_t* src = static_cast<const uint16_t*>(glc_.get_fbp());
		for(uint16_t i = 0; i < AFONT::height; ++i) {
			tft_.copy(vtx::spos(x, y + i), src, len);
			src += GLC::width;
		}
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

	utils::format("\r%s Start for Ray Trace: %u, %u\n") % system_str_ % LCD_X % LCD_Y;

	cmd_.set_prompt("# ");

#ifdef USE_GLCDC
	{  // GLCDC 初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 0;  // DISP Disable
		LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
		if(glcdc_mgr_.start()) {
			utils::format("Start GLCDC\n");
			LCD_DISP::P  = 1;  // DISP Enable
			LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
			if(!glcdc_mgr_.control(GLCDC_MGR::CONTROL_CMD::START_DISPLAY)) {
				utils::format("GLCDC ctrl fail...\n");
			}
		} else {
			utils::format("Fail GLCDC\n");
		}
	}
	SW2::DIR = 0;
#else
	tft_.start();
#endif

	LED::DIR = 1;

	clear_screen_();

	run_ = false;

	uint8_t n = 0;
	bool sw = false;
	while(1) {
#ifdef USE_GLCDC
		glcdc_mgr_.sync_vpos();

		bool v = !SW2::P();
		if(!sw && v) {
			render_.clear(graphics::def_color::Black);
			if(render_width_ == 320) {
				render_width_  = LCD_X;
				render_height_ = LCD_Y;
			} else {
				render_width_ = 320;
				render_height_ = 240;
				++sampling_;
				if(sampling_ > 4) sampling_ = 1;
			}
			run_ = false;
		}
		sw = v;
#else
 		utils::delay::milli_second(17);
#endif

		command_();

		if(!run_) {
			doRaytrace(sampling_, render_width_, render_height_);
			run_ = true;
		}

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
