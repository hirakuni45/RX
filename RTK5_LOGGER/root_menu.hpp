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
#if 0
			auto& core = at_core();

			core.menu_.set_space(4);
			core.menu_.add(core_t::MENU::type::PROP, "Laptimer");
			core.menu_.add(core_t::MENU::type::PROP, "Logging");
			core.menu_.add(core_t::MENU::type::PROP, "Recall");
			core.menu_.add(core_t::MENU::type::PROP, "Setup");
#endif
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service()
		{
			at_scenes_base().at_render().clear(0);

#if 0
			auto& core = at_core();

			core.bitmap_.frame(0, 0, 128, 64, 1);
			core.menu_.render();

			// 衛星数の表示
			core.bitmap_.draw_text(2, 1, core.nmea_.get_satellite());

			// マウント状態の表示
			if(core.sdc_.get_mount()) {
				core.bitmap_.draw_font(128 - 8, 1, '*'); 
			}

			int n = core.menu_run_;
			switch(n) {
			case 0:
				select_scene(app::scene_id::laptimer);
				core.menu_.clear();
				break;
			case 1:
				select_scene(app::scene_id::logging);
				core.menu_.clear();
				break;
			case 2:
				select_scene(app::scene_id::recall);
				core.menu_.clear();
				break;
			case 3:
				select_scene(app::scene_id::setup);
				core.menu_.clear();
				break;
			default:
				break;
			}
#endif
		}
	};
}
