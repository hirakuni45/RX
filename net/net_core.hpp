//=====================================================================//
/*! @file
    @brief  ネット・コア @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "net/dhcp_client.hpp"

#include "r_t4_itcpip.h"

extern TCPUDP_ENV tcpudp_env[];

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  net_core テンプレート・クラス
		@param[in]	ETHER_IO	インサーネット・ドライバー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHER_IO>
	class net_core {
	public:

	private:

		enum class task {
			halt,		// Halt !!!
			wait_link,	// リンクアップを待つ
			wait_dhcp,	// DHCP IP アドレスの取得を待つ
			setup_ip,	// IP アドレスを直接設定
			setup_tcpudp,
			main_loop,	// メイン・ループ
			stall,		// ストール
		};

		ETHER_IO&	io_;

		typedef dhcp_client<ETHER_IO> DHCP;
		DHCP		dhcp_;

		task		task_;

		uint8_t		link_interval_;

		uint32_t	tcpudp_work_[21504 / sizeof(uint32_t)];

		void set_tcpudp_env_()
		{
			const DHCP_INFO& info = dhcp_.get_info();
			info.list();

			memcpy(tcpudp_env[0].ipaddr, info.ipaddr, 4);
			memcpy(tcpudp_env[0].maskaddr, info.maskaddr, 4);
			memcpy(tcpudp_env[0].gwaddr, info.gwaddr, 4);

//			memcpy(dnsaddr1, info.dnsaddr, 4);
//			memcpy(dnsaddr2, info.dnsaddr2, 4);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	io	インサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		net_core(ETHER_IO& io) : io_(io), dhcp_(io),
			task_(task::wait_link), link_interval_(0)
			{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	mac	インサーネット・コントローラー MAC アドレス
		*/
		//-----------------------------------------------------------------//
		bool start(const uint8_t* mac)
		{
			bool ret = io_.open(mac);
			if(ret) {
				utils::format("Ether open OK\n");
			} else {
				utils::format("Ether open NG\n");
			}

			task_ = task::wait_link;

			return ret;
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
						io_.polling_link_status();
						link_interval_ = 0;
					}
					++link_interval_;

					bool link = io_.link_process();
					if(link) {
						utils::format("Ether Link UP\n");
						dhcp_.start(200);  // 2 sec
						task_ = task::wait_dhcp;
					}
				}
				break;

			case task::wait_dhcp:
				dhcp_.service();
				if(dhcp_.get_info().state == DHCP_INFO::state_t::collect) {
					utils::format("DHCP Collect\n");
					set_tcpudp_env_();
					task_ = task::setup_tcpudp;
				} else if(dhcp_.get_info().state == DHCP_INFO::state_t::timeout) {
					utils::format("DHCP Timeout\n");
					task_ = task::setup_ip;
				} else if(dhcp_.get_info().state == DHCP_INFO::state_t::error) {
					utils::format("DHCP Error\n");
					task_ = task::halt;
				}
				break;

			case task::setup_ip:
				break;

			case task::setup_tcpudp:
				{
					// Get the size of the work area used by the T4 (RAM size).
					uint32_t ramsize = tcpudp_get_ramsize();
					if(ramsize > (sizeof(tcpudp_work_))) {
						// Then reserve as much memory array for the work area as the size
						// indicated by the returned value.
						task_ = task::stall;
						break;
					}

					// Initialize the TCP/IP
					auto ercd = tcpudp_open(tcpudp_work_);
					if(ercd != E_OK) {
						task_ = task::stall;
						break;						
					}

					task_ = task::main_loop;
				}
				break;

			case task::main_loop:
				io_.link_process();


				break;

			case task::stall:
				break;

			default:
				break;
			}
		}
	};

}
