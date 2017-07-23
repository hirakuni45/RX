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
* File Name	   : r_t4_dhcp_client_rx_if.h
* Version      : 1.01
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.03.2011 1.00    First Release
*         : 09.05.2014 1.01    Corresponded to FIT Modules
***********************************************************************************************************************/
#ifndef	R_T4_DHCP_CLIENT_RX_IF_H
#define	R_T4_DHCP_CLIENT_RX_IF_H

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Version Number of API. */
#define T4_DHCP_CLIENT_VERSION_MAJOR       (1)
#define T4_DHCP_CLIENT_VERSION_MINOR       (01)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct _dhcp
{
	uint8_t	ipaddr[4];
	uint8_t maskaddr[4];
	uint8_t	gwaddr[4];
	uint8_t	dnsaddr[4];
	uint8_t	dnsaddr2[4];
#if defined(__GNUC__) || defined(GRSAKURA)
    uint32_t dhcpRenewalTimeValue;
    uint32_t dhcpRebindingTimeValue;
    uint32_t dhcpIPAddressLeaseTime;
#endif
	char	domain[20];
	uint8_t	macaddr[6];
}DHCP;

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
#if defined(__GNUC__) || defined(GRSAKURA)
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
int32_t  r_dhcp_open(DHCP *dhcp, uint8_t *work, const uint8_t *mac_addr);
uint32_t R_T4_DHCP_CLIENT_GetVersion(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

#endif	/* R_T4_DHCP_CLIENT_RX_IF_H */
