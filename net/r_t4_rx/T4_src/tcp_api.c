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
* Copyright (C) 2014-2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : tcp_api.c
* Version      : 1.01
* Description  : Processing for TCP API
* Website      : https://www.renesas.com/mw/t4
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.04.2014 1.00    First Release
*         : 30.11.2016 1.01    add DHCP relation
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "t4define.h"
#if defined(__GNUC__)
#include "r_tcpip_private.h"
#endif /* #if defined(__GNUC__) */
#include "type.h"
#include "r_t4_itcpip.h"
#if defined(_ETHER)
#include "ether.h"
#elif defined(_PPP)
#include "ppp.h"
#endif
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "dhcp.h"
#include "ether.h"
#include "dhcp.h"

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

extern _TCB   *_tcp_tcb;
extern _TCB   *head_tcb;
extern UH   _tcp_timer_cnt;
extern UH   _tcp_pre_timer_cnt;

#if defined(_ETHER)
_ARP_ENTRY   **_ether_arp_tbl;
#endif
#if defined(_PPP)
extern uint16 ppp_sio_status;
extern _PPP_API_REQ _ppp_api_req;
#endif

ER tcpudp_reset_sub(UB channel);

/***********************************************************************************************************************
* Function Name: tcpudp_open
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER tcpudp_open(UW *workp)
{
    UW *currp;
    UH rem;
    UB counter;
    T_UDP_CCEP* pt_udpccep;
    dhcp_inf_t* pt_dhcp_inf;

    currp = workp;

    _tcp_timer_cnt = 0;
    _tcp_pre_timer_cnt = 0;

    _tcp_tcb = (_TCB*)currp;
    head_tcb = (_TCB*)currp;
    currp = (UW*)((uchar*)currp + (sizeof(_TCB) * __tcpcepn));

#if defined(_TCP)
    for (counter = 0; counter < __tcpcepn; counter++)
    {
        _tcp_tcb[counter].rwin = (uchar*)currp;

        currp = (UW *)((uchar *)currp + tcp_ccep[counter].rbufsz);
        rem = tcp_ccep[counter].rbufsz % 4;
        if (rem != 0)
        {
            currp = (UW *)((uchar *)currp + (4 - rem));
        } /*2669*/
    }
#endif

#if defined(_UDP)
    _udp_init(&currp);
#endif

    if (1 == _t4_dhcp_enable)
    {
        pt_udpccep = (T_UDP_CCEP*)currp;                                            /* partation head */
        currp = (UW*)((uchar*)currp + (sizeof(T_UDP_CCEP) * _t4_channel_num));      /* keep partation DHCP */

        pt_dhcp_inf = (dhcp_inf_t*)currp;                                           /* partation head */
        currp = (UW*)((uchar*)currp + (sizeof(dhcp_inf_t) * _t4_channel_num));      /* keep partation DHCP */
    }

    _ch_info_tbl = (_CH_INFO*)currp;
    _ch_info_head = (_CH_INFO*)currp;
    for (counter = 0;counter < _t4_channel_num; counter++)
    {
        _ch_info_head[counter].etherlink = 0;
        if (1 == _t4_dhcp_enable)
        {
            _ch_info_head[counter].pt_udp_dhcp_ccep = (pt_udpccep + counter);
            _ch_info_head[counter].pt_dhcp_inf = (pt_dhcp_inf + counter);
        }
    }
    currp = (UW*)((uchar*)currp + (sizeof(_CH_INFO) * _t4_channel_num));

#if defined(_PPP)
    ppp_sio_status    = 0;
    memset(&_ppp_api_req, 0, sizeof(_ppp_api_req));
    _ppp_init();

#elif defined(_ETHER)
    _ether_arp_tbl = (_ARP_ENTRY **)currp;

    currp = (UW *)((uchar *)currp + _t4_channel_num * sizeof(_ARP_ENTRY *));

    for (counter = 0; counter < _t4_channel_num; counter++)
    {
        *(_ether_arp_tbl + counter) = ((_ARP_ENTRY *)currp);
        currp = (UW *)((uchar *)currp + _ip_tblcnt[counter] * sizeof(_ARP_ENTRY));
    }
