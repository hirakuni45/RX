#pragma once
//=====================================================================//
/*!	@file
	@brief	Widget クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/vtx.hpp"
#include "graphics/color.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	Widget クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct widget {

		typedef graphics::def_color DEF_COLOR;	///< 標準カラー

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	widget ID
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ID {
			GROUP,		///< グループ
			FRAME,		///< フレーム
			BUTTON,		///< ボタン
			CHECK,		///< チェック・ボタン
			RADIO,		///< ラジオ・ボタン
			SLIDER,		///< スライダー
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ステート
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class STATE : uint8_t {
			DISABLE,	///< 無効状態（表示されない）
			ENABLE,		///< 有効
			STALL,		///< 表示されているが、ストール状態
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タッチ・ステート
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct touch_state {
			vtx::spos	position_;	///< タッチしている絶対位置
			vtx::spos	expand_;	///< フォーカス拡張領域
			bool		positive_;	///< タッチした瞬間
			bool		level_;		///< タッチしている状態
			bool		negative_;	///< 離した瞬間
			touch_state(const vtx::spos& fexp = vtx::spos(4)) noexcept :
				position_(-1), expand_(fexp),
				positive_(false), level_(false), negative_(false) { }
		};

	private:

		widget*		parents_;		///< 親
		widget*		next_;			///< リンク

		vtx::srect	location_;		///< 位置とサイズ

		const char*	title_;			///< タイトル

		STATE		state_;
		bool		focus_;
		bool		touch_;

		touch_state	touch_state_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	title	タイトル
			@param[in]	fexp	フォーカス拡張領域
		*/
		//-----------------------------------------------------------------//
		widget(const vtx::srect& loc = vtx::srect(0), const char* title = nullptr, const vtx::spos& fexp = vtx::spos(0))
			noexcept :
			parents_(nullptr), next_(nullptr),
			location_(loc), title_(title),
			state_(STATE::DISABLE), focus_(false), touch_(false), touch_state_(fexp)
		{ } 


		//-----------------------------------------------------------------//
		/*!
			@brief	widget 名称の取得
			@return widget 名称
		*/
		//-----------------------------------------------------------------//
		virtual const char* get_name() const = 0;


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		virtual ID get_id() const = 0; 


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化 @n
					GUI が有効になった場合に実行される
		*/
		//-----------------------------------------------------------------//
		virtual void init()  = 0;


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		virtual void update_touch(const vtx::spos& pos, uint16_t num) = 0;


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移 @n
					状態の変化が起きた場合に呼び出される。
			@param[in]	ena		無効状態にする場合「false」
		*/
		//-----------------------------------------------------------------//
		virtual void exec_select(bool ena = true)  = 0;


		//-----------------------------------------------------------------//
		/*!
			@brief	親を設定
			@param[in]	w	親 widget
		*/
		//-----------------------------------------------------------------//
		void set_parents(widget* w) noexcept { parents_ = w; }


		//-----------------------------------------------------------------//
		/*!
			@brief	親 widget を返す
			@return	親 widget
		*/
		//-----------------------------------------------------------------//
		widget* get_parents() const noexcept { return parents_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	次接続設定
			@param[in]	w	親 widget
		*/
		//-----------------------------------------------------------------//
		void set_next(widget* w) noexcept { next_ = w; }


		//-----------------------------------------------------------------//
		/*!
			@brief	次接続 widget を返す
			@return	次接続 widget
		*/
		//-----------------------------------------------------------------//
		widget* get_next() const noexcept { return next_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ロケーションの取得
			@return ロケーション
		*/
		//-----------------------------------------------------------------//
		const vtx::srect& get_location() const noexcept { return location_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ロケーションの参照
			@return ロケーション
		*/
		//-----------------------------------------------------------------//
		vtx::srect& at_location() noexcept { return location_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タイトルの設定
			@param[in]	title	タイトル
		*/
		//-----------------------------------------------------------------//
		void set_title(const char* title) noexcept { title_ = title; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タイトルの取得
			@return タイトル
		*/
		//-----------------------------------------------------------------//
		const char* get_title() const noexcept { return title_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ステートの設定
			@param[in]	state	ステート
		*/
		//-----------------------------------------------------------------//
		void set_state(STATE state) noexcept
		{
			state_ = state;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ステートの取得
			@return	ステート
		*/
		//-----------------------------------------------------------------//
		auto get_state() const noexcept { return state_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	許可・不許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable(bool ena = true) noexcept
		{
			if(ena) set_state(STATE::ENABLE);
			else set_state(STATE::DISABLE);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フォーカスを取得
			@return フォーカス
		*/
		//-----------------------------------------------------------------//
		bool get_focus() const noexcept { return focus_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ・ステートを取得
			@return タッチ・ステート
		*/
		//-----------------------------------------------------------------//
		const auto& get_touch_state() const noexcept { return touch_state_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	標準的なタッチ判定更新
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		void update_touch_def(const vtx::spos& pos, uint16_t num) noexcept
		{
			auto loc = vtx::srect(get_final_position(), location_.size);
			loc.org  -= touch_state_.expand_;
			loc.size += touch_state_.expand_;
			focus_ = loc.is_focus(pos);
			if(focus_) {
				if(num > 0) {
					touch_ = true;
					touch_state_.position_ = pos;
				} else {
					touch_ = false;
					touch_state_.position_.set(-1);
				}
				auto level = touch_;
				touch_state_.positive_ = ( level && !touch_state_.level_);
				touch_state_.negative_ = (!level &&  touch_state_.level_);
				touch_state_.level_    =   level;
			} else {
				touch_state_.positive_ = false;
				touch_state_.negative_ = false;
				touch_state_.level_    = false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新（スライダー用）@n
					・スライダーの操作性を良くする為の工夫をする。@n
					・タッチしたまま、左右、上下にドラッグして、スライダー @n
					のフォーカスを外れた場合、操作が中断してしまうのを改善する。
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		void update_touch_slider(const vtx::spos& pos, uint16_t num) noexcept
		{
			if(num == 0) {
				focus_ = false;
				touch_ = false;
				touch_state_.position_.set(-1);
				touch_state_.positive_ = false;
				touch_state_.negative_ = touch_state_.level_;
				touch_state_.level_    = false;
				return;
			}

			auto loc = vtx::srect(get_final_position(), location_.size);
			loc.org  -= touch_state_.expand_;
			loc.size += touch_state_.expand_;
			bool focus = loc.is_focus(pos);
			if(!focus_ && focus) {
				touch_ = true;
			}
			focus_ = focus;
			touch_state_.position_ = pos;

			auto level = touch_;
			touch_state_.positive_ = ( level && !touch_state_.level_);
			touch_state_.negative_ = (!level &&  touch_state_.level_);
			touch_state_.level_    =   level;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	最終位置を取得
			@return 最終位置
		*/
		//-----------------------------------------------------------------//
		vtx::spos get_final_position() const noexcept
		{
			auto pos = location_.org;
			widget* w = parents_;
			while(w != nullptr) {
				pos += w->get_location().org;
				w = w->get_parents();
			}
			return pos;
		}
	};
}

extern bool insert_widget(gui::widget* w);
extern void remove_widget(gui::widget* w);
