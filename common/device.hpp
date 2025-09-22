#pragma once
//=========================================================================//
/*!	@file
	@brief	RX マイコン、デバイス固有ヘッダー @n
			RX110/RX111/RX113 @n
			RX13T @n
			EX130 @n
			RX140 @n
			RX210 @n
			RX220 @n
			RX230/RX231 @n
			RX23W @n
			RX23T @n
			RX24T/RX24U @n
			RX260/RX261 @n
			RX26T @n
			RX62N/RX621 @n
			RX63N/RX631 @n
			RX63T @n
			RX64M/RX71M @n
			RX65N/RX651 @n
			RX66N @n
			RX660 @n
			RX671 @n
			RX72N @n
			RX72M @n
			RX66T/RX72T
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

#if defined(SIG_RX110) || defined(SIG_RX111)
#if defined(SIG_RX110)
#include "RX110/clock_profile.hpp"
#else
#include "RX111/clock_profile.hpp"
#endif
#include "RX111/peripheral.hpp"
#include "RX111/system.hpp"
#include "RX111/power_mgr.hpp"
#include "RX111/icu.hpp"
#include "RX140/icu_mgr.hpp"
#include "RX111/port_map.hpp"
#include "RX111/port_map_mtu.hpp"
#include "RX111/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX113)
#include "RX113/clock_profile.hpp"
#include "RX113/peripheral.hpp"
#include "RX113/system.hpp"
#include "RX113/power_mgr.hpp"
#include "RX113/icu.hpp"
#include "RX140/icu_mgr.hpp"
#include "RX113/port_map.hpp"
#include "RX113/port_map_mtu.hpp"
#include "RX113/port_map_tmr.hpp"
#include "RX113/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX13T)
#include "RX13T/clock_profile.hpp"
#include "RX13T/peripheral.hpp"
#include "RX24T/system.hpp"
#include "RX13T/power_mgr.hpp"
#include "RX13T/icu.hpp"
#include "RX24T/icu_mgr.hpp"
#include "RX13T/port_map.hpp"
#include "RX13T/port_map_mtu.hpp"
#include "RX13T/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX130)
#include "RX130/clock_profile.hpp"
#include "RX130/peripheral.hpp"
#include "RX130/system.hpp"
#include "RX130/power_mgr.hpp"
#include "RX130/icu.hpp"
#include "RX140/icu_mgr.hpp"
#include "RX130/port_map.hpp"
#include "RX130/port_map_mtu.hpp"
#include "RX130/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX140)
#include "RX140/clock_profile.hpp"
#include "RX140/peripheral.hpp"
#include "RX140/system.hpp"
#include "RX140/power_mgr.hpp"
#include "RX140/icu.hpp"
#include "RX140/icu_mgr.hpp"
#include "RX140/port_map.hpp"
#include "RX140/port_map_mtu.hpp"
#include "RX140/port_map_tmr.hpp"
#include "RX140/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX210)
#include "RX210/clock_profile.hpp"
#include "RX210/peripheral.hpp"
#include "RX210/system.hpp"
#include "RX210/power_mgr.hpp"
#include "RX210/icu.hpp"
#include "RX220/icu_mgr.hpp"
#include "RX210/port_map.hpp"
#include "RX210/port_map_mtu.hpp"
#include "RX210/port_map_tpu.hpp"
#include "RX210/port_map_tmr.hpp"
#include "RX210/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX220)
#include "RX220/clock_profile.hpp"
#include "RX220/peripheral.hpp"
#include "RX220/system.hpp"
#include "RX220/power_mgr.hpp"
#include "RX220/icu.hpp"
#include "RX220/icu_mgr.hpp"
#include "RX220/port_map.hpp"
#include "RX220/port_map_mtu.hpp"
#include "RX220/port_map_tmr.hpp"
#include "RX220/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX230) || defined(SIG_RX231)
#include "RX231/clock_profile.hpp"
#include "RX231/peripheral.hpp"
#include "RX231/system.hpp"
#include "RX231/power_mgr.hpp"
#include "RX231/icu.hpp"
#include "RX231/icu_mgr.hpp"
#include "RX231/port_map.hpp"
#include "RX231/port_map_mtu.hpp"
#include "RX231/port_map_tpu.hpp"
#include "RX220/port_map_tmr.hpp"
#include "RX231/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX23W)
#include "RX23W/clock_profile.hpp"
#include "RX23W/peripheral.hpp"
#include "RX231/system.hpp"
#include "RX23W/power_mgr.hpp"
#include "RX23W/icu.hpp"
#include "RX231/icu_mgr.hpp"
#include "RX23W/port_map.hpp"
#include "RX23W/port_map_mtu.hpp"
#include "RX23W/port_map_tpu.hpp"
#include "RX23W/port_map_tmr.hpp"
#include "RX23W/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX23T)
#include "RX23T/clock_profile.hpp"
#include "RX23T/peripheral.hpp"
#include "RX24T/system.hpp"
#include "RX23T/power_mgr.hpp"
#include "RX23T/icu.hpp"
#include "RX24T/icu_mgr.hpp"
#include "RX23T/port_map.hpp"
#include "RX23T/port_map_mtu.hpp"
#include "RX23T/port_map_tmr.hpp"
#include "RX23T/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX24T)
#include "RX24T/clock_profile.hpp"
#include "RX24T/peripheral.hpp"
#include "RX24T/system.hpp"
#include "RX24T/power_mgr.hpp"
#include "RX24T/icu.hpp"
#include "RX24T/icu_mgr.hpp"
#include "RX24T/port_map.hpp"
#include "RX24T/port_map_mtu.hpp"
#include "RX24T/port_map_gpt.hpp"
#include "RX24T/port_map_tmr.hpp"
#include "RX24T/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX24U)
#include "RX24U/clock_profile.hpp"
#include "RX24U/peripheral.hpp"
#include "RX24T/system.hpp"
#include "RX24U/power_mgr.hpp"
#include "RX24U/icu.hpp"
#include "RX24T/icu_mgr.hpp"
#include "RX24U/port_map.hpp"
#include "RX24U/port_map_mtu.hpp"
#include "RX24U/port_map_gpt.hpp"
#include "RX24U/port_map_tmr.hpp"
#include "RX24U/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX260) || defined(SIG_RX261)
#include "RX26x/clock_profile.hpp"
#include "RX26x/peripheral.hpp"
#include "RX26x/system.hpp"
#include "RX26x/power_mgr.hpp"
#include "RX26x/icu.hpp"
#include "RX26x/icu_mgr.hpp"
#include "RX26x/port_map.hpp"
#include "RX26x/port_map_gptw.hpp"
#include "RX26x/port_map_tmr.hpp"
#include "RX26x/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX26T)
#include "RX26T/clock_profile.hpp"
#include "RX26T/peripheral.hpp"
#include "RX26T/system.hpp"
#include "RX26T/power_mgr.hpp"
#include "RX26T/icu.hpp"
#include "RX26T/icu_mgr.hpp"
#include "RX26T/port_map.hpp"
#include "RX26T/port_map_mtu.hpp"
#include "RX26T/port_map_gptw.hpp"
#include "RX26T/port_map_tmr.hpp"
#include "RX26T/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX621) || defined(SIG_RX62N)
#include "RX62x/clock_profile.hpp"
#include "RX62x/peripheral.hpp"
#include "RX62x/system.hpp"
#include "RX62x/power_mgr.hpp"
#include "RX62x/icu.hpp"
#include "RX62x/icu_mgr.hpp"
#include "RX62x/port_map.hpp"
#include "RX62x/port_map_mtu.hpp"
#include "RX62x/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX631) || defined(SIG_RX63N)
#include "RX63x/clock_profile.hpp"
#include "RX63x/peripheral.hpp"
#include "RX63x/system.hpp"
#include "RX63x/power_mgr.hpp"
#include "RX63x/icu.hpp"
#include "RX63x/icu_mgr.hpp"
#include "RX63x/port_map.hpp"
#include "RX63x/port_map_mtu.hpp"
#include "RX63x/port_map_tpu.hpp"
#include "RX63x/port_map_tmr.hpp"
#include "RX600/port_map_irq.hpp"
#if defined(SIG_RX63N)
#include "RX64M/port_map_ether.hpp"
#endif
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX63T) || defined(SIG_RX63T_S)
#include "RX63T/clock_profile.hpp"
#include "RX63T/peripheral.hpp"
#include "RX63T/system.hpp"
#include "RX63T/power_mgr.hpp"
#include "RX63T/icu.hpp"
#include "RX63T/icu_mgr.hpp"
#include "RX63T/port_map.hpp"
#include "RX63T/port_map_mtu.hpp"
#include "RX63T/port_map_gpt.hpp"
#include "RX63T/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX64M)
#include "RX64M/clock_profile.hpp"
#include "RX64M/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX64M/power_mgr.hpp"
#include "RX64M/icu.hpp"
#include "RX64M/icu_mgr.hpp"
#include "RX64M/port_map.hpp"
#include "RX64M/port_map_sci.hpp"
#include "RX64M/port_map_mtu.hpp"
#include "RX64M/port_map_gpt.hpp"
#include "RX64M/port_map_tpu.hpp"
#include "RX63x/port_map_tmr.hpp"
#include "RX64M/port_map_qspi.hpp"
#include "RX64M/port_map_ether.hpp"
#include "RX600/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX71M)
#include "RX71M/clock_profile.hpp"
#include "RX64M/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX64M/power_mgr.hpp"
#include "RX64M/icu.hpp"
#include "RX64M/icu_mgr.hpp"
#include "RX64M/port_map.hpp"
#include "RX64M/port_map_sci.hpp"
#include "RX64M/port_map_mtu.hpp"
#include "RX64M/port_map_gpt.hpp"
#include "RX64M/port_map_tpu.hpp"
#include "RX63x/port_map_tmr.hpp"
#include "RX64M/port_map_qspi.hpp"
#include "RX64M/port_map_ether.hpp"
#include "RX600/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX651) || defined(SIG_RX65N)
#include "RX65x/clock_profile.hpp"
#include "RX65x/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX65x/power_mgr.hpp"
#include "RX65x/icu.hpp"
#include "RX65x/icu_mgr.hpp"
#include "RX65x/port_map.hpp"
#include "RX65x/port_map_mtu.hpp"
#include "RX65x/port_map_tpu.hpp"
#include "RX63x/port_map_tmr.hpp"
#include "RX65x/port_map_qspi.hpp"
#include "RX64M/port_map_ether.hpp"
#include "RX600/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX66N)
#include "RX66N/clock_profile.hpp"
#include "RX66N/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX66N/power_mgr.hpp"
#include "RX66N/icu.hpp"
#include "RX66N/icu_mgr.hpp"
#include "RX72N/port_map.hpp"
#include "RX72N/port_map_mtu.hpp"
#include "RX72N/port_map_gptw.hpp"
#include "RX72N/port_map_tpu.hpp"
#include "RX63x/port_map_tmr.hpp"
#include "RX72N/port_map_qspi.hpp"
#include "RX72N/port_map_ether.hpp"
#include "RX600/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX660)
#include "RX660/clock_profile.hpp"
#include "RX660/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX660/power_mgr.hpp"
#include "RX660/icu.hpp"
#include "RX660/icu_mgr.hpp"
#include "RX660/port_map.hpp"
#include "RX660/port_map_mtu.hpp"
#include "RX671/port_map_tmr.hpp"
#include "RX671/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX671)
#include "RX671/clock_profile.hpp"
#include "RX671/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX671/power_mgr.hpp"
#include "RX671/icu.hpp"
#include "RX671/icu_mgr.hpp"
#include "RX671/port_map.hpp"
#include "RX671/port_map_mtu.hpp"
#include "RX671/port_map_tpu.hpp"
#include "RX671/port_map_tmr.hpp"
#include "RX671/port_map_qspix.hpp"
#include "RX671/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX72N)
#include "RX72N/clock_profile.hpp"
#include "RX72N/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX72N/power_mgr.hpp"
#include "RX72N/icu.hpp"
#include "RX72N/icu_mgr.hpp"
#include "RX72N/port_map.hpp"
#include "RX72N/port_map_sci.hpp"
#include "RX72N/port_map_mtu.hpp"
#include "RX72N/port_map_gptw.hpp"
#include "RX72N/port_map_tpu.hpp"
#include "RX63x/port_map_tmr.hpp"
#include "RX72N/port_map_qspi.hpp"
#include "RX72N/port_map_ether.hpp"
#include "RX600/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX72M)
#include "RX72M/clock_profile.hpp"
#include "RX72M/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX72M/power_mgr.hpp"
#include "RX72M/icu.hpp"
#include "RX72M/icu_mgr.hpp"
#include "RX72N/port_map.hpp"
#include "RX72N/port_map_sci.hpp"
#include "RX72N/port_map_mtu.hpp"
#include "RX72N/port_map_gptw.hpp"
#include "RX72N/port_map_tpu.hpp"
#include "RX63x/port_map_tmr.hpp"
#include "RX72N/port_map_qspi.hpp"
#include "RX72N/port_map_ether.hpp"
#include "RX600/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX66T)
#include "RX66T/clock_profile.hpp"
#include "RX72T/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX72T/power_mgr.hpp"
#include "RX72T/icu.hpp"
#include "RX72T/icu_mgr.hpp"
#include "RX72T/port_map.hpp"
#include "RX72T/port_map_mtu.hpp"
#include "RX72T/port_map_gptw.hpp"
#include "RX72T/port_map_tmr.hpp"
#include "RX72T/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#elif defined(SIG_RX72T)
#include "RX72T/clock_profile.hpp"
#include "RX72T/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX72T/power_mgr.hpp"
#include "RX72T/icu.hpp"
#include "RX72T/icu_mgr.hpp"
#include "RX72T/port_map.hpp"
#include "RX72T/port_map_sci.hpp"
#include "RX72T/port_map_mtu.hpp"
#include "RX72T/port_map_gptw.hpp"
#include "RX72T/port_map_tmr.hpp"
#include "RX72T/port_map_irq.hpp"
#include "RX600/rx_dsp_inst.h"

#else
  #error "device.hpp: Requires SIG_XXX to be defined"
#endif