#endif
    for (counter = 0; counter < _t4_channel_num; counter++)
    {
        tcpudp_reset_sub(counter);
    }
///    register_callback_linklayer(callback_tcpip);
    tcpudp_act_cyc(1);
    for (counter = 0; counter < _t4_channel_num; counter++)
    {
        _ch_info_head[counter].etherlink = lan_check_link(counter);
    }
    return (E_OK);
}

/***********************************************************************************************************************
* Function Name: tcpudp_close
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER tcpudp_close(void)
{
    tcpudp_act_cyc(0);
///    register_callback_linklayer(0);
    return (E_OK);
}

/***********************************************************************************************************************
* Function Name: _getRAMsize_sub
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
static void _getRAMsize_sub(W *ramsize)
{
    W   tmp;

    tmp = *ramsize & 0x3;
    if (tmp != 0)
    {
        *ramsize += (4 - tmp);
    } /*2669*/
    return;
}

#if defined(_TCP)
/***********************************************************************************************************************
* Function Name: _getTcpRAMsize
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
static W _getTcpRAMsize(void)
{
    W   ramsize = 0;
    UB   counter;

    for (counter = 0; counter < __tcpcepn; counter++)
    {
        ramsize += tcp_ccep[counter].rbufsz;
        ramsize += 4 - (tcp_ccep[counter].rbufsz % 4);
    }
    _getRAMsize_sub(&ramsize);

    ramsize += (sizeof(_TCB) * __tcpcepn);

    _getRAMsize_sub(&ramsize);

    return ramsize;
}
#endif

#if defined(_UDP)
/***********************************************************************************************************************
* Function Name: _getUdpRAMsize
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
static W _getUdpRAMsize(void)
{
    W ramsize = 0;

    ramsize += (sizeof(_UDP_CB) * __udpcepn);
    if (1 == _t4_dhcp_enable)
    {
        ramsize += (sizeof(_UDP_CB) * _t4_channel_num);
    }
    return ramsize;
}
#endif


/***********************************************************************************************************************
* Function Name: _getIpRAMsize
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
static W _getIpRAMsize(void)
{
    W   ramsize;

    ramsize = 0;

    ramsize += (_t4_channel_num * sizeof(_CH_INFO));

    return ramsize;
}


#if defined(_ETHER)
/***********************************************************************************************************************
* Function Name: _getTblRAMsize
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
static W _getTblRAMsize(void)
{
    W   ramsize;
    UH   count;

    ramsize = 0;
    ramsize += _t4_channel_num * sizeof(_ARP_ENTRY *);
    for (count = 0;count < _t4_channel_num; count++)
    {
        ramsize += (_ip_tblcnt[count] * sizeof(_ARP_ENTRY));
    }
    _getRAMsize_sub(&ramsize);

    return ramsize;
}
#endif


/***********************************************************************************************************************
* Function Name: tcpudp_get_ramsize
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
W tcpudp_get_ramsize(void)
{
    W   ramsize;

    ramsize = 0;
#if defined(_TCP)
    ramsize += _getTcpRAMsize();
#endif
#if defined(_UDP)
    ramsize += _getUdpRAMsize();
#endif

    ramsize += _getIpRAMsize();

#if defined(_ETHER)
    ramsize += _getTblRAMsize();
#endif

    if (1 == _t4_dhcp_enable)
    {
        ramsize += (sizeof(T_UDP_CCEP) * _t4_channel_num);
        ramsize += (sizeof(dhcp_inf_t) * _t4_channel_num);
    }

    return ramsize;
}

#if defined(_TCP)
/***********************************************************************************************************************
* Function Name: tcp_acp_cep
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER tcp_acp_cep(ID cepid, ID repid, T_IPVxEP *p_dstaddr, TMO tmout)
{
    ER err;
    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    if ((repid <= 0) || (repid > __tcprepn))
    {
        return E_PAR;
    }

    if (1 == _ch_info_head[(tcp_ccep[cepid-1].cepatr)].ip_terminated_flag)
    {
        return E_SYS;
    }

    err = _tcp_check_tmout_arg(_TCP_API_ACPCP, tmout, pTcbCb);
    if (err != E_OK && err != E_WBLK)
    {
        return err;
    }

    if (_tcp_is_tcb_queue_over(_TCP_API_ACPCP, &head_tcb[cepid-1], pTcbCb))
    {
        return E_QOVR;
    }

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_SET_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    dis_int();
    head_tcb[cepid-1].req.type = _TCP_API_ACPCP;
    head_tcb[cepid-1].req.tmout = tmout;
    head_tcb[cepid-1].req.d.cnr.dstaddr = p_dstaddr;
    head_tcb[cepid-1].req.d.cnr.repid = repid;
    head_tcb[cepid-1].req.stat = _TCP_API_STAT_UNTREATED;
    head_tcb[cepid-1].req.flag = 0;
    *head_tcb[cepid-1].req.error = E_INI;
    ena_int();                                                      /*  #3577 */

    err = _tcp_api_req(cepid);

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    return err;
}


