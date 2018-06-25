#pragma once
//=====================================================================//
/*!	@file
	@brief	８×１６フォント・クラス（東雲１６）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	フォント・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class font8x16 {
		static const uint8_t bitmap_[];
		static const int8_t width_tbl_[];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	文字の横幅
		*/
		//-----------------------------------------------------------------//
		static const int8_t width = 8;


		//-----------------------------------------------------------------//
		/*!
			@brief	文字の高さ
		*/
		//-----------------------------------------------------------------//
		static const int8_t height = 16;


		//-----------------------------------------------------------------//
		/*!
			@brief	文字のビットマップを取得
			@param[in]	code	文字コード
			@return 文字のビットマップ
		*/
		//-----------------------------------------------------------------//
		static const uint8_t* get(uint8_t code) noexcept {
			return &bitmap_[static_cast<uint16_t>(code) << 4];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	プロポーショナル・フォント幅を取得
			@param[in]	code	文字コード
			@return 文字幅
		*/
		//-----------------------------------------------------------------//
		static int8_t get_width(uint8_t code) noexcept {
			if(code < 32 || code >= 128) return width;
			else return width_tbl_[code - 32];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カーニングを取得
			@param[in]	code	文字コード
			@return 文字幅
		*/
		//-----------------------------------------------------------------//
		static int8_t get_kern(uint8_t code) {
			switch(code) {
			case '!':
			case '|':
			case 'i':
			case 'l':
				return -1;
			}
			return 0;
		}
	};
}
