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
#include "common/vtx.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	メニュー・クラス
		@param[in]	RDR		基本描画クラス
		@param[in]	BACK	ボタン背面の描画クラス	
		@param[in]	MAX		最大メニュー数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RDR, class BACK, uint16_t MAX>
	class menu {

		RDR&		rdr_;
		BACK&		back_;

		uint16_t	size_;

		struct obj_t {
			uint8_t		w_;
			uint8_t		h_;
			const void* src_;

			obj_t() : w_(0), h_(0), src_(nullptr) { }
		};
		obj_t	obj_[MAX];

		vtx::spos	m_;
		vtx::spos	ofs_;
		vtx::spos	space_;

		uint16_t	pos_;

		int8_t		gap_;
		bool		focus_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	rdr		描画クラス
			@param[in]	back	背面描画クラス
		*/
		//-----------------------------------------------------------------//
		menu(RDR& rdr, BACK& back) noexcept : rdr_(rdr), back_(back),
			size_(0), m_(0), ofs_(0), space_(0),
			pos_(0), gap_(0),
			focus_(true)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画オフセットの設定
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		void set_offset(const vtx::spos& ofs) noexcept
		{
			ofs_ = ofs;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	描画スペースの設定
			@param[in]	spc	スペース
		*/
		//-----------------------------------------------------------------//
		void set_space(const vtx::spos& spc) noexcept
		{
			space_ = spc;
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
			m_.set(0);
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
				auto sz = rdr_.get_mobj_size(src);
				obj_[size_].w_ = sz.x;
				obj_[size_].h_ = sz.y;
			} else {
				auto sz = rdr_.at_font().get_text_size(static_cast<const char*>(src), false);
				obj_[size_].w_ = sz.x;
				obj_[size_].h_ = sz.y;
			}
			obj_[size_].src_ = src;
			++size_;

			vtx::spos tt(0);
			for(auto i = 0; i < size_; ++i) {
				auto xx = obj_[i].w_ + space_.x * 2;
				if(tt.x < xx) tt.x = xx;
				tt.y += obj_[i].h_;
				tt.y += gap_;
				tt.y += space_.y * 2;
			}
			m_ = tt;
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

			vtx::spos n((RDR::glc_type::width  - ofs_.x - m_.x) / 2,
				(RDR::glc_type::height - ofs_.y - m_.y) / 2);
			n += ofs_;
			int16_t idx = -1;
			for(auto i = 0; i < size_; ++i) {
				const auto& obj = obj_[i];
				n.y += gap_ / 2;
				auto fc = graphics::def_color::White;
				auto bc = graphics::def_color::Darkgray;
				if(n.x <= px && px < (n.x + m_.x) &&
					n.y <= py && py < (n.y + obj.h_ + space_.y * 2)) {
					idx = i;
					if(touch) {
						bc = graphics::def_color::Silver;
					}
				}
				rdr_.set_fore_color(fc);
				rdr_.set_back_color(bc);
				back_(vtx::srect(n.x, n.y, m_.x, obj.h_ + space_.y * 2));
				n.y += space_.y;
				auto t = static_cast<const char*>(obj_[i].src_);
				rdr_.set_fore_color(graphics::def_color::White);
				rdr_.draw_text(vtx::spos(n.x + space_.x, n.y), t);
				n.y += obj.h_;
				n.y += space_.y;
				n.y += gap_ - (gap_ / 2);
			}

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
			@brief	RDR クラスの参照
			@return RDR クラス
		*/
		//-----------------------------------------------------------------//
		RDR& at_render() noexcept { return rdr_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	BACK クラスの参照
			@return BACK クラス
		*/
		//-----------------------------------------------------------------//
		BACK& at_back() noexcept { return back_; }
	};
}
