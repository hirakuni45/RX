#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 net クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#ifdef SEEDA
#include "rx64m_test/main.hpp"
#else
#include "GR-KAEDE/main.hpp"
#endif

#include "common/string_utils.hpp"

#include "GR/core/Ethernet.h"

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
	class net {

		typedef device::PORT<device::PORT7, device::bitpos::B0> LAN_RESN;
		typedef device::PORT<device::PORT7, device::bitpos::B3> LAN_PDN;

		EthernetServer	server_;

		uint32_t		count_;

		enum class server_task {
			wait_client,
			main_loop,
			disconnect_delay,
			disconnect,
		};
		server_task		server_task_;

		typedef utils::line_manage<2048, 20> LINE_MAN;
		LINE_MAN	line_man_;

		uint32_t	disconnect_loop_;

		static void dir_list_func_(const char* name, const FILINFO* fi, bool dir, void* option) {
			if(fi == nullptr) return;

			EthernetClient* cl = static_cast<EthernetClient*>(option);

			time_t t = utils::str::fatfs_time_to(fi->fdate, fi->ftime);
			struct tm *m = localtime(&t);
			if(dir) {
				cl->print("          ");
			} else {
				char tmp[16];
				utils::format("%9d ", tmp, sizeof(tmp)) % fi->fsize;
				cl->print(tmp);
			}
			{
				char tmp[32];
				utils::format("%s %2d %4d %02d:%02d ", tmp, sizeof(tmp)) 
					% get_mon(m->tm_mon)
					% static_cast<int>(m->tm_mday)
					% static_cast<int>(m->tm_year + 1900)
					% static_cast<int>(m->tm_hour)
					% static_cast<int>(m->tm_min);
				cl->print(tmp);
				if(dir) {
					cl->print("/");
				} else {
					cl->print(" ");
				}
				cl->print(name);
				cl->println("<br/>");
			}
		}


		void send_head_(EthernetClient& client, int id, bool keep)
		{
			client << "HTTP/1.1 ";
			client << id << " OK";
			client.println();
			client.println("Server: seeda/rx64m");
			client.println("Content-Type: text/html");
			client.print("Connection: ");
			if(keep) client.println("keep-alive");
			else client.println("close");
			client.println();
		}


		// クライアントからの応答を解析して終端（空行）があったら「true」
		int analize_request_(EthernetClient& client)
		{
			char tmp[1024];
			int len = client.read(tmp, sizeof(tmp));
			if(len <= 0) return -1;

			for(int i = 0; i < len; ++i) {
				char ch = tmp[i];
				if(ch == 0 || ch == 0x0d) continue;
				if(!line_man_.add(ch)) {
					utils::format("line_man: memory over\n");
					return -1;
				}
			}
			if(static_cast<size_t>(len) < sizeof(tmp)) {
				line_man_.set_term();
				if(!line_man_.empty()) {
#if 0
					for(uint32_t i = 0; i < line_man_.size(); ++i) {
						const char* p = line_man_[i];
						utils::format("%s\n") % p;
					}
#endif
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


		void do_cgi_(EthernetClient& client, const char* path, int pos)
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
			if(pos >= lines) {
				utils::format("CGI No Body\n");
			} else {
				char tmp[256];
				utils::str::conv_html_amp(line_man_[pos], tmp);
				utils::format("CGI Body: '%s'\n") % tmp;
			}



			
		}


		// POST などの空行以下のデータ列を受け取る
		bool recv_data_(EthernetClient& client, char* recv, uint32_t max)
		{
			int len = client.read(recv, max);
			if(len <= 0) return false;

			return true;
		}


		void render_404_(EthernetClient& client, const char* msg)
		{
			send_head_(client, 404, false);
		}


		void render_null_(EthernetClient& client, const char* title = nullptr)
		{
			send_head_(client, 200, false);

			client.println("<!DOCTYPE HTML>");
			client.println("<html>");
			if(title != nullptr) {
				client.println(title);
			}
			client.println("</html>");
		}


		void render_root_(EthernetClient& client)
		{
			send_head_(client, 200, false);

#if 0
			client.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">");
			client.println("<html>");
			client.println("<head>");
			client.println("<title>SEEDA Settings</title>");
			client.println("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">");
			client.println("<meta http-equiv=\"Pragma\" content=\"no-cache\">");
			client.println("<meta http-equiv=\"Cache-Control\" content=\"no-cache\">");
			client.println("<meta http-equiv=\"Expires\" content=\"0\">");
			client.println("<script src=\"seeda/OnceOnly.html\"></script>");
			client.println("</head>");
			client.println("<FRAMESET cols=\"223,*\" frameborder=\"NO\" border=\"0\">");
			client.println("<FRAMESET rows=\"137,*\" frameborder=\"NO\" border=\"0\">");
			client.println("<FRAME name=\"ttl\" scrolling=\"NO\" noresize src=\"seeda/title.png\">");
			client.println("<FRAME name=\"men\" scrolling=\"AUTO\" noresize src=\"seeda/men.html\">");
			client.println("</FRAMESET>");
			client.println("<FRAME name=\"frm\" src=\"seeda/frmtop.html\">");
			client.println("<NOFRAMES>");
			client.println("<p>You cann't access this page without frame brouser.</p>");
			client.println("</NOFRAMES>");
			client.println("</FRAMESET>");
			client.println("</html>");
#endif
		}


		// 設定画面
		void render_setup_(EthernetClient& client)
		{
			send_head_(client, 200, false);

			client.println("<html>");

			client.println("<head>");
			client.println("<title>SEEDA Setup</title>");
			client.println("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">");
			client.println("<meta http-equiv=\"Pragma\" content=\"no-cache\">");
			client.println("<meta http-equiv=\"Cache-Control\" content=\"no-cache\">");
			client.println("<meta http-equiv=\"Expires\" content=\"0\">");
			client.println("</head>");

			// RTC 設定 /// client.println("<input type=\"reset\" value=\"取消\">");
			client.println("<form method=\"POST\" action=\"cgi/set_date.cgi\">");
			client.println("<div>年月日(yyyy/mm/dd)：<input type=\"text\" name=\"date_ymd\" size=\"10\" /></div>");
			client.println("<div>時間　(hh:mm[:ss])：<input type=\"text\" name=\"date_t\" size=\"8\" /></div>");
			client.println("<input type=\"submit\" value=\"ＲＴＣ設定\" />");
			client.println("</form>");
			client.println("<br>");

#if 0
			// タイムスライス設定
			client.println("<form method=\"POST\" action=\"cgi/set_rate.cgi\">");
			client.println("<p>Ａ／Ｄ変換サンプリング・レート<br>");
			client.println("<input type=\"radio\" name=\"rate\" value=\"_10ms\" />１０［ｍｓ］"); 
			client.println("<input type=\"radio\" name=\"rate\" value=\"_01ms\" />　１［ｍｓ］"); 
			client.println("</p>");
			client.println("<input type=\"submit\" value=\"レート設定\" />");
			client.println("</form>");
			client.println("<br>");
#endif

			// 閾値設定
			client.println("<form method=\"POST\" action=\"cgi/set_level.cgi\">");
			static const char* ch16[] = { "０", "１", "２", "３", "４", "５", "６", "７" };
			for (int ch = 0; ch < 8; ++ch) {
				const auto& t = get_sample(ch);
				char tmp[256];
				utils::format("<div>チャネル%s：<input type=\"text\" name=\"level_ch%d\" size=\"6\" value=\"%d\"  /></div>", tmp, sizeof(tmp))
					% ch16[ch] % ch % static_cast<int>(t.limit_level_);
				client.println(tmp);
			}
			client.println("<input type=\"submit\" value=\"Ａ／Ｄ変換閾値設定\" />");
			client.println("</form>");
			client.println("<br>");

			client.println("</html>");
		}


		void render_files_(EthernetClient& client)
		{
			send_head_(client, 200, false);

			client.println("<!DOCTYPE HTML>");
			client.println("<html>");

			at_sdc().dir_loop("", dir_list_func_, true, &client);


			client.println("</html>");
		}


		void render_data_(EthernetClient& client)
		{
			send_head_(client, 200, false);
			// client.println("Refresh: 5");  // refresh the page automatically every 5 sec

			client.println("<!DOCTYPE HTML>");
			client.println("<html>");
			client.println("<font size=\"4\">");
			{  // コネクション回数表示
				char tmp[128];
				utils::format("Conection: %d", tmp, sizeof(tmp)) % count_;
				client.print(tmp);
				client.println("<br/>");
			}
			{  // 時間表示
				char tmp[128];
				time_t t = get_time();
				disp_time(t, tmp, sizeof(tmp));
				client.print(tmp);
				client.println("<br/>");
			}

			client << "サンプリング周期： 1[ms]\n";
			client << "<br/>\n";

			client.println("<br/>");
			client.println("</font>");

			client << "<style type=\"text/css\">\n";
			client << ".table5 {\n";
			client << "  border-collapse: collapse;\n";
			client << "  width: 500px;\n";
			client << "}\n";
			client << ".table5 th {\n";
			client << "  background-color: #cccccc;\n";
			client << "}\n";
			client << ".table5 td {\n";
			client << "  text-align: center;\n";
			client << "}\n";
			client << "</style>\n";

			client << "<table class=\"table5\" border=1>\n";
			client << " <tr><th>チャネル</th><th>最小値</th><th>最大値</th><th>平均</th>"
					  "<th>基準値</th><th>カウント</th><th>Median</th></tr>\n";
			for (int ch = 0; ch < 8; ++ch) {
				const auto& t = get_sample(ch);
				client << " <tr>";
				char tmp[128];
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % ch;
				client << tmp;
///				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.value_);
///				client << tmp;
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.min_);
				client << tmp;
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.max_);
				client << tmp;
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.average_);
				client << tmp;
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.limit_level_);
				client << tmp;
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.limit_up_);
				client << tmp;
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.median_);
				client << tmp;
				client << "</tr>\n";
			}
			client << "</table>\n";

			client.println("</html>");
		}


		void send_file_(EthernetClient& client, const char* path)
		{
			FILE* fp = fopen(path, "rb");
			if(fp != nullptr) {
				client.println("HTTP/1.1 200 OK");
				client.print("Content-Type: ");
				const char* ext = strrchr(path, '.');
				if(ext != nullptr) {
					++ext;
					if(strcmp(ext, "png") == 0 || strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0) {
						client.print("image/");
					} else {
						client.print("text/");
					}
					client.println(ext);
				} else {
					client.println("text/plain");
				}
				client.println("Connection: close");
				client.println();
				uint8_t tmp[512];
				uint32_t total = 0;
				uint32_t len;
				while((len = fread(tmp, 1, sizeof(tmp), fp)) == sizeof(tmp)) {
					client.write(tmp, sizeof(tmp));
					total += len;
				}
				if(len > 0) {
					client.write(tmp, len);
					total += len;
				}
				fclose(fp);
			} else {
				render_null_(client, path);
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


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		net() : server_(), count_(0), server_task_(server_task::wait_client),
			line_man_(0x0a), disconnect_loop_(0) { }


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

			Ethernet.maininit();

			static const uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

			bool develope = true;
#ifdef SEEDA
			if(get_switch() != 0) {
				develope = false;
			}
#endif

			if(develope) {
				if(Ethernet.begin(mac) == 0) {
					utils::format("Ethernet Fail: begin (DHCP)...\n");

					utils::format("SetIP: ");
					IPAddress ipa(192, 168, 3, 20);
					Ethernet.begin(mac, ipa);
				} else {
					utils::format("DHCP: ");
				}
			} else {
				utils::format("SetIP: ");
				IPAddress ipa(192, 168, 1, 10);
				Ethernet.begin(mac, ipa);
			}
			Ethernet.localIP().print();
			utils::format("\n");

			if(develope) {
				server_.begin(80);
			} else {
				server_.begin(3000);
			}

			utils::format("Start server: ");
			Ethernet.localIP().print();
			utils::format("  port(%d)\n") % static_cast<int>(server_.get_port());
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
			Ethernet.mainloop();

			EthernetClient client = server_.available();

			switch(server_task_) {

			case server_task::wait_client:
				if(client) {
					utils::format("new client\n");
					++count_;
					line_man_.clear();
					server_task_ = server_task::main_loop;
				}
				break;

			case server_task::main_loop:
				if(client.connected()) {

					if(client.available() == 0) {
///						utils::format("client not available\n");
						break;
					}

					auto pos = analize_request_(client);
					if(pos > 0) {
						char path[256];
						path[0] = 0;
						if(!line_man_.empty()) {
							const auto& t = line_man_[0];
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
///							render_root_(client);
							render_data_(client);
						} else if(strncmp(path, "/cgi/", 5) == 0) {
							do_cgi_(client, path, pos);
							render_setup_(client);
						} else if(strcmp(path, "/data") == 0) {
							render_data_(client);
						} else if(strcmp(path, "/setup") == 0) {
							render_setup_(client);
						} else if(strcmp(path, "/files") == 0) {
							render_files_(client);
						} else if(strncmp(path, "/seeda/", 7) == 0) {
							send_file_(client, path);
						} else {
							char tmp[256];
							utils::format("Invalid path: '%s'", tmp, sizeof(tmp)) % path;
							render_null_(client, tmp);
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
				client.stop();
				utils::format("client disconnected\n");
				server_task_ = server_task::wait_client;
				break;
			}
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
