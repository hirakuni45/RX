#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ MTU 制御 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"
#include "RX24T/port_map.hpp"
#include "RX24T/power_cfg.hpp"

/// F_PCKD は変換パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCKA
#  error "mtu_io.hpp requires F_PCKD to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU 制御クラス
		@param[in]	MTU		MTU ユニット
		@param[in]	TASK	割り込みタスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class MTU, class TASK>
	class mtu_io {
	public:




	};
}
