//=====================================================================//
/*!	@file
	@brief	ip.c @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "net_config.h"
#include "ip.h"
#include <string.h>
#include "type.h"
#include "config_tcpudp.h"
#if defined(_ETHER)
#include "ether.h"
#elif defined(_PPP)
#include "ppp.h"
#endif
#include "tcp.h"
#include "udp.h"
#include "core/driver/driver.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
uint8_t *data_link_buf_ptr;      /* Buffer pointer to Datalink layer */
_CH_INFO *_ch_info_tbl;
_CH_INFO *_ch_info_head;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
static int16_t _ip_chk_srcip(uint8_t *src_ipaddr);


/***********************************************************************************************************************
* Function Name: _ip_rcv_hdr
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int16_t _ip_rcv_hdr(void)
{
    _IP_HDR  *pip;
    uint16_t  total_len;

    /* Head of IP packet   */
    pip  = (_IP_HDR *)_ch_info_tbl->_p_rcv_buf.pip;

#if defined(_MULTI)
    /* Enabled: Broadcast or Multicast */
    if (E_OK != _ip_check_ipadd_proto(pip))
    {
        report_error(_ch_info_tbl->_ch_num, RE_IP_HEADER1, data_link_buf_ptr);
        goto _err_ip_rcv_hdr;
    }
#else
    /* Disabled: Broadcast or Multicast */
    /* Check destination IP address: Only accept my IP address */
    if (_cmp_ipaddr(pip->ip_dst, _ch_info_tbl->_myipaddr) != 0)
    {
        report_error(_ch_info_tbl->_ch_num, RE_IP_HEADER1, data_link_buf_ptr);
        goto _err_ip_rcv_hdr;
    }
#endif

    /* Check source IP address (discard multicast and broadcast address) */
    if (pip->ip_src[0] >= 0xE0)
    {
        report_error(_ch_info_tbl->_ch_num, RE_IP_HEADER2, data_link_buf_ptr);
        goto _err_ip_rcv_hdr;
    }
    /* Check source IP address (discard loopback address 172.0.0.1) */
    if ((pip->ip_src[0] == 127) && (pip->ip_src[1] == 0)
            && (pip->ip_src[2] == 0)   && (pip->ip_src[3] == 1))
    {
        report_error(_ch_info_tbl->_ch_num, RE_IP_HEADER3, data_link_buf_ptr);
        goto _err_ip_rcv_hdr;
    }

    /* Check IP version */
    if ((pip->ip_ver_len >> 4) != _IPH_VERSION4)
    {
        report_error(_ch_info_tbl->_ch_num, RE_IP_HEADER4, data_link_buf_ptr);
        goto _err_ip_rcv_hdr;
    }

    /* exist IP options? (IP option is not supported) */
    /*   - If IP header length is not minimum size, this means this packet includes IP options */
    if (((pip->ip_ver_len & 0xf) << 2) != _IP_HLEN_MIN)
    {
        report_error(_ch_info_tbl->_ch_num, RE_IP_HEADER5, data_link_buf_ptr);
        goto _err_ip_rcv_hdr;
    }

    /* Check checksum */
    if (_cksum((uint8_t *)pip, _IP_HLEN_MIN, 0) != 0)
    {
        report_error(_ch_info_tbl->_ch_num, RE_IP_HEADER6, data_link_buf_ptr);
        goto _err_ip_rcv_hdr;
    }

    /* Check IP datagram length is wrong.
     *  - IP datagram length in IP header is bigger than driver notified (include padding)
     *  - IP datagram length in IP header is smaller than IP header minimum size
     */
    total_len = net2hs(pip->ip_total_len);   /* IPヘッダに格納されたIPデータグラムサイズ */
    if ((total_len > _ch_info_tbl->_p_rcv_buf.len) || (total_len < _IP_HLEN_MIN))
    {
        report_error(_ch_info_tbl->_ch_num, RE_IP_HEADER7, data_link_buf_ptr);
        goto _err_ip_rcv_hdr;
    }

    /* Check invalid source IP address */
    if (_ip_chk_srcip(pip->ip_src) != 0)
    {
        report_error(_ch_info_tbl->_ch_num, RE_IP_HEADER8, data_link_buf_ptr);
        goto _err_ip_rcv_hdr;
    }

    /* Not supported fragment datagram */
    if ((pip->ip_fragoff & hs2net(_IPH_FRAGOFF | _IPH_MF)) != 0)
    {
        report_error(_ch_info_tbl->_ch_num, RE_IP_HEADER9, data_link_buf_ptr);
        goto _err_ip_rcv_hdr;
    }
    return 0;

_err_ip_rcv_hdr:
    return -1;
}

/***********************************************************************************************************************
* Function Name: _ip_snd
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int16_t _ip_snd(uint8_t *data, uint16_t dlen)
{
    int16_t ercd;
    register _IP_HDR *pip = (_IP_HDR *) & _tx_hdr.ihdr.tip.iph;
    register uint16_t sum;

    /* generate: IP header */
    pip->ip_chksum  = 0;
    pip->ip_tos   = 0;
    pip->ip_fragoff  = 0;
    pip->ip_ver_len  = (_IPH_VERSION4 << 4) | (_IP_HLEN_MIN >> 2);
#if defined(_MULTI)
    if ((pip->ip_dst[0] & 0xf0) == 0xe0)   /* multicast addresss */
        pip->ip_ttl  = multi_TTL[_ch_info_tbl->_ch_num];
    else
