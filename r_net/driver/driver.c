//=====================================================================//
/*!	@file
	@brief	ドライバー関係 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phy.h"
#include "r_ether.h"
#include "../T4_src/net_config.h"
#include "../T4_src/config_tcpudp.h"

#if defined (_T4_TEST)
extern H lan_read_for_test(uint8_t lan_port_no, int8_t **buf, H return_code);
#endif

extern volatile uint8_t g_request_all_reset_;
extern volatile uint8_t g_inetfbad_;

void enable_interrupt(void);
void disable_interrupt(void);

/******************************************************************************
Private global variables and functions
******************************************************************************/
uint16_t tcpudp_time_cnt;
static volatile uint8_t tcpip_flag_;
volatile uint16_t wait_timer_;
T4_STATISTICS t4_stat;
uint8_t *err_buf_ptr;


/******************************************************************************
Functions (for system that has no ET_LINKSTA pin using)
******************************************************************************/
static void polling_link_status_(void)
{
	static uint16_t timer_1s = 0;
	static int16_t pre_link_stat = R_PHY_ERROR;
	int16_t link_stat;

	if((timer_1s % 100) == 0) {
		link_stat = phy_get_link_status();
		if(pre_link_stat != link_stat) {
			if(link_stat == R_PHY_OK) {
				g_ether_LchngFlag = ETHER_FLAG_ON_LINK_ON;
			} else {
				g_ether_LchngFlag = ETHER_FLAG_ON_LINK_OFF;
			}
		}
		pre_link_stat = link_stat;
	}
	timer_1s++;
}


/******************************************************************************
Functions (Interrput handler)
******************************************************************************/
static void service_10ms_(void)
{
	if (tcpip_flag_ == 1)
	{
		_process_tcpip();
		tcpudp_time_cnt++;
	}

	/* for wait function */
	if (wait_timer_ < 0xffff)
	{
		wait_timer_++;
	}

	/* polling PHY chip to check LINK status @ per 1sec */
	polling_link_status_();
}

extern void set_task_10ms(void (*task)(void));


void open_timer(void)
{
	set_task_10ms(service_10ms_);
}


void close_timer(void)
{
	set_task_10ms(NULL);
} 


/******************************************************************************
Functions (API)
******************************************************************************/
int lan_open(void)
{
	int ret;
	memset(&t4_stat, 0, sizeof(T4_STATISTICS));
	int ch = 0;
	ret = R_ETHER_Open_ZC2(ethernet_mac[ch].mac);
	if (R_ETHER_OK != ret)
	{
		return -1;
	}
	return 0;
}

int lan_close(void)
{
	R_ETHER_Close_ZC2();
	return 0;
}

int lan_restart_flag(void)
{
	return g_request_all_reset_;
}


void lan_restart(void)
{
	g_inetfbad_ = 1;
}

/******************************************************************************
Functions (Use definiton function that called from T4 library)
******************************************************************************/

void ena_int(void)
{
	tcpip_flag_ = 1;
}

void dis_int(void)
{
	tcpip_flag_ = 0;
}


int16_t rcv_buff_release(uint8_t lan_port_no)
{
	/* This function is called when TCP/IP finished using receive buffer specified lan_read. */
	R_ETHER_Read_ZC2_BufRelease();
	return 0;
}

uint16_t tcpudp_get_time(void)
{
	return tcpudp_time_cnt;
}

void tcpudp_act_cyc(uint8_t cycact)
{
	switch (cycact)
	{
		case 0:
			tcpip_flag_ = 0;
			close_timer();
			break;
		case 1:
			tcpip_flag_ = 1;
			open_timer();
			break;
		default:
			break;
	}
}

void lan_reset(uint8_t lan_port_no)
{
	R_ETHER_Close_ZC2();
	int ch = 0;
	R_ETHER_Open_ZC2(ethernet_mac[ch].mac);
}

void udp_api_slp(uint16_t cepid)
{
	/* check LAN link stat */
	R_ETHER_LinkProcess();

	/* If user uses "Real time OS", user may define "sleep task" here. */
}

void udp_api_wup(uint16_t cepid)
{
	/* If user uses "Real time OS", user may define "wake up task" here. */
}

void tcp_api_slp(uint16_t cepid)
{
	/* check LAN link stat */
	R_ETHER_LinkProcess();

	/* If user uses "Real time OS", user may define "sleep task" here. */
}

void tcp_api_wup(uint16_t cepid)
{
	/* If user uses "Real time OS", user may define "wake up task" here. */
}

