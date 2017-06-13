#pragma once
//=====================================================================//
/*!	@file
	@brief	HTTP サーバー・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include <cstring>
#include "ethernet_server.hpp"

#include "common/sdc_io.hpp"
#include "common/fixed_string.hpp"

#define HTTP_DEBUG

extern "C" {
	time_t get_time(void);
};

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  http_server class テンプレート
		@param[in]	SDC	ＳＤカードファイル操作インスタンス
		@param[in]	MAX_SIZE	一時バッファの最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDC, uint32_t MAX_SIZE = 4096>
	class http_server {
	public:
		typedef utils::line_manage<2048, 20> LINE_MAN;
		typedef utils::basic_format<ether_string<ethernet::format_id::http, MAX_SIZE> > http_format;

	private:
		// デバッグ以外で出力を無効にする
#ifdef HTTP_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

		ethernet&		eth_;

		SDC&			sdc_;

		ethernet_server	http_;

		LINE_MAN		line_man_;

		time_t			last_modified_;
		char			server_name_[32];
		uint32_t		timeout_;
		uint32_t		max_;

		uint32_t		count_;
		uint32_t		disconnect_loop_;

		enum class task : uint8_t {
			none,
			begin_http,
			wait_http,
			main_loop,
			disconnect_delay,
			disconnect,
		};
		task		task_;


		static void get_path_(const char* src, char* dst) {
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
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		http_server(ethernet& e, SDC& sdc) : eth_(e), sdc_(sdc), http_(e), line_man_(0x0a),
			last_modified_(0), server_name_{ 0 }, timeout_(15), max_(60),
			count_(0), disconnect_loop_(0),
			task_(task::none)
		{ }


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
					debug_format("HTTP Server: line_man:- memory over\n");
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
			@brief  スタート
			@param[in]	server_name	サーバー名
		*/
		//-----------------------------------------------------------------//
		void start(const char* server_name)
		{
			std::strncpy(server_name_, server_name, sizeof(server_name_) - 1);

			last_modified_ = get_time();

			http_format::chaout().set_fd(0);

			count_ = 0;
			disconnect_loop_ = 0;

			task_ = task::begin_http;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  応答メッセージの生成
			@param[in]	length	コンテンツ長（バイト）
			@param[in]	keep	セッション・キープの場合「true」
			@return 「Content-Length: 」後の位置
		*/
		//-----------------------------------------------------------------//
		uint32_t make_info(uint32_t length, bool keep = false)
		{
			uint32_t lp = 0;
			http_format("HTTP/1.1 200 OK\n");

			time_t t = get_time();
			struct tm *m = gmtime(&t);
			// Sun, 11 Jan 2004 16:06:23 GMT
			http_format("Date: %s, %02d %s %4d %02d:%02d:%02d GMT\n")
				% get_wday(m->tm_wday)
				% static_cast<uint32_t>(m->tm_mon + 1)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_year + 1900)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec);
			http_format("Server: %s\n") % server_name_;

			http_format("Last-Modified: %s,%02d %s %4d %02d:%02d:%02d GMT\n")
				% get_wday(m->tm_wday)
				% static_cast<uint32_t>(m->tm_mon + 1)
				% get_mon(m->tm_mon)
				% static_cast<uint32_t>(m->tm_year + 1900)
				% static_cast<uint32_t>(m->tm_hour)
				% static_cast<uint32_t>(m->tm_min)
				% static_cast<uint32_t>(m->tm_sec);
			http_format("Accept_ranges: bytes\n");
			if(length > 0) {
				http_format("Content-Length: %6u\n") % length;
			} else {
				http_format("Content-Length: ");
				lp = http_format::chaout().size();
				http_format("      \n");
			}
			http_format("Keep-Alive: timeout=%u,max=%u\n") % timeout_ % max_;
			http_format("Connection: %s\n") % (keep == true ? "keep-alive" : "close");
			http_format("Content-Type: text/html\n\n");
			return lp;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンテンツ・ヘッドの生成
			@param[in]	title	コンテンツのタイトル
		*/
		//-----------------------------------------------------------------//
		void make_head(const char* title)
		{
			http_format("<head>\n");
			http_format("<title>%s %s</title>\n") % server_name_ % title;
			http_format("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
			http_format("<meta http-equiv=\"Pragma\" content=\"no-cache\">\n");
			http_format("<meta http-equiv=\"Cache-Control\" content=\"no-cache\">\n");
			http_format("<meta http-equiv=\"Expires\" content=\"0\">\n");
			http_format("</head>\n");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ページのレンダリング
			@param[in]	path	ページのパス
			@param[in]	body	ページ・ボディー
		*/
		//-----------------------------------------------------------------//
		void render_page(const char* path, const char* body)
		{
			http_format::chaout().clear();

			uint32_t clp = make_info(0, false);

			uint32_t org = http_format::chaout().size();
			http_format("<!DOCTYPE HTML>\n");
			http_format("<html>\n");

			make_head("test page");

			if(body != nullptr) {
				http_format("%s\n") % body;
			}

			http_format("</html>\n");
			uint32_t len = http_format::chaout().size();

			debug_format("HTTP Server: body size: %d\n") % (len - org);

			char tmp[6 + 1];  // 数字６文字＋終端（０）
			utils::sformat("%6d", tmp, sizeof(tmp)) % (len - org);
			strncpy(&http_format::chaout().at_str()[clp], tmp, 6); // 数字部のみコピー

//			debug_format("HTTP Server: html all\n%s\n") % &http_format::chaout().at_str()[0];

			http_format::chaout().flush();  // 最終的な書き込み
		}


		void render_404page(const char* path)
		{
			render_page(path, nullptr);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	http_port	HTTP ポート番号（通常８０番）
		*/
		//-----------------------------------------------------------------//
		void service(uint16_t http_port = 80)
		{
			switch(task_) {

			case task::begin_http:
				http_.begin(http_port);
				debug_format("Start HTTP Server: '%s' port(%d), fd(%d)\n")
					% eth_.get_local_ip().c_str()
					% static_cast<int>(http_.get_port()) % http_.get_cepid();
				http_format::chaout().set_fd(http_.get_cepid());
				task_ = task::wait_http;
				break;

			case task::wait_http:
				if(http_.connected()) {
					debug_format("HTTP Server: New connected, form: %s\n") % http_.get_from_ip().c_str();
					++count_;
					line_man_.clear();
					task_ = task::main_loop;
				}
				break;

			case task::main_loop:
				if(http_.connected()) {
					if(http_.available() == 0) {  // リードデータがあるか？
						break;
					}
					char tmp[2048];
					int len = http_.read(tmp, sizeof(tmp));
// tmp[len] = 0;
// debug_format("Request: %d, '%s'\n") % len % tmp;
					auto pos = analize_request(tmp, len);
					if(pos > 0) {
						char path[256];
						path[0] = 0;
						if(!line_man_.empty()) {
							const char* t = line_man_[0];
							if(strncmp(t, "GET ", 4) == 0) {
								get_path_(t + 4, path);
								debug_format("HTTP Server: GET '%s'\n") % path;
							} else if(strncmp(t, "POST ", 5) == 0) {
								get_path_(t + 5, path);
								debug_format("HTTP Server: POST '%s'\n") % path;
							} else {
								debug_format("HTTP Server: fail key '%s'\n") % t;
							}
						} else {
							debug_format("HTTP Server: fail GET/POST data section\n");
							break;
						}
						if(strcmp(path, "/") == 0) {
							render_page(path, "asdfgh");
#if 0
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
#endif
						} else {
							char tmp[256];
							utils::sformat("HTTP Server: Invalid path: '%s'", tmp, sizeof(tmp)) % path;
							render_404page(tmp);
						}

						task_ = task::disconnect_delay;
						disconnect_loop_ = 5;
					}
				} else {
					task_ = task::disconnect_delay;
					disconnect_loop_ = 5;
				}
				break;

			case task::disconnect_delay:
				if(disconnect_loop_ > 0) {
					--disconnect_loop_;
				} else {
					task_ = task::disconnect;
				}
				break;

			case task::disconnect:
			default:
				http_.stop();
				debug_format("http disconnected\n");
				task_ = task::begin_http;
				break;
			}
		}
	};

}
