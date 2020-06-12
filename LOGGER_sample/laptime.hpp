#pragma once
//=====================================================================//
/*!	@file
	@brief	ラップタイム
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/format.hpp"
#include "scenes_base.hpp"
#include "common/fixed_fifo.hpp"
#include "common/file_io.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ラップタイム・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class laptime : public utils::scene {

		static const uint16_t LAP_LIST_NUM = 6;
		static const uint16_t LAP_LIST_X = 24;
		static const uint16_t LAP_LIST_Y = 48;
		static const uint16_t LAP_FONT_HEIGHT = 28;

		gui::button		button_;
		gui::slider		slider_;

		uint32_t	lap_best_t_;
		uint32_t	lap_best_n_;

		typedef scenes_base::RENDER RENDER;
		typedef RENDER::glc_type GLC;
		typedef graphics::def_color DEF_COLOR;

		void make_file_name_(time_t t, char* out, uint32_t len)
		{
			struct tm *m = localtime(&t);
			utils::sformat("%04d%s%02d%02d%02d", out, len)
				% static_cast<uint32_t>(m->tm_year + 1900)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_mday)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
			;
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		laptime() :
			button_(vtx::srect(480-100-2, 272-30-10-2, 100, 30), "Exit"),
			slider_(vtx::srect(0, LAP_LIST_Y + LAP_FONT_HEIGHT, 0, LAP_LIST_NUM * LAP_FONT_HEIGHT), 0.0f),
			lap_best_t_(0), lap_best_n_(0)
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init() override
		{
			button_.enable();
			button_.at_select_func() = [this](uint32_t id) {
				change_scene(scene_id::root_menu);
			};
			slider_.enable();

			at_scenes_base().at_cmt().at_task().enable();
			lap_best_t_ = 0;
			lap_best_n_ = 0;

			auto& watch = at_scenes_base().at_cmt().at_task();
			watch.reset();

			auto& render = at_scenes_base().at_render();
			render.clear(DEF_COLOR::Black);
			render.set_fore_color(DEF_COLOR::White);
			render.set_back_color(DEF_COLOR::Black);

		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service() override
		{
			auto& render = at_scenes_base().at_render();
			render.set_fore_color(DEF_COLOR::White);
			render.line_v(480-1, 0, 272);

			auto& res = at_scenes_base().at_resource();
			auto& watch = at_scenes_base().at_cmt().at_task();

			auto t = watch.get();
			auto pos = watch.get_lap_pos();
			uint32_t dt = t;
			if(pos > 0) {
				dt -= watch.get_lap(pos - 1);
			}

			vtx::spos loc(0);
			res.draw_lap_state(loc, pos, t, dt);
//			res.draw_lap_24(x + 16, y, lap_best_n_, lap_best_t_);

			// プログレスバー表示
			render.set_fore_color(DEF_COLOR::White);
			render.frame(vtx::srect(0, GLC::height - 10, GLC::width, 10));
			uint32_t bt = 0;
			if(pos > 0) {
				bt = watch.get_lap(pos - 1);
				if(pos > 1) {
					bt -= watch.get_lap(pos - 2);
				}
				if(lap_best_t_ == 0 || lap_best_t_ > bt) {
					lap_best_t_ = bt;
					lap_best_n_ = pos;
				}
			}
			if(bt > 0) {
				uint32_t ref = RENDER::glc_type::width - 2;
				uint32_t per = ref * dt / bt;
				auto fc = DEF_COLOR::Lime;
				if(per > ref) {
					per = ref;
					fc = DEF_COLOR::Red;
				}
				auto bc = DEF_COLOR::Black;
				render.set_fore_color(bc);
				render.set_back_color(fc);
				render.fill_box(vtx::srect(1, RENDER::glc_type::height - 10 + 1, ref - per, 10 - 2));
				render.swap_color();
				render.fill_box(vtx::srect(1, RENDER::glc_type::height - 10 + 1, per, 10 - 2));
			}

			auto lapmax = watch.get_lap_pos();
			uint32_t ofs = 0;
			if(lapmax >= LAP_LIST_NUM) {
				ofs = (lapmax - LAP_LIST_NUM) * slider_.get_ratio();
			}
			for(uint32_t i = 0; i < LAP_LIST_NUM; ++i) {
				if(i >= pos) {
					break;
				}
				auto p = pos - i - 1 - ofs;
				auto t = watch.get_lap(p);
				if(pos > 1) {
					t -= watch.get_lap(p - 1);
				}
				if(lap_best_n_ == p) {
					render.set_fore_color(DEF_COLOR::Green);
				} else {
					render.set_fore_color(DEF_COLOR::White);
				}
				render.set_back_color(DEF_COLOR::Black);
				res.draw_short_lap(vtx::spos(LAP_LIST_X, LAP_LIST_Y + LAP_FONT_HEIGHT * LAP_LIST_NUM - i * LAP_FONT_HEIGHT), pos - i - ofs, t);
			}

			// GPS 書き込みサービス
//			auto& nmea = at_scenes_base().at_nmea();
//			auto n = nmea.get_satellite_num();

			render.set_fore_color(DEF_COLOR::Black);
			render.line_v(480-1, 0, 272);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	シーンの終了
		*/
		//-------------------------------------------------------------//
		void exit() override {
			button_.enable(false);
			slider_.enable(false);
		}
	};
}
