#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 client クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"
#include "sample.hpp"

// #define CLIENT_DEBUG

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  client クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class client {

#ifdef CLIENT_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

		static const uint16_t PORT = 3000;	///< クライアント・ポート

		NET_MAIN::ETHERNET&	eth_;

		uint32_t	desc_;

		typedef utils::basic_format<net::desc_string<net::format_id::client0, 1024> > format;

		enum class task {
			idle,
			startup,
			connect,
			sync_connect,
			sync_time,
			make_form,
			url_decode,
			send_data,
			disconnect,
		};

		task		task_;

		net::ip_adrs	ip_;

		uint16_t	port_;
		uint32_t	delay_;
		uint32_t	timeout_;

		time_t		time_;

		struct tm	tm_;

		char		form_[1024];
		char		data_[2048];

		char		buff_[1024];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		client(NET_MAIN::ETHERNET& eth) : eth_(eth), desc_(0), task_(task::idle),
#ifdef SEEDA
			ip_(192, 168, 1, 3),
#else
			ip_(192, 168, 3, 7),
#endif
			port_(PORT),
			delay_(0), timeout_(0), time_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  IP アドレスの取得
			@return IP アドレス
		*/
		//-----------------------------------------------------------------//
		const net::ip_adrs& get_ip() const { return ip_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  IP アドレスの参照
			@return IP アドレス
		*/
		//-----------------------------------------------------------------//
		net::ip_adrs& at_ip() { return ip_; }


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

			auto& ipv4 = eth_.at_ipv4();
			auto& tcp  = ipv4.at_tcp();

			switch(task_) {

			case task::idle:
				break;

			case task::startup:
				break;

			case task::connect:
				if(tcp.open(ip_, port_, false, desc_) == net::net_state::OK) {
					debug_format("Start SEEDA03 Client: %s port(%d), fd(%d)\n")
						% ip_.c_str() % port_ % desc_;
					timeout_ = 5 * 100;  // 5 sec
					time_ = get_sample_data().time_;
					format::chaout().set_desc(desc_);
					task_ = task::sync_connect;
				}
				break;

			case task::sync_connect:
				if(tcp.connected(desc_)) {
					task_ = task::sync_time;
				}
				break;

			case task::sync_time:
				if(!tcp.connected(desc_)) {
					task_ = task::disconnect;
					break;
				}
				{
					auto t = get_sample_data().time_;
					if(time_ == t) break;
					time_ = t;
					struct tm* m = localtime(&t);
					tm_ = *m;
					task_ = task::make_form;
				}
				break;

			case task::make_form:
				utils::sformat("%04d/%02d/%02d,%02d:%02d:%02d", form_, sizeof(form_))
					% static_cast<uint32_t>(tm_.tm_year + 1900)
					% static_cast<uint32_t>(tm_.tm_mon + 1)
					% static_cast<uint32_t>(tm_.tm_mday)
					% static_cast<uint32_t>(tm_.tm_hour)
					% static_cast<uint32_t>(tm_.tm_min)
					% static_cast<uint32_t>(tm_.tm_sec);
				{
					const sample_data& smd = get_sample_data();
					for(int ch = 0; ch < 8; ++ch) {
						utils::sformat(",", form_, sizeof(form_), true);
						smd.smp_[ch].make_csv2(form_, sizeof(form_), true);
					}
				}
				utils::sformat("\n", form_, sizeof(form_), true);
				task_ = task::url_decode;
				break;

			case task::url_decode:
				utils::str::url_decode_to_str(form_, data_, sizeof(data_)); 
				task_ = task::send_data;
				break;

			case task::send_data:
				format::chaout().clear();
				format("POST /api/?val=%s HTTP/1.1\n") % data_;
				format("Host: %d.%d.%d.%d\n")
					% static_cast<int>(ip_[0])
					% static_cast<int>(ip_[1])
					% static_cast<int>(ip_[2])
					% static_cast<int>(ip_[3]);
				format("Content-Type: application/x-www-form-urlencoded\n");
				format("User-Agent: SEEDA03 Post Client\n");
				format("Connection: close\n\n");
				format::chaout().flush();
				task_ = task::disconnect;
				break;
			
			case task::disconnect:
				tcp.close(desc_);
				debug_format("Client disconnected: %s\n") % ip_.c_str();
				task_ = task::connect;
				break;
			}
		}
	};
}
