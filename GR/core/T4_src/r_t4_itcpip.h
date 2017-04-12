/******************************************************************************
* WEBSITE
* Please refer to
*   http://www.renesas.com/mw/t4
*   http://japan.renesas.com/mw/t4
*******************************************************************************
  Copyright (C) 2004-2014. Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_t4_itcpip.h
* Version      : 2.02
* Description  : TCP/IP library T4 Header file
*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 25.08.2009 0.24     First beta Release
*         : 25.09.2009 0.25     Corresponded for RSK standard driver interface
*         : 08.10.2009 0.26     Applied T3-Tiny bug fix
*         : 11.03.2010 0.27     Fixed bug.
*         : 12.03.2010 0.28     Added setting variable "_tcp_dack"
*         : 27.08.2010 0.29     Corrected r_t4_itcpip.h
*         : 27.09.2010 1.00     First release
*         : 10.10.2010 1.01     Fixed bug.
*         : 05.01.2011 1.02     Fixed bug.
*         : 05.01.2011 1.03     Corrected r_t4_itcpip.h
*         : 23.08.2011 1.04     Added "report_error" function, cleanup code
*         : 01.04.2012 1.05     Added "PPP" connect and R8C support.
*         :                     Added SH-4A support.
*         :                     Added V850E2 support.
*         :                     Change user defined function spec
*         :                     api_slp() -> tcp_api_slp(), udp_api_slp(), ppp_api_slp()
*         :                     api_wup() -> tcp_api_wup(), udp_api_wup(), ppp_api_wup()
*         :                     Fixed bug.
*         : 21.06.2013 1.06     Fixed bug: r_t4_itcpip.h.
*         :                     Added UDP broadcast function.
*         :                     Fixed bug: TCP 3way hand-shake behavior with zero-window size SYN.
*         :                     Fixed bug: TCP sending.
*         :                     Fixed bug: ppp re-connect.
*         : 31.03.2014 2.00     Added setting variable "_t4_channel_num" for several link-layer channels.
*         :                     Change user defined function spec.
*         :                     lan_read(), lan_write(), lan_reset(),
*         :                     report_error(), and rcv_buff_release(),
*         :                     Change API define _process_tcpip().
*         :                     Change error code (E_XX) and NADR value.
*         :                     Deleted PPP Libraries temporary. (maybe return at next release)
*         :                     Fixed Bug.
*         : 07.08.2014 2.01     Clean up source code.
*         : 01.29.2015 2.02     Changed RX IDE from High-performance Embedded Workshop to CS+.
*         :                     Changed RX compiler option from (-rx600,-rx200) to (-rxv2,-rxv1).
*-----------------------------------------------------------------------------
* T4 library list :
*                   Ethernet    PPP     Notice
*   RXV2-big        V.2.02      x       PPP is temporarily unavailable
*   RXV2-little     V.2.02      x       PPP is temporarily unavailable
*   RXV1-big        V.2.02      x       PPP is temporarily unavailable
*   RXV1-little     V.2.02      x       PPP is temporarily unavailable
*   V850E2M         V.1.04      -
*   SH-2A           V.1.06      -
*   SH-2A-fpu       V.1.06      -
*   SH-4-big        -           -
*   SH-4-little     V.1.04      -
*   SH-4A-big       x           -       Renesas internal use
*   SH-4A-little    x           -       Renesas internal use
*   H8S/2600-adv    V.1.04      -
*   M16C            V.1.04      -
*   R8C             x           x       Renesas internal use
*   R8C-far         x           x       Renesas internal use
*-----------------------------------------------------------------------------
******************************************************************************/

#ifndef _R_T4_ITCPIP_H
#define _R_T4_ITCPIP_H
/*
 * ITRON data type definition
 */
#if defined(__MR30_H) || defined(__MR308_H) || defined(__MR32R) || defined(__HIOS_ITRON_H) || defined(__ITRON_H)
#define __ITRON_DATA_TYPE
#endif

