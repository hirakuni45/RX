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
* File Name    : dhcp.c
* Version      : 1.00
* Description  : dhcp client function
* Website      : https://www.renesas.com/mw/t4
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.11.2016 1.00    First Release
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes <System Includes> ,
***********************************************************************************************************************/

#ifdef PRINTDEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include "dhcp.h"
#include "r_t4_rx/src/config_tcpudp.h"

static void dhcp_dont_care(dhcp_inf_t* pt_dhcpinf);
static void dhcp_no_operation(dhcp_inf_t* pt_dhcpinf);
static void dhcp_initial(dhcp_inf_t* pt_dhcpinf);
static void dhcp_init(dhcp_inf_t* pt_dhcpinf);
static void dhcp_to_init(dhcp_inf_t* pt_dhcpinf);
/// static void dhcp_to_init_reboot(dhcp_inf_t* pt_dhcpinf);
static void dhcp_terminated(dhcp_inf_t* pt_dhcpinf);
static void dhcp_decline(dhcp_inf_t* pt_dhcpinf);
static void dhcp_init_reboot(dhcp_inf_t* pt_dhcpinf);
/// static void dhcp_to_decline(dhcp_inf_t* pt_dhcpinf);
static void dhcp_to_selecting(dhcp_inf_t* pt_dhcpinf);
static void dhcp_apipa(dhcp_inf_t* pt_dhcpinf);
static void dhcp_renewing(dhcp_inf_t* pt_dhcpinf);
static void dhcp_gratuitousarp(dhcp_inf_t* pt_dhcpinf);
static void dhcp_to_apipa(dhcp_inf_t* pt_dhcpinf);
static void dhcp_to_requesting(dhcp_inf_t* pt_dhcpinf);
static void dhcp_to_bound(dhcp_inf_t* pt_dhcpinf);
static void dhcp_to_renewing(dhcp_inf_t* pt_dhcpinf);
static void dhcp_to_rebooting(dhcp_inf_t* pt_dhcpinf);
static void dhcp_ipreplyarp(dhcp_inf_t* pt_dhcpinf);
static void dhcp_selecting(dhcp_inf_t* pt_dhcpinf);

static void dhcp_send_packet_header_make(dhcp_inf_t* pt_dhcpinf, uint16_t us_secs);
static void dhcp_option_write(dhcp_inf_t* pt_dhcpinf, uint8_t** huc_opt, uint8_t uc_cmd, uint8_t uc_cmd2nd);
static void dhcp_ch_info_head_to_tcpudp_env(dhcp_inf_t* pt_dhcpinf, UB channel);
static uint32_t dhcp_opt_message_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp);
static uint32_t dhcp_opt_serveridentifier_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp);
static uint32_t dhcp_opt_subnetmask_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp);
static uint32_t dhcp_opt_leasetime_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp);
static void dhcp_opt_routeroption_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp);
static void dhcp_opt_dns_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp);
static void dhcp_opt_domainname_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp);
static void dhcp_opt_t1_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp);
static uint8_t* dhcp_option_detect(uint8_t* puc_opt, uint8_t uc_command);
static ER dhcp_process_call_udp_snd_dat(uint8_t *puc_opt, dhcp_inf_t* pt_dhcpinf);
static void dhcp_callback_user(UW eventid, dhcp_inf_t* pt_dhcpinf);
static void dhcp_4_8_16_32_resend_timer(dhcp_inf_t* pt_dhcpinf);
static void dhcp_rest_half_resend_timer(dhcp_inf_t* pt_dhcpinf);
static void dhcp_memcpy_local(void* pv_dst, void* pv_src, size_t size);
static void dhcp_memset_local(void* pv_dst, uint32_t value, size_t size);
/// static void dhcp_memcmp_local(void* pv_dst, void* pv_src, size_t size);
static void dhcp_fatal_error(dhcp_inf_t* pt_dhcpinf);


/***********************************************************************************************************************
* Function Name: dhcp_dont_care
* Description  : dhcp_dont_care
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_dont_care(dhcp_inf_t* pt_dhcpinf)
{
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_no_operation
* Description  : dhcp_no_operation
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_no_operation(dhcp_inf_t* pt_dhcpinf)
{
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_initial
* Description  : dhcp initialize(ip/snm/gw/work clear)
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_initial(dhcp_inf_t* pt_dhcpinf)
{
    uint32_t    ul_channel;

    ul_channel = pt_dhcpinf->ul_channel;
#ifdef PRINTDEBUG
    printf("dhcp_initial()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    _ch_info_head[pt_dhcpinf->ul_channel]._myipaddr[0]   = 0;
    _ch_info_head[pt_dhcpinf->ul_channel]._mymaskaddr[0] = 0;
    _ch_info_head[pt_dhcpinf->ul_channel]._mygwaddr[0]   = 0;
    dhcp_memset_local(pt_dhcpinf, 0, sizeof(dhcp_inf_t));
    dhcp_memcpy_local((pt_dhcpinf->t_dhcp_param_get_inf.macaddr), (_myethaddr[ul_channel]), (EP_ALEN));
    pt_dhcpinf->t_cepid = (ul_channel + (__udpcepn + 1));
    pt_dhcpinf->ul_state = DHCP_STATE_INIT;
    pt_dhcpinf->ul_lease_time = DHCP_LEASE_INFINITY;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
    printf("channel %d cepid = %d\n", ul_channel, pt_dhcpinf->t_cepid);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_init
* Description  : DHCP stae INIT position
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_init(dhcp_inf_t* pt_dhcpinf)
{
    uint8_t*    puc_opt = pt_dhcpinf->t_dhcp_pkt.uca312_options;

    if (1 == (_ch_info_head[pt_dhcpinf->ul_channel].etherlink))
    {
#ifdef PRINTDEBUG
        printf("dhcp_init()\n");
        printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
        pt_dhcpinf->t_ipv4ep_distaddr.ipaddr = DHCP_BROADCAST_ADDRESS;
        pt_dhcpinf->t_ipv4ep_distaddr.portno = DHCP_SERVER_PORT;
        dhcp_memset_local((&(pt_dhcpinf->t_dhcp_pkt)), 0, (sizeof(dhcp_packet_t)));
        /* Top position because it is cast by the pointer is the same, write size is specified in the
        sizeof. No CAST So problem for writing 4 bytes of random numbers to 4 bytes of work. */
        get_random_number((uint8_t*)(&(pt_dhcpinf->ul_xid_mem)), sizeof(pt_dhcpinf->ul_xid_mem));
        dhcp_send_packet_header_make(pt_dhcpinf, 0);
        dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_DHCP_MESSAGE_TYPE, DHCP_CMD_DISCOVER);
        dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_CLIENT_IDENTIFIER, 0);
        dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_PARAMETER_REQUEST_LIST, 0);
        dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_MAXIMUM_DHCP_MESSAGE_SIZE, 0);
        if (E_WBLK == (dhcp_process_call_udp_snd_dat(puc_opt, pt_dhcpinf)))
        {
            dhcp_callback_user(DHCP_EV_INIT, pt_dhcpinf);
            pt_dhcpinf->ul_state = DHCP_STATE_DISCOVER_WAIT;
            if (DHCP_RE_SND_NOTUSE == (pt_dhcpinf->ul_re_send_cmp))
            {
                pt_dhcpinf->ul_re_send_time = 0;
                pt_dhcpinf->ul_re_send_cmp  = DHCP_RE_SND_START;
            }
        }
#ifdef PRINTDEBUG
        printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
        printf("ul_re_send_cmp %d\n", pt_dhcpinf->ul_re_send_cmp);
