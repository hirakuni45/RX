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
* Copyright (C) 2015-2016 Renesas Electronics Corporation, All Rights Reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : igmp.h
* Version      : 1.01
* Description  : igmp client function header
* Website      : https://www.renesas.com/mw/t4
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 12.11.2015 1.00    First Release
*         : 30.11.2016 1.01    File Header maintenance
***********************************************************************************************************************/
#ifndef __IGMP_H__
#define __IGMP_H__

/***********************************************************************************************************************
Includes <System Includes> , gProject Includesh
***********************************************************************************************************************/
#include "t4define.h"


#include "r_t4_itcpip.h"
#include "type.h"
#include "ether.h"
#include "ip.h"

/* user publication function */
extern UW igmp_join_group(UW* mCastAdr, UW RJ45port);
extern UW igmp_leave_group(UW* mCastAdr, UW RJ45port);

/* 10ms int. */
extern void int_send_igmp_when_router_query_receive(uint8_t RJ45port, _P_RCV_BUF *rxIPlayDatPt);
extern void int_send_igmp_when_membership_report_receive(uint8_t RJ45port, _P_RCV_BUF *rxIPlayDatPt);
extern void int_send_igmp_timer_expired(UH now_time_count);

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define INITIAL_IGMP_VER ENM_IGMPV2_TYPE

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
#if defined(__RX)
#pragma pack /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
#endif

/*
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|Version| Type  |    Unused     |           Checksum            |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                         Group Address                         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
typedef struct _IGMP_HEADER
{
    uint8_t     vertype;
    union
    {
        uint8_t     maxRespTime;
        uint8_t     unused;
    }time;
    uint16_t igmpcksum;
    IPaddr  group;
#if defined(__GNUC__)
} __attribute__ ((packed)) IGMP_HEADER ;
#else
}IGMP_HEADER ;
#endif

typedef struct
{
    _ETH_HDR  etherLay;
    _IP_HDR   ipv4Lay;
    IGMP_HEADER  igmpLay;
#if defined(__GNUC__)
} __attribute__ ((packed)) IGMP_PACKET;
#else
}IGMP_PACKET;
#endif

typedef struct
{
    _IP_HDR   iphdr;
    uint32_t  option;
#if defined(__GNUC__)
} __attribute__ ((packed)) _IP_HDR_EX;
#else
}_IP_HDR_EX;
#endif

typedef struct
{
    _ETH_HDR  etherLay;
    _IP_HDR_EX  ipv4Lay;
    IGMP_HEADER  igmpLay;
#if defined(__GNUC__)
} __attribute__ ((packed)) IGMP_PACKET_EX;
#else
}IGMP_PACKET_EX;
#endif

#if defined(__RX)
#pragma unpack /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#endif


enum igmpVersionType
{
    ENM_IGMP_QUERY  = 0x11,
    ENM_IGMP_REPORT_V1, /*0x12*/
    ENM_IGMP_REPORT_V2 = 0x16,
    ENM_IGMP_LEAVE_GROUP,/*0x17*/
};

enum igmpType
{
    ENM_IGMPV1_TYPE = 1,
    ENM_IGMPV2_TYPE,
};

#define MULTI_CAST_MAX_GROUP_COUNT 5

enum IGMP_GROUP_STATE  /* IGMP three state */
{
    ENM_NON_MEMBER = 0,
    ENM_DELAYING_MEMBER,
    ENM_IDLE_MEMBER
};

typedef struct
{
    UB    mCastAdr[IP_ALEN];
    UH   repDelayTimer;
    UB   state;
    UW   RJ45port;
    UB   igmpMode;
    UB   igmpModeReq;
    UB   finalAnswer;
    UB   leaveFlag;
}IGMP_GROUP_ARRAY;


#endif
