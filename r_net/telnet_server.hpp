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

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  telnet_server class テンプレート
		@param[in]	SEND_SIZE	送信、一時バッファサイズ
		@param[in]	RECV_SIZE	受信、一時バッファサイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t SEND_SIZE = 256, uint32_t RECV_SIZE = 1024>
	class telnet_server {


	private:
		// デバッグ以外で出力を無効にする
#ifdef HTTP_DEBUG
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
			main,
			disconnect_delay,
			disconnect,
		};
		task		task_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		telnet_server(ethernet& e) : eth_(e), telnet_(e), task_(task::none) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  スタート
			@param[in]	server_name	サーバー名
		*/
		//-----------------------------------------------------------------//
		void start(const char* server_name)
		{
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


			default:
				break;
			}
		}

	};
}

