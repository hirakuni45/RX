#pragma once
//=====================================================================//
/*!	@file
	@brief	ethernet_client class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ip_address.hpp"
#include "ethernet.hpp"
#include "ethernet_server.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet_client class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ethernet_client {

		ethernet&	ethernet_;	
		ethernet_server	server_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ethernet_client(ethernet& e) : ethernet_(e), server_(e) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  デストラクター
		*/
		//-----------------------------------------------------------------//
		~ethernet_client() { }

		size_t write(uint8_t byte);

		size_t write(const void* buffer, size_t size);


		//-----------------------------------------------------------------//
		/*!
			@brief  １バイト読み込み
			@return 読み込みデータ
		*/
		//-----------------------------------------------------------------//
		int read()
		{
#if defined(ETHER_DEBUG)
			utils::format("t4:EthernetClinet::read()");
			utils::format("%u : ") % static_cast<uint32_t>(millis());
#endif
			int32_t ercd = tcp_recv_data(ARDUINO_TCP_CEP, ethernet_.cep[0].rcv_buf, 1, TMO_FEVR);
#if defined(ETHER_DEBUG)
			utils::format("%u\n") % static_cast<uint32_t>(millis());
#endif
			int rcv_data;
			if(ercd <= 0) {
				rcv_data = -1;
			} else {
				rcv_data = static_cast<int>(ethernet_.cep[0].rcv_buf[0]);
			}
			return rcv_data;
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
			int32_t ercd = tcp_recv_data(ARDUINO_TCP_CEP, buf, size, TMO_FEVR);
			if(ercd <= 0) {
				ercd = -1;
			}
			return ercd;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列の転送
			@param[in]	str	文字列
		*/
		//-----------------------------------------------------------------//
		void print(const char* str) { server_.print(str); }


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列の転送＋改行
			@param[in]	str	文字列
		*/
		//-----------------------------------------------------------------//
		void println(const char* str = nullptr) { server_.println(str); }


		//-----------------------------------------------------------------//
		/*!
			@brief  接続確認
			@return 接続中なら「true」
		*/
		//-----------------------------------------------------------------//
		bool connected()
		{
			int ercd = tcp_read_stat(ARDUINO_TCP_CEP);
#if defined(T4_ETHER_DEBUG)
			utils::format("t4:EthernetClient::connected():tcp_read_stat=%d") % ercd;
			utils::format(":");
#endif
			bool res;
			if(ercd == T4_TCPS_ESTABLISHED || ercd == T4_TCPS_CLOSE_WAIT) {
				res = true;
#if defined(T4_ETHER_DEBUG)
				utils::format(":return true\n");
#endif
			} else {
				res = false;
#if defined(T4_ETHER_DEBUG)
				utils::format(":return false\n");
#endif
			}
			return res;
		}


		/// timeout [ms]
		int connect(const ip_address& ip, uint16_t port, int32_t timeout = 3000);


///		int connect(const uint8_t* host, uint16_t port, int32_t timeout = 3000);


		//-----------------------------------------------------------------//
		/*!
			@brief  有効なデータがあるか
			@return 有効なデータ数
		*/
		//-----------------------------------------------------------------//
		int available()
		{
			int res = 0;
			if(connected()){
				res =  head_tcb[0].rdsize;
				int ercd = tcp_read_stat(ARDUINO_TCP_CEP);
#ifdef ETHER_DEBUG
				static int ercd_ = -1;
				if(ercd != ercd_) {
					utils::format("(%d) tcp_read_stat: %d\n") % res % ercd;
					ercd_ = ercd;
				}
#endif
				if(res == 0 && ercd == T4_TCPS_CLOSE_WAIT) {
#ifdef ETHER_DEBUG
					utils::format("tcp_sht_cep\n");
#endif
					tcp_sht_cep(ARDUINO_TCP_CEP);
				}
			}
			return res;
		}


		void flush();


		//-----------------------------------------------------------------//
		/*!
			@brief  停止
		*/
		//-----------------------------------------------------------------//
		void stop()
		{
#if defined(T4_ETHER_DEBUG)
			Serial.print("t4:EthernetClient::stop():");
#endif
			while(tcp_sht_cep(ARDUINO_TCP_CEP) != E_OK) {
				delay(1);
			}
			ethernet_.stop();
		}


		operator bool() {
			return connected();
		}

		bool operator == (const bool value) {
#ifdef T4_ETHER_DEBUG
			Serial.print("t4:EthernetClient:==:");
			Serial.println(bool() == value);
#endif
			return bool() == value;
		}

		bool operator != (const bool value) {
#ifdef T4_ETHER_DEBUG
			Serial.print("t4:EthernetClient:!=:");
			Serial.println(bool() != value);
#endif
			return bool() != value;
		}

		bool operator == (const ethernet_client& rhs) {
#ifdef T4_ETHER_DEBUG
			Serial.println("t4:EthernetClient:==:true");
#endif
			return true;
		}


		bool operator != (const ethernet_client& rhs) {
#ifdef T4_ETHER_DEBUG
			Serial.print("t4:EthernetClient:!=:");
			Serial.println(!this->operator==(rhs));
#endif
			return !this->operator==(rhs);
		}
	};
}








