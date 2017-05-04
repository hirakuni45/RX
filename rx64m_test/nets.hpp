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
		typedef net::ftp_server<SDC> FTP;
		FTP				ftp_;

		uint32_t		count_;

		enum class server_task {
			begin_http,
			wait_http,
			main_loop,
			disconnect_delay,
			disconnect,
		};
		server_task		server_task_;

		enum class client_task {
			connect,
			wait_connect,
			main_loop,
			disconnect,
			delay_connection,
			delay_loop,
		};
		client_task		client_task_;
		uint16_t		client_port_;
		uint32_t		client_delay_;
		uint32_t		client_timeout_;

		typedef utils::line_manage<2048, 20> LINE_MAN;
		LINE_MAN	line_man_;

		uint32_t	disconnect_loop_;

		net::ip_address		client_ip_;
		time_t		client_time_;

		// サーミスタ定義
		// A/D: 12 bits, NT103_41G, 分圧抵抗: 10K オーム、サーミスタ: ＶＣＣ側
		typedef chip::NTCTH<4095, chip::thermistor::NT103_41G, 10000, true> THMISTER;
		THMISTER thmister_;

		write_file	write_file_;

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


		void send_info_(int fd, int id, bool keep)
		{
			format("HTTP/1.1 %d OK\n", fd) % id;
			format("Server: seeda/rx64m\n", fd);
			format("Content-Type: text/html\n", fd);
			format("Connection: %s\n\n", fd) % (keep == true ? "keep-alive" : "close");
		}


		void send_head_(int fd, const char* title)
		{
			format("<head>\n", fd);
			format("<title>SEEDA %s</title>\n", fd) % title;
			format("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n", fd);
			format("<meta http-equiv=\"Pragma\" content=\"no-cache\">\n", fd);
			format("<meta http-equiv=\"Cache-Control\" content=\"no-cache\">\n", fd);
			format("<meta http-equiv=\"Expires\" content=\"0\">\n", fd);
			format("</head>\n", fd);
		}


		// クライアントからの応答を解析して終端（空行）があったら「true」
		int analize_request_()
		{
			char tmp[512];
			int len = server_.read(tmp, sizeof(tmp));

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


		void select_cgi_(int fd, const char* path, int pos)
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
//				cgi.list();
			} else if(strcmp(path, "/cgi/set_client.cgi") == 0) {
				typedef utils::parse_cgi_post<256, 1> CGI_IP;
				CGI_IP cgi;
				cgi.parse(body);
				for(uint32_t i = 0; i < cgi.size(); ++i) {
					const auto& t = cgi.get_unit(i);
					if(strcmp(t.key, "ip") == 0) {
						utils::format("Set client IP: '%s'\n") % t.val;
						client_ip_.from_string(t.val);
						// restart service_client...
						client_task_ = client_task::disconnect;
					}
				}
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
			}
		}


#if 0
		// POST などの空行以下のデータ列を受け取る
		bool recv_data_(char* recv, uint32_t max)
		{
			int len = base.read(recv, max);
			if(len <= 0) return false;

			return true;
		}
