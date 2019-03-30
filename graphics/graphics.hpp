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
#include "graphics/pixel.hpp"
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
		typedef def_color DEF_COLOR;
		typedef share_color SHARE_COLOR;
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

		share_color	fore_color_;
		share_color	back_color_;
		vtx::srect	clip_;

		uint32_t	stipple_;
		uint32_t	stipple_mask_;

		vtx::spos	ofs_;

		// 1/8 円を拡張して、全周に点を打つ
		void circle_pset_(const vtx::spos& cen, const vtx::spos& pos) noexcept
		{
			plot(vtx::spos(cen.x + pos.x, cen.y + pos.y), fore_color_.rgb565);
			plot(vtx::spos(cen.x + pos.y, cen.y + pos.x), fore_color_.rgb565);
			plot(vtx::spos(cen.x - pos.y, cen.y + pos.x), fore_color_.rgb565);
			plot(vtx::spos(cen.x - pos.x, cen.y + pos.y), fore_color_.rgb565);
			plot(vtx::spos(cen.x - pos.x, cen.y - pos.y), fore_color_.rgb565);
			plot(vtx::spos(cen.x - pos.y, cen.y - pos.x), fore_color_.rgb565);
			plot(vtx::spos(cen.x + pos.y, cen.y - pos.x), fore_color_.rgb565);
			plot(vtx::spos(cen.x + pos.x, cen.y - pos.y), fore_color_.rgb565);
		}


		void circle_offset_(const vtx::spos& cen, const vtx::spos& org, const vtx::spos& ofs) noexcept
		{
			plot(vtx::spos(cen.x + org.x + ofs.x, cen.y + org.y + ofs.y), fore_color_.rgb565);
			plot(vtx::spos(cen.x + org.y + ofs.x, cen.y + org.x + ofs.y), fore_color_.rgb565);
			plot(vtx::spos(cen.x - org.y        , cen.y + org.x + ofs.y), fore_color_.rgb565);
			plot(vtx::spos(cen.x - org.x        , cen.y + org.y + ofs.y), fore_color_.rgb565);
			plot(vtx::spos(cen.x - org.x        , cen.y - org.y        ), fore_color_.rgb565);
			plot(vtx::spos(cen.x - org.y        , cen.y - org.x        ), fore_color_.rgb565);
			plot(vtx::spos(cen.x + org.y + ofs.x, cen.y - org.x        ), fore_color_.rgb565);
			plot(vtx::spos(cen.x + org.x + ofs.x, cen.y - org.y        ), fore_color_.rgb565);
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
			fore_color_(255, 255, 255), back_color_(0, 0, 0),
			clip_(0, 0, GLC::width, GLC::height),
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


		//-----------------------------------------------------------------//
		/*!
			@brief	フレームの同期
		*/
		//-----------------------------------------------------------------//
		void sync_frame() noexcept
		{
			glc_.sync_vpos();
		}


		void start_frame() noexcept { }
		void end_frame() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	停止 @n
					※互換性の為に用意
		*/
		//-----------------------------------------------------------------//
		void stop() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	フレームバッファのアドレスを返す
			@return フレームバッファ・アドレス
		*/
		//-----------------------------------------------------------------//
		const value_type* fb() const noexcept { return fb_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォア・カラーの取得
			@return フォア・カラー
		*/
		//-----------------------------------------------------------------//
		const share_color& get_fore_color() const noexcept { return fore_color_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォア・カラーの設定
			@param[in]	c	フォア・カラー
		*/
		//-----------------------------------------------------------------//
		void set_fore_color(const share_color& c) noexcept { fore_color_ = c; }


		//-----------------------------------------------------------------//
		/*!
			@brief	バック・カラーの取得
			@return バック・カラー
		*/
		//-----------------------------------------------------------------//
		const share_color& get_back_color() const noexcept { return back_color_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	バック・カラーの設定
			@param[in]	c	バック・カラー
		*/
		//-----------------------------------------------------------------//
		void set_back_color(const share_color& c) noexcept { back_color_ = c; }


		//-----------------------------------------------------------------//
		/*!
			@brief	カラーの交換
		*/
		//-----------------------------------------------------------------//
		void swap_color() noexcept { std::swap(fore_color_, back_color_); }


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
            @brief  クリッピング領域の設定
            @param[in]  clip    クリッピング領域
        */
        //-----------------------------------------------------------------//
        void set_clip(const vtx::srect& clip) noexcept
        {
            clip_ = clip;
        }


        //-----------------------------------------------------------------//
        /*!
            @brief  クリッピング領域の取得
			@return クリッピング領域
        */
        //-----------------------------------------------------------------//
        const auto& get_clip() const noexcept { return clip_; }


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
			@param[in]	pos	開始点を指定
			@param[in]	c	カラー
            @return 範囲内なら「true」
		*/
		//-----------------------------------------------------------------//
		bool plot(const vtx::spos& pos, T c) noexcept
		{
			auto m = stipple_mask_;
			stipple_mask_ <<= 1;
			if(stipple_mask_ == 0) stipple_mask_ = 1;

			if((stipple_ & m) == 0) {
				return false;
			}
			if(static_cast<uint16_t>(pos.x) >= static_cast<uint16_t>(clip_.size.x)) return false;
			if(static_cast<uint16_t>(pos.y) >= static_cast<uint16_t>(clip_.size.y)) return false;
			fb_[pos.y * line_offset + pos.x] = c;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	点を取得する
			@param[in]	pos	開始点を指定
			@return	カラー
		*/
		//-----------------------------------------------------------------//
		value_type get_plot(const vtx::spos& pos) const noexcept
		{
			if(static_cast<uint16_t>(pos.x) >= static_cast<uint16_t>(GLC::width)) return -1;
			if(static_cast<uint16_t>(pos.y) >= static_cast<uint16_t>(GLC::height)) return -1;
			return fb_[pos.y * line_offset + pos.x];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	水平ラインを描画
			@param[in]	y	開始位置 Y
			@param[in]	x	水平開始位置
			@param[in]	w	水平幅
		*/
		//-----------------------------------------------------------------//
		void line_h(int16_t y, int16_t x, int16_t w) noexcept
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
			uint16_t* out = &fb_[y * line_offset + x];
			for(int16_t i = 0; i < w; ++i) {
				*out++ = fore_color_.rgb565;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	垂直ラインを描画
			@param[in]	x	開始位置 x
			@param[in]	y	垂直開始位置
			@param[in]	h	垂直幅
		*/
		//-----------------------------------------------------------------//
		void line_v(int16_t x, int16_t y, int16_t h) noexcept
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
			uint16_t* out = &fb_[y * line_offset + x];
			for(int16_t i = 0; i < h; ++i) {
				*out = fore_color_.rgb565;
				out += line_offset;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	四角を塗りつぶす
			@param[in]	org		開始位置
			@param[in]	size	サイズ
		*/
		//-----------------------------------------------------------------//
		void fill_box(const vtx::spos& org, const vtx::spos& size) noexcept
		{
			if(size.x <= 0 || size.y <= 0) return;

			for(int16_t yy = org.y; yy < (org.y + size.y); ++yy) {
				line_h(yy, org.x, size.x);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	全画面クリアをする
			@param[in]	c	クリアカラー
		*/
		//-----------------------------------------------------------------//
		void clear(const share_color& c) noexcept
		{
			uint32_t c32 = (static_cast<uint32_t>(c.rgb565) << 16) | c.rgb565;
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
#if 0
			for(auto y = 0; y < GLC::height; ++y) {
				T* p = &fb_[line_offset * y];
				for(auto x = 0; x < GLC::width; ++x) {
					*p++ = c;
				}
			}
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	線を描画する
			@param[in]	org	開始点Ｘ軸を指定
			@param[in]	end	終了点Ｘ軸を指定
		*/
		//-----------------------------------------------------------------//
		void line(const vtx::spos& org, const vtx::spos& end) noexcept
		{
			int16_t dx;
			int16_t dy;
			int16_t sx;
			int16_t sy;
			if(end.x >= org.x) {
				dx = end.x - org.x; sx = 1;
			} else {
				dx = org.x - end.x; sx = -1;
			}
			if(end.y >= org.y) {
				dy = end.y - org.y; sy = 1;
			} else {
				dy = org.y - end.y; sy = -1;
			}

			int16_t m = 0;
			vtx::spos pos = org;
			if(dx > dy) {
				for(int16_t i = 0; i <= dx; i++) {
					plot(pos, fore_color_.rgb565);
					m += dy;
					if(m >= dx) {
						m -= dx;
						pos.y += sy;
					}
					pos.x += sx;
				}
			} else {
				for(int16_t i = 0; i <= dy; i++) {
					plot(pos, fore_color_.rgb565);
					m += dx;
					if(m >= dy) {
						m -= dy;
						pos.x += sx;
					}
					pos.y += sy;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フレーム（線の箱）を描画する
			@param[in]	rect	短形を指定
		*/
		//-----------------------------------------------------------------//
		void frame(const vtx::srect& rect) noexcept
		{
			line_h(rect.org.y,  rect.org.x, rect.size.x);
			line_h(rect.org.y + rect.size.y - 1, rect.org.x, rect.size.x);
			line_v(rect.org.x,  rect.org.y  + 1, rect.size.y - 2);
			line_v(rect.org.x + rect.size.x - 1, rect.org.y + 1, rect.size.y - 2);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	角がラウンドしたフレーム（線）を描画する
			@param[in]	rect	短形を指定
			@param[in]	rad		ラウンドの半径
		*/
		//-----------------------------------------------------------------//
		void round_frame(const vtx::srect& rect, int16_t rad) noexcept
		{
			if(rect.size.x < (rad + rad) || rect.size.y < (rad + rad)) {
				if(rect.size.x < rect.size.y) rad = rect.size.x / 2;
				else rad = rect.size.y / 2;
			} 
			auto cen = rect.org + rad;
			auto ofs = rect.size - (rad * 2 - 2);
			line_h(rect.org.y, cen.x, ofs.x);
			line_h(rect.org.y + rect.size.y - 1, cen.x, ofs.x);
			line_v(rect.org.x, cen.y, ofs.y);
			line_v(rect.org.x + rect.size.x - 1, cen.y, ofs.y);
			vtx::spos pos(0, rad);
			int16_t p = (5 - rad * 4) / 4;
			circle_offset_(cen, pos, ofs);
			while(pos.x < pos.y) {
				pos.x++;
				if(p < 0) {
					p += 2 * pos.x + 1;
				} else {
					pos.y--;
					p += 2 * (pos.x - pos.y) + 1;
				}
				circle_offset_(cen, pos, ofs);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	角がラウンドした塗りつぶされた箱を描画する
			@param[in]	rect	短形を指定
			@param[in]	rad		ラウンドの半径
		*/
		//-----------------------------------------------------------------//
		void round_box(const vtx::srect& rect, int16_t rad) noexcept
		{
			if(rect.size.x < (rad + rad) || rect.size.y < (rad + rad)) {
				if(rect.size.x < rect.size.y) rad = rect.size.x / 2;
				else rad = rect.size.y / 2;
			}
			auto cen = rect.org + rad;
			auto ofs = rect.size - (rad * 2 - 2);
			int16_t yo = rect.size.y - rad * 2 - 2;
			fill_box(vtx::spos(rect.org.x, cen.y), vtx::spos(rect.size.x, yo));
			vtx::spos pos(0, rad);
			int16_t p = (5 - rad * 4) / 4;
			line_h(cen.y + ofs.y, cen.x - pos.y, pos.y + pos.y + 1 + ofs.x);
			line_h(cen.y + pos.y + yo + 1, cen.x - pos.x, pos.x + pos.x + ofs.x);
			while(pos.x < pos.y) {
				pos.x++;
				if(p < 0) {
					p += 2 * pos.x + 1;
				} else {
					// x` = x - 1
					line_h(cen.y - pos.y,         cen.x - pos.x + 1, pos.x + pos.x + ofs.x - 1);
					line_h(cen.y + pos.y + ofs.y, cen.x - pos.x + 1, pos.x + pos.x + ofs.x - 1);
					pos.y--;
					p += 2 * (pos.x - pos.y) + 1;
				}
				line_h(cen.y - pos.x,         cen.x - pos.y, pos.y + pos.y + ofs.x + 1);
				line_h(cen.y + pos.x + ofs.y, cen.x - pos.y, pos.y + pos.y + ofs.x + 1);
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
			@return 座標指定が不整合な場合「false」
		*/
		//-----------------------------------------------------------------//
		bool arc(int16_t x0, int16_t y0, int16_t xc, int16_t yc, int16_t x1, int16_t y1)
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
				plot(pos.x, pos.y, fore_color_.rgb565);
			} while(!cir.step()) ;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	円（線）を描画する
			@param[in]	cen	中心点
			@param[in]	rad	半径を指定
		*/
		//-----------------------------------------------------------------//
		void circle(const vtx::spos& cen, int16_t rad) noexcept
		{
			vtx::spos pos(0, rad);
			int16_t p = (5 - rad * 4) / 4;
			circle_pset_(cen, pos);
			while(pos.x < pos.y) {
				pos.x++;
				if(p < 0) {
					p += 2 * pos.x + 1;
				} else {
					pos.y--;
					p += 2 * (pos.x - pos.y) + 1;
				}
				circle_pset_(cen, pos);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	円を描画する
			@param[in]	cen	中心点
			@param[in]	rad	半径を指定
		*/
		//-----------------------------------------------------------------//
		void fill_circle(const vtx::spos& cen, int16_t rad) noexcept
		{
			int16_t x = 0;
			int16_t y = rad;
			int16_t p = (5 - rad * 4) / 4;
			line_h(cen.y, cen.x - y, y + y + 1);
			while(x < y) {
				x++;
				if(p < 0) {
					p += 2 * x + 1;
				} else {
					// x` = x - 1
					line_h(cen.y - y, cen.x - x + 1, x + x - 1);
					line_h(cen.y + y, cen.x - x + 1, x + x - 1);
					y--;
					p += 2 * (x - y) + 1;
				}
				line_h(cen.y - x, cen.x - y, y + y + 1);
				line_h(cen.y + x, cen.x - y, y + y + 1);
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
			@param[in]	pos		開始点を指定
			@param[in]	img		描画ソースのポインター
			@param[in]	ssz		描画ソースのサイズ
			@param[in]	back	背景を描画する場合「true」
		*/
		//-----------------------------------------------------------------//
		void draw_bitmap(const vtx::spos& pos, const void* img, const vtx::spos& ssz, bool back = false)
		noexcept {
			if(img == nullptr) return;

			const uint8_t* p = static_cast<const uint8_t*>(img);
			uint8_t k = 1;
			uint8_t c = *p++;
			vtx::spos loc = pos;
			for(uint8_t i = 0; i < ssz.y; ++i) {
				loc.x = pos.x;
				for(uint8_t j = 0; j < ssz.x; ++j) {
					if(c & k) plot(loc, fore_color_.rgb565);
					else if(back) plot(loc, back_color_.rgb565);
					k <<= 1;
					if(k == 0) {
						k = 1;
						c = *p++;
					}
					++loc.x;
				}
				++loc.y;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	モーションオブジェクトのサイズを取得
			@param[in]	src	描画オブジェクト
			@return サイズwを返す
		*/
		//-----------------------------------------------------------------//
		vtx::spos get_mobj_size(const void* src) const noexcept
		{
			vtx::spos sz(0);
			if(src != nullptr) {
				const uint8_t* p = static_cast<const uint8_t*>(src);
				sz.x = *p++;
				sz.y = *p;
			}
			return sz;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	モーションオブジェクトを描画する
			@param[in]	pos		開始点を指定
			@param[in]	src		描画オブジェクト
			@param[in]	back	背景を描画する場合「true」
		*/
		//-----------------------------------------------------------------//
		void draw_mobj(const vtx::spos& pos, const void* src, bool back) noexcept
		{
			if(src == nullptr) return;

			const uint8_t* p = static_cast<const uint8_t*>(src);
			vtx::spos ssz(p[0], p[1]);
			p += 2;
			draw_bitmap(pos, p, ssz, back);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	UTF-16 フォントの描画
			@param[in]	pos		描画位置
			@param[in]	code	UTF-16 コード
			@param[in]	back	背景を描画する場合「true」
		*/
		//-----------------------------------------------------------------//
		void draw_font_utf16(const vtx::spos& pos, uint16_t code, bool back) noexcept
		{
			if(pos.y <= -AFONT::height || pos.y >= GLC::height) {
				return;
			}
			if(code < 0x80) {
				if(pos.x <= -AFONT::width || pos.x >= GLC::width) {
					return;
				}
				vtx::spos ssz(AFONT::width, AFONT::height);
				draw_bitmap(pos, AFONT::get(code), ssz, back);
			} else {
				if(pos.x <= -KFONT::width || pos.x >= GLC::width) {
					return;
				}
				auto p = kfont_.get(code);
				if(p != nullptr) {
					vtx::spos ssz(KFONT::width, KFONT::height);
					draw_bitmap(pos, p, ssz, back);
				} else {
					vtx::spos ssz(AFONT::width, AFONT::height);
					draw_bitmap(pos, AFONT::get('['), ssz, back);
					vtx::spos loc(pos.x + AFONT::width, pos.y);
					draw_bitmap(loc, AFONT::get(']'), ssz, back);
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フォントの描画 (UTF-8)
			@param[in]	pos		描画位置
			@param[in]	cha		文字コード
			@param[in]	prop	プロポーショナルの場合「true」
			@param[in]	back	背景を描画する場合「true」
			@return 文字の幅 (X)
		*/
		//-----------------------------------------------------------------//
		int16_t draw_font(const vtx::spos& pos, char cha, bool prop = false,
			bool back = false) noexcept
		{
			int16_t w = 0;
			if(static_cast<uint8_t>(cha) < 0x80) {
				uint8_t code = static_cast<uint8_t>(cha);
				if(prop) {
					w = AFONT::get_kern(code);
				}
				draw_font_utf16(vtx::spos(pos.x + w, pos.y), code, back);
				if(prop) {
					w += AFONT::get_width(code);
				} else {
					w = AFONT::width;
				}
			} else {
				if(kfont_.injection_utf8(static_cast<uint8_t>(cha))) {
					auto code = kfont_.get_utf16();
					if(code >= 0x80) {
						draw_font_utf16(pos, code, back);
						w = KFONT::width;
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
			@param[in]	back	背景を描画する場合「true」
			@return 文字の最終座標 (X)
		*/
		//-----------------------------------------------------------------//
		int16_t draw_text(const vtx::spos& pos, const char* str, bool prop = false,
			bool back = false) noexcept
		{
			if(str == nullptr) return 0;

			auto p = pos;
			char ch;
			while((ch = *str++) != 0) {
				if(ch == '\n') {
					p.x = pos.x;
					p.y += font_height;
				} else {
					p.x += draw_font(p, ch, prop, back);
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
				x += draw_font(vtx::spos(x, GLC::height), ch, prop);
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
						swap_color();
						fill_box(x, y, xx - x, AFONT::height);
						swap_color();
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
				swap_color();
				fill_box(x, y, xx - x, AFONT::height);
				swap_color();
			}
			return xx;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ダイアログ表示（画面の中心に表示される）
			@param[in]	size	大きさ
			@param[in]	text	テキスト
		*/
		//-----------------------------------------------------------------//
		void draw_dialog(const vtx::spos& size, const char* text) noexcept
		{
			vtx::spos pos((GLC::width  - size.x) / 2, (GLC::height - size.y) / 2);
			set_fore_color(DEF_COLOR::White);
			frame(vtx::srect(pos, size));
 			set_fore_color(DEF_COLOR::Black);
			fill_box(pos + 1, size - 2);
			auto l = get_text_length(text);
			pos.x += (size.x - l) / 2;
			pos.y += (size.y - font_height) / 2;
			set_fore_color(DEF_COLOR::White);
			draw_text(pos, text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	標準ボタンの描画 @n
					・背景色は「back_color」が使われる。@n
					・フォントの描画色は「fore_color」が利用
			@param[in]	org		位置
			@param[in]	size	サイズ
			@param[in]	text	テキスト
		*/
		//-----------------------------------------------------------------//
		void draw_button(const vtx::spos& org, const vtx::spos& size, const char* text) noexcept
		{
			auto len = get_text_length(text);
			swap_color();
			fill_box(org, size);
			swap_color();
			draw_text(org + vtx::spos((size.x - len) / 2, (size.y - font_height) / 2), text);
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
			auto c = SHARE_COLOR::to_565(r, g, b);
			plot(x + ofs_.x, y + ofs_.y, c);			
		}
	};
}
