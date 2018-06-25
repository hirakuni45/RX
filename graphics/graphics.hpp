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
#include <cstdint>

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ASCII 無効フォント定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class afont_null {
	public:
		static const int8_t width = 0;
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
		@brief	ビットマップ描画クラス
		@param[in]	WIDTH	横幅
		@param[in]	HEIGHT	高さ
		@param[in]	AFONT	ASCII フォント・クラス
		@param[in]	KFONT	漢字フォントクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T, uint16_t WIDTH, uint16_t HEIGHT, class AFONT = afont_null, class KFONT = kfont_null>
	class base {

		T*			fb_;

		KFONT& 		kfont_;

		T			fc_;
		T			bc_;

		uint16_t	code_;
		uint8_t		cnt_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		base(T* org, KFONT& kf) noexcept : fb_(org), kfont_(kf),
			fc_(0xffff), bc_(0x0000),
			code_(0), cnt_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	横幅の取得
			@return 横幅
		*/
		//-----------------------------------------------------------------//
		int16_t get_width() const noexcept { return WIDTH; }


		//-----------------------------------------------------------------//
		/*!
			@brief	高さの取得
			@return 高さ
		*/
		//-----------------------------------------------------------------//
		int16_t get_height() const noexcept { return HEIGHT; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォントの幅を取得
			@return フォントの幅
		*/
		//-----------------------------------------------------------------//
		int8_t get_afont_width() const noexcept { return AFONT::width; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォントの高さを取得
			@return フォントの高さ
		*/
		//-----------------------------------------------------------------//
		int8_t get_afont_height() const noexcept { return AFONT::height; }


		//-----------------------------------------------------------------//
		/*!
			@brief	漢字フォントの幅を取得
			@return フォントの幅
		*/
		//-----------------------------------------------------------------//
		int8_t get_kfont_width() const noexcept { return KFONT::width; }


		//-----------------------------------------------------------------//
		/*!
			@brief	漢字フォントの高さを取得
			@return フォントの高さ
		*/
		//-----------------------------------------------------------------//
		int8_t get_kfont_height() const noexcept { return KFONT::height; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フレームバッファのアドレスを返す
			@return フレームバッファ・アドレス
		*/
		//-----------------------------------------------------------------//
		const T* fb() const noexcept { return fb_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォア・カラーの設定
			@param[in]	c	フォア・カラー
		*/
		//-----------------------------------------------------------------//
		void set_fore_color(T c) noexcept { fc_ = c; }


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
			@brief	点を描画する
			@param[in]	x	開始点Ｘ軸を指定
			@param[in]	y	開始点Ｙ軸を指定
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		void plot(int16_t x, int16_t y, T c) noexcept {
			if(static_cast<uint16_t>(x) >= WIDTH) return;
			if(static_cast<uint16_t>(y) >= HEIGHT) return;
			fb_[y * WIDTH + x] = c;
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
		void fill(int16_t x, int16_t y, int16_t w, int16_t h, T c) {
			for(int16_t i = y; i < (y + h); ++i) {
				for(int16_t j = x; j < (x + w); ++j) {
					plot(j, i, c);
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	全画面クリアをする
			@param[in]	c	クリアカラー
		*/
		//-----------------------------------------------------------------//
		void clear(T c) noexcept {
			for(uint16_t i = 0; i < (WIDTH * HEIGHT); ++i) {
				fb_[i] = c;
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
		void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, T c) {
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
		void frame(int16_t x, int16_t y, int16_t w, int16_t h, T c) {
			for(int16_t i = 0; i < w; ++i) {
				plot(x + i, y, c);
				plot(x + i, y + h - 1, c);
			}
			for(int16_t i = 0; i < h; ++i) {
				plot(x, y + i, c);
				plot(x + w - 1, y + i, c);
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
		void draw_font_utf16(int16_t x, int16_t y, uint16_t code)
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
		int16_t draw_text(int16_t x, int16_t y, const char* text, bool prop = false)
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
		int16_t get_text_length(const char* text, bool prop = false)
		{
			char ch;
			int16_t x = 0;
			while((ch = *text++) != 0) {
				x = draw_font(x, get_height(), ch, prop);
			}
			return x;
		}


	};
}