#endif


		void render_404_(int fd, const char* msg)
		{
			send_info_(fd, 404, false);
		}


		void render_null_(int fd, const char* title = nullptr)
		{
			send_info_(fd, 200, false);

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			send_head_(fd, "NULL");

			if(title != nullptr) {
				format(title, fd);
			}
			format("</html>\n", fd);
		}


		void render_date_time_(int fd)
		{
			char tmp[128];
			time_t t = get_time();
			disp_time(t, tmp, sizeof(tmp));
			format("%s<br>\n", fd) % tmp;
		}


		// ビルドバージョン表示
		void render_version_(int fd)
		{
			format("Seeda03 Build: %u Version %d.%02d<br>\n", fd) % build_id_
				% (seeda_version_ / 100) % (seeda_version_ % 100);
		}


		void render_root_(int fd)
		{
			send_info_(fd, 200, false);

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			send_head_(fd, "Root/SimpleData");

			// コネクション回数表示
			format("Conection: %d<br>\n", fd) % count_;

			render_date_time_(fd);

			format("Sampling: 1[ms]<br>\n", fd);

			make_adc_csv_(fd, "<br>\n");

			format("</html>\n", fd);
		}


		// メイン設定画面
		void render_setup_main_(int fd)
		{
			send_info_(fd, 200, false);

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			send_head_(fd, "SetupMain");

			render_version_(fd);

			render_date_time_(fd);

			format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);

			format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"リロード\" />\n", fd);
			format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);

			format("<input type=\"button\" onclick=\"location.href='/data'\" value=\"データ表示\" />\n", fd);
			format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);

			{  // 内臓 A/D 表示
				float v = static_cast<float>(get_adc(5)) / 4095.0f * 3.3f;
				format("バックアップ電池電圧： %4.2f [V]<br>\n", fd) % v;
				format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);
			}

			// RTC 設定
			{
				format("<form method=\"POST\" action=\"/cgi/set_rtc.cgi\"><table>\n", fd);
				auto t = get_time();
				struct tm *m = localtime(&t);
				format("<tr>"
					"<td>年月日(yyyy/mm/dd)：</td>"
					"<td><input type=\"text\" name=\"date\" size=\"10\" value=\"%d/%d/%d\"></td></tr>\n", fd)
					% static_cast<int>(m->tm_year + 1900)
					% static_cast<int>(m->tm_mon + 1) % static_cast<int>(m->tm_mday);
				format("<tr>"
					"<td>時間(hh:mm[:ss])：</td>"
					"<td><input type=\"text\" name=\"time\" size=\"8\" value=\"%d:%d\"></td></tr>\n", fd)
					% static_cast<int>(m->tm_hour) % static_cast<int>(m->tm_min);
				format("<tr><td><input type=\"submit\" value=\"ＲＴＣ設定\"></td></tr>\n", fd);
				format("</table></form>\n", fd);
				format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);
			}

			// Ａ／Ｄ変換設定
			{
				format("<form method=\"POST\" action=\"/cgi/set_adc.cgi\"><table>\n", fd);
				for(int ch = 0; ch < 8; ++ch) {
					const seeda::sample_t& t = at_sample(ch);
					format("<tr>"
						"<td>CH%d</td>"
						"<td><input type=\"radio\" name=\"mode%d\" value=\"none\"%s>数値</td>"
						"<td><input type=\"radio\" name=\"mode%d\" value=\"real\"%s>係数</td>"
						"<td>ゲイン：</td>"
						"<td><input type=\"text\" name=\"gain%d\" size=\"6\" value=\"%6.2f\"></td>"
						"<td>オフセット：</td>"
						"<td><input type=\"text\" name=\"offset%d\" size=\"6\" value=\"%6.2f\"></td>"
						"<td>下限：</td>"
						"<td><input type=\"text\" name=\"level_lo%d\" size=\"6\" value=\"%d\"></td>"
						"<td>上限：</td>"
						"<td><input type=\"text\" name=\"level_hi%d\" size=\"6\" value=\"%d\"></td>"
						"</tr>\n", fd)
						% ch
						% ch % (t.mode_ == seeda::sample_t::mode::none ? " checked" : "")
						% ch % (t.mode_ == seeda::sample_t::mode::real ? " checked" : "")
						% ch % t.gain_
						% ch % t.offset_
						% ch % static_cast<int>(t.limit_lo_level_)
						% ch % static_cast<int>(t.limit_hi_level_);
				}
				format("<tr><td><input type=\"submit\" value=\"設定\"></td></tr>\n", fd);
				format("</table></form>\n", fd);
				format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);
			}

			{  // ＳＤカード操作画面へのボタン
				format("<input type=\"button\" onclick=\"location.href='/files'\" value=\"ＳＤカード\">\n",
					fd);
				format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);
			}

			{  // クライアント設定ボタン
				format("<input type=\"button\" onclick=\"location.href='/client'\" value=\"クライアント\">\n",
					fd);
				format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);
			}

			{  // ファイル書き込み設定
				format("<form method=\"POST\" action=\"/cgi/set_write.cgi\">\n", fd);
				format("<table><tr><td>ファイル名：</td>", fd);
				if(!write_file_.get_enable()) {
					format("<td><input type=\"text\" name=\"fname\" size=\"16\" value=\"%s\"></td></tr>\n", fd)
						% write_file_.get_path();
				} else {
					format("<td>%s</td></tr>\n", fd) % write_file_.get_path();
				}
				format("<tr><td>書き込み時間（秒）：</td>", fd);
				if(!write_file_.get_enable()) {
					format("<td><input type=\"text\" name=\"count\" size=\"16\" value=\"%d\"></td></tr>\n", fd)
						% write_file_.get_limit();
					format("<tr><td><input type=\"submit\" value=\"書き込み開始\"></td></tr>\n", fd);
				} else {
					format("<td>%d/%d</td></tr>\n", fd) % write_file_.get_resume() % write_file_.get_limit();
					format("<tr><td><input type=\"submit\" value=\"書き込み停止\"></td></tr>\n", fd);
				}
				format("</table></form>\n", fd);

				format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);
			}

			format("</html>\n", fd);
		}


		// クライアント設定画面
		void render_setup_client_(int fd)
		{
			send_info_(fd, 200, false);

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			send_head_(fd, "SetupClient");

			render_version_(fd);

			render_date_time_(fd);

			format("<hr align=\"left\" width=\"400\" size=\"3\" />\n", fd);

			// クライアント
			format("<form method=\"POST\" action=\"/cgi/set_client.cgi\">\n", fd);
			format("<div>クライアント IP：<input type=\"text\" name=\"ip\" size=\"15\" value=\"%d.%d.%d.%d\" /></div>\n", fd)
				% static_cast<int>(client_ip_[0])
				% static_cast<int>(client_ip_[1])
				% static_cast<int>(client_ip_[2])
				% static_cast<int>(client_ip_[3]);
			format("<input type=\"submit\" value=\"クライアント設定\" />\n", fd);
			format("</form>\n", fd);

			format("</html>\n", fd);
		}


		void render_files_(int fd)
		{
			send_info_(fd, 200, false);

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			send_head_(fd, "SD Files");

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
			format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);
			format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定\" />\n", fd);

			format("</html>\n", fd);
		}


		void render_data_(int fd)
		{
			send_info_(fd, 200, false);
			// format("Refresh: 5\n", fd);  // refresh the page automatically every 5 sec

			format("<!DOCTYPE HTML>\n", fd);
			format("<html>\n", fd);
			send_head_(fd, "Data");

			format("<font size=\"4\">\n", fd);
			// コネクション回数表示
			format("Conection: %d<br>\n", fd) % count_;

			render_date_time_(fd);

			format("サンプリング周期： 1[ms]<br>\n", fd);

			format("</font>\n", fd);

			{  // 内臓 A/D 表示（湿度、温度）
				auto v = get_adc(6);
				format("温度： %5.2f [度]\n", fd) % thmister_(v);
				format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);
			}

			format("<style type=\"text/css\">\n", fd);
			format(".table5 {\n", fd);
			format("  border-collapse: collapse;\n", fd);
			format("  width: 600px;\n", fd);
			format("}\n", fd);
			format(".table5 th {\n", fd);
			format("  background-color: #cccccc;\n", fd);
			format("}\n", fd);
			format(".table5 td {\n", fd);
			format("  text-align: center;\n", fd);
			format("}\n", fd);
			format("</style>\n", fd);

			format("<table class=\"table5\" border=1>\n", fd);
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

			format("<hr align=\"left\" width=\"600\" size=\"3\" />\n", fd);
			format("<input type=\"button\" onclick=\"location.href='/setup'\" value=\"設定\" />\n", fd);

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


		void make_client_data_(char* dst)
		{
#if 0
			t = get_time();
			if(client_time_ == t) break;
			client_time_ = t;
			{
				char tmp[128];
				time_t t = get_time();
				disp_time(t, tmp, sizeof(tmp));
				format("%s", client_.get_cepid()) % tmp;
			}
			for(int ch = 0; ch < 8; ++ch) {
				const auto& t = get_sample(ch);
				format("%d,%d,%d,%d,%d,%d,%d,%d,%d%s", base.get_cepid())
					% ch
					% static_cast<uint32_t>(t.min_)
					% static_cast<uint32_t>(t.max_)
					% static_cast<uint32_t>(t.average_)
					% static_cast<uint32_t>(t.limit_lo_level_)
					% static_cast<uint32_t>(t.limit_lo_count_)
					% static_cast<uint32_t>(t.limit_hi_level_)
					% static_cast<uint32_t>(t.limit_hi_count_)
					% static_cast<uint32_t>(t.median_)
					% tail;
			}
#endif
		}


		// 指定のアドレス、ポートに定期的に、Ａ／Ｄ変換データを送る。
		void service_client_()
		{
			time_t t;
			switch(client_task_) {

			case client_task::connect:
				if(client_.connect(client_ip_, client_port_, TMO_NBLK) == 1) {
					utils::format("Start SEEDA03 Client: %s port(%d), fd(%d)\n")
						% client_ip_.c_str() % client_port_ % client_.get_cepid();
					client_timeout_ = 5 * 100;  // 5 sec
					client_task_ = client_task::wait_connect;
				}
				break;

			case client_task::wait_connect:
				if(client_.connected()) {
					utils::format("Client Conected: %s\n") % client_ip_.c_str();
					client_time_ = get_time();
					client_task_ = client_task::main_loop;
				}
				if(client_timeout_) {
					--client_timeout_;
				} else {
///					client_task_ = client_task::disconnect;
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
					format("%s\n", client_.get_cepid()) % tmp;
				}
				{
					make_adc_csv_(client_.get_cepid(), "\n");
				}
				break;
			
			case client_task::disconnect:
				client_.stop();
				utils::format("Client disconnected: %s\n") % client_ip_.c_str();
				client_task_ = client_task::delay_connection;
				break;

			case client_task::delay_connection:
				client_delay_ = 50;  // 0.5sec
				client_task_ = client_task::delay_loop;
				break;

			case client_task::delay_loop:
				if(client_delay_) {
					--client_delay_;
				} else {
					client_task_ = client_task::connect;
				}
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		nets() : server_(ethernet_), client_(ethernet_), ftp_(ethernet_, at_sdc()),
			count_(0), server_task_(server_task::begin_http),
			client_task_(client_task::connect), client_port_(3000), client_delay_(0), client_timeout_(0),
			line_man_(0x0a), disconnect_loop_(0),
#ifdef SEEDA
			client_ip_(192, 168, 1, 3),
#else
			client_ip_(192, 168, 3, 7),
#endif
			client_time_(0),

			write_file_()
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
					line_man_.clear();
					server_task_ = server_task::main_loop;
				}
				break;

			case server_task::main_loop:
				if(server_.connected()) {

					if(server_.available() == 0) {  // リードデータがあるか？
						break;
					}
					int fd = server_.get_cepid();
					auto pos = analize_request_();
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
							render_root_(fd);
						} else if(strncmp(path, "/cgi/", 5) == 0) {
							select_cgi_(fd, path, pos);
							render_setup_main_(fd);
						} else if(strcmp(path, "/data") == 0) {
							render_data_(fd);
						} else if(strcmp(path, "/setup") == 0) {
							render_setup_main_(fd);
						} else if(strcmp(path, "/client") == 0) {
							render_setup_client_(fd);
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

			service_client_();

			ftp_.service();

			write_file_.service();
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
