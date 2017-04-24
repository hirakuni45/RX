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
#include "r_t4_itcpip.h"

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
int tcp_can_cep(int cepid, FN fncd);

#if defined(_TEST_LIBRARY)
int tcp_read_stat(int cepid);
int tcp_force_clr(int cepid);
int udp_force_clr(int cepid);
int tcp_set_mss(int cepid, uint16_t mss);
#endif
#endif

#if defined(__cplusplus)
}
#endif
