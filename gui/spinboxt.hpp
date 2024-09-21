#pragma once
//=====================================================================//
/*!	@file
	@brief	スピンボックス表示と制御（テキスト） @n
			通常のスピンボックスは、右端に小さい上下ボタンがあるが @n
			タッチパネル操作を考慮して、左右にボタンを配置する @n
			領域を三等分して、左、中央、右を判断する @n
			左右のアクションにより、ワードを進めたり、戻したりする。 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "gui/widget.hpp"
#include "common/format.hpp"
#include "common/string_utils.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	スピンボックス・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct spinboxt : public widget {

		typedef spinboxt value_type;

		// 横幅を三等分した領域
		enum class TOUCH_AREA : uint8_t {
			LEFT,		///< 左側領域
			CENTER,		///< 中心領域
			RIGHT,		///< 右側領域
		};

		typedef std::function<void(TOUCH_AREA, uint16_t pos, uint16_t num)> SELECT_FUNC_TYPE;	///< 選択関数型

	private:

		SELECT_FUNC_TYPE	select_func_;
		TOUCH_AREA			area_;
		vtx::spos			item_size_;
		char				sch_;
		uint16_t			num_;
		uint16_t			select_pos_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター（整数版）
			@param[in]	loc		ロケーション
			@param[in]	str		アイテム文字列
			@param[in]	sch		セパレート・キャラクタを指定する場合
		*/
		//-----------------------------------------------------------------//
		spinboxt(const vtx::srect& loc, const char* str, char sch = ',') noexcept :
			widget(loc, str), select_func_(),
			area_(TOUCH_AREA::CENTER),
			item_size_(0),
			sch_(sch), num_(utils::str::get_words(str, sch_)), select_pos_(0)
		{
			if(get_location().size.y <= 0) {
				at_location().size.y = DEF_SPINBOXT_HEIGHT;
			}
			insert_widget(this);
		}


		spinboxt(const spinboxt& th) = delete;
		spinboxt& operator = (const spinboxt& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~spinboxt() { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "SpinBoxT"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::SPINBOXT; }


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
			if(get_touch_state().negative_) {
				set_exec_request();
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
			@brief	タイトル更新時処理 @n
					「タイトル」は、メニューのアイテムとする。
		*/
		//-----------------------------------------------------------------//
		void update_title() noexcept override
		{
			num_ = utils::str::get_words(get_title(), sch_);
			if(select_pos_ >= num_) {
				select_pos_ = num_ - 1;
			}
			set_update();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
		*/
		//-----------------------------------------------------------------//
		void exec_select() noexcept override
		{
			if(area_ == TOUCH_AREA::LEFT) {
				if(select_pos_ > 0) {
					--select_pos_;
				}
			} else if(area_ == TOUCH_AREA::RIGHT) {
				if(num_ > 1 && select_pos_ < (num_ - 1)) {
					++select_pos_;
				}
			}
			if(select_func_) {
				select_func_(area_, select_pos_, num_);
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
			auto r = vtx::srect(get_final_position(), get_location().size);
			rdr.set_fore_color(get_base_color());
			rdr.round_box(r, DEF_SPINBOXT_ROUND_RADIUS);

			uint8_t inten = 64;
			if(get_touch_state().level_) {  // 0.75
				inten = 192;
			}

			graphics::share_color sc(0, 0, 0);
			sc.set_color(get_base_color().rgba8, inten);
			rdr.set_fore_color(sc);

			r.org  += DEF_SPINBOXT_FRAME_WIDTH;
			r.size -= DEF_SPINBOXT_FRAME_WIDTH * 2;
			rdr.round_box(r, DEF_SPINBOXT_ROUND_RADIUS - DEF_SPINBOXT_FRAME_WIDTH);

			{
				char tmp[32];
				if(utils::str::get_word(get_title(), select_pos_, tmp, sizeof(tmp), sch_)) {
					auto sz = rdr.at_font().get_text_size(tmp);
					rdr.set_fore_color(get_font_color());
					rdr.draw_text(r.org + (r.size - sz) / 2, tmp);
				}
			}

			// 左右のポイント描画
			rdr.set_fore_color(get_base_color());
			vtx::spos t[3];
			t[0].x = r.org.x + DEF_SPINBOXT_ARROW_SPACE;
			t[0].y = r.org.y + r.size.y / 2;
			t[1].x = t[2].x = r.org.x + DEF_SPINBOXT_ARROW_SPACE + DEF_SPINBOX_ARROW_W;
			t[1].y = r.org.y + r.size.y / 2 - DEF_SPINBOXT_ARROW_H / 2;
			t[2].y = r.org.y + r.size.y / 2 + DEF_SPINBOXT_ARROW_H / 2;
			if(select_pos_ > 0) {
				rdr.fill_triangle(t[0], t[1], t[2]);
			}
			if(select_pos_ < (num_ - 1)) {
				t[0].x = r.end_x() - DEF_SPINBOXT_ARROW_SPACE - 1;
				t[1].x = t[2].x = r.end_x() - DEF_SPINBOXT_ARROW_SPACE - DEF_SPINBOXT_ARROW_W - 1;
				rdr.fill_triangle(t[0], t[2], t[1]);
			}
		}
	};
}
