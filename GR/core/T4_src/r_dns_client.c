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
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_dns_client.c
* Version      : 1.0
* Device(s)	   : any
* Tool-Chain   : any
* OS		   : any
* H/W Platform : any
* Description  : This is the dns client code.
* Operation	   :
* Limitations  :
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*               : 04.04.2011 1.00    First Release
*               : 27.05.2014 1.01    Corresponded to Non-blocking call.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#if defined(__GNUC__) || defined(GRSAKURA)
#include "t4define.h"
#endif
#include <string.h>
#include <stdint.h>
#include "r_t4_itcpip.h"
#include "../r_config/r_t4_dns_client_rx_config.h"
#include "r_t4_dns_client_rx_if.h"
#include "r_dns_client.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
uint8_t dnsaddr1[] = {DNS_IP_ADDR_1};
uint8_t dnsaddr2[] = {DNS_IP_ADDR_2};

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
static uint8_t dns_buffer[512];
static DNS_PACKET dns_packet;
static uint16_t TRANSACTION_ID = 0;

static const uint8_t *dnsaddr_tbl[DNS_SELECT_NUM] =
{
	(const uint8_t *)&dnsaddr1,
	(const uint8_t *)&dnsaddr2
};

NAME_TABLE	name_table;
DNS_MNG		dns_mng;

#if defined(__GNUC__) || defined(GRSAKURA)
static int32_t send_dns_request(char *mame, uint32_t dstaddr);
static int32_t receive_dns_response(NAME_TABLE *table);
static int32_t convert_name_to_dns_query(char *query, char *name);
static int32_t check_query(char *query);
static int32_t check_answer(char *answer, char *dns_response, NAME_TABLE *table, uint8_t *query_type);
static int32_t get_name_till_stringend(const char *string, const char *dns_response, NAME_TABLE *table);
static void clear_table(NAME_TABLE *table);

static uint32_t convert_array_to_long(uint8_t *ipaddr);
static uint16_t htons(uint16_t data);
#endif

static int32_t dns_dummy_proc(void);
static int32_t dns_no_proc(void);
static int32_t dns_proc_A1(void);
static int32_t dns_proc_B2(void);
static int32_t dns_proc_C2(void);
static int32_t dns_proc_D2(void);
static int32_t dns_proc_D3(void);
static int32_t dns_proc_D6(void);
static int32_t dns_proc_E2(void);
static int32_t dns_proc_E4(void);
static int32_t dns_proc_F2(void);
static int32_t dns_proc_G2(void);
static int32_t dns_proc_H2(void);
static int32_t dns_proc_H5(void);
static int32_t dns_proc_I2(void);

