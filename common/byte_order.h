#pragma once
//=====================================================================//
/*!	@file
	@brief	バイト・オーダーの検出
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#if (defined(__GNUC__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__))
#ifndef BIG_ENDIAN
#define BIG_ENDIAN
#endif
#elif (defined(__GNUC__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__))
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN
#endif
#else
#error "byte_order.h requires BIG_ENDIAN or LITTLE_ENDIAN be defined."
#endif