/***********************************************************************************************************************
* Function Name: tcp_con_cep
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER tcp_con_cep(ID cepid, T_IPVxEP *p_myaddr, T_IPVxEP *p_dstaddr, TMO tmout)
{
    ER err;
    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    if (1 == _ch_info_head[(tcp_ccep[cepid-1].cepatr)].ip_terminated_flag)
    {
        return E_SYS;
    }

    err = _tcp_check_tmout_arg(_TCP_API_CONCP, tmout, GET_TCP_CALLBACK_INFO_PTR(cepid));
    if (err != E_OK && err != E_WBLK)
    {
        return err;
    }

    if (_tcp_is_tcb_queue_over(_TCP_API_CONCP, &head_tcb[cepid-1], pTcbCb))
    {
        return E_QOVR;
    }

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_SET_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    dis_int();
    head_tcb[cepid-1].req.type = _TCP_API_CONCP;
    head_tcb[cepid-1].req.tmout = tmout;
    head_tcb[cepid-1].req.d.cnr.dstaddr = p_dstaddr;
    head_tcb[cepid-1].req.stat = _TCP_API_STAT_UNTREATED;
    head_tcb[cepid-1].req.flag = 0;
    *head_tcb[cepid-1].req.error = E_INI;

    if ((p_myaddr == (T_IPVxEP *)NADR) || (p_myaddr->portno == TCP_PORTANY))
    {
        head_tcb[cepid-1].req.d.cnr.my_port = 0;
    } /*2669*/
    else
    {
        head_tcb[cepid-1].req.d.cnr.my_port = p_myaddr->portno;
    } /*2669*/
    ena_int();                                                      /*  #3577 */
    err = _tcp_api_req(cepid);

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    return err;
}


/***********************************************************************************************************************
* Function Name: tcp_sht_cep
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER tcp_sht_cep(ID cepid)
{
    ER err;

    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    if (1 == _ch_info_head[(tcp_ccep[cepid-1].cepatr)].ip_terminated_flag)
    {
        return E_SYS;
    }

    if (_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
    {
        return E_NOSPT;
    }

    if (_tcp_is_tcb_queue_over(_TCP_API_SHTCP, &head_tcb[cepid-1], pTcbCb))
    {
        return E_QOVR;
    }

    dis_int();
    head_tcb[cepid-1].req.type = _TCP_API_SHTCP;
    head_tcb[cepid-1].req.tmout = TMO_FEVR;
    head_tcb[cepid-1].req.stat = _TCP_API_STAT_UNTREATED;
    head_tcb[cepid-1].req.flag = 0;
    *head_tcb[cepid-1].req.error = E_INI;
    ena_int();                                                      /*  #3577 */

    if (_TCP_CB_GET_CALLBACK_FUNC_PTR(cepid))
    {
        head_tcb[cepid-1].req.tmout = TMO_NBLK;
    }
    err = _tcp_api_req(cepid);

    return err;
}

