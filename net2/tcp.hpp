#pragma once
//=========================================================================//
/*! @file
    @brief  TCP Protocol
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "net2/net_st.hpp"
#include "net2/arp.hpp"
#include "common/fixed_block.hpp"

#define TCP_DEBUG

extern "C" {
	uint32_t get_counter();
}

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TCP プロトコロ・クラス
		@param[in]	ETHD	イーサーネット・ドライバー・クラス
		@param[in]	NMAX	管理最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHD, uint32_t NMAX>
	class tcp {
	public:
		typedef arp<ETHD> ARP;

	private:
#ifndef TCP_DEBUG
		typedef utils::null_format debug_format;
#else
		typedef utils::format debug_format;
#endif

		static const uint16_t SEND_MAX      = 1460;      ///< 標準的なパケットの最大数
		static const uint16_t SYN_TIMEOUT   = 30 * 100;  ///< SYN_RCVD を送って、ACK が返るまでの最大時間

		static const uint16_t RESEND_WAIT   = 90;        ///< 0.9 sec (unit: 10ms)再送
		static const uint16_t RESEND_SPAN   = 20;        ///< 再送に対する揺らぎ
		static const uint16_t RESEND_LIMIT  = 5;         ///< 再送の最大回数

		static const uint16_t CLOSE_TIME_OUT = 5 * 1000 / 10;  // 5 sec (unit: 10ms)

		ETHD&		ethd_;

		net_info&	info_;

		net_state	last_state_;


		enum class recv_task : uint8_t {
			idle,

			listen_server,

			syn_rcvd,
			syn_sent,

			established,

			sync_close,
			close,
		};


		enum class send_task : uint8_t {
			idle,

			sync_mac,
			sync_ack,

			established,

			sync_close,
			close,
		};


		struct data_info {
			uint32_t	seq_;
			uint32_t	ack_;
			uint16_t	len_;
			uint16_t	flag_;
		};

		typedef utils::fixed_fifo<data_info, ETHD::TXD_NUM + 1> SEND_INFO;
		typedef utils::fixed_fifo<data_info, ETHD::RXD_NUM + 1> RECV_INFO;

		typedef memory<4096>  RECV_B;
		typedef memory<8192>  SEND_B;

		struct context {
			uint16_t	desc_;
			uint8_t		mac_[6];
			ip_adrs		adrs_;

			volatile bool		server_;
			volatile bool		recv_fin_;
			volatile send_task	send_task_;
			volatile recv_task	recv_task_;
			bool				close_req_;
			bool				request_ip_;
			volatile uint16_t	send_wait_;
			uint16_t	resend_cnt_;

			uint16_t	src_port_;
			uint16_t	dst_port_;

			uint16_t	send_time_;

			uint16_t	send_max_;
			uint16_t	id_;
			uint16_t	offset_;
			uint8_t		life_;

			SEND_B		send_;
			RECV_B		recv_;

			SEND_INFO	send_info_;
			RECV_INFO	recv_info_;

			uint32_t	timer_ref_;
			uint32_t	net_time_ref_;

			uint32_t	recv_seq_;
			uint32_t	recv_ack_;
			uint32_t	send_seq_;
			uint32_t	send_ack_;

//			uint32_t	send_fin_ack_;
//			uint32_t	send_fin_seq_;

			uint16_t	window_;
			uint16_t	urgent_ptr_;


			void reset(uint16_t desc, const ip_adrs& adrs, uint16_t port, bool server)
			{
				desc_ = desc;
				std::memset(mac_, 0x00, 6);
				adrs_ = adrs;

				server_ = server;
				recv_fin_ = false;
				send_task_ = send_task::idle;
				recv_task_ = recv_task::idle;
				close_req_ = false;
				request_ip_ = false;
				send_wait_ = 0;
				resend_cnt_ = 0;

				if(server) {
					src_port_ = port;
					dst_port_ = 0;
				} else {
					src_port_ = tools::connect_port();
					dst_port_ = port;
				}

				send_time_ = 0;
				
				send_max_ = SEND_MAX; // 通常の最大転送バイト
				id_ = 0;              // 識別子の初期値
				life_ = 255;          // 生存時間初期値（ルーターの通過台数）
				offset_ = 0;          // フラグメント・オフセット

				send_.clear();
				recv_.clear();
				send_info_.clear();
				recv_info_.clear();

				timer_ref_ = 0;
				net_time_ref_ = 0;
				recv_seq_ = 0;
				recv_ack_ = 0;
				send_seq_ = tools::rand() & 0x7fffffff;
				send_ack_ = 0;
				window_ = 0xffff;
				urgent_ptr_ = 0;
			}
		};

		typedef udp_tcp_common<context, NMAX> COMMON;
		COMMON		common_;


		struct frame_t {
			eth_h	eh_;
			ipv4_h	ipv4_;
			tcp_h	tcp_;

			void* next(frame_t* org) {
				return static_cast<void*>(reinterpret_cast<uint8_t*>(org) + sizeof(frame_t));
			}

			const void* next(const frame_t* org) {
				return static_cast<const void*>(reinterpret_cast<const uint8_t*>(org) + sizeof(frame_t));
			}
		} __attribute__((__packed__));


		// TCP checksum header 
		struct csum_h {
			ip_adrs		src_;
			ip_adrs		dst_;
			uint16_t	fix_;
			uint16_t	len_;
		};


		uint16_t make_send_wait_()
		{
			return RESEND_WAIT - (rand() % RESEND_SPAN); 
		}


		uint32_t delta_time_(uint32_t ref)
		{
			uint32_t n = get_counter();
			uint32_t ret = 0;
			if(n > ref) {  // unit 10ms
				ret = n - ref;
			} else {
				ret = (~ref) + 1 + n;
			}
			return ret;
		}


		uint16_t make_seg_(context& ctx, const uint8_t* dst_mac, const uint8_t* dst_ip, frame_t& t, uint32_t flags, bool data)
		{
			t.eh_.set_dst(dst_mac);  // 転送先の MAC
			t.eh_.set_src(info_.mac);      // 転送元の MAC
			t.eh_.set_type(eth_type::IPV4);

			uint16_t all = sizeof(frame_t);
			uint8_t* p = reinterpret_cast<uint8_t*>(&t) + all;

			// 送信データを上乗せする場合
			uint16_t send_len = 0;
			if(data
				&& ctx.recv_task_ == recv_task::established
				&& ctx.send_task_ == send_task::established) {

				send_len = ctx.send_.length();
				if(send_len > 0) {
					if(ctx.send_max_ < send_len) {
						send_len = ctx.send_max_;
					}
					ctx.send_.get(p, send_len, false);
					debug_format("TCP %s Send: src_port(%d) dst_port(%d) %d bytes\n")
						% (ctx.server_ ? "Server" : "Client")
						% ctx.src_port_ % ctx.dst_port_
						% send_len;
					all += send_len;
/// p[send_len] = 0;
/// utils::format("%s") % (char*)p;
					p += send_len;
					flags |= tcp_h::MASK_PSH;
					ctx.send_wait_ = make_send_wait_();
					ctx.resend_cnt_ = 0;

					data_info& di = ctx.send_info_.put_at();
					di.seq_ = ctx.send_seq_;
					di.ack_ = ctx.send_ack_;
					di.len_ = send_len;
					di.flag_ = 0;
					ctx.send_info_.put_go();
				}
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
			t.tcp_.set_src_port(ctx.src_port_);
			t.tcp_.set_dst_port(ctx.dst_port_);
			t.tcp_.set_seq(ctx.send_seq_);
			t.tcp_.set_ack(ctx.send_ack_);
			t.tcp_.set_length(tcp_len - send_len);  // TCP Header Length
			t.tcp_.set_flags(flags);
			t.tcp_.set_window(ctx.window_);
			t.tcp_.set_csum(0x0000);
			t.tcp_.set_urgent_ptr(ctx.urgent_ptr_);

			// ６０バイトに満たない場合は、ダミー・データ（０）を追加する。
			while(all < 60) {
				*p++ = 0;
				++all;
			}

			csum_h smh;
			smh.src_.set(info_.ip.get());
			smh.dst_.set(dst_ip);
			smh.fix_ = 0x0600;
			smh.len_ = tools::htons(tcp_len);
			uint16_t sum = tools::calc_sum(&smh, sizeof(csum_h));
			sum = tools::calc_sum(&t.tcp_, tcp_len, ~sum);
			t.tcp_.set_csum(sum);

			return all;
		}


		frame_t* get_send_frame_()
		{
			void* dst;
			uint16_t max;
			if(ethd_.send_buff(&dst, max) != 0) {
				debug_format("TCP Frame ether_io fail\n");
				return nullptr;
			}
			return static_cast<frame_t*>(dst);
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
			uint16_t opt_len = tcp->get_length() - sizeof(tcp_h);  // TCP ヘッダー・オプション・サイズ
			uint16_t recv_len = len - tcp->get_length();  // 受信データサイズ
			uint16_t flags = 0;
			bool send = false;
			ctx.recv_seq_ = tcp->get_seq();
			ctx.recv_ack_ = tcp->get_ack();
			if(tcp->get_flag_fin()) {  // FIN 受信で、recv_fin_ を有効にする。
				ctx.recv_fin_ = true;
			}

			// 「リセット」を受けたら、強制クローズするが、SYN_RCVD、SYN_SENT の状態は除外する。
			if(tcp->get_flag_rst()) {
				if(ctx.recv_task_ != recv_task::syn_rcvd &&	ctx.recv_task_ != recv_task::syn_sent) {
					ctx.recv_task_ = recv_task::close;
					ctx.send_task_ = send_task::close;
					debug_format("TCP Recv RST to close: desc(%d)\n") % ctx.desc_;
					return false;
				}
			}

/// dump(*tcp);
			switch(ctx.recv_task_) {

			case recv_task::listen_server:
				if(ctx.server_ && ctx.adrs_.is_any()) {
					std::memcpy(ctx.mac_, eh.get_src(), 6);
					ctx.adrs_ = ih.get_src_ipa();
				}
// dump(*tcp, " (LISTEN)");
// utils::format("(LIS) RECV:   SEQ: 0x%08X, ACK: 0x%08X (%d)\n") % ctx.recv_seq_ % ctx.recv_ack_ % recv_len;
// utils::format("(LIS) SERVER: SEQ: 0x%08X, ACK: 0x%08X\n") % ctx.send_seq_ % ctx.send_ack_;
				if(tcp->get_flag_syn()) {
					send = true;
					ctx.send_ack_ = ctx.recv_seq_;
					flags |= tcp_h::MASK_SYN | tcp_h::MASK_ACK;
					++ctx.send_ack_;
					ctx.timer_ref_ = get_counter();
					ctx.recv_task_ = recv_task::syn_rcvd;
				}
				if(ctx.recv_fin_) {
					send = true;
					flags |= tcp_h::MASK_ACK;
					ctx.recv_task_ = recv_task::sync_close;
				}
				break;

			// サーバー、接続シーケンス
			case recv_task::syn_rcvd:
// utils::format("(SYN) RECV:   SEQ: 0x%08X, ACK: 0x%08X (%d)\n") % ctx.recv_seq_ % ctx.recv_ack_ % recv_len;
// utils::format("(SYN) SERVER: SEQ: 0x%08X, ACK: 0x%08X\n") % ctx.send_seq_ % ctx.send_ack_;
				if(tcp->get_flag_ack()
						&& ctx.recv_seq_ == ctx.send_ack_
						&& ctx.recv_ack_ == (ctx.send_seq_ + 1)) {
					ctx.net_time_ref_ = delta_time_(ctx.timer_ref_);
					if(ctx.net_time_ref_ == 0) ++ctx.net_time_ref_;  // ０の場合、最低値を設定
					++ctx.send_seq_;
					ctx.recv_task_ = recv_task::established;
					debug_format("TCP Connection Server: desc(%d)\n") % ctx.desc_; 
#if 0
				} else {
					++ctx.timeout_;
					if(ctx.timeout_ >= SYN_TIMEOUT) {
						debug_format("TCP SYN_RCVD Timeout\n");
						send = true;
						flags |= tcp_h::MASK_FIN;
						ctx.recv_task_ = recv_task::sync_close;
					}
#endif
				}
				if(ctx.recv_fin_) {
					send = true;
					flags |= tcp_h::MASK_ACK;
					ctx.recv_task_ = recv_task::sync_close;
				}
				break;


			// クライアント、接続シーケンス
			case recv_task::syn_sent:
// utils::format("(SYN_CENT) RECV: SEQ: 0x%08X, ACK: 0x%08X (%d)\n") % ctx.recv_seq_ % ctx.recv_ack_ % recv_len;
// utils::format("(SYN_CENT) SEND: SEQ: 0x%08X, ACK: 0x%08X\n") % ctx.send_seq_ % ctx.send_ack_;
				if(tcp->get_flag_ack() && tcp->get_flag_syn() && ctx.recv_ack_ == (ctx.send_seq_ + 1)) {
					ctx.net_time_ref_ = delta_time_(ctx.timer_ref_);
					if(ctx.net_time_ref_ == 0) ++ctx.net_time_ref_;  // ０の場合、最低値を設定
					ctx.send_seq_ = ctx.recv_ack_;
					ctx.send_ack_ = ctx.recv_seq_ + 1;
					send = true;
					flags |= tcp_h::MASK_ACK;
					ctx.recv_task_ = recv_task::established;
					debug_format("TCP Connection Client: desc(%d)\n") % ctx.desc_; 
				}
				if(ctx.recv_fin_) {
					send = true;
					flags |= tcp_h::MASK_ACK;
					ctx.recv_task_ = recv_task::sync_close;
				}
				break;

			// データ、受信、送信
			case recv_task::established:
#if 0
if(!ctx.server_) {
	debug_format("(EST) RECV: SEQ: 0x%08X, ACK: 0x%08X recv_len(%d)\n")
		% ctx.recv_seq_ % ctx.recv_ack_ % recv_len;
	debug_format("(EST) HOST: SEQ: 0x%08X, ACK: 0x%08X send_len(%d)\n")
		% ctx.send_seq_ % ctx.send_ack_ % ctx.send_len_;
}
#endif
				if(tcp->get_flag_ack()) {
					if(ctx.send_info_.length() > 0) {  // 転送データがあるなら ACK 確認
						const data_info& di = ctx.send_info_.get_at();
						if(ctx.recv_seq_ == di.ack_ && ctx.recv_ack_ >= (di.seq_ + di.len_)) {
							ctx.send_.get_go(di.len_);  // 転送データが無事送れたので、バッファを進める
							ctx.send_seq_ += di.len_;
							debug_format("TCP Send OK: %d/%d bytes desc(%d)\n")
								% di.len_ % ctx.send_.length() % ctx.desc_;
							ctx.send_wait_ = make_send_wait_();
							ctx.resend_cnt_ = 0;
							ctx.send_info_.get_go();  // 確認情報を進める
						}
					}
				}

				if(tcp->get_flag_psh()) {  // データ受信
// utils::format("PSH:    SEQ: 0x%08X, ACK: 0x%08X (%d)\n") % ctx.recv_seq_ % ctx.recv_ack_ % recv_len;
// utils::format("SERVER: SEQ: 0x%08X, ACK: 0x%08X\n") % ctx.send_seq_ % ctx.send_ack_;
					if(recv_len > 0 && recv_len < (ctx.recv_.size() - ctx.recv_.length() - 1)) {
						if(ctx.recv_ack_ == ctx.send_seq_ && ctx.recv_seq_ >= ctx.send_ack_) {
							send = true;
							const uint8_t* org = reinterpret_cast<const uint8_t*>(tcp);
							org += tcp->get_length();
							ctx.recv_.put(org, recv_len);
							ctx.send_ack_ += recv_len;
							flags |= tcp_h::MASK_ACK;
						}
					}
				}
				break;

			case recv_task::sync_close:
// debug_format("sync_close (Recv Len: %d)\n") % recv_len;
// utils::format("RECV:      SEQ: 0x%08X, ACK: 0x%08X\n") % ctx.recv_seq_ % ctx.recv_ack_;
// utils::format("SEND(ACK): SEQ: 0x%08X, ACK: 0x%08X\n") % ctx.send_seq_ % ctx.send_ack_;
				if(tcp->get_flag_ack()) {
					if(ctx.recv_ack_ == (ctx.send_seq_ + 1) && ctx.recv_seq_ == ctx.send_ack_) { 
						++ctx.send_seq_;
						ctx.recv_task_ = recv_task::close;
					}
				}
				if(ctx.recv_fin_) {  // FIN に対するACKを返す
					ctx.recv_fin_ = true;
					send = true;
					++ctx.send_ack_;
					flags |= tcp_h::MASK_ACK;
				}
				if(tcp->get_flag_psh()) {
					debug_format("sync_close PSH (Recv Len: %d)\n") % recv_len;
				}
				break;

			case recv_task::close:
				break;

			default:
				break;
			}

			if(send) {
				frame_t* t = get_send_frame_();
				if(t == nullptr) {
					return false;
				}
				bool data = false;  // データ転送を「相乗り」しない
				auto all = make_seg_(ctx, eh.get_src(), ih.get_src_ipa(), *t, flags, data);
				ethd_.send(all);
			}
			return true;
		}


		// 割り込み「外」からの FIN 送信
		void send_flags_(context& ctx, uint8_t flags)
		{
			ethd_.enable_interrupt(false);

			frame_t* t = get_send_frame_();
			if(t != nullptr) {
				auto all = make_seg_(ctx, ctx.mac_, ctx.adrs_.get(), *t, flags, false);
				ethd_.send(all);
			}

			ethd_.enable_interrupt();
		}


		// 割り込み「外」からのデータ送信
		void send_(context& ctx)
		{
			if(ctx.recv_task_ != recv_task::established) return;
			// 転送バッファが一杯で送れない場合
			if(ctx.send_info_.length() >= (ctx.send_info_.size() - 1)) return;

			bool data = false;
			if(ctx.send_info_.length() > 0) data = true;

			if(ctx.send_info_.length() > 0) {
				if(ctx.send_wait_ > 0) {
					--ctx.send_wait_;
				} else {  // 送信データ再送
					++ctx.resend_cnt_;
					// 再送回数がリミットに達したらリセットを送って強制終了
					if(ctx.resend_cnt_ >= RESEND_LIMIT) {
						debug_format("TCP ReSend Limit for RST: desc(%d)\n") % ctx.desc_;
						send_flags_(ctx, tcp_h::MASK_RST);
						ctx.recv_task_ = recv_task::close;
						ctx.send_task_ = send_task::close;
					} else {
						data = true;
					}
				}
			}

			if(!data) return;

			ethd_.enable_interrupt(false);

			uint16_t len = ctx.send_.length();
			frame_t* t = nullptr;
			if(len == 0) {
				goto send_exit;
			}

			t = get_send_frame_();
			if(t == nullptr) {
				goto send_exit;
			}
			{
				auto all = make_seg_(ctx, ctx.mac_, ctx.adrs_.get(), *t, tcp_h::MASK_ACK, true);
				ethd_.send(all);
			}
/// dump(t->ipv4_, " (send_)");
/// dump(t->tcp_,  " (send_)");

		send_exit:
			ethd_.enable_interrupt();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	ethd	イーサーネット・ドライバー
			@param[in]	info	ネット情報
			@param[in]	seq		シーケンス番号初期値
		*/
		//-----------------------------------------------------------------//
		tcp(ETHD& ethd, net_info& info, uint32_t seq = 1) noexcept : ethd_(ethd), info_(info),
			last_state_(net_state::OK)

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
			@param[out]	ディスクリプタ
			@return ネット・ステートを返す
		*/
		//-----------------------------------------------------------------//
		net_state open(const ip_adrs& adrs, uint16_t port, bool server, uint32_t& desc) noexcept
		{
			if(port == 0) {  // ０番ポートは無効
				auto st = net_state::FAIL_PORT;
				if(last_state_ != st) {
					debug_format("TCP Open fail port: %d\n") % port;
					last_state_ = st;
				}
				desc = NMAX;
				return st;
			}
			if(adrs.is_brodcast()) {  // ブロードキャストアドレスは無効
				auto st = net_state::FAIL_ADRS;
				if(last_state_ != st) {
					debug_format("TCP Open fail brodcast address: %s\n") % adrs.c_str();
					last_state_ = st;
				}
				desc = NMAX;
				return st;
			}

			if(adrs.is_any() && !server) {  // クライアント接続では、ANY アドレスは無効
				auto st = net_state::FAIL_ANY;
				if(last_state_ != st) {
					debug_format("TCP Open fail any address for client: %s\n") % adrs.c_str();
					last_state_ = st;
				}
				desc = NMAX;
				return st;
			}

			// 同じポートがある場合は無効
			for(uint32_t i = 0; i < NMAX; ++i) {
				if(!common_.at_blocks().is_alloc(i)) continue;
				const context& ctx = common_.get_blocks().get(i);
				uint16_t pp;
				if(server) {
					pp = ctx.src_port_;
				} else {
					pp = ctx.dst_port_;
				}
				if(pp == port) {
					auto st = net_state::EVEN_PORT;
					if(last_state_ != st) {
						debug_format("TCP Open fail even port as: %d\n") % port;
						last_state_ = st;
					}
					desc = NMAX;
					return st;
				}
			}

			// コンテキスト・スペースが無い
			uint32_t idx = common_.at_blocks().alloc();
			if(!common_.at_blocks().is_alloc(idx)) {
				auto st = net_state::CONTEXT_EMPTY;
				if(last_state_ != st) {
					debug_format("TCP Open fail context empty\n"); 
					last_state_ = st;
				}
				desc = NMAX;
				return st;
			}

			last_state_ = net_state::OK;

			context& ctx = common_.at_blocks().at(idx);

			// コンテキスト初期化
			ctx.reset(idx, adrs, port, server);

			bool send_syn = false;
			if(server) {
				ctx.recv_task_ = recv_task::listen_server;
				ctx.send_task_ = send_task::established;
			} else {
				ctx.recv_task_ = recv_task::idle;
				if(common_.check_mac(ctx, info_)) {  // MAC アドレスが判っている場合
					ctx.recv_task_ = recv_task::syn_sent;
					ctx.send_task_ = send_task::sync_ack;
					send_syn = true;
				} else {  // MAC アドレスが判っていない場合
					ctx.request_ip_ = true;
					ctx.recv_task_ = recv_task::idle;
					ctx.send_task_ = send_task::sync_mac;
				}
			}

			common_.at_blocks().unlock(idx);

			if(send_syn) {  // クライアント動作の場合 SYN を送る
				send_flags_(ctx, tcp_h::MASK_SYN);
			}

			desc = idx;

			return net_state::OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ディスクリプタの検査
			@param[in]	desc	ディスクリプタ
			@return ディスクリプタが無効「false」
		*/
		//-----------------------------------------------------------------//
		bool probe(uint32_t desc) const
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			return common_.get_blocks().is_alloc(idx);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  接続の検査
			@param[in]	desc	ディスクリプタ
			@return 接続状態「true」、切断状態、ディスクリプタが無効「false」
		*/
		//-----------------------------------------------------------------//
		bool connected(uint32_t desc) const noexcept
		{
			if(!common_.get_blocks().is_alloc(desc)) return false;

			const context& ctx = common_.get_blocks().get(desc);
			return ctx.recv_task_ == recv_task::established;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  再コネクト要求（クライアント限定）
			@param[in]	desc	ディスクリプタ
			@return エラーが無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool re_connect(uint32_t desc) noexcept
		{
			if(!common_.get_blocks().is_alloc(desc)) return false;

			context& ctx = common_.at_blocks().at(desc);
			if(ctx.server_) return false;  // サーバー接続の場合エラー

			// SYN に対する ACK 待ち以外ならエラー
			if(ctx.recv_task_ != recv_task::syn_sent) return false;

			send_flags_(ctx, tcp_h::MASK_SYN);
			info_.re_send_syn_count_++;
			debug_format("TCP Client SYN re-send %d: desc(%d)\n")
				% info_.re_send_syn_count_
				% desc;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  FIN 受信の検査
			@param[in]	desc	ディスクリプタ
			@return 受信なら「true」
		*/
		//-----------------------------------------------------------------//
		bool is_fin(uint32_t desc) const noexcept
		{
			if(!common_.get_blocks().is_alloc(desc)) return false;

			const context& ctx = common_.get_blocks().get(desc);
			return ctx.recv_fin_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  接続ＩＰの取得
			@param[in]	desc	ディスクリプタ
			@return 接続ＩＰ（ANYなら無効）
		*/
		//-----------------------------------------------------------------//
		const ip_adrs& get_ip(uint32_t desc) const
		{
			static ip_adrs tmp;
			if(!common_.get_blocks().is_alloc(desc)) return tmp;

			const context& ctx = common_.get_blocks().get(desc);
			return ctx.adrs_;			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  接続ポートの取得
			@param[in]	desc	ディスクリプタ
			@return 接続ポート
		*/
		//-----------------------------------------------------------------//
		uint16_t get_port(uint32_t desc) const
		{
			static ip_adrs tmp;
			if(!common_.get_blocks().is_alloc(desc)) return tmp;

			const context& ctx = common_.get_blocks().get(desc);
			if(ctx.server_) {
				return ctx.src_port_;
			} else {
				return ctx.dst_port_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  内部接続ポートの取得（内部動作で接続するポート番号）@n
					・サーバーでは、クライアントが決定したポート番号を使う @n
					・クライアントでは、自分で、ポート番号を決定する @n
					※ポート番号は、４９１５２～６５５３５となる
			@param[in]	desc	ディスクリプタ
			@return 内部接続ポート（「０」の場合エラー）
		*/
		//-----------------------------------------------------------------//
		uint16_t get_internal_port(uint32_t desc) const
		{
			if(!common_.get_blocks().is_alloc(desc)) return 0;

			const context& ctx = common_.get_blocks().get(desc);
			if(ctx.server_) {
				return ctx.dst_port_;
			} else {
				return ctx.src_port_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  データ送信
			@param[in]	desc	ディスクリプタ
			@param[in]	src		ソース
			@param[in]	len		送信バイト数
			@return 送信バイト（負の値はエラー）
		*/
		//-----------------------------------------------------------------//
		int send(uint32_t desc, const void* src, uint16_t len) noexcept
		{
			if(!common_.get_blocks().is_alloc(desc)) return -1;
			const context& ctx = common_.get_blocks().get(desc);

			// FIN を受け取った、クローズした場合は、送信データをバッファに送らないでエラーにする。
			if(ctx.close_req_ || ctx.recv_fin_) {
				return -1;
			}
			return common_.send(desc, src, len);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信バッファの残量取得
			@param[in]	desc	ディスクリプタ
			@return 送信バッファの残量（負の値はエラー）
		*/
		//-----------------------------------------------------------------//
		inline int get_send_length(uint32_t desc) const noexcept
		{
			return common_.get_send_length(desc);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  データ受信
			@param[in]	desc	ディスクリプタ
			@param[in]	dst		ソース
			@param[in]	len		受信バイト数
			@return 受信バイト（負の値はエラー）
		*/
		//-----------------------------------------------------------------//
		inline int recv(uint32_t desc, void* dst, uint16_t len) noexcept
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
		inline int get_recv_length(uint32_t desc) const noexcept
		{
			return common_.get_recv_length(desc);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クローズ
			@param[in]	desc	ディスクリプタ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool close(uint32_t desc) noexcept
		{
			if(!common_.get_blocks().is_alloc(desc)) return false;

			context& ctx = common_.at_blocks().at(desc);
			ctx.close_req_ = true;
			return true;
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
				if(!common_.get_blocks().is_alloc(i)) continue;  // alloc: 有効
				if(common_.get_blocks().is_lock(i)) continue;  // lock:  無効
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
				if(ctx.server_) {
					if(ctx.src_port_ != tcp->get_dst_port()) {
						continue;
					}
					if(ctx.dst_port_ != 0) {
						if(ctx.dst_port_ != tcp->get_src_port()) {
							continue;
						}
					} else {
						if(tcp->get_flag_syn()) {
							ctx.dst_port_ = tcp->get_src_port();
							debug_format("TCP Server First Connection dst_port(%d) desc(%d)\n")
								% ctx.dst_port_ % i;
						}
					}
				} else {
					if(ctx.src_port_ != tcp->get_dst_port()) continue;
					if(ctx.dst_port_ != tcp->get_src_port()) continue;
				}

				return recv_(ctx, eh, ih, tcp);
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（１０ｍｓ毎に呼ぶ）@n
					※割り込み外から呼ぶ事
			@param[in]	arp	ARP コンテキスト
		*/
		//-----------------------------------------------------------------//
		void service(ARP& arp) noexcept
		{
			for(uint32_t i = 0; i < NMAX; ++i) {

				if(!common_.get_blocks().is_alloc(i)) continue;
				if(common_.get_blocks().is_lock(i)) continue;  // lock:  無効

				context& ctx = common_.at_blocks().at(i);

				switch(ctx.send_task_) {

				// クライアント動作、IP アドレスに対する MAC が判らない場合
				case send_task::sync_mac:
					if(common_.check_mac(ctx, info_)) {
						debug_format("TCP sync_mac OK\n");
						ctx.recv_task_ = recv_task::syn_sent;
						send_flags_(ctx, tcp_h::MASK_SYN);
						ctx.send_task_ = send_task::sync_ack;
					} else if(ctx.request_ip_) {
						ctx.request_ip_ = false;
						arp.request(ctx.adrs_);
					}
					break;

				case send_task::sync_ack:  // クライアント動作、SYN に対する ACK の受信確認
					if(ctx.recv_task_ == recv_task::established) {
						ctx.send_task_ = send_task::established;
					}
					break;

				case send_task::established:
					send_(ctx);
					// ・FIN を受け取っても、送信データがあれば、送る事ができる。
					// ・FIN を送っても、受信データがあれば、それを受け取る必要がある。
					// ※この「サービス」は、受信動作（割り込み）とは非同期なので、
					// FIN を送った後で、少しの間、受信データが無い事を確認する為の
					// 「間」をとる必要がある。
					if(ctx.send_info_.length() == 0 && ctx.close_req_) {
						debug_format("TCP Close start: desc(%d)\n") % i;
						send_flags_(ctx, tcp_h::MASK_FIN);
						//「クローズ同期」を始める
						ctx.send_task_ = send_task::sync_close;
						ctx.send_time_ = CLOSE_TIME_OUT;
					}
					break;

				case send_task::sync_close:
					// 送信動作、及びレシーブ動作が「クローズ」なら終了
					if(ctx.close_req_ && ctx.recv_task_ == recv_task::close) {
						common_.at_blocks().lock(i);  // ロックする（割り込みで利用不可にする）
						common_.at_blocks().erase(i);
					}
					if(ctx.send_time_ > 0) {
						ctx.send_time_--;
						if(ctx.send_time_ == 0) {
							debug_format("TCP Close TimeOut (%d)\n") % i;
						}
					} else {
						common_.at_blocks().lock(i);  // ロックする（割り込みで利用不可にする）
						common_.at_blocks().erase(i);
					}
					break;

				case send_task::close:  // 強制クローズ
					common_.at_blocks().lock(i);
					common_.at_blocks().erase(i);
					break;

				default:
					break;
				}
			}
		}
	};
}
