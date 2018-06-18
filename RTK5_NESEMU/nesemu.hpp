#pragma once
//=====================================================================//
/*!	@file
	@brief	NES Emulator ハンドラー
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

#include "chip/FAMIPAD.hpp"

// #include "emu/nsf/nsfplay.hpp"

extern "C" {

	uint8_t get_fami_pad();
	uint16_t sci_length(void);
	char sci_getch(void);

}


namespace emu {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ＮＥＳエミュレーション・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class nesemu {

		static const int nes_width_  = 256;
		static const int nes_height_ = 240;
        static const int sample_rate_ = 22050;
		static const int sample_bits_ = 16;
		static const int audio_len_ = sample_rate_ / 60;

		uint16_t		audio_buf_[audio_len_ + 16];

//		emu::nsfplay	nsfplay_;

		bool			nesrom_;

		uint32_t		delay_;

		nesinput_t		inp_[2];

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
			@param[in]	オーディオをサポートしない場合「false」
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(bool audio_ena = true)
		{
			log_init();
			nes_create(sample_rate_, sample_bits_);

            inp_[0].type = INP_JOYPAD0;
            inp_[0].data = 0;
            input_register(&inp_[0]);
            inp_[1].type = INP_JOYPAD1;
            inp_[1].data = 0;
            input_register(&inp_[1]);

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
			if(nes_insertcart(filename) == 0) {
				nesrom_ = true;
			}
//			} else if(nsfplay_.open(filename)) {
//				nesrom_ = true;
//			}
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
//					open("GALAXIAN.NES");
					open("GRADIUS.nes");
//					open("DragonQuest_J_fix.nes");
//					open("Dragon_Quest2_fix.nes");
//					open("Solstice_J.nes");
//					open("Zombie.nes");
				}
			}

			auto nes = nes_getcontext();
			bitmap_t* v = nes->vidbuf;
			const rgb_t* lut = get_palette();
			if(v == nullptr || lut == nullptr) {
				return;
			}

			{
				inp_[0].data = 0;
				inp_[1].data = 0;
				uint8_t pad = get_fami_pad();
				if(chip::on(pad, chip::FAMIPAD_ST::A)) {
					inp_[0].data |= INP_PAD_A;
				}
				if(chip::on(pad, chip::FAMIPAD_ST::B)) {
					inp_[0].data |= INP_PAD_B;
				}
				if(chip::on(pad, chip::FAMIPAD_ST::SELECT)) {
					inp_[0].data |= INP_PAD_SELECT;
				}
				if(chip::on(pad, chip::FAMIPAD_ST::START)) {
					inp_[0].data |= INP_PAD_START;
				}
				if(chip::on(pad, chip::FAMIPAD_ST::UP)) {
					inp_[0].data |= INP_PAD_UP;
				}
				if(chip::on(pad, chip::FAMIPAD_ST::DOWN)) {
					inp_[0].data |= INP_PAD_DOWN;
				}
				if(chip::on(pad, chip::FAMIPAD_ST::LEFT)) {
					inp_[0].data |= INP_PAD_LEFT;
				}
				if(chip::on(pad, chip::FAMIPAD_ST::RIGHT)) {
					inp_[0].data |= INP_PAD_RIGHT;
				}
			}

			uint16_t luttmp[256];
			for(uint32_t i = 0; i < 64; ++i) {
               	uint16_t r = lut[i].r;  // R
				uint16_t g = lut[i].g;  // G
				uint16_t b = lut[i].b;  // B
				// R(5), G(6), B(5)
				luttmp[i] = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3);
				luttmp[i+128+64] = luttmp[i+128] = luttmp[i+64] = luttmp[i];
			}
			uint16_t* dst = static_cast<uint16_t*>(org);
			dst += ((ys - (nes_height_ - 16)) / 2) * xs;
			const uint8_t* src = v->data;
			src += v->pitch * 16;
			for(int h = 0; h < (nes_height_ - 16); ++h) {
				uint16_t* tmp = dst;
				tmp += (xs - nes_width_) / 2;
				for(int w = 0; w < nes_width_ / 16; ++w) {
					*tmp++ = luttmp[*src++]; *tmp++ = luttmp[*src++];
					*tmp++ = luttmp[*src++]; *tmp++ = luttmp[*src++];
					*tmp++ = luttmp[*src++]; *tmp++ = luttmp[*src++];
					*tmp++ = luttmp[*src++]; *tmp++ = luttmp[*src++];
					*tmp++ = luttmp[*src++]; *tmp++ = luttmp[*src++];
					*tmp++ = luttmp[*src++]; *tmp++ = luttmp[*src++];
					*tmp++ = luttmp[*src++]; *tmp++ = luttmp[*src++];
					*tmp++ = luttmp[*src++]; *tmp++ = luttmp[*src++];
				}
				src += v->pitch - nes_width_;
				dst += xs;
			}
			if(nesrom_) {
				apu_process(audio_buf_, audio_len_);
				nes_emulate(1);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オーディオ・バッファの長さを取得
			@return オーディオ・バッファの長さ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_audio_len() const noexcept { return audio_len_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  オーディオ・バッファを取得
			@return オーディオ・バッファのポインター
		*/
		//-----------------------------------------------------------------//
		const uint16_t* get_audio_buf() const noexcept { return audio_buf_; }
	};
}

