#pragma once
//=====================================================================//
/*!	@file
	@brief	TCP/UDP api @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "net_config.h"
#include "type.h"
#include "config_tcpudp.h"

typedef enum {
	TCP_API_STAT_INVALID = -1,
	TCP_API_STAT_CLOSED = 0,
	TCP_API_STAT_LISTEN = 1,
	TCP_API_STAT_ESTABLISHED = 2,
	TCP_API_STAT_FIN_WAIT2 = 3,
	TCP_API_STAT_CLOSE_WAIT = 4,
	TCP_API_STAT_SYN_SENT = 5,
	TCP_API_STAT_SYN_RECEIVED = 6,
	TCP_API_STAT_FIN_WAIT1 = 7,
	TCP_API_STAT_LAST_ACK = 8,
	TCP_API_STAT_CLOSING = 9,
	TCP_API_STAT_TIME_WAIT = 10,
	TCP_API_STAT_OTHER = 11,
} TCP_API_STAT;

#if defined(__cplusplus)
extern "C" {
#endif

void tcpudp_open(uint32_t *workp);
uint32_t tcpudp_get_memory_size(void);
void tcpudp_close(void);

#if defined(_TCP)
int tcp_acp_cep(int cepid, int repid, T_IPVxEP *p_dstaddr, int32_t tmout);
int tcp_con_cep(int cepid, T_IPVxEP *p_myaddr, T_IPVxEP *p_dstaddr, int32_t tmout);
int tcp_sht_cep(int cepid, int32_t tmout);
int tcp_cls_cep(int cepid, int32_t tmout);
int tcp_send_data(int cepid, const void *data, int len, int32_t tmout);
int tcp_recv_data(int cepid, void *data, int len, int32_t tmout);
int tcp_can_cep(int cepid, int32_t fncd);

#if defined(_TEST_LIBRARY)
TCP_API_STAT tcp_read_stat(int cepid);
int tcp_force_clr(int cepid);
int udp_force_clr(int cepid);
int tcp_set_mss(int cepid, uint16_t mss);
void tcp_reset_queue(int cepid);
#endif
#endif

#if defined(__cplusplus)
}
#endif
