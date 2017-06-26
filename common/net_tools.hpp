#pragma once
//=====================================================================//
/*!	@file
	@brief	ネットワーク・ツール @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include <cstring>
#include "common/byte_order.h"

#if defined(BIG_ENDIAN)
#elif defined(LITTLE_ENDIAN)
#else
#error "net_tools.hpp requires BIG_ENDIAN or LITTLE_ENDIAN be defined."
#endif

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ネット・ツール
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct tools {

		//-----------------------------------------------------------------//
		/*!
			@brief  16 ビット列変換
			@param[in]	data	変換元
			@return 変換後
		*/
		//-----------------------------------------------------------------//
		static inline uint16_t htons(uint16_t data)
		{
#ifdef LITTLE_ENDIAN
			uint16_t tmp = 0;
			tmp  = (data & 0x00ff) << 8;
			tmp |= (data & 0xff00) >> 8;
			return tmp;
#else
			return data;
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  32 ビット列変換
			@param[in]	data	変換元
			@return 変換後
		*/
		//-----------------------------------------------------------------//
		static inline uint32_t htonl(uint32_t data)
		{
#ifdef LITTLE_ENDIAN
			uint32_t tmp = 0;
			tmp  = (data & 0x000000ff) << 24;
			tmp |= (data & 0x0000ff00) << 8;
			tmp |= (data & 0x00ff0000) >> 8;
			tmp |= (data & 0xff000000) >> 24;
			return tmp;
#else
   			return data;
#endif
		}
	};
}
