#pragma once

#include "t4define.h"
#include "type.h"
#include "r_t4_itcpip.h"

#if defined(__cplusplus)
extern "C" {
#endif

void tcpudp_open(UW *workp);
void tcpudp_close(void);

void _getRAMsize_sub(W *ramsize);

#if defined(_TCP)
W _getTcpRAMsize(void);
#endif

#if defined(_UDP)
W _getUdpRAMsize(void);
#endif

W _getIpRAMsize(void);

#if defined(_ETHER)
W _getTblRAMsize(void);
#endif

uint32_t tcpudp_get_ramsize(void);

#if defined(_TCP)
int tcp_acp_cep(ID cepid, ID repid, T_IPVxEP *p_dstaddr, int32_t tmout);
int tcp_con_cep(ID cepid, T_IPVxEP *p_myaddr, T_IPVxEP *p_dstaddr, int32_t tmout);
int tcp_sht_cep(ID cepid);
int tcp_cls_cep(ID cepid, int32_t tmout);
int tcp_send_data(ID cepid, const void *data, int len, int32_t tmout);
int tcp_recv_data(ID cepid, void *data, int len, int32_t tmout);
int tcp_can_cep(ID cepid, FN fncd);
int _tcp_api_req(ID cepid);
void _tcp_api_slp(ID cepid);
void _tcp_clr_req(ID cepid);

#if defined(_TEST_LIBRARY)
int tcp_read_stat(ID cepid);
int tcp_force_clr(ID cepid);
int udp_force_clr(ID cepid);
int tcp_set_mss(ID cepid, UH mss);
#endif
#endif

#if defined(__cplusplus)
}
#endif
