#pragma once
//=====================================================================//
/*!	@file
	@brief	グラフィックス・ピクセル定義
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
		@brief	ピクセル定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct pixel {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ピクセル・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TYPE {
			CLUT1  = 1,		///<  1 bits / pixel
			CLUT4  = 4,		///<  4 bits / pixel
			CLUT8  = 8,		///<  8 bits / pixel
			RGB565 = 16,	///< 16 bits / pixel
			RGB888 = 32,	///< 32 bits / pixel
		};

	};
}
