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
* File Name    : ip.h
* Version      : 1.0
* Description  : Processing for IP protocol header file
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 01.04.2014 1.00     First Release
***********************************************************************************************************************/
#ifndef IP_H
#define IP_H

/* protocol type */
#define _IPH_HBH  0  /* Relay point */
#define _IPH_ICMP  1  /* ICMP packets */
#define _IPH_IGMP  2  /* IGMP packets */
#define _IPH_IP   4  /* IP in I */
#define _IPH_TCP  6  /* TCP packets */
#define _IPH_UDP  17  /* UDP packets */
#define _IPH_RH   43  /* Route control header(IPv6) */
#define _IPH_FH   44  /* Fragment header */
#define _IPH_ESP  50  /* Encryption data payload */
#define _IPH_AH   51  /* Authentication header */
#define _IPH_ICMPV6  58  /* ICMPv6 packets */
#define _IPH_NULL  59  /* next header is null */
#define _IPH_ENDOPT  60  /* endpoint */

#define _IPH_VERSION4 4  /* IPv4 (IP version 4) */
#define _IPH_VERSION6 6  /* IPv6 (IP version 6) */

#define _ICMP_HLEN  8  /* ICMP header length (in bytes) */
#define _ICMPV6_HLEN_MIN 4  /* ICMPv6 header minimum length (in bytes) */
#define _ICMPV6_HLEN (_ICMPV6_HLEN_MIN + 56)  /* ICMPv6 MAX header length (in bytes) */
#define _IP_HLEN_MIN 20  /* minimum IP   header length (in bytes)  */
#define _IPV6_HLEN  40  /* IPv6 header length (fixed) (in bytes)  */

#define _IPH_TTL  80  /* Initial time-to-live value */
#define _IPH_MF   0x2000 /* more fragments bit   */
#define _IPH_DF   0x4000 /* don't fragment bit   */
#define _IPH_FRAGOFF 0x1fff  /* fragment offset mask   */

#define E_IP_SENT  0
#define E_IP_PENDING -1

#define _IPV6_ADDR_INVALID  0x00
#define _IPV6_ADDR_TENTATIVE 0x01
#define _IPV6_ADDR_PREFERRED 0x02
#define _IPV6_ADDR_DEPRECATED 0x04
#define _IPV6_ADDR_VALID  0x08

/* ICMPv4 */
#define _ICMP_ECHO_REPLY (0)  /* Echo reply    */
#define _ICMP_ECHO_REQ  (8)  /* Echo request    */

/* ICMPv6 */
#define _ICMPV6_ECHO_REQ (128)
#define _ICMPV6_ECHO_REPLY (129)
#define _ICMPV6_GRP_QUE  (130)
#define _ICMPV6_GRP_REP  (131)
#define _ICMPV6_GRP_TERM (132)
#define _ICMPV6_RTR_SOL  (133)
#define _ICMPV6_RTR_ADV  (134)
#define _ICMPV6_NBR_SOL  (135)
#define _ICMPV6_NBR_ADV  (136)

/* ICMP frag for transmit */
#define _ICMPV6_SND_ERP  0x0001
#define _ICMPV6_SND_RTS  0x0002
#define _ICMPV6_SND_RTA  0x0004
#define _ICMPV6_SND_NBS  0x0008
#define _ICMPV6_SND_NBA  0x0010
#define _ICMPV6_SND_5  0x0020
#define _ICMPV6_SND_6  0x0040
#define _ICMPV6_SND_7  0x0080
#define _ICMPV6_SND_8  0x0100


/* multicast address */
#define _IP_TYPE_NON_MULTI   0
#define _IP_TYPE_MULTI_RESERVED  1
#define _IP_TYPE_MULTI_ALL_HOST  2
#define _IP_TYPE_MULTI_ANY   3
#define _IP_TYPE_MULTI_ALL_RTR  4

/* broadcast address */
#define _IP_TYPE_NON_BROAD   0
#define _IP_TYPE_BROADCAST   1
#define _IP_TYPE_DIRECTED_BROADCAST 2

/* address cache status */
#define _IS_FREE  0x00
#define _IS_INCOMPLETE 0x01
#define _IS_REACHABLE 0x02
#define _IS_STALE  0x04
#define _IS_DELAY  0x08
#define _IS_PROBE  0x10
#define _IS_TMOUT  0x20

