#pragma once
//=====================================================================//
/*! @file
    @brief  global.h @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdint.h>
#include "t4define.h"
#include "type.h"
#include "r_t4_itcpip.h"
#include "ether.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "dhcp.h"

extern _TX_HDR _tx_hdr;
extern uint16_t _tcp_timer_cnt;   /* timer count: 10ms unit */
extern uint16_t _tcp_pre_timer_cnt;  /* previous timer count */

extern uint8_t *data_link_buf_ptr;      /* Buffer pointer to Datalink layer */
extern _CH_INFO *_ch_info_tbl;
extern _CH_INFO *_ch_info_head;
extern _UDP_CB  *_udp_cb;
extern uint8_t *data_link_buf_ptr;

extern _TCB  *_tcp_tcb;    /* TCB (Transport Control Block) pointer */
extern _TCB  *head_tcb;    /* TCB head pointer */

extern _ARP_ENTRY **_ether_arp_tbl;

extern uint8_t *_ether_p_rcv_buff;
