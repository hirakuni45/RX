//=====================================================================//
/*! @file
    @brief  net_io @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "net/net_tools.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  net_io テンプレート・クラス
		@param[in]	ETHER_IO	インサーネット・ドライバー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHER_IO>
	class net_io {
	public:

		enum class send_type : uint16_t {
///			HWT_ETH  = 0x0001,
			LOOP = 0x0060,  ///< Loopback
			IP   = 0x0800,  ///< Internet Protocol
			ARP  = 0x0806,  ///< ARP
			IPV6 = 0x86DD,  ///< IPv6
		};

	private:

		struct HDR {
			uint8_t		dst[6];  // destination ip address
			uint8_t		src[6];  // source ip address
			uint16_t	type;    // Ethernet packet type
		};

		ETHER_IO&	io_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	io	インサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		net_io(ETHER_IO& io) : io_(io) { }



		//-----------------------------------------------------------------//
		/*!
			@brief  送信
		*/
		//-----------------------------------------------------------------//
		int16_t send(send_type type, const void* data, uint16_t len)
		{
//			sint16  plen, ret, i;
//			uchar  pad[_EP_PAD_MAX]; /* 0 padding data (max size if 18(_EP_PAD_MAX)) */

//			_IP_HDR  *piph;
			static const uint8_t eth_multi_addr[3] = { 0x01, 0x00, 0x5e };
			static const uint8_t eth_broadcast[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
			static const uint8_t ip_broadcast[] = { 0xff, 0xff, 0xff, 0xff };
//			uint32_t addr;
//			uint32_t subnet_mask;
//			uint32_t broad_cast_addr = 0xffffffff;

// peh = &(_tx_hdr.eh);
			HDR hdr;
			// Generate Ethernet header
			memcpy(hdr.src, io_.get_mac(), sizeof(hdr.src));
			hdr.type = tools::htons(static_cast<uint16_t>(type));

			if(type == send_type::IP) {
#if 0
				// If destination IP address is multicast, change the destination
				// MAC address to for multicast
				piph = &_tx_hdr.ihdr.tip.iph;
        /* EX.XX.XX.XX (All Multicast) */
        if ((piph->ip_dst[0] & 0xf0) == 0xE0)
        {
            /* Set the Internet multicast address (01-00-5e-00-00-00)
               and lower 23-bit destination IP address  */
            memcpy(peh->eh_dst, (const void*)eth_multi_addr, sizeof(eth_multi_addr));
            memcpy(peh->eh_dst + sizeof(eth_multi_addr), piph->ip_dst + 1, 3);
            /* clear the bit-24 */
            peh->eh_dst[3] &= 0x7f;
        }
        /* If destination IP address is broadcast, change the destination MAC address to for broadcast */
        /* 255.255.255.255 (broadcast) */
        if (!memcmp(piph->ip_dst, ip_broadcast, 4))
        {
            memcpy(peh->eh_dst, eth_broadcast, EP_ALEN);
        }
        net2hl_yn_xn(&addr, piph->ip_dst);
        net2hl_yn_xn(&subnet_mask, tcpudp_env[_ch_info_tbl->_ch_num].maskaddr);
        /* (directed broadcast) */
        if ((addr & ~subnet_mask) == (broad_cast_addr & ~subnet_mask))
        {
            memcpy(peh->eh_dst, eth_broadcast, EP_ALEN);
        }
#endif
			}

#if 0
			// 0 padding when the pakcet lenght is less than 60 byte
			if((_tx_hdr.hlen + dlen) < _EP_MIN_LEN)
    {
        plen = _EP_MIN_LEN - (_tx_hdr.hlen + dlen);
        /* copy the data to temporarily area for padding */
        memcpy(pad, data, dlen);
        for (i = 0; i < plen; i++)
            pad[dlen+i] = 0;
        /* call the transmit function */
        ret = lan_write(_ch_info_tbl->_ch_num, (B*) & _tx_hdr, (H)_tx_hdr.hlen, (B*)pad, (H)(_EP_MIN_LEN - _tx_hdr.hlen));
    }
    else
        /* call the transmit function */
        ret = lan_write(_ch_info_tbl->_ch_num, (B *) & _tx_hdr, (H)_tx_hdr.hlen, (B*)data, (H)dlen);

    /* 0: transmit complete */
    if (ret == 0)
    {
        return 0;
    }
    else
        return -1;
#endif

			return 0;
		}

	};
}
