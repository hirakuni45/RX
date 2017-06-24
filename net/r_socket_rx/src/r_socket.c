/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this
* software and to discontinue the availability of this software.
* By using this software, you agree to the additional terms and
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2011(2015) Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************
* File Name    : r_socket.c
* Version      : 1.31
* Device(s)    : RX
* Tool-Chain   : RXC
* H/W Platform : -
* Description  : This module implements BSD socket functions for M3S-T4-Tiny
*              : with blocking/non-blocking;
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 24.05.2013 0.10    Initial version (with RDKRX63N support)
*         : 30.09.2013 0.30    Internal release
*           : xx.xx.xx  0.3x   Piggy back dns into socket.
*         : 30.01.2015 0.40    Add errno for each API
*         : 05.01.2015 1.21    fixed include header file.
*         : 12.02.2015 1.22    fixed include header file.
*         : 23.09.2015 1.30     Remove DNS. modify listen,accept,send,sendto
*         : 01.10.2016 1.31    Deleted USE_BSD_NON_BLOCKING macro. 
*         :                    Added SOCKET_TCP_WINSIZE macro.
*         :                    Changed R_SOCKET_Init() API name to R_SOCKET_Open().
*         :                    Added R_SOCKET_Close().
*         :                    Omitted Ether-2 channels support.
******************************************************************************/
/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "t4define.h"
#include "r_t4_itcpip.h"
#include "r_socket_rx_config.h"
#include "../r_socket_rx_if.h"
#ifdef R_SOCKET_PAR_CHECK
#include "r_socket_par_check.h"
#endif

#include "r_t4_rx/src/config_tcpudp.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/


/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/


/******************************************************************************
Private global variables and functions
******************************************************************************/
static BSDSocket  sockets[TOTAL_BSD_SOCKET];
static uint32_t   create_id;
static uint32_t tcpudp_work[TCPUDP_WORK / sizeof(uint32_t) + 1];

static int dup_tcp_socket( int sock );          /* Make a duplicate of a socket */
static int reset_socket( int sock );        /* Clear a socket. make it */
static uint16_t get_ephemeral_port(void);
static int is_sel_readable(int socks );
static int is_sel_writeable(int socks);
static int is_sel_errpending(int socks);

static uint32_t no_connect_count_;

/******************************************************************************
* ID                : 1.0
* Outline           : t4_tcp_generic_callback
* Include           : r_t4_itcpip.h
* Declaration       : ER t4_tcp_generic_callback(ID cepid, FN fncd , VP p_parblk)
* Function Name     : t4_tcp_generic_callback
* Description       : Callback function.
* Argument          : ID  cepid   ; Communication endpoint ID
*                   : FN  fncd    ; Event code
*                   : VP  p_parblk; Parameter block
* Return Value      : ER          ; always 0 (not in use)
******************************************************************************/
static ER t4_tcp_generic_callback(ID cepid, FN fncd , VP p_parblk)
{
    int32_t i, j, remain_size;
    ER ercd;

    i = cepid - 1;
    if ( i >= TOTAL_BSD_SOCKET || i < 0  )
    {
        return 0;
    }
    ercd = *(ER *)p_parblk;

    if (ercd < 0)
    {
        if (ercd == E_RLWAI)
        {
            /* Clarify the socket's error type */
            switch (fncd)
            {
                case TFN_TCP_ACP_CEP:
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_CAN_END);
                    sockets[i].T4proc &= ~((uint32_t)T4_PROC_ACP | T4_PROC_CAN_START);
                    sockets[i].err_type = ERR_RLWAI_ACP;
                    for ( j = 0; j < MAX_TCP_CCEP; j++ )
                    {
                        if ( sockets[j].peer_socket == i)
                            break;
                    }
                    if ( j != MAX_TCP_CCEP )
                    {
                        sockets[i].state = BSD_CLOSED;
                        sockets[j].event = SOCKET_ERR_CEP;
                        sockets[i].T4status = T4_ERROR_CLOSE;
                        sockets[i].err_type = ERR_RLWAI_ACP;
                    }
                    else
                    {
                        /*  fatal error */
                        sockets[i].state = BSD_FATALERROR;
                    }
                    break;
                case TFN_TCP_CON_CEP:
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_CAN_END);
                    sockets[i].T4proc &= ~((uint32_t)T4_PROC_CON | T4_PROC_CAN_START);
                    sockets[i].err_type = ERR_RLWAI_CON;
                    break;
                case TFN_TCP_CLS_CEP:
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_CLS_END | T4_PROC_CAN_END);
                    sockets[i].T4proc &= ~((uint32_t)T4_PROC_CLS_START | T4_PROC_CAN_START);
                    sockets[i].err_type = ERR_RLWAI_CLS;
                    break;
                case TFN_TCP_SND_DAT:
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_SND_END | T4_PROC_CAN_END);
                    sockets[i].T4proc &= ~((uint32_t)T4_PROC_SND_START | T4_PROC_CAN_START);
                    sockets[i].err_type = ERR_RLWAI_SND;
                    break;
                case TFN_TCP_RCV_DAT:
                    if (0 != (sockets[i].socket_proc & SOCKET_PROC_CLS_START))
                    {
                        sockets[i].T4proc |= ((uint32_t)T4_PROC_RCV_END | T4_PROC_CAN_END);
                        sockets[i].T4proc &= ~((uint32_t)T4_PROC_RCV_START | T4_PROC_CAN_START);
                    }
                    else if (0 != (sockets[i].T4proc & T4_PROC_SND_START))
                    {
                        sockets[i].T4proc |= ((uint32_t)T4_PROC_CAN_END);
                        sockets[i].T4proc &= ~((uint32_t)T4_PROC_CAN_START);

                        tcp_snd_dat(cepid, sockets[i].snd_buf, sockets[i].sndSz, TMO_NBLK);
                    }
                    else
                    {
                        /*  fatal error */
                        sockets[i].state = BSD_FATALERROR;
                    }
                    break;
                default:
                    sockets[i].err_type = ERR_OTHERS;
                    break;
            }
        }
        else
        {
            switch (fncd)
            {
                case TFN_TCP_ACP_CEP:
                    sockets[i].T4proc &= ~((uint32_t)T4_PROC_ACP);
                    for ( j = 0; j < MAX_TCP_CCEP; j++ )
                    {
                        if ( sockets[j].peer_socket == i)
                            break;
                    }
                    if ( j != MAX_TCP_CCEP )
                    {
                        sockets[i].state = BSD_CLOSED;
                        sockets[j].event = SOCKET_ERR_CEP;
                        sockets[i].T4status = T4_ERROR_CLOSE;
                        sockets[i].err_type = ERR_OTHERS;
                    }
                    else
                    {
                        /*  fatal error */
                        sockets[i].state = BSD_FATALERROR;
                    }
                    break;
                case TFN_TCP_CON_CEP:
                    sockets[i].T4proc &= ~((uint32_t)T4_PROC_CON);
                    sockets[i].T4status = T4_ERROR_CLOSE;
                    sockets[i].event = SOCKET_ERR_CEP;
                    sockets[i].err_type = ERR_OTHERS;
                    break;
                case TFN_TCP_SND_DAT:
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_SND_END);
                    sockets[i].T4proc &= ~((uint32_t)T4_PROC_SND_START);
                    sockets[i].T4status = T4_ERROR_CLOSE;
                    sockets[i].event = SOCKET_ERR_CEP;
                    sockets[i].err_type = ERR_OTHERS;
                    break;
                case TFN_TCP_RCV_DAT:
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_RCV_END);
                    sockets[i].T4proc &= ~((uint32_t)T4_PROC_RCV_START);
                    sockets[i].T4status = T4_ERROR_CLOSE;
                    sockets[i].event = SOCKET_ERR_CEP;
                    sockets[i].err_type = ERR_OTHERS;
                    break;
                case TFN_TCP_CLS_CEP:
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_CLS_END);
                    sockets[i].T4proc &= ~((uint32_t)T4_PROC_CLS_START);
                    sockets[i].T4status = T4_CLOSED;
                    sockets[i].state = BSD_CLOSED;
                    sockets[i].event = -1;
                    break;
                default: /* (ex. connect() API is issued to non-listening server's socket, ...) */
                    sockets[i].T4status = T4_ERROR_CLOSE;
                    sockets[i].event = SOCKET_ERR_CEP;
                    sockets[i].err_type = ERR_OTHERS;
                    break;
            }
        }
    }
    else
    {
        switch (fncd)
        {
            case TFN_TCP_ACP_CEP:
                sockets[i].T4proc &= ~((uint32_t)T4_PROC_ACP);
                /* Inform the listening socket instead */
                for ( j = 0; j < MAX_TCP_CCEP; j++ )
                {
                    if ( sockets[j].peer_socket == i)
                        break;
                }
                if ( j != MAX_TCP_CCEP )
                {
                    sockets[i].state = BSD_CONNECTED;
                    sockets[j].event = SOCKET_ACP_CEP;
                    sockets[i].T4status = T4_ESTABLISHED;
                }
                else
                {
                    sockets[i].state = BSD_CONNECTED;
                    sockets[i].event = SOCKET_ACP_CEP;
                    sockets[i].T4status = T4_ESTABLISHED;
                }
                sockets[i].rcvLen = 0;
                sockets[i].rcvin_offset = 0;
                sockets[i].rcvout_offset = 0;
                sockets[i].rcvcnt = 0;
                sockets[i].pending_rcvlen = BSD_RCV_BUFSZ;
                tcp_rcv_dat(cepid, (VP)(&sockets[i].rcv_buf[0]), BSD_RCV_BUFSZ, TMO_NBLK);
                sockets[i].T4proc |= ((uint32_t)T4_PROC_RCV_START);
                break;
            case TFN_TCP_CON_CEP:
                sockets[i].T4proc &= ~((uint32_t)T4_PROC_CON);
                sockets[i].event = SOCKET_CON_CEP;
                sockets[i].state = BSD_CONNECTED;
                sockets[i].T4status = T4_ESTABLISHED;
                sockets[i].rcvLen = 0;
                sockets[i].rcvin_offset = 0;
                sockets[i].rcvout_offset = 0;
                sockets[i].rcvcnt = 0;
                sockets[i].pending_rcvlen = BSD_RCV_BUFSZ;
                tcp_rcv_dat(cepid, (VP)(&sockets[i].rcv_buf[0]), BSD_RCV_BUFSZ, TMO_NBLK);
                sockets[i].T4proc |= ((uint32_t)T4_PROC_RCV_START);
                break;
            case TFN_TCP_SND_DAT:
                sockets[i].T4proc &= ~((uint32_t)T4_PROC_SND_START);
                /* error code == "0"  FIN or RST received? */

                sockets[i].event = SOCKET_SND_DAT;
                sockets[i].sndLen += ercd;
                remain_size = sockets[i].sndSz - sockets[i].sndLen;
                if ( remain_size > 0 )
                {
                    tcp_snd_dat(cepid, (VP)(&sockets[i].snd_buf[sockets[i].sndLen]),
                                remain_size, TMO_NBLK);
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_SND_START);
                }
                else
                {
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_SND_END);
                    if (0 != (sockets[i].T4proc & ((uint32_t)T4_PROC_RCV_START)))
                    {
                        tcp_rcv_dat(cepid, (VP)&sockets[i].rcv_buf[sockets[i].rcvin_offset], sockets[i].pending_rcvlen, TMO_NBLK);
                    }
                }
                break;
            case TFN_TCP_RCV_DAT:
                sockets[i].T4proc &= ~((uint32_t)T4_PROC_RCV_START);
                sockets[i].T4proc |= ((uint32_t)T4_PROC_RCV_END);
                /* error code == "0" : reception FIN */
                if (ercd == 0)
                {
                    sockets[i].finrcv = 1;
                    sockets[i].T4status = T4_CLOSE_WAIT;
                    sockets[i].state = BSD_CLOSING;

                }
                /* normal reception and echoback data */
                else
                {
                    sockets[i].event = SOCKET_RCV_DAT; //SOCKET_RCV_DAT;
                    sockets[i].rcvLen += ercd;
                    sockets[i].rcvin_offset += ercd;
                    if (sockets[i].rcvLen < BSD_RCV_BUFSZ)
                    {
                        int size;
                        if (sockets[i].rcvin_offset == BSD_RCV_BUFSZ)
                        {
                            sockets[i].rcvin_offset = 0;
                        }
                        if ((BSD_RCV_BUFSZ - sockets[i].rcvin_offset) > BSD_RCV_BUFSZ - sockets[i].rcvLen)
                        {
                            size = BSD_RCV_BUFSZ - sockets[i].rcvLen;
                        }
                        else
                        {
                            size = BSD_RCV_BUFSZ - sockets[i].rcvin_offset;
                        }
                        sockets[i].pending_rcvlen = size;
                        tcp_rcv_dat(cepid, (VP)(&sockets[i].rcv_buf[sockets[i].rcvin_offset]), size, TMO_NBLK);
                        sockets[i].T4proc |= ((uint32_t)T4_PROC_RCV_START);
                    }
                }
                break;
            case TFN_TCP_CLS_CEP:
                sockets[i].T4proc &= ~((uint32_t)T4_PROC_CLS_START);
                sockets[i].T4proc |= ((uint32_t)T4_PROC_CLS_END);
                sockets[i].event = SOCKET_CLS_CEP;
                sockets[i].state = BSD_CLOSED;
                sockets[i].T4status = T4_CLOSED;
                sockets[i].err_type = ERR_NONE;
                break;
            default:
                break;
        }
    }
    return 0;
}


