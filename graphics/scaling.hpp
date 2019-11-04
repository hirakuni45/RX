#pragma once
//=====================================================================//
/*!	@file
	@brief	スケーリング（拡大、縮小）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include <cmath>
#include "common/vtx.hpp"
#include "graphics/color.hpp"
// #include <unordered_map>

namespace img {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	スケーリング・クラス
		@param[in]	RENDER	レンダー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER>
	class scaling {

		RENDER&		render_;

		struct xy_pad {
			uint32_t	r;
			uint32_t	g;
			uint32_t	b;
			uint32_t	cnt;
		};

//		typedef std::unordered_map<uint32_t, xy_pad> MAP;
//		MAP			map_;

#if 0
		static float sinc_(float l)
		{
			return std::sin(vtx::get_pi<float>() * l) / (vtx::get_pi<float>() * l);
		}


		static float lanczos_(float d, float n)
		{
			if(d == 0.0f) {
				return 1.0f;
			} else if(std::abs(d) >= n) {
				return 0.0f;
			} else {
				return sinc_(d) * sinc_(d / n);
			}
		}


		float lanczos_tbl_[(12 + 1) * (12 + 1)];
		float lanczos_n_;
		// -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0
		void init_lanczos_(float n)
		{
			if(lanczos_n_ == n) return;

			float y = -3.0f;
			for(int i = 0; i < (12 + 1); ++i) {
				float yl = lanczos_(y, n);
				float x = -3.0f;
				for(int j = 0; j < (12 + 1); ++j) {
					float xl = lanczos_(x, n);
					lanczos_tbl_[i * (12 + 1) + j] = xl * yl;
					x += 0.5f;
				}
				y += 0.5f;
			}
			lanczos_n_ = n;
		}


		float lanczos_t_(float x, float y, float n)
		{
			int i = static_cast<int>(y * 2.0f);
			i += 6;
			int j = static_cast<int>(x * 2.0f);
			j += 6;
			if(i >= 0 && i < (12 + 1) && j >= 0 && j < (12 + 1)) {
				return lanczos_tbl_[i * (12 + 1) + j];
			} else {
				return lanczos_(x, n) * lanczos_(y, n);
			}
		}
#endif

#if 0
	static void color_div_(const rgbaf& col, float total, rgba8& c)
	{
		rgbaf cc;
		if(total != 0.0f) {
			float sf = 1.0f / total;
			cc.r = col.r * sf;
			cc.g = col.g * sf;
			cc.b = col.b * sf;
			cc.a = col.a * sf;
		} else {
			cc = col;
		}

		if(cc.r < 0.0f) {
			c.r = 0;
		} else if(cc.r > 255.0f) {
			c.r = 255;
		} else {
			c.r = static_cast<unsigned char>(cc.r);
		}

		if(cc.g < 0.0f) {
			c.g = 0;
		} else if(cc.g > 255.0f) {
			c.g = 255;
		} else {
			c.g = static_cast<unsigned char>(cc.g);
		}

		if(cc.b < 0.0f) {
			c.b = 0;
		} else if(cc.b > 255.0f) {
			c.b = 255;
		} else {
			c.b = static_cast<unsigned char>(cc.b);
		}

		if(cc.a < 0.0f) {
			c.a = 0;
		} else if(cc.a > 255.0f) {
			c.a = 255;
		} else {
			c.a = static_cast<unsigned char>(cc.a);
		}
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	画像をリサイズする（lanczos-3 アルゴリズム）
		@param[in]	src	ソースのイメージ
		@param[out]	dst	リサイズイメージ
		@param[in]	scale	スケール・ファクター
	*/
	//-----------------------------------------------------------------//
	void resize_image(const i_img* src, img_rgba8& dst, float scale)
	{
		if(scale <= 0.0f) return;

		int sw = src->get_size().x;
		int sh = src->get_size().y;
		int dw = static_cast<int>(static_cast<float>(sw) * scale);
		int dh = static_cast<int>(static_cast<float>(sh) * scale);
		dst.create(vtx::spos(dw, dh), src->test_alpha());

		float n = 3.0f;
		init_lanczos_(n);

		float scn = 1.0f / scale;
		if(scale > 1.0f) {
			vtx::spos out;
			for(out.y = 0; out.y < dh; ++out.y) {
				float yy = (static_cast<float>(out.y) + 0.5f) * scn;
				int ys = static_cast<int>(yy - n);
				if(ys < 0) ys = 0;
				int ye = static_cast<int>(yy + n);
				if(ye > (sh - 1)) ye = sh - 1;
				for(out.x = 0; out.x < dw; ++out.x) {
					float xx = (static_cast<float>(out.x) + 0.5f) * scn;
					int xs = static_cast<int>(xx - n);
					if(xs < 0) xs = 0;
					int xe = static_cast<int>(xx + n);
					if(xe > (sw - 1)) xe = sw - 1;

					rgbaf col(0.0f);
					float weight_total = 0.0f;
					vtx::spos pos;
					for(pos.y = ys; pos.y <= ye; ++pos.y) {
						float yl = fabs((pos.y + 0.5f) - yy);
						for(pos.x = xs; pos.x <= xe; ++pos.x) {
							float xl = std::abs((static_cast<float>(pos.x) + 0.5f) - xx);
							float weight = lanczos_t_(xl, yl, n);
							rgba8 c;
							src->get_pixel(pos, c);
							col.r += c.r * weight;
							col.g += c.g * weight;
							col.b += c.b * weight;
							col.a += c.a * weight;
							weight_total += weight;
						}
					}
					rgba8 c;
					color_div_(col, weight_total, c);
					dst.put_pixel(out, c);
				}
			}
		} else {
			vtx::spos out;
			for(out.y = 0; out.y < dh; ++out.y) {
				float yy = static_cast<float>(out.y) + 0.5f;
				int ys = static_cast<int>((yy - n) * scn);
				if(ys < 0) ys = 0;
				int ye = static_cast<int>((yy + n) * scn);
				if(ye > (sh - 1)) ye = sh - 1;
				for(out.x = 0; out.x < dw; ++out.x) {
					float xx = static_cast<float>(out.x) + 0.5f;
					int xs = static_cast<int>((xx - n) * scn);
					if(xs < 0) xs = 0;
					int xe = static_cast<int>((xx + n) * scn);
					if(xe > (sw - 1)) xe = sw - 1;

					rgbaf col(0.0f);
					float weight_total = 0.0f;
					vtx::spos pos;
					for(pos.y = ys; pos.y <= ye; ++pos.y) {
						float yl = std::abs(((static_cast<float>(pos.y) + 0.5f) * scale) - yy);
						for(pos.x = xs; pos.x <= xe; ++pos.x) {
							float xl = std::abs(((static_cast<float>(pos.x) + 0.5f) * scale) - xx);
							float weight = lanczos_t_(xl, yl, n);
							rgba8 c;
							src->get_pixel(pos, c);
							col.r += static_cast<float>(c.r) * weight;
							col.g += static_cast<float>(c.g) * weight;
							col.b += static_cast<float>(c.b) * weight;
							col.a += static_cast<float>(c.a) * weight;
							weight_total += weight;
						}
					}
					rgba8 c;
					color_div_(col, weight_total, c);
					dst.put_pixel(out, c);
				}
			}
		}
	}
