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
#include "common/time.h"

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
			at_scenes_base().at_menu().set_space(vtx::spos(12, 8));
			at_scenes_base().at_menu().add("Lap Time");
			at_scenes_base().at_menu().add("Recall");
			at_scenes_base().at_menu().add("Setup");
			at_scenes_base().at_menu().add("G.P.S.");
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service()
		{
			at_scenes_base().at_render().clear(graphics::def_color::Black);

			{
				static const int16_t LOC_Y = scenes_base::RENDER::glc_type::height - 16;
				auto& nmea = at_scenes_base().at_nmea();
				char tmp[32];
				auto stn = nmea.get_satellite_num();
				utils::sformat("%d", tmp, sizeof(tmp)) % stn;
				at_scenes_base().at_render().draw_text(vtx::spos(0, LOC_Y), tmp);
				if(stn > 0) {
					auto t = nmea.get_gmtime();
					struct tm *m = localtime(&t);
					utils::sformat("%s %s %d %02d:%02d:%02d  %4d\n", tmp, sizeof(tmp))
						% get_wday(m->tm_wday)
						% get_mon(m->tm_mon)
						% static_cast<uint32_t>(m->tm_mday)
						% static_cast<uint32_t>(m->tm_hour)
						% static_cast<uint32_t>(m->tm_min)
						% static_cast<uint32_t>(m->tm_sec)
						% static_cast<uint32_t>(m->tm_year + 1900);
				} else {
					strcpy(tmp, "--- --- - --:--:--  ----");
				}
				at_scenes_base().at_render().draw_text(vtx::spos(24, LOC_Y), tmp);
			}

			const auto& touch = at_scenes_base().at_touch();
			bool t = touch.get_touch_num() == 1 ? true : false;
			const auto& p = touch.get_touch_pos(0);
			bool trg = at_scenes_base().at_menu().render(p.x, p.y, t);
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
				case 3:
					change_scene(scenes_id::gps);
					break;
				}
			}
		}
	};
}
