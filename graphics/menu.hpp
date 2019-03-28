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
		@param[in]	BACK	背面の描画クラス	
		@param[in]	MAX		最大メニュー数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class REND, class BACK, uint16_t MAX>
	class menu {

		REND&		rend_;
		BACK&		back_;

		uint16_t	size_;

		struct obj_t {
			uint8_t		w_;
			uint8_t		h_;
			const void* src_;

			obj_t() : w_(0), h_(0), src_(nullptr) { }
		};
		obj_t	obj_[MAX];

		int16_t		mx_;
		int16_t		my_;
		int16_t		ox_;
		int16_t		oy_;

		int8_t		gap_;
		int8_t		space_w_;
		int8_t		space_h_;

		uint16_t	pos_;

		share_color	fc_;
		share_color	hc_;
		share_color	bc_;

		bool		focus_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	rend	描画クラス
		*/
		//-----------------------------------------------------------------//
		menu(REND& rend, BACK& back) noexcept : rend_(rend), back_(back),
			size_(0), mx_(0), my_(0), ox_(0), oy_(0),
			gap_(0), space_w_(0), space_h_(0), pos_(0),
			fc_(def_color::Black), hc_(def_color::White), bc_(def_color::Gray),
			focus_(true)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画オフセットの設定
			@param[in]	ox	X オフセット
			@param[in]	oy	Y オフセット
		*/
		//-----------------------------------------------------------------//
		void set_offset(int16_t ox, int16_t oy) noexcept
		{
			ox_ = ox;
			oy_ = oy;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	描画スペースの設定
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
			@brief	ギャップの設定（縦）
			@param[in]	gap	ギャップ
		*/
		//-----------------------------------------------------------------//
		void set_gap(int16_t gap) noexcept { gap_ = gap; }


		//-----------------------------------------------------------------//
		/*!
			@brief	メニュー・サイズを返す（登録されているメニュー数）
			@return メニュー・サイズ
		*/
		//-----------------------------------------------------------------//
		uint16_t size() const noexcept { return size_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォーカスを戻す
		*/
		//-----------------------------------------------------------------//
		void prev_focus() noexcept
		{
			if(size_ == 0) return;

			if(pos_ > 0) {
				pos_--;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フォーカスを進める
		*/
		//-----------------------------------------------------------------//
		void next_focus() noexcept
		{
			if(size_ == 0) return;

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
			@brief	登録メニューを全てクリア
		*/
		//-----------------------------------------------------------------//
		void clear() noexcept
		{
			size_ = 0;
			mx_ = 0;
			my_ = 0;
			pos_ = 0;
			focus_ = false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	オブジェクトを追加
			@param[in]	src		オブジェクト・ソース
			@param[in]	bitmap	ビットマップの場合「true」
		*/
		//-----------------------------------------------------------------//
		void add(const void* src, bool bitmap = false) noexcept
		{
			if(size_ >= MAX) return;

			if(bitmap) {
				uint8_t w;
				uint8_t h;
				rend_.get_mobj_size(src, w, h);
				obj_[size_].w_ = w;
				obj_[size_].h_ = h;
			} else {
				obj_[size_].w_ = rend_.get_text_length(static_cast<const char*>(src), false);
				obj_[size_].h_ = REND::font_height;
			}
			obj_[size_].src_ = src;
			++size_;

			int16_t x = 0;
			int16_t y = 0;
			for(auto i = 0; i < size_; ++i) {
				auto xx = obj_[i].w_ + space_w_ * 2;
				if(x < xx) x = xx;
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
			@param[in]	px	X 位置
			@param[in]	py	Y 位置
			@param[in]	touch	タッチ状態
			@return メニューが選択された場合「true」
		*/
		//-----------------------------------------------------------------//
		bool render(int16_t px = -1, int16_t py = -1, bool touch = false) noexcept
		{
			if(size_ == 0) return false;

			int16_t x = (REND::glc_type::width  - ox_ - mx_) / 2;
			int16_t y = (REND::glc_type::height - oy_ - my_) / 2;
			x += ox_;
			y += oy_;
			auto tmp_fc = rend_.get_fore_color();
			rend_.set_fore_color(fc_);
			int16_t idx = -1;
			for(auto i = 0; i < size_; ++i) {
				const auto& obj = obj_[i];
				y += gap_ / 2;
				auto c = bc_;
				if(x <= px && px < (x + mx_) && y <= py && py < (y + obj.h_ + space_h_ * 2)) {
					idx = i;
					if(touch) {
						c = hc_;
					}
				}
				back_(x, y, mx_, obj.h_ + space_h_ * 2, c.rgb565);
				y += space_h_;
				auto t = static_cast<const char*>(obj_[i].src_);
				rend_.draw_text(vtx::spos(x + space_w_, y), t);
				y += obj.h_;
				y += space_h_;
				y += gap_ - (gap_ / 2);
			}
			rend_.set_fore_color(tmp_fc);

			bool focus = focus_;
			focus_ = touch;
			if(idx >= 0) {
				pos_ = idx;
				if(focus && !focus_) {
					return true;
				}
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	REND クラスの参照
			@return REND クラス
		*/
		//-----------------------------------------------------------------//
		REND& at_render() noexcept { return rend_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	BACK クラスの参照
			@return BACK クラス
		*/
		//-----------------------------------------------------------------//
		BACK& at_back() noexcept { return back_; }
	};
}
