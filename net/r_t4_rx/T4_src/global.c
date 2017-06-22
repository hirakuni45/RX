//=====================================================================//
/*! @file
    @brief  global.c @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "global.h"

uint8_t *data_link_buf_ptr;      /* Buffer pointer to Datalink layer */
_CH_INFO *_ch_info_tbl;
_CH_INFO *_ch_info_head;
_UDP_CB  *_udp_cb;

uint8_t *data_link_buf_ptr;
_TX_HDR _tx_hdr;

_TCB  *_tcp_tcb;    /* TCB (Transport Control Block) pointer */
_TCB  *head_tcb;    /* TCB head pointer */
_TX_HDR  _tx_hdr;    /* TCP transmit header area */
uint16_t _tcp_timer_cnt;   /* timer count: 10ms unit */
uint16_t _tcp_pre_timer_cnt;  /* previous timer count */

_ARP_ENTRY **_ether_arp_tbl;

uint8_t *_ether_p_rcv_buff;
