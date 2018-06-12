#pragma once
//=====================================================================//
/*!	@file
	@brief	Space Invaders Emulator (side)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "side/arcade.h"

namespace emu {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  スペース・インベーダー・エミュレーション・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class spinv {

		InvadersMachine im_;

		uint16_t	backc_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		spinv() : im_(), backc_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	root	ルート・パス
			@return 成功なら「tue」
		*/
		//-----------------------------------------------------------------//
		bool start(const char* root)
		{
			static const char* rom_files[] = {
				"invaders.h", "invaders.g", "invaders.f", "invaders.e"
			};
			char rom[0x2000];
			for(uint32_t i = 0; i < 4; ++i) {
				char tmp[256];
				if(root != nullptr) {
					strcpy(tmp, root);
				} else {
					strcpy(tmp, "/");
				}
				strcat(tmp, "/");
				strcat(tmp, rom_files[i]);

				FILE* fp = fopen(tmp, "rb");
				if(fp == nullptr) {
					utils::format("Can't open: '%s'\n") % tmp;
					return false;
				}
				if(fread(&rom[i * 0x800], 1, 0x800, fp) != 0x800) {
					utils::format("Can't read data: '%s'\n") % tmp;
					fclose(fp);
					return false;
				}
				utils::format("Read ROM: '%s'\n") % tmp;
				fclose(fp);
			}

            uint32_t sum = 0;
            for(uint32_t i = 0; i < 0x2000; ++i) {
            	sum += (uint8_t)rom[i];
            }
            utils::format("SUM: %08X\n") % sum;

			im_.setROM(rom);

			im_.reset();

			auto fr = im_.getFrameRate();
			utils::format("FrameRate: %d\n") % fr;

			return true;
		}


		void service()
		{
			const uint8_t* video = im_.getVideo();
			if(video != nullptr) {
				uint16_t* fb = (uint16_t*)0x00800000;
				for(uint32_t y = 0; y < InvadersMachine::ScreenHeight; ++y) {
///					uint32_t c = scan_line_color_[y];
					for(uint32_t x = 0; x < InvadersMachine::ScreenWidth; ++x) {
						if( *video ) {
							fb[y * 480 + x] = 0xffff;
						} else {
							fb[y * 480 + x] = backc_;
						}
						++video;
					}
				}
			}

			im_.step();
		}
	};
}
