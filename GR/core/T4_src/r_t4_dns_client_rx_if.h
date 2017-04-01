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
* File Name	   : r_t4_dns_client_rx_if.h
* Version      : 1.01
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 09.05.2014 1.01    Corresponded to FIT Modules
***********************************************************************************************************************/
#ifndef	R_T4_DNS_CLIENT_RX_IF_H
#define	R_T4_DNS_CLIENT_RX_IF_H

#include "../r_config/r_t4_dns_client_rx_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Version Number of API. */
#define T4_DNS_CLIENT_VERSION_MAJOR       (1)
#define T4_DNS_CLIENT_VERSION_MINOR       (01)

#ifndef	E_DNS_INTERNAL
#define	E_DNS_INTERNAL		-1		/* Internal Error */
#endif	/* E_DNS_INTERNAL	*/
#ifndef	E_DNS_PROCESSING
#define	E_DNS_PROCESSING	-2		/* Processing	*/
#endif	/* E_DNS_PROCESSING	*/
#ifndef	E_DNS_TIMEOUT
#define	E_DNS_TIMEOUT		-3		/* DNS time out	*/
#endif	/* E_DNS_TIMEOUT	*/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct _name_table
{
	char name[NAME_SIZE];
	unsigned char ipaddr[4];
}NAME_TABLE;

typedef	int32_t (*DNS_CB_FUNC)(int32_t ercd, NAME_TABLE *table);

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
#if defined(__GNUC__) || defined(GRSAKURA)
#if defined(__cplusplus)
extern "C" {
#endif
#endif
void		R_dns_init(void);
int32_t		R_dns_resolve_name(char *name, DNS_CB_FUNC func);
int32_t		R_dns_process(void);
uint32_t	R_T4_DNS_CLIENT_GetVersion(void);
#if defined(__GNUC__) || defined(GRSAKURA)
#if defined(__cplusplus)
}
#endif
#endif

#endif	/* R_T4_DNS_CLIENT_RX_IF_H	*/
