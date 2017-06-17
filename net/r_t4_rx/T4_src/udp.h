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
* File Name    : udp.h
* Version      : 1.0
* Description  : processing for UDP
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 01.04.2014 1.00     First Release
***********************************************************************************************************************/

typedef struct     /* message format of DARPA UDP */
{
    uint16 src_port;  /* source UDP port number  */
    uint16 dst_port;  /* destination UDP port number */
    uint16 len;   /* length of UDP packet   */
    uint16 cksum;   /* UDP checksum (0 => none)  */
} _UDP_HDR;

typedef struct
{
    _UDP_HDR udph;
    uchar  data[1];
} _UDP_PKT;

typedef struct
{
    volatile uchar stat;
    uchar type;
    sint16 len;
    sint16 tmout;
    ID  cepid;
    uchar *data;
    T_IPVxEP *p_dstaddr;
    ER  *ercd;
    uchar cancel_flag;
    ER snd_ercd;
    ER rcv_ercd;
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
    sint16  len;
    uchar  *data;
} _UDP_RCV_INFO;

typedef struct
{
    _UDP_API_REQ req;
    _UDP_RCV_INFO rcv;
    volatile uchar stat;
} _UDP_CB;

#define _UDP_CB_STAT_CALLBACK 1
#define _UDP_CB_STAT_SND  2
#define _UDP_CB_STAT_RCV  4
#define _UDP_CB_STAT_LOCK  8

uint16 _tcpudp_cksum(_IP_HDR *iph, _TCPUDP_PHDR *ph);
void _udp_rcv(_IP_HDR *piph, _UDP_HDR *pudph);
sint16 _udp_rcv_sub(_UDP_CB *pucb, _UDP_HDR *udph, _TCPUDP_PHDR *ph);
void _proc_udp_api(void);
void _udp_api_tmout(void);
void _udp_api_slp(_UDP_CB *pucb, ID id);
void _udp_api_wup(_UDP_CB *pucb, ID id);
void _udp_init(UW **workpp);
void _udp_snd(_TCPUDP_PHDR *ph);
FN  _udp_api_type_to_fn(uint16 api_type);
ER _udp_check_cepid_arg(ID cepid);
ER _udp_check_len_arg(INT len);