#define _ICMP_MAX_MULTICAST_SOLICIT  2
#define _ICMP_MAX_UNICAST_SOLICIT  2
#define _ICMP_REACHABLE_TIME   (30*100)
#define _ICMP_RETRANS_TIMER    (1*100)
#define _ICMP_DELAY_FIRST_PROBE_TIME (5*100)

typedef struct
{
    uchar  ip_ver_len;
    uchar  ip_tos;
    uint16  ip_total_len;
    uint16  ip_id;
    uint16  ip_fragoff;
    uchar  ip_ttl;
    uchar  ip_proto_num;
    uint16  ip_chksum;
    IPaddr  ip_src;
    IPaddr  ip_dst;
} _IP_HDR;

typedef struct
{
    _IP_HDR  iph;   /* IP header */
    uchar  data[1];  /* DATA (upper protocol)*/
} _IP_PKT;


typedef struct
{
    uint32  rsvd;
    uchar  tgt_ip[16];
    uchar  opt_type;
    uchar  opt_len;
    uchar  opt[6];
} _ICMP_NBR_PKT;

typedef struct
{
    uint32  rsvd;
    uchar  opt_type;
    uchar  opt_len;
    uchar  opt[6];
} _ICMP_RTR_SOL_PKT;

typedef struct
{
    uchar  type;
    uchar  len;
    uchar  px_len;
    uchar  rsvd;
    uint32  valid_lt;
    uint32  pref_lt;
    uint32  rsvd2;
    uchar  prefix[16];
} _ICMP_OPT_PFX;

typedef struct
{
    uchar  hop_limit;
    uchar  flag;
    uint16  ef_time;
    uint32  reachable_time;
    uint32  reachable_rtx_timer; // 12
    uchar  opt_type;
    uchar  opt_len;
    uchar  opt[6];
    _ICMP_OPT_PFX pfx_opt;
} _ICMP_RTR_ADV_PKT;

typedef struct
{
    uint16 id;     /* message id */
    uint16 seq;    /* sequence number */
} _ICMP_ECHO_PKT;


typedef struct _icmp_hdr
{
    uchar type;    /* type of message */
    uchar code;    /* code (additional info. depend on type) */
    uint16 chksum;    /* checksum of ICMP header+data   */
    uint16 id;     /* message id */
    uint16 seq;    /* sequence number */
} _ICMP_HDR;

typedef struct
{
    _ICMP_HDR icmph;
    uchar  data[1];
} _ICMP_PKT;

/* Channel information  for v.2.00 */
typedef struct _channel_info
{
    uint8_t  _ch_num;
    _P_RCV_BUF _p_rcv_buf;
    uint32_t _myipaddr[1];
    uint16_t _ip_id;
    uint16_t _rcvd;
    uint16_t flag;
#if defined(_ETHER)
    uint32_t _mymaskaddr[1];
    uint32_t _mygwaddr[1];
    uint8_t  arp_buff[28];
#endif
} _CH_INFO;

extern _CH_INFO *_ch_info_tbl;
extern _CH_INFO *_ch_info_head;


sint16 _ip_rcv_hdr(void);
sint16 _ip_snd(uchar *data, uint16 len) ;
#if defined(_ETHER)
void _ip_icmp_init_tbl(void);
void _ip_icmp_update_tbl(void);
void _ip_icmp_clear_tbl(_ARP_ENTRY *ae);
_ARP_ENTRY *_ip_search_tbl(void);
#endif
void _ip_snd_icmp(void);
uint16 _cksum(uchar *data, uint16 nbytes, uint16 sum0);
#if defined(M16C) || defined(R8C)   /* assembler */
#pragma PARAMETER _cksum(a0, r0, r1);
#elif defined(M16C80) || defined(M32C80) /* assembler */
#pragma PARAMETER /C _cksum(a0, r0, r1);
#endif
schar _ip_check_ipadd_proto(_IP_HDR *piph);
uchar _ip_check_multicast(uchar *ipaddr);
uchar _ip_check_broadcast(uchar *ipaddr);
sint16 _ppp_snd_ip(uchar *data, uint16 len);

void dump_ip_header(const _IP_HDR *p);

#endif