static const DNS_PROC_FUNC dns_proc_table[DNS_PROC_NUM][DNS_EVENT_NUM] =
{
	/* A.unreceived request 			*/
	{
		dns_proc_A1,							/* 1.received request				*/
		dns_no_proc,							/* 2.periodic 						*/
		dns_dummy_proc,							/* 3.complete sending callback		*/
		dns_no_proc,							/* 4.complete receiving callback	*/
		dns_dummy_proc,							/* 5.complete canceling callback	*/
		dns_dummy_proc							/* 6.send ARP timeout callback		*/
	},
	/* B.initial						*/
	{
		dns_dummy_proc,							/* 1.received request				*/
		dns_proc_B2,							/* 2.periodic 						*/
		dns_dummy_proc,							/* 3.complete sending callback		*/
		dns_no_proc,							/* 4.complete receiving callback	*/
		dns_dummy_proc,							/* 5.complete canceling callback	*/
		dns_dummy_proc							/* 6.send ARP timeout callback		*/
	},
	/* C.start sending				*/
	{
		dns_dummy_proc,							/* 1.received request				*/
		dns_proc_C2,							/* 2.periodic 						*/
		dns_dummy_proc,							/* 3.complete sending callback		*/
		dns_no_proc,							/* 4.complete receiving callback	*/
		dns_dummy_proc,							/* 5.complete canceling callback	*/
		dns_dummy_proc							/* 6.send ARP timeout callback		*/
	},
	/* D.wait to complete sending request	*/
	{
		dns_dummy_proc,							/* 1.received request				*/
		dns_proc_D2,							/* 2.periodic 						*/
		dns_proc_D3,							/* 3.complete sending callback		*/
		dns_no_proc,							/* 4.complete receiving callback	*/
		dns_dummy_proc,							/* 5.complete canceling callback	*/
		dns_proc_D6								/* 6.send ARP timeout callback		*/
	},
	/* E.wait to complete receiveing request*/
	{
		dns_dummy_proc,							/* 1.received request				*/
		dns_proc_E2,							/* 2.periodic 						*/
		dns_dummy_proc,							/* 3.complete sending callback		*/
		dns_proc_E4,							/* 4.complete receiving callback	*/
		dns_dummy_proc,							/* 5.complete canceling callback	*/
		dns_dummy_proc							/* 6.send ARP timeout callback		*/
	},
	/* F.finish							*/
	{
		dns_dummy_proc,							/* 1.received request				*/
		dns_proc_F2,							/* 2.periodic 						*/
		dns_dummy_proc,							/* 3.complete sending callback		*/
		dns_no_proc,							/* 4.complete receiving callback	*/
		dns_dummy_proc,							/* 5.complete canceling callback	*/
		dns_dummy_proc							/* 6.send ARP timeout callback		*/
	},
	/* G.cancelling						*/
	{
		dns_dummy_proc,							/* 1.received request				*/
		dns_proc_G2,							/* 2.periodic 						*/
		dns_dummy_proc,							/* 3.complete sending callback		*/
		dns_no_proc,							/* 4.complete receiving callback	*/
		dns_dummy_proc,							/* 5.complete canceling callback	*/
		dns_dummy_proc							/* 6.send ARP timeout callback		*/
	},
	/* H.wait to complete cancelling	*/
	{
		dns_dummy_proc,							/* 1.received request				*/
		dns_proc_H2,							/* 2.periodic 						*/
		dns_dummy_proc,							/* 3.complete sending callback		*/
		dns_no_proc,							/* 4.complete receiving callback	*/
		dns_proc_H5,							/* 5.complete canceling callback	*/
		dns_dummy_proc							/* 6.send ARP timeout callback		*/
	},
	/* I.cancelled						*/
	{
		dns_dummy_proc,							/* 1.received request				*/
		dns_proc_I2,							/* 2.periodic 						*/
		dns_dummy_proc,							/* 3.complete sending callback		*/
		dns_no_proc,							/* 4.complete receiving callback	*/
		dns_dummy_proc,							/* 5.complete canceling callback	*/
		dns_dummy_proc							/* 6.send ARP timeout callback		*/
	}
};

static int32_t dns_dummy_proc(void)
{
	while (1);	/* System Error!! */

	return E_SYS;
}

static int32_t dns_no_proc(void)
{
	/* None */

	return E_OK;
}

static int32_t dns_proc_A1(void)
{
	dns_mng.proc = DNS_PROC_INIT;				/* proc <- B.initial	*/

	return	E_OK;
}

static int32_t dns_proc_B2(void)
{
	dns_mng.proc = DNS_PROC_START_SENDING;	/* proc <- C.start sending	*/

	return	E_OK;
}

static int32_t dns_proc_C2(void)
{
	int32_t		ercd;
	uint32_t	dstaddr;

	ercd = E_OK;
	dstaddr = convert_array_to_long((uint8_t *)dnsaddr_tbl[dns_mng.dns_select]);

	reset_timer();
	ercd = send_dns_request(dns_mng.name, dstaddr);

	if (E_WBLK == ercd)
	{
		dns_mng.proc = DNS_PROC_SENDING_REQUEST_WAIT;	/* proc <- D.wait to complete sending request */
	}
	else	/* if (E_WBLK == ercd) */
	{
		dns_mng.proc = DNS_PROC_CANCELLED;		/* proc <- I.cancelled */
		dns_mng.retry_cnt = 0;					/* no retry	*/
	}

	return	ercd;
}

