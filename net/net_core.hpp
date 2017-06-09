//=====================================================================//
/*! @file
    @brief  net_core @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "net/dhcp_client.hpp"

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
			wait_link,	// リンクアップを待つ
			wait_dhcp,	// DHCP IP アドレスの取得を待つ
			setup_ip,	// IP アドレスを直接設定
			main_loop,	// メイン・ループ
		};


		ETHER_IO&	io_;

		typedef dhcp_client<ETHER_IO> DHCP;
		DHCP		dhcp_;
///		DHCP::dhcp_t dhcp_status_;

		task		task_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	io	インサーネット・ドライバー・クラス
		*/
		//-----------------------------------------------------------------//
		net_core(ETHER_IO& io) : io_(io), dhcp_(io),
			task_(task::wait_link)
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
				io_.polling_link_status();
				if(io_.link_process()) {
					utils::format("Ether Link UP: OK\n");
					task_ = task::wait_dhcp;
				}
				break;

			case task::wait_dhcp:
				if(dhcp_.start()) {
					utils::format("DHCP OK\n");
					const DHCP_INFO& info = dhcp_.get_info();
					info.list();
					task_ = task::main_loop;
				} else {
					utils::format("DHCP NG\n");
					task_ = task::setup_ip;
				}
				break;

			case task::setup_ip:
				break;

			case task::main_loop:
				break;

			default:
				break;
			}
		}
	};

}
