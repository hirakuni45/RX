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

	private:

		uint32_t	num_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		ボタン文字列
		*/
		//-----------------------------------------------------------------//
		menu(const vtx::srect& loc = vtx::srect(0), const char* str = "") noexcept :
			widget(loc, str)
		{
			num_ = utils::str::get_words(str, ',');
			at_location().size.y = num_ * item_height;
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
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override { }


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
			@param[in]	inva	無効状態にする場合「true」
		*/
		//-----------------------------------------------------------------//
		void exec_select(bool inva) noexcept override { }


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
			@brief	描画
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = vtx::srect(get_final_position(), get_location().size);

			for(uint32_t i = 0; i < num_; ++i) {
				if(i & 1) rdr.set_fore_color(graphics::def_color::Darkgray);
				else rdr.set_fore_color(graphics::def_color::Gray);
				rdr.round_box(r, round_radius);

				rdr.set_fore_color(graphics::def_color::White);
				auto sz = rdr.at_font().get_text_size(get_title());
				rdr.draw_text(r.org + (r.size - sz) / 2, get_title());
			}

#if 0
			rdr.set_fore_color(graphics::def_color::White);

			if(get_touch_state().level_) {
				rdr.set_fore_color(graphics::def_color::Silver);
			} else {
				rdr.set_fore_color(graphics::def_color::Darkgray);
			}
			r.org += 2;
			r.size -= 4;
			rdr.round_box(r, round_radius - 2);
#endif
		}
	};
}
