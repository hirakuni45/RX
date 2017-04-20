#pragma once
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
* File Name    : tcp.h
* Version      : 1.0
* Description  : Processing for TCP protocol header file
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 01.04.2014 1.00     First Release
***********************************************************************************************************************/
#if defined(__GNUC__) || defined(GRSAKURA)
#include "t4define.h"
#endif

#define _TCPH_LEN  20 // minimum TCP  header length (in bytes)
#define _UDPH_LEN  8 // UDP header length (in bytes)

#define E_NO_RCV  -10
#define E_RST_RCV  -2
#define E_ERR   -2
#define E_SYN_OK   0
#define E_INI   -1

#define _TCP_DEFAULT_MSS 536

/* ====== TCB ===== */
#define _ITS_NORMAL 0
#define _ITS_SHT 1
#define _ITS_RST 2

#define _TCP_RTO_INIT  (2 * 100)  // 2 sec.
#define _TCP_RTO_INT_MAX (60 * 100)  // 1 min.

#define _TCPS_CLOSED  0x0000
#define _TCPS_LISTEN  0x0001
#define _TCPS_SYN_SENT  0x0002
#define _TCPS_SYN_RECEIVED 0x0004
#define _TCPS_ESTABLISHED 0x0008
#define _TCPS_FIN_WAIT1  0x0010
#define _TCPS_FIN_WAIT2  0x0020
#define _TCPS_CLOSE_WAIT 0x0040
#define _TCPS_LAST_ACK  0x0080
#define _TCPS_CLOSING  0x0100
#define _TCPS_TIME_WAIT  0x0200

#define  _TCPF_URG     0x20
#define  _TCPF_ACK     0x10
#define  _TCPF_PSH     0x08
#define  _TCPF_RST     0x04
#define  _TCPF_SYN     0x02
#define  _TCPF_FIN     0x01

#define _TCBF_NEED_SEND  0x0001
#define _TCBF_PEND_ARP  0x0002
#define _TCBF_PEND_ICMP  0x0004
#define _TCBF_PEND_ZWIN  0x0008
#define _TCBF_PEND_DRV  0x0010
#define _TCBF_NEED_INIT  0x0020
#define _TCBF_FIN_RCVD  0x0040
#define _TCBF_NEED_API  0x0080
#define _TCBF_SND_ICMP  0x0100
#define _TCBF_SND_TCP  0x0200
#define _TCBF_SND_RTX  0x0400
#define _TCBF_SND_ZWIN  0x0800
#define _TCBF_SND_ARP_REQ 0x1000
#define _TCBF_SND_ARP_REP 0x2000
#define _TCBF_RET_LISTEN 0x4000
#define _TCBF_AVOID_DACK 0x8000
#define _TCBF_14  0x0000

#define _TCP_API_ACPCP 1 // tcp_acp_cep()
#define _TCP_API_CONCP 2 // tcp_con_cep()
#define _TCP_API_SHTCP 3 // tcp_sht_cep()
#define _TCP_API_CLSCP 4 // tcp_cls_cep()
#define _TCP_API_SNDDT 5 // tcp_snd_dat()
#define _TCP_API_RCVDT 6 // tcp_rcv_dat()
#define _TCP_API_CANCP 7 // tcp_can_cep()

#define _TCP_API_STAT_INIT   0
#define _TCP_API_STAT_UNTREATED  1
#define _TCP_API_STAT_INCOMPLETE 2
#define _TCP_API_STAT_COMPLETE  3
#define _TCP_API_STAT_TMOUT   4

#define _TCP_API_FLAG_CANCELED  1

typedef struct
{
    uint16_t  my_port;
    T_IPVxEP *dstaddr;
    uint16_t  repid;
} _TCP_API_CNR;


typedef struct
{
    int16_t   dtsiz;
    uint8_t  *datap;
} _TCP_API_DR;

typedef struct
{
    uint8_t   type;
    volatile uint8_t stat;
    int16_t   tmout;
    int    *error;
    uint16_t   flag;
    uint16_t   reserved;
    union
    {
        _TCP_API_CNR  cnr;
        _TCP_API_DR   dr;
        void *parblk;
    } d;
} _API_REQ;


