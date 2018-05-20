#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ　DMACAa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX600/peripheral.hpp"
#include "RX600/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DMA コントローラ（DMACAa）
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct dmaca_core_t {


	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	DMA コントローラ（DMACAa）
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct dmaca_t : public dmaca_core_t<base> {

	};

	typedef dmaca_t<0x00820000, peripheral::DMACA0>    DMACA0;
	typedef dmaca_t<0x00820040, peripheral::DMACA1>    DMACA1;
	typedef dmaca_t<0x00820080, peripheral::DMACA2>    DMACA2;
	typedef dmaca_t<0x008200C0, peripheral::DMACA3>    DMACA3;
	typedef dmaca_t<0x00820100, peripheral::DMACA4>    DMACA4;
	typedef dmaca_t<0x00820140, peripheral::DMACA5>    DMACA5;
	typedef dmaca_t<0x00820180, peripheral::DMACA6>    DMACA6;
	typedef dmaca_t<0x008201C0, peripheral::DMACA7>    DMACA7;
}
