/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/

/*******************************************************************************
* File Name     : config_tcpudp.c
* Version       : 1.00
* Device(s)     : Renesas microcomputer
* Tool-Chain    : Renesas compilers
* OS            :
* H/W Platform  :
* Description   : T4 configuration file
* Limitations   :
******************************************************************************/
/******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 30.08.2011 1.00    First release.
******************************************************************************/
#if defined(__GNUC__) || defined(GRSAKURA)
#include "t4define.h"
#endif

#include "r_t4_itcpip.h"
extern ER t4_udp_callback(ID cepid, FN fncd , VP p_parblk);

/****************************************************************************/
/**********************     TCP-related definition     **********************/
/****************************************************************************/
/* Number of LAN port, Number of Serial port */
const UB _t4_channel_num = 1;

/***  Definition of TCP reception point (only port number needs to be set) ***/
T_TCP_CREP tcp_crep[] = {
	{ 0x0000, { 0, 80 }},
};

/* Total number of TCP reception points */
const H __tcprepn = sizeof(tcp_crep) / sizeof(T_TCP_CREP);

/***  Definition of TCP communication end point
      (only receive window size needs to be set) ***/
T_TCP_CCEP tcp_ccep[] = {
    { 0, 0, 0, 0, 1460, 0 },
};

/* Total number of TCP communication end points */
const H __tcpcepn = sizeof(tcp_ccep) / sizeof(T_TCP_CCEP);

/***  TCP MSS  ***/
const UH _tcp_mss = 1460;    /* MAX:1460 bytes */

/***  Initial value of sequence number (Set the value other than 0)  ***/
UW    _tcp_initial_seqno = 1;

/***  2MSL wait time (unit:10ms)  ***/
#if 0
const UH    _tcp_2msl = (1 * 60 * (1000 / 10));      /* 1 min */
#endif
const UH    _tcp_2msl = 1;      /* 10 ms */

/***  Maximum value of retransmission timeout period (unit:10ms)  ***/
const UH    _tcp_rt_tmo_rst = (10 * 60 * (1000 / 10));     /* 10 min */

/***  Transmit for delay ack (ON=1/OFF=0) ***/
UB    _tcp_dack = 1;


/****************************************************************************/
/**********************     UDP-related definition     **********************/
/****************************************************************************/
/***  Definition of UDP communication end point  ***/

T_UDP_CCEP udp_ccep[] = {
        { 0x0000, { 0, 1365 }, t4_udp_callback },
};

/* Total number of UDP communication end points */
const H __udpcepn = (sizeof(udp_ccep) / sizeof(T_UDP_CCEP));

/***  TTL for multicast transmission  ***/
const UB __multi_TTL = 1;

/*** Behavior of UDP zero checksum ***/
const UB _udp_enable_zerochecksum = 0;           /* 0 = disable, other = enable */

/****************************************************************************/
/**********************     IP-related definition     ***********************/
/****************************************************************************/
const UH _ip_tblcnt = 3;

#define MY_IP_ADDR     192,168,0,3            /* Local IP address  */
#define GATEWAY_ADDR   0,0,0,0                /* Gateway address (invalid if all 0s) */
#define SUBNET_MASK    255,255,255,0          /* Subnet mask  */

TCPUDP_ENV tcpudp_env =
{
    {MY_IP_ADDR},
    {SUBNET_MASK},
    {GATEWAY_ADDR}
};


/****************************************************************************/
/**********************     Driver-related definition     *******************/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*    Set of Ethernet-related                                               */
/*--------------------------------------------------------------------------*/
/* Local MAC address (Set all 0s when unspecified) */
#define MY_MAC_ADDR    0x02,0x00,0x00,0x00,0x00,0x00

UB _myethaddr[6] = {MY_MAC_ADDR};

/*--------------------------------------------------------------------------*/
/*    Set of PPP-related                                                    */
/*--------------------------------------------------------------------------*/
/* Authentication-related setting */
const UH ppp_auth  = AUTH_PAP;               /* PAP,No authentication enabled */
UB user_name[6]    = "abcde";                /* user name */
UB user_passwd[6]  = "abc00";                /* password  */

/* Dial up-related setting */
const UB peer_dial[]      = "0,123";                /* Destination telephone number */
const UB at_commands[]   = "ATW2S0=2&C0&D0&S0M0S10=255X3";    /* Modem initialization command */


/* Copyright 2014, RENESAS ELECTRONICS CORPORATION */

