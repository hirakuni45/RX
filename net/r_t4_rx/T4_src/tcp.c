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
* File Name    : tcp.c
* Version      : 1.01
* Description  : Processing for TCP protocol
* Website      : https://www.renesas.com/mw/t4
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.04.2014 1.00    First Release
*         : 05.12.2016 1.01    add DHCP relation
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "r_tcpip_private.h"
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

#if defined(_IGMP)
#include "igmp.h"
#endif
#include "dhcp.h"

#include "global.h"
#include "r_t4_rx/src/config_tcpudp.h"

extern void get_random_number(UB *data, UW len);

void dump_tcb(const _TCB *ptr);
void dump_ip(const char *head, const uint8_t *ip);

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

#if defined(_TCP)
extern UB *data_link_buf_ptr;
#endif

extern _UDP_CB  *_udp_cb;

extern _CH_INFO *_ch_info_tbl;
extern _CH_INFO *_ch_info_head;

/***********************************************************************************************************************
* Function Name: net2hl_yn_xn
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
#if BIGENDIAN == 0  /* little endian */
void net2hl_yn_xn(void *y, void *x)
{
    register uchar *a1 = (uchar *)y;
    register uchar *a0 = (uchar *)x;

    *((uchar*)a1 + 3) = *((uchar*)a0);
    *((uchar*)a1 + 2) = *((uchar*)a0 + 1);
    *((uchar*)a1 + 1) = *((uchar*)a0 + 2);
    *((uchar*)a1) = *((uchar*)a0 + 3);
}
#endif

#if BIGENDIAN == 1  /* big endian */
void net2hl_yn_xn(void *y, void *x)
{
    register uchar *a1 = (uchar *)y;
    register uchar *a0 = (uchar *)x;

    *((uchar*)a1) = *((uchar*)a0);
    *((uchar*)a1 + 1) = *((uchar*)a0 + 1);
    *((uchar*)a1 + 2) = *((uchar*)a0 + 2);
    *((uchar*)a1 + 3) = *((uchar*)a0 + 3);
}
#endif

/***********************************************************************************************************************
* Function Name: _tcp_init_tcb
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_init_tcb(_TCB *_ptcb)
{
    uint16 i;
    uint8_t ch;

    ch = tcp_ccep[_ptcb->cepid-1].cepatr;

    _ptcb->flag  = 0;
#if defined(_TCP)
    _ptcb->status  = _TCPS_CLOSED;
    _ptcb->nxt_status = _TCPS_CLOSED;
    _ptcb->it_stat = _ITS_NORMAL;
    _ptcb->hdr_flg = 0;
    _ptcb->mss  = _tcp_mss[ch];
    do
    {
        get_random_number((UB*)&(_ptcb->tcp_initial_seqno), sizeof((_ptcb->tcp_initial_seqno)));
    }
    while (_ptcb->tcp_initial_seqno == 0);
    _ptcb->suna  = _ptcb->tcp_initial_seqno;
    _ptcb->snxt  = _ptcb->tcp_initial_seqno;
    _ptcb->risn  = 0;
    _ptcb->rnxt  = 0;
    for (i = 0; i < 4; i++)
    {
        _ptcb->rem_ip[i] = 0;
    } /*2669*/
    _ptcb->rem_port = 0;
    _ptcb->loc_port = 0;
    _ptcb->rtchk_cnt = 0;
    _tcp_clr_rtq(_ptcb);
    _ptcb->nxtdat  = NULL;
    _ptcb->rwin_bnry = _ptcb->rwin;
    _ptcb->rwin_curr = _ptcb->rwin;
    _ptcb->swsize  = 0;
    _ptcb->rmt_rwsize = 0;
    _ptcb->sdsize  = 0;
    _ptcb->rdsize  = 0;
    _ptcb->mslcnt  = 0;
    _ptcb->zwin_int = _TCP_RTO_INIT;
    _ptcb->nxt_zero = 0xffff;
    _ptcb->zwp_noack_cnt = 0xffff;
#endif

    return;
}

/***********************************************************************************************************************
* Function Name: _process_tcpip
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _process_tcpip(void)
{
    UH counter = 0;
    volatile static UB _process_flag = 0;
    static UH _old_time;
    UH endpoint;
    uint32_t cnt;
    uint32_t channel;

    if (_process_flag == 0)
    {
        _process_flag = 1;
        _tcp_timer_cnt = get_tcpudp_time();

        if ( _old_time != _tcp_timer_cnt)
        {
#if defined(_IGMP)
            int_send_igmp_timer_expired(_tcp_timer_cnt);
#endif
            if (1 == _t4_dhcp_enable)
            {
                dhcp_int_timer();
            }
            _old_time = _tcp_timer_cnt;
        }

        while (1)
        {
            if (1 == _t4_dhcp_enable)
            {
                dhcp_process();
            }
#if defined(_PPP)
            _ppp_proc();

#endif
            _proc_api();
            _proc_rcv();
            if (1 == _t4_dhcp_enable)
            {
                for (cnt = 0; cnt < __tcpcepn; cnt++)
                {
                    channel = tcp_ccep[cnt].cepatr;
                    if (1 == (_ch_info_head[channel].ip_terminated_flag))
                    {
                        if (((head_tcb[cnt].req.tmout) == TMO_FEVR))
                        {
                            _tcp_tcb = &head_tcb[cnt];
                            _tcp_api_wup(head_tcb[cnt].cepid);
                        }
                    }
                }
                for (cnt = 0; cnt < __udpcepn; cnt++)
                {
                    channel = udp_ccep[cnt].cepatr;
                    if (1 == (_ch_info_head[channel].ip_terminated_flag))
                    {
                        if (((_udp_cb[cnt].req.tmout) == TMO_FEVR))
                        {
                            _udp_api_wup(&_udp_cb[cnt], _udp_cb[cnt].req.cepid);
                        }
                    }
                }
            }
            _proc_snd();

#if defined(_UDP)
            if (1 == _t4_dhcp_enable)
            {
                endpoint = __udpcepn + _t4_channel_num;
            }
            else
            {
                endpoint = __udpcepn;
            }
            for (counter = 0; counter < endpoint; counter++)
            {
                if ((_udp_cb[counter].req.type != _UDP_API_NON) &&
                        (_udp_cb[counter].req.stat == _UDP_API_STAT_UNTREATED))
                {
                    continue;
                }
            }
#endif
            for (counter = 0 ; counter < _t4_channel_num ; counter++)
            {
                if ((_ch_info_head[counter]._rcvd == 1) && ((_ch_info_head[counter].flag & _TCBF_SND_ICMP) == 0))
                {
                    break;
                }
            }
            if (counter >= _t4_channel_num)
            {
                break;
            }
        }
        _process_flag = 0;
    }
    else
    {

    }

    return;
}


/***********************************************************************************************************************
* Function Name: _proc_api
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _proc_api(void)
{
#if defined(_TCP)
    _API_REQ *areq;
    UH counter = 0;
    UB canceld;

    static void (* const functbl_tcp_api[])(void) =
    {
        _tcp_api_acpt,
        _tcp_api_con,
        _tcp_api_sht_cls,
        _tcp_api_sht_cls,
        _tcp_api_snddt,
        _tcp_api_rcvdt
    };

    for (counter = 0;counter < __tcpcepn; counter++)
    {
        _tcp_tcb = &head_tcb[counter];
        _ch_info_tbl = &_ch_info_head[tcp_ccep[counter].cepatr];

        areq = &(_tcp_tcb->req);

        canceld = 0;
        if (  ((areq->stat == _TCP_API_STAT_UNTREATED) || (areq->stat == _TCP_API_STAT_INCOMPLETE)  )
                && (areq->flag & _TCP_API_FLAG_CANCELED))
        {
            _tcp_cancel_api(E_RLWAI);
            areq->flag &= (~_TCP_API_FLAG_CANCELED);
            canceld = 1;
        }

        if (areq->stat == _TCP_API_STAT_UNTREATED)
        {
            if (((areq->type) == _TCP_API_CLSCP) && (canceld == 1))
            {
                /* nothing todo */
            }
            else
            {
                areq->stat = _TCP_API_STAT_INCOMPLETE;
                functbl_tcp_api[areq->type - 1]();
            }
        }
    }
#endif

#if defined(_UDP)
    _proc_udp_api();
#endif
    return;
}


#if defined(_TCP)
/***********************************************************************************************************************
* Function Name: _tcp_api_acpt
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_api_acpt(void)
{
    _API_REQ *areq;
    areq = &(_tcp_tcb->req);

    if ((_tcp_tcb->status != _TCPS_CLOSED) || (_tcp_tcb->it_stat != _ITS_NORMAL))
    {
        *(areq->error) = E_OBJ;

        if (areq->stat != _TCP_API_STAT_COMPLETE)
        {
            if (areq->tmout == TMO_NBLK)
            {
                FN fncd;
                fncd = _tcp_api_type_to_fn(areq->type);

                _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
            }
            else
            {
                _tcp_api_wup(_tcp_tcb->cepid);
            }
        }
        return;
    }
    _tcp_tcb->loc_port = tcp_crep[areq->d.cnr.repid-1].myaddr.portno;

    _tcp_tcb->rwin_bnry = _tcp_tcb->rwin;
    _tcp_tcb->rwin_curr = _tcp_tcb->rwin;

    _tcp_tcb->status = _TCPS_LISTEN;

    return;
}


/***********************************************************************************************************************
* Function Name: _tcp_api_con
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_api_con(void)
{
    _API_REQ *areq;
    uint16_t  ui_rndm;

    areq = &(_tcp_tcb->req);

    if ((_tcp_tcb->status != _TCPS_CLOSED) || (_tcp_tcb->it_stat != _ITS_NORMAL))
    {
        *(areq->error) = E_OBJ;

        if (areq->stat != _TCP_API_STAT_COMPLETE)
        {
            if (areq->tmout == TMO_NBLK)
            {
                FN fncd;
                fncd = _tcp_api_type_to_fn(areq->type);

                _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
            }
            else
            {
                _tcp_api_wup(_tcp_tcb->cepid);
            }
        }

        return;
    }

    hl2net_yn_xn(_tcp_tcb->rem_ip, &areq->d.cnr.dstaddr->ipaddr);
    _tcp_tcb->rem_port = areq->d.cnr.dstaddr->portno;

    if (areq->d.cnr.my_port == 0)
    {
        get_random_number((UB*)&ui_rndm, sizeof(ui_rndm));
        _tcp_tcb->loc_port = (ui_rndm & 0x3FFF) + 0xC000;    /* #3370 */
    }
    else
    {
        _tcp_tcb->loc_port = areq->d.cnr.my_port;
    } /*2669*/
    _tcp_tcb->hdr_flg = _TCPF_SYN;
    _tcp_tcb->nxt_status = _TCPS_SYN_SENT;
    _tcp_tcb->flag  |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);

    return;
}


