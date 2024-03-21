#pragma once
//=====================================================================//
/*! @file
    @brief  シンプル、固定長、文字 map
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <stdint.h>
#include <cstring>
#include <utility>
#include <iterator>

namespace utils {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  固定マップ・クラス
		@param[in]	KEY		キー
		@param[in]	T		値
		@param[in]	N		配列数
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class KEY, class T, uint32_t N>
    struct fixed_map {

		typedef KEY key_type;
		typedef std::pair<KEY, T> value_type;
		typedef T mapped_type;
		using iterator = value_type *;
		using const_iterator = const value_type *;

	private:
		uint32_t	last_;
		value_type	buff_[N];

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-------------------------------------------------------------//
		fixed_map() noexcept : last_(0), buff_()
		{ }

		iterator begin() noexcept { return &buff_[0]; }
		const_iterator begin() const noexcept { return &buff_[0]; }
		iterator end() noexcept { return &buff_[last_]; }
		const_iterator end() const noexcept { return &buff_[last_]; }

		//-------------------------------------------------------------//
		/*!
			@brief  全消去
		*/
		//-------------------------------------------------------------//
		void clear() noexcept
		{
			last_ = 0;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  照会
			@param[in]	key		キー
			@return イテレータを返す
		*/
		//-------------------------------------------------------------//
		iterator find(const KEY& key) noexcept
		{
			for(uint32_t i = 0; i < last_; ++i) {
				if(buff_[i].first == key) {
					return &buff_[i];
				}
			}
			return end();
		}


		//-------------------------------------------------------------//
		/*!
			@brief  挿入
			@param[in]	v	挿入値
			@return イテレータを返す
		*/
		//-------------------------------------------------------------//
		iterator insert(const value_type& v) noexcept
		{
			if(last_ >= N) return end();

			if(find(v.first) != end()) {
				return end();
			}

			auto it = &buff_[last_];
			*it = v;
			last_++;
			return it;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  削除
		*/
		//-------------------------------------------------------------//
		uint32_t erase(const key_type& key) noexcept
		{
			auto it = find(key);
			if(it == end()) {
				return 0;
			}
			if(last_ > 0) {
				--last_;
				*it = buff_[last_];
			}
			return 1;
		}
	};
}