/***********************************************************************************************************************
* Function Name: tcp_cls_cep
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER tcp_cls_cep(ID cepid, TMO tmout)
{
    ER   err;
    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    if (1 == _ch_info_head[(tcp_ccep[cepid-1].cepatr)].ip_terminated_flag)
    {
        return E_SYS;
    }

    err = _tcp_check_tmout_arg(_TCP_API_CLSCP, tmout, pTcbCb);
    if (err != E_OK && err != E_WBLK)
    {
        return err;
    }

    if (_tcp_is_tcb_queue_over(_TCP_API_CLSCP, &head_tcb[cepid-1], pTcbCb))
    {
        return E_QOVR;
    }

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_SET_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    dis_int();
    head_tcb[cepid-1].req.type = _TCP_API_CLSCP;
    head_tcb[cepid-1].req.tmout = tmout;
    head_tcb[cepid-1].req.stat = _TCP_API_STAT_UNTREATED;
    head_tcb[cepid-1].req.flag = 0;
    *head_tcb[cepid-1].req.error = E_INI;
    ena_int();                                                      /*  #3577 */

    err = _tcp_api_req(cepid);

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    return err;
}


/***********************************************************************************************************************
* Function Name: tcp_snd_dat
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER tcp_snd_dat(ID cepid, VP data, INT len, TMO tmout)
{
    ER err;
    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    if (1 == _ch_info_head[(tcp_ccep[cepid-1].cepatr)].ip_terminated_flag)
    {
        return E_SYS;
    }

    err = _tcp_check_len_arg(len);
    if (err != E_OK)
    {
        return E_PAR;
    }


    err = _tcp_check_tmout_arg(_TCP_API_SNDDT, tmout, GET_TCP_CALLBACK_INFO_PTR(cepid));
    if (err != E_OK && err != E_WBLK)
    {
        return err;
    }

    if (_tcp_is_tcb_queue_over(_TCP_API_SNDDT, &head_tcb[cepid-1], pTcbCb))
    {
        return E_QOVR;
    }
    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_SET_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    dis_int();
    head_tcb[cepid-1].req.type = _TCP_API_SNDDT;
    head_tcb[cepid-1].req.tmout = tmout;
    head_tcb[cepid-1].req.d.dr.dtsiz = len;
    head_tcb[cepid-1].req.d.dr.datap = (uchar *)data;
    head_tcb[cepid-1].req.stat = _TCP_API_STAT_UNTREATED;
    head_tcb[cepid-1].req.flag = 0;
    *head_tcb[cepid-1].req.error = E_INI;
    ena_int();                                                      /*  #3577 */

    err = _tcp_api_req(cepid);

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    return err;
}

/***********************************************************************************************************************
* Function Name: tcp_rcv_dat
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER tcp_rcv_dat(ID cepid, VP data, INT len, TMO tmout)
{
    ER err;
    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    if (1 == _ch_info_head[(tcp_ccep[cepid-1].cepatr)].ip_terminated_flag)
    {
        return E_SYS;
    }

    err = _tcp_check_len_arg(len);
    if (err != E_OK)
    {
        return E_PAR;
    }

    err = _tcp_check_tmout_arg(_TCP_API_RCVDT, tmout, GET_TCP_CALLBACK_INFO_PTR(cepid));
    if (err != E_OK && err != E_WBLK)
    {
        return err;
    }

    if (_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat) && tmout == TMO_POL)
    {
        if ((head_tcb[cepid-1].status & (_TCPS_LISTEN | _TCPS_SYN_SENT | _TCPS_SYN_RECEIVED))
                || ((head_tcb[cepid-1].status == _TCPS_CLOSED) && (head_tcb[cepid-1].it_stat == _ITS_NORMAL)))
        {
            return E_OBJ;
        }

        if (head_tcb[cepid-1].rdsize > 0)
        {
            err = _tcp_recv_polling(&head_tcb[cepid-1], (uchar*)data, len);
            return err;
        }
        else
        {
            if (head_tcb[cepid-1].flag & _TCBF_FIN_RCVD)
            {
                return 0;
            }
            return E_TMOUT;
        }
    }

    if (_tcp_is_tcb_queue_over(_TCP_API_RCVDT, &head_tcb[cepid-1], pTcbCb))
    {
        return E_QOVR;
    }

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_SET_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    dis_int();
    head_tcb[cepid-1].req.type = _TCP_API_RCVDT;
    head_tcb[cepid-1].req.tmout = tmout;
    head_tcb[cepid-1].req.d.dr.dtsiz = len;
    head_tcb[cepid-1].req.d.dr.datap = (uchar *)data;
    head_tcb[cepid-1].req.stat = _TCP_API_STAT_UNTREATED;
    head_tcb[cepid-1].req.flag = 0;
    *head_tcb[cepid-1].req.error = E_INI;
    ena_int();                                                      /*  #3577 */

    err = _tcp_api_req(cepid);

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
        }
    }
    return err;
}

