#pragma once
//=====================================================================//
/*!	@file
	@brief	RX65N/RX651 DRW2D マネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/afont.hpp"
#include "graphics/kfont.hpp"
#include "graphics/color.hpp"

#include "RX65x/drw2d.hpp"

#include "dave_base.h"
#include "dave_videomodes.h"
#include "dave_driver.h"

#include "common/vtx.hpp"

extern "C" {
	extern void drw_int_isr(void);	// drw2d library interrupt handler
};

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DRW2D 制御／マネージャー・クラス
		@param[in]	GLC		グラフィックス・コントローラー・クラス
		@param[in]	AFONT	ASCII フォント
		@param[in]	KFONT	漢字フォント
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GLC, class AFONT = graphics::afont_null, class KFONT = graphics::kfont_null>
	class drw2d_mgr {
	public:
		typedef uint16_t value_type;
		typedef graphics::def_color DEF_COLOR;
		typedef GLC glc_type;
		typedef AFONT afont_type;
		typedef KFONT kfont_type;
		static const int16_t font_height  = KFONT::height < AFONT::height
			? AFONT::height : KFONT::height;

	private:
		typedef device::DRW2D DRW;

		static const int16_t line_offset = (((GLC::width * sizeof(value_type)) + 63) & 0x7fc0) / sizeof(value_type);

		GLC&		glc_;

		KFONT&		kfont_;

		value_type*	fb_;

		uint32_t	stipple_;
		uint32_t	stipple_mask_;

		d2_device*	d2_;

		graphics::share_color	fore_color_;
		graphics::share_color	back_color_;
		vtx::srect	clip_;
		int16_t		pen_size_;
		int16_t		scale_;
		bool		set_fore_color_;
		bool		set_back_color_;
		bool		set_clip_;
		bool		start_frame_enable_;

		int32_t		last_error_;

		d2_color	clut_[256];


		static uint32_t get_mode_()
		{
			switch(GLC::PXT) {
			case graphics::pixel::TYPE::RGB888:
				return d2_mode_argb8888;
			case graphics::pixel::TYPE::RGB565:
				return d2_mode_rgb565;
			case graphics::pixel::TYPE::CLUT8:
				return d2_mode_i8;
			case graphics::pixel::TYPE::CLUT4:
				return d2_mode_i4;
			case graphics::pixel::TYPE::CLUT1:
				return d2_mode_i1;
			default:
				return d2_mode_rgb565;
			}
		}


		void setup_()
		{
			if(!set_fore_color_) {
				d2_setcolor(d2_, 0, fore_color_.rgba8.rgba);
				set_fore_color_ = true;
			}
			if(!set_back_color_) {
				d2_setcolor(d2_, 1, back_color_.rgba8.rgba);
				set_back_color_ = true;
			}
			if(!set_clip_) {
				d2_cliprect(d2_, clip_.org.x, clip_.org.y, clip_.size.x, clip_.size.y);
				set_clip_ = true;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
			@param[in]	glc	GLC クラスの参照
		*/
		//-----------------------------------------------------------------//
		drw2d_mgr(GLC& glc, KFONT& kfont) noexcept : glc_(glc), kfont_(kfont),
			fb_(static_cast<value_type*>(glc.get_fbp())),
			stipple_(-1), stipple_mask_(1),
			d2_(nullptr),
			fore_color_(DEF_COLOR::White), back_color_(DEF_COLOR::Black),
			clip_(0, 0, GLC::width, GLC::height),
			pen_size_(16), scale_(16),
			set_fore_color_(false), set_back_color_(false),
			set_clip_(false), start_frame_enable_(false),
			last_error_(D2_OK)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	ハードウェアーバージョンを取得
			@return ハードウェアーバージョン
		*/
		//-----------------------------------------------------------------//
		uint16_t get_version() const noexcept { return DRW::HWVER.REV(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	ハードウェアー仕様の表示
		*/
		//-----------------------------------------------------------------//
		void list_info() const noexcept
		{
			utils::format("REV:             0x%03X\n") % get_version();
			utils::format("Alpha Blend:       %d\n") % static_cast<uint16_t>(DRW::HWVER.ACBLD());
			utils::format("Clomakey:          %d\n") % static_cast<uint16_t>(DRW::HWVER.COLKEY());
			utils::format("Texture CLUT:      %s\n") % (DRW::HWVER.TEXCLUT256() ? "256" : "16");
			utils::format("RLE unit:          %d\n") % static_cast<uint16_t>(DRW::HWVER.RLEUNIT());
			utils::format("Texture CLUT func: %d\n") % static_cast<uint16_t>(DRW::HWVER.TEXCLUT());
			utils::format("Pefrmance CNT:     %d\n") % static_cast<uint16_t>(DRW::HWVER.PERFCNT());
			utils::format("Texture CASH:      %d\n") % static_cast<uint16_t>(DRW::HWVER.TXCACHE());
			utils::format("FB CASH:           %d\n") % static_cast<uint16_t>(DRW::HWVER.FBCACHE());
			utils::format("Display List R:    %d\n") % static_cast<uint16_t>(DRW::HWVER.DLR());
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			// DRW2D power management
			power_mgr::turn(DRW::get_peripheral());

			// initialization Dave2D
			d2_ = d2_opendevice(0);
			uint32_t init_flag = 0;
			d2_inithw(d2_, init_flag);

			icu_mgr::install_group_task(DRW::get_irq_vec(), drw_int_isr);
			icu_mgr::set_level(ICU::VECTOR::GROUPAL1, 2);

			clut_[0] = 0xff000000;
			clut_[1] = 0xffffffff;

			return true;
		}


		void start_frame() noexcept
		{
			start_frame_enable_ = true;
			d2_startframe(d2_);

			auto xs = GLC::width;
			auto ys = GLC::height;
			d2_framebuffer(d2_, fb_, xs, xs, ys, get_mode_());
			d2_cliprect(d2_, 0, 0, xs * 16, ys * 16);
			d2_settexclut(d2_, clut_);
		}


		void end_frame() noexcept
		{
			if(start_frame_enable_) {
				d2_endframe(d2_);
				start_frame_enable_ = false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フレームの同期
		*/
		//-----------------------------------------------------------------//
		void sync_frame() noexcept
		{
			if(d2_ == nullptr) {
				start();
			}
			end_frame();
			glc_.sync_vpos();
			start_frame();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	停止
		*/
		//-----------------------------------------------------------------//
		void stop() noexcept
		{
			d2_closedevice(d2_);
			d2_ = nullptr;

			icu_mgr::install_group_task(DRW::get_irq_vec(), nullptr);

			power_mgr::turn(DRW::get_peripheral(), false);
		}


		//-----------------------------------------------------------------//
        /*!
            @brief  フレームバッファのアドレスを返す
            @return フレームバッファ・アドレス
        */
        //-----------------------------------------------------------------//
        const value_type* fb() const noexcept { return fb_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	前面カラーの設定
			@param[in]	color	カラー
		*/
		//-----------------------------------------------------------------//
		void set_fore_color(const graphics::share_color& color) noexcept
		{
			fore_color_ = color;
			set_fore_color_ = false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	背面カラーの設定
			@param[in]	color	カラー
		*/
		//-----------------------------------------------------------------//
		void set_back_color(const graphics::share_color& color) noexcept
		{
			back_color_ = color;
			set_back_color_ = false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	クリッピング領域の設定
			@param[in]	clip	クリッピング領域
		*/
		//-----------------------------------------------------------------//
		void set_clip(const vtx::srect& clip) noexcept
		{
			clip_ = clip;
			set_clip_ = false;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  クリッピング領域の取得
            @return クリップ領域
        */
        //-----------------------------------------------------------------//
		const auto& get_clip() const noexcept { return clip_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  破線パターンの設定
            @param[in]  stipple 破線パターン
        */
        //-----------------------------------------------------------------//
		void set_stipple(uint32_t stipple = -1) noexcept {
			stipple_ = stipple;
			stipple_mask_ = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	点を描画する
			@param[in]	pos	開始点
			@param[in]	c	カラー
			@return 範囲内なら「true」
		*/
		//-----------------------------------------------------------------//
		bool plot(const vtx::spos& pos, value_type c) noexcept
		{
			auto m = stipple_mask_;
			stipple_mask_ <<= 1;
			if(stipple_mask_ == 0) stipple_mask_ = 1;

			if((stipple_ & m) == 0) {
				return false;
			}
			if(static_cast<uint16_t>(pos.x) >= static_cast<uint16_t>(GLC::width)) return false;
			if(static_cast<uint16_t>(pos.y) >= static_cast<uint16_t>(GLC::height)) return false;
			fb_[pos.y * line_offset + pos.x] = c;
			return true;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  点のカラーを取得する
            @param[in]  pos 開始点を指定
            @return カラー
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
			@brief	ペンサイズの設定
			@param[in]	size	ペンサイズ（1/16 pixel）
		*/
		//-----------------------------------------------------------------//
		void set_pen_size(int16_t size) noexcept { pen_size_ = size; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ペンサイズの取得
			@return ペンサイズ（1/16 pixel）
		*/
		//-----------------------------------------------------------------//
		auto get_pen_size() const noexcept { return pen_size_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	スケールの設定
			@param[in]	scale	スケール（等倍１６）
		*/
		//-----------------------------------------------------------------//
		void set_scale(int16_t scale = 16) noexcept { scale_ = scale; }


		//-----------------------------------------------------------------//
		/*!
			@brief	スケールの取得
			@return スケール（1/16 pixel）
		*/
		//-----------------------------------------------------------------//
		auto get_scale() const noexcept { return scale_; }


        //-----------------------------------------------------------------//
        /*!
            @brief  水平ラインを描画
            @param[in]  y   開始位置 Y
            @param[in]  x   水平開始位置
            @param[in]  w   水平幅
			@return エラー無い場合「true」
        */
        //-----------------------------------------------------------------//
        bool line_h(int16_t y, int16_t x, int16_t w) noexcept
		{
			setup_();
			last_error_ = d2_renderline(d2_, x * scale_, y * scale_,
				(x + w) * scale_, y * scale_, pen_size_, d2_le_exclude_none);
			return last_error_ == D2_OK;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  垂直ラインを描画
            @param[in]  x   開始位置 x
            @param[in]  y   垂直開始位置
            @param[in]  h   垂直幅
			@return エラー無い場合「true」
        */
        //-----------------------------------------------------------------//
        bool line_v(int16_t x, int16_t y, int16_t h) noexcept
		{
			setup_();
			last_error_ = d2_renderline(d2_, x * scale_, y * scale_,
				x * scale_, (y + h) * scale_, pen_size_, d2_le_exclude_none);
			return last_error_ == D2_OK;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  四角を塗りつぶす
            @param[in]  org     開始位置
            @param[in]  size    サイズ
			@return エラー無い場合「true」
        */
        //-----------------------------------------------------------------//
        bool fill_box(const vtx::spos& org, const vtx::spos& size) noexcept
		{
			setup_();
			last_error_ = d2_renderbox(d2_, org.x * scale_, org.y * scale_,
				size.x * scale_, size.y * scale_);
			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	全クリア
			@param[in]	col	クリアカラー
			@return エラー無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool clear(const graphics::share_color& col) noexcept
		{
			last_error_ = d2_clear(d2_, col.rgba8.rgba);
			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ライン描画（アンチエリアスされたライン）
			@param[in]	org		開始位置
			@param[in]	end		終端位置
			@return エラー無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool line(const vtx::spos& org, const vtx::spos& end) noexcept
		{
			setup_();
			last_error_ = d2_renderline(d2_, org.x * scale_, org.y * scale_,
				end.x * scale_, end.y * scale_, pen_size_, d2_le_exclude_none);
			return last_error_ == D2_OK;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  フレーム（線の箱）を描画する
            @param[in]  rect    短径を指定
			@return エラー無い場合「true」
        */
        //-----------------------------------------------------------------//
        bool frame(const vtx::srect& rect) noexcept
        {
            line_h(rect.org.y,  rect.org.x, rect.size.x);
            line_h(rect.org.y + rect.size.y - 1, rect.org.x, rect.size.x);
            line_v(rect.org.x,  rect.org.y  + 1, rect.size.y - 2);
            line_v(rect.org.x + rect.size.x - 1, rect.org.y + 1, rect.size.y - 2);
			return last_error_ == D2_OK;
        }





		//-----------------------------------------------------------------//
		/*!
			@brief	サークル描画
			@param[in]	org		中心位置
			@param[in]	r		半径
			@param[in]	w		幅（０の場合 fill）
			@return エラー無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool circle(const vtx::spos& org, int16_t r, int16_t w = 0) noexcept
		{
			setup_();
			last_error_ = d2_rendercircle(d2_, org.x * scale_, org.y * scale_,
				r * scale_, w * scale_);
			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	UTF-16 フォントの描画
			@param[in]	pos		描画位置
			@param[in]	cha		UTF-16 コード
		*/
		//-----------------------------------------------------------------//
		void draw_font_utf16(const vtx::spos& pos, uint16_t cha) noexcept
		{
			const uint8_t* src = nullptr;
			int16_t w;
			int16_t h;
			if(cha < 0x80) {
				src = AFONT::get(cha);
				w = AFONT::width;
				h = AFONT::height;
			} else {
				src = kfont_.get(cha);
				if(src == nullptr) {
					return;
				}
				w = KFONT::width;
				h = KFONT::height;
			}
			d2_setblitsrc(d2_, src, w, w, h, d2_mode_i1 | d2_mode_clut);
			d2_blitcopy(d2_, w, h,
				0, 0, w * 16, h * 16, pos.x * 16, pos.y * 16, d2_bf_filter);
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
			if(static_cast<uint8_t>(cha) < 0x80) {
				uint8_t code = static_cast<uint8_t>(cha);
				if(prop) {
					w = AFONT::get_kern(code);
				}
				draw_font_utf16(vtx::spos(pos.x + w, pos.y), code);
				if(prop) {
					w += AFONT::get_width(code);
				} else {
					w = AFONT::width;
				}
			} else {
				if(kfont_.injection_utf8(static_cast<uint8_t>(cha))) {
					auto code = kfont_.get_utf16();
					if(code >= 0x80) {
						draw_font_utf16(pos, code);
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
			@param[in]	str		文字列 (UTF-8)
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
					p.x += draw_font(p, ch, prop);
				}
			}
			return p.x;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	描画フラッシュ
		*/
		//-----------------------------------------------------------------//
		void flush() noexcept { d2_flushframe(d2_); }
	};
}
