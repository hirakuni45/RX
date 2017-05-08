/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Technology Corp. and is only
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Technology Corp. and is protected under
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* TECHNOLOGY CORP. NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
* FOR ANY REASON RELATED TO THE THIS SOFTWARE, EVEN IF RENESAS OR ITS
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this
* software and to discontinue the availability of this software.
* By using this software, you agree to the additional terms and
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************
* Copyright (C) 2011. Renesas Technology Corp., All Rights Reserved.
*******************************************************************************
* File Name    : r_dhcp_client.c
* Version      : 1.00
* Description  : DHCP client sample software
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 15.03.2011 1.00    First Release
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "net_config.h"
#include <string.h>
#include "config_tcpudp.h"
#include "../r_config/r_t4_dhcp_client_rx_config.h"
#include "r_t4_dhcp_client_rx_if.h"
#include "r_dhcp_client.h"
#include "../driver/r_ether.h"
#include "../driver/driver.h"

#if defined(__GNUC__) || defined(GRSAKURA)
static int32_t dhcp_discover(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
static int32_t dhcp_wait_offer(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
static int32_t dhcp_request(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
static int32_t dhcp_wait_ack(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
static uint16_t htons(uint16_t data);
static uint32_t htonl(uint32_t data);
static uint16_t checksum(uint16_t *data, int32_t len);
static uint16_t checksum_udp(uint16_t *pre_header, uint16_t *data, int32_t len);
#endif

/******************************************************************************
* Function Name	: main
* Declaration	: r_dhcp_open
* Description	: dhcp process
* Arguments		: none
* Return value	: none
******************************************************************************/
int32_t r_dhcp_open(DHCP *dhcp, uint8_t *work, const uint8_t *mac_addr)
{

	DHCP_PACKET *dhcp_packet;
	dhcp_packet = (DHCP_PACKET*)work;

	memcpy(dhcp->macaddr, mac_addr, 6);
	memset(work, 0, sizeof(DHCP_PACKET));

	if (dhcp_discover(dhcp, dhcp_packet) != 0)
	{
		return -1;
	}
	if (dhcp_wait_offer(dhcp, dhcp_packet) != 0)
	{
		return -1;
	}
	if (dhcp_request(dhcp, dhcp_packet) != 0)
	{
		return -1;
	}
	if (dhcp_wait_ack(dhcp, dhcp_packet) != 0)
	{
		return -1;
	}

	return 0;

}

int32_t dhcp_discover(DHCP *dhcp, DHCP_PACKET *dhcp_packet)
{

	const char broadcast[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	const char blank_ip[] = {0, 0, 0, 0};
	uint8_t tmp_header[12];

	memset(dhcp_packet, 0, sizeof(DHCP_PACKET));

	memcpy(dhcp_packet->ether.destination_address, broadcast, 6);
	memcpy(dhcp_packet->ether.source_address, dhcp->macaddr, 6);
	dhcp_packet->ether.packet_type = htons(0x0800);

	dhcp_packet->ipv4.version_and_length 			= 0x45;
	dhcp_packet->ipv4.differentiated_services_field = 0x00;
	dhcp_packet->ipv4.total_length					= htons(0x0148);
	dhcp_packet->ipv4.identification				= htons(0x1234);
	dhcp_packet->ipv4.flags_and_fragment_offset		= htons(0x0000);
	dhcp_packet->ipv4.time_to_live					= 0x80;
	dhcp_packet->ipv4.protocol						= 0x11;
	dhcp_packet->ipv4.checksum						= htons(0x0000);
	memcpy(dhcp_packet->ipv4.source_ip, blank_ip, 4);
	memcpy(dhcp_packet->ipv4.destination_ip, broadcast, 4);

	dhcp_packet->udp.source_port					= htons(68);
	dhcp_packet->udp.destination_port				= htons(67);
	dhcp_packet->udp.length							= htons(0x0134);
	dhcp_packet->udp.checksum						= htons(0x0000);

	dhcp_packet->dhcp.opecode						= 0x01;
	dhcp_packet->dhcp.hard_addr						= 0x01;
	dhcp_packet->dhcp.hard_addr_len					= 0x06;
	dhcp_packet->dhcp.hop_count						= 0x00;
	dhcp_packet->dhcp.transaction_id				= htonl(TRANSACTION_ID);
	dhcp_packet->dhcp.second						= htons(0x0000);
	dhcp_packet->dhcp.dummy							= htons(0x0000);
	memcpy(dhcp_packet->dhcp.client_hard_addr, dhcp->macaddr, 6);

	dhcp_packet->dhcp.options.magic_cookie			= htonl(0x63825363);
	dhcp_packet->dhcp.options.message_type1			= htons(0x3501);
	dhcp_packet->dhcp.options.message_type2			= 0x01;
	dhcp_packet->dhcp.options.client_id1			= htons(0x3d07);
	dhcp_packet->dhcp.options.client_id2			= 0x01;
	memcpy(dhcp_packet->dhcp.options.client_mac, dhcp->macaddr, 6);
	dhcp_packet->dhcp.options.dummy[0]				= 0xff;

	dhcp_packet->ipv4.checksum						= checksum((uint16_t *) & dhcp_packet->ipv4, sizeof(dhcp_packet->ipv4));

	memcpy(tmp_header, dhcp_packet->ipv4.source_ip, 4);
	memcpy(tmp_header + 4, dhcp_packet->ipv4.destination_ip, 4);
	tmp_header[8]	=	0x00;
	tmp_header[9]	=	dhcp_packet->ipv4.protocol;
	memcpy(&tmp_header[10], &dhcp_packet->udp.length, 2);

	dhcp_packet->udp.checksum						= checksum_udp((uint16_t *)tmp_header, (uint16_t *) & dhcp_packet->udp,
	                                 sizeof(dhcp_packet->udp) + sizeof(dhcp_packet->dhcp));

	lan_write(ETHER_CHANNEL_0, (int8_t *)&dhcp_packet->ether, sizeof(dhcp_packet->ether), (int8_t *)&dhcp_packet->ipv4, sizeof(DHCP_PACKET) - sizeof(dhcp_packet->ether));

	return 0;

}

int32_t dhcp_wait_offer(DHCP *dhcp, DHCP_PACKET *dhcp_packet)
{

	int16_t	len;
	int8_t	*p;
	volatile uint16_t	timer;

	reset_timer();
	memset(dhcp_packet, 0, sizeof(DHCP_PACKET));

	while (1)
	{
		timer = get_timer();
		if (timer > DHCP_TIMEOUT)
		{
			return -1;
		}
		len	= lan_read(ETHER_CHANNEL_0, (int8_t **) & p);
		if (len > 0)
		{
			memcpy(dhcp_packet, p, sizeof(dhcp_packet->ether) + sizeof(dhcp_packet->ipv4)\
			       + sizeof(dhcp_packet->udp) + sizeof(dhcp_packet->dhcp));
			rcv_buff_release(ETHER_CHANNEL_0);
			if ((dhcp_packet->udp.source_port == htons(0x0043)) && \
			        (dhcp_packet->udp.destination_port == htons(0x0044)) && \
			        (dhcp_packet->dhcp.transaction_id == htonl(TRANSACTION_ID)) && \
			        (dhcp_packet->dhcp.options.message_type1 == htons(0x3501)) && \
			        (dhcp_packet->dhcp.options.message_type2 == 0x02))
				break;
		}
	}
	memcpy(dhcp->ipaddr, dhcp_packet->dhcp.user_ip, 4);
	return 0;
}

int32_t dhcp_request(DHCP *dhcp, DHCP_PACKET *dhcp_packet)
{

	const char broadcast[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	const char blank_ip[] = {0, 0, 0, 0};
	const char request_ip[] = {0x32, 0x04};
	uint8_t tmp_header[12];

	memset(dhcp_packet, 0, sizeof(DHCP_PACKET));

	memcpy(dhcp_packet->ether.destination_address, broadcast, 6);
	memcpy(dhcp_packet->ether.source_address, dhcp->macaddr, 6);
	dhcp_packet->ether.packet_type = htons(0x0800);

	dhcp_packet->ipv4.version_and_length 			= 0x45;
	dhcp_packet->ipv4.differentiated_services_field	= 0x00;
	dhcp_packet->ipv4.total_length					= htons(0x0148);
	dhcp_packet->ipv4.identification				= htons(0x1234);
	dhcp_packet->ipv4.flags_and_fragment_offset		= htons(0x0000);
	dhcp_packet->ipv4.time_to_live					= 0x80;
	dhcp_packet->ipv4.protocol						= 0x11;
	dhcp_packet->ipv4.checksum						= htons(0x0000);
	memcpy(dhcp_packet->ipv4.source_ip, blank_ip, 4);
	memcpy(dhcp_packet->ipv4.destination_ip, broadcast, 4);

	dhcp_packet->udp.source_port					= htons(68);
	dhcp_packet->udp.destination_port				= htons(67);
	dhcp_packet->udp.length							= htons(0x0134);
	dhcp_packet->udp.checksum						= htons(0x0000);

	dhcp_packet->dhcp.opecode						= 0x01;
	dhcp_packet->dhcp.hard_addr						= 0x01;
	dhcp_packet->dhcp.hard_addr_len					= 0x06;
	dhcp_packet->dhcp.hop_count						= 0x00;
	dhcp_packet->dhcp.transaction_id				= htonl(TRANSACTION_ID);
	dhcp_packet->dhcp.second						= htons(0x0000);
	dhcp_packet->dhcp.dummy							= htons(0x0000);
	memcpy(dhcp_packet->dhcp.client_hard_addr, dhcp->macaddr, 6);

	dhcp_packet->dhcp.options.magic_cookie			= htonl(0x63825363);
	dhcp_packet->dhcp.options.message_type1			= htons(0x3501);
	dhcp_packet->dhcp.options.message_type2			= 0x03;
	*(&dhcp_packet->dhcp.options.message_type2 + 1)	= 0x00;
	dhcp_packet->dhcp.options.client_id1			= htons(0x3d07);
	dhcp_packet->dhcp.options.client_id2			= 0x01;
	memcpy(dhcp_packet->dhcp.options.client_mac, dhcp->macaddr, 6);
	memset(dhcp_packet->dhcp.options.dummy, 0, sizeof(dhcp_packet->dhcp.options.dummy));
	memcpy(dhcp_packet->dhcp.options.dummy, request_ip, 2);
	memcpy(&dhcp_packet->dhcp.options.dummy[2], dhcp->ipaddr, 4);
	dhcp_packet->dhcp.options.dummy[6]				= 0xff;

	dhcp_packet->ipv4.checksum						= checksum((uint16_t *) & dhcp_packet->ipv4, sizeof(dhcp_packet->ipv4));

	memcpy(tmp_header, dhcp_packet->ipv4.source_ip, 4);
	memcpy(tmp_header + 4, dhcp_packet->ipv4.destination_ip, 4);
	tmp_header[8]	=	0x00;
	tmp_header[9]	=	dhcp_packet->ipv4.protocol;
	memcpy(&tmp_header[10], &dhcp_packet->udp.length, 2);

	dhcp_packet->udp.checksum						= checksum_udp((uint16_t *)tmp_header, (uint16_t *) & dhcp_packet->udp,
	                                 sizeof(dhcp_packet->udp) + sizeof(dhcp_packet->dhcp));

	lan_write(ETHER_CHANNEL_0, (int8_t *)&dhcp_packet->ether, sizeof(dhcp_packet->ether), (int8_t *)&dhcp_packet->ipv4, sizeof(DHCP_PACKET) - sizeof(dhcp_packet->ether));

	return 0;

}

#define DOMAIN_GET 0x01

int32_t dhcp_wait_ack(DHCP *dhcp, DHCP_PACKET *dhcp_packet)
{

	int16_t	len;
	int8_t	*p;
	uint8_t	*option;
	uint8_t	flag = 0;
	char none[5] = {"none"};

	volatile uint16_t	timer;

	reset_timer();

	while (1)
	{
		timer = get_timer();
		if (timer > DHCP_TIMEOUT)
		{
			return -1;
		}
		len	= lan_read(ETHER_CHANNEL_0, (int8_t **) & p);
		if (len > 0)
		{
			memcpy(dhcp_packet, p, sizeof(dhcp_packet->ether) + sizeof(dhcp_packet->ipv4)\
			       + sizeof(dhcp_packet->udp) + sizeof(dhcp_packet->dhcp));
			rcv_buff_release(ETHER_CHANNEL_0);
			if ((dhcp_packet->udp.source_port == htons(0x0043)) && \
			        (dhcp_packet->udp.destination_port == htons(0x0044)) && \
			        (dhcp_packet->dhcp.transaction_id == htonl(TRANSACTION_ID)) && \
			        (dhcp_packet->dhcp.options.message_type1 == htons(0x3501)) && \
			        (dhcp_packet->dhcp.options.message_type2 == 0x05))
				break;
		}
	}

	option	=	(uint8_t *) & dhcp_packet->dhcp.options.message_type1;

	while (*option != 0xff) 	// End option
	{
		while (*option == 0)	// OPTION No.0 : Padding
		{
			option++;
		}

		switch (*option)
		{
			case 1:				// OPTION No.1 : Subnet Mask
				memcpy(dhcp->maskaddr, option + 2, 4);
				break;
			case 3:				// OPTION No.3 : Router
				memcpy(dhcp->gwaddr, option + 2, 4);
				break;
			case 6:				// OPTION No.6 : Domain Name Server
				// The length must always be a multiple of 4.
				if (*(option + 1) >= 4)
				{
					memcpy(dhcp->dnsaddr, option + 2, 4);
				}
				if (*(option + 1) >= 8)
				{
					memcpy(dhcp->dnsaddr2, option + 6, 4);
				}
				break;
			case 15:			// OPTION No.15 : Domain Name
				memcpy(dhcp->domain, option + 2, *(option + 1));
				dhcp->domain[*(option+1)] = '\0';
				flag |= DOMAIN_GET;
				break;
			case 51:			// OPTION No.51 : IP Address Lease Time :4byte
#if defined(__GNUC__) || defined(GRSAKURA)
			    dhcp->dhcpIPAddressLeaseTime = htonl(*(uint32_t *)(option+2));
#endif
				break;
			case 53:			// OPTION No.53 : DHCP Message Type
				break;
			case 54:			// OPTION No.54 : Server Identiffer
				break;
			case 58:			// OPTION No.58 : Renewal Time Value : 4byte
#if defined(__GNUC__) || defined(GRSAKURA)
                dhcp->dhcpRenewalTimeValue = htonl(*(uint32_t *)(option+2));
#endif
				break;
			case 59:			// OPTION No.59 : Rebinding Time Value : 4byte
#if defined(__GNUC__) || defined(GRSAKURA)
			    dhcp->dhcpRebindingTimeValue = htonl(*(uint32_t *)(option+2));
#endif
				break;
			default:
				break;
		}
		option += *(option + 1) + 2;
	}

	if (!(flag & DOMAIN_GET))
	{
		memcpy(dhcp->domain, none, 5);
	}

	return 0;
}

static uint16_t htons(uint16_t data)
{

#ifndef __BIG
	uint16_t tmp = 0;
	tmp		=	(data & 0x00ff) << 8;
	tmp		|=	(data & 0xff00) >> 8;
	data	=	tmp;
#endif
	return data;
}

static uint32_t htonl(uint32_t data)
{

#ifndef __BIG
	uint32_t tmp = 0;
	tmp		=	(data & 0x000000ff) << 24;
	tmp		|=	(data & 0x0000ff00) << 8;
	tmp		|=	(data & 0x00ff0000) >> 8;
	tmp		|=	(data & 0xff000000) >> 24;
	data	=	tmp;
#endif
	return data;
}

static uint16_t checksum(uint16_t *data, int32_t len)
{
	long sum = 0;

	for (; len > 1; len -= 2)
	{
		sum += *data++;
		if (sum & 0x80000000)
			sum = (sum & 0xffff) + (sum >> 16);
	}

	if (len == 1)
	{
		uint8_t i = 0;
		*(uint8_t*)(&i) = *(uint8_t *)data;
		sum += i;
	}

	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return ~sum;
}


static uint16_t checksum_udp(uint16_t *pre_header, uint16_t *data, int32_t len)
{
	long sum = 0;
	char cnt;

	for (cnt = 0; cnt < 6; cnt++)
	{
		sum += *pre_header++;
		if (sum & 0x80000000)
			sum = (sum & 0xffff) + (sum >> 16);
	}

	for (; len > 1; len -= 2)
	{
		sum += *data++;
		if (sum & 0x80000000)
			sum = (sum & 0xffff) + (sum >> 16);
	}

	if (len == 1)
	{
		uint8_t i = 0;
		*(uint8_t*)(&i) = *(uint8_t *)data;
		sum += i;
	}

	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return ~sum;
}

/*****************************************************************************
* Function Name: R_T4_DHCP_CLIENT_GetVersion
* Description  : Returns the version of this module. The version number is
*                encoded such that the top two bytes are the major version
*                number and the bottom two bytes are the minor version number.
* Arguments    : none
* Return Value : version number
******************************************************************************/
#if !defined(__GNUC__) && !defined(GRSAKURA)
#pragma inline(R_T4_DHCP_CLIENT_GetVersion)
#endif
uint32_t  R_T4_DHCP_CLIENT_GetVersion(void)
{
	uint32_t const version = (T4_DHCP_CLIENT_VERSION_MAJOR << 16) | T4_DHCP_CLIENT_VERSION_MINOR;

	return version;
}


