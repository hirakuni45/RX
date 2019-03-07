#pragma once
//=====================================================================//
/*!	@file
	@brief	グラフィックス・ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/color.hpp"
#include "graphics/afont.hpp"
#include "graphics/kfont.hpp"
#include "common/intmath.hpp"
#include "common/circle.hpp"

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	レンダリング
		@param[in]	GLC		グラフィックス・コントローラー・クラス
		@param[in]	AFONT	ASCII フォント・クラス
		@param[in]	KFONT	漢字フォントクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GLC, class AFONT = afont_null, class KFONT = kfont_null>
	class render {

		GLC&		glc_;

	public:
		static const uint16_t VERSION = 100;

//		typedef typename device::glcdc_def::pix<GLC::PXT>::type T;
		typedef uint16_t T;
		typedef T value_type;
		typedef base_color<T> COLOR;

		typedef GLC glc_type;
		typedef AFONT afont_type;
		typedef KFONT kfont_type;

		static const int16_t font_height  = KFONT::height < AFONT::height
			? AFONT::height : KFONT::height;

		static const int16_t line_offset = (((GLC::width * sizeof(T)) + 63) & 0x7fc0) / sizeof(T);

		static const int16_t round_radius = 8;

	private:
		T*			fb_;

		KFONT& 		kfont_;

		T			fc_;
		T			bc_;

		uint32_t	stipple_;
		uint32_t	stipple_mask_;

		vtx::spos	ofs_;

		// 1/8 円を拡張して、全周に点を打つ
		void circle_pset_(int16_t xc, int16_t yc, int16_t x, int16_t y, T c) noexcept
		{
			plot(xc + x, yc + y, c);
			plot(xc + y, yc + x, c);
			plot(xc - y, yc + x, c);
			plot(xc - x, yc + y, c);
			plot(xc - x, yc - y, c);
			plot(xc - y, yc - x, c);
			plot(xc + y, yc - x, c);
			plot(xc + x, yc - y, c);
		}


		void circle_offset_(int16_t xc, int16_t yc, int16_t x, int16_t y, int16_t ox, int16_t oy, T c) noexcept
		{
			plot(xc + ox + x, yc + oy + y, c);
			plot(xc + ox + y, yc + oy + x, c);
			plot(xc - y,      yc + oy + x, c);
			plot(xc - x,      yc + oy + y, c);
			plot(xc - x,      yc - y,      c);
			plot(xc - y,      yc - x,      c);
			plot(xc + ox + y, yc - x,      c);
			plot(xc + ox + x, yc - y,      c);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	glc		グラフィックス制御クラス
			@param[in]	kf		漢字フォントクラス
		*/
		//-----------------------------------------------------------------//
		render(GLC& glc, KFONT& kf) noexcept : glc_(glc), kfont_(kf),
			fc_(COLOR::White), bc_(COLOR::Black),
			stipple_(-1), stipple_mask_(1), ofs_(0)
		{ fb_ = static_cast<T*>(glc_.get_fbp()); }


		//-----------------------------------------------------------------//
		/*!
			@brief	ハードウェアーバージョンを取得
			@return ハードウェアーバージョン
		*/
		//-----------------------------------------------------------------//
		uint16_t get_version() const noexcept { return VERSION; }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始 @n
					※互換性の為に用意
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			return true;
		}


		void start_frame() noexcept { }
		void end_frame() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	フレームバッファのアドレスを返す
			@return フレームバッファ・アドレス
		*/
		//-----------------------------------------------------------------//
		const T* fb() const noexcept { return fb_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォア・カラーの取得
			@return フォア・カラー
		*/
		//-----------------------------------------------------------------//
		T get_fore_color() const noexcept { return fc_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォア・カラーの設定
			@param[in]	c	フォア・カラー
		*/
		//-----------------------------------------------------------------//
		void set_fore_color(T c) noexcept { fc_ = c; }


		//-----------------------------------------------------------------//
		/*!
			@brief	バック・カラーの取得
			@return バック・カラー
		*/
		//-----------------------------------------------------------------//
		T get_back_color() const noexcept { return bc_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	バック・カラーの設定
			@param[in]	c	バック・カラー
		*/
		//-----------------------------------------------------------------//
		void set_back_color(T c) noexcept { bc_ = c; }


		//-----------------------------------------------------------------//
		/*!
			@brief	カラーの交換
		*/
		//-----------------------------------------------------------------//
		void swap_color() noexcept { std::swap(fc_, bc_); }


		//-----------------------------------------------------------------//
		/*!
			@brief	カラーの合成
			@param[in]	c0	カラーＡ
			@param[in]	c1	カラーＢ
			@return 合成されたカラー
		*/
		//-----------------------------------------------------------------//
		uint16_t color_sum(T c0, T c1) noexcept
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
			@brief	破線パターンの設定
			@param[in]	stipple	破線パターン
		*/
		//-----------------------------------------------------------------//
		void set_stipple(uint32_t stipple = -1) noexcept {
			stipple_ = stipple;
			stipple_mask_ = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	点を描画する
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		void plot(int16_t x, int16_t y, T c) noexcept
		{
			auto m = stipple_mask_;
			stipple_mask_ <<= 1;
			if(stipple_mask_ == 0) stipple_mask_ = 1;

			if((stipple_ & m) == 0) {
				return;
			}
			if(static_cast<uint16_t>(x) >= static_cast<uint16_t>(GLC::width)) return;
			if(static_cast<uint16_t>(y) >= static_cast<uint16_t>(GLC::height)) return;
			fb_[y * line_offset + x] = c;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	点を取得する
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@return	カラー
		*/
		//-----------------------------------------------------------------//
		T get_plot(int16_t x, int16_t y) const noexcept
		{
			if(static_cast<uint16_t>(x) >= static_cast<uint16_t>(GLC::width)) return -1;
			if(static_cast<uint16_t>(y) >= static_cast<uint16_t>(GLC::height)) return -1;
			return fb_[y * line_offset + x];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	水平ラインを描画
			@param[in]	y	開始位置 Y
			@param[in]	x	水平開始位置
			@param[in]	w	水平幅
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		void line_h(int16_t y, int16_t x, int16_t w, T c) noexcept
		{
			if(w <= 0) return;
			if(static_cast<uint16_t>(y) >= static_cast<uint16_t>(GLC::height)) return;
			if(x < 0) {
				w += x;
				x = 0;
			} else if(static_cast<uint16_t>(x) >= static_cast<uint16_t>(GLC::width)) {
				return;
			}
			if(static_cast<uint16_t>(x + w) >= static_cast<uint16_t>(GLC::width)) {
				w = GLC::width - x;
			}
			T* out = &fb_[y * line_offset + x];
			for(int16_t i = 0; i < w; ++i) {
				*out++ = c;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	垂直ラインを描画
			@param[in]	x	開始位置 x
			@param[in]	y	垂直開始位置
			@param[in]	h	垂直幅
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		void line_v(int16_t x, int16_t y, int16_t h, T c) noexcept
		{
			if(h <= 0) return;
			if(static_cast<uint16_t>(x) >= static_cast<uint16_t>(GLC::width)) return;
			if(y < 0) {
				h += y;
				y = 0;
			} else if(static_cast<uint16_t>(y) >= static_cast<uint16_t>(GLC::height)) {
				return;
			}
			if(static_cast<uint16_t>(y + h) >= static_cast<uint16_t>(GLC::height)) {
				h = GLC::height - y;
			}
			T* out = &fb_[y * line_offset + x];
			for(int16_t i = 0; i < h; ++i) {
				*out = c;
				out += line_offset;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	四角を塗りつぶす
			@param[in]	x	開始位置 X
			@param[in]	y	開始位置 Y
			@param[in]	w	横幅 
			@param[in]	h	高さ
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		void fill_box(int16_t x, int16_t y, int16_t w, int16_t h, T c) noexcept
		{
			if(w <= 0 || h <= 0) return;

			for(int16_t yy = y; yy < (y + h); ++yy) {
				line_h(yy, x, w, c);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	全画面クリアをする
			@param[in]	c	クリアカラー
		*/
		//-----------------------------------------------------------------//
		void clear(T c) noexcept
		{
			if(sizeof(T) == 2) {  // 16 bits pixel
				uint32_t c32 = (static_cast<uint32_t>(c) << 16) | c;
				uint32_t* out = reinterpret_cast<uint32_t*>(fb_);
				for(uint32_t i = 0; i < (GLC::width * GLC::height) / 32; ++i) {
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
					*out++ = c32;
				}
			} else {
				for(auto y = 0; y < GLC::height; ++y) {
					T* p = &fb_[line_offset * y];
					for(auto x = 0; x < GLC::width; ++x) {
						*p++ = c;
					}
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	線を描画する
			@param[in]	x1	開始点Ｘ軸を指定
			@param[in]	y1	開始点Ｙ軸を指定
			@param[in]	x2	終了点Ｘ軸を指定
			@param[in]	y2	終了点Ｙ軸を指定
			@param[in]	c	描画色
		*/
		//-----------------------------------------------------------------//
		void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, T c) noexcept {
			int16_t dx;
			int16_t dy;
			int16_t sx;
			int16_t sy;
			if(x2 >= x1) { dx = x2 - x1; sx = 1; } else { dx = x1 - x2; sx = -1; }
			if(y2 >= y1) { dy = y2 - y1; sy = 1; } else { dy = y1 - y2; sy = -1; }

			int16_t m = 0;
			int16_t x = x1;
			int16_t y = y1;
			if(dx > dy) {
				for(int16_t i = 0; i <= dx; i++) {
					plot(x, y, c);
					m += dy;
					if(m >= dx) {
						m -= dx;
						y += sy;
					}
					x += sx;
				}
			} else {
				for(int16_t i = 0; i <= dy; i++) {
					plot(x, y, c);
					m += dx;
					if(m >= dy) {
						m -= dy;
						x += sx;
					}
					y += sy;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム（線の箱）を描画する
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	w	横幅
			@param[in]	h	高さ
			@param[in]	c	描画色
		*/
		//-----------------------------------------------------------------//
		void frame(int16_t x, int16_t y, int16_t w, int16_t h, T c) noexcept
		{
			line_h(y, x, w, c);
			line_h(y + h - 1, x, w, c);
			line_v(x, y + 1, h - 2, c);
			line_v(x + w - 1, y + 1, h - 2, c);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	角がラウンドしたフレーム（線）を描画する
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	w	横幅
			@param[in]	h	高さ
			@param[in]	rad	ラウンドの半径
			@param[in]	col	描画色
		*/
		//-----------------------------------------------------------------//
		void round_frame(int16_t x, int16_t y, int16_t w, int16_t h, int16_t rad, T col) noexcept
		{
			if(w < (rad + rad) || h < (rad + rad)) {
				if(w < h) rad = w / 2;
				else rad = h / 2;
			} 
			int16_t xc = x + rad;
			int16_t yc = y + rad;
			int16_t xo = w - rad * 2 - 2;
			int16_t yo = h - rad * 2 - 2;
			line_h(y, xc, xo, col);
			line_h(y + h - 1, xc, xo, col);
			line_v(x, yc, yo, col);
			line_v(x + w - 1, yc, yo, col);
			int16_t xx = 0;
			int16_t yy = rad;
			int16_t p = (5 - rad * 4) / 4;
			circle_offset_(xc, yc, xx, yy, xo, yo, col);
			while(xx < yy) {
				xx++;
				if(p < 0) {
					p += 2 * xx + 1;
				} else {
					yy--;
					p += 2 * (xx - yy) + 1;
				}
				circle_offset_(xc, yc, xx, yy, xo, yo, col);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	角がラウンドした塗りつぶされた箱を描画する
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	w	横幅
			@param[in]	h	高さ
			@param[in]	rad	ラウンドの半径
			@param[in]	col	描画色
		*/
		//-----------------------------------------------------------------//
		void round_box(int16_t x, int16_t y, int16_t w, int16_t h, int16_t rad, T col) noexcept
		{
			if(w < (rad + rad) || h < (rad + rad)) {
				if(w < h) rad = w / 2;
				else rad = h / 2;
			}
			int16_t xc = x + rad;
			int16_t yc = y + rad;
			int16_t xo = w - rad * 2 - 2;
			int16_t yo = h - rad * 2 - 2;
			fill_box(x, yc, w, yo, col);
			int16_t xx = 0;
			int16_t yy = rad;
			int16_t p = (5 - rad * 4) / 4;
			line_h(yc + yo, xc - yy, yy + yy + 1 + xo, col);
			line_h(yc + yy + yo + 1, xc - xx, xx + xx + xo, col);
			while(xx < yy) {
				xx++;
				if(p < 0) {
					p += 2 * xx + 1;
				} else {
					// x` = x - 1
					line_h(yc - yy,      xc - xx + 1, xx + xx + xo - 1, col);
					line_h(yc + yy + yo, xc - xx + 1, xx + xx + xo - 1, col);
					yy--;
					p += 2 * (xx - yy) + 1;
				}
				line_h(yc - xx,      xc - yy, yy + yy + xo + 1, col);
				line_h(yc + xx + yo, xc - yy, yy + yy + xo + 1, col);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	円弧（線）を描画する
			@param[in]	x0	開始点Ｘ軸
			@param[in]	y0	開始点Ｙ軸
			@param[in]	xc	中心点Ｘ軸
			@param[in]	yc	中心点Ｙ軸
			@param[in]	x1	終了点Ｘ軸
			@param[in]	y1	終了点Ｙ軸
			@param[in]	col	描画色
			@return 座標指定が不整合な場合「false」
		*/
		//-----------------------------------------------------------------//
		bool arc(int16_t x0, int16_t y0, int16_t xc, int16_t yc, int16_t x1, int16_t y1, T col)
			noexcept
		{
			imath::circle cir;
//			cir.test();
//			return false;
			if(!cir.start(vtx::ipos(x0, y0), vtx::ipos(xc, yc), vtx::ipos(x1, y1))) {
				return false;
			}
			do {
				vtx::ipos pos = cir.get_position();
				plot(pos.x, pos.y, col);
			} while(!cir.step()) ;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	円（線）を描画する
			@param[in]	xc	中心点Ｘ軸
			@param[in]	yc	中心点Ｙ軸
			@param[in]	rad	半径を指定
			@param[in]	col	描画色
		*/
		//-----------------------------------------------------------------//
		void circle(int16_t xc, int16_t yc, int16_t rad, T col) noexcept
		{
			int16_t x = 0;
			int16_t y = rad;
			int16_t p = (5 - rad * 4) / 4;
			circle_pset_(xc, yc, x, y, col);
			while(x < y) {
				x++;
				if(p < 0) {
					p += 2 * x + 1;
				} else {
					y--;
					p += 2 * (x - y) + 1;
				}
				circle_pset_(xc, yc, x, y, col);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	円を描画する
			@param[in]	xc	中心点Ｘ軸
			@param[in]	yc	中心点Ｙ軸
			@param[in]	rad	半径を指定
			@param[in]	col	描画色
		*/
		//-----------------------------------------------------------------//
		void fill_circle(int16_t xc, int16_t yc, int16_t rad, T col) noexcept
		{
			int16_t x = 0;
			int16_t y = rad;
			int16_t p = (5 - rad * 4) / 4;
			line_h(yc, xc - y, y + y + 1, col);
			while(x < y) {
				x++;
				if(p < 0) {
					p += 2 * x + 1;
				} else {
					// x` = x - 1
					line_h(yc - y, xc - x + 1, x + x - 1, col);
					line_h(yc + y, xc - x + 1, x + x - 1, col);
					y--;
					p += 2 * (x - y) + 1;
				}
				line_h(yc - x, xc - y, y + y + 1, col);
				line_h(yc + x, xc - y, y + y + 1, col);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	スクロール
			@param[in]	h		スクロール高さ（+up、-down）
		*/
		//-----------------------------------------------------------------//
		void scroll(int16_t h) noexcept
		{
			if(h > 0) {
				for(int32_t i = 0; i < (line_offset * (GLC::height - h)); ++i) {
					fb_[i] = fb_[i + (line_offset * h)];
				}
			} else if(h < 0) {
				h = -h;
				for(int32_t i = (line_offset * (GLC::height - h)) - 1; i >= 0; --i) {
					fb_[i + (line_offset * h)] = fb_[i];
				}
			}			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ビットマップイメージを描画する
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	img	描画ソースのポインター
			@param[in]	w	描画ソースの幅
			@param[in]	h	描画ソースの高さ
			@param[in]	b	背景を描画する場合「true」
		*/
		//-----------------------------------------------------------------//
		void draw_bitmap(int16_t x, int16_t y, const void* img, uint8_t w, uint8_t h, bool b = false)
		noexcept {
			if(img == nullptr) return;

			const uint8_t* p = static_cast<const uint8_t*>(img);
			uint8_t k = 1;
			uint8_t c = *p++;
			for(uint8_t i = 0; i < h; ++i) {
				int16_t xx = x;
				for(uint8_t j = 0; j < w; ++j) {
					if(c & k) plot(xx, y, fc_);
					else if(b) plot(xx, y, bc_);
					k <<= 1;
					if(k == 0) {
						k = 1;
						c = *p++;
					}
					++xx;
				}
				++y;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	モーションオブジェクトのサイズを取得
			@param[in]	src	描画オブジェクト
			@param[in]	w	横幅
			@param[in]	h	高さ
		*/
		//-----------------------------------------------------------------//
		void get_mobj_size(const void* src, uint8_t& w, uint8_t& h) const noexcept {
			if(src == nullptr) {
				w = 0;
				h = 0;
				return;
			}
			const uint8_t* p = static_cast<const uint8_t*>(src);
			w = *p++;
			h = *p;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	モーションオブジェクトを描画する
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	src	描画オブジェクト
			@param[in]	b	背景を描画する場合「true」
		*/
		//-----------------------------------------------------------------//
		void draw_mobj(int16_t x, int16_t y, const void* src, bool b) noexcept
		{
			if(src == nullptr) return;

			const uint8_t* p = static_cast<const uint8_t*>(src);
			uint8_t w = *p++;
			uint8_t h = *p++;
			draw_bitmap(x, y, p, w, h, b);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	UTF-16 フォントの描画
			@param[in]	pos		描画位置
			@param[in]	code	UTF-16 コード
		*/
		//-----------------------------------------------------------------//
		void draw_font_utf16(const vtx::spos& pos, uint16_t code) noexcept
		{
			if(pos.y <= -AFONT::height || pos.y >= GLC::height) {
				return;
			}
			if(code < 0x80) {
				if(pos.x <= -AFONT::width || pos.x >= GLC::width) {
					return;
				}
				draw_bitmap(pos.x, pos.y, AFONT::get(code), AFONT::width, AFONT::height);
			} else {
				if(pos.x <= -KFONT::width || pos.x >= GLC::width) {
					return;
				}
				auto p = kfont_.get(code);
				if(p != nullptr) {
					draw_bitmap(pos.x, pos.y, p, KFONT::width, KFONT::height);
				} else {
					draw_bitmap(pos.x, pos.y, AFONT::get('['), AFONT::width, AFONT::height);
					auto x = pos.x + AFONT::width;
					draw_bitmap(x, pos.y, AFONT::get(']'), AFONT::width, AFONT::height);
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フォントの描画 (UTF-8)
			@param[in]	pos		描画位置
			@param[in]	cha		文字コード
			@param[in]	prop	プロポーショナルの場合「true」
			@return 文字の終端座標 (X)
		*/
		//-----------------------------------------------------------------//
		int16_t draw_font(const vtx::spos& pos, char cha, bool prop = false) noexcept
		{
			int16_t w = 0;
			if(kfont_.injection_utf8(static_cast<uint8_t>(cha))) {
				auto code = kfont_.get_utf16();
				if(code >= 0x80) {
					draw_font_utf16(pos, code);
					w = KFONT::width;
				} else {
					int16_t o = 0;
					if(prop) {
						o = AFONT::get_kern(code);
					}
					draw_font_utf16(vtx::spos(pos.x + o, pos.y), code);
					if(prop) {
						w = AFONT::get_width(code);
					} else {
						w = AFONT::width;
					}
				}
			}
			return w;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	文字列の描画
			@param[in]	pos		描画位置
			@param[in]	str		文字列　(UTF-8)
			@param[in]	prop	プロポーショナルの場合「true」
			@return 文字の最終座標 (X)
		*/
		//-----------------------------------------------------------------//
		int16_t draw_text(const vtx::spos& pos, const char* str, bool prop = false) noexcept
		{
			if(str == nullptr) return 0;

			auto p = pos;
			char ch;
			while((ch = *str++) != 0) {
				if(ch == '\n') {
					p.x = 0;
					p.y += AFONT::height;
				} else {
					p.x = draw_font(p, ch, prop);
				}
			}
			return p.x;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	テキストの描画サイズを得る
			@param[in]	text	テキスト（UTF-8）
			@param[in]	prop	プロポーショナルの場合「true」
			@return 描画サイズ
		*/
		//-----------------------------------------------------------------//
		int16_t get_text_length(const char* text, bool prop = false) noexcept
		{
			char ch;
			int16_t x = 0;
			while((ch = *text++) != 0) {
				// 画面外描画
				x = draw_font(vtx::spos(x, GLC::height), ch, prop);
			}
			return x;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	テキストの背景を描画する
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	text	テキスト（UTF-8）
			@param[in]	prop	プロポーショナルの場合「true」
			@return 文字の終端座標（Ｘ）
		*/
		//-----------------------------------------------------------------//
		int16_t draw_text_back(int16_t x, int16_t y, const char* text, bool prop = false) noexcept
		{
			char ch;
			bool fill = false;
			auto xx = x;
			uint16_t code = 0;
			uint16_t cnt = 0;
			while((ch = *text++) != 0) {
				auto c = static_cast<uint8_t>(ch);
				if(c < 0x80) {
					if(ch == 0x20) {
						fill_box(x, y, xx - x, AFONT::height, bc_);
						x = xx;
						fill = true;
					} else {
						fill = false;
					}
					if(prop) {
						xx += AFONT::get_kern(ch);
						xx += AFONT::get_width(ch);
					} else {
						xx += AFONT::width;
					}
				} else if((c & 0xf0) == 0xe0) {
					code = (c & 0x0f);
					cnt = 2;
				} else if((c & 0xe0) == 0xc0) {
					code = (c & 0x1f);
					cnt = 1;
				} else if((c & 0xc0) == 0x80) {
					code <<= 6;
					code |= c & 0x3f;
					cnt--;
					if(cnt == 0 && code != 0) {
						xx += KFONT::width;
					} else if(cnt < 0) {
						code = 0;
					}
				}
			}
			if(!fill) {
				fill_box(x, y, xx - x, AFONT::height, bc_);
			}
			return xx;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ダイアログ表示（画面の中心に表示される）
			@param[in]	w		横幅
			@param[in]	h		高さ
			@param[in]	text	テキスト
		*/
		//-----------------------------------------------------------------//
		void draw_dialog(uint16_t w, uint16_t h, const char* text) noexcept
		{
			auto x = (GLC::width  - w) / 2;
			auto y = (GLC::height - h) / 2;
			frame(x, y, w, h, COLOR::White);
			fill_box(x + 1, y + 1, w - 2, h - 2, COLOR::Black);
			auto l = get_text_length(text);
			x += (w - l) / 2;
			y += (h - font_height) / 2;
			draw_text(vtx::spos(x, y), text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	標準ボタンの描画 @n
					・背景色は「back_color」が使われる。@n
					・フォントの描画色は「fore_color」が利用
			@param[in]	x		X 位置
			@param[in]	y		Y 位置
			@param[in]	w		横幅
			@param[in]	h		高さ
			@param[in]	text	テキスト
		*/
		//-----------------------------------------------------------------//
		void draw_button(int16_t x, int16_t y, int16_t w, int16_t h, const char* text) noexcept
		{
			auto len = get_text_length(text);
			fill_box(x, y, w, h, bc_);
			x += (w - len) / 2;
			y += (h - font_height) / 2;
			draw_text(x, y, text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	オフセットを設定
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		void set_offset(const vtx::spos& ofs = vtx::spos(0)) noexcept { ofs_ = ofs; }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画ファンクタ
			@param[in]	x	X 座標
			@param[in]	y	Y 座標
			@param[in]	r	R カラー
			@param[in]	g	G カラー
			@param[in]	b	B カラー
		*/
		//-----------------------------------------------------------------//
		void operator() (int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b) noexcept {
			auto c = COLOR::rgb(r, g, b);
			plot(x + ofs_.x, y + ofs_.y, c);			
		}
	};
}