/***********************************************************************************************************************
* Function Name: tcp_can_cep
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER tcp_can_cep(ID cepid, FN fncd)
{
    ER err;
    FN fn;

    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    if (1 == _ch_info_head[(tcp_ccep[cepid-1].cepatr)].ip_terminated_flag)
    {
        return E_SYS;
    }

    if (_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
    {
        return E_NOSPT;
    }

    if (fncd == TFN_TCP_SHT_CEP)
    {
        return E_PAR;
    }

    dis_int();

    err = E_OBJ;

    if (head_tcb[cepid-1].req.stat != _TCP_API_STAT_INIT && head_tcb[cepid-1].req.stat != _TCP_API_STAT_COMPLETE)
    {
        fn = _tcp_api_type_to_fn(head_tcb[cepid -1].req.type);
        if ((fn == fncd) || (fncd == TFN_TCP_ALL))
        {
            if (TFN_TCP_SHT_CEP != fn)
            {
                if (head_tcb[cepid-1].req.tmout == TMO_NBLK)
                {
                    head_tcb[cepid-1].req.flag = _TCP_API_FLAG_CANCELED;
                    err = E_OK;
                }
            }
        }
    }

    ena_int();

    return err;
}


/***********************************************************************************************************************
* Function Name: _tcp_api_req
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER _tcp_api_req(ID cepid)
{
    if (head_tcb[cepid-1].req.tmout == TMO_NBLK)
    {
        return E_WBLK;
    }
    _tcp_api_slp(cepid);
    dis_int();
    _tcp_clr_req(cepid);
    ena_int();
    if (1 == (_ch_info_head[tcp_ccep[cepid-1].cepatr].ip_terminated_flag))
    {
        *head_tcb[cepid-1].req.error = E_SYS;
    }
    return *head_tcb[cepid-1].req.error;
}


/***********************************************************************************************************************
* Function Name: _tcp_api_slp
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_api_slp(ID cepid)
{
    do
    {
        tcp_api_slp(cepid);
    }
    while (head_tcb[cepid-1].req.stat != _TCP_API_STAT_COMPLETE);
    return;
}


/***********************************************************************************************************************
* Function Name: _tcp_clr_req
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_clr_req(ID cepid)
{
    head_tcb[cepid-1].req.type = 0;
    head_tcb[cepid-1].req.stat = _TCP_API_STAT_INIT;
    head_tcb[cepid-1].req.tmout = 0;
    head_tcb[cepid-1].req.d.dr.dtsiz = 0;
    head_tcb[cepid-1].req.d.dr.datap = NULL;
    head_tcb[cepid-1].req.flag = 0;
    return;
}


#if defined(_TEST_LIBRARY)

ER tcp_read_stat(ID cepid);
ER tcp_force_clr(ID cepid);
ER udp_force_clr(ID cepid);
ER tcp_set_mss(ID cepid, UH mss);

/***********************************************************************************************************************
* Function Name: tcp_read_stat
* Description  : read TCB status
* Arguments    : cepid
* Return Value : return the TCP status specified cepid
*    E_PAR invalid cepid
*    0(E_OK) closed
*    1  listen
*    2  established
*    3  fin_wait2
*    4  close_wait
*    5  syn_sent
*    6  syn_received
*    7  fin_wait1
*    8  last_ack
*    9  closing
*    10  time_wait
*    11  others
***********************************************************************************************************************/
ER tcp_read_stat(ID cepid)
{
    ER err = E_INI;

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    switch (head_tcb[cepid-1].status)
    {
        case _TCPS_CLOSED:
            err = 0;
            break;
        case _TCPS_LISTEN:
            err = 1;
            break;
        case _TCPS_ESTABLISHED:
            err = 2;
            break;
        case _TCPS_FIN_WAIT2:
            err = 3;
            break;
        case _TCPS_CLOSE_WAIT:
            err = 4;
            break;
        case _TCPS_SYN_SENT:
            err = 5;
            break;
        case _TCPS_SYN_RECEIVED:
            err = 6;
            break;
        case _TCPS_FIN_WAIT1:
            err = 7;
            break;
        case _TCPS_LAST_ACK:
            err = 8;
            break;
        case _TCPS_CLOSING:
            err = 9;
            break;
        case _TCPS_TIME_WAIT:
            err = 10;
            break;
        default:
            err = 11;
            break;
    }
    return err;
}

