//=====================================================================//
/*!	@file
	@brief	ドライバー @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../T4_src/t4define.h"
#include "../T4_src/r_t4_itcpip.h"
#include "rx64m/iodefine.h"
#include "r_ether.h"
#include "phy.h"
// #include "timer.h"

extern UB _myethaddr[6];

#if defined (_T4_TEST)
extern H lan_read_for_test(UB lan_port_no, B **buf, H return_code);
#endif


/******************************************************************************
Private global variables and functions
******************************************************************************/
UH tcpudp_time_cnt;
UB tcpip_flag;
volatile UH wait_timer_;
T4_STATISTICS t4_stat;
UB *err_buf_ptr;


/******************************************************************************
Functions (for system that has no ET_LINKSTA pin using)
******************************************************************************/
static void polling_link_status_(void)
{
	static uint16_t _1s_timer;
	static int16_t pre_link_stat = R_PHY_ERROR;
	int16_t link_stat;

	if (!(_1s_timer++ % 100))
	{
		link_stat = phy_get_link_status();
		if (pre_link_stat != link_stat)
		{
			if (link_stat == R_PHY_OK)
			{
				g_ether_LchngFlag = ETHER_FLAG_ON_LINK_ON;
			}
			else
			{
				g_ether_LchngFlag = ETHER_FLAG_ON_LINK_OFF;
			}
		}
		pre_link_stat = link_stat;
	}
}


/******************************************************************************
Functions (Interrput handler)
******************************************************************************/
///void __attribute__((interrupt)) INT_Excep_CMT1_CMI1(void)
static void service_10ms_(void)
{
	if (tcpip_flag == 1)
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

ER lan_open(void)
{
	ER ret;
	memset(&t4_stat, 0, sizeof(T4_STATISTICS));
	ret = R_ETHER_Open_ZC2(_myethaddr);
	if (R_ETHER_OK != ret)
	{
		return -1;
	}
	return 0;
}

ER lan_close(void)
{
	R_ETHER_Close_ZC2();
	return 0;
}

/******************************************************************************
Functions (Use definiton function that called from T4 library)
******************************************************************************/

void ena_int(void)
{
	tcpip_flag = 1;
}

void dis_int(void)
{
	tcpip_flag = 0;
}


H rcv_buff_release(UB lan_port_no)
{
	/* This function is called when TCP/IP finished using receive buffer specified lan_read. */
	R_ETHER_Read_ZC2_BufRelease();
	return 0;
}

UH tcpudp_get_time(void)
{
	return tcpudp_time_cnt;
}

void tcpudp_act_cyc(UB cycact)
{
	switch (cycact)
	{
		case 0:
			tcpip_flag = 0;
			close_timer();
			break;
		case 1:
			tcpip_flag = 1;
			open_timer();
			break;
		default:
			break;
	}
}

void lan_reset(UB lan_port_no)
{
	R_ETHER_Close_ZC2();
	R_ETHER_Open_ZC2(_myethaddr);
}

void udp_api_slp(ID cepid)
{
	/* check LAN link stat */
	R_ETHER_LinkProcess();

	/* If user uses "Real time OS", user may define "sleep task" here. */
}

void udp_api_wup(ID cepid)
{
	/* If user uses "Real time OS", user may define "wake up task" here. */
}

void tcp_api_slp(ID cepid)
{
	/* check LAN link stat */
	R_ETHER_LinkProcess();

	/* If user uses "Real time OS", user may define "sleep task" here. */
}

void tcp_api_wup(ID cepid)
{
	/* If user uses "Real time OS", user may define "wake up task" here. */
}

H	lan_read(UB lan_port_no, B **buf)
{
	int32_t driver_ret;
	H return_code;

	driver_ret = R_ETHER_Read_ZC2((void **)buf);
	if (driver_ret > 0)
	{
		t4_stat.t4_rec_cnt++;
		t4_stat.t4_rec_byte += (UW)driver_ret;
		return_code = (H)driver_ret;
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

H	lan_write(UB lan_port_no, B *header , H header_len, B *data , H data_len)
{
	int32_t driver_ret;
	B	*buf;
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

void report_error(UB lan_port_no, H err_code, UB *err_data)
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
#if defined(__GNUC__) || defined(GRSAKURA)
///    interrupts();
#else
	setpsw_i();
#endif
	if (tcpip_flag == 1)
	{
		_process_tcpip();
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

UH get_timer(void)
{
	return wait_timer_;
}




