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

		enum class task {
			idle,
			open,
			main,
			close,
			wait,
		};

		task		task_;
		uint32_t	desc_;
		uint32_t	loop_;
		uint32_t	wait_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		test_udp() : task_(task::idle), desc_(0), loop_(0), wait_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	eth	イーサーネット・コンテキスト
		*/
		//-----------------------------------------------------------------//
		template <class ETHERNET>
		void service(ETHERNET& eth)
		{
			auto& ipv4 = eth.at_ipv4();
			auto& udp  = ipv4.at_udp();

			switch(task_) {
			case task::idle:
				task_ = task::open;
				break;

			case task::open:
				{
					auto state = udp.open(ip_adrs(192,168,3,7), 3000, desc_);
					if(state != net_state::OK) {
						utils::format("Test UDP Open: (%s)\n") % desc_;
						wait_ = 300;
						task_ = task::wait;
					} else {
						task_ = task::main;
					}
				}
				break;

			case task::main:
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
							loop_ = 0;
							task_ = task::close;
						}
					}
				}
				break;

			case task::close:
				udp.close(desc_);
				utils::format("Test UDP Close: (%d)\n") % desc_;
				task_ = task::wait;
				wait_ = 50;
				break;

			case task::wait:
				if(wait_ > 0) {
					--wait_;
				} else {
					task_ = task::idle;
				}
				break;
			}
		}
	};
}
