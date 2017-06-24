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
* Copyright (C) 2014-2016 Renesas Electronics Corporation, All Rights Reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : ether.c
* Version      : 1.01
* Description  : Processing for Ether protocol
* Website      : https://www.renesas.com/mw/t4
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.04.2014 1.00    First Release
*         : 30.11.2016 1.01    add DHCP relation
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "r_tcpip_private.h"
#include "type.h"
#include "r_t4_itcpip.h"
#include "ether.h"
#include "ip.h"
#include "tcp.h"
#include "dhcp.h"
#include "global.h"

#include "r_t4_rx/src/config_tcpudp.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (read from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: _ether_proc_rcv
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/

void _ether_proc_rcv(void)
{
    sint16  len;
    _EP   *pep;

    /* Return when receive buffer has not released yet */
    /* The information has already stored in '_p_rcv_buf' */
    if (_ch_info_tbl->_p_rcv_buf.len != 0)
    {
        return;
    }

    /* Call: driver interface to receive */
    void *buf;
    len = lan_read(_ch_info_tbl->_ch_num, &buf);

    /*
     *  len > 0 : receive data size
     *       -1 : No data in LAN controller buffer
     *       -2 : LAN controller status is 'STOP'
     *       -5 : LAN controller status is 'ILLEGAL' or need reset.
     *       -6 : CRC error
     */

    if (len < 0)
    {
        /* CRC error: buffer release */
        if (len == -6)
        {
            rcv_buff_release(_ch_info_tbl->_ch_num) ;
            _ch_info_tbl->_p_rcv_buf.len = 0;
        }
        /* LAN Controller reset */
        else if (len == -5)
        {
            lan_reset(_ch_info_tbl->_ch_num);
        }
        /* No data, LAN controller status is 'STOP'. */
        return;
    }
    /* Illegal len: discard the received data */
    else if ((len > 1514) || (len < 60))
    {
        rcv_buff_release(_ch_info_tbl->_ch_num);
        _ch_info_tbl->_p_rcv_buf.len = 0;
        report_error(_ch_info_tbl->_ch_num, RE_LEN, (UB*)buf);
        return;
    }
    pep = (_EP *)buf;
    data_link_buf_ptr = (UB*)buf;

    /* other(len >= 0): start receive process */
    _ch_info_tbl->_p_rcv_buf.len = len - _ETH_LEN;
    _ch_info_tbl->_p_rcv_buf.pip = &(pep->data[0]);
    _ch_info_tbl->_p_rcv_buf.ip_rcv = 0;

    /* Find the packet type */
    switch (pep->eh.eh_type)
    {
            /* IP Packet Receive */
        case hs2net(EPT_IP) :
            /* IP data received flag ON */
            _ch_info_tbl->_p_rcv_buf.ip_rcv = 1;
            break ;
            /* ARP Packet Receive */
        case hs2net(EPT_ARP) :
            _ether_rcv_arp() ;
            break ;
        default :
            rcv_buff_release(_ch_info_tbl->_ch_num);
            _ch_info_tbl->_p_rcv_buf.len = 0;
            report_error(_ch_info_tbl->_ch_num, RE_NETWORK_LAYER, data_link_buf_ptr);
            break;  /*2670*/
    }

    return;
}

