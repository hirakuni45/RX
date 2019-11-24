#pragma once
//=====================================================================//
/*!	@file
	@brief	オーディオ GUI クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/filer.hpp"
#include "graphics/dialog.hpp"
#include "graphics/img_in.hpp"
#include "graphics/widget_director.hpp"

#include "chip/FAMIPAD.hpp"
#include "chip/FT5206.hpp"

namespace app {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  AUDIO GUI クラス
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    class audio_gui {
	public:
		static const int16_t LCD_X = 480;
		static const int16_t LCD_Y = 272;
		static const auto PIX = graphics::pixel::TYPE::RGB565;

		typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
		typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
		typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC;

		typedef graphics::font8x16 AFONT;
//  	for cash into SD card /kfont16.bin
//		typedef graphics::kfont<16, 16, 64> KFONT;
		typedef graphics::kfont<16, 16> KFONT;
		typedef graphics::font<AFONT, KFONT> FONT;

//	typedef device::drw2d_mgr<GLCDC, FONT> RENDER;
		// ソフトウェアーレンダラー
		typedef graphics::render<GLCDC, FONT> RENDER;

		typedef graphics::def_color DEF_COLOR;

	private:
		GLCDC	glcdc_;
		AFONT	afont_;
		KFONT	kfont_;
		FONT	font_;
		RENDER	render_;

		// FT5206, SCI6 簡易 I2C 定義
		typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
		typedef utils::fixed_fifo<uint8_t, 64> RB6;
		typedef utils::fixed_fifo<uint8_t, 64> SB6;
		typedef device::sci_i2c_io<device::SCI6, RB6, SB6,
		device::port_map::option::FIRST_I2C> FT5206_I2C;

		FT5206_I2C	ft5206_i2c_;
		typedef chip::FT5206<FT5206_I2C> TOUCH;
		TOUCH	touch_;
		// INT to P02(IRQ10)

		typedef gui::filer<RENDER> FILER;
		FILER	filer_;

		typedef gui::dialog<RENDER, TOUCH> DIALOG;
		DIALOG	dialog_;

		typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
		WIDD	widd_;

		typedef gui::button BUTTON;
		BUTTON	select_;
		BUTTON	rew_;
		BUTTON	play_;
//		BUTTON	pause_;
		BUTTON	ff_;

		uint32_t	ctrl_;

		char		path_[256];

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  AUDIO GUI コンストラクタ
		*/
		//-------------------------------------------------------------//
		audio_gui() noexcept :
			glcdc_(nullptr, reinterpret_cast<void*>(0x00000100)),
			afont_(), kfont_(), font_(afont_, kfont_),
			render_(glcdc_, font_),
			ft5206_i2c_(), touch_(ft5206_i2c_),
			filer_(render_, false),
			dialog_(render_, touch_),
			widd_(render_, touch_),
			select_(vtx::srect(   0, 272-64*2-6, 64, 64), "Sel"),
			rew_(   vtx::srect(70*0, 272-64, 64, 64), "<<"),
			play_(  vtx::srect(70*1, 272-64, 64, 64), "Play"),
			ff_(    vtx::srect(70*2, 272-64, 64, 64), ">>"),
			ctrl_(0), path_{ 0 }
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief  レンダーの参照
			@return レンダー
		*/
		//-------------------------------------------------------------//
		RENDER& at_render() noexcept { return render_; }


		//-------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-------------------------------------------------------------//
		void start() noexcept
		{
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

			{  // DRW2D 初期化
				auto ver = render_.get_version();
				utils::format("DRW2D Version: %04X\n") % ver;
				if(render_.start()) {
					utils:: format("Start DRW2D\n");
				} else {
					utils:: format("DRW2D Fail\n");
				}
			}

#ifdef ENABLE_FAMIPAD
			{  // ファミコンパッド初期化
				PAD_VCC::DIR = 1;
				PAD_VCC::P = 1;
				PAD_GND::DIR = 1;
				PAD_GND::P = 0;
				famipad_.start();
			}
#endif

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
		}


		void setup_touch_panel() noexcept
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
///					update_led_();
			}
			render_.clear(DEF_COLOR::Black);
		}


		bool insert_widget(gui::widget* w) noexcept {
			return widd_.insert(w);
		}


		void remove_widget(gui::widget* w) noexcept {
			widd_.remove(w);
		}


		//-------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-------------------------------------------------------------//
		void open() noexcept
		{
			select_.enable();
            select_.at_select_func() = [this](uint32_t id) {
				gui::set(gui::filer_ctrl::OPEN, ctrl_);
				enable(false);
			};

			rew_.enable();
			play_.enable();
			ff_.enable();
		}


		//-------------------------------------------------------------//
		/*!
			@brief  GUI クローズ
		*/
		//-------------------------------------------------------------//
		void enable(bool ena = true) noexcept
		{
			ff_.enable(ena);
			play_.enable(ena);
			rew_.enable(ena);
			select_.enable(ena);
		}


		//-------------------------------------------------------------//
		/*!
			@brief  GUI 関係更新
			@param[in]	mount	SD カードマウント状態
			@return ファイルが選択されたら「true」
		*/
		//-------------------------------------------------------------//
		bool update(bool mount) noexcept
		{
			render_.sync_frame();
			touch_.update();

			ctrl_ = 0;
			if(mount) {
				gui::set(gui::filer_ctrl::MOUNT, ctrl_);
			}
			widd_.update();

			bool ret = false;
			{
#ifdef ENABLE_FAMIPAD
				auto data = get_fami_pad();
				if(chip::on(data, chip::FAMIPAD_ST::SELECT)) {
					gui::set(gui::filer_ctrl::OPEN, ctrl_);
				}
				if(chip::on(data, chip::FAMIPAD_ST::UP)) {
					gui::set(gui::filer_ctrl::UP, ctrl_);
				}
				if(chip::on(data, chip::FAMIPAD_ST::DOWN)) {
					gui::set(gui::filer_ctrl::DOWN, ctrl_);
				}
				if(chip::on(data, chip::FAMIPAD_ST::LEFT)) {
					gui::set(gui::filer_ctrl::BACK, ctrl_);
				}
				if(chip::on(data, chip::FAMIPAD_ST::RIGHT)) {
					gui::set(gui::filer_ctrl::SELECT, ctrl_);
				}
#endif
				auto tnum = touch_.get_touch_num();
				const auto& t = touch_.get_touch_pos(0);
				filer_.set_touch(tnum, t.pos); 
				path_[0] = 0;
				if(filer_.update(ctrl_, path_, sizeof(path_))) {
					enable();
					widd_.redraw_all();
//					utils::format("Play: '%s'\n") % path_;
					ret = true;
				}
			}
			return ret;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  ファイル名の取得
			@return ファイル名
		*/
		//-------------------------------------------------------------//
		const char* get_filename() const noexcept { return path_; }
	};
}
