#pragma once
//=========================================================================//
/*! @file
    @brief  UDP Protocol @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "common/fixed_block.hpp"
#include "net2/net_st.hpp"
#include "net2/memory.hpp"

#define UDP_DEBUG

namespace net {

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

		enum class task : uint16_t {
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
			uint16_t	src_port_;
			uint16_t	port_;
			uint16_t	dst_port_;
			uint16_t	time_;

			// IPV4 関係
			uint16_t	id_;
			uint16_t	offset_;
			uint8_t		life_;

			task		task_;

			RECV_B		recv_;
			SEND_B		send_;
		};


		typedef utils::fixed_block<context, NMAX> UDP_BLOCK;
		UDP_BLOCK	udps_;


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


		bool get_mac_(context& ctx)
		{
			const auto& cash = info_.get_cash();
			auto idx = cash.lookup(ctx.adrs_);
			if(cash.is_valid(idx)) {
				std::memcpy(ctx.mac_, cash[idx].mac, 6);
				debug_format("UDP MAC lookup: %s at %s\n")
					% ctx.adrs_.c_str()
					% tools::mac_str(cash[idx].mac);
				return true;
			}
			return false;
		}


		void send_(context& ctx)
		{
			uint16_t len = ctx.send_.length();
			if(len == 0) return;

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

			p->udp_.set_src_port(ctx.src_port_);
			if(ctx.port_ == 0) {
				ctx.port_ = tools::random_port();
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
		udp(ETHD& ethd, net_info& info) : ethd_(ethd), info_(info) { }


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
			@param[in]	adrs	アドレス
			@param[in]	port	ポート
			@return ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		int open(const ip_adrs& adrs, uint16_t port)
		{
			uint32_t idx = udps_.alloc();
			if(!udps_.is_alloc(idx)) {
				return -1;
			}

			context& ctx = udps_.at(idx);
			std::memset(ctx.mac_, 0x00, 6);
			ctx.adrs_ = adrs;
			ctx.src_port_ = port;
			ctx.port_ = 0;  // 初期は「０」
			ctx.dst_port_ = port;
			ctx.time_ = TIME_OUT;
			ctx.id_ = 0;  // 識別子の初期値
			ctx.life_ = 255;  // 生存時間初期値（ルーターの通過台数）
			ctx.offset_ = 0;  // フラグメント・オフセット

			ctx.recv_.clear();
			ctx.send_.clear();

			udps_.unlock(idx);

			if(adrs.is_any() || adrs.is_brodcast()) {
				ctx.task_ = task::main;
			} else {
				if(get_mac_(ctx)) {  // 既に MAC が利用可能なら「main」へ
					ctx.task_ = task::main;
				} else {
					ctx.task_ = task::sync_mac;
				}
			}
			return static_cast<int>(idx);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信
			@param[in]	desc	ディスクリプタ
			@param[in]	src		ソース
			@param[in]	len		送信バイト数
			@return 送信バイト
		*/
		//-----------------------------------------------------------------//
		int send(int desc, const void* src, uint16_t len)
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!udps_.is_alloc(idx)) return -1;
			if(udps_.is_lock(idx)) return -1;

			context& ctx = udps_.at(idx);
			uint16_t spc = ctx.send_.size() - ctx.send_.length() - 1;
			if(spc < len) {
				len = spc;
			}
			ctx.send_.put(src, len);

			return len;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  受信
			@param[in]	desc	ディスクリプタ
			@param[in]	dst		ソース
			@param[in]	len		受信バイト数
			@return 受信バイト
		*/
		//-----------------------------------------------------------------//
		int recv(int desc, void* dst, uint16_t len)
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!udps_.is_alloc(idx)) return -1;
			if(udps_.is_lock(idx)) return -1;

			context& ctx = udps_.at(idx);
			int rlen = ctx.recv_.length();
			if(rlen == 0) {  // 読み込むデータが無い
				return rlen;
			}

			if(rlen > len) {
				rlen = len;
			}
			ctx.recv_.get(dst, rlen);
			return rlen;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クローズ
			@param[in]	desc	ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		void close(int desc)
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!udps_.is_alloc(idx)) return;

			context& ctx = udps_.at(idx);
			ctx.task_ = task::sync_close;
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
		bool process(const eth_h& eh, const ipv4_h& ih, const udp_h* udp, int32_t len)
		{
			// 該当するコンテキストを探す
			uint32_t idx = NMAX;
			for(uint32_t i = 0; i < NMAX; ++i) {
				if(!udps_.is_alloc(i)) continue;  // alloc: 有効
				if(udps_.is_lock(i)) continue;  // lock:  無効
				context& ctx = udps_.at(i);  // コンテキスト取得

				// 転送先の確認（ブロードキャスト）
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
				if(ctx.dst_port_ != udp->get_dst_port()) {
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
			@brief  サービス（１０ｍｓ毎に呼ぶ）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			for(uint32_t i = 0; i < NMAX; ++i) {

				if(!udps_.is_alloc(i)) continue;

				context& ctx = udps_.at(i);
				switch(ctx.task_) {
				case task::sync_mac:
					if(get_mac_(ctx)) {
						ctx.task_ = task::main;
					}
					break;

				case task::main:
					send_(ctx);
					break;

				case task::sync_close:
					if(ctx.send_.length() == 0) {
						udps_.lock(i);  // ロックする（割り込みで利用不可にする）
						ctx.task_ = task::close;
					} else {
						send_(ctx);
					}
					break;

				case task::close:
					udps_.erase(i);
					break;
				default:
					break;
				}
			}
		}
	};
}