/***********************************************************************************************************************
* Function Name: _ether_rcv_arp
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _ether_rcv_arp(void)
{
    _ARP_ENTRY *ae;
    _ARP_PKT *rpap;
    uint16  i;
    uint32  ul_res;

    rpap = (_ARP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    /* Discard: exclude ARP packet addressed to itself */
    ul_res = memcmp(rpap->ar_spa, _ch_info_tbl->_myipaddr, IP_ALEN);
    if ( ul_res == 0)               /* colligion ip detect */
    {
        if ((rpap->ar_op) == hs2net(AR_REPLY))
        {
            callback_tcpip(_ch_info_tbl->_ch_num, ETHER_EV_COLLISION_IP, 0);
        }
        else
        {
            /* nothing to do */
        }
        rcv_buff_release(_ch_info_tbl->_ch_num);
        _ch_info_tbl->_p_rcv_buf.len = 0;
        return;
    }
    else if (_cmp_ipaddr(&(rpap->ar_tpa), _ch_info_tbl->_myipaddr))
    {
        rcv_buff_release(_ch_info_tbl->_ch_num);
        _ch_info_tbl->_p_rcv_buf.len = 0;
        return;
    }

    /* Check each field value */
    if ((rpap->ar_hwtype != hs2net(AR_HARDWARE))
            || (rpap->ar_prtype != hs2net(EPT_IP))
            || (rpap->ar_hwlen != EP_ALEN) || (rpap->ar_prlen != IP_ALEN))
    {
        rcv_buff_release(_ch_info_tbl->_ch_num);
        _ch_info_tbl->_p_rcv_buf.len = 0;
        report_error(_ch_info_tbl->_ch_num, RE_ARP_HEADER2, data_link_buf_ptr);
        return;
    }

    switch (rpap->ar_op)
    {
            /* ARP request: generate ARP response and transmit flag on and renew the ARP table */
        case(hs2net(AR_REQUEST)):
            /* transmit flag on */
            _ch_info_tbl->flag |= (_TCBF_NEED_SEND | _TCBF_SND_ARP_REP);
            /* generate packet process is in transmit process (this timing, only store the data) */
            memcpy(_ch_info_tbl->arp_buff, rpap, sizeof(_ARP_PKT));
            /* renew the ARP table */
            _ether_arp_add(rpap->ar_spa, rpap->ar_sha);
            break;
            /* renew the ARP table when unresolved entry is exist */
        case(hs2net(AR_REPLY)):
            /* Is unresolved entry exist? */
            ae = _ether_arp_tbl[_ch_info_tbl->_ch_num];
            for (i = 0; i < _ip_tblcnt[_ch_info_tbl->_ch_num]; i++, ae++)
            {
                if (ae->ae_state == AS_PENDING)
                {
                    /* If yes, its reply? */
                    if (_cmp_ipaddr(ae->ae_pra, rpap->ar_spa) == 0)
                    {
                        /* If yes, resolve the entry */
                        _cpy_eaddr(ae->ae_hwa, rpap->ar_sha);
                        ae->ae_ttl = ARP_TIMEOUT;
                        ae->ae_state = AS_RESOLVED;
                    }
                }
            }
            break;
        default:
            break; /*2670*/
    }

    rcv_buff_release(_ch_info_tbl->_ch_num);
    _ch_info_tbl->_p_rcv_buf.len = 0;
    return;
}


