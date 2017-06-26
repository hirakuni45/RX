#pragma once
//=====================================================================//
/*! @file
    @brief  ネット・メイン @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/ip_adrs.hpp"
#include "common/dhcp_client.hpp"
#include "net2/ethernet.hpp"

#define NET_MAIN_DEBUG

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  net_main テンプレート・クラス
		@param[in]	ETHER	インサーネット・ドライバー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHER>
	class net_main {

#ifndef NET_MAIN_DEBUG
		typedef utils::null_format debug_format;
#else
		typedef utils::format debug_format;
#endif

		enum class task : uint8_t {
			wait_link,	// リンクアップを待つ
			wait_dhcp,	// DHCP IP アドレスの取得を待つ
			main_init,	// メイン初期化
			main_loop,	// メインループ
			stall,		// ストール
		};

		ETHER&		eth_;

		typedef dhcp_client<ETHER> DHCP;
		DHCP		dhcp_;

		typedef ethernet<ETHER> ETHERNET;
		ETHERNET	ethernet_;

		task		task_;

		uint8_t		link_interval_;
		uint8_t		stall_loop_;

		ip_adrs		ip_;
		ip_adrs		mask_;
		ip_adrs		gw_;
		ip_adrs		dns_;
		ip_adrs		dns2_;

		void set_tcpudp_env_()
		{
			const DHCP_INFO& info = dhcp_.get_info();
			info.list();
			ip_.set(info.ipaddr);
			mask_.set(info.maskaddr);
			gw_.set(info.gwaddr);
			dns_.set(info.dnsaddr);
			dns2_.set(info.dnsaddr2);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	io	インサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		net_main(ETHER& eth) : eth_(eth), dhcp_(eth), ethernet_(eth),
			task_(task::wait_link), link_interval_(0), stall_loop_(0),
			ip_(192, 168, 3, 20), mask_(255, 255, 255, 0), gw_(192, 168, 3, 1),
			dns_(192, 168, 3, 1), dns2_()
			{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  IP アドレスを参照
			@return IP アドレス
		*/
		//-----------------------------------------------------------------//
		const ip_adrs& get_ip_adrs() const { return ip_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  MASK を参照
			@return MASK
		*/
		//-----------------------------------------------------------------//
		const ip_adrs& get_mask() const { return mask_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  GW アドレスを参照
			@return GW アドレス
		*/
		//-----------------------------------------------------------------//
		const ip_adrs& get_gw_adrs() const { return gw_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  DNS アドレスを参照
			@return DNS アドレス
		*/
		//-----------------------------------------------------------------//
		const ip_adrs& get_dns_adrs() const { return dns_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  DNS2 アドレスを参照
			@return DNS2 アドレス
		*/
		//-----------------------------------------------------------------//
		const ip_adrs& get_dns2_adrs() const { return dns2_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	mac	インサーネット・コントローラー MAC アドレス
		*/
		//-----------------------------------------------------------------//
		bool start(const uint8_t* mac)
		{
			bool ret = eth_.open(mac);
			if(ret) {
				debug_format("net_main: start OK\n");
				link_interval_ = 0;
				task_ = task::wait_link;
			} else {
				debug_format("net_main: start NG\n");
				task_ = task::stall;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  フレーム・サービス
		*/
		//-----------------------------------------------------------------//
		void service_frame()
		{
			if(task_ == task::main_loop) {
				ethernet_.service();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（10ミリ秒毎に呼び出す）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			switch(task_) {

			case task::wait_link:
				{
					if(link_interval_ >= 100) {
						eth_.polling_link_status();
						link_interval_ = 0;
						debug_format("net_main: PHY wait link loop\n");
					}
					++link_interval_;

					bool link = eth_.service_link();
					if(link) {
						dhcp_.start();
						task_ = task::wait_dhcp;
					}
				}
				break;

			case task::wait_dhcp:
				dhcp_.service();
				if(dhcp_.get_info().state == DHCP_INFO::state_t::collect) {
					debug_format("net_main: DHCP Collect\n");
					set_tcpudp_env_();
					task_ = task::main_init;
				} else if(dhcp_.get_info().state == DHCP_INFO::state_t::timeout) {
					debug_format("net_main: DHCP Timeout (setup for fixed IP)\n");
					task_ = task::main_init;
				} else if(dhcp_.get_info().state == DHCP_INFO::state_t::error) {
					debug_format("net_main: DHCP Error\n");
					task_ = task::stall;
				}
				ethernet_.set_adrs(ip_, mask_, gw_);
//				memcpy(tcpudp_env[0].ipaddr,   ip_.get(),   4);
//				memcpy(tcpudp_env[0].maskaddr, mask_.get(), 4);
//				memcpy(tcpudp_env[0].gwaddr,   gw_.get(),   4);
//				memcpy(dnsaddr1, info.dnsaddr, 4);
//				memcpy(dnsaddr2, info.dnsaddr2, 4);
				break;

			case task::main_init:
				eth_.service_link();

				task_ = task::main_loop;
				break;

			case task::main_loop:
				eth_.service_link();

				if(link_interval_ >= 100) {
					eth_.polling_link_status();
					link_interval_ = 0;
				}
				++link_interval_;

				if(!eth_.get_stat().link_) {
					task_ = task::wait_link;
				}

				break;

			case task::stall:
				if(stall_loop_ >= 250) {
					debug_format("net_main: stall\n");
					stall_loop_ = 0;
				}
				++stall_loop_;
				break;

			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  メインを確認する
			@return 「true」なら、リンク
		*/
		//-----------------------------------------------------------------//
		bool check_main() const { return task_ == task::main_loop; }
	};
}
