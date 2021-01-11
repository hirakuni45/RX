#pragma once
//=====================================================================//
/*!	@file
	@brief	複数行のテキスト表示と制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	テキストボックス・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct textbox : public widget {

		typedef textbox value_type;

	private:

		H_ALIGNMENT	h_alignment_;
		V_ALIGNMENT	v_alignment_;

		bool		text_update_;
		vtx::spos	text_size_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		テキスト文字列
		*/
		//-----------------------------------------------------------------//
		textbox(const vtx::srect& loc = vtx::srect(0), const char* str = "") noexcept :
			widget(loc, str), h_alignment_(H_ALIGNMENT::LEFT), v_alignment_(V_ALIGNMENT::TOP),
			text_update_(false), text_size_(0)
		{
			set_base_color(graphics::def_color::Gray);
			insert_widget(this);
		}


		textbox(const frame& th) = delete;
		textbox& operator = (const frame& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~textbox() noexcept { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "TextBox"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::TEXTBOX; }


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
			@brief	タイトル更新時処理
		*/
		//-----------------------------------------------------------------//
		void update_title() noexcept override { text_update_ = true; }


		//-----------------------------------------------------------------//
		/*!
			@brief	水平整列を設定
			@param[in]	ha	水平整列型
		*/
		//-----------------------------------------------------------------//
		void set_holizontal_alignment(H_ALIGNMENT ha) noexcept { h_alignment_ = ha; }


		//-----------------------------------------------------------------//
		/*!
			@brief	垂直整列を設定
			@param[in]	va	垂直整列型
		*/
		//-----------------------------------------------------------------//
		void set_vertical_alignment(V_ALIGNMENT va) noexcept { v_alignment_ = va; }


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
			auto r = vtx::srect(get_final_position(), get_location().size);
			rdr.set_fore_color(get_base_color());
			rdr.fill_box(r);

			rdr.set_fore_color(get_font_color());

			if(text_update_) {
				text_update_ = false;
				text_size_ = rdr.at_font().get_text_size(get_title());
			}

			vtx::spos ofs;
			switch(h_alignment_) {
			case H_ALIGNMENT::CENTER:
				ofs.x = (r.size.x - text_size_.x) / 2;
				break;
			case H_ALIGNMENT::RIGHT:
				ofs.x = r.size.x - text_size_.x;
				break;
			case H_ALIGNMENT::LEFT:
			default:
				ofs.x = 0;
				break;
			}

			switch(v_alignment_) {
			case V_ALIGNMENT::CENTER:
				ofs.y = (r.size.y - text_size_.y) / 2;
				break;
			case V_ALIGNMENT::BOTTOM:
				ofs.y = r.size.y - text_size_.y;
				break;
			case V_ALIGNMENT::TOP:
			default:
				ofs.y = 0;
				break;
			}

			auto oc = rdr.get_clip();
			rdr.set_clip(r);
			rdr.draw_text(r.org + ofs, get_title());
			rdr.set_clip(oc);
		}
	};
}
