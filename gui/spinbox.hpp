#pragma once
//=====================================================================//
/*!	@file
	@brief	スピンボックス表示と制御 @n
			通常のスピンボックスは、右端に小さい上下ボタンがあるが @n
			タッチパネル操作を考慮して、左右にボタンを配置する @n
			領域を三等分して、左、中央、右を判断する @n
			左右のアクションにより、定数を進めたり、戻したりする。 @n
			長押しの場合、加速する機能を有する。（許可／不許可）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "gui/widget.hpp"
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
			/// 変数初期化は、gcc の拡張機能でー
			/// { .min = -100, .value = 0, .max = 100, .step = 1, .accel = true }

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
			@param[in]	nmb		数値構造体の参照
		*/
		//-----------------------------------------------------------------//
		spinbox(const vtx::srect& loc, const number_t& nmb) noexcept :
			widget(loc, nullptr), select_func_(),
			area_(TOUCH_AREA::CENTER), number_(nmb),
			ace_wait_(0), ace_tick_(0)
		{
			if(get_location().size.y <= 0) {
				at_location().size.y = DEF_SPINBOX_HEIGHT;
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
			@brief	値の変更
			@param[in] value	値
		*/
		//-----------------------------------------------------------------//
		void set_value(int16_t value) noexcept
		{
			if(number_.min <= value && value <= number_.max && number_.value != value) {
				number_.value = value;
				set_update();
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
			rdr.set_fore_color(get_base_color());
			rdr.round_box(r, DEF_SPINBOX_ROUND_RADIUS);

			uint8_t inten = 64;
			if(get_touch_state().level_) {  // 0.75
				inten = 192;
			}

			graphics::share_color sc(0, 0, 0);
			sc.set_color(get_base_color().rgba8, inten);
			rdr.set_fore_color(sc);

			r.org  += DEF_SPINBOX_FRAME_WIDTH;
			r.size -= DEF_SPINBOX_FRAME_WIDTH * 2;
			rdr.round_box(r, DEF_SPINBOX_ROUND_RADIUS - DEF_SPINBOX_FRAME_WIDTH);

			{
				rdr.set_fore_color(get_font_color());
				char tmp[8];  // 最大７桁（符号を入れて）
				utils::sformat("%d", tmp, sizeof(tmp)) % number_.value;
				auto sz = rdr.at_font().get_text_size(tmp);
				rdr.draw_text(r.org + (r.size - sz) / 2, tmp);
			}

			// 左右のポイント描画
			rdr.set_fore_color(get_base_color());
			vtx::spos t[3];
			t[0].x = r.org.x + DEF_SPINBOX_ARROW_SPACE;
			t[0].y = r.org.y + r.size.y / 2;
			t[1].x = t[2].x = r.org.x + DEF_SPINBOX_ARROW_SPACE + DEF_SPINBOX_ARROW_W;
			t[1].y = r.org.y + r.size.y / 2 - DEF_SPINBOX_ARROW_H / 2;
			t[2].y = r.org.y + r.size.y / 2 + DEF_SPINBOX_ARROW_H / 2;
			rdr.fill_triangle(t[0], t[1], t[2]);
			t[0].x = r.end_x() - DEF_SPINBOX_ARROW_SPACE - 1;
			t[1].x = t[2].x = r.end_x() - DEF_SPINBOX_ARROW_SPACE - DEF_SPINBOX_ARROW_W - 1;
			rdr.fill_triangle(t[0], t[2], t[1]);
		}
	};
}
