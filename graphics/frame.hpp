#pragma once
//=====================================================================//
/*!	@file
	@brief	フレーム表示と制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	フレーム・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct frame : public widget {

		typedef frame value_type;

		static const int16_t round_radius = 6;  // round radius

	private:

		int16_t		caption_height_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		フレーム・タイトル
		*/
		//-----------------------------------------------------------------//
		frame(const vtx::srect& loc = vtx::srect(0), const char* str = "") noexcept :
			widget(loc, str), caption_height_(0)
		{
			insert_widget(this);
		}


		frame(const frame& th) = delete;
		frame& operator = (const frame& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~frame() noexcept { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "Frame"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::FRAME; }


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
		void enable(bool ena = true) override
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
			@brief	描画
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = get_location();
			rdr.set_fore_color(get_base_color());
			rdr.round_box(r, round_radius);

			uint8_t inten = 64;
			if(get_touch_state().level_) {  // 0.75
				inten = 192;
			}
			graphics::share_color sh(0, 0, 0);
			sh.set_color(get_base_color().rgba8, inten);
			rdr.set_fore_color(sh);

			r.org += 2;
			r.size -= 4;
			rdr.round_box(r, round_radius - 2);

			rdr.set_fore_color(get_font_color());
			auto sz = rdr.at_font().get_text_size(get_title());
			rdr.draw_text(r.org + (r.size - sz) / 2, get_title());
		}


		template <class T>
		frame& operator + (T& th)
		{
			th.set_parents(this);
			return *this;
		}


		template <class T>
		frame& operator += (T& th)
		{
			th.set_parents(this);
			return *this;
		}
	};
}
