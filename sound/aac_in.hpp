#pragma once
//=====================================================================//
/*!	@file
	@brief	AAC 音声ファイルを扱うクラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <neaacdec.h>
#include "common/file_io.hpp"
#include "common/format.hpp"
#include "sound/tag.hpp"
#include "sound/af_play.hpp"
#include "sound/sound_out.hpp"
#include "sound/audio_info.hpp"

extern "C" {
	void set_sample_rate(uint32_t freq);
};

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	AAC 形式ファイルクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class aac_in : public af_play {

		struct decode_mp4_t {
			NeAACDecHandle	h_decoder;
//			mp4ff_callback_t mp4cb;
//			mp4ff_t*		infile;
			NeAACDecConfigurationPtr config;
			NeAACDecFrameInfo frame_info;
			mp4AudioSpecificConfig	mp4ASC;
			int			track;
			unsigned char*	tmp;
			uint32_t	samples;
			uint32_t	useAacLength;
			uint32_t	timescale;
			uint32_t	channels;
			uint32_t	samplerate;
			uint32_t	framesize;
			uint32_t	count;
			uint32_t	delay;
			void* 		sample;
			bool		no_gapless;
			bool		initial;
			decode_mp4_t() : h_decoder(0),
//				infile(0),
				config(0), frame_info(), track(-1), tmp(0), samples(0),
				useAacLength(0), timescale(0), channels(0), samplerate(0), framesize(0),
				count(0), delay(0), sample(0),
				no_gapless(false), initial(false) { }
		};

		decode_mp4_t	mp4_t_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		aac_in() noexcept : mp4_t_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイル拡張子を返す
			@return ファイル拡張子の文字列
		*/
		//-----------------------------------------------------------------//
		const char* get_file_ext() const { return "aac,m4a"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	AAC ファイルか確認する
			@param[in]	fin	file_io クラス
			@return エラーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool probe(utils::file_io& fin) noexcept 
		{
			auto org = fin.tell();
			bool ret = false;
			uint8_t h[8];
			auto len = fin.read(h, 8);
			fin.seek(utils::file_io::SEEK::SET, org);
			if(len != 8) {
				return ret;
			}

			if(h[4] == 'f' && h[5] == 't' && h[6] == 'y' && h[7] == 'p') {
#if 0
				decode_mp4_t dt;
				if(decode_track_mp4_(fin, dt)) {
					ret = true;
					destroy_mp4_(dt);
				}
#endif
			}
			return ret;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	ヘッダーをロードして、フォーマット、サイズを取得する
			@param[in]	path	ファイル・パス
			@param[in]	tag		タグの参照
		*/
		//-------------------------------------------------------------//
		bool load_header(utils::file_io& fi, tag_t& tag) noexcept
		{




			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	情報を取得
			@param[in]	fin		file_io コンテキスト（参照）
			@param[out]	info	情報
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool info(utils::file_io& fin, audio_info& info) noexcept
		{
			set_state(STATE::TAG);
			tag_t tag;
			if(!load_header(fin, tag)) {
				set_state(STATE::IDLE);
				return false;
			}
			if(tag_task_) {
				tag_task_(fin, tag);
			}

			info.type = audio_format::NONE;




			return true;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	デコード @n
					デコードの準備として、info で情報を取得する事。
			@param[in]	fi	ファイルＩ／Ｏ
			@return 正常終了なら「true」
		*/
		//-------------------------------------------------------------//
		template <class SOUND_OUT>
		bool decode(utils::file_io& fin, SOUND_OUT& out) noexcept
		{


			return true;
		}
	};
}