#endif
    }
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_to_init
* Description  : DHCP state change to INIT
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_to_init(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_to_init()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    _ch_info_head[pt_dhcpinf->ul_channel]._myipaddr[0]   = 0;
    _ch_info_head[pt_dhcpinf->ul_channel]._mymaskaddr[0] = 0;
    _ch_info_head[pt_dhcpinf->ul_channel]._mygwaddr[0]   = 0;
    dhcp_memset_local(&pt_dhcpinf->t_dhcp_param_get_inf, 0, sizeof(DHCP));
    pt_dhcpinf->ul_event |= 0;
    pt_dhcpinf->ul_re_send_cmp  = 0;
    pt_dhcpinf->ul_re_send_time = 0;
    pt_dhcpinf->ul_lease_time   = 0;
    pt_dhcpinf->ul_siaddr       = 0;
    pt_dhcpinf->ul_giaddr       = 0;

    pt_dhcpinf->ul_state = DHCP_STATE_INIT;
    pt_dhcpinf->ul_skiptime = DHCP_10SEC_WAIT;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_terminated
* Description  : IP address is changed situation
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_terminated(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_terminated()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    pt_dhcpinf->ul_state = DHCP_STATE_INFINITY;
    dhcp_callback_user(DHCP_EV_LEASE_OVER, pt_dhcpinf);
    _ch_info_tbl->ip_terminated_flag = 1;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_fatal_error
* Description  : IP address is changed situation
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_fatal_error(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_fatal_error()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    pt_dhcpinf->ul_state = DHCP_STATE_INFINITY;
    dhcp_callback_user(DHCP_EV_FATAL_ERROR, pt_dhcpinf);
    _ch_info_tbl->ip_terminated_flag = 1;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_decline
* Description  : notifies DECLINE to the DHCP server from leased IP address from the DHCP server detect collision
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_decline(dhcp_inf_t* pt_dhcpinf)
{
    uint8_t*    puc_opt = pt_dhcpinf->t_dhcp_pkt.uca312_options;

#ifdef PRINTDEBUG
    printf("dhcp_decline()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    dhcp_memset_local(&(pt_dhcpinf->t_dhcp_pkt), 0, sizeof(dhcp_packet_t));
    pt_dhcpinf->ul_xid_mem++;
    dhcp_send_packet_header_make(pt_dhcpinf, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_DHCP_MESSAGE_TYPE, DHCP_CMD_DECLINE);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_CLIENT_IDENTIFIER, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_SERVER_IDENTIFIER, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_REQUESTED_IP_ADDRESS, 0);
    if (E_WBLK == (dhcp_process_call_udp_snd_dat(puc_opt, pt_dhcpinf)))
    {
        pt_dhcpinf->ul_state = DHCP_STATE_DECLINE_WAIT;
#ifdef PRINTDEBUG
        printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    }
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_init_reboot
* Description  : INIT-REBOOT send
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_init_reboot(dhcp_inf_t* pt_dhcpinf)
{
    uint8_t*    puc_opt = pt_dhcpinf->t_dhcp_pkt.uca312_options;

#ifdef PRINTDEBUG
    printf("dhcp_init_reboot()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    pt_dhcpinf->ul_state = DHCP_STATE_INIT_REBOOT;
    pt_dhcpinf->t_ipv4ep_distaddr.ipaddr = DHCP_BROADCAST_ADDRESS;
    dhcp_memset_local(&(pt_dhcpinf->t_dhcp_pkt), 0, (sizeof(dhcp_packet_t)));
    (pt_dhcpinf->ul_xid_mem)++;
    dhcp_send_packet_header_make(pt_dhcpinf, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_DHCP_MESSAGE_TYPE, DHCP_CMD_REQUEST);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_CLIENT_IDENTIFIER, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_REQUESTED_IP_ADDRESS, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_PARAMETER_REQUEST_LIST, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_MAXIMUM_DHCP_MESSAGE_SIZE, 0);
    if (E_WBLK == (dhcp_process_call_udp_snd_dat(puc_opt, pt_dhcpinf)))
    {
        pt_dhcpinf->ul_state = DHCP_STATE_INIT_REBOOT_WAIT;
        dhcp_callback_user(DHCP_EV_INIT_REBOOT, pt_dhcpinf);
        if ((DHCP_RE_SND_NOTUSE == (pt_dhcpinf->ul_re_send_cmp)) || ((pt_dhcpinf->ul_renew_time) == (pt_dhcpinf->ul_re_send_cmp)))
        {
            pt_dhcpinf->ul_re_send_time  = 0;
            pt_dhcpinf->ul_re_send_cmp   = DHCP_RE_SND_START;
        }
#ifdef PRINTDEBUG
        printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
        printf("ul_re_send_cmp %d\n", pt_dhcpinf->ul_re_send_cmp);
#endif
    }
    return;
}


/***********************************************************************************************************************
* Function Name: dhcp_to_selecting
* Description  : DHCP state change SELECTING
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_to_selecting(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_to_selecting()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    pt_dhcpinf->ul_state = DHCP_STATE_SELECTING;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_apipa
* Description  : APIPA address setting
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_apipa(dhcp_inf_t* pt_dhcpinf)
{
    in_addr_t   ipaddr, mskaddr;
    uint8_t     uc_rnd;

    dhcp_memset_local(&(pt_dhcpinf->t_dhcp_param_get_inf), 0, sizeof(DHCP));
#ifdef PRINTDEBUG
    printf("dhcp_apipa()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    ipaddr.S_un.S_un_b.s_b1 = 169;
    ipaddr.S_un.S_un_b.s_b2 = 254;
    do
    {
        get_random_number(&(uc_rnd), 1);
    }
    while ((uc_rnd < 1) || (254 < uc_rnd));
    ipaddr.S_un.S_un_b.s_b3 = uc_rnd;
    get_random_number(&(ipaddr.S_un.S_un_b.s_b4), 1);

    _ch_info_head[pt_dhcpinf->ul_channel]._myipaddr[0]   = ipaddr.S_un.S_addr;

    mskaddr.S_un.S_un_b.s_b1 = 255;
    mskaddr.S_un.S_un_b.s_b2 = 255;
    mskaddr.S_un.S_un_b.s_b3 = 0;
    mskaddr.S_un.S_un_b.s_b4 = 0;
    _ch_info_head[pt_dhcpinf->ul_channel]._mymaskaddr[0] = mskaddr.S_un.S_addr;

    _ch_info_head[pt_dhcpinf->ul_channel]._mygwaddr[0]   = 0;

    dhcp_ch_info_head_to_tcpudp_env(pt_dhcpinf, pt_dhcpinf->ul_channel);
    ether_snd_gratuitous_arp();
    dhcp_callback_user(DHCP_EV_APIPA, pt_dhcpinf);
    pt_dhcpinf->ul_state = DHCP_STATE_INFINITY;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_renewing
* Description  : RENEWING send
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_renewing(dhcp_inf_t* pt_dhcpinf)
{
    uint8_t*    puc_opt = pt_dhcpinf->t_dhcp_pkt.uca312_options;

#ifdef PRINTDEBUG
    printf("dhcp_renewing()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    pt_dhcpinf->t_ipv4ep_distaddr.ipaddr = hl2net(pt_dhcpinf->ul_siaddr);
    dhcp_memset_local(&(pt_dhcpinf->t_dhcp_pkt), 0, (sizeof(dhcp_packet_t)));
    (pt_dhcpinf->ul_xid_mem)++;
    dhcp_send_packet_header_make(pt_dhcpinf, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_DHCP_MESSAGE_TYPE, DHCP_CMD_REQUEST);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_CLIENT_IDENTIFIER, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_PARAMETER_REQUEST_LIST, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_MAXIMUM_DHCP_MESSAGE_SIZE, 0);
    if (E_WBLK == (dhcp_process_call_udp_snd_dat(puc_opt, pt_dhcpinf)))
    {
        pt_dhcpinf->ul_state = DHCP_STATE_RENEWING_WAIT;
#ifdef PRINTDEBUG
        printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    }
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_to_apipa
* Description  : DHCP state change APIPA
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_to_apipa(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_to_apipa()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    pt_dhcpinf->ul_state = DHCP_STATE_APIPA;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_gratuitousarp
* Description  : gratuitousARP send
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_gratuitousarp(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_gratuitousarp()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    ether_snd_gratuitous_arp();
    pt_dhcpinf->ul_skiptime = (_t4_dhcp_ip_reply_arp_delay);
    pt_dhcpinf->ul_state = DHCP_STATE_IPREPLYARP;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
    printf("skiptime set %d\n", pt_dhcpinf->ul_skiptime);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_to_requesting
* Description  : DHCP state change REQUESTING
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_to_requesting(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_to_requesting()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    pt_dhcpinf->ul_state = DHCP_STATE_REQUESTING;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_to_bound
* Description  : DHCP stae change BOUND
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_to_bound(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_to_bound()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    pt_dhcpinf->ul_state = DHCP_STATE_BOUND;
    dhcp_callback_user(DHCP_EV_LEASE_IP, pt_dhcpinf);

    pt_dhcpinf->ul_renew_time = (pt_dhcpinf->ul_lease_limit_time) - (pt_dhcpinf->ul_lease_time);
    pt_dhcpinf->ul_renew_time *= DHCP_T1_DEFAULTUPP;
    pt_dhcpinf->ul_renew_time /= DHCP_T1_DEFAULTLOW;
    pt_dhcpinf->ul_re_send_cmp = pt_dhcpinf->ul_renew_time;

#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_to_renewing
* Description  : DHCP state change RENEWING
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_to_renewing(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_to_renewing()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    pt_dhcpinf->ul_state = DHCP_STATE_RENEWING;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_to_rebooting
* Description  : DHCP state change REBOOTING
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_to_rebooting(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_to_rebooting\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    pt_dhcpinf->ul_state = DHCP_STATE_REBOOTING;
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_ipreplyarp
* Description  : IP reply ARP send
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_ipreplyarp(dhcp_inf_t* pt_dhcpinf)
{
#ifdef PRINTDEBUG
    printf("dhcp_ipreplyarp\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    ether_snd_ip_reply_arp();
    pt_dhcpinf->ul_state = DHCP_STATE_BOUND;
    dhcp_callback_user(DHCP_EV_LEASE_IP, pt_dhcpinf);
#ifdef PRINTDEBUG
    printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_selecting
* Description  : DHCP state SELECTING send
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_selecting(dhcp_inf_t* pt_dhcpinf)
{
    uint8_t*    puc_opt = pt_dhcpinf->t_dhcp_pkt.uca312_options;

#ifdef PRINTDEBUG
    printf("dhcp_selecting()\n");
    printf("channel %d func E%04X,S%02d->", pt_dhcpinf->ul_channel, pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
    dhcp_memset_local((&(pt_dhcpinf->t_dhcp_pkt)), 0, (sizeof(dhcp_packet_t)));
    dhcp_send_packet_header_make(pt_dhcpinf, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_DHCP_MESSAGE_TYPE, DHCP_CMD_REQUEST);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_CLIENT_IDENTIFIER, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_SERVER_IDENTIFIER, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_REQUESTED_IP_ADDRESS, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_PARAMETER_REQUEST_LIST, 0);
    dhcp_option_write(pt_dhcpinf, &puc_opt, DHCP_OPT_MAXIMUM_DHCP_MESSAGE_SIZE, 0);
    if (E_WBLK == (dhcp_process_call_udp_snd_dat(puc_opt, pt_dhcpinf)))
    {
        pt_dhcpinf->ul_state = DHCP_STATE_REQUESTING_WAIT;
        if (DHCP_RE_SND_NOTUSE == (pt_dhcpinf->ul_re_send_cmp))
        {
            pt_dhcpinf->ul_re_send_time  = 0;
            pt_dhcpinf->ul_re_send_cmp   = DHCP_RE_SND_START;
        }
#ifdef PRINTDEBUG
        printf("E%04X,S%02d\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
        printf("ul_re_send_cmp %d\n", pt_dhcpinf->ul_re_send_cmp);
#endif
    }
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_send_packet_header_make
* Description  : dhcp send packet header make
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
*              : uint16_t us_secs
*                    member secs value
* Return Value : none
***********************************************************************************************************************/
static void dhcp_send_packet_header_make(dhcp_inf_t* pt_dhcpinf, uint16_t us_secs)
{
    pt_dhcpinf->t_dhcp_pkt.uc_op     = DHCP_HEAD_OP_BOOTREQUEST;
    pt_dhcpinf->t_dhcp_pkt.uc_htype  = DHCP_HEAD_HTYPE_TYPE_ETHER_10MB;
    pt_dhcpinf->t_dhcp_pkt.uc_hlen   = DHCP_HEAD_HLEN_TYPE_ETHER_10MB;
    pt_dhcpinf->t_dhcp_pkt.uc_hops   = DHCP_HEAD_HOPS_INITIAL_CLIENT_ZERO_SET;
    pt_dhcpinf->t_dhcp_pkt.ul_xid    = hl2net(pt_dhcpinf->ul_xid_mem);
    pt_dhcpinf->t_dhcp_pkt.us_secs   = us_secs;
    pt_dhcpinf->t_dhcp_pkt.ul_giaddr = pt_dhcpinf->ul_giaddr;
    pt_dhcpinf->t_dhcp_pkt.ul_siaddr = pt_dhcpinf->ul_siaddr;

    if (DHCP_STATE_INIT_REBOOT == (pt_dhcpinf->ul_state))
    {
        pt_dhcpinf->t_dhcp_pkt.ul_ciaddr = 0;
        pt_dhcpinf->t_dhcp_pkt.ul_yiaddr = 0;
    }
    else if (DHCP_STATE_BOUND <= (pt_dhcpinf->ul_state))
    {
        dhcp_memcpy_local(&(pt_dhcpinf->t_dhcp_pkt.ul_yiaddr), (pt_dhcpinf->t_dhcp_param_get_inf.ipaddr), IP_ALEN);
        dhcp_memcpy_local(&(pt_dhcpinf->t_dhcp_pkt.ul_ciaddr), (pt_dhcpinf->t_dhcp_param_get_inf.ipaddr), IP_ALEN);
    }
    else
    {
        /* Do Nothing */
    }
    dhcp_memcpy_local((pt_dhcpinf->t_dhcp_pkt.uca16_chaddr), (_myethaddr[(pt_dhcpinf->ul_channel)]), (EP_ALEN));
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_option_write
* Description  : dhcp option write process
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
*              : uint8_t** huc_opt
*                    handle option
*              : uint8_t uc_cmd
*                    1st command
*              : uint8_t uc_cmd2nd
*                    2nd command
* Return Value : none
***********************************************************************************************************************/
static void dhcp_option_write(dhcp_inf_t* pt_dhcpinf, uint8_t** huc_opt, uint8_t uc_cmd, uint8_t uc_cmd2nd)
{
    uint32_t    ul_work;
    uint16_t    us_size;
    uint8_t*    puc_opt = *huc_opt;

    if ((puc_opt) == (pt_dhcpinf->t_dhcp_pkt.uca312_options))
    {
        ul_work = hl2net(DHCP_PKTFLD_MAGIC_COOKIE);
        dhcp_memcpy_local((puc_opt), (&ul_work), (IP_ALEN));
        (puc_opt) += IP_ALEN;
    }
    switch (uc_cmd)
    {
        case DHCP_OPT_DHCP_MESSAGE_TYPE:
            (*puc_opt) = DHCP_OPT_DHCP_MESSAGE_TYPE;
            puc_opt++;
            (*puc_opt) = DHCP_DATLEN_1B;
            puc_opt++;
            (*puc_opt) = uc_cmd2nd;
            puc_opt++;
            break;

        case DHCP_OPT_CLIENT_IDENTIFIER:
            (*puc_opt) = DHCP_OPT_CLIENT_IDENTIFIER;
            puc_opt++;
            (*puc_opt) = (DHCP_DATLEN_1B + DHCP_HEAD_HLEN_TYPE_ETHER_10MB);
            puc_opt++;
            (*puc_opt) = DHCP_HEAD_HTYPE_TYPE_ETHER_10MB;
            puc_opt++;
            dhcp_memcpy_local((puc_opt), (_myethaddr[pt_dhcpinf->ul_channel]), (EP_ALEN));
            (puc_opt) += EP_ALEN;
            break;

        case DHCP_OPT_REQUESTED_IP_ADDRESS:
            (*puc_opt) = DHCP_OPT_REQUESTED_IP_ADDRESS;
            puc_opt++;
            (*puc_opt) = DHCP_DATLEN_4B;
            puc_opt++;
            dhcp_memcpy_local(&ul_work, (pt_dhcpinf->t_dhcp_param_get_inf.ipaddr), IP_ALEN);
            dhcp_memcpy_local(puc_opt, &ul_work, IP_ALEN);
            (puc_opt) += IP_ALEN;
            break;

        case DHCP_OPT_SERVER_IDENTIFIER:
            (*puc_opt) = DHCP_OPT_SERVER_IDENTIFIER;
            puc_opt++;
            (*puc_opt) = DHCP_DATLEN_4B;
            puc_opt++;
            ul_work = pt_dhcpinf->ul_siaddr;
            dhcp_memcpy_local((puc_opt), (&ul_work), (IP_ALEN));
            (puc_opt) += IP_ALEN;
            break;

        case DHCP_OPT_PARAMETER_REQUEST_LIST:
            (*puc_opt) = DHCP_OPT_PARAMETER_REQUEST_LIST;
            puc_opt++;
            (*puc_opt) = DHCP_DATLEN_4B;
            puc_opt++;
            (*puc_opt) = DHCP_OPT_SUBNET_MASK;
            puc_opt++;
            (*puc_opt) = DHCP_OPT_DOMAIN_NAME;
            puc_opt++;
            (*puc_opt) = DHCP_OPT_DOMAIN_NAME_SERVER_OPTION;
            puc_opt++;
            (*puc_opt) = DHCP_OPT_ROUTER_OPTION;
            puc_opt++;
            break;

        case DHCP_OPT_MAXIMUM_DHCP_MESSAGE_SIZE:
            (*puc_opt) = DHCP_OPT_MAXIMUM_DHCP_MESSAGE_SIZE;
            puc_opt++;
            (*puc_opt) = DHCP_DATLEN_2B;
            puc_opt++;
            us_size = hs2net(DHCP_PKTFLD_MAX_MSG_SIZE);
            dhcp_memcpy_local((puc_opt), (&us_size), (sizeof(us_size)));
            (puc_opt) += (sizeof(us_size));
            break;

        default:
            break;
    }
    (*huc_opt) = puc_opt;
    return;
}

/***********************************************************************************************************************
* Function Name: ch_info_head_to_tcpudp_env
* Description  : copy ip/subnetmask/gateway
* Arguments    : dhcp_inf_t* pt_dhcpinf
*              :     pointer dhcp information
*              : UB channel
*              :     I/F
* Return Value : none
***********************************************************************************************************************/
static void dhcp_ch_info_head_to_tcpudp_env(dhcp_inf_t* pt_dhcpinf, UB channel)
{
    dhcp_memcpy_local((tcpudp_env[channel].ipaddr),   (_ch_info_head[channel]._myipaddr),   (IP_ALEN));
    dhcp_memcpy_local((tcpudp_env[channel].maskaddr), (_ch_info_head[channel]._mymaskaddr), (IP_ALEN));
    dhcp_memcpy_local((tcpudp_env[channel].gwaddr),   (_ch_info_head[channel]._mygwaddr),   (IP_ALEN));

    dhcp_memcpy_local((pt_dhcpinf->t_dhcp_param_get_inf.ipaddr),   (_ch_info_head[channel]._myipaddr),   (IP_ALEN));
    dhcp_memcpy_local((pt_dhcpinf->t_dhcp_param_get_inf.maskaddr), (_ch_info_head[channel]._mymaskaddr), (IP_ALEN));
    dhcp_memcpy_local((pt_dhcpinf->t_dhcp_param_get_inf.gwaddr),   (_ch_info_head[channel]._mygwaddr),   (IP_ALEN));

    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_rcv_dat_int
* Description  : dhcp receive data interrupt from T4 system
* Arguments    : _UDP_CB *pucb
*                    udp callback pointer
*              : _UDP_HDR *udph
*                    udp header pointer
*              : _TCPUDP_PHDR *ph
*                    tcpudp header pointer
* Return Value : none
***********************************************************************************************************************/
void dhcp_rcv_dat_int(_UDP_CB *pucb, _UDP_HDR *udph, _TCPUDP_PHDR *ph)
{
    _UDP_PKT*       pudp;
    dhcp_packet_t*  pt_dhcp;
    dhcp_inf_t*     pt_dhcpinf;
    uint32_t        ul_message;
    uint32_t        ul_svident;
    uint32_t        ul_subnet;
    uint32_t        ul_lease;
    uint32_t        ul_judge;
    uint8_t*        puc_res;

    /* You will be able to accelerator to easily member data by type-casting in the structure */
    pudp = (_UDP_PKT*)udph;
    /* Cast for the type extraction */
    pt_dhcp = (dhcp_packet_t*)pudp->data;
    pt_dhcpinf = _ch_info_tbl->pt_dhcp_inf;

    if ((DHCP_HEAD_OP_BOOTREPLY != (pt_dhcp->uc_op)) || ((hl2net(pt_dhcpinf->ul_xid_mem)) != (pt_dhcp->ul_xid)))
    {
        /* Do Nothing */
    }
    else
    {
        ul_message = (dhcp_opt_message_check(pt_dhcpinf, pt_dhcp));
        ul_svident = (dhcp_opt_serveridentifier_check(pt_dhcpinf, pt_dhcp));
        ul_subnet  = (dhcp_opt_subnetmask_check(pt_dhcpinf, pt_dhcp));
        ul_lease   = (dhcp_opt_leasetime_check(pt_dhcpinf, pt_dhcp));
        ul_judge = ((ul_message * ul_svident) * (ul_subnet * ul_lease));
        puc_res = dhcp_option_detect((pt_dhcp->uca312_options), DHCP_OPT_DHCP_MESSAGE_TYPE);
        if (FALSE != ul_judge)
        {
            dhcp_opt_routeroption_check(pt_dhcpinf, pt_dhcp);
            dhcp_opt_dns_check(pt_dhcpinf, pt_dhcp);
            dhcp_opt_domainname_check(pt_dhcpinf, pt_dhcp);
            dhcp_opt_t1_check(pt_dhcpinf, pt_dhcp);

            *(_ch_info_tbl->_myipaddr) = pt_dhcp->ul_yiaddr;
            dhcp_ch_info_head_to_tcpudp_env(pt_dhcpinf, pt_dhcpinf->ul_channel);

            pt_dhcpinf->ul_event |= DHCP_EVENT_ACK_RECEIVE;
            pt_dhcpinf->ul_re_send_cmp = pt_dhcpinf->ul_renew_time;
            pt_dhcpinf->ul_re_send_time = 0;
            pt_dhcpinf->ul_lease_time   = 0;
#ifdef PRINTDEBUG
            printf("DHCP_EVENT_ACK_RECEIVE\n");
            printf("time parameter all clear\n");
            printf("ul_re_send_cmp = %d\n", pt_dhcpinf->ul_re_send_cmp);
            printf("ul_re_send_time= %d\n", pt_dhcpinf->ul_re_send_time);
            printf("ul_lease_time  = %d\n", pt_dhcpinf->ul_lease_time);
#endif
        }
        else if (((((void*)0) != puc_res) && (DHCP_CMD_OFFER == (*(puc_res + 2)))) && (0 == (pt_dhcpinf->ul_siaddr)))
        {
            puc_res = (dhcp_option_detect((pt_dhcp->uca312_options), DHCP_OPT_SERVER_IDENTIFIER));
            /* NULL pointer */
            if (((void*)0) != puc_res)
            {
                dhcp_memcpy_local((pt_dhcpinf->t_dhcp_param_get_inf.ipaddr), &(pt_dhcp->ul_yiaddr), IP_ALEN);
                dhcp_memcpy_local(&(pt_dhcpinf->ul_siaddr), (puc_res + 2), IP_ALEN);
#ifdef PRINTDEBUG
                printf("DHCP server ip address %03d.%03d.%03d.%03d\n",
                       *(puc_res + 2), *(puc_res + 3), *(puc_res + 4), *(puc_res + 5));
#endif
                pt_dhcpinf->ul_re_send_cmp = DHCP_RE_SND_NOTUSE;
                pt_dhcpinf->ul_event      |= DHCP_EVENT_OFFER_RECEIVE;
#ifdef PRINTDEBUG
                printf("ul_re_send_cmp %d\n", pt_dhcpinf->ul_re_send_cmp);
                printf("DHCP_EVENT_OFFER_RECEIVE\n");
#endif
            }
        }
        else
        {
            /* Do Nothing */
        }
    }

    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_opt_message_check
* Description  : receive dhcp packet option message check
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
*              : dhcp_packet_t* pt_dhcp
*                    pointer to dhcp packet
* Return Value : TRUE
*                    ACK receive
*                FALSE
*                    ACK not receive
***********************************************************************************************************************/
static uint32_t dhcp_opt_message_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp)
{
    uint32_t    ul_res;
    uint8_t*    puc_res;

#ifdef PRINTDEBUG
    printf("message check is ");
#endif
    puc_res = dhcp_option_detect((pt_dhcp->uca312_options), DHCP_OPT_DHCP_MESSAGE_TYPE);
    if (((void*)0) == puc_res)
    {
        ul_res = FALSE;
#ifdef PRINTDEBUG
        printf("not message\n");
#endif
    }
    else
    {
        if (DHCP_CMD_NAK == (*(puc_res + 2)))
        {
            ul_res = FALSE;
            dhcp_callback_user(DHCP_EV_NAK, pt_dhcpinf);
            pt_dhcpinf->ul_event |= DHCP_EVENT_NAK_RECEIVE;
#ifdef PRINTDEBUG
            printf("NAK\n");
#endif
        }
        else if (DHCP_CMD_ACK == (*(puc_res + 2)))
        {
            ul_res = TRUE;
#ifdef PRINTDEBUG
            printf("ACK\n");
#endif
        }
        else
        {
            ul_res = FALSE;
#ifdef PRINTDEBUG
            printf("other %d\n", *(puc_res + 2));
#endif
        }
    }
    return ul_res;
}

/***********************************************************************************************************************
* Function Name: dhcp_opt_serveridentifier_check
* Description  : receive dhcp packet option serveridentifier check
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
*              : dhcp_packet_t* pt_dhcp
*                    pointer to dhcp packet
* Return Value : TRUE
*                    server identifier same memory
*                FALSE
*                    illegal
***********************************************************************************************************************/
static uint32_t dhcp_opt_serveridentifier_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp)
{
    uint32_t    ul_res;
    uint8_t*    puc_res;

#ifdef PRINTDEBUG
    printf("server identifier is ");
#endif
    puc_res = dhcp_option_detect((pt_dhcp->uca312_options), DHCP_OPT_SERVER_IDENTIFIER);
    if (((void*)0) == puc_res)
    {
        ul_res = FALSE;
#ifdef PRINTDEBUG
        printf("false:option nothing\n");
#endif
    }
    else
    {
        if (0 != memcmp(&(pt_dhcpinf->ul_siaddr), (puc_res + 2), IP_ALEN))
        {
#ifdef PRINTDEBUG
            printf("\nsvidentifier address %08x\n", pt_dhcpinf->ul_siaddr);
            printf("dhcp packet  address %08x\n", *((uint32_t*)(puc_res + 2)));
#endif
            ul_res = FALSE;
#ifdef PRINTDEBUG
            printf("false:not same address\n");
#endif
        }
        else
        {
            ul_res = TRUE;
#ifdef PRINTDEBUG
            printf("true\n");
#endif
        }
    }

    return ul_res;
}

/***********************************************************************************************************************
* Function Name: dhcp_opt_subnetmask_check
* Description  : receive dhcp packet option subnetmask check
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
*              : dhcp_packet_t* pt_dhcp
*                    pointer to dhcp packet
* Return Value : TRUE
*                    hit search
*                FALSE
*                    not search
***********************************************************************************************************************/
static uint32_t dhcp_opt_subnetmask_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp)
{
    uint32_t    ul_res;
    uint8_t*    puc_res;
    void*       pv_ptr;

#ifdef PRINTDEBUG
    printf("subnetmask is ");
#endif
    puc_res = dhcp_option_detect((pt_dhcp->uca312_options), DHCP_OPT_SUBNET_MASK);
    /* NULL pointer */
    if (((void*)0) != puc_res)
    {
        ul_res = TRUE;
        puc_res += 2;
        pv_ptr = puc_res;
        dhcp_memcpy_local((_ch_info_tbl->_mymaskaddr), pv_ptr, IP_ALEN);
        puc_res += IP_ALEN;
#ifdef PRINTDEBUG
        printf("true\n");
#endif
    }
    else
    {
        ul_res = FALSE;
#ifdef PRINTDEBUG
        printf("false\n");
#endif
    }

    return ul_res;
}

/***********************************************************************************************************************
* Function Name: dhcp_opt_leasetime_check
* Description  : receive dhcp packet option lease time check
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
*              : dhcp_packet_t* pt_dhcp
*                    pointer to dhcp packet
* Return Value : TRUE
*                    hit search
*                FALSE
*                    not search
***********************************************************************************************************************/
static uint32_t dhcp_opt_leasetime_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp)
{
    uint32_t    ul_res;
    uint8_t*    puc_res;
    void*       pv_ptr;

#ifdef PRINTDEBUG
    printf("leasetime is ");
#endif
    puc_res = dhcp_option_detect((pt_dhcp->uca312_options), DHCP_OPT_IP_ADDRESS_LEASE_TIME);
    /* NULL pointer */
    if (((void*)0) != puc_res)
    {
        ul_res = TRUE;
        pv_ptr = (puc_res + 2);
        /* Lease limit time information is 4 bytes length of the length of the data to be retrieved */
        pt_dhcpinf->ul_lease_limit_time = net2hl(*((uint32_t*)pv_ptr));
#ifdef PRINTDEBUG
        printf("true\n");
#endif
    }
    else
    {
        ul_res = FALSE;
#ifdef PRINTDEBUG
        printf("false\n");
#endif
    }
    return ul_res;
}

/***********************************************************************************************************************
* Function Name: dhcp_opt_routeroption_check
* Description  : receive dhcp packet option router option check
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
*              : dhcp_packet_t* pt_dhcp
*                    pointer to dhcp packet
* Return Value : none
***********************************************************************************************************************/
static void dhcp_opt_routeroption_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp)
{
    uint8_t*    puc_res;
    void*       pv_ptr;

#ifdef PRINTDEBUG
    printf("dhcp_opt_routeroption_check()\n");
    printf("_mygwaddr %08lX -> ", *(uint32_t*)(_ch_info_tbl->_mygwaddr));
#endif
    puc_res = (dhcp_option_detect((pt_dhcp->uca312_options), DHCP_OPT_ROUTER_OPTION));
    /* NULL pointer */
    if (((void*)0) != puc_res)
    {
        puc_res += 2;
        pv_ptr = puc_res;
        dhcp_memcpy_local((_ch_info_tbl->_mygwaddr), pv_ptr, IP_ALEN);
#ifdef PRINTDEBUG
        printf("option hit(%lx)\n", *(uint32_t*)pv_ptr);
        printf("%08lX\n", *(uint32_t*)(_ch_info_tbl->_mygwaddr));
#endif
        puc_res += IP_ALEN;
    }
    else
    {
#ifdef PRINTDEBUG
        printf("option nothing\n");
        printf("%08lX\n", *(uint32_t*)(_ch_info_tbl->_mygwaddr));
#endif
    }

    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_opt_dns_check
* Description  : receive dhcp packet option dns check
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
*              : dhcp_packet_t* pt_dhcp
*                    pointer to dhcp packet
* Return Value : none
***********************************************************************************************************************/
static void dhcp_opt_dns_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp)
{
    uint8_t*    puc_res;
    void*       pv_ptr;
    uint32_t    ul_count;

#ifdef PRINTDEBUG
    printf("dhcp_opt_dns_check()\n");
    printf("DHCP.dnsaddr %08lX -> ", *(uint32_t*)(pt_dhcpinf->t_dhcp_param_get_inf.dnsaddr));
#endif
    puc_res = dhcp_option_detect((pt_dhcp->uca312_options), DHCP_OPT_DOMAIN_NAME_SERVER_OPTION);
    if (((void*)0) != puc_res)
    {
#ifdef PRINTDEBUG
        printf("option hit\n");
#endif
        puc_res++;
        ul_count = (*puc_res);
#ifdef PRINTDEBUG
        printf("data count(%d)\n", (*puc_res));
#endif
        ul_count++;
        ul_count /= IP_ALEN;
        if (ul_count > 2)
        {
            ul_count = 2;
        }
        puc_res++;
        pv_ptr = puc_res;
        dhcp_memcpy_local((pt_dhcpinf->t_dhcp_param_get_inf.dnsaddr), pv_ptr, IP_ALEN);
#ifdef PRINTDEBUG
        printf("address1(%lx)\n", *(uint32_t*)pv_ptr);
        printf("%08lX\n", *(uint32_t*)(pt_dhcpinf->t_dhcp_param_get_inf.dnsaddr));
#endif
        puc_res += IP_ALEN;
        if (2 == ul_count)
        {
            pv_ptr = puc_res;
            dhcp_memcpy_local((pt_dhcpinf->t_dhcp_param_get_inf.dnsaddr2), pv_ptr, IP_ALEN);
#ifdef PRINTDEBUG
            printf("address2(%lx)\n", *(uint32_t*)pv_ptr);
            printf("%08lX\n", *(uint32_t*)(pt_dhcpinf->t_dhcp_param_get_inf.dnsaddr));
#endif
            puc_res += IP_ALEN;
        }
    }
    else
    {
#ifdef PRINTDEBUG
        printf("option nothing\n");
#endif
    }

    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_opt_domainname_check
* Description  : receive dhcp packet option domain name check
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
*              : dhcp_packet_t* pt_dhcp
*                    pointer to dhcp packet
* Return Value : none
***********************************************************************************************************************/
static void dhcp_opt_domainname_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp)
{
    uint8_t*    puc_res;
    uint32_t    ul_count;

#ifdef PRINTDEBUG
    printf("dhcp_opt_domainname_check()\n");
#endif
    puc_res = dhcp_option_detect((pt_dhcp->uca312_options), DHCP_OPT_DOMAIN_NAME);
    if (((void*)0) != puc_res)
    {
#ifdef PRINTDEBUG
        printf("option hit\n");
#endif
        dhcp_memset_local((pt_dhcpinf->t_dhcp_param_get_inf.domain), 0, (DHCP_DOMAIN_MAX_LEN + 1));
        puc_res++;
        ul_count = (*puc_res);
        puc_res++;
        if (DHCP_DOMAIN_MAX_LEN < ul_count)
        {
            ul_count = DHCP_DOMAIN_MAX_LEN;
        }
        dhcp_memcpy_local((pt_dhcpinf->t_dhcp_param_get_inf.domain), puc_res, ul_count);
        puc_res += ul_count;
    }
    else
    {
#ifdef PRINTDEBUG
        printf("option nothing\n");
#endif
    }

    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_opt_t1_check
* Description  : receive dhcp packet option T1 check
* Arguments    : dhcp_inf_t* pt_dhcpinf
*                    pointer dhcp information
*              : dhcp_packet_t* pt_dhcp
*                    pointer to dhcp packet
* Return Value : none
***********************************************************************************************************************/
static void dhcp_opt_t1_check(dhcp_inf_t* pt_dhcpinf, dhcp_packet_t* pt_dhcp)
{
    uint8_t*    puc_res;
    void*       pv_ptr;

#ifdef PRINTDEBUG
    printf("dhcp_opt_t1_check()\n");
#endif
    puc_res = dhcp_option_detect((pt_dhcp->uca312_options), DHCP_OPT_RENEWAL_T1_TIME_VALUE);
    /* NULL pointer */
    if (((void*)0) != puc_res)
    {
        pv_ptr = (puc_res + 2);
        /* Lease time information is 4 bytes length of the length of the data to be retrieved */
        pt_dhcpinf->ul_renew_time = net2hl(*((uint32_t*)pv_ptr));
#ifdef PRINTDEBUG
        printf("option hit(%ld)\n", pt_dhcpinf->ul_renew_time);
#endif
    }
    else
    {
        pt_dhcpinf->ul_renew_time = pt_dhcpinf->ul_lease_limit_time;
        pt_dhcpinf->ul_renew_time *= DHCP_T1_DEFAULTUPP;
        pt_dhcpinf->ul_renew_time /= DHCP_T1_DEFAULTLOW;
#ifdef PRINTDEBUG
        printf("option no hit. make t1(%ld)\n", pt_dhcpinf->ul_renew_time);
#endif
    }
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_option_detect
* Description  : dhcp option detect
* Arguments    : uint8_t* puc_opt
*                    pointer to option area
*              : uint8_t uc_command
*                    search command number
* Return Value : uint8_t*
*                    pointer to target option area
*                zero
*                    fail
***********************************************************************************************************************/
static uint8_t* dhcp_option_detect(uint8_t* puc_opt, uint8_t uc_command)
{
    uint8_t*    puc_res = puc_opt;
    uint32_t    ul_fin = 0;
    uint32_t    ul_magic_cookie;
    uint32_t    ul_rest_size;

#ifdef PRINTDEBUG
    printf("dhcp_optoin_detect()\n");
#endif
    dhcp_memcpy_local(&(ul_magic_cookie), puc_opt, DHCP_PKTFLD_MAGIC_COOKIE_LEN);
    if (DHCP_PKTFLD_MAGIC_COOKIE == (net2hl(ul_magic_cookie)))
    {
        puc_res += DHCP_PKTFLD_MAGIC_COOKIE_LEN;
        do
        {
            while (DHCP_OPT_PAD == (*puc_res))
            {
#ifdef PRINTDEBUG
                printf(".(%d).", (*puc_res));
#endif
                puc_res++;
            }
            if (DHCP_OPT_END == (*puc_res))
            {
#ifdef PRINTDEBUG
                printf("terminater detect(%d)\n", (*puc_res));
#endif
                puc_res = ((void*)0);
                ul_fin = 1;
            }
            else if ((*puc_res) == uc_command)
            {
#ifdef PRINTDEBUG
                printf("target detect(%d)\n", (*puc_res));
#endif
                ul_fin = 1;
            }
            else
            {
#ifdef PRINTDEBUG
                printf(".(%d).", (*puc_res));
#endif
                puc_res += (*(puc_res + 1));
                puc_res += 2;
            }
            ul_rest_size = puc_res - puc_opt;
        }
        while ((DHCP_PKTFLD_MINIMUMOPTION > ul_rest_size) && (0 == ul_fin));
    }
    else
    {
        puc_res = (void*)0;
    }

    return puc_res;
}

/***********************************************************************************************************************
* Function Name: dhcp_callbackp_from_ether
* Description  : dhcp_callback process
* Arguments    : UB channel
*                    I/F
*              : UW eventid
*                    event id
*              : VP param
*                    always zero
* Return Value : ER
*                    always zero
***********************************************************************************************************************/
ER dhcp_callback_from_ether(UB channel, UW eventid, VP param)
{
    dhcp_inf_t* pt_dhcpinf = _ch_info_head[channel].pt_dhcp_inf;

    if (ETHER_EV_LINK_ON == eventid)
    {
        pt_dhcpinf->ul_event |= DHCP_EVENT_LINK_ON;
        pt_dhcpinf->ul_skiptime = DHCP_LINK_WAIT;
#ifdef PRINTDEBUG
        printf("ETHER_EV_LINK_ON, set SKIP time(%d)\n", pt_dhcpinf->ul_skiptime);
#endif
    }
    else if (ETHER_EV_LINK_OFF == eventid)
    {
        pt_dhcpinf->ul_event &= (~DHCP_EVENT_LINK_ON);
#ifdef PRINTDEBUG
        printf("ETHER_EV_LINK_OFF\n");
#endif
    }
    else if (ETHER_EV_COLLISION_IP == eventid)
    {
        pt_dhcpinf->ul_event |= DHCP_EVENT_IP_COLLISION;
#ifdef PRINTDEBUG
        printf("ETHER_EV_COLLISION_IP\n");
#endif
    }
    else
    {
        /* Do Nothing */
    }
    return 0;
}

/***********************************************************************************************************************
* Function Name: dhcp_rest_half_resend_timer
* Description  : rest half time
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void dhcp_rest_half_resend_timer(dhcp_inf_t* pt_dhcpinf)
{
    if ((pt_dhcpinf->ul_lease_time) >= (pt_dhcpinf->ul_re_send_cmp))
    {
#ifdef PRINTDEBUG
        printf("call dhcp_rest_half_resend_timer()\n");
        printf("ul_lease_time(%d) >= ul_re_send_cmp(%d)\n", pt_dhcpinf->ul_lease_time, pt_dhcpinf->ul_re_send_cmp);
#endif
        pt_dhcpinf->ul_event |= DHCP_EVENT_LESTTIME_HALF_OVER;
        (pt_dhcpinf->ul_re_send_cmp) = (((pt_dhcpinf->ul_lease_limit_time) - (pt_dhcpinf->ul_lease_time)) / 2u);
        if (DHCP_1MINUTES > (pt_dhcpinf->ul_re_send_cmp))
        {
            (pt_dhcpinf->ul_re_send_cmp) = DHCP_1MINUTES;
        }
        (pt_dhcpinf->ul_re_send_cmp) += (pt_dhcpinf->ul_lease_time);
#ifdef PRINTDEBUG
        printf("ul_re_send_cmp = %d\n", pt_dhcpinf->ul_re_send_cmp);
#endif
    }
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_4_8_16_32_resend_timer
* Description  : 4s/8s/16s/32s resend timer
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void dhcp_4_8_16_32_resend_timer(dhcp_inf_t* pt_dhcpinf)
{
    if ((pt_dhcpinf->ul_re_send_time) >= (pt_dhcpinf->ul_re_send_cmp))
    {
#ifdef PRINTDEBUG
        printf("call dhcp_4_8_16_32_resend_timer()\n");
        printf("ul_re_send_time(%d) >= ul_re_send_cmp(%d)\n", pt_dhcpinf->ul_re_send_time, pt_dhcpinf->ul_re_send_cmp);
#endif
        (pt_dhcpinf->ul_re_send_cmp) <<= 1;
        if (DHCP_RE_SND_LIMIT < (pt_dhcpinf->ul_re_send_cmp))
        {
            pt_dhcpinf->ul_re_send_cmp  = DHCP_RE_SND_NOTUSE;
            pt_dhcpinf->ul_re_send_time = 0;
            pt_dhcpinf->ul_event |= DHCP_EVENT_RESEND_TIME_OVER;
            pt_dhcpinf->ul_event &= (~DHCP_EVENT_RESEND_TIMER);
#ifdef PRINTDEBUG
            printf("re send over 64s\n");
#endif
        }
        else
        {
            pt_dhcpinf->ul_event |= DHCP_EVENT_RESEND_TIMER;
            pt_dhcpinf->ul_event &= (~DHCP_EVENT_RESEND_TIME_OVER);
#ifdef PRINTDEBUG
            printf("re-send %d\n", pt_dhcpinf->ul_re_send_cmp);
#endif
        }
    }
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_int_timer
* Description  : timer countup
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void dhcp_int_timer(void)
{
    dhcp_inf_t* pt;
    uint32_t    count;

    for (count = 0; count < _t4_channel_num; count++)
    {
        pt = _ch_info_head[count].pt_dhcp_inf;

        if (DHCP_RE_SND_NOTUSE == (pt->ul_re_send_cmp))
        {
            pt->ul_re_send_time_10ms = 0;
            pt->ul_re_send_time      = 0;
        }
        else
        {
            pt->ul_re_send_time_10ms++;
            if ((pt->ul_re_send_time_10ms) >= DHCP_SEC_ADJ)
            {
                pt->ul_re_send_time_10ms = 0;
                pt->ul_re_send_time++;
            }

            if ((DHCP_STATE_BOUND <= pt->ul_state) && (DHCP_STATE_RENEWING_WAIT >= pt->ul_state))
            {
                dhcp_rest_half_resend_timer(pt);
            }
            else if (((DHCP_STATE_INIT <= pt->ul_state) && (DHCP_STATE_REQUESTING >= pt->ul_state))
                     || ((DHCP_STATE_INIT_REBOOT <= pt->ul_state) && (DHCP_STATE_REBOOTING >= pt->ul_state)))
            {
                dhcp_4_8_16_32_resend_timer(pt);
            }
            else
            {
                /* Do Nothing */
            }
        }

        if ((DHCP_LEASE_INFINITY != (pt->ul_lease_limit_time)) && (DHCP_STATE_INIT < pt->ul_state)
                && (DHCP_STATE_INFINITY != (pt->ul_state)))
        {
            pt->ul_lease_time_10ms++;
            if (DHCP_SEC_ADJ <= (pt->ul_lease_time_10ms))
            {
                pt->ul_lease_time++;
                pt->ul_lease_time_10ms = 0;
                if ((DHCP_STATE_BOUND <= (pt->ul_state)) && ((pt->ul_lease_time) >= (pt->ul_lease_limit_time)))
                {
#ifdef PRINTDEBUG
                    printf("lease over\n");
#endif
                    pt->ul_event |= DHCP_EVENT_LEASE_OVER;
                    pt->ul_event &= (~DHCP_EVENT_LESTTIME_HALF_OVER);
                    pt->ul_event &= (~DHCP_EVENT_RESEND_TIME_OVER);
                    pt->ul_event &= (~DHCP_EVENT_RESEND_TIMER);
                    pt->ul_re_send_cmp  = DHCP_RE_SND_NOTUSE;
                    pt->ul_re_send_time = 0;
                }
            }
        }
    }
    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_process_call_udp_snd_dat
* Description  : dhcp process call udp_snd_dat()
* Arguments    : uint8_t* puc_opt
*              :     DHCP packet option area
*              : dhcp_inf_t* pt_dhcpinf
*              :     pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static ER dhcp_process_call_udp_snd_dat(uint8_t *puc_opt, dhcp_inf_t* pt_dhcpinf)
{
    ER    ercd;
    dhcp_inf_t* pt = pt_dhcpinf;

    (*puc_opt) = DHCP_OPT_END;
    puc_opt++;
    pt->ul_option_size = (puc_opt - (pt->t_dhcp_pkt.uca312_options));
    pt->ul_option_size = ((sizeof(dhcp_packet_t)) - (DHCP_PKTFLD_MINIMUMOPTION - (pt->ul_option_size)));
    /* Notation is different, but the same size, send size is not the maximum 576 (structure size), so the problem */
    ercd = udp_snd_dat(pt->t_cepid, &(pt->t_ipv4ep_distaddr), &(pt->t_dhcp_pkt), (INT)(pt->ul_option_size), TMO_NBLK);
#ifdef PRINTDEBUG
    printf("call udp_snd_dat() = %d ", ercd);
    printf("cepid %d, size %d\n", pt->t_cepid, pt->ul_option_size);
#endif
    if (E_WBLK != ercd)
    {
#ifdef PRINTDEBUG
        printf("fail\n");
#endif
        /* Cast for error notification function of the argument requires a pointer to the data.
        Together address data type can also pass different. */
        report_error(pt->ul_channel, RE_DHCP_ILLEGAL, (UB*)&(pt->t_dhcp_pkt));
        dhcp_fatal_error(pt_dhcpinf);
    }
    else
    {
#ifdef PRINTDEBUG
        printf("success\n");
#endif
    }

    return ercd;
}

/***********************************************************************************************************************
* Function Name: dhcp_callback_user
* Description  : user callback
* Arguments    : UW eventid
*              :     interrupt event identifier
*              : dhcp_inf_t* pt_dhcpinf
*              :     pointer dhcp information
* Return Value : none
***********************************************************************************************************************/
static void dhcp_callback_user(UW eventid, dhcp_inf_t* pt_dhcpinf)
{
#if 0
    ER  ercd;
    if (NULL != g_fp_user)
    {
        if ((DHCP_EV_LEASE_IP == eventid) || (DHCP_EV_APIPA == eventid))
        {
            ercd = g_fp_user((pt_dhcpinf->ul_channel), eventid, &(pt_dhcpinf->t_dhcp_param_get_inf));
        }
        else
        {
            /* NULL pointer */
            ercd = g_fp_user((pt_dhcpinf->ul_channel), eventid, (void*)0);
        }
        if (0 != ercd)
        {
            /* Cast for error notification function of the argument requires a pointer to the data.
            Together address data type can also pass different. */
            report_error(pt_dhcpinf->ul_channel, RE_DHCP_ILLEGAL, (UB*)&(pt_dhcpinf->t_dhcp_pkt));
            dhcp_terminated(pt_dhcpinf);
        }
    }
#endif
}


/***********************************************************************************************************************
* Function Name: dhcp_callback_from_t4
* Description  : callback from T4 send interrupt
* Arguments    : UW eventid
*              :     interrupt event identifier
*              : FN fncd
*              :     function id
*              : VP p_parblk
*              :     parameter pointer
* Return Value : ER
*              :   0 (fixed)
***********************************************************************************************************************/
ER dhcp_callback_from_t4(ID cepid, FN fncd , VP p_parblk)
{
    ER parblk;
    dhcp_inf_t* pt_dhcpinf;

    dhcp_memcpy_local(&parblk, p_parblk, sizeof(ER));
    uint32_t    count;

    for (count = 0; count < _t4_channel_num; count++)
    {
        pt_dhcpinf = _ch_info_head[count].pt_dhcp_inf;
        if ((pt_dhcpinf->t_cepid) == cepid)
        {
            switch (fncd)
            {
                case TFN_UDP_SND_DAT:
                    if (0 < parblk)
                    {
                        pt_dhcpinf->ul_event |= DHCP_EVENT_SND_FIN_CB;
                        pt_dhcpinf->ul_event &= (~DHCP_EVENT_SND_FIN_CB_TIMEOUT);
                    }
                    else if (E_CLS == parblk)
                    {
                        pt_dhcpinf->ul_event |= DHCP_EVENT_SND_FIN_CB_TIMEOUT;
                        pt_dhcpinf->ul_event &= (~DHCP_EVENT_SND_FIN_CB);
                        /* Cast for error notification function of the argument requires a pointer to the data.
                        Together address data type can also pass different. */
                        report_error(pt_dhcpinf->ul_channel, RE_DHCP_SND_TIMEOUT, (UB*)&(pt_dhcpinf->t_dhcp_pkt));
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                    break;

                default:
                    break;
            }
        }
    }
    return 0;
}

/***********************************************************************************************************************
* Function Name: dhcp_memcpy_local
* Description  : memory copy
* Arguments    : void* pv_dst
*                    distination address
*              : void* pv_src
*                    source address
*              : size_t size
*                    transfer size
* Return Value : none
***********************************************************************************************************************/
static void dhcp_memcpy_local(void* pv_dst, void* pv_src, size_t size)
{
    memcpy((pv_dst), (pv_src), (size));

    return;
}

/***********************************************************************************************************************
* Function Name: dhcp_memset_local
* Description  : memory set
* Arguments    : void* pv_dst
*                    distination address
*              : long l_value
*                    value
*              : size_t size
* Return Value : none
***********************************************************************************************************************/
static void dhcp_memset_local(void* pv_dst, uint32_t value, size_t size)
{
    memset((pv_dst), (value), (size));

    return;
}


/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
typedef void (ft_dhcp_handler)(dhcp_inf_t* pt_dhcpinf);
/// static const ft_dhcp_handler* const gpft_dhcpf[DHCP_EVENT_COUNT+1][DHCP_STATE_COUNT+1] =
static ft_dhcp_handler* gpft_dhcpf[DHCP_EVENT_COUNT+1][DHCP_STATE_COUNT+1] =
{
    {
        dhcp_initial,       dhcp_init,          dhcp_to_init,       dhcp_to_init,
        dhcp_to_init,       dhcp_to_init,       dhcp_init_reboot,   dhcp_init_reboot,
        dhcp_init_reboot,   dhcp_init_reboot,   dhcp_terminated,    dhcp_terminated,
        dhcp_init_reboot,   dhcp_init_reboot,   dhcp_init_reboot,   dhcp_decline,
        dhcp_dont_care
    },
    {
        dhcp_initial,       dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_terminated,    dhcp_terminated,    dhcp_dont_care,     dhcp_dont_care,
        dhcp_terminated,    dhcp_terminated,    dhcp_terminated,    dhcp_dont_care,
        dhcp_dont_care
    },
    {
        dhcp_initial,       dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_decline,       dhcp_decline,       dhcp_decline,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care
    },
    {
        dhcp_initial,       dhcp_dont_care,     dhcp_to_selecting,  dhcp_dont_care,
        dhcp_to_requesting, dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_to_renewing,   dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_to_rebooting,  dhcp_dont_care,     dhcp_dont_care,
        dhcp_to_init
    },
    {
        dhcp_initial,       dhcp_dont_care,     dhcp_fatal_error,   dhcp_dont_care,
        dhcp_fatal_error,   dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_fatal_error,   dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_fatal_error,   dhcp_dont_care,     dhcp_dont_care,
        dhcp_fatal_error
    },
    {
        dhcp_initial,       dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_to_init,       dhcp_dont_care,     dhcp_terminated,
        dhcp_terminated,    dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_terminated,    dhcp_dont_care,
        dhcp_dont_care
    },
    {
        dhcp_initial,       dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_gratuitousarp, dhcp_no_operation,  dhcp_no_operation,
        dhcp_to_bound,      dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_to_bound,      dhcp_dont_care,
        dhcp_dont_care
    },
    {
        dhcp_initial,       dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,     dhcp_renewing,
        dhcp_renewing,      dhcp_renewing,      dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care
    },
    {
        dhcp_initial,       dhcp_init,          dhcp_init,          dhcp_init,
        dhcp_selecting,     dhcp_selecting,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_init_reboot,   dhcp_init_reboot,   dhcp_init_reboot,   dhcp_dont_care,
        dhcp_dont_care
    },
    {
        dhcp_initial,       dhcp_dont_care,     dhcp_dont_care,     dhcp_to_apipa,
        dhcp_dont_care,     dhcp_to_apipa,      dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_to_bound,      dhcp_dont_care,
        dhcp_dont_care
    },
    {
        dhcp_initial,       dhcp_dont_care,     dhcp_dont_care,     dhcp_selecting,
        dhcp_no_operation,  dhcp_no_operation,  dhcp_no_operation,  dhcp_no_operation,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care
    },
    {
        dhcp_initial,       dhcp_init,          dhcp_dont_care,     dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_ipreplyarp,    dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_apipa,         dhcp_dont_care,
        dhcp_dont_care,     dhcp_dont_care,     dhcp_dont_care,     dhcp_decline,
        dhcp_dont_care
    }
};

/***********************************************************************************************************************
* Function Name: dhcp_process
* Description  : dhcp process
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void dhcp_process(void)
{
    dhcp_inf_t* pt_dhcpinf;
    uint32_t    ul_if;
    uint32_t    ul_evcnt;
    uint32_t    ul_state;

    for (ul_if = 0; ul_if < _t4_channel_num; ul_if++)
    {
        pt_dhcpinf = _ch_info_head[ul_if].pt_dhcp_inf;
        if (0u < (pt_dhcpinf->ul_skiptime))
        {
            pt_dhcpinf->ul_skiptime--;
        }
        else
        {
            pt_dhcpinf->ul_channel = ul_if;
            _ch_info_tbl = (&_ch_info_head[ul_if]);
            if (1u == (_ch_info_tbl->ip_terminated_flag))
            {
                pt_dhcpinf->ul_skiptime = 0xffffffffu;
                dhcp_callback_user(DHCP_EV_PLEASE_RESET, pt_dhcpinf);
            }
            else
            {
                ul_evcnt = 0;
                while ((0 == (((pt_dhcpinf->ul_event) >> ul_evcnt)&1)) && (ul_evcnt < DHCP_EVENT_COUNT))
                {
                    ul_evcnt++;
                }
                ul_state = (pt_dhcpinf->ul_state);
                (*gpft_dhcpf[ul_evcnt][ul_state])(pt_dhcpinf);
                if ((gpft_dhcpf[ul_evcnt][ul_state] != dhcp_dont_care) && (0 != (pt_dhcpinf->ul_event)))
                {
#ifdef PRINTDEBUG
                    printf("ch %02d, flag clear E%04X, S%02d->", ul_if, pt_dhcpinf->ul_event, ul_state);
#endif
                    pt_dhcpinf->ul_event &= (~(1 << ul_evcnt));
#ifdef PRINTDEBUG
                    printf("E%04X, S%02d\n\n", pt_dhcpinf->ul_event, pt_dhcpinf->ul_state);
#endif
                }
            }
        }
    }

    return;
}
