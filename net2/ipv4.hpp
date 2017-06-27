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

		static const uint16_t ICMP_REQ = 0x0008;

		uint16_t sum_(const void* org, uint32_t len)
		{
			const uint8_t* p = static_cast<const uint8_t*>(org);
			uint32_t sum = 0;
			for(uint32_t i = 0; i < len; ++i) {
				sum += static_cast<uint32_t>(p[0]) << 8;
				sum += static_cast<uint32_t>(p[1]);
				p += 2;
			}
			return !((sum & 0xffff) + (sum >> 16));
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth		イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		ipv4(ETHER& eth, net_info& info) : eth_(eth), info_(info) { }


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
			uint16_t sum = sum_(&ih, 10);
			if(sum != 0) {
				utils::format("IP Header sum error(%04X): %04X\n")
					% static_cast<uint32_t>(tools::htons(ih.csum))
					% static_cast<uint32_t>(sum);
				return false;
			}

			dump(eh);
			dump(ih);

			switch(ih.get_protocol()) {
			case ipv4_protocol::ICMP:

				break;
			case ipv4_protocol::TCP:

				break;
			case ipv4_protocol::UDP:

				break;
			default:

				break;
			}

			return true;
		}

	};
}
