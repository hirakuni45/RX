#pragma once
//=====================================================================//
/*!	@file
	@brief	セットアップ
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/scene.hpp"
#include "common/format.hpp"
#include "scenes_base.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	セットアップ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class setup : public utils::scene {

		typedef scenes_base::RENDER RENDER;
		typedef graphics::def_color DEF_COLOR;

		gui::button		button_;
		gui::check		check_;
		gui::group		group_;
		gui::radio		radio1_;
		gui::radio		radio2_;
		gui::radio		radio3_;
		gui::slider		sliderh_;
		gui::slider		sliderv_;
		gui::menu		menu_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		setup() noexcept :
			button_(vtx::srect( 30, 20, 80, 30), "OK"),
			check_(vtx::srect(  30, 70 + 40*0, 0, 0), "Check"),
			group_(vtx::srect(  30, 70 + 40*1, 0, 0)),
			radio1_(vtx::srect(  0, 40*0, 0, 0), "Red"),
			radio2_(vtx::srect(  0, 40*1, 0, 0), "Green"),
			radio3_(vtx::srect(  0, 40*2, 0, 0), "Blue"),
			sliderh_(vtx::srect(150,20, 150, 0), 0.5f),
			sliderv_(vtx::srect(450,20, 0, 200), 1.0f),
			menu_(vtx::srect(150, 70, 100, 0), "Red,Green,Blue,White")
		{
			group_ + radio1_ + radio2_ + radio3_;
			radio2_.exec_select();  // 初期 radio2_ を有効にする
		}


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init() noexcept override
		{
			at_scenes_base().at_render().clear(DEF_COLOR::Black);

			button_.enable();
			button_.at_select_func() = [this](uint32_t id) {
				change_scene(scene_id::root_menu);
			};
			check_.enable();
			check_.at_select_func() = [this](bool ena) {
				utils::format("Check: %d\n") % static_cast<int>(ena);
			};

			group_.enable();  // ラジオボタングループ

			sliderh_.enable();
			sliderh_.at_select_func() = [this](float val) {
				utils::format("SliderH: %4.3f\n") % val;
			};
			sliderv_.enable();
			sliderv_.at_select_func() = [this](float val) {
				utils::format("SliderV: %4.3f\n") % val;
			};

			menu_.enable();
			menu_.at_select_func() = [this](uint32_t pos, uint32_t num) {
				utils::format("Menu: %u/%u\n") % pos % num;
			};
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service() noexcept override
		{
#if 0
			const auto& touch = at_scenes_base().at_touch();
			bool t = touch.get_touch_num() == 1 ? true : false;
//			const auto& p = touch.get_touch_pos(0);
			if(t) {
				change_scene(scenes_id::root_menu);
			}
#endif
		}


		//-------------------------------------------------------------//
		/*!
			@brief	シーンの終了
		*/
		//-------------------------------------------------------------//
		void exit() noexcept override
		{
			button_.enable(false);
			check_.enable(false);
			group_.enable(false);
			sliderh_.enable(false);
			sliderv_.enable(false);
			menu_.enable(false);
		}
	};
}
