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
* Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : dhcp.h
* Version      : 1.00
* Description  : dhcp client function header
* Website      : https://www.renesas.com/mw/t4
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.11.2016 1.00    First Release
***********************************************************************************************************************/

/* Guards against multiple inclusion */
#ifndef DHCP_H

/***********************************************************************************************************************
Includes <System Includes> , “Project Includes”
***********************************************************************************************************************/
#include "t4define.h"
#include "r_t4_itcpip.h"
#include "t4define.h"
#include "type.h"
#include "ether.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"

#define DHCP_H

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define DHCP_HEAD_OP_BOOTREQUEST                    (1u)
#define DHCP_HEAD_OP_BOOTREPLY                      (2u)
#define DHCP_HEAD_HTYPE_TYPE_ETHER_10MB             (1u)
#define DHCP_HEAD_HLEN_TYPE_ETHER_10MB              (6u)
#define DHCP_HEAD_HOPS_INITIAL_CLIENT_ZERO_SET      (0u)

#define DHCP_STATE_INITIAL                          (0u)
#define DHCP_STATE_INIT                             (1u)
#define DHCP_STATE_DISCOVER_WAIT                    (2u)
#define DHCP_STATE_SELECTING                        (3u)
#define DHCP_STATE_REQUESTING_WAIT                  (4u)
#define DHCP_STATE_REQUESTING                       (5u)
#define DHCP_STATE_IPREPLYARP                       (6u)
#define DHCP_STATE_BOUND                            (7u)
#define DHCP_STATE_RENEWING                         (8u)
#define DHCP_STATE_RENEWING_WAIT                    (9u)
#define DHCP_STATE_APIPA                            (10u)
#define DHCP_STATE_INFINITY                         (11u)
#define DHCP_STATE_INIT_REBOOT                      (12u)
#define DHCP_STATE_INIT_REBOOT_WAIT                 (13u)
#define DHCP_STATE_REBOOTING                        (14u)
#define DHCP_STATE_DECLINE                          (15u)
#define DHCP_STATE_DECLINE_WAIT                     (16u)

#define DHCP_EVENT_LINK_ON                          (1<<0u)
#define DHCP_EVENT_LEASE_OVER                       (1<<1u)
#define DHCP_EVENT_IP_COLLISION                     (1<<2u)
#define DHCP_EVENT_SND_FIN_CB                       (1<<3u)
#define DHCP_EVENT_SND_FIN_CB_TIMEOUT               (1<<4u)
#define DHCP_EVENT_NAK_RECEIVE                      (1<<5u)
#define DHCP_EVENT_ACK_RECEIVE                      (1<<6u)
#define DHCP_EVENT_LESTTIME_HALF_OVER               (1<<7u)
#define DHCP_EVENT_RESEND_TIMER                     (1<<8u)
#define DHCP_EVENT_RESEND_TIME_OVER                 (1<<9u)
#define DHCP_EVENT_OFFER_RECEIVE                    (1<<10u)

#define DHCP_PKTFLD_CLIENTHARDADDR                  (16u)
#define DHCP_PKTFLD_SERVERNAME                      (64u)
#define DHCP_PKTFLD_BOOTFILENAME                    (128u)
#define DHCP_PKTFLD_MINIMUMOPTION                   (312u)
#define DHCP_PKTFLD_MAX_MSG_SIZE                    (312u)
#define DHCP_PKTFLD_MAGIC_COOKIE_LEN                (4u)
#define DHCP_PKTFLD_MAGIC_COOKIE                    (0x63825363u)

#define DHCP_OPT_PAD                                (0u)
#define DHCP_OPT_END                                (255u)
#define DHCP_OPT_SUBNET_MASK                        (1u)
#define DHCP_OPT_ROUTER_OPTION                      (3u)
#define DHCP_OPT_DOMAIN_NAME_SERVER_OPTION          (6u)
#define DHCP_OPT_DOMAIN_NAME                        (15u)
#define DHCP_OPT_MAX_DATAGRAM_REASSEMBLY_SIZE       (22u)
#define DHCP_OPT_REQUESTED_IP_ADDRESS               (50u)
#define DHCP_OPT_IP_ADDRESS_LEASE_TIME              (51u)
#define DHCP_OPT_DHCP_MESSAGE_TYPE                  (53u)
#define DHCP_OPT_SERVER_IDENTIFIER                  (54u)
#define DHCP_OPT_PARAMETER_REQUEST_LIST             (55u)
#define DHCP_OPT_MESSAGE                            (56u)
#define DHCP_OPT_MAXIMUM_DHCP_MESSAGE_SIZE          (57u)
#define DHCP_OPT_RENEWAL_T1_TIME_VALUE              (58u)
#define DHCP_OPT_CLIENT_IDENTIFIER                  (61u)

