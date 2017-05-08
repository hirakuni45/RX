#pragma once
//=====================================================================//
/*!	@file
	@brief	TCP/UDP config @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "net_config.h"
#include "type.h"
#include "udp.h"
#include "tcp.h"

/***  TCP reception point  ***/
typedef struct t_tcp_crep
{
    uint16_t repatr;    /* TCP reception point attribute    */
    T_IPV4EP myaddr;    /* Local IP address and port number */
} T_TCP_CREP;

/***  TCP communication end point  ***/
typedef struct t_tcp_ccep
{
    uint16_t cepatr;    /* TCP communication end point attribute  */
    void    *sbuf;      /* Top address of transmit window buffer  */
    int      sbufsz;    /* Size of transmit window buffer         */
    void    *rbuf;      /* Top address of receive window buffer   */
    int      rbufsz;    /* Size of receive window buffer          */
    int (*callback)(uint32_t cepid, int32_t fncd , void *p_parblk);   /* Callback routine */
} T_TCP_CCEP;

/***  UDP communication end point  ***/
typedef struct t_udp_ccep
{
    uint16_t cepatr;    /* UDP communication end point attribute  */
    T_IPV4EP myaddr;    /* Local IP address and port number       */
    int (*callback)(uint32_t cepid, int32_t fncd , void *p_parblk); /* Callback routine */
} T_UDP_CCEP;

/***  IP address settings  ***/
typedef struct
{
    uint8_t ipaddr[4];       /* Local IP address        */
    uint8_t maskaddr[4];     /* Subnet mask             */
    uint8_t gwaddr[4];       /* Gateway address X       */
#if defined(__M32R__)
    uint32_t dummy;           /* for alignment           */
#endif
} TCPUDP_ENV;

/*** statistics of T4 ***/
typedef struct T4_STATISTICS
{
    /* t4 status */
    uint32_t t4_rec_cnt;
    uint32_t t4_rec_byte;
    uint32_t t4_snd_cnt;
    uint32_t t4_snd_byte;

    /* report error */
    uint32_t re_len_cnt;
    uint32_t re_network_layer_cnt;
    uint32_t re_transport_layer_cnt;
    uint32_t re_arp_header1_cnt;
    uint32_t re_arp_header2_cnt;
    uint32_t re_ip_header1_cnt;
    uint32_t re_ip_header2_cnt;
    uint32_t re_ip_header3_cnt;
    uint32_t re_ip_header4_cnt;
    uint32_t re_ip_header5_cnt;
    uint32_t re_ip_header6_cnt;
    uint32_t re_ip_header7_cnt;
    uint32_t re_ip_header8_cnt;
    uint32_t re_ip_header9_cnt;
    uint32_t re_tcp_header1_cnt;
    uint32_t re_tcp_header2_cnt;
    uint32_t re_udp_header1_cnt;
    uint32_t re_udp_header2_cnt;
    uint32_t re_udp_header3_cnt;
    uint32_t re_icmp_header1_cnt;
} T4_STATISTICS;

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
    uint8_t *at_commands;               /* Modem setting for data communication    */
    uint8_t *peer_dial;                 /*  Server telephone number                */
} DUP_INFO;
/* PPP connection information */
typedef struct
{
    uint8_t src_ipaddr[4];              /* Local IP address         */
    uint8_t dst_ipaddr[4];              /* Remote IP address        */
} PPP_CLIENT_INFO;


#if defined(__cplusplus)
extern "C" {
#endif
	int t4_udp_callback(uint32_t cepid, int32_t fncd, void *p_parblk);
#if defined(__cplusplus)
}
#endif


#if defined(_TCP)
extern T_TCP_CREP tcp_crep[];
extern const uint32_t tcp_crep_num;

extern T_TCP_CCEP tcp_ccep[];
extern const uint32_t tcp_ccep_num;

extern const uint16_t tcp_mss[];
extern const uint32_t tcp_initial_seqno[];
extern const uint16_t tcp_2msl[];
extern const uint32_t tcp_rt_tmo_rst[];

extern const uint8_t tcp_dack[];

typedef struct {
	uint8_t	mac[6];
} MAC_ADDRESS;

extern MAC_ADDRESS ethernet_mac[];

#endif

#if defined(_UDP)
extern _UDP_CB  *_udp_cb;
extern T_UDP_CCEP udp_ccep[];
extern const uint32_t udp_ccep_num;
#endif

extern const uint8_t multi_TTL[];

extern const uint8_t udp_enable_zerochecksum[];

extern const uint16_t _ip_tblcnt[];

extern TCPUDP_ENV tcpudp_env[];

