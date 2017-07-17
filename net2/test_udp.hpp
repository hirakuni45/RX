#pragma once
//=========================================================================//
/*! @file
    @brief  Test UDP Protocol
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

		uint8_t		send_buff_[4096];
		uint8_t		recv_buff_[4096];
		uint32_t	desc_;
		uint32_t	loop_;
		uint32_t	wait_;

		bool		enable_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		test_udp() : task_(task::idle), desc_(0), loop_(0), wait_(0), enable_(false) { }


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
		*/
		//-----------------------------------------------------------------//
		template <class ETHERNET>
		void service(ETHERNET& eth)
		{
			auto& ipv4 = eth.at_ipv4();
			auto& udp  = ipv4.at_udp();

			switch(task_) {
			case task::idle:
				if(enable_) {
					task_ = task::open;
				}
				break;

			case task::open:
				{
					bool err = false;
					if(udp.open(send_buff_, sizeof(send_buff_),
						recv_buff_, sizeof(recv_buff_), desc_)) {
						if(udp.start(desc_, ip_adrs(192,168,3,7), 3000)) {
							utils::format("Test UDP Open: (%d)\n") % desc_;
							task_ = task::main;
						} else {
							err = true;
						}
					} else {
						err = true;
					}
					if(err) {
						wait_ = 300;
						task_ = task::wait;
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
