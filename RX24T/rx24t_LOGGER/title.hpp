#pragma once
//=====================================================================//
/*!	@file
	@brief	タイトル・クラス
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	タイトル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class title {

		uint8_t	title_loop_ = 0;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init()
		{
			auto& core = at_core();

			core.fbc_enable_ = false;  // フレームバッファのクリアを禁止

///			if(title_mode_ == 0) {	// タイトルを表示しない
///				title_loop_ = 0;
///			} else if(title_mode_ == 1) {	// system title
				title_loop_ = 100;	// 約３秒
				core.resource_.draw_title();
///			} else if(title_mode_ == 2) {	// user title
///				title_loop_ = 100 + 15;	// 約３秒＋マウント待ち
///			}
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service()
		{
			auto& core = at_core();
#if 0
			if((g_switch_negative != 0) || (g_title_loop == 0)) {
				if(g_startup_mode == 0) {
					install_task(speed_init);
				} else if(g_startup_mode == 1) {
					install_task(tacho_init);
				} else if(g_startup_mode == 2) {
					install_task(menu_init);
				} else {
					install_task(laptimer_init);
				}
				set_fb_clear(1);
			} else {
				--g_title_loop;
				if(g_title_mode == 2) {
					if(g_title_loop == 100) {
						if(fileio_get_status() & FILEIO_DISK_MOUNT) {
							char name[16];
							strcpy_P(name, PSTR("title.bin"));
							FIL fd;
							if(f_open(&fd, name, FA_OPEN_EXISTING | FA_READ) == 0) {
								char img[64];
								int i;
								for(i = 0; i < 16; ++i) {
									UINT bw;
									if(f_read(&fd, img, 64, &bw) == 0) {
										monograph_draw_image(0, i * 4, (unsigned char *)img, 128, 4);
									}
								}
								f_close(&fd);
							} else {
								g_title_loop = 0;
							}
						} else {
							g_title_loop = 0;	// マウント出来ない場合
						}
					}
				}
			}
#endif
			if(title_loop_ > 0) {
				--title_loop_;
				if(title_loop_ == 0) {
					select_scene(scene_id::root_menu);
					core.fbc_enable_ = true;  // フレームバッファのクリアを許可
				}
			}
		}
	};
}
