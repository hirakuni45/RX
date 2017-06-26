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

		struct header {
			uint8_t		ver_hlen;	///< バージョン(B0-B3)、ヘッダー長(B4-B7)
			uint8_t		type;		///< サービス・タイプ
			uint16_t	paket_len;	///< パケット長
			uint16_t	id;			///< 識別番号
			uint16_t	f_offset;	///< フラグ(B0-B2)、フラグメントオフセット(B3-B15)
			uint8_t		time;		///< 生存時間
			uint8_t		protocol;	///< プロトコル
			uint16_t	checksum;	///< ヘッダ・チェックサム

			uint8_t		src_ipa[4];	///< 送信元 IP アドレス
			uint8_t		dst_ipa[4];	///< 宛先 IP アドレス

			uint8_t		option[3];	///< オプション
			uint8_t		pad;		///< パディング
		};

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
		*/
		//-----------------------------------------------------------------//
		bool parse(const uint8_t* org, uint32_t len)
		{


			return true;
		}
	};
}

