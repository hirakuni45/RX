#pragma once
//=====================================================================//
/*!	@file
	@brief	ether.h
	@brief	ether.c
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <stdint.h>

#define _EP_MIN_LEN  60
#define _ETH_LEN  14
#define _EP_PAD_MAX  18

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct
{
    uint16_t len; // 受信パケットの長さ
    uint8_t *pip; // IPヘッダの先頭へのポインタ
    uint8_t ip_rcv; // IPデータを受信：1　それ以外：0（リリース時にゼロクリア）
} _P_RCV_BUF;

typedef struct
{
    uint8_t   eh_dst[6];    /* destination ip address     */
    uint8_t   eh_src[6];    /* source ip address          */
    uint16_t  eh_type;   /* Ethernet packet type */
} _ETH_HDR;

typedef struct
{
    _ETH_HDR eh;    /* Ether Header (Received BUFFER) */
    uint8_t data[1];  /* DATA */
} _EP;


/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
void _ether_proc_rcv(void);
int16_t _ether_snd_ip(uint8_t *data, uint16_t dlen);
int16_t _ether_snd(uint16_t type, uint8_t  *data, uint16_t dlen);

/*==================================================*/
/* For ARP */
/*==================================================*/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#define AR_REQUEST 1 /* ARP request to resolve address */
#define AR_REPLY 2 /* reply to a resolve request  */

/* cache timeouts */

#define ARP_TIMEOUT  (10*60*100) /* 10 minutes    */
#define ARP_RESEND_1ST 2 /* resend if no reply in 1 ～ 2sec (only first time) */
#define ARP_RESEND  1 /* resend if no reply in 1 sec                      */
#define CYC_INTVL  100 /* 100 x 10ms = 1sec */
#define ARP_MAXRETRY 4 /* give up after a ~30 seconds  */

#define AS_FREE  0x0 /* Entry is unused (initial value) */
#define AS_PENDING 0x1 /* Entry is used but incomplete  */
#define AS_RESOLVED 0x2 /* Entry has been resolved  */
#define AS_TMOUT 0x4 /* ARP Retry Timeout */

#define RES_MASK        0x01    /* arpflag mask Resolved or not */
#define PAC_MASK        0x02    /* arpflag mask Packet exist or not */

#define HWT_ETH         0x0001
#define EPT_LOOP 0x0060  /* type: Loopback  */
#define EPT_IP  0x0800  /* type: Internet Protocol */
#define EPT_ARP  0x0806  /* type: ARP   */
#define EPT_IPV6 0x86DD  /* type: IPv6   */

#define AR_HARDWARE 1 /* Ethernet hardware type code  */
#define ETH_HLEN_ARP    (2 * EP_ALEN + 2) /* = 14 Byte */
#define ARP_PLEN        28      /* ARP packet length (Except for Eth Hdr) */
#define DUMMY_LEN       (60 - ETH_HLEN_ARP - ARP_PLEN) /* = 18 Byte */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

typedef struct
{
    uint32_t dst_ipaddr; /* Destination IP address (may differ from nexthop) */
    uint8_t  proto;    /* protocol code */
} _IPH_INFO;

typedef struct
{
    int16_t   ar_hwtype; /* hardware type   */
    int16_t   ar_prtype; /* protocol type   */
    uint8_t ar_hwlen; /* hardware address length  */
    uint8_t ar_prlen; /* protocol address length  */
    uint16_t ar_op;  /* ARP operation (see list above) */
    uint8_t ar_sha[6];  /* sender hw addrs */
    uint8_t ar_spa[4];  /* sender proto addrs */
    uint8_t ar_tha[6];  /* target hw addrs */
    uint8_t ar_tpa[4];  /* target proto addrs */
} _ARP_PKT ;


#if !defined(_IPV6)
typedef struct
{
    uint8_t ae_pra[4];   /* Protocol address   */
    uint8_t ae_hwa[6];   /* Hardware address   */
    uint16_t ae_ttl;   /* time to live    */
    uint8_t ae_state;  /* state of this entry (see above) */
    uint8_t ae_attempts; /* number of retries so far  */
} ARP_ENTRY;

extern ARP_ENTRY **ether_arp_tbl_;

void _ether_rcv_arp(void);
int16_t _ether_snd_arp(ARP_ENTRY *ae);
void _ether_arp_resolve(void);
void _ether_arp_init(void);
void _ether_arp_del(ARP_ENTRY *ae);
ARP_ENTRY *_ether_arp_add(uint8_t *ipaddr, uint8_t *ethaddr);

#if defined(__cplusplus)
extern "C" {
#endif

//-----------------------------------------------------------------//
/*!
	@brief  ARP テーブル数をカウント
	@return ARP テーブル数
*/
//-----------------------------------------------------------------//
uint32_t ether_arp_num(void);


//-----------------------------------------------------------------//
/*!
	@brief  ARP テーブルを取得
	@return ARP テーブル
*/
//-----------------------------------------------------------------//
const ARP_ENTRY* ether_arp_get(uint32_t idx);

#if defined(__cplusplus)
}
#endif

#endif
