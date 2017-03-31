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
* File Name    : r_t4_ftp_server_rx_config.h
* Description  : Configuration options for the r_t4_ftp_server_rx module.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 09.05.2014 1.02    First Release
***********************************************************************************************************************/
#ifndef R_T4_FTP_SERVER_RX_CONFIG_H
#define R_T4_FTP_SERVER_RX_CONFIG_H

#if	!defined(T4_FTP_SERVER_FIRST) && defined(T4_FTP_SERVER)
#include "r_t4_http_server_rx_config.h"
#endif	/* !defined(T4_FTP_SERVER_FIRST) && defined(T4_FTP_SERVER) */

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/
#define	FTP_TCP_CEP_NUM		6		// Adapt myself to the communication endpoint number of config_tcpudp.c

#if	defined(T4_FTP_SERVER_FIRST) || !defined(T4_FTP_SERVER)
#define	FTP_START_TCP_CEP	0					// starting position of the communication endpoint in config_tcpudp.c
#else	/* defined(T4_FTP_SERVER_FIRST) || !defined(T4_FTP_SERVER) */
#define	FTP_START_TCP_CEP	HTTP_TCP_CEP_NUM	// starting position of the communication endpoint in config_tcpudp.c
#endif	/* defined(T4_FTP_SERVER_FIRST) || !defined(T4_FTP_SERVER) */

#define FTP_MAX_FILE_LIST	10		// A maximum number of the file (a directory) information that acquires from a file driver by a LIST,NLST response at a time

#define	CMD_BUF_SIZE	272		// A transmission and reception buffer for command port
#define	DATA_BUF_SIZE	(2560)	// A transmission and reception buffer for data port

#define MAX_USER	(3)

#define LF_CODE 		"\r\n"	// Line feed code which server uses.

#define PATH_NAME_SIZE	(64)	// the limitation size of file path

#define	USER_LIST		{"user1"},  {"user2"},  {"user3"}
#define	PASS_LIST		{"user01"}, {"user02"}, {"user03"}
#define	ROOT_DIR_LIST	{"/"},      {"/"},      {"/"}

#endif /* R_T4_FTP_SERVER_RX_CONFIG_H */


