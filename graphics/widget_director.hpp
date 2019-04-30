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
#include "graphics/group.hpp"
#include "graphics/frame.hpp"
#include "graphics/button.hpp"
#include "graphics/check.hpp"
#include "graphics/radio.hpp"
#include "graphics/slider.hpp"

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
			widget*			w_;
			widget::STATE	state_;
			bool			init_;
			bool			focus_;
			bool			draw_;
			widget_t() : w_(nullptr), state_(widget::STATE::DISABLE),
				init_(false), focus_(false), draw_(false) { }
		};

		typedef std::array<widget_t, WNUM> WIDGETS; 

	private:
		using GLC = typename RDR::glc_type;

		RDR&		rdr_;
		TOUCH&		touch_;

		WIDGETS		widgets_;

		// ipass 自分を含めない場合「false」
		uint32_t create_childs_(widget* w, widget_t** list, uint32_t max, bool ipass)
		{
			uint16_t idx = 0;
			for(auto& t : widgets_) {
				if(t.w_ == nullptr) continue;
				if(t.w_->get_state() == widget::STATE::STALL) continue;
				if(ipass && t.w_ == w) continue;
				if(t.w_->get_parents() == w->get_parents()) {
					if(max > idx) {
						list[idx] = &t;
						++idx;
					} else {
						break;
					}
				}
			}
			return idx;
		}

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
					t.init_ = false;
					t.draw_ = true;
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
					if(!t.init_) {  // 初期化プロセス
						t.w_->init();
						t.init_ = true;
						t.draw_ = true;
					}
					if(t.state_ != t.w_->get_state()) {
						t.state_ = t.w_->get_state();
						t.draw_ = true;
					}
					if(t.w_->get_state() == widget::STATE::ENABLE) {
						t.w_->update_touch(vtx::spos(tp.x, tp.y), num);
					}
					if(t.focus_ != t.w_->get_focus()) {
						t.focus_ = t.w_->get_focus();
						t.draw_ = true;
					}
				}
			}

			for(auto& t : widgets_) {
				if(t.w_ == nullptr) continue;
				if(t.w_->get_state() == widget::STATE::ENABLE) {
					const auto& ts = t.w_->get_touch_state();
					if(ts.negative_) {
						t.w_->exec_select();
						t.draw_ = true;
						if(t.w_->get_id() == widget::ID::RADIO) {
							widget_t* list[8];
							auto n = create_childs_(t.w_, list, 8, true);
							for(uint16_t i = 0; i < n; ++i) {
								list[i]->w_->exec_select(false);
								list[i]->draw_ = true;
							}
						}
					}
					if(ts.positive_) {
						t.draw_ = true;
					}
					if(ts.level_) {
						if(t.w_->get_id() == widget::ID::SLIDER) {
							t.w_->exec_select();
							t.draw_ = true;
						}
					}
				}
			}

			for(auto& t : widgets_) {
				if(t.w_ == nullptr) continue;
				if(t.w_->get_state() == widget::STATE::DISABLE) continue;
				if(!t.draw_) continue; 
				t.draw_ = false;

				switch(t.w_->get_id()) {
				case widget::ID::GROUP:
					break;
				case widget::ID::FRAME:
					{
						auto* w = dynamic_cast<frame*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::BUTTON:
					{
						auto* w = dynamic_cast<button*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::CHECK:
					{
						auto* w = dynamic_cast<check*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::RADIO:
					{
						auto* w = dynamic_cast<radio*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::SLIDER:
					{
						auto* w = dynamic_cast<slider*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
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

