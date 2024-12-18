#pragma once
//=========================================================================//
/*!	@file
	@brief	ルネサス RX マイコンシリーズ・ペリフェラル・セレクタ
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/byte_order.h"
#include "common/vect.h"
#include "common/delay.hpp"
#include "common/device.hpp"

#include "RX600/dtc.hpp"
#include "RX600/cmt.hpp"
#include "RX600/iwdt.hpp"
#include "RX600/riic.hpp"
#include "RX600/rspi.hpp"

#if defined(SIG_RX110) || defined(SIG_RX111)
#include "RX231/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX140/bus.hpp"
#include "RX140/elc.hpp"
#include "RX220/mtu2.hpp"
#if defined(SIG_RX111)
#include "RX220/poe2.hpp"
#endif
#include "RX140/rtc.hpp"
#if defined(SIG_RX111)
#include "RX600/usb.hpp"
#endif
#include "RX600/sci_e.hpp"
#include "RX600/sci_f.hpp"
#include "RX600/crc.hpp"
#include "RX111/s12adb.hpp"
#if defined(SIG_RX111)
#include "RX140/da.hpp"
#endif
#include "RX600/doc.hpp"
#include "RX130/flash.hpp"

#include "RX140/system_io.hpp"
#if defined(SIG_RX111)
#include "RX24T/flash_io.hpp"
#endif
#include "RX24T/adc_in.hpp"
#if defined(SIG_RX111)
#include "RX600/dac_out.hpp"
#endif

#if defined(SIG_RX110)
#include "RX110/board_profile.hpp"
#elif defined(SIG_RX111)
#include "RX111/board_profile.hpp"
#endif

#elif defined(SIG_RX113)
#include "RX231/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX140/bus.hpp"
#include "RX140/elc.hpp"
#include "RX220/mtu2.hpp"
#include "RX220/poe2.hpp"
#include "RX600/tmr.hpp"
#include "RX140/rtc.hpp"
#include "RX600/lpt.hpp"
#include "RX600/usb.hpp"
#include "RX600/sci_e.hpp"
#include "RX600/sci_f.hpp"
#include "RX220/irda.hpp"
#include "RX600/ssi.hpp"
#include "RX600/crc.hpp"
#include "RX600/lcdc.hpp"
#include "RX600/ctsu.hpp"
#include "RX111/s12adb.hpp"
#include "RX600/r12da.hpp"
#include "RX231/cmpb.hpp"
#include "RX600/doc.hpp"
#include "RX130/flash.hpp"

#include "RX113/system_io.hpp"
#include "RX24T/flash_io.hpp"
#include "RX24T/adc_in.hpp"
#include "RX600/dac_out.hpp"

#include "RX113/board_profile.hpp"

#elif defined(SIG_RX13T)
#include "RX24T/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/mtu3.hpp"
#include "RX13T/poe3.hpp"
#include "RX600/tmr.hpp"
#include "RX600/sci_g.hpp"
#include "RX600/sci_h.hpp"
#include "RX13T/s12ad.hpp"
#include "RX13T/da.hpp"
#include "RX600/cmpc.hpp"
#include "RX130/flash.hpp"
#include "RX600/crc.hpp"
#include "RX600/doc.hpp"

#include "RX24T/system_io.hpp"
#include "RX24T/flash_io.hpp"
#include "RX24T/adc_in.hpp"
#include "RX24T/dac_out.hpp"

#include "RX13T/board_profile.hpp"

#elif defined(SIG_RX130)
#include "RX231/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX140/bus.hpp"
#include "RX140/elc.hpp"
#include "RX220/mtu2.hpp"
#include "RX220/poe2.hpp"
#include "RX600/tmr.hpp"
#include "RX140/rtc.hpp"
#include "RX600/lpt.hpp"
#include "RX600/sci_g.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/remc.hpp"
#include "RX600/crc.hpp"
#include "RX600/ctsu.hpp"
#include "RX231/s12ade.hpp"
#include "RX140/da.hpp"
#include "RX231/cmpb.hpp"
#include "RX600/doc.hpp"
#include "RX130/flash.hpp"

#include "RX140/system_io.hpp"
#include "RX24T/flash_io.hpp"
#include "RX24T/adc_in.hpp"
#include "RX600/dac_out.hpp"

#include "RX130/board_profile.hpp"

#elif defined(SIG_RX140)
#include "RX231/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX140/bus.hpp"
#include "RX140/elc.hpp"
#include "RX220/mtu2.hpp"
#include "RX220/poe2.hpp"
#include "RX600/tmr.hpp"
#include "RX140/rtc.hpp"
#include "RX600/lpt.hpp"
#include "RX600/sci_k.hpp"
#include "RX600/sci_g.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/rscan.hpp"
#include "RX600/crc.hpp"
#include "RX600/ctsu2.hpp"
#include "RX231/s12ade.hpp"
#include "RX140/da.hpp"
#include "RX231/cmpb.hpp"
#include "RX600/doc.hpp"
#include "RX140/flash.hpp"

#include "RX140/system_io.hpp"
#include "RX24T/flash_io.hpp"
#include "RX24T/adc_in.hpp"
#include "RX600/dac_out.hpp"

#include "RX140/board_profile.hpp"

#elif defined(SIG_RX220)
#include "RX220/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX220/bus.hpp"
#include "RX600/dmac.hpp"
#include "RX220/elc.hpp"
#include "RX220/port.hpp"
#include "RX220/mtu2.hpp"
#include "RX220/poe2.hpp"
#include "RX600/tmr.hpp"
#include "RX220/rtc.hpp"
#include "RX600/sci_e.hpp"
#include "RX600/sci_f.hpp"
#include "RX220/irda.hpp"
#include "RX600/crc.hpp"
#include "RX220/s12ad.hpp"
#include "RX220/cmpa.hpp"
#include "RX600/doc.hpp"
#include "RX220/flash.hpp"

#include "RX220/system_io.hpp"
#include "RX62x/flash_io.hpp"
#include "RX24T/adc_in.hpp"
#include "RX600/dmac_mgr.hpp"

#include "RX220/board_profile.hpp"

#elif defined(SIG_RX230) || defined(SIG_RX231)
#include "RX231/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX231/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/dmac.hpp"
#include "RX231/elc.hpp"
#include "RX231/port.hpp"
#include "RX220/mtu2.hpp"
#include "RX231/poe2.hpp"
#include "RX600/tpu.hpp"
#include "RX600/tmr.hpp"
#include "RX231/rtc.hpp"
#include "RX600/lpt.hpp"
#include "RX600/wdta.hpp"
#if defined(SIG_RX231)
#include "RX600/usb.hpp"
#endif
#include "RX600/sci_g.hpp"
#include "RX600/sci_h.hpp"
#include "RX220/irda.hpp"
#if defined(SIG_RX231)
#include "RX600/rscan.hpp"
#endif
#include "RX600/ssi.hpp"
#include "RX600/crc.hpp"
#if defined(SIG_RX231)
#include "RX600/sdhi.hpp"
#endif
#include "RX600/ctsu.hpp"
#include "RX231/s12ade.hpp"
#include "RX600/r12da.hpp"
#include "RX231/cmpb.hpp"
#include "RX600/doc.hpp"
#include "RX231/flash.hpp"

#include "RX231/system_io.hpp"
#include "RX24T/flash_io.hpp"
#include "ff14/sdhi_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX24T/adc_in.hpp"
#include "RX600/dac_out.hpp"

#include "RX231/board_profile.hpp"

#elif defined(SIG_RX23W)

#include "RX231/system_io.hpp"
#include "RX24T/flash_io.hpp"
#include "ff14/sdhi_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/dac_out.hpp"

#include "RX23W/board_profile.hpp"

#elif defined(SIG_RX23T)
#include "RX24T/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX600/bus.hpp"
#include "RX600/mtu3.hpp"
#include "RX13T/poe3.hpp"
#include "RX600/tmr.hpp"
#include "RX600/sci_g.hpp"
#include "RX23T/s12ad.hpp"
#include "RX13T/da.hpp"
#include "RX600/cmpc.hpp"
#include "RX24T/flash.hpp"
#include "RX600/crc.hpp"
#include "RX600/doc.hpp"

#include "RX24T/system_io.hpp"
#include "RX24T/flash_io.hpp"
#include "RX24T/adc_in.hpp"
#include "RX24T/dac_out.hpp"

#include "RX23T/board_profile.hpp"

#elif defined(SIG_RX24T)
#include "RX24T/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX24T/port.hpp"
#include "RX600/mtu3.hpp"
#include "RX24T/poe3.hpp"
#include "RX600/tmr.hpp"
#include "RX600/gpt.hpp"
#include "RX600/rscan.hpp"
#include "RX600/sci_g.hpp"
#include "RX24T/s12ad.hpp"
#include "RX24T/da.hpp"
#include "RX600/cmpc.hpp"
#include "RX24T/flash.hpp"
#include "RX600/crc.hpp"
#include "RX600/doc.hpp"

#include "RX24T/system_io.hpp"
#include "RX24T/flash_io.hpp"
#include "RX24T/adc_in.hpp"
#include "RX24T/dac_out.hpp"

#include "RX24T/board_profile.hpp"

#elif defined(SIG_RX24U)
#include "RX24T/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX24T/port.hpp"
#include "RX600/mtu3.hpp"
#include "RX24T/poe3.hpp"
#include "RX600/tmr.hpp"
#include "RX600/gpt.hpp"
#include "RX600/rscan.hpp"
#include "RX600/sci_g.hpp"
#include "RX24T/s12ad.hpp"
#include "RX24T/da.hpp"
#include "RX600/cmpc.hpp"
#include "RX24T/flash.hpp"
#include "RX600/crc.hpp"
#include "RX600/doc.hpp"

#include "RX24T/system_io.hpp"
#include "RX24T/flash_io.hpp"
#include "RX24T/adc_in.hpp"
#include "RX24T/dac_out.hpp"

#include "RX24U/board_profile.hpp"

#elif defined(SIG_RX260) || defined(SIG_RX261)
#include "RX231/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/dmac.hpp"
#include "RX600/elc.hpp"
#include "RX600/gptw.hpp"
#include "RX600/poeg.hpp"
#include "RX600/tmr.hpp"
#include "RX231/rtc.hpp"
#include "RX600/lpt.hpp"
#include "RX600/wdta.hpp"
#include "RX600/usb.hpp"
#include "RX600/sci_k.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/rsci.hpp"
#include "RX600/canfd.hpp"
#include "RX600/crc.hpp"
#include "RX600/remc.hpp"
#include "RX600/ctsu2.hpp"
#include "RX231/s12ade.hpp"
#include "RX140/da.hpp"
#include "RX231/cmpb.hpp"
#include "RX600/doc.hpp"
#include "RX140/flash.hpp"

#include "RX26x/system_io.hpp"
#include "RX24T/flash_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/dac_out.hpp"

#include "RX26x/board_profile.hpp"

#elif defined(SIG_RX26T)
#include "RX24T/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/dmac.hpp"
#include "RX600/elc.hpp"
#include "RX26T/port.hpp"
#include "RX600/mtu3.hpp"
#include "RX600/poe3d.hpp"
#include "RX600/gptw.hpp"
#include "RX600/hrpwm.hpp"
#include "RX600/poeg.hpp"
#include "RX600/tmr.hpp"
#include "RX600/cmtw.hpp"
#include "RX600/wdta.hpp"
#include "RX600/sci_k.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/rsci.hpp"
#include "RX600/ri3c.hpp"
#include "RX600/canfd.hpp"
#include "RX600/rspia.hpp"
#include "RX600/crca.hpp"
#include "RX600/tfu.hpp"
#include "RX26T/s12adh.hpp"
#include "RX600/r12da.hpp"
#include "RX600/cmpc.hpp"
#include "RX600/doca.hpp"
#include "RX26T/flash.hpp"

#include "RX26T/system_io.hpp"
#include "RX62x/flash_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/adc_in.hpp"
#include "RX600/dac_out.hpp"

#include "RX26T/board_profile.hpp"

#elif defined(SIG_RX62N) || defined(SIG_RX621)
#include "RX62x/lvd.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/dmac.hpp"
#include "RX600/exdmac.hpp"
#include "RX62x/port.hpp"
#include "RX62x/mtu2.hpp"
#include "RX62x/poe2.hpp"
#include "RX600/ppg.hpp"
#include "RX600/tmr.hpp"
#include "RX600/sci_a.hpp"
#include "RX62x/rtc.hpp"
#include "RX62x/wdt.hpp"
#if defined(SIG_RX62N)
#include "RX600/etherc.hpp"
#include "RX600/edmac.hpp"
#endif
#include "RX62x/usb.hpp"
#include "RX600/crc.hpp"
#include "RX600/can.hpp"
#include "RX62x/s12ad.hpp"
#include "RX62x/ad.hpp"
#include "RX62x/da.hpp"
#include "RX62x/flash.hpp"

#include "RX62x/system_io.hpp"
#include "RX62x/flash_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX24T/dac_out.hpp"

#include "RX62x/board_profile.hpp"

#elif defined(SIG_RX63N) || defined(SIG_RX631)
#include "RX63T/lvda.hpp"
#include "RX63x/mck.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/dmac.hpp"
#include "RX600/exdmac.hpp"
#include "RX63x/port.hpp"
#include "RX220/mtu2.hpp"
#include "RX63x/poe2.hpp"
#include "RX600/tpu.hpp"
#include "RX600/ppg.hpp"
#include "RX600/tmr.hpp"
#include "RX63x/rtc.hpp"
#include "RX600/wdta.hpp"
#if defined(SIG_RX63N)
#include "RX600/etherc.hpp"
#include "RX600/edmac.hpp"
#endif
#include "RX62x/usb.hpp"
#include "RX600/sci_c.hpp"
#include "RX600/sci_d.hpp"
#include "RX600/can.hpp"
#include "RX63x/ieb.hpp"
#include "RX600/crc.hpp"
#include "RX600/pdc.hpp"
#include "RX63x/s12ad.hpp"
#include "RX63x/ad.hpp"
#include "RX63x/da.hpp"
#include "RX63x/flash.hpp"

#include "RX63x/system_io.hpp"
#include "RX62x/flash_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/adc_in.hpp"
#include "RX24T/dac_out.hpp"

#include "RX63x/board_profile.hpp"

#elif defined(SIG_RX63T) || defined(SIG_RX63T_S)
#include "RX63T/lvda.hpp"
#include "RX63T/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/dmac.hpp"
#include "RX63T/port.hpp"
#include "RX600/mtu3.hpp"
#include "RX63T/poe3.hpp"
#include "RX63T/gpt.hpp"
#include "RX600/usb.hpp"
#include "RX600/sci_c.hpp"
#include "RX600/sci_d.hpp"
#include "RX600/can.hpp"
#include "RX600/crc.hpp"
#include "RX63T/s12adb.hpp"
#include "RX63T/ad.hpp"
#include "RX63T/da.hpp"
#include "RX600/doc.hpp"
#include "RX63T/dpc.hpp"
#include "RX63T/flash.hpp"

#include "RX63T/system_io.hpp"
#include "RX62x/flash_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/adc_in.hpp"
// #include "RX63T/dac_out.hpp"

#include "RX63T/board_profile.hpp"

#elif defined(SIG_RX64M) || defined(SIG_RX71M)
#include "RX600/lvda.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/cac.hpp"
#include "RX64M/port.hpp"
#include "RX600/mtu3.hpp"
#include "RX64M/poe3.hpp"
#include "RX600/tmr.hpp"
#include "RX600/dmac.hpp"
#include "RX600/elc.hpp"
#include "RX600/exdmac.hpp"
#include "RX600/tpu.hpp"
#include "RX600/gpt.hpp"
#include "RX600/ppg.hpp"
#include "RX600/cmtw.hpp"
#include "RX600/can.hpp"
#include "RX600/qspi.hpp"
#include "RX64M/s12adc.hpp"
#include "RX600/r12da.hpp"
#include "RX600/sdram.hpp"
#include "RX600/etherc.hpp"
#include "RX600/eptpc.hpp"
#include "RX600/edmac.hpp"
#include "RX600/usb.hpp"
#include "RX600/usba.hpp"
#include "RX600/sci_g.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/scif.hpp"
#include "RX600/rtc.hpp"
#include "RX600/rtc_io.hpp"
#include "RX600/wdta.hpp"
#include "RX600/flash.hpp"
#include "RX600/ssi.hpp"
#include "RX600/src.hpp"
#include "RX600/sdhi.hpp"
#include "RX600/mmcif.hpp"
#include "RX600/pdc.hpp"
#include "RX600/standby_ram.hpp"
#include "RX600/crc.hpp"
#include "RX600/doc.hpp"

#include "RX600/system_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/ether_io.hpp"
#include "RX600/adc_in.hpp"
#include "RX600/dac_out.hpp"
#include "RX600/flash_io.hpp"
#include "ff14/sdhi_io.hpp"
#include "RX600/ssi_io.hpp"

#include "RX64M/board_profile.hpp"

#elif defined(SIG_RX65N) || defined(SIG_RX651)
#include "RX600/lvda.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/cac.hpp"
#include "RX64M/port.hpp"
#include "RX600/mtu3.hpp"
#include "RX65x/poe3.hpp"
#include "RX600/tmr.hpp"
#include "RX600/dmac.hpp"
#include "RX600/elc.hpp"
#include "RX600/exdmac.hpp"
#include "RX600/tpu.hpp"
#include "RX600/ppg.hpp"
#include "RX600/cmtw.hpp"
#include "RX600/qspi.hpp"
#include "RX600/can.hpp"
#include "RX600/s12adf.hpp"
#include "RX600/r12da.hpp"
#include "RX600/sdram.hpp"
#if defined(SIG_RX65N)
#include "RX600/etherc.hpp"
#include "RX600/edmac.hpp"
#endif
#include "RX600/usb.hpp"
#include "RX600/sci_g.hpp"
#include "RX600/sci_i.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/rtc.hpp"
#include "RX600/wdta.hpp"
#include "RX600/flash.hpp"
#include "RX600/sdhi.hpp"
#include "RX600/sdsi.hpp"
#include "RX600/mmcif.hpp"
#include "RX600/pdc.hpp"
#include "RX600/standby_ram.hpp"
#include "RX600/glcdc.hpp"
#include "RX600/drw2d.hpp"
#include "RX600/crca.hpp"
#include "RX600/doc.hpp"

#include "RX600/system_io.hpp"
#include "RX600/rtc_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/ether_io.hpp"
#include "ff14/sdhi_io.hpp"
#include "RX600/glcdc_mgr.hpp"
#include "RX600/drw2d_mgr.hpp"
#include "RX600/adc_in.hpp"
#include "RX600/dac_out.hpp"
#include "RX600/flash_io.hpp"

#include "RX65x/board_profile.hpp"

#elif defined(SIG_RX660)
#include "RX600/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/dmac.hpp"
#include "RX600/elc.hpp"
#include "RX600/mtu3.hpp"
#include "RX72N/poe3.hpp"
#include "RX600/cmtw.hpp"
#include "RX600/rtc.hpp"
#include "RX600/wdta.hpp"
#include "RX600/sci_g.hpp"
#include "RX600/sci_m.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/rsci.hpp"
#include "RX600/canfd.hpp"
#include "RX600/crca.hpp"
#include "RX600/remc.hpp"
#include "RX660/s12adh.hpp"
#include "RX600/r12da.hpp"
#include "RX600/cmpc.hpp"
#include "RX600/doca.hpp"
#include "RX600/flash.hpp"

#include "RX600/system_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/flash_io.hpp"
#include "RX600/adc_in.hpp"
#include "RX600/dac_out.hpp"

#include "RX660/board_profile.hpp"

#elif defined(SIG_RX671)
#include "RX600/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/dmac.hpp"
#include "RX600/exdmac.hpp"
#include "RX600/elc.hpp"
#include "RX600/mtu3.hpp"
#include "RX72N/poe3.hpp"
#include "RX600/tpu.hpp"
#include "RX600/ppg.hpp"
#include "RX600/cmtw.hpp"
#include "RX600/rtc.hpp"
#include "RX600/wdta.hpp"
#include "RX600/usb.hpp"
#include "RX600/sci_g.hpp"
#include "RX600/sci_m.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/rsci.hpp"
#include "RX600/riichs.hpp"
#include "RX600/can.hpp"
#include "RX600/rspia.hpp"
#include "RX600/qspix.hpp"
#include "RX600/crca.hpp"
#include "RX600/sdhi.hpp"
#include "RX600/ssie.hpp"
#include "RX600/remc.hpp"
#include "RX600/ctsu.hpp"
#include "RX600/s12adf.hpp"
#include "RX600/doca.hpp"
#include "RX600/standby_ram.hpp"
#include "RX600/flash.hpp"

#include "RX600/system_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/rtc_io.hpp"
#include "ff14/sdhi_io.hpp"
#include "RX600/ssie_io.hpp"
#include "RX600/adc_in.hpp"
#include "RX600/flash_io.hpp"

#include "RX671/board_profile.hpp"

#elif defined(SIG_RX66N) || defined(SIG_RX72N) || defined(SIG_RX72M)
#include "RX600/lvda.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/cac.hpp"
#include "RX72N/port.hpp"
#include "RX600/mtu3.hpp"
#include "RX72N/poe3.hpp"
#include "RX600/tmr.hpp"
#include "RX600/dmac.hpp"
#include "RX600/elc.hpp"
#include "RX600/exdmac.hpp"
#include "RX600/tpu.hpp"
#include "RX600/gptw.hpp"
#include "RX600/ppg.hpp"
#include "RX600/cmtw.hpp"
#include "RX600/can.hpp"
#include "RX600/qspi.hpp"
#include "RX600/s12adf.hpp"
#include "RX600/r12da.hpp"
#include "RX600/sdram.hpp"
#include "RX600/etherc.hpp"
#include "RX600/eptpc.hpp"
#include "RX600/edmac.hpp"
#include "RX600/pmgi.hpp"
#include "RX600/usb.hpp"
#include "RX600/sci_j.hpp"
#include "RX600/sci_i.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/rtc.hpp"
#include "RX600/wdta.hpp"
#include "RX600/flash.hpp"
#include "RX600/ssie.hpp"
#include "RX600/sdhi.hpp"
#include "RX600/mmcif.hpp"
#include "RX600/pdc.hpp"
#if defined(SIG_RX72M)
#include "RX600/dsmif.hpp"
#endif
#include "RX600/standby_ram.hpp"
#include "RX600/glcdc.hpp"
#include "RX600/drw2d.hpp"
#include "RX600/crca.hpp"
#include "RX600/doc.hpp"

#include "RX600/system_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/rtc_io.hpp"
#include "ff14/sdhi_io.hpp"
#include "RX600/ssie_io.hpp"
#include "RX600/glcdc_mgr.hpp"
#include "RX600/drw2d_mgr.hpp"
#include "RX600/adc_in.hpp"
#include "RX600/dac_out.hpp"
#include "RX600/flash_io.hpp"
#include "RX600/ether_io.hpp"

#if defined(SIG_RX72M)
#include "RX72M/board_profile.hpp"
#elif defined(SIG_RX72N)
#include "RX72N/board_profile.hpp"
#elif defined(SIG_RX66N)
#include "RX66N/board_profile.hpp"
#endif

#elif defined(SIG_RX66T) || defined(SIG_RX72T)
#include "RX600/lvda.hpp"
#include "RX600/bus.hpp"
#include "RX600/mpu.hpp"
#include "RX600/cac.hpp"
#include "RX600/mtu3.hpp"
#include "RX72T/poe3.hpp"
#include "RX600/tmr.hpp"
#include "RX600/dmac.hpp"
#include "RX600/elc.hpp"
#include "RX600/gptw.hpp"
#include "RX600/hrpwm.hpp"
#include "RX600/poeg.hpp"
#include "RX600/can.hpp"
#include "RX72T/s12adh.hpp"
#include "RX600/r12da.hpp"
#include "RX600/usb.hpp"
#include "RX600/sci_j.hpp"
#include "RX600/sci_i.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/wdta.hpp"
#include "RX600/flash.hpp"
#include "RX600/cmpc.hpp"
#include "RX600/crca.hpp"
#include "RX600/doc.hpp"

#include "RX600/system_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/dac_out.hpp"
#include "RX600/flash_io.hpp"
#include "RX600/adc_in.hpp"

#if defined(SIG_RX66T)
#include "RX66T/board_profile.hpp"
#else
#include "RX72T/board_profile.hpp"
#endif

#else
#  error "renesas.hpp: Requires SIG_RXxxx to be defined"
#endif
