//=====================================================================//
/*! @file
    @brief  net_core @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "net/dhcp_client.hpp"
#include "net/net_io.hpp"

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
			main_loop,	// メイン・ループ
		};


		ETHER_IO&	io_;

		typedef dhcp_client<ETHER_IO> DHCP;
		DHCP		dhcp_;

		task		task_;

		uint8_t	link_interval_;
		bool	link_up_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	io	インサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		net_core(ETHER_IO& io) : io_(io), dhcp_(io),
			task_(task::wait_link), link_interval_(0), link_up_(false)
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
			if(link_interval_ >= 100) {
				io_.polling_link_status();
				link_interval_ = 0;
			}
			++link_interval_;

			bool link = io_.link_process();

			switch(task_) {

			case task::wait_link:
				if(link) {
					utils::format("Ether Link UP\n");
					dhcp_.start(200);  // 2 sec
					task_ = task::wait_dhcp;
				}
				break;

			case task::wait_dhcp:
				dhcp_.service();
				if(dhcp_.get_info().state == DHCP_INFO::state_t::collect) {
					utils::format("DHCP Collect\n");
					const DHCP_INFO& info = dhcp_.get_info();
					info.list();
					task_ = task::main_loop;
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

			case task::main_loop:
				break;

			default:
				break;
			}

//			if(link_up_ && !link) {  // link is down
//				utils::format("Ether Link Down\n");
//				task_ = task::wait_link;
//			}

			link_up_ = link;
		}
	};

}
