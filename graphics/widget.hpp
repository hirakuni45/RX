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
#include "graphics/widget_set.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	Widget クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct widget {

		typedef graphics::def_color DEF_COLOR;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ステート
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class STATE {
			DISABLE,	///< 無効状態（表示されない）
			ENABLE,		///< 有効
			STALL,		///< 表示されているが、ストール状態
		};

	private:
		widget*		parents_;	///< 親

		vtx::srect	location_;	///< 位置とサイズ

		const char*	title_;		///< タイトル

		STATE		state_;		///< 状態
		bool		focus_;		///< フォーカスされている場合「true」
		bool		touch_;		///< タッチされている場合「true」

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	title	タイトル
		*/
		//-----------------------------------------------------------------//
		widget(const vtx::srect& loc = vtx::srect(0), const char* title = nullptr) noexcept :
			parents_(nullptr),
			location_(loc),
			title_(title),
			state_(STATE::DISABLE), focus_(false), touch_(false)
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
		virtual widget_set::ID get_id() const = 0; 


		//-----------------------------------------------------------------//
		/*!
			@brief	親を設定
			@param[in]	w	親 widget
		*/
		//-----------------------------------------------------------------//
		void set_parents(widget* w) { parents_ = w; }


		//-----------------------------------------------------------------//
		/*!
			@brief	親 widget を返す
			@return	親 widget
		*/
		//-----------------------------------------------------------------//
		widget* get_parents() const noexcept { return parents_; }


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
///			utils::format("set_state: %d\n") % static_cast<int>(state_);
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
			@brief	エリア判定を行い、内部状態へ反映する
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		void check_area(const vtx::spos& pos, uint16_t num) noexcept
		{
			focus_ = location_.is_focus(pos);
			if(focus_ && num > 0) touch_ = true;
			else touch_ = false;
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
			@brief	タッチを取得
			@return タッチ
		*/
		//-----------------------------------------------------------------//
		bool get_touch() const noexcept { return touch_; }
	};
}

extern bool insert_widget(gui::widget* w);
extern void remove_widget(gui::widget* w);
