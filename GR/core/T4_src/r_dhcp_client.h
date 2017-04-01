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
* File Name	   : r_dhcp_client.h
* Version      : 1.00
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 15.03.2011 1.00    First Release
*         : 09.05.2014 1.01    Corresponded to FIT Modules.
***********************************************************************************************************************/
#ifndef	R_DHCP_CLIENT_H
#define	R_DHCP_CLIENT_H

#if !defined(__GNUC__) && !defined(GRSAKURA)
#pragma pack
#endif

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define EXPANSION_DHCP_PACKET_SIZE 300
#define TRANSACTION_ID	0x12345678

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct _dv_options
{
	uint32_t	magic_cookie;
	uint16_t	message_type1;
	uint8_t		message_type2;
	uint16_t	client_id1;
	uint8_t		client_id2;
	uint8_t		client_mac[6];
	uint8_t		dummy[48 + EXPANSION_DHCP_PACKET_SIZE];
#if defined(__GNUC__) || defined(GRSAKURA)
} __attribute__((__packed__)) DV_OPTIONS;
#else
}DV_OPTIONS;
#endif

typedef struct _dhcp_data
{
	uint8_t		opecode;
	uint8_t		hard_addr;
	uint8_t		hard_addr_len;
	uint8_t		hop_count;
	uint32_t	transaction_id;
	uint16_t	second;
	uint16_t	dummy;
	uint8_t		client_ip[4];
	uint8_t		user_ip[4];
	uint8_t		server_ip[4];
	uint8_t		gateway_ip[4];
	uint8_t		client_hard_addr[16];
	uint8_t		server_host_name[64];
	uint8_t		file_name[128];
	DV_OPTIONS	options;
#if defined(__GNUC__) || defined(GRSAKURA)
} __attribute__((__packed__)) DHCP_DATA;
#else
}DHCP_DATA;
#endif


typedef struct udp_packet
{

	uint16_t	source_port;
	uint16_t	destination_port;
	uint16_t	length;
	uint16_t	checksum;

#if defined(__GNUC__) || defined(GRSAKURA)
} __attribute__((__packed__)) UDP_PACKET;
#else
}UDP_PACKET;
#endif


typedef struct ipv4_packet
{

	uint8_t		version_and_length;
	uint8_t		differentiated_services_field;
	uint16_t	total_length;
	uint16_t	identification;
	uint16_t	flags_and_fragment_offset;
	uint8_t		time_to_live;
	uint8_t		protocol;
	uint16_t	checksum;
	uint8_t		source_ip[4];
	uint8_t		destination_ip[4];

#if defined(__GNUC__) || defined(GRSAKURA)
} __attribute__((__packed__)) IPV4_PACKET;
#else
}IPV4_PACKET;
#endif

typedef struct ether_packet
{

	uint8_t		destination_address[6];
	uint8_t		source_address[6];
	uint16_t	packet_type;

#if defined(__GNUC__) || defined(GRSAKURA)
} __attribute__((__packed__)) ETHER_PACKET;
#else
}ETHER_PACKET;
#endif

typedef struct _dhcp_packet
{
	ETHER_PACKET	ether;
	IPV4_PACKET		ipv4;
	UDP_PACKET		udp;
	DHCP_DATA		dhcp;
#if defined(__GNUC__) || defined(GRSAKURA)
} __attribute__((__packed__)) DHCP_PACKET;
#else
}DHCP_PACKET;
#endif

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
#if !defined(__GNUC__) && !defined(GRSAKURA)
static int32_t dhcp_discover(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
static int32_t dhcp_wait_offer(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
static int32_t dhcp_request(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
static int32_t dhcp_wait_ack(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
static int32_t dchp_release(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
static uint16_t htons(uint16_t data);
static uint32_t htonl(uint32_t data);
static uint16_t checksum(uint16_t *data, int32_t len);
static uint16_t checksum_udp(uint16_t *pre_header, uint16_t *data, int32_t len);
#endif

void	 reset_timer(void);
uint16_t get_timer(void);

#endif	/* R_DHCP_CLIENT_H */
