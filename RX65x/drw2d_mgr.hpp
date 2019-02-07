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
#include "RX65x/drw2d.hpp"
#include "RX65x/glcdc_def.hpp"

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
		@brief  DRW2D 制御／マネージャー
		@param[in]	GLC		グラフィックス・コントローラー・クラス
		@param[in]	DRW		DRW2D 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GLC, class DRW>
	class drw2d_mgr {

		GLC&		glc_;

		d2_device*	d2_;
		d2_renderbuffer*	rb_;

		d2_color	color_;
		vtx::srect	clip_;
		int16_t		pen_size_;
		int16_t		scale_;
		bool		set_color_;
		bool		set_clip_;

		int32_t		last_error_;

		d2_color	clut_[256];

		static uint32_t get_mode_()
		{
			switch(GLC::get_pxt()) {
			case glcdc_def::PIX_TYPE::RGB888:
				return d2_mode_argb8888;
			case glcdc_def::PIX_TYPE::RGB565:
				return d2_mode_rgb565;
			case glcdc_def::PIX_TYPE::CLUT8:
				return d2_mode_i8;
			case glcdc_def::PIX_TYPE::CLUT4:
				return d2_mode_i4;
			case glcdc_def::PIX_TYPE::CLUT1:
				return d2_mode_i1;
			default:
				return d2_mode_rgb565;
			}
		}


		void setup_()
		{
			auto mode = get_mode_();
			d2_framebuffer(d2_, glc_.get_layer2(), GLC::get_xsize(), GLC::get_xsize(), GLC::get_ysize(), mode);
//			d2_selectrenderbuffer(d2_, rb_);
			if(!set_color_) {
				d2_setcolor(d2_, 0, color_);
				set_color_ = true;
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
		drw2d_mgr(GLC& glc) noexcept : glc_(glc), d2_(nullptr), rb_(nullptr),
			color_(0xffffffff), clip_(0, 0, GLC::get_xsize(), GLC::get_ysize()),
			pen_size_(16), scale_(16),
			set_color_(false), set_clip_(false), last_error_(D2_OK)
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
			@param[in]	dlis	ディスプレイリストエントリー初期化サイズ
			@param[in]	stsz	ディスプレイリストエントリーステップサイズ
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t dlis = 20, uint32_t stsz = 20) noexcept
		{
			// DRW2D power management
			power_mgr::turn(DRW::get_peripheral());

			// initialization Dave2D
			d2_ = d2_opendevice(0);
			uint32_t init_flag = 0;
			d2_inithw(d2_, init_flag);

			icu_mgr::install_group_task(DRW::get_irq_vec(), drw_int_isr);
			icu_mgr::set_level(ICU::VECTOR::GROUPAL1, 2);

			rb_ = d2_newrenderbuffer(d2_, dlis, stsz);

			clut_[0] = 0xff000000;
			clut_[1] = 0xffffffff;

			return true;
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
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カラーの設定
			@param[in]	color	カラー
		*/
		//-----------------------------------------------------------------//
		void set_color(d2_color color) noexcept
		{
			color_ = color;
			set_color_ = false;
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
			@brief	DRW2D フレーム・セットアップ
		*/
		//-----------------------------------------------------------------//
		void setup_frame()
		{
			set_clip_ = false;
			setup_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	全クリア
			@return エラー無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool clear() noexcept
		{
			setup_();
			last_error_ = d2_clear(d2_, color_);

			d2_executerenderbuffer(d2_, rb_, 0);
			d2_flushframe(d2_);
			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ライン描画
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

			d2_executerenderbuffer(d2_, rb_, 0);
			d2_flushframe(d2_);
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
		bool circle(const vtx::spos& org, int16_t r, int16_t w = 0)
		{
			setup_();
			last_error_ = d2_rendercircle(d2_, org.x * scale_, org.y * scale_,
				r * scale_, w * scale_);

			d2_executerenderbuffer(d2_, rb_, 0);
			d2_flushframe(d2_);
			return last_error_ == D2_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ボックス描画
			@param[in]	org		基点
			@param[in]	size	サイズ
			@return エラー無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool box(const vtx::spos& org, const vtx::spos& size)
		{
			setup_();
			last_error_ = d2_renderbox(d2_, org.x * scale_, org.y * scale_,
				size.x * scale_, size.y * scale_);

			d2_executerenderbuffer(d2_, rb_, 0);
			d2_flushframe(d2_);
			return last_error_ == D2_OK;
		}





		void copy_bitmap(const vtx::spos& pos)
		{
			d2_settexclut(d2_, clut_);

			static const uint8_t src[8] = {
				0b11111111,
				0b11111101,
				0b11111001,
				0b11110001,
				0b11100001,
				0b11000001,
				0b10000001,
				0b11111111
			};

			auto mode = get_mode_();
			d2_framebuffer(d2_, glc_.get_fbp(), GLC::get_xsize(), GLC::get_xsize(), GLC::get_ysize(), mode);
			d2_selectrenderbuffer(d2_, rb_);
			d2_setblitsrc(d2_, (void*)src, 8, 8, 8, d2_mode_i1);
			d2_blitcopy(d2_, 8, 8,
				0, 0, 8 * 16, 8 * 16, pos.x * 16, pos.y * 16, d2_bf_usealpha);

			d2_executerenderbuffer(d2_, rb_, 0);
			d2_flushframe(d2_);
		}


		void test_frame(d2_color col, int16_t rad)
		{
			d2_startframe(d2_);
			auto xs = GLC::get_xsize();
			auto ys = GLC::get_ysize();
			d2_framebuffer(d2_, glc_.get_fbp(), xs, xs, ys, d2_mode_rgb565);
			d2_cliprect(d2_, 0, 0, xs * 16, ys * 16);
			d2_clear(d2_, 0x000000);
			d2_setcolor(d2_, 0, col);
//			d2_renderbox(d2_, 480/2*16, 272/2*16, rad*16, rad*16);
			d2_rendercircle(d2_, 480/2*16, 272/2*16, rad*16, 0);
			d2_endframe(d2_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	描画フラッシュ
		*/
		//-----------------------------------------------------------------//
		void flush() noexcept { d2_flushframe(d2_); }
	};
}
