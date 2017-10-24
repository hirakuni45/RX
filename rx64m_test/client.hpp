#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 client クラス
	@copyright Copyright 2017 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"

#include "r_net/ethernet_client.hpp"
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

		net::ethernet_client	client_;

		typedef utils::basic_format<net::ether_string<net::ethernet::format_id::client0, 2048> > format;

		enum class recv_task {
			idle,
			sync_time,
			sample_put,
		};
		recv_task	recv_task_;

		enum class send_task {
			idle,
			req_connect,
			wait_req_connect,
			wait_connect,
			make_form,
			url_decode,
			send_data,
			disconnect,
			sync_close,
		};
		send_task	send_task_;

		net::ip_address		ip_;

		uint16_t	port_;
		uint32_t	delay_;
		uint32_t	timeout_;
		uint32_t	re_connect_cnt_;

		time_t		time_org_;
		time_t		time_ref_;
		time_t		time_ofs_;
		time_t		time_;

		uint32_t	idle_count_;

		struct tm	tm_;

		static const uint32_t BUF_SIZE = 64;

		typedef utils::fixed_fifo<sample_t, BUF_SIZE> FIFO;
		FIFO	fifo_;

		char		form_[1024];
		char		data_[2048];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		client(net::ethernet& eth) : client_(eth, PORT),
			recv_task_(recv_task::idle), send_task_(send_task::idle),
#ifdef SEEDA
			ip_(192, 168, 1, 3),
#else
			ip_(192, 168, 3, 7),
#endif
			port_(PORT),
			delay_(0), timeout_(0), re_connect_cnt_(0),
			time_org_(0), time_ref_(0), time_ofs_(0), time_(0), idle_count_(0) { }


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
			recv_task_ = recv_task::sync_time;
			send_task_ = send_task::req_connect;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  動作状態
			@return idle では無い場合[true」
		*/
		//-----------------------------------------------------------------//
		bool probe() const
		{
			if(send_task_ == send_task::req_connect) return false;
			if(send_task_ == send_task::wait_req_connect) return false;
			if(send_task_ == send_task::wait_connect) return false;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	cycle	サービス・サイクル（通常１００Ｈｚ）
		*/
		//-----------------------------------------------------------------//
		void service(uint32_t cycle)
		{
			++idle_count_;

			switch(recv_task_) {
			case recv_task::idle:
				time_org_ = get_time();
				break;

			case recv_task::sync_time:
				{
					const sample_data& smd = get_sample_data();
					if(time_ref_ != smd.time_) {
						time_ref_ = smd.time_;
						recv_task_ = recv_task::sample_put;
					}
				}
				break;

			case recv_task::sample_put:
				{
					if((BUF_SIZE - 1 - fifo_.length()) < 8) { // スペースが無い場合
						break;
					}
					const sample_data& smd = get_sample_data();
					for(int i = 0; i < 8; ++i) {
						fifo_.put(smd.smp_[i]);
					}
					recv_task_ = recv_task::sync_time;
				}
				break;
			}

			switch(send_task_) {

			case send_task::idle:
				break;

			case send_task::req_connect:
				if(client_.connect(ip_, port_, TMO_NBLK)) {
					re_connect_cnt_ = 0;
					timeout_ = 5 * cycle;  // 再接続待ち時間
					send_task_ = send_task::wait_connect;
				} else {
					timeout_ = 1 * cycle;
					send_task_ = send_task::wait_req_connect;
				}
				break;

			case send_task::wait_req_connect:
				if(timeout_ > 0) {
					--timeout_;
				} else {
					send_task_ = send_task::req_connect;
				}
				break;

			case send_task::wait_connect:
				if(!client_.connected()) {
					if(timeout_ > 0) {
						--timeout_;
					} else {
						++re_connect_cnt_;
						auto st = client_.get_ethernet().get_stat(client_.get_cepid());
///						debug_format("TCP Client re_connect(%d): status: %d, desc(%d)\n")
///							% re_connect_cnt_ % static_cast<int>(st) % client_.get_cepid();
						// 接続しないので、「re_connect」要求を出してみる
						// ※ re_connect では、タイムアウト（１０分）を無効にする。
						client_.re_connect(ip_, port_);
						timeout_ = 5 * cycle;  // 再接続待ち時間
					}
				} else {
///					debug_format("[%d] [%d] ") % get_time() % (time_ - time_ofs_ + time_org_);
					debug_format("Start SEEDA03 Client: %s port(%d), fd(%d)\n")
						% ip_.c_str() % port_ % client_.get_cepid();
					format::chaout().set_fd(client_.get_cepid());
					// 以前接続してから、4 秒以上、の「間」がある場合、設定初期化
					if(idle_count_ > (cycle * 4)) {
						fifo_.clear();
/// utils::format("Reset fifo\n");
						time_org_ = get_time();
						time_ofs_ = time_ref_;
						time_     = time_ref_;
					}
					send_task_ = send_task::make_form;
				}
				break;

			case send_task::make_form:
				if(fifo_.length() < 8) {
					break;
				} 
				for(int ch = 0; ch < 8; ++ch) {
					const auto& smd = fifo_.get_at();
					if(ch == 0) {
						time_t t = time_ - time_ofs_ + time_org_;
						struct tm* m = localtime(&t);
						tm_ = *m;
						utils::sformat("%04d/%02d/%02d,%02d:%02d:%02d", form_, sizeof(form_))
							% static_cast<uint32_t>(tm_.tm_year + 1900)
							% static_cast<uint32_t>(tm_.tm_mon + 1)
							% static_cast<uint32_t>(tm_.tm_mday)
							% static_cast<uint32_t>(tm_.tm_hour)
							% static_cast<uint32_t>(tm_.tm_min)
							% static_cast<uint32_t>(tm_.tm_sec);
						++time_;
					}
					utils::sformat(",", form_, sizeof(form_), true);
					smd.make_csv2(form_, sizeof(form_), true);
					fifo_.get_go();
				}
				utils::sformat("\n", form_, sizeof(form_), true);
				send_task_ = send_task::url_decode;
				break;

			case send_task::url_decode:
				utils::str::url_decode_to_str(form_, data_, sizeof(data_)); 
				send_task_ = send_task::send_data;
				break;

			case send_task::send_data:
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
				send_task_ = send_task::disconnect;
				break;
			
			case send_task::disconnect:
				client_.stop();
				timeout_ = 0;
				send_task_ = send_task::sync_close;
				break;

			case send_task::sync_close:
				if(timeout_ > 0) {
					--timeout_;
				} else {
					idle_count_ = 0;
					debug_format("Client disconnected: %s\n") % ip_.c_str();
					send_task_ = send_task::req_connect;
				}
				break;
			}
		}
	};
}
