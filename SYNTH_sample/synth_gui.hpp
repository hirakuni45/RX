#pragma once
//=====================================================================//
/*! @file
    @brief  SYNTH GUI クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2021 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/widget_director.hpp"

#include "keyboard.hpp"

namespace synth {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SYNTH 描画クラス
		@param[in]	RENDER	描画クラス
		@param[in]	TOUCH	タッチ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER, class TOUCH>
	class synth_gui {
	public:
		typedef keyboard<RENDER, TOUCH> KEYBOARD;

	private:
		RENDER&		render_;
		TOUCH&		touch_;

		typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
		WIDD		widd_;

        KEYBOARD    keyboard_;

        typedef gui::widget WIDGET;
		typedef gui::button BUTTON;

    public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	render	描画クラス
			@param[in]	touch	タッチ・クラス
		*/
		//-----------------------------------------------------------------//
		synth_gui(RENDER& render, TOUCH& touch) noexcept :
			render_(render), touch_(touch), widd_(render, touch),
            keyboard_(render, touch)
        { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start() noexcept
		{
            keyboard_.start();
#if 0
            key_c1_.enable();
            key_c1_.at_select_func() = [=](uint32_t id) {
                utils::format("C1\n");
            };

            key_d1_.enable();
            key_d1_.at_select_func() = [=](uint32_t id) {
                utils::format("D1\n");
            };

            key_c1s_.enable();
            key_c1s_.at_select_func() = [=](uint32_t id) {
                utils::format("C1#\n");
            };
#endif
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  更新 @n
					※毎フレーム呼ぶ
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			widd_.update();
            keyboard_.update();
        }

    
		//-----------------------------------------------------------------//
		/*!
			@brief  widget_director の参照
			@return widget_director
		*/
		//-----------------------------------------------------------------//
		auto& at_widd() noexcept { return widd_; }


		const auto& get_keyboard() const noexcept { return keyboard_; }
    };
}