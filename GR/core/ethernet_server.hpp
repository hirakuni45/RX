#pragma once
//=====================================================================//
/*!	@file
	@brief	ethernet_server class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
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
				cepid_ = ethernet_.start(port, true);
				if(cepid_ > 0) {
					port_ = port;
				}
			} else {
				utils::format("port == 0\n");
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
			bool ret = false;
			TCP_API_STAT ercd = tcp_read_stat(cepid_);
			if(ercd == TCP_API_STAT_ESTABLISHED || ercd == TCP_API_STAT_CLOSE_WAIT) {
				ret = true;
			}
			return ret;
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
			int ret = 0;
			if(connected()) {
				ret = head_tcb[cepid_ - 1].rdsize;
				TCP_API_STAT ercd = tcp_read_stat(cepid_);

				if(ret == 0 && ercd == TCP_API_STAT_CLOSE_WAIT) {
					tcp_sht_cep(cepid_, TMO_FEVR);
				}
			}
			return ret;
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
			cep.call_flag = false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  終了
		*/
		//-----------------------------------------------------------------//
		void end()
		{
			stop();
			ethernet_.end_connection(cepid_);
		}
	};
}
