#pragma once
//=========================================================================//
/*! @file
    @brief  Ethernet DIX(Ethernet II) @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "net2/net_st.hpp"
#include "net2/ipv4.hpp"
#include "net2/arp.hpp"

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

		ETHER&		eth_;

		net_info	info_;

		typedef arp<ETHER, ARPN> ARP;
		ARP			arp_;

		typedef ipv4<ETHER> IPV4;
		IPV4		ipv4_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth	イーサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		ethernet(ETHER& eth) : eth_(eth), info_(),
			arp_(eth, info_), ipv4_(eth, info_)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  ネット情報の登録
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		void set_info(const net_info& info)
		{
			info_ = info;
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
			} else if((len > 1514) || (len < 60)) {  // サイズ範囲外は捨てる

				eth_.recv_buff_release();
				return;
			} else {  // recv data

				const eth_h& h = *static_cast<const eth_h*>(org);

				const void* top = static_cast<const uint8_t*>(org) + sizeof(eth_h);

				switch(h.get_type()) {
				case eth_type::IPV4:
					ipv4_.parse(h, top, len - sizeof(eth_h));
					break;

				case eth_type::ARP:
					arp_.parse(h, top, len - sizeof(eth_h));
					break;

				case eth_type::IPX:
					break;
				default:
					break;
				}

				eth_.recv_buff_release();
			}
		}
	};
}