#if defined(_ICMP)
/***********************************************************************************************************************
* Function Name: _ether_arp_resolve
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _ether_arp_resolve(void)
{
    _ETH_HDR *peh;
    _IP_HDR  *piph;

    piph = (_IP_HDR *)(_ch_info_tbl->_p_rcv_buf.pip);
    peh = (_ETH_HDR *)(data_link_buf_ptr);

    _ether_arp_add(piph->ip_src, peh->eh_src);

    return;
}

/***********************************************************************************************************************
* Function Name: _ether_proc_rcv
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
sint16 _ether_snd_arp(_ARP_ENTRY *ae)
{
    _ETH_HDR *peh;
    _ARP_PKT *rpap, *parp;
    sint16  ret;
    rpap = (_ARP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    rpap = (_ARP_PKT *)_ch_info_tbl->arp_buff;

    peh = &(_tx_hdr.eh);
    parp = &(_tx_hdr.ihdr.tarp);

    /* If ARP request, generate ARP packet */
    if (_ch_info_tbl->flag & _TCBF_SND_ARP_REQ)
    {
        /* generate ARP packet */
        parp->ar_hwtype = hs2net(HWT_ETH);
        parp->ar_prtype = hs2net(EPT_IP);
        parp->ar_hwlen = EP_ALEN;
        parp->ar_prlen = IP_ALEN;
        parp->ar_op  = hs2net(AR_REQUEST);
        memcpy(parp->ar_sha, _myethaddr[_ch_info_tbl->_ch_num], EP_ALEN);
        _cpy_ipaddr(parp->ar_spa, _ch_info_tbl->_myipaddr);
        _cpy_eaddr(parp->ar_tha, ae->ae_hwa);
        _cpy_ipaddr(parp->ar_tpa, ae->ae_pra);
        _cpy_eaddr(peh->eh_dst, ae->ae_hwa);
    }
    /* If ARP response request, generate ARP packet using received ARP packet */
    else if (_ch_info_tbl->flag & _TCBF_SND_ARP_REP)
    {
        _cpy_eaddr(parp, rpap);
        parp->ar_op = hs2net(AR_REPLY);
        memcpy(parp->ar_sha, _myethaddr[_ch_info_tbl->_ch_num], EP_ALEN);
        memcpy(parp->ar_spa, _ch_info_tbl->_myipaddr, IP_ALEN);
        memcpy(parp->ar_tha, rpap->ar_sha, EP_ALEN + IP_ALEN);
        _cpy_eaddr(peh->eh_dst, rpap->ar_sha);
    }

    else
    {
        return 0;
    }    /*2669*/

    _tx_hdr.hlen = _ETH_LEN + ARP_PLEN;
    ret = _ether_snd(EPT_ARP, NULL, 0);

    _ch_info_tbl->flag &= ~(_TCBF_SND_ARP_REQ | _TCBF_SND_ARP_REP);

    return ret;
}
#endif

void ether_snd_gratuitous_arp(void)
{
    _ARP_PKT *parp;
    const uint8_t bcastadr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    parp = &(_tx_hdr.ihdr.tarp);
    parp->ar_hwtype = hs2net(HWT_ETH);
    parp->ar_prtype = hs2net(EPT_IP);
    parp->ar_hwlen  = EP_ALEN;
    parp->ar_prlen  = IP_ALEN;
    parp->ar_op     = hs2net(AR_REQUEST);

    memcpy(parp->ar_sha, _myethaddr[_ch_info_tbl->_ch_num], EP_ALEN);       /* senderHWaddrs is my ether addr */
    _cpy_ipaddr(parp->ar_spa, _ch_info_tbl->_myipaddr);                     /* senderProtoAddrs is my ip addr */
    _cpy_eaddr(parp->ar_tha, bcastadr);                                     /* targetHWaddrs is broad cast addr */
    _cpy_ipaddr(parp->ar_tpa, _ch_info_tbl->_myipaddr);                     /* targetProtoAddrs is my ip addr */

    _tx_hdr.hlen = _ETH_LEN + ARP_PLEN;
    _ether_snd(EPT_ARP, NULL, 0);

    _ch_info_tbl->flag &= ~(_TCBF_SND_ARP_REQ | _TCBF_SND_ARP_REP);

    return;
}

void ether_snd_ip_reply_arp(void)
{
    _ARP_PKT *parp;
    const uint8_t bcastadr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    parp = &(_tx_hdr.ihdr.tarp);
    parp->ar_hwtype = hs2net(HWT_ETH);
    parp->ar_prtype = hs2net(EPT_IP);
    parp->ar_hwlen  = EP_ALEN;
    parp->ar_prlen  = IP_ALEN;
    parp->ar_op     = hs2net(AR_REPLY);

    memcpy(parp->ar_sha, _myethaddr[_ch_info_tbl->_ch_num], EP_ALEN);       /* senderHWaddrs is my ether addr */
    _cpy_ipaddr(parp->ar_spa, _ch_info_tbl->_myipaddr);                     /* senderProtoAddrs is my ip addr */
    _cpy_eaddr(parp->ar_tha, bcastadr);                                     /* targetHWaddrs is b_cast */
    _cpy_ipaddr(parp->ar_tpa, _ch_info_tbl->_myipaddr);                     /* targetProtoAddrs is my ip addr */

    _tx_hdr.hlen = _ETH_LEN + ARP_PLEN;
    _ether_snd(EPT_ARP, NULL, 0);

    _ch_info_tbl->flag &= ~(_TCBF_SND_ARP_REQ | _TCBF_SND_ARP_REP);

    return;
}


