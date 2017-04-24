#pragma once
//=====================================================================//
/*!	@file
	@brief	ethernet_base クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ethernet.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet_base
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ethernet_base {

		ethernet&	ethernet_;

		uint16_t	port_;
		uint32_t	cepid_;

		int16_t set_tcp_crep_(ID repid, UH portno) {
			if (repid == 0 || repid > __tcprepn) {
				return -1;
			}
			tcp_crep[repid - 1].myaddr.portno = portno;
			return 0;
		}

		int16_t set_tcp_ccep_(ID cepid, UB ch, int rbufsz) {
			if (cepid == 0 || cepid > __tcpcepn){
				return -1;
			}
			tcp_ccep[cepid - 1].cepatr = ch;
			tcp_ccep[cepid - 1].rbufsz = rbufsz;
			return 0;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ethernet_base(ethernet& e) : ethernet_(e), port_(0), cepid_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  ethernet を参照
			@return ethernet
		*/
		//-----------------------------------------------------------------//
		ethernet& at_ethernet() { return ethernet_; }


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
			@brief  開始
			@param[in]	port	ポート番号
		*/
		//-----------------------------------------------------------------//
		void begin(uint16_t port)
		{
			port_ = port;

#ifdef ETHER_DEBUG
			utils::format("ethernet_server: begin: %d") % static_cast<int>(port);
#endif
			if(port_ > 0) {
				cepid_ = ethernet_.new_connection();
				if(cepid_ == 0) {
					utils::format("New connection fail\n");
					return;
				}

				/* initialize cep status */
				ethernet_.at_cep(cepid_).status = T4_CLOSED;
				/* Initialize TCP reception point */
#ifdef ETHER_DEBUG
				utils::format("set_tcp_crep_(): %d") % cepid_;
#endif
				if(set_tcp_crep_(cepid_, port_) != E_OK) {
					utils::format("set_tcp_crep() fail: %d\n") % cepid_;
					return;
				}

				/* Initialize TCP communication end point */
#ifdef ETHER_DEBUG
				utils::format("set_tcp_ccep(): %d\n") % cepid_;
#endif
				if(set_tcp_ccep_(cepid_, 0, ethernet::TCP_MSS) != E_OK) {
					utils::format("set_tcp_ccep_() fail: %d\n") % cepid_;
					return;
				}
			} else {
				utils::format("port == 0\n");
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  終了
		*/
		//-----------------------------------------------------------------//
		void end()
		{
			ethernet_.end_connection(cepid_);
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
			int ercd = tcp_read_stat(cepid_);
			if(ercd == T4_TCPS_ESTABLISHED || ercd == T4_TCPS_CLOSE_WAIT) {
				ret = true;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	byte	データ
			@return 書き込み成功なら「１」
		*/
		//-----------------------------------------------------------------//
		int32_t write(uint8_t data)
		{
			int32_t ercd = tcp_send_data(cepid_, &data, 1, TMO_FEVR);
			return ercd;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  １バイト書き込み
			@return 書き込み成功なら「１」
		*/
		//-----------------------------------------------------------------//
		int32_t write(const void* buffer, uint32_t size)
		{
			int32_t ercd;
			uint32_t current_send_size = 0;

			const uint8_t* p = static_cast<const uint8_t*>(buffer);
			if (size <= 0x7fff) {
				ercd = tcp_send_data(cepid_, p, size, TMO_FEVR);
			} else {
				while (size > current_send_size) {
					if((size - current_send_size) > 0x7fff) {
						ercd = tcp_send_data(cepid_, (p + current_send_size), 0x7fff, TMO_FEVR);
					} else {
						ercd = tcp_send_data(cepid_, (p + current_send_size),
									(size - current_send_size), TMO_FEVR);
					}
					if(ercd < 0) {
						break; // error
					}
					current_send_size += static_cast<uint32_t>(ercd);
				}
			}
			return current_send_size;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  １バイト読み込み
			@return 読み込みデータ
		*/
		//-----------------------------------------------------------------//
		int read()
		{
#if defined(ETHER_DEBUG)
			utils::format("EthernetClinet::read()");
			utils::format("%u : ") % static_cast<uint32_t>(millis());
#endif
			ethernet::CEP& cep = ethernet_.at_cep(cepid_);
			int32_t ercd = tcp_recv_data(cepid_, cep.recv_buf, 1, TMO_FEVR);
#if defined(ETHER_DEBUG)
			utils::format("%u\n") % static_cast<uint32_t>(millis());
#endif
			int recv_data;
			if(ercd <= 0) {
				recv_data = -1;
			} else {
				recv_data = static_cast<int>(cep.recv_buf[0]);
			}
			return recv_data;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み込み
			@param[out]	buf		読み込み先
			@param[in]	size	読み込みサイズ
			@return 読み込みサイズ
		*/
		//-----------------------------------------------------------------//
		int read(void* buf, size_t size)
		{
			int32_t ercd = tcp_recv_data(cepid_, buf, size, TMO_FEVR);
			if(ercd <= 0) {
				ercd = -1;
			}
			return ercd;
		}


		int print(const char* t) {
			if(t == nullptr) return 0;
			size_t l = strlen(t);
			return write(t, l);
		}


		int print(int value) {
			char tmp[16];
			utils::format("%d", tmp, sizeof(tmp)) % value;
			return print(tmp);
		}


		/* get the length of the string * s return. '\ 0' is not included in length. */
		int println(const char* t = nullptr)
		{
			if(t == nullptr) {
				return write("\r\n", 2);
			}

			size_t l = strlen(t);
			char tmp[l + 2];
			strcpy(tmp, t);
			tmp[l + 0] = '\r';
			tmp[l + 1] = '\n';
			return write(tmp, l + 2);
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
				int ercd = tcp_read_stat(cepid_);

				if(ret == 0 && ercd == T4_TCPS_CLOSE_WAIT) {
					tcp_sht_cep(cepid_, TMO_FEVR);
				}
			}
			return ret;
		}
	};
}
