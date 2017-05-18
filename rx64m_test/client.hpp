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
					task_ = task::disconnect;
					break;
				}
				t = get_time();
				if(time_ == t) break;
				time_ = t;
				{
					struct tm *m = localtime(&t);
					char data[1024];
					uint32_t l = 0;
					l += (utils::format("%04d/%02d/%02d,%02d:%02d:%02d", &data[l], sizeof(data) - l)
						% static_cast<uint32_t>(m->tm_year + 1900)
						% static_cast<uint32_t>(m->tm_mon + 1)
						% static_cast<uint32_t>(m->tm_mday)
						% static_cast<uint32_t>(m->tm_hour)
						% static_cast<uint32_t>(m->tm_min)
						% static_cast<uint32_t>(m->tm_sec)).get_length();
					for(int ch = 0; ch < 8; ++ch) {
						const auto& smp = get_sample(ch);
						data[l] = ',';
						++l;
						l += smp.make_csv2(&data[l], sizeof(data) - l);
					}
					data[l] = '\n';
					++l;
					data[l] = 0;
					++l;

					char tmp[2048];
					utils::str::url_decode_to_str(data, tmp, sizeof(tmp)); 

					auto fd = client_.get_cepid();
					format("POST /api/?val=%s HTTP/1.1\n", fd) % tmp;
					format("Host: %d.%d.%d.%d\n", fd)
						% static_cast<int>(ip_[0])
						% static_cast<int>(ip_[1])
						% static_cast<int>(ip_[2])
						% static_cast<int>(ip_[3]);
					format("Content-Type: application/x-www-form-urlencoded\n", fd);
					format("User-Agent: SEEDA03 Post Client\n", fd);
					format("Connection: close\n\n", fd);
				}
				task_ = task::disconnect;
				break;
			
			case task::disconnect:
				client_.stop();
				utils::format("Client disconnected: %s\n") % ip_.c_str();
				task_ = task::connect;
				break;
			}
		}
	};
}
