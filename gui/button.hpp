#pragma once
//=====================================================================//
/*!	@file
	@brief	ボタン表示と制御 @n
			・領域内で、「押した」、「離した」がある場合に「押された」と認識する。 @n
			・選択時関数を使わない場合、select_id を監視する事で、状態の変化を認識できる。 @n
			・select_id は、ボタンが押される度にインクリメントされる。 @n
			・角がラウンドした四角、又は、円が選択可能。（円の場合、幅と高さを同じにする）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "gui/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ボタン・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct button : public widget {

		typedef button value_type;

		/// 選択される度に count が＋１する。（select_id_）
		typedef std::function<void(uint32_t count)> SELECT_FUNC_TYPE;

		enum class STYLE : uint8_t {
			ROUND_WITH_FRAME,	///< 角がラウンド、フレーム付き
			CIRCLE_WITH_FRAME,	///< 円、フレーム付き
		};

	private:

		SELECT_FUNC_TYPE	select_func_;
		uint32_t			select_id_;
		STYLE				style_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		ボタン文字列
			@param[in]	style	描画スタイル
		*/
		//-----------------------------------------------------------------//
		button(const vtx::srect& loc = vtx::srect(0), const char* str = "", STYLE style = STYLE::ROUND_WITH_FRAME) noexcept :
			widget(loc, str), select_func_(), select_id_(0), style_(style)
		{
			if(get_location().size.x <= 0) {  // 自動で幅を推定する場合
				auto tlen = 0;
				if(str != nullptr) {
					tlen = strlen(str) * 8;  // font::get_text_size(str); を使うべきだが、インスタンスが・・
				}
				at_location().size.x = (DEF_BUTTON_FRAME_WIDTH + DEF_BUTTON_TO_STR) * 2 + tlen;
			}
			if(get_location().size.y <= 0) {
				at_location().size.y = DEF_BUTTON_HEIGHT;
			}
			insert_widget(this);
		}


		button(const button& th) = delete;
		button& operator = (const button& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~button() { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "Button"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::BUTTON; }


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
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
		*/
		//-----------------------------------------------------------------//
		void exec_select() noexcept override
		{
			++select_id_;
			if(select_func_) {
				select_func_(select_id_);
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
			@brief	描画テンプレート
			@param[in] rdr	描画インスタンス
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = vtx::srect(get_final_position(), get_location().size);
			rdr.set_fore_color(get_base_color());

			uint8_t inten = 64;
			if(get_touch_state().level_) {  // 0.75
				inten = 192;
			}

			switch(style_) {
			case STYLE::CIRCLE_WITH_FRAME:
				if(r.size.x == r.size.y) {
					auto rad = r.size.x / 2;
					vtx::spos cen(r.center_x(), r.center_y());
					rdr.fill_circle(cen, rad);

					graphics::share_color sc(0, 0, 0);
					sc.set_color(get_base_color().rgba8, inten);
					rdr.set_fore_color(sc);

					rad -= DEF_BUTTON_FRAME_WIDTH;
					rdr.fill_circle(cen, rad);
				}
				break;
			case STYLE::ROUND_WITH_FRAME:
				{
					rdr.round_box(r, DEF_BUTTON_ROUND_RADIUS);

					graphics::share_color sc(0, 0, 0);
					sc.set_color(get_base_color().rgba8, inten);
					rdr.set_fore_color(sc);

					r.org  += DEF_BUTTON_FRAME_WIDTH;
					r.size -= DEF_BUTTON_FRAME_WIDTH * 2;
					rdr.round_box(r, DEF_BUTTON_ROUND_RADIUS - DEF_BUTTON_FRAME_WIDTH);
				}
				break;
			default:
				break;
			}

			rdr.set_fore_color(get_font_color());
			auto mobj = get_mobj();
			if(mobj != nullptr) {  // mobj があれば、テキストより優先される。
				auto sz = rdr.get_mobj_size(mobj);
				rdr.draw_mobj(r.org + (r.size - sz) / 2, mobj, false);
			} else {
				auto sz = rdr.at_font().get_text_size(get_title());
				rdr.draw_text(r.org + (r.size - sz) / 2, get_title());
			}
		}
	};
}
