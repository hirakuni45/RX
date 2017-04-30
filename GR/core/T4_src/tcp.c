//=====================================================================//
/*!	@file
	@brief	TCP @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "net_config.h"
#include <string.h>
#include "type.h"
#include "config_tcpudp.h"
#if defined(_ETHER)
#include "ether.h"
#elif defined(_PPP)
#include "ppp.h"
#endif
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "core/driver/driver.h"

/*******************************************************************************************************
Exported global variables (to be accessed by other files)
*******************************************************************************************************/
_TCB  *_tcp_tcb;    /* TCB (Transport Control Block) pointer */
_TCB  *head_tcb;    /* TCB head pointer */
_TX_HDR  _tx_hdr;    /* TCP transmit header area */
UH   _tcp_timer_cnt;   /* timer count: 10ms unit */
UH   _tcp_pre_timer_cnt;  /* previous timer count */

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

#if defined(_ETHER)
extern UB *_ether_p_rcv_buff;
/// extern const UH  _ip_tblcnt[];
extern const UH  _ip_tblcnt;
#endif /* _ETHER */

#if defined(_PPP)
extern UB ppp_mode;
#endif

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
    register uint8_t *a1 = (uint8_t *)y;
    register uint8_t *a0 = (uint8_t *)x;

    *((uint8_t*)a1 + 3) = *((uint8_t*)a0);
    *((uint8_t*)a1 + 2) = *((uint8_t*)a0 + 1);
    *((uint8_t*)a1 + 1) = *((uint8_t*)a0 + 2);
    *((uint8_t*)a1) = *((uint8_t*)a0 + 3);
}
#endif

