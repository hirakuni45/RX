#pragma once
//=====================================================================//
/*!	@file
	@brief	TELNET サーバー・クラス @n
		0xF0	[Sub-negotiaon End] ２次交渉終了  ２次交渉パラメータの終了 @n
		0xF1	[No Operation] オペレーションなし オペレーションなし。受信した側はこれを無視する @n
		0xF2	[Data Mark] データマーク          データ削除・リセット @n
		0xF3	[Break] ブレーク	              ブレーク @n
		0xF4	[Interrupt Process] プロセス中断  操作の一時中断・割り込み・停止 @n
		0xF5	[Abort Output] 出力中止	          出力を抑止する @n
		0xF6	[Are You There] 相手確認          相手が動作しているかどうか確認する @n
		0xF7	[Erase Character] 文字消去        最後の文字を消去する @n
		0xF8	[Erase Line] 行消去               最後の行をすべて消去する @n
		0xF9	[Go Ahead] 送信勧誘               送信するように受信側にうながす @n
		0xFA	[Sub-negotiation Begin] ２次交渉開始  ２次交渉の開始 @n
		0xFB	WILL	オプション希望 @n
		0xFC	WON'T	オプション拒絶 @n
		0xFD	DO	オプション実行要求 @n
		0xFE	DON'T	オプション使用中止 @n
		0xFF	[Interpret as Command] コマンドとして解釈	telnetエスケープシーケンス @n
		オプション・コード @n
		0x00	[Transmit Binary] バイナリ転送	IAC以外の文字列はバイナリデータと解釈される @n
		0x01	[Echo] エコー	データのエコー @n
		0x03	[Suppress Go Ahead] Go Ahead抑止    Go Aheadコマンドを使わないようにする @n
		0x05	[Telnet Status Option] telnet状態オプション	相手側のtelnetオプションの状態を見られるようにする @n
		0x06	[Telnet Timing Mark] telnetタイミングマーク	受信したデータが処理済ならばタイミングマークというデータを送る @n
		0x18	[Terminal Type] ターミナルタイプ    ターミナルタイプを交換可能にし、適切なターミナルタイプを設定する @n
		0x22	[Telnet Line Mode] telnetラインモード    行単位で転送できるようにする
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "ethernet_server.hpp"
#include "common/fixed_fifo.hpp"

#define TELNETS_DEBUG

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  telnet_server class テンプレート
		@param[in]	SEND_SIZE	送信、一時バッファサイズ
		@param[in]	RECV_SIZE	受信、一時バッファサイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t SEND_SIZE, uint32_t RECV_SIZE>
	class telnet_server {

	private:
		// デバッグ以外で出力を無効にする
#ifdef TELNETS_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

		ethernet&		eth_;
		ethernet_server	telnet_;
		uint16_t		port_;

		enum class task : uint8_t {
			none,
			begin,
			wait,
			main_loop,
			disconnect_delay,
			disconnect,
		};
		task		task_;

		char		server_name_[32];
		char		user_[32];
		char		pass_[32];
		uint32_t	count_;
		uint32_t	disconnect_loop_;

		typedef utils::fixed_fifo<char, SEND_SIZE> SEND_FIFO;
		typedef utils::fixed_fifo<char, RECV_SIZE> RECV_FIFO;

		SEND_FIFO	send_;
		RECV_FIFO	recv_;

		bool		crlf_;

		char		line_[RECV_SIZE];
		char		line_copy_[RECV_SIZE];
		uint32_t	line_pos_;


		enum class esc_task : uint8_t {
			none,
			entry,
			option,
			second,
			second_end,
		};
		esc_task	esc_task_;

		void write_()
		{
			char tmp[1024];
			uint16_t l = 0;
			while(send_.length() > 0) {
				auto ch = send_.get();
				tmp[l] = ch;
				++l;
				if(l >= sizeof(tmp)) {
					telnet_.write(tmp, l);
					
					l = 0;
				}
			}
			if(l > 0) {
				telnet_.write(tmp, l);
			}
		}


		bool service_options_(char ch)
		{
			bool ret = true;
			switch(esc_task_) {
			case esc_task::entry:
				if(ch == 0xFB || ch == 0xFC || ch == 0xFD || ch == 0xFE) {
					esc_task_ = esc_task::option;
					ret = false;
				} else if(ch == 0xFA) {  // 二次交渉開始
					esc_task_ = esc_task::second;
					ret = false;
				}
				break;
			case esc_task::option:
				esc_task_ = esc_task::none;
				ret = false;
				break;
			case esc_task::second:
				if(ch == 0xFF) {
					esc_task_ = esc_task::second_end;
				}
				ret = false;
				break;
			case esc_task::second_end:
				if(ch == 0xF0) {
					esc_task_ = esc_task::none;
				}
				ret = false;
				break;

			case esc_task::none:
			default:
				if(ch == 0xFF) {  // TELNET ESC シーケンス開始
					esc_task_ = esc_task::entry;
					ret = false;
				}
				break;
			}
			return ret;
		}

		bool service_line_()
		{
			while(length() > 0) {
				auto ch = getch();
				if(ch == 0x00) {  // TERM
					line_[line_pos_] = 0;
					strcpy(line_copy_, line_);
					line_pos_ = 0;
					return true;
				} else if(ch == '\n') {  // LF 
				} else if(ch == '\r') {  // CR
				} else if(ch == 0x08) {  // BS
					if(line_pos_ > 0) {
						--line_pos_;
					}
				} else if(ch >= ' ') {
					if(line_pos_ < (sizeof(line_) - 1)) {
						line_[line_pos_] = ch;
						++line_pos_;
					}
				}
			}
			return false;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	e	イーサーネット・コンテキスト
			@param[in]	crlf	LF コードを CR/LF に変換しない場合「false」
			@param[in]	port	TELNET ポート番号（通常２３番）
		*/
		//-----------------------------------------------------------------//
		telnet_server(ethernet& e, bool crlf = true, uint16_t port = 23) :
			eth_(e), telnet_(e), port_(port),
			task_(task::none),
			server_name_{ 0 }, user_{ 0 }, pass_{ 0 },
			count_(0), disconnect_loop_(0), crlf_(crlf),
			line_{ 0 }, line_copy_{ 0 }, line_pos_(0),
			esc_task_(esc_task::none)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  スタート
			@param[in]	server_name	サーバー名
			@param[in]	user		ユーザー名
			@param[in]	pass		パスワード
		*/
		//-----------------------------------------------------------------//
		void start(const char* server_name, const char* user = nullptr, const char* pass = nullptr)
		{
			std::strncpy(server_name_, server_name, sizeof(server_name_) - 1);
			if(user != nullptr) std::strncpy(user_, user, sizeof(user_) - 1);
			if(pass != nullptr) std::strncpy(pass_, pass, sizeof(pass_) - 1);

			count_ = 0;
			disconnect_loop_ = 0;
			esc_task_ = esc_task::none;

			task_ = task::begin;

			line_pos_ = 0;

			debug_format("TELNET Server: SEND_BUFF: %d, RECV_BUFF: %d\n") % SEND_SIZE % RECV_SIZE;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  接続の確認
			@return 接続していれば「true」
		*/
		//-----------------------------------------------------------------//
		bool probe() const { return task_ == task::main_loop; }


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
			@param[in]	cycle	サービス・サイクル（通常１００Ｈｚ）
			@param[in]	lns		ライン・サービスを行う場合「true」
			@return 改行されたら「true」
		*/
		//-----------------------------------------------------------------//
		bool service(uint32_t cycle, bool lns = false)
		{
			bool ret = false;
			switch(task_) {
			case task::none:
				break;

			case task::begin:
				telnet_.begin(port_);
				debug_format("Start TELNET Server: '%s' port(%d), fd(%d)\n")
					% eth_.get_local_ip().c_str()
					% static_cast<int>(telnet_.get_port()) % telnet_.get_cepid();
				task_ = task::wait;
				break;

			case task::wait:
				if(telnet_.connected()) {
					debug_format("TELNET Server: New connected, from: %s\n")
						% telnet_.get_from_ip().c_str();
					++count_;
					line_pos_ = 0;
					task_ = task::main_loop;
				}
				break;

			case task::main_loop:
				if(telnet_.connected()) {
					if(telnet_.available() > 0) {  // リードデータがあるか？
						char tmp[256];
						int len = telnet_.read(tmp, sizeof(tmp));
						if(len > 0) {
							int l = 0;
							while((recv_.size() - recv_.length()) > 2) {
								char ch = tmp[l];
								++l;
								if(service_options_(ch)) {
///									putch(ch);  // local echo
/// utils::format("%d: %02X\n") % l % static_cast<uint16_t>(ch);
									recv_.put(ch);
								}
								if(l >= len) break;
							}
						}
					}
					if(lns) {
						ret = service_line_();
					}
					write_();
				} else {
					task_ = task::disconnect_delay;
					disconnect_loop_ = 10;
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
				telnet_.stop();
				debug_format("TELNET Server: disconnected\n");
				task_ = task::begin;
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  出力
			@param[in]	ch	出力文字
		*/
		//-----------------------------------------------------------------//
		void putch(char ch)
		{
			if(!probe()) return;

			if(crlf_ && ch == '\n') {
				putch('\r');
			}
			if(task_ == task::main_loop) {
				if((send_.size() - send_.length()) <= 2) {
					write_();
				}
				send_.put(ch);
//				if(ch == '\r') {
//					flush_();
//				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  出力
			@param[in]	str	出力文字列
		*/
		//-----------------------------------------------------------------//
		void puts(const char* str)
		{
			if(str == nullptr) return;

			char ch;
			while((ch = *str++) != 0) {
				putch(ch);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  入力文字数取得
			@return 入力文字数
		*/
		//-----------------------------------------------------------------//
		uint32_t length() const
		{
			return recv_.length();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  入力文字取得
			@return 入力文字（入力文字が無い場合「０」が返る）
		*/
		//-----------------------------------------------------------------//
		char getch()
		{
			if(recv_.length() > 0) {
				return recv_.get();
			} else {
				return 0;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  行を取得
			@return 行
		*/
		//-----------------------------------------------------------------//
		const char* get_line() const { return line_copy_; }
	};
}

