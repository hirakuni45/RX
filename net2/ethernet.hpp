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
#include "net2/mac_cash.hpp"
#include "net2/arp.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet クラス
		@param[in]	ETHD	イーサーネット・ドライバー・クラス
		@param[in]	UDPN	UDP 経路数の最大数
		@param[in]	TCPN	TCP 経路数の最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHD, uint32_t UDPN, uint32_t TCPN>
	class ethernet {
	public:
		static const uint32_t UDP_OPEN_MAX = UDPN;  ///< UDP 経路数の最大数
		static const uint32_t TCP_OPEN_MAX = TCPN;  ///< TCP 経路数の最大数

		typedef arp<ETHD> ARP;

		typedef ipv4<ETHD, UDPN, TCPN> IPV4;

	private:

		ETHD&		ethd_;

		net_info	info_;

		ARP			arp_;

		IPV4		ipv4_;

		uint32_t	info_update_count_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	ethd	イーサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		ethernet(ETHD& ethd) : ethd_(ethd), info_(),
			arp_(ethd, info_), ipv4_(ethd, info_),
			info_update_count_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  イーサーネット・ドライバーの参照
			@return イーサーネット・ドライバー
		*/
		//-----------------------------------------------------------------//
		ETHD& at_ethd() { return ethd_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ネット情報の参照
			@return ネット情報
		*/
		//-----------------------------------------------------------------//
		net_info& at_info() { return info_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ネット情報の参照（ＲＯ）
			@return ネット情報
		*/
		//-----------------------------------------------------------------//
		const net_info& get_info() const { return info_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  IPV4 インスタンスの参照
			@return IPV4 インスタンス
		*/
		//-----------------------------------------------------------------//
		IPV4& at_ipv4() { return ipv4_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  データ、受信、送信、プロセス
		*/
		//-----------------------------------------------------------------//
		void process()
		{
			// recv
			void* org;
			int32_t len = ethd_.recv_buff(&org);
			if(len < 0) {  // error state

				return;
			} else if((len > 1514) || (len < 60)) {  // サイズ範囲外は捨てる
				if(len != 0) {
					ethd_.recv_buff_release();
				}
				return;
			} else {  // recv data

				const eth_h& h = *static_cast<const eth_h*>(org);

				const void* top = static_cast<const uint8_t*>(org) + sizeof(eth_h);

				switch(h.get_type()) {
				case eth_type::IPV4:
					ipv4_.process(h, top, len - sizeof(eth_h));
					break;

				case eth_type::ARP:
					arp_.process(h, top, len - sizeof(eth_h));
					break;

				case eth_type::IPX:
					break;
				default:
					break;
				}

				ethd_.recv_buff_release();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（１０ｍｓ毎に呼ぶ）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			if(info_update_count_ >= 10) {
				info_.at_cash().update();
				info_update_count_ = 0;
			} else {
				++info_update_count_;
			}

			ipv4_.service(arp_);

			arp_.service();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ARP コンテキストの参照
			@return ARP コンテキスト
		*/
		//-----------------------------------------------------------------//
		ARP& at_arp() noexcept { return arp_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ARP リスト表示
		*/
		//-----------------------------------------------------------------//
		void arp_list() const
		{
			info_.get_cash().list();
		}
	};
}