#define DHCP_DATLEN_1B                              (1u)
#define DHCP_DATLEN_2B                              (2u)
#define DHCP_DATLEN_3B                              (3u)
#define DHCP_DATLEN_4B                              (4u)

#define DHCP_CMD_DISCOVER                           (1u)
#define DHCP_CMD_OFFER                              (2u)
#define DHCP_CMD_REQUEST                            (3u)
#define DHCP_CMD_DECLINE                            (4u)
#define DHCP_CMD_ACK                                (5u)
#define DHCP_CMD_NAK                                (6u)

#define DHCP_T1_DEFAULTUPP                          (1u)
#define DHCP_T1_DEFAULTLOW                          (2u)
#define DHCP_LINK_WAIT                              (100u)
#define DHCP_SEC_ADJ                                (100u)
#define DHCP_10SEC_WAIT                             (10*DHCP_SEC_ADJ)
#define DHCP_RE_SND_NOTUSE                          (0u)
#define DHCP_RE_SND_LIMIT                           (64u)
#define DHCP_RE_SND_START                           (4u)
#define DHCP_1MINUTES                               (60u)
#define DHCP_LEASE_INFINITY                         (0xFFFFFFFFu)
#define DHCP_BROADCAST_ADDRESS                      (0xFFFFFFFFu)

#define DHCP_SERVER_PORT                            (67u)
#define DHCP_CLIENT_PORT                            (68u)

#define DHCP_DOMAIN_MAX_LEN                         (253u)

#define DHCP_HL8                                    (8u)
#define DHCP_HS8                                    (8u)
#define DHCP_HL24                                   (24u)
#define DHCP_HL2ND_OCT                              (0x00ff0000u)
#define DHCP_HL3RD_OCT                              (0x0000ff00u)

#define ETHER_FLAG_ON_LINK_ON                       (3)

#define DHCP_EVENT_COUNT                            (11u)
#define DHCP_STATE_COUNT                            (16u)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct _in_addr
{
    union
    {
        struct
        {
            uint8_t     s_b1;
            uint8_t     s_b2;
            uint8_t     s_b3;
            uint8_t     s_b4;
        } S_un_b;
        struct
        {
            uint16_t    s_w1;
            uint16_t    s_w2;
        } S_un_w;
        uint32_t        S_addr;
    }S_un;
} in_addr_t_;

typedef struct
{
    uint8_t     uc_op;
    uint8_t     uc_htype;
    uint8_t     uc_hlen;
    uint8_t     uc_hops;
    uint32_t    ul_xid;
    uint16_t    us_secs;
    uint16_t    us_flags;
    uint32_t    ul_ciaddr;
    uint32_t    ul_yiaddr;
    uint32_t    ul_siaddr;
    uint32_t    ul_giaddr;
    uint8_t     uca16_chaddr[DHCP_PKTFLD_CLIENTHARDADDR];
    uint8_t     uca64_sname[DHCP_PKTFLD_SERVERNAME];
    uint8_t     uca128_file[DHCP_PKTFLD_BOOTFILENAME];
    uint8_t     uca312_options[DHCP_PKTFLD_MINIMUMOPTION];
} dhcp_packet_t;


typedef struct
{
    uint32_t        ul_skiptime;
    uint32_t        ul_state;
    uint32_t        ul_event;
    ID              t_cepid;
    uint32_t        ul_channel;

    dhcp_packet_t   t_dhcp_pkt;
    T_IPV4EP        t_ipv4ep_distaddr;
    uint32_t        ul_option_size;

    uint32_t        ul_xid_mem;
    uint32_t        ul_siaddr;
    uint32_t        ul_giaddr;

    uint32_t        ul_lease_limit_time;
    uint32_t        ul_renew_time;
    uint32_t        ul_lease_time;
    uint32_t        ul_lease_time_10ms;
    uint32_t        ul_re_send_time;
    uint32_t        ul_re_send_time_10ms;
    uint32_t        ul_re_send_cmp;

    DHCP            t_dhcp_param_get_inf;
} dhcp_inf_t;

extern void dhcp_process(void);
extern void dhcp_rcv_dat_int(_UDP_CB *pucb, _UDP_HDR *udph, _TCPUDP_PHDR *ph);
extern ER dhcp_callback_from_ether(UB channel, UW eventid, VP param);
extern void dhcp_int_timer(void);
extern ER dhcp_callback_from_t4(ID cepid, FN fncd , VP p_parblk);

#endif /* DHCP_H */
