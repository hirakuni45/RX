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
		@param[in]	ETHD	イーサーネット・ドライバー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHD>
	class net_main {
	public:
		typedef ethernet<ETHD> ETHERNET;

	private:
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

		ETHD&		ethd_;

		typedef dhcp_client<ETHD> DHCP;
		DHCP		dhcp_;

		ETHERNET	ethernet_;

		task		task_;

		uint8_t		link_interval_;
		uint8_t		stall_loop_;

		void set_tcpudp_env_()
		{
			const DHCP_INFO& info = dhcp_.get_info();
			info.list();
			ethernet_.at_info().ip.set(info.ipaddr);
			ethernet_.at_info().mask.set(info.maskaddr);
			ethernet_.at_info().gw.set(info.gwaddr);
			ethernet_.at_info().dns.set(info.dnsaddr);
			ethernet_.at_info().dns2.set(info.dnsaddr2);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	ETHD	イーサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		net_main(ETHD& ethd) : ethd_(ethd), dhcp_(ethd), ethernet_(ethd),
			task_(task::wait_link), link_interval_(0), stall_loop_(0)
			{
				ethernet_.at_info().ip.set(192, 168, 3, 20);
				ethernet_.at_info().mask.set(255, 255, 255, 0);
				ethernet_.at_info().gw.set(192, 168, 3, 1);
				ethernet_.at_info().dns.set(192, 168, 3, 1);
			}


		//-----------------------------------------------------------------//
		/*!
			@brief  ネット情報を参照
			@return ネット情報
		*/
		//-----------------------------------------------------------------//
		const net_info& get_info() const { return ethernet_.get_info(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  イーサーネットの参照
			@return	インサーネット
		*/
		//-----------------------------------------------------------------//
		ETHERNET& at_ethernet() { return ethernet_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	mac	インサーネット・コントローラー MAC アドレス
		*/
		//-----------------------------------------------------------------//
		bool start(const uint8_t* mac)
		{
			bool ret = ethd_.open(mac);
			if(ret) {
				debug_format("net_main: start OK\n");
				link_interval_ = 0;
				std::memcpy(ethernet_.at_info().mac, ethd_.get_mac(), 6);
				task_ = task::wait_link;
			} else {
				debug_format("net_main: start NG\n");
				task_ = task::stall;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  プロセス（割り込みタスク）
		*/
		//-----------------------------------------------------------------//
		void process()
		{
			if(task_ == task::main_loop) {
				ethernet_.process();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（10ミリ秒毎に呼び出す）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			ethernet_.service();

			switch(task_) {

			case task::wait_link:
				{
					if(link_interval_ >= 100) {
						ethd_.polling_link_status();
						link_interval_ = 0;
						debug_format("net_main: PHY wait link loop\n");
					}
					++link_interval_;

					bool link = ethd_.service_link();
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
				break;

			case task::main_init:
				ethd_.service_link();


				// test code
				{

				}



				task_ = task::main_loop;
				break;

			case task::main_loop:
				ethd_.service_link();

				if(link_interval_ >= 100) {
					ethd_.polling_link_status();
					link_interval_ = 0;
				}
				++link_interval_;

				if(!ethd_.get_stat().link_) {
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
