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

		enum class task {
			idle,
			open,
			main,
			close,
			wait,
		};

		task		task_;
		uint32_t	desc_;
		uint32_t	wait_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		test_tcp() : task_(task::idle), desc_(0), wait_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	eth	イーサーネット・コンテキスト
			@param[in]	server	サーバーの場合「true」
		*/
		//-----------------------------------------------------------------//
		template <class ETHERNET>
		void service(ETHERNET& eth, bool server)
		{
			auto& ipv4 = eth.at_ipv4();
			auto& tcp  = ipv4.at_tcp();

			switch(task_) {
			case task::idle:
				task_ = task::open;
				break;

			case task::open:
				{
					auto state = tcp.open(ip_adrs(192,168,3,7), 3000, server, desc_);
					if(state != net_state::OK) {
						utils::format("Test TCP Open (%s): %s\n")
							% get_state_str(state) % (server ? "Server" : "Client");
						wait_ = 500;
						task_ = task::wait;
					} else {
						task_ = task::main;
					}
				}
				break;

			case task::main:
				{
					char tmp[256];
					int len = tcp.recv(desc_, tmp, sizeof(tmp));
					if(len > 0) {
						tmp[len] = 0;
						utils::format("Test TCP Recv (%d): '%s', %d\n") % desc_ % tmp % len;

						tcp.send(desc_, tmp, len);
						utils::format("Test TCP Send (%d): '%s', %d\n") % desc_ % tmp % len;
					}

					if(!tcp.connection(desc_)) {
						task_ = task::close;
					}
				}
				break;

			case task::close:
				tcp.close(desc_);
				utils::format("Test TCP Close (%d)\n") % desc_;
				wait_ = 10;
				task_ = task::wait;
				break;

			case task::wait:
				if(wait_ > 0) {
					--wait_;
				} else {
					task_ = task::open;
				}
				break;

			default:
				break;
			}

		}
	};
}