static int32_t dns_proc_D2(void)
{
	int32_t		ercd;
	uint16_t	timer;

	ercd = E_OK;
	timer = get_timer();

	if (DNS_TIMEOUT < timer)
	{
		dns_mng.proc = DNS_PROC_CANCELLING;		/* proc <- G.cancelling */
		ercd = E_DNS_INTERNAL;
	}
	return	ercd;
}

static int32_t dns_proc_D3(void)
{
	reset_timer();
	dns_mng.proc = DNS_PROC_RECEIVEING_REQUEST_WAIT;	/* proc <- E.wait to complete receiveing request */

	return	E_OK;
}

static int32_t dns_proc_D6(void)
{
	dns_mng.proc = DNS_PROC_CANCELLED;		/* proc <- I.cancelled */
	dns_mng.retry_cnt = 0;					/* no retry	*/

	return	E_DNS_INTERNAL;
}

static int32_t dns_proc_E2(void)
{
	int32_t		ercd;
	uint16_t	timer;

	ercd = E_OK;
	timer = get_timer();

	if (DNS_TIMEOUT < timer)
	{
		dns_mng.proc = DNS_PROC_CANCELLED;		/* proc <- I.cancelled */
		ercd = E_DNS_INTERNAL;
	}
	return	ercd;
}

static int32_t dns_proc_E4(void)
{
	int32_t	ercd;

	clear_table(&name_table);
	ercd = receive_dns_response(&name_table);

	if (0 <= ercd)
	{
		dns_mng.proc = DNS_PROC_FINISH;			/* proc <- F.finish */
		ercd = E_OK;
	}
	else	/* if (0 <= ercd) */
	{
		dns_mng.proc = DNS_PROC_CANCELLED;		/* proc <- I.cancelled */
		dns_mng.retry_cnt = 0;					/* no retry	*/
		ercd = E_DNS_INTERNAL;
	}

	return	ercd;
}

static int32_t dns_proc_F2(void)
{
	int32_t	ercd;

	ercd = E_OK;

	if (NULL != dns_mng.cb_func)
	{
		dns_mng.cb_func(ercd, &name_table);
	}

	dns_mng.proc = DNS_PROC_UNRECEIVED_REQUEST;		/* proc <- A.unreceived request */

	return	ercd;
}

static int32_t dns_proc_G2(void)
{
	int32_t	ercd;

	ercd = E_OK;
	reset_timer();

	ercd = udp_can_cep(dns_mng.cepid, TFN_UDP_ALL);

	if (E_OK == ercd)
	{
		dns_mng.proc = DNS_PROC_CANCELLING_WAIT;	/* proc <- H.wait to complete cancelling */
	}
	else	/* H.wait to complete cancelling */
	{
		dns_mng.proc = DNS_PROC_UNRECEIVED_REQUEST;		/* proc <- A.unreceived request */

		if (NULL != dns_mng.cb_func)
		{
			dns_mng.cb_func(ercd, NULL);
		}
	}
	return	ercd;
}

static int32_t dns_proc_H2(void)
{
	int32_t		ercd;
	uint16_t	timer;

	ercd = E_OK;
	timer = get_timer();

	if (DNS_TIMEOUT < timer)
	{
		dns_mng.proc = DNS_PROC_CANCELLED;		/* proc <- I.cancelled */
		dns_mng.retry_cnt = 0;					/* no retry	*/
		ercd = E_DNS_INTERNAL;
	}
	return	ercd;
}

