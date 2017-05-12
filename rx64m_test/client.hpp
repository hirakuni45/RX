#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 client クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "GR/core/ethernet_client.hpp"
#include "sample.hpp"

#include "main.hpp"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  client クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class client {

		net::ethernet_client	client_;

		enum class task {
			startup,
			connect,
			main_loop,
			disconnect,
		};

		task		task_;

		net::ip_address		ip_;

		uint16_t	port_;
		uint32_t	delay_;
		uint32_t	timeout_;

		time_t		time_;

		typedef utils::basic_format<net::eth_chaout> format;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		client(net::ethernet& eth) : client_(eth), task_(task::startup),
#ifdef SEEDA
			ip_(192, 168, 1, 3),
#else
			ip_(192, 168, 3, 7),
#endif
			port_(3000),
			delay_(0), timeout_(0), time_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  IP アドレスの取得
			@return IP アドレス
		*/
		//-----------------------------------------------------------------//
		const net::ip_address& get_ip() const { return ip_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  IP アドレスの参照
			@return IP アドレス
		*/
		//-----------------------------------------------------------------//
		net::ip_address& at_ip() { return ip_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートの取得
			@return ポート
		*/
		//-----------------------------------------------------------------//
		uint16_t get_port() const { return port_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートの設定
			@param[in]	port	ポート
		*/
		//-----------------------------------------------------------------//
		void set_port(uint16_t port) { port_ = port; }


		//-----------------------------------------------------------------//
		/*!
			@brief  接続開始
		*/
		//-----------------------------------------------------------------//
		void start_connect()
		{
			task_ = task::connect;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  再接続
		*/
		//-----------------------------------------------------------------//
		void restart()
		{
			task_ = task::disconnect;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			time_t t;
			switch(task_) {

			case task::startup:
				break;

			case task::connect:
				if(client_.connect(ip_, port_, TMO_NBLK)) {
					utils::format("Start SEEDA03 Client: %s port(%d), fd(%d)\n")
						% ip_.c_str() % port_ % client_.get_cepid();
					timeout_ = 5 * 100;  // 5 sec
					task_ = task::main_loop;
					time_ = get_time();
				}
				break;

			case task::main_loop:
				if(!client_.connected()) {
					break;
				}
				t = get_time();
				if(time_ == t) break;
				time_ = t;
				{
					auto fd = client_.get_cepid();
					{
						char s[64];
						int n = disp_time(t, s, sizeof(s));
						s[n] = '\n';
						s[n + 1] = 0;
						char tmp[128];
						utils::str::url_decode_to_str(s, tmp, sizeof(tmp)); 

						format("POST /api/?val=%s", fd) % tmp;
					}
					for(int ch = 0; ch < 8; ++ch) {
						const auto& t = get_sample(ch);
						char s[256];
						t.make_csv("\n", s, sizeof(s));
						char tmp[512];
						utils::str::url_decode_to_str(s, tmp, sizeof(tmp)); 
						format("%s", fd) % tmp;
					}
					format(" HTTP/1.1\n", fd);
					format("Host: %d.%d.%d.%d\n", fd)
						% static_cast<int>(ip_[0])
						% static_cast<int>(ip_[1])
						% static_cast<int>(ip_[2])
						% static_cast<int>(ip_[3]);
					format("Content-Type: application/x-www-form-urlencoded\n", fd);
					format("User-Agent: SEEDA03 Post Client\n", fd);
					format("Connection: close\n\n", fd);
				}
				client_.stop();
				task_ = task::connect;
				break;
			
			case task::disconnect:
				client_.stop();
				utils::format("Client disconnected: %s\n") % ip_.c_str();
				task_ = task::connect;
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポスト
		*/
		//-----------------------------------------------------------------//
		void post(const sample_t& t)
		{

		}


	};
}
