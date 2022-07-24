#pragma once
//=====================================================================//
/*!	@file
	@brief	ラジオ・ボタン表示と制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "gui/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ラジオ・ボタン・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct radio : public widget {

		typedef radio value_type;

		typedef std::function<void(bool)> SELECT_FUNC_TYPE;

	private:

		SELECT_FUNC_TYPE	select_func_;
		bool				switch_state_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		ボタン文字列
			@param[in]	first	初期状態
		*/
		//-----------------------------------------------------------------//
		radio(const vtx::srect& loc = vtx::srect(0), const char* str = "", bool first = false) noexcept :
			widget(loc, str), select_func_(), switch_state_(first)
		{
			if(loc.size.x <=0) {
				int16_t tlen = 0;
				if(str != nullptr) tlen = strlen(str) * 8;
				at_location().size.x = DEF_RADIO_BOX + DEF_RADIO_TO_STR + tlen;
			}
			if(loc.size.y <=0) {
				at_location().size.y = DEF_RADIO_BOX;
			}
			insert_widget(this);
		}

		radio(const check& th) = delete;
		radio& operator = (const check& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~radio() { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const override { return "Radio"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const override { return ID::RADIO; }


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
			@brief	スイッチ状態の取得
			@return スイッチ状態
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
			@brief	描画
			@param[in]	rdr		描画インスタンス
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto font_height = RDR::font_type::height;
			auto rad = get_location().size.y / 2;
			const auto& org = get_final_position();
			auto cen = org + rad;

			rdr.set_fore_color(get_base_color());
			rdr.fill_circle(cen, rad);
			rad -= DEF_RADIO_FRAME_WIDTH;

			graphics::share_color sc(0, 0, 0);
			sc.set_color(get_base_color().rgba8, 64);
			rdr.set_fore_color(sc);
			rdr.fill_circle(cen, rad);

			if(get_touch_state().level_ || switch_state_) {
				rad -= DEF_RADIO_SPACE;
				rdr.set_fore_color(get_base_color());
				rdr.fill_circle(cen, rad);
			}

			auto pos = org;
			pos.x +=  get_location().size.y + DEF_RADIO_TO_STR;
			pos.y += (get_location().size.y - RDR::font_type::height) / 2;
			rdr.set_fore_color(get_font_color());
			rdr.draw_text(pos, get_title());
		}
	};
}
