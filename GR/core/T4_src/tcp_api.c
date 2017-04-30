//=====================================================================//
/*!	@file
	@brief	TCP/UDP api @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdio.h>
#include <string.h>
#include "tcp_api.h"

#if defined(_ETHER)
#include "ether.h"
#elif defined(_PPP)
#include "ppp.h"
#endif

#include "config_tcpudp.h"

#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "core/driver/driver.h"

extern _TCB   *_tcp_tcb;
extern _TCB   *head_tcb;
extern UH _tcp_timer_cnt;
extern UH _tcp_pre_timer_cnt;

#if defined(_ETHER)
extern UH const _ip_tblcnt;
_ARP_ENTRY   **_ether_arp_tbl;
#endif
#if defined(_PPP)
extern uint16_t ppp_sio_status;
extern _PPP_API_REQ _ppp_api_req;
#endif


static void tcpudp_api_slp_(int cepid)
{
	do {
		tcp_api_slp(cepid);
	} while (head_tcb[cepid-1].req.stat != _TCP_API_STAT_COMPLETE) ;
}


static void tcpudp_clr_req_(int cepid)
{
	head_tcb[cepid-1].req.type = 0;
	head_tcb[cepid-1].req.stat = _TCP_API_STAT_INIT;
	head_tcb[cepid-1].req.tmout = 0;
	head_tcb[cepid-1].req.error = NULL;
	head_tcb[cepid-1].req.d.dr.dtsiz = 0;
	head_tcb[cepid-1].req.d.dr.datap = NULL;
	head_tcb[cepid-1].req.flag = 0;
}


static int tcpudp_api_req_(int cepid)
{
    int err = E_INI;

    head_tcb[cepid-1].req.error = &err;
    head_tcb[cepid-1].req.stat = _TCP_API_STAT_UNTREATED;
    head_tcb[cepid-1].req.flag = 0;

    if (head_tcb[cepid-1].req.tmout == TMO_NBLK)
    {
        _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

        pTcbCb->req.ercd = E_INI;
        head_tcb[cepid-1].req.error = &pTcbCb->req.ercd;

        return E_WBLK;
    }
    tcpudp_api_slp_(cepid);
    tcpudp_clr_req_(cepid);
    return err;
}


void tcpudp_open(uint32_t *workp)
{
	uint32_t *currp = workp;

	_tcp_timer_cnt = 0;
	_tcp_pre_timer_cnt = 0;

	_tcp_tcb = (_TCB*)currp;
	head_tcb = (_TCB*)currp;
	currp = (uint32_t*)((uint8_t*)currp + (sizeof(_TCB) * tcp_ccep_num));

#if defined(_TCP)
	for(int counter = 0; counter < tcp_ccep_num; counter++) {
		tcpudp_clr_req_(counter + 1);

		_tcp_init_callback_info(&head_tcb[counter].callback_info);

		_tcp_tcb[counter].rwin = (uint8_t*)currp;

		currp = (uint32_t *)((uint8_t *)currp + tcp_ccep[counter].rbufsz);
		uint16_t rem = tcp_ccep[counter].rbufsz % 4;
		if(rem != 0) {
			currp = (uint32_t *)((uint8_t *)currp + (4 - rem));
		}
		_tcp_tcb[counter].cepid = counter + 1;
		_tcp_init_tcb(&_tcp_tcb[counter]);
    }
#endif

#if defined(_UDP)
	_udp_init(&currp);
#endif

	_ch_info_tbl = (_CH_INFO*)currp;
	_ch_info_head = (_CH_INFO*)currp;
	for(int counter = 0;counter < TCPUDP_CHANNEL_NUM; counter++) {
		_ch_info_head[counter]._ch_num = counter;
		_ch_info_head[counter].flag = 0;
		_ch_info_head[counter]._rcvd = 0;

		memset(&_ch_info_head[counter]._p_rcv_buf, 0, sizeof(_P_RCV_BUF));

		memcpy(_ch_info_head[counter]._myipaddr,   tcpudp_env[counter].ipaddr, IP_ALEN);
		memcpy(_ch_info_head[counter]._mymaskaddr, tcpudp_env[counter].maskaddr, IP_ALEN);
		memcpy(_ch_info_head[counter]._mygwaddr,   tcpudp_env[counter].gwaddr, IP_ALEN);
	}
	currp = (uint32_t*)((uint8_t*)currp + (sizeof(_CH_INFO) * TCPUDP_CHANNEL_NUM));

#if defined(_PPP)
	ppp_sio_status    = 0;
	memset(&_ppp_api_req, 0, sizeof(_ppp_api_req));
	_ppp_init();

#elif defined(_ETHER)
	_ether_arp_tbl = (_ARP_ENTRY **)currp;

	currp = (uint32_t *)((uint8_t *)currp + TCPUDP_CHANNEL_NUM * sizeof(_ARP_ENTRY *));

	for(int counter = 0; counter < TCPUDP_CHANNEL_NUM; counter++) {
		*(_ether_arp_tbl + counter) = ((_ARP_ENTRY *)currp);
///		currp = (uint32_t *)((uint8_t *)currp + _ip_tblcnt[counter] * sizeof(_ARP_ENTRY));
		currp = (uint32_t *)((uint8_t *)currp + _ip_tblcnt * sizeof(_ARP_ENTRY));
	}

	_ether_arp_init();
#endif

	tcpudp_act_cyc(1);
}


void tcpudp_close(void)
{
	tcpudp_act_cyc(0);
}


static void get_align_memory_size_(uint32_t *ramsize)
{
	uint32_t tmp = *ramsize & 0x3;
	if(tmp != 0) {
		*ramsize += (4 - tmp);
	}
}

#if defined(_TCP)
static uint32_t get_tcp_memory_size_(void)
{
	uint32_t ramsize = 0;
    for(int counter = 0; counter < tcp_ccep_num; counter++) {
		ramsize += tcp_ccep[counter].rbufsz;
		ramsize += 4 - (tcp_ccep[counter].rbufsz % 4);
	}
    get_align_memory_size_(&ramsize);

    ramsize += (sizeof(_TCB) * tcp_ccep_num);

    get_align_memory_size_(&ramsize);

    return ramsize;
}
#endif

#if defined(_UDP)
static uint32_t get_udp_memory_size_(void)
{
    uint32_t ramsize = 0;
    ramsize += (sizeof(_UDP_CB) * udp_ccep_num);
    return ramsize;
}
#endif


static uint32_t get_ip_memory_size_(void)
{
    uint32_t ramsize = 0;
    ramsize += (TCPUDP_CHANNEL_NUM * sizeof(_CH_INFO));
    return ramsize;
}


#if defined(_ETHER)
static uint32_t get_ether_memory_size_(void)
{
	uint32_t ramsize = 0;
	ramsize += TCPUDP_CHANNEL_NUM * sizeof(_ARP_ENTRY *);
	for(int count = 0; count < TCPUDP_CHANNEL_NUM; count++) {
///		ramsize += (_ip_tblcnt[count] * sizeof(_ARP_ENTRY));
		ramsize += (_ip_tblcnt * sizeof(_ARP_ENTRY));
	}
    get_align_memory_size_(&ramsize);

	return ramsize;
}
#endif


uint32_t tcpudp_get_memory_size(void)
{
	uint32_t ramsize = 0;

#if defined(_TCP)
	ramsize += get_tcp_memory_size_();
#endif
#if defined(_UDP)
	ramsize += get_udp_memory_size_();
#endif

	ramsize += get_ip_memory_size_();

#if defined(_ETHER)
	ramsize += get_ether_memory_size_();
#endif

	return ramsize;
}

#if defined(_TCP)
int tcp_acp_cep(int cepid, int repid, T_IPVxEP *p_dstaddr, int32_t tmout)
{
    int err;
    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
    }

    if ((repid <= 0) || (repid > tcp_crep_num))
    {
        return E_PAR;
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

    head_tcb[cepid-1].req.type = _TCP_API_ACPCP;
    head_tcb[cepid-1].req.tmout = tmout;
    head_tcb[cepid-1].req.d.cnr.dstaddr = p_dstaddr;
    head_tcb[cepid-1].req.d.cnr.repid = repid;

    err = tcpudp_api_req_(cepid);

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    return err;
}


int tcp_con_cep(int cepid, T_IPVxEP *p_myaddr, T_IPVxEP *p_dstaddr, int32_t tmout)
{
    _TCP_CB *pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    int err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
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

    head_tcb[cepid-1].req.type = _TCP_API_CONCP;
    head_tcb[cepid-1].req.tmout = tmout;
    head_tcb[cepid-1].req.d.cnr.dstaddr = p_dstaddr;

    if ((p_myaddr == (T_IPVxEP *)NADR) || (p_myaddr->portno == TCP_PORTANY))
        head_tcb[cepid-1].req.d.cnr.my_port = 0;
    else
        head_tcb[cepid-1].req.d.cnr.my_port = p_myaddr->portno;

    err = tcpudp_api_req_(cepid);

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    return err;
}


int tcp_sht_cep(int cepid, int32_t tmout)
{
    int ret = _tcp_check_cepid_arg(cepid);
	if(ret != E_OK) {
		return E_PAR;
	}

	_TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);
	ret = _tcp_check_tmout_arg(_TCP_API_CLSCP, tmout, pTcbCb);
	if(ret != E_OK && ret != E_WBLK) {
		return ret;
	}

	if(_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat)) {
		return E_NOSPT;
	}

	if(_tcp_is_tcb_queue_over(_TCP_API_SHTCP, &head_tcb[cepid-1], pTcbCb)) {
		return E_QOVR;
	}

	if(ret == E_WBLK) {
		if(!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat)) {
			_TCP_CB_STAT_SET_API_LOCK_FLG(pTcbCb->stat);
		}
	}
	head_tcb[cepid-1].req.type = _TCP_API_SHTCP;
	head_tcb[cepid-1].req.tmout = tmout;

///	if(_TCP_CB_GET_CALLBACK_FUNC_PTR(cepid)) {
///		head_tcb[cepid-1].req.tmout = TMO_NBLK;
///	}

	ret = tcpudp_api_req_(cepid);
	if(ret == E_WBLK) {
		if(!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat)) {
			_TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
		}
	}
	return ret;
}


int tcp_cls_cep(int cepid, int32_t tmout)
{
	int ret = _tcp_check_cepid_arg(cepid);
	if(ret != E_OK) {
		return E_PAR;
	}

	_TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);
	ret = _tcp_check_tmout_arg(_TCP_API_CLSCP, tmout, pTcbCb);
	if(ret != E_OK && ret != E_WBLK) {
		return ret;
	}

	if(_tcp_is_tcb_queue_over(_TCP_API_CLSCP, &head_tcb[cepid-1], pTcbCb)) {
		return E_QOVR;
	}
	if(ret == E_WBLK) {
		if(!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat)) {
			_TCP_CB_STAT_SET_API_LOCK_FLG(pTcbCb->stat);
		}
	}

	head_tcb[cepid-1].req.type = _TCP_API_CLSCP;
	head_tcb[cepid-1].req.tmout = tmout;

	ret = tcpudp_api_req_(cepid);
	if(ret == E_WBLK) {
		if(!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat)) {
			_TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
		}
	}
    return ret;
}


int tcp_send_data(int cepid, const void *data, int len, int32_t tmout)
{
    int err;
    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
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

    head_tcb[cepid-1].req.type = _TCP_API_SNDDT;
    head_tcb[cepid-1].req.tmout = tmout;
    head_tcb[cepid-1].req.d.dr.dtsiz = len;
    head_tcb[cepid-1].req.d.dr.datap = (uint8_t *)((uint32_t)data);

    err = tcpudp_api_req_(cepid);

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
        }
    }

    return err;
}


int tcp_recv_data(int cepid, void *data, int len, int32_t tmout)
{
    int err;
    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
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
            err = _tcp_recv_polling(&head_tcb[cepid-1], (uint8_t*)((uint32_t)data), len);
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

    head_tcb[cepid-1].req.type = _TCP_API_RCVDT;
    head_tcb[cepid-1].req.tmout = tmout;
    head_tcb[cepid-1].req.d.dr.dtsiz = len;
    head_tcb[cepid-1].req.d.dr.datap = (uint8_t *)((uint32_t)data);

    err = tcpudp_api_req_(cepid);

    if (err == E_WBLK)
    {
        if (!_TCP_CB_STAT_IS_VIA_CALLBACK(pTcbCb->stat))
        {
            _TCP_CB_STAT_CLEAR_API_LOCK_FLG(pTcbCb->stat);
        }
    }
    return err;
}


int tcp_can_cep(int cepid, int32_t fncd)
{
    int err;
    int32_t fn;

    _TCP_CB* pTcbCb = GET_TCP_CALLBACK_INFO_PTR(cepid);

    err = _tcp_check_cepid_arg(cepid);
    if (err != E_OK)
    {
        return E_PAR;
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




#if defined(_TEST_LIBRARY)
/***************************************************************************************
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
***************************************************************************************/
TCP_API_STAT tcp_read_stat(int cepid)
{
    int err = _tcp_check_cepid_arg(cepid);
    if(err != E_OK) {
        return TCP_API_STAT_INVALID;
    }

	TCP_API_STAT ret = TCP_API_STAT_OTHER;
    switch (head_tcb[cepid - 1].status)
    {
        case _TCPS_CLOSED:
            ret = TCP_API_STAT_CLOSED;
            break;
        case _TCPS_LISTEN:
            ret = TCP_API_STAT_LISTEN;
            break;
        case _TCPS_ESTABLISHED:
            ret = TCP_API_STAT_ESTABLISHED;
            break;
        case _TCPS_FIN_WAIT2:
            ret = TCP_API_STAT_FIN_WAIT2;
            break;
        case _TCPS_CLOSE_WAIT:
            ret = TCP_API_STAT_CLOSE_WAIT;
            break;
        case _TCPS_SYN_SENT:
            ret = TCP_API_STAT_SYN_SENT;
            break;
        case _TCPS_SYN_RECEIVED:
            ret = TCP_API_STAT_SYN_RECEIVED;
            break;
        case _TCPS_FIN_WAIT1:
            ret = TCP_API_STAT_FIN_WAIT1;
            break;
        case _TCPS_LAST_ACK:
            ret = TCP_API_STAT_LAST_ACK;
            break;
        case _TCPS_CLOSING:
            ret = TCP_API_STAT_CLOSING;
            break;
        case _TCPS_TIME_WAIT:
            ret = TCP_API_STAT_TIME_WAIT;
            break;
        default:
            ret = TCP_API_STAT_OTHER;
            break;
    }
    return ret;
}


extern void _tcp_init_tcb(_TCB *_ptcb);


/***************************************************************************************
* Function Name: tcp_force_clr
* Description  : force break TCP TMO_FEVR loop
* Arguments    : cepid
* Return Value : E_OK force clear OK
*       : E_PAR invalid cepid
***************************************************************************************/
int tcp_force_clr(int cepid)
{
    int err = E_PAR;

    // cepid 引数をチェックする。
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


/***************************************************************************************
* Function Name: udp_force_clr
* Description  : force break UDP TMO_FEVR loop
* Arguments    : cepid
* Return Value : E_OK force clear OK
*       : E_PAR invalid cepid
***************************************************************************************/
int udp_force_clr(int cepid)
{
    int err = E_PAR;
    _UDP_CB      *pucb;
    _UDP_API_REQ *pureq;

    // cepid 引数をチェックする。
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


/***************************************************************************************
* Function Name: tcp_set_mss
* Description  : MSS setting function
* Arguments    : cepid
* Return Value : E_OK setting OK
*       : E_PAR invalid cepid
***************************************************************************************/
int tcp_set_mss(int cepid, uint16_t mss)
{
    int err = E_PAR;

    // cepid 引数をチェックする。
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