int16_t	lan_read(uint8_t lan_port_no, int8_t **buf)
{
	int32_t driver_ret;
	int16_t return_code;

	driver_ret = R_ETHER_Read_ZC2((void **)buf);
	if (driver_ret > 0)
	{
		t4_stat.t4_rec_cnt++;
		t4_stat.t4_rec_byte += (uint32_t)driver_ret;
		return_code = (int16_t)driver_ret;
	}
	else if (driver_ret == 0)
	{
		/* R_Ether_Read() returns "0" when receiving data is nothing */
		return_code = -1;	// Return code "-1" notifies "no data" to T4.
	}
	else
	{
		/* R_Ether_Read() returns "negative values" when error occurred */
		return_code = -2;	// Return code "-2" notifies "Ether controller disable" to T4.
//		return_code = -5;	// Return code "-5" notifies "reset request" to T4.
//		return_code = -6;	// Return code "-6" notifies "CRC error" to T4.
	}

#if defined (_T4_TEST)
	return_code = lan_read_for_test(lan_port_no, buf, return_code);
#endif

	return return_code;
}

int16_t lan_write(uint8_t lan_port_no, int8_t *header , int16_t header_len, int8_t *data , int16_t data_len)
{
	int32_t driver_ret;
	int8_t	*buf;
	uint16_t	buf_size;

	driver_ret = R_ETHER_Write_ZC2_GetBuf((void **) &buf, &buf_size);
	if (R_ETHER_OK == driver_ret)
	{
		if (buf_size >= header_len + data_len)
		{
			memcpy(buf, header, header_len);
			memcpy(buf + header_len, data, data_len);

			driver_ret =  R_ETHER_Write_ZC2_SetBuf((uint16_t)(header_len + data_len));
			if (R_ETHER_OK == driver_ret)
			{
				t4_stat.t4_snd_cnt++;
				t4_stat.t4_snd_byte += (header_len + data_len);
				return 0;
			}
		}
	}
	return -5;
}

void report_error(uint8_t lan_port_no, int16_t err_code, uint8_t *err_data)
{
	err_buf_ptr = err_data;

	switch (err_code)
	{
		case RE_LEN:
			t4_stat.re_len_cnt++;
			break;
		case RE_NETWORK_LAYER:
			t4_stat.re_network_layer_cnt++;
			break;
		case RE_TRANSPORT_LAYER:
			t4_stat.re_transport_layer_cnt++;
			break;
		case RE_ARP_HEADER1:
			t4_stat.re_arp_header1_cnt++;
			break;
		case RE_ARP_HEADER2:
			t4_stat.re_arp_header2_cnt++;
			break;
		case RE_IP_HEADER1:
			t4_stat.re_ip_header1_cnt++;
			break;
		case RE_IP_HEADER2:
			t4_stat.re_ip_header2_cnt++;
			break;
		case RE_IP_HEADER3:
			t4_stat.re_ip_header3_cnt++;
			break;
		case RE_IP_HEADER4:
			t4_stat.re_ip_header4_cnt++;
			break;
		case RE_IP_HEADER5:
			t4_stat.re_ip_header5_cnt++;
			break;
		case RE_IP_HEADER6:
			t4_stat.re_ip_header6_cnt++;
			break;
		case RE_IP_HEADER7:
			t4_stat.re_ip_header7_cnt++;
			break;
		case RE_IP_HEADER8:
			t4_stat.re_ip_header8_cnt++;
			break;
		case RE_IP_HEADER9:
			t4_stat.re_ip_header9_cnt++;
			break;
		case RE_TCP_HEADER1:
			t4_stat.re_tcp_header1_cnt++;
			break;
		case RE_TCP_HEADER2:
			t4_stat.re_tcp_header2_cnt++;
			break;
		case RE_UDP_HEADER1:
			t4_stat.re_udp_header1_cnt++;
			break;
		case RE_UDP_HEADER2:
			t4_stat.re_udp_header2_cnt++;
			break;
		case RE_UDP_HEADER3:
			t4_stat.re_udp_header3_cnt++;
			break;
		case RE_ICMP_HEADER1:
			t4_stat.re_icmp_header1_cnt++;
			break;
		default:
			break;
	}
}


void lan_inthdr(void)	// callback from r_ether.c
{
	if (tcpip_flag_ != 0)
	{
//		enable_interrupt();  // 多重割り込み許可
		_process_tcpip();
//		disable_interrupt();
	}
}

/******************************************************************************
Functions (Test function)
******************************************************************************/

void wait_Xms(uint16_t limit_time)
{
	uint16_t max;

	wait_timer_ = 0;
	max = limit_time / 10;

	while (wait_timer_ < max);
}

void reset_timer(void)
{
	wait_timer_ = 0;
}

uint16_t get_timer(void)
{
	return wait_timer_;
}




