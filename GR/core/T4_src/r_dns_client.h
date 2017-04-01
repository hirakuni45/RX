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
* File Name	   : r_dns_client.h
* Version      : 1.01
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 09.05.2014 1.01    Corresponded to FIT Modules
***********************************************************************************************************************/
#ifndef	R_DNS_CLIENT_H
#define	R_DNS_CLIENT_H

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define QUERY_TYPE_A		0x01
#define QUERY_TYPE_CNAME	0x05
#define QUERY_TYPE_UNKNOWN	0xff

#define DNS_ERROR_COUNT		3
#define DNS_BUFFER_COUNT	1

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct DNS_HEADER_STRUCTURE
{

	uint16_t	ID;
	uint16_t	Flag;
	uint16_t	QDCOUNT;
	uint16_t	ANCOUNT;
	uint16_t	NSCOUNT;
	uint16_t	ARCOUNT;

}DNS_HEADER;

typedef struct DNS_QUESTION_STRUCTURE
{

	char		*QNAME;
	uint16_t	QTYPE;
	uint16_t	QCLASS;

}DNS_QUESTION;

typedef struct DNS_RESOUCE_RECORD_STRUCTURE
{

	char		*NAME;
	uint16_t	TYPE;
	uint16_t	CLASS;
	uint16_t	TTL;
	uint16_t	RDLENGTH;
	char		*RDATA;

}DNS_RESOUCE_RECORD;

typedef struct DNS_REQUEST_PACKET_STRUCTURE
{

	DNS_HEADER			header;
	DNS_QUESTION		question;
	DNS_RESOUCE_RECORD	resouce_record;

}DNS_PACKET;

typedef enum
{
	DNS_PROC_UNRECEIVED_REQUEST,				/* A.unreceived request 				*/
	DNS_PROC_INIT,								/* B.initial							*/
	DNS_PROC_START_SENDING,						/* C.start sending						*/
	DNS_PROC_SENDING_REQUEST_WAIT,				/* D.wait to complete sending request	*/
	DNS_PROC_RECEIVEING_REQUEST_WAIT,			/* E.wait to complete receiveing request*/
	DNS_PROC_FINISH,							/* F.finish								*/
	DNS_PROC_CANCELLING,						/* G.cancelling							*/
	DNS_PROC_CANCELLING_WAIT,					/* H.wait to complete cancelling		*/
	DNS_PROC_CANCELLED,							/* I.cancelled							*/
	DNS_PROC_NUM								/* the number of proccess				*/
} DNS_PROC;

typedef enum
{
	DNS_EVENT_RECEIVED_REQUEST,					/* 1.received request					*/
	DNS_EVENT_PERIODIC,							/* 2.periodic 							*/
	DNS_EVENT_CALLBACK_SEND,					/* 3.complete sending callback			*/
	DNS_EVENT_CALLBACK_RECEIVE,					/* 4.complete receiving callback		*/
	DNS_EVENT_CALLBACK_CANCEL,					/* 5.complete canceling callback		*/
	DNS_EVENT_CALLBACK_SEND_ARP_TIMEOUT,		/* 6.send ARP timeout callback			*/
	DNS_EVENT_NUM								/* the number of event					*/
} DNS_EVENT;

typedef enum
{
	DNS_SELECT_PRIMARY,							/* select primary DNS server			*/
	DNS_SELECT_SECONDARY,						/* select secondary DNS server			*/
	DNS_SELECT_NUM								/* the number of selecting DNS server	*/
} DNS_SELECT;

typedef struct
{
	DNS_PROC 		proc;						/* state of DNS process					*/
	DNS_SELECT		dns_select;					/* selected DNS server					*/
	DNS_CB_FUNC		cb_func;					/* callback function					*/
	char			name[NAME_SIZE];			/* domain name							*/
	uint32_t 		retry_cnt;					/* retry counter						*/
	ID				cepid;						/* the communication endpoint ID		*/
} DNS_MNG;

typedef	int32_t (*DNS_PROC_FUNC)(void);

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
#if !defined(__GNUC__) && !defined(GRSAKURA)
static int32_t send_dns_request(char *mame, uint32_t dstaddr);
static int32_t receive_dns_response(NAME_TABLE *table);
static int32_t convert_name_to_dns_query(char *query, char *name);
static int32_t check_query(char *query);
static int32_t check_answer(char *answer, char *dns_response, NAME_TABLE *table, uint8_t *query_type);
static int32_t get_name_till_stringend(const char *string, const char *dns_response, NAME_TABLE *table);
static void clear_table(NAME_TABLE *table);

static uint32_t convert_array_to_long(uint8_t *ipaddr);
static uint16_t htons(uint16_t data);
static uint32_t htonl(uint32_t data);
#endif
void	 reset_timer(void);
uint16_t get_timer(void);

#endif	/* R_DNS_CLIENT_H */
