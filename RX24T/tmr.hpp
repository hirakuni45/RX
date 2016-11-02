#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・8 ビットタイマ（TMR）定義 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX24T/peripheral.hpp"
#include "RX24T/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  8 ビットタイマ（TMR）
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct tmr_t {





	};
	typedef tmr_t<0x00088200> TMR01;
	typedef tmr_t<0x00088210> TMR23;
	typedef tmr_t<0x00088220> TMR45;
	typedef tmr_t<0x00088230> TMR67;
}