static int32_t dns_proc_H5(void)
{
	dns_mng.proc = DNS_PROC_CANCELLED;		/* proc <- I.cancelled */

	return	E_OK;
}

static int32_t dns_proc_I2(void)
{
	int32_t	ercd;

	ercd = E_OK;

	if (dns_mng.retry_cnt > 0)
	{
		dns_mng.retry_cnt--;
		dns_mng.proc = DNS_PROC_START_SENDING;	/* proc <- C.start sending */
	}
	else	/* if (dns_mng.retry_cnt > 0) */
	{
		if (DNS_SELECT_PRIMARY == dns_mng.dns_select)
		{
			dns_mng.dns_select = DNS_SELECT_SECONDARY;
			dns_mng.retry_cnt = DNS_ERROR_COUNT;
			dns_mng.proc = DNS_PROC_START_SENDING;	/* proc <- C.start sending */
		}
		else	/* if (DNS_SELECT_PRIMARY == dns_mng.dns_select) */
		{
			ercd = E_DNS_TIMEOUT;
			dns_mng.proc = DNS_PROC_UNRECEIVED_REQUEST;		/* proc <- A.unreceived request */

			if (NULL != dns_mng.cb_func)
			{
				dns_mng.cb_func(ercd, NULL);
			}
		}
	}
	return	ercd;
}

/***********************************************************************************************************************
* Function Name: R_dns_init
* Description  : Initialize DNS management variables
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void R_dns_init(void)
{
	dns_mng.proc = DNS_PROC_UNRECEIVED_REQUEST;			/* proc <- A.unreceived request		*/
	dns_mng.dns_select = DNS_SELECT_PRIMARY;			/* selected dns server <- primary	*/
	dns_mng.cb_func = NULL;								/* callback function <- NULL		*/
	memset(&dns_mng.name[0], 0, sizeof(dns_mng.name));	/* domain name <- all '\0'			*/
	dns_mng.retry_cnt = DNS_ERROR_COUNT;				/* Initialize retry counter			*/
	dns_mng.cepid = 0;									/* invalid ID						*/
}

/***********************************************************************************************************************
* Function Name: R_dns_resolve_name
* Description  : Setting the domain name you want to resolve
* Arguments    : name -
*                    address of domain name
*                func -
*                    callback function
* Return Value : error code
***********************************************************************************************************************/
int32_t R_dns_resolve_name(char *name, DNS_CB_FUNC func)
{
	int32_t ercd;

	ercd = E_OK;

	if (DNS_PROC_UNRECEIVED_REQUEST == dns_mng.proc)
	{
		R_dns_init();

		dns_mng.cepid = DNS_UDP_CEP_ID;
		strncpy(&dns_mng.name[0], name, sizeof(dns_mng.name));
		dns_mng.cb_func = func;

		if (dns_mng.proc < DNS_PROC_NUM)
		{
			ercd = dns_proc_table[dns_mng.proc][DNS_EVENT_RECEIVED_REQUEST]();
		}
		else	/* if (dns_mng.proc < DNS_PROC_NUM) */
		{
			while (1);	/* System Error!! */
		}
	}
	else	/* if (DNS_PROC_UNRECEIVED_REQUEST == dns_mng.proc) */
	{
		ercd = E_DNS_PROCESSING;
	}
	return ercd;
}

/***********************************************************************************************************************
* Function Name: R_dns_process
* Description  : DNS client main process.
*                This function must be called periodic.
* Arguments    : none
* Return Value : error code
***********************************************************************************************************************/
int32_t R_dns_process(void)
{
	int32_t ercd;

	ercd = E_OK;

	if (dns_mng.proc < DNS_PROC_NUM)
	{
		ercd = dns_proc_table[dns_mng.proc][DNS_EVENT_PERIODIC]();
	}
	else	/* if (dns_mng.proc < DNS_PROC_NUM) */
	{
		while (1);	/* System Error!! */
	}

	return ercd;
}

