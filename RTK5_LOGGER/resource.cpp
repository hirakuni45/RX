//=====================================================================//
/*!	@file
    @brief  LOGGER リソース
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "resource.hpp"

namespace app {

	// 16x24 ピクセル数字フォント
	#include "resource/nmb24_0.h"
	#include "resource/nmb24_1.h"
	#include "resource/nmb24_2.h"
	#include "resource/nmb24_3.h"
	#include "resource/nmb24_4.h"
	#include "resource/nmb24_5.h"
	#include "resource/nmb24_6.h"
	#include "resource/nmb24_7.h"
	#include "resource/nmb24_8.h"
	#include "resource/nmb24_9.h"
	#include "resource/nmb24_co.h"
	#include "resource/nmb24_do.h"
	#include "resource/nmb24_x.h"

	const uint8_t* nmb24[] = {
		nmb24_0,
		nmb24_1,
		nmb24_2,
		nmb24_3,
		nmb24_4,
		nmb24_5,
		nmb24_6,
		nmb24_7,
		nmb24_8,
		nmb24_9,
		nmb24_co,  // idx: 10
		nmb24_do,  // idx: 11
		nmb24_x,   // idx: 12
	};
}
