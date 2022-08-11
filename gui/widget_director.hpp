#pragma once
//=====================================================================//
/*!	@file
	@brief	Widget ディレクター
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <array>
#include "gui/widget.hpp"
#include "gui/group.hpp"
#include "gui/frame.hpp"
#include "gui/box.hpp"
#include "gui/text.hpp"
#include "gui/textbox.hpp"
#include "gui/dialog.hpp"
#include "gui/button.hpp"
#include "gui/check.hpp"
#include "gui/radio.hpp"
#include "gui/slider.hpp"
#include "gui/menu.hpp"
#include "gui/term.hpp"
#include "gui/spinbox.hpp"
#include "gui/toggle.hpp"
#include "gui/progress.hpp"
#include "gui/closebox.hpp"
#include "gui/filer.hpp"
#include "gui/key_asc.hpp"
#include "gui/key_10.hpp"

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
			const char*		title_;	// タイトルの変化を監視するパッド
			widget::STATE	state_;
			bool			init_;
			bool			focus_;
			bool			draw_;
			bool			refresh_;
			uint8_t			exec_request_;
			widget_t() : w_(nullptr), title_(nullptr),
				state_(widget::STATE::DISABLE),
				init_(false), focus_(false), draw_(false), refresh_(false),
				exec_request_(0) { }
		};

		typedef std::array<widget_t, WNUM> WIDGETS; 

	private:
		using GLC = typename RDR::glc_type;

		RDR&		rdr_;
		TOUCH&		touch_;

		WIDGETS		widgets_;

		graphics::share_color	back_color_;

		widget*		current_;


		// ipass 自分を含めない場合「false」
		// 「子」のリストを作成
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

		// 領域に含まれる widget に描画を設定
		// return: 描画数（widget 単位）
		uint32_t redraw_overlap_widget_(widget* area)
		{
			uint32_t cnt = 0;
			for(auto& t : widgets_) {
				if(t.w_ == nullptr) continue;
				if(t.w_->get_state() == widget::STATE::STALL) continue;
				if(t.w_ == area) continue;  // 自分は評価しない
				if(t.w_->get_parents() != nullptr) continue;  // 子は評価しない
				if(area->get_location().is_overlap(t.w_->get_location())) {
					t.w_.draw_ = true;
					++cnt;
				}
			}
			return cnt;
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
			rdr_(rdr), touch_(touch), widgets_(),
			back_color_(graphics::def_color::Black), current_(nullptr)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	全クリア
		*/
		//-----------------------------------------------------------------//
		void clear() noexcept
		{
			rdr_.clear(back_color_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カレント widget を取得（最後に操作した widget）
			@return カレント widget
		*/
		//-----------------------------------------------------------------//
		auto get_current_widget() const noexcept { return current_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	背面色の設定
			@param[in]	color	背面色
		*/
		//-----------------------------------------------------------------//
		void set_back_color(const graphics::share_color& color) noexcept
		{
			back_color_ = color;
		}


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
					t.title_ = w->get_title();
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
			@brief	該当するレイヤーを許可、不許可
			@param[in]	bits	レイヤービット
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable(uint8_t bits, bool ena = true) noexcept
		{
			for(auto& t : widgets_) {
				if(t.w_ == nullptr) continue;
				if((t.w_->get_layer_bits() & bits) != 0) {
					t.w_->enable(ena);
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	該当するレイヤーを許可、不許可
			@param[in]	layer	レイヤー
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable(widget::LAYER layer, bool ena = true) noexcept
		{
			enable(1 << static_cast<uint8_t>(layer), ena);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	再描画設定
		*/
		//-----------------------------------------------------------------//
		void redraw_all() noexcept
		{
			for(auto& t : widgets_) {
				if(t.w_ == nullptr) continue;
				if(t.w_->get_state() == widget::STATE::ENABLE) {
					t.draw_ = true;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リフレッシュ描画設定
		*/
		//-----------------------------------------------------------------//
		void refresh() noexcept
		{
			for(auto& t : widgets_) {
				if(t.w_ == nullptr) continue;
				if(t.w_->get_state() == widget::STATE::ENABLE) {
					t.refresh_ = true;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アップデート（管理と描画）
			@return 書き換えアイテムがあれば「true」
		*/
		//-----------------------------------------------------------------//
		bool update() noexcept
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
						if(t.state_ != widget::STATE::DISABLE) {
							t.draw_ = true;
						}
					}
					if(t.w_->get_state() == widget::STATE::ENABLE) {
						t.w_->update_touch(tp.pos, num);
					}
					if(t.focus_ != t.w_->get_focus()) {
						t.focus_ = t.w_->get_focus();
						t.draw_ = true;
					}
					if(t.w_->get_title() != t.title_) {  // タイトル変更で再描画
						t.w_->update_title();  // タイトル更新前処理
						t.title_ = t.w_->get_title();
						t.draw_ = true;
					}
					if(t.w_->get_update()) {  // 描画更新リクエス？
						t.w_->set_update(false);
						t.draw_ = true;
					}
				}
			}

			for(auto& t : widgets_) {
				if(t.w_ == nullptr) continue;
				if(t.w_->get_state() == widget::STATE::ENABLE) {
					const auto& ts = t.w_->get_touch_state();
					if(ts.negative_ || t.exec_request_ != t.w_->get_exec_request()) {
						t.exec_request_ = t.w_->get_exec_request();
						t.w_->exec_select();
						current_ = t.w_;
						t.draw_ = true;
						if(t.w_->get_id() == widget::ID::RADIO) {  // ラジオボタン、個別案件の処理
							widget_t* list[16];
							auto n = create_childs_(t.w_, list, 16, true);  // 自分以外のラジオボタンを集める
							for(uint16_t i = 0; i < n; ++i) {
								auto* w = dynamic_cast<radio*>(list[i]->w_);
								if(w->get_switch_state()) {  // 許可されているボタンを不許可にする。
									w->exec_select();
									list[i]->draw_ = true;
								} else {
									continue;
								}
							}
						}
					}
					if(ts.positive_) {
						t.draw_ = true;
					}
					if(ts.level_) {
						if(t.w_->get_id() == widget::ID::SLIDER) {  // スライダー、個別案件の処理
							t.draw_ = true;
						} else if(t.w_->get_id() == widget::ID::MENU) {  // メニュー、個別案件の処理
							t.draw_ = true;
						}
					}
				}
			}

			uint32_t dc = 0;
			for(auto& t : widgets_) {
				if(t.w_ == nullptr) continue;
				if(t.w_->get_state() == widget::STATE::DISABLE) continue;
				bool draw = false;
				if(t.draw_) {
					draw = true;
					t.draw_ = false;
					++dc;
				}
				if(t.refresh_) {
					draw = true;
					t.refresh_ = false;
				}
				if(!draw) continue;

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
				case widget::ID::BOX:
					{
						auto* w = dynamic_cast<box*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::TEXT:
					{
						auto* w = dynamic_cast<text*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::TEXTBOX:
					{
						auto* w = dynamic_cast<textbox*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::DIALOG:
					{
						auto* w = dynamic_cast<dialog*>(t.w_);
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
				case widget::ID::MENU:
					{
						auto* w = dynamic_cast<menu*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::TERM:
					{
						auto* w = dynamic_cast<term*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::SPINBOX:
					{
						auto* w = dynamic_cast<spinbox*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::TOGGLE:
					{
						auto* w = dynamic_cast<toggle*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::PROGRESS:
					{
						auto* w = dynamic_cast<progress*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::CLOSEBOX:
					{
						auto* w = dynamic_cast<closebox*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::FILER:
					{
						auto* w = dynamic_cast<filer*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::KEY_ASC:
					{
						auto* w = dynamic_cast<key_asc*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				case widget::ID::KEY_10:
					{
						auto* w = dynamic_cast<key_10*>(t.w_);
						if(w == nullptr) break;
						w->draw(rdr_);
					}
					break;
				}
			}
			return dc != 0;
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
