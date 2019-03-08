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

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ラップタイム・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class laptime {

		uint32_t	lap_best_t_;
		uint32_t	lap_best_n_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		laptime() : lap_best_t_(0), lap_best_n_(0) { }


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init()
		{
			at_scenes_base().at_cmt().at_task().enable();
			lap_best_t_ = 0;
			lap_best_n_ = 0;

			typedef scenes_base::RENDER RENDER;

			auto& render = at_scenes_base().at_render();
			render.clear(RENDER::COLOR::Black);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service()
		{
			typedef scenes_base::RENDER RENDER;
			auto& render = at_scenes_base().at_render();
			auto& res = at_scenes_base().at_resource();
			auto& watch = at_scenes_base().at_cmt().at_task();

			auto t = watch.get();
			auto pos = watch.get_lap_pos();
			uint32_t dt = t;
			if(pos > 0) {
				dt -= watch.get_lap(pos - 1);
			}

			int16_t x = 0;
			int16_t y = 0;
			res.draw_lap_state(x, y, pos, t, dt);
//			res.draw_lap_24(x + 16, y, lap_best_n_, lap_best_t_);


			// プログレスバー表示
			render.frame(0, RENDER::glc_type::height - 10, RENDER::glc_type::width, 10, RENDER::COLOR::White);
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
				auto fc = RENDER::COLOR::Lime;
				if(per > ref) {
					per = ref;
					fc = RENDER::COLOR::Red;
				}
				auto bc = RENDER::COLOR::Black;
				render.fill_box(1, RENDER::glc_type::height - 10 + 1, ref - per, 10 - 2, bc);
				render.fill_box(1, RENDER::glc_type::height - 10 + 1, per, 10 - 2, fc);
			}

			for(uint32_t i = 0; i < 4; ++i) {
				if(i >= pos) {
					break;
				}
				auto t = watch.get_lap(pos - i - 1);
				if(pos > 1) {
					t -= watch.get_lap(pos - i - 2);
				}
				res.draw_short_lap(0, 48 + 28 * 4 - i * 28, pos - i, t);
			}
		}
	};
}
