#pragma once
//=====================================================================//
/*! @file
    @brief  RX71M イグナイター・テスター・コントローラー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#define HTTP_DEBUG

#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/rspi_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/delay.hpp"
#include "common/command.hpp"

#include "r_net/ethernet.hpp"
#include "r_net/http_server.hpp"
#include "r_net/ftp_server.hpp"
#include "r_net/telnet_server.hpp"

extern "C" {
	void INT_Excep_ICU_GROUPAL1(void);
}

