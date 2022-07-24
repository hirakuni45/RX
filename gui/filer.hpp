#pragma once
//=====================================================================//
/*!	@file
	@brief	ファイル選択ユーティリティー (widget 版)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/file_io.hpp"
#include "common/fixed_stack.hpp"
#include "gui/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ファイラー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct filer : public widget {

		typedef filer value_type;

//		typedef std::function<void(uint32_t pos, uint32_t num)> SELECT_FUNC_TYPE;

	private:

		typedef utils::dir_list DLIST;
		DLIST		dlist_;

		uint16_t	focus_pos_;
		uint16_t	select_pos_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		タイトル
		*/
		//-----------------------------------------------------------------//
		filer(const vtx::srect& loc = vtx::srect(0), const char* str = nullptr) noexcept :
			widget(loc, str), dlist_(), focus_pos_(0), select_pos_(0)
		{
			insert_widget(this);
		}


		filer(const filer& th) = delete;
		filer& operator = (const filer& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~filer() noexcept { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "Filer"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::FILER; }


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
					auto newpos = st.relative_.y / DEF_FILER_HEIGHT;
				//	if(newpos >= static_cast<int16_t>(num_)) newpos = num_ - 1;
				//	else if(newpos < 0) newpos = 0;
					focus_pos_ = newpos;
				}
			}
			if(st.negative_) {
				if(get_focus()) {
					auto newpos = st.relative_.y / DEF_FILER_HEIGHT;
				//	if(newpos >= 0 && newpos < static_cast<int16_t>(num_)) {
						select_pos_ = newpos;
				//	}
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
		}
	

		//-----------------------------------------------------------------//
		/*!
			@brief	タイトル更新時処理
		*/
		//-----------------------------------------------------------------//
		void update_title() noexcept override
		{
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
			@brief	描画
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = vtx::srect(get_final_position(), get_location().size);
			uint16_t num = r.size.y / DEF_FILER_HEIGHT;
			r.size.y = DEF_FILER_HEIGHT;
			for(uint16_t i = 0; i < num; ++i) {
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
				rdr.fill_box(r);

#if 0
				if(check_draw_ && i == select_pos_) {
					rdr.set_fore_color(get_base_color());
					rdr.fill_box(
						vtx::srect(r.org.x + DEF_MENU_SIGN_SPACE, r.org.y + (r.size.y - DEF_MENU_SIGN_SIZE) / 2,
						DEF_MENU_SIGN_SIZE, DEF_MENU_SIGN_SIZE));
				}

				char tmp[32];
				if(utils::str::get_word(get_title(), i, tmp, sizeof(tmp), ',')) {
					auto sz = rdr.at_font().get_text_size(tmp);
					rdr.set_fore_color(get_font_color());
					rdr.draw_text(r.org + (r.size - sz) / 2, tmp);
				}
#endif
				r.org.y += DEF_FILER_HEIGHT;
			}
		}
	};
}
