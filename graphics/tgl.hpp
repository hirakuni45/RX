#pragma once
//=====================================================================//
/*!	@file
	@brief	Tiny 3D Glaphics Library (Tiny OpenGL)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
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
		@brief	TinyGL class
		@param[in]	RDR		レンダークラス
		@param[in]	VNUM	最大頂点数
		@param[in]	PNUM	最大プリミティブ数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class RDR, uint32_t VNUM, uint32_t PNUM>
	class tgl {
	public:

		enum class PTYPE {
			NONE,
			POINTS,
			LINES,
			LINE_STRIP,
			LINE_LOOP,
		};

		typedef gl::matrixf	MATRIX;

	private:
		RDR&		rdr_;

		uint32_t	vtx_idx_;
		vtx::ivtx4	vtxs_[VNUM];

		struct dt_t {
			PTYPE		pt_;
			uint32_t	org_;
			uint32_t	len_;
			dt_t() : pt_(PTYPE::NONE), org_(0), len_(0) { }
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
		tgl(RDR& rdr) : rdr_(rdr),
			vtx_idx_(0), vtxs_{},
			dt_idx_(0), dts_{},
			color_(0, 0, 0),
			matrix_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画開始
			@param[in]	pt	描画タイプ
		*/
		//-----------------------------------------------------------------//
		void begin(PTYPE pt)
		{
			if(dt_idx_ >= PNUM) return;

			dts_[dt_idx_].pt_ = pt;
			dts_[dt_idx_].org_ = vtx_idx_;
			dts_[dt_idx_].len_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	描画終了
		*/
		//-----------------------------------------------------------------//
		void end()
		{
			if(dts_[dt_idx_].org_ == vtx_idx_) {
				return;
			}
			dts_[dt_idx_].len_ = vtx_idx_ - dts_[dt_idx_].org_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	色設定
			@param[in]	c	カラー
		*/
		//-----------------------------------------------------------------//
		void color(const share_color& c)
		{
			color_ = c;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点の登録（spos）
			@param[in]	v	頂点
		*/
		//-----------------------------------------------------------------//
		void vertex(const vtx::spos& v)
		{
			if(vtx_idx_ >= VNUM) return;
			vtxs_[vtx_idx_].x = static_cast<float>(v.x);
			vtxs_[vtx_idx_].y = static_cast<float>(v.y);
			vtxs_[vtx_idx_].z = 0.0f;
			vtxs_[vtx_idx_].w = 1.0f;
			++vtx_idx_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点の登録（ipos）
			@param[in]	v	頂点
		*/
		//-----------------------------------------------------------------//
		void vertex(const vtx::ipos& v)
		{
			if(vtx_idx_ >= VNUM) return;
			vtxs_[vtx_idx_].x = static_cast<float>(v.x);
			vtxs_[vtx_idx_].y = static_cast<float>(v.y);
			vtxs_[vtx_idx_].z = 0.0f;
			vtxs_[vtx_idx_].w = 1.0f;
			++vtx_idx_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点の登録（fpos）
			@param[in]	v	頂点
		*/
		//-----------------------------------------------------------------//
		void vertex(const vtx::fpos& v)
		{
			if(vtx_idx_ >= VNUM) return;
			vtxs_[vtx_idx_].x = v.x;
			vtxs_[vtx_idx_].y = v.y;
			vtxs_[vtx_idx_].z = 0.0f;
			vtxs_[vtx_idx_].w = 1.0f;
			++vtx_idx_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点の登録（svtx）
			@param[in]	v	頂点
		*/
		//-----------------------------------------------------------------//
		void vertex(const vtx::svtx& v)
		{
			if(vtx_idx_ >= VNUM) return;
			vtxs_[vtx_idx_].x = static_cast<float>(v.x);
			vtxs_[vtx_idx_].y = static_cast<float>(v.y);
			vtxs_[vtx_idx_].z = static_cast<float>(v.z);
			vtxs_[vtx_idx_].w = 1.0f;
			++vtx_idx_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点の登録（ivtx）
			@param[in]	v	頂点
		*/
		//-----------------------------------------------------------------//
		void vertex(const vtx::ivtx& v)
		{
			if(vtx_idx_ >= VNUM) return;
			vtxs_[vtx_idx_].x = static_cast<float>(v.x);
			vtxs_[vtx_idx_].y = static_cast<float>(v.y);
			vtxs_[vtx_idx_].z = static_cast<float>(v.z);
			vtxs_[vtx_idx_].w = 1.0f;
			++vtx_idx_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点の登録（fvtx）
			@param[in]	v	頂点
		*/
		//-----------------------------------------------------------------//
		void vertex(const vtx::fvtx& v)
		{
			if(vtx_idx_ >= VNUM) return;
			vtxs_[vtx_idx_].x = v.x;
			vtxs_[vtx_idx_].y = v.y;
			vtxs_[vtx_idx_].z = v.z;
			vtxs_[vtx_idx_].w = 1.0f;
			++vtx_idx_;
		}


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
			for(uint32_t i = 0; i < dt_idx_; ++i) {
				const auto& t = dts_[i];
				auto org = t.org_;
				auto len = t.len_;
				switch(t.pt_) {
				case PTYPE::POINTS:
					break;
				case PTYPE::LINES:
					break;
				case PTYPE::LINE_STRIP:
					break;
				case PTYPE::LINE_LOOP:
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