/***********************************************************************************************************************
* Function Name: dns_callback
* Description  : DNS callback function
* Arguments    : cepid -
*                    the communication endpoint ID
*                fncd -
*                    function code
*                p_parblk -
*                    error code pointer
* Return Value : error code
***********************************************************************************************************************/
ER dns_callback(ID cepid, FN fncd , VP p_parblk)
{
	ER	parblk;
	ER	ercd;

	parblk = *(ER *)p_parblk;
	ercd   = E_OK;

	/* cepid is 1 fixed */
	if (dns_mng.cepid != cepid)
	{
		while (1);	/* System Error!! */
	}

	if (DNS_PROC_NUM < dns_mng.proc)
	{
		while (1);	/* System Error!! */
	}

	switch (fncd)
	{
		case TFN_UDP_SND_DAT:
			if (0 < parblk)				/* completed sending */
			{
				ercd = dns_proc_table[dns_mng.proc][DNS_EVENT_CALLBACK_SEND]();
			}
			else if (E_CLS == parblk)	/* send ARP timeout */
			{
				ercd = dns_proc_table[dns_mng.proc][DNS_EVENT_CALLBACK_SEND_ARP_TIMEOUT]();
			}
			else if (E_RLWAI == parblk)
			{
				ercd = dns_proc_table[dns_mng.proc][DNS_EVENT_CALLBACK_CANCEL]();
			}
			else						/* default */
			{
				/* None */
			}
			break;

		case TEV_UDP_RCV_DAT:
			if (0 < parblk)				/* completed receving */
			{
				ercd = dns_proc_table[dns_mng.proc][DNS_EVENT_CALLBACK_RECEIVE]();
			}
			break;

		default:
			/* None */
			break;
	}
	return ercd;
}

static int32_t send_dns_request(char *name, uint32_t dstaddr)
{
	static T_IPV4EP	dns;
	int32_t ercd;

	dns.ipaddr	=	dstaddr;
	dns.portno	=	53;

	dns_packet.header.ID			=	htons(TRANSACTION_ID);
	dns_packet.header.Flag			=	htons(0x0100);
	dns_packet.header.QDCOUNT		=	htons(1);
	dns_packet.header.ANCOUNT		=	htons(0);
	dns_packet.header.NSCOUNT		=	htons(0);
	dns_packet.header.ARCOUNT		=	htons(0);

	memcpy(dns_buffer, &dns_packet.header, sizeof(dns_packet.header));

	dns_packet.question.QNAME		=	name;
	dns_packet.question.QTYPE		=	htons(0x0001);
	dns_packet.question.QCLASS		=	htons(0x0001);

	convert_name_to_dns_query((char*)&dns_buffer[sizeof(dns_packet.header)], name);

	dns_buffer[sizeof(dns_packet.header)+strlen((char*)name)+1] 	=	0;

#if defined(__BIG)
	dns_buffer[sizeof(dns_packet.header)+strlen((char*)name)+2] 	=	((dns_packet.question.QTYPE & 0xff00) >> 8);
	dns_buffer[sizeof(dns_packet.header)+strlen((char*)name)+3] 	=	(dns_packet.question.QTYPE & 0x00ff);
	dns_buffer[sizeof(dns_packet.header)+strlen((char*)name)+4] 	=	((dns_packet.question.QCLASS & 0xff00) >> 8);
	dns_buffer[sizeof(dns_packet.header)+strlen((char*)name)+5] 	=	(dns_packet.question.QCLASS & 0x00ff);
#else
	dns_buffer[sizeof(dns_packet.header)+strlen((char*)name)+3] 	=	((dns_packet.question.QTYPE & 0xff00) >> 8);
	dns_buffer[sizeof(dns_packet.header)+strlen((char*)name)+2] 	=	(dns_packet.question.QTYPE & 0x00ff);
	dns_buffer[sizeof(dns_packet.header)+strlen((char*)name)+5] 	=	((dns_packet.question.QCLASS & 0xff00) >> 8);
	dns_buffer[sizeof(dns_packet.header)+strlen((char*)name)+4] 	=	(dns_packet.question.QCLASS & 0x00ff);
#endif

	ercd = udp_snd_dat(1, &dns, dns_buffer, sizeof(dns_packet.header) + strlen((char*)name) + 6, TMO_NBLK);

	return ercd;

}


