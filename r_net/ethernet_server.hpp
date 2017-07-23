#pragma once
//=====================================================================//
/*!	@file
	@brief	ethernet_server class
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "ethernet.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet_server class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ethernet_server {

		ethernet&	ethernet_;

		uint32_t	cepid_;
		uint16_t	port_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ethernet_server(ethernet& e) : ethernet_(e), cepid_(0), port_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  デストラクター
		*/
		//-----------------------------------------------------------------//
		~ethernet_server() {
			stop();
			end();
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
			uint32_t ipw = cep.dst_addr.ipaddr;
			static ip_address ip((ipw >> 24) & 255, (ipw >> 16) & 255, (ipw >> 8) & 255, ipw & 255);
			return ip;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	port	ポート番号
		*/
		//-----------------------------------------------------------------//
		void begin(uint16_t port)
		{
			if(port > 0) {
				cepid_ = ethernet_.create(port);
				if(cepid_ > 0) {
					port_ = port;
					auto& cep = ethernet_.at_cep(cepid_);
					cep.server = true;
				}
			} else {
				debug_format("port == 0\n");
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
			tcp_cls_cep(cepid_, TMO_FEVR);
			ethernet::CEP& cep = ethernet_.at_cep(cepid_);
			end();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  終了
		*/
		//-----------------------------------------------------------------//
		void end()
		{
			ethernet_.end_connection(cepid_);
			cepid_ = 0;
		}
	};
}
