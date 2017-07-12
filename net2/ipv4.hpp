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
#include "common/format.hpp"
#include "common/net_tools.hpp"
#include "common/fixed_memory.hpp"
#include "common/ip_adrs.hpp"
#include "net2/icmp.hpp"
#include "net2/arp.hpp"
#include "net2/udp.hpp"
#include "net2/tcp.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ipv4 クラス
		@param[in]	ETHD	イーサーネット・ドライバー・クラス
		@param[in]	UDPN	UDP 管理数
		@param[in]	TCPN	TCP 管理数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHD, uint32_t UDPN, uint32_t TCPN>
	class ipv4 {
	public:
		typedef arp<ETHD> ARP;
		typedef udp<ETHD, UDPN> UDP;
		typedef tcp<ETHD, TCPN> TCP;

	private:

		ETHD&		ethd_;

		net_info&	info_;

		typedef icmp<ETHD>	ICMP;
		ICMP		icmp_;

		UDP			udp_;
		TCP			tcp_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth		イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		ipv4(ETHD& ethd, net_info& info) : ethd_(ethd), info_(info),
			icmp_(), udp_(ethd, info), tcp_(ethd, info)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  UDP の参照
			@return UDP
		*/
		//-----------------------------------------------------------------//
		UDP& at_udp() { return udp_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  TCP の参照
			@return TCP
		*/
		//-----------------------------------------------------------------//
		TCP& at_tcp() { return tcp_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  プロセス（割り込みから呼ばれる）
			@param[in]	h	イーサーネット・ヘッダー
			@param[in]	org	データ・フレーム
			@param[in]	len	データ・フレーム長
		*/
		//-----------------------------------------------------------------//
		bool process(const eth_h& eh, const void* org, int32_t len)
		{
			bool myframe = false;
			if(std::memcmp(eh.get_dst(), info_.mac, 6) == 0) {  // 自分に宛てたフレーム
				myframe = true;
//				utils::format("IPV4 Recv MyFrame:\n");
			} else if(tools::check_brodcast_mac(eh.get_dst())) {  // ブロード・キャスト
//				utils::format("IPV4 Recv Brodcast:\n");
			} else {
//				utils::format("IPV4 Recv Other\n");
				return false;
			}

			len -= 20;
			if(len < 0) {
				return false;
			}

			const ipv4_h& ih = *static_cast<const ipv4_h*>(org);
			uint16_t sum = tools::calc_sum(&ih, 20);
			if(sum != 0) {
				utils::format("IP Header sum error (%04X) -> %04X\n")
					% static_cast<uint32_t>(ih.get_csum())
					% static_cast<uint32_t>(sum);
				return false;
			}

			const uint8_t* msg = static_cast<const uint8_t*>(org);
			msg += sizeof(ipv4_h);

//			dump(eh);
//			dump(ih);

			switch(ih.get_protocol()) {

			case ipv4_h::protocol::ICMP:
				icmp_.process(ethd_, eh, ih, msg, len); 
				break;

			case ipv4_h::protocol::TCP:
				if(myframe) {  // TCP では、自分に関係するフレームを受け取る
					tcp_.process(eh, ih, reinterpret_cast<const tcp_h*>(msg), len);
				}
				break;

			case ipv4_h::protocol::UDP:
				// UDP では、自分に関係するフレーム、及び、ブロードキャスト・フレームを受け取る
				udp_.process(eh, ih, reinterpret_cast<const udp_h*>(msg), len);
				break;

			default:
				break;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（１０ｍｓ毎に呼ぶ）
			@param[in]	arp	ARP コンテキスト
		*/
		//-----------------------------------------------------------------//
		void service(ARP& arp)
		{
			udp_.service();
			tcp_.service(arp);
		}
	};
}