#endif

		vtx::spos	ofs_;
		struct step_t {
			int32_t	up;
			int32_t	dn;
			step_t(uint32_t u = 1, uint32_t d = 1) noexcept : up(u), dn(d) { }
		};
		step_t		scale_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
			@param[in]	render	レンダークラス（参照）
		*/
		//-----------------------------------------------------------------//
		scaling(RENDER& render) noexcept : render_(render),
//			lanczos_n_(0.0f),
			ofs_(0), scale_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	オフセットを設定
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		void set_offset(const vtx::spos& ofs = vtx::spos(0)) noexcept { ofs_ = ofs; }


		//-----------------------------------------------------------------//
		/*!
			@brief	スケールを設定
			@param[in]	up		分子
			@param[in]	dn		分母
		*/
		//-----------------------------------------------------------------//
		void set_scale(uint32_t up = 1, uint32_t dn = 1) noexcept { scale_ = step_t(up, dn); }


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
		void operator() (int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept
		{
			if(a == 0) return;

			auto sc = graphics::share_color(r, g, b);
			if(scale_.up < scale_.dn) {
				if(sc.rgb565 == 0) sc = graphics::share_color(0, 0, 1);
				auto xx = x * scale_.up / scale_.dn;
				auto yy = y * scale_.up / scale_.dn;
				auto rc = render_.get_plot(vtx::spos(xx + ofs_.x, yy + ofs_.y));
				if(rc == 0) {
					render_.plot(vtx::spos(xx + ofs_.x, yy + ofs_.y), sc.rgb565);
				} else {
					if(a == 255) {
						auto nc = graphics::share_color::color_sum(sc.rgb565, rc);
						render_.plot(vtx::spos(xx + ofs_.x, yy + ofs_.y), nc);
					} else {
						auto ac = graphics::share_color::conv_rgba8(rc);
						auto t = graphics::share_color::blend(ac, graphics::rgba8_t(r, g, b, a));
						auto dc = graphics::share_color(t.r, t.g, t.b);
						render_.plot(vtx::spos(x + ofs_.x, y + ofs_.y), dc.rgb565);
					}
				}
			} else if(scale_.up > scale_.dn) {
				auto d  = (scale_.up + (scale_.dn - 1)) / scale_.dn;
				auto xx = x * scale_.up / scale_.dn;
				auto yy = y * scale_.up / scale_.dn;
				render_.set_fore_color(sc);
				render_.fill_box(vtx::srect(xx + ofs_.x, yy + ofs_.y, d, d));
			} else {
				if(a == 255) {
					render_.plot(vtx::spos(x + ofs_.x, y + ofs_.y), sc.rgb565);
				} else {
					auto rc = render_.get_plot(vtx::spos(x + ofs_.x, y + ofs_.y));
					auto ac = graphics::share_color::conv_rgba8(rc);
					auto t = graphics::share_color::blend(ac, graphics::rgba8_t(r, g, b, a));
					auto dc = graphics::share_color(t.r, t.g, t.b);
					render_.plot(vtx::spos(x + ofs_.x, y + ofs_.y), dc.rgb565);
				}
			}
#if 0
			uint32_t key = static_cast<uint16_t>(xx) | (static_cast<uint16_t>(yy) << 16);
			auto it = map_.find(key);
			if(it != map_.end()) {
//				it->first.r += r;
//				it->first.g += g;
//				it->first.b += b;
//				++it->first.cnt;
//				if(it->first.cnt >= 4) {
//					auto c = RENDER::COLOR::rgb(r, g, b);
//					render_.plot(xx + ofs_.x, yy + ofs_.y, c);					
//				}
			} else {
				map_.emplace(r, g, b, 1);
			}
#endif
		}
	};
}
