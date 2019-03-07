#pragma once
//=====================================================================//
/*!	@file
	@brief	アスキーフォント定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ASCII 無効フォント定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class afont_null {
	public:
		static const int8_t width  = 0;
		static const int8_t height = 0;
		static const uint8_t* get(uint8_t code) { return nullptr; }
		static const int8_t get_width(uint8_t code) { return 0; }
	};

}
