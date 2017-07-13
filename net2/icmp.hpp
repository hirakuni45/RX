#pragma once
//=========================================================================//
/*! @file
    @brief  ICMP Protocol (ping protocol)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "net2/net_st.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ICMP クラス
		@param[in]	ETHD	イーサーネット・ドライバー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHD>
	class icmp {

		struct icmp_t {
			uint8_t		type;
			uint8_t		code;
			uint16_t	csum;
			uint16_t	process;
			uint16_t	ping_idx;
		};

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		icmp() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  プロセス
					※割り込み外から呼ぶ事は禁止
			@param[in]	eth	イーサーネット・ドライバー
			@param[in]	eh	イーサーネット・ヘッダー
			@param[in]	ih	IPV4 ヘッダー
			@param[in]	msg	メッセージ部
			@param[in]	len	長さ
			@return ICMP、PING 要求の場合「true」
		*/
		//-----------------------------------------------------------------//
		bool process(ETHD& ethd, const eth_h& eh, const ipv4_h& ih, const void* msg, int32_t len)
		{
			const icmp_t& t = *static_cast<const icmp_t*>(msg);

			if(t.type == 0x08 && t.code == 0x00) {  // PING request

				uint16_t sum = tools::calc_sum(msg, len);
				if(sum != 0) {
					const uint16_t* p = static_cast<const uint16_t*>(msg);
					utils::format("ICMP: sum error: %04X -> %04X\n")
						% static_cast<uint32_t>(tools::htons(p[1]))
						% static_cast<uint32_t>(sum);
					return false;
				}

//				utils::format("ICMP: %d bytes\n") % len;

				void* dst;
				uint16_t dlen;
				if(ethd.send_buff(&dst, dlen) != 0) {
					utils::format("ICMP: send_buff error\n");
					return false;
				}
				uint16_t all = sizeof(eth_h) + sizeof(ipv4_h) + len;
				if(all > dlen) {  // empty output buffer
					utils::format("ICMP: empty buffer error\n");
					return false;
				}

				eth_h* d_eh = reinterpret_cast<eth_h*>(dst);
				swap_copy_eth_h(d_eh, &eh);
				ipv4_h* d_ih = reinterpret_cast<ipv4_h*>(static_cast<uint8_t*>(dst) + sizeof(eth_h));
				swap_copy_ipv4_h(d_ih, &ih);
				{
					d_ih->set_csum(0x0000);
					uint16_t sum = tools::calc_sum(d_ih, sizeof(ipv4_h));
					d_ih->set_csum(sum);
				}
				uint8_t* d_msg = static_cast<uint8_t*>(dst);
				d_msg += sizeof(eth_h) + sizeof(ipv4_h);
				std::memcpy(d_msg, msg, len);
				d_msg[0] = 0x00;
				d_msg[2] = 0x00;
				d_msg[3] = 0x00;
				{
					uint16_t sum = tools::calc_sum(d_msg, len);
					d_msg[2] = sum >> 8;
					d_msg[3] = sum;
				}

//				dump(*d_eh);
//				dump(*d_ih);

				ethd.send(all);
			}
			return true;
		}
	};
}
