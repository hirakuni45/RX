#pragma once
//=====================================================================//
/*!	@file
	@brief	ethernet_client class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ethernet.hpp"
#include "ethernet_base.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet_client class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ethernet_client : public ethernet_base {

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ethernet_client(ethernet& e) : ethernet_base(e) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  デストラクター
		*/
		//-----------------------------------------------------------------//
		virtual ~ethernet_client() {
			stop();
			end();
		}


		/// timeout [ms]
		int connect(const ip_address& ip, uint16_t port, int32_t timeout = 3000);


///		int connect(const uint8_t* host, uint16_t port, int32_t timeout = 3000);


		//-----------------------------------------------------------------//
		/*!
			@brief  停止
		*/
		//-----------------------------------------------------------------//
        void stop()
		{
///			while(tcp_sht_cep(ARDUINO_TCP_CEP) != E_OK) {
			while(tcp_sht_cep(get_cepid()) != E_OK) {
				delay(1);
			}
			tcp_cls_cep(get_cepid(), TMO_FEVR);
			ethernet::CEP& cep = at_ethernet().at_cep(get_cepid());
			cep.call_flag = false;
		}
	};
}








