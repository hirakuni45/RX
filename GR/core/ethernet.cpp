//=====================================================================//
/*!	@file
	@brief	ethernet class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ethernet.hpp"

namespace net {

	T_IPV4EP ethernet::remoteIPV4EP_;
	char ethernet::UDPrecvBuf_[UDP_RCV_DAT_DATAREAD_MAXIMUM];

	uint8_t ethernet::byteq_buf[RING_SIZ];
	byteq_hdl_t	ethernet::hdl_;
	byteq_hdl_t	ethernet::hdl_forSize_;
	uint8_t ethernet::byteq_buf_forSize_[RING_SIZ_forSize];    /* sizeQueBody 1024 >> 2 = 256 */
}

extern "C" {

	int t4_udp_callback(uint32_t cepid, int32_t fncd , void *p_parblk) {
		return net::ethernet::udp_callback(cepid, fncd , p_parblk);
	}

}
