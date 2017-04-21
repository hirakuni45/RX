#pragma once
//=====================================================================//
/*!	@file
	@brief	ethernet_server class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ip_address.hpp"
#include "ethernet.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet_server class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ethernet_server {

		ethernet&		ethernet_;

		uint16_t port_;
	
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		ethernet_server(ethernet& e) : ethernet_(e), port_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  デストラクター
		*/
		//-----------------------------------------------------------------//
		~ethernet_server() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート番号を取得
			@return ポート番号
		*/
		//-----------------------------------------------------------------//
		uint16_t get_port() const { return port_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	port	ポート番号
		*/
		//-----------------------------------------------------------------//
		void begin(uint16_t port = 0)
		{
			port_ = port;

#ifdef ETHER_DEBUG
			utils::format("t4:EthernetServer::begin:");
#endif
			if(port_ > 0) {
				/* initialize cep status */
				ethernet_.cep[0].status = T4_CLOSED;
				/* Initialize TCP reception point */
#ifdef ETHER_DEBUG
				utils::format("t4_set_tcp_crep():");
#endif
				if(t4_set_tcp_crep(ARDUINO_TCP_CEP, port_) != E_OK) {
					utils::format("t4_set_tcp_crep(): halt...\n");
					while(1);
				}
				/* Initialize TCP communication end point */
#ifdef ETHER_DEBUG
				utils::format("t4_set_tcp_ccep():\n");
#endif
				if(t4_set_tcp_ccep(ARDUINO_TCP_CEP, 0, TCP_MSS) != E_OK) {
					utils::format("t4_set_tcp_ccep(): halt...\n");
					while(1) ;
				}
			} else {
#ifdef ETHER_DEBUG
				utils::format("port == 0\n");
#endif
			}
		}


		size_t write(uint8_t byte);


		size_t write(const void* buffer, size_t size);


		void available()
		{
			int ercd = tcp_read_stat(ARDUINO_TCP_CEP);
#if defined(T4_ETHER_DEBUG)
			Serial.print("t4:EthernetServer::available():tcp_read_stat()=");
			Serial.print(ercd);
			Serial.println(":");
			Serial.print("get_tcp_acp_cep_call_flg()=");
			Serial.print(get_tcp_acp_cep_call_flg());
			Serial.println();
#endif
			if(ercd == T4_TCPS_CLOSED && ethernet_.get_tcp_acp_cep_call_flg() == 0) {
				ercd = tcp_acp_cep(ARDUINO_TCP_CEP, ARDUINO_TCP_CEP, &ethernet_.cep[0].dst_addr, TMO_NBLK);
#if defined(T4_ETHER_DEBUG)
				Serial.print("t4:EthernetServer::available():tcp_acp_cep(TMO_NBLK)=");
				Serial.print(ercd);
				Serial.print(":");
				if(ercd == E_WBLK){
					Serial.println("E_WBLK(success)");
				} else {
					Serial.print("fail:");
					Serial.println(ercd);
				}
#endif
				ethernet_.set_tcp_acp_cep_call_flg();   /*one time call flag is on*/
			}
		}


		size_t print(const char* t) {
			if(t == nullptr) return 0;
			size_t l = strlen(t);
			return write(t, l);
		}


		size_t print(int value) {
			char tmp[16];
			utils::format("%d", tmp, sizeof(tmp)) % value;
			return print(tmp);
		}


		/* get the length of the string * s return. '\ 0' is not included in length. */
		size_t println(const char* t = nullptr)
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


		int16_t t4_set_tcp_crep(ID repid, UH portno) {
			if (repid == 0 || repid > __tcprepn) {
				return -1;
			}
			tcp_crep[repid - 1].myaddr.portno = portno;
			return 0;
		}

		int16_t t4_set_tcp_ccep(ID cepid, UB ch, int rbufsz) {
			if (cepid == 0 || cepid > __tcpcepn){
				return -1;
			}
			tcp_ccep[cepid - 1].cepatr = ch;
			tcp_ccep[cepid - 1].rbufsz = rbufsz;
			return 0;
		}
	};
}