/***********************************************************************************************************************
* Function Name: _ether_snd_ip
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
sint16 _ether_snd_ip(uchar *data, uint16 dlen)
{
    sint16 ret = 0;
    sint16 i;
    uint32  nexthop;
    uint32  tmp1;
    uchar  eaddr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
#if defined(_MULTI)
    uint32 addr;
    uint32 subnet_mask;
    uint32 broad_cast_addr = 0xffffffffu;
    static const uchar ip_broadcast[] = {0xff, 0xff, 0xff, 0xff};
#endif
    _ETH_HDR *peh;
    _ARP_ENTRY *ae;


#if defined(_MULTI)
    net2hl_yn_xn(&addr, _tx_hdr.ihdr.tip.iph.ip_dst);
    net2hl_yn_xn(&subnet_mask, tcpudp_env[_ch_info_tbl->_ch_num].maskaddr);
#endif

    peh = &(_tx_hdr.eh);

    /* Judge the destination is multicast or out of LAN (over G/W) */
    _cpy_ipaddr(&tmp1, _tx_hdr.ihdr.tip.iph.ip_dst);

#if defined(_MULTI)
    /* EX.XX.XX.XX (multicast) */
    if ((*((uchar*)&tmp1) & 0xf0) == 0xe0)
    {
        _cpy_ipaddr(&nexthop, &tmp1);
        _tx_hdr.hlen += _ETH_LEN;
        ret = _ether_snd(EPT_IP, data, dlen);

        /* Return when multicast */
        return ret;
    }
    /* 255.255.255.255 (broadcast) or (directed broadcast) */
    else if (!memcmp(_tx_hdr.ihdr.tip.iph.ip_dst, ip_broadcast, 4) ||
             ((addr & ~subnet_mask) == (broad_cast_addr & ~subnet_mask)))
    {
        /* Change the destination MAC address to broadcast address */
        _tx_hdr.hlen += _ETH_LEN;
        ret = _ether_snd(EPT_IP, data, dlen);

        /* Return when broadcast */
        return ret;
    }
    else
    {
        /* Normally sending */
    }
#endif
    /* If destination is in same network, nexthop is destination IP address directly */
    if ((_ch_info_tbl->_myipaddr[0] & _ch_info_tbl->_mymaskaddr[0]) == (tmp1 & _ch_info_tbl->_mymaskaddr[0]))
    {
        _cpy_ipaddr(&nexthop, &tmp1);
    }
    /* If destination is out of same network, nexthop is G/W IP address */
    else
    {
        if (_ch_info_tbl->_mygwaddr[0] != 0)
        {
            _cpy_ipaddr(&nexthop, _ch_info_tbl->_mygwaddr);
        } /*2669*/
        else
        {
            return 0;
        } /*2669*/
    }

    /* exist nexthop in ARP table? */
    ae = _ether_arp_tbl[_ch_info_tbl->_ch_num];
    for (i = 0; i < _ip_tblcnt[_ch_info_tbl->_ch_num]; i++, ae++)
    {
        if ((_cmp_ipaddr(&nexthop, ae->ae_pra)) == 0)
        {
            break;
        } /*2669*/
    }
    if (i < _ip_tblcnt[_ch_info_tbl->_ch_num])
    {
        /* If exist */
        switch (ae->ae_state)
        {
            case AS_RESOLVED:
                _tx_hdr.hlen += _ETH_LEN;
                _cpy_eaddr(peh->eh_dst, ae->ae_hwa);
                ret = _ether_snd(EPT_IP, data, dlen);
                break;
            case AS_PENDING:
                /* Already ARP sent and waiting for resolve, return with no process */
                return -1;
            case AS_TMOUT:
                /* ARP timeout */
                return -2;

        }
    }
    /* If no exist */
    else
    {
        /* Regist the new entry to the ARP table */
        ae = _ether_arp_add((uchar *) & nexthop, eaddr);
        _ch_info_tbl->flag |= _TCBF_SND_ARP_REQ;
        _ether_snd_arp(ae);

        return -1;
    }
    return ret;
}

