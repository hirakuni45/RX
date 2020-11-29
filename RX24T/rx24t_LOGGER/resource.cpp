//=====================================================================//
/*!	@file
	@breif	リソース・データ @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "resource.hpp"

namespace app {

	// 8x12 ピクセルフォント
	const uint8_t nmb12_0[] = {
		#include "resource/nmb12_0.h"
	};
	const uint8_t nmb12_1[] = {
		#include "resource/nmb12_1.h"
	};
	const uint8_t nmb12_2[] = {
		#include "resource/nmb12_2.h"
	};
	const uint8_t nmb12_3[] = {
		#include "resource/nmb12_3.h"
	};
	const uint8_t nmb12_4[] = {
		#include "resource/nmb12_4.h"
	};
	const uint8_t nmb12_5[] = {
		#include "resource/nmb12_5.h"
	};
	const uint8_t nmb12_6[] = {
		#include "resource/nmb12_6.h"
	};
	const uint8_t nmb12_7[] = {
		#include "resource/nmb12_7.h"
	};
	const uint8_t nmb12_8[] = {
		#include "resource/nmb12_8.h"
	};
	const uint8_t nmb12_9[] = {
		#include "resource/nmb12_9.h"
	};

	const uint8_t nmb12_co[] = {
		#include "resource/nmb12_co.h"
	};
	const uint8_t nmb12_po[] = {
		#include "resource/nmb12_po.h"
	};
	const uint8_t nmb12_sl[] = {
		#include "resource/nmb12_sl.h"
	};
	const uint8_t nmb12_x[] = {
		#include "resource/nmb12_x.h"
	};
	const uint8_t nmb12_a[] = {
		#include "resource/nmb12_a.h"
	};
	const uint8_t nmb12_b[] = {
		#include "resource/nmb12_b.h"
	};
	const uint8_t nmb12_v[] = {
		#include "resource/nmb12_v.h"
	};
	const uint8_t nmb12_c[] = {
		#include "resource/nmb12_c.h"
	};
	const uint8_t nmb12_do[] = {
		#include "resource/nmb12_do.h"
	};

	// 18x32 ピクセルフォント
	const uint8_t nmb32_0[] = {
		#include "resource/nmb32_0.h"
	};
	const uint8_t nmb32_1[] = {
		#include "resource/nmb32_1.h"
	};
	const uint8_t nmb32_2[] = {
		#include "resource/nmb32_2.h"
	};
	const uint8_t nmb32_3[] = {
		#include "resource/nmb32_3.h"
	};
	const uint8_t nmb32_4[] = {
		#include "resource/nmb32_4.h"
	};
	const uint8_t nmb32_5[] = {
		#include "resource/nmb32_5.h"
	};
	const uint8_t nmb32_6[] = {
		#include "resource/nmb32_6.h"
	};
	const uint8_t nmb32_7[] = {
		#include "resource/nmb32_7.h"
	};
	const uint8_t nmb32_8[] = {
		#include "resource/nmb32_8.h"
	};
	const uint8_t nmb32_9[] = {
		#include "resource/nmb32_9.h"
	};
	const uint8_t nmb32_kmh[] = {
		#include "resource/nmb32_kmh.h"
	};
	const uint8_t nmb32_c[] = {
		#include "resource/nmb32_c.h"
	};
	const uint8_t nmb32_p[] = {
		#include "resource/nmb32_p.h"
	};
	const uint8_t nmb32_x[] = {
		#include "resource/nmb32_x.h"
	};
	const uint8_t nmb32_rpm[] = {
		#include "resource/nmb32_rpm.h"
	};

	const uint8_t title_bmp[] = {
		#include "resource/title_bmp.h"
	};

#if 0
	const uint8_t batt_icon[] = {
		#include "resource/batt_icon.h"
	};
	const uint8_t batt_ext[] = {
		#include "resource/batt_ext.h"
	};
#endif

	const uint8_t* nmb12[10] = {
		nmb12_0,
		nmb12_1,
		nmb12_2,
		nmb12_3,
		nmb12_4,
		nmb12_5,
		nmb12_6,
		nmb12_7,
		nmb12_8,
		nmb12_9,
	};

	const uint8_t* nmb32[10] = {
		nmb32_0,
		nmb32_1,
		nmb32_2,
		nmb32_3,
		nmb32_4,
		nmb32_5,
		nmb32_6,
		nmb32_7,
		nmb32_8,
		nmb32_9,
	};

}
