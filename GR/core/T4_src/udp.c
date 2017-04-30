//=====================================================================//
/*!	@file
	@brief	udp.c @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "net_config.h"
#include <string.h>
#include "type.h"
#include "r_t4_itcpip.h"
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

#if defined(_UDP)
_UDP_CB  *_udp_cb;
extern const UB _udp_enable_zerochecksum[];
extern UB *data_link_buf_ptr;
#endif

extern _TX_HDR _tx_hdr;

#if defined(_ETHER)
extern UB *_ether_p_rcv_buff;
#endif /* _ETHER */


#if defined(_UDP)
/***********************************************************************************************************************
* Function Name: udp_rcv_dat
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int udp_rcv_dat(int cepid, T_IPVxEP *p_dstaddr, void *data, int len, int32_t tmout)
{
    int  ercd;
    _UDP_CB *pcb;
    _UDP_API_REQ *p;

    ercd = _udp_check_cepid_arg(cepid);
    if (ercd != E_OK)
    {
        return E_PAR;
    }

    ercd = _udp_check_len_arg(len);
    if (ercd != E_OK)
    {
        return E_PAR;
    }
    pcb = &_udp_cb[cepid - 1];
    p   = &pcb->req;

    if (pcb->stat & _UDP_CB_STAT_CALLBACK)
    {
        if (tmout != TMO_POL && tmout != TMO_NBLK)
        {
            return E_PAR;
        }
    }
    else
    {
        if (tmout == TMO_POL)
        {
            return E_PAR;
        }
    }

    if (tmout == TMO_POL)
    {
        if (pcb->stat & _UDP_CB_STAT_RCV)
        {
            if (pcb->rcv.len > len)
            {
                ercd = E_BOVR;
            }
            else
            {
                len = pcb->rcv.len;
                ercd = len;
            }
            memcpy(p_dstaddr, &pcb->rcv.dstaddr, sizeof(T_IPVxEP));
            memcpy(data, pcb->rcv.data, len);

            pcb->stat &= (~_UDP_CB_STAT_RCV);
        }
        else
        {
            ercd = E_TMOUT;
        }
    }
    else
    {

        if ((p->type != _UDP_API_NON) ||
                ((pcb->stat & (_UDP_CB_STAT_CALLBACK | _UDP_CB_STAT_LOCK))
                 == (_UDP_CB_STAT_CALLBACK | _UDP_CB_STAT_LOCK)))
        {
            return (E_QOVR);
        }

        dis_int();

        if ((pcb->stat & _UDP_CB_STAT_CALLBACK) == 0)
        {
            pcb->stat |= _UDP_CB_STAT_LOCK;
        }

        p->cepid = cepid;
        p->len  = len;
        p->data  = (uint8_t *)((uint32_t)data);
        p->cancel_flag = 0;
        p->tmout = tmout;
        p->ercd  = &ercd;
        p->p_dstaddr = p_dstaddr;
        p->type  = _UDP_API_RCV_DAT;
        p->stat  = _UDP_API_STAT_UNTREATED;

        if ((pcb->stat & _UDP_CB_STAT_CALLBACK) == 0)
        {
            pcb->stat &= (~_UDP_CB_STAT_LOCK);
        }

        ena_int();

        if (tmout == TMO_NBLK)
        {
            ercd = E_WBLK;
        }
        else
        {
            _udp_api_slp(pcb, cepid);
        }
    }
    return (ercd);
}


/***********************************************************************************************************************
* Function Name: udp_snd_dat
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int udp_snd_dat(int cepid, T_IPVxEP *p_dstaddr, void *data, int len, int32_t tmout)
{
    int  ercd;
    _UDP_CB *pcb;
    _UDP_API_REQ *p;

#if 1
    ercd = _udp_check_cepid_arg(cepid);
    if (ercd != E_OK)
    {
        return E_PAR;
    }

    ercd = _udp_check_len_arg(len);
    if (ercd != E_OK)
    {
        return E_PAR;
    }
#endif
    if (tmout == TMO_POL)
    {
        return E_PAR;
    }

    pcb = &_udp_cb[cepid - 1];
    p   = &pcb->req;

    if (pcb->stat & _UDP_CB_STAT_CALLBACK)
    {
        if (tmout != TMO_NBLK)
        {
            return E_PAR;
        }
    }

    if ((p->type != _UDP_API_NON) ||
            ((pcb->stat & (_UDP_CB_STAT_CALLBACK | _UDP_CB_STAT_LOCK))
             == (_UDP_CB_STAT_CALLBACK | _UDP_CB_STAT_LOCK)))
    {
        return (E_QOVR);
    }

    dis_int();

    if ((pcb->stat & _UDP_CB_STAT_CALLBACK) == 0)
    {
        pcb->stat |= _UDP_CB_STAT_LOCK;
    }

    p->cepid = cepid;
    p->len  = len;
    p->data  = (uint8_t *)((uint32_t)data);
    p->cancel_flag = 0;
    p->tmout = tmout;
    p->ercd  = &ercd;
    p->p_dstaddr = p_dstaddr;
    p->type  = _UDP_API_SND_DAT;
    p->stat  = _UDP_API_STAT_UNTREATED;

    if ((pcb->stat & _UDP_CB_STAT_CALLBACK) == 0)
    {
        pcb->stat &= (~_UDP_CB_STAT_LOCK);
    }

    ena_int();

    if (tmout == TMO_NBLK)
    {
        ercd = E_WBLK;
    }
    else
    {
        _udp_api_slp(pcb, cepid);
    }
    return (ercd);
}

/***********************************************************************************************************************
* Function Name: udp_can_cep
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int udp_can_cep(int cepid, int32_t fncd)
{
    int  ercd;
    _UDP_CB *pcb;
    _UDP_API_REQ *p;
    int cepid_tmp = cepid;
    int32_t fncd_tmp = fncd;

    ercd = _udp_check_cepid_arg(cepid);
    if (ercd != E_OK)
    {
        return E_PAR;
    }

    pcb = &_udp_cb[cepid - 1];
    p   = &pcb->req;

    if (pcb->stat & _UDP_CB_STAT_CALLBACK)
    {
        return E_NOSPT;
    }

    if ((pcb->stat & _UDP_CB_STAT_CALLBACK) == 0)
    {
        pcb->stat |= _UDP_CB_STAT_LOCK;
    }


    ercd = E_OBJ;

    dis_int();

    if (((cepid_tmp == p->cepid) && (fncd_tmp == _udp_api_type_to_fn(p->type))) || \
            ((cepid_tmp == p->cepid) && (fncd_tmp == TFN_UDP_ALL) && (_udp_api_type_to_fn(p->type) == TFN_UDP_SND_DAT)) || \
            ((cepid_tmp == p->cepid) && (fncd_tmp == TFN_UDP_ALL) && (_udp_api_type_to_fn(p->type) == TFN_UDP_RCV_DAT)))
    {
        ercd = E_OK;

        p->cancel_flag = 1;
    }

    ena_int();

    if ((pcb->stat & _UDP_CB_STAT_CALLBACK) == 0)
    {
        pcb->stat &= (~_UDP_CB_STAT_LOCK);
    }

    return (ercd);
}

/***********************************************************************************************************************
* Function Name: _udp_rcv
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _udp_rcv(_IP_HDR *piph, _UDP_HDR *pudph)
{
    int16_t  i;
    _TCPUDP_PHDR ph;
    uint16_t  dport;
    _UDP_CB  *pucb;
    uint16_t  cksum_tmp;

    cksum_tmp = _tcpudp_cksum(piph, &ph);
    if (pudph->cksum != 0)
    {
        if (pudph->cksum == 0xffff)
        {
            if (cksum_tmp == 0xffff)
            {
                cksum_tmp = 0;
            }
        }
        if (cksum_tmp != 0)
        {
            report_error(_ch_info_tbl->_ch_num, RE_UDP_HEADER1, data_link_buf_ptr);
            goto __err__udp_rcv;
        }
    }
    else
    {
        _tcpudp_cksum(piph, &ph);
        if (_udp_enable_zerochecksum[_ch_info_tbl->_ch_num] != 0)
        {
            report_error(_ch_info_tbl->_ch_num, RE_UDP_HEADER2, data_link_buf_ptr);
            goto __err__udp_rcv;
        }
    }
    dport = net2hs(pudph->dst_port);

    for (i = 0; i < udp_ccep_num; i++)
    {
        if ((udp_ccep[i].myaddr.portno == dport) && (_ch_info_tbl->_ch_num == udp_ccep[i].cepatr))
        {
            pucb = &_udp_cb[i];
            _udp_rcv_sub(pucb, pudph, &ph);
            break;
        }
    }

    if (i == udp_ccep_num)
    {
        report_error(_ch_info_tbl->_ch_num, RE_UDP_HEADER3, data_link_buf_ptr);
    }

__err__udp_rcv:
    rcv_buff_release(_ch_info_tbl->_ch_num);
    _ch_info_tbl->_p_rcv_buf.len = 0;
}

/***********************************************************************************************************************
* Function Name: _udp_rcv_sub
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int16_t _udp_rcv_sub(_UDP_CB *pucb, _UDP_HDR *udph, _TCPUDP_PHDR *ph)
{
    T_UDP_CCEP const *pcep;
    int    ercd;
    int32_t    fncd;
    uint16_t   sport;
    uint16_t   saddr[IP_ALEN/2];
    uint16_t   len;
    uint8_t   *data;
    uint16_t   ip_dlen;
    ID    cepid;
    UH    count;
    _UDP_CB   *tmp;

    fncd = 0;
    if ((pucb->req.type == _UDP_API_RCV_DAT)
            && (pucb->req.stat == _UDP_API_STAT_INCOMPLETE))
    {
        if (pucb->req.tmout == TMO_NBLK)
        {
            fncd = TFN_UDP_RCV_DAT;
        }
    }
    else
    {
        fncd = TEV_UDP_RCV_DAT;
    }

    len = net2hs(udph->len);
    ip_dlen = net2hs(ph->len);
    if ((len < sizeof(_UDP_HDR)) || (ip_dlen < sizeof(_UDP_HDR)))
    {
        return (-1);
    }
    if (ip_dlen < len)
    {
        return (-1);
    }
    len  -= sizeof(_UDP_HDR);
    ercd  = len;
    sport = net2hs(udph->src_port);
    data  = (uint8_t*)udph + sizeof(_UDP_HDR);
    net2hl_yn_xn(saddr, ph->src_addr);

    if (fncd != TEV_UDP_RCV_DAT)
    {
        if (len > pucb->req.len)
        {
            ercd = E_BOVR;
            len = pucb->req.len;
        }

        memcpy(pucb->req.data, data, len);
        _cpy_ipaddr(&pucb->req.p_dstaddr->ipaddr, saddr);
        pucb->req.p_dstaddr->portno = sport;

        pucb->req.type = _UDP_API_NON;
    }
    else
    {
        pucb->rcv.data = data;
        _cpy_ipaddr(&pucb->rcv.dstaddr.ipaddr, saddr);
        pucb->rcv.dstaddr.portno = sport;
        pucb->rcv.len = len;
        pucb->stat |= _UDP_CB_STAT_RCV;
    }

    cepid = (pucb   - _udp_cb) + 1;
    pcep = &udp_ccep[cepid - 1];
    if (fncd == 0)
    {
        *(pucb->req.ercd) = ercd;

        _udp_api_wup(pucb, cepid);
    }
    else
    {
        if (pcep->callback != NULL)
        {
            for (count = 0; count < udp_ccep_num; count++)
            {
                tmp = &_udp_cb[count];
                tmp->stat |= _UDP_CB_STAT_CALLBACK;
            }
            (*pcep->callback)(cepid, fncd, (void *)&ercd);
        }
        for (count = 0; count < udp_ccep_num; count++)
        {
            tmp = &_udp_cb[count];
            tmp->stat &= (~(_UDP_CB_STAT_CALLBACK | _UDP_CB_STAT_RCV));
        }
    }
    return (0);
}

/***********************************************************************************************************************
* Function Name: _udp_snd
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _udp_snd(_TCPUDP_PHDR *ph)
{
    int    ercd;
    int32_t    fncd;
    T_UDP_CCEP const *pcep;
    int16_t   len;
    uint16_t   sum16;
    _UDP_CB   *pucb;
    _UDP_API_REQ *pureq;
    _UDP_HDR  *udph;
    int16_t   ret;
    int16_t   i;
    UH    count;
    _UDP_CB   *tmp;

    for (i = 0; i < udp_ccep_num; i++)
    {
        pucb  = &_udp_cb[i];
        pureq = &pucb->req;
        _ch_info_tbl = &_ch_info_head[udp_ccep[i].cepatr];

        if (pucb->stat & _UDP_CB_STAT_SND)
        {
            udph = (_UDP_HDR *)(_tx_hdr.ihdr.tip.thdr.udph);
            udph->src_port = hs2net(udp_ccep[i].myaddr.portno);
            udph->dst_port = hs2net(pureq->p_dstaddr->portno);
            len    = pureq->len + sizeof(_UDP_HDR);
            udph->len  = hs2net(len);
            udph->cksum  = 0;

            ph->len      = udph->len;
            ph->reserve  = 0;
            hl2net_yn_xn(&ph->dst_addr, &pureq->p_dstaddr->ipaddr);
            _cpy_ipaddr(ph->src_addr, _ch_info_tbl->_myipaddr);
            ph->proto = _IPH_UDP;

            sum16 = _cksum((uint8_t *)ph,   sizeof(_TCPUDP_PHDR), 0);
            sum16 = _cksum((uint8_t *)udph, sizeof(_UDP_HDR), ~hs2net(sum16));
            sum16 = _cksum((uint8_t *)pureq->data, pureq->len, ~hs2net(sum16));
            udph->cksum = hs2net(sum16);

            if (udph->cksum == 0)
            {
                udph->cksum = 0xffff;
            }

            _tx_hdr.hlen = sizeof(_UDP_HDR);
            _cpy_ipaddr(_tx_hdr.ihdr.tip.iph.ip_dst, ph->dst_addr);
            _cpy_ipaddr(_tx_hdr.ihdr.tip.iph.ip_src, ph->src_addr);
            _tx_hdr.ihdr.tip.iph.ip_proto_num = _IPH_UDP;
            ret = _ip_snd(pureq->data, pureq->len);

            if (ret >= 0 || -2 == ret)
            {
                if (-2 == ret)
                {
                    ercd = E_CLS;
                }
                else
                {
                    ercd = pureq->len;
                }
                pucb->stat &= ~(_UDP_CB_STAT_SND);

                if (pureq->tmout == TMO_NBLK)
                {
                    pureq->stat = _UDP_API_STAT_COMPLETE;
                    pureq->type = _UDP_API_NON;
                    pcep = &udp_ccep[i];
                    if (pcep->callback != NULL)
                    {
                        for (count = 0; count < udp_ccep_num; count++)
                        {
                            tmp = &_udp_cb[count];
                            tmp->stat |= _UDP_CB_STAT_CALLBACK;
                        }
                        fncd = TFN_UDP_SND_DAT;
                        (*pcep->callback)(i + 1, fncd, (void *)&ercd);
                    }
                    for (count = 0; count < udp_ccep_num; count++)
                    {
                        tmp = &_udp_cb[count];
                        tmp->stat &= ~(_UDP_CB_STAT_CALLBACK);
                    }
                }
                else
                {
                    *(pureq->ercd) = ercd;

                    _udp_api_wup(pucb, i + 1);
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: _udp_api_slp
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _udp_api_slp(_UDP_CB *pcb, ID id)
{
    do
    {
        udp_api_slp(id);
    }
    while (pcb->req.stat != _UDP_API_STAT_COMPLETE);

    pcb->req.type = _UDP_API_NON;
}

/***********************************************************************************************************************
* Function Name: _udp_api_wup
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _udp_api_wup(_UDP_CB *pcb, ID id)
{
    if (pcb->req.stat != _UDP_API_STAT_COMPLETE)
    {
        pcb->req.stat = _UDP_API_STAT_COMPLETE;
        udp_api_wup(id);
    }
}


/***********************************************************************************************************************
* Function Name: _proc_udp_api
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _proc_udp_api()
{
    _UDP_CB      *pucb;
    _UDP_API_REQ *pureq;
    int16_t  i;
    int   ercd;
    int32_t   fn;
    UH    count;
    _UDP_CB   *tmp;

    for (i = 0; i < udp_ccep_num; i++)
    {
        pucb  = &_udp_cb[i];
        pureq = &pucb->req;
        if (pureq->type != _UDP_API_NON)
        {
            if (pureq->stat == _UDP_API_STAT_UNTREATED)
            {
                pureq->stat = _UDP_API_STAT_INCOMPLETE;
                if (pureq->type == _UDP_API_SND_DAT)
                {
                    pucb->stat |= _UDP_CB_STAT_SND;
                }
            }
            if (pureq->cancel_flag == 1)
            {
                fn = _udp_api_type_to_fn(pureq->type);
                memset(pucb, 0, sizeof(_UDP_CB));
                ercd = E_RLWAI;
                for (count = 0; count < udp_ccep_num; count++)
                {
                    tmp = &_udp_cb[count];
                    tmp->stat |= _UDP_CB_STAT_CALLBACK;
                }
                (udp_ccep[i].callback)(i + 1 /* cepid */, fn, (void *)&ercd);
                for (count = 0; count < udp_ccep_num; count++)
                {
                    tmp = &_udp_cb[count];
                    tmp->stat &= ~(_UDP_CB_STAT_CALLBACK);
                }
                pureq->stat = _UDP_API_STAT_COMPLETE;
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: _udp_init
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _udp_init(UW **workpp)
{
    _udp_cb = (_UDP_CB *)(*workpp);
    memset(_udp_cb, 0, sizeof(_UDP_CB) * udp_ccep_num);
    *workpp = (UW *)((uint8_t *)(*workpp) + (sizeof(_UDP_CB) * udp_ccep_num));
}