/***********************************************************************************************************************
* Function Name: _ether_snd
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
sint16 _ether_snd(uint16 type, uchar *data, uint16 dlen)
{
    _ETH_HDR *peh;
    sint16  plen, ret, i;
    uchar  pad[_EP_PAD_MAX]; /* 0 padding data (max size if 18(_EP_PAD_MAX)) */

#if defined(_MULTI)
    _IP_HDR  *piph;
    static const uchar eth_multi_addr[3] = {0x01, 0x00, 0x5e};
    static const uchar eth_broadcast[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    static const uchar ip_broadcast[] = {0xff, 0xff, 0xff, 0xff};
    uint32 addr;
    uint32 subnet_mask;
    uint32 broad_cast_addr = 0xffffffffu;
#endif

    peh = &(_tx_hdr.eh);

    /* Generate Ethernet header */
    memcpy(peh->eh_src, _myethaddr[_ch_info_tbl->_ch_num],  EP_ALEN);
    peh->eh_type = hs2net(type);

#if defined(_MULTI)
    if (type == EPT_IP)
    {
        /* If destination IP address is multicast, change the destination MAC address to for multicast */
        piph = &_tx_hdr.ihdr.tip.iph;
        /* EX.XX.XX.XX (All Multicast) */
        if ((piph->ip_dst[0] & 0xf0) == 0xE0)
        {
            /* Set the Internet multicast address (01-00-5e-00-00-00)
               and lower 23-bit destination IP address  */
            memcpy(peh->eh_dst, (const void*)eth_multi_addr, sizeof(eth_multi_addr));
            memcpy(peh->eh_dst + sizeof(eth_multi_addr), piph->ip_dst + 1, 3);
            /* clear the bit-24 */
            peh->eh_dst[3] &= 0x7f;
        }
        /* If destination IP address is broadcast, change the destination MAC address to for broadcast */
        /* 255.255.255.255 (broadcast) */
        if (!memcmp(piph->ip_dst, ip_broadcast, 4))
        {
            memcpy(peh->eh_dst, eth_broadcast, EP_ALEN);
        }
        net2hl_yn_xn(&addr, piph->ip_dst);
        net2hl_yn_xn(&subnet_mask, tcpudp_env[_ch_info_tbl->_ch_num].maskaddr);
        /* (directed broadcast) */
        if ((addr & ~subnet_mask) == (broad_cast_addr & ~subnet_mask))
        {
            memcpy(peh->eh_dst, eth_broadcast, EP_ALEN);
        }
    }
#endif

    /* 0 padding when the packet length is less than 60 byte */
    if ((_tx_hdr.hlen + dlen) < _EP_MIN_LEN)
    {
        plen = _EP_MIN_LEN - (_tx_hdr.hlen + dlen);
        /* copy the data to temporarily area for padding */
        memcpy(pad, data, dlen);
        for (i = 0; i < plen; i++)
        {
            pad[dlen+i] = 0;
        } /*2669*/
        /* call the transmit function */
        ret = lan_write(_ch_info_tbl->_ch_num, (B*) & _tx_hdr, \
                        (H)_tx_hdr.hlen, (B*)pad, (H)(_EP_MIN_LEN - _tx_hdr.hlen));
    }
    else
        /* call the transmit function */
        ret = lan_write(_ch_info_tbl->_ch_num, (B *) & _tx_hdr, (H)_tx_hdr.hlen, (B*)data, (H)dlen);

    /* 0: transmit complete */
    if (ret == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    } /*2669*/
}

