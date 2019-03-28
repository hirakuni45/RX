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
		typedef graphics::def_color DEF_COLOR;

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

			render.clear(DEF_COLOR::White);
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
					auto& im = at_scenes_base().at_img();
					static const char* fname = { "HRC_logo_s.bmp" };
					img::img_info ifo;
					if(im.info(fname, ifo)) {
						int16_t xo = (RENDER::glc_type::width  - ifo.width) / 2;
						int16_t yo = (RENDER::glc_type::height - ifo.height) / 2;
						at_scenes_base().at_plot().set_offset(vtx::spos(xo, yo));
						logo_ = im.load(fname);
						if(logo_) count_ = 90;
					}
				}
			} else {
				change_scene(scenes_id::root_menu);
			}
		}
	};
}
