//=====================================================================//
/*!	@file
	@brief	RX600 グループ・割り込みマネージャー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/icu_mgr.hpp"

namespace device {

	utils::dispatch<icu_t::VECTOR::GROUPBE0, 2>  icu_mgr::GROUPBE0_dispatch_;
#if defined(SIG_RX65N)
	utils::dispatch<icu_t::VECTOR::GROUPBL2, 1>  icu_mgr::GROUPBL2_dispatch_;
#endif
	utils::dispatch<icu_t::VECTOR::GROUPBL0, 32> icu_mgr::GROUPBL0_dispatch_;
	utils::dispatch<icu_t::VECTOR::GROUPBL1, 32> icu_mgr::GROUPBL1_dispatch_;
	utils::dispatch<icu_t::VECTOR::GROUPAL0, 22> icu_mgr::GROUPAL0_dispatch_;
	utils::dispatch<icu_t::VECTOR::GROUPAL1, 12> icu_mgr::GROUPAL1_dispatch_;

}