/***********************************************************************************************************************
* Function Name: _ether_arp_add
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
_ARP_ENTRY *_ether_arp_add(uchar *ipaddr, uchar *ethaddr)
{
    sint16 i;
    uint16 tmp_ttl = ARP_TIMEOUT;
    uchar bcast[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    _ARP_ENTRY *ae, *ae_tmp, *ae_tmp2;


    /* Search the existed entry */
    ae_tmp = NULL;
    ae = _ether_arp_tbl[_ch_info_tbl->_ch_num];
    for (i = 0; i < _ip_tblcnt[_ch_info_tbl->_ch_num]; i++, ae++)
    {
        if ((_cmp_ipaddr(ipaddr, ae->ae_pra)) == 0)
        {
            /* If the resolved entry is already exist */
            if (ae->ae_state == AS_RESOLVED)
            {
                /* renew the TTL */
                ae->ae_ttl = ARP_TIMEOUT;
            }
            /* If the entry is already exist but not resoleved */
            else
            {
                memcpy(ae->ae_hwa, ethaddr, EP_ALEN);
                ae->ae_ttl = ARP_TIMEOUT;
                ae->ae_state = AS_RESOLVED;
            }
            return ae;
        }
        else if (ae->ae_state == AS_FREE)
        {
            ae_tmp = ae;
        } /*2669*/
    }

    /* Delete the most old entry if FREE entry is not exist */
    if (ae_tmp == NULL)
    {
        ae_tmp2 = NULL;
        /* Select the most smallest TTL */
        ae = _ether_arp_tbl[_ch_info_tbl->_ch_num];
        for (i = 0; i < _ip_tblcnt[_ch_info_tbl->_ch_num]; i++, ae++)
        {
            if (ae->ae_state == AS_RESOLVED)
            {
                if (ae->ae_ttl <= tmp_ttl)
                {
                    tmp_ttl = ae->ae_ttl;
                    ae_tmp = ae;
                }
            }
            else if (ae->ae_state & (AS_PENDING | AS_TMOUT))
            {
                ae_tmp2 = ae;
            } /*2669*/
        }
        if (ae_tmp != NULL)
        {
            ae = ae_tmp;
        }
        else
        {
            ae = ae_tmp2;
        } /*2669*/

        /* Delete the selected entry */
        _ether_arp_del(ae);
    }
    /* If FREE entry is exist, use this */
    else
    {
        ae = ae_tmp;
    } /*2669*/

    memcpy(ae->ae_pra, ipaddr, IP_ALEN);
    memcpy(ae->ae_hwa, ethaddr, EP_ALEN);
    ae->ae_ttl = ARP_TIMEOUT;
    /* If MAC address is all 'f', change the status to PENDING */
    if (memcmp(ethaddr, bcast, EP_ALEN) == 0)
    {
        ae->ae_state = AS_PENDING;
        ae->ae_attempts = ARP_MAXRETRY;
    }
    else
    {
        ae->ae_state = AS_RESOLVED;
        /* Do not use MAXRETRY when RESOLEVED */
    }

    return ae;
}

/***********************************************************************************************************************
* Function Name: _ether_arp_del
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _ether_arp_del(_ARP_ENTRY *ae)
{
    memset(ae->ae_pra, 0, sizeof(_ARP_ENTRY));
    return;
}

/***********************************************************************************************************************
* Function Name: _ether_arp_init
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _ether_arp_init(void)
{
    uint16 counter;
    _ARP_ENTRY *ae;

    /* table clear for all channels */
    for (counter = 0; counter < _t4_channel_num; counter++)
    {
        ae = _ether_arp_tbl[counter];
        memset(ae->ae_pra, 0, (sizeof(_ARP_ENTRY) * _ip_tblcnt[counter]));
    }
    return;
}

ER callback_tcpip(UB channel, UW eventid, VP param)
{
    if (eventid == ETHER_EV_LINK_ON)
    {
        _ch_info_head[channel].etherlink = 1;
    }
    else if (eventid == ETHER_EV_LINK_OFF)
    {
        _ch_info_head[channel].etherlink = 0;
    }
///    if (0 != g_fp_user)
///    {
///        g_fp_user(channel, eventid, param);
///    }
    if (1 == _t4_dhcp_enable)
    {
        dhcp_callback_from_ether(channel, eventid, param);
    }
    return 0;
}


