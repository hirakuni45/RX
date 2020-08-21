#pragma once
//=====================================================================//
/*!	@file
	@brief	オーディオ情報クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/format.hpp"

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	オーディオのタイプ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class audio_format {
		NONE,			///< 不明なタイプ
		PCM8_MONO,		///< PCM  8 ビット、モノラル
		PCM8_STEREO,	///< PCM  8 ビット、ステレオ
		PCM16_MONO,		///< PCM 16 ビット、モノラル
		PCM16_STEREO,	///< PCM 16 ビット、ステレオ
		PCM24_MONO,		///< PCM 24 ビット、モノラル
		PCM24_STEREO,	///< PCM 24 ビット、ステレオ
		PCM32_MONO,		///< PCM 32 ビット、モノラル
		PCM32_STEREO,	///< PCM 32 ビット、モノラル
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	オーディオ情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct audio_info {

		audio_format	type;			///< オーディオ・タイプ
		uint32_t		samples;		///< サンプル数
		uint32_t		chanels;		///< チャネル数
		uint32_t		bits;			///< ビット数
		uint32_t		frequency;		///< サンプリング周波数
		uint32_t		block_align;	///< ブロック辺りのバイト数
		uint32_t		header_size;	///< インフォメーション・ヘッダーのサイズ


        //-----------------------------------------------------------------//
        /*!
            @brief  コンストラクター
        */
        //-----------------------------------------------------------------//
        audio_info() noexcept :
			type(audio_format::NONE), samples(0), chanels(0), bits(0), frequency(0),
            block_align(0), header_size(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サンプル位置を時間に変換
			@param[in]  spos    サンプル位置
			@param[in]  t       秒単位の時間
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool sample_to_time(uint32_t spos, time_t& t) noexcept
		{
			if(frequency <= 0) return false;
			t = spos / frequency;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サンプル情報を出力
		*/
		//-----------------------------------------------------------------//
		void list() const noexcept
		{
			utils::format("Audio infomations:\n");
            utils::format("    Samples:     %u\n") % static_cast<int>(samples);
            utils::format("    Chanels:     %u\n") % chanels;
            utils::format("    Bits/Chanel: %u\n") % bits;
            utils::format("    Sample Rate: %u [Hz]\n") % frequency;
        }
	};
}
