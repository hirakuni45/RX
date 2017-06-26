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

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  net_main テンプレート・クラス
		@param[in]	ETHER_IO	インサーネット・ドライバー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHER_IO>
	class net_main {

		enum class task : uint8_t {
			halt,		// Halt !!!
			wait_link,	// リンクアップを待つ
			wait_dhcp,	// DHCP IP アドレスの取得を待つ
			setup_tcpudp,
			main_init,	// メイン初期化
			main_loop,	// メインループ
			stall,		// ストール
		};

		ETHER_IO&	eth_;

		typedef dhcp_client<ETHER_IO> DHCP;
		DHCP		dhcp_;

		task		task_;

		uint8_t		link_interval_;

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
		net_main(ETHER_IO& io) : eth_(io), dhcp_(io),
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
			bool ret = eth_.open(mac);
			if(ret) {
				utils::format("Ether open OK\n");
///				memcpy(&_myethaddr[0][0], mac, 6);				
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
						eth_.polling_link_status();
						link_interval_ = 0;
						utils::format("Link wait loop\n");
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
//				memcpy(tcpudp_env[0].ipaddr,   ip_.get(),   4);
//				memcpy(tcpudp_env[0].maskaddr, mask_.get(), 4);
//				memcpy(tcpudp_env[0].gwaddr,   gw_.get(),   4);
//				memcpy(dnsaddr1, info.dnsaddr, 4);
//				memcpy(dnsaddr2, info.dnsaddr2, 4);
				break;

			case task::setup_tcpudp:
#if 0
				if(!socket<ETHER_IO>::start()) {
					task_ = task::stall;
				} else {
					task_ = task::main_init;
				}
#else
				task_ = task::main_init;
#endif
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


		//-----------------------------------------------------------------//
		/*!
			@brief  リンクを確認する
			@return 「true」なら、リンク
		*/
		//-----------------------------------------------------------------//
		bool check_link() const { return task_ == task::main_loop; }
	};
}
