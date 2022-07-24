#pragma once
//=====================================================================//
/*!	@file
	@brief	トグル（スイッチ）の表示と制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "graphics/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	トグル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct toggle : public widget {

		typedef toggle value_type;

		typedef std::function<void(bool state)> SELECT_FUNC_TYPE;

	private:

		SELECT_FUNC_TYPE	select_func_;
		bool				switch_state_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	first	トグルの初期状態
		*/
		//-----------------------------------------------------------------//
		toggle(const vtx::srect& loc = vtx::srect(0), bool first = false) noexcept :
			widget(loc, nullptr), select_func_(), switch_state_(first)
		{
			if(get_location().size.x <= 0) {  // 自動で幅を推定する場合
				at_location().size.x = DEF_TOGGLE_WIDTH;
			}
			if(get_location().size.y <= 0) {
				at_location().size.y = DEF_TOGGLE_HEIGHT;
			}
			insert_widget(this);
		}


		toggle(const toggle& th) = delete;
		toggle& operator = (const toggle& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~toggle() { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "Toggle"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::TOGGLE; }


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-----------------------------------------------------------------//
		void init() noexcept override { }


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override
		{
			update_touch_def(pos, num);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
		*/
		//-----------------------------------------------------------------//
		void exec_select() noexcept override
		{
			switch_state_ = !switch_state_;
			if(select_func_) {
				select_func_(switch_state_);
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
			@brief	トグルスイッチの状態取得
			@return	トグルスイッチの状態
		*/
		//-----------------------------------------------------------------//
		bool get_switch_state() const noexcept { return switch_state_; }
	

		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト関数への参照
			@return	セレクト関数
		*/
		//-----------------------------------------------------------------//
		SELECT_FUNC_TYPE& at_select_func() noexcept { return select_func_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画テンプレート
			@param[in]	rdr		描画インスタンス
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = vtx::srect(get_final_position(), get_location().size);
			rdr.set_fore_color(get_base_color());
			auto arc = r.size.y / 2;
			rdr.round_box(r, arc);

			uint8_t inten = 64;
			if(switch_state_) inten = 128;
			if(get_touch_state().level_) {  // 0.75
				inten = 192;
			}
			graphics::share_color sc(0, 0, 0);
			sc.set_color(get_base_color().rgba8, inten);
			rdr.set_fore_color(sc);
			r.org  += DEF_TOGGLE_FRAME_WIDTH;
			r.size -= DEF_TOGGLE_FRAME_WIDTH * 2;
			arc -= DEF_TOGGLE_FRAME_WIDTH;
			rdr.round_box(r, arc);

			auto cen = r.org + arc;
			if(switch_state_) {
				inten = 255;
				cen.x = r.org.x + r.size.x - arc - 1;
			} else {
				inten = 128;
			}
			sc.set_color(get_base_color().rgba8, inten);
			rdr.set_fore_color(sc);
			rdr.fill_circle(cen, arc);
		}
	};
}
