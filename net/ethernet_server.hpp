//=====================================================================//
/*!	@file
	@brief	イーサーネット・サーバー・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#pragma once

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet_server クラス
		@param[in]	ETHERNET	イーサーネット・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHERNET>
	class ethernet_server {

		uint16_t	port_;

		void accept_()
		{
			bool listening = false;
			for (int sock = 0; sock < ETHERNET::socket_max; sock++) {
				ethernet_client client(sock);
				if(ETHERNET::server_port[sock] == _port) {
					if(client.status() == SnSR::LISTEN) {
					listening = true;
					} else if(client.status() == SnSR::CLOSE_WAIT && !client.available()) {
						client.stop();
					}
				}
			}
			if(!listening) {
				begin();
			}
		}

	public:
		ethernet_server(uint16_t port) : port_(port) { }

		EthernetClient available()
		{
#if 0
EthernetClient EthernetServer::available()
{
  accept();

  for (int sock = 0; sock < MAX_SOCK_NUM; sock++) {
    EthernetClient client(sock);
    if (EthernetClass::_server_port[sock] == _port) {
      uint8_t s = client.status();
      if (s == SnSR::ESTABLISHED || s == SnSR::CLOSE_WAIT) {
        if (client.available()) {
          // XXX: don't always pick the lowest numbered socket.
          return client;
        }
      }
    }
  }

  return EthernetClient(MAX_SOCK_NUM);
}
#endif
		}


		void begin() {
#if 0
void EthernetServer::begin()
{
  for (int sock = 0; sock < MAX_SOCK_NUM; sock++) {
    EthernetClient client(sock);
    if (client.status() == SnSR::CLOSED) {
      socket(sock, SnMR::TCP, _port, 0);
      listen(sock);
      EthernetClass::_server_port[sock] = _port;
      break;
    }
  }  
}
#endif
		}

		size_t write(const void* buf, size_t size)
		{
#if 0
size_t EthernetServer::write(const uint8_t *buffer, size_t size) 
{
  size_t n = 0;
  
  accept();

  for (int sock = 0; sock < MAX_SOCK_NUM; sock++) {
    EthernetClient client(sock);

    if (EthernetClass::_server_port[sock] == _port &&
      client.status() == SnSR::ESTABLISHED) {
      n += client.write(buffer, size);
    }
  }
  
  return n;
}
#endif
		}

		size_t write(uint8_t data)
		{
			return write(&data, 1);
		}
	};
}