/******************************************************************************
* ID                : 1.0
* Outline           : t4_udp_generic_callback
* Include           : r_t4_itcpip.h
* Declaration       : ER t4_udp_generic_callback(ID cepid, FN fncd , VP p_parblk)
* Function Name     : t4_callback
* Description       : Callback function.
* Argument          : ID  cepid   ; Communication endpoint ID
*                   : FN  fncd    ; Event code
*                   : VP  p_parblk; Parameter block
* Return Value      : ER          ; always 0 (not in use)
******************************************************************************/
static ER t4_udp_generic_callback(ID cepid, FN fncd , VP p_parblk)
{
    int32_t i, remain_size;
    ER ercd;
    T_IPV4EP local_dstaddr;

    i = cepid - 1 + MAX_TCP_CCEP;
    if ( i >= TOTAL_BSD_SOCKET || i < 0  )
    {
        return 0;
    }
    ercd = *(ER *)p_parblk;

    if (ercd < 0)
    {
        if (ercd == E_RLWAI)
        {
            sockets[i].T4proc |= ((uint32_t)T4_PROC_CAN_END);
            sockets[i].T4proc &= ~((uint32_t)T4_PROC_CAN_START);
            sockets[i].T4proc |= ((uint32_t)T4_PROC_SND_END);
            sockets[i].T4proc &= ~((uint32_t)T4_PROC_SND_START);
        }
        else
        {
            sockets[i].T4proc |= ((uint32_t)T4_PROC_SND_END);
            sockets[i].T4proc &= ~((uint32_t)T4_PROC_SND_START);
            sockets[i].event = SOCKET_ERR_CEP;
            sockets[i].err_type = ERR_OTHERS;
        }
    }
    else
    {
        switch (fncd)
        {
            case TEV_UDP_RCV_DAT:
                if (sockets[i].state == BSD_CONNECTED)
                {
                    ercd = udp_rcv_dat(cepid, &local_dstaddr,
                                       sockets[i].rcv_buf,
                                       BSD_RCV_BUFSZ, TMO_POL);

                    if ((sockets[i].dstaddr.ipaddr == local_dstaddr.ipaddr) && (sockets[i].dstaddr.portno == local_dstaddr.portno))
                    {
                        sockets[i].event = SOCKET_RCV_DAT;
                        sockets[i].rcvLen += ercd;
                        sockets[i].rcvin_offset += ercd;
                    }
                }
                else
                {
                    ercd = udp_rcv_dat(cepid, &sockets[i].dstaddr,
                                       sockets[i].rcv_buf + sockets[i].rcvLen,
                                       BSD_RCV_BUFSZ - sockets[i].rcvLen, TMO_POL);
                    sockets[i].event = SOCKET_RCV_DAT;
                    sockets[i].rcvLen = ercd;
                    sockets[i].rcvin_offset = ercd;
                    sockets[i].rcvout_offset = 0;
                }
                break;
            case TFN_UDP_SND_DAT:
                sockets[i].T4proc &= ~((uint32_t)T4_PROC_SND_START);
                sockets[i].event = SOCKET_SND_DAT;
                sockets[i].sndLen += ercd;
                remain_size = sockets[i].sndSz - sockets[i].sndLen;
                if ( remain_size > 0 )
                {
                    udp_snd_dat(cepid,  &sockets[i].dstaddr, (VP)(&sockets[i].snd_buf[sockets[i].sndLen]),
                                remain_size, TMO_NBLK);
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_SND_START);
                }
                else
                {
                    sockets[i].T4proc |= ((uint32_t)T4_PROC_SND_END);
                }
                break;
            default:
                break;
        }
    }
    return 0;
}


/******************************************************************************
* Function Name: R_SOCKET_Open
* Description  : Initialize the socket structure to a known initial value
* Arguments    : none
* Return Value : none
******************************************************************************/
int R_SOCKET_Open(void)
{
    int i;
    ER  ercd;
    int size;

    memset(tcp_ccep, 0x00, MAX_TCP_CCEP * sizeof(T_TCP_CCEP));
    memset(tcp_crep, 0x00, MAX_TCP_CREP * sizeof(T_TCP_CREP));
    memset(udp_ccep, 0x00, MAX_UDP_CCEP * sizeof(T_UDP_CCEP));
    for ( i = 0; i < TOTAL_BSD_SOCKET; i++)
    {
        sockets[i].state = BSD_CLOSED;
        sockets[i].T4status = T4_CLOSED;
        sockets[i].event = -1;
        sockets[i].socket_type = 0;
        sockets[i].backlog = 0;
        sockets[i].dstaddr.ipaddr = 0;
        sockets[i].dstaddr.portno = 0;
        sockets[i].tmout = 0;  /* default is TMO_POL */
        sockets[i].T4proc = 0;
        sockets[i].rcvLen = 0;
        sockets[i].sndLen = 0;
        sockets[i].sndSz = 0;
        sockets[i].err_type = ERR_NONE; /* No errors */
        sockets[i].peer_socket = -1;
        sockets[i].socket_proc = 0;
        if ( i < MAX_TCP_CCEP )
        {
            tcp_ccep[i].rbufsz = SOCKET_TCP_WINSIZE;
            tcp_ccep[i].callback = t4_tcp_generic_callback;
        }
        else
        {
            udp_ccep[i-MAX_TCP_CCEP].callback = t4_udp_generic_callback;
        }
    }

    /* initialize TCP/IP */
    size = tcpudp_get_ramsize();
    if (size > sizeof(tcpudp_work))
    {
		printf("R_SOCKET_Open: empty memory (%d, %d)\n", (int)size, (int)sizeof(tcpudp_work));
		return -1;
    }
	memset(tcpudp_work, 0x00, sizeof(tcpudp_work));

    ercd = tcpudp_open(tcpudp_work);
    if (ercd != E_OK)
    {
		printf("R_SOCKET_Open: tcpudp_open error\n");
		return -2;
    }
	return size;
}


/******************************************************************************
* Function Name: R_SOCKET_Open
* Description  : Initialize the socket structure to a known initial value
* Arguments    : none
* Return Value : none
******************************************************************************/
void R_SOCKET_Close( void )
{
    tcpudp_close();
}