/***********************************************************************************************************************
* Function Name: _tcp_api_sht_cls
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_api_sht_cls(void)
{
    _API_REQ *areq;
    areq = &(_tcp_tcb->req);

    /* If RST has already been received */
    if ((_tcp_tcb->it_stat == _ITS_RST) || (_tcp_tcb->it_stat == _ITS_SHT))
    {
        switch (areq->type)
        {
                /* If this msg is from 'tcp_cls_cep()' */
            case _TCP_API_CLSCP :
                if (_tcp_tcb->status != _TCPS_CLOSED)
                {
                    return;
                } /*2669*/
                else
                {
                    *(areq->error) = E_OK ;
                    _tcp_init_tcb(_tcp_tcb) ;
                    break ;
                }
            case _TCP_API_SHTCP :
                *(areq->error) = E_OBJ ;
                break;
            default :
                break; /*2670*/
        }

        if (areq->stat != _TCP_API_STAT_COMPLETE)
        {
            if (areq->tmout == TMO_NBLK)
            {
                FN fncd;
                fncd = _tcp_api_type_to_fn(areq->type);

                _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
            }
            else
            {
                _tcp_api_wup(_tcp_tcb->cepid);
            }
        }
        return;
    }

    switch (_tcp_tcb->status)
    {
            /* Allowed Status */
        case _TCPS_ESTABLISHED :
            if (_tcp_tcb->nxt_status == _TCPS_CLOSE_WAIT)
            {
                _tcp_tcb->nxt_status = _TCPS_LAST_ACK;
            } /*2669*/
            else
            {
                _tcp_tcb->nxt_status = _TCPS_FIN_WAIT1;
            } /*2669*/
            break ;
        case _TCPS_CLOSE_WAIT :
            _tcp_tcb->nxt_status = _TCPS_LAST_ACK;
            break ;
        case _TCPS_CLOSED :
            *(areq->error) = E_OBJ ;

            if (areq->stat != _TCP_API_STAT_COMPLETE)
            {
                if (areq->tmout == TMO_NBLK)
                {
                    FN fncd;
                    fncd = _tcp_api_type_to_fn(areq->type);

                    _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
                }
                else
                {
                    _tcp_api_wup(_tcp_tcb->cepid);
                }
            }
            return;
        default :
            return ;
    }

    _tcp_tcb->hdr_flg = (_TCPF_FIN | _TCPF_ACK);

    _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);

    return ;
}


/***********************************************************************************************************************
* Function Name: _tcp_api_snddt
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_api_snddt(void)
{
    _API_REQ *areq;
    areq = &(_tcp_tcb->req);

    /* RST Received? */
    if (_tcp_tcb->it_stat == _ITS_RST)
    {
        *(areq->error) = E_CLS;
        goto _snddt_error;
    }

    if ((_tcp_tcb->status & (_TCPS_ESTABLISHED | _TCPS_CLOSE_WAIT)) == 0)
    {
        *(areq->error) = E_OBJ;

        if (areq->stat != _TCP_API_STAT_COMPLETE)
        {
            if (areq->tmout == TMO_NBLK)
            {
                _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, TFN_TCP_SND_DAT, _tcp_tcb);
            }
            else
            {
                _tcp_api_wup(_tcp_tcb->cepid);
            }
        }

        return;
    }
    _tcp_tcb->nxtdat = areq->d.dr.datap;
    _tcp_tcb->sdsize = areq->d.dr.dtsiz;

    _tcp_tcb->hdr_flg = _TCPF_ACK;
    _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);

    if (_tcp_dack[ tcp_ccep[ _tcp_tcb->cepid-1].cepatr ] == 1)
    {
        _tcp_tcb->flag &= ~_TCBF_AVOID_DACK;
    }

    return;

_snddt_error:
    if (areq->stat != _TCP_API_STAT_COMPLETE)
    {
        if (areq->tmout == TMO_NBLK)
        {
            _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, TFN_TCP_SND_DAT, _tcp_tcb);
        }
        else
        {
            _tcp_api_wup(_tcp_tcb->cepid);
        }
    }
    return;
}


/***********************************************************************************************************************
* Function Name: _tcp_api_rcvdt
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_api_rcvdt(void)
{
    _API_REQ *areq;

    areq = &(_tcp_tcb->req);

    if ((_tcp_tcb->status & (_TCPS_LISTEN | _TCPS_SYN_SENT | _TCPS_SYN_RECEIVED))
            || ((_tcp_tcb->status == _TCPS_CLOSED) && (_tcp_tcb->it_stat == _ITS_NORMAL)))
    {
        *(areq->error) = E_OBJ;

        if (areq->stat != _TCP_API_STAT_COMPLETE)
        {
            if (areq->tmout == TMO_NBLK)
            {
                _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, TFN_TCP_RCV_DAT, _tcp_tcb);
            }
            else
            {
                _tcp_api_wup(_tcp_tcb->cepid);
            }
        }
        return;
    }

    if (_tcp_tcb->rdsize == 0)
    {
        if (_tcp_tcb->flag & _TCBF_FIN_RCVD)
        {
            *(areq->error) = 0;

            if (areq->stat != _TCP_API_STAT_COMPLETE)
            {
                if (areq->tmout == TMO_NBLK)
                {
                    _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, TFN_TCP_RCV_DAT, _tcp_tcb);
                }
                else
                {
                    _tcp_api_wup(_tcp_tcb->cepid);
                }
            }
        }

        else if (_tcp_tcb->it_stat == _ITS_RST)
        {
            *(areq->error) = E_CLS;

            if (areq->stat != _TCP_API_STAT_COMPLETE)
            {
                if (areq->tmout == TMO_NBLK)
                {
                    _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, TFN_TCP_RCV_DAT, _tcp_tcb);
                }
                else
                {
                    _tcp_api_wup(_tcp_tcb->cepid);
                }
            }
        }
        return;
    }

    if (_tcp_tcb->rdsize > 0)
    {
        _tcp_cpy_rwdat();
    }

    return;
}


/***********************************************************************************************************************
* Function Name: _tcp_cpy_rwdat
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_cpy_rwdat(void)
{
    _API_REQ *areq;
    uint16  api_dsiz;
    uint16  free_win;

    areq = &(_tcp_tcb->req);

    api_dsiz = areq->d.dr.dtsiz;

    if (_tcp_tcb->rdsize < api_dsiz)
    {
        api_dsiz = _tcp_tcb->rdsize;
    }

    _tcp_tcb->rdsize -= api_dsiz;

    memcpy(areq->d.dr.datap, _tcp_tcb->rwin_bnry, api_dsiz);

    if (_tcp_tcb->rdsize == 0)
    {
        free_win = tcp_ccep[_tcp_tcb->cepid-1].rbufsz - (_tcp_tcb->rwin_curr - _tcp_tcb->rwin);
        if ((free_win < _tcp_tcb->mss) && (free_win < (tcp_ccep[_tcp_tcb->cepid-1].rbufsz / 2)))
        {
            _tcp_tcb->hdr_flg |= _TCPF_ACK;
            _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
        }
        _tcp_tcb->rwin_bnry = _tcp_tcb->rwin;
        _tcp_tcb->rwin_curr = _tcp_tcb->rwin;
    }
    else
    {
        _tcp_tcb->rwin_bnry += api_dsiz;
    } /*2669*/

    *(areq->error) = api_dsiz;

    if (areq->stat == _TCP_API_STAT_INCOMPLETE)
    {
        if (areq->tmout == TMO_NBLK)
        {
            _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, TFN_TCP_RCV_DAT, _tcp_tcb);
        }
        else
        {
            _tcp_api_wup(_tcp_tcb->cepid);
        }
    }

    return;
}
#endif /* _TCP */


/***********************************************************************************************************************
* Function Name: _proc_rcv
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _proc_rcv(void)
{
    _IP_PKT *pip;
    _IP_HDR *piph;
    _ICMP_PKT *picmp;
    _ICMP_HDR *picmph;
    _TCP_HDR *ptcph;
    uint16 seg_size, sum16;

    _tcp_tcb = head_tcb;

    uint8_t ch;
    for(ch = 0; ch < _t4_channel_num; ch++) {
        _ch_info_tbl = &_ch_info_head[ch];
        _ether_proc_rcv();

        if (_ch_info_tbl->_p_rcv_buf.len == 0)
        {
            _ch_info_tbl->_rcvd = 0;
            continue;
        }
        else
        {
            _ch_info_tbl->_rcvd = 1;
        } /*2669*/

#if defined(_ETHER)
        if (_ch_info_tbl->_p_rcv_buf.ip_rcv == 0)
        {
            continue;
        }
