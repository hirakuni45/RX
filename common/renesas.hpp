#pragma once
//=====================================================================//
/*!	@file
	@brief	ルネサス RX 選択
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/byte_order.h"
#include "common/vect.h"
#include "common/delay.hpp"

#if defined(SIG_RX621)
#include "RX600/port.hpp"
#include "RX600/cmt.hpp"
#include "RX621/system.hpp"
#include "RX621/sci.hpp"
#include "RX621/icu.hpp"

#elif defined(SIG_RX24T)
#include "RX24T/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX24T/system.hpp"
#include "RX24T/dtc.hpp"
#include "RX24T/icu.hpp"
#include "RX24T/mtu3.hpp"
#include "RX24T/mtu_io.hpp"
#include "RX24T/poe3.hpp"
#include "RX24T/gpt.hpp"
#include "RX24T/tmr.hpp"
#include "RX600/cmt.hpp"
#include "RX24T/sci.hpp"
#include "RX24T/riic.hpp"
#include "RX24T/rspi.hpp"
#include "RX24T/crc.hpp"
#include "RX24T/s12ad.hpp"
#include "RX24T/adc_io.hpp"
#include "RX24T/da.hpp"
#include "RX24T/cmpc.hpp"
#include "RX24T/doc.hpp"
#include "RX24T/port_map.hpp"
#include "RX24T/power_cfg.hpp"
#include "RX24T/icu_mgr.hpp"
#include "RX24T/flash.hpp"
#include "RX24T/flash_io.hpp"

#elif defined(SIG_RX63T)
#include "RX63T/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX600/cmt.hpp"
#include "RX63T/system.hpp"
#include "RX63T/sci.hpp"
#include "RX63T/icu.hpp"
#include "RX63T/port_map.hpp"
#include "RX63T/power_cfg.hpp"
#include "RX63T/icu_mgr.hpp"

#elif defined(SIG_RX64M)
#include "RX64M/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX600/cmt.hpp"
#include "RX64M/system.hpp"
#include "RX64M/system_io.hpp"
#include "RX64M/bus.hpp"
#include "RX64M/mpc.hpp"
#include "RX64M/icu.hpp"
#include "RX64M/mtu3.hpp"
#include "RX64M/sci.hpp"
#include "RX64M/riic.hpp"
#include "RX64M/rspi.hpp"
#include "RX64M/port_map.hpp"
#include "RX64M/power_cfg.hpp"
#include "RX64M/icu_mgr.hpp"
#include "RX64M/s12adc.hpp"
#include "RX64M/r12da.hpp"
#include "RX64M/adc_io.hpp"
#include "RX64M/sdram.hpp"
#include "RX64M/etherc.hpp"
#include "RX64M/edmac.hpp"
#include "RX64M/rtc.hpp"
#include "RX64M/rtc_io.hpp"
#include "RX64M/flash.hpp"
#include "RX64M/flash_io.hpp"
#include "RX64M/ether_io.hpp"
#include "RX64M/ssi.hpp"
#include "RX64M/sdhi.hpp"

#else
#  error "Requires SIG_XXX to be defined"
#endif
