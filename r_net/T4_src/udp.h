#pragma once
//=====================================================================//
/*!	@file
	@brief	udp.h @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "net_config.h"
#include "type.h"
#include "ip.h"
#include "tcp.h"

typedef struct     /* message format of DARPA UDP */
{
    uint16_t src_port;  /* source UDP port number  */
    uint16_t dst_port;  /* destination UDP port number */
    uint16_t len;   /* length of UDP packet   */
    uint16_t cksum;   /* UDP checksum (0 => none)  */
} _UDP_HDR;

typedef struct
{
    _UDP_HDR udph;
    uint8_t  data[1];
} _UDP_PKT;

typedef struct
{
    volatile uint8_t stat;
    uint8_t  type;
    int16_t  len;
    int16_t  tmout;
    uint16_t cepid;
    uint8_t *data;
    T_IPVxEP *p_dstaddr;
    int  *ercd;
    uint8_t cancel_flag;
} _UDP_API_REQ;

#define _UDP_API_NON   0
#define _UDP_API_RCV_DAT  1
#define _UDP_API_SND_DAT  2
#define _UDP_API_CAN_CEP  4

#define _UDP_API_STAT_INIT   0
#define _UDP_API_STAT_COMPLETE  0
#define _UDP_API_STAT_UNTREATED  1
#define _UDP_API_STAT_INCOMPLETE 2
#define _UDP_API_STAT_TMOUT   4

typedef struct
{
    T_IPVxEP dstaddr;
    int16_t  len;
    uint8_t  *data;
} _UDP_RCV_INFO;

typedef struct
{
    _UDP_API_REQ req;
    _UDP_RCV_INFO rcv;
    volatile uint8_t stat;
} _UDP_CB;

#define _UDP_CB_STAT_CALLBACK 1
#define _UDP_CB_STAT_SND  2
#define _UDP_CB_STAT_RCV  4
#define _UDP_CB_STAT_LOCK  8

uint16_t _tcpudp_cksum(_IP_HDR *iph, _TCPUDP_PHDR *ph);
void _udp_rcv(_IP_HDR *piph, _UDP_HDR *pudph);
int16_t _udp_rcv_sub(_UDP_CB *pucb, _UDP_HDR *udph, _TCPUDP_PHDR *ph);
void _udp_snd(_TCPUDP_PHDR *ph);
void _proc_udp_api(void);
void _udp_api_tmout(void);
void _udp_api_slp(_UDP_CB *pucb, uint16_t id);
void _udp_api_wup(_UDP_CB *pucb, uint16_t id);
void _udp_init(uint32_t **workpp);
void _udp_snd(_TCPUDP_PHDR *ph);
int32_t  _udp_api_type_to_fn(uint16_t api_type);
int _udp_check_cepid_arg(uint16_t cepid);
int _udp_check_len_arg(int len);

#if defined(_UDP)

#if defined(__cplusplus)
extern "C" {
#endif
int udp_rcv_dat(int cepid, T_IPVxEP *p_dstaddr, void *data, int len, int32_t tmout);
int udp_snd_dat(int cepid, T_IPVxEP *p_dstaddr, void *data, int len, int32_t tmout);
int udp_can_cep(int cepid, int32_t fncd);
#if defined(__cplusplus)
}
#endif
#endif