#endif
        pip->ip_ttl   = _IPH_TTL;
    pip->ip_total_len = _IP_HLEN_MIN + _tx_hdr.hlen + dlen;
    pip->ip_total_len = hs2net(pip->ip_total_len);
    pip->ip_id   = hs2net(_ch_info_tbl->_ip_id);
    _ch_info_tbl->_ip_id++;

    sum  = _cksum((uint8_t *)pip, _IP_HLEN_MIN, 0);
    pip->ip_chksum  = hs2net(sum);

    _tx_hdr.hlen += _IP_HLEN_MIN;

#if defined(_PPP)
    ercd = _ppp_snd_ip(data, dlen);
#elif defined(_ETHER)
    ercd = _ether_snd_ip(data, dlen);
#endif
    if (ercd == 0)
    {
        return E_IP_SENT;
    }
    else if (ercd == -2)
    {
        return -2;
    }
    else
    {
        return E_IP_PENDING;
    }
}

#if defined(_ICMP)
/***********************************************************************************************************************
* Function Name: _ip_snd_icmp
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _ip_snd_icmp(void)
{
    _ch_info_tbl->flag |= _TCBF_SND_ICMP;
    return;
}
#endif

/***********************************************************************************************************************
* Function Name: _ip_chk_srcip
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int16_t _ip_chk_srcip(uint8_t *src_ip)
{
    uint32_t tmp1, tmp2, tmp3 ;

    /* Check if src IP is Broadcast or Multicast */
    if (src_ip[0] >= 0xE0)
        return -1;

#if defined(_ETHER)
    /* Check if src IP is Network Address or Network Broadcast */
    _cpy_ipaddr(&tmp1, src_ip);
    _cpy_ipaddr(&tmp2, _ch_info_tbl->_mymaskaddr);
    _cpy_ipaddr(&tmp3, _ch_info_tbl->_myipaddr);
    if ((tmp1 == (tmp2 & tmp3)) || (tmp1 == (~tmp2 | tmp3)))
        return -1;

    return 0;
#endif
}

#if defined(_MULTI)
/***********************************************************************************************************************
* Function Name: _ip_check_ipadd_proto
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int8_t _ip_check_ipadd_proto(_IP_HDR *piph)
{
    uint8_t type;

    if (_cmp_ipaddr(piph->ip_dst, _ch_info_tbl->_myipaddr) == 0)
    {
        if ((piph->ip_proto_num == _IPH_TCP)
#if defined(_ICMP)
                || (piph->ip_proto_num == _IPH_ICMP)
#endif
#if defined(_UDP)
                || (piph->ip_proto_num == _IPH_UDP)
#endif
           )
        {
            return (0);
        }
    }
    else
    {
        type = _ip_check_broadcast(piph->ip_dst);
        if (type == _IP_TYPE_BROADCAST)     // 255.255.255.255
        {
            if (piph->ip_proto_num != _IPH_TCP)
                return (0);
        }
        else if (type == _IP_TYPE_DIRECTED_BROADCAST)    // ディレクテッドブロードキャスト
        {
            if (piph->ip_proto_num != _IPH_TCP)
            {
                return (0);
            }
        }

        type = _ip_check_multicast(piph->ip_dst);
        if (type == _IP_TYPE_MULTI_ALL_HOST)    // 224.0.0.1
        {
            if (piph->ip_proto_num != _IPH_TCP)
                return (0);
        }
        else if (type == _IP_TYPE_MULTI_ANY)
        {
            if (piph->ip_proto_num != _IPH_TCP)
            {
                return (0);
            }
        }
    }
    return (-1);
}

/***********************************************************************************************************************
* Function Name: _ip_check_multicast
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
uint8_t _ip_check_multicast(uint8_t *ipaddr)
{
    uint32_t addr;

    net2hl_yn_xn(&addr, ipaddr);

    if (addr == 0xe0000000)     // 224.0.0.0 (Reserved)
        return (_IP_TYPE_MULTI_RESERVED);
    else if (addr == 0xe0000001)   // 224.0.0.1 (All Host)
        return (_IP_TYPE_MULTI_ALL_HOST);
    else if ((ipaddr[0] & 0xf0) == 0xe0) // EX.XX.XX.XX (Other Multicast)
        return (_IP_TYPE_MULTI_ANY);
    else
        return (_IP_TYPE_NON_MULTI);
}

/***********************************************************************************************************************
* Function Name: _ip_check_broadcast
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
uint8_t _ip_check_broadcast(uint8_t *ipaddr)
{
    uint32_t addr;
    uint32_t myipaddr;
    uint32_t subnet_mask;
    uint32_t broad_cast_addr = 0xffffffff;

    net2hl_yn_xn(&addr, ipaddr);
    net2hl_yn_xn(&subnet_mask, tcpudp_env[_ch_info_tbl->_ch_num].maskaddr);
    net2hl_yn_xn(&myipaddr, tcpudp_env[_ch_info_tbl->_ch_num].ipaddr);

    if (addr == 0xffffffff)     // 255.255.255.255 (Broadcast)
        return (_IP_TYPE_BROADCAST);
    else if ((addr & ~subnet_mask) == (broad_cast_addr & ~subnet_mask))   // (Directed Broadcast)
    {
        if ((addr & subnet_mask) == (myipaddr & subnet_mask))
        {
            return (_IP_TYPE_DIRECTED_BROADCAST);
        }
        else
        {
            return (_IP_TYPE_NON_BROAD);
        }
    }
    else
        return (_IP_TYPE_NON_BROAD);
}
#endif

#if 0
uint16_t _cksum(const uint8_t *data, uint16_t nbytes, uint16_t sum0)
{
	uint16_t sum = sum0;
	while(nbytes > 0) {
		sum += *data++;
		nbytes--;
	}
	return sum ^ 0xffff;
}
#endif
