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
		@param[in]	ETHERNET	イーサーネット・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHERNET>
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

		static const uint32_t CLIENT_RE_CONNECT_TIME = 500;	///< クライアント再接続のインターバル

	private:

		ETHERNET&	eth_;

		enum class task {
			idle,
			open,
			connect,

			send,
			recv,

			close,

			wait,
			halt,
		};

		ip_adrs		ip_;

		type		type_;
		uint16_t	port_;
		task		task_;

		uint8_t		send_buff_[4096];
		uint8_t		recv_buff_[4096];
		uint32_t	desc_;

		uint32_t	wait_;
		uint32_t	loop_;

		uint32_t	data_len_;

		void reverse_(char* ptr, uint32_t len)
		{
			for(uint32_t i = 0; i < len / 2; ++i) {
				std::swap(ptr[i], ptr[len - 1 - i]);
			}
		}


		int send_(uint32_t send_len, bool server)
		{
			auto& ipv4 = eth_.at_ipv4();
			auto& tcp  = ipv4.at_tcp();

			int loop = loop_ / 2;

			char tmp[send_len + 1];
			for(uint32_t i = 0; i < send_len; ++i) { tmp[i] = 0x20 + (rand() & 63); }

			int len = tcp.send(desc_, tmp, send_len);
			if(len < 0) return -1;

			tmp[len] = 0;
			utils::format("TCP Test (%d)Send (%s):  '%s' %d bytes desc(%d)\n")
				% loop % (server ? "Server" : "Client") % tmp % len % desc_;

			return len;
		}

		int recv_(uint32_t recv_len, bool server)
		{
			auto& ipv4 = eth_.at_ipv4();
			auto& tcp  = ipv4.at_tcp();

			int loop = loop_ / 2;

			char tmp[recv_len + 1];
			int len = tcp.recv(desc_, tmp, recv_len);
			if(len <= 0) return len;

			tmp[len] = 0;
			utils::format("TCP Test (%d)Recv (%s):  '%s' %d bytes desc(%d)\n")
				% loop % (server ? "Server" : "Client") % tmp % len % desc_;

#if 0
			reverse_(tmp, len);

					len *= 5;
					len /= 7;
					tmp[len] = 0;
					if(tcp.send(desc_, tmp, len) < 0) return false;

					utils::format("Test TCP Send %s (%d): '%s', %d\n")
						% (server ? "Server" : "Client") % desc_ % tmp % len;
				} else if(len < 0) {
					return false;
				}
			}
#endif
			return len;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth	イーサーネット参照
		*/
		//-----------------------------------------------------------------//
		test_tcp(ETHERNET& eth) : eth_(eth), ip_(), type_(type::idle), port_(3000), task_(task::idle), desc_(0),
		  wait_(0), loop_(0), data_len_(20) { }


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
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			auto& ipv4 = eth_.at_ipv4();
			auto& tcp  = ipv4.at_tcp();

			bool server = false;
			bool send_first = false;
			switch(type_) {
			case type::server_send_first:
				server = true;
				send_first = true;
				break;
			case type::server_recv_first:
				server = true;
				send_first = false;
				break;
			case type::client_send_first:
				server = false;
				send_first = true;
				break;
			case type::client_recv_first:
				server = false;
				send_first = false;
				break;
			default:
				break;
			}

			switch(task_) {
			case task::idle:
				if(type_ != type::idle) {
					task_ = task::open;
				}
				break;

			case task::open:
				{
					bool err = false;
					if(tcp.open(send_buff_, sizeof(send_buff_),
						recv_buff_, sizeof(recv_buff_), desc_)) {
						if(tcp.start(desc_, ip_, port_, server)) {
							utils::format("TCP Test Open (%d): %s\n")
								% desc_ % (server ? "Server" : "Client");
							task_ = task::connect;
							wait_ = CLIENT_RE_CONNECT_TIME;
						} else {
							err = true;
						}
					} else {
						err = true;
					}
					if(err) {
						wait_ = 500;
						task_ = task::wait;
					}
				}
				break;

			case task::connect:
				if(tcp.connected(desc_)) {
					utils::format("TCP Test Connection (%s)\n")
						% (server ? "Server" : "Client");
					if(send_first) {
						task_ = task::send;
					} else {
						task_ = task::recv;
					}
				} else {
					if(!server) {
						if(wait_ > 0) {
							--wait_;
						} else {
							tcp.re_connect(desc_);
							wait_ = CLIENT_RE_CONNECT_TIME;
						}
					}
				}
				break;

			case task::send:
				if(!tcp.connected(desc_) || tcp.is_fin(desc_)) {
					utils::format("TCP Test Connection: OFF\n");
					task_ = task::close;
				} else {
					int len = send_(data_len_, server);
					if(len > 0) {
						++loop_;
						task_ = task::recv;
					}
				}
				break;

			case task::recv:
				if(!tcp.connected(desc_) || tcp.is_fin(desc_)) {
					utils::format("TCP Test Connection: OFF\n");
					task_ = task::close;
				} else {
					int len = recv_(data_len_, server);
					if(len > 0) {
						++loop_;
						task_ = task::send;
					}
				}
				break;

			case task::close:
				tcp.close(desc_);
				utils::format("TCP Test Close (%d)\n") % desc_;
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
