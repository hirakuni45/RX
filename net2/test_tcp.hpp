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
		bool	onetime_;
		int		open_delay_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		test_tcp() : desc_(-1), onetime_(true), open_delay_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		template <class ETH>
		void service(ETH& eth, bool server)
		{
			if(!onetime_) return;

			if(desc_ < 0) {
				if(open_delay_ > 0) {
					open_delay_--;
					return;
				}

				auto& ipv4 = eth.at_ipv4();
				auto& tcp  = ipv4.at_tcp();
				desc_ = tcp.open(ip_adrs(192,168,3,7), 3000, server);
				if(desc_ >= 0) {
					utils::format("Test TCP Open (%d): %s\n")
						% desc_ % (server ? "Server" : "Client");
				}
			} else {
				auto& ipv4 = eth.at_ipv4();
				auto& tcp  = ipv4.at_tcp();

				char tmp[256];
				int len = tcp.recv(desc_, tmp, sizeof(tmp));
				if(len > 0) {
					tmp[len] = 0;
					utils::format("Test TCP Recv (%d): '%s', %d\n") % desc_ % tmp % len;

					tcp.send(desc_, tmp, len);
					utils::format("Test TCP Send (%d): '%s', %d\n") % desc_ % tmp % len;

///					tcp.close(desc_);
///					utils::format("Test TCP Close (%d)\n") % desc_;
///					desc_ = -1;

					onetime_ = false;
					open_delay_ = 50;
				}
			}
		}
	};
}
