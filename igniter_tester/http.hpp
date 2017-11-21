#pragma once
//=====================================================================//
/*! @file
    @brief  RX71M イグナイター・テスター HTTP サーバー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "r_net/http_server.hpp"

namespace {

	template <class HTTPS>
	class http {

		HTTPS&		https_;

	public:
		http(HTTPS& https) : https_(https) { }



	};
}

