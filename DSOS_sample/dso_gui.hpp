#pragma once
//=====================================================================//
/*! @file
    @brief  DSO GUI クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2020 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/widget_director.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  波形描画クラス
		@param[in]	RENDER	描画クラス
		@param[in]	TOUCH	タッチ・クラス
		@param[in]	CAPTURE	キャプチャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER, class TOUCH, class CAPTURE>
	class dso_gui {

		static const int16_t GRID = 40;

		RENDER&		render_;
		CAPTURE&	capture_;
		TOUCH&		touch_;

		typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
		WIDD		widd_;

		typedef gui::button BUTTON;
		BUTTON		ch0_;
		BUTTON		ch1_;
		BUTTON		trg_;
		BUTTON		smp_;
		BUTTON		mes_;
		BUTTON		opt_;

//					"CH0", "CH1", "Trg", "Smp", "Mes", "Opt" };
//					dialog_.square_button(vtx::srect(441, 16 + GRID * i + 1, GRID - 1, GRID - 1), menu[i]);
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	render	描画クラス
			@param[in]	touch	タッチ・クラス
			@param[in]	capture	キャプチャー・クラス
		*/
		//-----------------------------------------------------------------//
		dso_gui(RENDER& render, TOUCH& touch, CAPTURE& capture) noexcept :
			render_(render), capture_(capture), touch_(touch),
			widd_(render, touch),
			ch0_(vtx::srect(441, 16+GRID*0+1, GRID-1, GRID-1), "CH0"),
			ch1_(vtx::srect(441, 16+GRID*0+1, GRID-1, GRID-1), "CH1"),
			trg_(vtx::srect(441, 16+GRID*0+1, GRID-1, GRID-1), "Trg"),
			smp_(vtx::srect(441, 16+GRID*0+1, GRID-1, GRID-1), "Smp"),
			mes_(vtx::srect(441, 16+GRID*0+1, GRID-1, GRID-1), "Mes"),
			opt_(vtx::srect(441, 16+GRID*0+1, GRID-1, GRID-1), "Opt")
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  更新 @n
					※毎フレーム呼ぶ
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			widd_.update();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  widget_director の参照
			@return widget_director
		*/
		//-----------------------------------------------------------------//
		auto& at_widd() noexcept { return widd_; }
	};
}