typedef struct
{
    uint16_t    sport;
    uint16_t    dport;
    uint32_t    seq;
    uint32_t    ack;
    uint8_t     len;
    uint8_t     flg;
    uint16_t    win_size;
    uint16_t    cksum;
    uint16_t    urg_ptr;
    uint8_t     opt[2];
} _TCP_HDR;

typedef struct
{
    _TCP_HDR  th;
    uint8_t     data[1];
} _TCPS;



typedef struct
{
    int  ercd;
} _TCP_API_REQ;

typedef struct
{
    volatile uint8_t stat;
    uint8_t dummy;
    _TCP_API_REQ req;
} _TCP_CB;
#define GET_TCP_CALLBACK_INFO_PTR(cepid) \
    (&head_tcb[cepid-1].callback_info)
enum
{
    _TCP_CB_STAT_CALLBACK = 1,
    _TCP_CB_STAT_LOCK  = 8,
};
#define _TCP_CB_STAT_IS_VIA_CALLBACK(stat)  ((stat) & _TCP_CB_STAT_CALLBACK)
#define _TCP_CB_STAT_SET_CALLBACK_FLG(stat)  ((stat)=(stat)|((_TCP_CB_STAT_CALLBACK)))
#define _TCP_CB_STAT_CLEAR_CALLBACK_FLG(stat) ((stat)=(stat)&(~(_TCP_CB_STAT_CALLBACK)))
#define _TCP_CB_STAT_IS_API_LOCKED(stat)  ((stat) & _TCP_CB_STAT_LOCK)
#define _TCP_CB_STAT_SET_API_LOCK_FLG(stat)  ((stat)=(stat)|((_TCP_CB_STAT_LOCK)))
#define _TCP_CB_STAT_CLEAR_API_LOCK_FLG(stat) ((stat)=(stat)&(~(_TCP_CB_STAT_LOCK)))
typedef int (*_TCP_CALLBACK_FUNC)(ID cepid, FN fncd , void *p_parblk);
#define _TCP_CB_GET_CALLBACK_FUNC_PTR(cepid) (tcp_ccep[(cepid)-1].callback)
#define _TCP_CB_CALL_CALLBACK(cepid, fncd, pTcpTcb)       \
    do {\
        if ( (*(pTcpTcb->req.error) < 0 && pTcpTcb->req.stat != _TCP_API_STAT_COMPLETE) || \
                (*(pTcpTcb->req.error) >=0 && pTcpTcb->req.stat == _TCP_API_STAT_INCOMPLETE) ) \
        {                     \
            pTcpTcb->req.stat = _TCP_API_STAT_COMPLETE;      \
            \
            _tcp_call_callback(cepid, fncd, (void *)pTcpTcb->req.error);  \
        }                 \
    }while(0)
#define _TCP_CB_CALL_CALLBACK_WITH_CLOSE(cepid, fncd, req_error, req_stat) \
    do {\
        if ( (*(req_error) < 0 && req_stat != _TCP_API_STAT_COMPLETE) || \
                (*(req_error) >=0 && req_stat == _TCP_API_STAT_INCOMPLETE) ) \
        {                     \
            req_stat = _TCP_API_STAT_COMPLETE;         \
            \
            _tcp_call_callback(cepid, fncd, (void *)req_error);     \
        }                 \
    }while(0)                \
        \
         
typedef struct
{
    uint8_t   sadr[IP_ALEN];
    uint8_t   dadr[IP_ALEN];
    uint8_t   reserve;
    uint8_t   prtcl;
    uint16_t  len;
} _TCP_PHDR;

typedef struct
{
    uint8_t src_addr[IP_ALEN];
    uint8_t dst_addr[IP_ALEN];
    uint8_t reserve;
    uint8_t proto;
    uint16_t len;
} _TCPUDP_PHDR;


typedef struct
{
    uint8_t    *data;
    uint8_t     hdr_flg;
    uint16_t   len;
    uint16_t    rst_cnt;
    uint16_t    nxt_rtx_cnt;
    uint16_t    cur_int;
    uint32_t    seq;
} _TCP_RTX_Q;