extern void _tcp_init_tcb(_TCB *_ptcb);

/***********************************************************************************************************************
* Function Name: tcp_force_clr
* Description  : force break TCP TMO_FEVR loop
* Arguments    : cepid
* Return Value : E_OK force clear OK
*       : E_PAR invalid cepid
***********************************************************************************************************************/
ER tcp_force_clr(ID cepid)
{
    ER err = E_PAR;

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    if (head_tcb[cepid-1].req.tmout == TMO_FEVR)
    {
        _tcp_init_tcb((_TCB*)&head_tcb[cepid-1]);
        head_tcb[cepid-1].req.stat = _TCP_API_STAT_COMPLETE;
        err = E_OK;
    }

    return err;
}

extern _UDP_CB  *_udp_cb;

/***********************************************************************************************************************
* Function Name: udp_force_clr
* Description  : force break UDP TMO_FEVR loop
* Arguments    : cepid
* Return Value : E_OK force clear OK
*       : E_PAR invalid cepid
***********************************************************************************************************************/
ER udp_force_clr(ID cepid)
{
    ER err = E_PAR;
    _UDP_CB      *pucb;
    _UDP_API_REQ *pureq;

    err = _udp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    pucb  = &_udp_cb[cepid-1];
    pureq = &pucb->req;

    if (pureq->tmout == TMO_FEVR)
    {
        memset(pucb, 0, sizeof(_UDP_CB));
        pureq->stat = _UDP_API_STAT_COMPLETE;
    }

    return err;
}

/***********************************************************************************************************************
* Function Name: tcp_set_mss
* Description  : MSS setting function
* Arguments    : cepid
* Return Value : E_OK setting OK
*       : E_PAR invalid cepid
***********************************************************************************************************************/
ER tcp_set_mss(ID cepid, UH mss)
{
    ER err = E_PAR;

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    head_tcb[cepid-1].mss = mss;

    return err;
}
#endif
#endif

/***********************************************************************************************************************
* Function Name: tcpudp_reset
* Description  : T4-interface mono channel reset function wrapper(User public API)
* Arguments    : channel
*                  RJ45 interface,other
* Return Value : E_OK fixed
***********************************************************************************************************************/
ER tcpudp_reset(UB channel)
{
    dis_int();
    tcpudp_reset_sub(channel);
    ena_int();
    return (E_OK);
}

