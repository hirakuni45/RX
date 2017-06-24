//=====================================================================//
/*! @file
    @brief  ネット・コア @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "net/dhcp_client.hpp"
#include "net/socket.hpp"

#include "net/r_tcpip_private.h"

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

		enum class task : uint8_t {
			halt,		// Halt !!!
			wait_link,	// リンクアップを待つ
			wait_dhcp,	// DHCP IP アドレスの取得を待つ
			setup_tcpudp,
			main_init,	// メイン初期化
			main_loop,	// メインループ
			stall,		// ストール
		};

		ETHER_IO&	io_;

		typedef dhcp_client<ETHER_IO> DHCP;
		DHCP		dhcp_;

		typedef socket<ETHER_IO> SOCKET;
		SOCKET		socket_;

		task		task_;

		uint8_t		link_interval_;

		ip_adrs		ip_;
		ip_adrs		mask_;
		ip_adrs		gw_;
		ip_adrs		dns_;
		ip_adrs		dns2_;

///		uint32_t	tcpudp_work_[21504 / sizeof(uint32_t)];

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
		net_core(ETHER_IO& io) : io_(io), dhcp_(io), socket_(io),
			task_(task::wait_link), link_interval_(0),
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
			bool ret = io_.open(mac);
			if(ret) {
				utils::format("Ether open OK\n");
				memcpy(&_myethaddr[0][0], mac, 6);				
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
						dhcp_.start();
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
					utils::format("DHCP Timeout (setup fixed)\n");
					task_ = task::setup_tcpudp;
				} else if(dhcp_.get_info().state == DHCP_INFO::state_t::error) {
					utils::format("DHCP Error\n");
					task_ = task::halt;
				}
				memcpy(tcpudp_env[0].ipaddr,   ip_.get(),   4);
				memcpy(tcpudp_env[0].maskaddr, mask_.get(), 4);
				memcpy(tcpudp_env[0].gwaddr,   gw_.get(),   4);
//				memcpy(dnsaddr1, info.dnsaddr, 4);
//				memcpy(dnsaddr2, info.dnsaddr2, 4);
				break;

			case task::setup_tcpudp:
				{
#if 1
					if(!socket<ETHER_IO>::start()) {
						task_ = task::stall;
						break;
					}
#else
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

					const uint8_t* ip = tcpudp_env[0].ipaddr;
					utils::format("TCP/IP start: (%d.%d.%d.%d) %u bytes\n")
						% static_cast<int>(ip[0])
						% static_cast<int>(ip[1])
						% static_cast<int>(ip[2])
						% static_cast<int>(ip[3])
						% ramsize;
#endif
					task_ = task::main_init;
				}
				break;

			case task::main_init:
				io_.link_process();

///				socket_.open(3000, false, ip_adrs(192,168,3,7));  // client socket
				socket_.open(3000);  // server socket

				task_ = task::main_loop;
				break;

			case task::main_loop:
				io_.link_process();


				if(link_interval_ >= 100) {
					io_.polling_link_status();
					link_interval_ = 0;
				}
				++link_interval_;


				if(!io_.get_stat().link_) {
					task_ = task::wait_link;
				}


				socket_.service();
				{
					char tmp[64 + 1];
					int ret = socket_.recv(tmp, sizeof(tmp) - 1);
					if(ret > 0) {
						tmp[ret] = 0;
						utils::format("%s\n") % tmp;
						socket_.send(tmp, ret);
					}
				}

				break;

			case task::stall:
				{
					static uint32_t count = 0;
					if(count >= 100) {
						utils::format("Stall net_core\n");
						count = 0;
					}
					++count;
				}
				break;

			default:
				break;
			}
		}
	};
}
