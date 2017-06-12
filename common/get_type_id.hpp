#pragma once
//=====================================================================//
/*!	@file
	@brief	クラス型識別 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	クラスの「型」情報を取得する仕組み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	namespace any_detail {
		template<class value_type> struct dummy_ { static char p; };
		template<class value_type> char dummy_<value_type>::p;
	}
	typedef void* type_id;
	template<class value_type>
	type_id get_type_id() { return &any_detail::dummy_<value_type>::p; }

}
