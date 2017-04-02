#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ A/D 制御 @n
			Copyright 2016, 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#if defined(SIG_RX24T)
#include "RX24T/adc_io.hpp"
#elif defined(SIG_RX64M)
#include "RX64M/adc_io.hpp"
#endif
