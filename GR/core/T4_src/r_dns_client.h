#pragma once
//=====================================================================//
/*!	@file
	@brief	r_dns_client.h @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//

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


#if defined(__cplusplus)
extern "C" {
#endif
int dns_callback(ID cepid, int32_t fncd , void *p_parblk);
#if defined(__cplusplus)
}
#endif

#if 0
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
