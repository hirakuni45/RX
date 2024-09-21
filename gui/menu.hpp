#pragma once
//=====================================================================//
/*!	@file
	@brief	メニュー・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "gui/widget.hpp"
#include "common/string_utils.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	メニュー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct menu : public widget {

		typedef menu value_type;

		typedef std::function<void(uint32_t pos, uint32_t num)> SELECT_FUNC_TYPE;

	private:

		SELECT_FUNC_TYPE	select_func_;
		vtx::spos			item_size_;
		bool				check_draw_;
		char				sch_;
		uint16_t			num_;
		uint16_t			focus_pos_;
		uint16_t			select_pos_;


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		メニュー・アイテム文字列
			@param[in]	chd		チェック描画を行わない場合「false」
			@param[in]	sch		セパレート・キャラクタ
		*/
		//-----------------------------------------------------------------//
		menu(const vtx::srect& loc = vtx::srect(0), const char* str = nullptr, bool chd = true, char sch = ',')
			noexcept :
			widget(loc, str),
			select_func_(), item_size_(0),
			check_draw_(chd), sch_(sch),
			num_(utils::str::get_words(str, sch)), focus_pos_(0), select_pos_(0)
		{
			if(loc.size.y <= 0) {
				at_location().size.y = num_ * DEF_MENU_HEIGHT;
				item_size_.y = DEF_MENU_HEIGHT;
			} else {
				if(num_ > 0) {
					item_size_.y = loc.size.y / num_;
				}
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
		*/
		//-----------------------------------------------------------------//
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override
		{
			update_touch_def(pos, num, false);
			const auto& st = get_touch_state();
			if(st.level_) {
				if(get_focus()) {
					auto newpos = st.relative_.y / item_size_.y;
					if(newpos >= static_cast<int16_t>(num_)) newpos = num_ - 1;
					else if(newpos < 0) newpos = 0;
					focus_pos_ = newpos;
				}
			}
			if(st.negative_) {
				if(get_focus()) {
					auto newpos = st.relative_.y / item_size_.y;
					if(newpos >= 0 && newpos < static_cast<int16_t>(num_)) {
						select_pos_ = newpos;
					}
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
		*/
		//-----------------------------------------------------------------//
		void exec_select() noexcept override
		{
			if(select_func_) {
				select_func_(select_pos_, num_);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	タイトル更新時処理 @n
					「タイトル」は、メニューのアイテムとする。
		*/
		//-----------------------------------------------------------------//
		void update_title() noexcept override
		{
			num_ = utils::str::get_words(get_title(), sch_);
			at_location().size.y = num_ * item_size_.y;
			if(select_pos_ >= num_) {
				select_pos_ = num_ - 1;
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
			if(ena) {
				set_state(STATE::ENABLE);
			} else {
				set_state(STATE::DISABLE);
				reset_touch_state();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アイテム数の取得
			@return	アイテム数
		*/
		//-----------------------------------------------------------------//
		uint32_t get_item_num() const noexcept { return num_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト位置の取得
			@return	セレクト位置
		*/
		//-----------------------------------------------------------------//
		uint32_t get_select_pos() const noexcept { return select_pos_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト位置の設定
			@param[in]	pos	セレクト位置
		*/
		//-----------------------------------------------------------------//
		void set_select_pos(uint32_t pos) noexcept { select_pos_ = pos; }


		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト位置の文字取得
			@param[in]	dst		文字列バッファ
			@param[in]	len		文字列バッファサイズ
			@return	セレクト位置
		*/
		//-----------------------------------------------------------------//
		uint32_t get_select_text(char* dst, uint32_t len) const noexcept
		{
			utils::str::get_word(get_title(), select_pos_, dst, len, sch_);
			return select_pos_;
		}


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
			@param[in] rdr	描画インスタンス
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			if(num_ == 0 || get_title() == nullptr) return;

			auto r = vtx::srect(get_final_position(), get_location().size);
			r.size.y /= num_;
			for(uint16_t i = 0; i < num_; ++i) {
				uint8_t inten = 64;
				if(get_touch_state().level_ && focus_pos_ == i) {
					inten = 192;
				} else {
					if(i & 1) {
						inten = 96;
					} else {
						inten = 128;
					}
				}
				graphics::share_color sc(0, 0, 0);
				sc.set_color(get_base_color().rgba8, inten);
				rdr.set_fore_color(sc);
				bool up = false;
				bool dn = false;
				if(i == 0) up = true;
				if(i == (num_ - 1)) dn = true;
				rdr.round_box(r, DEF_MENU_ROUND_RADIUS, up, dn);

				if(check_draw_ && i == select_pos_) {
					rdr.set_fore_color(get_base_color());
					rdr.fill_box(
						vtx::srect(r.org.x + DEF_MENU_SIGN_SPACE, r.org.y + (r.size.y - DEF_MENU_SIGN_SIZE) / 2,
						DEF_MENU_SIGN_SIZE, DEF_MENU_SIGN_SIZE));
				}

				char tmp[32];
				if(utils::str::get_word(get_title(), i, tmp, sizeof(tmp), sch_)) {
					auto sz = rdr.at_font().get_text_size(tmp);
					rdr.set_fore_color(get_font_color());
					rdr.draw_text(r.org + (r.size - sz) / 2, tmp);
				}
				r.org.y += r.size.y;
			}
		}
	};
}
