#pragma once
//=====================================================================//
/*!	@file
	@brief	ソケット・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

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
					utils::format("Open socket memory empty\n");
				} else {
					utils::format("Open socket fail\n");
				}
			} else {
				utils::format("Socket start: %u bytes\n") % static_cast<uint32_t>(ret);
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

