#pragma once
//=====================================================================//
/*!	@file
	@brief	NES Emulator
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "emu/log.h"
#include "emu/nes/nes.h"
#include "emu/nes/nesinput.h"
#include "emu/nes/nesstate.h"
#include "emu/nes/nes_pal.h"

#include "emu/nsf/nsfplay.hpp"

namespace emu {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ＮＥＳエミュレーション・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class nesemu {

		static const int nes_width_  = 256;
		static const int nes_height_ = 240;
//        static const int sample_rate_ = 44100;
//        static const int audio_len_ = sample_rate_ / 60;

		emu::nsfplay	nsfplay_;

		bool			nesrom_;

		uint32_t		delay_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		nesemu() noexcept : nesrom_(false), delay_(120) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start()
		{
			log_init();
			nes_create(22050, 8);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  エミュレーター・ファイルを開く
			@param[in]	filename	ファイル名
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool open(const char* filename)
		{
			nesrom_ = false;
			if(nsfplay_.open(filename)) {
				nesrom_ = true;
			} else if(nes_insertcart(filename) == 0) {
				nesrom_ = true;
			}
			return nesrom_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	org		フレームバッファのアドレス
			@param[in]	xs		フレームバッファのＸ幅
			@param[in]	ys		フレームバッファのＹ幅
		*/
		//-----------------------------------------------------------------//
		void service(void* org, uint32_t xs, uint32_t ys)
		{
			if(delay_ > 0) {
				--delay_;
				if(delay_ == 0) {
					open("GRADIUS.nes");
//					open("Dragon_Quest2_fix.nes");
//					open("Solstice_J.nes");
// low memory		open("Zombie.nes");
				}
			}

			auto nes = nes_getcontext();
			bitmap_t* v = nes->vidbuf;
			const rgb_t* lut = get_palette();
			if(v == nullptr || lut == nullptr) {
				return;
			}
			uint16_t luttmp[64];
			for(uint32_t i = 0; i < 64; ++i) {
               	uint16_t r = lut[i].r;  // R
				uint16_t g = lut[i].g;  // G
				uint16_t b = lut[i].b;  // B
				// R(5), G(6), B(5)
				luttmp[i] = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3);
			}
			uint16_t* dst = static_cast<uint16_t*>(org);
			dst += ((ys - nes_height_) / 2) * xs;
			for(int h = 0; h < nes_height_; ++h) {
				const uint8_t* src = &v->data[h * v->pitch];
				uint16_t* tmp = dst;
				tmp += (xs - nes_width_) / 2;
				for(int w = 0; w < nes_width_; ++w) {
					auto idx = *src++;
					idx &= 63;
					*tmp++ = luttmp[idx];
				}
				dst += xs;
			}
			if(nesrom_) {
				nes_emulate(1);
			}
		}
	};
}

