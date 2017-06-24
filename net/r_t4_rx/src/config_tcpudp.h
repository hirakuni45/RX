#pragma once
//=====================================================================//
/*!	@file
	@brief	TCP/UDP config @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "t4define.h"
#include "r_t4_itcpip.h"

#define MAX_TCP_CREP  8
#define MAX_TCP_CCEP  8
#define MAX_UDP_CCEP  4
#define TOTAL_BSD_SOCKET    (MAX_TCP_CCEP + MAX_UDP_CCEP)

#define TCPUDP_WORK         (13392)

#define  _t4_channel_num 1

extern const uint8_t _t4_dhcp_enable;
extern const uint16_t _t4_dhcp_ip_reply_arp_delay;


extern T_TCP_CREP tcp_crep[MAX_TCP_CREP];

extern const uint16_t __tcprepn;

extern T_TCP_CCEP tcp_ccep[MAX_TCP_CCEP];

extern const uint16_t __tcpcepn;

extern const uint16_t _tcp_mss[_t4_channel_num];

extern uint16_t _tcp_initial_seqno[_t4_channel_num];

extern const uint16_t _tcp_2msl[_t4_channel_num];

extern const uint16_t _tcp_2msl[_t4_channel_num];

extern const uint16_t _tcp_rt_tmo_rst[_t4_channel_num];

extern const uint8_t _tcp_dack[_t4_channel_num];

extern T_UDP_CCEP udp_ccep[MAX_UDP_CCEP];

extern const uint16_t __udpcepn;

extern const uint8_t __multi_TTL[_t4_channel_num];

extern const uint8_t _udp_enable_zerochecksum[_t4_channel_num];

/// extern const callback_from_system_t g_fp_user;

extern const uint16_t _ip_tblcnt[_t4_channel_num];

extern TCPUDP_ENV tcpudp_env[_t4_channel_num];

extern uint8_t _myethaddr[_t4_channel_num][6];

extern const uint16_t ppp_auth;
extern char user_name[8];
extern char user_passwd[8];

/* Dial up-related setting */
extern const char peer_dial[];
extern const char at_commands[];
