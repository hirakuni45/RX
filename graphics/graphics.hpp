#pragma once
//=====================================================================//
/*!	@file
	@brief	グラフィックス・ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/pixel.hpp"
#include "graphics/color.hpp"
#include "graphics/font.hpp"
#include "common/intmath.hpp"
#include "common/circle.hpp"
#include "common/vtx.hpp"

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	レンダリング
		@param[in]	GLC		グラフィックス・コントローラー・クラス
		@param[in]	AFONT	ASCII フォント・クラス
		@param[in]	KFONT	漢字フォントクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GLC, class FONT = font_null>
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
		typedef FONT font_type;

		static const int16_t line_offset = (((GLC::width * sizeof(T)) + 63) & 0x7fc0) / sizeof(T);

	private:
		T*			fb_;

		FONT& 		font_;

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
		render(GLC& glc, FONT& font) noexcept : glc_(glc), font_(font),
			fore_color_(255, 255, 255), back_color_(0, 0, 0),
			clip_(0, 0, GLC::width, GLC::height),
			stipple_(-1), stipple_mask_(1), ofs_(0)
		{ fb_ = static_cast<T*>(glc_.get_fbp()); }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォントの参照を返す
			@return フォントの参照
		*/
		//-----------------------------------------------------------------//
		FONT& at_font() { return font_; }


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
					※DRW2D エンジン互換性の為に用意
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
			@param[in]	vsync	垂直同期を行わない場合「false」
		*/
		//-----------------------------------------------------------------//
		void sync_frame(bool vsync = true) noexcept
		{
			if(vsync) glc_.sync_vpos();
		}


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
			@brief	点を描画する
			@param[in]	pos	開始点を指定
			@param[in]	c	カラー
            @return 範囲内なら「true」
		*/
		//-----------------------------------------------------------------//
		bool fast_plot(const vtx::spos& pos, T c) noexcept
		{
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
			@param[in]	y	開始位置Ｘ
			@param[in]	x	開始位置Ｙ
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
			@param[in]	x	開始位置Ｘ
			@param[in]	y	開始位置Ｙ
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
			@param[in]	rect	配置
		*/
		//-----------------------------------------------------------------//
		void fill_box(const vtx::srect& rect) noexcept
		{
			if(rect.size.x <= 0 || rect.size.y <= 0) return;

			for(int16_t yy = rect.org.y; yy < (rect.org.y + rect.size.y); ++yy) {
				line_h(yy, rect.org.x, rect.size.x);
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
			if(rect.size.x < (rad * 2) || rect.size.y < (rad * 2)) {
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
			@param[in]	up		上部をラウンドする
			@param[in]	dn		下部をラウンドする
		*/
		//-----------------------------------------------------------------//
		void round_box(const vtx::srect& rect, int16_t rad, bool up = true, bool dn = true) noexcept
		{
			if(rect.size.x < (rad + rad) || rect.size.y < (rad + rad)) {
				if(rect.size.x < rect.size.y) rad = rect.size.x / 2;
				else rad = rect.size.y / 2;
			}
			auto cn = rect.org + rad;
			auto of = rect.size - (rad * 2);
			{
				auto yy = rect.org.y;
				auto sz = rect.size.y;
				if(up) { sz -= rad; yy += rad; }
				if(dn) sz -= rad;
				fill_box(vtx::srect(rect.org.x, yy, rect.size.x, sz));
			}
			vtx::spos po(0, rad);
			int16_t p = (5 - rad * 4) / 4;
			of -= 1;
///			line_h(cen.y, cen.x - pos.y, pos.y + pos.y + ofs.x + 1);
			while(po.x < po.y) {
				po.x++;
				if(p < 0) {
					p += 2 * po.x + 1;
				} else {
					// x` = x - 1
					if(up) line_h(cn.y - po.y,        cn.x - po.x + 1, po.x + po.x + of.x - 1);
					if(dn) line_h(cn.y + po.y + of.y, cn.x - po.x + 1, po.x + po.x + of.x - 1);
					po.y--;
					p += 2 * (po.x - po.y) + 1;
				}
				if(up) line_h(cn.y - po.x,        cn.x - po.y, po.y + po.y + of.x + 1);
				if(dn) line_h(cn.y + po.x + of.y, cn.x - po.y, po.y + po.y + of.x + 1);
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
			@param[in]	cen	中心位置
			@param[in]	rad	半径
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
					if(c & k) fast_plot(loc, fore_color_.rgb565);
					else if(back) fast_plot(loc, back_color_.rgb565);
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
			if(pos.y <= -FONT::height || pos.y >= GLC::height) {
				return;
			}
			if(code < 0x80) {
				if(pos.x <= -FONT::a_type::width || pos.x >= GLC::width) {
					return;
				}
				vtx::spos ssz(FONT::a_type::width, FONT::a_type::height);
				draw_bitmap(pos, FONT::a_type::get(code), ssz, back);
			} else {
				if(pos.x <= -FONT::k_type::width || pos.x >= GLC::width) {
					return;
				}
				auto p = font_.at_kfont().get(code);
				if(p != nullptr) {
					vtx::spos ssz(FONT::k_type::width, FONT::k_type::height);
					draw_bitmap(pos, p, ssz, back);
				} else {
					vtx::spos ssz(FONT::a_type::width, FONT::a_type::height);
					draw_bitmap(pos, FONT::a_type::get('['), ssz, back);
					vtx::spos loc(pos.x + FONT::a_type::width, pos.y);
					draw_bitmap(loc, FONT::a_type::get(']'), ssz, back);
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
					w = FONT::a_type::get_kern(code);
				}
				draw_font_utf16(vtx::spos(pos.x + w, pos.y), code, back);
				if(prop) {
					w += FONT::a_type::get_width(code);
				} else {
					w = FONT::a_type::width;
				}
			} else {
				if(font_.at_kfont().injection_utf8(static_cast<uint8_t>(cha))) {
					auto code = font_.at_kfont().get_utf16();
					if(code >= 0x80) {
						draw_font_utf16(pos, code, back);
						w = FONT::k_type::width;
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
					p.y += FONT::height;
				} else {
					p.x += draw_font(p, ch, prop, back);
				}
			}
			return p.x;
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
						fill_box(x, y, xx - x, FONT::a_type::height);
						swap_color();
						x = xx;
						fill = true;
					} else {
						fill = false;
					}
					if(prop) {
						xx += FONT::a_type::get_kern(ch);
						xx += FONT::a_type::get_width(ch);
					} else {
						xx += FONT::a_type::width;
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
						xx += FONT::k_type::width;
					} else if(cnt < 0) {
						code = 0;
					}
				}
			}
			if(!fill) {
				swap_color();
				fill_box(x, y, xx - x, FONT::a_type::height);
				swap_color();
			}
			return xx;
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
			plot(vtx::spos(x + ofs_.x, y + ofs_.y), c);			
		}
	};
}