#endif

        pip = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
        piph = (_IP_HDR *)pip;
        if ((_ip_rcv_hdr() != 0))
        {
            goto _err_proc_rcv;
        }

		uint16  counter = 0;
        switch (piph->ip_proto_num)
        {
#if defined(_TCP)
                /****** TCP ******/
            case(_IPH_TCP):
                ptcph = (_TCP_HDR *)(pip->data);
                while (counter != __tcpcepn)
                {
                    _tcp_tcb = &head_tcb[counter];
#if 0
if(ptcph->dport == hs2net(_tcp_tcb->loc_port)) {
	printf("sport: %d, rem_port: %d\n", (int)hs2net(ptcph->sport), (int)_tcp_tcb->rem_port);
	printf("ch_num: %d, cepatr: %d\n", (int)_ch_info_tbl->_ch_num, (int)tcp_ccep[counter].cepatr);
	dump_ip("rem:", _tcp_tcb->rem_ip);
	dump_ip("src:", piph->ip_src);
}
#endif
                    if ((ptcph->sport == hs2net(_tcp_tcb->rem_port))
                            && (ptcph->dport == hs2net(_tcp_tcb->loc_port))
                            && (_cmp_ipaddr(piph->ip_src, _tcp_tcb->rem_ip) == 0)
                            && (_ch_info_tbl->_ch_num == tcp_ccep[counter].cepatr)
                            && ( (_tcp_tcb->status != _TCPS_LISTEN)
                                  || ((_tcp_tcb->status == _TCPS_LISTEN) &&
                                      (_tcp_tcb->nxt_status == _TCPS_SYN_RECEIVED)))
                            && (_tcp_tcb->status != _TCPS_CLOSED))
                    {
                        break;
                    }
                    counter++;
                }
                if (counter == __tcpcepn)
                {
                    counter = 0;
                    while (counter != __tcpcepn)
                    {
                        _tcp_tcb = &head_tcb[counter];
                        if ((_tcp_tcb->status == _TCPS_LISTEN)
                                && (_tcp_tcb->nxt_status != _TCPS_SYN_RECEIVED)
                                && (_ch_info_tbl->_ch_num == tcp_ccep[counter].cepatr)
                                && (ptcph->dport == hs2net(_tcp_tcb->loc_port)))
                        {
                            break;
                        }
                        counter++;
                    }
                    if (counter == __tcpcepn)
                    {
                        report_error(_ch_info_tbl->_ch_num, RE_TCP_HEADER1, data_link_buf_ptr);
                        goto _err_proc_rcv;
                    }
                }
			    _TCP_PHDR phdr;
				_cpy_ipaddr(phdr.sadr, piph->ip_src);
				_cpy_ipaddr(phdr.dadr, piph->ip_dst);
                phdr.reserve = 0;
                phdr.prtcl = _IPH_TCP;
                seg_size = net2hs(piph->ip_total_len) - _IP_HLEN_MIN;
                phdr.len = hs2net(seg_size);
                sum16 = _cksum(&phdr, sizeof(_TCP_PHDR), 0);
                sum16 = _cksum(ptcph, seg_size, ~hs2net(sum16));
				if(sum16 != 0) {
// dump_ip("src:", phdr.sadr);
// dump_ip("dst:", phdr.dadr);
// printf("sum16 error: %d\n", (int)sum16);
                    report_error(_ch_info_tbl->_ch_num, RE_TCP_HEADER2, data_link_buf_ptr);
                    goto _err_proc_rcv;
                }

                _tcp_stat();
                if (_tcp_tcb->req.stat == _TCP_API_STAT_INCOMPLETE)
                {
                    if (((_tcp_tcb->req.type == _TCP_API_ACPCP) && (_tcp_tcb->status == _TCPS_ESTABLISHED))
                            || ((_tcp_tcb->req.type == _TCP_API_RCVDT) && (*(_tcp_tcb->req.error) != E_INI))
                            || ((_tcp_tcb->req.type == _TCP_API_SNDDT) && (_tcp_tcb->snxt == _tcp_tcb->suna)
                                && (_tcp_tcb->sdsize == 0))
                            || ((_tcp_tcb->req.type == _TCP_API_CLSCP) && (_tcp_tcb->status == _TCPS_CLOSED)))
                    {
                        if (_tcp_tcb->req.tmout == TMO_NBLK)
                        {
                            FN fncd;
                            fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);

                            _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
                        }
                        else
                        {
                            _tcp_api_wup(_tcp_tcb->cepid);
                        }
                    }
                } /*2669*/
                break;
#endif /* _TCP */
#if defined(_ICMP)
            case(_IPH_ICMP):
                picmp = (_ICMP_PKT *)(pip->data);
                picmph = (_ICMP_HDR *)picmp;
                if (picmph->type != _ICMP_ECHO_REQ)
                {
                    report_error(_ch_info_tbl->_ch_num, RE_ICMP_HEADER1, data_link_buf_ptr);
                    goto _err_proc_rcv;
                }
# if defined(_ETHER)
                _ether_arp_resolve();
# endif
                _ip_snd_icmp();
                break;
#endif /* ICMP */
#if defined(_UDP)
            case(_IPH_UDP):
                _udp_rcv(piph, (_UDP_HDR *)(((_IP_PKT*)piph)->data));
                break;
#endif

            default:
                report_error(_ch_info_tbl->_ch_num, RE_TRANSPORT_LAYER, data_link_buf_ptr);
                goto _err_proc_rcv;
        }
        continue;

_err_proc_rcv:
        rcv_buff_release(_ch_info_tbl->_ch_num);
        _ch_info_tbl->_p_rcv_buf.len = 0;
    }    /* for(ch = 0; ch < _t4_channel_num; ch++) */

    return;
}


#if defined(_TCP)
/***********************************************************************************************************************
* Function Name: _tcp_stat
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_stat(void)
{
    sint16 ret;

    ret = _tcp_rcv_opt();
    if (ret == E_ERR)
    {
        goto _tcp_stat_release;
    } /*2669*/

    ret = _tcp_rcv_rst();
    if (ret != E_NO_RCV)
    {
        goto _tcp_stat_release;
    } /*2669*/
    if (_tcp_tcb->status == _TCPS_CLOSED)
    {
        goto _tcp_stat_release;
    }

    ret = _tcp_rcv_syn();
    if ((ret == E_ERR) || ((_tcp_tcb->status == _TCPS_LISTEN) && (ret != E_SYN_OK)))
    {
        goto _tcp_stat_release;
    } /*2669*/
    if (!(_tcp_tcb->status & _TCPS_LISTEN))
    {
        _tcp_rcv_ack();
    } /*2669*/
    if (_tcp_tcb->status == _TCPS_CLOSED)
    {
        goto _tcp_stat_release;
    }

    if (_tcp_tcb->status & (_TCPS_ESTABLISHED | _TCPS_FIN_WAIT1 | _TCPS_FIN_WAIT2))
    {
        ret = _tcp_proc_data();
        if (ret == E_ERR)
        {
            goto _tcp_stat_release;
        }
    }

    _tcp_rcv_fin();

    _tcp_swin_updt();

_tcp_stat_release:
    rcv_buff_release(_ch_info_tbl->_ch_num);
    _ch_info_tbl->_p_rcv_buf.len = 0;
    return;
}


/***********************************************************************************************************************
* Function Name: _tcp_rcv_rst
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER _tcp_rcv_rst(void)
{
    _IP_PKT  *pip;
    _TCP_HDR *ph;
    _API_REQ *areq;

    areq = &(_tcp_tcb->req);
    pip = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    ph = (_TCP_HDR *)(pip->data);

    if (!(ph->flg & _TCPF_RST))
    {
        return E_NO_RCV;
    } /*2669*/
    if (areq->stat == _TCP_API_STAT_INCOMPLETE)
    {
        switch (areq->type)
        {
                /* tcp_acp_cep */
            case _TCP_API_ACPCP:
                /* SYN-RECEIVED */
                if (_tcp_tcb->status == _TCPS_SYN_RECEIVED)
                {
                    _tcp_return_listen();
                }
                return E_RST_RCV;
                /* tcp_con_cep */
            case _TCP_API_CONCP:
                _tcp_init_tcb(_tcp_tcb);
                *(areq->error) = E_CLS;

                if (areq->tmout == TMO_NBLK)
                {
                    _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, TFN_TCP_CON_CEP, _tcp_tcb);
                }
                else
                {
                    _tcp_api_wup(_tcp_tcb->cepid);
                }
                break;
                /* tcp_cls_cep */
            case _TCP_API_CLSCP:
                _tcp_init_tcb(_tcp_tcb);
                *(areq->error) = E_OK;

                if (areq->tmout == TMO_NBLK)
                {
                    _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, TFN_TCP_CLS_CEP, _tcp_tcb);
                }
                else
                {
                    _tcp_api_wup(_tcp_tcb->cepid);
                }
                break;
                /* tcp_snd_dat */
            case _TCP_API_SNDDT:
                /* _ITS_RST */
                _tcp_tcb->it_stat = _ITS_RST;
                *(areq->error) = E_CLS;

                if (areq->tmout == TMO_NBLK)
                {
                    _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, TFN_TCP_SND_DAT, _tcp_tcb);
                }
                else
                {
                    _tcp_api_wup(_tcp_tcb->cepid);
                }
                break;
                /* tcp_rcv_dat */
            case _TCP_API_RCVDT:
                /* _ITS_RST */
                _tcp_tcb->it_stat = _ITS_RST;
                if (_tcp_tcb->rdsize > 0)
                {
                    break;
                } /*2669*/
                *(areq->error) = E_CLS;

                if (areq->tmout == TMO_NBLK)
                {
                    _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, TFN_TCP_RCV_DAT, _tcp_tcb);
                }
                else
                {
                    _tcp_api_wup(_tcp_tcb->cepid);
                }
                break;
            default:
                break;
        }
    }
    else
    {
        /* _ITS_RST */
        _tcp_tcb->it_stat = _ITS_RST;
    }
    _tcp_tcb->status = _TCPS_CLOSED;
    _tcp_tcb->nxt_status = _TCPS_CLOSED;

    _tcp_clr_rtq(_tcp_tcb);

    return E_RST_RCV;
}

/***********************************************************************************************************************
* Function Name: _tcp_rcv_syn
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER _tcp_rcv_syn(void)
{
    _IP_PKT  *pip;
    _IP_HDR  *piph;
    _TCP_HDR *ph;
    uint32  tmp;

    pip  = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    piph = (_IP_HDR *)pip;
    ph  = (_TCP_HDR *)(pip->data);

    if (!(ph->flg & _TCPF_SYN))
    {
        return E_NO_RCV;
    } /*2669*/
    switch (_tcp_tcb->status)
    {
            /* LISTEN */
        case _TCPS_LISTEN:
            _cpy_ipaddr(_tcp_tcb->rem_ip, piph->ip_src);
            _tcp_tcb->rem_port = net2hs(ph->sport);
            net2hl_yn_xn(&_tcp_tcb->risn,  &ph->seq) ;
            _tcp_tcb->rnxt = _tcp_tcb->risn + 1;
            _tcp_tcb->hdr_flg = (_TCPF_SYN | _TCPF_ACK);
            _tcp_tcb->nxt_status = _TCPS_SYN_RECEIVED;
            _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
            return E_SYN_OK;
            /* SYN-SENT */
        case _TCPS_SYN_SENT:
            net2hl_yn_xn(&tmp,  &ph->ack) ;
            if ((ph->flg & (_TCPF_SYN | _TCPF_ACK)) && (tmp == _tcp_tcb->tcp_initial_seqno + 1))
            {
                net2hl_yn_xn(&_tcp_tcb->risn,  &ph->seq) ;
                _tcp_tcb->rnxt = _tcp_tcb->risn + 1;
                _tcp_tcb->nxt_status = _TCPS_ESTABLISHED;
                _tcp_tcb->hdr_flg |= _TCPF_ACK;
                _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
                return E_SYN_OK;
            }
            _tcp_tcb->flag |= _TCBF_NEED_INIT;
            break;
        default:
            net2hl_yn_xn(&tmp,  &ph->seq) ;
            if (tmp == _tcp_tcb->risn)
            {
                if (_tcp_tcb->status == _TCPS_ESTABLISHED)
                {
                    _tcp_tcb->hdr_flg = _TCPF_ACK;
                    _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
                }
                return E_SYN_OK;
            }
            break;
    }
    _tcp_tcb->hdr_flg = _TCPF_RST;
    _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
    _tcp_tcb->nxt_status = _TCPS_CLOSED;
    _tcp_tcb->it_stat = _ITS_RST;
    if (_tcp_tcb->req.stat == _TCP_API_STAT_INCOMPLETE)
    {
        switch (_tcp_tcb->req.type)
        {
            case _TCP_API_ACPCP:
                return E_ERR;
            case _TCP_API_CONCP:
            case _TCP_API_SNDDT:
            case _TCP_API_RCVDT:
                *(_tcp_tcb->req.error) = E_CLS;
                break;
            case _TCP_API_CLSCP:
                *(_tcp_tcb->req.error) = E_OK;
                break;
            default:
                break;
        }

        if (_tcp_tcb->req.tmout == TMO_NBLK)
        {
            FN fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
            _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
        }
        else
        {
            _tcp_api_wup(_tcp_tcb->cepid);
        }
    }
    return E_ERR;
}

