/**********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURCOORDE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE COORDSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_socket_par_check.h
* Description  : Functions for checking socket parameter.
***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 26.09.2013 1.00    First Release
**********************************************************************************************************************/
#ifndef R_SOCKET_PAR_CHECK_H
#define R_SOCKET_PAR_CHECK_H


/**********************************************************************************************************************
Includes <System Includes>, "Project Includes"
**********************************************************************************************************************/
#include <stdbool.h>
#include "r_t4_itcpip.h"
#include "r_socket_rx_config.h"
//#include "r_t4_config.h"
#include "r_socket_rx_if.h"


#ifdef R_SOCKET_PAR_CHECK
/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/


/**********************************************************************************************************************
Typedef definitions
**********************************************************************************************************************/


/**********************************************************************************************************************
Exported global variables
**********************************************************************************************************************/


/**********************************************************************************************************************
Public Functions
**********************************************************************************************************************/
bool socket_par_check(int domain, int type, int protocol);
bool bind_par_check(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
bool connect_par_check(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
bool listen_par_check(int sockfd, int backlog);
bool accept_par_check(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
bool send_par_check(int sockfd, const void *buf, size_t len, int flags);
bool sendto_par_check(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);
bool recv_par_check(int sockfd, void *buf, size_t len, int flags);
bool recvfrom_par_check(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);
bool shutdown_par_check(int sockfd);
bool closesocket_par_check(int sockfd);
bool fcntl_par_check(int sockfd, int cmd, int flags);
bool select_par_check( int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
                       struct timeval *timeout);


#endif  /* R_SOCKET_PAR_CHECK */

#endif  /* R_SOCKET_PAR_CHECK_H */
