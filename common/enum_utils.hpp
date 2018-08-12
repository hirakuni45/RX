#pragma once
//=====================================================================//
/*!	@file
	@brief	enum class utils
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

struct enum_utils {

	//-----------------------------------------------------------------//
	/*!
		@brief	進める
		@param[in]	val		値
		@param[in]	min		最小
		@param[in]	max		最大
		@return +1 した値
	*/
	//-----------------------------------------------------------------//
	template<typename T>
	static T inc(T val, T min, T max, bool cyc = true) noexcept
	{
		int32_t v  = static_cast<int32_t>(val);
		int32_t mi = static_cast<int32_t>(min);
		int32_t mx = static_cast<int32_t>(max);
		++v;
		if(v > mx) {
			if(cyc) v = mi;
			else v = mx;
		}
		return static_cast<T>(v);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	戻る
		@param[in]	val		値
		@param[in]	min		最小
		@param[in]	max		最大
		@return -1 した値
	*/
	//-----------------------------------------------------------------//
	template<typename T>
	static T dec(T val, T min, T max, bool cyc = true) noexcept
	{
		int32_t v  = static_cast<int32_t>(val);
		int32_t mi = static_cast<int32_t>(min);
		int32_t mx = static_cast<int32_t>(max);
		--v;
		if(v < mi) {
			if(cyc) v = mx;
			else v = mi;
		}
		return static_cast<T>(v);
	}
};
