#pragma once
//=========================================================================//
/*! @file
    @brief  UDP Protocol 全体管理 @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "net2/udp.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  UDP マネージメント・クラス
		@param[in]	ETHER	イーサーネット・ドライバー・クラス
		@param[in]	NMAX	管理最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHER, uint32_t NMAX>
	class udp_manage {

		ETHER&		eth_;

		udp			udp_[NMAX];

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
		*/
		//-----------------------------------------------------------------//
		udp_manage(ETHER& eth) : eth_(eth)
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
			int ds = 0;
			for(uint32_t i = 0; i < NMAX; ++i) {
				if(udp_[i].empty()) {
					udp_[i].open(adrs, sport, dport);
					return i;
				}
			}
			return -1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  プロセス（割り込みから呼ばれる）
			@param[in]	eh	イーサーネット・ヘッダー
			@param[in]	ih	IPV4 ヘッダー
			@param[in]	msg	メッセージ先頭
			@param[in]	len	メッセージ長
			@return エラーが無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool process(const eth_h& eh, const ipv4_h& ih, const void* msg, int32_t len)
		{


			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（１０ｍｓ毎に呼ぶ）
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			for(udp& u : udp_) {
///				u.service();
			}
		}
	};
}
