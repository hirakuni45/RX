#pragma once
//=====================================================================//
/*!	@file
	@brief	ethernet_server class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ethernet.hpp"
#include "ethernet_base.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet_server class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ethernet_server : public ethernet_base {

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ethernet_server(ethernet& e) : ethernet_base(e) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  デストラクター
		*/
		//-----------------------------------------------------------------//
		virtual ~ethernet_server() {
			stop();
			end();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  接続先を取得
			@return 接続先
		*/
		//-----------------------------------------------------------------//
		const ip_address& get_from_ip() const {
			const ethernet::CEP& cep = get_ethernet().get_cep(get_cepid());
			uint32_t ipw = cep.dst_addr.ipaddr;
			static ip_address ip((ipw >> 24) & 255, (ipw >> 16) & 255, (ipw >> 8) & 255, ipw & 255);
			return ip;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（定期的に呼び出す）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			TCP_API_STAT ercd = tcp_read_stat(get_cepid());
			ethernet::CEP& cep = at_ethernet().at_cep(get_cepid());
#if defined(ETHER_DEBUG)
			int cfg = cep.call_flag;
			utils::format("ethernet_server::available():tcp_read_stat() = %d, call_flag: %d\n") % ercd;
#endif
			if(ercd == TCP_API_STAT_CLOSED && !cep.call_flag) {
				int ret = tcp_acp_cep(get_cepid(), get_cepid(), &cep.dst_addr, TMO_NBLK);
#if defined(ETHER_DEBUG)
				utils::format("ethernet_server::available():tcp_acp_cep(TMO_NBLK) = %d") % ret;
				if(ret == E_WBLK){
					utils::format(", E_WBLK(success)\n");
				} else {
					utils::format("fail: %d\n") % ret;
				}
#endif
				// one time call flag is on
				cep.call_flag = true;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  停止
		*/
		//-----------------------------------------------------------------//
        void stop()
		{
			tcp_cls_cep(get_cepid(), TMO_FEVR);
			ethernet::CEP& cep = at_ethernet().at_cep(get_cepid());
			cep.call_flag = false;
		}
	};
}
