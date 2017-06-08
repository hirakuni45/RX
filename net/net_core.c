//=====================================================================//
/*! @file
    @brief  net core C/C++ interface @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "r_ether_rx_if.h"
#include "r_t4_itcpip.h"
#include "r_t4_dhcp_client_rx_if.h"
#include "r_t4_driver_rx/src/timer.h"
#include "net_core.h"

#define DEBUG_NET

extern TCPUDP_ENV tcpudp_env[];
extern uint8_t _myethaddr[2][6];
//extern uint8_t dnsaddr1[];
//extern uint8_t dnsaddr2[];
extern volatile uint8_t link_detect[ETHER_CHANNEL_MAX];

extern void timer_interrupt(void*);

extern volatile uint32_t ether_intr_count;

extern volatile uint32_t timer_count;

static UW tcpudp_work[ 21504 / sizeof(UW)];  // calculated by W tcpudp_get_ramsize( void )

static void set_tcpudp_env_(DHCP *dhcp)
{
	if(NULL != dhcp) {
		memcpy(tcpudp_env[0].ipaddr, dhcp->ipaddr, 4);
		memcpy(tcpudp_env[0].maskaddr, dhcp->maskaddr, 4);
		memcpy(tcpudp_env[0].gwaddr, dhcp->gwaddr, 4);

//		memcpy((char *)dnsaddr1, (char *)dhcp->dnsaddr, 4);
//		memcpy((char *)dnsaddr2, (char *)dhcp->dnsaddr2, 4);
	}
}


//-----------------------------------------------------------------//
/*!
	@brief	net 初期化
	@return 「０」以外の場合エラー
 */
//-----------------------------------------------------------------//
int net_init(void)
{
	// start LAN controller
	ER ercd = lan_open();
	if(ercd != E_OK) {
#ifdef DEBUG_NET
		printf("net_init: LAN controller open error\n");
#endif
		return -1;
    }

#ifdef DEBUG_NET
	printf("DHCP client start\n");
#endif
	// DHCP client
	OpenTimer();
//	while(ETHER_FLAG_ON_LINK_ON != link_detect[0] && ETHER_FLAG_ON_LINK_ON != link_detect[1]) {
	volatile uint32_t n = ether_intr_count;
	timer_count = 0;
	uint32_t t = 100;
	int loop = 0;
	while(ETHER_FLAG_ON_LINK_ON != link_detect[0]) {
		R_ETHER_LinkProcess(0);
		// R_ETHER_LinkProcess(1);
		if(n != ether_intr_count) {
			printf("net_init: Ether link loop: %d\n", (int)ether_intr_count);
			n = ether_intr_count;
		}
		if(timer_count >= t) {
			loop++;
			printf("net_init: Ether link wait %d\n", loop);
			t += 100;
		}
	}
#ifdef DEBUG_NET
	printf("net_init 'LINK_ON'\n");
#endif

//	volatile DHCP dhcp;
	DHCP dhcp;
	if(!r_dhcp_open(&dhcp, (unsigned char*)tcpudp_work, &_myethaddr[0][0])) {
		set_tcpudp_env_(&dhcp);
	}
	CloseTimer();

	nop();

	// Get the size of the work area used by the T4 (RAM size).
	W ramsize = tcpudp_get_ramsize();
	if(ramsize > (sizeof(tcpudp_work))) {
		// Then reserve as much memory array for the work area as the size
		// indicated by the returned value.
#ifdef DEBUG_NET
		printf("net_init: memory empty\n");
#endif
		return -2;
	}

	// Initialize the TCP/IP
	ercd = tcpudp_open(tcpudp_work);
	if(ercd != E_OK) {
#ifdef DEBUG_NET
		printf("net_init: Fail tcpudp_open\n");
#endif
		return -3;
	}
	return 0;
}


//-----------------------------------------------------------------//
/*!
	@brief	net サービス
 */
//-----------------------------------------------------------------//
void net_service(void)
{
	// Ethernet driver link up processing
	R_ETHER_LinkProcess(0);
	// R_ETHER_LinkProcess(1);

	// HTTPD wake-up
//	R_httpd();
	// FTP server wake-up
//	R_ftpd();
	// DNS client wake-up
//	R_dns_process();
}


//-----------------------------------------------------------------//
/*!
	@brief	タイマーサービス（割り込み）
 */
//-----------------------------------------------------------------//
void net_timer_service(void)
{
	timer_interrupt(NULL);
}
