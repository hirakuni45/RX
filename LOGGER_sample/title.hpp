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
#include "common/scene.hpp"
#include "common/format.hpp"
#include "scenes_base.hpp"

bool get_mount();

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	タイトル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class title : public utils::scene {

		typedef scenes_base::RENDER RENDER;
		typedef graphics::def_color DEF_COLOR;

		uint8_t		wait_;
		uint8_t		count_;
		bool		logo_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		title() : wait_(0), count_(0), logo_(false) { }


		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init() override
		{
			auto& render = at_scenes_base().at_render();

			wait_  = 60;
			count_ = 90;  // 1.5sec
			logo_ = false;

			render.clear(DEF_COLOR::White);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service() override
		{
			if(wait_ > 0) {
				--wait_;
				if(wait_ == 0 && get_mount() == 0) {
					at_scenes_base().at_dialog().modal(vtx::spos(400, 60),
						"Not mount SD card.");
					logo_ = true;
				}
				return;
			}
			if(count_ > 0) {
				--count_;
				if(logo_) {
					return;
				}
				if(get_mount() != 0) {
					auto& im = at_scenes_base().at_img();
					static const char* fname = { "HRC_logo_s.bmp" };
					img::img_info ifo;
					if(im.info(fname, ifo)) {
						int16_t xo = (RENDER::glc_type::width  - ifo.width) / 2;
						int16_t yo = (RENDER::glc_type::height - ifo.height) / 2;
						at_scenes_base().at_plot().set_offset(vtx::spos(xo, yo));
						logo_ = im.load(fname);
						if(logo_) count_ = 180;
					} else {
						auto& render = at_scenes_base().at_render();
						char tmp[64];
						utils::sformat("Can't open '%s'", tmp, sizeof(tmp)) % fname;
						at_scenes_base().at_dialog().modal(vtx::spos(400, 60), tmp);
						logo_ = true;
					}
				}
			} else {
				change_scene(scene_id::root_menu);
			}
		}


		//-------------------------------------------------------------//
		/*!
			@brief	シーンの終了
		*/
		//-------------------------------------------------------------//
		void exit() override { }
	};
}
