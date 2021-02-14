//=====================================================================//
/*! @file
    @brief  RX24T/RX64M/RX71M/RX65N/RX66T/RX72N RayTracer サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2021 Kunihito Hiramatsu @n
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
#include "graphics/tgl.hpp"
#include "graphics/shape_3d.hpp"

namespace {

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT			cmt_;

	typedef graphics::font8x16 AFONT;
	typedef graphics::kfont_null KFONT;
	typedef graphics::font<AFONT, KFONT> FONT;
	AFONT		afont_;
	KFONT		kfont_;
	FONT		font_(afont_, kfont_);

#if defined(SIG_RX72N)
	/// for RX72N Envision Kit
	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B7> SW2;
	typedef device::SCI2 SCI_CH;
	static const char* system_str_ = { "RX72N Envision Kit" };
	static const uint16_t LCD_X = 480;
	static const uint16_t LCD_Y = 272;
	uint16_t*	fb_ = reinterpret_cast<uint16_t*>(0x0080'0000);
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, graphics::pixel::TYPE::RGB565> GLCDC_MGR;
	typedef device::drw2d_mgr<GLCDC_MGR, FONT> RENDER;

	GLCDC_MGR	glcdc_mgr_(nullptr, fb_);
	RENDER		render_(glcdc_mgr_, font_);

	static const uint32_t VNUM = 500;  // 最大の頂点数
	static const uint32_t PNUM = 300;  // プリミティブ最大数
	typedef graphics::tgl<RENDER, VNUM, PNUM> TGL;
	TGL			tgl_(render_);

	typedef graphics::shape_3d<TGL> SHAPE;
	SHAPE		shape_(tgl_);
#endif

	typedef graphics::def_color DEF_COLOR;

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<SCI_CH, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

	typedef utils::command<256> CMD;
	CMD 		cmd_;


	void command_()
	{
		if(!cmd_.service()) {
			return;
		}
		uint8_t cmdn = cmd_.get_words();
		if(cmdn >= 1) {
			bool f = false;
			if(cmd_.cmp_word(0, "clear")) {

			} else if(cmd_.cmp_word(0, "help")) {
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

	utils::format("\r%s Start for TinyGL: %u, %u\n") % system_str_ % LCD_X % LCD_Y;

	cmd_.set_prompt("# ");

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
			} else {
				if(!glcdc_mgr_.enable_double_buffer()) {  // ダブルバッファを有効にする。
					utils::format("Can't enable double-bufer\n");
				}
			}
		} else {
			utils::format("Fail GLCDC\n");
		}
	}

	{  // DRW2D 初期化
		if(render_.start()) {
			utils::format("DRW2D Start\n");
			render_.list_info();
		} else {
			utils::format("DRW2D Fail...\n");
		}
	}

	{  // TGL 初期化
		tgl_.start();
	}

	LED::OUTPUT();

	uint8_t n = 0;
	int16_t xx = 0;
	uint16_t nn = 0;
	float ax = 0.0f;
	float ay = 0.0f;
	while(1) {
		render_.sync_frame();

		render_.clear(DEF_COLOR::Black);

		auto& m = tgl_.at_matrix();
		m.set_viewport(0, 0, LCD_X, LCD_Y);

		m.set_mode(gl::matrixf::mode::projection);
		m.identity();
		m.perspective(45.0f, static_cast<float>(LCD_X) / static_cast<float>(LCD_Y), 1.0f, 50.0f);

		m.set_mode(gl::matrixf::mode::modelview);
		m.identity();
		m.translate(0.0f, 0.0f, -10.0f);
		m.rotate(ax, 1.0f, 0.0f, 0.0f);
		m.rotate(ay, 0.0f, 1.0f, 0.0f);

		ax += 1.0f;
		if(ax >= 360.0f) ax -= 360.0f;
		ay += 1.5f;
		if(ay >= 360.0f) ay -= 360.0f;
#if 0
		render_.set_fore_color(DEF_COLOR::White);
		render_.set_back_color(DEF_COLOR::Black);
		render_.set_stipple(0x33);
		render_.line_d(vtx::spos(0, 100 << 4), vtx::spos(256 << 4, 100 << 4));
#endif
		if(nn < 240) {
			tgl_.LineWidth(3.0f);
			shape_.WireCube(2.0f);
		} else {
			shape_.SolidCube(2.0f);
		}
		++nn;
		if(nn >= 480) nn = 0;

		tgl_.renderring();

//		render_.set_fore_color(graphics::def_color::White);
//		render_.fill_box(vtx::srect(xx, 0, 50, 50));
//		++xx;
//		if(xx >= 480) xx = 0;

		command_();

		++n;
		if(n >= 30) {
			n = 0;
		}
		if(n < 10) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}

		render_.flip();
	}
}
