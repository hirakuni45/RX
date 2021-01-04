#pragma once
//=====================================================================//
/*!	@file
	@brief	テキスト表示と制御 @n
			クリッピングされた描画と、位置の管理などを行う @n
			描画領域より大きなテキスト描画を行う場合は、自動でスクロールを行う。@n
			現状の実装では、複数行はサポートしない。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	テキスト・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct text : public widget {

		typedef text value_type;

	private:

		static const uint16_t	SCROLL_SPEED_FRAME = 3;		///< 標準スクロール速度
		static const uint16_t	SCROLL_WAIT_FRAME = 60 * 6;	///< 標準ホールド時間

		bool		enable_scroll_;
		int16_t		text_draw_h_;
		int16_t		scroll_h_;
		uint16_t	scroll_speed_;
		uint16_t	scroll_delay_;
		uint16_t	scroll_wait_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		初期文字列
		*/
		//-----------------------------------------------------------------//
		text(const vtx::srect& loc = vtx::srect(0), const char* str = "") noexcept :
			widget(loc, str),
			enable_scroll_(true), text_draw_h_(0), scroll_h_(0),
			scroll_speed_(SCROLL_SPEED_FRAME), scroll_delay_(0), scroll_wait_(SCROLL_WAIT_FRAME)
		{
			set_base_color(graphics::def_color::Gray);
			insert_widget(this);
		}


		text(const text& th) = delete;
		text& operator = (const text& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~text() noexcept { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "Text"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::TEXT; }


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-----------------------------------------------------------------//
		void init() noexcept override { }


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新（通常毎フレーム呼ばれる）
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override
		{
			if(enable_scroll_ && text_draw_h_ > get_location().size.x) {
				if(scroll_wait_ > 0) {
					scroll_wait_--;
				} else {
					++scroll_delay_;
					if(scroll_delay_ >= scroll_speed_) {
						scroll_delay_ = 0;
						++scroll_h_;
						if(scroll_h_ == 0) {
							scroll_wait_ = SCROLL_WAIT_FRAME;
						}
						set_update();
						if(scroll_h_ > text_draw_h_) {
							scroll_h_ = -get_location().size.x;
						}					
					}
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
			@param[in]	ena		無効状態にする場合「false」
		*/
		//-----------------------------------------------------------------//
		void exec_select(bool ena = true) noexcept override { }


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
			@brief	スクロールを許可
			@param[in]	ena	不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable_scroll(bool ena = true) noexcept { enable_scroll_ = ena; }


		//-----------------------------------------------------------------//
		/*!
			@brief	スクロールをリセット
		*/
		//-----------------------------------------------------------------//
		void reset_scroll() noexcept
		{
			text_draw_h_ = 0;
			scroll_h_ = 0;
			scroll_speed_ = SCROLL_SPEED_FRAME;
			scroll_delay_ = 0;
			scroll_wait_ = SCROLL_WAIT_FRAME;
			set_update();
		}


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
			auto fsz = rdr.at_font().get_text_size(get_title());
			if(fsz.x < r.size.x) {
				rdr.set_fore_color(get_base_color());
				rdr.fill_box(r);
			} else {
				if(text_draw_h_ != fsz.x) {
					text_draw_h_ = fsz.x;
					scroll_h_ = 0;
					rdr.set_fore_color(get_base_color());
					rdr.fill_box(r);
				}
			}

			rdr.set_fore_color(get_font_color());

			if(fsz.x < r.size.x) {
				rdr.draw_text(vtx::spos(r.org.x, r.org.y + (r.size.y - fsz.y) / 2), get_title());
			} else { 
				if(enable_scroll_ && text_draw_h_ > 0) {
					auto bc = rdr.get_back_color();
					rdr.set_back_color(get_base_color());
					auto oc = rdr.get_clip();
					rdr.set_clip(r);
					auto ex = rdr.draw_text(vtx::spos(r.org.x - scroll_h_,
						r.org.y + (r.size.y - fsz.y) / 2), get_title(),
						false, true);
					rdr.swap_color();
					rdr.fill_box(vtx::srect(ex, r.org.y, 1, r.size.y));
					rdr.set_clip(oc);
					rdr.set_back_color(bc);
				}
			}
		}
	};
}
