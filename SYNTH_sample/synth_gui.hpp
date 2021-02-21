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

extern void select_synth_color(uint32_t no);

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
		static const int16_t SC_NAME_LEN = 16;   ///< With EOT
		static const int16_t SC_NUM = 32;   ///< 音色最大数

		typedef keyboard<RENDER, TOUCH> KEYBOARD;

	private:

		RENDER&		render_;
		TOUCH&		touch_;

		typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
		WIDD		widd_;

        KEYBOARD    keyboard_;

		static const int16_t LOC = 10;   ///< ボタン関係、縦の位置
		static const int16_t SPC = 10;   ///< ボタンとの隙間
		static const int16_t CENTER = 480/2;   ///< X 中心
		static const int16_t BTN_SZ = 30;   ///< ボタンサイズ
		static const int16_t TEX_W = 8 * SC_NAME_LEN;  ///< テキスト横幅
		static const int16_t TEX_H = 24;       ///< テキスト高さ

        typedef gui::widget WIDGET;
		typedef gui::button BUTTON;
		typedef gui::text TEXT;
		BUTTON		sc_idx_m_;
		TEXT		sc_name_;
		BUTTON		sc_idx_p_;

		uint32_t	sc_idx_;
		uint32_t	sc_idx_before_;
		const char*	sc_name_org_;

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
            keyboard_(render, touch),
			sc_idx_m_(vtx::srect(CENTER-TEX_W/2-BTN_SZ-SPC, LOC, BTN_SZ, BTN_SZ), "<"),
			sc_name_ (vtx::srect(CENTER-TEX_W/2, LOC+(BTN_SZ-TEX_H)/2, TEX_W, TEX_H),  ""),
			sc_idx_p_(vtx::srect(CENTER+TEX_W/2+SPC,        LOC, BTN_SZ, BTN_SZ), ">"),
			sc_idx_(0), sc_idx_before_(0), sc_name_org_(nullptr)
        { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	sc_name		音色名（１２ｘ３２）
		*/
		//-----------------------------------------------------------------//
		void start(const char* sc_name) noexcept
		{
			sc_name_org_ = sc_name;

            keyboard_.start();

			sc_idx_m_.enable();
			sc_idx_m_.set_state(WIDGET::STATE::STALL);
			sc_idx_m_.at_select_func() = [this](uint32_t id) {
				if(sc_idx_ > 0) {
					sc_idx_--;
				}
				select_synth_color(sc_idx_);
			};

			sc_name_.enable();

			sc_idx_p_.enable();
			sc_idx_p_.set_state(WIDGET::STATE::STALL);
			sc_idx_p_.at_select_func() = [this](uint32_t id) {
				++sc_idx_;
				if(sc_idx_ >= SC_NUM) {
					sc_idx_ = SC_NUM - 1;
				}
				select_synth_color(sc_idx_);
			};

			sc_idx_before_ = SC_NUM;
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  更新 @n
					※毎フレーム呼ぶ
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			if(sc_name_org_[0] != 0) {
				sc_idx_p_.set_state(WIDGET::STATE::ENABLE);
				sc_idx_m_.set_state(WIDGET::STATE::ENABLE);
			}
			if(sc_idx_before_ != sc_idx_) {
				if(sc_name_org_[SC_NAME_LEN * sc_idx_] != 0) {
					sc_idx_before_ = sc_idx_;
					sc_name_.set_title(&sc_name_org_[SC_NAME_LEN * sc_idx_]);
				}
			}
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
