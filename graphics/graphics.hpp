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
		@param[in]	T		ピクセル型（８、１６、３２）
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

		int8_t		round_[round_radius];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		render(T* org, KFONT& kf) noexcept : fb_(org), kfont_(kf),
			fc_(COLOR::White), bc_(COLOR::Black),
			code_(0), cnt_(0), stipple_(-1), stipple_mask_(1)
		{
			for(int16_t r = 0; r < round_radius; ++r) {
				round_[r] = intmath::sqrt16((round_radius * round_radius) - (r * r)).val;
			}
		}


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
		void fill(int16_t x, int16_t y, int16_t w, int16_t h, T c) noexcept
		{
			if(w <= 0 || h <= 0) return;

			for(int16_t yy = y; yy < (y + h); ++yy) {
				line_h(yy, x, w, c);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	角がラウンドした四角を塗りつぶす
			@param[in]	x	開始位置 X
			@param[in]	y	開始位置 Y
			@param[in]	w	横幅 
			@param[in]	h	高さ
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		void fill_r(int16_t x, int16_t y, int16_t w, int16_t h, T c) noexcept {
			for(int16_t yy = 0; yy < h; ++yy) {
				int16_t o = 0;
				if(h >= (round_radius * 2)) {
					if(yy < round_radius) {
						o = round_radius - round_[round_radius - yy - 1];
					} else if((h - round_radius) <= yy) {
						o = round_radius - round_[yy - (h - round_radius)];
					}
				}
				line_h(y + yy, x + o, w - o * 2, c);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	全画面クリアをする
			@param[in]	c	クリアカラー
		*/
		//-----------------------------------------------------------------//
		void clear(T c) noexcept {
			if(sizeof(T) == 2) {  // 16 bits pixel
				uint32_t c32 = (static_cast<uint32_t>(c) << 16) | c;
				uint32_t* out = reinterpret_cast<uint32_t*>(fb_);
				for(uint32_t i = 0; i < (WIDTH * HEIGHT) / 16; ++i) {
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
			@brief	フレームを描画する
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
		*/
		//-----------------------------------------------------------------//
		void draw_bitmap(int16_t x, int16_t y, const void* img, uint8_t w, uint8_t h) noexcept
		{
			if(img == nullptr) return;

			const uint8_t* p = static_cast<const uint8_t*>(img);
			uint8_t k = 1;
			uint8_t c = *p++;
			for(uint8_t i = 0; i < h; ++i) {
				int16_t xx = x;
				for(uint8_t j = 0; j < w; ++j) {
					if(c & k) plot(xx, y, fc_);
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
		*/
		//-----------------------------------------------------------------//
		void draw_mobj(int16_t x, int16_t y, const void* src) noexcept
		{
			if(src == nullptr) return;

			const uint8_t* p = static_cast<const uint8_t*>(src);
			uint8_t w = *p++;
			uint8_t h = *p++;
			draw_bitmap(x, y, p, w, h);
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
				x = draw_font(x, height, ch, prop);
			}
			return x;
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
			fill(x + 1, y + 1, w - 2, h - 2, COLOR::Black);
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
			fill(x, y, w, h, bc_);
			x += (w - len) / 2;
			y += (h - font_height) / 2;
			draw_text(x, y, text);
		}
	};
}
