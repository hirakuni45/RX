//=====================================================================//
/*! @file
    @brief  RX65N/RX72N GUI サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/sci_i2c_io.hpp"
#include "common/fixed_string.hpp"

#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/simple_dialog.hpp"
#include "graphics/img_in.hpp"
#include "graphics/scaling.hpp"
#include "graphics/img_in.hpp"

#include "gui/widget_director.hpp"

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
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;

	// SDHI 関係定義（RX65N Envision Kit の SDHI ポートは、候補３で指定できる）
    typedef device::PORT<device::PORT6, device::bitpos::B4, 0> SDC_POWER;	///< '0'でＯＮ
    typedef device::NULL_PORT SDC_WP;		///< 書き込み禁止は使わない
    typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::ORDER::THIRD> SDC;

	// GLCDC 関係定義
	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	static const uint32_t LCD_ORG = 0x0000'0100;
	typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::FIRST_I2C> FT5206_I2C;

#elif defined(SIG_RX72N)
	/// RX72N Envision Kit
	static const char* system_str_ = { "RX72N Envision Kit" };
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;

	// SDHI 関係定義（RX72N Envision Kit の SDHI ポートは、候補３で指定できる）
    typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;	///< '1'でＯＮ
    typedef device::NULL_PORT SDC_WP;  ///< カード書き込み禁止ポート設定
    typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::ORDER::THIRD> SDC;

	// GLCDC 関係定義
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	static const uint32_t LCD_ORG = 0x0080'0000;
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::THIRD_I2C> FT5206_I2C;

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
	typedef device::drw2d_mgr<GLCDC, FONT> RENDER;
	// ソフトウェアーレンダラー
//	typedef graphics::render<GLCDC, FONT> RENDER;
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

	typedef gui::simple_dialog<RENDER, TOUCH> DIALOG;
	DIALOG		dialog_(render_, touch_);

	// 最大３２個の Widget 管理
	typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
	WIDD		widd_(render_, touch_);

	typedef gui::widget WIDGET;

	// --- page 1

	typedef gui::button BUTTON;
	BUTTON		button_(vtx::srect(10, 10, 80, 32), "Button");
	BUTTON		button_stall_(vtx::srect(100, 10, 80, 32), "Stall");
	typedef gui::check CHECK;
	CHECK		check_(vtx::srect(   10, 10+50, 0, 0), "Check");  // サイズ０指定で標準サイズ
	typedef gui::group<3> GROUP3;
	GROUP3		group_(vtx::srect(   10, 10+50+40, 0, 0));
	typedef gui::radio RADIO;
	RADIO		radioR_(vtx::srect(   0, 40*0, 0, 0), "Red");
	RADIO		radioG_(vtx::srect(   0, 40*1, 0, 0), "Green");
	RADIO		radioB_(vtx::srect(   0, 40*2, 0, 0), "Blue");
	typedef gui::slider SLIDER;
	SLIDER		sliderh_(vtx::srect(200, 20, 200, 0), 0.5f);
	SLIDER		sliderv_(vtx::srect(460, 20, 0, 200), 0.0f);
	typedef gui::menu MENU;
	MENU		menu_(vtx::srect(120, 70, 100, 0), "ItemA,ItemB,ItemC,ItemD");
	typedef gui::text TEXT;
	TEXT		text_(vtx::srect(240, 70, 150, 20), "１６ピクセル漢字の表示サンプル～");
	typedef gui::textbox TEXTBOX;
	TEXTBOX		textbox_(vtx::srect(240, 100, 160, 80), "");
	typedef gui::spinbox SPINBOX;
	SPINBOX		spinbox_(vtx::srect(20, 220, 120, 0),
					{ .min = -100, .value = 0, .max = 100, .step = 1, .accel = true });
	typedef gui::toggle TOGGLE;
	TOGGLE		toggle_(vtx::srect(160, 220, 0, 0));
	typedef gui::progress PROGRESS;
	PROGRESS	progress_(vtx::srect(240, 220, 150, 0));

	BUTTON		next0_(vtx::srect(480-45, 272-45, 40, 40), ">", BUTTON::STYLE::CIRCLE_WITH_FRAME);

	// --- page 1
	BUTTON		prev1_(vtx::srect(5, 5, 40, 40), "<", BUTTON::STYLE::CIRCLE_WITH_FRAME);
	BUTTON		next1_(vtx::srect(480 - 40 - 5, 5, 40, 40), ">", BUTTON::STYLE::CIRCLE_WITH_FRAME);

	TEXT		text_asc_(vtx::srect(70, 0, 260, 20));
	typedef gui::key_asc KEY_ASC;
	KEY_ASC		key_asc_(vtx::srect((480 - KEY_ASC::BOARD_WIDTH) / 2, 272 - KEY_ASC::BOARD_HEIGHT, WIDGET::SIZE_AUTO, WIDGET::SIZE_AUTO));

	// --- page 2
	BUTTON		prev2_(vtx::srect(5, 5, 40, 40), "<", BUTTON::STYLE::CIRCLE_WITH_FRAME);
	BUTTON		next2_(vtx::srect(480 - 40 - 5, 5, 40, 40), ">", BUTTON::STYLE::CIRCLE_WITH_FRAME);

	TEXT		text_10_(vtx::srect(70, 0, 260, 20));
	typedef gui::key_10 KEY_10;
//	KEY_10		key_10_(vtx::srect(240, 0, WIDGET::SIZE_AUTO, WIDGET::SIZE_AUTO));
	KEY_10		key_10_(vtx::srect(40, 100, WIDGET::SIZE_AUTO, WIDGET::SIZE_AUTO), KEY_10::STYLE::W5_H2);

	// --- page 3
	BUTTON		prev3_(vtx::srect(5, 5, 40, 40), "<", BUTTON::STYLE::CIRCLE_WITH_FRAME);

	typedef gui::filer FILER;
	FILER		filer_(vtx::srect(80, 10, 320, 240));

	float		progress_ratio_ = 0.0f;
	utils::fixed_string<32> buff_asc_;
	utils::fixed_string<16> buff_10_;

	void setup_gui_()
	{
		button_.set_layer(WIDGET::LAYER::_0);
		button_.at_select_func() = [=](uint32_t id) {
			utils::format("Select Button: %d\n") % id;
			if(button_stall_.get_state() == BUTTON::STATE::STALL) {
				button_stall_.set_state(BUTTON::STATE::ENABLE);
				button_stall_.set_title("Active");
			} else if(button_stall_.get_state() == BUTTON::STATE::ENABLE) {
				button_stall_.set_state(BUTTON::STATE::STALL);
				button_stall_.set_title("Stall");
			}
		};
		button_stall_.set_layer(WIDGET::LAYER::_0);
		button_stall_.set_state(BUTTON::STATE::STALL);

		check_.set_layer(WIDGET::LAYER::_0);
		check_.at_select_func() = [=](bool ena) {
			utils::format("Select Check: %s\n") % (ena ? "On" : "Off");
			if(ena) {
				radioR_.set_base_color(DEF_COLOR::White);
				radioG_.set_base_color(DEF_COLOR::White);
				radioB_.set_base_color(DEF_COLOR::White);
				radioR_.set_font_color(DEF_COLOR::White);
				radioG_.set_font_color(DEF_COLOR::White);
				radioB_.set_font_color(DEF_COLOR::White);
			}
		};

		// グループにラジオボタンを登録
		group_ + radioR_ + radioG_ + radioB_;
		group_.set_layer(WIDGET::LAYER::_0);  // レイヤー設定は、親にすればＯＫ。
		radioR_.at_select_func() = [=](bool ena) {
			utils::format("Select Red: %s\n") % (ena ? "On" : "Off");
			if(ena) {
				radioR_.set_base_color(DEF_COLOR::Red);
				radioG_.set_base_color(DEF_COLOR::Red);
				radioB_.set_base_color(DEF_COLOR::Red);
				radioR_.set_font_color(DEF_COLOR::Red);
				radioG_.set_font_color(DEF_COLOR::Red);
				radioB_.set_font_color(DEF_COLOR::Red);
			}
		};
		radioG_.at_select_func() = [=](bool ena) {
			utils::format("Select Green: %s\n") % (ena ? "On" : "Off");
			if(ena) {
				radioR_.set_base_color(DEF_COLOR::Green);
				radioG_.set_base_color(DEF_COLOR::Green);
				radioB_.set_base_color(DEF_COLOR::Green);
				radioR_.set_font_color(DEF_COLOR::Green);
				radioG_.set_font_color(DEF_COLOR::Green);
				radioB_.set_font_color(DEF_COLOR::Green);
			}
		};
		radioB_.at_select_func() = [=](bool ena) {
			utils::format("Select Blue: %s\n") % (ena ? "On" : "Off");
			if(ena) {
				radioR_.set_base_color(DEF_COLOR::Blue);
				radioG_.set_base_color(DEF_COLOR::Blue);
				radioB_.set_base_color(DEF_COLOR::Blue);
				radioR_.set_font_color(DEF_COLOR::Blue);
				radioG_.set_font_color(DEF_COLOR::Blue);
				radioB_.set_font_color(DEF_COLOR::Blue);
			}
		};
		radioG_.exec_select();  // 最初に選択されるラジオボタン

		sliderh_.set_layer(WIDGET::LAYER::_0);
		sliderh_.at_select_func() = [=](float val) {
			utils::format("Slider H: %3.2f\n") % val;
		};
		sliderv_.set_layer(WIDGET::LAYER::_0);
		sliderv_.at_select_func() = [=](float val) {
			utils::format("Slider V: %3.2f\n") % val;
		};

		menu_.set_layer(WIDGET::LAYER::_0);
		menu_.at_select_func() = [=](uint32_t pos, uint32_t num) {
			char tmp[32];
			menu_.get_select_text(tmp, sizeof(tmp));
			utils::format("Menu: '%s', %u/%u\n") % tmp % pos % num;
		};

		text_.set_layer(WIDGET::LAYER::_0);

		textbox_.set_layer(WIDGET::LAYER::_0);
		textbox_.set_title("(1) 項目\n(2) GUI サンプルについて。\n(3) まとめ");
		textbox_.set_vertical_alignment(TEXTBOX::V_ALIGNMENT::CENTER);

		spinbox_.set_layer(WIDGET::LAYER::_0);
		spinbox_.at_select_func() = [=](SPINBOX::TOUCH_AREA area, int16_t value) {
			static const char* st[3] = { "Minus", "Stay", "Plus" };
			utils::format("Spinbox: %s Value: %d\n")
				% st[static_cast<uint8_t>(area)] % value;
		};

		toggle_.set_layer(WIDGET::LAYER::_0);
		toggle_.at_select_func() = [=](bool state) {
			utils::format("Toggle: %s\n") % (state ? "OFF" : "ON");
			if(!state) {
				progress_ratio_ = 0.0f;
			}
		};

		progress_.set_layer(WIDGET::LAYER::_0);
		progress_.at_update_func() = [=](float ratio) {
			if(toggle_.get_switch_state()) {
				ratio += 1.0f / 120.0f;  // 2 sec (60 frame/sec)
				if(ratio > 1.0f) ratio = 1.0f;
			} else {
				ratio = 0.0f;
				progress_ratio_ = 0.0f;
			}
			return ratio;
		};

		// page 0
		next0_.set_layer(WIDGET::LAYER::_0);
		next0_.at_select_func() = [=](uint32_t id) {
			widd_.clear();
			widd_.enable(WIDGET::LAYER::_0, false);
			widd_.enable(WIDGET::LAYER::_1);
		};

		// page 1
		prev1_.set_layer(WIDGET::LAYER::_1);
		prev1_.at_select_func() = [=](uint32_t id) {
			widd_.clear();
			widd_.enable(WIDGET::LAYER::_0);
			widd_.enable(WIDGET::LAYER::_1, false);
		};

		next1_.set_layer(WIDGET::LAYER::_1);
		next1_.at_select_func() = [=](uint32_t id) {
			widd_.clear();
			widd_.enable(WIDGET::LAYER::_1, false);
			widd_.enable(WIDGET::LAYER::_2);
		};

		text_asc_.set_layer(WIDGET::LAYER::_1);
		text_asc_.enable_scroll(false);
		text_asc_.set_title(buff_asc_.c_str());

		key_asc_.set_layer(WIDGET::LAYER::_1);
		key_asc_.at_select_func() = [=](char code, KEY_ASC::KEY_MAP key_map) {
			if(code == KEY_ASC::KEY_BACK_SPACE || code == KEY_ASC::KEY_DEL) {
				buff_asc_.pop_back();
				text_asc_.set_update();
			} else if(code == KEY_ASC::KEY_ENTER) {
				buff_asc_.clear();
				text_asc_.set_update();
			} else if(code >= 0x20 && code <= 0x7f) {
				if(buff_asc_.capacity() == buff_asc_.size()) {
					buff_asc_.erase(0, 1);
				}
				buff_asc_ += code;
				text_asc_.set_update();
			}
			auto map = static_cast<uint16_t>(key_map);
			utils::format("ASCII Key: 0x%02X (%d): '%c'\n") % map % map % code; 
		};

		// page 2
		prev2_.set_layer(WIDGET::LAYER::_2);
		prev2_.at_select_func() = [=](uint32_t id) {
			widd_.clear();
			widd_.enable(WIDGET::LAYER::_1);
			widd_.enable(WIDGET::LAYER::_2, false);
		};
		next2_.set_layer(WIDGET::LAYER::_2);
		next2_.at_select_func() = [=](uint32_t id) {
			widd_.clear();
			widd_.enable(WIDGET::LAYER::_2, false);
			widd_.enable(WIDGET::LAYER::_3);
		};

		text_10_.set_layer(WIDGET::LAYER::_2);
		text_10_.enable_scroll(false);
		text_10_.set_title(buff_10_.c_str());

		key_10_.set_layer(WIDGET::LAYER::_2);
		key_10_.at_select_func() = [=](char code, KEY_10::KEY_MAP key_map) {
			if(buff_10_.capacity() == buff_10_.size()) {
				buff_10_.erase(0, 1);
			}
			buff_10_ += code;
			text_10_.set_update();
			auto map = static_cast<uint16_t>(key_map);
			utils::format("10 Key: 0x%02X (%d): '%c'\n") % map % map % code; 
		};

		// page 3
		prev3_.set_layer(WIDGET::LAYER::_3);
		prev3_.at_select_func() = [=](uint32_t id) {
			widd_.clear();
			widd_.enable(WIDGET::LAYER::_2);
			widd_.enable(WIDGET::LAYER::_3, false);
		};

		filer_.set_layer(WIDGET::LAYER::_3);

		widd_.enable(WIDGET::LAYER::_0);
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
	SYSTEM_IO::boost_master_clock();

	{  // SCI 設定
		auto sci_level = device::ICU::LEVEL::_2;
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
		if(glcdc_.start(device::ICU::LEVEL::_2)) {
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
		auto intr_lvl = device::ICU::LEVEL::_1;
		if(!ft5206_i2c_.start(FT5206_I2C::MODE::MASTER, FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
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

