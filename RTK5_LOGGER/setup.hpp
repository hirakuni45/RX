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
		gui::slider		slider_;
		

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
			radio1_(vtx::srect( 30, 70 + 40*1, 0, 0), "Red"),
			radio2_(vtx::srect( 30, 70 + 40*2, 0, 0), "Green"),
			radio3_(vtx::srect( 30, 70 + 40*3, 0, 0), "Blue"),
			slider_(vtx::srect(150,20, 120, 0))
		{ }


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
			group_ + radio1_ + radio2_ + radio3_;
			radio1_.enable();
			radio2_.enable();
			radio3_.enable();
			slider_.enable();
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
			radio1_.enable(false);
			radio2_.enable(false);
			radio3_.enable(false);
			slider_.enable(false);
		}
	};
}
