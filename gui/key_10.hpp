#pragma once
//=========================================================================//
/*!	@file
	@brief	１０キーボード @n
			タッチ操作で数字を入力する、ソフトキーボード
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
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


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	10 ソフトキー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct key_10 : public widget {

		typedef key_10 value_type;

		//=================================================================//
		/*!
			@brief	ボタンの配置スタイル型
		*/
		//=================================================================//
		enum class STYLE : uint8_t {
			W3_H4,	///< 横に３個、縦に４個の並び
			W5_H2,	///< 横に５個、縦に２個の並び
		};


		//=================================================================//
		/*!
			@brief	キーマップ型
		*/
		//=================================================================//
		enum class KEY_MAP : uint8_t {
			_9,
			_8,
			_7,
			_6,
			_5,
			_4,
			_3,
			_2,
			_1,
			_0,
			NONE
		};

		typedef std::function<void(char, KEY_MAP)> SELECT_FUNC_TYPE;

	private:
		static constexpr int16_t space = 10;  // 隙間

		static constexpr int16_t sz_x = 40;  // 通常幅

		static constexpr int16_t sz_y = 40;  // 通常高

		static constexpr int16_t g0_x = 0;
		static constexpr int16_t g1_x = g0_x + space * 1 + sz_x * 1;
		static constexpr int16_t g2_x = g0_x + space * 2 + sz_x * 2;
		static constexpr int16_t g3_x = g0_x + space * 3 + sz_x * 3;
		static constexpr int16_t g4_x = g0_x + space * 4 + sz_x * 4;

		static constexpr int16_t g0_y = 0;
		static constexpr int16_t g1_y = g0_y + space * 1 + sz_y * 1;
		static constexpr int16_t g2_y = g0_y + space * 2 + sz_y * 2;
		static constexpr int16_t g3_y = g0_y + space * 3 + sz_y * 3;

	public:

		//-----------------------------------------------------------------//
		/*!
			@brief	ボードサイズを取得
			@param[in]	style	ボード・スタイル
			@return ボードサイズ
		*/
		//-----------------------------------------------------------------//
		static constexpr vtx::spos get_board_size(STYLE style)
		{
			switch(style) {
			case STYLE::W3_H4:
				return vtx::spos(sz_x * 3 + space * 2, sz_y * 4 + space * 3);
			case STYLE::W5_H2:
				return vtx::spos(sz_x * 5 + space * 4, sz_x * 2 + space * 1);
			}
			return vtx::spos(0);
		}

	private:

		static constexpr key_10_base::location_t key_locations_[2][10] = {
			{  // W3_H4
				{ { g0_x, g0_y, sz_x, sz_y }, '9' },
				{ { g1_x, g0_y, sz_x, sz_y }, '8' },
				{ { g2_x, g0_y, sz_x, sz_y }, '7' },
				{ { g0_x, g1_y, sz_x, sz_y }, '6' },
				{ { g1_x, g1_y, sz_x, sz_y }, '5' },
				{ { g2_x, g1_y, sz_x, sz_y }, '4' },
				{ { g0_x, g2_y, sz_x, sz_y }, '3' },
				{ { g1_x, g2_y, sz_x, sz_y }, '2' },
				{ { g2_x, g2_y, sz_x, sz_y }, '1' },
				{ { g1_x, g3_y, sz_x, sz_y }, '0' }
			}, {  // W5_H2
				{ { g0_x, g0_y, sz_x, sz_y }, '9' },
				{ { g1_x, g0_y, sz_x, sz_y }, '8' },
				{ { g2_x, g0_y, sz_x, sz_y }, '7' },
				{ { g3_x, g0_y, sz_x, sz_y }, '6' },
				{ { g4_x, g0_y, sz_x, sz_y }, '5' },
				{ { g0_x, g1_y, sz_x, sz_y }, '4' },
				{ { g1_x, g1_y, sz_x, sz_y }, '3' },
				{ { g2_x, g1_y, sz_x, sz_y }, '2' },
				{ { g3_x, g1_y, sz_x, sz_y }, '1' },
				{ { g4_x, g1_y, sz_x, sz_y }, '0' }
			}
		};

		static const auto& get_key_locations_(STYLE style, uint32_t item)
		{
			return key_locations_[static_cast<uint32_t>(style)][item];
		}

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
		KEY_MAP	key_map_;
		STYLE	style_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	style	ボタンの配置スタイル（標準は「縦型」）
		*/
		//-----------------------------------------------------------------//
		key_10(const vtx::srect& loc = vtx::srect(0), STYLE style = STYLE::W3_H4) noexcept :
			widget(loc, nullptr), key_{ },
			select_func_(), code_(0xff), key_map_(KEY_MAP::NONE), style_(style)
		{
			if(at_location().size.x <= 0) {
				at_location().size.x = get_board_size(style).x;
			}
			if(at_location().size.y <= 0) {
				at_location().size.y = get_board_size(style).y;
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
			@brief	ハイブリッド・タイプか検査
			@return ハイブリッドの場合「true」
		*/
		//-----------------------------------------------------------------//
		bool hybrid() const noexcept override { return true; }


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
				auto key_loc = get_key_locations_(style_, i);
				vtx::srect r(loc.org + key_loc.rect.org, key_loc.rect.size);
				auto level = false;
				if(r.is_focus(pos)) {
					level = num > 0;
				}
				k.positive = ( level && !k.level);
				k.negative = (!level &&  k.level);
				k.level = level;
				if(k.positive) {
					code_ = key_loc.code;
					key_map_ = static_cast<KEY_MAP>(i);
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
					select_func_(code_, key_map_);
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
				request_redraw();
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
			@brief	全体再描画をリクエスト
		*/
		//-----------------------------------------------------------------//
		void request_redraw() noexcept
		{
			for(auto& k : key_) {
				k.draw = true;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	描画
			@param[in] rdr	描画インスタンス
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = vtx::srect(get_final_position(), get_location().size);

			uint32_t i = 0;
			for(auto& k : key_) {
				auto key_loc = get_key_locations_(style_, i);
				uint8_t inten = 64;
				if(k.level) {
					inten = 192;
				}
				if(k.draw) {
					k.draw = false;
					graphics::share_color sc;
					sc.set_color(get_base_color().rgba8, inten);
					rdr.set_fore_color(sc);
					auto rr = key_loc.rect;
					rr.org += r.org;
					if(k.level) {
						rr.org += 1;
						rr.size -= 2;
					}
					auto rad = rr.size.x / 2;
					rdr.fill_circle(rr.org + rr.size / 2, rad);

					rdr.set_fore_color(get_font_color());
					auto cha = key_loc.code;
					vtx::spos sz(8, 16);					
					rdr.draw_font(rr.org + (rr.size - sz) / 2, cha); 
				}
				++i;
			}
		}
	};
}
