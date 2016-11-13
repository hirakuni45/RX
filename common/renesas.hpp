#pragma once
//=====================================================================//
/*!	@file
	@brief	ルネサス RX 選択 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
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
#include "RX24T/poe3.hpp"
#include "RX24T/tmr.hpp"
#include "RX600/cmt.hpp"
#include "RX24T/sci.hpp"
#include "RX24T/riic.hpp"
#include "RX24T/rspi.hpp"
#include "RX24T/crc.hpp"
#include "RX24T/s12ad.hpp"
#include "RX24T/da.hpp"
#include "RX24T/cmpc.hpp"
#include "RX24T/doc.hpp"
#include "RX24T/port_map.hpp"
#include "RX24T/power_cfg.hpp"
#include "RX24T/icu_mgr.hpp"

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
#include "RX64M/mpc.hpp"
#include "RX64M/icu.hpp"
#include "RX64M/sci.hpp"
#include "RX64M/riic.hpp"
#include "RX64M/port_map.hpp"
#include "RX64M/power_cfg.hpp"
#include "RX64M/icu_mgr.hpp"
#else
#  error "Requires SIG_XXX to be defined"
#endif
