#pragma once
//=====================================================================//
/*!	@file
	@brief	クローズ・ボックス・ボタン表示と制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "graphics/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	クローズ・ボックス・ボタン・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct closebox : public widget {

		typedef closebox value_type;

		typedef std::function<void(bool)> SELECT_FUNC_TYPE;

		static const int16_t round_radius = 2;
		static const int16_t frame_width  = 3;
		static const int16_t box_size     = 22;		///< サイズが省略された場合の標準的なサイズ

	private:

		SELECT_FUNC_TYPE	select_func_;
		bool				enable_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		ボタン文字列
		*/
		//-----------------------------------------------------------------//
		closebox(const vtx::srect& loc = vtx::srect(0), const char* str = "") noexcept :
			widget(loc, str), select_func_(), enable_(false)
		{
			if(loc.size.x <= 0) {
				at_location().size.x = box_size;
			}
			if(loc.size.y <= 0) {
				at_location().size.y = box_size;
			}
			insert_widget(this);
		}

		closebox(const closebox& th) = delete;
		closebox& operator = (const closebox& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~closebox() { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const override { return "CloseBox"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const override { return ID::CLOSEBOX; }


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-----------------------------------------------------------------//
		void init() override { }


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
			@param[in]	slt		スライド・タイプの場合「true」
		*/
		//-----------------------------------------------------------------//
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override
		{
			update_touch_def(pos, num);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
			@param[in]	ena		無効状態にする場合「false」
		*/
		//-----------------------------------------------------------------//
		void exec_select(bool ena = true) noexcept override
		{
			enable_ = ena;
			if(select_func_) {
				select_func_(enable_);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	許可・不許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable(bool ena = true) noexcept override
		{
			if(ena) {
				set_state(STATE::ENABLE);
			} else {
				set_state(STATE::DISABLE);
				reset_touch_state();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト ID の取得
			@return	セレクト ID
		*/
		//-----------------------------------------------------------------//
		bool get_enable() const noexcept { return enable_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト関数への参照
			@return	セレクト関数
		*/
		//-----------------------------------------------------------------//
		SELECT_FUNC_TYPE& at_select_func() noexcept { return select_func_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画
			@param[in]	rdr		描画インスタンス
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto font_height = RDR::font_type::height;
			auto loc = vtx::srect(get_final_position(), get_location().size);
			loc.size.x = loc.size.y;
			auto r = loc;

			rdr.set_fore_color(graphics::def_color::White);
			rdr.round_box(r, round_radius);

			r.org  += frame_width;
			r.size -= frame_width * 2;
			rdr.set_fore_color(graphics::def_color::Darkgray);
			rdr.round_box(r, round_radius - frame_width);

			if(get_touch_state().level_ || enable_) {
				rdr.set_fore_color(graphics::def_color::White);
//				r.org  += check_space;
//				r.size -= check_space * 2;
				auto s = r.org;
				auto e = r.org + r.size;
				rdr.line(s, e);
				std::swap(s.x, e.x);
				rdr.line(s, e);
			}
		}
	};
}
