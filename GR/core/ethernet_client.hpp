#pragma once
//=====================================================================//
/*!	@file
	@brief	ethernet_client class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ethernet.hpp"

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

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ethernet_client(ethernet& e) : ethernet_(e), cepid_(0), port_(0) { }


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
			@brief  コネクション
			@param[in]	ip		接続先の IP アドレス
			@param[in]	port	接続ポート
			@param[in]	timeout	タイムアウト、単位１０ミリ秒（標準で１０秒）
			@return 接続できた場合「１」
		*/
		//-----------------------------------------------------------------//
		int connect(const ip_address& ip, uint16_t port, int32_t timeout = 1000)
		{
			if(cepid_ == 0) {
				cepid_ = ethernet_.create(port);
				utils::format("New Client: %d\n") % cepid_;
				if(cepid_ == 0) return -1;
			}

			T_IPV4EP adr;
			adr.ipaddr =  (static_cast<uint32_t>(ip[0]) << 24)
						| (static_cast<uint32_t>(ip[1]) << 16)
						| (static_cast<uint32_t>(ip[2]) << 8)
						| (static_cast<uint32_t>(ip[3]));
			adr.portno = port;

			int res = 0;
			if(!connected()) {
				int ercd = tcp_con_cep(cepid_, NADR,  &adr, timeout);
				if(ercd == E_OK || ercd == E_WBLK) {
					res = 1;
				} else {
					res = -1;
				}
			} else {
				res = 1;  /* already connect */
			}
			return res;
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
			tcp_sht_cep(cepid_, TMO_FEVR);
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
			ethernet_.end_connection(cepid_);
			cepid_ = 0;
		}
	};
}








