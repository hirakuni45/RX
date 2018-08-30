#pragma once
//=====================================================================//
/*!	@file
	@brief	メニュー・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	メニュー・クラス
		@param[in]	REND	描画クラス
		@param[in]	MAX		最大メニュー数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class REND, uint16_t MAX>
	class menu {

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	オブジェクト・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class type : uint8_t {
			TEXT,	///< 等幅フォント
			PROP,	///< プロポーショナル・フォント
			MOBJ,	///< モーション・オブジェクト
		};

	private:
		REND&		rend_;

		uint16_t	size_;

		struct obj_t {
			type		type_;
			uint8_t		w_;
			uint8_t		h_;
			const void* src_;

			obj_t() : type_(type::TEXT), w_(0), h_(0), src_(nullptr) { }
		};
		obj_t	obj_[MAX];

		int16_t		mx_;
		int16_t		my_;

		int8_t		gap_;
		int8_t		space_w_;
		int8_t		space_h_;

		uint16_t	pos_;

		typename REND::value_type	fc_;
		typename REND::value_type	bc_;

		bool		frame_;
		bool		focus_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	rend	描画クラス
		*/
		//-----------------------------------------------------------------//
		menu(REND& rend) noexcept : rend_(rend), size_(0), mx_(0), my_(0),
			gap_(0), space_w_(0), space_h_(0), pos_(0),
			fc_(REND::COLOR::Black), bc_(REND::COLOR::White),
			frame_(true), focus_(true)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	スペースの設定
			@param[in]	w	横幅
			@param[in]	h	高さ
		*/
		//-----------------------------------------------------------------//
		void set_space(int16_t w, int16_t h) noexcept
		{
			space_w_ = w;
			space_h_ = h;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ギャップの設定
			@param[in]	gap	ギャップ
		*/
		//-----------------------------------------------------------------//
		void set_gap(int16_t gap) noexcept { gap_ = gap; }


		//-----------------------------------------------------------------//
		/*!
			@brief	サイズを返す（登録されているメニュー数）
		*/
		//-----------------------------------------------------------------//
		uint16_t size() const noexcept { return size_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォーカスを許可
			@param[in]	f	不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable_focus(bool f = true) noexcept
		{
			focus_ = f;
		} 


		//-----------------------------------------------------------------//
		/*!
			@brief	フレームの描画
			@param[in]	f	不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void draw_frame(bool f = true) noexcept
		{
			frame_ = f;
		} 


		//-----------------------------------------------------------------//
		/*!
			@brief	フォーカスを戻す
		*/
		//-----------------------------------------------------------------//
		void focus_prev() noexcept
		{
			if(!focus_) return;

			if(pos_ > 0) {
				pos_--;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フォーカスを進める
		*/
		//-----------------------------------------------------------------//
		void focus_next() noexcept
		{
			if(!focus_) return;

			++pos_;
			if(pos_ >= size_) {
				pos_ = size_ - 1;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	メニュー位置を取得
			@return メニュー位置
		*/
		//-----------------------------------------------------------------//
		uint16_t get_pos() const noexcept { return pos_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	クリア
		*/
		//-----------------------------------------------------------------//
		void clear() noexcept
		{
			size_ = 0;
			mx_ = 0;
			my_ = 0;
			pos_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	オブジェクトを追加
			@param[in]	t	オブジェクト・タイプ
			@param[in]	src	オブジェクト・ソース
		*/
		//-----------------------------------------------------------------//
		void add(type t, const void* src) noexcept {
			if(size_ >= MAX) return;

			if(t == type::TEXT) {
				obj_[size_].w_ = rend_.get_text_length(static_cast<const char*>(src), false);
				obj_[size_].h_ = REND::font_height;
			} else if(t == type::PROP) {
				obj_[size_].w_ = rend_.get_text_length(static_cast<const char*>(src), true);
				obj_[size_].h_ = REND::font_height;
			} else if(t == type::MOBJ) {
				uint8_t w;
				uint8_t h;
				rend_.get_mobj_size(src, w, h);
				obj_[size_].w_ = w;
				obj_[size_].h_ = h;
			} else {
				return;
			}
			obj_[size_].type_ = t;
			obj_[size_].src_  = src;
			++size_;

			int16_t x = 0;
			int16_t y = 0;
			for(auto i = 0; i < size_; ++i) {
				if(x < obj_[i].w_) x = obj_[i].w_;
				y += obj_[i].h_;
				y += gap_;
				y += space_h_ * 2;
			}
			mx_ = x;
			my_ = y;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	レンダリング
			@param[in]	ox	描画オフセットＸ
			@param[in]	oy	描画オフセットＹ
		*/
		//-----------------------------------------------------------------//
		void render(int16_t ox = 0, int16_t oy = 0) const noexcept
		{
			if(size_ == 0) return;

			int16_t x = (REND::width  - ox - mx_) / 2;
			int16_t y = (REND::height - oy - my_) / 2;
			x += ox;
			y += oy;
			auto tmp_fc = rend_.get_fore_color();
			rend_.set_fore_color(fc_);
			for(auto i = 0; i < size_; ++i) {
				y += gap_ / 2;
				uint8_t w;
				uint8_t h;
				if(obj_[i].type_ == type::TEXT) {
					rend_.fill_r(x, y, mx_ + space_w_ * 2, obj_[i].h_ + space_h_ * 2, bc_);
					y += space_h_;
					auto t = static_cast<const char*>(obj_[i].src_);
					rend_.draw_text(x + space_w_, y, t);
						
				} else if(obj_[i].type_ == type::PROP) {
					rend_.fill_r(x, y, mx_ + space_w_ * 2, obj_[i].h_ + space_h_ * 2, bc_);
					y += space_h_;
					auto t = static_cast<const char*>(obj_[i].src_);
					rend_.draw_text(x + space_w_, y, t, true);
				} else if(obj_[i].type_ == type::MOBJ) {
					y += space_h_;
					rend_.draw_mobj(x, y, obj_[i].src_);
				}
//				if(focus_ && i == pos_) {
//					rend_.reverse(x - 1, y, obj_[i].w_ + 2, obj_[i].h_);
//				}
				y += REND::font_height;
				y += space_h_;
				y += gap_ - (gap_ / 2);
			}
			rend_.set_fore_color(tmp_fc);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	REND クラスの参照
			@return REND クラス
		*/
		//-----------------------------------------------------------------//
		REND& at() noexcept { return rend_; }
	};
}
