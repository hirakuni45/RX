#pragma once
//=========================================================================//
/*! @file
    @brief  ARP Protocol @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "net2/net_st.hpp"
#include "common/fixed_fifo.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ARP クラス
		@param[in]	ETHER	イーサーネット・ドライバー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHER>
	class arp {

		static const uint16_t ARP_REQUEST_WAIT = 200;   ///< 2 sec
		static const uint16_t ARP_REQUEST_NUM  = 5;     ///< 5 times

		struct arp_t {
			uint8_t	head[8];
			uint8_t	src_mac[6];
			uint8_t	src_ipa[4];
			uint8_t dst_mac[6];
			uint8_t dst_ipa[4];
		};

		net_info&	info_;

		typedef utils::fixed_fifo<arp_info, 8> ARP_BUFF;

		ARP_BUFF	arp_buff_;

		ip_adrs		req_ipa_;
		uint16_t	req_wait_;
		uint16_t	req_num_;

		static const uint8_t* get_arp_head7()
		{
			static const uint8_t head[7] = { 0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00 };
			return head;
		}


		void dump_(const arp_t& arp)
		{
			utils::format("ARP Header:\n");
			utils::format("  %02X%02X\n")
				% static_cast<uint32_t>(arp.head[0]) % static_cast<uint32_t>(arp.head[1]);
			utils::format("  %02X%02X\n")
				% static_cast<uint32_t>(arp.head[2]) % static_cast<uint32_t>(arp.head[3]);
			utils::format("  %02X%02X\n")
				% static_cast<uint32_t>(arp.head[4]) % static_cast<uint32_t>(arp.head[5]);
			utils::format("  %02X%02X\n")
				% static_cast<uint32_t>(arp.head[6]) % static_cast<uint32_t>(arp.head[7]);
			utils::format("  src: %s, %s\n") % tools::mac_str(arp.src_mac) % tools::ip_str(arp.src_ipa);
			utils::format("  dst: %s, %s\n") % tools::mac_str(arp.dst_mac) % tools::ip_str(arp.dst_ipa);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		arp(net_info& info) : info_(info), req_ipa_(), req_wait_(0), req_num_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  パース
			@param[in]	eth		イーサーネット・ドライバー
			@param[in]	h		ヘッダー
			@param[in]	top		先頭ポインター
			@param[in]	len		長さ
		*/
		//-----------------------------------------------------------------//
		bool parse(ETHER& eth, const eth_h& h, const void* top, int32_t len)
		{
			if(static_cast<size_t>(len) < sizeof(arp_t)) {
				return false;
			}

			const arp_t& r = *static_cast<const arp_t*>(top);
			if(std::memcmp(get_arp_head7(), r.head, 7) != 0) {
				return false;
			}

			if(tools::check_brodcast_mac(h.get_dst()) && r.head[7] == 0x01) {  // ARP Request
				if(arp_buff_.length() < (arp_buff_.size() - 1)) {
					arp_info a;
					a.ipa.set(r.src_ipa[0], r.src_ipa[1], r.src_ipa[2], r.src_ipa[3]);
					std::memcpy(a.mac, r.src_mac, 6);
					arp_buff_.put(a);
				}
			} else if(r.head[7] == 0x02) {  // ARP Response
				// IP/MAC の収集
				if(arp_buff_.length() < (arp_buff_.size() - 2)) {
					arp_info a;
					a.ipa.set(r.src_ipa[0], r.src_ipa[1], r.src_ipa[2], r.src_ipa[3]);
					std::memcpy(a.mac, r.src_mac, 6);
					arp_buff_.put(a);
					a.ipa.set(r.dst_ipa[0], r.dst_ipa[1], r.dst_ipa[2], r.dst_ipa[3]);
					std::memcpy(a.mac, r.dst_mac, 6);
					arp_buff_.put(a);
				}
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
			void* dst;
			uint16_t dlen;
			if(eth.send_buff(&dst, dlen) != 0) {
				utils::format("ARP: ether send_buff error\n");
				return false;
			}

			eth_h& eh = *static_cast<eth_h*>(dst);
			eh.set_dst(h.get_src());
			eh.set_src(info_.mac);
			eh.set_type(eth_type::ARP);

   			arp_t& arp = *static_cast<arp_t*>(eth_h::next_ptr(dst));
			std::memcpy(arp.head, get_arp_head7(), 7);
			arp.head[7] = 0x02;
			std::memcpy(arp.src_mac, info_.mac, 6);
			std::memcpy(arp.src_ipa, info_.ip.get(), 4);
			std::memcpy(arp.dst_mac, r.src_mac, 6);
			std::memcpy(arp.dst_ipa, r.src_ipa, 4);

//			dump(eh);
//			dump_(arp);

			eth.send(sizeof(eth_h) + sizeof(arp_t));

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  リクエスト
			@param[in]	eth		イーサーネット・ドライバー
			@param[in]	ipa		リクエストする IP アドレス
			@return 正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		bool request(ETHER& eth, const ip_adrs& ipa)
		{
			void* dst;
			uint16_t dlen;
			if(eth.send_buff(&dst, dlen) != 0) {
				utils::format("ARP: ether send_buff error\n");
				return false;
			}

			eth_h& eh = *static_cast<eth_h*>(dst);
			eh.set_dst(tools::get_brodcast_mac());
			eh.set_src(info_.mac);
			eh.set_type(eth_type::ARP);

   			arp_t& arp = *static_cast<arp_t*>(eth_h::next_ptr(dst));
			std::memcpy(arp.head, get_arp_head7(), 7);
			arp.head[7] = 0x01;  // request
			std::memcpy(arp.src_mac, info_.mac, 6);
			std::memcpy(arp.src_ipa, info_.ip.get(), 4);
			std::memset(arp.dst_mac, 0x00, 6);
			std::memcpy(arp.dst_ipa, ipa.get(), 4);

			eth.send(sizeof(eth_h) + sizeof(arp_t));

			req_ipa_   = ipa;
			req_wait_  = ARP_REQUEST_WAIT;
			req_num_   = ARP_REQUEST_NUM;
			utils::format("ARP request: %s\n") % ipa.c_str();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	eth		イーサーネット・ドライバー
		*/
		//-----------------------------------------------------------------//
		void service(ETHER& eth)
		{
			while(arp_buff_.length() > 0) {
				const auto a = arp_buff_.get();
				info_.cash.insert(a.ipa, a.mac);
			}

			if(req_wait_) {
				--req_wait_;
			} else if(req_num_) {
				--req_num_;
				auto n = info_.cash.lookup(req_ipa_);
				if(n >= info_.cash.capacity()) {
					req_wait_ = ARP_REQUEST_WAIT;
					request(eth, req_ipa_);
				}
			}
		}
	};
}
