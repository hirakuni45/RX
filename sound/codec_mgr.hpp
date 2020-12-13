#pragma once
//=====================================================================//
/*!	@file
	@brief	オーディオ・コーデック・マネージャー @n
			複数のオーディオ・コーデックを扱う。@n
			・wav（wav_in.hpp）@n
			・mp3（mp3_in.hpp）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "sound/wav_in.hpp"
#include "sound/mp3_in.hpp"
#include "sound/sound_out.hpp"
#include "common/dir_list.hpp"
#include "common/format.hpp"

extern "C" {
	char sci_getch();
	uint16_t sci_get_length();
};

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	コンソール版、LIST_CTRL クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class def_list_ctrl {
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		def_list_ctrl() noexcept { }


		void start(const char* fn) noexcept
		{
			utils::format("\nAudio file: '%s'\n") % fn;
		}


		void close() noexcept
		{
		}


		af_play::CTRL ctrl() noexcept
		{
			auto ctrl = sound::af_play::CTRL::NONE;

			if(sci_length() > 0) {
				auto ch = sci_getch();
				if(ch == ' ') {
					ctrl = sound::af_play::CTRL::PAUSE;
				} else if(ch == 0x08) {  // BS
					ctrl = sound::af_play::CTRL::REPLAY;
				} else if(ch == 0x0D) {  // RETURN
					ctrl = sound::af_play::CTRL::NEXT;
				} else if(ch == 0x1b) {  // ESC
					ctrl = sound::af_play::CTRL::STOP;
				}
			}
			return ctrl;
		}


		void tag(utils::file_io& fin, const sound::tag_t& t) noexcept
		{
			utils::format("Album:  '%s'\n") % t.get_album().c_str();
			utils::format("Title:  '%s'\n") % t.get_title().c_str();
			utils::format("Artist: '%s'\n") % t.get_artist().c_str();
			utils::format("Year:    %s\n")  % t.get_year().c_str();
			utils::format("Disc:    %s\n")  % t.get_disc().c_str();
			utils::format("Track:   %s\n")  % t.get_track().c_str();
		}


		void update(uint32_t t) noexcept
		{
			uint16_t sec = t % 60;
			uint16_t min = (t / 60) % 60;
			uint16_t hor = (t / 3600) % 24;
			utils::format("\r%02d:%02d:%02d") % hor % min % sec;
			utils::format::chaout().flush();
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	codec manager class
		@param[in]	LIST_CTRL	TAG 情報表示と制御クラス
		@param[in]	SOUND_OUT	サウンド出力クラス(sound_out クラス)
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class LIST_CTRL, class SOUND_OUT>
	class codec_mgr {

		LIST_CTRL&	list_ctrl_;
		SOUND_OUT&	sound_out_;

		audio_info	info_;

		wav_in		wav_in_;
		mp3_in		mp3_in_;

		enum class CODEC : uint8_t {
			NONE,
			WAV,
			MP3,
		};

		typedef utils::dir_list DLIST;
		DLIST		dlist_;

		struct loop_t {
			const char* start;
			bool    enable;
			loop_t() : start(nullptr), enable(false) { }
		};
		loop_t		loop_t_;

		bool		stop_;

		CODEC		codec_;

		bool play_mp3_(const char* fname) noexcept
		{
			utils::file_io fin;
			if(!fin.open(fname, "rb")) {
				return false;
			}
			codec_ = CODEC::MP3;
			mp3_in_.set_ctrl_task([=]() {
					auto c = list_ctrl_.ctrl();
					if(c == sound::af_play::CTRL::STOP) {
						dlist_.stop();
						stop_ = true;
					}
					return c;
				} );
			mp3_in_.set_tag_task([=](utils::file_io& fin, const sound::tag_t& tag) {
				list_ctrl_.tag(fin, tag); }
			);

			// 情報取得
			bool ret = false;
			if(mp3_in_.info(fin, info_)) {
				mp3_in_.set_update_task([=](uint32_t t) { list_ctrl_.update(t); });
				list_ctrl_.start(fname);
				stop_ = false;
				ret = mp3_in_.decode(fin, sound_out_);
			}
			list_ctrl_.close();
			fin.close();
			return ret;
		}


		bool play_wav_(const char* fname) noexcept
		{
			utils::file_io fin;
			if(!fin.open(fname, "rb")) {
				return false;
			}
			codec_ = CODEC::WAV;
			wav_in_.set_ctrl_task([=]() {
					auto c = list_ctrl_.ctrl();
					if(c == sound::af_play::CTRL::STOP) {
						dlist_.stop();
						stop_ = true;
					}
					return c;
				} );
			wav_in_.set_tag_task([=](utils::file_io& fin, const sound::tag_t& tag) {
				list_ctrl_.tag(fin, tag); }
			);
			// 情報取得
			bool ret = false;
			if(wav_in_.info(fin, info_)) {
				wav_in_.set_update_task([=](uint32_t t) { list_ctrl_.update(t); });
				list_ctrl_.start(fname);
				stop_ = false;
				ret = wav_in_.decode(fin, sound_out_);
			}
			list_ctrl_.close();
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
					bool ret = true;  // 拡張子が無い場合スルー
					if(utils::str::strcmp_no_caps(ext, ".mp3") == 0) {
						ret = play_mp3_(name);
					} else if(utils::str::strcmp_no_caps(ext, ".wav") == 0) {
						ret = play_wav_(name);
					}
					if(!ret && !stop_) {
						utils::format("Can't open audio file: '%s'\n") % name;
					}
				}
			}
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	LIST_CTRL	TAG 情報表示と制御クラスの参照
			@param[in]	sound_out	サウンドバッファクラスの参照
		*/
		//-----------------------------------------------------------------//
		codec_mgr(LIST_CTRL& list_ctrl, SOUND_OUT& sound_out) noexcept :
			list_ctrl_(list_ctrl), sound_out_(sound_out),
			info_(), wav_in_(), mp3_in_(),
			dlist_(), loop_t_(), stop_(false), codec_(CODEC::NONE)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	コーデックファイル再生
			@param[in]	name	ファイル名
		*/
		//-----------------------------------------------------------------//
		void play(const char* name) noexcept
		{
			play_loop_("", name);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			dlist_.service(1, [=](const char* name, const FILINFO* fi, bool dir, void* option) {
				play_loop_func_(name, fi, dir, option); }, true, &loop_t_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ステートを取得
			@return ステート
		*/
		//-----------------------------------------------------------------//
		auto get_state() const noexcept
		{
			switch(codec_) {
			case CODEC::MP3:
				return mp3_in_.get_state();
			case CODEC::WAV:
				return wav_in_.get_state();
			default:
				return af_play::STATE::IDLE;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	オーディオ情報を取得
			@return オーディオ情報
		*/
		//-----------------------------------------------------------------//
		auto get_audio_info() const noexcept
		{
			return info_;
		}
	};
}
