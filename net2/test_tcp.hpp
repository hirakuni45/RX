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
			connect,
			main,
			close,
			wait,

			halt,
		};

		task		task_;
		uint32_t	desc_;
		uint32_t	wait_;

		bool		enable_;
		bool		first_send_;

		void reverse_(char* ptr, uint32_t len)
		{
			for(uint32_t i = 0; i < len / 2; ++i) {
				std::swap(ptr[i], ptr[len - 1 - i]);
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		test_tcp() : task_(task::idle), desc_(0), wait_(0), enable_(false), first_send_(true) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  テスト許可
			@param[in]	ena	不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable(bool ena = true) { enable_ = ena; }


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
				if(enable_) {
					task_ = task::open;
				}
				break;

			case task::open:
				{
					ip_adrs adrs;
					if(!server) {  // Client の場合の接続先（サーバーのアドレス）
						adrs.set(192,168,3,7);
					}
					auto state = tcp.open(adrs, 3000, server, desc_);
					if(state == net_state::OK) {
						utils::format("Test TCP Open (%d): %s\n")
							% desc_ % (server ? "Server" : "Client");
						task_ = task::connect;
					} else {
						wait_ = 500;
						task_ = task::wait;
					}
				}
				break;

			case task::connect:
				if(tcp.connected(desc_)) {
					task_ = task::main;
				}
				break;

			case task::main:
				if(!tcp.connected(desc_)) {
					utils::format("Test TCP Connection: OFF\n");
					task_ = task::close;
				} else {
					char tmp[256];
					if(first_send_) {
						uint32_t send_len = 20;
						for(uint32_t i = 0; i < send_len; ++i) { tmp[i] = 0x20 + (rand() & 63); }
						int len = tcp.send(desc_, tmp, send_len);
						tmp[send_len] = 0;
						utils::format("Test TCP Send (%d): '%s', %d\n") % desc_ % tmp % len;

					} else {
						int len = tcp.recv(desc_, tmp, sizeof(tmp));
						if(len > 0) {
							tmp[len] = 0;
							utils::format("Test TCP Recv (%d): '%s', %d\n") % desc_ % tmp % len;

							reverse_(tmp, len);

							len *= 5;
							len /= 7;
							tmp[len] = 0;
							tcp.send(desc_, tmp, len);
							utils::format("Test TCP Send (%d): '%s', %d\n") % desc_ % tmp % len;
						}
					}
				}
				break;

			case task::close:
				tcp.close(desc_);
				utils::format("Test TCP Close (%d)\n") % desc_;
				wait_ = 5;
				task_ = task::wait;
				break;

			case task::wait:
				if(wait_ > 0) {
					--wait_;
				} else {
					task_ = task::idle;
				}
				break;

			case task::halt:
				break;

			default:
				break;
			}

		}
	};
}
