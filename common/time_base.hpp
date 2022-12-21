#pragma once
//=========================================================================//
/*!	@file
	@brief	時間定義クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  タイム・ベース・クラス
		@param[in]	REF		基準周波数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t REF>
	struct time_base {

		//-----------------------------------------------------------------//
		/*!
			@brief  カウント値を計算
			@param[in]	freq	周波数（小数以下４ビット固定小数点）
		*/
		//-----------------------------------------------------------------//
		uint32_t operator () (uint32_t freq)
		{
			auto n = (REF << 4) / freq;
			return 0;
		}
	};
}
