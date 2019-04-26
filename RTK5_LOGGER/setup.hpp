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

		gui::button		btn_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		setup() noexcept : btn_(vtx::srect(100, 50, 80, 30), "OK")
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init() noexcept override
		{
			at_scenes_base().at_render().clear(DEF_COLOR::Black);

//			btn_.at_location().org.set(100, 50);
//			btn_.at_location().size.set(80, 30);
//			btn_.set_title("OK");
//			insert_widget(&btn_);

			btn_.set_state(gui::widget::STATE::ENABLE);
			btn_.at_select_func() = [this](uint32_t id) {
				change_scene(scene_id::root_menu);
			};
//			at_scenes_base().at_widget_director().list_all();
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service() noexcept override
		{
			btn_.set_state(gui::widget::STATE::ENABLE);


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
			btn_.set_state(gui::widget::STATE::DISABLE);
		}
	};
}
