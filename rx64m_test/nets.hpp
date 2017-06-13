#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 net クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include <cmath>
#include "rx64m_test/main.hpp"
#include "common/string_utils.hpp"
#include "chip/NTCTH.hpp"

#include "write_file.hpp"
#include "client.hpp"

#include "GR/core/ethernet.hpp"
#include "GR/core/ethernet_client.hpp"

#include "net_tools.hpp"
#include "setup.hpp"
#include "preference.hpp"

extern "C" {
	void INT_Excep_ICU_GROUPAL1(void);
}

#define GET_DEBUG

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  net クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class nets {

		typedef device::PORT<device::PORT7, device::bitpos::B0> LAN_RESN;
		typedef device::PORT<device::PORT7, device::bitpos::B3> LAN_PDN;

		net::ethernet	ethernet_;

		HTTP			http_;
		FTP				ftp_;

		client			client_;

		uint32_t		count_;

		// サーミスタ定義
		// A/D: 12 bits, NT103_41G, 分圧抵抗: 10K オーム、サーミスタ: ＶＣＣ側
		typedef chip::NTCTH<4095, chip::thermistor::NT103_41G, 10000, true> THMISTER;
		THMISTER	thmister_;

		write_file	write_file_;

		setup	setup_;

		preference	pre_;

		uint32_t	startup_delay_;

		uint8_t	ip_[4];

		bool 	develope_;
		bool	dhcp_;

		//-------------------------------------------------------------------------//

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

		void make_adc_csv_(const char* tail)
		{
			for(int ch = 0; ch < 8; ++ch) {
				const auto& t = get_sample(ch);
				char tmp[256];
				t.make_csv(tail, tmp, sizeof(tmp));
				http_format("%s") % tmp;
			}
		}

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


		void send_file_(int fd, const char* path)
		{
			FILE* fp = fopen(path, "rb");
			if(fp != nullptr) {
				format("HTTP/1.1 200 OK\n", fd);
				format("Content-Type: ", fd);
				const char* ext = strrchr(path, '.');
				if(ext != nullptr) {
					++ext;
					if(strcmp(ext, "png") == 0 || strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0) {
						format("image/%s\n", fd) % ext;
					} else {
						format("text/%s\n", fd) % ext;
					}
				} else {
					format("text/plain\n", fd);
				}
				format("Connection: close\n\n", fd);
				uint8_t tmp[512];
				uint32_t total = 0;
				uint32_t len;
				while((len = fread(tmp, 1, sizeof(tmp), fp)) == sizeof(tmp)) {
					server_.write(tmp, sizeof(tmp));
					total += len;
				}
				if(len > 0) {
					server_.write(tmp, len);
					total += len;
				}
				fclose(fp);
			} else {
				render_null_(fd, path);
			}
		}
#endif

		void render_data_()
		{
			http_format("<font size=\"4\">\n");
			++count_;
			http_format("Conection: %d<br>\n") % count_;

			net_tools::render_date_time();

			http_format("サンプリング周期： 1[ms]<br>\n");

			http_format("</font>\n");

			{  // 内臓 A/D 表示（湿度、温度）
				auto v = get_adc(6);
				http_format("温度： %5.2f [度]\n") % thmister_(v);
				http_format("<hr align=\"left\" width=\"600\" size=\"3\">\n");
			}

			http_format("<style type=\"text/css\">");
			http_format(".table5 {");
			http_format("  border-collapse: collapse;");
			http_format("  width: 600px;");
			http_format("}");
			http_format(".table5 th {");
			http_format("  background-color: #cccccc;\n");
			http_format("}");
			http_format(".table5 td {");
			http_format("  text-align: center;");
			http_format("}");
			http_format("</style>\n");

			http_format("<table class=\"table5\" border=1>");
			http_format(" <tr><th>チャネル</th><th>表示</th><th>最小値</th><th>最大値</th><th>平均</th>"
				"<th>下限</th><th>下限数</th>"
				"<th>上限</th><th>上限数</th><th>Median</th></tr>\n");

			static const char* modes[] = { "数値", "係数" };
			for(int ch = 0; ch < 8; ++ch) {
				const auto& t = get_sample(ch);
				char min[16];
				t.value_convert(t.min_,     min, sizeof(min));
				char max[16];
				t.value_convert(t.max_,     max, sizeof(max));
				char ave[16];
				t.value_convert(t.average_, ave, sizeof(ave));
				char med[16];
				t.value_convert(t.median_,  med, sizeof(med));
				http_format("<tr>"
					"<td>%d</td>"
					"<td>%s</td>"
					"<td>%s</td>"
					"<td>%s</td>"
					"<td>%s</td>"
					"<td>%d</td>"
					"<td>%d</td>"
					"<td>%d</td>"
					"<td>%d</td>"
					"<td>%s</td>"
					"</tr>\n")
					% ch
					% modes[static_cast<uint32_t>(t.mode_)]
					% min
					% max
					% ave
					% static_cast<uint32_t>(t.limit_lo_level_)
					% static_cast<uint32_t>(t.limit_lo_count_)
					% static_cast<uint32_t>(t.limit_hi_level_)
					% static_cast<uint32_t>(t.limit_hi_count_)
					% med;
			}
			http_format("</table>\n");
			http_format("<br>\n");

			http_format("<hr align=\"left\" width=\"600\" size=\"3\">\n");
			http_format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定\">\n");
		}


		void set_rtc_()
		{
			typedef utils::parse_cgi_post<256, 2> CGI_RTC;
			CGI_RTC cgi;
			cgi.parse(http_.get_post_body());
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
//			cgi.list();
		}


		void set_adc_()
		{
			typedef utils::parse_cgi_post<2048, 6 * 8> CGI_ADC;
			CGI_ADC cgi;
			cgi.parse(http_.get_post_body());
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
					float v = 0.0f;
					const char* p = t.val;
					if((utils::input("%f", p) % v).status()) {
						at_sample(ch).gain_ = v;
					}
				} else if((utils::input("offset%d", t.key) % ch).status()) {
					float v = 0.0f;
					const char* p = t.val;
					if((utils::input("%f", p) % v).status()) {
						at_sample(ch).offset_ = v;
					}
				} else if((utils::input("level_lo%d", t.key) % ch).status()) {
					int v = 0;
					if((utils::input("%d", t.val) % v).status()) {
						if(v >= 0 && v <= 65535) {
							at_sample(ch).limit_lo_level_ = v;
						}
					}
				} else if((utils::input("level_hi%d", t.key) % ch).status()) {
					int v = 0;
					if((utils::input("%d", t.val) % v).status()) {
						if(v >= 0 && v <= 65535) {
							at_sample(ch).limit_hi_level_ = v;
						}
					}
				}
			}
			write_pre_();