/***********************************************************************************************************************
* Function Name: _tcp_rcv_ack
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_rcv_ack(void)
{
    _IP_PKT  *pip;
    _TCP_HDR *ph;
    uint32  tmp, ackdsz;
    uint32   suna;

    pip  = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    ph  = (_TCP_HDR *)(pip->data);
    net2hl_yn_xn(&tmp,  &ph->ack) ;

    if (!(ph->flg & _TCPF_ACK))
    {
        return;
    } /*2669*/
    if (_tcp_tcb->nxt_zero != 0xffff)
    {
        _tcp_tcb->zwp_noack_cnt = 0xffff;
    } /*2669*/
    if ((tmp > _tcp_tcb->suna) && ((tmp - _tcp_tcb->suna) < 0x7fffffff))
    {
        ackdsz = tmp - _tcp_tcb->suna;
    }
    else if ((tmp <  _tcp_tcb->suna) && ((_tcp_tcb->suna - tmp) > 0x7fffffff))
    {
        ackdsz = 0xffffffffu - _tcp_tcb->suna + tmp + 1;
    }
    else
    {
        return;
    } /*2669*/
    suna = tmp;

    if (_tcp_dack[_ch_info_tbl->_ch_num] == 1)
    {
        if ((_tcp_tcb->snxt != suna) && (_tcp_tcb->retrans_q.len == ackdsz))
        {
            _tcp_tcb->retrans_q.data    = _tcp_tcb->retrans_q2.data;
            _tcp_tcb->retrans_q.hdr_flg = _tcp_tcb->retrans_q2.hdr_flg;
            _tcp_tcb->retrans_q.len     = _tcp_tcb->retrans_q2.len;
            _tcp_tcb->retrans_q.rst_cnt = _tcp_rt_tmo_rst[_ch_info_tbl->_ch_num];
            _tcp_tcb->retrans_q.seq     = _tcp_tcb->retrans_q2.seq;
        }
        else
        {

        }
    }
    if (_tcp_tcb->snxt == suna)
    {
        uchar cur_req_stat = _tcp_tcb->req.stat;
        uchar cur_req_type = _tcp_tcb->req.type;

        _tcp_tcb->suna = suna;

        if (_tcp_dack[_ch_info_tbl->_ch_num])
        {
            _tcp_tcb->flag &= ~_TCBF_AVOID_DACK;
        }

        _tcp_clr_rtq(_tcp_tcb);


        switch (_tcp_tcb->status)
        {
            case _TCPS_SYN_RECEIVED:
                _tcp_tcb->status = _TCPS_ESTABLISHED;
                _tcp_tcb->nxt_status = _TCPS_ESTABLISHED;
                net2hl_yn_xn(&_tcp_tcb->req.d.cnr.dstaddr->ipaddr, _tcp_tcb->rem_ip);
                _tcp_tcb->req.d.cnr.dstaddr->portno = _tcp_tcb->rem_port;
                *(_tcp_tcb->req.error) = E_OK;

                if (_tcp_tcb->req.tmout == TMO_NBLK)
                {
                    FN fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
                    _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
                }
                else
                {
                    _tcp_api_wup(_tcp_tcb->cepid);
                }
                break;
            case _TCPS_FIN_WAIT1:
                if (_tcp_tcb->nxt_status == _TCPS_CLOSING)
                {
                    _tcp_tcb->nxt_status = _TCPS_TIME_WAIT;
                }
                else
                {
                    _tcp_tcb->status = _TCPS_FIN_WAIT2;
                    _tcp_tcb->nxt_status = _TCPS_FIN_WAIT2;
                }
                break;
            case _TCPS_CLOSING:
                _tcp_tcb->status = _TCPS_TIME_WAIT;
                _tcp_tcb->nxt_status = _TCPS_TIME_WAIT;
                _tcp_tcb->mslcnt = _tcp_2msl[_ch_info_tbl->_ch_num];
                break;
            case _TCPS_LAST_ACK:
                _tcp_tcb->status = _TCPS_CLOSED;
                _tcp_tcb->nxt_status = _TCPS_CLOSED;
                if ((_tcp_tcb->req.type == _TCP_API_CLSCP)
                        && (_tcp_tcb->req.stat == _TCP_API_STAT_INCOMPLETE))
                {
                    *(_tcp_tcb->req.error) = E_OK;

                    if (_tcp_tcb->req.tmout == TMO_NBLK)
                    {
                        FN fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
                        _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
                    }
                    else
                    {
                        _tcp_api_wup(_tcp_tcb->cepid);
                    }

                    _tcp_init_tcb(_tcp_tcb);
                }
                break;
            default:
                break;
        }

        if ((cur_req_type == _TCP_API_SNDDT)
                && (cur_req_stat == _TCP_API_STAT_INCOMPLETE))
        {
            if (_tcp_tcb->sdsize < ackdsz)
            {
                _tcp_tcb->sdsize = 0;
            } /*2669*/
            else
            {
                _tcp_tcb->sdsize -= ackdsz;
            } /*2669*/
            if (_tcp_tcb->sdsize == 0)
            {
                *(_tcp_tcb->req.error) = _tcp_tcb->req.d.dr.dtsiz;
            } /*2669*/
            else
            {
                _tcp_tcb->hdr_flg |= _TCPF_ACK;
                _tcp_tcb->flag  |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
            }
        }
    }


    return;
}

/***********************************************************************************************************************
* Function Name: _tcp_rcv_opt
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
sint16 _tcp_rcv_opt(void)
{
    uint16  mss;
    _IP_PKT  *pip;
    _TCP_HDR *ph;
    uint32  tmp;
    uint16  hdr_siz;
    uchar  *p, opt_len, opt_type;
    uint16  total_opt_len;

    pip  = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    ph  = (_TCP_HDR *)(pip->data);
    net2hl_yn_xn(&tmp,  &ph->ack) ;
    hdr_siz  = ((ph->len & 0xf0) >> 2);

    if (hdr_siz < 20)
    {
        return E_ERR;
    } /*2669*/
    else if (hdr_siz == 20)
    {
        return E_OK;
    } /*2669*/
    mss = 0;
    p = &(ph->opt[0]);
    total_opt_len = hdr_siz - 20;
    while (total_opt_len != 0)
    {
        opt_type = *p;

        if (opt_type == 0)
        {
            break;
        }
        if (opt_type == 1)
        {
            opt_len = 1;
        }
        else
        {
            opt_len  = *(p + 1);

            if ((total_opt_len == 1)
                    || (opt_len < 2) || (opt_len > total_opt_len))
            {
                return E_ERR;
            }
            if (opt_type == 2)
            {
                if (opt_len != 4)
                {
                    return E_ERR;
                } /*2669*/
                mss = (((uint16) * (p + 2)) << 8) | ((uint16) * (p + 3));
            }
        }
        p += opt_len;
        total_opt_len -= opt_len;
    }
    if (mss == 0)
    {
        mss = _TCP_DEFAULT_MSS;
    } /*2669*/
    if ((_tcp_tcb->status & (_TCPS_LISTEN | _TCPS_SYN_SENT)) && (mss < _tcp_tcb->mss))
    {
        _tcp_tcb->mss = mss;
    } /*2669*/
    return mss;
}


/***********************************************************************************************************************
* Function Name: _tcp_proc_data
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
sint16 _tcp_proc_data(void)
{
    uint16 hdr_siz;
    sint32 data_siz;
    sint32 free_siz;
    uint32 seq;
    uchar  *p_tdata;
    _TCPS *p_tcps ;
    _IP_PKT *p_ip;
    uint32 calc;

    p_ip = (_IP_PKT *)_ch_info_tbl->_p_rcv_buf.pip;
    p_tcps = (_TCPS *) & (((_IP_PKT *)_ch_info_tbl->_p_rcv_buf.pip)->data) ;

    hdr_siz  = ((p_tcps->th.len & 0xf0) >> (4 - 2));
    data_siz = net2hs(p_ip->iph.ip_total_len) - _IP_HLEN_MIN - hdr_siz;
    p_tdata  = ((uchar *)p_tcps) + hdr_siz;

    calc = 0;
    net2hl_yn_xn(&seq, &p_tcps->th.seq);
    if (seq != _tcp_tcb->rnxt)
    {
        _tcp_tcb->hdr_flg |= _TCPF_ACK;
        _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
        if (_tcp_tcb->rnxt > seq && (_tcp_tcb->rnxt - seq) < 0x7fffffff)
        {
            calc = _tcp_tcb->rnxt - seq;
            data_siz -= calc;
            p_tdata += calc;
        }
        else if (_tcp_tcb->rnxt < seq && (seq - _tcp_tcb->rnxt) > 0x7fffffff)
        {
            calc = 0xffffffffu - seq + _tcp_tcb->rnxt + 1;
            data_siz -= calc;
            p_tdata += calc;
        }
        else
        {
            return E_ERR;
        }
    }
    if (data_siz <= 0)
    {
        return E_NO_RCV;
    } /*2669*/
    _tcp_tcb->hdr_flg |= _TCPF_ACK;
    _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);

    free_siz = _tcp_tcb->rwin + tcp_ccep[_tcp_tcb->cepid-1].rbufsz - _tcp_tcb->rwin_curr;
    if (free_siz == 0)
    {
        return E_NO_RCV;
    } /*2669*/
    else if (data_siz > free_siz)
    {
        data_siz = free_siz;
    } /*2669*/
    memcpy(_tcp_tcb->rwin_curr, p_tdata, data_siz);
    _tcp_tcb->rdsize += data_siz;
    _tcp_tcb->rwin_curr += data_siz;

    _tcp_tcb->rnxt = seq + data_siz + calc;

    if ((_tcp_tcb->req.type == _TCP_API_RCVDT)
            && (_tcp_tcb->req.stat == _TCP_API_STAT_INCOMPLETE))
    {
        _tcp_cpy_rwdat();
    } /*2669*/
    return E_OK;
}


