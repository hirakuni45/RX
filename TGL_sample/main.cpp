//=====================================================================//
/*! @file
    @brief  RX72N Envision Kit TinyGL サンプル @n
			OpenGL の縮小セット風３Ｄグラフィックスサンプル @n
			ダブルバッファを使うので、RX72N 専用
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
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

#include "common/sci_i2c_io.hpp"
#include "chip/FT5206.hpp"

namespace {

	typedef graphics::font8x16 AFONT;
	typedef graphics::kfont_null KFONT;
	typedef graphics::font<AFONT, KFONT> FONT;
	AFONT		afont_;
	KFONT		kfont_;
	FONT		font_(afont_, kfont_);

#if defined(SIG_RX72N)
/// for RX72N Envision Kit
	static const char* system_str_ = { "RX72N Envision Kit" };
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B7> SW2;
	typedef device::SCI2 SCI_CH;
	static const uint16_t LCD_X = 480;
	static const uint16_t LCD_Y = 272;
	uint16_t* fb_ = reinterpret_cast<uint16_t*>(0x0080'0000);
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, graphics::pixel::TYPE::RGB565> GLCDC_MGR;
	typedef device::drw2d_mgr<GLCDC_MGR, FONT> RENDER;

	typedef utils::fixed_fifo<uint8_t, 64> RB64;
	typedef utils::fixed_fifo<uint8_t, 64> SB64;
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::SECOND> FT5206_I2C;

	GLCDC_MGR	glcdc_mgr_(nullptr, fb_);
	RENDER		render_(glcdc_mgr_, font_);

	static const uint32_t V_NUM = 500;  // 最大の頂点数
	static const uint32_t P_NUM = 300;  // プリミティブ最大数
	static const uint32_t T_NUM = 32;   // テクスチャー管理数
	typedef graphics::tgl<RENDER, V_NUM, P_NUM, T_NUM> TGL;
	TGL			tgl_(render_);

	typedef graphics::shape_3d<TGL> SHAPE;
	SHAPE		shape_(tgl_);

	// タッチパネル定義
	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> TOUCH;
	TOUCH		touch_(ft5206_i2c_);

	static const int16_t TEX_W = 32;
	static const int16_t TEX_H = 32;
	graphics::rgba8_t	texture_[TEX_W * TEX_H];
	
	uint32_t	tex_id_;

#endif

	typedef graphics::def_color DEF_COLOR;

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<SCI_CH, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;
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
	SYSTEM_IO::boost_master_clock();

	{  // SCI 設定
		auto intr_lvl = device::ICU::LEVEL::_2;
		sci_.start(115200, intr_lvl);
	}

	utils::format("\r%s Start for TinyGL: %u, %u\n") % system_str_ % LCD_X % LCD_Y;

	{  // GLCDC 初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 0;  // DISP Disable
		LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
		if(glcdc_mgr_.start(device::ICU::LEVEL::_2)) {
			utils::format("Start GLCDC\n");
			LCD_DISP::P  = 1;  // DISP Enable
			LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
			if(!glcdc_mgr_.control(GLCDC_MGR::CONTROL_CMD::START_DISPLAY)) {
				utils::format("GLCDC ctrl fail...\n");
			} else {
				if(!glcdc_mgr_.enable_double_buffer()) {  // ダブルバッファを有効にする。
					utils::format("Can't enable double-buffer\n");
				}
			}
		} else {
			utils::format("Fail GLCDC\n");
		}
	}

	{  // DRW2D 初期化
		if(render_.start(device::ICU::LEVEL::_2)) {
			utils::format("DRW2D Start\n");
			render_.list_info();
		} else {
			utils::format("DRW2D Fail...\n");
		}
	}

	{  // FT5206 touch screen controller
		TOUCH::reset<FT5206_RESET>();
		auto intr_lvl = device::ICU::LEVEL::_1;
		if(!ft5206_i2c_.start( FT5206_I2C::MODE::MASTER, FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
			utils::format("FT5206 I2C Start Fail...\n");
		}
		if(!touch_.start()) {
			utils::format("FT5206 Start Fail...\n");
		}
	}

	{  // TGL 初期化
		tgl_.start();

		// テクスチャーパターンの生成
		for(int16_t y = 0; y < TEX_H; ++y) {
			for(int16_t x = 0; x < TEX_W; ++x) {
				texture_[y * TEX_W + x].a = 255;
				texture_[y * TEX_W + x].r = ((y & 3) < 3) ? 192 : 255;
				texture_[y * TEX_W + x].g = ((x & 3) < 3) ? 192 : 255;
				uint8_t b = ((x & 7) < 6) ? 192 : 255;
				if((y & 7) < 6) b /= 2;
				texture_[y * TEX_W + x].b = b;
			}
		}

		// テクスチャーのバインド
		tex_id_ = tgl_.GenTexture();
		tgl_.BindTexture(TGL::TARGET::TEXTURE_2D, tex_id_);
		tgl_.TexImage2D(TGL::TARGET::TEXTURE_2D, vtx::spos(TEX_W, TEX_H), TGL::FORMAT::RGBA8, texture_);
	}

	LED::OUTPUT();

	uint8_t n = 0;
	bool ctrl = false;
	uint16_t ctrl_timer = 0;
	int16_t xx = 0;
	uint16_t nn = 0;
	float ax = 0.0f;
	float ay = 0.0f;
	float ax_org = 0.0f;
	float ay_org = 0.0f;
	while(1) {
		render_.sync_frame();

		touch_.update();

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

		{
			auto tnum = touch_.get_touch_num();
			if(tnum == 1) {
				ctrl = true;
				const auto& t = touch_.get_touch_pos(0);
				if(t.event == TOUCH::EVENT::DOWN) {
					ax_org = ax;
					ay_org = ay;
				}
				auto d = t.org - t.pos;
				ax = ax_org + static_cast<float>(d.y);
				ay = ay_org + static_cast<float>(d.x);
			}
		}
		if(ctrl) {
			ctrl_timer++;
			if(ctrl_timer >= (60 * 5)) {
				ctrl_timer = 0;
				ctrl = false;
			}
		} else {
			ax += 1.0f;
			ay += 1.5f;
		}
		ax = fmod(ax, 360.0f);
		ay = fmod(ay, 360.0f);
#if 0
		render_.set_fore_color(DEF_COLOR::White);
		render_.set_back_color(DEF_COLOR::Black);
		render_.set_stipple(0x33);
		render_.line_d(vtx::spos(0, 100 << 4), vtx::spos(256 << 4, 100 << 4));
#endif
#if 0
		if(nn < (60 * 5)) {
			tgl_.LineWidth(3.0f);
			shape_.WireCube(2.0f);
		} else {
			shape_.SolidCube(2.0f);
		}
		++nn;
		if(nn >= 480) nn = 0;
#endif
		shape_.SolidCube(2.0f);

		tgl_.renderring();

//		render_.set_fore_color(graphics::def_color::White);
//		render_.fill_box(vtx::srect(xx, 0, 50, 50));
//		++xx;
//		if(xx >= 480) xx = 0;

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
