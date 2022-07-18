#pragma once
//=====================================================================//
/*!	@file
	@brief	RX65N/RX651 DRW2D マネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/color.hpp"
#include "RX600/drw2d.hpp"

#include "dave_base.h"
#include "dave_videomodes.h"
#include "dave_driver.h"

#include "common/vtx.hpp"

///#include "drw2d/box.hpp"

extern "C" {
	extern void drw_int_isr(void);	// drw2d library interrupt handler
};

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DRW2D 制御／マネージャー・クラス
		@param[in]	GLC		グラフィックス・コントローラー・クラス
		@param[in]	FONT	フォント・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GLC, class FONT>
	class drw2d_mgr {
	public:
		typedef uint16_t value_type;
		typedef graphics::def_color DEF_COLOR;
		typedef graphics::share_color COLOR;
		typedef GLC glc_type;
		typedef FONT font_type;

	private:
		typedef device::DRW2D DRW;

		GLC&		glc_;

		FONT&		font_;

		value_type*	fb_;

		uint32_t	stipple_;
		uint32_t	stipple_mask_;

		d2_device*	d2_;

		COLOR		fore_color_;
		COLOR		back_color_;
		vtx::srect	clip_;
		int16_t		pen_size_;
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


		void setup_(bool texture)
		{
#if 0
			if(texture) {
				d2_setfillmode(d2_, d2_fm_texture);
				return;
			}
			if(!set_fore_color_) {
				d2_setcolor(d2_, 0, fore_color_.rgba8.rgba);
				set_fore_color_ = true;
			}
			if(!set_back_color_) {
				d2_setcolor(d2_, 1, back_color_.rgba8.rgba);
				set_back_color_ = true;
			}
			if(!set_clip_) {
				d2_cliprect(d2_, clip_.org.x, clip_.org.y, clip_.end_x(), clip_.end_y());
				set_clip_ = true;
			}
			d2_setfillmode(d2_, d2_fm_color);
#else
			if(!set_fore_color_) {
				d2_setcolor(d2_, 0, fore_color_.rgba8.rgba);
				set_fore_color_ = true;
			}
			if(!set_back_color_) {
				d2_setcolor(d2_, 1, back_color_.rgba8.rgba);
				set_back_color_ = true;
			}
			if(!set_clip_) {
				d2_cliprect(d2_, clip_.org.x, clip_.org.y, clip_.end_x(), clip_.end_y());
				set_clip_ = true;
			}
			if(texture) {
				d2_setfillmode(d2_, d2_fm_texture);
			} else {
				d2_setfillmode(d2_, d2_fm_color);
			}
#endif
		}


		void setup_stipple_(const vtx::spos& d)
		{
			if(stipple_ != 0xffffffff) {
				d2_setpatternsize(d2_, 8);
//				d2_setpatternalpha(d2_, 0, 255);
//				d2_setpatternalpha(d2_, 1, 255);
				d2_setpatternparam(d2_, 0, 0, d.x, d.y);
				d2_setpattern(d2_, stipple_);
  				d2_setfillmode(d2_, d2_fm_pattern);
			}
		}


		void arc_(const vtx::spos& cen, int16_t rad, int16_t w, const vtx::spos& n1, const vtx::spos& n2, uint32_t f = 0)
		{
			d2_renderwedge(d2_, cen.x << 4, cen.y << 4, rad << 4, w,
				n1.x << 16, n1.y << 16, n2.x << 16, n2.y << 16, f);
		}


		void start_frame_() noexcept
		{
			start_frame_enable_ = true;
			d2_startframe(d2_);

			fb_ = static_cast<value_type*>(glc_.get_fbp());

			auto xs = GLC::width;
			auto ys = GLC::height;
			d2_framebuffer(d2_, fb_, xs, xs, ys, get_mode_());
			d2_cliprect(d2_, 0, 0, xs, ys);
//			d2_settexclut(d2_, clut_);
		}


		void end_frame_() noexcept
		{
			if(start_frame_enable_) {
				d2_endframe(d2_);
				start_frame_enable_ = false;
			}
		}


		void draw_bitmapn_(const vtx::spos& pos, const void* src, const vtx::spos& ssz, bool alpha, int16_t pitch, d2_u32 mode) noexcept
		{
			int16_t w = ssz.x;
			int16_t h = ssz.y;
			if(pitch == 0) pitch = w;
			d2_setblitsrc(d2_, src, pitch, w, h, mode | d2_mode_clut);
			auto copyflag = d2_bf_filter;
			if(alpha) copyflag |= d2_bf_usealpha;
			d2_blitcopy(d2_, w, h,
				0, 0, w * 16, h * 16, pos.x * 16, pos.y * 16, copyflag);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
			@param[in]	glc		GLC クラスの参照
			@param[in]	font	フォントクラス参照
		*/
		//-----------------------------------------------------------------//
		drw2d_mgr(GLC& glc, FONT& font) noexcept : glc_(glc), font_(font),
			fb_(static_cast<value_type*>(glc.get_fbp())),
			stipple_(-1), stipple_mask_(1),
			d2_(nullptr),
			fore_color_(DEF_COLOR::White), back_color_(DEF_COLOR::Black),
			clip_(0, 0, GLC::width, GLC::height),
			pen_size_(16),
			set_fore_color_(false), set_back_color_(false),
			set_clip_(false), start_frame_enable_(false),
			last_error_(D2_OK),
			clut_{ 0 }
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	漢字フォントの参照を返す
			@return 漢字フォントの参照
		*/
		//-----------------------------------------------------------------//
		FONT& at_font() { return font_; }


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
			power_mgr::turn(DRW::PERIPHERAL);

			// initialization Dave2D
			d2_ = d2_opendevice(0);
			uint32_t init_flag = 0;
			d2_inithw(d2_, init_flag);

			icu_mgr::install_group_task(DRW::IVEC, drw_int_isr);
			icu_mgr::set_level(ICU::VECTOR::GROUPAL1, 2);

			clut_[0] = 0xff000000;
			clut_[1] = 0xffffffff;

			start_frame_();
			d2_settexclut(d2_, clut_);
			end_frame_();

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
			if(d2_ == nullptr) {
				start();
			}
			end_frame_();
			if(vsync) glc_.sync_vpos();
			start_frame_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ダブルバッファが有効か検査
			@return ダブルバッファが有効なら「true」
		*/
		//-----------------------------------------------------------------//
		bool is_double_buffer() const noexcept { return glc_.is_double_buffer(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	フレームバッファ、フリッピング
		*/
		//-----------------------------------------------------------------//
		void flip() noexcept
		{
			if(glc_.is_double_buffer()) {
				glc_.flip();
			}
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

			icu_mgr::install_group_task(DRW::IVEC, nullptr);

			power_mgr::turn(DRW::PERIPHERAL, false);
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
			@brief	フォア・カラーの取得
			@return フォア・カラー
		*/
		//-----------------------------------------------------------------//
		const auto& get_fore_color() const noexcept { return fore_color_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	前面カラーの設定
			@param[in]	color	カラー
		*/
		//-----------------------------------------------------------------//
		void set_fore_color(const COLOR& color) noexcept
		{
			fore_color_ = color;
			set_fore_color_ = false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	バック・カラーの取得
			@return バック・カラー
		*/
		//-----------------------------------------------------------------//
		const auto& get_back_color() const noexcept { return back_color_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	背面カラーの設定
			@param[in]	color	カラー
		*/
		//-----------------------------------------------------------------//
		void set_back_color(const COLOR& color) noexcept
		{
			back_color_ = color;
			set_back_color_ = false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  カラーの交換
		*/
		//-----------------------------------------------------------------//
		void swap_color() noexcept
		{
			std::swap(fore_color_, back_color_);
			std::swap(clut_[0], clut_[1]);
			set_fore_color_ = false;
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
			fb_[pos.y * GLC::line_width + pos.x] = c;
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
            return fb_[pos.y * GLC::line_width + pos.x];
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
            @brief  水平ラインを描画
            @param[in]  y   開始位置 Y
            @param[in]  x   水平開始位置
            @param[in]  w   水平幅
			@return エラー無い場合「true」
        */
        //-----------------------------------------------------------------//
        bool line_h(int16_t y, int16_t x, int16_t w) noexcept
		{
			setup_(false);
			setup_stipple_(vtx::spos(128, 0));
			last_error_ = d2_renderline(d2_, x << 4, y << 4, (x + w - 1) << 4, y << 4,
				pen_size_, d2_le_exclude_none);
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
			setup_(false);
			setup_stipple_(vtx::spos(0, 128));
			last_error_ = d2_renderline(d2_, x << 4, y << 4, x << 4, (y + h - 1) << 4,
				pen_size_, d2_le_exclude_none);
			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  四角を塗りつぶす
			@param[in]	rect	配置
			@return エラー無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool fill_box(const vtx::srect& rect) noexcept
		{
			setup_(false);
			last_error_ = d2_renderbox(d2_, rect.org.x << 4, rect.org.y << 4,
				rect.size.x << 4, rect.size.y << 4);
			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	全クリア
			@param[in]	col	クリアカラー
			@return エラー無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool clear(const COLOR& col) noexcept
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
		bool line_d(const vtx::spos& org, const vtx::spos& end) noexcept
		{
			setup_(false);
			// setup_stipple_();
			last_error_ = d2_renderline(d2_, org.x, org.y, end.x, end.y,
				pen_size_, d2_le_exclude_none);
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
			setup_(false);
			// setup_stipple_();
			last_error_ = d2_renderline(d2_, org.x << 4, org.y << 4, end.x << 4, end.y << 4,
				pen_size_, d2_le_exclude_none);
			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	三角形の描画
			@param[in]	p0		頂点０
			@param[in]	p1		頂点１
			@param[in]	p2		頂点２
			@return エラー無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool triangle_d(const vtx::spos& p0, const vtx::spos& p1, const vtx::spos& p2, bool texture = false) noexcept
		{
			setup_(texture);
			last_error_ = d2_rendertri(d2_, p0.x, p0.y, p1.x, p1.y, p2.x, p2.y,
				d2_le_exclude_none);
			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	四角形の描画
			@param[in]	p0		頂点０
			@param[in]	p1		頂点１
			@param[in]	p2		頂点２
			@param[in]	p3		頂点３
			@return エラー無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool quad_d(const vtx::spos& p0, const vtx::spos& p1, const vtx::spos& p2, const vtx::spos& p3, bool texture = false) noexcept
		{
			setup_(texture);
			last_error_ = d2_renderquad(d2_, p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y,
				d2_le_exclude_none);
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
            @brief  角がラウンドしたフレーム（線）を描画する
            @param[in]  rect    短形を指定
            @param[in]  rad     ラウンドの半径
			@return エラー無い場合「true」
        */
        //-----------------------------------------------------------------//
        bool round_frame(const vtx::srect& rect, int16_t rad) noexcept
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

			auto end = rect.end() - rad - 1;
			arc_(cen, rad, 32, vtx::spos(-1, 0), vtx::spos(0, -1));
			arc_(vtx::spos(end.x, cen.y), rad, 32, vtx::spos(0, -1), vtx::spos(1, 0));
			arc_(end, rad, 32, vtx::spos(1, 0), vtx::spos(0, 1));
			arc_(vtx::spos(cen.x, end.y), rad, 32, vtx::spos(0, 1), vtx::spos(-1, 0));

			return last_error_ == D2_OK;
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
            if(rect.size.x < (rad * 2) || rect.size.y < (rad * 2)) {
                if(rect.size.x < rect.size.y) rad = rect.size.x / 2;
                else rad = rect.size.y / 2;
            }
            auto cen = rect.org + rad;
			auto len = rect.size - (rad * 2);
			setup_(false);
			auto yo = rect.org.y;
			auto yl = len.y;
			if(up) {
				d2_renderbox(d2_, cen.x << 4, rect.org.y << 4, len.x << 4, rad << 4);
				yo += rad;
			} else {
				yl += rad;
			}
			if(!dn) {
				yl += rad;
			}
			d2_renderbox(d2_, rect.org.x << 4, yo << 4, rect.size.x << 4, yl << 4);
			auto end = rect.end() - rad - 1;
			if(dn) {
				d2_renderbox(d2_, cen.x << 4, (end.y + 1) << 4, len.x << 4, rad << 4);
			}

//			uint32_t f = d2_edge0_shared | d2_edge1_shared;
			++rad;
			if(up) {
				arc_(cen, rad, 0, vtx::spos(-1, 0), vtx::spos(0, -1));
				arc_(vtx::spos(end.x, cen.y), rad, 0, vtx::spos(0, -1), vtx::spos(1, 0));
			}
			if(dn) {
				arc_(end, rad, 0, vtx::spos(1, 0), vtx::spos(0, 1));
				arc_(vtx::spos(cen.x, end.y), rad, 0, vtx::spos(0, 1), vtx::spos(-1, 0));
			}
//			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	円（線）を描画する
			@param[in]	cen	中心位置
			@param[in]	rad	半径
			@param[in]	w	線幅（０の場合 fill）
			@return エラー無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool circle(const vtx::spos& cen, int16_t rad, int16_t w = 1) noexcept
		{
			setup_(false);
			last_error_ = d2_rendercircle(d2_, cen.x << 4, cen.y << 4, rad << 4, w << 4);
			return last_error_ == D2_OK;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  円を描画する
            @param[in]  cen 中心点
            @param[in]  rad 半径を指定
			@return エラー無い場合「true」
        */
        //-----------------------------------------------------------------//
        bool fill_circle(const vtx::spos& cen, int16_t rad) noexcept
		{
			setup_(false);
			last_error_ = d2_rendercircle(d2_, cen.x << 4, cen.y << 4, rad << 4, 0);
			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	移動
			@param[in]	src		ソース位置と大きさ
			@param[in]	dst		転送位置
		*/
		//-----------------------------------------------------------------//
		void move(const vtx::srect& src, const vtx::spos& dst) noexcept
		{
			d2_utility_fbblitcopy(d2_, src.size.x, src.size.y, src.org.x, src.org.y, dst.x, dst.y,
				d2_bf_filter);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  全体スクロール
			@param[in]  h       スクロール高さ（+up、-down）
		*/
		//-----------------------------------------------------------------//
		void scroll(int16_t h) noexcept
		{
			if(h > 0) {
				move(vtx::srect(0, h, GLC::width, GLC::height - h), vtx::spos(0, 0));
			} else if(h < 0) {
				h = -h;
				move(vtx::srect(0, 0, GLC::width, GLC::height - h), vtx::spos(0, h));
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

			const uint8_t* src = static_cast<const uint8_t*>(img);
			int16_t w = ssz.x;
			int16_t h = ssz.y;

			if(!set_clip_) {
				d2_cliprect(d2_, clip_.org.x, clip_.org.y, clip_.end_x(), clip_.end_y());
				set_clip_ = true;
			}

			auto c0 = clut_[0];
			auto c1 = clut_[1];
			clut_[0] = back_color_.rgba8.rgba;
			auto copyflag = d2_bf_filter;
			if(!back) {
				clut_[0] &= 0xffffff;
				copyflag |= d2_bf_usealpha;
			}
			clut_[1] = fore_color_.rgba8.rgba;
			if(c0 != clut_[0] || c1 != clut_[1]) {
				d2_settexclut_part(d2_, clut_, 0, 2);
			}
			d2_setblitsrc(d2_, src, w, w, h, d2_mode_i1 | d2_mode_clut);
			d2_blitcopy(d2_, w, h,
				0, 0, w * 16, h * 16, pos.x * 16, pos.y * 16, copyflag);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	clut のポインター取得
			@return clut ポインター
		*/
		//-----------------------------------------------------------------//
		uint32_t* get_clut() noexcept { return reinterpret_cast<uint32_t*>(clut_); }


		//-----------------------------------------------------------------//
		/*!
			@brief	clut の設定
			@param[in]	org	開始インデックス
			@param[in]	num	個数
		*/
		//-----------------------------------------------------------------//
		void set_clut(uint32_t org, uint32_t num) noexcept
		{
			d2_settexclut_part(d2_, clut_, org, num);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	2 bits indexed color イメージを描画する
			@param[in]	pos		開始点を指定
			@param[in]	src		indexed4 のポインター
			@param[in]	ssz		ソースのサイズ
			@param[in]	alpha	アルファチャネルを使った描画を行う場合「true」
			@param[in]	pitch	ソースの横幅ピッチ（指定しないとソースの横幅と同じ）
		*/
		//-----------------------------------------------------------------//
		void draw_indexed2(const vtx::spos& pos, const void* src, const vtx::spos& ssz, bool alpha, int16_t pitch = 0) noexcept
		{
			if(src == nullptr) return;

			draw_bitmapn_(pos, src, ssz, pitch, d2_mode_i2);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	4 bits indexed color イメージを描画する
			@param[in]	pos		開始点を指定
			@param[in]	src		indexed4 のポインター
			@param[in]	ssz		ソースのサイズ
			@param[in]	alpha	アルファチャネルを使った描画を行う場合「true」
			@param[in]	pitch	ソースの横幅ピッチ（指定しないとソースの横幅と同じ）
		*/
		//-----------------------------------------------------------------//
		void draw_indexed4(const vtx::spos& pos, const void* src, const vtx::spos& ssz, bool alpha, int16_t pitch = 0) noexcept
		{
			if(src == nullptr) return;

			draw_bitmapn_(pos, src, ssz, alpha, pitch, d2_mode_i4);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	8 bits indexed color イメージを描画する
			@param[in]	pos		開始点を指定
			@param[in]	src		indexed8 のポインター
			@param[in]	ssz		ソースのサイズ
			@param[in]	alpha	アルファチャネルを使った描画を行う場合「true」
			@param[in]	pitch	ソースの横幅ピッチ（指定しないとソースの横幅と同じ）
		*/
		//-----------------------------------------------------------------//
		void draw_indexed8(const vtx::spos& pos, const void* src, const vtx::spos& ssz, bool alpha, int16_t pitch = 0) noexcept
		{
			if(src == nullptr) return;

			draw_bitmapn_(pos, src, ssz, alpha, pitch, d2_mode_i8);
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
			if(pos.y <= (clip_.org.y - FONT::height) || pos.y >= clip_.end_y()) {
				return;
			}
			if(code < 0x80) {
				if(pos.x <= (clip_.org.x - FONT::a_type::width) || pos.x >= clip_.end_x()) {
					return;
				}
				vtx::spos ssz(FONT::a_type::width, FONT::a_type::height);
				draw_bitmap(pos, FONT::a_type::get(code), ssz, back);
			} else {
				if(pos.x <= (clip_.org.x - FONT::k_type::width) || pos.x >= clip_.end_x()) {
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
			@brief	テクスチャーの設定
			@param[in]	image	画像データ
			@param[in]	size	画像サイズ
			@param[in]	form	画像フォーマット
		*/
		//-----------------------------------------------------------------//
		void set_texture(const void* image, const vtx::spos& size, uint32_t form)
		{
			d2_settexture(d2_, image, size.x, size.x, size.y, form);

			d2_settexturemode(d2_, d2_tm_wrapu | d2_tm_wrapv | d2_tm_filter);

			d2_point x = 0;
			d2_point y = 0;
			d2_settexturemapping(d2_, x, y, 0, 0, 65536 / 64, 0, 0, 65536 / 64);

		}


		//-----------------------------------------------------------------//
		/*!
			@brief	描画フラッシュ
		*/
		//-----------------------------------------------------------------//
		void flush() noexcept { d2_flushframe(d2_); }
	};
}
