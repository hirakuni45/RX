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

#include "GR/core/ethernet.hpp"
#include "GR/core/ethernet_client.hpp"
#include "GR/core/ethernet_server.hpp"
#include "GR/core/ftp_server.hpp"

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
		net::ethernet_client	client_;
		net::ftp_server			ftp_;

		uint32_t		count_;

		enum class server_task {
			wait_client,
			main_loop,
			disconnect_delay,
			disconnect,
		};
		server_task		server_task_;

		enum class client_task {
			connection,
			main_loop,
			disconnect,
		};
		client_task		client_task_;

		typedef utils::line_manage<2048, 20> LINE_MAN;
		LINE_MAN	line_man_;

		uint32_t	disconnect_loop_;

		net::ip_address		client_ip_;
		time_t		client_time_;

		// サーミスタ定義
		// A/D: 12 bits, NT103_41G, 分圧抵抗: 10K オーム、サーミスタ: ＶＣＣ側
		typedef chip::NTCTH<4095, chip::thermistor::NT103_41G, 10000, true> THMISTER;
		THMISTER thmister_;

		static void dir_list_func_(const char* name, const FILINFO* fi, bool dir, void* option) {
			if(fi == nullptr) return;

			net::ethernet_base* base = static_cast<net::ethernet_base*>(option);

			base->print("<tr>");

			time_t t = utils::str::fatfs_time_to(fi->fdate, fi->ftime);
			struct tm *m = localtime(&t);
			if(dir) {
				base->print("<td>-</td>");
			} else {
				char tmp[32];
				utils::format("<td>%9d</td>", tmp, sizeof(tmp)) % fi->fsize;
				base->print(tmp);
			}
			{
				char tmp[64];
				utils::format("<td>%s %2d %4d</td>", tmp, sizeof(tmp)) 
					% get_mon(m->tm_mon)
					% static_cast<int>(m->tm_mday)
					% static_cast<int>(m->tm_year + 1900);
				base->print(tmp);
				utils::format("<td>%02d:%02d</td>", tmp, sizeof(tmp)) 
					% static_cast<int>(m->tm_hour)
					% static_cast<int>(m->tm_min);
				base->print(tmp);
				if(dir) {
					base->print("<td>/");
				} else {
					base->print("<td> ");
				}
				base->print(name);
				base->print("</td>");
				base->println("</tr>");
			}
		}


		void make_adc_csv_(net::ethernet_base& base, const char* tail)
		{
			char tmp[256];
			for(int ch = 0; ch < 8; ++ch) {
				const auto& t = get_sample(ch);
				utils::format("%d,%d,%d,%d,%d,%d,%d%s", tmp, sizeof(tmp))
					% ch
					% static_cast<uint32_t>(t.min_)
					% static_cast<uint32_t>(t.max_)
					% static_cast<uint32_t>(t.average_)
					% static_cast<uint32_t>(t.limit_level_)
					% static_cast<uint32_t>(t.limit_up_)
					% static_cast<uint32_t>(t.median_)
					% tail;
				base.print(tmp);
			}
		}


		void send_info_(net::ethernet_base& base, int id, bool keep)
		{
			base.print("HTTP/1.1 ");
			char tmp[10];
			utils::format("%d", tmp, sizeof(tmp)) % id;
			base.print(tmp);
			base.print(" OK");
			base.println();
			base.println("Server: seeda/rx64m");
			base.println("Content-Type: text/html");
			base.print("Connection: ");
			if(keep) base.println("keep-alive");
			else base.println("close");
			base.println();
		}


		void send_head_(net::ethernet_base& base, const char* title)
		{
			base.println("<head>");
			char tmp[256];
			utils::format("<title>SEEDA %s</title>", tmp, sizeof(tmp)) % title;
			base.println(tmp);
			base.println("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">");
			base.println("<meta http-equiv=\"Pragma\" content=\"no-cache\">");
			base.println("<meta http-equiv=\"Cache-Control\" content=\"no-cache\">");
			base.println("<meta http-equiv=\"Expires\" content=\"0\">");
			base.println("</head>");
		}


		// クライアントからの応答を解析して終端（空行）があったら「true」
		int analize_request_(net::ethernet_base& base)
		{
			char tmp[1024];
			int len = base.read(tmp, sizeof(tmp));
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


		void select_cgi_(net::ethernet_base& base, const char* path, int pos)
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
			char body[256];
			if(pos >= lines) {
				utils::format("CGI No Body\n");
				return;
			} else {
				utils::str::conv_html_amp(line_man_[pos], body);
//				utils::format("CGI Body: '%s'\n") % body;
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
			} else if(strcmp(path, "/cgi/set_level.cgi") == 0) {
				typedef utils::parse_cgi_post<256, 8> CGI_ADC;
				CGI_ADC cgi;
				cgi.parse(body);
				for(uint32_t i = 0; i < cgi.size(); ++i) {
					const auto& t = cgi.get_unit(i);
					int ch;
					if((utils::input("level_ch%d", t.key) % ch).status()) {
						sample_t samp = get_sample(ch);
						int v;
						if((utils::input("%d", t.val) % v).status()) {
							if(v >= 0 && v <= 65535) {
								samp.limit_level_ = v;
								set_sample(ch, samp);
							}
						}
					}
				}
//				cgi.list();
			} else if(strcmp(path, "/cgi/set_client.cgi") == 0) {
				typedef utils::parse_cgi_post<256, 1> CGI_IP;
				CGI_IP cgi;
				cgi.parse(body);
				for(uint32_t i = 0; i < cgi.size(); ++i) {
					const auto& t = cgi.get_unit(i);
					if(strcmp(t.key, "ip") == 0) {
						client_ip_.from_string(t.val);
						utils::format("Set new client ip: %s\n") % client_ip_.c_str();
					}
				}
			}
		}


		// POST などの空行以下のデータ列を受け取る
		bool recv_data_(net::ethernet_base& base, char* recv, uint32_t max)
		{
			int len = base.read(recv, max);
			if(len <= 0) return false;

			return true;
		}


		void render_404_(net::ethernet_base& base, const char* msg)
		{
			send_info_(base, 404, false);
		}


		void render_null_(net::ethernet_base& base, const char* title = nullptr)
		{
			send_info_(base, 200, false);

			base.println("<!DOCTYPE HTML>");
			base.println("<html>");
			send_head_(base, "NULL");


			if(title != nullptr) {
				base.println(title);
			}
			base.println("</html>");
		}


		void render_date_time_(net::ethernet_base& base)
		{
			char tmp[128];
			time_t t = get_time();
			disp_time(t, tmp, sizeof(tmp));
			base.print(tmp);
			base.println("<br>");
		}


		void render_version_(net::ethernet_base& base)
		{  // ビルドバージョン表示
			char tmp[128];
			utils::format("Seeda03 Build: %u Version %d.%02d", tmp, sizeof(tmp)) % build_id_
				% (seeda_version_ / 100) % (seeda_version_ % 100);
			base.println(tmp);
			base.println("<br>");
		}


		void render_root_(net::ethernet_base& base)
		{
			send_info_(base, 200, false);

			base.println("<!DOCTYPE HTML>");
			base.println("<html>");
			send_head_(base, "Root/SimpleData");

			{  // コネクション回数表示
				char tmp[64];
				utils::format("Conection: %d<br>", tmp, sizeof(tmp)) % count_;
				base.println(tmp);
			}

			render_date_time_(base);

			base.println("Sampling: 1[ms]<br>");

			make_adc_csv_(base, "<br>\r\n");

			base.println("</html>");
		}


		// メイン設定画面
		void render_setup_main_(net::ethernet_base& base)
		{
			send_info_(base, 200, false);

			base.println("<!DOCTYPE HTML>");
			base.println("<html>");
			send_head_(base, "SetupMain");

			render_version_(base);

			render_date_time_(base);

			base.println("<hr align=\"left\" width=\"400\" size=\"3\" />");

			base.println("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"リロード\" />");
			base.println("<hr align=\"left\" width=\"400\" size=\"3\" />");

			base.println("<input type=\"button\" onclick=\"location.href='/'\" value=\"データ表示\" />");
			base.println("<hr align=\"left\" width=\"400\" size=\"3\" />");

			{  // 内臓 A/D 表示
				char tmp[128];
				float v = static_cast<float>(get_adc(5)) / 4095.0f * 3.3f;
				utils::format("バックアップ電池電圧： %4.2f [V]", tmp, sizeof(tmp)) % v;
				base.println(tmp);
				base.println("<br>");
				base.println("<hr align=\"left\" width=\"400\" size=\"3\" />");
			}

//			base.println("<font size=\"4\">");
//			base.println("</font>");

			// RTC 設定
			{
				base.println("<form method=\"POST\" action=\"/cgi/set_rtc.cgi\">");
				auto t = get_time();
				struct tm *m = localtime(&t);
				char tmp[256];
				utils::format("<div>年月日(yyyy/mm/dd)：<input type=\"text\" name=\"date\" size=\"10\" value=\"%d/%d/%d\" /></div>", tmp, sizeof(tmp))
					% static_cast<int>(m->tm_year + 1900) % static_cast<int>(m->tm_mon + 1) % static_cast<int>(m->tm_mday);
				base.println(tmp);
				utils::format("<div>時間　(hh:mm[:ss])：<input type=\"text\" name=\"time\" size=\"8\" value=\"%d:%d\" /></div>", tmp, sizeof(tmp))
					% static_cast<int>(m->tm_hour) % static_cast<int>(m->tm_min);
				base.println(tmp);
				base.println("<input type=\"submit\" value=\"ＲＴＣ設定\" />");
				base.println("</form>");
				base.println("<hr align=\"left\" width=\"400\" size=\"3\" />");
			}

			// 閾値設定
			{
				base.println("<form method=\"POST\" action=\"/cgi/set_level.cgi\">");
				static const char* ch16[] = { "０", "１", "２", "３", "４", "５", "６", "７" };
				for (int ch = 0; ch < 8; ++ch) {
					const auto& t = get_sample(ch);
					char tmp[256];
					utils::format("<div>チャネル%s：<input type=\"text\" name=\"level_ch%d\" size=\"6\" value=\"%d\"  /></div>", tmp, sizeof(tmp))
						% ch16[ch] % ch % static_cast<int>(t.limit_level_);
					base.println(tmp);
				}
				base.println("<input type=\"submit\" value=\"Ａ／Ｄ変換閾値設定\" />");
				base.println("</form>");

				base.println("<hr align=\"left\" width=\"400\" size=\"3\" />");
			}

			// ＳＤカード操作画面へのボタン
			base.println("<input type=\"button\" onclick=\"location.href='/files'\" value=\"ＳＤカード\" />");
			base.println("<hr align=\"left\" width=\"400\" size=\"3\" />");

			base.println("</html>");
		}


		// クライアント設定画面
		void render_setup_client_(net::ethernet_base& base)
		{
			send_info_(base, 200, false);

			base.println("<!DOCTYPE HTML>");
			base.println("<html>");
			send_head_(base, "SetupClient");

			render_version_(base);

			render_date_time_(base);

			base.println("<hr align=\"left\" width=\"400\" size=\"3\" />");

			// クライアント
			{
				base.println("<form method=\"POST\" action=\"/cgi/set_client.cgi\">");
				char tmp[256];
				utils::format("<div>クライアント IP：<input type=\"text\" name=\"ip\" size=\"15\" value=\"%d.%d.%d.%d\" /></div>", tmp, sizeof(tmp))
					% static_cast<int>(client_ip_[0])
					% static_cast<int>(client_ip_[1])
					% static_cast<int>(client_ip_[2])
					% static_cast<int>(client_ip_[3]);
				base.println(tmp);
				base.println("<input type=\"submit\" value=\"クライアント設定\" />");
				base.println("</form>");
			}

			base.println("</html>");
		}


		void render_files_(net::ethernet_base& base)
		{
			send_info_(base, 200, false);

			base.println("<!DOCTYPE HTML>");
			base.println("<html>");
			send_head_(base, "SD Files");

			base.println("<style type=\"text/css\">");
			base.println(".table3 {");
			base.println("  border-collapse: collapse;");
			base.println("  width: 500px;");
			base.println("}");
			base.println(".table3 th {");
			base.println("  background-color: #cccccc;");
			base.println("}");
			base.println("</style>");
			base.println("<table class=\"table3\" border=1>");
			base.println("<tr><th>Size</th><th>Date</th><th>Time</th><th>Name</th></tr>");
			at_sdc().dir_loop("", dir_list_func_, true, &base);
			base.println("</table>");

			base.println("<br>");
			base.println("<hr align=\"left\" width=\"600\" size=\"3\" />");
			base.println("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定\" />");

			base.println("</html>");
		}


		void render_data_(net::ethernet_base& base)
		{
			send_info_(base, 200, false);
			// base.println("Refresh: 5");  // refresh the page automatically every 5 sec

			base.println("<!DOCTYPE HTML>");
			base.println("<html>");
			send_head_(base, "Data");

			base.println("<font size=\"4\">");
			{  // コネクション回数表示
				char tmp[128];
				utils::format("Conection: %d", tmp, sizeof(tmp)) % count_;
				base.print(tmp);
				base.println("<br>");
			}

			render_date_time_(base);

			base.println("サンプリング周期： 1[ms]");
			base.println("<br>");

			base.println("</font>");

			{  // 内臓 A/D 表示（湿度、温度）
				char tmp[64];
				auto v = get_adc(6);
				utils::format("温度： %5.2f [度]", tmp, sizeof(tmp)) % thmister_(v);
				base.println(tmp);
				base.println("<hr align=\"left\" width=\"600\" size=\"3\" />");
			}

			base.println("<style type=\"text/css\">");
			base.println(".table5 {");
			base.println("  border-collapse: collapse;");
			base.println("  width: 500px;");
			base.println("}");
			base.println(".table5 th {");
			base.println("  background-color: #cccccc;");
			base.println("}");
			base.println(".table5 td {");
			base.println("  text-align: center;");
			base.println("}");
			base.println("</style>");

			base.println("<table class=\"table5\" border=1>");
			base.println(" <tr><th>チャネル</th><th>最小値</th><th>最大値</th><th>平均</th>"
					  "<th>基準値</th><th>カウント</th><th>Median</th></tr>");
			for (int ch = 0; ch < 8; ++ch) {
				const auto& t = get_sample(ch);
				base.print(" <tr>");
				char tmp[128];
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % ch;
				base.print(tmp);
///				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.value_);
///				base.print(tmp);
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.min_);
				base.print(tmp);
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.max_);
				base.print(tmp);
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.average_);
				base.print(tmp);
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.limit_level_);
				base.print(tmp);
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.limit_up_);
				base.print(tmp);
				utils::format("<td>%d</td>", tmp, sizeof(tmp)) % static_cast<uint32_t>(t.median_);
				base.print(tmp);
				base.println("</tr>");
			}
			base.println("</table>");

			base.println("<br>");

			base.println("<hr align=\"left\" width=\"600\" size=\"3\" />");
			base.println("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定\" />");

			base.println("</html>");
		}


		void send_file_(net::ethernet_base& base, const char* path)
		{
			FILE* fp = fopen(path, "rb");
			if(fp != nullptr) {
				base.println("HTTP/1.1 200 OK");
				base.print("Content-Type: ");
				const char* ext = strrchr(path, '.');
				if(ext != nullptr) {
					++ext;
					if(strcmp(ext, "png") == 0 || strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0) {
						base.print("image/");
					} else {
						base.print("text/");
					}
					base.println(ext);
				} else {
					base.println("text/plain");
				}
				base.println("Connection: close");
				base.println();
				uint8_t tmp[512];
				uint32_t total = 0;
				uint32_t len;
				while((len = fread(tmp, 1, sizeof(tmp), fp)) == sizeof(tmp)) {
					base.write(tmp, sizeof(tmp));
					total += len;
				}
				if(len > 0) {
					base.write(tmp, len);
					total += len;
				}
				fclose(fp);
			} else {
				render_null_(base, path);
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


		// 指定のアドレス、ポートに定期的に、Ａ／Ｄ変換データを送る。
		void service_client_()
		{
			time_t t;
			switch(client_task_) {

			case client_task::connection:
				{
					uint16_t dstport = 3000;
					if(client_.connected()) {
						utils::format("Conected: %s (port: %d)\n") % client_ip_.c_str() % dstport;
						client_task_ = client_task::main_loop;
						client_time_ = get_time();
					} else {
						client_.connect(client_ip_, dstport, TMO_NBLK);
					}
				}
				break;

			case client_task::main_loop:
				if(!client_.connected()) {
					client_task_ = client_task::disconnect;
					break;
				}
				t = get_time();
				if(client_time_ == t) break;
				client_time_ = t;
				{
					char tmp[128];
					time_t t = get_time();
					disp_time(t, tmp, sizeof(tmp));
					client_.println(tmp);
				}
				{
					make_adc_csv_(client_, "\n");
///					client_.print("end\n");
///					client_task_ = client_task::disconnect;
				}
				break;
			
			case client_task::disconnect:
				client_.stop();
				utils::format("client disconnected: %s\n") % client_ip_.c_str();
				client_task_ = client_task::connection;
				break;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		nets() : server_(ethernet_), client_(ethernet_), ftp_(ethernet_),
			count_(0), server_task_(server_task::wait_client),
			client_task_(client_task::connection),
			line_man_(0x0a), disconnect_loop_(0),
#ifdef SEEDA
			client_ip_(192, 168, 1, 3),
#else
			client_ip_(192, 168, 3, 4),
#endif
			client_time_(0) { }


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

			static const uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

			bool develope = true;
#ifdef SEEDA
			if(get_switch() != 0) {
				develope = false;
			}
#endif

			if(develope) {
				if(ethernet_.begin(mac) == 0) {
					utils::format("Ethernet Fail: begin (DHCP)...\n");

					utils::format("SetIP: ");
					net::ip_address ipa(192, 168, 3, 20);
					ethernet_.begin(mac, ipa);
				} else {
					utils::format("DHCP: ");
				}
			} else {
				net::ip_address ipa(192, 168, 1, 10);
				ethernet_.begin(mac, ipa);
				utils::format("SetIP: ");
			}
			utils::format("%s\n") % ethernet_.get_local_ip().c_str();

			// http server
			server_.begin(80);
			utils::format("Start server: %s") % ethernet_.get_local_ip().c_str();
			utils::format("  port(%d)\n") % static_cast<int>(server_.get_port());

			// client service (3000)
			client_.begin(3000);
			utils::format("Start client: %s") % ethernet_.get_local_ip().c_str();
			utils::format("  port(%d)\n") % static_cast<int>(client_.get_port());

			// FTP Server
			ftp_.start();
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

			service_client_();

			server_.service();

			switch(server_task_) {

			case server_task::wait_client:
				if(server_.connected()) {
					utils::format("New http connected, form: %s\n") % server_.get_from_ip().c_str();
					++count_;
					line_man_.clear();
					server_task_ = server_task::main_loop;
				}
				break;

			case server_task::main_loop:
				if(server_.connected()) {

					if(server_.available() == 0) {  // リードデータがあるか？
						break;
					}
					net::ethernet_base& base = static_cast<net::ethernet_base&>(server_);
					auto pos = analize_request_(base);
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
							render_root_(base);
						} else if(strncmp(path, "/cgi/", 5) == 0) {
							select_cgi_(base, path, pos);
							render_setup_main_(base);
						} else if(strcmp(path, "/data") == 0) {
							render_data_(base);
						} else if(strcmp(path, "/setup") == 0) {
							render_setup_main_(base);
						} else if(strcmp(path, "/client") == 0) {
							render_setup_client_(base);
						} else if(strcmp(path, "/files") == 0) {
							render_files_(base);
						} else if(strncmp(path, "/seeda/", 7) == 0) {
							send_file_(base, path);
						} else {
							char tmp[256];
							utils::format("Invalid path: '%s'", tmp, sizeof(tmp)) % path;
							render_null_(base, tmp);
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
				server_task_ = server_task::wait_client;
				break;
			}

			ftp_.service();
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
