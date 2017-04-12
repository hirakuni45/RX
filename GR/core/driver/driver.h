#pragma once
//=====================================================================//
/*!	@file
	@brief	ドライバー関連 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdint.h>

#if defined(__cplusplus)
extern "C"{
#endif
	void open_timer(void);
	void close_timer(void);
	void reset_timer(void);
	uint16_t get_timer(void);

	ER lan_open(void);
	ER lan_close(void);

	void ena_int(void);
	void dis_int(void);
	H rcv_buff_release(UB lan_port_no);
	UH tcpudp_get_time(void);
	void tcpudp_act_cyc(UB cycact);
	void lan_reset(UB lan_port_no);
	void udp_api_slp(ID cepid);
	void udp_api_wup(ID cepid);
	void tcp_api_wup(ID cepid);
	H lan_read(UB lan_port_no, B **buf);
	H lan_write(UB lan_port_no, B *header , H header_len, B *data , H data_len);
	void report_error(UB lan_port_no, H err_code, UB *err_data);
	void lan_inthdr(void);
	void wait_Xms(uint16_t limit_time);
	void reset_timer(void);
	UH get_timer(void);

#if defined(__cplusplus)
};
#endif