/******************************************************************************
* Function Name: socket
* Description  : This function creates a new socket
* Arguments    : domain   - Address domain/Families - AF_INET, AF_UNIX etc.,
*                type     - socket type SOCK_DGRAM or SOCK_STREAM
*                protocol - IP protocol IPPROTO_UDP or IPPROTO_TCP
*                           Don't care
* Return Value : SOCKET socket - An integer representing socket descriptor
******************************************************************************/
int r_socket( int domain, int type, int protocol )
{
    SOCKET sock, ifirst, ilast;
    int semp_ret;

    errno = E_OK;           /* No error */
    semp_ret = E_OK;

#ifdef R_SOCKET_PAR_CHECK
    if (socket_par_check(domain, type, protocol) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */

    if ( (type == SOCK_STREAM) && (protocol == IPPROTO_TCP) )
    {
        /* sock {0..MAX_TCP_CCEP-1} reserved for SOCK_STREAM */
        ifirst = 0;
        ilast = MAX_TCP_CCEP;
    }
    else if (( type == SOCK_DGRAM ) && ( protocol == IPPROTO_UDP))
    {
        /* {MAX_TCP_CCEP .. MAX_TCP_CCEP+MAX_UDP_CCEP-1} reserved for SOCK_DGRAM */
        ifirst = MAX_TCP_CCEP;
        ilast = MAX_TCP_CCEP + MAX_UDP_CCEP;
    }
    else
    {
        errno = EPROTONOSUPPORT;    /* The protocol is not supported by the address family, or */
        /* the protocol is not supported by the implementation. */
        return SOCKET_ERROR;
    }
#if (SOCKET_IF_USE_SEMP == 1)
    semp_ret = r_socket_sem_lock();            /* Return immediately if lock cannot be acquired? */
#endif
    if (semp_ret != E_OK)
    {
        errno = EACCES;
        return  SOCKET_ERROR;    /* No sockets available */
    }
    for ( sock = ifirst; sock < ilast; sock++)
    {
        if ( sockets[sock].state == BSD_CLOSED ) /* sock available for use? */
        {
            break;
        }
    }
    if ( sock == ilast )
    {
        r_socket_sem_release();
        errno = ENFILE;          /* No more file descriptors are available for the system. */
        return  SOCKET_ERROR;    /* No sockets available */
    }

    if ( type == SOCK_STREAM )
    {
        tcp_ccep[sock].cepatr = 0;              /* Choose first channel; */
    }
    else
    {
        udp_ccep[sock-MAX_TCP_CCEP].cepatr = 0; /* Choose first channel; */
    }
    sockets[sock].socket_type = type;
    sockets[sock].state = BSD_CREATED;
    sockets[sock].tmout = TMO_FEVR;    /* Default is blocking type */
    sockets[sock].err_type = ERR_NONE; /* No error */

    sockets[sock].T4proc = 0;
    sockets[sock].socket_proc = 0;
    ++ create_id;
    sockets[sock].create_id = create_id; /* Set this is a peer socket */
    if ( type == SOCK_DGRAM )
    {
        udp_ccep[sock-MAX_TCP_CCEP].myaddr.portno = get_ephemeral_port(); /*  Choose next channel; */
    }
#if (SOCKET_IF_USE_SEMP == 1)
    r_socket_sem_release();
#endif
    return sock;
}


/****************************************************************************
* Function Name: bind
* Description  : The bind function assigns a name to an unnamed socket.
* Arguments    : sock  - socket descriptor
*                name    - pointer to the sockaddr structure containing the
*                          local address of the socket.
*                namelen - length of the sockaddr structure.
* Return Value : 0 for success, SOCKET_ERROR indicates an error.
*****************************************************************************/
int r_bind( int sock, const sockaddr_in *local_addr)
{
    int cepno;

    errno = E_OK;           /* No error */
#ifdef R_SOCKET_PAR_CHECK
    if (bind_par_check(sock, name, namelen) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */

    if ( sockets[sock].state != BSD_CREATED ) /* only work with newly created socket */
    {

        errno = EINVAL;         /* The socket is already bound to an address, and the protocol does not support */
        /* binding to a new address; or the socket has been shut down. */
        return SOCKET_ERROR;
    }

//	sockets[i].dstaddr.ipaddr = 0;
//	sockets[i].dstaddr.portno = 0;

    /* If ipaddr is IPADDR_ANY, should get addr of local adaptor and bind to it? */
    if ( sockets[sock].socket_type == SOCK_STREAM )
    {
        cepno = sock;
        tcp_crep[cepno].repatr = 0x0000; /* TCP recp point attribute */
        tcp_crep[cepno].myaddr.ipaddr = local_addr->sin_addr.S_un.S_addr;
        tcp_crep[cepno].myaddr.portno = htons(local_addr->sin_port);  /* local 's IP and portno */

        tcp_ccep[cepno].sbuf = 0;   /* Not implemented */
        tcp_ccep[cepno].sbufsz = 0; /* Not implemented */
        tcp_ccep[cepno].rbuf = 0;  /* Not implemented */
        tcp_ccep[cepno].rbufsz = SOCKET_TCP_WINSIZE;
    }
    else if ( sockets[sock].socket_type == SOCK_DGRAM )
    {
        /* cepno is never negative. sock assigned from MAX_TCP_CCEP..MAX_TCP_CCEP+MAX_UDP_CCEP */
        cepno = sock - MAX_TCP_CCEP;
        udp_ccep[cepno].myaddr.ipaddr = local_addr->sin_addr.S_un.S_addr;
        udp_ccep[cepno].myaddr.portno = htons(local_addr->sin_port);  /* local's IP and portno */
    }
    else
    {
        errno = EPROTONOSUPPORT;    /*  Should have failed when create socket */
        return SOCKET_ERROR;
    }
    sockets[sock].state = BSD_BOUND;
    return E_OK;
}


/******************************************************************************
* Function Name: connect
* Description  : The connect function assigns the address of the peer communications
* Arguments    : sock  - socket descriptor
*                name    - pointer to the the sockaddr structure containing the
*                          peer address of the socket to be connected to
*                namelen - length of the sockaddr structure.
* Return Value : 0 for success, SOCKET_ERROR indicates an error.
******************************************************************************/
int r_connect( int sock, const sockaddr_in *addr)
{
    uint32_t remote_ip;
    uint16_t remote_port;
    ER ercd = SOCKET_ERROR;
    signed short i;
    unsigned short lport;
    uint32_t this_id;

    errno = E_OK;
#ifdef R_SOCKET_PAR_CHECK
    if (connect_par_check(sock, name, namelen) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */
    this_id = sockets[sock].create_id;

    if ( sockets[sock].socket_type == SOCK_STREAM )
    {
        if ((sockets[sock].state != BSD_BOUND) && (sockets[sock].state != BSD_CREATED) )
        {
            switch (sockets[sock].state)
            {
                case BSD_CONNECTING:
                    errno = EALREADY;   /* A connection request is already in progress for the specified socket. */
                    break;
                case BSD_CONNECTED:
                    errno = EISCONN;    /* The specified socket is connection-mode and is already connected. */
                    break;
                case BSD_LISTENING:
                case BSD_CLOSED:
                case BSD_CLOSING:
                default:
                    errno = EOPNOTSUPP; /* The socket is listening and cannot be connected. */
                    break;
            }
            return SOCKET_ERROR;
        }
    }
    else if ( sockets[sock].socket_type == SOCK_DGRAM )
    {
        if ((sockets[sock].state < BSD_CREATED) )
        {
            errno = EOPNOTSUPP;
            return SOCKET_ERROR;
        }
    }
    else
    {
        errno = EPROTOTYPE;
        return SOCKET_ERROR;
    }

    remote_ip   = addr->sin_addr.S_un.S_addr;
    remote_port = htons(addr->sin_port);

    if ( (remote_ip == 0) || (remote_port == 0) )
    {
        errno = EINVAL;
        return SOCKET_ERROR;
    }
    if ( sockets[sock].socket_type == SOCK_STREAM )
    {
        int  t4_cepno;

        t4_cepno = sock + 1;
        if (sockets[sock].state == BSD_CREATED)
        {
            i = 0;
            while (i < MAX_TCP_CREP)
            {
                lport = get_ephemeral_port();
                for (i = 0;i < MAX_TCP_CREP;i++)
                {
                    if (lport == tcp_crep[i].myaddr.portno)
                    {
                        break;
                    }
                }
            }
            tcp_crep[t4_cepno - 1].repatr = 0x0000; /* TCP recp point attribute */
            tcp_crep[t4_cepno - 1].myaddr.ipaddr = NADR;
            tcp_crep[t4_cepno - 1].myaddr.portno = lport;/* local 's IP and portno */

            tcp_ccep[t4_cepno - 1].sbuf = 0;   /* Not implemented */
            tcp_ccep[t4_cepno - 1].sbufsz = 0; /* Not implemented */
            tcp_ccep[t4_cepno - 1].rbuf = 0;   /* Not implemented */
            tcp_ccep[t4_cepno - 1].rbufsz = SOCKET_TCP_WINSIZE;
            tcp_ccep[t4_cepno - 1].callback = t4_tcp_generic_callback;
        }

        sockets[sock].dstaddr.portno = remote_port;
        sockets[sock].dstaddr.ipaddr = remote_ip;

        ercd = tcp_con_cep(t4_cepno, (T_IPV4EP*)&tcp_crep[t4_cepno - 1].myaddr,
                           (T_IPV4EP*)&sockets[sock].dstaddr,
                           TMO_NBLK);
        if (ercd == E_WBLK)
        {
            sockets[sock].T4proc |= T4_PROC_CON;
            sockets[sock].state = BSD_CONNECTING; /* State to be completed in callback */
            if (sockets[sock].tmout == TMO_NBLK)
            {
                errno = EINPROGRESS;
                return SOCKET_ERROR;
            }
            else
            {
                while (   (0 != (sockets[sock].T4proc & T4_PROC_CON))
                          && (this_id == sockets[sock].create_id)

                      )
                {
                    r_socket_task_switch(sock);
                }
                if (this_id != sockets[sock].create_id)
                {
                    errno = ECONNABORTED;
                    return SOCKET_ERROR;
                }
                if (sockets[sock].state != BSD_CONNECTED)
                {
                    errno = EINVAL;           /* TODO : E_PAR, E_QOVR, E_OBJ */
                    return SOCKET_ERROR;
                }
            }
        }
        else
        {
            errno = EINVAL;           /* TODO : E_PAR, E_QOVR, E_OBJ */
            return SOCKET_ERROR;
        }
    }
    else
    {
        /* UDP: remote port is used as a filter only.  no need to call connect() */
        /* TODO any check for addr range, port range? */
        sockets[sock].dstaddr.portno = remote_port;
        sockets[sock].dstaddr.ipaddr = remote_ip; /* Does it mean only talk to this ip? */
        sockets[sock].state = BSD_CONNECTED;
    }
    return E_OK;
}

/******************************************************************************
* Function Name: listen
* Description  : The listen function sets the specified socket in a listen mode.
* Arguments    : sock  - Socket identifier
*                backlog - maximum number of connection requests that can be
*                queued (fixed to 1 ONLY - not use internally )
* Return Value : 0 for success, SOCKET_ERROR indicates an error.
******************************************************************************/
int r_listen( int sock, int backlog )
{
    SOCKET peer_socket;
    int     peer_cepid, cepid, ercd;

#ifdef R_SOCKET_PAR_CHECK
    if (listen_par_check(sock, backlog) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */

    if ( (sock >= TOTAL_BSD_SOCKET) || (sock < 0 ))
    {
        errno = ENOTSOCK;       /* The socket argument does not refer to a socket. */
        return SOCKET_ERROR;
    }
    if (sockets[sock].socket_type != SOCK_STREAM)
    {
        errno = EOPNOTSUPP;
        return SOCKET_ERROR;
    }
    if (sockets[sock].state != BSD_BOUND)
    {
        switch ( sockets[sock].state)
        {
            case BSD_CLOSING:
            case BSD_CLOSED:
                errno = EINVAL;         /* The socket has been shut down */
                break;
            case BSD_CREATED:
                errno = EDESTADDRREQ;   /* The socket is not bound to a local address, and the protocol does not */
                /* support listening on an unbound socket */
                break;
            default:                    /* TODO */
                errno = EINVAL;         /*  The socket has been shut down */
                break;
        }
        return SOCKET_ERROR;
    }
    /* put this socket in listen mode */
    sockets[sock].state = BSD_LISTENING;
    sockets[sock].backlog = backlog;  /* Not Used */

    peer_socket = dup_tcp_socket( sock );
    if ( peer_socket == SOCKET_ERROR )
    {
        errno = ENFILE;
        return SOCKET_ERROR;
    }
    peer_cepid = peer_socket + 1;
    cepid = sock + 1;

    ercd = tcp_acp_cep(peer_cepid, cepid, &sockets[peer_socket].dstaddr, TMO_NBLK);
    if (ercd == E_WBLK)
    {
        sockets[peer_socket].state = BSD_CONNECTING; /* State change in callback */
        sockets[peer_socket].T4proc |= (uint32_t)T4_PROC_ACP;
        sockets[sock].peer_socket = peer_socket;
    }
    else
    {
        reset_socket( peer_socket );
        sockets[sock].peer_socket = -1;
        errno = EINVAL;         /* Dont have a proper return code */
        return SOCKET_ERROR;
    }

	no_connect_count_ = 0;
    return E_OK;
}

/******************************************************************************
* Function Name: accept
* Description  : The accept function is used to accept a connection request
*                queued for a listening socket.
* Arguments    : sock      Socket descriptor
*                              must be bound to a local name and in
*                              listening mode.
*                address       pointer to the the sockaddr structure that will receive
*                              the connecting node IP address and port number.
* Return Value : peersocket for success non-negative descriptor,
*                   SOCKET_ERROR indicates an error.
*              : if successful, peersocket = socket
******************************************************************************/
int r_accept(int sock, sockaddr_in *padr)
{
    uint32_t this_id;
    uint32_t this_peer_id;
    int  cepid;
    int  peer_socket, ret_socket;
    int  peer_cepid;
    ER ercd = SOCKET_ERROR;

	memset(padr, 0x00, sizeof(sockaddr_in));
    ret_socket = peer_socket = SOCKET_ERROR;
    errno = E_OK;

#ifdef R_SOCKET_PAR_CHECK
    if (accept_par_check(sock, address, address_len) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */

    this_id = sockets[sock].create_id;
    if ((sockets[sock].tmout != TMO_FEVR) && (sockets[sock].tmout != TMO_NBLK))
    {
        errno = EINVAL;
        return SOCKET_ERROR;
    }
    if (sockets[sock].event == SOCKET_ERR_CEP)
    {
        errno = ECONNABORTED;
        return SOCKET_ERROR;
    }
    if ( sockets[sock].socket_type != SOCK_STREAM )
    {
        errno = EOPNOTSUPP;
        return SOCKET_ERROR;
    }

    cepid = sock + 1;

    if ( sockets[sock].state == BSD_LISTENING )/* if listening, do accept */
    {
        /* Get the listener's peer socket */
        ret_socket = sockets[sock].peer_socket;
        if (ret_socket != -1)
        {
            this_peer_id = sockets[ret_socket].create_id;
            /* Check the state of the peer socket */
			int connect = 0;
            if(sockets[ret_socket].state == BSD_CONNECTING) {
				do {
					if(( 0 == (sockets[ret_socket].T4proc & T4_PROC_ACP)
					  || (sockets[sock].state == BSD_CLOSED)
					  || (this_id != sockets[sock].create_id))
					  || (this_peer_id != sockets[ret_socket].create_id)) {
						printf("Connecting\n");
						connect = 1;
						break;
					}

					r_socket_task_switch(sock);

				} while(sockets[sock].tmout == TMO_FEVR) ;

				if((sockets[sock].state == BSD_CLOSED)
				  || (this_id != sockets[sock].create_id)
				  || (this_peer_id != sockets[ret_socket].create_id)) {
					errno = ECONNABORTED;
					return SOCKET_ERROR;
				}
            } else {
				goto acp_chk_ret_socket;
			}

			if(connect == 0) {
				++no_connect_count_;
				if(no_connect_count_ >= 100) {
///					printf("r_accept: connection wait\n");
					no_connect_count_ = 0;
				}
		        errno = EAGAIN;
        		return SOCKET_ERROR;
			}

            sockets[sock].event = -1;

            peer_socket = dup_tcp_socket(sock);
            if (peer_socket == SOCKET_ERROR)
            {
                sockets[sock].event = -1;
                sockets[sock].peer_socket = -1;
                goto acp_chk_ret_socket;
            }
            else
            {
                sockets[sock].peer_socket = peer_socket;
            }
        }
        else
        {
            peer_socket = dup_tcp_socket(sock);
            if (peer_socket == SOCKET_ERROR)
            {
                errno = ENFILE;
                return SOCKET_ERROR;
            }
            else
            {
                sockets[sock].peer_socket = peer_socket;
            }
        }
        peer_cepid = peer_socket + 1;
        sockets[sock].event = -1;
        ercd = tcp_acp_cep(peer_cepid, cepid, &sockets[peer_socket].dstaddr, TMO_NBLK); /*  Fix bug in case non-blocking */

        if (ercd == E_WBLK)
        {
            sockets[peer_socket].T4proc |= (uint32_t)T4_PROC_ACP;
            sockets[peer_socket].state = BSD_CONNECTING; /* State change in callback */
            errno = EAGAIN; /* O_NONBLOCK is set for the socket file descriptor and */
            /* no connections are present to be accepted. */
            return ret_socket;
        }
        else
        {
            reset_socket( peer_socket );
            errno = EINVAL; /* The socket is not accepting connections. */
            return SOCKET_ERROR;
        }
    }
    else /* Close the peer socket if the sock is not listening/connected */
    {
        errno = EOPNOTSUPP; /* The socket type of the specified socket does not */
        /* support accepting connections. */
        return SOCKET_ERROR;
    }
acp_chk_ret_socket:             /* Check return socket before return */
    if ( sockets[ret_socket].state != BSD_CONNECTED )
    {
        errno = EAGAIN;     /* Poll again.  Socket not established yet */
        return SOCKET_ERROR;
    }

	if(ret_socket >= 0) {
		padr->sin_family = AF_INET;
		padr->sin_addr.S_un.S_addr = sockets[ret_socket].dstaddr.ipaddr;
		padr->sin_port = htons(sockets[ret_socket].dstaddr.portno);
	}

    return ret_socket;
}


/******************************************************************************
* Function Name: send
* Description  : The send function is used to send outgoing data to a connected
*                socket.
* Arguments    : sock - Socket descriptor
*                buffer - application data buffer containing data to transmit
*                length - length of data in bytes
* Return Value : Number of bytes sent for success, SOCKET_ERROR indicates an error.
******************************************************************************/
int r_send( int sock,  const void *buffer, uint32_t length)
{
    int  cepid;
    int ercd = 0;
    uint32_t this_id;

    errno = E_OK;
#ifdef R_SOCKET_PAR_CHECK
    if (send_par_check(sock, buffer, length) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */

    this_id = sockets[sock].create_id;
    if (sockets[sock].event == SOCKET_ERR_CEP)
    {
        return SOCKET_ERROR;
    }
    /* For NBLK, data is transfer to an internal sndbuf[] so API can return immediately  */
    /* In callback, data is throttled out depending on available BW */

    /* In TCP data to be send may be broken into segments */
    /* In UDP data should not be broken up, but send within 1 frame */

    if ( sockets[sock].state < BSD_CONNECTED)
    {
        errno = ENOTCONN;   /* The socket is not connected. */
        return SOCKET_ERROR;
    }

    if ( sockets[sock].socket_type == SOCK_DGRAM ) /* udp */
    {
        errno = EOPNOTSUPP;     /* The socket argument is associated with a socket that */
        /* does not support one or more of the values set in flags. */
        return SOCKET_ERROR;
    }
    if ( sockets[sock].socket_type == SOCK_STREAM ) /* tcp */
    {
        cepid = sock + 1;
        if ( 0 != (sockets[sock].T4proc & T4_PROC_SND_START))
        {
            errno = ENOBUFS;
            ercd  = SOCKET_ERROR;
            return ercd;
        }
        if ( length > BSD_SND_BUFSZ)
        {
            errno = ENOBUFS;
            return SOCKET_ERROR;
        }

        memcpy( sockets[sock].snd_buf, buffer, length );
        sockets[sock].sndLen = 0;
        sockets[sock].sndSz = length;
        sockets[sock].pending_sndlen = length;
        sockets[sock].T4proc &= ~(T4_PROC_SND_END);
        if ( 0 != (sockets[sock].T4proc & T4_PROC_RCV_START))
        {
            sockets[sock].T4proc |= (T4_PROC_SND_START | T4_PROC_CAN_START);
            ercd = tcp_can_cep( cepid, TFN_TCP_ALL );
            if (ercd == E_OK)
            {
                ercd = length;
            }
            else
            {
                sockets[sock].T4proc &= ~(T4_PROC_SND_START | T4_PROC_CAN_START);
                sockets[sock].T4proc |= (T4_PROC_CAN_END);

                sockets[sock].T4proc &= ~(T4_PROC_SND_END);
                sockets[sock].T4proc |= (T4_PROC_SND_START);
                ercd = tcp_snd_dat( cepid, (VP)sockets[sock].snd_buf, length,
                                    TMO_NBLK );
                if ( ercd == E_WBLK )
                {
                    ercd = length;  /* Return length of data even though it may not been sent*/

                }
                else
                {
                    sockets[sock].T4proc &= ~(T4_PROC_SND_START);
                    errno = ENOBUFS;
                    return SOCKET_ERROR;

                }
            }

        }
        else
        {
            sockets[sock].T4proc |= (T4_PROC_SND_START);
            ercd = tcp_snd_dat( cepid, (VP)sockets[sock].snd_buf, length,
                                TMO_NBLK );
            if ( ercd == E_WBLK )
            {
                ercd = length;  /* Return length of data even though it may not been sent*/
            }
            else
            {
                sockets[sock].T4proc &= ~(T4_PROC_SND_START);
                errno = ENOBUFS;
                return SOCKET_ERROR;
            }
        }
        if (sockets[sock].tmout == TMO_FEVR)
        {
            while (1)
            {
                if (  (sockets[sock].sndLen == sockets[sock].sndSz)
                        || (0 != (sockets[sock].socket_proc & SOCKET_PROC_CLS_END))
                        || (  this_id != sockets[sock].create_id)
                        || (sockets[sock].socket_type ==  ERR_OTHERS))
                {
                    break;
                }
                r_socket_task_switch(sock);
            }
            if (this_id != sockets[sock].create_id)
            {
                errno = ECONNABORTED;
                ercd  = SOCKET_ERROR;
            }
            else
            {
                sockets[sock].socket_proc &= ~(SOCKET_PROC_SND);
                if (sockets[sock].sndLen == sockets[sock].sndSz)
                {
                    ercd = length;
                }
                else
                {
                    errno = ECONNABORTED;
                    ercd  = SOCKET_ERROR;
                }
            }
        }
        else
        {
            ercd = length;  /* Return length of data even though it may not been sent*/
        }
    }
    return ercd;
}


/******************************************************************************
* Function Name: sendto
* Description  : The sendto function is used to send outgoing data on a socket
*                of type datagram.
* Arguments    : sock - Socket descriptor returned from a previous call to socket
*                buffer - application data buffer containing data to transmit
*                length - length of data in bytes
*                to - pointer to the the sockaddr structure containing the destination address.
*                tolen - length of the sockaddr structure.
* Return Value : Number of bytes sent for success, SOCKET_ERROR indicates an error.
******************************************************************************/
int r_sendto( int sock,  const void * buffer, uint32_t length, const sockaddr_in *addr)
{
    ER ercd = E_OK;
    uint32_t this_id;
    int  cepid;

    errno = E_OK;
    this_id = sockets[sock].create_id;
#ifdef R_SOCKET_PAR_CHECK
    if (sendto_par_check(sock, buffer, length, to, tolen) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */

    if (sockets[sock].event == SOCKET_ERR_CEP)
    {
        errno = ECONNABORTED;
        return SOCKET_ERROR;
    }
    if ( 0 != (sockets[sock].T4proc & T4_PROC_SND_START))
    {
        errno = ENOBUFS;
        return SOCKET_ERROR;
    }
    if ( sockets[sock].socket_type == SOCK_DGRAM )
    {

        if ( sockets[sock].state < BSD_CREATED ) /* must create and bind before send */
        {
            errno = ENOTCONN;
            return SOCKET_ERROR;
        }
        if ( length > BSD_SND_BUFSZ)
        {
            errno = ENOBUFS;
            return SOCKET_ERROR;
        }
        cepid = sock + 1 - MAX_TCP_CCEP;

        if ( sockets[sock].state < BSD_CONNECTED )
        {
            sockets[sock].dstaddr.ipaddr = addr->sin_addr.S_un.S_addr;
            sockets[sock].dstaddr.portno = htons(addr->sin_port);
        }

        memcpy( sockets[sock].snd_buf, buffer, length );
        sockets[sock].sndLen = 0;
        sockets[sock].sndSz = length;
        sockets[sock].pending_sndlen = length;
        sockets[sock].T4proc &= ~(T4_PROC_SND_END);
        sockets[sock].T4proc |= (T4_PROC_SND_START);
        ercd = udp_snd_dat( cepid, (T_IPV4EP*) & sockets[sock].dstaddr, (VP)sockets[sock].snd_buf, length, TMO_NBLK );
        if ( ercd == E_WBLK )
        {
            ercd = length;  /* Return length of data even though it may not been sent*/

        }
        else
        {
            sockets[sock].T4proc &= ~((uint32_t)T4_PROC_SND_START);
            errno = ENOBUFS;
            return SOCKET_ERROR;
        }
        if (sockets[sock].tmout == TMO_FEVR)
        {
            while (1)
            {
                if (  (sockets[sock].sndLen == sockets[sock].sndSz)
                        || (  this_id != sockets[sock].create_id)
                        || (0 != (sockets[sock].socket_proc & SOCKET_PROC_CLS_END))
                        || (sockets[sock].socket_type ==  ERR_OTHERS))
                {
                    break;
                }
                r_socket_task_switch(sock);
            }
            if (this_id != sockets[sock].create_id)
            {
                errno = ECONNABORTED;
                return SOCKET_ERROR;
            }
            if ( 0 != (sockets[sock].socket_proc & SOCKET_PROC_CLS_END))
            {
                errno = ECONNABORTED;
                return SOCKET_ERROR;
            }
            else
            {
                sockets[sock].socket_proc &= ~(SOCKET_PROC_SND);
                if (sockets[sock].sndLen == sockets[sock].sndSz)
                {
                    ercd = length;
                }
                else
                {
                    errno = ECONNABORTED;
                    return SOCKET_ERROR;
                }
            }
        }
        else
        {
            ercd = length;  /* Return length of data even though it may not been sent*/
        }

    }
    else
    {
        errno = EOPNOTSUPP;     /* The socket argument is associated with a socket that */
        /* does not support one or more of the values set in flags. */
        return SOCKET_ERROR;

    }
    return ercd;
}


/******************************************************************************
* Function Name: recv
* Description  : The recv() function is used to receive incoming data that has been
*                queued for a socket.
* Arguments    : sock - Socket descriptor returned from a previous call to socket
*                buffer - application data receive buffer
*                length - buffer length in bytes
* Return Value : Number of bytes returned for success, SOCKET_ERROR indicates an error.
******************************************************************************/
int r_recv(int sock, void * buffer, uint32_t length)
{
    sockaddr_in from;      /* No use. To pass par check */
#ifdef R_SOCKET_PAR_CHECK
    if (recv_par_check(sock, buffer, length) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */

    if ( sockets[sock].socket_type != SOCK_STREAM )
    {
        errno = EPROTONOSUPPORT;
        return SOCKET_ERROR;
    }
    return r_recvfrom( sock, buffer, length, &from);
}


/******************************************************************************
* Function Name: recvfrom
* Description  : The recvfrom() function is used to receive incoming data that has been
*                queued for a socket.
* Arguments    : sock - Socket descriptor returned from a previous call to socket
*                buffer - application data receive buffer
*                length - buffer length in bytes
*                from - pointer to the the sockaddr structure that will be filled
*                       in with the destination address.
*                fromlen - size of buffer pointed by from.
* Return Value : Number of bytes returned for success, SOCKET_ERROR indicates an error.
******************************************************************************/
int r_recvfrom( int sock, void * buffer, uint32_t length, sockaddr_in *remoteaddr)
{
    int BytesRead = 0;
    unsigned char * buf;
    int  cepid;
    int  len;
    ER   ercd;
    uint32_t this_id;

#ifdef R_SOCKET_PAR_CHECK
    if (recvfrom_par_check(sock, buffer, length, from, fromlen) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */

    this_id = sockets[sock].create_id;
    if ((sockets[sock].tmout != TMO_FEVR) && (sockets[sock].tmout != TMO_NBLK))
    {
        errno = EINVAL;
        return SOCKET_ERROR;
    }
    if ((sockets[sock].tmout == TMO_NBLK) && (sockets[sock].event == SOCKET_ERR_CEP))
    {
        errno = ECONNRESET;
        return SOCKET_ERROR;
    }
    buf = (unsigned char *)buffer;
    if ( sockets[sock].socket_type == SOCK_STREAM ) /* TCP */
    {
        cepid = sock + 1;
        if ( sockets[sock].state !=  BSD_CONNECTED && sockets[sock].state !=  BSD_CLOSING)
        {
            errno = ENOTCONN;
            return SOCKET_ERROR;
        }
        if ( sockets[sock].rcvLen > 0 ) /* Previous data remain in read_buf. */
        {
            if ( length > sockets[sock].rcvLen )
            {
                BytesRead = sockets[sock].rcvLen;
            }
            else
            {
                BytesRead = length;
            }
            if (sockets[sock].rcvout_offset + BytesRead > BSD_RCV_BUFSZ)
            {
                int cnt;
                cnt =  BSD_RCV_BUFSZ - sockets[sock].rcvout_offset;
                memcpy(buf, (const char *)&sockets[sock].rcv_buf[sockets[sock].rcvout_offset], cnt);
                sockets[sock].rcvout_offset = 0;
                memcpy(&buf[cnt], (const char *)&sockets[sock].rcv_buf[0], BytesRead - cnt);
                sockets[sock].rcvout_offset += (BytesRead - cnt);

            }
            else
            {
                memcpy(buf, (const char *)&sockets[sock].rcv_buf[sockets[sock].rcvout_offset], BytesRead);
                sockets[sock].rcvout_offset += BytesRead;
            }
            len = sockets[sock].rcvLen;
            sockets[sock].rcvLen -= BytesRead;
            if ( len == BSD_RCV_BUFSZ && sockets[sock].state ==  BSD_CONNECTED)
            {
                int size;
                if (sockets[sock].rcvin_offset == BSD_RCV_BUFSZ)
                {
                    sockets[sock].rcvin_offset = 0;
                }
                if ((BSD_RCV_BUFSZ - sockets[sock].rcvin_offset) > BSD_RCV_BUFSZ - sockets[sock].rcvLen)
                {
                    size = BSD_RCV_BUFSZ - sockets[sock].rcvLen;
                }
                else
                {
                    size = BSD_RCV_BUFSZ - sockets[sock].rcvin_offset;
                }
                sockets[sock].pending_rcvlen = size;
                sockets[sock].T4proc &= ~((uint32_t)T4_PROC_RCV_END);
                sockets[sock].T4proc |= ((uint32_t)T4_PROC_RCV_START);
                ercd = tcp_rcv_dat(cepid, (VP)(&sockets[sock].rcv_buf[sockets[sock].rcvin_offset]), size, TMO_NBLK);
                if ((ercd != E_WBLK) && (ercd != E_QOVR))
                {
                    /* fatal error */
                    sockets[sock].state = BSD_FATALERROR;
                }
            }
            return BytesRead;
        }
        if ( sockets[sock].rcvLen == 0 ) /* Previous data remain in read_buf. */
        {

            if (sockets[sock].finrcv == 1)
            {
                return 0;
            }
            if ( sockets[sock].tmout == TMO_NBLK )
            {
                errno = EAGAIN;
                return SOCKET_ERROR;
            }
            else
            {
                sockets[sock].T4proc &= ~((uint32_t)T4_PROC_RCV_END);
                while (1)
                {
                    if (  (sockets[sock].rcvLen > 0)
                            || (sockets[sock].finrcv == 1)
                            || (0 != (sockets[sock].socket_proc & SOCKET_PROC_CLS_END))
                            || (this_id != sockets[sock].create_id)
                            || (sockets[sock].socket_type ==  ERR_OTHERS))
                    {
                        break;
                    }
                    r_socket_task_switch(sock);
                }

                if ( this_id != sockets[sock].create_id)
                {
                    errno = ECONNABORTED;
                    return SOCKET_ERROR;
                }
                if ( 0 != (sockets[sock].socket_proc & SOCKET_PROC_CLS_END))
                {
                    errno = ECONNABORTED;
                    return SOCKET_ERROR;
                }
                if ( sockets[sock].rcvLen > 0 ) /* Previous data remain in read_buf. */
                {
                    if ( length > sockets[sock].rcvLen )
                    {
                        BytesRead = sockets[sock].rcvLen;
                    }
                    else
                    {
                        BytesRead = length;
                    }
                    if (sockets[sock].rcvout_offset + BytesRead > BSD_RCV_BUFSZ)
                    {
                        int cnt;
                        cnt =  BSD_RCV_BUFSZ - sockets[sock].rcvout_offset;
                        memcpy(buf, (const char *)&sockets[sock].rcv_buf[sockets[sock].rcvout_offset], cnt);
                        sockets[sock].rcvout_offset = 0;
                        memcpy(&buf[cnt], (const char *)&sockets[sock].rcv_buf[0], BytesRead - cnt);
                        sockets[sock].rcvout_offset += (BytesRead - cnt);
                    }
                    else
                    {
                        memcpy(buf, (const char *)&sockets[sock].rcv_buf[sockets[sock].rcvout_offset], BytesRead);
                        sockets[sock].rcvout_offset += BytesRead;
                    }
                    len = sockets[sock].rcvLen;
                    sockets[sock].rcvLen -= BytesRead;
                    if ( len == BSD_RCV_BUFSZ && sockets[sock].state ==  BSD_CONNECTED )
                    {
                        int size;
                        if (sockets[sock].rcvin_offset == BSD_RCV_BUFSZ)
                        {
                            sockets[sock].rcvin_offset = 0;
                        }
                        if ((BSD_RCV_BUFSZ - sockets[sock].rcvin_offset) > BSD_RCV_BUFSZ - sockets[sock].rcvLen)
                        {
                            size = BSD_RCV_BUFSZ - sockets[sock].rcvLen;
                        }
                        else
                        {
                            size = BSD_RCV_BUFSZ - sockets[sock].rcvin_offset;
                        }
                        sockets[sock].pending_rcvlen = size;
                        sockets[sock].T4proc &= ~((uint32_t)T4_PROC_RCV_END);
                        sockets[sock].T4proc |= ((uint32_t)T4_PROC_RCV_START);
                        tcp_rcv_dat(cepid, (VP)(&sockets[sock].rcv_buf[sockets[sock].rcvin_offset]), size, TMO_NBLK);
                    }
                    return BytesRead;
                }
                if ( sockets[sock].rcvLen == 0 ) /* Previous data remain in read_buf. */
                {
                    if (sockets[sock].finrcv == 1)
                    {
                        return 0;
                    }
                    else
                    {
                    }
                }
                return SOCKET_ERROR;

            }
        }
    }
    else
    {
        if ( sockets[sock].state < BSD_CREATED ) /* must call bind before recv */
        {
            errno = ENOTCONN;
            return SOCKET_ERROR;
        }
        cepid = sock + 1 - MAX_TCP_CCEP;

        if ( sockets[sock].rcvLen > 0 ) /* Previous data remain in read_buf. */
        {
            if ( length > sockets[sock].rcvLen )
            {
                BytesRead = sockets[sock].rcvLen;
            }
            else
            {
                BytesRead = length;
            }
            if (sockets[sock].rcvout_offset + BytesRead > BSD_RCV_BUFSZ)
            {
                int cnt;
                cnt =  BSD_RCV_BUFSZ - sockets[sock].rcvout_offset;
                memcpy(buf, (const char *)&sockets[sock].rcv_buf[sockets[sock].rcvout_offset], cnt);
                sockets[sock].rcvout_offset = 0;
                memcpy(&buf[cnt], (const char *)&sockets[sock].rcv_buf[0], BytesRead - cnt);
                sockets[sock].rcvout_offset += (BytesRead - cnt);

            }
            else
            {
                memcpy(buf, (const char *)&sockets[sock].rcv_buf[sockets[sock].rcvout_offset], BytesRead);
                sockets[sock].rcvout_offset += BytesRead;
            }
            sockets[sock].rcvLen -= BytesRead;
            /* Must return the addr also */
            if ( remoteaddr != NULL )
            {
//                remoteaddr = (sockaddr_in *)from;
                remoteaddr->sin_family = AF_INET;
                remoteaddr->sin_port = sockets[sock].dstaddr.portno;
                remoteaddr->sin_port = sockets[sock].dstaddr.portno;
                remoteaddr->sin_addr.S_un.S_addr = sockets[sock].dstaddr.ipaddr;
            }
//            if ( fromlen != NULL )
//            {
//                *fromlen = sizeof(sockaddr_in); /* fixed? why? */
//            }
            return BytesRead;
        }
        if ( sockets[sock].rcvLen == 0 ) /* Previous data remain in read_buf. */
        {
            if ( sockets[sock].tmout == TMO_NBLK )
            {
                errno = EAGAIN;
                return SOCKET_ERROR;
            }
            else
            {
                sockets[sock].T4proc &= ~((uint32_t)T4_PROC_RCV_END);
                while (1)
                {
                    if (  (sockets[sock].rcvLen > 0)
                            || (0 != (sockets[sock].socket_proc & SOCKET_PROC_CLS_END))
                            || (this_id != sockets[sock].create_id)
                            || (sockets[sock].socket_type ==  ERR_OTHERS))
                    {
                        break;
                    }
                    r_socket_task_switch(sock);
                }

                if ( this_id != sockets[sock].create_id)
                {
                    errno = ECONNABORTED;
                    return SOCKET_ERROR;
                }
                if ( 0 != (sockets[sock].socket_proc & SOCKET_PROC_CLS_END))
                {
                    errno = ECONNABORTED;
                    return SOCKET_ERROR;
                }
                if ( sockets[sock].rcvLen > 0 ) /* Previous data remain in read_buf. */
                {
                    if ( length > sockets[sock].rcvLen )
                    {
                        BytesRead = sockets[sock].rcvLen;
                    }
                    else
                    {
                        BytesRead = length;
                    }
                    if (sockets[sock].rcvout_offset + BytesRead > BSD_RCV_BUFSZ)
                    {
                        int cnt;
                        cnt =  BSD_RCV_BUFSZ - sockets[sock].rcvout_offset;
                        memcpy(buf, (const char *)&sockets[sock].rcv_buf[sockets[sock].rcvout_offset], cnt);
                        sockets[sock].rcvout_offset = 0;
                        memcpy(&buf[cnt], (const char *)&sockets[sock].rcv_buf[0], BytesRead - cnt);
                        sockets[sock].rcvout_offset += (BytesRead - cnt);

                    }
                    else
                    {
                        memcpy(buf, (const char *)&sockets[sock].rcv_buf[sockets[sock].rcvout_offset], BytesRead);
                        sockets[sock].rcvout_offset += BytesRead;
                    }
                    sockets[sock].rcvLen -= BytesRead;
                    if ( remoteaddr != NULL )
                    {
                        remoteaddr->sin_family = AF_INET;
                        remoteaddr->sin_port = sockets[sock].dstaddr.portno;
                        remoteaddr->sin_port = sockets[sock].dstaddr.portno;
                        remoteaddr->sin_addr.S_un.S_addr = sockets[sock].dstaddr.ipaddr;
                    }
                    return BytesRead;
                }
                if ( sockets[sock].rcvLen == 0 ) /* Previous data remain in read_buf. */
                {
                }
                return SOCKET_ERROR;
            }
        }
    }
    return BytesRead;
}


/******************************************************************************
* Function Name: closesocket
* Description  : The closesocket() function closes an existing socket.
* Arguments    : sock - Socket descriptor returned from a previous call to socket
* Return Value : E_OK for success, SOCKET_ERROR indicates an error.
******************************************************************************/
int r_close( int sock )
{
    ER ercd = E_OK;
    int  cepid;

    errno = E_OK;
#ifdef R_SOCKET_PAR_CHECK
    if (closesocket_par_check(sock) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */


    if ((sockets[sock].tmout != TMO_FEVR) && (sockets[sock].tmout != TMO_NBLK))
    {
        errno = ENOTSOCK;   /* No socket created */
        return SOCKET_ERROR;
    }

    if ( sockets[sock].socket_type == SOCK_STREAM )
    {

        if ((sockets[sock].event == SOCKET_ERR_CEP)) /* if I want to close a socket with error?*/
        {
            if ((sockets[sock].state == BSD_CONNECTED))
            {
                /* Close a socket error */
                ercd = tcp_cls_cep(sock + 1, T4_TCP_CLS_CEP_TMOUT);
            }
            sockets[sock].state = BSD_CLOSED; /* In callback it will change to BSD_CLOSED */
            sockets[sock].event = -1;
            return E_OK;
        }
        if ( sockets[sock].event == SOCKET_CLS_CEP)
        {
            sockets[sock].state = BSD_CLOSED;
            sockets[sock].event = -1;
            return E_OK;
        }
        if ( sockets[sock].state == BSD_CLOSED)
        {
            errno = EINVAL;
            return SOCKET_ERROR;
        }
        if ( sockets[sock].state <= BSD_BOUND)
        {
            reset_socket(sock);
            sockets[sock].state = BSD_CLOSED;
            sockets[sock].event = -1;
            return E_OK;
        }
        /*------------------------------*/
        if ( sockets[sock].state == BSD_LISTENING)
        {
            if (sockets[sock].peer_socket != -1)
            {
                if (sockets[sockets[sock].peer_socket].state >= BSD_CONNECTING)
                {
                    sockets[sockets[sock].peer_socket].T4proc &= ~T4_PROC_CAN_END;
                    sockets[sockets[sock].peer_socket].T4proc |= T4_PROC_CAN_START;
                    if (E_OK == tcp_can_cep(sockets[sock].peer_socket + 1, TFN_TCP_ALL))
                    {
                        while (0 == (sockets[sockets[sock].peer_socket].T4proc & T4_PROC_CAN_END))
                        {
                            r_socket_task_switch(sock);
                        }
                    }
                    else
                    {
                        sockets[sockets[sock].peer_socket].T4proc &= ~T4_PROC_CAN_START;
                    }
                    if (sockets[sockets[sock].peer_socket].state >= BSD_CLOSING)
                    {
                        tcp_cls_cep(sockets[sock].peer_socket + 1, T4_TCP_CLS_CEP_TMOUT);
                    }
                    reset_socket(sockets[sock].peer_socket);
                }
            }
            sockets[sock].socket_proc |= SOCKET_PROC_CLS_END;
            reset_socket(sock);
            return E_OK;
        }
        else if (sockets[sock].state == BSD_CONNECTING)
        {
            sockets[sock].T4proc &= ~T4_PROC_CAN_END;
            sockets[sock].T4proc |= T4_PROC_CAN_START;
            if (E_OK == tcp_can_cep(sock + 1, TFN_TCP_ALL))
            {
                while (0 == (sockets[sock].T4proc & T4_PROC_CAN_END))
                {
                    r_socket_task_switch(sock);
                }
            }
            else
            {
                sockets[sock].T4proc &= ~T4_PROC_CAN_START;
            }
            tcp_cls_cep(sock + 1, T4_TCP_CLS_CEP_TMOUT);
            sockets[sock].socket_proc |= SOCKET_PROC_CLS_END;
            reset_socket(sock);
            return E_OK;
        }
        else if (sockets[sock].state == BSD_CLOSING)
        {
            sockets[sock].T4proc |= T4_PROC_CAN_START;
            if (E_OK == tcp_can_cep(sock + 1, TFN_TCP_ALL))
            {
                while (0 == (sockets[sock].T4proc & T4_PROC_CAN_END))
                {
                    r_socket_task_switch(sock);
                }
            }
            else
            {
                sockets[sock].T4proc &= ~T4_PROC_CAN_START;
            }
            tcp_cls_cep(sock + 1, T4_TCP_CLS_CEP_TMOUT);
            sockets[sock].socket_proc |= SOCKET_PROC_CLS_END;
            reset_socket(sock);
            return E_OK;
        }
        else if (sockets[sock].state == BSD_CONNECTED)
        {
            sockets[sock].socket_proc |= SOCKET_PROC_CLS_START;
            sockets[sock].T4proc &= ~T4_PROC_CAN_END;
            sockets[sock].T4proc |= T4_PROC_CAN_START;
            if (E_OK == tcp_can_cep(sock + 1, TFN_TCP_ALL))
            {
                while (0 == (sockets[sock].T4proc & T4_PROC_CAN_END))
                {
                    r_socket_task_switch(sock);
                }
            }
            else
            {
                sockets[sock].T4proc &= ~T4_PROC_CAN_START;
            }
            ercd = tcp_cls_cep(sock + 1, T4_TCP_CLS_CEP_TMOUT);
            sockets[sock].socket_proc |= SOCKET_PROC_CLS_END;
            reset_socket(sock);
            return E_OK;
        }
    }
    else
    {
        cepid = sock + 1 - MAX_TCP_CCEP;
        if ( 0 != (sockets[sock].T4proc & T4_PROC_SND_START))
        {
            ercd = udp_can_cep(cepid, TFN_UDP_ALL );
            if (ercd == E_OK)
            {
                while (0 == (sockets[sock].T4proc & T4_PROC_CAN_END))
                {
                    r_socket_task_switch(sock);
                }
            }
        }
        sockets[sock].socket_proc |= SOCKET_PROC_CLS_END;
        reset_socket(sock);
        ercd = E_OK;
    }
    return ercd;
}


/******************************************************************************
* Function Name: fcntl
* Description  : The fcntl() function for file control operations, e.g. opening a file,
*                retrieving and changing the permissions of file, or locking a file for edit
* Arguments    : sock - Socket descriptor returned from a previous call to socket
*                command - Command to execute
				 flags - flags
* Return Value : E_OK for success, SOCKET_ERROR indicates an error.
******************************************************************************/
int r_fcntl (int sock, int command, int flags)
{
    int ret_code = E_OK;

    errno = E_OK;
#ifdef R_SOCKET_PAR_CHECK
    if (fcntl_par_check(sock, command, flags) != true)
    {
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */

    if ( sockets[sock].state < BSD_CREATED )
    {
        errno = EINVAL;
        return SOCKET_ERROR;
    }
    switch (command)
    {
        case F_GETFL:
            ret_code = (int)sockets[sock].tmout;
            break;
        case F_SETFL:
            if ((flags & ~O_NONBLOCK) == 0)
            {
                flags = TMO_NBLK;
            }
            else
            {
                flags = TMO_FEVR;
            }
            sockets[sock].tmout = flags;
            if ( sockets[sock].peer_socket != -1)
            {
                sockets[sockets[sock].peer_socket].tmout = flags;
            }
            break;
        default:
            errno = EINVAL;
            ret_code = SOCKET_ERROR;
            break;
    }
    return ret_code;
}

/******************************************************************************
* Function Name: select
* Description  : The select() function examines a list/lists of file/socket descriptor
*              : for pending action (read, write or exception condition pending)
*              : This is synchronous I/O multiplexing
* Arguments    : nfds - range(or largest) descriptors in the fd_set
*              :      - check from 0 to nfds-1
*              : readfds - a set of descriptor to check for read readiness NULL-no check
*              : writefds - a set of descriptor to check for write readiness. NULL=no check
*              : errorfds - a set of descriptor to check for exception condition. NULL=no check
*              : timeout -  NULL-block, 0 - polling, n-wait time before timeout.
* Caveats      : No consideration for timeout / signals releasing yet
* Return Value : the total number of ready descriptors in all the output sets.
******************************************************************************/
int r_select (int nfds, r_fd_set *p_readfds, r_fd_set *p_writefds, r_fd_set *p_errorfds, r_timeval *timeout )
{
    int tot_count = 0, sockfd;
    uint16_t timer1;
    uint16_t timer2;
    r_fd_set readfds;
    r_fd_set writefds;
    r_fd_set errorfds;
#ifdef R_SOCKET_PAR_CHECK
    if (select_par_check(nfds, p_readfds, p_writefds, p_errorfds, timeout) != true)
    {
        if ( p_readfds != NULL )
        {
            FD_ZERO(p_readfds);
        }
        if ( p_writefds != NULL )
        {
            FD_ZERO(p_writefds);
        }
        if ( p_errorfds != NULL )
        {
            FD_ZERO(p_errorfds);
        }
        return E_PAR;
    }
#endif  /* R_SOCKET_PAR_CHECK */
    if ( timeout == NULL )
    {
    }
    else if ((timeout->tv_usec >= 1000000) || (timeout->tv_usec < 0) || (timeout->tv_sec < 0))
    {
        timeout = NULL;
    }
    else
    {
        timeout->tv_usec /= 10000;
    }
    timer1 = get_tcpudp_time();

    R_FD_COPY(p_readfds,  &readfds);
    R_FD_COPY(p_writefds, &writefds);
    R_FD_COPY(p_errorfds, &errorfds);

    while (1)
    {
        R_FD_COPY(&readfds, p_readfds);
        R_FD_COPY(&writefds, p_writefds);
        R_FD_COPY(&errorfds, p_errorfds);
        tot_count = 0;
        if ( p_readfds != NULL )
        {
            for ( sockfd = 0; sockfd < nfds; sockfd++ )
            {
                if ( R_FD_ISSET(sockfd, p_readfds))
                {
                    if ( is_sel_readable( sockfd ) == 0 )
                    {
                        R_FD_CLR(sockfd, p_readfds);
                    }
                    else
                    {
                        tot_count++;
                    }
                }
            }
        }
        if ( p_writefds != NULL )
        {
            for ( sockfd = 0; sockfd < nfds; sockfd++ )
            {
                if ( R_FD_ISSET(sockfd, p_writefds))
                {
                    if ( is_sel_writeable( sockfd ) == 0 )
                    {
                        R_FD_CLR(sockfd, p_writefds);
                    }
                    else
                    {
                        tot_count++;
                    }
                }
            }
        }

        if ( p_errorfds != NULL )
        {
            for ( sockfd = 0; sockfd < nfds; sockfd++ )
            {
                if ( R_FD_ISSET(sockfd, p_errorfds))
                {
                    if ( is_sel_errpending(sockfd ) == 0 )
                    {
                        R_FD_CLR(sockfd, p_errorfds);
                    }
                    else
                    {
                        tot_count++;
                    }
                }
            }
        }

        if (tot_count > 0)
        {
            break;
        }
        if (timeout != NULL)
        {
            timer2 = get_tcpudp_time();
            if (timer1 != timer2)
            {
                timer1 = timer2;
                timeout->tv_usec -= 10000;
                if (timeout->tv_usec < 0)
                {
                    timeout->tv_sec--;
                    timeout->tv_usec = 990000;
                    if (timeout->tv_sec < 0)
                    {
                        break;
                    }
                }
            }
        }
        r_socket_task_switch_select();
    }
    return tot_count;
}


/*********** helper function *******************************/
/******************************************************************************
* Function Name: htons
* Description  : The htons() function converts host byte order to net byte order with short int
* Arguments    : n - Host byte variable to be converted
* Return Value : Net byte order
******************************************************************************/
uint16_t htons(uint16_t n)
{
    return ((n & 0xff) << 8) | ((n & 0xff00) >> 8);
}

/******************************************************************************
* Function Name: htonl
* Description  : The htonl() function converts host byte order to net byte order with long int
* Arguments    : n - Host byte variable to be converted
* Return Value : Net byte order
******************************************************************************/
uint32_t htonl(uint32_t n)
{
    return ((n & 0xff) << 24) |
           ((n & 0xff00) << 8) |
           ((n & 0xff0000UL) >> 8) |
           ((n & 0xff000000UL) >> 24);
}

/******************************************************************************
* Function Name: ntohs
* Description  : The ntohs() function converts net byte order to host byte order with short int
* Arguments    : n - Host byte variable to be converted
* Return Value : Net byte order
******************************************************************************/
uint16_t ntohs(uint16_t n)
{
    return ((n & 0xff) << 8) | ((n & 0xff00) >> 8);
}

/******************************************************************************
* Function Name: ntohl
* Description  : The ntohl() function converts net byte order to host byte order with long int
* Arguments    : n - Host byte variable to be converted
* Return Value : Net byte order
******************************************************************************/
uint32_t ntohl(uint32_t n)
{
    return ((n & 0xff) << 24) |
           ((n & 0xff00) << 8) |
           ((n & 0xff0000UL) >> 8) |
           ((n & 0xff000000UL) >> 24);
}


/******************************************************************************
* Function Name: how_many_closed
* Description  : How many sockets with state == BSD_CLOSED (i.e. available for use)
* Arguments    : sock_type : socket_type
* Return Value : the number of BSD_CLOSED sockets of 'sock_type'
******************************************************************************/
int how_many_closed(ID sock_type )
{
    int j, found = 0;

    if ( SOCK_STREAM == sock_type )
    {
        for ( j = 0;j < MAX_TCP_CCEP; j++)
        {
            if ( sockets[j].state == BSD_CLOSED )
            {
                found++;
            }
        }
    }
    else
    {
        for ( j = MAX_TCP_CCEP;j < (MAX_TCP_CCEP + MAX_UDP_CCEP); j++)
        {
            if ( sockets[j].state == BSD_CLOSED )
            {
                found++;
            }
        }
    }
    return found;
}


/******************************************************************************
* Function Name: is_sel_readable, is_sel_writeable, is_sel_errpending
* Description  : Is this socket
*              : readable?
*              : writeable?
*              : has error pending?
* Arguments    : socks : socket
* Return Value : 1 if condition met
******************************************************************************/
// TODO : readable means socket is connected (STREAM) or BOUND (DGRAM)
static int is_sel_readable(int socks )
{
    int can_read = 0;

    /*Incoming data is ready to read (UDP) */
    if ((sockets[socks].socket_type == SOCK_DGRAM) &&
            (sockets[socks].state >= BSD_CREATED) &&
            (sockets[socks].rcvLen  > 0))
    {
        can_read = 1;
    }

    /* Incoming data is ready to read (TCP) */
    if ((sockets[socks].socket_type == SOCK_STREAM) &&
            (sockets[socks].state >= BSD_CONNECTED) &&
            (sockets[socks].rcvLen  > 0))
    {
        can_read = 1;
    }

    /* Receive FIN packet */
    if ((sockets[socks].socket_type == SOCK_STREAM) &&
            (sockets[socks].finrcv == 1) &&
            (sockets[socks].state == BSD_CLOSING))
    {
        can_read = 1;
    }

    /* Socket is in Listening state */
    if ((sockets[socks].socket_type == SOCK_STREAM) &&
            (sockets[socks].state == BSD_LISTENING) &&
            (sockets[socks].event == SOCKET_ACP_CEP ))
    {
//      sockets[socks].event = -1;  // One time use only
        can_read = 1;
    }

    /* Socket is in closesocket */
    if (0 != (sockets[socks].socket_proc & SOCKET_PROC_CLS_END))
    {
        can_read = 1;
    }

    /* Socket is in Listening state but peer socket is not allocated
       Trigger an "accept" to put T4 in connecting state iff there is a spare socket */
    if ((sockets[socks].state == BSD_LISTENING) &&
            (sockets[socks].socket_type == SOCK_STREAM) &&
            (sockets[socks].peer_socket == -1 ))
    {
        if ( how_many_closed(SOCK_STREAM) )
        {
            can_read = 1;
        }
    }

    return can_read;
}
// TODO : writeable means socket is connected (STREAM) or BOUND (DGRAM)
static int is_sel_writeable(int socks)
{
    int can_write = 0;

    /* UDP */
    if ((sockets[socks].socket_type == SOCK_DGRAM) &&
            (sockets[socks].state >= BSD_CREATED) &&
            (sockets[socks].sndSz == sockets[socks].sndLen)) // All data has been sent completely, available for next sending
    {
        can_write = 1;
    }

    /* TCP */
    if ((sockets[socks].socket_type == SOCK_STREAM) &&
            (sockets[socks].state >= BSD_CONNECTED) &&
            (sockets[socks].sndSz == sockets[socks].sndLen)) // All data has been sent completely, available for next sending
    {
        can_write = 1;
    }

    /* Connect() request to server's socket completely */
    if ((sockets[socks].socket_type == SOCK_STREAM) &&
            (sockets[socks].state >= BSD_CONNECTED))
    {
        switch (sockets[socks].event)
        {
            case SOCKET_CON_CEP:
                can_write = 1;
                sockets[socks].event = -1;
                break;
            default:
                break;
        }
    }

    return can_write;
}


// TODO : What sort of error can I track
// TODO : Does the socket layer get all information from T4?
static int is_sel_errpending(int socks)
{
    int can_err = 0;

    if ( (sockets[socks].socket_type == SOCK_STREAM) &&
            (sockets[socks].state == BSD_CLOSING) &&
            (sockets[socks].event == SOCKET_ERR_CEP))
    {
        /* T4 Error */
        if (sockets[socks].T4status == T4_ERROR_CLOSE)
        {
            can_err = 1;
        }

        /* Error due to sending data to closed connection */
        if (sockets[socks].finrcv == 1)
        {
            can_err = 1;
        }
    }

    /* Close socket successfully */
    if ((sockets[socks].socket_type == SOCK_STREAM) &&
            (sockets[socks].state == BSD_CLOSED) && (sockets[socks].T4status == T4_CLOSED))
    {
        can_err = 1;
    }

    /* Cancel API */
    if ((sockets[socks].socket_type == SOCK_STREAM) &&
            (sockets[socks].state <= BSD_CONNECTED))
    {
        switch (sockets[socks].err_type)
        {
            case ERR_RLWAI_ACP:
            case ERR_RLWAI_CON:
            case ERR_RLWAI_SND:
            case ERR_RLWAI_RCV:
            case ERR_RLWAI_RCV_TEV:
            case ERR_RLWAI_CLS:
                can_err = 1;
                break;
            default:
                break;
        }
    }

    return can_err;
}


/******************************************************************************
* Function Name: dup_tcp_socket
* Description  : Make a duplicate socket
* Arguments    : sock      Socket descriptor
* Return Value : peersocket a "clone" of sock
*                   SOCKET_ERROR indicates an error.
*              : if successful, peersocket = new socket
******************************************************************************/
static int dup_tcp_socket( int sock )           // Make a duplicate of a socket
{
    int i;
    int semp_ret;

    semp_ret = E_OK;

#if (SOCKET_IF_USE_SEMP == 1)
    semp_ret = r_socket_sem_lock();            /* Return immediately if lock cannot be acquired? */
#endif
    if (semp_ret != E_OK)
    {
        return  SOCKET_ERROR;    /* No sockets available */
    }
    for (i = 0;i < MAX_TCP_CCEP;i++ )
    {
        if ( i != sock )
        {
            if ( sockets[i].state == BSD_CLOSED )
            {
                break;
            }
        }
    }
    if ( i != MAX_TCP_CCEP )
    {
        memcpy( &sockets[i], &sockets[sock], sizeof(BSDSocket));
        tcp_ccep[i].cepatr = tcp_ccep[sock].cepatr; /* Choose same channel; */
        tcp_ccep[i].callback = t4_tcp_generic_callback;
        sockets[i].peer_socket = -1; /* Set this is a peer socket */
        ++create_id;
        sockets[i].create_id = create_id;
    }
    else
    {
        i = SOCKET_ERROR;
    }
#if (SOCKET_IF_USE_SEMP == 1)
    r_socket_sem_release();
#endif
    return i;
}


/******************************************************************************
* Function Name: reset_socket
* Description  : Clean up a TCP socket without affecting the underlying T4
*              : Is that enough? May have already called tcp_acp_con();
* Arguments    : sock      Socket descriptor
* Return Value : E_OK
******************************************************************************/
static int reset_socket( int sock )     // Clear a socket. make it
{
    if ( sock != -1 )
    {
        sockets[sock].state = BSD_CLOSED;
        sockets[sock].T4status = T4_CLOSED;
        sockets[sock].event = -1;
        sockets[sock].socket_type = 0;
        sockets[sock].backlog = 0;
        sockets[sock].dstaddr.ipaddr = 0;
        sockets[sock].dstaddr.portno = 0;
        sockets[sock].tmout = 0;  //default is TMO_POL
        sockets[sock].T4proc &= (T4_PROC_CAN_END | T4_PROC_CLS_END ) ;
        sockets[sock].rcvLen = 0;
        sockets[sock].sndLen = 0;
        sockets[sock].sndSz = 0;
        sockets[sock].err_type = ERR_NONE; // No errors
        sockets[sock].peer_socket = -1;
        sockets[sock].finrcv = 0;
        tcp_ccep[sock].rbufsz = SOCKET_TCP_WINSIZE;
    }
    return E_OK;
}


#define EPHEMERAL_PORT_MAX (65535)
#define EPHEMERAL_PORT_MIN (49152)
static uint16_t get_ephemeral_port(void)
{
    uint32_t value;
    get_random_number((UB *)&value, 4);

    value %= (((uint32_t)EPHEMERAL_PORT_MAX + 1) - EPHEMERAL_PORT_MIN);
    value += EPHEMERAL_PORT_MIN;

    return (uint16_t)value;

}

