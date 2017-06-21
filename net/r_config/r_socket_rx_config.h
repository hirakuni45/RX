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
* Copyright (C) 2011(2015) Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_socket_rx_config.h
* Version      : 1.31
* Description  : Configures the socket interface for T4
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 17.09.2012 1.00    First Release (With RSKRX62N support)
*         : 21.05.2013 1.01    Re-Release (With RSKRX62N, RX63N support)
*         : 05.01.2015 1.02    Change file name
*         : 31.01.2015 1.20    Support 2nd Ether channel.
*         : 31.01.2015 1.30    Support select() function.
*         : 01.10.2016 1.31    Deleted USE_BSD_NON_BLOCKING macro. 
*         :                    Added SOCKET_TCP_WINSIZE macro.
*         :                    Changed R_SOCKET_Init() API name to R_SOCKET_Open().
*         :                    Added R_SOCKET_Close().
*         :                    Omitted Ether-2 channels support.
***********************************************************************************************************************/
#ifndef R_SOCKET_RX_CONFIG_H
#define R_SOCKET_RX_CONFIG_H

///#ifndef MAX_UDP_CCEP
///#define MAX_UDP_CCEP        (4)
///#endif
///#ifndef MAX_TCP_CCEP
///#define MAX_TCP_CCEP        (8)
///#endif
///#ifndef MAX_TCP_CREP
///#define MAX_TCP_CREP        MAX_TCP_CCEP
///#endif

#define SOCKET_TCP_WINSIZE   (1460)

#define TCPUDP_WORK         (13344)

///#define TOTAL_BSD_SOCKET    (MAX_TCP_CCEP + MAX_UDP_CCEP)

/// #define R_SOCKET_PAR_CHECK  (1) /* comment out this to skip parameter checking */

#define SOCKET_IF_USE_SEMP  (0)

#define BSD_RCV_BUFSZ        (1460)
#define BSD_SND_BUFSZ        (1460)

#endif /* R_SOCKET_CONFIG_H */