#if BIGENDIAN == 1  /* big endian */
void net2hl_yn_xn(void *y, void *x)
{
    register uint8_t *a1 = (uint8_t *)y;
    register uint8_t *a0 = (uint8_t *)x;

    *((uint8_t*)a1) = *((uint8_t*)a0);
    *((uint8_t*)a1 + 1) = *((uint8_t*)a0 + 1);
    *((uint8_t*)a1 + 2) = *((uint8_t*)a0 + 2);
    *((uint8_t*)a1 + 3) = *((uint8_t*)a0 + 3);
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
    uint16_t i;
    uint8_t ch;
    ch = tcp_ccep[_ptcb->cepid-1].cepatr;

    _ptcb->flag  = 0;      // TCP status flag
#if defined(_TCP)
    _ptcb->status  = _TCPS_CLOSED;   // TCP connection status
    _ptcb->nxt_status = _TCPS_CLOSED;   // Next status to transit
    _ptcb->it_stat = _ITS_NORMAL;    // ITRON status
    _ptcb->hdr_flg = 0;      // Header flag
    _ptcb->mss  = tcp_mss[ch];	// MSS: max segment size

    _ptcb->suna  = tcp_initial_seqno[ch]; // transmitted, but no acked sequence number
    _ptcb->snxt  = tcp_initial_seqno[ch]; // next transmit sequence number
    _ptcb->risn  = 0;      // the sequence number that first received when connecting
    _ptcb->rnxt  = 0;      // next receive(expected) sequence number
    for (i = 0; i < 4; i++)
        _ptcb->rem_ip[i] = 0;     // destination IP address (need 4 byte align)
    _ptcb->rem_port = 0;      // remote port number
    _ptcb->loc_port = 0;      // local port number
    _ptcb->rtchk_cnt = 0;     // timeer count for re-transmit
    _tcp_clr_rtq(_ptcb);      // initialize re-transmit queue
    _ptcb->nxtdat  = NULL;     // pointer to next transmit data
    _ptcb->rwin_bnry = _ptcb->rwin;   // Received window BNRY(boundary) pointer
    _ptcb->rwin_curr = _ptcb->rwin;   // Received window CURR(current) pointer
    _ptcb->swsize  = 0;     // the recieve window size that notified by remote host
    _ptcb->rmt_rwsize = 0;     // local transmit window size
    _ptcb->sdsize  = 0;     // remain transmit data size
    _ptcb->rdsize  = 0;     // received data size
    _ptcb->mslcnt  = 0;     // 2MSL remain count
    _ptcb->zwin_int = _TCP_RTO_INIT;   // zero-window probe interval
    _ptcb->nxt_zero = 0xffff;     // the time that until next zero-window probe
    _ptcb->zwp_noack_cnt = 0xffff;   // no acked time for the zero-window probe
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

    if (_process_flag == 0)
    {
        _process_flag = 1;
        _tcp_timer_cnt = tcpudp_get_time();

        while (1)
        {
#if defined(_PPP)
            _ppp_proc();

#endif
            _proc_api();
            _proc_rcv();
            _proc_snd();

#if defined(_UDP)
            for (counter = 0; counter < udp_ccep_num; counter++)
            {
                if ((_udp_cb[counter].req.type != _UDP_API_NON) && (_udp_cb[counter].req.stat == _UDP_API_STAT_UNTREATED))
                {
                    continue;
                }
            }
#endif
            for (counter = 0 ; counter < TCPUDP_CHANNEL_NUM; counter++)
            {
                if ((_ch_info_head[counter]._rcvd == 1) && ((_ch_info_head[counter].flag & _TCBF_SND_ICMP) == 0))
                {
                    break;
                }
            }
            if (counter >= TCPUDP_CHANNEL_NUM)
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

    static void (* const functbl_tcp_api[])(void) =
    {
        _tcp_api_acpt,
        _tcp_api_con,
        _tcp_api_sht_cls,
        _tcp_api_sht_cls,
        _tcp_api_snddt,
        _tcp_api_rcvdt
    };

    for (counter = 0;counter < tcp_ccep_num; counter++)
    {
        _tcp_tcb = &head_tcb[counter];
        _ch_info_tbl = &_ch_info_head[tcp_ccep[counter].cepatr];

        areq = &(_tcp_tcb->req);

        if (areq->stat == _TCP_API_STAT_UNTREATED)
        {

            areq->stat = _TCP_API_STAT_INCOMPLETE;
            functbl_tcp_api[areq->type - 1]();
        }

        if ((areq->stat == _TCP_API_STAT_INCOMPLETE) && (areq->flag & _TCP_API_FLAG_CANCELED))
        {
            _tcp_cancel_api(E_RLWAI);
            areq->flag &= (~_TCP_API_FLAG_CANCELED);
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
                int32_t fncd;
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
    static uint16_t port;

    areq = &(_tcp_tcb->req);

    if ((_tcp_tcb->status != _TCPS_CLOSED) || (_tcp_tcb->it_stat != _ITS_NORMAL))
    {
        *(areq->error) = E_OBJ;

        if (areq->stat != _TCP_API_STAT_COMPLETE)
        {
            if (areq->tmout == TMO_NBLK)
            {
                int32_t fncd;
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
        if ((port < 1024) || (port > 5000))
            port = 1024;
        _tcp_tcb->loc_port = port++;
    }
    else
        _tcp_tcb->loc_port = areq->d.cnr.my_port;

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
                    return;
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
                ;
        }

        if (areq->stat != _TCP_API_STAT_COMPLETE)
        {
            if (areq->tmout == TMO_NBLK)
            {
                int32_t fncd;
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
                _tcp_tcb->nxt_status = _TCPS_LAST_ACK;
            else
                _tcp_tcb->nxt_status = _TCPS_FIN_WAIT1;
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
                    int32_t fncd;
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

    if (tcp_dack[ tcp_ccep[ _tcp_tcb->cepid-1].cepatr ] == 1)
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
    uint16_t  api_dsiz;
    uint16_t  free_win;

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
        _tcp_tcb->rwin_bnry += api_dsiz;

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
    _IP_PKT  *pip;
    _IP_HDR  *piph;
    _ICMP_PKT *picmp;
    _ICMP_HDR *picmph;
    _TCP_HDR *ptcph;
    _TCP_PHDR phdr;
    uint16_t  seg_size, sum16;
    uint16_t  counter = 0;
    uint8_t  ch;

    _tcp_tcb = head_tcb;

    for (ch = 0; ch < TCPUDP_CHANNEL_NUM; ch++)
    {
        _ch_info_tbl = &_ch_info_head[ch];
        _ether_proc_rcv();

        if (_ch_info_tbl->_p_rcv_buf.len == 0)
        {
            _ch_info_tbl->_rcvd = 0;
            continue;
        }
        else
            _ch_info_tbl->_rcvd = 1;

#if defined(_ETHER)
        if (_ch_info_tbl->_p_rcv_buf.ip_rcv == 0)
        {
            continue;
        }
#endif

        pip = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
        piph = (_IP_HDR *)pip;

        if (_ip_rcv_hdr() != 0)
        {
            goto _err_proc_rcv;
        }


        switch (piph->ip_proto_num)
        {
#if defined(_TCP)
                /****** TCP ******/
            case(_IPH_TCP):
                ptcph = (_TCP_HDR *)(pip->data);
                while (counter != tcp_ccep_num)
                {
                    _tcp_tcb = &head_tcb[counter];
                    if ((ptcph->sport == hs2net(_tcp_tcb->rem_port))
                            && (ptcph->dport == hs2net(_tcp_tcb->loc_port))
                            && (_cmp_ipaddr(piph->ip_src, _tcp_tcb->rem_ip) == 0)
                            && (_ch_info_tbl->_ch_num == tcp_ccep[counter].cepatr)
                            && (_tcp_tcb->status != _TCPS_LISTEN)
                            && (_tcp_tcb->status != _TCPS_CLOSED))
                    {
                        break;
                    }
                    counter++;
                }
                if (counter == tcp_ccep_num)
                {
                    counter = 0;
                    while (counter != tcp_ccep_num)
                    {
                        _tcp_tcb = &head_tcb[counter];
                        if ((_tcp_tcb->status == _TCPS_LISTEN)
                                && (_ch_info_tbl->_ch_num == tcp_ccep[counter].cepatr)
                                && (ptcph->dport == hs2net(_tcp_tcb->loc_port)))
                        {
                            break;
                        }
                        counter++;
                    }
                    if (counter == tcp_ccep_num)
                    {
                        report_error(_ch_info_tbl->_ch_num, RE_TCP_HEADER1, data_link_buf_ptr);
                        goto _err_proc_rcv;
                    }
                }
                _cpy_ipaddr(phdr.sadr, piph->ip_src);
                _cpy_ipaddr(phdr.dadr, piph->ip_dst);
                phdr.reserve = 0;
                phdr.prtcl = _IPH_TCP;
                seg_size = net2hs(piph->ip_total_len) - _IP_HLEN_MIN;
                phdr.len = hs2net(seg_size);
                sum16 = _cksum((uint8_t *) & phdr, sizeof(_TCP_PHDR), 0);
                sum16 = _cksum((uint8_t *)ptcph, seg_size, ~hs2net(sum16));
                if (sum16 != 0)
                {
                    report_error(_ch_info_tbl->_ch_num, RE_TCP_HEADER2, data_link_buf_ptr);
                    goto _err_proc_rcv;
                }

                _tcp_stat();
                if (((_tcp_tcb->req.type == _TCP_API_ACPCP) && (_tcp_tcb->status == _TCPS_ESTABLISHED))
                        || ((_tcp_tcb->req.type == _TCP_API_RCVDT) && (*(_tcp_tcb->req.error) != E_INI))
                        || ((_tcp_tcb->req.type == _TCP_API_SNDDT) && (_tcp_tcb->snxt == _tcp_tcb->suna)
                            && (_tcp_tcb->sdsize == 0))
                        || ((_tcp_tcb->req.type == _TCP_API_CLSCP) && (_tcp_tcb->status == _TCPS_CLOSED)))

                    if (_tcp_tcb->req.stat == _TCP_API_STAT_INCOMPLETE)
                    {
                        if (_tcp_tcb->req.tmout == TMO_NBLK)
                        {
                            int32_t fncd;
                            fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);

                            _TCP_CB_CALL_CALLBACK(_tcp_tcb->cepid, fncd, _tcp_tcb);
                        }
                        else
                        {
                            _tcp_api_wup(_tcp_tcb->cepid);
                        }
                    }
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
    }

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
    int16_t ret;

    ret = _tcp_rcv_opt();
    if (ret == E_ERR)
        goto _tcp_stat_release;

    ret = _tcp_rcv_rst();
    if (ret != E_NO_RCV)
        goto _tcp_stat_release;

    ret = _tcp_rcv_syn();
    if ((ret == E_ERR) || ((_tcp_tcb->status == _TCPS_LISTEN) && (ret != E_SYN_OK)))
        goto _tcp_stat_release;

    if (!(_tcp_tcb->status & _TCPS_LISTEN))
        _tcp_rcv_ack();

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
int _tcp_rcv_rst(void)
{
    _IP_PKT  *pip;
    _TCP_HDR *ph;
    _API_REQ *areq;

    areq = &(_tcp_tcb->req);
    pip = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    ph = (_TCP_HDR *)(pip->data);

    if (!(ph->flg & _TCPF_RST))
        return E_NO_RCV;

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
                /* エラーコード：E_OK */
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
                    break;
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
int _tcp_rcv_syn(void)
{
    _IP_PKT  *pip;
    _IP_HDR  *piph;
    _TCP_HDR *ph;
    uint32_t  tmp;

    pip  = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    piph = (_IP_HDR *)pip;
    ph  = (_TCP_HDR *)(pip->data);

    if (!(ph->flg & _TCPF_SYN))
        return E_NO_RCV;

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
            if ((ph->flg & (_TCPF_SYN | _TCPF_ACK)) && (tmp == tcp_initial_seqno[_ch_info_tbl->_ch_num] + 1))
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
            int32_t fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
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
    uint32_t  tmp, ackdsz;
    uint32_t   suna;

    pip  = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    ph  = (_TCP_HDR *)(pip->data);
    net2hl_yn_xn(&tmp,  &ph->ack) ;

    if (!(ph->flg & _TCPF_ACK))
        return;

    if (_tcp_tcb->nxt_zero != 0xffff)
        _tcp_tcb->zwp_noack_cnt = 0xffff;

    if ((tmp > _tcp_tcb->suna) && ((tmp - _tcp_tcb->suna) < 0x7fffffff))
    {
        ackdsz = tmp - _tcp_tcb->suna;
    }
    else if ((tmp <  _tcp_tcb->suna) && ((_tcp_tcb->suna - tmp) > 0x7fffffff))
    {
        ackdsz = 0xffffffff - _tcp_tcb->suna + tmp + 1;
    }
    else
        return;

    suna = tmp;

    if (tcp_dack[_ch_info_tbl->_ch_num] == 1)
    {
        if ((_tcp_tcb->snxt != suna) && (_tcp_tcb->retrans_q.len == ackdsz))
        {
            _tcp_tcb->retrans_q.data    = _tcp_tcb->retrans_q2.data;
            _tcp_tcb->retrans_q.hdr_flg   = _tcp_tcb->retrans_q2.hdr_flg;
            _tcp_tcb->retrans_q.len    = _tcp_tcb->retrans_q2.len;
            _tcp_tcb->retrans_q.rst_cnt   = tcp_rt_tmo_rst[_ch_info_tbl->_ch_num];
            _tcp_tcb->retrans_q.nxt_rtx_cnt  = _TCP_RTO_INIT;
            _tcp_tcb->retrans_q.cur_int   = _TCP_RTO_INIT;
            _tcp_tcb->retrans_q.seq    = _tcp_tcb->retrans_q2.seq;
        }
        else
        {

        }
    }
    if (_tcp_tcb->snxt == suna)
    {
        uint8_t cur_req_stat = _tcp_tcb->req.stat;
        uint8_t cur_req_type = _tcp_tcb->req.type;

        _tcp_tcb->suna = suna;

        if (tcp_dack[_ch_info_tbl->_ch_num])
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
                    int32_t fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
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
                _tcp_tcb->mslcnt = tcp_2msl[_ch_info_tbl->_ch_num];
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
                        int32_t fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
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
                _tcp_tcb->sdsize = 0;
            else
                _tcp_tcb->sdsize -= ackdsz;
            if (_tcp_tcb->sdsize == 0)
                *(_tcp_tcb->req.error) = _tcp_tcb->req.d.dr.dtsiz;
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
int16_t _tcp_rcv_opt(void)
{
    uint16_t  mss;
    _IP_PKT  *pip;
    _TCP_HDR *ph;
    uint32_t  tmp;
    uint16_t  hdr_siz;
    uint8_t  *p, opt_len, opt_type;
    uint16_t  total_opt_len;

    pip  = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    ph  = (_TCP_HDR *)(pip->data);
    net2hl_yn_xn(&tmp,  &ph->ack) ;
    hdr_siz  = ((ph->len & 0xf0) >> 2);

    if (hdr_siz < 20)
        return E_ERR;
    else if (hdr_siz == 20)
        return E_OK;

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
                    return E_ERR;
                mss = (((uint16_t) * (p + 2)) << 8) | ((uint16_t) * (p + 3));
            }
        }
        p += opt_len;
        total_opt_len -= opt_len;
    }
    if (mss == 0)
        mss = _TCP_DEFAULT_MSS;

    if ((_tcp_tcb->status & (_TCPS_LISTEN | _TCPS_SYN_SENT)) && (mss < _tcp_tcb->mss))
        _tcp_tcb->mss = mss;

    return mss;
}


/***********************************************************************************************************************
* Function Name: _tcp_proc_data
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int16_t _tcp_proc_data(void)
{
    uint16_t hdr_siz;
    int32_t data_siz;
    int32_t free_siz;
    uint32_t seq;
    uint8_t  *p_tdata;
    _TCPS *p_tcps ;
    _IP_PKT *p_ip;

    p_ip = (_IP_PKT *)_ch_info_tbl->_p_rcv_buf.pip;
    p_tcps = (_TCPS *) & (((_IP_PKT *)_ch_info_tbl->_p_rcv_buf.pip)->data) ;

    hdr_siz  = ((p_tcps->th.len & 0xf0) >> (4 - 2));
    data_siz = net2hs(p_ip->iph.ip_total_len) - _IP_HLEN_MIN - hdr_siz;
    p_tdata  = ((uint8_t *)p_tcps) + hdr_siz;

    net2hl_yn_xn(&seq, &p_tcps->th.seq);
    if (seq != _tcp_tcb->rnxt)
    {
        _tcp_tcb->hdr_flg |= _TCPF_ACK;
        _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);
        return E_ERR;
    }
    if (data_siz == 0)
        return E_NO_RCV;

    _tcp_tcb->hdr_flg |= _TCPF_ACK;
    _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_TCP);

    free_siz = _tcp_tcb->rwin + tcp_ccep[_tcp_tcb->cepid-1].rbufsz - _tcp_tcb->rwin_curr;
    if (free_siz == 0)
        return E_NO_RCV;
    else if (data_siz > free_siz)
        data_siz = free_siz;

    memcpy(_tcp_tcb->rwin_curr, p_tdata, data_siz);
    _tcp_tcb->rdsize += data_siz;
    _tcp_tcb->rwin_curr += data_siz;

    _tcp_tcb->rnxt = seq + data_siz;

    if ((_tcp_tcb->req.type == _TCP_API_RCVDT)
            && (_tcp_tcb->req.stat == _TCP_API_STAT_INCOMPLETE))
        _tcp_cpy_rwdat();

    return E_OK;
}


/***********************************************************************************************************************
* Function Name: _tcp_rcv_fin
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int _tcp_rcv_fin(void)
{
    _IP_PKT  *pip;
    _TCP_HDR *ph;

    pip = (_IP_PKT *)(_ch_info_tbl->_p_rcv_buf.pip);
    ph = (_TCP_HDR *)(pip->data);

    if (!(ph->flg & _TCPF_FIN))
        return E_NO_RCV;

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
                            int32_t fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
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
                ;
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
    uint32_t  win_size;
    int32_t  diff;
    _TCPS  *p_tcps ;
    uint32_t  suna;

    p_tcps = (_TCPS *) & (((_IP_PKT *)_ch_info_tbl->_p_rcv_buf.pip)->data) ;
    ph  = &(p_tcps->th);

    /* Update remote window size */
    win_size = net2hs(ph->win_size);
    _tcp_tcb->swsize = win_size ;

    if (tcp_dack[_ch_info_tbl->_ch_num])
    {
        net2hl_yn_xn(&suna,  &ph->ack) ;
        if ((_tcp_tcb->snxt >= suna) && ((_tcp_tcb->snxt - suna) < 0x7fffffff))
        {
            diff = win_size - (_tcp_tcb->snxt - suna);
        }
        else if ((_tcp_tcb->snxt <  suna) && ((suna - _tcp_tcb->snxt) > 0x7fffffff))
        {
            diff = win_size - (0xffffffff - suna + _tcp_tcb->snxt + 1);
        }
        else
            diff = win_size;
    }
    else
    {
        if ((_tcp_tcb->snxt >= _tcp_tcb->suna) && ((_tcp_tcb->snxt - _tcp_tcb->suna) < 0x7fffffff))
        {
            diff = win_size - (_tcp_tcb->snxt - _tcp_tcb->suna);
        }
        else if ((_tcp_tcb->snxt <  _tcp_tcb->suna) && ((_tcp_tcb->suna - _tcp_tcb->snxt) > 0x7fffffff))
        {
            diff = win_size - (0xffffffff - _tcp_tcb->suna + _tcp_tcb->snxt + 1);
        }
        else
            diff = win_size;
    }
    if (diff < 0)
        diff = 0;
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
            if ((_tcp_tcb->rmt_rwsize >= _tcp_tcb->mss) || (_tcp_tcb->rmt_rwsize >= _tcp_tcb->sdsize) || (_tcp_tcb->rmt_rwsize != _tcp_tcb->swsize)/*(bug39 fix)*/)
            {
                if (tcp_dack[_ch_info_tbl->_ch_num] == 1)
                {
                    _tcp_tcb->retrans_q.rst_cnt = tcp_rt_tmo_rst[_ch_info_tbl->_ch_num];
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
    uint16_t  sum, len = 0;
#if defined(__GNUC__) || defined(GRSAKURA)
    int16_t  i;
#else
    int16_t  ret, i;
#endif
    uint8_t  *picmpdata;
    _ICMP_HDR *picmph_r, *picmph_s;
    _ICMP_PKT *picmp;
    _IP_PKT  *pip;
    uint8_t cur_req_stat;
    uint8_t cur_req_type;
    uint16_t counter = 0;

    _TCP_PHDR phdr;
#if defined(_ETHER)
    _ARP_ENTRY *ae;

    ae = _ether_arp_tbl[0];
#endif
    if (_tcp_pre_timer_cnt != _tcp_timer_cnt)
    {
        _tcp_pre_timer_cnt = _tcp_timer_cnt;

#if defined(_ETHER)
        for (counter = 0;counter < TCPUDP_CHANNEL_NUM; counter++)
        {
            ae = _ether_arp_tbl[counter];
            _ch_info_tbl = &_ch_info_head[counter];

///            for (i = 0; i < _ip_tblcnt[counter]; i++, ae++)
            for (i = 0; i < _ip_tblcnt; i++, ae++)
            {
                if (((ae->ae_state == AS_RESOLVED)
                        || (ae->ae_state == AS_PENDING)) && (ae->ae_ttl > 0))
                    ae->ae_ttl--;

                if (ae->ae_state == AS_RESOLVED)
                {
                    if (ae->ae_ttl == 0)
                        _ether_arp_del(ae);
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
#if defined(__GNUC__) || defined(GRSAKURA)
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
        for (counter = 0;counter < tcp_ccep_num; counter++)
        {
            _tcp_tcb = &head_tcb[counter];
            _ch_info_tbl = &_ch_info_head[tcp_ccep[counter].cepatr];

            cur_req_stat = _tcp_tcb->req.stat;
            cur_req_type = _tcp_tcb->req.type;

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
                            int32_t fncd = _tcp_api_type_to_fn(cur_req_type);
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
                _tcp_tcb->retrans_q.nxt_rtx_cnt--;
            if ((_tcp_tcb->retrans_q.rst_cnt != 0xffff) && (_tcp_tcb->retrans_q.rst_cnt > 0))
                _tcp_tcb->retrans_q.rst_cnt--;


            if (_tcp_tcb->zwp_noack_cnt != 0xffff)
                if (_tcp_tcb->zwp_noack_cnt > 0)
                    _tcp_tcb->zwp_noack_cnt--;
            if (_tcp_tcb->nxt_zero != 0xffff)
                if (_tcp_tcb->nxt_zero > 0)
                    _tcp_tcb->nxt_zero--;
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
                    _tcp_tcb->zwin_int = _TCP_RTO_INT_MAX;
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
                    _tcp_tcb->retrans_q.cur_int = _TCP_RTO_INT_MAX;
                _tcp_tcb->retrans_q.nxt_rtx_cnt = _tcp_tcb->retrans_q.cur_int;
                _tcp_tcb->flag |= (_TCBF_NEED_SEND | _TCBF_SND_RTX);
            }
        }

#endif /* _TCP */

#if defined(_UDP)
        _udp_api_tmout();
#endif

    }

    for (counter = 0; counter < TCPUDP_CHANNEL_NUM; counter++)
    {
        _ch_info_tbl = &_ch_info_head[counter];

#if defined(_ETHER)
        if (_ch_info_tbl->flag & _TCBF_SND_ARP_REP)
        {
#if defined(__GNUC__) || defined(GRSAKURA)
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
            sum = _cksum((uint8_t *)picmph_s, _ICMP_HLEN, 0);
            sum = ~hs2net(sum);
            sum = _cksum((uint8_t *)picmpdata, len, sum);
            picmph_s->chksum = hs2net(sum);

            _tx_hdr.hlen = _ICMP_HLEN;
            _tx_hdr.ihdr.tip.iph.ip_proto_num = _IPH_ICMP;
            _cpy_ipaddr(_tx_hdr.ihdr.tip.iph.ip_dst, pip->iph.ip_src);
            _cpy_ipaddr(_tx_hdr.ihdr.tip.iph.ip_src, _ch_info_tbl->_myipaddr);

#if defined(__GNUC__) || defined(GRSAKURA)
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
    }

    for (counter = 0; counter != tcp_ccep_num;counter++)
    {
        _tcp_tcb = &head_tcb[counter];
        _ch_info_tbl = &_ch_info_head[tcp_ccep[counter].cepatr];

#if defined(_TCP)
        if (_tcp_tcb->flag & _TCBF_NEED_SEND)
        {
            if (_tcp_tcb->flag & (_TCBF_SND_TCP | _TCBF_SND_RTX | _TCBF_SND_ZWIN))
            {
                _tcp_snd();
            }
        }
#endif
    }  /* for(counter = 0; counter != tcp_ccep_num;counter++) */
#if defined(_UDP)
    _udp_snd((_TCPUDP_PHDR*)&phdr);
#endif
}

#if defined(_TCP)
void _tcp_snd(void)
{
    uint32_t  seq;
    uint16_t  sum, tmp, len = 0, smode = 0;
    int16_t  ret;
    uint8_t  *pdata = NULL, flg = 0;
    _TCP_HDR *ptcph;
    _TCP_PHDR phdr;
    uint16_t  dack_flag = _tcp_tcb->flag;

    if (_tcp_tcb->flag & _TCBF_SND_ZWIN)
    {
        if (_tcp_tcb->nxt_zero == 0xffff)
        {
            _tcp_tcb->nxt_zero = _TCP_RTO_INIT;
            _tcp_tcb->zwin_int = _TCP_RTO_INIT;
            _tcp_tcb->flag &= ~_TCBF_SND_ZWIN;
            if (tcp_dack[_ch_info_tbl->_ch_num] == 1)
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
        if (tcp_dack[_ch_info_tbl->_ch_num] == 1)
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
        if (tcp_dack[_ch_info_tbl->_ch_num] == 1)
        {
            if (_tcp_tcb->sdsize > 0)
            {
                if ((_tcp_tcb->flag & _TCBF_SND_TCP) && ((_tcp_tcb->suna == _tcp_tcb->snxt) || (_tcp_tcb->flag & _TCBF_AVOID_DACK)))
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
                        len = _tcp_tcb->rmt_rwsize;
                }
                else if (_tcp_tcb->flag & _TCBF_SND_RTX)
                {
                    if ((_tcp_tcb->snxt >= _tcp_tcb->suna) &&
                            ((_tcp_tcb->snxt - _tcp_tcb->suna) < 0x7fffffff))
                        len = _tcp_tcb->snxt - _tcp_tcb->suna;
                    else if ((_tcp_tcb->snxt <  _tcp_tcb->suna) &&
                             ((_tcp_tcb->suna - _tcp_tcb->snxt) > 0x7fffffff))
                        len = 0xffffffff - _tcp_tcb->suna + _tcp_tcb->snxt + 1;
                    else
                        len = 0;
                }
            }
            else
            {
                len = 0;
            }
        }
        if (_tcp_tcb->flag & _TCBF_SND_TCP)
        {
            pdata = _tcp_tcb->nxtdat;
            seq  = _tcp_tcb->snxt;
            flg  |= _tcp_tcb->hdr_flg;
            smode = _TCBF_SND_TCP;

            if (!(((len == 0) && (_tcp_tcb->hdr_flg == _TCPF_ACK))
                    || (_tcp_tcb->hdr_flg & _TCPF_RST)))
            {

                if (tcp_dack[_ch_info_tbl->_ch_num] == 1)
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
                        _tcp_tcb->retrans_q.rst_cnt   = tcp_rt_tmo_rst[_ch_info_tbl->_ch_num];
                        _tcp_tcb->retrans_q.nxt_rtx_cnt  = _TCP_RTO_INIT;
                        _tcp_tcb->retrans_q.cur_int   = _TCP_RTO_INIT;
                        _tcp_tcb->retrans_q.seq    = seq;
                    }
                }
                else
                {
                    _tcp_tcb->retrans_q.data   = pdata;
                    _tcp_tcb->retrans_q.hdr_flg   = flg;
                    _tcp_tcb->retrans_q.rst_cnt   = tcp_rt_tmo_rst[_ch_info_tbl->_ch_num];
                    _tcp_tcb->retrans_q.nxt_rtx_cnt  = _TCP_RTO_INIT;
                    _tcp_tcb->retrans_q.cur_int   = _TCP_RTO_INIT;
                    _tcp_tcb->retrans_q.seq    = seq;
                }
            }
        }
        else if (_tcp_tcb->flag & _TCBF_SND_RTX)
        {
            pdata = _tcp_tcb->retrans_q.data;
            seq  = _tcp_tcb->retrans_q.seq;
            flg  |= _tcp_tcb->retrans_q.hdr_flg;
            smode = _TCBF_SND_RTX;
        }
    }
    ptcph = (_TCP_HDR *)(_tx_hdr.ihdr.tip.thdr.tcph);
    ptcph->sport = hs2net(_tcp_tcb->loc_port) ;
    ptcph->dport = hs2net(_tcp_tcb->rem_port) ;
    hl2net_yn_xn(&ptcph->ack, &_tcp_tcb->rnxt);
    hl2net_yn_xn(&ptcph->seq, &seq);
    if (flg & _TCPF_RST)
        ptcph->flg  = _TCPF_RST ;
    else
        ptcph->flg  = flg ;
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
    ptcph->win_size = hs2net(_tcp_tcb->rwin + tcp_ccep[_tcp_tcb->cepid-1].rbufsz - _tcp_tcb->rwin_curr) ;
    _cpy_ipaddr(phdr.sadr, _ch_info_tbl->_myipaddr);
    _cpy_ipaddr(phdr.dadr, _tcp_tcb->rem_ip);
    phdr.reserve = 0 ;
    phdr.prtcl = _IPH_TCP ;
    phdr.len = hs2net(len + (ptcph->len >> 2)) ;
    ptcph->cksum = 0 ;
    sum = _cksum((uint8_t *) & phdr, 12, 0);
    sum = ~hs2net(sum);
    sum = _cksum((uint8_t *)ptcph, (ptcph->len >> 2), sum);
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
        if (tcp_dack[_ch_info_tbl->_ch_num] == 1)
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
                        int32_t fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
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
                _tcp_tcb->zwp_noack_cnt = tcp_rt_tmo_rst[_ch_info_tbl->_ch_num];
        }
        if (tcp_dack[_ch_info_tbl->_ch_num] == 1)
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
                    int32_t fncd = _tcp_api_type_to_fn(_tcp_tcb->req.type);
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
                _tcp_return_listen();
            else
                _tcp_tcb->status = _tcp_tcb->nxt_status;
            _tcp_tcb->flag &= ~_TCBF_NEED_SEND;
            return;
        }
        if (smode == _TCBF_SND_TCP)
        {
            _tcp_tcb->snxt += len;
            if (_tcp_tcb->hdr_flg & (_TCPF_SYN | _TCPF_FIN))
                _tcp_tcb->snxt++;
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
                            _tcp_tcb->it_stat = _ITS_SHT;
                        if (_tcp_tcb->req.tmout == TMO_NBLK)
                        {
                            int32_t fncd;
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
                    _tcp_tcb->mslcnt = tcp_2msl[_ch_info_tbl->_ch_num];
            }

            else
            {
                _tcp_tcb->nxtdat += len;

            }
        }
        if (tcp_dack[_ch_info_tbl->_ch_num] == 1)
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
void _tcp_cancel_api(int ercd)
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
            /* RST送信手続き（送信後にTCB初期化） */
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
            int32_t fncd = _tcp_api_type_to_fn(areq->type);
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
    if (tcp_dack[ tcp_ccep[_ptcb->cepid-1].cepatr ] == 1)
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
    uint16_t tmp;

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
int _tcp_check_cepid_arg(ID cepid)
{
    int err = E_OK;
    if ((cepid <= 0) || (cepid > tcp_ccep_num))
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
int _tcp_check_len_arg(int len)
{
    int err = E_OK;
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
int  _tcp_check_tmout_arg(uint16_t api_type, int32_t tmout, _TCP_CB* pTcpcb)
{
    int errcode = E_OK;

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
uint16_t  _tcp_is_tcb_queue_over(uint16_t api_type, _TCB* pTcb,  _TCP_CB* pTcpcb)
{
    uint16_t bResult = FALSE;

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
uint16_t _tcp_call_callback(ID cepid, int32_t fncd, void *p_parblk)
{
    UH count;

    _TCP_CB *tmp;

    _TCP_CALLBACK_FUNC pCallback = _TCP_CB_GET_CALLBACK_FUNC_PTR(cepid);

    if (pCallback)
    {
        for (count = 0; count < tcp_ccep_num; count++)
        {
            tmp = GET_TCP_CALLBACK_INFO_PTR(count + 1);
            _TCP_CB_STAT_SET_CALLBACK_FLG(tmp->stat);
        }
        pCallback(_tcp_tcb->cepid, fncd, p_parblk);

        for (count = 0; count < tcp_ccep_num; count++)
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
int32_t _tcp_api_type_to_fn(uint16_t api_type)
{
    int32_t fncd = TFN_TCP_ALL;

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
int _tcp_recv_polling(_TCB* pTcb, uint8_t *buf, uint16_t size)
{
    uint16_t  api_dsiz;
    uint16_t  free_win;

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
        pTcb->rwin_bnry += api_dsiz;

    return api_dsiz;
}

void _tcp_init_callback_info(_TCP_CB* pCallbackInfo)
{
    memset((void*)pCallbackInfo, 0, sizeof(_TCP_CB));
}

#endif /* _TCP */