//			cgi.list();
		}


		void set_client_()
		{
			typedef utils::parse_cgi_post<256, 2> CGI_IP;
			CGI_IP cgi;
			cgi.parse(http_.get_post_body());
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
		}


		void set_write_()
		{
			if(!write_file_.get_enable()) {
				typedef utils::parse_cgi_post<256, 2> CGI_IP;
				CGI_IP cgi;
				cgi.parse(http_.get_post_body());
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
		}


		void set_ip_()
		{
			typedef utils::parse_cgi_post<256, 5> CGI_IP;
			CGI_IP cgi;
			cgi.parse(http_.get_post_body());
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


		void startup_()
		{
			setup_.init_eui(develope_);
			const uint8_t* ips = setup_.get_ip();
			const uint8_t* mac = setup_.get_mac();

			net::ip_address ipa(ips[0], ips[1], ips[2], ips[3]);
			if(setup_.get_dhcp()) {
				if(ethernet_.begin(mac) == 0) {
					utils::format("Ethernet Fail: begin (DHCP)...\n");
					utils::format("SetIP: ");
					ethernet_.begin(mac, ipa);
				} else {
					utils::format("DHCP: ");
				}
			} else {
				ethernet_.begin(mac, ipa);
				utils::format("SetIP: ");
			}
			utils::format("%s\n") % ethernet_.get_local_ip().c_str();

			// HTTP Server
			http_.start("Seeda03 HTTP Server");

			http_.set_page("/", "SimpleData", [=](void) {
				++count_;
				http_format("Conection: %d<br>\n") % count_;
				net_tools::render_date_time();
				http_format("Sampling: 1[ms]<br>\n");
				make_adc_csv_("<br>\n");
			} );

			http_.set_page("/data", "RichData", [=](void) {
				render_data_();
			} );

			http_.set_page("/setup", "SetupMain", [=](void) {
				setup_.render_main(develope_);
			} );

			http_.set_page("/client", "SetupClient", [=](void) {
				setup_.render_client(develope_);
			} );

#if 0
			} else if(strcmp(path, "/files") == 0) {
				render_files_(fd);
			} else if(strncmp(path, "/seeda/", 7) == 0) {
				send_file_(fd, path);
#endif

			http_.set_cgi("/cgi/set_rtc.cgi", "SetRTC", [=](void) {
				set_rtc_();
				http_.exec_page("/setup");
			} );

			http_.set_cgi("/cgi/set_adc.cgi", "SetADC", [=](void) {
				set_adc_();
				http_.exec_page("/setup");
			} );

			http_.set_cgi("/cgi/set_client.cgi", "SetClient", [=](void) {
				set_client_();
				http_.exec_page("/setup");
			} );

			http_.set_cgi("/cgi/set_write.cgi", "SetWrite", [=](void) {
				set_write_();
				http_.exec_page("/setup");
			} );

			http_.set_cgi("/cgi/del_pre.cgi", "DelFile", [=](void) {
				at_sdc().remove("seeda03.pre");
				http_.exec_page("/setup");
			} );

			http_.set_cgi("/cgi/set_ip.cgi", "SetIP", [=](void) {
				set_ip_();
				http_.exec_page("/setup");
			} );

			// FTP Server
			ftp_.start("SEEDA03", "Renesas_RX64M", "SEEDA03", "SEEDA03");
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		nets() : http_(ethernet_, at_sdc()), ftp_(ethernet_, at_sdc()), client_(ethernet_),
			count_(0),
			write_file_(),
			setup_(write_file_, client_),
			startup_delay_(100), ip_{ 0 },
			develope_(true), dhcp_(false)
			{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void init()
		{
			// LAN initialize (PHY reset, PHY POWER-DOWN
			LAN_PDN::DIR = 1;  // output;
			LAN_PDN::P = 1;    // Not Power Down Mode..
			LAN_RESN::DIR = 1; // output;
			LAN_RESN::P = 0;
			utils::delay::milli_second(200); /// reset rise time
			LAN_RESN::P = 1;

#ifdef SEEDA
			device::power_cfg::turn(device::peripheral::ETHERCA);
			device::port_map::turn(device::peripheral::ETHERCA);
#else
			device::power_cfg::turn(device::peripheral::ETHERC0);
			device::port_map::turn(device::peripheral::ETHERC0);
#endif
			set_interrupt_task(INT_Excep_ICU_GROUPAL1, static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));

			ethernet_.start();

#ifdef SEEDA
			if(get_switch() != 0) {
				develope_ = false;
			}
#endif
			startup_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイトル表示（ネット関係）
		*/
		//-----------------------------------------------------------------//
		void title()
		{
		}


		void service_sub()
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


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			ethernet_.service();

			http_.service();

			client_.service();

			write_file_.service();

			ftp_.service();

			service_sub();			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY リセット信号制御
			@param[in]	cmd		コマンド入力インスタンス
		*/
		//-----------------------------------------------------------------//
		bool reset_signal(CMD cmd)
		{
			uint8_t cmdn = cmd.get_words();
			bool f = false;
			if(cmdn == 1) {
				bool v = LAN_RESN::P();
				utils::format("LAN-RESN: %d\n") % static_cast<int>(v);
				return true;
			} else if(cmdn > 1) {
				char tmp[16];
				if(cmd.get_word(1, sizeof(tmp), tmp)) {
					// Reset signal
					if(strcmp(tmp, "0") == 0) {
						device::PORT7::PODR.B0 = 0;
						f = true;
					} else if(strcmp(tmp, "1") == 0) {
						device::PORT7::PODR.B0 = 1;
						f = true;
					} else {
						utils::format("reset param error: '%s'\n") % tmp;
					}
				}
			}
			return f;
		}
	};
}
