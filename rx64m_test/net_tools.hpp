#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 net_tools クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"
#include "GR/core/ethernet.hpp"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  net_tools クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class net_tools {

		typedef utils::basic_format<net::eth_chaout> format;

		public:

		//-----------------------------------------------------------------//
		/*!
			@brief  info
		*/
		//-----------------------------------------------------------------//
		static void send_info(int fd, int id, bool keep)
		{
			format("HTTP/1.1 %d OK\n", fd) % id;
			format("Server: seeda/rx64m\n", fd);
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
			format("<title>SEEDA %s</title>\n", fd) % title;
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


		//-----------------------------------------------------------------//
		/*!
			@brief  ビルドバージョン表示
		*/
		//-----------------------------------------------------------------//
		static void render_version(int fd)
		{
			format("Seeda03 Build: %u Version %d.%02d<br>\n", fd) % build_id_
				% (seeda_version_ / 100) % (seeda_version_ % 100);
		}

	};
}
