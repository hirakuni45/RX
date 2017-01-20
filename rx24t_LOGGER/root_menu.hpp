#pragma once
//=====================================================================//
/*!	@file
	@brief	ルート・メニュー・クラス
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"

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
			auto& core = at_core();

			core.menu_.set_space(4);
			core.menu_.add(core_t::MENU::type::PROP, "Logging");
			core.menu_.add(core_t::MENU::type::PROP, "Recall");
			core.menu_.add(core_t::MENU::type::PROP, "Setup");
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service()
		{
			auto& core = at_core();

			core.bitmap_.frame(0, 0, 128, 64, 1);
			core.menu_.render();

			// 衛星数の表示
			core.bitmap_.draw_text(2, 1, core.nmea_.get_satellite());

			int n = core.menu_pos_;
			switch(n) {
			case 0:
				select_scene(app::scene_id::logging);
				core.menu_.clear();
				break;
			case 1:

				break;
			case 2:

				break;
			default:
				break;
			}
		}
	};

}
