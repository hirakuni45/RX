/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : ether.h
* Version      : 1.0
* Description  : Processing for Ether protocol header file
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 01.04.2014 1.00     First Release
***********************************************************************************************************************/

/*==================================================*/
/* For Ethernet*/
/*==================================================*/
#ifndef __ETHER_H__
#define __ETHER_H__
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _EP_MIN_LEN  60
#define _ETH_LEN  14
#define _EP_PAD_MAX  18

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct
{
    uint16 len; // 受信パケットの長さ
    uchar *pip; // IPヘッダの先頭へのポインタ
    uchar ip_rcv; // IPデータを受信：1　それ以外：0（リリース時にゼロクリア）
} _P_RCV_BUF ;

typedef struct
{
    uchar   eh_dst[6];    /* destination ip address     */
    uchar   eh_src[6];    /* source ip address          */
    uint16  eh_type;   /* Ethernet packet type */
} _ETH_HDR;

typedef struct
{
    _ETH_HDR eh;    /* Ether Header (Received BUFFER) */
    uchar data[1];  /* DATA */
} _EP;

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/
extern UB   _myethaddr[][6];

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
void _ether_proc_rcv(void);
sint16 _ether_snd_ip(uchar *data, uint16 dlen);
sint16 _ether_snd(uint16 type, uchar  *data, uint16 dlen);

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
    uint32 dst_ipaddr; /* Destination IP address (may differ from nexthop) */
    uchar  proto;    /* protocol code */
} _IPH_INFO;

typedef struct
{
    sint16   ar_hwtype; /* hardware type   */
    sint16   ar_prtype; /* protocol type   */
    uchar ar_hwlen; /* hardware address length  */
    uchar ar_prlen; /* protocol address length  */
    uint16 ar_op;  /* ARP operation (see list above) */
    uchar ar_sha[6];  /* sender hw addrs */
    uchar ar_spa[4];  /* sender proto addrs */
    uchar ar_tha[6];  /* target hw addrs */
    uchar ar_tpa[4];  /* target proto addrs */
} _ARP_PKT ;


#if !defined(_IPV6)
typedef struct
{
    uchar ae_pra[4];   /* Protocol address   */
    uchar ae_hwa[6];   /* Hardware address   */
    uint16 ae_ttl;   /* time to live    */
    uchar ae_state;  /* state of this entry (see above) */
    uchar ae_attempts; /* number of retries so far  */
} _ARP_ENTRY ;
extern _ARP_ENTRY **_ether_arp_tbl;

void _ether_rcv_arp(void);
sint16 _ether_snd_arp(_ARP_ENTRY *ae);
void _ether_arp_resolve(void);
void _ether_arp_init(void);
void _ether_arp_del(_ARP_ENTRY *ae);
_ARP_ENTRY *_ether_arp_add(uchar *ipaddr, uchar *ethaddr);
#endif

void dump_ep_header(const _EP *p);

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
#endif	/*multi include guard*/
