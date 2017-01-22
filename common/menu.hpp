#pragma once
//=====================================================================//
/*!	@file
	@brief	メニュー・クラス
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

namespace graphics {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	メニュー・クラス
		@param[in]	GR		描画クラス
		@param[in]	MAX		最大メニュー数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GR, uint16_t MAX>
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
		GR&	gr_;

		uint16_t	size_;

		struct obj_t {
			type		type_;
			const void* src_;
			uint8_t		w_;
			uint8_t		h_;

			obj_t() : type_(type::TEXT), src_(nullptr), w_(0), h_(0) { }
		};
		obj_t	obj_[MAX];

		int16_t		mx_;
		int16_t		my_;

		int16_t		spc_;

		uint16_t	pos_;

		bool		focus_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		menu(GR& gr) : gr_(gr), size_(0), mx_(0), my_(0),
					   spc_(0), pos_(0), focus_(true)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	隙間の設定
			@param[in]	spc	隙間
		*/
		//-----------------------------------------------------------------//
		void set_space(int16_t spc) { spc_ = spc; }


		//-----------------------------------------------------------------//
		/*!
			@brief	サイズを返す（登録されているメニュー数）
		*/
		//-----------------------------------------------------------------//
		uint16_t size() const { return size_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォーカスを許可
		*/
		//-----------------------------------------------------------------//
		void enable_focus(bool f = true)
		{
			focus_ = f;
		} 


		//-----------------------------------------------------------------//
		/*!
			@brief	フォーカスを戻す
		*/
		//-----------------------------------------------------------------//
		void focus_prev()
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
		void focus_next()
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
		uint16_t get_pos() const { return pos_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	クリア
		*/
		//-----------------------------------------------------------------//
		void clear()
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
		void add(type t, const void* src) {
			if(size_ >= MAX) return;

			if(t == type::TEXT) {
				obj_[size_].w_ = gr_.draw_text_length(static_cast<const char*>(src), false);
				obj_[size_].h_ = gr_.get_afont_height();
			} else if(t == type::PROP) {
				obj_[size_].w_ = gr_.draw_text_length(static_cast<const char*>(src), true);
				obj_[size_].h_ = gr_.get_afont_height();
			} else if(t == type::MOBJ) {
				uint8_t w;
				uint8_t h;
				gr_.get_mobj_size(src, w, h);
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
				y += spc_;
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
		void render(int16_t ox = 0, int16_t oy = 0) const
		{
			if(size_ == 0) return;

			int16_t x = (gr_.get_width()  - ox - mx_) / 2;
			int16_t y = (gr_.get_height() - oy - my_) / 2;
			x += ox;
			y += oy;
			for(auto i = 0; i < size_; ++i) {
				y += spc_ / 2;
				uint8_t w;
				uint8_t h;
				if(obj_[i].type_ == type::TEXT) {
					gr_.draw_text(x, y, static_cast<const char*>(obj_[i].src_), false);
				} else if(obj_[i].type_ == type::PROP) {
					gr_.draw_text(x, y, static_cast<const char*>(obj_[i].src_), true);
				} else if(obj_[i].type_ == type::MOBJ) {
					gr_.draw_mobj(x, y, obj_[i].src_);
				}
				if(focus_ && i == pos_) {
					gr_.reverse(x - 1, y, obj_[i].w_ + 2, obj_[i].h_);
				}
				y += gr_.get_afont_height();
				y += spc_ / 2;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	GR インスタンスへの参照
		*/
		//-----------------------------------------------------------------//
		GR& at() { return gr_; }
	};
}
