#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・ペリフェラル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ペリフェラル種別
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral {
		SCI0,
		SCI1,
		SCI2,
		SCI3,

		CMT0,
		CMT1,
		CMT2,
		CMT3,
	};
}
