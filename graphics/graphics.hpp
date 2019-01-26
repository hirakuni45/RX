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
#include "common/intmath.hpp"
#include "common/circle.hpp"

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


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	漢字 無効フォント定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class kfont_null {
	public:
		static const int8_t width = 0;
		static const int8_t height = 0;
		const uint8_t* get(uint16_t code) { return nullptr; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	レンダリング
		@param[in]	T		ピクセル型：uint8_t(8)、uint16_t(16)、uint32_t(32)
		@param[in]	WIDTH	横幅
		@param[in]	HEIGHT	高さ
		@param[in]	AFONT	ASCII フォント・クラス
		@param[in]	KFONT	漢字フォントクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T, uint16_t WIDTH, uint16_t HEIGHT, class AFONT = afont_null, class KFONT = kfont_null>
	class render {
	public:
		typedef T value_type;

		typedef base_color<T> COLOR;

		static const int16_t width  = static_cast<int16_t>(WIDTH);
		static const int16_t height = static_cast<int16_t>(HEIGHT);
		static const int16_t afont_width  = AFONT::width;
		static const int16_t afont_height = AFONT::height;
		static const int16_t kfont_width  = KFONT::width;
		static const int16_t kfont_height = KFONT::height;
		static const int16_t font_height  = KFONT::height < AFONT::height
			? AFONT::height : KFONT::height;

		static const int16_t line_offset = (((width * sizeof(T)) + 63) & 0x7fc0) / sizeof(T);

		static const int16_t round_radius = 8;

	private:
		T*			fb_;

		KFONT& 		kfont_;

		T			fc_;
		T			bc_;

		uint16_t	code_;
		uint8_t		cnt_;

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
			@param[in]	org		フレーム・バッファ先頭アドレス
			@param[in]	kf		漢字フォントクラス
		*/
		//-----------------------------------------------------------------//
		render(void* org, KFONT& kf) noexcept : fb_(static_cast<T*>(org)), kfont_(kf),
			fc_(COLOR::White), bc_(COLOR::Black),
			code_(0), cnt_(0), stipple_(-1), stipple_mask_(1), ofs_(0)
		{ }


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
			if(static_cast<uint16_t>(x) >= WIDTH) return;
			if(static_cast<uint16_t>(y) >= HEIGHT) return;
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
			if(static_cast<uint16_t>(x) >= WIDTH) return 0;
			if(static_cast<uint16_t>(y) >= HEIGHT) return 0;
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
			if(static_cast<uint16_t>(y) >= HEIGHT) return;
			if(x < 0) {
				w += x;
				x = 0;
			} else if(x >= static_cast<int16_t>(WIDTH)) {
				return;
			}
			if((x + w) >= static_cast<int16_t>(WIDTH)) {
				w = static_cast<int16_t>(WIDTH) - x;
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
			if(static_cast<uint16_t>(x) >= WIDTH) return;
			if(y < 0) {
				h += y;
				y = 0;
			} else if(y >= static_cast<int16_t>(HEIGHT)) {
				return;
			}
			if((y + h) >= static_cast<int16_t>(HEIGHT)) {
				h = static_cast<int16_t>(HEIGHT) - y;
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
				for(uint32_t i = 0; i < (WIDTH * HEIGHT) / 32; ++i) {
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
				for(uint32_t y = 0; y < HEIGHT; ++y) {
					T* p = &fb_[line_offset * y];
					for(uint32_t x = 0; x < WIDTH; ++x) {
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
				for(int32_t i = 0; i < (line_offset * (HEIGHT - h)); ++i) {
					fb_[i] = fb_[i + (line_offset * h)];
				}
			} else if(h < 0) {
				h = -h;
				for(int32_t i = (line_offset * (HEIGHT - h)) - 1; i >= 0; --i) {
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
			@brief	フォントを描画する（UTF-16）
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	code	キャラクター・コード
		*/
		//-----------------------------------------------------------------//
		void draw_font_utf16(int16_t x, int16_t y, uint16_t code) noexcept
		{
			if(y <= -AFONT::height || y >= static_cast<int16_t>(HEIGHT)) {
				return;
			}
			if(code < 0x80) {
				if(x <= -AFONT::width || x >= static_cast<int16_t>(WIDTH)) {
					return;
				}
				draw_bitmap(x, y, AFONT::get(code), AFONT::width, AFONT::height);
			} else {
				if(x <= -KFONT::width || x >= static_cast<int16_t>(WIDTH)) {
					return;
				}
				auto p = kfont_.get(code);
				if(p != nullptr) {
					draw_bitmap(x, y, p, KFONT::width, KFONT::height);
				} else {
					draw_bitmap(x, y, AFONT::get('['), AFONT::width, AFONT::height);
					x += AFONT::width;
					draw_bitmap(x, y, AFONT::get(']'), AFONT::width, AFONT::height);
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フォントを描画する（UTF-8）
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	ch	キャラクター・コード
			@param[in]	prop	プロポーショナルの場合「true」
			@return 文字の終端座標（Ｘ）
		*/
		//-----------------------------------------------------------------//
		int16_t draw_font(int16_t x, int16_t y, char ch, bool prop = false) noexcept
		{
			uint8_t c = static_cast<uint8_t>(ch);
			if(c < 0x80) {
				int16_t o = 0;
				if(prop) {
					o = AFONT::get_kern(c);
				}
				draw_font_utf16(x + o, y, c);
				if(prop) {
					x += AFONT::get_width(c);
				} else {
					x += AFONT::width;
				}
				code_ = 0;
				return x;
			} else if((c & 0xf0) == 0xe0) {
				code_ = (c & 0x0f);
				cnt_ = 2;
				return x;
			} else if((c & 0xe0) == 0xc0) {
				code_ = (c & 0x1f);
				cnt_ = 1;
				return x;
			} else if((c & 0xc0) == 0x80) {
				code_ <<= 6;
				code_ |= c & 0x3f;
				cnt_--;
				if(cnt_ == 0 && code_ < 0x80) {
					code_ = 0;	// 不正なコードとして無視
					return x;
				} else if(cnt_ < 0) {
					code_ = 0;
				}
			}
			if(cnt_ == 0 && code_ != 0) {
				draw_font_utf16(x, y, code_);
				x += KFONT::width;
				code_ = 0;
			}
			return x;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	テキストを描画する。
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	text	テキスト（UTF-8）
			@param[in]	prop	プロポーショナルの場合「true」
			@return 文字の終端座標（Ｘ）
		*/
		//-----------------------------------------------------------------//
		int16_t draw_text(int16_t x, int16_t y, const char* text, bool prop = false) noexcept
		{
			char ch;
			while((ch = *text++) != 0) {
				if(ch == '\n') {
					x = 0;
					y += KFONT::height;
				} else {
					x = draw_font(x, y, ch, prop);
				}
			}
			return x;
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
				x = draw_font(x, height, ch, prop);
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
					} else if(cnt_ < 0) {
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
			int16_t x = (width  - w) / 2;
			int16_t y = (height - h) / 2;
			frame(x, y, w, h, COLOR::White);
			fill_box(x + 1, y + 1, w - 2, h - 2, COLOR::Black);
			auto l = get_text_length(text);
			x += (w - l) / 2;
			y += (h - font_height) / 2;
			draw_text(x, y, text);
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
