#pragma once
//=========================================================================//
/*! @file
    @brief  UDP/TCP 共通クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "common/fixed_block.hpp"
#include "net2/net_st.hpp"
#include "net2/memory.hpp"

#define UDP_TCP_DEBUG

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  UDP/TCP 共通テンプレート
		@param[in]	CTX	コンテキスト
		@param[in]	NMAX	管理最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class CTX, uint32_t NMAX>
	class udp_tcp_common {

#ifndef UDP_TCP_DEBUG
		typedef utils::null_format debug_format;
#else
		typedef utils::format debug_format;
#endif

		typedef utils::fixed_block<CTX, NMAX> BLOCKS;
		BLOCKS	blocks_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		udp_tcp_common() : blocks_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  MAC アドレス取得の検査
			@param[in]	ctx		コンテキスト
			@param[in]	info	ネット情報
			@return MAC アドレス取得済みなら「true」
		*/
		//-----------------------------------------------------------------//
		bool check_mac(CTX& ctx, net_info& info)
		{
			const auto& cash = info.get_cash();
			auto idx = cash.lookup(ctx.adrs_);
			if(cash.is_valid(idx)) {
				std::memcpy(ctx.mac_, cash[idx].mac, 6);
				debug_format("UDP/TCP MAC lookup: %s at %s\n")
					% ctx.adrs_.c_str()
					% tools::mac_str(cash[idx].mac);
				return true;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンテキスト・ブロックの参照
			@return コンテキスト・ブロック
		*/
		//-----------------------------------------------------------------//
		inline BLOCKS& at_blocks()
		{
			return blocks_;
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
		int send(int desc, const void* src, uint16_t len) noexcept
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!blocks_.is_alloc(idx)) return -1;
			if(blocks_.is_lock(idx)) return -1;

			CTX& ctx = blocks_.at(idx);
			uint16_t spc = ctx.send_.size() - ctx.send_.length() - 1;
			if(spc < len) {
				len = spc;
			}
			ctx.send_.put(src, len);

			return len;
		}

		//-----------------------------------------------------------------//
		/*!
			@brief  送信バッファの残量取得
			@param[in]	desc	ディスクリプタ
			@return 送信バッファの残量（負の値はエラー）
		*/
		//-----------------------------------------------------------------//
		int get_send_length(int desc) const noexcept
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!blocks_.is_alloc(idx)) return -1;
			if(blocks_.is_lock(idx)) return -1;

			CTX& ctx = blocks_.at(idx);
			return ctx.send_.length();
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
		int recv(int desc, void* dst, uint16_t len) noexcept
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!blocks_.is_alloc(idx)) return -1;
			if(blocks_.is_lock(idx)) return -1;

			CTX& ctx = blocks_.at(idx);
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
			@brief  受信バッファの残量取得
			@param[in]	desc	ディスクリプタ
			@return 受信バッファの残量（負の値はエラー）
		*/
		//-----------------------------------------------------------------//
		int get_recv_length(int desc) const noexcept
		{
			uint32_t idx = static_cast<uint32_t>(desc);
			if(!blocks_.is_alloc(idx)) return -1;
			if(blocks_.is_lock(idx)) return -1;

			CTX& ctx = blocks_.at(idx);
			return ctx.recv_.length();
		}
	};
}
