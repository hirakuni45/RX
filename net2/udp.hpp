#pragma once
//=========================================================================//
/*! @file
    @brief  UDP Protocol
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "net2/udp_tcp_common.hpp"

#define UDP_DEBUG

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  UDP ステート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class udp_state : uint8_t {
		OK,
		FAIL_PORT,      ///< 不正なポート番号
		FAIL_ADRS,      ///< 不正なアドレス
		FAIL_ANY,       ///< クライアントでは、「ANY」は不正
		EVEN_PORT,      ///< 既にそのポート番号は利用されている
		CONTEXT_EMPTY,  ///< コンテキストが無い
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  UDP マネージメント・クラス
		@param[in]	ETHD	イーサーネット・ドライバー・クラス
		@param[in]	NMAX	管理最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHD, uint32_t NMAX>
	class udp {

#ifndef UDP_DEBUG
		typedef utils::null_format debug_format;
#else
		typedef utils::format debug_format;
#endif

		static const uint16_t TIME_OUT = 20 * 1000 / 10;  // 20 sec (unit: 10ms)

		ETHD&		ethd_;

		net_info&	info_;

		net_state	last_state_;

		enum class send_task : uint8_t {
			idle,
			sync_mac,
			main,
			sync_close,
		};

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

			memory		recv_;
			memory		send_;


			void init(void* send_buff, uint16_t send_size, void* recv_buff, uint16_t recv_size)
			{
				send_.set_buff(send_buff, send_size);
				recv_.set_buff(recv_buff, recv_size);
			}


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
			}
		};

		typedef udp_tcp_common<context, NMAX> COMMON;
		COMMON		common_;

		struct frame_t {
			eth_h	eh_;
			ipv4_h	ipv4_;
			udp_h	udp_;
		} __attribute__((__packed__));


		struct csum_h {  // UDP checksum header 
			ip_adrs		src_;
			ip_adrs		dst_;
			uint16_t	fix_;
			uint16_t	len_;
		};


		void send_(context& ctx)
		{
			uint16_t len = ctx.send_.length();
			if(len == 0) return;

			ethd_.enable_interrupt(false);

			void* dst;
			uint16_t dlen;
			if(ethd_.send_buff(&dst, dlen) != 0) {
				return;
			}

			{
				uint16_t lim = dlen - sizeof(eth_h) - sizeof(ipv4_h) - sizeof(udp_h);
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
			p->ipv4_.set_length(sizeof(ipv4_h) + sizeof(udp_h) + len);
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
			smh.fix_ = 0x1100;  // UDP 固定値
			smh.len_ = tools::htons(sizeof(udp_h) + len);

			p->udp_.set_src_port(ctx.cn_port_);
			if(ctx.port_ == 0) {
				ctx.port_ = tools::connect_port();
			}
			p->udp_.set_dst_port(ctx.port_);
			p->udp_.set_length(sizeof(udp_h) + len);
			p->udp_.set_csum(0x0000);
			ctx.send_.get(static_cast<uint8_t*>(dst) + sizeof(frame_t), len);

			uint16_t sum = tools::calc_sum(&smh, sizeof(csum_h));
			sum = tools::calc_sum(&p->udp_, sizeof(udp_h) + len, ~sum);
			p->udp_.set_csum(sum);

// dump(p->ipv4_);
// dump(p->udp_);

//			sum = tools::calc_sum(&smh, sizeof(csum_h));
//			sum = tools::calc_sum(&p->udp_, sizeof(udp_h) + len, ~sum);
//			utils::format("Sum: %04X\n") % sum;
			uint16_t all = sizeof(frame_t) + len;
			if(all < 60) {
				uint8_t* mp = static_cast<uint8_t*>(dst) + all;
				while(all < 60) {
					*mp++ = 0;
					++all;
				}
			}
//			utils::format("UDP Send: %d\n") % all;
			ethd_.send(all);

			ethd_.enable_interrupt();

			++ctx.id_;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth		イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		udp(ETHD& ethd, net_info& info) noexcept : ethd_(ethd), info_(info),
			last_state_(net_state::OK), common_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  UDP の同時接続数を返す
			@return UDP の同時接続数
		*/
		//-----------------------------------------------------------------//
		uint32_t capacity() const noexcept { return NMAX; }


		//-----------------------------------------------------------------//
		/*!
			@brief  オープン
			@param[in]	send_buff	送信バッファ
			@param[in]	send_size	送信バッファサイズ
			@param[in]	recv_buff	受信バッファ
			@param[in]	recv_size	受信バッファサイズ
			@param[out]	desc	ディスクリプタ
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool open(void* send_buff, uint16_t send_size, void* recv_buff, uint16_t recv_size, uint32_t& desc) noexcept
		{
			// コンテキスト・スペースが無い
			uint32_t idx = common_.at_blocks().alloc();  // ロックされた状態
			if(!common_.at_blocks().is_alloc(idx)) {
				auto st = net_state::CONTEXT_EMPTY;
				if(last_state_ != st) {
					debug_format("TCP Open fail context empty\n"); 
					last_state_ = st;
				}
				desc = NMAX;
				return false;
			}

			context& ctx = common_.at_blocks().at(idx);
			ctx.init(send_buff, send_size, recv_buff, recv_size);

			desc = idx;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オープン
			@param[in]	desc	ディスクリプタ
			@param[in]	adrs	アドレス
			@param[in]	port	ポート
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t desc, const ip_adrs& adrs, uint16_t port) noexcept
		{
			if(!common_.get_blocks().is_alloc(desc)) return false;

			// ロック状態で、呼ばれるので、ロックが無い場合はエラー
			if(!common_.get_blocks().is_lock(desc)) {
				return false;
			}

			if(port == 0) {
				debug_format("UDP Open fail port: %d desc(%d)\n") % port % desc;
				desc = NMAX;
				last_state_ = net_state::FAIL_PORT;
				return false;
			}

			context& ctx = common_.at_blocks().at(desc);
#if 0
			// 同じポートがある場合は無効
			for(uint32_t i = 0; i < NMAX; ++i) {
				if(!common_.at_blocks().is_alloc(i)) continue;
				const context& ctx = common_.get_blocks().get(i);
				if(ctx.cn_port_ == port) {
					auto st = net_state::EVEN_PORT;
					if(last_state_ != st) {
						debug_format("TCP Open fail even port as: %d\n") % port;
						last_state_ = st;
					}
					desc = NMAX;
					return st;
				}
			}
#endif
			ctx.reset(adrs, port);

			if(adrs.is_any() || adrs.is_brodcast()) {
				ctx.send_task_ = send_task::main;
			} else {
				if(common_.check_mac(ctx, info_)) {  // 既に MAC が利用可能なら「main」へ
					ctx.send_task_ = send_task::main;
				} else {
					ctx.send_task_ = send_task::sync_mac;
				}
			}

			common_.at_blocks().unlock(desc);

			return true;
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
			return common_.get_blocks().is_alloc(desc);
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
		inline int send(uint32_t desc, const void* src, uint16_t len) noexcept
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
		inline int get_send_length(uint32_t desc) const noexcept
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
			if(!common_.at_blocks().is_alloc(desc)) return false;

			context& ctx = common_.at_blocks().at(desc);
			ctx.send_task_ = send_task::sync_close;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  プロセス（割り込みから呼ばれる）
			@param[in]	eh	イーサーネット・ヘッダー
			@param[in]	ih	IPV4 ヘッダー
			@param[in]	udp	UDP ヘッダー
			@param[in]	len	メッセージ長
			@return エラーが無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool process(const eth_h& eh, const ipv4_h& ih, const udp_h* udp, int32_t len) noexcept
		{
			// 該当するコンテキストを探す
			uint32_t idx = NMAX;
			for(uint32_t i = 0; i < NMAX; ++i) {
				if(!common_.at_blocks().is_alloc(i)) continue;  // alloc: 有効
				if(common_.at_blocks().is_lock(i)) continue;  // lock:  無効
				context& ctx = common_.at_blocks().at(i);  // コンテキスト取得

				// 転送先の確認
				if(info_.ip != ih.get_dst_ipa()) continue;

				// 転送元の確認
				if(!ctx.adrs_.is_any() && ctx.adrs_ != ih.get_src_ipa()) continue; 

				// ポート番号の確認
				if(ctx.port_ != 0) {
					if(ctx.port_ != udp->get_src_port()) {
						continue;
					}
				} else {
					ctx.port_ = udp->get_src_port();
				}
				if(ctx.cn_port_ != udp->get_dst_port()) {
					continue;
				}

				// UDP サムの計算
				csum_h smh;
				smh.src_.set(ih.get_src_ipa());
				smh.dst_.set(ih.get_dst_ipa());
				smh.fix_ = 0x1100;
				smh.len_ = udp->get_length_();  // 直接アクセス
				uint16_t sum = tools::calc_sum(&smh, sizeof(smh));
				sum = tools::calc_sum(udp, udp->get_length(), ~sum);
				if(sum != 0) {
					utils::format("UDP Frame sum error: %04X -> %04X\n") % udp->get_csum() % sum;
					return false;
				}

				if(udp->get_data_len() < (ctx.recv_.size() - ctx.recv_.length() - 1)) {
					ctx.recv_.put(udp->get_data_ptr(udp), udp->get_data_len());
				}
				return true;
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
						ctx.send_task_ = send_task::idle;
						common_.at_blocks().erase(i);
					} else {
						send_(ctx);
					}
					break;

				default:
					break;
				}
			}
		}
	};
}
