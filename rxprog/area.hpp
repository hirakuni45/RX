#pragma once
//=====================================================================//
/*!	@file
	@brief	領域クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <vector>

namespace utils {

	struct area_t {
		uint32_t	org_;
		uint32_t	end_;
		area_t(uint32_t o = 0, uint32_t e = 0) : org_(o), end_(e) { }

		bool is_in(uint32_t adr) const {
			if(org_ <= adr && adr <= end_) return true;
			else return false;
		}

		uint32_t length() const {
			return end_ - org_ + 1;
		}
	};

	typedef std::vector<area_t>	areas;
}
