#pragma once
//=========================================================================//
/*!	@file
	@brief	固定サイズ文字列クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <algorithm>
#include <cstring>
#include <iterator>
#include <boost/functional/hash.hpp>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  固定サイズ文字列クラス
		@param[in]	SIZE	文字列サイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t SIZE>
	class fixed_string {

		char		str_[SIZE + 1];
		uint32_t	pos_;

		static char* strncpy_(char* dst, const char* src, uint32_t n) noexcept
		{
			if(n == 0) return dst;

			auto tmp = dst;
			do {
				auto ch = *src++;
				*tmp++ = ch;
				if(ch == 0) {
					return dst;
				}
			} while(tmp < (dst + n)) ;
			*tmp = 0;
			return dst;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	s	文字列
			@param[in]	n	コピー最大数
		*/
		//-----------------------------------------------------------------//
		constexpr fixed_string(const char* s = nullptr, uint32_t n = SIZE) noexcept : str_{ 0, }, pos_(0)
		{
			if(s != nullptr) {
				strncpy_(str_, s, n);
				str_[n] = 0;
				pos_ = std::strlen(str_);
			} else {
				str_[0] = 0;
				pos_ = 0;
			}
			str_[SIZE] = 0;
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
			@brief  空か調べる
			@return 空の場合「true」
		*/
		//-----------------------------------------------------------------//
		bool empty() const noexcept { return pos_ == 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列をクリア（リセット）
		*/
		//-----------------------------------------------------------------//
		void clear() noexcept {
			pos_ = 0;
			str_[pos_] = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	末尾の1要素を削除する。
		*/
		//-----------------------------------------------------------------//
		void pop_back() noexcept {
			if(pos_ > 0) {
				--pos_;
				str_[pos_] = 0;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	要素を削除する。
			@param[in] org	先頭位置
			@param[in] num	個数
			@return 自分
		*/
		//-----------------------------------------------------------------//
		fixed_string& erase(uint32_t org, uint32_t num) noexcept {
			if(org < pos_ && (org + num) <= pos_) {
				for(uint32_t i = 0; i < (pos_ - num); ++i) {
					str_[org + i] = str_[org + i + num];
				}
				pos_ -= num;
				str_[pos_] = 0;
			}
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  配列の先頭
			@return 配列の先頭
		*/
		//-----------------------------------------------------------------//
		const char* begin() const noexcept { return &str_[0]; }


		//-----------------------------------------------------------------//
		/*!
			@brief  配列の先頭
			@return 配列の先頭
		*/
		//-----------------------------------------------------------------//
		char* begin() noexcept { return &str_[0]; }


		//-----------------------------------------------------------------//
		/*!
			@brief  配列の終端
			@return 配列の終端
		*/
		//-----------------------------------------------------------------//
		const char* end() const noexcept { return &str_[pos_]; }


		//-----------------------------------------------------------------//
		/*!
			@brief  配列の終端
			@return 配列の終端
		*/
		//-----------------------------------------------------------------//
		char* end() noexcept { return &str_[pos_]; }


  		//-----------------------------------------------------------------//
		/*!
			@brief  末尾要素への参照を取得する。
			@return 末尾要素への参照
		*/
		//-----------------------------------------------------------------//
		char& back() noexcept {
			auto pos = pos_;
			if(pos > 0) --pos;
			return str_[pos];
		}


  		//-----------------------------------------------------------------//
		/*!
			@brief  末尾要素への参照を取得する。
			@return 末尾要素への参照
		*/
		//-----------------------------------------------------------------//
		const char& back() const noexcept {
			auto pos = pos_;
			if(pos > 0) --pos;
			return str_[pos];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列を返す
			@return 文字列
		*/
		//-----------------------------------------------------------------//
		const char* c_str() const noexcept { return str_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  交換
			@param[in]	src	ソース
		*/
		//-----------------------------------------------------------------//
		void swap(fixed_string& src) noexcept {
			std::swap(src.str_, str_);
			std::swap(src.pos_, pos_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  代入
			@param[in]	src	ソース
			@return 自分
		*/
		//-----------------------------------------------------------------//
		fixed_string& operator = (const char* src) noexcept {
			strncpy_(str_, src, SIZE);
			pos_ = std::strlen(str_);
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  代入
			@param[in]	src	ソース
			@return 自分
		*/
		//-----------------------------------------------------------------//
		fixed_string& operator = (const fixed_string& src) noexcept {
			strncpy_(str_, src.c_str(), SIZE);
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
		fixed_string& operator += (char ch) noexcept {
			if(pos_ < SIZE) {
				str_[pos_] = ch;
				++pos_;
				str_[pos_] = 0;
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
		fixed_string& operator += (const char* str) noexcept {
			if(str == nullptr) {
				return *this;
			}

			uint32_t l = std::strlen(str);
			if((pos_ + l) < SIZE) {
				std::strcpy(&str_[pos_], str);
				pos_ += l;
			} else {  // バッファが許す範囲でコピー
				l = SIZE - pos_;
				strncpy_(&str_[pos_], str, l);
				pos_ = SIZE;
			}
			str_[pos_] = 0; 
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字参照 @n
					※範囲外ではテンポラリを返す（例外を投げない）
			@param[in]	pos	配列位置
			@return 文字
		*/
		//-----------------------------------------------------------------//
		char& operator [] (uint32_t pos) noexcept {
			if(pos >= SIZE) {
				static char tmp = 0;
				return tmp;
			}
			return str_[pos];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字参照 const @n
					※範囲外ではテンポラリを返す（例外を投げない）
			@param[in]	pos	配列位置
			@return 文字
		*/
		//-----------------------------------------------------------------//
		const char& operator [] (uint32_t pos) const noexcept {
			if(pos >= SIZE) {
				static char tmp = 0;
				return tmp;
			}
			return str_[pos];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クラス一致比較
			@param[in]	th		文字列クラス
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		int cmp(const fixed_string& th) const noexcept {
			return std::strcmp(c_str(), th.c_str());
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クラス一致比較（オペレーター）
			@param[in]	th	文字列クラス
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator == (const fixed_string& th) const noexcept {
			return std::strcmp(c_str(), th.c_str()) == 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クラス、不一致比較（オペレーター）
			@param[in]	th	文字列クラス
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator != (const fixed_string& th) const noexcept {
			return std::strcmp(c_str(), th.c_str()) != 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クラス大小比較（オペレーター）
			@param[in]	th		文字列クラス
			@return 大小なら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator > (const fixed_string& th) const noexcept {
			return std::strcmp(c_str(), th.c_str()) > 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クラス小大比較（オペレーター）
			@param[in]	th		文字列クラス
			@return 小大なら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator < (const fixed_string& th) const noexcept {
			return std::strcmp(c_str(), th.c_str()) < 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クラス大小一致比較（オペレーター）
			@param[in]	th		文字列
			@return 大小一致なら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator >= (const fixed_string& th) const noexcept {
			return std::strcmp(c_str(), th.c_str()) >= 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クラス小大一致比較（オペレーター）
			@param[in]	th		文字列クラス
			@return 小大一致なら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator <= (const fixed_string& th) const noexcept {
			return std::strcmp(c_str(), th.c_str()) <= 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ハッシュ値の計算
			@return ハッシュ値
		*/
		//-----------------------------------------------------------------//
		size_t hash() const noexcept
		{
			size_t h = 0;
			for(uint32_t i = 0; i < pos_; ++i) {
 				boost::hash_combine(h, str_[i]);
			}
			return h;
		}
	};

	typedef fixed_string<8> STR8;
	typedef fixed_string<16> STR16;
	typedef fixed_string<32> STR32;
	typedef fixed_string<64> STR64;
	typedef fixed_string<128> STR128;
	typedef fixed_string<256> STR256;

	template <class T>
	inline size_t hash_value(const T& t) { return t.hash(); }
}
