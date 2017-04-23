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


		//-----------------------------------------------------------------//
		/*!
			@brief  コネクション
			@param[in]	ip		接続先の IP アドレス
			@param[in]	port	接続ポート
			@param[in]	timeout	タイムアウト、単位１０ミリ秒（標準で１０秒）
			@return 接続できた場合「１」
		*/
		//-----------------------------------------------------------------//
		int connect(const ip_address& ip, uint16_t port, int32_t timeout = 1000)
		{
			T_IPV4EP adr;
			adr.ipaddr =  (static_cast<uint32_t>(ip[0]) << 24)
						| (static_cast<uint32_t>(ip[1]) << 16)
						| (static_cast<uint32_t>(ip[2]) << 8)
						| (static_cast<uint32_t>(ip[3]));
			adr.portno = port;

			int res = 0;
			if(!connected()) {
				int ercd = tcp_con_cep(get_cepid(), NADR,  &adr, timeout);
				if(ercd == E_OK) {
					res = 1;
				} else if(ercd == E_WBLK) {  // timeout が「TMO_NBLK」の場合
//					if(head_tcb[get_cepid() - 1].req.error == E_OK) ;
					if(head_tcb[get_cepid() - 1].req.stat == _TCP_API_STAT_COMPLETE) {
						res = 1;
					} else {
						res = -1;
					}
				} else {
					res = -1;
				}
			} else {
				res = 1;  /* already connect */
			}
			return res;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  停止
		*/
		//-----------------------------------------------------------------//
        void stop()
		{
			while(tcp_sht_cep(get_cepid()) != E_OK) {
				delay(1);
			}
			tcp_cls_cep(get_cepid(), TMO_FEVR);
			ethernet::CEP& cep = at_ethernet().at_cep(get_cepid());
			cep.call_flag = false;
		}
	};
}








