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
		enum class ID : uint8_t {
			GROUP,		///< グループ
			FRAME,		///< フレーム
			BOX,		///< ボックス（シンプルな単型）
			TEXT,		///< テキスト
			TEXTBOX,	///< テキスト・ボックス
			DIALOG,		///< ダイアログ
			BUTTON,		///< ボタン
			CHECK,		///< チェック・ボタン
			RADIO,		///< ラジオ・ボタン
			SLIDER,		///< スライダー
			MENU,		///< メニュー
			TERM,		///< ターミナル
			SPINBOX,	///< スピンボックス
			CLOSEBOX,	///< クローズボックス
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
			vtx::spos	relative_;	///< タッチしている相対位置
			vtx::spos	expand_;	///< フォーカス拡張領域
			bool		positive_;	///< タッチした瞬間
			bool		level_;		///< タッチしている状態
			bool		negative_;	///< 離した瞬間
			touch_state(const vtx::spos& fexp = vtx::spos(4)) noexcept :
				position_(-1), expand_(fexp),
				positive_(false), level_(false), negative_(false) { }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	水平配置型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class H_ALIGNMENT : uint8_t {
			LEFT,	///< 左
			CENTER,	///< 中央
			RIGHT,	///< 右
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	垂直配置型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class V_ALIGNMENT : uint8_t {
			TOP,	///< 上
			CENTER,	///< 中央
			BOTTOM,	///< 下
		};

	private:

		widget*		parents_;	///< 親
		widget*		next_;		///< リンク

		vtx::srect	location_;	///< 位置とサイズ

		const char*	title_;		///< タイトル
		const void*	mobj_;		///< モーションオブジェクト	

		graphics::share_color	base_color_;	///< GUI 基本色
		graphics::share_color	font_color_;	///< フォント基本色

		STATE		state_;
		bool		focus_;
		bool		touch_;

		touch_state	touch_state_;

		bool		update_;

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
			location_(loc), title_(title), mobj_(nullptr),
			base_color_(graphics::def_color::White), font_color_(graphics::def_color::White),
			state_(STATE::DISABLE), focus_(false), touch_(false),
			touch_state_(fexp), update_(false)
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
			@brief	タッチ判定を更新（通常毎フレーム呼ばれる）
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
		virtual void exec_select(bool ena = true) = 0;


		//-----------------------------------------------------------------//
		/*!
			@brief	許可・不許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		virtual void enable(bool ena = true) = 0;


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
			@brief	タイトル更新前処理
		*/
		//-----------------------------------------------------------------//
		virtual void update_title() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	モーションオブジェクトの設定
			@param[in]	mobj	モーションオブジェクト
		*/
		//-----------------------------------------------------------------//
		void set_mobj(const void* mobj) noexcept {
			mobj_ = mobj;
			set_update();			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	モーションオブジェクトの取得
			@return モーションオブジェクト
		*/
		//-----------------------------------------------------------------//
		const void* get_mobj() const noexcept { return mobj_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ベースカラーの設定
			@param[in]	color	カラー
		*/
		//-----------------------------------------------------------------//
		void set_base_color(const graphics::share_color& color) noexcept {
			base_color_ = color;
			set_update();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ベースカラーの取得
			@return ベースカラー
		*/
		//-----------------------------------------------------------------//
		auto get_base_color() const noexcept {
			if(state_ == STATE::STALL) {
				graphics::share_color sh(0, 0, 0);
				sh.set_color(base_color_.rgba8, 96);
				return sh;
			} else {
				return base_color_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フォントカラーの設定
			@param[in]	color	カラー
		*/
		//-----------------------------------------------------------------//
		void set_font_color(const graphics::share_color& color) noexcept {
			font_color_ = color;
			set_update();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フォントカラーの取得
			@return フォントカラー
		*/
		//-----------------------------------------------------------------//
		auto get_font_color() const noexcept
		{
			if(state_ == STATE::STALL) {
				graphics::share_color sh(0, 0, 0);
				sh.set_color(font_color_.rgba8, 96);
				return sh;
			} else {
				return font_color_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	「更新」の設定
			@param[in]	update	更新をしない場合「false」
		*/
		//-----------------------------------------------------------------//
		void set_update(bool update = true) noexcept { update_ = update; }


		//-----------------------------------------------------------------//
		/*!
			@brief	「更新」の取得
			@return	「更新」
		*/
		//-----------------------------------------------------------------//
		auto get_update() const noexcept { return update_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ステートの設定
			@param[in]	state	ステート
		*/
		//-----------------------------------------------------------------//
		void set_state(STATE state) noexcept { state_ = state; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ステートの取得
			@return	ステート
		*/
		//-----------------------------------------------------------------//
		auto get_state() const noexcept { return state_; }


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
			@brief	タッチステートをリセット
		*/
		//-----------------------------------------------------------------//
		void reset_touch_state() noexcept
		{
			touch_state_.positive_ = false;
			touch_state_.negative_ = false;
			touch_state_.level_    = false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	標準的なタッチ判定更新
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
			@param[in]	exp		タッチ領域拡張を行わない場合「false」
		*/
		//-----------------------------------------------------------------//
		void update_touch_def(const vtx::spos& pos, uint16_t num, bool exp = true) noexcept
		{
			auto loc = vtx::srect(get_final_position(), location_.size);
			if(exp) {
				loc.org  -= touch_state_.expand_;
				loc.size += touch_state_.expand_;
			}
			focus_ = loc.is_focus(pos);
			if(focus_) {
				if(num > 0) {
					touch_ = true;
					touch_state_.position_ = pos;
					touch_state_.relative_ = pos - loc.org;
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
