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
#include "net2/net_st.hpp"

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

		net_info	info_;

		void set_tcpudp_env_()
		{
			const DHCP_INFO& info = dhcp_.get_info();
			info.list();
			info_.ip.set(info.ipaddr);
			info_.mask.set(info.maskaddr);
			info_.gw.set(info.gwaddr);
			info_.dns.set(info.dnsaddr);
			info_.dns2.set(info.dnsaddr2);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	io	インサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		net_main(ETHER& eth) : eth_(eth), dhcp_(eth), ethernet_(eth),
			task_(task::wait_link), link_interval_(0), stall_loop_(0)
			{
				info_.ip.set(192, 168, 3, 20);
				info_.mask.set(255, 255, 255, 0);
				info_.gw.set(192, 168, 3, 1);
				info_.dns.set(192, 168, 3, 1);
			}


		//-----------------------------------------------------------------//
		/*!
			@brief  ネット情報を参照
			@return ネット情報
		*/
		//-----------------------------------------------------------------//
		const net_info& get_info() const { return info_; }


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
				std::memcpy(info_.mac, eth_.get_mac(), 6);
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
				ethernet_.set_info(info_);
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