/***********************************************************************************************************************
* Function Name: _udp_api_tmout
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
void _udp_api_tmout()
{
    _UDP_API_REQ *pureq;
    int16_t  i;

    for (i = 0; i < udp_ccep_num; i++)
    {
        pureq = &_udp_cb[i].req;
        if (pureq->type != _UDP_API_NON)
        {
            if (pureq->stat == _UDP_API_STAT_INCOMPLETE)
            {
                if (pureq->tmout > 0)
                {
                    pureq->tmout--;
                }
                if (pureq->tmout == 0)
                {
                    *(pureq->ercd) = E_TMOUT;

                    _udp_api_wup(&_udp_cb[i], i + 1);
                }
            }
        }
    }
}
#endif

/***********************************************************************************************************************
* Function Name: _tcpudp_cksum
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
uint16_t _tcpudp_cksum(_IP_HDR *piph, _TCPUDP_PHDR *ph)
{
    uint16_t   sum16;
    uint16_t   len;

    _cpy_ipaddr(ph->src_addr, piph->ip_src);
    _cpy_ipaddr(ph->dst_addr, piph->ip_dst);
    ph->reserve = 0;
    ph->proto = piph->ip_proto_num;
    len    = piph->ip_total_len;

    len = net2hs(len);
    len -= _IP_HLEN_MIN;
    ph->len = hs2net(len);

    sum16 = _cksum((uint8_t *)ph, sizeof(_TCPUDP_PHDR), 0);
    sum16 = _cksum((uint8_t *)piph + sizeof(_IP_HDR), len, ~hs2net(sum16));

    return (sum16);
}

/***********************************************************************************************************************
* Function Name: _udp_api_type_to_fn
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int32_t _udp_api_type_to_fn(uint16_t api_type)
{
    int32_t fncd = TFN_TCP_ALL;

    switch (api_type)
    {
        case _UDP_API_SND_DAT:
            fncd = TFN_UDP_SND_DAT;
            break;
        case _UDP_API_RCV_DAT:
            fncd = TFN_UDP_RCV_DAT;
            break;
        default:
            break;
    }

    return fncd;
}

/***********************************************************************************************************************
* Function Name: _udp_check_cepid_arg
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int _udp_check_cepid_arg(ID cepid)
{
    int err = E_OK;
    if ((cepid <= 0) || (cepid > udp_ccep_num))
    {
        err = E_PAR;
    }
    return err;
}

/***********************************************************************************************************************
* Function Name: _udp_check_len_arg
* Description  :
* Arguments    :
* Return Value :
***********************************************************************************************************************/
int _udp_check_len_arg(int len)
{
    int err = E_OK;
    if (len < 0)
    {
        err = E_PAR;
    }
    return err;
}


