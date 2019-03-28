#pragma once
//=====================================================================//
/*!	@file
	@brief	グラフィックス・カラー定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/byte_order.h"

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RGBA カラー型
		@param[in]	T	基本型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	struct rgba_base_t {

		typedef T value_type;

#if defined(LITTLE_ENDIAN)
		T		r;
		T		g;
		T		b;
		T		a;
		constexpr rgba_base_t(T rr = 0, T gg = 0, T bb = 0, T aa = 255) :
			r(rr), g(gg), b(bb), a(aa) { }
		constexpr rgba_base_t(const rgba_base_t<T>& t) : r(t.r), g(t.g), b(t.b), a(t.a) { }
#elif defined(BIG_ENDIAN)
		T		a;
		T		b;
		T		g;
		T		r;
		constexpr rgba_base_t(T rr = 0, T gg = 0, T bb = 0, T aa = 255) :
			a(aa), b(bb), g(gg), r(rr) { }
		constexpr rgba_base_t(const rgba_base_t<T>& t) : a(t.a), b(t.b), g(t.g), r(t.r) { }
#endif
	};
	typedef rgba_base_t<uint8_t> rgba8_t;
	typedef rgba_base_t<float  > rgbaf_t;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	カラー型（共有型）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	union color_t {
		uint32_t	rgba;
		rgba8_t		unit;

		constexpr explicit color_t(uint32_t v = 0xff000000) : rgba(v) { }
		constexpr color_t(const rgba8_t& t) : unit(t) { }
		constexpr color_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : unit(r, g, b, a) { }
		color_t(const color_t& t) noexcept : rgba(t.rgba) { }
 		color_t& operator = (const color_t& t) noexcept { rgba = t.rgba; return *this; }
		color_t& operator = (color_t&& t) noexcept { rgba = t.rgba; return *this; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	共有カラー・クラス @n
				16 ビットカラー、32 ビットカラー格納クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct share_color {

		static constexpr uint16_t to_565(uint8_t r, uint8_t g, uint8_t b)
		{
			return
				(static_cast<uint16_t>(r & 0xf8) << 8)
			  | (static_cast<uint16_t>(g & 0xfc) << 3)
			  | (static_cast<uint16_t>(b) >> 3);
		}

		uint16_t	rgb565;
		color_t		rgba8;

		constexpr share_color(uint8_t r, uint8_t g, uint8_t b) noexcept :
			rgb565(to_565(r, g, b)), rgba8(r, g, b, 255) { }

		share_color(const share_color& t) noexcept :
			rgb565(t.rgb565), rgba8(t.rgba8) { }

		share_color& operator = (const share_color& t) {
			rgb565 = t.rgb565;
			rgba8 = t.rgba8;
			return *this;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	カラー定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct def_color {
		static const share_color Black;
		static const share_color Maroon;
		static const share_color Green;
		static const share_color Olive;
		static const share_color Navy;
		static const share_color Purple;
		static const share_color Teal;
		static const share_color Silver;
		static const share_color Gray;
		static const share_color Grey;
		static const share_color Red;
		static const share_color Lime;
		static const share_color Yellow;
		static const share_color Blue;
		static const share_color Fuchsi;
		static const share_color Aqua;
		static const share_color White;
	};
}