/***********************************************************************************************************************
* Function Name: _tcp_rcv_fin
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER _tcp_rcv_fin(void)
{
    _IP_PKT  *pip;
    _TCP_HDR *ph;

    pip = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    ph = (_TCP_HDR *)(pip->data);

    if (!(ph->flg & _TCPF_FIN))
    {
        return E_NO_RCV;
    } /*2669*/
    if (!(_tcp_tcb->flag & _TCBF_FIN_RCVD))
    {
        switch (_tcp_tcb->status)
        {
            case _TCPS_ESTABLISHED:
                if (_tcp_tcb->nxt_status == _TCPS_FIN_WAIT1)
                {
                    _tcp_tcb->nxt_status = _TCPS_LAST_ACK;
                }
                else
                {
                    _tcp_tcb->nxt_status = _TCPS_CLOSE_WAIT;
                    if ((_tcp_tcb->req.type == _TCP_API_RCVDT)
                            && (_tcp_tcb->req.stat == _TCP_API_STAT_INCOMPLETE))
                    {
                        *(_tcp_tcb->req.error) = 0;

                        if (_tcp_tcb->req.tmout == TMO_NBLK)
                        {
                            FN fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
                            _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
                        }
                        else
                        {
                            _tcp_api_wup(_tcp_tcb->cepid);
                        }
                    }
                }
                break;

            case _TCPS_FIN_WAIT1:
                _tcp_tcb->nxt_status = _TCPS_CLOSING;
                break;

            case _TCPS_FIN_WAIT2:
                _tcp_tcb->nxt_status = _TCPS_TIME_WAIT;
                break;
            case _TCPS_LISTEN:
            case _TCPS_SYN_RECEIVED:
                _tcp_tcb->nxt_status = _TCPS_LISTEN;
                _tcp_tcb->hdr_flg |= _TCPF_RST;
                _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
                return E_OK;
            case _TCPS_SYN_SENT:
                _tcp_tcb->nxt_status = _TCPS_CLOSED;
                _tcp_tcb->hdr_flg |= _TCPF_RST;
                _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP
                                   | _TCBF_NEED_API | _TCBF_NEED_INIT);
                *(_tcp_tcb->req.error) = E_CLS;
                return E_OK;
            default:
                break; /*2670*/
        }
        _tcp_tcb->flag |= _TCBF_FIN_RCVD;
        _tcp_tcb->rnxt++;
    }

    _tcp_tcb->hdr_flg |= _TCPF_ACK;
    _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);

    return E_OK;
}


/***********************************************************************************************************************
* Function Name: _tcp_swin_updt
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_swin_updt(void)
{
    _TCP_HDR *ph ;
    uint32  win_size;
    sint32  diff;
    _TCPS  *p_tcps ;
    uint32  suna;

    p_tcps = (_TCPS *) & (((_IP_PKT *)_ch_info_tbl->_p_rcv_buf.pip)->data) ;
    ph  = &(p_tcps->th);

    /* Update remote window size */
    win_size = net2hs(ph->win_size);
    _tcp_tcb->swsize = win_size ;

    if (_tcp_dack[_ch_info_tbl->_ch_num])
    {
        net2hl_yn_xn(&suna,  &ph->ack) ;
        if ((_tcp_tcb->snxt >= suna) && ((_tcp_tcb->snxt - suna) < 0x7fffffff))
        {
            diff = win_size - (_tcp_tcb->snxt - suna);
        }
        else if ((_tcp_tcb->snxt <  suna) && ((suna - _tcp_tcb->snxt) > 0x7fffffff))
        {
            diff = win_size - (0xffffffffu - suna + _tcp_tcb->snxt + 1);
        }
        else
        {
            diff = win_size;
        } /*2669*/
    }
    else
    {
        if ((_tcp_tcb->snxt >= _tcp_tcb->suna) && ((_tcp_tcb->snxt - _tcp_tcb->suna) < 0x7fffffff))
        {
            diff = win_size - (_tcp_tcb->snxt - _tcp_tcb->suna);
        }
        else if ((_tcp_tcb->snxt <  _tcp_tcb->suna) && ((_tcp_tcb->suna - _tcp_tcb->snxt) > 0x7fffffff))
        {
            diff = win_size - (0xffffffffu - _tcp_tcb->suna + _tcp_tcb->snxt + 1);
        }
        else
        {
            diff = win_size;
        } /*2669*/
    }
    if (diff < 0)
    {
        diff = 0;
    } /*2669*/
    _tcp_tcb->rmt_rwsize = diff;

    if (_tcp_tcb->rmt_rwsize == 0)
    {
        if (_tcp_tcb->status != _TCPS_LISTEN)
        {
            _tcp_tcb->flag |= _TCBF_SND_ZWIN;
        }
    }

    if ((_tcp_tcb->nxt_zero != 0xffff) || (_tcp_tcb->flag & _TCBF_SND_ZWIN))
    {
        if (_tcp_tcb->sdsize > 0)
        {
            if ((_tcp_tcb->rmt_rwsize >= _tcp_tcb->mss) || (_tcp_tcb->rmt_rwsize >= _tcp_tcb->sdsize) \
                    || (_tcp_tcb->rmt_rwsize != _tcp_tcb->swsize)/*(bug39 fix)*/)
            {
                if (_tcp_dack[_ch_info_tbl->_ch_num] == 1)
                {
                    _tcp_tcb->retrans_q.rst_cnt = _tcp_rt_tmo_rst[_ch_info_tbl->_ch_num];
                    _tcp_tcb->retrans_q.nxt_rtx_cnt = _TCP_RTO_INIT;
                    if (!(_tcp_tcb->flag & _TCBF_NEED_SEND))
                    {
                        if (_tcp_tcb->flag & _TCBF_SND_TCP)
                        {
                            _tcp_tcb->flag |= _TCBF_NEED_SEND;
                        }
                    }
                }
                else
                {
                    _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
                }
                _tcp_tcb->flag &= ~_TCBF_SND_ZWIN;
                _tcp_tcb->nxt_zero = 0xffff;
                _tcp_tcb->zwin_int = 0xffff ;
            }
        }
        else
        {
            if (_tcp_tcb->rmt_rwsize >= _tcp_tcb->mss)
            {
                _tcp_tcb->flag &= ~_TCBF_SND_ZWIN;
                _tcp_tcb->nxt_zero = 0xffff;
                _tcp_tcb->zwin_int = 0xffff ;
            }
        }
    }

    return ;
}
#endif /* _TCP */



/***********************************************************************************************************************
* Function Name: _proc_snd
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _proc_snd(void)
{
    uint16  sum, len = 0;
#if defined(__GNUC__)
    sint16  i;
#else
    sint16  ret, i;
#endif
    uchar  *picmpdata;
    _ICMP_HDR *picmph_r, *picmph_s;
    _ICMP_PKT *picmp;
    _IP_PKT  *pip;
    uchar cur_req_stat;
    uchar cur_req_type;
    uint16 counter = 0;

    _TCP_PHDR phdr;
#if defined(_ETHER)
    _ARP_ENTRY *ae;

    ae = _ether_arp_tbl[0];
#endif
    if (_tcp_pre_timer_cnt != _tcp_timer_cnt)
    {
        _tcp_pre_timer_cnt = _tcp_timer_cnt;

#if defined(_ETHER)
        for (counter = 0;counter < _t4_channel_num; counter++)
        {
            ae = _ether_arp_tbl[counter];
            _ch_info_tbl = &_ch_info_head[counter];

            for (i = 0; i < _ip_tblcnt[counter]; i++, ae++)
            {
                if (((ae->ae_state == AS_RESOLVED)
                        || (ae->ae_state == AS_PENDING)) && (ae->ae_ttl > 0))
                {
                    ae->ae_ttl--;
                } /*2669*/

                if (ae->ae_state == AS_RESOLVED)
                {
                    if (ae->ae_ttl == 0)
                    {
                        _ether_arp_del(ae);
                    } /*2669*/
                }
                else if (ae->ae_state == AS_TMOUT)
                {
                    _ether_arp_del(ae);
                }
                else if (ae->ae_state == AS_PENDING)
                {
                    if (((ARP_TIMEOUT - ae->ae_ttl) % 100) == 0)
                    {
                        if ((ae->ae_attempts-- == 0) || (ae->ae_ttl == 0))
                        {
                            ae->ae_state = AS_TMOUT;
                        }
                        else
                        {
                            _ch_info_tbl->flag |= _TCBF_SND_ARP_REQ;
#if defined(__GNUC__)
                            _ether_snd_arp(ae);
#else
                            ret = _ether_snd_arp(ae);
                            ret = ret;
#endif
                        }
                    }
                }
            }
        }
#endif

