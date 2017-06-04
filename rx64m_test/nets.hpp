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
#include "GR/core/ethernet_server.hpp"
#include "GR/core/ftp_server.hpp"

#include "net_tools.hpp"
#include "setup.hpp"
#include "cgi.hpp"

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

		net::ethernet			ethernet_;
		net::ethernet_server	server_;

		typedef net::ftp_server<SDC> FTP;
		FTP				ftp_;

		client			client_;

		uint32_t		count_;

		enum class server_task {
			begin_http,
			wait_http,
			main_loop,
			disconnect_delay,
			disconnect,
		};
		server_task		server_task_;

		uint32_t	disconnect_loop_;

		// サーミスタ定義
		// A/D: 12 bits, NT103_41G, 分圧抵抗: 10K オーム、サーミスタ: ＶＣＣ側
		typedef chip::NTCTH<4095, chip::thermistor::NT103_41G, 10000, true> THMISTER;
		THMISTER thmister_;

		write_file	write_file_;

		setup	setup_;
		cgi		cgi_;

		bool 	develope_;

		//-------------------------------------------------------------------------//

		typedef utils::basic_format<net::eth_chaout> format;

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


		void make_adc_csv_(uint32_t fd, const char* tail)
		{
			for(int ch = 0; ch < 8; ++ch) {
				const auto& t = get_sample(ch);
				char tmp[256];
				t.make_csv(tail, tmp, sizeof(tmp));
				format("%s", fd) % tmp;
			}
		}


		void render_404_(int fd, const char* msg)
		{
			net_tools::send_info(fd, 404, false);
		}


		void render_null_(int fd, const char* title = nullptr)
		{
			net_tools::send_info(fd, 200, false);

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			net_tools::send_head(fd, "NULL");

			if(title != nullptr) {
				format(title, fd);
			}
			format("</html>\n", fd);
		}


		void render_root_(int fd)
		{
			net_tools::send_info(fd, 200, false);

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			net_tools::send_head(fd, "Root/SimpleData");

			// コネクション回数表示
			format("Conection: %d<br>\n", fd) % count_;

			net_tools::render_date_time(fd);

			format("Sampling: 1[ms]<br>\n", fd);

			make_adc_csv_(fd, "<br>\n");

			format("</html>\n", fd);
		}


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


		void render_data_(int fd)
		{
			net_tools::send_info(fd, 200, false);
			// format("Refresh: 5\n", fd);  // refresh the page automatically every 5 sec

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			net_tools::send_head(fd, "Data");

			format("<font size=\"4\">\n", fd);
			// コネクション回数表示
			format("Conection: %d<br>\n", fd) % count_;

			net_tools::render_date_time(fd);

			format("サンプリング周期： 1[ms]<br>\n", fd);

			format("</font>\n", fd);

			{  // 内臓 A/D 表示（湿度、温度）
				auto v = get_adc(6);
				format("温度： %5.2f [度]\n", fd) % thmister_(v);
				format("<hr align=\"left\" width=\"600\" size=\"3\">\n", fd);
			}

			format("<style type=\"text/css\">", fd);
			format(".table5 {", fd);
			format("  border-collapse: collapse;", fd);
			format("  width: 600px;", fd);
			format("}", fd);
			format(".table5 th {", fd);
			format("  background-color: #cccccc;\n", fd);
			format("}", fd);
			format(".table5 td {", fd);
			format("  text-align: center;", fd);
			format("}", fd);
			format("</style>\n", fd);

			format("<table class=\"table5\" border=1>", fd);
			format(" <tr><th>チャネル</th><th>表示</th><th>最小値</th><th>最大値</th><th>平均</th>"
					  "<th>下限</th><th>下限数</th>"
					  "<th>上限</th><th>上限数</th><th>Median</th></tr>\n", fd);

			static const char* modes[] = { "数値", "係数" };
			for(int ch = 0; ch < 8; ++ch) {
				const auto& t = get_sample(ch);
				char min[16];
				t.value_convert(t.min_,    min, sizeof(min));
				char max[16];
				t.value_convert(t.max_,     max, sizeof(max));
				char ave[16];
				t.value_convert(t.average_, ave, sizeof(ave));
				char med[16];
				t.value_convert(t.median_,  med, sizeof(med));
				format("<tr>"
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
					"</tr>\n", fd)
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


		void get_path_(const char* src, char* dst) {
			int n = 0;
			char ch;
			while((ch = src[n]) != 0) {
				if(ch == ' ') break;
				dst[n] = ch;
				++n;
			}
			dst[n] = 0;
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

			// FTP Server
			ftp_.start();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		nets() : server_(ethernet_), ftp_(ethernet_, at_sdc()), client_(ethernet_),
			count_(0), server_task_(server_task::begin_http),
			disconnect_loop_(0),
			write_file_(),
			setup_(write_file_, client_), cgi_(write_file_, client_, setup_),
			develope_(true)
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


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			ethernet_.service();

			switch(server_task_) {

			case server_task::begin_http:
				// http server
				server_.begin(80);
				utils::format("Start HTTP server: %s") % ethernet_.get_local_ip().c_str();
				utils::format("  port(%d), fd(%d)\n")
					% static_cast<int>(server_.get_port()) % server_.get_cepid();
				server_task_ = server_task::wait_http;
				break;

			case server_task::wait_http:
				if(server_.connected()) {
					utils::format("New http connected, form: %s\n") % server_.get_from_ip().c_str();
					++count_;
					cgi_.at_line_man().clear();
					server_task_ = server_task::main_loop;
				}
				break;

			case server_task::main_loop:
				if(server_.connected()) {

					if(server_.available() == 0) {  // リードデータがあるか？
						break;
					}
					int fd = server_.get_cepid();
					char tmp[512];
					int len = server_.read(tmp, sizeof(tmp));
					auto pos = cgi_.analize_request(tmp, len);
					if(pos > 0) {
						char path[256];
						path[0] = 0;
						if(!cgi_.at_line_man().empty()) {
							const auto& t = cgi_.at_line_man()[0];
							if(strncmp(t, "GET ", 4) == 0) {
								get_path_(t + 4, path);
							} else if(strncmp(t, "POST ", 5) == 0) {
								get_path_(t + 5, path);
							}
						} else {
							utils::format("fail GET/POST data section\n");
							break;
						}
						if(strcmp(path, "/") == 0) {
							render_root_(fd);
						} else if(strncmp(path, "/cgi/", 5) == 0) {
							cgi_.select(fd, path, pos);
							setup_.render_main(fd, develope_);
						} else if(strcmp(path, "/data") == 0) {
							render_data_(fd);
						} else if(strcmp(path, "/setup") == 0) {
							setup_.render_main(fd, develope_);
						} else if(strcmp(path, "/client") == 0) {
							setup_.render_client(fd);
						} else if(strcmp(path, "/files") == 0) {
							render_files_(fd);
						} else if(strncmp(path, "/seeda/", 7) == 0) {
							send_file_(fd, path);
						} else {
							char tmp[256];
							utils::format("Invalid path: '%s'", tmp, sizeof(tmp)) % path;
							render_null_(fd, tmp);
						}
						server_task_ = server_task::disconnect_delay;
						disconnect_loop_ = 5;
					}
				} else {
					server_task_ = server_task::disconnect_delay;
					disconnect_loop_ = 5;
				}
				break;

			case server_task::disconnect_delay:
				if(disconnect_loop_ > 0) {
					--disconnect_loop_;
				} else {
					server_task_ = server_task::disconnect;
				}
				break;

			case server_task::disconnect:
			default:
				server_.stop();
				utils::format("http disconnected\n");
				server_task_ = server_task::begin_http;
				break;
			}

			client_.service();

			write_file_.service();

			ftp_.service();

			cgi_.service();
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
