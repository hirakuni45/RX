#pragma once
//=====================================================================//
/*!	@file
	@brief	イーサーネット・クライアント・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ip_address.h"

namespace net {

	class ethernet_client {

		static uint16_t srcport_;
		uint8_t sock_;

	public:
		ethernet_client();

		ethernet_client(uint8_t sock);

		uint8_t status();

		int connect(IPAddress ip, uint16_t port);

		int connect(const char *host, uint16_t port);

		size_t write(uint8_t);

		size_t write(const uint8_t *buf, size_t size);

		int available();

		int read();

		int read(uint8_t *buf, size_t size);

		int peek();

		void flush();

		void stop();

		uint8_t connected();

		operator bool();

		bool operator==(const bool value) { return bool() == value; }

		bool operator!=(const bool value) { return bool() != value; }

		bool operator==(const EthernetClient&);

		bool operator!=(const EthernetClient& rhs) { return !this->operator==(rhs); };

		uint8_t get_socket_number();
	};
}