#if !defined(__ITRON_DATA_TYPE)
#define __ITRON_DATA_TYPE
#if defined(R8C) || defined(M16C) || defined(M16C80) || defined(M32C80) ||\
    defined(__300HA__) || defined(__2600A__) ||\
    defined(_SH2) || defined(_SH2A) || defined(_SH2AFPU) || defined(_SH4) || defined(_SH4A) ||\
    defined(__RX) || defined(__v850) || (defined(__GNUC__) || defined(GRSAKURA))

#if defined(__RX)
#include <stdint.h>
#else
#include "r_stdint.h"
#endif

typedef int8_t          B;
typedef int16_t         H;
typedef int32_t         W;
typedef uint8_t         UB;
typedef uint16_t        UH;
typedef uint32_t        UW;
typedef int8_t          VB;
typedef int16_t         VH;
typedef int32_t         VW;
typedef void    (*FP)(void);
typedef H               ID;
typedef H               PRI;
typedef W               TMO;
typedef H               HNO;
typedef W               ER;
typedef UH              ATR;
#endif
#endif

typedef int32_t         FN;

#include "r_mw_version.h"

/*
 * ITRON TCP/IP API Specifications header file
 */
/*********************************/
/*** Data structure definition ***/
/*********************************/
/*** IP address/Port No. information ***/
typedef struct t_ipv4ep
{
    UW       ipaddr;    /* IP address */
    UH       portno;    /* Port number */
} T_IPV4EP;

/***  TCP reception point  ***/
typedef struct t_tcp_crep
{
    ATR      repatr;    /* TCP reception point attribute    */
    T_IPV4EP myaddr;    /* Local IP address and port number */
} T_TCP_CREP;

/***  TCP communication end point  ***/
typedef struct t_tcp_ccep
{
    ATR      cepatr;    /* TCP communication end point attribute  */
    void    *sbuf;      /* Top address of transmit window buffer  */
    int      sbufsz;    /* Size of transmit window buffer         */
    void    *rbuf;      /* Top address of receive window buffer   */
    int      rbufsz;    /* Size of receive window buffer          */
    ER(*callback)(ID cepid, FN fncd , void *p_parblk);   /* Callback routine */
} T_TCP_CCEP;

/***  UDP communication end point  ***/
typedef struct t_udp_ccep
{
    ATR      cepatr;    /* UDP communication end point attribute  */
    T_IPV4EP myaddr;    /* Local IP address and port number       */
    ER(*callback)(ID cepid, FN fncd , void *p_parblk); /* Callback routine */
} T_UDP_CCEP;

/***  IP address settings  ***/
typedef struct
{
    UB ipaddr[4];       /* Local IP address        */
    UB maskaddr[4];     /* Subnet mask             */
    UB gwaddr[4];       /* Gateway address X       */
#if defined(__M32R__)
    UW dummy;           /* for alignment           */
#endif
} TCPUDP_ENV;

/*** statistics of T4 ***/
typedef struct T4_STATISTICS
{
    /* t4 status */
    UW t4_rec_cnt;
    UW t4_rec_byte;
    UW t4_snd_cnt;
    UW t4_snd_byte;

    /* report error */
    UW re_len_cnt;
    UW re_network_layer_cnt;
    UW re_transport_layer_cnt;
    UW re_arp_header1_cnt;
    UW re_arp_header2_cnt;
    UW re_ip_header1_cnt;
    UW re_ip_header2_cnt;
    UW re_ip_header3_cnt;
    UW re_ip_header4_cnt;
    UW re_ip_header5_cnt;
    UW re_ip_header6_cnt;
    UW re_ip_header7_cnt;
    UW re_ip_header8_cnt;
    UW re_ip_header9_cnt;
    UW re_tcp_header1_cnt;
    UW re_tcp_header2_cnt;
    UW re_udp_header1_cnt;
    UW re_udp_header2_cnt;
    UW re_udp_header3_cnt;
    UW re_icmp_header1_cnt;
}T4_STATISTICS;

