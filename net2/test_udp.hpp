#pragma once
//=========================================================================//
/*! @file
    @brief  Test UDP Protocol@n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "udp.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Test UDP プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class test_udp {

		int		desc_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		test_udp() : desc_(-1) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		template <class ETH>
		void service(ETH& eth)
		{
			if(desc_ < 0) {
				auto& ipv4 = eth.at_ipv4();
				auto& udp  = ipv4.at_udp();
				desc_ = udp.open(ip_adrs(192,168,3,7), 3000);
				utils::format("net_main: UDP Open: (%d)\n") % desc_;
			} else {
				auto& ipv4 = eth.at_ipv4();
				auto& udp  = ipv4.at_udp();

				char tmp[256];
				int len = udp.recv(desc_, tmp, sizeof(tmp));
				if(len > 0) {
					tmp[len] = 0;
					utils::format("net_main: UDP Recv: '%s'\n") % tmp;
					udp.send(desc_, tmp, len);
					utils::format("net_main: UDP Send: '%s'\n") % tmp;
					udp.close(desc_);
					utils::format("net_main: UDP Close: (%d)\n") % desc_;
					desc_ = -1;
				}
			}
		}
	};
}
