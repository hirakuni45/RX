#pragma once
//=========================================================================//
/*! @file
    @brief  TCP Protocol @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "net2/net_st.hpp"
#include "common/fixed_block.hpp"

#define TCP_DEBUG

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TCP クラス
		@param[in]	ETHD	イーサーネット・ドライバー・クラス
		@param[in]	NMAX	管理最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHD, uint32_t NMAX>
	class tcp {
	public:
		static const int OPEN_FAIL_PORT          = -1;  ///< 不正なポート番号
		static const int OPEN_FAIL_ADRS          = -2;	///< 不正なアドレス
		static const int OPEN_FAIL_ANY           = -3;  ///< クライアントでは、「ANY」は不正
		static const int OPEN_FAIL_EVEN_PORT     = -4;  ///< 既にそのポート番号は利用されている
		static const int OPEN_FAIL_CONTEXT_EMPTY = -5;  ///< コンテキストが無い

	private:
#ifndef TCP_DEBUG
		typedef utils::null_format debug_format;
#else
		typedef utils::format debug_format;
#endif

		static const uint16_t TIME_OUT = 5 * 1000 / 10;  // 5 sec (unit: 10ms)
		static const uint16_t RESEND_WAIT    = 1 * 1000 / 10;  // 1 sec (unit: 10ms)
		static const uint16_t CLOSE_TIME_OUT = 5 * 1000 / 10;  // 5 sec (unit: 10ms)

		ETHD&		ethd_;

		net_info&	info_;

		uint32_t	master_seq_;

		uint16_t	ethd_max_;

		int			last_error_;

		enum class recv_task : uint8_t {
			idle,

			listen_server,
			syn_rcvd,
			established_server,

			listen_client,
			syn_cent,
			established_client,
			fin_wait1,
			fin_wait2,
			time_wait,

			sync_close,
			close,
		};

		enum class send_task : uint8_t {
			idle,
			sync_mac,

			main,

			sync_close,
		};

		typedef memory<4096>  RECV_B;
		typedef memory<4096>  SEND_B;

		struct context {
			ip_adrs		adrs_;
			uint8_t		mac_[6];
			uint16_t	cn_port_;
			uint16_t	port_;
			uint16_t	recv_time_;
			uint16_t	send_time_;

			// IPV4 関係
			uint16_t	id_;
			uint16_t	offset_;
			uint8_t		life_;

			send_task	send_task_;

			RECV_B		recv_;
			SEND_B		send_;

			uint32_t	seq_;
			uint32_t	ack_;
			uint32_t	send_seq_;
			uint32_t	send_ack_;
			uint16_t	flags_;
			uint16_t	window_;
			uint16_t	urgent_ptr_;
			uint16_t	timeout_;

			volatile uint16_t	send_len_;
			volatile uint16_t	send_wait_;
			volatile recv_task	recv_task_;
			volatile bool		server_;
			volatile bool		fin_;
			bool	close_req_;

			void reset(const ip_adrs& adrs, uint16_t port, bool server)
			{
				adrs_ = adrs;
				std::memset(mac_, 0x00, 6);
				cn_port_ = port;
				port_ = 0;  // 初期は「０」
				recv_time_ = TIME_OUT;
				send_time_ = TIME_OUT;
				id_ = 0;  // 識別子の初期値
				life_ = 255;  // 生存時間初期値（ルーターの通過台数）
				offset_ = 0;  // フラグメント・オフセット

				send_task_ = send_task::idle;

				recv_.clear();
				send_.clear();

				seq_ = 0;
				ack_ = 0;
				send_seq_ = 0;
				send_ack_ = 0;
				flags_ = 0x00;
				window_ = 0xffff;
				urgent_ptr_ = 0;
				timeout_ = 0;
				send_len_ = 0;
				send_wait_ = 0;

				recv_task_ = recv_task::idle;
				server_ = server;

				fin_ = false;

				close_req_ = false;
			}
		};

		typedef udp_tcp_common<context, NMAX> COMMON;
		COMMON		common_;


		struct frame_t {
			eth_h	eh_;
			ipv4_h	ipv4_;
			tcp_h	tcp_;
		} __attribute__((__packed__));


		// TCP checksum header 
		struct csum_h {
			ip_adrs		src_;
			ip_adrs		dst_;
			uint16_t	fix_;
			uint16_t	len_;
		};


		uint16_t make_tcp_frame_(context& ctx, const uint8_t* dst_mac, const uint8_t* dst_ip, frame_t& t)
		{
			t.eh_.set_dst(dst_mac);  // 転送先の MAC
			t.eh_.set_src(info_.mac);      // 転送元の MAC
			t.eh_.set_type(eth_type::IPV4);

			uint16_t all = sizeof(frame_t);
			uint8_t* p = reinterpret_cast<uint8_t*>(&t) + all;

			// 送信データを上乗せする場合
			uint16_t data_len = 0;
			if(ctx.send_len_ == 0 && ctx.recv_task_ == recv_task::established_server
			  && ctx.send_task_ == send_task::main) {
				data_len = ctx.send_.length();
				if(data_len > 0) {
					uint16_t max_len = ethd_max_ - sizeof(frame_t);
					if(max_len < data_len) {
						data_len = max_len;
					}
					ctx.send_len_ = data_len;
					ctx.send_.get(p, data_len, false);
///					debug_format("Send step ORG: 0x%08X, %d\n") % ctx.seq_ % data_len;
					all += data_len;
					p += data_len;
					ctx.flags_ |= tcp_h::MASK_PSH;

					t.tcp_.set_seq(ctx.send_seq_);
					t.tcp_.set_ack(ctx.send_ack_);

					ctx.send_wait_ = RESEND_WAIT;  // ACK が返らない場合の、再送待ち時間
				}
			} else {
				t.tcp_.set_seq(ctx.seq_);
				t.tcp_.set_ack(ctx.ack_);
			}

			t.ipv4_.set_ver_hlen(0x45);
			t.ipv4_.set_type(0x00);
			t.ipv4_.set_length(all - sizeof(eth_h));
			t.ipv4_.set_id(ctx.id_);
			t.ipv4_.set_f_offset(ctx.offset_);
			t.ipv4_.set_life(ctx.life_);
			t.ipv4_.set_protocol(ipv4_h::protocol::TCP);
			t.ipv4_.set_csum(0);
			t.ipv4_.set_src_ipa(info_.ip.get());
			t.ipv4_.set_dst_ipa(dst_ip);
			t.ipv4_.set_csum(tools::calc_sum(&t.ipv4_, sizeof(ipv4_h)));

			uint16_t tcp_len = all - sizeof(eth_h) - sizeof(ipv4_h);
			t.tcp_.set_src_port(ctx.cn_port_);
			t.tcp_.set_dst_port(ctx.port_);
			t.tcp_.set_length(tcp_len - data_len);  // TCP Header Length
			t.tcp_.set_flags(ctx.flags_);
			t.tcp_.set_window(ctx.window_);
			t.tcp_.set_csum(0x0000);
			t.tcp_.set_urgent_ptr(ctx.urgent_ptr_);

			csum_h smh;
			smh.src_.set(info_.ip.get());
			smh.dst_.set(dst_ip);
			smh.fix_ = 0x0600;
			smh.len_ = tools::htons(tcp_len);
			uint16_t sum = tools::calc_sum(&smh, sizeof(csum_h));
			sum = tools::calc_sum(&t.tcp_, tcp_len, ~sum);
			t.tcp_.set_csum(sum);
			// ６０バイトに満たない場合は、ダミー・データ（０）を追加する。
			while(all < 60) {
				*p++ = 0;
				++all;
			}
			return all;
		}


		frame_t* get_send_frame_()
		{
			void* dst;
			if(ethd_.send_buff(&dst, ethd_max_) != 0) {
				debug_format("TCP Frame ether_io fail\n");
				return nullptr;
			}
			return static_cast<frame_t*>(dst);
		}


		void send_close_ack_(context& ctx, const uint8_t* dst_mac, const uint8_t* dst_ip, const tcp_h* tcp)
		{
			frame_t* t = get_send_frame_();
			if(t == nullptr) {
				return;
			}
			ctx.seq_ = tcp->get_ack();
			ctx.ack_ = tcp->get_seq() + 1;
			ctx.flags_ = tcp_h::MASK_FIN | tcp_h::MASK_ACK;
			auto all = make_tcp_frame_(ctx, dst_mac, dst_ip, *t);
			ethd_.send(all);
		}


		bool recv_(context& ctx, const eth_h& eh, const ipv4_h& ih, const tcp_h* tcp)
		{
			// TCP サムの計算
			uint16_t len = ih.get_length() - sizeof(ipv4_h);
			csum_h smh;
			smh.src_.set(ih.get_src_ipa());
			smh.dst_.set(ih.get_dst_ipa());
			smh.fix_ = 0x0600;
			smh.len_ = tools::htons(len);
			uint16_t sum = tools::calc_sum(&smh, sizeof(smh));
			sum = tools::calc_sum(tcp, len, ~sum);
			if(sum != 0) {
				utils::format("\nTCP Frame(%d) sum error: %04X -> %04X\n")
					% len % tcp->get_csum() % sum;
				return false;
			}
			uint16_t data_len = len - tcp->get_length();

			switch(ctx.recv_task_) {

			case recv_task::listen_server:
				if(tcp->get_flag_syn()) {
					frame_t* t = get_send_frame_();
					if(t == nullptr) {
						return false;
					}
					ctx.seq_ = master_seq_;  // start seq
					ctx.ack_ = tcp->get_seq() + 1;
					ctx.flags_ = tcp_h::MASK_SYN | tcp_h::MASK_ACK;
					auto all = make_tcp_frame_(ctx, eh.get_src(), ih.get_src_ipa(), *t);
					ethd_.send(all);
					ctx.timeout_ = 0;
					ctx.recv_task_ = recv_task::syn_rcvd;
				}
				if(tcp->get_flag_fin()) {
					ctx.fin_ = true;
					send_close_ack_(ctx, eh.get_src(), ih.get_src_ipa(), tcp);
					ctx.recv_task_ = recv_task::sync_close;
				}
				break;

			case recv_task::syn_rcvd:
				if(tcp->get_flag_ack() && tcp->get_seq() == ctx.ack_ && tcp->get_ack() > ctx.seq_) {
					ctx.timeout_ = 0;
					ctx.recv_task_ = recv_task::established_server;
				}
				if(tcp->get_flag_fin()) {
					ctx.fin_ = true;
					send_close_ack_(ctx, eh.get_src(), ih.get_src_ipa(), tcp);
					ctx.recv_task_ = recv_task::sync_close;
				}
				++ctx.timeout_;
				break;

			case recv_task::established_server:
				if(tcp->get_flag_ack()) {
					if(ctx.send_len_ > 0) {  // 転送データの ACK 確認
// utils::format("Send SEQ: %08X, ACK: %08X\n") % ctx.send_seq_ % ctx.send_ack_;
// dump(*tcp, " (Data ACK)");
						if(tcp->get_seq() == ctx.send_ack_ &&
						   tcp->get_ack() >= (ctx.send_seq_ + ctx.send_len_)) {
//							debug_format("Send step END: 0x%08X, %d\n") % ctx.seq_ % ctx.send_len_;
							ctx.send_.get_go(ctx.send_len_);
							ctx.send_len_ = 0;
							ctx.send_wait_ = 0;
						}
					}
				} else {
					// 転送データの再送を行うか？
					if(ctx.send_len_ > 0) {

					}
				}
				if(tcp->get_flag_psh()) {
					if(data_len > 0 && data_len < (ctx.recv_.size() - ctx.recv_.length() - 1)) {
						const uint8_t* org = reinterpret_cast<const uint8_t*>(tcp);
						org += tcp->get_length();
						ctx.recv_.put(org, data_len);

						// データ受信に対するアクノリッジの生成
						frame_t* t = get_send_frame_();
						if(t == nullptr) {
							return false;
						}
						ctx.seq_ = tcp->get_ack();
						ctx.ack_ = tcp->get_seq() + data_len;
						ctx.send_seq_ = tcp->get_ack();
						ctx.send_ack_ = tcp->get_seq() + data_len;
						master_seq_ += data_len;
						ctx.flags_ = tcp_h::MASK_ACK;
						auto all = make_tcp_frame_(ctx, eh.get_src(), ih.get_src_ipa(), *t);
						ethd_.send(all);
						ctx.timeout_ = 0;
					}
				}
				if(tcp->get_flag_fin()) {
					ctx.fin_ = true;
					send_close_ack_(ctx, eh.get_src(), ih.get_src_ipa(), tcp);
					ctx.recv_task_ = recv_task::sync_close;
				}
				break;

			case recv_task::sync_close:
				if(tcp->get_flag_ack() && tcp->get_seq() == ctx.ack_ && tcp->get_ack() > ctx.seq_) {
// dump(*tcp, " (SYNC Close)");
					master_seq_ = tcp->get_ack() + 1;
///					debug_format("Sync Close OK (seq: %d)\n") % master_seq_;
					ctx.recv_task_ = recv_task::close;
				}
				break;

			case recv_task::close:
				break;

			case recv_task::listen_client:
				break;

			default:
				break;
			}
			return true;
		}


		void send_(context& ctx)
		{
			if(ctx.recv_task_ != recv_task::established_server) {
				return;
			}

			if(ctx.send_len_ > 0) {
				return;
			}

			ethd_.enable_interrupt(false);

			uint16_t len = ctx.send_.length();
			if(len == 0) {
				ethd_.enable_interrupt();
				return;
			}

			frame_t* t = get_send_frame_();
			if(t == nullptr) {
				ethd_.enable_interrupt();
				return;
			}

			auto all = make_tcp_frame_(ctx, ctx.mac_, ctx.adrs_.get(), *t);
			ethd_.send(all);
			ctx.ack_ += 1;

			ethd_.enable_interrupt();
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	ethd	イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		tcp(ETHD& ethd, net_info& info) noexcept : ethd_(ethd), info_(info),
			master_seq_(1), ethd_max_(0), last_error_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  TCP の同時接続数を返す
			@return TCP の同時接続数
		*/
		//-----------------------------------------------------------------//
		uint32_t capacity() const noexcept { return NMAX; }


		//-----------------------------------------------------------------//
		/*!
			@brief  オープン
			@param[in]	adrs	アドレス
			@param[in]	port	ポート
			@param[in]	server	サーバーの場合「true」
			@return ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		int open(const ip_adrs& adrs, uint16_t port, bool server) noexcept
		{
			if(port == 0) {  // ０番ポートは無効
				int error = OPEN_FAIL_PORT;
				if(last_error_ != error) {
					debug_format("TCP Open fail port: %d\n") % port;
					last_error_ = error;
				}
				return error;
			}
			if(adrs.is_brodcast()) {  // ブロードキャストアドレスは無効
				int error = OPEN_FAIL_ADRS;
				if(last_error_ != error) {
					debug_format("TCP Open fail brodcast address: %s\n") % adrs.c_str();
					last_error_ = error;
				}
				return error;
			}

			if(adrs.is_any() && !server) {  // クライアント接続では、ANY アドレスは無効
				int error = OPEN_FAIL_ANY;
				if(last_error_ != error) {
					debug_format("TCP Open fail any address for client: %s\n") % adrs.c_str();
					last_error_ = error;
				}
				return error;
			}

			// 同じポートがある場合は無効
			for(uint32_t i = 0; i < NMAX; ++i) {
				if(!common_.at_blocks().is_alloc(i)) continue;
				context& ctx = common_.at_blocks().at(i);
				if(ctx.cn_port_ == port) {
					int error = OPEN_FAIL_EVEN_PORT;
					if(last_error_ != error) {
						debug_format("TCP Open fail even port as: %d\n") % port;
						last_error_ = error;
					}
					return error;
				}
			}

			// コンテキスト・スペースが無い
			uint32_t idx = common_.at_blocks().alloc();
			if(!common_.at_blocks().is_alloc(idx)) {
				int error = OPEN_FAIL_CONTEXT_EMPTY;
				if(last_error_ != error) {
					debug_format("TCP Open fail context empty\n"); 
					last_error_ = error;
				}
				return error;
			}

			last_error_ = 0;

			context& ctx = common_.at_blocks().at(idx);
			ctx.reset(adrs, port, server);

			if(!server && adrs.is_any()) {
				ctx.send_task_ = send_task::main;
			} else {
				if(common_.check_mac(ctx, info_)) {  // 既に MAC が利用可能なら「main」へ
					ctx.send_task_ = send_task::main;
				} else {
					ctx.send_task_ = send_task::sync_mac;
				}
			}
			if(server) {
				ctx.recv_task_ = recv_task::listen_server;
			} else {
				ctx.recv_task_ = recv_task::listen_client;
			}
			common_.at_blocks().unlock(idx);
			return static_cast<int>(idx);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コネクションの検査
			@param[in]	desc	ディスクリプタ
			@return 接続状態「true」、切断状態、ディスクリプタが無効「false」
		*/
		//-----------------------------------------------------------------//
		bool connection(int desc) const noexcept
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!common_.get_blocks().is_alloc(idx)) return false;

			const context& ctx = common_.get_blocks().get(idx);
			return !ctx.fin_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信
			@param[in]	desc	ディスクリプタ
			@param[in]	src		ソース
			@param[in]	len		送信バイト数
			@return 送信バイト（負の値はエラー）
		*/
		//-----------------------------------------------------------------//
		inline int send(int desc, const void* src, uint16_t len) noexcept
		{
			return common_.send(desc, src, len);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信バッファの残量取得
			@param[in]	desc	ディスクリプタ
			@return 送信バッファの残量（負の値はエラー）
		*/
		//-----------------------------------------------------------------//
		inline int get_send_length(int desc) const noexcept
		{
			return common_.get_send_length(desc);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  受信
			@param[in]	desc	ディスクリプタ
			@param[in]	dst		ソース
			@param[in]	len		受信バイト数
			@return 受信バイト（負の値はエラー）
		*/
		//-----------------------------------------------------------------//
		inline int recv(int desc, void* dst, uint16_t len) noexcept
		{
			return common_.recv(desc, dst, len);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  受信バッファの残量取得
			@param[in]	desc	ディスクリプタ
			@return 受信バッファの残量（負の値はエラー）
		*/
		//-----------------------------------------------------------------//
		inline int get_recv_length(int desc) const noexcept
		{
			return common_.get_recv_length(desc);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クローズ
			@param[in]	desc	ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		void close(int desc) noexcept
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!common_.at_blocks().is_alloc(idx)) return;

			context& ctx = common_.at_blocks().at(idx);
			ctx.close_req_ = true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  プロセス（割り込みから呼ばれる）
			@param[in]	eh	イーサーネット・ヘッダー
			@param[in]	ih	IPV4 ヘッダー
			@param[in]	tcp	TCP ヘッダー
			@param[in]	len	メッセージ長
			@return エラーが無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool process(const eth_h& eh, const ipv4_h& ih, const tcp_h* tcp, int32_t len) noexcept
		{
			// 該当するコンテキストを探す
			uint32_t idx = NMAX;
			for(uint32_t i = 0; i < NMAX; ++i) {
				if(!common_.at_blocks().is_alloc(i)) continue;  // alloc: 有効
				if(common_.at_blocks().is_lock(i)) continue;  // lock:  無効
				context& ctx = common_.at_blocks().at(i);  // コンテキスト取得

				uint16_t sum = tools::calc_sum(&ih, sizeof(ipv4_h));
				if(sum != 0) {
					debug_format("TCP IPV4 Header Sum Error: %04X -> %04X\n") % ih.get_csum() % sum;
					continue;
				}

				// 転送先の確認
				if(info_.ip != ih.get_dst_ipa()) continue;

				// 転送元の確認
				if(!ctx.adrs_.is_any() && ctx.adrs_ != ih.get_src_ipa()) continue; 

				// ポート番号の確認
				if(ctx.port_ != 0) {
					if(ctx.port_ != tcp->get_src_port()) {
						continue;
					}
				} else {
					ctx.port_ = tcp->get_src_port();
				}
				if(ctx.cn_port_ != tcp->get_dst_port()) {
					continue;
				}

				return recv_(ctx, eh, ih, tcp);
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（１０ｍｓ毎に呼ぶ）@n
					※割り込み外から呼ぶ事
		*/
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			for(uint32_t i = 0; i < NMAX; ++i) {

				if(!common_.at_blocks().is_alloc(i)) continue;

				context& ctx = common_.at_blocks().at(i);
				switch(ctx.send_task_) {
				case send_task::sync_mac:
					if(common_.check_mac(ctx, info_)) {
						ctx.send_task_ = send_task::main;
					}
					break;

				case send_task::main:
					send_(ctx);
					if(ctx.fin_) {
						ctx.send_task_ = send_task::sync_close;
						ctx.send_time_ = CLOSE_TIME_OUT;
					}
					break;

				case send_task::sync_close:
					// 送信動作、及びレシーブ動作が「クローズ」なら終了
					if(ctx.close_req_ && ctx.send_.length() == 0 && ctx.recv_task_ == recv_task::close) {
						common_.at_blocks().lock(i);  // ロックする（割り込みで利用不可にする）
						common_.at_blocks().erase(i);
					} else {
						send_(ctx);
					}
					if(ctx.send_time_ > 0) {
						ctx.send_time_--;
						if(ctx.send_time_ == 0) {
							debug_format("TCP Close TimeOut (%d)\n") % i;
						}
					} else {
						// 内部的タイムアウトでは、コンテキストを除去できない
						// 外部からのクローズ要求が必須
						if(ctx.close_req_) {
							common_.at_blocks().lock(i);  // ロックする（割り込みで利用不可にする）
							common_.at_blocks().erase(i);
						}
					}
					break;

				default:
					break;
				}
			}
		}
	};
}
