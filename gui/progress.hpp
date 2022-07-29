#pragma once
//=====================================================================//
/*!	@file
	@brief	プログレスバー表示と制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <functional>
#include "gui/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	プログレス・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct progress : public widget {

		typedef progress value_type;

		typedef std::function<float(float ratio)> UPDATE_FUNC_TYPE;
	
	private:

		UPDATE_FUNC_TYPE	update_func_;
		float				ratio_;
		bool				nmbe_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	nmbe	百分率の表示（行わない場合「false」）
		*/
		//-----------------------------------------------------------------//
		progress(const vtx::srect& loc = vtx::srect(0), bool nmbe = true ) noexcept :
			widget(loc, nullptr), update_func_(), ratio_(0.0f), nmbe_(nmbe)
		{
			if(loc.size.y <= 0) {
				at_location().size.y = DEF_PROGRESS_HEIGHT;
			}
			insert_widget(this);
		}


		progress(const progress& th) = delete;
		progress& operator = (const progress& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~progress() { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const override { return "Progress"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const override { return ID::PROGRESS; }


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-----------------------------------------------------------------//
		void init() override { }


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override
		{
			if(update_func_) {
				auto ratio = update_func_(ratio_);
				set_ratio(ratio);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
		*/
		//-----------------------------------------------------------------//
		void exec_select() noexcept override { }


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
			@brief	レシオの取得（移動量を正規化した値 0.0 to 1.0）
			@return	レシオ
		*/
		//-----------------------------------------------------------------//
		float get_ratio() const noexcept { return ratio_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	レシオを設定（正規化した値 0.0 to 1.0）
			@param	ratio	レシオ
		*/
		//-----------------------------------------------------------------//
		void set_ratio(float ratio) noexcept {
			auto tmp = ratio_;
			if(ratio >= 0.0f && ratio <= 1.0f) {
				ratio_ = ratio;
			}
			if(tmp != ratio_) {
				set_update();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アップデート関数への参照
			@return	アップデート関数
		*/
		//-----------------------------------------------------------------//
		UPDATE_FUNC_TYPE& at_update_func() noexcept { return update_func_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画
			@param[in] rdr	描画インスタンス
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto org = get_final_position();
			auto r = vtx::srect(org, get_location().size);
			rdr.set_fore_color(get_base_color());
			rdr.fill_box(r);

			graphics::share_color sc(0, 0, 0);
			sc.set_color(get_base_color().rgba8, 170);
			rdr.set_fore_color(sc);

			r.org  += DEF_PROGRESS_FRAME_WIDTH;
			r.size -= DEF_PROGRESS_FRAME_WIDTH * 2;
			auto rr = r;

			auto size = r.size.x; 
			r.size.x = static_cast<int16_t>(ratio_ * size);
			rdr.fill_box(r);

			sc.set_color(get_base_color().rgba8, 64);
			rdr.set_fore_color(sc);
			r.org.x += r.size.x;
			r.size.x = size - r.size.x;
			rdr.fill_box(r);

			if(nmbe_) {
				rdr.set_fore_color(get_font_color());
				char tmp[8];
				utils::sformat("%d%%", tmp, sizeof(tmp)) % static_cast<int>(ratio_ * 100.0f);
				auto sz = rdr.at_font().get_text_size(tmp);
				rdr.draw_text(rr.org + (rr.size - sz) / 2, tmp);
			}
		}
	};
}
