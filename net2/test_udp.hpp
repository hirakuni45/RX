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
		int		loop_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		test_udp() : desc_(-1), loop_(0) { }


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
				utils::format("Test UDP Open: (%d)\n") % desc_;
			} else {
				auto& ipv4 = eth.at_ipv4();
				auto& udp  = ipv4.at_udp();

				if(udp.get_recv_length(desc_) > 0) {
					char tmp[256];
					int len = udp.recv(desc_, tmp, sizeof(tmp));
					if(len > 0) {
						tmp[len] = 0;
						utils::format("Test UDP Recv: '%s'\n") % tmp;
						udp.send(desc_, tmp, len);
						utils::format("Test UDP Send: '%s'\n") % tmp;
						++loop_;
						if(loop_ >= 4) {
							udp.close(desc_);
							utils::format("Test UDP Close: (%d)\n") % desc_;
							desc_ = -1;
							loop_ = 0;
						}
					}
				}
			}
		}
	};
}
