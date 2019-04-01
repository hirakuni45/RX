#pragma once
//=====================================================================//
/*!	@file
	@brief	ダイアログ表示
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/graphics.hpp"
#include "graphics/color.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ダイアログ表示クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RDR, class TOUCH>
	class dialog {
	public:
		typedef graphics::def_color DEF_COLOR;
		static const int16_t modal_radius = 10;  // modal round radius

	private:
		RDR&	rdr_;
		TOUCH&	touch_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	rdr		描画クラス
			@param[in]	touch	タッチクラス
		*/
		//-----------------------------------------------------------------//
		dialog(RDR& rdr, TOUCH& touch) noexcept : rdr_(rdr), touch_(touch)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	モーダルウィンドウ描画（画面の中心に表示される）
			@param[in]	size	大きさ
			@param[in]	text	テキスト
		*/
		//-----------------------------------------------------------------//
		void modal(const vtx::spos& size, const char* text) noexcept
		{
			vtx::spos pos((RDR::glc_type::width  - size.x) / 2, (RDR::glc_type::height - size.y) / 2);
			rdr_.set_fore_color(DEF_COLOR::White);
			rdr_.set_back_color(DEF_COLOR::Darkgray);
			vtx::srect r(pos, size);
			rdr_.round_box(r, modal_radius);
			r.org += 2;
			r.size -= 2 * 2;
			rdr_.swap_color();
			rdr_.round_box(r, modal_radius - 2);

			auto sz = rdr_.at_font().get_text_size(text);
			pos.x += (size.x - sz.x) / 2;
			pos.y += (size.y - sz.y) / 2;
			rdr_.swap_color();
			rdr_.draw_text(pos, text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	標準ボタンの描画 @n
					・背景色は「back_color」が使われる。@n
					・フォントの描画色は「fore_color」が利用
			@param[in]	rect	配置
			@param[in]	text	テキスト
		*/
		//-----------------------------------------------------------------//
		void draw_button(const vtx::srect& rect, const char* text) noexcept
		{
			auto sz = rdr_.at_font().get_text_size(text);
			rdr_.swap_color();
			rdr_.fill_box(rect);
			rdr_.swap_color();
			rdr_.draw_text(rect.org + vtx::spos((rect.size.x - sz.x) / 2, (rect.size.y - sz.y) / 2), text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アップデート
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
		}
	};
}
