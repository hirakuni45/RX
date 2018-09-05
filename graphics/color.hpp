#pragma once
//=====================================================================//
/*!	@file
	@brief	グラフィックス・カラー定義
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
		@brief	基本カラー定数
		@param[in]	T		ピクセル型（uint16_t、uint32_t）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	class base_color {

		static constexpr uint32_t rgb888_(uint8_t r, uint8_t g, uint8_t b)
		{
			return
				(static_cast<uint32_t>(r) << 16)
			  | (static_cast<uint32_t>(g) << 8)
			  | static_cast<uint32_t>(b);
		}


		static constexpr uint16_t rgb565_(uint8_t r, uint8_t g, uint8_t b)
		{
			return
				(static_cast<uint16_t>(r & 0xf8) << 8)
			  | (static_cast<uint16_t>(g & 0xfc) << 3)
			  | (static_cast<uint16_t>(b & 0xf8) >> 3);
		}


		static constexpr T rgb_(uint8_t r, uint8_t g, uint8_t b)
		{
			if(sizeof(T) == 1) {
				return (r & 0b11100000) | ((g & 0b11100000) >> 3) | ((b & 0b11000000) >> 6);
			} else if(sizeof(T) == 2) return rgb565_(r, g, b);
			else if(sizeof(T) == 4) return rgb888_(r, g, b);
			else return 0;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	RGB 値から、パックされた RGB 値に変換
			@param[in]	r	R 値
			@param[in]	g	G 値
			@param[in]	b	B 値
			@return パックされた RGB 値
		*/
		//-----------------------------------------------------------------//
		static T rgb(uint8_t r, uint8_t g, uint8_t b) { return rgb_(r, g, b); }


		// https://jonasjacek.github.io/colors/
		static constexpr T Black   = rgb_(  0,   0,   0);
		static constexpr T Maroon  = rgb_(128,   0,   0);
		static constexpr T Green   = rgb_(  0, 128,   0);
		static constexpr T Olive   = rgb_(128, 128,   0);
		static constexpr T Navy    = rgb_(  0,   0, 128);
		static constexpr T Purple  = rgb_(128,   0, 128);
		static constexpr T Teal    = rgb_(  0, 128, 128);
		static constexpr T Silver  = rgb_(192, 192, 192);
		static constexpr T Gray    = rgb_(128, 128, 128);  // 米国
		static constexpr T Grey    = rgb_(128, 128, 128);  // 英国
		static constexpr T Red     = rgb_(255,   0,   0);
		static constexpr T Lime    = rgb_(  0, 255,   0);
		static constexpr T Yellow  = rgb_(255, 255,   0);
		static constexpr T Blue    = rgb_(  0,   0, 255);
		static constexpr T Fuchsi  = rgb_(255,   0, 255);
		static constexpr T Aqua    = rgb_(  0, 255, 255);
		static constexpr T White   = rgb_(255, 255, 255);
	};
}