typedef struct
{
    uint8_t    *data;
    uint8_t     hdr_flg;
    uint16_t   len;
    uint32_t    seq;
} _TCP_RTX_Q2;

typedef struct
{
    uint16_t          flag;
#if defined(_TCP)
    uint16_t   cepid;
    uint16_t   status;
    uint16_t   nxt_status;
    uint8_t   it_stat;
    uint8_t           hdr_flg;
    uint16_t          mss;
    _API_REQ  req;
    _API_REQ  req_can;
    uint32_t          suna;
    uint32_t          snxt;
    uint32_t          risn;
    uint32_t          rnxt;
    uint8_t           rem_ip[IP_ALEN];
    uint16_t          rem_port;
    uint16_t          loc_port;
    uint16_t          rtchk_cnt;
    _TCP_RTX_Q      retrans_q;
    _TCP_RTX_Q2  retrans_q2;
    uint8_t          *nxtdat;
    uint8_t          *rwin;
    uint8_t          *rwin_bnry;
    uint8_t          *rwin_curr;
    uint16_t          swsize;
    uint16_t          rmt_rwsize;
    uint16_t          sdsize;
    uint16_t          rdsize;
    uint16_t          mslcnt;
    uint16_t   zwin_int;
    uint16_t          nxt_zero;
    uint16_t          zwp_noack_cnt;

    _TCP_CB   callback_info;

#endif
} _TCB;


typedef struct
{
    _IP_HDR  iph;    // IP Header
    union
    {
        uint8_t tcph[_TCPH_LEN+4]; // TCP Header (20:header+4:MSS option)
        uint8_t icmph[_ICMP_HLEN]; // ICMP Header
#if defined(_UDP)
        uint8_t udph[_UDPH_LEN]; // UDP Header
#endif
    } thdr;
} _TX_IPH ;

typedef struct
{
#if defined(_ETHER)
    _ETH_HDR eh;     // Ether Header
#elif defined(_PPP)
    uint8_t  address;   /* 0xff */
    uint8_t  control;   /* 0x03 */
    uint16_t  proto;
#endif
    union
    {
        _TX_IPH  tip;   // IP Header
#if defined(_ETHER)
#if !defined(_IPV6)
        _ARP_PKT tarp;
#endif
#endif
    } ihdr;
    uint16_t  hlen;
} _TX_HDR;

void _proc_api(void);
void _proc_rcv(void);
void _proc_snd(void);

void _tcp_init_tcb(_TCB *_ptcb);
// int  _tcp_api_req(ID cepid);
// void _tcp_clr_req(ID cepid);
void _tcp_cancel_api(int ercd);
void _tcp_stat(void);
int  _tcp_rcv_rst(void);
int  _tcp_rcv_syn(void);
void _tcp_rcv_ack(void);
int16_t _tcp_rcv_opt(void);
int16_t _tcp_proc_data(void);
int  _tcp_rcv_fin(void);
void _tcp_swin_updt(void);
void _tcp_cpy_rwdat(void);
void _tcp_clr_rtq(_TCB *ptcb);
void _tcp_return_listen(void);
void _tcp_snd(void);

void _tcp_api_acpt(void);
void _tcp_api_con(void);
void _tcp_api_sht_cls(void);
void _tcp_api_snddt(void);
void _tcp_api_rcvdt(void);
void _tcp_api_wup(ID);
// void _tcp_api_slp(ID cepid);
int _tcp_check_cepid_arg(ID cepid);
int _tcp_check_len_arg(int len);
int  _tcp_check_tmout_arg(uint16_t api_type, int32_t tmout, _TCP_CB* pTcpcb);
uint16_t _tcp_is_tcb_queue_over(uint16_t api_type, _TCB* pTcb,  _TCP_CB* pTcpcb);
uint16_t _tcp_call_callback(ID cepid, FN fncd, void *p_parblk);
FN _tcp_api_type_to_fn(uint16_t api_type);
int _tcp_recv_polling(_TCB* pTcb, uint8_t *buf, uint16_t size);
void _tcp_init_callback_info(_TCP_CB* pCallbackInfo);

