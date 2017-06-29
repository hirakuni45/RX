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
#include "net2/udp_manage.hpp"
#include "net2/tcp_manage.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ipv4 クラス
		@param[in]	ETHER	イーサーネット・ドライバー・クラス
		@param[in]	UDPN	UDP 管理数
		@param[in]	TCPN	TCP 管理数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHER, uint32_t UDPN, uint32_t TCPN>
	class ipv4 {

		ETHER&		eth_;

		net_info&	info_;

		typedef icmp<ETHER>	ICMP;
		ICMP		icmp_;

		typedef udp_manage<ETHER, UDPN> UDP_M;
		UDP_M		udpm_;

		typedef tcp_manage<ETHER, TCPN> TCP_M;
		TCP_M		tcpm_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth		イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		ipv4(ETHER& eth, net_info& info) : eth_(eth), info_(info),
			icmp_(), udpm_(eth), tcpm_(eth)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  UDP の格納可能な最大サイズを返す
			@return UDP の格納可能な最大サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t udp_capacity() const noexcept { return udpm_.capacity(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  UDP の格納可能な最大サイズを返す
			@return UDP の格納可能な最大サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t tcp_capacity() const noexcept { return tcpm_.capacity(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  プロセス @n
					※割り込み外から呼ぶ事は禁止
			@param[in]	h	イーサーネット・ヘッダー
			@param[in]	org	データ・フレーム
			@param[in]	len	データ・フレーム長
		*/
		//-----------------------------------------------------------------//
		bool process(const eth_h& eh, const void* org, int32_t len)
		{
			if(std::memcmp(eh.get_dst(), info_.mac, 6) == 0) {  // 自分に宛てたフレーム
//				dump_("Match:    ", h);
			} else if(tools::check_brodcast_mac(eh.get_dst())) {  // ブロード・キャスト
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
				icmp_.process(eth_, eh, ih, msg, len); 
				break;
			case ipv4_h::protocol::TCP:
				tcpm_.process(eh, ih, msg, len);
				break;
			case ipv4_h::protocol::UDP:
				udpm_.process(eh, ih, msg, len);
				break;
			default:

				break;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（１０ｍｓ毎に呼ぶ）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			udpm_.service();
			tcpm_.service();
		}
	};
}
