#pragma once
//=========================================================================//
/*! @file
    @brief  Test TCP Protocol
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
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
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Test TCP テスト・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class type {
			idle,					///< アイドル
			server_send_first,		///< サーバー動作、サーバー側が送信開始
			server_recv_first,		///< サーバー動作、サーバー側が受信開始
			client_send_first,		///< クライアント動作、クライアントが送信開始
			client_recv_first,		///< クライアント動作、クライアントが受信開始
		};

	private:

		enum class task {
			idle,
			open,
			connect,
			main,
			close,
			wait,

			halt,
		};

		ip_adrs		ip_;

		type		type_;
		uint16_t	port_;
		task		task_;
		uint32_t	desc_;
		uint32_t	wait_;

		void reverse_(char* ptr, uint32_t len)
		{
			for(uint32_t i = 0; i < len / 2; ++i) {
				std::swap(ptr[i], ptr[len - 1 - i]);
			}
		}


		template <class ETHERNET>
		void trans_(ETHERNET& eth)
		{
			auto& ipv4 = eth.at_ipv4();
			auto& tcp  = ipv4.at_tcp();

			bool server = false;
			if(type_ == type::server_send_first || type_ == type::server_recv_first) {
				server = true;
			}

			char tmp[256];
			if(type_ == type::server_send_first || type_ == type::client_send_first) {
				uint32_t send_len = 20;
				for(uint32_t i = 0; i < send_len; ++i) { tmp[i] = 0x20 + (rand() & 63); }
				int len = tcp.send(desc_, tmp, send_len);
				tmp[send_len] = 0;
				utils::format("Test TCP Send %s (%d): '%s', %d\n")
					% (server ? "Server" : "Client") % desc_ % tmp % len;
			} else {
				int len = tcp.recv(desc_, tmp, sizeof(tmp));
				if(len > 0) {
					tmp[len] = 0;
					utils::format("Test TCP Recv %s (%d): '%s', %d\n")
						% (server ? "Server" : "Client") % desc_ % tmp % len;

					reverse_(tmp, len);

					len *= 5;
					len /= 7;
					tmp[len] = 0;
					tcp.send(desc_, tmp, len);
					utils::format("Test TCP Send %s (%d): '%s', %d\n")
						% (server ? "Server" : "Client") % desc_ % tmp % len;
				}
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		test_tcp() : ip_(), type_(type::idle), port_(3000), task_(task::idle), desc_(0),
		  wait_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  テスト・タイプの設定
			@param[in]	t	テスト・タイプ
		*/
		//-----------------------------------------------------------------//
		void set_type(type t) { type_ = t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  IP アドレスの設定
			@param[in]	ip	IP アドレス
		*/
		//-----------------------------------------------------------------//
		void set_ip(const ip_adrs& ip) { ip_ = ip; }


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
				if(type_ != type::idle) {
					task_ = task::open;
				}
				break;

			case task::open:
				{
					bool server = false;
					if(type_ == type::server_send_first || type_ == type::server_recv_first) {
						server = true;
					}
					auto state = tcp.open(ip_, port_, server, desc_);
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
					utils::format("Test TCP Connection (%s)\n")
						% (server ? "Server" : "Client");
					task_ = task::main;
				}
				break;

			case task::main:
				if(!tcp.connected(desc_)) {
					utils::format("Test TCP Connection: OFF\n");
					task_ = task::close;
				} else {
					trans_(eth);
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
