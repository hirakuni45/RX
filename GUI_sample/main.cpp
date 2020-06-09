//=====================================================================//
/*! @file
    @brief  RX65N/RX72N GUI サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/sci_i2c_io.hpp"

#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/filer.hpp"
#include "graphics/dialog.hpp"
#include "graphics/img_in.hpp"
#include "graphics/widget_director.hpp"
#include "graphics/scaling.hpp"
#include "graphics/img_in.hpp"

#include "common/dir_list.hpp"
#include "common/shell.hpp"

#include "chip/FT5206.hpp"

namespace {

	// LCD 定義
	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	static const auto PIX = graphics::pixel::TYPE::RGB565;

	// SCI_I2C バッファ定義
	typedef utils::fixed_fifo<uint8_t, 64> RB64;
	typedef utils::fixed_fifo<uint8_t, 64> SB64;

#if defined(SIG_RX65N)
	/// RX65N Envision Kit
	static const char* system_str_ = { "RX65N Envision Kit" };
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;

	// SDHI 関係定義（RX65N Envision Kit の SDHI ポートは、候補３で指定できる）
    typedef device::PORT<device::PORT6, device::bitpos::B4, 0> SDC_POWER;	///< '0'でＯＮ
    typedef device::NULL_PORT SDC_WP;		///< 書き込み禁止は使わない
    typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::option::THIRD> SDC;

	// GLCDC 関係定義
	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	static const uint32_t LCD_ORG = 0x0000'0100;
	typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::option::FIRST_I2C> FT5206_I2C;

#elif defined(SIG_RX72N)
	/// RX72N Envision Kit
	static const char* system_str_ = { "RX72N Envision Kit" };
	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;

	// SDHI 関係定義（RX72N Envision Kit の SDHI ポートは、候補３で指定できる）
    typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;	///< '1'でＯＮ
    typedef device::NULL_PORT SDC_WP;  ///< カード書き込み禁止ポート設定
    typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::option::THIRD> SDC;

	// GLCDC 関係定義
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	static const uint32_t LCD_ORG = 0x0080'0000;
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::option::THIRD_I2C> FT5206_I2C;

#endif

	typedef utils::fixed_fifo<char, 1024> RECV_BUFF;
	typedef utils::fixed_fifo<char, 2048> SEND_BUFF;
	typedef device::sci_io<SCI_CH, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

    SDC			sdc_;

	// コマンドライン
	typedef utils::command<256> CMD;
	CMD 		cmd_;

	// SD-CARD 操作コンテキスト
	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);

	// GLCDC 関係リソース
	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC;

	// フォントの定義
	typedef graphics::font8x16 AFONT;
// 	for cash into SD card /kfont16.bin
//	typedef graphics::kfont<16, 16, 64> KFONT;
	typedef graphics::kfont<16, 16> KFONT;
	typedef graphics::font<AFONT, KFONT> FONT;

	// DRW2D レンダラー
//	typedef device::drw2d_mgr<GLCDC, FONT> RENDER;
	// ソフトウェアーレンダラー
	typedef graphics::render<GLCDC, FONT> RENDER;
	// 標準カラーインスタンス
	typedef graphics::def_color DEF_COLOR;

	GLCDC		glcdc_(nullptr, reinterpret_cast<void*>(LCD_ORG));
	AFONT		afont_;
	KFONT		kfont_;
	FONT		font_(afont_, kfont_);
	RENDER		render_(glcdc_, font_);

	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> TOUCH;
	TOUCH		touch_(ft5206_i2c_);

	typedef gui::dialog<RENDER, TOUCH> DIALOG;
	DIALOG		dialog_(render_, touch_);

	// 最大３２個の Widget 管理
	typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
	WIDD		widd_(render_, touch_);

	typedef gui::button BUTTON;
	BUTTON		button_  (vtx::srect(   10, 10+50*0, 80, 32), "Button");
	typedef gui::check CHECK;
	CHECK		check_(vtx::srect(   10, 10+50*1, 0, 0), "Check");  // サイズ０指定で標準サイズ
	typedef gui::group<3> GROUP3;
	GROUP3		group_(vtx::srect(   10, 10+50*2, 0, 0));
	typedef gui::radio RADIO;
	RADIO		radioR_(vtx::srect(   0, 50*0, 0, 0), "Red");
	RADIO		radioG_(vtx::srect(   0, 50*1, 0, 0), "Green");
	RADIO		radioB_(vtx::srect(   0, 50*2, 0, 0), "Blue");
	typedef gui::slider SLIDER;
	SLIDER		sliderh_(vtx::srect(200, 20, 200, 0), 0.5f);
	SLIDER		sliderv_(vtx::srect(440, 20, 0, 200), 0.0f);
	typedef gui::menu MENU;
	MENU		menu_(vtx::srect(120, 70, 100, 0), "ItemA,ItemB,ItemC,ItemD");

	void setup_gui_()
	{
		button_.enable();
		button_.at_select_func() = [=](uint32_t id) {
			utils::format("Select Button: %d\n") % id;
		};

		check_.enable();
		check_.at_select_func() = [=](bool ena) {
			utils::format("Select Check: %s\n") % (ena ? "On" : "Off");
		};

		// グループにラジオボタンを登録
		group_ + radioR_ + radioG_ + radioB_;
		group_.enable();  // グループ登録された物が全て有効になる。
		radioR_.at_select_func() = [=](bool ena) {
			utils::format("Select Red: %s\n") % (ena ? "On" : "Off");
		};
		radioG_.at_select_func() = [=](bool ena) {
			utils::format("Select Green: %s\n") % (ena ? "On" : "Off");
		};
		radioB_.at_select_func() = [=](bool ena) {
			utils::format("Select Blue: %s\n") % (ena ? "On" : "Off");
		};
		radioG_.exec_select();  // 最初に選択されるラジオボタン

		sliderh_.enable();
		sliderh_.at_select_func() = [=](float val) {
			utils::format("Slider H: %3.2f\n") % val;
		};
		sliderv_.enable();
		sliderv_.at_select_func() = [=](float val) {
			utils::format("Slider V: %3.2f\n") % val;
		};

		menu_.enable();
		menu_.at_select_func() = [=](uint32_t pos, uint32_t num) {
			char tmp[32];
			menu_.get_select_text(tmp, sizeof(tmp));
			utils::format("Menu: '%s', %u/%u\n") % tmp % pos % num;
		};
	}


	void cmd_service_()
	{
		// コマンド入力と、コマンド解析
		if(!cmd_.service()) {
			return;
		}
		if(shell_.analize()) {
			return;
		}
#if 0
		auto cmdn = cmd_.get_words();
		if(cmd_.cmp_word(0, "play")) {  // play [xxx]
			if(cmdn >= 2) {
				char tmp[FF_MAX_LFN + 1];
				cmd_.get_word(1, tmp, sizeof(tmp));
				if(std::strcmp(tmp, "*") == 0) {
					codec_mgr_.play("");
				} else {
					codec_mgr_.play(tmp);
				}
			} else {
				codec_mgr_.play("");
			}
		} else if(cmd_.cmp_word(0, "help") || cmd_.cmp_word(0, "?")) {
			shell_.help();
			utils::format("    play file-name\n");
		} else {
			utils::format("Command error: '%s'\n") % cmd_.get_command();
		}
#endif
	}
}


/// widget の登録・グローバル関数
bool insert_widget(gui::widget* w)
{
    return widd_.insert(w);
}

/// widget の解除・グローバル関数
void remove_widget(gui::widget* w)
{
    widd_.remove(w);
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
        auto ch = sci_.getch();
        return ch;
	}


	uint16_t sci_length()
	{
		return sci_.recv_length();
	}


	DSTATUS disk_initialize(BYTE drv) {
		return sdc_.disk_initialize(drv);
	}


	DSTATUS disk_status(BYTE drv) {
		return sdc_.disk_status(drv);
	}


	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdc_.disk_read(drv, buff, sector, count);
	}


	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdc_.disk_write(drv, buff, sector, count);
	}


	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdc_.disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
		return 0;
	}


	void setup_touch_panel_()
	{
		render_.sync_frame();
		dialog_.modal(vtx::spos(400, 60),
			"Touch panel device wait...\nPlease touch it with some screen.");
		uint8_t nnn = 0;
		while(1) {
			render_.sync_frame();
			touch_.update();
			auto num = touch_.get_touch_num();
			if(num == 0) {
				++nnn;
				if(nnn >= 60) break;
			} else {
				nnn = 0;
			}
		}
		render_.clear(DEF_COLOR::Black);
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	{  // SD カード・クラスの初期化
		sdc_.start();
	}

	utils::format("\rStart for GUI Sample: '%s'\n") % system_str_;

	{  // GLCDC の初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 0;  // DISP Disable
		LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
		if(glcdc_.start()) {
			utils::format("Start GLCDC\n");
			LCD_DISP::P  = 1;  // DISP Enable
			LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
			if(!glcdc_.control(GLCDC::CONTROL_CMD::START_DISPLAY)) {
				utils::format("GLCDC ctrl fail...\n");
			}
		} else {
			utils::format("GLCDC Fail\n");
		}
	}

	{  // FT5206 touch screen controller
		TOUCH::reset<FT5206_RESET>();
		uint8_t intr_lvl = 1;
		if(!ft5206_i2c_.start(FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
			utils::format("FT5206 I2C Start Fail...\n");
		}
		if(!touch_.start()) {
			utils::format("FT5206 Start Fail...\n");
		}
	}

	setup_touch_panel_();

	setup_gui_();

	cmd_.set_prompt("# ");

	LED::OUTPUT();  // LED ポートを出力に設定

	uint8_t cnt = 0;
	while(1) {
		render_.sync_frame();
		touch_.update();			

		widd_.update();

		sdc_.service();

		cmd_service_();

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

