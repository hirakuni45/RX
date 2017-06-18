#pragma once
//=====================================================================//
/*! @file
    @brief  r_tcpip_private.h @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdint.h>

#define _far
#define far

#define _ETHER
#define _UDP
#define _TCP
#define _ICMP
#define _IGMP
#define _MULTI
#define _TCP_DACK

#define __RX600 1
#define __LIT 1

void get_random_number(uint8_t *, uint16_t);
