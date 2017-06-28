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
		@param[in]	ETHER	イーサーネット・ドライバー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHER>
	class ethernet {

		ETHER&		eth_;

		net_info	info_;

		typedef arp<ETHER> ARP;
		ARP			arp_;

		typedef ipv4<ETHER> IPV4;
		IPV4		ipv4_;

		uint32_t	info_update_count_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth	イーサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		ethernet(ETHER& eth) : eth_(eth), info_(),
			arp_(info_), ipv4_(eth, info_),
			info_update_count_(0)
		{ }


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
			@brief  データ、受信、送信、プロセス
		*/
		//-----------------------------------------------------------------//
		void process()
		{
			// recv
			void* org;
			int32_t len = eth_.recv(&org);
			if(len < 0) {  // error state

				return;
			} else if((len > 1514) || (len < 60)) {  // サイズ範囲外は捨てる
				if(len != 0) {
					eth_.recv_buff_release();
				}
				return;
			} else {  // recv data

				const eth_h& h = *static_cast<const eth_h*>(org);

				const void* top = static_cast<const uint8_t*>(org) + sizeof(eth_h);

				switch(h.get_type()) {
				case eth_type::IPV4:
					ipv4_.parse(h, top, len - sizeof(eth_h));
					break;

				case eth_type::ARP:
					arp_.parse(eth_, h, top, len - sizeof(eth_h));
					break;

				case eth_type::IPX:
					break;
				default:
					break;
				}

				eth_.recv_buff_release();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オープン
			@param[in]	adrs	アドレス
			@param[in]	port	ポート
			@return ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		int open(const ip_adrs& adrs, uint16_t port)
		{
			int dsc = -1;

#if 0
			uint32_t n = info_.cash.lookup(adrs);
			if(n == info_.cash.capacity()) {

			} else {
				
			}
#endif


			return dsc;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クローズ
			@param[in]	dsc	ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		void close(int dsc)
		{
///			if(dsc < 0 || dsc >= (

		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（１０ｍｓ毎に呼ぶ）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			if(info_update_count_ >= 10) {
				info_.cash.update();
				info_update_count_ = 0;
			} else {
				++info_update_count_;
			}

			arp_.service(eth_);

			ipv4_.service();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ARP リスト表示
		*/
		//-----------------------------------------------------------------//
		void arp_list() const
		{
			info_.cash.list();
		}
	};
}