static int32_t receive_dns_response(NAME_TABLE *table)
{

	T_IPV4EP dstaddr;
	int32_t receive_data_len = 0;
	uint16_t answer_offset = 0;
	int32_t query_size = 0;
	uint8_t answer_count = 0;
	uint8_t answer_check_count = 0;
	uint16_t answer_size = 0;
	uint8_t query_type = 0;

	receive_data_len = udp_rcv_dat(1, &dstaddr, dns_buffer, 512 , TMO_POL);

	if (receive_data_len < 0)
	{
		return -1;
	}

	memcpy(&dns_packet.header, dns_buffer, sizeof(dns_packet.header));

	answer_count = answer_check_count = htons(dns_packet.header.ANCOUNT);
	if (answer_count > DNS_BUFFER_COUNT)
	{
		answer_count = answer_check_count = DNS_BUFFER_COUNT;
	}
	else if (answer_count == 0)
	{
		return -1;
	}
	else
	{

	}

	if (dns_packet.header.ID != htons(TRANSACTION_ID++))
	{
		return -1;
	}

	if (!(dns_packet.header.Flag & htons(0x8000))) 	// Response Bit(1) : Message is a response
	{
		return -1;
	}

	if (dns_packet.header.Flag & htons(0x7800)) 		// Op Code(0000) : Standard query
	{
		return -1;
	}

	if (dns_packet.header.Flag & htons(0x000f)) 		// Reply Code(0000) : No error
	{
		return -1;
	}

	query_size = check_query((char*) & dns_buffer[sizeof(dns_packet.header)]);
	if (query_size < 0)
	{
		return -1;
	}
	answer_offset = query_size + sizeof(dns_packet.header);

	while (answer_check_count)
	{
		answer_size = check_answer((char*) & dns_buffer[answer_offset], (char*)dns_buffer, table, &query_type);
		answer_offset += answer_size;
		if (query_type == QUERY_TYPE_A)
		{
			answer_check_count--;
		}
	}

	return 0;
}

uint32_t convert_array_to_long(uint8_t *ipaddr)
{
	uint32_t tmp = 0;

	tmp = ((((uint32_t)ipaddr[0]) << 24) & 0xFF000000);
	tmp |= ((((uint32_t)ipaddr[1]) << 16) & 0x00FF0000);
	tmp |= ((((uint32_t)ipaddr[2]) << 8)  & 0x0000FF00);
	tmp |= (((uint32_t)ipaddr[3])      & 0x000000FF);

	return tmp;
}

static int32_t convert_name_to_dns_query(char *query, char *name)
{
	uint8_t count = 0;
	uint8_t loop_counter = 0;
	uint8_t label_cnt = 0;
	uint8_t name_len = strlen((char*)name);

	memcpy(query + 1, name, strlen((char*)name));

	while (loop_counter < name_len)
	{
		if (*name++ == '.')
		{
			*query = label_cnt;
			query += label_cnt + 1;
			label_cnt = 0;
		}
		else
		{
			label_cnt++;
		}
		loop_counter++;
	}

	*query	= label_cnt;

	return count;
}

static int32_t check_query(char *query)
{
	char	*check = query;

	while (*query != 0x00)
	{
		query += *query + 1;
		if ((query - check) > 0xff)
		{
			return -1;
		}
	}
	return ((query + 5) - check);

}

