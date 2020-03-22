#pragma once
//=====================================================================//
/*! @file
    @brief  RX71M イグナイター・テスター HTTP サーバー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "main.hpp"

namespace {

	static const int HTTP_VERSION = 50;
	static const uint32_t BUILD_ID = B_ID;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ＩＰ設定構造体
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct ip_t {
		bool        dhcp_;
		uint8_t     ip_[4];
		uint8_t     gw_[4];
		uint8_t     mask_[4];

		ip_t() :
			dhcp_(true),
			ip_{ 192, 168, 0, 20 },
			gw_{ 192, 168, 0, 1 },
			mask_{ 255, 255, 255, 0 }
			{ }
	};

	typedef HTTP_SERVER::http_format http_format;

	template <class HTTPS>
	class http {

		HTTPS&		https_;

		ip_t		ipt_;

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


        void set_ip_()
        {
            typedef utils::parse_cgi_post<512, 13> CGI_IP;
            CGI_IP cgi;
            cgi.parse(https_.get_post_body());
///            setup_.at_ipt().dhcp_ = false;
            for(uint32_t i = 0; i < cgi.size(); ++i) {
                const auto& t = cgi.get_unit(i);
                int n = 0;
                bool err = true;
                if(t.key == nullptr || t.val == nullptr) {

                } else if(strcmp(t.key, "dhcp") == 0) {
                    if(strcmp(t.val, "on") == 0) {
///                        setup_.at_ipt().dhcp_ = true;
                        err = false;
                    }
                } else if((utils::input("ip%d", t.key) % n).status()) {
                    if(n >= 0 && n <= 3) {
                        int v = 0;
                        if((utils::input("%d", t.val) % v).status()) {
                            if(v >= 0 && v <= 255) {
///                                debug_format("%d, ") % v;
///                                setup_.at_ipt().ip_[n] = v;
                                err = false;
                            }
                        }
                    }
                } else if((utils::input("gw%d", t.key) % n).status()) {
                    if(n >= 0 && n <= 3) {
                        int v = 0;
                        if((utils::input("%d", t.val) % v).status()) {
                            if(v >= 0 && v <= 255) {
///                                debug_format("%d, ") % v;
///                                setup_.at_ipt().gw_[n] = v;
                                err = false;
                            }
                        }
                    }
                } else if((utils::input("mask%d", t.key) % n).status()) {
                    if(n >= 0 && n <= 3) {
                        int v = 0;
                        if((utils::input("%d", t.val) % v).status()) {
                            if(v >= 0 && v <= 255) {
///                               debug_format("%d, ") % v;
///                               setup_.at_ipt().mask_[n] = v;
                                err = false;
                            }
                        }
                    }
///                    debug_format("\n");
                }

                if(err) {
                    return;
                }
            }
///            setup_.write_eui();
        }


	public:
		http(HTTPS& https) : https_(https) { }


		void start()
		{
			https_.start("HTTP Server");

			https_.set_link("/", "Root", [=](void) {

				http_format("Graviton Ignitor CNT Build: %u, Version %d.%02d<br>")
					% BUILD_ID % (HTTP_VERSION / 100) % (HTTP_VERSION % 100);
				https_.tag_hr(500, 3);

				time_t t = get_time();
				struct tm *m = localtime(&t);
				http_format("%s %s %d %02d:%02d:%02d  %4d<br>")
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
						"<td><input type=\"text\" name=\"time\" size=\"8\" value=\"%d:%d\"></td></tr>")
						% static_cast<int>(m->tm_hour) % static_cast<int>(m->tm_min);
					http_format("<tr><td><input type=\"submit\" value=\"ＲＴＣ設定\"></td></tr>");
					http_format("</table></form>\n");
				}

				https_.tag_hr(500, 3);

			// IP 設定
			{
				http_format("<form method=\"POST\" action=\"/cgi/set_ip.cgi\">\n");
				http_format("<table>"
					   "<tr><td><input type=\"checkbox\" name=\"dhcp\" value=\"on\"%s>ＤＨＣＰ</td></tr>")
						% (ipt_.dhcp_ ? " checked=\"checked\"" : "");
				http_format("<tr><td>IP:</td>");
				for(int i = 0; i < 4; ++i) {
					http_format("<td><input type=\"text\" name=\"ip%d\" size=\"3\" value=\"%d\"></td>")
						% i
						% static_cast<uint32_t>(ipt_.ip_[i]);
				}
				http_format("</tr><tr><td>GW:</td>");
				for(int i = 0; i < 4; ++i) {
					http_format("<td><input type=\"text\" name=\"gw%d\" size=\"3\" value=\"%d\"></td>")
						% i
						% static_cast<uint32_t>(ipt_.gw_[i]);
				}
				http_format("</tr><tr><td>MASK:</td>");
				for(int i = 0; i < 4; ++i) {
					http_format("<td><input type=\"text\" name=\"mask%d\" size=\"3\" value=\"%d\"></td>")
						% i
						% static_cast<uint32_t>(ipt_.mask_[i]);
				}
				http_format("</tr>");
				http_format("<td><input type=\"submit\" value=\"ＩＰ設定\"></td>\n");
				http_format("</table></form>\n");

				https_.tag_hr(500, 3);
			}

			} );

			https_.set_cgi("/cgi/set_rtc.cgi", "SetRTC", [=](void) {
				set_rtc_();
				https_.exec_link("/");
			} );

			https_.set_cgi("/cgi/set_ip.cgi", "SetIP", [=](void) {
				set_ip_();
				https_.exec_link("/setup");
			} );
		}
	};
}

