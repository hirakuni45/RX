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
			@brief  サービス（定期的に呼び出す）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
///			int ercd = tcp_read_stat(ARDUINO_TCP_CEP);
			int ercd = tcp_read_stat(get_cepid());
			ethernet::CEP& cep = at_ethernet().at_cep(get_cepid());
#if defined(ETHER_DEBUG)
			int cfg = cep.call_flag;
			utils::format("ethernet_server::available():tcp_read_stat() = %d, call_flag: %d\n") % ercd;
#endif
//			if(ercd == T4_TCPS_CLOSED && ethernet_.get_tcp_acp_cep_call_flg() == 0) {

			if(ercd == T4_TCPS_CLOSED && !cep.call_flag) {
///				ercd = tcp_acp_cep(ARDUINO_TCP_CEP, ARDUINO_TCP_CEP, &ethernet_.cep[0].dst_addr, TMO_NBLK);
				ercd = tcp_acp_cep(get_cepid(), get_cepid(), &cep.dst_addr, TMO_NBLK);
#if defined(ETHER_DEBUG)
				utils::format("ethernet_server::available():tcp_acp_cep(TMO_NBLK) = %d") % ercd;
				if(ercd == E_WBLK){
					utils::format(", E_WBLK(success)\n");
				} else {
					utils::format("fail: %d\n") % ercd;
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