static int32_t check_answer(char *answer, char *dns_response, NAME_TABLE *table, uint8_t *query_type)
{

	uint16_t	src_offset = 0;
	uint16_t	answer_length = 0;
	uint16_t	query_length = 0;

	if ((*answer & 0xc0) == 0xc0)
	{
		switch (answer[3])
		{

			case QUERY_TYPE_A:
				src_offset	=	(*answer & ~0xc0) << 8;
				src_offset	|=	*(answer + 1);

				query_length = get_name_till_stringend(&dns_response[src_offset], dns_response, table);

				memcpy(table->ipaddr, &answer[12], 4);
				answer_length = 16;
				*query_type = QUERY_TYPE_A;
				break;

			case QUERY_TYPE_CNAME:
				table->name[0] = 0;
				answer_length = answer[11] + 12;
				*query_type = QUERY_TYPE_CNAME;
				break;

			default:
				*query_type = QUERY_TYPE_UNKNOWN;
				break;
		}
	}
	else
	{
		query_length = get_name_till_stringend(answer, dns_response, table);

		switch (answer[query_length + 2])
		{
			case QUERY_TYPE_A:
				memcpy(table->ipaddr, &answer[query_length + 11], 4);
				answer_length = 15 + query_length;
				*query_type = QUERY_TYPE_A;
				break;

			case QUERY_TYPE_CNAME:
				table->name[0] = 0;
				answer_length = answer[query_length + 10] + query_length + 11;
				*query_type = QUERY_TYPE_CNAME;
				break;

			default:
				*query_type = QUERY_TYPE_UNKNOWN;
				break;
		}
	}
	return answer_length;
}

static int32_t get_name_till_stringend(const char *string, const char *dns_response, NAME_TABLE *table)
{
	uint16_t	dst_offset = 0;
	uint16_t	src_offset = 0;
	uint16_t	next_offset = 0;

	while (string[src_offset] != 0x00)
	{
		if (strlen(table->name) > NAME_SIZE)
		{
			return -1;
		}
		if ((string[src_offset] & 0xc0) == 0xc0)
		{
			next_offset	=	(string[src_offset] & ~0xc0) << 8;
			next_offset	|=	(string[src_offset + 1]);
			dst_offset += get_name_till_stringend(&dns_response[next_offset], dns_response, table);

			while ((string[src_offset] & 0xc0) == 0xc0)
			{
				src_offset += 2;
				if (src_offset > NAME_SIZE)
				{
					return -1;
				}
			}
		}

		else
		{
			strncat((char*)table->name, (char*)&string[src_offset+1], string[src_offset]);
			dst_offset += string[src_offset] + 1;
			src_offset += string[src_offset] + 1;
			if (string[src_offset] != 0x00)
			{
				strcat((char*)table->name, ".");
			}
		}
	}
	return src_offset;
}

static void clear_table(NAME_TABLE *table)
{
	memset(table, 0, sizeof(NAME_TABLE));
}

static uint16_t htons(uint16_t data)
{

	uint16_t tmp = 0;
#ifndef __BIG
	tmp		=	(data & 0x00ff) << 8;
	tmp		|=	(data & 0xff00) >> 8;
	data	=	tmp;
#endif
	return data;
}

/*****************************************************************************
* Function Name: R_T4_DNS_CLIENT_GetVersion
* Description  : Returns the version of this module. The version number is
*                encoded such that the top two bytes are the major version
*                number and the bottom two bytes are the minor version number.
* Arguments    : none
* Return Value : version number
******************************************************************************/
#if !defined(__GNUC__) && !defined(GRSAKURA)
#pragma inline(R_T4_DNS_CLIENT_GetVersion)
#endif
uint32_t  R_T4_DNS_CLIENT_GetVersion(void)
{
	uint32_t const version = (T4_DNS_CLIENT_VERSION_MAJOR << 16) | T4_DNS_CLIENT_VERSION_MINOR;

	return version;
}
