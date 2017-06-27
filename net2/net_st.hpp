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
	enum class ipv4_protcol : uint8_t {
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
		ipv4_protcol	protocol;	///< プロトコル
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
}
