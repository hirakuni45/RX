#pragma once
//=====================================================================//
/*! @file
    @brief  RX71M イグナイター・テスター HTTP サーバー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "main.hpp"

namespace {

	typedef HTTP_SERVER::http_format http_format;

	template <class HTTPS>
	class http {

		HTTPS&		https_;

		void set_rtc_()
		{
			typedef utils::parse_cgi_post<256, 2> CGI_RTC;
			CGI_RTC cgi;
			cgi.parse(https_.get_post_body());
			const char* date = nullptr;
			const char* time = nullptr;
			for(uint32_t i = 0; i < cgi.size(); ++i) {
				const auto& t = cgi.get_unit(i);
				if(t.key == nullptr) {
					break;
				} else if(strcmp(t.key, "date") == 0) {
					date = t.val;
				} else if(strcmp(t.key, "time") == 0) {
					time = t.val;
				} else {
					break;
				}
			}
			if(date != nullptr && time != nullptr) {
				time_t t = make_time(date, time);
				if(t != 0) {
					set_time(t);
				}
			}
//			cgi.list();
		}


	public:
		http(HTTPS& https) : https_(https) { }


		void start()
		{
			https_.start("HTTP Server");
			https_.set_link("/", "Root", [=](void) {
				time_t t = get_time();
				struct tm *m = localtime(&t);
				http_format("%s %s %d %02d:%02d:%02d  %4d<br>\n")
					% get_wday(m->tm_wday)
					% get_mon(m->tm_mon)
					% static_cast<uint32_t>(m->tm_mday)
					% static_cast<uint32_t>(m->tm_hour)
					% static_cast<uint32_t>(m->tm_min)
					% static_cast<uint32_t>(m->tm_sec)
					% static_cast<uint32_t>(m->tm_year + 1900);

				https_.tag_hr(500, 3);

				// RTC 設定
				{
					http_format("<form method=\"POST\" action=\"/cgi/set_rtc.cgi\">\n");
					auto t = get_time();
					struct tm *m = localtime(&t);
					http_format("<table><tr>"
						"<td>年月日(yyyy/mm/dd)：</td>"
						"<td><input type=\"text\" name=\"date\" size=\"10\" value=\"%d/%d/%d\"></td></tr>\n")
						% static_cast<int>(m->tm_year + 1900)
						% static_cast<int>(m->tm_mon + 1) % static_cast<int>(m->tm_mday);
					http_format("<tr>"
						"<td>時間(hh:mm[:ss])：</td>"
						"<td><input type=\"text\" name=\"time\" size=\"8\" value=\"%d:%d\"></td></tr>\n")
						% static_cast<int>(m->tm_hour) % static_cast<int>(m->tm_min);
					http_format("<tr><td><input type=\"submit\" value=\"ＲＴＣ設定\"></td></tr>\n");
					http_format("</table></form>\n");
					http_format("<hr align=\"left\" width=\"750\" size=\"3\">\n");
				}

				https_.tag_hr(500, 3);

			} );

			https_.set_cgi("/cgi/set_rtc.cgi", "SetRTC", [=](void) {
				set_rtc_();
				https_.exec_link("/");
			} );


		}
	};
}

