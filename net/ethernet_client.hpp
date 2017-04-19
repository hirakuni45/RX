#pragma once
//=====================================================================//
/*!	@file
	@brief	イーサーネット・クライアント・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ip_address.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet_client クラス
		@param[in]	ETHERNET	イーサーネット・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHERNET>
	class ethernet_client {

		static uint16_t srcport_;

		uint8_t sock_id_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	sock	ソケット・ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		ethernet_client(uint8_t sock_id = ETHERNET::socket_max) : sock_id_(sock_id) { }



		uint8_t status();
#if 0
uint8_t EthernetClient::status() {
  if (_sock == MAX_SOCK_NUM) return SnSR::CLOSED;
  return socketStatus(_sock);
}
#endif


		bool connect(IPAddress ip, uint16_t port);
#if 0
int EthernetClient::connect(IPAddress ip, uint16_t port) {
  if (_sock != MAX_SOCK_NUM)
    return 0;

  for (int i = 0; i < MAX_SOCK_NUM; i++) {
    uint8_t s = socketStatus(i);
    if (s == SnSR::CLOSED || s == SnSR::FIN_WAIT || s == SnSR::CLOSE_WAIT) {
      _sock = i;
      break;
    }
  }

  if (_sock == MAX_SOCK_NUM)
    return 0;

  _srcport++;
  if (_srcport == 0) _srcport = 49152;          //Use IANA recommended ephemeral port range 49152-65535
  socket(_sock, SnMR::TCP, _srcport, 0);

  if (!::connect(_sock, rawIPAddress(ip), port)) {
    _sock = MAX_SOCK_NUM;
    return 0;
  }

  while (status() != SnSR::ESTABLISHED) {
    delay(1);
    if (status() == SnSR::CLOSED) {
      _sock = MAX_SOCK_NUM;
      return 0;
    }
  }

  return 1;
}
#endif

		int connect(const char* host, uint16_t port);


		size_t write(const uint8_t *buf, size_t size)
		{
#if 0
size_t EthernetClient::write(const uint8_t *buf, size_t size) {
  if (_sock == MAX_SOCK_NUM) {
    setWriteError();
    return 0;
  }
  if (!send(_sock, buf, size)) {
    setWriteError();
    return 0;
  }
  return size;
}
#endif
			return 0;
		}


		size_t write(uint8_t data) { return write(&data, 1); }


		int available();
#if 0
int EthernetClient::available() {
  if (_sock != MAX_SOCK_NUM)
    return recvAvailable(_sock);
  return 0;
}
#endif


		int read();
#if 0
int EthernetClient::read() {
  uint8_t b;
  if ( recv(_sock, &b, 1) > 0 )
  {
    // recv worked
    return b;
  }
  else
  {
    // No data available
    return -1;
  }
}
#endif

		int read(uint8_t *buf, size_t size);
#if 0
  return recv(_sock, buf, size);
#endif

		int peek();
#if 0
int EthernetClient::peek() {
  uint8_t b;
  // Unlike recv, peek doesn't check to see if there's any data available, so we must
  if (!available())
    return -1;
  ::peek(_sock, &b);
  return b;
}
#endif

		void flush();
#if 0
void EthernetClient::flush() {
  ::flush(_sock);
}
#endif

		void stop();
#if 0
void EthernetClient::stop() {
  if (_sock == MAX_SOCK_NUM)
    return;

  // attempt to close the connection gracefully (send a FIN to other side)
  disconnect(_sock);
  unsigned long start = millis();

  // wait up to a second for the connection to close
  uint8_t s;
  do {
    s = status();
    if (s == SnSR::CLOSED)
      break; // exit the loop
    delay(1);
  } while (millis() - start < 1000);

  // if it hasn't closed, close it forcefully
  if (s != SnSR::CLOSED)
    close(_sock);

  EthernetClass::_server_port[_sock] = 0;
  _sock = MAX_SOCK_NUM;
}
#endif


		uint8_t connected();
#if 0
uint8_t EthernetClient::connected() {
  if (_sock == MAX_SOCK_NUM) return 0;

  uint8_t s = status();
  return !(s == SnSR::LISTEN || s == SnSR::CLOSED || s == SnSR::FIN_WAIT ||
    (s == SnSR::CLOSE_WAIT && !available()));
}
#endif

		operator bool() const { return sock_id_ != ETHERNET::socket_max; }


		bool operator == (const bool value) const { return bool() == value; }


		bool operator!=(const bool value) const { return bool() != value; }


		bool operator == (const ethernet_client& rhs) const {
			return sock_id_ == rhs.sock_id_
				&& sock_id_ != ETHERNET::socket_max && rhs.sock_id_ != ETHERNET::socket_max;
		}


		bool operator != (const ethernet_client& rhs) const { return !this->operator == (rhs); };


		//-----------------------------------------------------------------//
		/*!
			@brief  ソケットのＩＤ（ディスクリプタ）を返す
			@return ソケットのＩＤ
		*/
		//-----------------------------------------------------------------//
		uint8_t get_socket_id() const { return sock_id_; }
	};
}
