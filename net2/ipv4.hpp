#pragma once
//=========================================================================//
/*! @file
    @brief  ipv4 クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include <cstdint>
#include <cstring>
#include "common/net_tools.hpp"
#include "common/format.hpp"
#include "common/ip_adrs.hpp"
#include "net2/icmp.hpp"
#include "net2/udp.hpp"
#include "net2/tcp.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ipv4 クラス
		@param[in]	ETHER	イーサーネット・ドライバー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHER>
	class ipv4 {

		ETHER&		eth_;

		net_info&	info_;

		typedef icmp<ETHER>	ICMP;
		ICMP		icmp_;

		typedef udp<ETHER> UDP;
		UDP			udp_;

		typedef tcp<ETHER> TCP;
		TCP			tcp_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth		イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		ipv4(ETHER& eth, net_info& info) : eth_(eth), info_(info),
			icmp_(eth), udp_(eth), tcp_(eth)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  パース
			@param[in]	h	イーサーネット・ヘッダー
			@param[in]	org	データ・フレーム
			@param[in]	len	データ・フレーム長
		*/
		//-----------------------------------------------------------------//
		bool parse(const eth_h& eh, const void* org, int32_t len)
		{
			if(std::memcmp(eh.dst, info_.mac, 6) == 0) {  // 自分に宛てたフレーム
//				dump_("Match:    ", h);
			} else if(tools::check_brodcast_mac(eh.dst)) {  // ブロード・キャスト
//				dump_("Brodcast: ", h);
			} else {
				return false;
			}

			len -= 20;
			if(len < 0) {
				return false;
			}

			const ipv4_h& ih = *static_cast<const ipv4_h*>(org);
			uint16_t sum = tools::calc_sum(&ih, 20);
			if(sum != 0) {
				utils::format("IP Header sum error(%04X) -> %04X\n")
					% static_cast<uint32_t>(tools::htons(ih.csum))
					% static_cast<uint32_t>(sum);
				return false;
			}

			const uint8_t* msg = static_cast<const uint8_t*>(org);
			msg += sizeof(ipv4_h);

//			dump(eh);
//			dump(ih);

			switch(ih.get_protocol()) {
			case ipv4_protocol::ICMP:
				icmp_.parse(eh, ih, msg, len); 
				break;
			case ipv4_protocol::TCP:
				tcp_.parse(eh, ih, msg, len);
				break;
			case ipv4_protocol::UDP:
				udp_.parse(eh, ih, msg, len);
				break;
			default:

				break;
			}

			return true;
		}

	};
}