#if defined(_TCP)
        for (counter = 0;counter < __tcpcepn; counter++)
        {
            _tcp_tcb = &head_tcb[counter];
            _ch_info_tbl = &_ch_info_head[tcp_ccep[counter].cepatr];

            cur_req_stat = _tcp_tcb->req.stat;
            cur_req_type = _tcp_tcb->req.type;

            if (_tcp_tcb->ack_wait_timercnt > 0)
            {
                if (_tcp_tcb->ack_wait_timer != _tcp_timer_cnt)
                {
                    _tcp_tcb->ack_wait_timer = _tcp_timer_cnt;
                    _tcp_tcb->ack_wait_timercnt--;
                }
            }

            if (_tcp_tcb->status == _TCPS_TIME_WAIT)
            {
                if (--_tcp_tcb->mslcnt == 0)
                {
                    _tcp_tcb->status = _TCPS_CLOSED;
                    _tcp_tcb->nxt_status = _TCPS_CLOSED;
                    if (cur_req_type == _TCP_API_CLSCP)
                    {
                        *(_tcp_tcb->req.error) = E_OK;
                        if (_tcp_tcb->req.tmout == TMO_NBLK)
                        {
                            FN fncd = _tcp_api_type_to_fn(cur_req_type);
                            _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
                        }
                        else
                        {
                            _tcp_api_wup(_tcp_tcb->cepid);
                        }
                        _tcp_init_tcb(_tcp_tcb);
                    }
                    else
                    {

                    }
                }
            }
            if (((cur_req_stat == _TCP_API_STAT_UNTREATED)
                    || (cur_req_stat == _TCP_API_STAT_INCOMPLETE))
                    && (_tcp_tcb->req.tmout >= 0))
            {
                if (_tcp_tcb->req.tmout-- == 0)
                {
                    _tcp_cancel_api(E_TMOUT);
                }
            }


            if ((_tcp_tcb->retrans_q.nxt_rtx_cnt != 0xffff) && (_tcp_tcb->retrans_q.nxt_rtx_cnt > 0))
            {
                _tcp_tcb->retrans_q.nxt_rtx_cnt--;
            } /*2669*/
            if ((_tcp_tcb->retrans_q.rst_cnt != 0xffff) && (_tcp_tcb->retrans_q.rst_cnt > 0))
            {
                _tcp_tcb->retrans_q.rst_cnt--;
            } /*2669*/

            if (_tcp_tcb->zwp_noack_cnt != 0xffff)
            {
                if (_tcp_tcb->zwp_noack_cnt > 0)
                {
                    _tcp_tcb->zwp_noack_cnt--;
                } /*2669*/
            } /*2669*/
            if (_tcp_tcb->nxt_zero != 0xffff)
            {
                if (_tcp_tcb->nxt_zero > 0)
                {
                    _tcp_tcb->nxt_zero--;
                } /*2669*/
            } /*2669*/
            if (_tcp_tcb->zwp_noack_cnt == 0)
            {
                _tcp_tcb->zwp_noack_cnt = 0xffff;
                _tcp_tcb->nxt_zero   = 0xffff;
                *(_tcp_tcb->req.error) = E_CLS;
                _tcp_tcb->nxt_status  = _TCPS_CLOSED;
                _tcp_tcb->it_stat  = _ITS_RST;
                _tcp_tcb->hdr_flg  = _TCPF_RST;
                _tcp_tcb->flag   |= (_TCBF_NEED_SEND | _TCBF_SND_TCP | _TCBF_NEED_API);
            }
            if (_tcp_tcb->nxt_zero == 0)
            {
                _tcp_tcb->zwin_int *= 2;
                if (_tcp_tcb->zwin_int > _TCP_RTO_INT_MAX)
                {
                    _tcp_tcb->zwin_int = _TCP_RTO_INT_MAX;
                } /*2669*/
                _tcp_tcb->nxt_zero = _tcp_tcb->zwin_int;
                _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_ZWIN);
            }

            else if (_tcp_tcb->retrans_q.rst_cnt == 0)
            {
                if (cur_req_type != 0)
                {
                    switch (cur_req_type)
                    {
                        case _TCP_API_ACPCP:
                            _tcp_tcb->flag |= _TCBF_RET_LISTEN;
                            break;
                        case _TCP_API_CONCP:
                            *(_tcp_tcb->req.error) = E_CLS;
                            _tcp_tcb->flag |= (_TCBF_NEED_INIT | _TCBF_NEED_API);
                            break;
                        case _TCP_API_CLSCP:
                            *(_tcp_tcb->req.error) = E_OK;
                            _tcp_tcb->flag |= (_TCBF_NEED_INIT | _TCBF_NEED_API);
                            break;
                        case _TCP_API_SHTCP:
                            _tcp_tcb->nxt_status = _TCPS_CLOSED;
                            _tcp_tcb->it_stat = _ITS_RST;
                            break;
                        case _TCP_API_SNDDT:
                            *(_tcp_tcb->req.error) = E_CLS;
                            _tcp_tcb->nxt_status = _TCPS_CLOSED;
                            _tcp_tcb->it_stat = _ITS_RST;
                            _tcp_tcb->flag |= _TCBF_NEED_API;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    if (_tcp_tcb->retrans_q.hdr_flg & _TCPF_FIN)
                    {
                        _tcp_tcb->nxt_status = _TCPS_CLOSED;
                        _tcp_tcb->it_stat = _ITS_RST;
                    }
                }
                _tcp_tcb->sdsize  = 0;
                _tcp_tcb->hdr_flg = _TCPF_RST;
                _tcp_tcb->flag  |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
                _tcp_tcb->retrans_q.nxt_rtx_cnt = 0xffff;
                _tcp_tcb->retrans_q.rst_cnt     = 0xffff;
            }
            else if (_tcp_tcb->retrans_q.nxt_rtx_cnt == 0)
            {
                _tcp_tcb->retrans_q.cur_int *= 2;
                if (_tcp_tcb->retrans_q.cur_int > _TCP_RTO_INT_MAX)
                {
                    _tcp_tcb->retrans_q.cur_int = _TCP_RTO_INT_MAX;
                } /*2669*/
                _tcp_tcb->retrans_q.nxt_rtx_cnt = _tcp_tcb->retrans_q.cur_int;
                _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_RTX);
            }
        }

#endif /* _TCP */

#if defined(_UDP)
        _udp_api_tmout();
#endif

    }

    for (counter = 0; counter < _t4_channel_num; counter++)
    {
        _ch_info_tbl = &_ch_info_head[counter];

#if defined(_ETHER)
        if (_ch_info_tbl->flag & _TCBF_SND_ARP_REP)
        {
#if defined(__GNUC__)
            _ether_snd_arp(ae);
#else
            ret = _ether_snd_arp(ae);
#endif
        }
#endif
#if defined(_ICMP)
        if (_ch_info_tbl->flag & _TCBF_SND_ICMP)
        {
            pip  = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);

            picmp = (_ICMP_PKT *)(pip->data);
            picmpdata = picmp->data;
            picmph_r = &picmp->icmph;
            len = _ch_info_tbl->_p_rcv_buf.len - _ICMP_HLEN - _IP_HLEN_MIN;

            picmph_s = (_ICMP_HDR *)(_tx_hdr.ihdr.tip.thdr.icmph);
            picmph_s->type = _ICMP_ECHO_REPLY;
            picmph_s->code = 0;
            picmph_s->chksum = 0;
            picmph_s->id = picmph_r->id;
            picmph_s->seq = picmph_r->seq;
            sum = _cksum((uchar *)picmph_s, _ICMP_HLEN, 0);
            sum = ~hs2net(sum);
            sum = _cksum((uchar *)picmpdata, len, sum);
            picmph_s->chksum = hs2net(sum);

            _tx_hdr.hlen = _ICMP_HLEN;
            _tx_hdr.ihdr.tip.iph.ip_proto_num = _IPH_ICMP;
            _cpy_ipaddr(_tx_hdr.ihdr.tip.iph.ip_dst, pip->iph.ip_src);
            _cpy_ipaddr(_tx_hdr.ihdr.tip.iph.ip_src, _ch_info_tbl->_myipaddr);

#if defined(__GNUC__)
            _ip_snd(picmpdata, len);
#else
            ret = _ip_snd(picmpdata, len);
#endif
#if defined(_PPP)
            if (ret == 0)
            {
#endif
                _ch_info_tbl->flag &= ~(_TCBF_PEND_ICMP | _TCBF_SND_ICMP);
                rcv_buff_release(_ch_info_tbl->_ch_num);
                _ch_info_tbl->_p_rcv_buf.len = 0;
#if defined(_PPP)
            }
#endif
        }
#endif
    }  /* for(counter = 0; counter < _t4_channel_num; counter++) */

    for (counter = 0; counter != __tcpcepn;counter++)
    {
        _tcp_tcb = &head_tcb[counter];
        _ch_info_tbl = &_ch_info_head[tcp_ccep[counter].cepatr];

#if defined(_TCP)
        if (_tcp_tcb->flag & _TCBF_NEED_SEND)
        {
            if (_tcp_tcb->flag & (_TCBF_SND_TCP | _TCBF_SND_RTX | _TCBF_SND_ZWIN))
            {
                if ((_tcp_tcb->status == _TCPS_FIN_WAIT1) && \
                        (_tcp_tcb->nxt_status == _TCPS_CLOSING) && (_tcp_tcb->ack_wait_timercnt != 0))
                {
                    /* nothing to do */
                }
                else
                {
                    _tcp_snd();
                }
            }
        }
#endif
    }  /* for(counter = 0; counter != __tcpcepn;counter++) */
#if defined(_UDP)
    _udp_snd((_TCPUDP_PHDR*)&phdr);
#endif
}

