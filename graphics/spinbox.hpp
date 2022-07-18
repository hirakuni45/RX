#pragma once
//=====================================================================//
/*!	@file
	@brief	スピンボックス表示と制御 @n
			左右のアクションにより、定数を進めたり、戻したりする。 @n
			長押しの場合、加速する機能を有する。（許可／不許可）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "graphics/widget.hpp"
#include "common/format.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	スピンボックス・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct spinbox : public widget {

		typedef spinbox value_type;

		static constexpr uint8_t ACCEL_WAIT = 75;	///< 加速開始までの遅延（フレーム数）
		static constexpr uint8_t ACCEL_TICK = 4;	///< 加速遅延（フレーム数）

		// 横幅を三等分した領域
		enum class TOUCH_AREA : uint8_t {
			LEFT,		///< 左側領域
			CENTER,		///< 中心領域
			RIGHT,		///< 右側領域
		};

		/// 数値設定構造体
		struct number_t {
			int16_t	min;	///< 最小値
			int16_t	value;	///< 値
			int16_t	max;	///< 最大値
			int16_t	step;	///< 加算、減算幅
			bool	accel;	///< 数値変更の加速を有効にする場合「true」
//			number_t() noexcept : min(0), value(0), max(0), step(1), accel(false) { }

			void add() noexcept
			{
				if((value + step) <= max) {
					value += step;
				}
			}

			void sub() noexcept
			{
				if(min <= (value - step)) {
					value -= step;
				}
			}
		};

		typedef std::function<void(TOUCH_AREA, int16_t)> SELECT_FUNC_TYPE;	///< 選択関数型

	private:

		SELECT_FUNC_TYPE	select_func_;
		TOUCH_AREA			area_;
		number_t			number_;
		uint8_t				ace_wait_;
		uint8_t				ace_tick_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター（整数版）
			@param[in]	loc		ロケーション
			@param[in]	min		最小値
			@param[in]	max		最大値
			@param[in]	org		初期値
			@param[in]	ace		アクセレーターを許可する場合「true」
		*/
		//-----------------------------------------------------------------//
		spinbox(const vtx::srect& loc, const number_t& nmb) noexcept :
			widget(loc, nullptr), select_func_(),
			area_(TOUCH_AREA::CENTER), number_(nmb),
			ace_wait_(0), ace_tick_(0)
		{
			if(get_location().size.x <= 0) {
			}
			if(get_location().size.y <= 0) {
				at_location().size.y = DEF_FRAME_HEIGHT;
			}
			insert_widget(this);
		}


		spinbox(const spinbox& th) = delete;
		spinbox& operator = (const spinbox& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~spinbox() { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "SpinBox"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::SPINBOX; }


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
			if(get_touch_state().level_) {
				if(number_.accel) {
					if(ace_wait_ < ACCEL_WAIT) {
						++ace_wait_;
					} else {
						if(ace_tick_ < ACCEL_TICK) {
							++ace_tick_;
						} else {
							ace_tick_ = 0;
							set_exec_request();
						}
					}
				}
				auto pos = get_touch_state().relative_.x;
				if(pos <= (get_location().size.x / 3)) {
					area_ = TOUCH_AREA::LEFT;
				} else if((get_location().size.x * 2 / 3) <= pos) {
					area_ = TOUCH_AREA::RIGHT;
				} else {
					area_ = TOUCH_AREA::CENTER;
				}
			} else {
				ace_wait_ = 0;
				ace_tick_ = 0;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
		*/
		//-----------------------------------------------------------------//
		void exec_select() noexcept override
		{
			if(area_ == TOUCH_AREA::LEFT) {
				number_.sub();
			} else if(area_ == TOUCH_AREA::RIGHT) {
				number_.add();
			}
			if(select_func_) {
				select_func_(area_, number_.value);
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
			@brief	セレクト関数への参照
			@return	セレクト関数
		*/
		//-----------------------------------------------------------------//
		SELECT_FUNC_TYPE& at_select_func() noexcept { return select_func_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	数値構造体の取得
			@return	数値構造体
		*/
		//-----------------------------------------------------------------//
		const auto& get_number() const noexcept { return number_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	数値構造体の参照
			@return	数値構造体
		*/
		//-----------------------------------------------------------------//
		auto& at_number() const noexcept { return number_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画
			@param[in]	rdr		描画インスタンス
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = vtx::srect(get_final_position(), get_location().size);
			
			uint8_t inten = 64;
			if(get_touch_state().level_) {  // 0.75
				inten = 192;
			}

			graphics::share_color sc(0, 0, 0);
			sc.set_color(get_base_color().rgba8, inten);
			rdr.set_fore_color(sc);
			{
				auto t = r;
				t.size.x = r.size.x - (DEF_ITEM_SPACE * 2 + DEF_ITEM_CHECK);
				switch(area_) {
				case TOUCH_AREA::LEFT:
					rdr.round_box(t, DEF_ROUND_RADIUS);
					break;
				case TOUCH_AREA::RIGHT:
					t.org.x = r.org.x + (DEF_ITEM_SPACE * 2 + DEF_ITEM_CHECK);
					rdr.round_box(t, DEF_ROUND_RADIUS);
					break;
				default:
					rdr.round_box(r, DEF_ROUND_RADIUS);
					break;
				}
			}

			rdr.set_fore_color(get_font_color());
			{
				char tmp[10];
				utils::sformat("%d", tmp, sizeof(tmp)) % number_.value;
				auto sz = rdr.at_font().get_text_size(tmp);
				rdr.draw_text(r.org + (r.size - sz) / 2, tmp);
			}
///			auto sz = rdr.at_font().get_text_size(get_title());
///			rdr.draw_text(r.org + (r.size - sz) / 2, get_title());

			// 左右のポイント描画
			rdr.set_fore_color(get_base_color());
			vtx::srect t;
			t.org.x = r.org.x + DEF_ITEM_SPACE;
			t.org.y = r.org.y + (r.size.y - DEF_ITEM_CHECK) / 2;
			t.size.x = t.size.y = DEF_ITEM_CHECK;
			rdr.fill_box(t);
			t.org.x = r.end_x() - DEF_ITEM_SPACE - DEF_ITEM_SPACE - 1;
			rdr.fill_box(t);
		}
	};
}
