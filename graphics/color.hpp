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

		/// BGRA for DRW2D d2_color type
#if defined(LITTLE_ENDIAN)
		T		b;
		T		g;
		T		r;
		T		a;
		constexpr rgba_base_t(T rr = 0, T gg = 0, T bb = 0, T aa = 255) :
			b(bb), g(gg), r(rr), a(aa) { }
		constexpr rgba_base_t(const rgba_base_t<T>& t) : b(t.b), g(t.g), r(t.r), a(t.a) { }
#elif defined(BIG_ENDIAN)
		T		a;
		T		r;
		T		g;
		T		b;
		constexpr rgba_base_t(T rr = 0, T gg = 0, T bb = 0, T aa = 255) :
			a(aa), r(rr), g(gg), b(bb) { }
		constexpr rgba_base_t(const rgba_base_t<T>& t) : a(t.a), r(t.r), g(t.g), b(t.b) { }
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
		color_t& operator *= (uint8_t s) noexcept {
			unit.r = (static_cast<uint16_t>(unit.r) * (static_cast<uint16_t>(s) + 1)) >> 8;
			unit.g = (static_cast<uint16_t>(unit.g) * (static_cast<uint16_t>(s) + 1)) >> 8;
			unit.b = (static_cast<uint16_t>(unit.b) * (static_cast<uint16_t>(s) + 1)) >> 8;
			return *this;
		}
		bool operator == (const color_t& t) const { return rgba == t.rgba; }
		bool operator != (const color_t& t) const { return rgba != t.rgba; }
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

		share_color& operator = (const share_color& t) noexcept {
			rgb565 = t.rgb565;
			rgba8 = t.rgba8;
			return *this;
		}

		bool operator == (const share_color& t) const noexcept {
			return rgba8 == t.rgba8;
		}

		bool operator != (const share_color& t) const noexcept {
			return rgba8 != t.rgba8;
		}

		//-----------------------------------------------------------------//
		/*!
			@brief	輝度付きカラー設定
			@param[in]	col	ベースカラー
			@param[in]	y	輝度
		*/
		//-----------------------------------------------------------------//
		void set_color(const color_t& col, uint8_t y) noexcept
		{
			rgba8 = col;
			rgba8 *= y;
			rgb565 = to_565(rgba8.unit.r, rgba8.unit.g, rgba8.unit.b);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	RGB565 カラーの合成
			@param[in]	c0	カラーＡ
			@param[in]	c1	カラーＢ
			@return 合成されたカラー
		*/
		//-----------------------------------------------------------------//
		static uint16_t color_sum(uint16_t c0, uint16_t c1) noexcept
		{
			uint16_t r = c0 & 0b1111100000000000;
			uint16_t g = c0 & 0b0000011111100000;
			uint16_t b = c0 & 0b0000000000011111;
			r >>= 1;
			r += (c1 & 0b1111100000000000) >> 1;
			r &= 0b1111100000000000;
			g += c1 & 0b0000011111100000;
			g >>= 1;
			g &= 0b0000011111100000;
			b += c1 & 0b0000000000011111;
			b >>= 1;
			b &= 0b0000000000011111;
			return r | g | b;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	RGB565 カラーから RGBA888 への変換
			@param[in]	src		ソースカラー
			@return 変換されたカラー
		*/
		//-----------------------------------------------------------------//
		static rgba8_t conv_rgba8(uint16_t src) noexcept {
			uint8_t r = (src & 0b1111100000000000) >> 8;
			r |= r >> 5;
			uint8_t g = (src & 0b0000011111100000) >> 3;
			g |= g >> 6;
			uint8_t b = (src & 0b0000000000011111) << 3;
			b |= b >> 5;
			rgba8_t t(r, g, b);
			return t;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アルファ・ブレンド
			@param[in]	dst		元カラー
			@param[in]	src		合成カラー
			@return ブレンドされたカラー
		*/
		//-----------------------------------------------------------------//
		static rgba8_t blend(const rgba8_t& dst, const rgba8_t& src) noexcept {
			uint16_t aa = 256 - (src.a + 1);
			uint16_t ba = src.a + 1;
			uint16_t r = (dst.r * aa) + (src.r * ba);
			uint16_t g = (dst.g * aa) + (src.g * ba);
			uint16_t b = (dst.b * aa) + (src.b * ba);
			rgba8_t t(r >> 8, g >> 8, b >> 8);
			return t;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アルファ・ブレンド
			@param[in]	fc		正カラー
			@param[in]	alpha	輝度
			@param[in]	bc		裏カラー
			@return 合成後カラー
		*/
		//-----------------------------------------------------------------//
		static rgba8_t blend(const rgba8_t& fc, uint8_t alpha, const rgba8_t& bc) noexcept
		{
			uint16_t fi = alpha + 1;
			uint16_t bi = 256 - (alpha + 1);
			uint8_t r = (static_cast<uint16_t>(fc.r) * fi + static_cast<uint16_t>(bc.r) * bi) >> 8;
			uint8_t g = (static_cast<uint16_t>(fc.g) * fi + static_cast<uint16_t>(bc.g) * bi) >> 8;
			uint8_t b = (static_cast<uint16_t>(fc.b) * fi + static_cast<uint16_t>(bc.b) * bi) >> 8;
			return rgba8_t(r, g, b);
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
		static const share_color Midgray;
		static const share_color Darkgray;
		static const share_color Red;
		static const share_color Lime;
		static const share_color Yellow;
		static const share_color Blue;
		static const share_color Fuchsi;
		static const share_color Aqua;
		static const share_color White;
		static const share_color Orange;
		static const share_color SafeColor;
		static const share_color EmeraldGreen;
		static const share_color LightPink;
		static const share_color DarkSafeColor;
		static const share_color LightSafeColor;
	};
}