/****************************/
/***  API Function Codes  ***/
/****************************/
#define TFN_TCP_CRE_REP -0x0201  /* Create TCP reception point               */
#define TFN_TCP_DEL_REP -0x0202  /* Delete TCP reception point               */
#define TFN_TCP_CRE_CEP -0x0203  /* Create TCP communication end point       */
#define TFN_TCP_DEL_CEP -0x0204  /* Delete TCP communication end point       */
#define TFN_TCP_ACP_CEP -0x0205  /* Wait for TCP connection request          */
#define TFN_TCP_CON_CEP -0x0206  /* TCP connection request(active open)      */
#define TFN_TCP_SHT_CEP -0x0207  /* TCP data transmission end                */
#define TFN_TCP_CLS_CEP -0x0208  /* TCP communication end point close        */
#define TFN_TCP_SND_DAT -0x0209  /* Transmission of TCP data                 */
#define TFN_TCP_RCV_DAT -0x020A  /* Reception of TCP data                    */
#define TFN_TCP_GET_BUF -0x020B  /* TCP Transmission buffer retrieval        */
#define TFN_TCP_SND_BUF -0x020C  /* Transmission of data in TCP buffer       */
#define TFN_TCP_RCV_BUF -0x020D  /* Get TCP reception data in the buffer     */
#define TFN_TCP_REL_BUF -0x020E  /* TCP Reception buffer release             */
#define TFN_TCP_SND_OOB -0x020F  /* Transmission of urgent TCP data          */
#define TFN_TCP_RCV_OOB -0x0210  /* Reception of urgent TCP data             */
#define TFN_TCP_CAN_CEP -0x0211  /* Cancel pending TCP operation             */
#define TFN_TCP_SET_OPT -0x0212  /* Set TCP communication end point option   */
#define TFN_TCP_GET_OPT -0x0213  /* Read TCP communication end point option  */
#define TFN_TCP_ALL     0x0000
#define TFN_UDP_CRE_CEP -0x0221  /* Create UDP communication end point       */
#define TFN_UDP_DEL_CEP -0x0222  /* Delete UDP communication end point       */
#define TFN_UDP_SND_DAT -0x0223  /* Transmission of UDP data                 */
#define TFN_UDP_RCV_DAT -0x0224  /* Reception of UDP data                    */
#define TFN_UDP_CAN_CEP -0x0225  /* Cancel pending UDP operation             */
#define TFN_UDP_SET_OPT -0x0226  /* Set UDP communication end point option   */
#define TFN_UDP_GET_OPT -0x0227  /* Read UDP communication end point option  */
#define TFN_UDP_ALL     0x0000

/************************/
/***  API Event code  ***/
/************************/
#define TEV_TCP_RCV_OOB  0x0201 /* TCP urgent data received      */
#define TEV_UDP_RCV_DAT  0x0221 /* UDP data received             */

/***************************
 *      Error Code         *
 ***************************/
#ifndef E_OK
#define E_OK                  0  /* Normal completion               */
#endif
#ifndef E_SYS
#define E_SYS                -5  /* System error                    */
#endif
#ifndef E_NOSPT
#define E_NOSPT              -9  /* Function not supported          */
#endif
#ifndef E_RSATR
#define E_RSATR             -11  /* Reserved attribute              */
#endif
#ifndef E_PAR
#define E_PAR               -17  /* Parameter error                 */
#endif
#ifndef E_ID
#define E_ID                -18  /* Invalid ID number               */
#endif
#ifndef E_MACV
#define E_MACV              -26  /* Memory access violation         */
#endif
#ifndef E_NOMEM
#define E_NOMEM             -33  /* Insufficient memory             */
#endif
#ifndef E_OBJ
#define E_OBJ               -41  /* Object state error              */
#endif
#ifndef E_NOEXS
#define E_NOEXS             -42  /* Object does not exist           */
#endif
#ifndef E_QOVR
#define E_QOVR              -43  /* Queuing overflow                */
#endif
#ifndef E_RLWAI
#define E_RLWAI             -49  /* Forced release from waiting     */
#endif
#ifndef E_TMOUT
#define E_TMOUT             -50  /* Timeout                         */
#endif
#ifndef E_DLT
#define E_DLT               -51  /* Waiting object deleted          */
#endif
#ifndef E_WBLK
#define E_WBLK              -57  /* Non-blocking call accept        */
#endif
#ifndef E_CLS
#define E_CLS               -52  /* Connection failure              */
#endif
#ifndef E_BOVR
#define E_BOVR              -58  /* Buffer overflow                 */
#endif

