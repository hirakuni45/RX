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
		gui::check		lap_button_check_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		setup() noexcept :
			button_(vtx::srect( 30, 20, 80, 30), "Exit"),
			lap_button_check_(vtx::srect(  30, 70 + 40*0, 0, 0), "LAP Button")
		{
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
			lap_button_check_.enable();
//			check_.at_select_func() = [this](bool ena) {
//				utils::format("Check: %d\n") % static_cast<int>(ena);
//			};
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service() noexcept override
		{
		}


		//-------------------------------------------------------------//
		/*!
			@brief	シーンの終了
		*/
		//-------------------------------------------------------------//
		void exit() noexcept override
		{
			button_.enable(false);
			lap_button_check_.enable(false);
		}
	};
}
