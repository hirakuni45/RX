#pragma once
//=====================================================================//
/*!	@file
	@brief	スピンボックス表示と制御 @n
			左右のアクションにより、内部の定数、文字列を選択
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

		// 横幅を三等分した領域
		enum class TOUCH_AREA : uint8_t {
			LEFT,		///< 左側領域
			CENTER,		///< 中心領域
			RIGHT,		///< 右側領域
		};

		typedef std::function<void(uint32_t, TOUCH_AREA)> SELECT_FUNC_TYPE;

	private:

		SELECT_FUNC_TYPE	select_func_;
		uint32_t			select_id_;
		int16_t				min_;
		int16_t				max_;
		int16_t				org_;
		TOUCH_AREA			area_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター（整数版）
			@param[in]	loc		ロケーション
			@param[in]	min		最小値
			@param[in]	max		最大値
			@param[in]	org		初期値
		*/
		//-----------------------------------------------------------------//
		spinbox(const vtx::srect& loc, int16_t min, int16_t max, int16_t org = 0) noexcept :
			widget(loc, ""), select_func_(), select_id_(0),
			min_(min), max_(max), org_(org), area_(TOUCH_AREA::CENTER)
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
				auto pos = get_touch_state().relative_.x;
				if(pos <= (get_location().size.x / 3)) {
					area_ = TOUCH_AREA::LEFT;
				} else if((get_location().size.x * 2 / 3) <= pos) {
					area_ = TOUCH_AREA::RIGHT;
				} else {
					area_ = TOUCH_AREA::CENTER;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
			@param[in]	ena		無効状態にする場合「false」
		*/
		//-----------------------------------------------------------------//
		void exec_select(bool ena = true) noexcept override
		{
			++select_id_;
			if(min_ < max_) {
				if(area_ == TOUCH_AREA::LEFT) {
					if(min_ < org_) {
						org_--;
					}
				} else if(area_ == TOUCH_AREA::RIGHT) {
					if(org_ < max_) {
						++org_;
					}
				}
			}
			if(select_func_) {
				select_func_(select_id_, area_);
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
			@brief	セレクト ID の取得
			@return	セレクト ID
		*/
		//-----------------------------------------------------------------//
		uint32_t get_select_id() const noexcept { return select_id_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト関数への参照
			@return	セレクト関数
		*/
		//-----------------------------------------------------------------//
		SELECT_FUNC_TYPE& at_select_func() noexcept { return select_func_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	最小値の取得
			@return	最小値
		*/
		//-----------------------------------------------------------------//
		auto get_min() const noexcept { return min_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	最大値の取得
			@return	最大値
		*/
		//-----------------------------------------------------------------//
		auto get_max() const noexcept { return max_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	値の取得
			@return	値
		*/
		//-----------------------------------------------------------------//
		auto get_value() const noexcept { return org_; }


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
//			rdr.set_fore_color(get_base_color());
//			rdr.round_box(r, DEF_ROUND_RADIUS);

			uint8_t inten = 64;
			if(get_touch_state().level_) {  // 0.75
				inten = 192;
			}

			graphics::share_color sh(0, 0, 0);
			sh.set_color(get_base_color().rgba8, inten);
			rdr.set_fore_color(sh);
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
			if(min_ < max_) {
				char tmp[10];
				utils::sformat("%d", tmp, sizeof(tmp)) % org_;
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
