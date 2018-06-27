#pragma once
//=====================================================================//
/*!	@file
	@brief	ファイル操作ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/sdc_man.hpp"

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ファイラー制御型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class filer_ctrl {
		OPEN,		///< ファイラーを起動
		UP,			///< スクロール上
		DOWN,		///< スクロール下
		BACK,		///< ディレクトリーを戻る
		SELECT,		///< 選択
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	制御データ構築
		@param[in]	pos		ファイラー制御型
		@param[in]	ctrl	制御データ（参照）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	static inline void set(filer_ctrl pos, uint32_t& ctrl) noexcept
	{
		ctrl |= 1 << static_cast<uint8_t>(pos);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ファイラー
		@param[in]	SDC	sdc_man クラス型
		@param[in]	RDR	render クラス型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDC, class RDR>
	class filer {

		static const int16_t SPC = 2;                           ///< 文字間隙間
		static const int16_t FLN = RDR::font_height + SPC;      ///< 行幅
		static const int16_t SCN = (RDR::height - SPC) / FLN;   ///< 行数

		static const uint32_t PATH_MAX = 128;					///< パスの最大文字数

		SDC&	sdc_;
		RDR&	rdr_;

		uint32_t	ctrl_;
		bool		open_;

		struct rdr_st {
			RDR&		rdr_;
			int16_t		vofs_;
			int16_t		vpos_;
			int16_t		hmax_;
			int16_t		sel_pos_;
			uint16_t	num_;

			char		path_[PATH_MAX * SCN];

			rdr_st(RDR& rdr) : rdr_(rdr), vofs_(0), vpos_(0), hmax_(0), sel_pos_(0),
				num_(0), path_{ 0 }
			{ }
		};
		rdr_st	rdr_st_;

		static uint32_t ctrl_mask_(filer_ctrl ctrl) noexcept
		{
			return 1 << static_cast<uint8_t>(ctrl);
		}


		static void dir_draw_func_(const char* name, const FILINFO* fi, bool dir, void* opt)
			noexcept
		{
			rdr_st& t = *static_cast<rdr_st*>(opt);
			t.rdr_.fill(SPC, t.vpos_, RDR::width - SPC * 2, RDR::font_height, 0x0000);
			if(dir) t.rdr_.draw_font(SPC, t.vpos_, '/');
			auto w = t.rdr_.draw_text(SPC + 8, t.vpos_, name);
			if(t.hmax_ < w) t.hmax_ = w;
			uint32_t n = t.num_ + t.vofs_ / FLN;
			if(n < SCN) {
				strncpy(&t.path_[n * PATH_MAX], name, PATH_MAX);
				if(dir) {
					strncat(&t.path_[n * PATH_MAX], "/", PATH_MAX);
				}
			}
			t.vpos_ += FLN;
			++t.num_;
		}


		void start_dir_draw_() noexcept
		{
			uint32_t num = (RDR::height - 2) / (RDR::font_height + 2);
			rdr_st_.vpos_ = rdr_st_.vofs_ + 2;
			rdr_st_.num_ = 0;
			sdc_.start_dir_list("", dir_draw_func_, true, &rdr_st_);
		}


		void draw_sel_frame_(int16_t pos, uint16_t c)
		{
			int16_t h = RDR::font_height + 2;
			int16_t y = pos * h;
			rdr_.frame(0, y, rdr_st_.hmax_ + 3, h + 1, c);
		}


		void scan_dir_()
		{
			rdr_st_.vofs_ = 0;
			rdr_st_.sel_pos_ = 0;
			start_dir_draw_();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		filer(SDC& sdc, RDR& rdr) noexcept : sdc_(sdc), rdr_(rdr),
			ctrl_(0), open_(false),
			rdr_st_(rdr_)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	アップデート（毎フレーム呼ぶ）
			@param[in]	ctrl	ファイラー制御
			@return ファイルが選択された場合、ファイルパス
		*/
		//-----------------------------------------------------------------//
		const char* update(uint32_t ctrl) noexcept
		{
			uint32_t ptrg = ~ctrl_ &  ctrl;
			uint32_t ntrg =  ctrl_ & ~ctrl;
			ctrl_ = ctrl;

			if(!sdc_.get_mount()) return nullptr;

			if(ptrg & ctrl_mask_(filer_ctrl::OPEN)) {
				open_ = !open_;
				if(open_) {
					scan_dir_();
				} else {
					rdr_.clear(0x0000);
				}
			}

			if(!open_) return nullptr;

			{
				uint32_t n;
				bool f = sdc_.probe_dir_list(n);
				if(f) return nullptr;
				if(rdr_st_.num_ < static_cast<int16_t>(n)) return nullptr;
			}

			// 選択フレームの描画
			draw_sel_frame_(rdr_st_.sel_pos_, 0xffff);
			int16_t pos = rdr_st_.sel_pos_;
			if(ptrg & ctrl_mask_(filer_ctrl::UP)) {
				pos--;
			}
			if(ptrg & ctrl_mask_(filer_ctrl::DOWN)) {
				++pos;
			}
			int16_t vofs = rdr_st_.vofs_;
			int16_t scn = SCN;
			if(rdr_st_.num_ < scn) scn = rdr_st_.num_; 
			if(pos < 0) {
				pos = 0;
				vofs += FLN;
			} else if(pos >= scn) {
				pos = scn - 1;
				vofs -= FLN;
			}
			int16_t lim = 0;
			if(rdr_st_.num_ > scn) {
				lim = -(rdr_st_.num_ - scn) * FLN;
			}
			if(vofs > 0) {
				vofs = 0;
			} else if(vofs < lim) {
				vofs = lim;
			}
			if(vofs != rdr_st_.vofs_) {
				rdr_st_.vofs_ = vofs;
				start_dir_draw_();
			}
			
			if(pos != rdr_st_.sel_pos_) {
				draw_sel_frame_(rdr_st_.sel_pos_, 0x0000);
				rdr_st_.sel_pos_ = pos;
			}

			if(ptrg & ctrl_mask_(filer_ctrl::SELECT)) {
				char* p = &rdr_st_.path_[PATH_MAX * rdr_st_.sel_pos_];
				uint32_t l = strlen(p);
				if(p[l - 1] == '/') {
					p[l - 1] = 0;
					sdc_.cd(p);
					rdr_.clear(0x0000);
					scan_dir_();
				} else {
					rdr_.clear(0x0000);
					open_ = false;
					return static_cast<const char*>(p);
				}
			}

			if(ptrg & ctrl_mask_(filer_ctrl::BACK)) {
				sdc_.cd("..");
				rdr_.clear(0x0000);
				scan_dir_();
			}

			return nullptr;
		}
	};
}
