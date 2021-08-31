#pragma once
//=====================================================================//
/*!	@file
	@brief	Tiny 3D Glaphics Library (Tiny OpenGL)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
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
		enum class PTYPE : uint8_t {
			NONE,
			POINTS,			///< 点の描画
			LINES,			///< 単線の描画
			LINE_STRIP,		///< 複数線の描画
			LINE_LOOP,		///< 閉じた線の描画
			QUAD,			///< ４角形の描画
			TRIANGLE,		///< ３角形の描画
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	TinyGL 制御型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CTRL : uint8_t {
			NONE,
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	TinyGL ターゲット型（テクスチャー）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TARGET : uint8_t {
			NONE,
			TEXTURE_2D,
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	TinyGL フォーマット型（テクスチャー・ピクセル）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class FORMAT : uint8_t {
			RGBA8,	///< R:8, G:8, B:8, A:8 (32 bits)
			RGB565,	///< R:5, G:6, B:5 (16 bits)
			RGBA4,	///< R:4, G:4, B:4, A:4 (16 bits)
		};

		typedef gl::matrixf MATRIX;
	};
}