#if defined(_TCP)
void _tcp_snd(void)
{
    uint32  seq;
    uint16  sum, tmp, len = 0, smode = 0;
    sint16  ret;
    uchar  *pdata = NULL, flg = 0;
    _TCP_HDR *ptcph;
    _TCP_PHDR phdr;
    uint16  dack_flag = _tcp_tcb->flag;

    if (_tcp_tcb->flag & _TCBF_SND_ZWIN)
    {
        if (_tcp_tcb->nxt_zero == 0xffff)
        {
            _tcp_tcb->nxt_zero = _TCP_RTO_INIT;
            _tcp_tcb->zwin_int = _TCP_RTO_INIT;
            _tcp_tcb->flag &= ~_TCBF_SND_ZWIN;
            if (_tcp_dack[_ch_info_tbl->_ch_num] == 1)
            {
                if (_tcp_tcb->retrans_q.data != NULL)
                {
                    _tcp_tcb->retrans_q.rst_cnt = 0xffff;
                    _tcp_tcb->retrans_q.nxt_rtx_cnt = 0xffff;
                }
            }
            else
            {
                _tcp_clr_rtq(_tcp_tcb);
            }
            return;
        }
        len  = 0;
        pdata = NULL;
        seq = _tcp_tcb->suna - 1;
        flg  = _TCPF_ACK;
        smode = _TCBF_SND_ZWIN;
        if (_tcp_dack[_ch_info_tbl->_ch_num] == 1)
        {
            _tcp_tcb->flag &= ~_TCBF_AVOID_DACK;
        }
    }

    else if (_tcp_tcb->nxt_zero != 0xffff)
    {
        return;
    }
    else
    {
        if (_tcp_dack[_ch_info_tbl->_ch_num] == 1)
        {
            if (_tcp_tcb->sdsize > 0)
            {
                if ((_tcp_tcb->flag & _TCBF_SND_TCP) && \
                        ((_tcp_tcb->suna == _tcp_tcb->snxt) || (_tcp_tcb->flag & _TCBF_AVOID_DACK)))
                {
                    if (_tcp_tcb->sdsize > _tcp_tcb->mss)
                    {
                        if (_tcp_tcb->flag & _TCBF_AVOID_DACK)
                        {
                            if (_tcp_tcb->sdsize > (_tcp_tcb->mss * 2))
                            {
                                len = _tcp_tcb->mss;
                            }
                            else
                            {
                                len = _tcp_tcb->sdsize - _tcp_tcb->mss;
                            }
                            flg = _TCPF_ACK;
                            _tcp_tcb->flag &= ~_TCBF_AVOID_DACK;
                        }
                        else
                        {
                            len = _tcp_tcb->mss;
                            flg = _TCPF_ACK;
                            _tcp_tcb->flag |= _TCBF_AVOID_DACK;
                        }
                    }
                    else
                    {
                        if (_tcp_tcb->flag & _TCBF_AVOID_DACK)
                        {
                            len = 1;
                            flg = (_TCPF_ACK | _TCPF_PSH);
                            _tcp_tcb->flag &= ~_TCBF_AVOID_DACK;
                        }
                        else
                        {
                            if (_tcp_tcb->sdsize > 1)
                            {
                                len = _tcp_tcb->sdsize - 1;
                                _tcp_tcb->flag |= _TCBF_AVOID_DACK;
                            }
                            else
                            {
                                len = _tcp_tcb->sdsize;
                                flg = _TCPF_PSH;
                            }
                            flg |= _TCPF_ACK;
                        }
                    }
                    if (len > _tcp_tcb->rmt_rwsize)
                    {
                        if ((_tcp_tcb->rmt_rwsize == 0) && (_tcp_tcb->hdr_flg & _TCPF_RST))
                        {
                            len = 0;
                            _tcp_tcb->flag &= ~_TCBF_AVOID_DACK;
                        }
                        else if (_tcp_tcb->rmt_rwsize == 0)
                        {
                            _tcp_tcb->flag = dack_flag;
                            return;
                        }
                        else
                        {
                            len = _tcp_tcb->rmt_rwsize;
                            _tcp_tcb->flag &= ~_TCBF_AVOID_DACK;
                        }
                    }
                }
                else if (_tcp_tcb->flag & _TCBF_SND_RTX)
                {
                    _tcp_tcb->flag &= ~_TCBF_AVOID_DACK;
                    len = _tcp_tcb->retrans_q.len;

                }
            }
            else
            {
                len = 0;
            }
        }
        else
        {
            if (_tcp_tcb->sdsize > 0)
            {
                if ((_tcp_tcb->flag & _TCBF_SND_TCP) && (_tcp_tcb->suna == _tcp_tcb->snxt))
                {
                    if (_tcp_tcb->sdsize > _tcp_tcb->mss)
                    {
                        len = _tcp_tcb->mss;
                        flg = _TCPF_ACK;
                    }
                    else
                    {
                        len = _tcp_tcb->sdsize;
                        flg = (_TCPF_ACK | _TCPF_PSH);
                    }
                    if (len > _tcp_tcb->rmt_rwsize)
                    {
                        len = _tcp_tcb->rmt_rwsize;
                    } /*2669*/
                }
                else if (_tcp_tcb->flag & _TCBF_SND_RTX)
                {
                    if ((_tcp_tcb->snxt >= _tcp_tcb->suna) &&
                            ((_tcp_tcb->snxt - _tcp_tcb->suna) < 0x7fffffff))
                    {
                        len = _tcp_tcb->snxt - _tcp_tcb->suna;
                    } /*2669*/
                    else if ((_tcp_tcb->snxt <  _tcp_tcb->suna) &&
                             ((_tcp_tcb->suna - _tcp_tcb->snxt) > 0x7fffffff))
                    {
                        len = 0xffffffffu - _tcp_tcb->suna + _tcp_tcb->snxt + 1;
                    } /*2669*/
                    else
                    {
                        len = 0;
                    } /*2669*/
                }
            }
            else
            {
                len = 0;
            }
        }
        if (_tcp_tcb->flag & _TCBF_SND_RTX)
        {
            pdata = _tcp_tcb->retrans_q.data;
            seq  = _tcp_tcb->retrans_q.seq;
            flg  |= _tcp_tcb->retrans_q.hdr_flg;
            smode = _TCBF_SND_RTX;
        }
        else if (_tcp_tcb->flag & _TCBF_SND_TCP)
        {
            pdata = _tcp_tcb->nxtdat;
            seq  = _tcp_tcb->snxt;
            flg  |= _tcp_tcb->hdr_flg;
            smode = _TCBF_SND_TCP;

            if (!(((len == 0) && (_tcp_tcb->hdr_flg == _TCPF_ACK))
                    || (_tcp_tcb->hdr_flg & _TCPF_RST)))
            {

                if (_tcp_dack[_ch_info_tbl->_ch_num] == 1)
                {
                    if (dack_flag & _TCBF_AVOID_DACK)
                    {
                        _tcp_tcb->retrans_q2.data    = pdata;
                        _tcp_tcb->retrans_q2.hdr_flg   = flg;
                        _tcp_tcb->retrans_q2.len   = len;
                        _tcp_tcb->retrans_q2.seq    = seq;

                    }
                    else
                    {
                        _tcp_tcb->retrans_q.data    = pdata;
                        _tcp_tcb->retrans_q.hdr_flg   = flg;
                        _tcp_tcb->retrans_q.len    = len;
                        _tcp_tcb->retrans_q.rst_cnt   = _tcp_rt_tmo_rst[_ch_info_tbl->_ch_num];
                        _tcp_tcb->retrans_q.nxt_rtx_cnt  = _TCP_RTO_INIT;
                        _tcp_tcb->retrans_q.cur_int   = _TCP_RTO_INIT;
                        _tcp_tcb->retrans_q.seq    = seq;
                    }
                }
                else
                {
                    _tcp_tcb->retrans_q.data   = pdata;
                    _tcp_tcb->retrans_q.hdr_flg   = flg;
                    _tcp_tcb->retrans_q.rst_cnt   = _tcp_rt_tmo_rst[_ch_info_tbl->_ch_num];
                    _tcp_tcb->retrans_q.nxt_rtx_cnt  = _TCP_RTO_INIT;
                    _tcp_tcb->retrans_q.cur_int   = _TCP_RTO_INIT;
                    _tcp_tcb->retrans_q.seq    = seq;
                }
            }
        }
    }
    ptcph = (_TCP_HDR *)(_tx_hdr.ihdr.tip.thdr.tcph);
    ptcph->sport = hs2net(_tcp_tcb->loc_port) ;
    ptcph->dport = hs2net(_tcp_tcb->rem_port) ;
    hl2net_yn_xn(&ptcph->ack, &_tcp_tcb->rnxt);
    hl2net_yn_xn(&ptcph->seq, &seq);
    if (flg & _TCPF_RST)
    {
        ptcph->flg  = _TCPF_RST ;
    } /*2669*/
    else
    {
        ptcph->flg  = flg ;
    } /*2669*/
    if (ptcph->flg & _TCPF_SYN)
    {
        ptcph->opt[0] = 0x02 ; /* Option Kind = 2 (MSS) */
        ptcph->opt[1] = 0x04 ; /* Option Length = 4 */
        tmp = hs2net(_tcp_tcb->mss) ;
        memcpy(&ptcph->opt[2], &tmp, 2) ;
        ptcph->len = (24 << 2);
    }
    else
    {
        ptcph->len = (20 << 2);
    }
    ptcph->win_size = hs2net((_tcp_tcb->rwin) + (tcp_ccep[_tcp_tcb->cepid-1].rbufsz) - (_tcp_tcb->rwin_curr)) ;
    _cpy_ipaddr(phdr.sadr, _ch_info_tbl->_myipaddr);
    _cpy_ipaddr(phdr.dadr, _tcp_tcb->rem_ip);
    phdr.reserve = 0 ;
    phdr.prtcl = _IPH_TCP ;
    phdr.len = hs2net(len + (ptcph->len >> 2)) ;
    ptcph->cksum = 0 ;
    sum = _cksum((uchar *) & phdr, 12, 0);
    sum = ~hs2net(sum);
    sum = _cksum((uchar *)ptcph, (ptcph->len >> 2), sum);
    sum = ~hs2net(sum);
    sum = _cksum(pdata, len, sum);
    ptcph->cksum = hs2net(sum);

    _tx_hdr.hlen = (ptcph->len >> 2);
    _tx_hdr.ihdr.tip.iph.ip_proto_num = _IPH_TCP;
    _cpy_ipaddr(_tx_hdr.ihdr.tip.iph.ip_dst, _tcp_tcb->rem_ip);
    _cpy_ipaddr(_tx_hdr.ihdr.tip.iph.ip_src, _ch_info_tbl->_myipaddr);

    ret = _ip_snd(pdata, len);
    if (ret == E_IP_PENDING)
    {
        if (_tcp_dack[_ch_info_tbl->_ch_num] == 1)
        {
            _tcp_tcb->flag = dack_flag;
        }

        if (_tcp_tcb->req.type == _TCP_API_CLSCP)
        {
            if (_tcp_tcb->hdr_flg & _TCPF_RST)
            {

                if (_tcp_tcb->flag & _TCBF_NEED_API)
                {
                    if (_tcp_tcb->req.tmout == TMO_NBLK)
                    {
                        FN fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
                        _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
                    }
                    else
                    {
                        _tcp_api_wup(_tcp_tcb->cepid);
                    }
                }
                _tcp_init_tcb(_tcp_tcb);
                _tcp_tcb->flag &= ~_TCBF_NEED_SEND;
                return;
            }
        }
        return;
    }
    else
    {
        if (ret == -2 && _tcp_tcb->req.type == _TCP_API_ACPCP)
        {
            _tcp_return_listen();
            return;
        }
        else
        {

        }

        if ((_tcp_tcb->flag & _TCBF_SND_ZWIN) && !(_tcp_tcb->hdr_flg & (_TCPF_FIN | _TCPF_SYN | _TCPF_RST)))
        {
            if (_tcp_tcb->zwp_noack_cnt == 0xffff)
            {
                _tcp_tcb->zwp_noack_cnt = _tcp_rt_tmo_rst[_ch_info_tbl->_ch_num];
            } /*2669*/
        }
        if (_tcp_dack[_ch_info_tbl->_ch_num] == 1)
        {
            if (!(_tcp_tcb->flag & _TCBF_SND_TCP))
            {
                _tcp_tcb->flag &= ~smode;
            }
        }
        else
        {
            _tcp_tcb->flag &= ~smode;
        }
        if (_tcp_tcb->hdr_flg & _TCPF_RST)
        {
            if (_tcp_tcb->flag & _TCBF_NEED_API)
            {
                if (_tcp_tcb->req.tmout == TMO_NBLK)
                {
                    FN fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
                    _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
                }
                else
                {
                    _tcp_api_wup(_tcp_tcb->cepid);
                }
            }
            if (_tcp_tcb->flag & _TCBF_NEED_INIT)
            {
                _tcp_init_tcb(_tcp_tcb);
            }
            else if (_tcp_tcb->flag & _TCBF_RET_LISTEN)
            {
                _tcp_return_listen();
            } /*2669*/
            else
            {
                _tcp_tcb->status = _tcp_tcb->nxt_status;
            } /*2669*/
            _tcp_tcb->flag &= ~_TCBF_NEED_SEND;
            return;
        }
        if (smode == _TCBF_SND_TCP)
        {
            _tcp_tcb->snxt += len;
            if (_tcp_tcb->hdr_flg & (_TCPF_SYN | _TCPF_FIN))
            {
                _tcp_tcb->snxt++;
                if (_tcp_tcb->hdr_flg & (_TCPF_FIN))
                {
                    if (_tcp_tcb->nxt_status == _TCPS_FIN_WAIT1)
                    {
                        _tcp_tcb->ack_wait_timer = get_tcpudp_time();
                        _tcp_tcb->ack_wait_timercnt = _TCP_FIN_WAIT1_SND_WAIT;
                    }
                }
            }
            _tcp_tcb->rmt_rwsize -= len;
            if ((_tcp_tcb->sdsize - len) == 0)
            {
                if (_tcp_tcb->req.stat == _TCP_API_STAT_INCOMPLETE)
                {
                    if (((_tcp_tcb->req.type == _TCP_API_CONCP) && (_tcp_tcb->nxt_status == _TCPS_ESTABLISHED))
                            || (_tcp_tcb->req.type == _TCP_API_SHTCP))
                    {
                        *(_tcp_tcb->req.error) = E_OK;
                        if (_tcp_tcb->req.type == _TCP_API_SHTCP)
                        {
                            _tcp_tcb->it_stat = _ITS_SHT;
                        } /*2669*/
                        if (_tcp_tcb->req.tmout == TMO_NBLK)
                        {
                            FN fncd;
                            fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);

                            _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
                        }
                        else
                        {
                            _tcp_api_wup(_tcp_tcb->cepid);
                        }
                    }
                }
                _tcp_tcb->status = _tcp_tcb->nxt_status;
                if (_tcp_tcb->status == _TCPS_TIME_WAIT)
                {
                    _tcp_tcb->mslcnt = _tcp_2msl[_ch_info_tbl->_ch_num];
                } /*2669*/
            }

            else
            {
                _tcp_tcb->nxtdat += len;

            }
        }
        if (_tcp_dack[_ch_info_tbl->_ch_num] == 1)
        {
            if ((_tcp_tcb->flag & _TCBF_AVOID_DACK) == 0)
            {
                _tcp_tcb->flag &= ~smode;
                _tcp_tcb->flag &= ~_TCBF_NEED_SEND;
            }
            _tcp_tcb->hdr_flg = 0;
        }
        else
        {
            _tcp_tcb->flag &= ~smode;
            _tcp_tcb->flag &= ~_TCBF_NEED_SEND;
            _tcp_tcb->hdr_flg = 0;
        }
    }

    return;
}

