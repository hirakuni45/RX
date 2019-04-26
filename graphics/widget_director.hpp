#pragma once
//=====================================================================//
/*!	@file
	@brief	Widget ディレクター
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <array>
#include "graphics/widget.hpp"
#include "graphics/frame.hpp"
#include "graphics/button.hpp"
#include "graphics/check.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	Widget ディレクター
		@param[in]	RDR		レンダークラス
		@param[in]	TOUCH	タッチクラス
		@param[in]	WNUM	widget の最大管理数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RDR, class TOUCH, uint32_t WNUM>
	struct widget_director {

		struct widget_t {
			widget*		w_;
			widget_t() : w_(nullptr) { }
		};

		typedef std::array<widget_t, WNUM> WIDGETS; 

	private:
		using GLC = typename RDR::glc_type;

		RDR&		rdr_;
		TOUCH&		touch_;

		WIDGETS		widgets_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	rdr		描画クラス
			@param[in]	touch	タッチクラス
		*/
		//-----------------------------------------------------------------//
		widget_director(RDR& rdr, TOUCH& touch) noexcept :
			rdr_(rdr), touch_(touch), widgets_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	widget の登録
			@param[in]	w	widget のポインター
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool insert(widget* w) noexcept
		{
			for(auto& t : widgets_) {
				if(t.w_ == nullptr) {
					t.w_ = w;
					return true;
				}
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	widget の解除
			@param[in]	w	widget のポインター
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool remove(widget* w) noexcept
		{
			for(auto& t : widgets_) {
				if(t.w_ == w) {
					t.w_ = nullptr;
					return true;
				}
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	四角を描画
		*/
		//-----------------------------------------------------------------//
		void draw_square(const vtx::srect& rect, const char* text) noexcept
		{
			auto sz = rdr_.at_font().get_text_size(text);
			rdr_.swap_color();
			rdr_.fill_box(rect);
			rdr_.swap_color();
			rdr_.draw_text(rect.org + (rect.size - sz) / 2, text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ラウンドした四角を描画
		*/
		//-----------------------------------------------------------------//
		void draw_round(const vtx::srect& rect, const char* text, int16_t radius) noexcept
		{
			rdr_.swap_color();
			rdr_.round_box(rect, radius);
			rdr_.swap_color();
			auto sz = rdr_.at_font().get_text_size(text);
			rdr_.draw_text(rect.org + (rect.size - sz) / 2, text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アップデート（管理と描画）
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			// 状態の生成とGUIへ反映
			{
				auto num = touch_.get_touch_num();
				const auto& tp = touch_.get_touch_pos(0);
				for(auto& t : widgets_) {
					if(t.w_ == nullptr) continue;
					if(t.w_->get_state() == widget::STATE::DISABLE) continue;
					t.w_->update_touch(vtx::spos(tp.x, tp.y), num);
				}
			}

			for(auto& t : widgets_) {
				if(t.w_ == nullptr) continue;
				if(t.w_->get_state() == widget::STATE::DISABLE) continue;

				switch(t.w_->get_id()) {
				case widget_set::ID::FRAME:
					{
						auto* w = dynamic_cast<frame*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget_set::ID::BUTTON:
					{
						auto* w = dynamic_cast<button*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);

						if(w->get_touch_state().neg_) {
							w->exec_select();
						}
						if(w->get_touch_state().pos_) {
						}
						if(w->get_touch_state().lvl_) {
						}
					}
					break;
				case widget_set::ID::CHECK:
					{

					}
					break;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	管理リスト表示（デバッグ用）
		*/
		//-----------------------------------------------------------------//
		void list_all() noexcept
		{
			for(auto& t : widgets_) {
				widget* w = t.w_;
				if(w != nullptr) {
					utils::format("%s: id(%d)") % w->get_name() % static_cast<int>(w->get_id());
					const auto& t = w->get_location(); 
					utils::format(" %d, %d, %d, %d") % t.org.x % t.org.y % t.size.x % t.size.y;
					utils::format(" State: %d") % static_cast<int>(w->get_state());
					utils::format("\n");
				}
			}
		}
	};
}

