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

	int lan_open(void);
	int lan_close(void);

	void ena_int(void);
	void dis_int(void);
	int16_t rcv_buff_release(uint8_t lan_port_no);
	uint16_t tcpudp_get_time(void);
	void tcpudp_act_cyc(uint8_t cycact);
	void lan_reset(uint8_t lan_port_no);
	void udp_api_slp(uint16_t cepid);
	void udp_api_wup(uint16_t cepid);
	void tcp_api_wup(uint16_t cepid);
	void tcp_api_slp(uint16_t cepid);
	int16_t lan_read(uint8_t lan_port_no, int8_t **buf);
	int16_t lan_write(uint8_t lan_port_no, int8_t *header , int16_t header_len, int8_t *data , int16_t data_len);
	void report_error(uint8_t lan_port_no, int16_t err_code, uint8_t *err_data);
	void lan_inthdr(void);
	void wait_Xms(uint16_t limit_time);
	void reset_timer(void);
	uint16_t get_timer(void);

#if defined(__cplusplus)
};
#endif
