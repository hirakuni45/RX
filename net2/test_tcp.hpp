#pragma once
//=========================================================================//
/*! @file
    @brief  Test TCP Protocol@n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "udp.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Test TCP プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class test_tcp {

		int		desc_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		test_tcp() : desc_(-1) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		template <class ETH>
		void service(ETH& eth, bool server)
		{
			if(desc_ < 0) {
				auto& ipv4 = eth.at_ipv4();
				auto& tcp  = ipv4.at_tcp();
				desc_ = tcp.open(ip_adrs(192,168,3,7), 3000, server);
				utils::format("Test TCP Open: (%d) %s\n")
					% desc_ % (server ? "Server" : "Client");
			} else {
				auto& ipv4 = eth.at_ipv4();
				auto& tcp  = ipv4.at_tcp();

				char tmp[256];
				int len = tcp.recv(desc_, tmp, sizeof(tmp));
				if(len > 0) {
					tmp[len] = 0;
					utils::format("Test TCP Recv(%d): '%s'\n") % len % tmp;
					tcp.send(desc_, tmp, len);
					utils::format("Test TCP Send(%d): '%s'\n") % len % tmp;
//					tcp.close(desc_);
//					utils::format("net_main: TCP Close: (%d)\n") % desc_;
//					desc_ = -1;
				}
			}
		}
	};
}
