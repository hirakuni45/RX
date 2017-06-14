#pragma once
//=====================================================================//
/*!	@file
	@brief	HTML filer class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include <cstring>
#include "ethernet_server.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  html_filer class
		@param[in]	HTML	html サーバー型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class HTML>
	class html_filer {

		HTML	&html_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
        html_filer(HTML& html) : html_(html) { }




#if 0
		static void dir_list_func_(const char* name, const FILINFO* fi, bool dir, void* option) {
			if(fi == nullptr) return;

			int fd = reinterpret_cast<int>(option);

			format("<tr>", fd);

			time_t t = utils::str::fatfs_time_to(fi->fdate, fi->ftime);
			struct tm *m = localtime(&t);
			if(dir) {
				format("<td>-</td>\n", fd);
			} else {
				format("<td>%9d</td>\n", fd) % fi->fsize;
			}
			{
				format("<td>%s %2d %4d</td>\n", fd) 
					% get_mon(m->tm_mon)
					% static_cast<int>(m->tm_mday)
					% static_cast<int>(m->tm_year + 1900);
				format("<td>%02d:%02d</td>\n", fd) 
					% static_cast<int>(m->tm_hour)
					% static_cast<int>(m->tm_min);
				if(dir) {
					format("<td>/", fd);
				} else {
					format("<td> ", fd);
				}
				format(name, fd);
				format("</td>", fd);
				format("</tr>\n", fd);
			}
		}
#endif


#if 0
		void render_files_(int fd)
		{
			net_tools::send_info(fd, 200, false);

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			net_tools::send_head(fd, "SD Files");

			format("<style type=\"text/css\">\n", fd);
			format(".table3 {\n", fd);
			format("  border-collapse: collapse;\n", fd);
			format("  width: 500px;\n", fd);
			format("}\n", fd);
			format(".table3 th {\n", fd);
			format("  background-color: #cccccc;\n", fd);
			format("}\n", fd);
			format("</style>\n", fd);
			format("<table class=\"table3\" border=1>\n", fd);
			format("<tr><th>Size</th><th>Date</th><th>Time</th><th>Name</th></tr>\n", fd);
			at_sdc().dir_loop("", dir_list_func_, true, reinterpret_cast<void*>(fd));
			format("</table>\n", fd);

			format("<br>\n", fd);
			format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);
			format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定\">\n", fd);

			format("</html>\n", fd);
		}
#endif



	};
}
