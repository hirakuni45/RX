#pragma once
//=====================================================================//
/*!	@file
	@brief	NES Emulator ハンドラー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/string_utils.hpp"
#include "emu/log.h"
#include "emu/nes/nes.h"
#include "emu/nes/nesinput.h"
#include "emu/nes/nesstate.h"
#include "emu/nes/nes_pal.h"
#include "emu/cpu/dis6502.hpp"

#include "chip/FAMIPAD.hpp"

extern "C" {
	uint8_t get_fami_pad();
}


namespace emu {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ＮＥＳエミュレーション・クラス
		@param[in]	AUDIO_SAMPLE_RATE	オーディオ・サンプル・レート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t AUDIO_SAMPLE_RATE>
	class nesemu {

		static const int nes_width_  = 256;
		static const int nes_height_ = 240;
        static const int sample_rate_ = AUDIO_SAMPLE_RATE;
		static const int sample_bits_ = 16;
		static const int audio_len_ = (sample_rate_ / 60) + 1;

		uint16_t		audio_buf_[audio_len_];

		bool			nesrom_;

		cpu::dis6502	disa_;

		uint16_t		mon_val_[3];

		nesinput_t		inp_[2];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		nesemu() noexcept : audio_buf_{ 0 }, nesrom_(false),
			disa_(nes6502_getbyte, nes6502_putbyte),
			mon_val_{ 0 }
		{ }


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
			if(nes_insert_cart(filename) == 0) {
				nesrom_ = true;
			}
			return nesrom_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  カートリッジが有効か？
			@return 有効なら「true」
		*/
		//-----------------------------------------------------------------//
		bool probe() const { return nesrom_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  一時停止の取得
			@return 一時停止
		*/
		//-----------------------------------------------------------------//
		bool get_pause() const noexcept {
			const nes_t* t = nes_getcontext();
			return t->pause;			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  一時停止
		*/
		//-----------------------------------------------------------------//
		void enable_pause(bool ena = true) noexcept {
			if(!nesrom_) return;

			nes_pause(ena);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  情報取得
			@return 情報テキスト
		*/
		//-----------------------------------------------------------------//
		const char* get_info() noexcept {
			nes_t* t = nes_getcontext();
	   		if(t == nullptr) return nullptr;
			if(t->rominfo == nullptr) return nullptr;
			return rom_getinfo(t->rominfo);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  エミュレーターを終了
		*/
		//-----------------------------------------------------------------//
		void close() noexcept
		{
			if(nesrom_) {
				nes_eject_cart();
				nesrom_ = false;
			}
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
			auto nes = nes_getcontext();
			bitmap_t* v = nes->vidbuf;
			const rgb_t* lut = get_palette();
			if(v == nullptr || lut == nullptr) {
				return;
			}

			{
				inp_[0].data = 0;  // Player 1
				inp_[1].data = 0;  // Player 2
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


		//-----------------------------------------------------------------//
		/*!
			@brief  ステートのセーブ
			@param[in]	no	スロット番号（０～９）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool save_state(int no) noexcept {
			if(!nesrom_) return false;
			state_setslot(no);
			return state_save() == 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ステートのロード
			@param[in]	no	スロット番号（０～９）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool load_state(int no) noexcept {
			if(!nesrom_) return false;
			state_setslot(no);
			return state_load() == 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ハード・リセット
		*/
		//-----------------------------------------------------------------//
		void reset() noexcept {
			nes_reset(HARD_RESET);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  モニター機能
			@param[in]	cmd		コマンド
		*/
		//-----------------------------------------------------------------//
		void monitor(const char* cmd) noexcept {
			char ch;
			uint16_t hexadec = 0;
			bool write = false;
			bool area = false;
			bool search = false;
			while(1) {
				ch = *cmd++;
				if(ch >= 'a' && ch <= 'z') ch -= 0x20;
				if(ch >= '0' && ch <= '9') {
					mon_val_[0] <<= 4;
					mon_val_[0] |= static_cast<uint16_t>(ch - '0');
					++hexadec;
				} else if(ch >= 'A' && ch <= 'F') {
					mon_val_[0] <<= 4;
					mon_val_[0] |= static_cast<uint16_t>(ch - 'A' + 10);
					++hexadec;
				} else if(ch == 'L') {  ///< disasm List
					if(hexadec > 0) {
						mon_val_[2] = mon_val_[0];
					}
					for(int i = 0; i < 20; ++i) {
						char tmp[64];
						disa_.disasm(mon_val_[2], tmp, sizeof(tmp));
						utils::str::to_caps(tmp, tmp, sizeof(tmp));
						utils::format("%s\n") % tmp;
						mon_val_[2] = disa_.get_pc();
					}
					hexadec = 0;
					write = false;
					area = false;
				} else if(ch == 'S') {  ///< Search
					mon_val_[2] = mon_val_[0];
					search = true;
					hexadec = 0;
				} else if(ch == '.') {
					mon_val_[1] = mon_val_[0];
					write = false;
					area = true;
					hexadec = 0;
				} else if(ch == ':') {
					mon_val_[1] = mon_val_[0];
					write = true;
					area = false;
					hexadec = 0;
				} else if(ch == ' ' || ch == 0) {
					if(write) {
						if(hexadec > 0) {
							nes6502_putbyte(mon_val_[1], mon_val_[0]);
							mon_val_[1]++;						
						}
					} else if(ch == 0) {
						uint32_t org = 0;
						uint32_t end = 0;
						if(search) {  // search
							org = mon_val_[1];
							end = mon_val_[2];
							while(org <= end) {
								auto rd = nes6502_getbyte(org);
								if(rd == (mon_val_[0] & 0xff)) {
									utils::format("%04X- %02X\n") % org % static_cast<uint16_t>(rd);
								} 
								++org;
							}
						} else {  // for dump
							if(area) {
								org = mon_val_[1];
								if(hexadec > 0) {
									end = mon_val_[0] + 1;
									if(org > end) end = org;
								} else {
									end = org + 16;
								}
								area = false; 
							} else {
								if(hexadec > 0) {
									org = mon_val_[1] = mon_val_[0];
									end = org + 1;
								} else {
									org = end = mon_val_[1];
								}
							}
							while(org < end) {
								char tmp[96];
								auto l = end - org;
								if(l == 0) l = 1;
								else if(l > 16) l = 16;
								org = disa_.dump(org, l, tmp, sizeof(tmp));
								utils::format("%s\n") % tmp;
							 }
							mon_val_[1] = org;
						}
					}
					mon_val_[0] = 0;
					hexadec = 0;
				} else {
					utils::format("%c?\n") % ch;
					hexadec = 0;
					write = false;
					area = false;
					search = false;
				}

				if(ch == 0) break;
			}
		}
	};
}
