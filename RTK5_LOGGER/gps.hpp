#pragma once
//=====================================================================//
/*!	@file
	@brief	ＧＰＳ表示
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
		@brief	ＧＰＳ表示・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class gps {

		typedef scenes_base::RENDER RENDER;
		typedef graphics::def_color DEF_COLOR;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		gps() noexcept { }


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init() noexcept
		{
			at_scenes_base().at_render().clear(DEF_COLOR::Black);
//			auto& nmea = at_scenes_base().at_nmea();
//			nmea.set_baudrate(scenes_base::NMEA::BAUDRATE::B57600);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service() noexcept
		{
			auto& nmea = at_scenes_base().at_nmea();
			auto n = nmea.get_satellite_num();
//			const auto& info = nmea.get_satellite_info();

			const auto& touch = at_scenes_base().at_touch();
			bool t = touch.get_touch_num() == 1 ? true : false;
//			const auto& p = touch.get_touch_pos(0);
			if(t) {
				change_scene(scenes_id::root_menu);
			}
		}
	};
}
