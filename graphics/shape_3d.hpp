#pragma once
//=====================================================================//
/*!	@file
	@brief	3D Shape
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/vtx.hpp"
#include "graphics/color.hpp"
#include "graphics/tgl_base.hpp"

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	3D Shape class
        @param[in] TGL  TinyGL 型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    template <class TGL> 
	class shape_3d : tgl_base {

        typedef graphics::def_color DEF_COLOR;

        TGL&     tgl_;

	    void draw_box_(float size, PTYPE prim) noexcept
	    {
	    	static constexpr vtx::fvtx n[6] = {
	    		{ -1.0f,  0.0f,  0.0f },
	    		{  0.0f,  1.0f,  0.0f },
	    		{  1.0f,  0.0f,  0.0f },
	    		{  0.0f, -1.0f,  0.0f },
	    		{  0.0f,  0.0f,  1.0f },
	    		{  0.0f,  0.0f, -1.0f }
	    	};

	    	static const int faces[6][4] =
	    	{
	    		{ 0, 1, 2, 3 },
	    		{ 3, 2, 6, 7 },
	    		{ 7, 6, 5, 4 },
	    		{ 4, 5, 1, 0 },
	    		{ 5, 6, 2, 1 },
	    		{ 7, 4, 0, 3 }
	    	};

	    	vtx::fvtx v[8];
	    	v[0].x = v[1].x = v[2].x = v[3].x = -size / 2;
	    	v[4].x = v[5].x = v[6].x = v[7].x =  size / 2;
	    	v[0].y = v[1].y = v[4].y = v[5].y = -size / 2;
	    	v[2].y = v[3].y = v[6].y = v[7].y =  size / 2;
	    	v[0].z = v[3].z = v[4].z = v[7].z = -size / 2;
	    	v[1].z = v[2].z = v[5].z = v[6].z =  size / 2;

	    	static const graphics::share_color c[6] = {
	    		DEF_COLOR::White,
	    		DEF_COLOR::Red,
	    		DEF_COLOR::Blue,
	    		DEF_COLOR::Green,
	    		DEF_COLOR::Fuchsi,
	    		DEF_COLOR::Yellow
	    	};

	    	for(int i = 5; i >= 0; i--) {
	    		tgl_.Color(c[i]);
        		tgl_.Begin(prim);
        		// Normal(&n[i]);
        		tgl_.Vertex(v[faces[i][0]]);
        		tgl_.Vertex(v[faces[i][1]]);
        		tgl_.Vertex(v[faces[i][2]]);
        		tgl_.Vertex(v[faces[i][3]]);
        		tgl_.End();
  	    	}
	    }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
            @param[in] tgl  TinyGL インスタンス
		*/
		//-----------------------------------------------------------------//
        shape_3d(TGL& tgl) noexcept : tgl_(tgl) { } 


		//-----------------------------------------------------------------//
		/*!
			@brief	塗りつぶされた、ボックスの描画
            @param[in] size     サイズ
		*/
		//-----------------------------------------------------------------//
        void SolidCube(float size) noexcept
        {
            draw_box_(size, PTYPE::QUAD);
        }


		//-----------------------------------------------------------------//
		/*!
			@brief	ワイヤーフレーム、ボックスの描画
            @param[in] size     サイズ
		*/
		//-----------------------------------------------------------------//
        void WireCube(float size) noexcept
        {
            draw_box_(size, PTYPE::LINE_LOOP);
        }
    };
}
