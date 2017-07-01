#pragma once
//=========================================================================//
/*! @file
    @brief  TCP Protocol @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "net2/net_st.hpp"
#include "common/fixed_block.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TCP クラス
		@param[in]	ETHD	イーサーネット・ドライバー・クラス
		@param[in]	NMAX	管理最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHD, uint32_t NMAX>
	class tcp {

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

		typedef utils::fixed_block<context, NMAX> TCP_BLOCK;
		TCP_BLOCK	tcps_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	ethd	イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		tcp(ETHD& ethd, net_info& info) : ethd_(ethd), info_(info)
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
			@brief  プロセス
					※割り込み外から呼ぶ事は禁止
			@param[in]	eh	イーサーネット・ヘッダー
			@param[in]	ih	IPV4 ヘッダー
			@param[in]	tcp	TCP ヘッダー
			@param[in]	len	メッセージ長
			@return エラーが無い場合「true」
		*/
		//-----------------------------------------------------------------//
		bool process(const eth_h& eh, const ipv4_h& ih, const tcp_h* tcp, int32_t len)
		{
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  オープン
			@param[in]	adrs	アドレス
			@param[in]	port	ポート
			@return ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		int open(const ip_adrs& adrs, uint16_t port)
		{
			int ds = -1;


			return ds;
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
