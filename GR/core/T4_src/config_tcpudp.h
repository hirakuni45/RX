#pragma once
//=====================================================================//
/*!	@file
	@brief	TCP/UDP config @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "net_config.h"
#include "r_t4_itcpip.h"
#include "udp.h"
#include "tcp.h"

extern int t4_udp_callback(uint32_t cepid, int32_t fncd, void *p_parblk);

#if defined(_TCP)
extern T_TCP_CREP tcp_crep[];
extern const uint32_t tcp_crep_num;

extern T_TCP_CCEP tcp_ccep[];
extern const uint32_t tcp_ccep_num;

extern const uint16_t tcp_mss[];
extern const uint32_t tcp_initial_seqno[];
extern const uint16_t tcp_2msl[];
extern const uint32_t tcp_rt_tmo_rst[];

extern const uint8_t tcp_dack[];

typedef struct {
	uint8_t	mac[6];
} MAC_ADDRESS;

extern MAC_ADDRESS ethernet_mac[];

#endif

#if defined(_UDP)
extern _UDP_CB  *_udp_cb;
extern T_UDP_CCEP udp_ccep[];
extern const uint32_t udp_ccep_num;
#endif

extern TCPUDP_ENV tcpudp_env[];
