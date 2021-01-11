#pragma once
//=====================================================================//
/*!	@file
	@brief	ボックス表示と制御 @n
			シンプルな描画を行う
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	フレーム・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct box : public widget {

		typedef box value_type;

		typedef std::function<void(const vtx::srect& r)> DRAW_FUNC_TYPE;

	private:

		DRAW_FUNC_TYPE	draw_func_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		フレーム・タイトル
		*/
		//-----------------------------------------------------------------//
		box(const vtx::srect& loc = vtx::srect(0), const char* str = "") noexcept :
			widget(loc, str), draw_func_()
		{
			insert_widget(this);
		}


		box(const box& th) = delete;
		box& operator = (const box& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~box() noexcept { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "Box"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::BOX; }


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
			@param[in]	slt		スライド・タイプの場合「true」
		*/
		//-----------------------------------------------------------------//
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override { }


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
			@param[in]	inva	無効状態にする場合「true」
		*/
		//-----------------------------------------------------------------//
		void exec_select(bool inva) noexcept override { }


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
			@brief	描画関数への参照
			@return	描画関数
		*/
		//-----------------------------------------------------------------//
		DRAW_FUNC_TYPE& at_draw_func() noexcept { return draw_func_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = get_location();
			if(draw_func_) {
				draw_func_(r);
			} else {
				rdr.set_fore_color(get_base_color());
				rdr.fill_box(r);
			}
		}
	};
}
