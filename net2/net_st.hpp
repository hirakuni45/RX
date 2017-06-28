#pragma once
//=========================================================================//
/*! @file
    @brief  NET 関係構造体 @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include <cstdint>
#include <cstring>
#include "common/net_tools.hpp"
#include "common/format.hpp"
#include "common/ip_adrs.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ネット情報構造体
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct net_info {
		uint8_t		mac[6];  ///< イーサーネット、ＭＡＣアドレス（EUI-48）

		ip_adrs		ip;      ///< IP アドレス 
		ip_adrs		mask;    ///< ネット・マスク
		ip_adrs		gw;      ///< ゲートウェイ
		ip_adrs		dns;     ///< Domain Name Server
		ip_adrs		dns2;    ///< Domain Name Server 2ND

		net_info() : mac{ 0 }, ip(), mask(), gw(), dns(), dns2() { }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  イーサーネット・タイプ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class eth_type : uint16_t {
		IPV4       = 0x0800,  ///< IPV4
		ARP        = 0x0806,  ///< ARP
		APPLETALK  = 0x809B,  ///< AppleTalk
		IEEE802_1Q = 0x8100,  ///< IEEE802.1Q
		IPX        = 0x8137,  ///< IPX
		IPV6       = 0x86DD,  ///< IPV6
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  イーサーネット・ヘッダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct eth_h {
		uint8_t		dst[6];    ///< destination MAC address 受信先
		uint8_t		src[6];    ///< source MAC address 送信元
		eth_type	type;      ///< type


		//-----------------------------------------------------------------//
		/*!
			@brief  イーサーネット・タイプの取得 @n
					※ネット・エンディアンを変換
			@return イーサーネット・タイプ
		*/
		//-----------------------------------------------------------------//
		eth_type get_type() const {
			return static_cast<eth_type>(tools::htons(static_cast<uint16_t>(type)));
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  イーサーネット・ヘッダー、スワップコピー
		@param[out]	dst	コピー先
		@param[in]	src	コピー元
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	void swap_copy_eth_h(eth_h* dst, const eth_h* src)
	{
		std::memcpy(dst->dst, src->src, 6);
		std::memcpy(dst->src, src->dst, 6);
		dst->type = src->type;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  イーサーネット・ヘッダーのダンプ
		@param[in]	h	イーサーネット・ヘッダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	void dump(const eth_h& h) {
		utils::format("src(%s), dst(%s), type(%04X)\n")
			% tools::mac_str(h.src)
			% tools::mac_str(h.dst)
			% static_cast<uint32_t>(h.get_type());
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IPV4 プロトコル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class ipv4_protocol : uint8_t {
		ICMP = 0x01,	///< ICMP
		TCP  = 0x06,	///< TCP
		UDP  = 0x11,	///< UDP
	};

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IPV4 ヘッダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct ipv4_h {
		uint8_t		ver_hlen;	///< バージョン(B0-B3)、ヘッダー長(B4-B7)
		uint8_t		type;		///< サービス・タイプ
		uint16_t	length;		///< 全長
		uint16_t	id;			///< 識別番号
		uint16_t	f_offset;	///< フラグ(B0-B2)、フラグメントオフセット(B3-B15)
		uint8_t		time;		///< 生存時間
		ipv4_protocol	protocol;	///< プロトコル
		uint16_t	csum;		///< ヘッダ・チェックサム

		uint8_t		src_ipa[4];	///< 送信元 IP アドレス
		uint8_t		dst_ipa[4];	///< 宛先 IP アドレス

		uint16_t get_version() const { return ver_hlen & 0x0f; }
		uint16_t get_header_length() const { return ver_hlen >> 4; }
		uint16_t get_length() const { return tools::htons(length); }
		uint16_t get_id() const { return tools::htons(id); }
		uint16_t get_flag() const { return tools::htons(f_offset) >> 13; }
		uint16_t get_flagment_offset() const { return tools::htons(f_offset) & 0x1fff; }
		uint16_t get_time() const { return static_cast<uint16_t>(time); }
		ipv4_protocol get_protocol() const { return protocol; }
		uint16_t get_csum() const { return tools::htons(csum); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IPV4 ヘッダー、スワップコピー
		@param[out]	dst	コピー先
		@param[in]	src	コピー元
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	void swap_copy_ipv4_h(ipv4_h* dst, const ipv4_h* src)
	{
		std::memcpy(dst, src, 12);
		std::memcpy(dst->src_ipa, src->dst_ipa, 4);
		std::memcpy(dst->dst_ipa, src->src_ipa, 4);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  IPV4 ヘッダーのダンプ
		@param[in]	h	IPV4 ヘッダー
	*/
	//-----------------------------------------------------------------//
	void dump(const ipv4_h& h)
	{
		utils::format("IP Header:\n");
		utils::format("  version: %d, header length: %d\n")
			% h.get_version()
			% h.get_header_length();
		utils::format("  length: %d") % h.get_length();
		utils::format(", id: %d") % h.get_id();
		utils::format(", flag: %d, flagment ofs: %d\n")
			% h.get_flag()
			% h.get_flagment_offset();
		utils::format("  time: %d") % h.get_time();

		switch(h.get_protocol()) {
		case ipv4_protocol::ICMP:
			utils::format(", ICMP\n");
			break;
		case ipv4_protocol::TCP:
			utils::format(", TCP\n");
			break;
		case ipv4_protocol::UDP:
			utils::format(", UDP\n");
			break;
		default:
			utils::format(", Other(%d)\n") % static_cast<uint32_t>(h.get_protocol());
			break;
		}

		utils::format("  csum: 0x%04X, src: %s, dst: %s\n")
			% h.get_csum()
			% tools::ip_str(h.src_ipa)
			% tools::ip_str(h.dst_ipa);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TCP セグメント・ヘッダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class tcp_segment {

		static void set_flag_(bool f, uint16_t mask, uint16_t& dst) {
			if(f) {
				dst |=  mask;
			} else {
				dst &= ~mask;
			}
		}

	public:
		uint16_t	src_port_;
		uint16_t	dst_port_;
		uint32_t	seq_;
		uint32_t	ack_;
		uint16_t	flag_ofs_;
		uint16_t	window_;
		uint16_t	csum_;
		uint16_t	urgent_ptr_;

		uint16_t get_src_port() const { return tools::htons(src_port_); }
		void set_src_port(uint16_t port) { src_port_ = tools::htons(port); }

		uint16_t get_dst_port() const { return tools::htons(dst_port_); }
		void set_dst_port(uint16_t port) { dst_port_ = tools::htons(port); }

		uint32_t get_seq() const { return tools::htonl(seq_); }
		void set_seq(uint32_t seq) { seq_ = tools::htonl(seq); }

		uint32_t get_ack() const { return tools::htonl(ack_); }
		void set_ack(uint32_t ack) { ack_ = tools::htonl(ack); }

		uint16_t get_flag_ofs() const { return tools::htons(flag_ofs_); }
		void set_flag_ofs(uint16_t ofs) { flag_ofs_ = tools::htons(ofs); }

		uint16_t get_window() const { return tools::htons(window_); }
		void set_window(uint16_t win) { window_ = tools::htons(win); }

		uint16_t get_csum() const { return tools::htons(csum_); }
		void set_csum(uint16_t sum) { csum_ = tools::htons(sum); }

		uint16_t get_urgent_ptr() const { return tools::htons(urgent_ptr_); }
		void set_urgent_ptr(uint16_t ptr) { urgent_ptr_ = tools::htons(ptr); }

		bool get_flag_urg() const { return (flag_ofs_ & 0x0004) != 0; }
		void set_flag_urg(bool f) { set_flag_(f, 0x0004, flag_ofs_); }

		bool get_flag_ack() const { return (flag_ofs_ & 0x0008) != 0; }
		void set_flag_ack(bool f) { set_flag_(f, 0x0008, flag_ofs_); }

		bool get_flag_psh() const { return (flag_ofs_ & 0x0010) != 0; }
		void set_flag_psh(bool f) { set_flag_(f, 0x0010, flag_ofs_); }

		bool get_flag_rst() const { return (flag_ofs_ & 0x0020) != 0; }
		void set_flag_rst(bool f) { set_flag_(f, 0x0020, flag_ofs_); }

		bool get_flag_syn() const { return (flag_ofs_ & 0x0040) != 0; }
		void set_flag_syn(bool f) { set_flag_(f, 0x0040, flag_ofs_); }

		bool get_flag_fin() const { return (flag_ofs_ & 0x0080) != 0; }
		void set_flag_fin(bool f) { set_flag_(f, 0x0080, flag_ofs_); }
	};
}
