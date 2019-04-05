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

		bool	trg_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		gps() noexcept : trg_(false) { }


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

			trg_ = false;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service() noexcept
		{
			auto& rdr = at_scenes_base().at_render();
			rdr.clear(DEF_COLOR::Black);

			auto& nmea = at_scenes_base().at_nmea();

			auto n = nmea.get_satellite_num();
			auto iid = nmea.get_iid();
			char tmp[32];
			utils::sformat("Satellite: %u (%u)", tmp, sizeof(tmp)) % n % iid;
			rdr.draw_text(vtx::spos(0, 16*1), tmp);

			auto brn = static_cast<int>(nmea.get_baudrate());
			utils::sformat("Baudrate: %d [bps]", tmp, sizeof(tmp)) % brn;
			rdr.draw_text(vtx::spos(0, 16*2), tmp);

			auto upd = static_cast<int>(nmea.get_update_rate());
			utils::sformat("Update rate: %d [Hz]", tmp, sizeof(tmp)) % upd;
			rdr.draw_text(vtx::spos(0, 16*3), tmp);
			{
				const auto& t = nmea.get_satellite_info(0);
				utils::sformat("Satellite NO: %s", tmp, sizeof(tmp)) % t.no_;
				rdr.draw_text(vtx::spos(0, 16*5), tmp);
				utils::sformat("Elevation: %s", tmp, sizeof(tmp)) % t.elv_;
				rdr.draw_text(vtx::spos(0, 16*6), tmp);
				utils::sformat("Azimuth: %s", tmp, sizeof(tmp)) % t.azi_;
				rdr.draw_text(vtx::spos(0, 16*7), tmp);
				utils::sformat("Carria noise: %s [dB]", tmp, sizeof(tmp)) % t.cn_;
				rdr.draw_text(vtx::spos(0, 16*8), tmp);
			}
			const auto& touch = at_scenes_base().at_touch();
			bool t = touch.get_touch_num() == 1 ? true : false;
			if(trg_ && !t) {
				change_scene(scenes_id::root_menu);
			}
			trg_ = t;
		}
	};
}
