#pragma once
//=====================================================================//
/*!	@file
	@brief	カラー管理クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  カラー構造
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct color {

		// http://www.rapidtables.com/web/color/RGB_Color.htm
		//　@brief  カラー属性
		enum class type : uint8_t {
			black,	///< 黒
			white,	///< 白
			red,	///< 赤
			lime,	///< ライム
			blue,	///< ブルー
			yellow,	///< イエロー
			cyan,	///< シアン
			aqua = cyan,	///< アクア（シアン）
			magenta,		///< マジェンタ
			fuchsia = magenta,
			silver,	///< シルバー
			gray,	///< グレー
			maroon,	///< マルーン
			olive,	///< オリーブ
			green,	///< グリーン
			purple,	///< パープル
			teal,
			navy,
		};

		uint8_t	r;
		uint8_t	g;
		uint8_t	b;

		color(uint8_t rr = 0, uint8_t gg = 0, uint8_t bb = 0) : r(rr), g(gg), b(bb) { }

		color(type t) { set(t); }

		void set(type t)
		{
			switch(t) {
			case type::black:   r = 0x00; g = 0x00; b = 0x00; break;
			case type::white:   r = 0xFF; g = 0xFF; b = 0xFF; break;
			case type::red:     r = 0xFF; g = 0x00; b = 0x00; break;
			case type::lime:    r = 0x00; g = 0xFF; b = 0x00; break;
			case type::blue:    r = 0x00; g = 0x00; b = 0xFF; break;
			case type::yellow:  r = 0xFF; g = 0xFF; b = 0x00; break;
			case type::cyan:    r = 0x00; g = 0xFF; b = 0xFF; break;
			case type::magenta: r = 0xFF; g = 0x00; b = 0xFF; break;
			case type::silver: 	r = 0xC0; g = 0xC0; b = 0xC0; break;
			case type::gray: 	r = 0x80; g = 0x80; b = 0x80; break;
			case type::maroon: 	r = 0x80; g = 0x00; b = 0x00; break;
			case type::olive: 	r = 0x80; g = 0x80; b = 0x00; break;
			case type::green: 	r = 0x00; g = 0x80; b = 0x00; break;
			case type::purple: 	r = 0x80; g = 0x00; b = 0x80; break;
			case type::teal: 	r = 0x00; g = 0x80; b = 0x80; break;
			case type::navy: 	r = 0x00; g = 0x00; b = 0x80; break;
			}
		}
	};
}
