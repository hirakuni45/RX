#pragma once
//=====================================================================//
/*!	@file
	@brief	http server class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include <cstring>
#include "ethernet_server.hpp"

#include "common/fixed_string.hpp"

extern "C" {
	time_t get_time(void);
};

namespace net {

	typedef utils::basic_format<ether_string<ethernet::format_id::http, 4096 > > http_format;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ftp_server class
		@param[in]	SDC	ＳＤカードファイル操作関係
		@param[in]	MAX_SIZE	一時バッファの最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDC, uint32_t MAX_SIZE = 4096>
	class http_server {

		ethernet&		eth_;

		SDC&			sdc_;

		ethernet_server	http_;




	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		http_server(ethernet& e, SDC& sdc) : eth_(e), sdc_(sdc), http_(e) { }


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  info
		*/
		//-----------------------------------------------------------------//
		static void send_info(int fd, int id, bool keep)
		{
			format("HTTP/1.1 %d OK\n", fd) % id;
			format("Server: SEEDA03/RX64M\n", fd);
			format("Content-Type: text/html\n", fd);
			format("Connection: %s\n\n", fd) % (keep == true ? "keep-alive" : "close");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  head
		*/
		//-----------------------------------------------------------------//
		static void send_head(int fd, const char* title)
		{
			format("<head>\n", fd);
			format("<title>SEEDA03 %s</title>\n", fd) % title;
			format("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n", fd);
			format("<meta http-equiv=\"Pragma\" content=\"no-cache\">\n", fd);
			format("<meta http-equiv=\"Cache-Control\" content=\"no-cache\">\n", fd);
			format("<meta http-equiv=\"Expires\" content=\"0\">\n", fd);
			format("</head>\n", fd);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  render date/time
		*/
		//-----------------------------------------------------------------//
		static void render_date_time(int fd)
		{
			char tmp[128];
			time_t t = get_time();
			disp_time(t, tmp, sizeof(tmp));
			format("%s<br>\n", fd) % tmp;
		}
#endif


	};

}
