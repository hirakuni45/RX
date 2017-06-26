#pragma once
//=========================================================================//
/*! @file
    @brief  Ethernet DIX(Ethernet II) @n
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
		@brief  ethernet クラス
		@param[in]	ETHER	イーサーネット・ドライバー・クラス
		@param[in]	ARPN	ARP キャッシュの最大数（通常８）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHER, uint32_t ARPN = 8>
	class ethernet {

		static const uint16_t TYPE_IPV4       = 0x0800;
		static const uint16_t TYPE_ARP        = 0x0806;
		static const uint16_t TYPE_APPLETALK  = 0x809B;
		static const uint16_t TYPE_IEEE802_1Q = 0x8100;
		static const uint16_t TYPE_IPX        = 0x8137;
		static const uint16_t TYPE_IPV6       = 0x86DD;


		struct header {
			uint8_t		dst[6];    // dst MAC address 受信先
			uint8_t		src[6];    // src MAC address 送信元
			uint16_t	type;      // TYPE_xxx
		};

		ETHER&		eth_;

		ip_adrs		ip_;
		ip_adrs		mask_;
		ip_adrs		gw_;

		struct arp_cash {
			uint8_t	ip[4];
			uint8_t	mac[6];
		};
		arp_cash	arp_cash_[ARPN];
		uint32_t	arp_cash_num_;

		bool check_brodcast_(const uint8_t* p) {
			static uint8_t tbl[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
			return memcmp(p, tbl, 6) == 0;
		}


		static const char* mac_str_(const uint8_t* p) {
			static char tmp[20];
			utils::sformat("%02X:%02X:%02X:%02X:%02X:%02X", tmp, sizeof(tmp))
				% static_cast<uint32_t>(p[0])
				% static_cast<uint32_t>(p[1])
				% static_cast<uint32_t>(p[2])
				% static_cast<uint32_t>(p[3])
				% static_cast<uint32_t>(p[4])
				% static_cast<uint32_t>(p[5]);
			return tmp;
		}


		static const char* ip_str_(const uint8_t* p) {
			static char tmp[17];
			utils::sformat("%d.%d.%d.%d", tmp, sizeof(tmp))
				% static_cast<int>(p[0])
				% static_cast<int>(p[1])
				% static_cast<int>(p[2])
				% static_cast<int>(p[3]);
			return tmp;
		}


		void dump_(const char* init, const header* h) {
			utils::format("%ssrc(%s), dst(%s), type(%04X)\n")
				% init
				% mac_str_(h->src)
				% mac_str_(h->dst)
				% static_cast<uint32_t>(tools::htons(h->type));
		}


		void parse_ipv4_(const header* h, const void* top, int32_t len)
		{
			if(std::memcmp(h->dst, eth_.get_mac(), 6) == 0) {  // 自分に宛てたフレーム
				dump_("Match:    ", h);
			} else if(check_brodcast_(h->dst)) {  // ブロード・キャスト
				dump_("Brodcast: ", h);
			}
		}


		struct arp_t {
			uint8_t	head[8];
			uint8_t	src_mac[6];
			uint8_t	src_ipa[4];
			uint8_t dst_mac[6];
			uint8_t dst_ipa[4];
		};


		void install_arp_cash_(const arp_t& t)
		{
		}


		bool parse_arp_(const header* h, const void* top, int32_t len)
		{
			if(!check_brodcast_(h->dst)) {
				return false;
			}
			if(static_cast<size_t>(len) < sizeof(arp_t)) {
				return false;
			}

			const arp_t* r = static_cast<const arp_t*>(top);
			static const uint8_t head[8] = { 0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01 };
			if(std::memcmp(head, r->head, 8) != 0) {
				return false;
			}

			ip_adrs ipa(r->dst_ipa[0], r->dst_ipa[1], r->dst_ipa[2], r->dst_ipa[3]);
			if(ip_ != ipa) {
				install_arp_cash_(*r);
				return false;
			}

			utils::format("ARP: src: %s, dst: %s\n") % ip_str_(r->src_ipa) % ip_str_(r->dst_ipa);

			header eh;
			std::memcpy(eh.dst, h->src, 6);
			std::memcpy(eh.src, eth_.get_mac(), 6);
			eh.type = h->type;
			arp_t arp;
			std::memcpy(arp.head, head, 7);
			arp.head[7] = 0x02;
			std::memcpy(arp.src_mac, eth_.get_mac(), 6);
			std::memcpy(arp.src_ipa, ip_.get(), 4);
			std::memcpy(arp.dst_mac, r->src_mac, 6);
			std::memcpy(arp.dst_ipa, r->src_ipa, 4);

			eth_.write(&eh, sizeof(eh), &arp, sizeof(arp));

			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth	イーサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		ethernet(ETHER& eth) : eth_(eth),
			ip_(), mask_(), gw_(),
			arp_cash_{ 0 }, arp_cash_num_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  アドレス情報の登録
			@param[in]	ip		IP アドレス
			@param[in]	mask	MASK アドレス
			@param[in]	gw		GW アドレス
		*/
		//-----------------------------------------------------------------//
		void set_adrs(const ip_adrs& ip, const ip_adrs& mask, const ip_adrs& gw)
		{
			ip_ = ip;
			mask_ = mask;
			gw_ = gw;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			// recv
			void* org;
			int32_t len = eth_.recv(&org);
			if(len < 0) {  // error state

				return;
			} else if((len > 1514) || (len < 60)) {

				eth_.recv_buff_release();
				return;
			} else {  // recv data

				const header* h = static_cast<const header*>(org);
				const void* top = static_cast<const uint8_t*>(org) + sizeof(header);
				switch(tools::htons(h->type)) {

				case TYPE_IPV4:
					parse_ipv4_(h, top, len - sizeof(header));
					break;

				// 自分の IP アドレスに応答
				case TYPE_ARP:
					parse_arp_(h, top, len - sizeof(header));
					break;

				case TYPE_IPX:
					break;
				default:
					break;
				}
				eth_.recv_buff_release();
			}
		}
	};
}
