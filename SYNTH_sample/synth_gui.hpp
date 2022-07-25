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
#include "gui/widget_director.hpp"

#include "graphics/simple_filer.hpp"

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
		static constexpr int16_t SC_NAME_LEN = 16;   ///< With EOT
		static constexpr int16_t SC_NUM = 32;   ///< 音色最大数
		static constexpr int16_t OCT_NUM = 5;   ///< オクターブ域

		typedef keyboard<RENDER, TOUCH> KEYBOARD;

	private:

		RENDER&		render_;
		TOUCH&		touch_;

		typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
		WIDD		widd_;

        KEYBOARD    keyboard_;

		static constexpr int16_t SC_LOC = 10;   ///< ボタン関係、縦の位置
		static constexpr int16_t SC_SPC = 10;   ///< ボタンとの隙間
		static constexpr int16_t CENTER = 480/2;   ///< X 中心
		static constexpr int16_t SC_BTN_SZ = 40;   ///< ボタンサイズ
		static constexpr int16_t SC_TEX_W = 8 * SC_NAME_LEN;  ///< テキスト横幅
		static constexpr int16_t SC_TEX_H = 24;       ///< テキスト高さ

		static constexpr int16_t OCT_LOC = 40;   ///< オクターブ関係、縦の位置
		static constexpr int16_t OCT_AREA_W = 300;
		static constexpr int16_t OCT_AREA_H = 20;
		static constexpr int16_t OCT_BTN_SZ = 50;   ///< ボタンサイズ

		typedef gui::widget WIDGET;
		typedef gui::button BUTTON;
		typedef gui::text TEXT;
		typedef gui::slider SLIDER;
		BUTTON		filer_run_;

		BUTTON		sc_idx_m_;
		TEXT		sc_name_;
		BUTTON		sc_idx_p_;

		BUTTON		test_play_;

		BUTTON		octave_m_;
		SLIDER		octave_d_;
		BUTTON		octave_p_;

		uint32_t	sc_idx_;
		uint32_t	sc_idx_before_;
		const char*	sc_name_org_;

		uint32_t	oct_idx_;

		typedef gui::simple_filer_base FILER_BASE;
		typedef gui::simple_filer<RENDER> FILER;
		FILER		filer_;
		uint32_t	ctrl_;
		bool		filer_state_;
		char		path_[256];
		uint32_t	file_id_;


		void gui_enable_(bool mount, bool sc, bool ena)
		{
			if(ena) {
				if(mount) {
					filer_run_.enable(ena);
				} else {
					filer_run_.set_state(WIDGET::STATE::STALL);
				}
				if(sc) {  // 音色が有効になったら、ボタンを有効にする。
					sc_idx_m_.enable(ena);
					sc_idx_p_.enable(ena);
				} else {
					sc_idx_m_.set_state(WIDGET::STATE::STALL);
					sc_idx_p_.set_state(WIDGET::STATE::STALL);
				}
			} else {
				sc_idx_m_.enable(ena);
				sc_idx_p_.enable(ena);
				filer_run_.enable(ena);
			}

			sc_name_.enable(ena);
			octave_m_.enable(ena);
			octave_d_.enable(ena);
			octave_p_.enable(ena);

			keyboard_.enable(ena);
		}

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
			filer_run_(vtx::srect(CENTER-SC_TEX_W/2 - (SC_BTN_SZ+SC_SPC) * 2 - 10, SC_LOC, SC_BTN_SZ, SC_BTN_SZ), "@"),
			sc_idx_m_(vtx::srect(CENTER-SC_TEX_W/2 - SC_BTN_SZ-SC_SPC, SC_LOC, SC_BTN_SZ, SC_BTN_SZ), "<"),
			sc_name_ (vtx::srect(CENTER-SC_TEX_W/2, SC_LOC+(SC_BTN_SZ-SC_TEX_H)/2, SC_TEX_W, SC_TEX_H),  ""),
			sc_idx_p_(vtx::srect(CENTER+SC_TEX_W/2 + SC_SPC, SC_LOC, SC_BTN_SZ, SC_BTN_SZ), ">"),
			test_play_(vtx::srect(CENTER+SC_TEX_W/2 + (SC_BTN_SZ+SC_SPC) * 2 - 30, SC_LOC, SC_BTN_SZ, SC_BTN_SZ), "T"),
			octave_m_(vtx::srect(0,              OCT_LOC, OCT_BTN_SZ, OCT_BTN_SZ), "<<"),
			octave_d_(vtx::srect(CENTER-OCT_AREA_W/2, OCT_LOC+(OCT_BTN_SZ-OCT_AREA_H)/2, OCT_AREA_W, OCT_AREA_H)),
			octave_p_(vtx::srect(480-OCT_BTN_SZ, OCT_LOC, OCT_BTN_SZ, OCT_BTN_SZ), ">>"),
			sc_idx_(0), sc_idx_before_(0), sc_name_org_(nullptr),
			oct_idx_(2),
			filer_(render), ctrl_(0), filer_state_(false), file_id_(0)
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

			filer_run_.set_layer(WIDGET::LAYER::_0);
			filer_run_.at_select_func() = [this](uint32_t id) {
				FILER_BASE::set(FILER_BASE::ctrl::OPEN, ctrl_);
			};

			sc_idx_m_.set_layer(WIDGET::LAYER::_0);
			sc_idx_m_.at_select_func() = [this](uint32_t id) {
				if(sc_idx_ > 0) {
					sc_idx_--;
				}
			};

			sc_name_.set_layer(WIDGET::LAYER::_0);

			sc_idx_p_.set_layer(WIDGET::LAYER::_0);
			sc_idx_p_.at_select_func() = [this](uint32_t id) {
				++sc_idx_;
				if(sc_idx_ >= SC_NUM) {
					sc_idx_ = SC_NUM - 1;
				}
			};

			test_play_.set_layer(WIDGET::LAYER::_0);
			test_play_.at_select_func() = [this](uint32_t id) {
				
			};

			sc_idx_before_ = SC_NUM;

			octave_m_.set_layer(WIDGET::LAYER::_0);
			octave_m_.at_select_func() = [this](uint32_t) {
				if(oct_idx_ > 0) {
					oct_idx_--;
				}
			};

			octave_d_.set_layer(WIDGET::LAYER::_0);
			octave_d_.enable_read_only();

			octave_p_.set_layer(WIDGET::LAYER::_0);
			octave_p_.at_select_func() = [this](uint32_t) {
				++oct_idx_;
				if(oct_idx_ >= OCT_NUM) {
					oct_idx_ = OCT_NUM - 1;
				}
			};

			widd_.enable(WIDGET::LAYER::_0);
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  更新 @n
					※毎フレーム呼ぶ
			@param[in] mount	SD カードのマウント状態
		*/
		//-----------------------------------------------------------------//
		void update(bool mount) noexcept
		{
			ctrl_ = 0;
			if(mount) {
				FILER_BASE::set(FILER_BASE::ctrl::MOUNT, ctrl_);
			}

			// 音色が変更になったら、音色名を表示
			if(sc_idx_before_ != sc_idx_) {
				if(sc_name_org_[SC_NAME_LEN * sc_idx_] != 0) {
					sc_idx_before_ = sc_idx_;
					sc_name_.set_title(&sc_name_org_[SC_NAME_LEN * sc_idx_]);
					select_synth_color(sc_idx_);
				}
			}

			octave_d_.set_ratio(static_cast<float>(oct_idx_) / static_cast<float>(OCT_NUM - 1));

			// ファイラーが有効なら、GUI を無効、ファイラーが無効なら GUI を有効にする。
			auto fs = filer_.get_state();
			gui_enable_(mount, sc_name_org_[0] != 0, !fs);
			filer_state_ = fs;

			widd_.update();
            keyboard_.update();

			{  // ファイラーの操作
				auto tnum = touch_.get_touch_num();
				const auto& t = touch_.get_touch_pos(0);
				filer_.set_touch(tnum, t.pos);
				auto fst = filer_.update(ctrl_, path_, sizeof(path_));
				if(fst == FILER_BASE::status::FILE) {  // ファイル選択
//					utils::format("Play: '%s'\n") % path_;
					++file_id_;
				} else if(fst == FILER_BASE::status::CANCEL) {  // ファイル選択キャンセル

				}
			}
        }

    
		//-----------------------------------------------------------------//
		/*!
			@brief  widget_director の参照
			@return widget_director
		*/
		//-----------------------------------------------------------------//
		auto& at_widd() noexcept { return widd_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  オクターブ域の取得
			@return オクターブ域
		*/
		//-----------------------------------------------------------------//
		auto get_octave() const noexcept { return oct_idx_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  keyboard の取得
			@return keyboard
		*/
		//-----------------------------------------------------------------//
		const auto& get_keyboard() const noexcept { return keyboard_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ファイル名の取得
			@paramout]	id	ファイル ID
			@return ファイル名
		*/
		//-----------------------------------------------------------------//
		const char* get_file_name(uint32_t& id) const noexcept {
			id = file_id_;
			return path_;
		}
    };
}
