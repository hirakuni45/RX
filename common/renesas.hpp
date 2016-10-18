#pragma once
//=====================================================================//
/*!	@file
	@brief	ルネサス RX 選択 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#if defined(SIG_RX621)
#include "RX600/cmt.hpp"
#include "RX600/port.hpp"
#include "RX621/system.hpp"
#include "RX621/sci.hpp"
#include "RX621/icu.hpp"
#elif defined(SIG_RX62N)

#elif defined(SIG_RX62G)

#elif defined(SIG_RX63T)
#include "RX600/cmt.hpp"
#include "RX600/port.hpp"
#include "RX63T/system.hpp"
#include "RX63T/sci.hpp"
#include "RX63T/icu.hpp"
#include "RX63T/port_map.hpp"
#include "RX63T/power_cfg.hpp"
#include "RX63T/icu_mgr.hpp"
#elif defined(SIG_RX630)

#elif defined(SIG_RX64M)
#include "RX600/port.hpp"
#include "RX600/cmt.hpp"
#include "RX64M/system.hpp"
#include "RX64M/mpc.hpp"
#include "RX64M/icu.hpp"
#include "RX64M/sci.hpp"
#include "RX64M/port_map.hpp"
#include "RX64M/power_cfg.hpp"
#include "RX64M/icu_mgr.hpp"
#else
#  error "Requires SIG_XXX to be defined"
#endif