/***************/
/***  Other  ***/
/***************/
#ifndef TMO_POL
#define TMO_POL              0  /* Polling                                       */
#endif
#ifndef TMO_FEVR
#define TMO_FEVR            -1  /* Waiting forever                               */
#endif
#ifndef TMO_NBLK
#define TMO_NBLK            -2  /* Non-blocking call (Set timeout value)         */
#endif
#ifndef NADR
#define NADR                 0  /* IP address, port number specification omitted */
#endif
#ifndef IPV4_ADDRANY
#define IPV4_ADDRANY         0  /* IP address specification omitted              */
#endif
#ifndef TCP_PORTANY
#define TCP_PORTANY          0  /* TCP port number specification omitted         */
#endif
#ifndef UDP_PORTANY
#define UDP_PORTANY          0  /* UDP port number specification omitted         */
#endif

/******************************************
 *      Error code (report error)         *
 ******************************************/

#define RE_LEN              -1
#define RE_NETWORK_LAYER    -2
#define RE_TRANSPORT_LAYER  -3
#define RE_ARP_HEADER1      -21
#define RE_ARP_HEADER2      -22
#define RE_IP_HEADER1       -41
#define RE_IP_HEADER2       -42
#define RE_IP_HEADER3       -43
#define RE_IP_HEADER4       -44
#define RE_IP_HEADER5       -45
#define RE_IP_HEADER6       -46
#define RE_IP_HEADER7       -47
#define RE_IP_HEADER8       -48
#define RE_IP_HEADER9       -49
#define RE_TCP_HEADER1      -61
#define RE_TCP_HEADER2      -62
#define RE_UDP_HEADER1      -81
#define RE_UDP_HEADER2      -82
#define RE_UDP_HEADER3      -83
#define RE_ICMP_HEADER1     -101

/*******************************/
/***  Prototype Declaration  ***/
/*******************************/
#if defined(__GNUC__) || defined(GRSAKURA)
#if defined(__cplusplus)
extern "C" {
#endif
#endif
ER udp_snd_dat(ID cepid, T_IPV4EP *p_dstaddr, void *data, int len, TMO tmout);
ER udp_rcv_dat(ID cepid, T_IPV4EP *p_dstaddr, void *data, int len, TMO tmout);
ER udp_can_cep(ID cepid, FN fncd);

ER tcp_acp_cep(ID cepid, ID repid, T_IPV4EP *p_dstadr, TMO tmout);
ER tcp_con_cep(ID cepid, T_IPV4EP *p_myadr,  T_IPV4EP *p_dstadr, TMO tmout);
ER tcp_sht_cep(ID cepid);
ER tcp_cls_cep(ID cepid, TMO tmout);
ER tcp_snd_dat(ID cepid, void *data, int dlen, TMO tmout);
ER tcp_rcv_dat(ID cepid, void *data, int dlen, TMO tmout);
ER tcp_can_cep(ID cepid, FN fncd);

ER tcpudp_open(UW *workp);    /* Open TCP/IP library (initialization)                         */
ER tcpudp_close(void);        /* Close TCP/IP library (stop)                                  */
W  tcpudp_get_ramsize(void);  /* Calculation of size of work area                             */
void _process_tcpip(void);    /* TCP/IP process function called from ether INT and timer INT. */
#if defined(__GNUC__) || defined(GRSAKURA)
#if defined(__cplusplus)
}
#endif
#endif

