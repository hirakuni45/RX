#pragma once
//=====================================================================//
/*!	@file
	@brief	タイトル
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
		@brief	タイトル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class title {

		typedef scenes_base::RENDER RENDER;

		uint8_t		count_;
		bool		logo_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		title() : count_(0), logo_(false) { }


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init()
		{
			auto& render = at_scenes_base().at_render();

			count_ = 90;  // 1.5sec
			logo_ = false;

			render.clear(RENDER::COLOR::White);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service()
		{
			if(count_ > 0) {
				--count_;
				if(!logo_ && fatfs_get_mount() != 0) {
					auto& bmp = at_scenes_base().at_bmp();
					utils::file_io fin;
//					if(fin.open("wim02.bmp", "rb")) {
					if(fin.open("HRC_logo_s.bmp", "rb")) {
						img::img_info ifo;
						if(bmp.info(fin, ifo)) {
							int16_t xo = (RENDER::width  - ifo.width) / 2;
							int16_t yo = (RENDER::height - ifo.height) / 2;
							bmp.set_draw_offset(xo, yo);
							logo_ = bmp.load(fin);
							if(logo_) count_ = 90;
						}
						fin.close();
					}
				}
			} else {
				change_scene(scenes_id::root_menu);
			}
		}
	};
}
