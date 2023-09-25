#pragma once
//=====================================================================//
/*!	@file
	@brief	ルネサス RX ペリフェラル／デバイス選択
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/byte_order.h"
#include "common/vect.h"
#include "common/delay.hpp"
#include "common/device.hpp"

#if defined(SIG_RX220)
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
// #include "RX220/flash_io.hpp"
#include "RX600/dmac_mgr.hpp"

#elif defined(SIG_RX24T)
#include "RX24T/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX600/bus.hpp"
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

#elif defined(SIG_RX26T)
#include "RX24T/lvda.hpp"
#include "RX600/cac.hpp"
#include "RX600/bus.hpp"
#include "RX600/dmac.hpp"
#include "RX600/elc.hpp"
#include "RX26T/port.hpp"
#include "RX600/mtu3.hpp"
// #include "RX600/poe3d.hpp"
#include "RX600/gptw.hpp"
#include "RX600/hrpwm.hpp"
// #include "RX600/poeg.hpp"
#include "RX600/tmr.hpp"
#include "RX600/cmtw.hpp"
#include "RX600/wdta.hpp"
#include "RX600/sci_k.hpp"
#include "RX600/sci_h.hpp"
#include "RX600/rsci.hpp"
// #include "RX600/ri3c.hpp"
// #include "RX600/canfd.hpp"
// #include "RX600/rspia.hpp"
#include "RX600/crca.hpp"
// #include "RX600/tfuv2.hpp"
// #include "RX72T/s12adh.hpp"
#include "RX600/r12da.hpp"
// #include "RX600/temps.hpp"
#include "RX600/cmpc.hpp"
// #include "RX600/doca.hpp"
#include "RX26T/flash.hpp"

#include "RX26T/system_io.hpp"
// #include "RX600/flash_io.hpp"
#include "RX600/dmac_mgr.hpp"
#include "RX600/dac_out.hpp"

#elif defined(SIG_RX621) || defined(SIG_RX62N)
#include "RX62x/lvd.hpp"
#include "RX62x/bus.hpp"
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
#include "RX600/etherc.hpp"
#include "RX600/edmac.hpp"
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

#elif defined(SIG_RX631) || defined(SIG_RX63N)
#include "RX63T/lvda.hpp"
#include "RX63x/mck.hpp"
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
#include "RX600/etherc.hpp"
#include "RX600/edmac.hpp"
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
#include "RX24T/dac_out.hpp"

#elif defined(SIG_RX63T) || defined(SIG_RX63T_S)
#include "RX63T/lvda.hpp"
#include "RX63T/bus.hpp"
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
// #include "RX63T/flash_io.hpp"
#include "RX600/dmac_mgr.hpp"
// #include "RX63T/dac_out.hpp"

#elif defined(SIG_RX64M) || defined(SIG_RX71M)
#include "RX600/lvda.hpp"
#include "RX600/bus.hpp"
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
#include "RX64M/flash.hpp"
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

#elif defined(SIG_RX65N)
#include "RX600/lvda.hpp"
#include "RX600/bus.hpp"
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
#include "RX600/etherc.hpp"
#include "RX600/edmac.hpp"
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

#elif defined(SIG_RX72M) || defined(SIG_RX72N)
#include "RX600/lvda.hpp"
#include "RX600/bus.hpp"
#include "RX600/cac.hpp"
#include "RX72N/port.hpp"
#include "RX600/mtu3.hpp"
#include "RX72N/poe3.hpp"
#include "RX600/tmr.hpp"
#include "RX600/dmac.hpp"
#include "RX600/elc.hpp"
#include "RX600/exdmac.hpp"
#include "RX600/tpu.hpp"
#include "RX600/ppg.hpp"
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

#elif defined(SIG_RX66T) || defined(SIG_RX72T)
#include "RX600/lvda.hpp"
#include "RX600/bus.hpp"
#include "RX600/cac.hpp"
#include "RX66T/port.hpp"
#include "RX600/mtu3.hpp"
#include "RX66T/poe3.hpp"
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

#else
#  error "renesas.hpp: Requires SIG_RXxxx to be defined"
#endif

// RX マイコン共通ペリフェラル
#include "RX600/dtc.hpp"
#include "RX600/cmt.hpp"
#include "RX600/iwdt.hpp"
#include "RX600/riic.hpp"
#include "RX600/rspi.hpp"
#include "RX600/mpu.hpp"
