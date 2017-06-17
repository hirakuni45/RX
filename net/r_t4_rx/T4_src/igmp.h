/**
 * IGMP
 *
 * IGMPv1 and v2
 *
 * @file
 * source ver 1.00 2015/11/12 thu
 */
#ifndef __IGMP_H__
#define __IGMP_H__

#include "t4define.h"


#include "r_t4_itcpip.h"
#include "type.h"
#include "ether.h"
#include "ip.h"

/* user publication function */
extern UW igmp_join_group(UW* mCastAdr, UW RJ45port);
extern UW igmp_leave_group(UW* mCastAdr, UW RJ45port);

/* 10ms int. */
extern void int_send_igmp_when_router_query_receive(uint8_t RJ45port,_P_RCV_BUF *rxIPlayDatPt);
extern void int_send_igmp_when_membership_report_receive(uint8_t RJ45port, _P_RCV_BUF *rxIPlayDatPt);
extern void int_send_igmp_timer_expired(UH now_time_count);

#define	INITIAL_IGMP_VER	ENM_IGMPV2_TYPE

#if defined(__RX)
#if defined(__GNUC__)
#else
#pragma pack	/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
#endif
#endif
/*
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|Version| Type  |    Unused     |           Checksum            |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                         Group Address                         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
typedef struct _IGMP_HEADER{
    uint8_t     vertype;
	union{
		uint8_t		maxRespTime;
	    uint8_t     unused;
	}time;
	uint16_t	igmpcksum;
	IPaddr		group;
#if defined(__GNUC__)
} __attribute__ ((packed)) IGMP_HEADER ;
#else
}IGMP_HEADER ;
#endif

typedef struct{
	_ETH_HDR		etherLay;
	_IP_HDR			ipv4Lay;
	IGMP_HEADER		igmpLay;
#if defined(__GNUC__)
} __attribute__ ((packed)) IGMP_PACKET;
#else
}IGMP_PACKET;
#endif

typedef struct{
	_IP_HDR			iphdr;
	uint32_t		option;
#if defined(__GNUC__)
} __attribute__ ((packed)) _IP_HDR_EX;
#else
}_IP_HDR_EX;
#endif

typedef struct{
	_ETH_HDR		etherLay;
	_IP_HDR_EX		ipv4Lay;
	IGMP_HEADER		igmpLay;
#if defined(__GNUC__)
} __attribute__ ((packed)) IGMP_PACKET_EX;
#else
}IGMP_PACKET_EX;
#endif
	
#if defined(__RX)
#if defined(__GNUC__)
#else
#pragma unpack	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#endif
#endif


enum igmpVersionType{
	ENM_IGMP_QUERY		= 0x11,
	ENM_IGMP_REPORT_V1,	/*0x12*/
	ENM_IGMP_REPORT_V2	= 0x16,
	ENM_IGMP_LEAVE_GROUP,/*0x17*/
};

enum igmpType{
	ENM_IGMPV1_TYPE	=1,
	ENM_IGMPV2_TYPE,
};

#define	MULTI_CAST_MAX_GROUP_COUNT	5

enum IGMP_GROUP_STATE{	/* IGMP three state */
	ENM_NON_MEMBER = 0,
	ENM_DELAYING_MEMBER,
	ENM_IDLE_MEMBER
};

typedef struct{
	UB 			mCastAdr[IP_ALEN];
	UH			repDelayTimer;
	UB			state;
	UW			RJ45port;
	UB			igmpMode;
	UB			igmpModeReq;
	UB			finalAnswer;
	UB			leaveFlag;
}IGMP_GROUP_ARRAY;


#endif
