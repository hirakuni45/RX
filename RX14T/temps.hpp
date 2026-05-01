#pragma once
//=========================================================================//
/*!	@file
	@brief	RX14T 温度センサ (TEMPSA)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  温度センサ・クラス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct tempsa_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  温度センサ校正データレジスタ (TSCDR) @n
					V1 = 5 × CAL140 / 4096 [V]
		*/
		//-----------------------------------------------------------------//
		static inline ro16_t<0x007F'C228> TSCDR;

	};
	typedef tempsa_t TEMPS;
}