/***********************************************************************************************************************
* Function Name: tcpudp_reset_sub
* Description  : T4-interface mono channel reset function body(internal API)
* Arguments    : channel
*                  RJ45 interface,other
* Return Value : E_OK fixed
***********************************************************************************************************************/
ER tcpudp_reset_sub(UB channel)
{
    UB counter;
    _ARP_ENTRY *ae;

#if defined(_TCP)
    for (counter = 0; counter < __tcpcepn; counter++)
    {
        if (channel == tcp_ccep[counter].cepatr)
        {
            uchar *rwin = head_tcb[counter].rwin;
            memset(&head_tcb[counter], 0, sizeof(_TCB));
            head_tcb[counter].rwin = rwin;
            _tcp_clr_req(counter + 1);
            _tcp_init_callback_info(&head_tcb[counter].callback_info);
            head_tcb[counter].cepid = counter + 1;
            _tcp_init_tcb(&head_tcb[counter]);
            head_tcb[counter].req.error = &head_tcb[counter].callback_info.req.ercd;     /* #3577 */
        }
    }
#endif

#if defined(_UDP)
    for (counter = 0; counter < __udpcepn; counter++)
    {
        if (channel == (udp_ccep[((_udp_cb+counter)->req.cepid)].cepatr))
        {
            memset((_udp_cb + counter), 0, (sizeof(_UDP_CB)));
        }
    }
    for (counter = 0; counter < _t4_channel_num; counter++)
    {
        if (channel == counter)
        {
            memset((_udp_cb + __udpcepn + counter), 0, (sizeof(_UDP_CB)));
        }
    }
#endif

    if (1 == _t4_dhcp_enable)
    {
        for (counter = 0; counter < _t4_channel_num; counter++)
        {
            if (channel == counter)
            {
                memset((_ch_info_head[counter].pt_dhcp_inf), 0, sizeof(dhcp_inf_t));
            }
        }
    }

    for (counter = 0;counter < _t4_channel_num; counter++)
    {
        if (channel == counter)
        {
            _ch_info_head[counter]._ch_num = counter;
            _ch_info_head[counter].flag = 0;
            _ch_info_head[counter]._rcvd = 0;
            if (1 == _t4_dhcp_enable)
            {
                _ch_info_head[counter].ip_terminated_flag = 0u;
                _ch_info_head[counter].pt_udp_dhcp_ccep->cepatr = counter;
                _ch_info_head[counter].pt_udp_dhcp_ccep->myaddr.ipaddr = 0u;
                _ch_info_head[counter].pt_udp_dhcp_ccep->myaddr.portno = DHCP_CLIENT_PORT;
                _ch_info_head[counter].pt_udp_dhcp_ccep->callback = dhcp_callback_from_t4;
                memset(_ch_info_head[counter]._myipaddr, 0, IP_ALEN);
                memset(_ch_info_head[counter]._mymaskaddr, 0, IP_ALEN);
                memset(_ch_info_head[counter]._mygwaddr, 0, IP_ALEN);
            }
            else
            {
                memcpy(_ch_info_head[counter]._myipaddr, tcpudp_env[counter].ipaddr, IP_ALEN);
                memcpy(_ch_info_head[counter]._mymaskaddr, tcpudp_env[counter].maskaddr, IP_ALEN);
                memcpy(_ch_info_head[counter]._mygwaddr, tcpudp_env[counter].gwaddr, IP_ALEN);
            }
            memset(&_ch_info_head[counter]._p_rcv_buf, 0, sizeof(_P_RCV_BUF));

        }
    }

#if defined(_PPP)
    ppp_sio_status    = 0;
    memset(&_ppp_api_req, 0, sizeof(_ppp_api_req));
    _ppp_init();

#elif defined(_ETHER)
    /* table clear for all channels */
    for (counter = 0; counter < _t4_channel_num; counter++)
    {
        if (channel == counter)
        {
            ae = _ether_arp_tbl[counter];
            memset(ae->ae_pra, 0, (sizeof(_ARP_ENTRY) * _ip_tblcnt[counter]));
        }
    }
#endif
    return (E_OK);
}
