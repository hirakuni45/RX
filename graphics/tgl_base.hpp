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
		enum class PTYPE {
			NONE,
			POINTS,			///< 点の描画
			LINES,			///< 単線の描画
			LINE_STRIP,		///< 複数線の描画
			LINE_LOOP,		///< 閉じた線の描画
			QUAD,			///< ４角形の描画
			TRIANGLE,		///< ３角形の描画
		};

		typedef gl::matrixf	MATRIX;
	};
}
