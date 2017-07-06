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
		udp_tcp_common() noexcept : blocks_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  MAC アドレス取得の検査
			@param[in]	ctx		コンテキスト
			@param[in]	info	ネット情報
			@return MAC アドレス取得済みなら「true」
		*/
		//-----------------------------------------------------------------//
		bool check_mac(CTX& ctx, net_info& info) noexcept
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
		inline BLOCKS& at_blocks() noexcept
		{
			return blocks_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンテキスト・ブロックの参照（const）
			@return コンテキスト・ブロック
		*/
		//-----------------------------------------------------------------//
		inline const BLOCKS& get_blocks() const noexcept
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

			const CTX& ctx = blocks_.get(idx);
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

			const CTX& ctx = blocks_.get(idx);
			return ctx.recv_.length();
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  UDP/TCP 文字出力テンプレートクラス
		@param[in]	SIZE	バッファ・サイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t SIZE>
	class desc_string
	{
	public:
		typedef utils::fixed_string<SIZE + 1> STR;  // 終端分を追加

	private:
		STR		str_;
		int		desc_;

	public:
		desc_string() : str_(), desc_(-1) { }

		void clear() {
			str_.clear();
		}

		void flush() {
			if(str_.size() > 0) {
				if(desc_ >= 0) {
					uint32_t len = str_.size();
					const char* p = str_.c_str();
#if 0
					while(len > 0) {
						uint32_t l = len;
						if(l >= 2048) {
							l = 2048;
						}
						r_send(fd_, p, l);
						len -= l;
						p += l;
					}
#else
///					r_send(fd_, p, len);
#endif				
				} else {
					utils::format("ether_string: FD is null.\n");
				}
			}
			clear();
		}

		void operator() (char ch) {
			if(ch == '\n') {
				str_ += '\r';  // 改行を「CR+LF」とする
				if(str_.size() >= (str_.capacity() - 1)) {
					flush();
				}
			}
			str_ += ch;
			if(str_.size() >= (str_.capacity() - 1)) {
				flush();
			}
		}

		uint32_t size() const { return str_.size(); }

		void set_desc(int desc) { desc_ = desc; }

		STR& at_str() { return str_; }
	};
}
