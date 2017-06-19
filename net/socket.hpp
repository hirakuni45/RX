#pragma once
//=====================================================================//
/*!	@file
	@brief	ソケット・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

#include "r_t4_rx/src/config_tcpudp.h"
#include "r_socket_rx_if.h"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  socket クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class socket {

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start()
		{
			auto ret = R_SOCKET_Open();
			if(ret < 0) {
				if(ret == -1) {
					utils::format("Socket open memory empty\n");
				} else {
					utils::format("Socket open fail\n");
				}
			} else {
			const uint8_t* ip = tcpudp_env[0].ipaddr;
			utils::format("Socket start: (%d.%d.%d.%d) %u bytes\n")
				% static_cast<int>(ip[0])
				% static_cast<int>(ip[1])
				% static_cast<int>(ip[2])
				% static_cast<int>(ip[3])
				% static_cast<uint32_t>(ret);
			}
		}



		//-----------------------------------------------------------------//
		/*!
			@brief  終了
		*/
		//-----------------------------------------------------------------//
		void end()
		{
			R_SOCKET_Close();
		}
	};
}