/* PPP-related APIs */
ER ppp_open(void);            /* Open PPP driver         */
ER ppp_close(void);           /* Close PPP driver        */
UH ppp_status(void);          /* PPP status              */


/**************************/
/***  Driver Interface  ***/
/**************************/
/*++++++++++++++++ PPP/Ether common items +++++++++++++++++*/
void tcp_api_slp(ID);               /* Wait for completion of TCP API               */
void ppp_api_slp(void);             /* Wait for completion of PPP API               */
void ppp_api_wup(void);             /* Cancel the wait state of PPP API completion  */
void get_random_number(UB *, UW);   /* Get random number for CHAP auth              */

/* T4 version information structure*/
extern const mw_version_t R_t4_version;

/*++++++++++++++++ PPP +++++++++++++++++*/
/* PPP authentication system (Set ppp_auth) */
#define AUTH_NON                1 /* No authentication          */
#define AUTH_PAP                2 /* PAP                        */
#define AUTH_CHAP_MD5           4 /* CHAP_MD5                   */

/* Serial data baud rate (sio_open() argument) */
#define BR96                0
#define BR192               1
#define BR288               2
#define BR384               3
#define BR576               4
#define BR1152              5

/* Serial transfer mode (ppp_sio_status) */
#define PPP_SIO_STAT_MODEM  1  /* Modem command transmission and reception mode */
#define PPP_SIO_STAT_PPP    2  /* PPP frame transmission and reception mode  */

/* ppp_status() return value */
#define PS_DEAD             0x0001 /* Initial state                   */
#define PS_ESTABLISH        0x0002 /* LCP phase                       */
#define PS_AUTHENTICATE     0x0004 /* Authentication phase (PAP)      */
#define PS_NETWORK          0x0008 /* NCP phase (IPCP)                */
#define PS_NETOPEN          0x0010 /* Established Network             */
#define PS_TERMINATE        0x0020 /* Disconnecting Link              */
#define PS_RESERVED         0xffc0 /* Reservation                     */

/* ppp_drv_status() return value */
#define PDS_SND             0x0001 /* 1: sending, 0: transmit buffer empty / sending completed */
#define PDS_SND_FULL        0x0002 /* 1: transmit buffer full, 0: transmit buffer empty        */
#define PDS_RCV             0x0010 /* 1: received data present, 0: receive buffer empty        */
#define PDS_RCV_FULL        0x0020 /* 1: receive buffer full, 0: receive buffer empty          */
#define PDS_RESERVED        0xffcc /* Reserved             */

/* ppp_api_req() argument type */
#define PPP_API_SNDCOMMAND  3  /* Request to send AT command              */
#define PPP_API_RCVRZLT     4  /* Request to receive response code        */
#define PPP_API_WAIT        5  /* Request to wait for a specified time    */

/* PPP mode */
#define PPP_MODE_SERVER     0x0001 /* server mode           */
#define PPP_MODE_CLIENT     0x0002 /* client mode           */

/* Dial-up information */
typedef struct
{
    UB *at_commands;               /* Modem setting for data communication    */
    UB *peer_dial;                 /*  Server telephone number                */
} DUP_INFO;
/* PPP connection information */
typedef struct
{
    UB src_ipaddr[4];              /* Local IP address         */
    UB dst_ipaddr[4];              /* Remote IP address        */
} PPP_CLIENT_INFO;

/* PPP driver API (called by user application)  */
void sio_open(UB rate);
void sio_close(void);
ER  modem_active_open(void);
ER  modem_passive_open(void);
ER  modem_close(void);

/* PPP driver interface function (called by library) */
H  ppp_read(UB **ppp);
H  ppp_write(B *hdr, H hlen, B **pdata, H *pdlen, H num);
ER ppp_api_req(UH type, void *parblk, H tmout);
UH ppp_drv_status(void);            /* Get PPP driver state      */
H  modem_read(UB **rzlt);
H  modem_write(void *parblk);


#endif /* _R_T4_ITCPIP_H */


