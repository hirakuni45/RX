#pragma once
//=====================================================================//
/*!	@file
	@brief	Ethernet クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "ip_address.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet クラス
		@param[in]	SOCKET		ソケットハードウェアー
		@param[in]	SOCKET_MAX	ソケットの最大
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class SOCKET, uint32_t SOCKET_MAX>
	class ethernet {

		SOCKET&	sock_;

		ip_address	dns_server_;

		static uint8_t state_[SOCKET_MAX];
		static uint16_t server_port_[SOCKET_MAX];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	sock	ソケット・クラス（参照）
		*/
		//-----------------------------------------------------------------//
		ethernet(SOCKET& sock) : sock_(sock), dns_server_(0) { }


		// Initialise the Ethernet shield to use the provided MAC address and gain the rest of the
		// configuration through DHCP.
		// Returns 0 if the DHCP configuration failed, and 1 if it succeeded
		bool begin(const uint8_t* mac, uint32_t timeout = 60000, uint32_t response_timeout = 4000);


		void begin(const uint8_t* mac, const ip_address& local_ip, const ip_address& dns_server,
									   const ip_address& gateway, const ip_address& subnet)
		{
			sock_.init();
//			SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
//			W5100.setMACAddress(mac);
//			W5100.setIPAddress(local_ip.raw_address());
//			W5100.setGatewayIp(gateway.raw_address());
//			W5100.setSubnetMask(subnet.raw_address());
//			SPI.endTransaction();
//			_dnsServerAddress = dns_server;
		}


		void begin(const uint8_t* mac, const ip_address& local_ip, const ip_address& dns_server,
									   const ip_address& gateway)
		{
			ip_address subnet(255, 255, 255, 0);
			begin(mac, local_ip, dns_server, gateway, subnet);
		}


		void begin(const uint8_t* mac, const ip_address& local_ip, const ip_address& dns_server)
		{
			ip_address gateway = local_ip;
			gateway[3] = 1;
			begin(mac, local_ip, dns_server, gateway);
		}


		void begin(const uint8_t* mac, const ip_address& local_ip)
		{
			auto dns_server = local_ip;
			dns_server[3] = 1;
			begin(mac, local_ip, dns_server);
		}


		int maintain();


		const ip_address& local_ip() const;
		const ip_address& subnet_mask() const;
		const ip_address& gateway_ip() const;
		const ip_address& dns_server_ip() const;


		//-----------------------------------------------------------------//
		/*!
			@brief  SOCKET への参照
			@return SOCKET
		*/
		//-----------------------------------------------------------------//
		SOCKET& at_sock() { return sock_; }
	};

	template<class SOCKET, uint32_t SOCKET_MAX>
		uint8_t ethernet<SOCKET, SOCKET_MAX>::state_[SOCKET_MAX];
	template<class SOCKET, uint32_t SOCKET_MAX>
		uint16_t ethernet<SOCKET, SOCKET_MAX>::server_port_[SOCKET_MAX];
}
