#pragma once
//=====================================================================//
/*!	@file
	@brief	固定サイズ文字列クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <algorithm>
#include <cstring>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  固定サイズ文字列クラス
		@param[in]	SIZE	文字列サイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint16_t SIZE>
	class fixed_string {
		char		text_[SIZE];
		uint16_t	pos_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		fixed_string() : pos_(0) { text_[0] = 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief  最大サイズを返す
			@return 最大サイズ
		*/
		//-----------------------------------------------------------------//
		uint16_t max_size() const { return SIZE; }


		//-----------------------------------------------------------------//
		/*!
			@brief  現在のサイズを返す
			@return 現在のサイズ
		*/
		//-----------------------------------------------------------------//
		uint16_t size() const { return pos_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列をクリア
		*/
		//-----------------------------------------------------------------//
		void clear() noexcept {
			pos_ = 0;
			text_[pos_] = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列を返す
			@return 文字列
		*/
		//-----------------------------------------------------------------//
		const char* c_str() const noexcept { return text_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  交換
			@param[in]	src	ソース
			@return 自分
		*/
		//-----------------------------------------------------------------//
		void swap(fixed_string& src) {
			std::swap(src.text_, text_);
			std::swap(src.pos_, pos_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  代入
			@param[in]	src	ソース
			@return 自分
		*/
		//-----------------------------------------------------------------//
		fixed_string& operator = (const fixed_string& src) {
			std::strcpy(text_, src.text_);
			pos_ = src.pos_;
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字を加える
			@param[in]	ch	文字
			@return 自分
		*/
		//-----------------------------------------------------------------//
		fixed_string& operator += (char ch) {
			if(pos_ < (SIZE - 1)) {
				text_[pos_] = ch;
				++pos_;
				text_[pos_] = 0;
			}
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字参照
			@param[in]	pos	配列位置
			@return 文字
		*/
		//-----------------------------------------------------------------//
		char& operator [] (uint32_t pos) {
			if(pos >= pos_) {
				static char tmp = 0;
				return tmp;
			}
			return text_[pos];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  一致比較
			@param[in]	text	文字列
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator == (const char* text) const {
			if(text == nullptr) {
				return pos_ == 0;
			}
			return std::strcmp(text_, text) == 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  一致比較
			@param[in]	th	比較対象
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator == (const fixed_string& th) const {
			return std::strcmp(c_str(), th.c_str()) == 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  不一致比較
			@param[in]	th	比較対象
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator != (const fixed_string& th) const {
			return std::strcmp(c_str(), th.c_str()) != 0;
		}
	};
}
