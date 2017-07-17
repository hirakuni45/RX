#pragma once
//=====================================================================//
/*!	@file
	@brief	ethernet_client class
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "ethernet.hpp"

#include "common/delay.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet_client class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ethernet_client {

		ethernet&	ethernet_;

		uint32_t	cepid_;
		uint16_t	port_;

		uint16_t	close_count_;

		uint16_t	re_con_cnt_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	e	インサーネットへの参照
			@param[in]	port	ポート番号
		*/
		//-----------------------------------------------------------------//
		ethernet_client(ethernet& e, uint16_t port) : ethernet_(e), cepid_(0), port_(port),
			close_count_(0), re_con_cnt_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  デストラクター
		*/
		//-----------------------------------------------------------------//
		~ethernet_client() {
			stop();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ethernet を参照
			@return ethernet
		*/
		//-----------------------------------------------------------------//
		ethernet& at_ethernet() { return ethernet_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ethernet を参照
			@return ethernet
		*/
		//-----------------------------------------------------------------//
		const ethernet& get_ethernet() const { return ethernet_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート番号を取得
			@return ポート番号
		*/
		//-----------------------------------------------------------------//
		uint16_t get_port() const { return port_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  CEP ID を取得
			@return CEP ID
		*/
		//-----------------------------------------------------------------//
		uint32_t get_cepid() const { return cepid_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  接続先を取得
			@return 接続先
		*/
		//-----------------------------------------------------------------//
		const ip_address& get_from_ip() const {
			const ethernet::CEP& cep = ethernet_.get_cep(cepid_);
			uint32_t ipw = cep.src_addr.ipaddr;
			static ip_address ip((ipw >> 24) & 255, (ipw >> 16) & 255, (ipw >> 8) & 255, ipw & 255);
			return ip;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コネクション
			@param[in]	ip		接続先の IP アドレス
			@param[in]	port	接続ポート
			@param[in]	timeout	タイムアウト、単位１０ミリ秒（標準で１０秒）
			@return 接続できた場合「true」
		*/
		//-----------------------------------------------------------------//
		bool connect(const ip_address& ip, uint16_t port, int32_t timeout = 1000)
		{
			if(cepid_ == 0) {
				cepid_ = ethernet_.create(port_);
				if(cepid_ == 0) return false;
				close_count_ = tcp_get_close_count(cepid_);
			}

			if(connected()) {
				return true;
			}

			debug_format("TCP Client Request Connect (%d): %d\n") % re_con_cnt_ % cepid_;

			static T_IPV4EP adr;
			adr.ipaddr =  (static_cast<uint32_t>(ip[0]) << 24)
						| (static_cast<uint32_t>(ip[1]) << 16)
						| (static_cast<uint32_t>(ip[2]) << 8)
						| (static_cast<uint32_t>(ip[3]));
			adr.portno = port;
			int ercd = tcp_con_cep(cepid_, NADR, &adr, timeout);
			if(ercd == E_OK) {
				debug_format("TCP Client connect OK: %d\n") % cepid_;
			} else if(ercd == E_QOVR) {
				debug_format("TCP Client E_QOVR: %d\n") % cepid_;
///				tcp_can_cep(cepid_, TFN_TCP_CON_CEP);
			} else {
				debug_format("TCP Client connect state(%d): %d\n") % ercd % cepid_;
			}
			++re_con_cnt_;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  再接続要求
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool re_connect()
		{
			if(cepid_ == 0) {  // ディスクリプタが無効
				return false;
			}

			if(tcp_re_con_cep(cepid_) < 0) {
				return false;
			} else {
				return true;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  接続確認
			@return 接続中なら「true」
		*/
		//-----------------------------------------------------------------//
		bool connected()
		{
			return ethernet_.connected(cepid_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み込み
			@param[out]	buff	読み込み先
			@param[in]	size	読み込みサイズ
			@return 読み込みサイズ（負の場合エラー）
		*/
		//-----------------------------------------------------------------//
		int read(void* buff, size_t size)
		{
			return ethernet_.read(cepid_, buff, size);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	buff	書き込み元
			@param[in]	size	サイズ
			@return 書き込みサイズ（負の場合エラー）
		*/
		//-----------------------------------------------------------------//
		int32_t write(const void* buffer, uint32_t size)
		{
			return ethernet_.write(cepid_, buffer, size);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  有効なデータがあるか
			@return 有効なデータ数
		*/
		//-----------------------------------------------------------------//
		int available()
		{
			return ethernet_.available(cepid_);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  停止
		*/
		//-----------------------------------------------------------------//
        void stop()
		{
			if(!connected()) {
				tcp_sht_cep(cepid_, TMO_FEVR);
			}
			tcp_cls_cep(cepid_, TMO_FEVR);
			ethernet::CEP& cep = ethernet_.at_cep(cepid_);
			cep.call_flag = false;
			end();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  終了
		*/
		//-----------------------------------------------------------------//
		void end()
		{
			tcp_init(cepid_);
			ethernet_.end_connection(cepid_);
			cepid_ = 0;
			re_con_cnt_ = 0;
		}
	};
}








