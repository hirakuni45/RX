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

		static const uint16_t TIME_OUT = 20 * 1000 / 10;  // 20 sec (unit: 10ms)

		ETHD&		ethd_;

		net_info&	info_;

		enum class task : uint16_t {
			idle,
			open,
			main,
			close,
		};

		typedef memory<4096>  BUFFER;

		struct context {
			ip_adrs		adrs_;
			uint8_t		mac_[6];
			bool		src_port_match_;
			bool		dst_port_match_;
			uint16_t	src_port_;
			uint16_t	dst_port_;
			uint16_t	time_;
			task		task_;

			BUFFER		recv_;
			BUFFER		send_;
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

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	eth		イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		udp(ETHD& ethd, net_info& info) : ethd_(ethd), info_(info)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  格納可能な最大サイズを返す
			@return 格納可能な最大サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t capacity() const noexcept { return NMAX; }


		//-----------------------------------------------------------------//
		/*!
			@brief  オープン
			@param[in]	adrs	アドレス
			@param[in]	sport	転送元ポート
			@param[in]	dport	転送先ポート
			@return ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		int open(const ip_adrs& adrs, uint16_t sport, uint16_t dport)
		{
			uint32_t idx = udps_.alloc();
			if(udps_.is_alloc(idx)) {
				context& ctx = udps_.at(idx);
				std::memset(ctx.mac_, 0x00, 6);
				ctx.adrs_ = adrs;
				ctx.src_port_ = sport;
				ctx.src_port_match_ = false;
				ctx.dst_port_ = dport;
				ctx.dst_port_match_ = true;
				ctx.time_ = TIME_OUT;
				if(adrs.is_any() || adrs.is_brodcast()) {
					ctx.task_ = task::main;
				} else {
					ctx.task_ = task::open;
				}
				ctx.recv_.clear();
				ctx.send_.clear();

				udps_.unlock(idx);
				return static_cast<int>(idx);
			}
			return -1;
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
		int send(int desc, const void* src, uint16_t)
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!udps_.is_alloc(idx)) return -1;
			if(udps_.is_lock(idx)) return -1;

			context& ctx = udps_.at(idx);

			frame_t t;
			t.eh_.set_dst(ctx.mac_);
			t.eh_.set_src(info_.mac);
			t.eh_.set_type(eth_type::IPV4);
			t.ipv4_.ver_hlen_ = 0x45;
			t.ipv4_.type_ = 0x00;
//			t.udp_


			return 0;
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

			udps_.lock(idx);  // ロックする（割り込みで利用不可）
			context& con = udps_.at(idx);
			con.task_ = task::close;  // 実際のコンテキスト破棄は、サービスルーチン内で行う
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
				if(ctx.task_ != task::main) continue;  // task: main 以外は無効

				// 転送先の確認（ブロードキャスト）
///				if(ih.get_dst_ipa() 
				if(info_.ip != ih.get_dst_ipa()) continue;
				// 転送元の確認
				if(!ctx.adrs_.is_any() && ctx.adrs_ != ih.get_src_ipa()) continue; 

				// ポート番号の確認
				if(ctx.src_port_match_) {
					if(ctx.src_port_ != udp->get_src_port()) {
						continue;
					}
				}

				if(ctx.dst_port_match_) {
					if(ctx.dst_port_ != udp->get_dst_port()) {
						continue;
					}
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
				case task::open:
					{
						const auto& cash = info_.get_cash();
						auto idx = cash.lookup(ctx.adrs_);
						if(cash.is_valid(idx)) {
							std::memcpy(ctx.mac_, cash[idx].mac, 6);
							ctx.task_ = task::main;
utils::format("UDP MAC lookup: %s\n") % ctx.adrs_.c_str();
						}
					}
					break;

				case task::main:
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
