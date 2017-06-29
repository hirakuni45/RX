#pragma once
//=========================================================================//
/*! @file
    @brief  UDP Protocol @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "net2/net_st.hpp"
#include "net2/mac_cash.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  UDP クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class udp {

		enum class task : uint8_t {
			idle,
		};

		task		task_;

		struct frame_t {
			eth_h	eh_;
			ipv4_h	ipv4_;
			udp_h	udp_;
		} __attribute__((__packed__));

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		udp() : task_(task::idle) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  パース
			@param[in]	eh	イーサーネット・ヘッダー
			@param[in]	ih	IPV4 ヘッダー
			@param[in]	msg	メッセージ先頭
			@param[in]	len	メッセージ長
			@return エラーが無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool parse(const eth_h& eh, const ipv4_h& ih, const void* msg, int32_t len)
		{
			const udp_h* h = reinterpret_cast<const udp_h*>(msg);



			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オープン
			@param[in]	adrs	アドレス
			@param[in]	port	ポート
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool open(const ip_adrs& adrs, uint16_t port)
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
		}
	};
}
