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
#include "common/file_io.hpp"
#include "common/snd_mgr.hpp"

extern "C" {
	uint8_t get_fami_pad();
};

namespace emu {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  スペース・インベーダー・エミュレーション・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class spinv {
	public:
		typedef audio::snd_mgr<9, 8, 184> SND_MGR;

	private:
		InvadersMachine im_;

		uint16_t	scan_lines_[InvadersMachine::ScreenHeight];

		SND_MGR		snd_mgr_;

		uint32_t	se_hnd_[9];

		bool load_sounds_(const char* root)
		{
			if(root == nullptr) {
				return false;
			}

			static const char* sdf[] = {
				"BaseHit.wav", "InvHit.Wav", "Shot.wav", "Ufo.wav",
				"UfoHit.wav", "Walk1.wav", "Walk2.wav", "Walk3.wav",
				"Walk4.wav"
			};

			uint32_t allsize = 0;
			for(uint32_t i = 0; i < 9; ++i) {
				char tmp[256];
				strcpy(tmp, root);
				strcat(tmp, "/");
				strcat(tmp, sdf[i]);

				se_hnd_[i] = snd_mgr_.set_sound(tmp);
				utils::format("Load SE: '%s' at %d\n") % sdf[i] % se_hnd_[i];
			}

			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		spinv() noexcept : im_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	rom_path	ROM ファイル・ルート・パス
			@param[in]	wav_path	WAV ファイル・ルート・パス
			@return 成功なら「tue」
		*/
		//-----------------------------------------------------------------//
		bool start(const char* rom_path, const char* wav_path = nullptr)
		{
			static const char* rom_files[] = {
				"invaders.h", "invaders.g", "invaders.f", "invaders.e"
			};

			{
				char rom[0x2000];
				for(uint32_t i = 0; i < 4; ++i) {
					char tmp[256];
					if(rom_path != nullptr) {
						strcpy(tmp, rom_path);
					} else {
						strcpy(tmp, "/");
					}
					strcat(tmp, "/");
					strcat(tmp, rom_files[i]);

					utils::file_io fi;
					if(!fi.open(tmp, "rb")) {
						utils::format("Can't open: '%s'\n") % tmp;
						return false;
					}
					if(fi.read(&rom[i * 0x800], 0x800) != 0x800) {
						utils::format("Can't read data: '%s'\n") % tmp;
						fi.close();
						return false;
					}
					utils::format("Read ROM: '%s'\n") % tmp;
					fi.close();
				}

				uint32_t sum = 0;
				for(uint32_t i = 0; i < 0x2000; ++i) {
					sum += (uint8_t)rom[i];
				}
				utils::format("ROM SUM: %08X\n") % sum;

				im_.setROM(rom);
			}

			if(!load_sounds_(wav_path)) {
				utils::format("Sound files not found. no sound\n");
			}

			im_.reset();

//			auto fr = im_.getFrameRate();
//			utils::format("FrameRate: %d\n") % fr;

			for(int i = 0; i < InvadersMachine::ScreenHeight; ++i) {
				uint16_t c = 0b11111'111111'11111;
				if( i >=  32 && i <  64 ) c = 0b11111'000000'00000; // Red
				if( i >= 184 && i < 240 ) c = 0b00000'111111'00000; // Green
				scan_lines_[i] = c;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	org		フレームバッファアドレス
			@param[in]	w		横幅
			@param[in]	h		高さ
		*/
		//-----------------------------------------------------------------//
		void service(void* org, int w, int h)
		{
			uint8_t pad = get_fami_pad();

			const uint8_t* video = im_.getVideo();
			if(video != nullptr) {
				uint16_t* fb = static_cast<uint16_t*>(org);
				uint32_t yo = (h - InvadersMachine::ScreenHeight) / 2;
				uint32_t xo = (w - InvadersMachine::ScreenWidth) / 2;
				for(uint32_t y = 0; y < InvadersMachine::ScreenHeight; ++y) {
					uint32_t c = scan_lines_[y];
					for(uint32_t x = 0; x < InvadersMachine::ScreenWidth; ++x) {
						if( *video ) {
							fb[(y + yo) * w + x + xo] = c;
						} else {
							fb[(y + yo) * w + x + xo] = 0x0000;
						}
						++video;
					}
				}
			}

			// 1P
			if(chip::on(pad, chip::FAMIPAD_ST::START)) {
				im_.fireEvent(InvadersMachine::KeyOnePlayerDown);
			} else {
				im_.fireEvent(InvadersMachine::KeyOnePlayerUp);
			}
			// 2P
//			if(dev.get_positive(gl::device::key::_2)) {
//				im_.fireEvent(InvadersMachine::KeyTwoPlayersDown);
//			}
//			if(dev.get_negative(gl::device::key::_2)) {
//				im_.fireEvent(InvadersMachine::KeyTwoPlayersUp);
//			}
			// coin
			if(chip::on(pad, chip::FAMIPAD_ST::SELECT)) {
				im_.fireEvent(InvadersMachine::CoinInserted);
			}

			// Left
			if(chip::on(pad, chip::FAMIPAD_ST::LEFT)) {
   			 	im_.fireEvent( InvadersMachine::KeyLeftDown);
			} else {
				im_.fireEvent( InvadersMachine::KeyLeftUp);
			}

			// Right
			if(chip::on(pad, chip::FAMIPAD_ST::RIGHT)) {
				im_.fireEvent( InvadersMachine::KeyRightDown);
			} else {
				im_.fireEvent( InvadersMachine::KeyRightUp);
			}

			// Fire
			if(chip::on(pad, chip::FAMIPAD_ST::A)) {
				im_.fireEvent( InvadersMachine::KeyFireDown);
			} else {
				im_.fireEvent( InvadersMachine::KeyFireUp);
			}

			im_.step();

			static const unsigned se_mask[9] = {
				InvadersMachine::SoundBaseHit,
				InvadersMachine::SoundInvaderHit,
				InvadersMachine::SoundShot,
				InvadersMachine::SoundUfo,
				InvadersMachine::SoundUfoHit,
				InvadersMachine::SoundWalk1,
				InvadersMachine::SoundWalk2,
				InvadersMachine::SoundWalk3,
				InvadersMachine::SoundWalk4
			};

			unsigned bits = im_.getSounds();
			for(int i = 0; i < 9; ++i) {
				if(!snd_mgr_.status(se_hnd_[i]) && (bits & se_mask[i]) != 0) {
					snd_mgr_.request(se_hnd_[i]);
				}
			}
			snd_mgr_.update();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サウンド・マネージャーの参照
			@return サウンド・マネージャー
		*/
		//-----------------------------------------------------------------//
		SND_MGR& at_sound() noexcept { return snd_mgr_; }		
	};
}