/***********************************************************************************************************************
* Function Name: _tcp_cancel_api
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_cancel_api(ER ercd)
{
    _API_REQ *areq;

    areq = &(_tcp_tcb->req);

    *(areq->error) = ercd;

    switch (areq->type)
    {
            /****** tcp_acp_cep, tcp_con_cep ******/
        case _TCP_API_ACPCP:
        case _TCP_API_CONCP:
            _tcp_init_tcb(_tcp_tcb);
            break;
            /****** tcp_cls_cep *****/
        case _TCP_API_CLSCP:
            _tcp_tcb->hdr_flg = _TCPF_RST;
            _tcp_tcb->flag |=
                (_TCBF_NEED_SEND | _TCBF_SND_TCP | _TCBF_NEED_INIT | _TCBF_NEED_API);
            break;
            /****** tcp_snd_dat ******/
        case _TCP_API_SNDDT:
            _tcp_tcb->flag &= ~_TCBF_NEED_SEND;
            _tcp_tcb->nxtdat = NULL;
            _tcp_tcb->sdsize = 0;
            _tcp_clr_rtq(_tcp_tcb);
            break;
            /****** tcp_rcv_dat ******/
        case _TCP_API_RCVDT:

            break;
    }
    if (areq->type != _TCP_API_CLSCP)
    {
        if (_tcp_tcb->req.tmout == TMO_NBLK)
        {
            FN fncd = _tcp_api_type_to_fn(areq->type);
            _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
        }
        else
        {
            _tcp_api_wup(_tcp_tcb->cepid);
        }
    }
    return;
}

/***********************************************************************************************************************
* Function Name: _tcp_clr_rtq
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_clr_rtq(_TCB *_ptcb)
{
    _ptcb->retrans_q.data   = NULL;
    _ptcb->retrans_q.hdr_flg  = 0;
    if (_tcp_dack[ tcp_ccep[_ptcb->cepid-1].cepatr ] == 1)
    {
        _ptcb->retrans_q.len   = 0;
    }
    _ptcb->retrans_q.rst_cnt  = 0xffff;
    _ptcb->retrans_q.nxt_rtx_cnt = 0xffff;
    _ptcb->retrans_q.cur_int  = _TCP_RTO_INIT;
    _ptcb->retrans_q.seq   = 0;

    return;
}


/***********************************************************************************************************************
* Function Name: _tcp_return_listen
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_return_listen(void)
{
    uint16 tmp;

    tmp = _tcp_tcb->loc_port;

    _tcp_init_tcb(_tcp_tcb);

    _tcp_tcb->loc_port = tmp;
    _tcp_tcb->status = _TCPS_LISTEN;

    return;
}

/***********************************************************************************************************************
* Function Name: _tcp_api_wup
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _tcp_api_wup(ID id)
{
    if (_tcp_tcb->req.stat != _TCP_API_STAT_COMPLETE)
    {
        _tcp_tcb->req.stat = _TCP_API_STAT_COMPLETE;

        tcp_api_wup(id);
    }

    return;
}

/***********************************************************************************************************************
* Function Name: _tcp_check_cepid_arg
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER _tcp_check_cepid_arg(ID cepid)
{
    ER err = E_OK;
    if ((cepid <= 0) || (cepid > __tcpcepn))
    {
        err = E_PAR;
    }
    return err;
}

/***********************************************************************************************************************
* Function Name: _tcp_check_len_arg
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER _tcp_check_len_arg(INT len)
{
    ER err = E_OK;
    if (len < 0)
    {
        err = E_PAR;
    }
    return err;
}

/***********************************************************************************************************************
* Function Name: _tcp_check_tmout_arg
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER  _tcp_check_tmout_arg(uint16 api_type, TMO tmout, _TCP_CB* pTcpcb)
{
    ER errcode = E_OK;

    if (_TCP_CB_STAT_IS_VIA_CALLBACK(pTcpcb->stat))
    {
        errcode = E_WBLK;

        if (tmout != TMO_NBLK)
        {
            if (api_type == _TCP_API_RCVDT && tmout == TMO_POL)
            {
                errcode = E_OK;
            }
            else
            {
                errcode = E_PAR;
            }
        }
    }
    else
    {
        errcode = E_OK;

        if (tmout == TMO_POL && api_type != _TCP_API_RCVDT)
        {
            errcode = E_PAR;
        }
        else if (tmout == TMO_NBLK)
        {
            errcode = E_WBLK;
        }
    }

    return errcode;
}

/***********************************************************************************************************************
* Function Name: _tcp_is_tcb_queue_over
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
uint16  _tcp_is_tcb_queue_over(uint16 api_type, _TCB* pTcb,  _TCP_CB* pTcpcb)
{
    uint16 bResult = FALSE;

    if (pTcb->req.stat != _TCP_API_STAT_INIT && pTcb->req.stat != _TCP_API_STAT_COMPLETE)
    {
        bResult = TRUE;
    }
    else if (_TCP_CB_STAT_IS_VIA_CALLBACK(pTcpcb->stat) &&
             _TCP_CB_STAT_IS_API_LOCKED(pTcpcb->stat))
    {
        bResult = TRUE;
    }

    return bResult;
}


/***********************************************************************************************************************
* Function Name: _tcp_call_callback
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
uint16 _tcp_call_callback(ID cepid, FN fncd, VP p_parblk)
{
    UH count;

    _TCP_CB *tmp;

    _TCP_CALLBACK_FUNC pCallback = _TCP_CB_GET_CALLBACK_FUNC_PTR(cepid);

    if (pCallback)
    {
        for (count = 0; count < __tcpcepn; count++)
        {
            tmp = GET_TCP_CALLBACK_INFO_PTR(count + 1);
            _TCP_CB_STAT_SET_CALLBACK_FLG(tmp->stat);
        }
        pCallback(_tcp_tcb->cepid, fncd, p_parblk);

        for (count = 0; count < __tcpcepn; count++)
        {
            tmp = GET_TCP_CALLBACK_INFO_PTR(count + 1);
            _TCP_CB_STAT_CLEAR_CALLBACK_FLG(tmp->stat);
        }
    }

    return 0;
}


/***********************************************************************************************************************
* Function Name: _tcp_api_type_to_fn
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
FN  _tcp_api_type_to_fn(uint16 api_type)
{
    FN fncd = TFN_TCP_ALL;

    switch (api_type)
    {
        case _TCP_API_ACPCP:
            fncd = TFN_TCP_ACP_CEP;
            break;
        case _TCP_API_CONCP:
            fncd = TFN_TCP_CON_CEP;
            break;
        case _TCP_API_SHTCP:
            fncd = TFN_TCP_SHT_CEP;
            break;
        case _TCP_API_CLSCP:
            fncd = TFN_TCP_CLS_CEP;
            break;
        case _TCP_API_SNDDT:
            fncd = TFN_TCP_SND_DAT;
            break;
        case _TCP_API_RCVDT:
            fncd = TFN_TCP_RCV_DAT;
            break;
        case _TCP_API_CANCP:
            fncd = TFN_TCP_CAN_CEP;
            break;
        default:
            break;
    }

    return fncd;
}

/***********************************************************************************************************************
* Function Name: _tcp_recv_polling
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
ER _tcp_recv_polling(_TCB* pTcb, uchar *buf, uint16 size)
{
    uint16  api_dsiz;
    uint16  free_win;

    api_dsiz = size;

    if (pTcb->rdsize < api_dsiz)
    {
        api_dsiz = pTcb->rdsize;
    }

    pTcb->rdsize -= api_dsiz;

    memcpy(buf, pTcb->rwin_bnry, api_dsiz);

    if (pTcb->rdsize == 0)
    {

        free_win = tcp_ccep[pTcb->cepid-1].rbufsz - (pTcb->rwin_curr - pTcb->rwin);
        if ((free_win < pTcb->mss) && (free_win < (tcp_ccep[pTcb->cepid-1].rbufsz / 2)))
        {
            pTcb->hdr_flg |= _TCPF_ACK;
            pTcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
        }
        pTcb->rwin_bnry = pTcb->rwin;
        pTcb->rwin_curr = pTcb->rwin;
    }
    else
    {
        pTcb->rwin_bnry += api_dsiz;
    } /*2669*/
    return api_dsiz;
}


void _tcp_init_callback_info(_TCP_CB* pCallbackInfo)
{
    memset((void*)pCallbackInfo, 0, sizeof(_TCP_CB));
}

#endif /* _TCP */


void dump_tcb(const _TCB *ptr)
{
	printf("TCB:\n");
	printf("  rem_port: %d\n", (int)hs2net(ptr->rem_port));
	printf("  loc_port: %d\n", (int)hs2net(_tcp_tcb->loc_port));
	printf("  rem_ip: %d\n", (int)ptr->rem_ip);
///                            && (_ch_info_tbl->_ch_num == tcp_ccep[counter].cepatr)
	printf("  status: %d\n", (int)ptr->status);
	printf("  nxt_status: %d\n", (int)ptr->nxt_status);
}

void dump_ip(const char *head, const uint8_t *ip)
{
	printf("%s %d,%d,%d,%d\n", head, (int)ip[0], (int)ip[1], (int)ip[2], (int)ip[3]);
}
