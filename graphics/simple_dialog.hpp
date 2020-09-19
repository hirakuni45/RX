#pragma once
//=====================================================================//
/*!	@file
	@brief	ダイアログ表示 @n
			・単独で利用できるシンプルなダイアログクラス。@n
			・文字列を表示して、タッチを検出して閉じる事しか出来ない。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/graphics.hpp"
#include "graphics/color.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シンプル・ダイアログ表示クラス
		@param[in]	RDR		レンダークラス
		@param[in]	TOUCH	タッチクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RDR, class TOUCH>
	class simple_dialog {
	public:
		typedef graphics::def_color DEF_COLOR;
		static const int16_t modal_radius = 10;  // modal round radius
		static const int16_t button_radius = 6;  // button round radius

	private:
		using GLC = typename RDR::glc_type;

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
		simple_dialog(RDR& rdr, TOUCH& touch) noexcept : rdr_(rdr), touch_(touch)
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
			vtx::spos pos((GLC::width  - size.x) / 2, (GLC::height - size.y) / 2);
			rdr_.set_fore_color(DEF_COLOR::White);
			rdr_.set_back_color(DEF_COLOR::Darkgray);
			vtx::srect r(pos, size);
			rdr_.round_box(r, modal_radius);
			r.org += 2;
			r.size -= 2 * 2;
			rdr_.swap_color();
			rdr_.round_box(r, modal_radius - 2);

			auto sz = rdr_.at_font().get_text_size(text);
			rdr_.swap_color();
			rdr_.draw_text(pos + (size - sz) / 2, text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	四角ボタンの描画 @n
					・背景色は「back_color」が使われる。@n
					・フォントの描画色は「fore_color」が利用
			@param[in]	rect	配置
			@param[in]	text	テキスト
		*/
		//-----------------------------------------------------------------//
		void square_button(const vtx::srect& rect, const char* text) noexcept
		{
			auto sz = rdr_.at_font().get_text_size(text);
			rdr_.swap_color();
			rdr_.fill_box(rect);
			rdr_.swap_color();
			rdr_.draw_text(rect.org + (rect.size - sz) / 2, text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ラウンドボタンの描画 @n
					・背景色は「back_color」が使われる。@n
					・フォントの描画色は「fore_color」が利用
			@param[in]	rect	配置
			@param[in]	text	テキスト
		*/
		//-----------------------------------------------------------------//
		void round_button(const vtx::srect& rect, const char* text) noexcept
		{
			rdr_.swap_color();
			rdr_.round_box(rect, button_radius);
			rdr_.swap_color();
			auto sz = rdr_.at_font().get_text_size(text);
			rdr_.draw_text(rect.org + (rect.size - sz) / 2, text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アップデート
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチパネルの安定待ち
		*/
		//-----------------------------------------------------------------//
		void ready_to_touch()
		{
			rdr_.sync_frame();
			modal(vtx::spos(400, 60),
				"Touch panel device wait...\nPlease touch it with some screen.");
			uint8_t nnn = 0;
			while(1) {
				rdr_.sync_frame();
				touch_.update();
				auto num = touch_.get_touch_num();
				if(num == 0) {
					++nnn;
					if(nnn >= 60) break;
				} else {
					nnn = 0;
				}
			}
		}
	};
}
