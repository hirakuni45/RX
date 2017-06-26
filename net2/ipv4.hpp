#pragma once
//=========================================================================//
/*! @file
    @brief  ipv4 クラス @n
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
		@brief  ipv4 クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ipv4 {

		static const uint16_t ICMP_REQ = 0x0008;


		struct header {
			uint8_t		ver_hlen;	///< バージョン(B0-B3)、ヘッダー長(B4-B7)
			uint8_t		type;		///< サービス・タイプ
			uint16_t	all_len;	///< 全長
			uint16_t	id;			///< 識別番号
			uint16_t	f_offset;	///< フラグ(B0-B2)、フラグメントオフセット(B3-B15)
			uint8_t		time;		///< 生存時間
			uint8_t		protocol;	///< プロトコル
			uint16_t	csum;		///< ヘッダ・チェックサム

			uint8_t		src_ipa[4];	///< 送信元 IP アドレス
			uint8_t		dst_ipa[4];	///< 宛先 IP アドレス
		};


		uint16_t sum_(const void* org, uint32_t len)
		{
			const uint8_t* p = static_cast<const uint8_t*>(org);
			uint32_t sum = 0;
			for(uint32_t i = 0; i < len; ++i) {
				sum += static_cast<uint32_t>(p[0]) << 8;
				sum += static_cast<uint32_t>(p[1]);
				p += 2;
			}
			return !((sum & 0xffff) + (sum >> 16));
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ipv4() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  パース
			@param[in]	org	データ・フレーム
			@param[in]	len	データ・フレーム長
			@param[in]	brodcast	ブロードキャスト
		*/
		//-----------------------------------------------------------------//
		bool parse(const void* org, int32_t len, bool brodcast)
		{
			const header* h = static_cast<const header*>(org);
			len -= 20;
			if(len < 0) {
				return false;
			}

			uint16_t sum = sum_(h, 10);
			if(sum != 0) {
				utils::format("IP Header sum error(%04X): %04X\n")
					% static_cast<uint32_t>(tools::htons(h->csum))
					% static_cast<uint32_t>(sum);
				return false;
			}

			list_header(org, len, brodcast);

			const uint16_t* p = static_cast<const uint16_t*>(org);
			uint16_t code = tools::htons(p[10]);
			switch(code) {
			case ICMP_REQ:

				break;
			default:
				break;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  IP ヘッダーの表示
			@param[in]	org	データ・フレーム
			@param[in]	len	データ・フレーム長
			@param[in]	brodcast	ブロードキャスト
		*/
		//-----------------------------------------------------------------//
		void list_header(const void* org, int32_t len, bool brodcast)
		{
			const header* h = static_cast<const header*>(org);
			len -= 20;

			uint8_t		ver_hlen;	///< バージョン(B0-B3)、ヘッダー長(B4-B7)
			uint8_t		type;		///< サービス・タイプ
			uint16_t	all_len;	///< 全長
			uint16_t	id;			///< 識別番号
			uint16_t	f_offset;	///< フラグ(B0-B2)、フラグメントオフセット(B3-B15)
			uint8_t		time;		///< 生存時間
			uint8_t		protocol;	///< プロトコル
			uint16_t	csum;		///< ヘッダ・チェックサム

			utils::format("IP Header: %s (%d)\n") % (brodcast ? "brodcast" : "") % len;
			utils::format("  version: %d, header length: %d\n")
				% static_cast<uint32_t>(h->ver_hlen & 0xf)
				% static_cast<uint32_t>(h->ver_hlen >> 4);
			utils::format("  length: %d") % tools::htons(h->all_len);
			utils::format(", id: %d") % tools::htons(h->id);
			utils::format(", flag: %d, fofs: %d\n")
				% tools::htons(h->f_offset & 7)
				% tools::htons(h->f_offset >> 3);
			utils::format("  time: %d\n") % tools::htons(h->time);
			utils::format("  protocol: %d\n") % static_cast<uint32_t>(h->protocol);
			utils::format("  csum: 0x%04X, src: %s, dst: %s\n")
				% tools::htons(h->csum)
				% tools::ip_str(h->src_ipa)
				% tools::ip_str(h->dst_ipa);
		}
	};
}

