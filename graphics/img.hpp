#pragma once
//=====================================================================//
/*!	@file
	@brief	イメージ関係定義、宣言
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace img {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ASCII 無効フォント定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct img_info {
		uint16_t	width;
		uint16_t	height;

		bool		grayscale;
		uint8_t		i_depth;
		uint8_t		r_depth;
		uint8_t		g_depth;
		uint8_t		b_depth;
		uint8_t		a_depth;

		uint16_t	clut_num;
		img_info() : width(0), height(0),
			grayscale(false), i_depth(0), r_depth(0), g_depth(0), b_depth(0), a_depth(0),
			clut_num(0) { }
	};
}
