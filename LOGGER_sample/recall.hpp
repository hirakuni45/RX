#pragma once
//=====================================================================//
/*!	@file
	@brief	リコール
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/format.hpp"
#include "scenes_base.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	リコール・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class recall : public utils::scene {

		typedef scenes_base::RENDER RENDER;
		typedef graphics::def_color DEF_COLOR;

		gui::button		button_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		recall() noexcept :
			button_(vtx::srect( 30, 20, 80, 30), "OK") {
		}


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init() override
		{
			at_scenes_base().at_render().clear(DEF_COLOR::Black);

			button_.enable();
			button_.at_select_func() = [this](uint32_t id) {
				change_scene(scene_id::root_menu);
			};

			at_scenes_base().at_render().clear(DEF_COLOR::Black);
			at_scenes_base().enable_filer();
			at_scenes_base().get_filer_state();
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service() override
		{
			auto f = at_scenes_base().get_filer_state();
			if(!f) {
				change_scene(scene_id::root_menu);
			}
		}


		//-------------------------------------------------------------//
		/*!
			@brief	シーンの終了
		*/
		//-------------------------------------------------------------//
		void exit() override
		{
			button_.enable(false);
		}
	};
}
