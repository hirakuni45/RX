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

		void draw_lap_(int16_t x, int16_t y, uint32_t no, uint32_t n) noexcept
		{
			auto mod = n % 100;
			n /= 100;
			auto sec = n % 60;
			n /= 60;
			auto min = n % 60;
			n /= 60;
			auto hur = n % 24;
			char tmp[24];
			utils::sformat("%03d %02d:%02d:%02d.%02d", tmp, sizeof(tmp))
				% no % hur % min % sec % mod;
			at_scenes_base().at_render().draw_text(x, y, tmp);
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		laptime() { }


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init()
		{
			at_scenes_base().at_cmt().at_task().enable();
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service()
		{
			at_scenes_base().at_render().clear(0);

			auto& watch = at_scenes_base().at_cmt().at_task();
			auto n = watch.get();
			auto pos = watch.get_lap_pos();
			draw_lap_(0, 16, pos, n);

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
		}
	};
}
