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
#include "config_tcpudp.h"

extern ER t4_callback(ID cepid, FN fncd , VP p_parblk);

/****************************************************************************/
/**********************     TCP-related definition     **********************/
/****************************************************************************/
/* Number of LAN port, Number of Serial port */
const uint8_t _t4_channel_num = 1;

/***  Definition of TCP reception point (only port number needs to be set) ***/
T_TCP_CREP tcp_crep[MAX_TCP_CREP] =
{
    /* { attribute of reception point, {local IP address, local port number}} */
    { 0x0000, { 0, 1024 } },
    { 0x0000, { 0, 1025 } },
    { 0x0000, { 0, 1026 } },
    { 0x0000, { 0, 1027 } },
    { 0x0000, { 0, 1028 } },
    { 0x0000, { 0, 1029 } },
    { 0x0000, { 0, 1030 } },
    { 0x0000, { 0, 1031 } },
};

/* Total number of TCP reception points */
const uint16_t __tcprepn = sizeof(tcp_crep) / sizeof(T_TCP_CREP);

/***  Definition of TCP communication end point
      (only receive window size needs to be set) ***/
T_TCP_CCEP tcp_ccep[MAX_TCP_CCEP] =
{
    /* { attribute of TCP communication end point,
         top address of transmit window buffer, size of transmit window buffer,
         top address of receive window buffer, size of receive window buffer,
         address of callback routine }
    */
    { 0, 0, 0, 0, 1460, 0 },
    { 0, 0, 0, 0, 1460, 0 },
    { 0, 0, 0, 0, 1460, 0 },
    { 0, 0, 0, 0, 1460, 0 },
    { 0, 0, 0, 0, 1460, 0 },
    { 0, 0, 0, 0, 1460, 0 },
    { 0, 0, 0, 0, 1460, 0 },
    { 0, 0, 0, 0, 1460, 0 },
};

/* Total number of TCP communication end points */
const uint16_t __tcpcepn = sizeof(tcp_ccep) / sizeof(T_TCP_CCEP);

/***  TCP MSS  ***/
const uint16_t _tcp_mss[2] =
{
    /* MAX:1460 bytes */
    1460,
    1460,
};

/***  Initial value of sequence number (Set the value other than 0)  ***/
uint16_t _tcp_initial_seqno[2] = { 1, 1 };

/***  2MSL wait time (unit:10ms)  ***/
const uint16_t _tcp_2msl[2] =
{
    (1 * 60 * (1000 / 10)),      /* 1 min */
    (1 * 60 * (1000 / 10)),      /* 1 min */
};
/***  Maximum value of retransmission timeout period (unit:10ms)  ***/
const uint16_t _tcp_rt_tmo_rst[2] =
{
    (10 * 60 * (1000 / 10)),     /* 10 min */
    (10 * 60 * (1000 / 10)),     /* 10 min */
};
/***  Transmit for delay ack (ON=1/OFF=0) ***/
uint8_t _tcp_dack[2] = { 1, 1 };


/****************************************************************************/
/**********************     UDP-related definition     **********************/
/****************************************************************************/
/***  Definition of UDP communication end point  ***/
T_UDP_CCEP udp_ccep[MAX_UDP_CCEP] =
{
    /* only setting port number */
    { 0, { 0, 1365 }, 0 },
    { 0, { 0, 1366 }, 0 },
    { 0, { 0, 1367 }, 0 },
    { 0, { 0, 1365 }, 0 },
};
/* Total number of UDP communication end points */
const uint16_t __udpcepn = (sizeof(udp_ccep) / sizeof(T_UDP_CCEP));

/***  TTL for multicast transmission  ***/
const uint8_t __multi_TTL[2] = { 1, 1 };

/*** Behavior of UDP zero checksum ***/
const uint8_t _udp_enable_zerochecksum[2] = { 0, 0 };           /* 0 = disable, other = enable */

/****************************************************************************/
/**********************     IP-related definition     ***********************/
/****************************************************************************/
const uint16_t _ip_tblcnt[2] = { 3, 3 };

#define MY_IP_ADDR0     192,168,0,3            /* Local IP address  */
#define GATEWAY_ADDR0   0,0,0,0                /* Gateway address (invalid if all 0s) */
#define SUBNET_MASK0    255,255,255,0          /* Subnet mask  */

#define MY_IP_ADDR1     192,168,0,10           /* Local IP address  */
#define GATEWAY_ADDR1   0,0,0,0                /* Gateway address (invalid if all 0s) */
#define SUBNET_MASK1    255,255,255,0          /* Subnet mask  */

TCPUDP_ENV tcpudp_env[2] =
{
    { { MY_IP_ADDR0 }, { SUBNET_MASK0 }, { GATEWAY_ADDR0 } },
    { { MY_IP_ADDR1 }, { SUBNET_MASK1 }, { GATEWAY_ADDR1 } },
};


/****************************************************************************/
/**********************     Driver-related definition     *******************/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*    Set of Ethernet-related                                               */
/*--------------------------------------------------------------------------*/
/* Local MAC address (Set all 0s when unspecified) */
#define MY_MAC_ADDR0    0x74,0x90,0x50,0x00,0x79,0x03
#define MY_MAC_ADDR1    0x74,0x90,0x50,0x00,0x79,0x04

uint8_t _myethaddr[2][6] =
{
    { MY_MAC_ADDR0 },
    { MY_MAC_ADDR1 },
};

/*--------------------------------------------------------------------------*/
/*    Set of PPP-related                                                    */
/*--------------------------------------------------------------------------*/
/* Authentication-related setting */
const uint16_t ppp_auth  = AUTH_PAP;               /* PAP,No authentication enabled */
uint8_t user_name[6]    = "abcde";                /* user name */
uint8_t user_passwd[6]  = "abc00";                /* password  */

/* Dial up-related setting */
const uint8_t peer_dial[]      = "0,123";                /* Destination telephone number */
const uint8_t at_commands[]   = "ATW2S0=2&C0&D0&S0M0S10=255X3";    /* Modem initialization command */


/* Copyright 2014, RENESAS ELECTRONICS CORPORATION */

