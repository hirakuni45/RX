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

#ifndef TCP_DEBUG
		typedef utils::null_format debug_format;
#else
		typedef utils::format debug_format;
#endif

		static const uint16_t TIME_OUT = 20 * 1000 / 10;  // 20 sec (unit: 10ms)

		ETHD&		ethd_;

		net_info&	info_;

		uint32_t	master_seq_;
		uint16_t	ethd_max_;

		enum class recv_task : uint8_t {
			idle,
			listen_server,
			syn_rcvd,
			established_server,
			close_wait_server,
			last_ack_server,
			closed,

			listen_client,

			sync_close,
			close,
		};

		enum class send_task : uint8_t {
			idle,
			sync_mac,

			main,

			sync_close,
			close,
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
			uint16_t	flags_;
			uint16_t	window_;
			uint16_t	urgent_ptr_;

			volatile recv_task	recv_task_;
			volatile bool		server_;

			void reset(const ip_adrs& adrs, uint16_t port)
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

				recv_.clear();
				send_.clear();

				seq_ = 0;
				ack_ = 0;
				flags_ = 0x00;
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
		} __attribute__((__packed__));


		// TCP checksum header 
		struct csum_h {
			ip_adrs		src_;
			ip_adrs		dst_;
			uint16_t	fix_;
			uint16_t	len_;
		};


		uint16_t make_tcp_frame_(context& ctx, const eth_h& eh, const ipv4_h& ih, const tcp_h* tcp, frame_t& t)
		{
			swap_copy_eth_h(&t.eh_, &eh);

			uint16_t all = sizeof(frame_t);
			uint8_t* p = reinterpret_cast<uint8_t*>(&t) + all;

			// 送信データを上乗せする場合
			if(ctx.recv_task_ == recv_task::established_server
			  && ctx.send_.length() > 0
			  && ctx.send_task_ == send_task::main) {
				uint16_t out_len = ctx.send_.length();
				uint16_t max_len = ethd_max_ - sizeof(frame_t);
				if(max_len < out_len) {
					out_len = max_len;
				}
				ctx.send_.get(p, out_len);
				all += out_len;
				ctx.flags_ |= tcp_h::MASK_PSH;
			}

			while(all < 60) {
				*p++ = 0;
				++all;
			}

			t.ipv4_.set_ver_hlen(0x45);
			t.ipv4_.set_type(0x00);
			t.ipv4_.set_length(all - sizeof(eth_h));
			t.ipv4_.set_id(ctx.id_);
			t.ipv4_.set_f_offset(ctx.offset_);
			t.ipv4_.set_life(ctx.life_);
			t.ipv4_.set_protocol(ipv4_h::protocol::TCP);
			t.ipv4_.set_csum(0);
			t.ipv4_.set_src_ipa(ih.get_dst_ipa());
			t.ipv4_.set_dst_ipa(ih.get_src_ipa());
			t.ipv4_.set_csum(tools::calc_sum(&t.ipv4_, sizeof(ipv4_h)));

			uint16_t tcp_len = all - sizeof(eth_h) - sizeof(ipv4_h);
			t.tcp_.set_src_port(ctx.cn_port_);
			t.tcp_.set_dst_port(ctx.port_);
			t.tcp_.set_seq(master_seq_);
			t.tcp_.set_ack(ctx.seq_);
			t.tcp_.set_length(tcp_len);
			t.tcp_.set_flags(ctx.flags_);
			t.tcp_.set_window(ctx.window_);
			t.tcp_.set_csum(0x0000);
			t.tcp_.set_urgent_ptr(ctx.urgent_ptr_);

			csum_h smh;
			smh.src_.set(ih.get_dst_ipa());
			smh.dst_.set(ih.get_src_ipa());
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
			if(ethd_.send_buff(&dst, ethd_max_) != 0) {
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
			uint16_t data_len = len - tcp->get_length();
// dump(ih);
// dump(*tcp);
			switch(ctx.recv_task_) {

			case recv_task::listen_server:
				if(tcp->get_flag_syn()) {
///					utils::format("listen_server\n");
					frame_t* t = get_send_frame_();
					if(t == nullptr) {
						return false;
					}
					ctx.seq_ = tcp->get_seq() + 1;
					ctx.ack_ = tcp->get_ack();
					ctx.flags_ = tcp_h::MASK_SYN | tcp_h::MASK_ACK;
					auto all = make_tcp_frame_(ctx, eh, ih, tcp, *t);
// dump(t->ipv4_);
// dump(t->tcp_);
// utils::format("\n");
					ethd_.send(all);
					master_seq_ += 1;
					++ctx.ack_;
					ctx.recv_task_ = recv_task::syn_rcvd;
				}
				if(tcp->get_flag_fin()) {
					ctx.recv_task_ = recv_task::close_wait_server;
				}
				break;

			case recv_task::syn_rcvd:
				if(tcp->get_flag_ack()) {
///					&& tcp->get_seq() == ctx.ack_ && tcp->get_ack() == master_seq_) {
///					utils::format("syn_rcvd\n");
					ctx.recv_task_ = recv_task::established_server;
				}
				if(tcp->get_flag_fin()) {
					ctx.recv_task_ = recv_task::close_wait_server;
				}
				break;

			case recv_task::established_server:
				if(tcp->get_flag_ack()) {
dump(*tcp);
				}
				if(tcp->get_flag_psh()) {
					if(data_len > 0 && data_len < (ctx.recv_.size() - ctx.recv_.length() - 1)) {
///						utils::format("established_server: data(%d)\n") % data_len;
						const uint8_t* org = reinterpret_cast<const uint8_t*>(tcp);
						org += tcp->get_length();
						ctx.recv_.put(org, data_len);

						frame_t* t = get_send_frame_();
						if(t == nullptr) {
							return false;
						}
						ctx.seq_ = tcp->get_seq() + data_len;
						ctx.ack_ = tcp->get_ack();
						ctx.flags_ = tcp_h::MASK_ACK;
						auto all = make_tcp_frame_(ctx, eh, ih, tcp, *t);
						ethd_.send(all);
						master_seq_ += 1;
						++ctx.ack_;
					}
				}
				if(tcp->get_flag_fin()) {
					ctx.recv_task_ = recv_task::close_wait_server;
				}
				break;

			case recv_task::close_wait_server:

				break;

			case recv_task::last_ack_server:
				break;

			case recv_task::closed:
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
#if 0
			uint16_t len = ctx.send_.length();
			if(len == 0) return;

			void* dst;
			uint16_t dlen;
			if(ethd_.send_buff(&dst, dlen) != 0) {
				return;
			}

			{
				uint16_t lim = dlen - sizeof(eth_h) - sizeof(ipv4_h) - sizeof(tcp_h);
				if(len > lim) {  // 最大転送サイズ
					len = lim;
				}
			}

			frame_t* p = static_cast<frame_t*>(dst);
			p->eh_.set_dst(ctx.mac_);   // 転送先の MAC
			p->eh_.set_src(info_.mac);  // 転送元の MAC
			p->eh_.set_type(eth_type::IPV4);

			p->ipv4_.ver_hlen_ = 0x45;
			p->ipv4_.type_ = 0x00;
			p->ipv4_.set_length(sizeof(ipv4_h) + len);
			p->ipv4_.set_id(ctx.id_);  // 識別子（送信パケットごとに＋１する）
			// 1500バイトより大きなデータを送る場合にフラグメントに分割されて
			// その連番がオフセットとして設定される。
			p->ipv4_.set_flag(0);
			p->ipv4_.set_flagment_offset(ctx.offset_);
			p->ipv4_.set_life(ctx.life_);  // 生存時間（ルーターの通過台数）
			p->ipv4_.set_protocol(ipv4_h::protocol::UDP);
			p->ipv4_.csum_ = 0;
			p->ipv4_.set_src_ipa(info_.ip.get());
			p->ipv4_.set_dst_ipa(ctx.adrs_.get());
			p->ipv4_.set_csum(tools::calc_sum(&p->ipv4_, sizeof(ipv4_h)));

			// データグラムのサム計算
			csum_h smh;
			smh.src_ = info_.ip;   // src adrs
			smh.dst_ = ctx.adrs_;  // dst adrs
			smh.fix_ = 0x0600;  // TCP 固定値
			smh.len_ = tools::htons(len);

			p->tcp_.set_src_port(ctx.cn_port_);
			if(ctx.port_ == 0) {
				ctx.port_ = tools::random_port();
			}
			p->tcp_.set_dst_port(ctx.port_);




			p->tcp_.set_csum(0x0000);
			ctx.send_.get(static_cast<uint8_t*>(dst) + sizeof(frame_t), len);

			uint16_t sum = tools::calc_sum(&smh, sizeof(csum_h));
			sum = tools::calc_sum(&p->tcp_, sizeof(tcp_h) + len, ~sum);
			p->tcp_.set_csum(sum);

			uint16_t all = sizeof(frame_t) + len;
			if(all < 60) {
				uint8_t* mp = static_cast<uint8_t*>(dst) + all;
				while(all < 60) {
					*mp++ = 0;
					++all;
				}
			}
			ethd_.send(all);

			++ctx.id_;
#endif
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	ethd	イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		tcp(ETHD& ethd, net_info& info) noexcept : ethd_(ethd), info_(info), master_seq_(1),
			ethd_max_(0)
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
			@brief  マスター・シーケンス番号の設定
			@param[in]	mseq	マスター・シーケンス番号
		*/
		//-----------------------------------------------------------------//
		void set_master_seq(uint32_t mseq) noexcept { master_seq_ = mseq; }


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
			if(port == 0) {
				debug_format("TCP Open fail port: %d\n") % port;
				return -1;
			}
			if(adrs.is_brodcast()) {
				debug_format("TCP Open fail brodcast address: %s\n") % adrs.c_str();
				return -1;
			}

			uint32_t idx = common_.at_blocks().alloc();
			if(!common_.at_blocks().is_alloc(idx)) {
				debug_format("TCP Context Empty\n"); 
				return -1;
			}

			context& ctx = common_.at_blocks().at(idx);
			ctx.reset(adrs, port);
			ctx.server_ = server;

			if(adrs.is_any() || adrs.is_brodcast()) {
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
			ctx.send_task_ = send_task::sync_close;
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
					break;

				case send_task::sync_close:
					if(ctx.send_.length() == 0) {
						common_.at_blocks().lock(i);  // ロックする（割り込みで利用不可にする）
						ctx.send_task_ = send_task::close;
					} else {
						send_(ctx);
					}
					break;

				case send_task::close:
					common_.at_blocks().erase(i);
					break;
				default:
					break;
				}
			}
		}
	};
}
