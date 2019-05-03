#pragma once
//=====================================================================//
/*!	@file
	@brief	メニュー・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "graphics/widget.hpp"
#include "common/string_utils.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	メニュー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct menu : public widget {

		typedef menu value_type;

		static const int16_t round_radius = 6;  // round radius
		static const int16_t item_height  = 28;	// ITEM height

		typedef std::function<void(uint32_t pos, uint32_t num)> SELECT_FUNC_TYPE;

	private:

		SELECT_FUNC_TYPE	select_func_;
		vtx::spos			item_size_;
		uint32_t			num_;
		uint32_t			select_pos_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		ボタン文字列
		*/
		//-----------------------------------------------------------------//
		menu(const vtx::srect& loc = vtx::srect(0), const char* str = "") noexcept :
			widget(loc, str),
			select_func_(), item_size_(0),
			num_(utils::str::get_words(str, ',')), select_pos_(num_)
		{
			if(loc.size.y <= 0) {
				at_location().size.y = num_ * item_height;
				item_size_.y = item_height;
			} else {
				item_size_.y = loc.size.y / num_;
			}
			insert_widget(this);
		}


		menu(const menu& th) = delete;
		menu& operator = (const menu& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~menu() noexcept { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "Menu"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::MENU; }


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
			@param[in]	slt		スライド・タイプの場合「true」
		*/
		//-----------------------------------------------------------------//
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override
		{
			update_touch_def(pos, num, false);
			const auto& st = get_touch_state();
			if(st.level_) {
				select_pos_ = st.relative_.y / item_size_.y;
			}
			if(st.negative_) {
				if(!get_focus()) {
					select_pos_ = num_;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
			@param[in]	inva	無効状態にする場合「true」
		*/
		//-----------------------------------------------------------------//
		void exec_select(bool inva) noexcept override
		{
			if(select_func_) {
				select_func_(select_pos_, num_);
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
			if(ena) set_state(STATE::ENABLE);
			else set_state(STATE::DISABLE);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト位置の取得
			@return	セレクト位置
		*/
		//-----------------------------------------------------------------//
		uint32_t get_select_pos() const noexcept { return select_pos_; }


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
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = vtx::srect(get_final_position(), get_location().size);
			r.size.y /= num_;
			for(uint32_t i = 0; i < num_; ++i) {
				if(get_touch_state().level_ && select_pos_ == i) {
					rdr.set_fore_color(graphics::def_color::Silver);
				} else {
					if(i & 1) rdr.set_fore_color(graphics::def_color::Midgray);
					else rdr.set_fore_color(graphics::def_color::Gray);
				}
				bool up = false;
				bool dn = false;
				if(i == 0) up = true;
				if(i == (num_ - 1)) dn = true;
				rdr.round_box(r, round_radius, up, dn);

				char tmp[16];
				if(utils::str::get_word(get_title(), i, tmp, sizeof(tmp), ',')) {
					auto sz = rdr.at_font().get_text_size(tmp);
					rdr.set_fore_color(graphics::def_color::White);
					rdr.draw_text(r.org + (r.size - sz) / 2, tmp);
				}
				r.org.y += r.size.y;
			}
		}
	};
}
