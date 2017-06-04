#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 CGI クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/string_utils.hpp"

#include "net_tools.hpp"
#include "write_file.hpp"
#include "preference.hpp"
#include "client.hpp"
#include "setup.hpp"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  setup クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class cgi {
	public:
		typedef utils::line_manage<2048, 20> LINE_MAN;

	private:
		write_file&	write_file_;
		client&		client_;
		setup&		setup_;

		LINE_MAN	line_man_;

		preference	pre_;

		uint32_t	startup_delay_;

		bool		dhcp_;
		uint8_t		ip_[4];

		typedef utils::basic_format<net::eth_chaout> format;

		void write_pre_()
		{
			for(int i = 0; i < 4; ++i) pre_.at().client_ip_[i] = (client_.get_ip())[i];
			pre_.at().client_port_ = client_.get_port();

			for(int ch = 0; ch < 8; ++ch) {
				pre_.at().mode_[ch] = static_cast<uint8_t>(at_sample(ch).mode_);
				pre_.at().gain_[ch] = at_sample(ch).gain_;
				pre_.at().offset_[ch] = at_sample(ch).offset_;
				pre_.at().limit_lo_level_[ch] = at_sample(ch).limit_lo_level_;
				pre_.at().limit_hi_level_[ch] = at_sample(ch).limit_hi_level_;
			}

			strcpy(pre_.at().write_path_, write_file_.get_path());
			pre_.at().write_limit_ = write_file_.get_limit();

			pre_.write();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		cgi(write_file& wf, client& cl, setup& stu) : write_file_(wf), client_(cl), setup_(stu),
			line_man_(0x0a),
			pre_(), startup_delay_(100), dhcp_(false), ip_{ 0 } { }


		//-----------------------------------------------------------------//
		/*!
			@brief ライン・マネージャーへの参照
			@return ライン・マネージャー
		*/
		//-----------------------------------------------------------------//
		LINE_MAN& at_line_man() { return line_man_; }


		//-----------------------------------------------------------------//
		/*!
			@brief クライアントからの応答を解析して終端（空行）があったら行数を返す
			@return 行数
		*/
		//-----------------------------------------------------------------//
		int analize_request(const char* tmp, int len)
		{
			for(int i = 0; i < len; ++i) {
				char ch = tmp[i];
				if(ch == 0 || ch == 0x0d) continue;
				if(!line_man_.add(ch)) {
					utils::format("line_man: memory over\n");
					return -1;
				}
			}
			if(len > 0) {
				line_man_.set_term();
				if(!line_man_.empty()) {
					for(uint32_t i = 0; i < line_man_.size(); ++i) {
						const char* p = line_man_[i];
						if(p[0] == 0) {  // 応答の終端！（空行）
							return i;
						}
					}
				}
			}
			return -1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief CGI 解析 
		*/
		//-----------------------------------------------------------------//
		void select(int fd, const char* path, int pos)
		{
			utils::format("CGI: '%s'\n") % path;

			int len = 0;
			for(int i = 0; i < static_cast<int>(line_man_.size()); ++i) {
				const char* p = line_man_[i];
				static const char* key = { "Content-Length: " };
				if(strncmp(p, key, strlen(key)) == 0) {
					utils::input("%d", p + strlen(key)) % len;
					break;
				}
			}

			int lines = static_cast<int>(line_man_.size());
			++pos;
			char body[1024];
			if(pos >= lines) {
				utils::format("CGI No Body\n");
				return;
			} else {
//				utils::format("CGI param (URL enocde): '%s'\n") % line_man_[pos];
				utils::str::url_encode_to_str(line_man_[pos], body);
//				utils::format("CGI param (str): '%s'\n") % body;
			}


			if(strcmp(path, "/cgi/set_rtc.cgi") == 0) {
				typedef utils::parse_cgi_post<256, 2> CGI_RTC;
				CGI_RTC cgi;
				cgi.parse(body);
				const char* date = nullptr;
				const char* time = nullptr;
				for(uint32_t i = 0; i < cgi.size(); ++i) {
					const auto& t = cgi.get_unit(i);
					if(strcmp(t.key, "date") == 0) {
						date = t.val;
					} else if(strcmp(t.key, "time") == 0) {
						time = t.val;
					}
				}
				if(date != nullptr && time != nullptr) {
					time_t t = seeda::make_time(date, time);
					if(t != 0) {
						seeda::set_time(t);
					}
				}
//				cgi.list();
			} else if(strcmp(path, "/cgi/set_adc.cgi") == 0) {
				typedef utils::parse_cgi_post<1024, 5 * 8> CGI_ADC;
				CGI_ADC cgi;
				cgi.parse(body);
				for(uint32_t i = 0; i < cgi.size(); ++i) {
					const auto& t = cgi.get_unit(i);
					int ch;
					if((utils::input("mode%d", t.key) % ch).status()) {
						if(strcmp(t.val, "none") == 0) {  // 数値（無変換）
							at_sample(ch).mode_ = seeda::sample_t::mode::none;
						} else if(strcmp(t.val, "real") == 0) {  // 係数変換
							at_sample(ch).mode_ = seeda::sample_t::mode::real;
						}
					} else if((utils::input("gain%d", t.key) % ch).status()) {
						float v;
						const char* p = t.val;
						if((utils::input("%f", p) % v).status()) {
							at_sample(ch).gain_ = v;
						}
					} else if((utils::input("offset%d", t.key) % ch).status()) {
						float v;
						const char* p = t.val;
						if((utils::input("%f", p) % v).status()) {
							at_sample(ch).offset_ = v;
						}
					} else if((utils::input("level_lo%d", t.key) % ch).status()) {
						int v;
						if((utils::input("%d", t.val) % v).status()) {
							if(v >= 0 && v <= 65535) {
								at_sample(ch).limit_lo_level_ = v;
							}
						}
					} else if((utils::input("level_hi%d", t.key) % ch).status()) {
						int v;
						if((utils::input("%d", t.val) % v).status()) {
							if(v >= 0 && v <= 65535) {
								at_sample(ch).limit_hi_level_ = v;
							}
						}
					}
				}

				write_pre_();

//				cgi.list();
			} else if(strcmp(path, "/cgi/set_client.cgi") == 0) {
				typedef utils::parse_cgi_post<256, 2> CGI_IP;
				CGI_IP cgi;
				cgi.parse(body);
				for(uint32_t i = 0; i < cgi.size(); ++i) {
					const auto& t = cgi.get_unit(i);
					if(strcmp(t.key, "ip") == 0) {
						utils::format("Set client IP: '%s'\n") % t.val;
						client_.at_ip().from_string(t.val);
					} else if(strcmp(t.key, "port") == 0) {
						int port;
						if((utils::input("%d", t.val) % port).status()) {
							utils::format("Set client PORT: %d\n") % port;
							client_.set_port(port);
						}
					}
				}

				write_pre_();

				client_.restart();

			} else if(strcmp(path, "/cgi/set_write.cgi") == 0) {
				if(!write_file_.get_enable()) {
					typedef utils::parse_cgi_post<256, 2> CGI_IP;
					CGI_IP cgi;
					cgi.parse(body);
					for(uint32_t i = 0; i < cgi.size(); ++i) {
						const auto& t = cgi.get_unit(i);
						if(strcmp(t.key, "fname") == 0) {
							if(t.val != nullptr) write_file_.set_path(t.val);
						} else if(strcmp(t.key, "count") == 0) {
							int n;
							utils::input("%d", t.val) % n;
							write_file_.set_limit(n);
						}
					}
					write_file_.enable();
				} else {
					write_file_.enable(false);
				}
			} else if(strcmp(path, "/cgi/del_pre.cgi") == 0) {
				at_sdc().remove("seeda03.pre");
			} else if(strcmp(path, "/cgi/set_ip.cgi") == 0) {
				typedef utils::parse_cgi_post<256, 5> CGI_IP;
				CGI_IP cgi;
				cgi.parse(body);
				dhcp_ = false;
				for(uint32_t i = 0; i < cgi.size(); ++i) {
					const auto& t = cgi.get_unit(i);
					int n;
					if(strcmp(t.key, "dhcp") == 0) {
						if(strcmp(t.val, "on") == 0) {
							dhcp_ = true;
						}
					} else if((utils::input("ip%d", t.key) % n).status()) {
						if(n >= 0 && n <= 3) {
							int v;
							utils::input("%d", t.val) % v;
							utils::format("%d, ") % v;
							ip_[n] = v;
						}
						utils::format("\n");
					}
				}
				setup_.write_eui(dhcp_, ip_);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			if(startup_delay_ == 0) {
				return;
			}

			--startup_delay_;
			if(startup_delay_ == 0) {
				if(pre_.read()) {
					for(int ch = 0; ch < 8; ++ch) {
						at_sample(ch).mode_ = static_cast<sample_t::mode>(pre_.get().mode_[ch]);
						at_sample(ch).gain_ = pre_.get().gain_[ch];
						at_sample(ch).offset_ = pre_.get().offset_[ch];
						at_sample(ch).limit_lo_level_ = pre_.get().limit_lo_level_[ch];
						at_sample(ch).limit_hi_level_ = pre_.get().limit_hi_level_[ch];
					}
					for(int i = 0; i < 4; ++i) client_.at_ip()[i] = pre_.get().client_ip_[i];
					client_.set_port(pre_.get().client_port_);

					write_file_.set_path(pre_.get().write_path_);
					write_file_.set_limit(pre_.get().write_limit_); 
				}
				client_.start_connect();
			}
		}
	};
}
