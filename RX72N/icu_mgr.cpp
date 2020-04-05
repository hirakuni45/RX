//=====================================================================//
/*!	@file
	@brief	RX72N グループ・割り込みマネージャー定数実装
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX72N/icu_mgr.hpp"

namespace device {

	utils::dispatch<icu_t::VECTOR::GROUPBE0, 2>  icu_mgr::GROUPBE0_dispatch_;
	utils::dispatch<icu_t::VECTOR::GROUPBL0, 32> icu_mgr::GROUPBL0_dispatch_;
	utils::dispatch<icu_t::VECTOR::GROUPBL1, 32> icu_mgr::GROUPBL1_dispatch_;
	utils::dispatch<icu_t::VECTOR::GROUPAL0, 22> icu_mgr::GROUPAL0_dispatch_;
	utils::dispatch<icu_t::VECTOR::GROUPAL1, 12> icu_mgr::GROUPAL1_dispatch_;

}
