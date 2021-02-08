#pragma once
//=====================================================================//
/*!	@file
	@brief	Tiny 3D Glaphics Library (Tiny OpenGL)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/vtx.hpp"
#include "graphics/color.hpp"
#include "graphics/glmatrix.hpp"

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	TinyGL base class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class tgl_base {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	TinyGL Primitive Type
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PTYPE {
			NONE,
			POINTS,			///< 点の描画
			LINES,			///< 単線の描画
			LINE_STRIP,		///< 複数線の描画
			LINE_LOOP,		///< 閉じた線の描画
			QUAD,			///< ４点ポリゴンの描画
		};

		typedef gl::matrixf	MATRIX;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	TinyGL class
		@param[in]	RDR		レンダークラス
		@param[in]	VNUM	最大頂点数
		@param[in]	PNUM	最大プリミティブ数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class RDR, uint32_t VNUM, uint32_t PNUM>
	class tgl : public tgl_base {

		RDR&		rdr_;

		uint32_t	vtx_idx_;
		vtx::fvtx4	vtxs_[VNUM];

		struct dt_t {
			PTYPE		pt_;
			share_color	col_;
			uint32_t	org_;
			uint32_t	end_;
			dt_t() : pt_(PTYPE::NONE), col_(0, 0, 0), org_(0), end_(0) { }
		};

		uint32_t	dt_idx_;
		dt_t		dts_[PNUM];

		share_color	color_;

		MATRIX		matrix_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		tgl(RDR& rdr) noexcept : rdr_(rdr),
			vtx_idx_(0), vtxs_{},
			dt_idx_(0), dts_{},
			color_(0, 0, 0),
			matrix_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		*/
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
#ifdef SIG_RX72N
			utils::format("TinyGL Start\n");
			__init_tfu();
			utils::format("  TFU initializations\n");
#endif
//	void __builtin_rx_atan2hypotf(float, float, float*, float*);
//	float __builtin_rx_sinf(float);
//	float __builtin_rx_cosf(float);
//	float __builtin_rx_atan2f(float, float);
//	float __builtin_rx_hypotf(float, float);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	描画開始
			@param[in]	pt	描画タイプ
		*/
		//-----------------------------------------------------------------//
		void begin(PTYPE pt) noexcept
		{
			if(dt_idx_ >= PNUM) return;

			dts_[dt_idx_].pt_ = pt;
			dts_[dt_idx_].col_ = color_;
			dts_[dt_idx_].org_ = vtx_idx_;
			dts_[dt_idx_].end_ = vtx_idx_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	描画終了
		*/
		//-----------------------------------------------------------------//
		void end() noexcept
		{
			if(dts_[dt_idx_].org_ == vtx_idx_) {
				return;
			}
			dts_[dt_idx_].end_ = vtx_idx_;
			++dt_idx_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	色設定
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		void color(const share_color& c) noexcept
		{
			color_ = c;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点の登録（spos）
			@param[in]	v	頂点
		*/
		//-----------------------------------------------------------------//
		void vertex(float x, float y) noexcept
		{
			if(vtx_idx_ >= VNUM) return;
			vtxs_[vtx_idx_].x = x;
			vtxs_[vtx_idx_].y = y;
			vtxs_[vtx_idx_].z = 0.0f;
			vtxs_[vtx_idx_].w = 1.0f;
			++vtx_idx_;
		}
		void vertex(const vtx::spos& v) noexcept { vertex(v.x, v.y); }
		void vertex(const vtx::ipos& v) noexcept { vertex(v.x, v.y); }
		void vertex(const vtx::fpos& v) noexcept { vertex(v.x, v.y); }


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点の登録（svtx）
			@param[in]	v	頂点
		*/
		//-----------------------------------------------------------------//
		void vertex(float x, float y, float z) noexcept
		{
			if(vtx_idx_ >= VNUM) return;
			vtxs_[vtx_idx_].x = x;
			vtxs_[vtx_idx_].y = y;
			vtxs_[vtx_idx_].z = z;
			vtxs_[vtx_idx_].w = 1.0f;
			++vtx_idx_;
		}
		void vertex(const vtx::svtx& v) noexcept { vertex(v.x, v.y, v.z); }
		void vertex(const vtx::ivtx& v) noexcept { vertex(v.x, v.y, v.z); }
		void vertex(const vtx::fvtx& v) noexcept { vertex(v.x, v.y, v.z); }


		//-----------------------------------------------------------------//
		/*!
			@brief	マトリックスへの参照
			@return マトリックス
		*/
		//-----------------------------------------------------------------//
		MATRIX& at_matrix() noexcept { return matrix_; }		


		//-----------------------------------------------------------------//
		/*!
			@brief	レンダリング
		*/
		//-----------------------------------------------------------------//
		void renderring() noexcept
		{
			MATRIX::matrix_type wm;
			matrix_.world_matrix(wm);

			int ox;
			int oy;
			int w;
			int h;
			matrix_.get_viewport(ox, oy, w, h);  // drw2d for fixed point
			ox <<= 4;
			oy <<= 4;
			w <<= 4;
			h <<= 4;

			for(uint32_t i = 0; i < dt_idx_; ++i) {
				const auto& t = dts_[i];
				rdr_.set_fore_color(t.col_);

				uint32_t k = 0;
				vtx::spos tmp[16];
				for(uint32_t j = t.org_; j < t.end_; ++j) {
					vtx::fvtx src(vtxs_[j].x, vtxs_[j].y, vtxs_[j].z);
					vtx::fvtx dst;
					matrix_.vertex_screen(wm, src, dst);
					tmp[k].x = static_cast<int16_t>(dst.x * w) + (w / 2) + ox;
					tmp[k].y = static_cast<int16_t>(dst.y * h) + (h / 2) + oy;
					++k;
				}
				switch(t.pt_) {
				case PTYPE::POINTS:
					break;
				case PTYPE::LINES:
					break;
				case PTYPE::LINE_STRIP:
					break;
				case PTYPE::LINE_LOOP:
					for(uint32_t j = 0; j < k; ++j) {
						auto l = j + 1;
						if(l >= k) l = 0;
						rdr_.line_d(tmp[j], tmp[l]);
					}
					break;
				case PTYPE::QUAD:
					for(uint32_t j = 0; j < k; j += 4) {
						rdr_.quad_d(tmp[j+0], tmp[j+1], tmp[j+2], tmp[j+3]);
					}
					break;
				default:
					break;
				}
			}

			dt_idx_ = 0;
			vtx_idx_ = 0;
		}
	};
}
