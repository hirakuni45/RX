#pragma once
//=====================================================================//
/*!	@file
	@brief	オーディオ・コーデック・マネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "sound/mp3_in.hpp"
#include "sound/wav_in.hpp"
#include "sound/sound_out.hpp"
#include "common/dir_list.hpp"

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	codec manager class
		@param[in]	SOUND_OUT	サウンド出力クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class SOUND_OUT>
	class codec_mgr {

		SOUND_OUT&	sound_out_;

		wav_in		wav_in_;
		mp3_in		mp3_in_;

		typedef utils::dir_list DLIST;
		DLIST		dlist_;

		char		get_ch_;

		struct loop_t {
			const char* start;
			bool    enable;
			loop_t() : start(nullptr), enable(false) { }
		};
		loop_t		loop_t_;


		af_play::CTRL ctrl_task_() noexcept
		{
			auto ctrl = sound::af_play::CTRL::NONE;

			if(get_ch_ != 0) {
				auto ch = get_ch_;
				if(ch == ' ') {
					ctrl = sound::af_play::CTRL::PAUSE;
				} else if(ch == 0x08) {  // BS
					ctrl = sound::af_play::CTRL::REPLAY;
				} else if(ch == 0x0D) {  // RETURN
					ctrl = sound::af_play::CTRL::STOP;
				} else if(ch == 0x1b) {  // ESC
					ctrl = sound::af_play::CTRL::STOP;
					dlist_.stop();
				}
				get_ch_ = 0;
			}
//			update_led_();
			return ctrl;
		}


		void tag_task_(utils::file_io& fin, const sound::tag_t& tag) noexcept
		{
			utils::format("Album:  '%s'\n") % tag.get_album().c_str();
			utils::format("Title:  '%s'\n") % tag.get_title().c_str();
			utils::format("Artist: '%s'\n") % tag.get_artist().c_str();
			utils::format("Year:    %s\n") % tag.get_year().c_str();
			utils::format("Disc:    %s\n") % tag.get_disc().c_str();
			utils::format("Track:   %s\n") % tag.get_track().c_str();
		}


		void update_task_(uint32_t t) noexcept
		{
			uint16_t sec = t % 60;
			uint16_t min = (t / 60) % 60;
			uint16_t hor = (t / 3600) % 24;
			utils::format("\r%02d:%02d:%02d") % hor % min % sec;
		}


		bool play_mp3_(const char* fname) noexcept
		{
			utils::file_io fin;
			if(!fin.open(fname, "rb")) {
				return false;
			}
			mp3_in_.set_ctrl_task(ctrl_task_);
			mp3_in_.set_tag_task(tag_task_);
			mp3_in_.set_update_task(update_task_);
			bool ret = mp3_in_.decode(fin, sound_out_);
			fin.close();
			return ret;
		}


		bool play_wav_(const char* fname) noexcept
		{
			utils::file_io fin;
			if(!fin.open(fname, "rb")) {
				return false;
			}
			wav_in_.set_ctrl_task(ctrl_task_);
			wav_in_.set_tag_task(tag_task_);
			wav_in_.set_update_task(update_task_);
			bool ret = wav_in_.decode(fin, sound_out_);
			fin.close();
			return ret;
		}


		void play_loop_(const char* root, const char* start) noexcept
		{
			loop_t_.start = start;
			if(strlen(start) != 0) {
				loop_t_.enable = true;
			} else {
				loop_t_.enable = false;
			}
			dlist_.start(root);
		}


		void play_loop_func_(const char* name, const FILINFO* fi, bool dir, void* option) noexcept
		{
			loop_t* t = static_cast<loop_t*>(option);
			if(t->enable) {
				if(strcmp(name, t->start) != 0) {
					return;
				} else {
					t->enable = false;
				}
			}
			if(dir) {
				play_loop_(name, "");
			} else {
				const char* ext = strrchr(name, '.');
				if(ext != nullptr) {
					bool ret = true;
					if(utils::str::strcmp_no_caps(ext, ".mp3") == 0) {
						ret = play_mp3_(name);
					} else if(utils::str::strcmp_no_caps(ext, ".wav") == 0) {
						ret = play_wav_(name);
					}
					if(!ret) {
						utils::format("Can't open audio file: '%s'\n") % name;
					}
				}
			}
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	sound_out	サウンドバッファの参照
		*/
		//-----------------------------------------------------------------//
		codec_mgr(SOUND_OUT& sound_out) noexcept : sound_out_(sound_out),
			wav_in_(), mp3_in_(),
			dlist_(), get_ch_(0), loop_t_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
			@param[in]	ctrl	制御キャラクタを注入
		*/
		//-----------------------------------------------------------------//
		void service(char ctrl) noexcept
		{
			if(ctrl) {
				get_ch_ = ctrl;
			}
			dlist_.service(1, play_loop_func_, true, &loop_t_);
		}



	};
}
