#pragma once
//=========================================================================//
/*! @file
    @brief  UDP Protocol @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "net2/net_st.hpp"
#include "common/fixed_block.hpp"

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


		struct context {
			ip_adrs		adrs_;
			uint16_t	src_port_;
			uint16_t	dst_port_;
			uint16_t	time_;
			task		task_;

			uint8_t*	recv_;
			uint8_t*	send_;
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
				context& con = udps_.at(idx);
				con.adrs_ = adrs;
				con.src_port_ = sport;
				con.dst_port_ = dport;
				con.time_ = TIME_OUT;
				con.task_ = task::open;

				con.recv_ = nullptr;
				con.send_ = nullptr;

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




			return 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  受信
			@param[in]	desc	ディスクリプタ
			@param[in]	dst		ソース
			@param[in]	len		受信バイト数
			@param[in]	time	最大待ち時間（１０ｍｓ単位）
			@return 受信バイト
		*/
		//-----------------------------------------------------------------//
		int recv(int desc, void* dst, uint16_t len, int16_t time)
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!udps_.is_alloc(idx)) return -1;
			if(udps_.is_lock(idx)) return -1;



			return 0;
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
#if 0
			// 該当するコンテキストを探す
			uint32_t idx = NMAX;
			for(uint32_t i = 0; i < NMAX; ++i) {
				if(!udps_.is_alloc(i)) continue;  // alloc: 有効
				if(udps_.is_lock(i)) continue;  // lock:  無効
				context& con = udps_.at(i);
				if(con.task_ != task::main) continue;  // task: main 以外は無効

				if(udp->get_src_port() == con.dst_port_ && udp->get_dst_port() == con.src_port_) {
					idx = i;
					break;
				} 
			}
			if(idx == NMAX) return false;
#endif
			if(udp->get_dst_port() != 3000) {
				return false;
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

			dump(*udp);

			char tmp[16];
			std::memcpy(tmp, udp->get_data_ptr(udp), udp->get_data_len());
			tmp[udp->get_data_len()] = 0;
			utils::format("UDP Data: '%s'\n") % tmp;

			return true;
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

				context& con = udps_.at(i);
				switch(con.task_) {
				case task::open:					
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
