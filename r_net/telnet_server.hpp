#pragma once
//=====================================================================//
/*!	@file
	@brief	TELNET サーバー・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "ethernet_server.hpp"
#include "common/fixed_fifo.hpp"

#define TELNETS_DEBUG

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  telnet_server class テンプレート
		@param[in]	SEND_SIZE	送信、一時バッファサイズ
		@param[in]	RECV_SIZE	受信、一時バッファサイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t SEND_SIZE, uint32_t RECV_SIZE>
	class telnet_server {


	private:
		// デバッグ以外で出力を無効にする
#ifdef TELNETS_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

		ethernet&		eth_;
		ethernet_server	telnet_;

		enum class task : uint8_t {
			none,
			begin,
			wait,
			main_loop,
			disconnect_delay,
			disconnect,
		};
		task		task_;

		char		server_name_[32];
		uint32_t	count_;
		uint32_t	disconnect_loop_;

		typedef utils::fixed_fifo<char, SEND_SIZE> SEND_FIFO;
		typedef utils::fixed_fifo<char, RECV_SIZE> RECV_FIFO;

		SEND_FIFO	send_;
		RECV_FIFO	recv_;

		void write_()
		{
			char tmp[256];
			uint16_t l = 0;
			while(send_.length() > 0) {
				auto ch = send_.get();
				tmp[l] = ch;
				++l;
				if(l >= sizeof(tmp)) {
					telnet_.write(tmp, l);
					l = 0;
				}
			}
			if(l > 0) {
				telnet_.write(tmp, l);
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		telnet_server(ethernet& e) : eth_(e), telnet_(e), task_(task::none),
			server_name_{ 0 }, count_(0), disconnect_loop_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  スタート
			@param[in]	server_name	サーバー名
		*/
		//-----------------------------------------------------------------//
		void start(const char* server_name)
		{
			std::strncpy(server_name_, server_name, sizeof(server_name_) - 1);

			count_ = 0;
			disconnect_loop_ = 0;

			task_ = task::begin;

			debug_format("TELNET Server: SEND_BUFF: %d, RECV_BUFF: %d\n") % SEND_SIZE % RECV_SIZE;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	cycle	サービス・サイクル（通常１００Ｈｚ）
			@param[in]	port	TELNET ポート番号（通常２３番）
		*/
		//-----------------------------------------------------------------//
		void service(uint32_t cycle, uint16_t port = 23)
		{
			switch(task_) {
			case task::none:
				break;

			case task::begin:
				telnet_.begin(port);
				debug_format("Start TELNET Server: '%s' port(%d), fd(%d)\n")
					% eth_.get_local_ip().c_str()
					% static_cast<int>(telnet_.get_port()) % telnet_.get_cepid();
				task_ = task::wait;
				break;

			case task::wait:
				if(telnet_.connected()) {
					debug_format("TELNET Server: New connected, from: %s\n") % telnet_.get_from_ip().c_str();
					++count_;
					task_ = task::main_loop;
				}
				break;

			case task::main_loop:
				if(telnet_.connected()) {
					if(telnet_.available() > 0) {  // リードデータがあるか？
						char tmp[RECV_SIZE];
						int len = telnet_.read(tmp, sizeof(tmp));
//						recv_.length()
					}
					write_();
				} else {
					task_ = task::disconnect_delay;
					disconnect_loop_ = 10;
				}
				break;

			case task::disconnect_delay:
				if(disconnect_loop_ > 0) {
					--disconnect_loop_;
				} else {
					task_ = task::disconnect;
				}
				break;

			case task::disconnect:
			default:
				telnet_.stop();
				debug_format("TELNET Server: disconnected\n");
				task_ = task::begin;
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  出力
			@param[in]	text	出力文字列
		*/
		//-----------------------------------------------------------------//
		void putch(char ch)
		{
			if(ch == '\n') {
				putch('\r');
			}
			if(task_ == task::main_loop) {
				if((send_.size() - send_.length()) <= 2) {
					write_();
				}
				send_.put(ch);
//				if(ch == '\r') {					
//				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  出力
			@param[in]	text	出力文字列
		*/
		//-----------------------------------------------------------------//
		void puts(const char* text)
		{
			if(text == nullptr) return;

			if(task_ == task::main_loop) {
				char ch;
				while((ch = *text++) != 0) {
					putch(ch);
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  入力文字数取得
			@return 入力文字数
		*/
		//-----------------------------------------------------------------//
		uint32_t length() const
		{
			return 0;
		}
	};
}

