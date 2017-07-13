#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ A/D 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#if defined(SIG_RX24T)
#include "RX24T/adc_io.hpp"
#elif defined(SIG_RX64M)
#include "RX64M/adc_io.hpp"
#endif
