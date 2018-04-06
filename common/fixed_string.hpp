#pragma once
//=====================================================================//
/*!	@file
	@brief	固定サイズ文字列クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
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
	template <uint32_t SIZE>
	class fixed_string {
		uint32_t	pos_;
		char		text_[SIZE + 1];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	str	初期設定文字列
		*/
		//-----------------------------------------------------------------//
		fixed_string(const char* str = nullptr) noexcept : pos_(0) {
			if(str != nullptr) {
				std::strncpy(text_, str, SIZE);
				pos_ = std::strlen(text_);
			}
			text_[pos_] = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  格納可能な最大サイズを返す（終端の数を除外）
			@return 格納可能な最大サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t capacity() const noexcept { return SIZE; }


		//-----------------------------------------------------------------//
		/*!
			@brief  現在のサイズを返す
			@return 現在のサイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t size() const noexcept { return pos_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列をクリア（リセット）
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
		void swap(fixed_string& src) noexcept {
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
			std::strncpy(text_, src.c_str(), SIZE);
			pos_ = src.pos_;
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字を追加
			@param[in]	ch	文字
			@return 自分
		*/
		//-----------------------------------------------------------------//
		fixed_string& operator += (char ch) {
			if(pos_ < SIZE) {
				text_[pos_] = ch;
				++pos_;
				text_[pos_] = 0;
			}
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列を追加
			@param[in]	str	文字列
			@return 自分
		*/
		//-----------------------------------------------------------------//
		fixed_string& operator += (const char* str) {
			if(str == nullptr) {
				return *this;
			}

			uint32_t l = std::strlen(str);
			if((pos_ + l) < SIZE) {
				std::strcpy(&text_[pos_], str);
				pos_ += l;
			} else {  // バッファが許す範囲でコピー
				l = SIZE - pos_;
				std::strncpy(&text_[pos_], str, l);
				pos_ = SIZE;
			}
			text_[pos_] = 0; 
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字参照
			@param[in]	pos	配列位置
			@return 文字
		*/
		//-----------------------------------------------------------------//
		char& operator [] (uint32_t pos) noexcept {
			if(pos >= SIZE) {
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
		bool cmp(const char* text) const noexcept {
			if(text == nullptr) {
				return pos_ == 0;
			}
			return std::strcmp(c_str(), text) == 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  一致比較（オペレーター）
			@param[in]	text	文字列
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator == (const char* text) const { return cmp(text); }


		//-----------------------------------------------------------------//
		/*!
			@brief  不一致比較（オペレーター）
			@param[in]	text	文字列
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator != (const char* text) const { return !cmp(text); }


		//-----------------------------------------------------------------//
		/*!
			@brief  クラス、一致比較（オペレーター）
			@param[in]	th	比較対象
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator == (const fixed_string& th) const {
			return std::strcmp(c_str(), th.c_str()) == 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クラス、不一致比較（オペレーター）
			@param[in]	th	比較対象
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator != (const fixed_string& th) const {
			return std::strcmp(c_str(), th.c_str()) != 0;
		}
	};
}
