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

#define CASH_KFONT
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/jpeg_in.hpp"
#include "graphics/bmp_in.hpp"
#include "chip/FT5206.hpp"

// #define SOFT_I2C

#ifdef SOFT_I2C
#include "common/si2c_io.hpp"
#else
#include "common/sci_i2c_io.hpp"
#endif

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン ID
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class scenes_id {
		title,
		root_menu,
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン・ベース
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class scenes_base {
	public:
		// GLCDC
		static const int16_t LCD_X = 480;
		static const int16_t LCD_Y = 272;
		typedef device::glcdc_io<device::GLCDC, LCD_X, LCD_Y,
			device::glcdc_def::PIX_TYPE::RGB565> GLCDC_IO;

		// DRW2D
		typedef device::drw2d_mgr<device::DRW2D, LCD_X, LCD_Y> DRW2D_MGR;

		typedef graphics::font8x16 AFONT;
		typedef graphics::kfont<16, 16, 64> KFONT;

		typedef graphics::render<uint16_t, LCD_X, LCD_Y, AFONT, KFONT> RENDER;

	private:
		typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
		typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;

		GLCDC_IO	glcdc_io_;
		DRW2D_MGR	drw2d_mgr_;

		KFONT		kfont_;

		RENDER		render_;

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
		FT5206_I2C	ft5206_i2c_;
		typedef chip::FT5206<FT5206_I2C> FT5206;
		FT5206		ft5206_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		*/
		//-------------------------------------------------------------//
		scenes_base() : render_(reinterpret_cast<uint16_t*>(0x00000000), kfont_),
			ft5206_(ft5206_i2c_) { }


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
			@brief	RENDER の参照
			@return RENDER
		*/
		//-------------------------------------------------------------//
		RENDER& at_render() noexcept { return render_; }
	};
}

extern void change_scene(app::scenes_id id);
extern app::scenes_base& at_scenes_base();
