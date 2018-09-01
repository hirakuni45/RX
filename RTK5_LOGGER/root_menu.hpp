#pragma once
//=====================================================================//
/*!	@file
	@brief	ルート・メニュー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "scenes_base.hpp"
#include "common/format.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ルート・メニュー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class root_menu {

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		root_menu() { }


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init()
		{
			at_scenes_base().at_menu().clear();
			at_scenes_base().at_menu().set_gap(20);
			at_scenes_base().at_menu().set_space(12, 8);
			at_scenes_base().at_menu().add("Lap Time");
			at_scenes_base().at_menu().add("Recall");
			at_scenes_base().at_menu().add("Setup");
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service()
		{
			at_scenes_base().at_render().clear(0);

			const auto& touch = at_scenes_base().at_touch();
			bool t = touch.get_touch_num() == 1 ? true : false;
			int16_t x = touch.get_touch_pos(0).x;
			int16_t y = touch.get_touch_pos(0).y;
			bool trg = at_scenes_base().at_menu().render(x, y, t);
			if(trg) {
				auto pos = at_scenes_base().at_menu().get_pos();
//				utils::format("Menu: %d\n") % static_cast<int>(pos);
				switch(pos) {
				case 0:
					change_scene(scenes_id::laptime);
					break;
				case 1:
					change_scene(scenes_id::recall);
					break;
				case 2:
					change_scene(scenes_id::setup);
					break;
				}
			}
		}
	};
}
