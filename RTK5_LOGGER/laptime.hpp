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

		int16_t draw_time_(int16_t x, int16_t y, uint32_t t) noexcept
		{
			auto mod = t % 100;
			t /= 100;
			auto sec = t % 60;
			t /= 60;
			auto min = t % 60;
			t /= 60;
			auto hur = t % 24;
			char tmp[16];
			utils::sformat("%02d:%02d:%02d.%02d", tmp, sizeof(tmp))
				% hur % min % sec % mod;
			return at_scenes_base().at_render().draw_text(x, y, tmp);
		}


		int16_t draw_lap_(int16_t x, int16_t y, uint32_t no, uint32_t t) noexcept
		{
			char tmp[8];
			utils::sformat("%03d ", tmp, sizeof(tmp)) % no;
			x = at_scenes_base().at_render().draw_text(x, y, tmp);
			return draw_time_(x, y, t);
		}

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
			render.clear(RENDER::COLOR::Black);

			auto& watch = at_scenes_base().at_cmt().at_task();
			auto t = watch.get();
			auto pos = watch.get_lap_pos();
			uint32_t dt = t;
			if(pos > 0) {
				dt -= watch.get_lap(pos - 1);
			}

			int16_t y = 16;
			auto x = draw_lap_(0, y, pos, t);
			x = draw_time_(x + 8, y, dt);
			draw_lap_(x + 16, y, lap_best_n_, lap_best_t_);

			render.frame(0, RENDER::height - 10, RENDER::width, 10, RENDER::COLOR::White);
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
				uint32_t ref = RENDER::width - 2;
				uint32_t per = ref * dt / bt;
				auto c = RENDER::COLOR::Lime;
				if(per > ref) {
					per = ref;
					c = RENDER::COLOR::Red;
				}
				render.fill_box(1, RENDER::height - 10 + 1, per, 10 - 2, c);
			}

			for(uint32_t i = 0; i < 4; ++i) {
				if(i >= pos) {
					break;
				}
				auto t = watch.get_lap(pos - i - 1);
				if(pos > 1) {
					t -= watch.get_lap(pos - i - 2);
				}
				draw_lap_(0, 32 + 16 * 4 - i * 16, pos - i, t);
			}

			auto& res = at_scenes_base().at_resource();
			res.draw_nmb_24(0, 272 - 10 - 24 - 1, "0123456789:.");
		}
	};
}
