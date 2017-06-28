#pragma once
//=========================================================================//
/*! @file
    @brief  ARP Protocol @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "net2/net_st.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ARP クラス
		@param[in]	ETHER	イーサーネット・ドライバー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHER>
	class arp {

		ETHER&		eth_;

		net_info&	info_;

		struct arp_t {
			uint8_t	head[8];
			uint8_t	src_mac[6];
			uint8_t	src_ipa[4];
			uint8_t dst_mac[6];
			uint8_t dst_ipa[4];
		};

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth		イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		arp(ETHER& eth, net_info& info) : eth_(eth), info_(info)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  パース
			@param[in]	h	ヘッダー
			@param[in]	top	先頭ポインター
			@param[in]	len	長さ
		*/
		//-----------------------------------------------------------------//
		bool parse(const eth_h& h, const void* top, int32_t len)
		{
			if(!tools::check_brodcast_mac(h.dst)) {
				return false;
			}
			if(static_cast<size_t>(len) < sizeof(arp_t)) {
				return false;
			}

			const arp_t& r = *static_cast<const arp_t*>(top);
			static const uint8_t head[7] = { 0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00 };
			if(std::memcmp(head, r.head, 7) != 0) {
				return false;
			}

			if(r.head[7] == 0x01) {  // ARP request
				ip_adrs ipa(r.src_ipa[0], r.src_ipa[1], r.src_ipa[2], r.src_ipa[3]);
				info_.cash.insert(ipa, r.src_mac);
			} else if(r.head[7] == 0x02) {  // ARP response
				// IP/MAC の収集
				ip_adrs ipa(r.src_ipa[0], r.src_ipa[1], r.src_ipa[2], r.src_ipa[3]);
				info_.cash.insert(ipa, r.src_mac);
				ipa.set(r.dst_ipa[0], r.dst_ipa[1], r.dst_ipa[2], r.dst_ipa[3]);
				info_.cash.insert(ipa, r.dst_mac);
				return false;
			} else {
				return false;
			}

			ip_adrs ipa(r.dst_ipa[0], r.dst_ipa[1], r.dst_ipa[2], r.dst_ipa[3]);
			if(info_.ip != ipa) {
				return false;
			}

//			utils::format("ARP: src: %s, dst: %s\n")
//				% tools::ip_str(r.src_ipa)
//				% tools::ip_str(r.dst_ipa);

			eth_h eh;
			std::memcpy(eh.dst, h.src, 6);
			std::memcpy(eh.src, info_.mac, 6);
			eh.type = h.type;
			arp_t arp;
			std::memcpy(arp.head, head, 7);
			arp.head[7] = 0x02;
			std::memcpy(arp.src_mac, info_.mac, 6);
			std::memcpy(arp.src_ipa, info_.ip.get(), 4);
			std::memcpy(arp.dst_mac, r.src_mac, 6);
			std::memcpy(arp.dst_ipa, r.src_ipa, 4);

			eth_.write(&eh, sizeof(eth_h), &arp, sizeof(arp_t));

			return true;
		}
	};
}
