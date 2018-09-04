#pragma once
//=====================================================================//
/*!	@file
    @brief  LOGGER リソース
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/format.hpp"

namespace app {

	extern const uint8_t* nmb24[];

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	リソース・クラス
		@param[in]	RENDER	描画クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER>
	class resource {

		RENDER&	render_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	render	RENDER クラス（参照）
		*/
		//-------------------------------------------------------------//
		resource(RENDER& render) : render_(render) { }


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）を使ったキャラクター表示
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	ch	キャラクター・コード
		*/
		//-----------------------------------------------------------------//
		void draw_nmb_24(int16_t x, int16_t y, char ch)
		{
			if(ch >= '0' && ch <= '9') {
				render_.draw_mobj(x, y, nmb24[ch - '0']);
			} else if(ch == ':') {
				render_.draw_mobj(x, y, nmb24[10]);
			} else if(ch == '.') {
				render_.draw_mobj(x, y, nmb24[11]);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	１２ピクセル（高さ）を使ったキャラクター表示
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	str	文字列
			@return 描画後のＸ座標
		*/
		//-----------------------------------------------------------------//
		int16_t draw_nmb_24(int16_t x, int16_t y, const char* str)
		{
			if(str == nullptr) return x;

			char ch;
			while((ch = *str) != 0) {
				draw_nmb_24(x, y, ch);
				x += 18;
				++str;
			}
			return x;
		}
	};
}
