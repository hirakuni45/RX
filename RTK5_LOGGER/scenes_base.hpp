#pragma once
//=====================================================================//
/*!	@file
	@brief	シーン共通関係
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/font8x16.hpp"

// 漢字フォントをキャッシュする場合
#define CASH_KFONT
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/picojpeg_in.hpp"
#include "graphics/scaling.hpp"
#include "graphics/img_in.hpp"
#include "graphics/menu.hpp"
#include "chip/FT5206.hpp"

// #define SOFT_I2C

#ifdef SOFT_I2C
#include "common/si2c_io.hpp"
#else
#include "common/sci_i2c_io.hpp"
#endif

#include "common/cmt_io.hpp"

#include "resource.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン ID
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class scenes_id {
		title,
		root_menu,

		laptime,
		recall,
		setup
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン・ベース
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class scenes_base {

		typedef device::PORT<device::PORT0, device::bitpos::B5> SW2;

	public:
		/// GLCDC
		static const int16_t LCD_X = 480;
		static const int16_t LCD_Y = 272;
		typedef device::glcdc_io<device::GLCDC, LCD_X, LCD_Y,
			device::glcdc_def::PIX_TYPE::RGB565> GLCDC_IO;

		/// DRW2D
		typedef device::drw2d_mgr<device::DRW2D, LCD_X, LCD_Y> DRW2D_MGR;

		typedef graphics::font8x16 AFONT;
		typedef graphics::kfont<16, 16, 64> KFONT;

		typedef graphics::render<uint16_t, LCD_X, LCD_Y, AFONT, KFONT> RENDER;

		// FT5206, SCI6 簡易 I2C 定義
		typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
#ifdef SOFT_I2C
		typedef device::PORT<device::PORT0, device::bitpos::B0> FT5206_SDA;
		typedef device::PORT<device::PORT0, device::bitpos::B1> FT5206_SCL;
		typedef device::si2c_io<FT5206_SDA, FT5206_SCL> FT5206_I2C;
#else
		typedef utils::fixed_fifo<uint8_t, 64> RECV6_BUFF;
		typedef utils::fixed_fifo<uint8_t, 64> SEND6_BUFF;
		typedef device::sci_i2c_io<device::SCI6, RECV6_BUFF, SEND6_BUFF,
				device::port_map::option::FIRST_I2C> FT5206_I2C;
#endif
		// FT5206 touch device
		typedef chip::FT5206<FT5206_I2C> FT5206;

		typedef resource<RENDER> RESOURCE;

	private:
		GLCDC_IO	glcdc_io_;
		DRW2D_MGR	drw2d_mgr_;
		KFONT		kfont_;
		RENDER		render_;

	public:
		// 最大８個のメニュー
		class BACK {
			RENDER&	render_;
		public:
			BACK(RENDER& render) : render_(render) { }

			void operator () (int16_t x, int16_t y, int16_t w, int16_t h, RENDER::value_type c)
			{
				render_.round_box(x, y, w, h, 8, c);
//				render_.fill_box_r(x + 3, y + 3, w - 6, h - 6, c);
			}
		};
		typedef graphics::menu<RENDER, BACK, 8> MENU;

		typedef img::scaling<RENDER> PLOT;
		typedef img::img_in<PLOT> IMG_IN;

		// CMT 1/100 秒計測
		class watch_task {
		public:
			static const uint32_t LAP_LIMIT = 500;

		private:
			uint32_t	count_;
			bool		enable_;
			bool		lvl_;

			uint32_t	lap_pos_;
			uint32_t	lap_pad_[LAP_LIMIT];

		public:
			watch_task() : count_(0), enable_(false), lvl_(false),
				lap_pos_(0), lap_pad_{ 0 } { }

			void operator() () noexcept
			{
				bool lvl = !SW2::P();
				if(enable_) {
					if(!lvl_ && lvl) {
						if(lap_pos_ < LAP_LIMIT) {
							lap_pad_[lap_pos_] = count_;
							++lap_pos_;
						}
					}
					++count_;
				}
				lvl_ = lvl;
			}

			void enable(bool ena = true) noexcept { enable_ = ena; }

			void set(uint32_t count) noexcept { count_ = count; }

			uint32_t get() const noexcept { return count_; }

			void reset() noexcept
			{
				count_ = 0;
				lap_pos_ = 0;
			}

			uint32_t get_lap_pos() const noexcept { return lap_pos_; }

			uint32_t get_lap(uint32_t pos) const noexcept {
				if(pos >= LAP_LIMIT) return 0;
				return lap_pad_[pos];
			}
		};
		typedef device::cmt_io<device::CMT0, watch_task> CMT;

	private:
		typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
		typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;

		FT5206_I2C	ft5206_i2c_;
		FT5206		ft5206_;

		MENU		menu_;
		BACK		back_;

		CMT			cmt_;

		RESOURCE	resource_;

		PLOT		plot_;
		IMG_IN		img_in_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		*/
		//-------------------------------------------------------------//
		scenes_base() noexcept : render_(reinterpret_cast<uint16_t*>(0x00000000), kfont_),
			ft5206_(ft5206_i2c_), menu_(render_, back_), back_(render_), resource_(render_),
			plot_(render_), img_in_(plot_) { }


		//-------------------------------------------------------------//
		/*!
			@brief	ベースの初期化
		*/
		//-------------------------------------------------------------//
		void init() noexcept
		{
			{  // GLCDC の初期化
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
					utils::format("GLCDC Fail\n");
				}
			}

			{  // DRW2D 初期化
				auto ver = drw2d_mgr_.get_version();
				utils::format("DRW2D Version: %04X\n") % ver;

				if(drw2d_mgr_.start(0x00000000)) {
					utils:: format("Start DRW2D\n");
				} else {
					utils:: format("DRW2D Fail\n");
				}
			}
			{  // FT5206 touch screen controller
				FT5206::reset<FT5206_RESET>();
				uint8_t intr_lvl = 1;
				if(!ft5206_i2c_.start(FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
					utils::format("FT5206 I2C Start Fail...\n");
				}
				if(!ft5206_.start()) {
					utils::format("FT5206 Start Fail...\n");
				}
			}

			{  // CMT 100Hz タイマー
				uint8_t intr_level = 5;
				cmt_.start(100, intr_level);
			}

			// スイッチ入力
			SW2::DIR = 0;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	同期と、タッチパネルデータ更新
		*/
		//-------------------------------------------------------------//
		void sync() noexcept
		{
			glcdc_io_.sync_vpos();
			ft5206_.update();
		}


		//-------------------------------------------------------------//
		/*!
			@brief	GLCDC_IO の参照
			@return GLCDC_IO
		*/
		//-------------------------------------------------------------//
		GLCDC_IO& at_glcdc_io() noexcept { return glcdc_io_; }


		//-------------------------------------------------------------//
		/*!
			@brief	タッチデバイスの参照
			@return タッチデバイス
		*/
		//-------------------------------------------------------------//
		FT5206& at_touch() noexcept { return ft5206_; }


		//-------------------------------------------------------------//
		/*!
			@brief	RENDER の参照
			@return RENDER
		*/
		//-------------------------------------------------------------//
		RENDER& at_render() noexcept { return render_; }


		//-------------------------------------------------------------//
		/*!
			@brief	MENU の参照
			@return MENU
		*/
		//-------------------------------------------------------------//
		MENU& at_menu() noexcept { return menu_; }


		//-------------------------------------------------------------//
		/*!
			@brief	CMT の参照
			@return CMT
		*/
		//-------------------------------------------------------------//
		CMT& at_cmt() noexcept { return cmt_; }


		//-------------------------------------------------------------//
		/*!
			@brief	RESOURCE の参照
			@return RESOURCE
		*/
		//-------------------------------------------------------------//
		RESOURCE& at_resource() noexcept { return resource_; }


		//-------------------------------------------------------------//
		/*!
			@brief	PLOT の参照
			@return PLOT
		*/
		//-------------------------------------------------------------//
		PLOT& at_plot() noexcept { return plot_; }


		//-------------------------------------------------------------//
		/*!
			@brief	IMG_IN の参照
			@return IMG_IN
		*/
		//-------------------------------------------------------------//
		IMG_IN& at_img() noexcept { return img_in_; }
	};
}

extern void change_scene(app::scenes_id id);
extern app::scenes_base& at_scenes_base();
