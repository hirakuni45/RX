#pragma once
//=====================================================================//
/*!	@file
	@brief	１０キーボード @n
			タッチ操作で数字を入力する、ソフトキーボード
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "gui/widget.hpp"

namespace gui {

	namespace key_10_base {  // キーの位置、キーコードを保持する構造体

		struct location_t {
			vtx::srect	rect;
			char		code;  // normal-code
			constexpr location_t(const vtx::srect& r, char c) noexcept :
				rect(r), code(c)
			{ }
		};

	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	10 ソフトキー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct key_10 : public widget {

		typedef key_10 value_type;

		typedef std::function<void(char)> SELECT_FUNC_TYPE;

	private:

	public:
		static constexpr int16_t BOARD_WIDTH  = 100;  ///< ボード幅
		static constexpr int16_t BOARD_HEIGHT = 100;  ///< ボード高さ

	private:

		static constexpr key_10_base::location_t key_locations_[] = {
			{ { 0, 0, 0, 0 }, '9' }
		};

		struct key_t {
			bool	level;
			bool	positive;
			bool	negative;
			bool	draw;
			key_t() noexcept : level(false), positive(false), negative(true), draw(true) { }
		};
		key_t	key_[10];

		SELECT_FUNC_TYPE	select_func_;
		char	code_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
		*/
		//-----------------------------------------------------------------//
		key_10(const vtx::srect& loc = vtx::srect(0), const char* str = nullptr) noexcept :
			widget(loc, str), key_{ },
			select_func_(), code_(0xff)
		{
			if(at_location().size.x <= 0) {
				at_location().size.x = BOARD_WIDTH;
			}
			if(at_location().size.y <= 0) {
				at_location().size.y = BOARD_HEIGHT;
			}
			insert_widget(this);
		}


		key_10(const key_10& th) = delete;
		key_10& operator = (const key_10& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~key_10() noexcept { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "Key10"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::KEY_10; }


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
			update_touch_def(pos, num);

			auto loc = vtx::srect(get_final_position(), widget::get_location().size);
			uint32_t i = 0;
			for(auto& k : key_) {
				vtx::srect r(loc.org + key_locations_[i].rect.org, key_locations_[i].rect.size);
				auto level = false;
				if(r.is_focus(pos)) {
					level = num > 0;
				}
				k.positive = ( level && !k.level);
				k.negative = (!level &&  k.level);
				k.level = level;
				if(k.positive) {
#if 0
					auto code = key_locations_[i].code;
						if(ctrl_) {
							if(code >= 'a') {
								code_ = code - 0x60;
							} else {
								code_ = code;
							}
						} else if(shift_) {
							code_ = key_locations_[i].shift;
						} else {
							code_ = key_locations_[i].code;
						}
#endif
					k.draw = true;
				}
				if(k.negative) {
					k.draw = true;
				}
				++i;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
		*/
		//-----------------------------------------------------------------//
		void exec_select() noexcept override
		{
			if(code_ != 0xff) {
				if(select_func_) {
					select_func_(code_);
				}
				code_ = 0xff;
			}
		}


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
			@brief	セレクト関数への参照
			@return	セレクト関数
		*/
		//-----------------------------------------------------------------//
		SELECT_FUNC_TYPE& at_select_func() noexcept { return select_func_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
#if 0
			auto r = vtx::srect(get_final_position(), get_location().size);

			uint32_t i = 0;
			for(auto& k : key_) {
				uint8_t inten = 64;
				if(k.level) {
					inten = 192;
				}
				if(k.draw) {
					k.draw = false;
					graphics::share_color sc;
					sc.set_color(get_base_color().rgba8, inten);
					rdr.set_fore_color(sc);
					auto rr = key_locations_[i].rect;
					rr.org += r.org;
					if(k.level) {
						rr.org += 1;
						rr.size -= 2;
					}
					rdr.round_box(rr, 3);

					rdr.set_fore_color(get_font_color());
					char cha;
					if(shift_) {
						cha = key_locations_[i].shift;
					} else {
						cha = key_locations_[i].code;
					}

					vtx::spos sz(8, 16);					
					rdr.draw_font(rr.org + (rr.size - sz) / 2, cha); 
				}
				++i;
			}
#endif
		}
	};
}
