#pragma once
//=====================================================================//
/*!	@file
	@brief	DHCP クライアント・テンプレート・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include <cstring>
#include "common/format.hpp"
#include "common/input.hpp"

#ifdef BIG_ENDIAN
#elif LITTLE_ENDIAN
#elif
#error "dhcp_client.hpp requires BIG_ENDIAN or LITTLE_ENDIAN be defined."
#endif

extern "C" {
	void reset_timer(void);
	uint32_t get_timer(void);
}

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DHCP Client テンプレート・クラス
		@param[in]	ETHER_IO	インサーネット入出力・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHER_IO>
	class dhcp_client {

		static const uint32_t TIMEOUT = 2 * 1000 / 10;  ///< 2sec (unit 10ms)
		static const uint8_t DOMAIN_GET = 0x01;

	public:
		struct dhcp_t {
			uint8_t	ipaddr[4];
			uint8_t	maskaddr[4];
			uint8_t	gwaddr[4];
			uint8_t	dnsaddr[4];
			uint8_t	dnsaddr2[4];
			char	domain[20];
			uint8_t	macaddr[6];
		};

	private:
		static const uint32_t EXPANSION_DHCP_PACKET_SIZE  = 300;
		static const uint32_t TRANSACTION_ID = 0x12345678;

		struct dv_options {
			uint32_t	magic_cookie;
			uint16_t	message_type1;
			uint8_t		message_type2;
			uint16_t	client_id1;
			uint8_t		client_id2;
			uint8_t		client_mac[6];
			uint8_t		dummy[48 + EXPANSION_DHCP_PACKET_SIZE];

			dv_options() :
				magic_cookie(0),
				message_type1(0),
				message_type2(0),
				client_id1(0),
				client_id2(0),
				client_mac{ 0 },
				dummy{ 0 } { }
		};


		struct dhcp_data {
			uint8_t		opecode;
			uint8_t		hard_addr;
			uint8_t		hard_addr_len;
			uint8_t		hop_count;
			uint32_t	transaction_id;
			uint16_t	second;
			uint16_t	dummy;
			uint8_t		client_ip[4];
			uint8_t		user_ip[4];
			uint8_t		server_ip[4];
			uint8_t		gateway_ip[4];
			uint8_t		client_hard_addr[16];
			uint8_t		server_host_name[64];
			uint8_t		file_name[128];
			dv_options	options;

			dhcp_data() :
				opecode(0),
				hard_addr(0),
				hard_addr_len(0),
				hop_count(0),
				transaction_id(0),
				second(0),
				dummy(0),
				client_ip{ 0 },
				user_ip{ 0 },
				server_ip{ 0 },
				gateway_ip{ 0 },
				client_hard_addr{ 0 },
				server_host_name{ 0 },
				file_name{ 0 },
				options() { }
		};


		struct udp_packet {
			uint16_t	source_port;
			uint16_t	destination_port;
			uint16_t	length;
			uint16_t	checksum;

			udp_packet() : source_port(0), destination_port(0), length(0), checksum(0) { }
		};


		struct ipv4_packet {
			uint8_t		version_and_length;
			uint8_t		differentiated_services_field;
			uint16_t	total_length;
			uint16_t	identification;
			uint16_t	flags_and_fragment_offset;
			uint8_t		time_to_live;
			uint8_t		protocol;
			uint16_t	checksum;
			uint8_t		source_ip[4];
			uint8_t		destination_ip[4];

			ipv4_packet() : version_and_length(0),
				differentiated_services_field(0),
				total_length(0),
				identification(0),
				flags_and_fragment_offset(0),
				time_to_live(0),
				protocol(0),
				checksum(0),
				source_ip{ 0 }, destination_ip{ 0 } { }
		};


		struct ether_packet {
			uint8_t  destination_address[6];
			uint8_t  source_address[6];
			uint16_t packet_type;

			ether_packet() : destination_address{ 0 }, source_address{ 0 }, packet_type(0) { }
		};


		struct dhcp_packet {
			ether_packet	ether;
			ipv4_packet		ipv4;
			udp_packet		udp;
			dhcp_data		dhcp;

			dhcp_packet() : ether(), ipv4(), udp(), dhcp() { } 
		};


		ETHER_IO&	io_;


		static inline uint16_t htons_(uint16_t data)
		{
#ifndef BIG_ENDIAN
			uint16_t tmp = 0;
			tmp  = (data & 0x00ff) << 8;
			tmp |= (data & 0xff00) >> 8;
			return tmp;
#else
			return data;
#endif
		}


		static inline uint32_t htonl_(uint32_t data)
		{
#ifndef BIG_ENDIAN
			uint32_t tmp = 0;
			tmp  = (data & 0x000000ff) << 24;
			tmp |= (data & 0x0000ff00) << 8;
			tmp |= (data & 0x00ff0000) >> 8;
			tmp |= (data & 0xff000000) >> 24;
			return tmp;
#else
    		return data;
#endif
		}


		static uint16_t checksum_(const void* ptr, int32_t len)
		{
			const uint16_t* data = static_cast<const uint16_t*>(ptr);

			long sum = 0;
			for (; len > 1; len -= 2) {
				sum += *data++;
				if(sum & 0x80000000) {
					sum = (sum & 0xffff) + (sum >> 16);
				}
			}

			if(len == 1) {
				const void* tmp = data;
				const uint8_t* p = static_cast<const uint8_t*>(tmp);
				sum += *p;
			}

			while(sum >> 16) {
				sum = (sum & 0xffff) + (sum >> 16);
			}

			return ~sum;
		}


		static uint16_t checksum_udp_(const void* pre, const void* d, int32_t len)
		{
			const uint16_t* pre_header = static_cast<const uint16_t*>(pre);
			const uint16_t* data = static_cast<const uint16_t*>(d);

			long sum = 0;
			for(int cnt = 0; cnt < 6; ++cnt) {
				sum += *pre_header++;
				if(sum & 0x80000000) {
					sum = (sum & 0xffff) + (sum >> 16);
				}    
			}

			for(; len > 1; len -= 2) {
				sum += *data++;
				if(sum & 0x80000000) {
					sum = (sum & 0xffff) + (sum >> 16);
				}
			}

			if(len == 1) {
				const void* tmp = data;
				const uint8_t* p = static_cast<const uint8_t*>(tmp);
				sum += *p;
			}

			while(sum >> 16) {
				sum = (sum & 0xffff) + (sum >> 16);
			}
			return ~sum;
		}


		bool discover_(dhcp_t& dhcp, dhcp_packet& packet)
		{
			const uint8_t broadcast[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
			const uint8_t blank_ip[] = { 0, 0, 0, 0 };

			memcpy(packet.ether.destination_address, broadcast, 6);
			memcpy(packet.ether.source_address, dhcp.macaddr, 6);
			packet.ether.packet_type = htons_(0x0800);

			packet.ipv4.version_and_length            = 0x45;
			packet.ipv4.differentiated_services_field = 0x00;
			packet.ipv4.total_length                  = htons_(0x0148);
			packet.ipv4.identification                = htons_(0x1234);
			packet.ipv4.flags_and_fragment_offset     = htons_(0x0000);
			packet.ipv4.time_to_live                  = 0x80;
			packet.ipv4.protocol                      = 0x11;
			packet.ipv4.checksum                      = htons_(0x0000);
			memcpy(packet.ipv4.source_ip, blank_ip, 4);
			memcpy(packet.ipv4.destination_ip, broadcast, 4);

			packet.udp.source_port                    = htons_(68);
			packet.udp.destination_port               = htons_(67);
			packet.udp.length                         = htons_(0x0134);
			packet.udp.checksum                       = htons_(0x0000);

			packet.dhcp.opecode                       = 0x01;
			packet.dhcp.hard_addr                     = 0x01;
			packet.dhcp.hard_addr_len                 = 0x06;
			packet.dhcp.hop_count                     = 0x00;
			packet.dhcp.transaction_id                = htonl_(TRANSACTION_ID);
			packet.dhcp.second                        = htons_(0x0000);
			packet.dhcp.dummy                         = htons_(0x0000);
			memcpy(packet.dhcp.client_hard_addr, dhcp.macaddr, 6);

			packet.dhcp.options.magic_cookie          = htonl_(0x63825363);
			packet.dhcp.options.message_type1         = htons_(0x3501);
			packet.dhcp.options.message_type2         = 0x01;
			packet.dhcp.options.client_id1            = htons_(0x3d07);
			packet.dhcp.options.client_id2            = 0x01;
			memcpy(packet.dhcp.options.client_mac, dhcp.macaddr, 6);
			packet.dhcp.options.dummy[0]              = 0xff;

			packet.ipv4.checksum                      = checksum_(&packet.ipv4, sizeof(packet.ipv4));

			uint8_t tmp_header[12];
			memcpy(tmp_header, packet.ipv4.source_ip, 4);
			memcpy(tmp_header + 4, packet.ipv4.destination_ip, 4);
			tmp_header[8] = 0x00;
			tmp_header[9] = packet.ipv4.protocol;
			memcpy(&tmp_header[10], &packet.udp.length, 2);

			packet.udp.checksum                       = checksum_udp_(tmp_header, &packet.udp,
				sizeof(packet.udp) + sizeof(packet.dhcp));

			io_.write(&packet.ether, sizeof(packet.ether),
					  &packet.ipv4, sizeof(dhcp_packet) - sizeof(packet.ether));
			return true;
		}


		bool wait_offer_(dhcp_t& dhcp, dhcp_packet& packet)
		{
			reset_timer();
			memset(&packet, 0, sizeof(packet));

			while(1) {
				auto timer = get_timer();
				if(timer > TIMEOUT) {
					return false;
				}

				void* ptr;
				auto len = io_.read(&ptr);
				if(len > 0) {
					memcpy(&packet, ptr,
						sizeof(packet.ether) + sizeof(packet.ipv4)
						+ sizeof(packet.udp) + sizeof(packet.dhcp));

					io_.read_buf_release();
            		if((packet.udp.source_port == htons_(0x0043)) &&
						(packet.udp.destination_port == htons_(0x0044)) &&
						(packet.dhcp.transaction_id == htonl_(TRANSACTION_ID)) &&
						(packet.dhcp.options.message_type1 == htons_(0x3501)) &&
						(packet.dhcp.options.message_type2 == 0x02)) {
						break;
					}
				}
			}
			memcpy(dhcp.ipaddr, packet.dhcp.user_ip, 4);
			return true;
		}


		bool request_(dhcp_t& dhcp, dhcp_packet& packet)
		{
			const uint8_t broadcast[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
			const uint8_t blank_ip[] = { 0, 0, 0, 0 };
			const uint8_t request_ip[] = { 0x32, 0x04 };
			uint8_t tmp_header[12];

			memset(&packet, 0, sizeof(dhcp_packet));

			memcpy(packet.ether.destination_address, broadcast, 6);
			memcpy(packet.ether.source_address, dhcp.macaddr, 6);
			packet.ether.packet_type = htons_(0x0800);

			packet.ipv4.version_and_length            = 0x45;
			packet.ipv4.differentiated_services_field = 0x00;
			packet.ipv4.total_length                  = htons_(0x0148);
			packet.ipv4.identification                = htons_(0x1234);
			packet.ipv4.flags_and_fragment_offset     = htons_(0x0000);
			packet.ipv4.time_to_live                  = 0x80;
			packet.ipv4.protocol                      = 0x11;
			packet.ipv4.checksum                      = htons_(0x0000);
			memcpy(packet.ipv4.source_ip, blank_ip, 4);
			memcpy(packet.ipv4.destination_ip, broadcast, 4);

			packet.udp.source_port                    = htons_(68);
			packet.udp.destination_port               = htons_(67);
			packet.udp.length                         = htons_(0x0134);
			packet.udp.checksum                       = htons_(0x0000);

			packet.dhcp.opecode                       = 0x01;
			packet.dhcp.hard_addr                     = 0x01;
			packet.dhcp.hard_addr_len                 = 0x06;
			packet.dhcp.hop_count                     = 0x00;
			packet.dhcp.transaction_id                = htonl_(TRANSACTION_ID);
			packet.dhcp.second                        = htons_(0x0000);
			packet.dhcp.dummy                         = htons_(0x0000);
			memcpy(packet.dhcp.client_hard_addr, dhcp.macaddr, 6);

			packet.dhcp.options.magic_cookie          = htonl_(0x63825363);
			packet.dhcp.options.message_type1         = htons_(0x3501);
			packet.dhcp.options.message_type2         = 0x03;
			*(&packet.dhcp.options.message_type2 + 1) = 0x00;
			packet.dhcp.options.client_id1            = htons_(0x3d07);
			packet.dhcp.options.client_id2            = 0x01;
			memcpy(packet.dhcp.options.client_mac, dhcp.macaddr, 6);
			memset(packet.dhcp.options.dummy, 0, sizeof(packet.dhcp.options.dummy));
			memcpy(packet.dhcp.options.dummy, request_ip, 2);
			memcpy(&packet.dhcp.options.dummy[2], dhcp.ipaddr, 4);
			packet.dhcp.options.dummy[6]              = 0xff;

			packet.ipv4.checksum                      = checksum_(&packet.ipv4, sizeof(packet.ipv4));

			memcpy(tmp_header, packet.ipv4.source_ip, 4);
			memcpy(tmp_header + 4, packet.ipv4.destination_ip, 4);
			tmp_header[8] = 0x00;
			tmp_header[9] = packet.ipv4.protocol;
			memcpy(&tmp_header[10], &packet.udp.length, 2);

			packet.udp.checksum                       = checksum_udp_(tmp_header, &packet.udp,
				sizeof(packet.udp) + sizeof(packet.dhcp));

			io_.write(&packet.ether, sizeof(packet.ether), &packet.ipv4,
				sizeof(dhcp_packet) - sizeof(packet.ether));
			return true;
		}


		bool wait_ack_(dhcp_t& dhcp, dhcp_packet& packet)
		{
			uint8_t none[5] = { "none" };

			reset_timer();
			while(1) {
				auto timer = get_timer();
				if(timer > TIMEOUT) {
					return false;
				}
				void* ptr;
				auto len = io_.read(&ptr);
				if(len > 0) {
					memcpy(&packet, ptr, sizeof(packet.ether) + sizeof(packet.ipv4)
						+ sizeof(packet.udp) + sizeof(packet.dhcp));
					io_.read_buf_release();
					if((packet.udp.source_port == htons_(0x0043))
						&& (packet.udp.destination_port == htons_(0x0044))
						&& (packet.dhcp.transaction_id == htonl_(TRANSACTION_ID))
						&& (packet.dhcp.options.message_type1 == htons_(0x3501))
						&& (packet.dhcp.options.message_type2 == 0x05)) {
                		break;
					}
				}
			}

			const void* p = static_cast<const void*>(&packet.dhcp.options.message_type1);
			const uint8_t* option = static_cast<const uint8_t*>(p);
			uint8_t flag = 0;
			while(*option != 0xff) {  // End option
				while(*option == 0) {  // OPTION No.0 : Padding
					option++;
				}

				switch(*option) {
				case 1:    // OPTION No.1 : Subnet Mask
					memcpy(dhcp.maskaddr, option + 2, 4);
					break;

				case 3:    // OPTION No.3 : Router
					memcpy(dhcp.gwaddr, option + 2, 4);
					break;

				case 6:    // OPTION No.6 : Domain Name Server
					// The length must always be a multiple of 4.
					if(*(option + 1) >= 4) {
						memcpy(dhcp.dnsaddr, option + 2, 4);
					}
					if(*(option + 1) >= 8) {
						memcpy(dhcp.dnsaddr2, option + 6, 4);
					}
					break;

				case 15:   // OPTION No.15 : Domain Name
					memcpy(dhcp.domain, option + 2, *(option + 1));
					dhcp.domain[*(option + 1)] = '\0';
					flag |= DOMAIN_GET;
					break;

				case 51:   // OPTION No.51 : IP Address Lease Time
				case 53:   // OPTION No.53 : DHCP Message Type
				case 54:   // OPTION No.54 : Server Identiffer
				case 58:   // OPTION No.58 : Renewal Time Value
				case 59:   // OPTION No.59 : Rebinding Time Value
				default:
					break;
				}
				option += *(option + 1) + 2;
			}

			if(!(flag & DOMAIN_GET)) {
				memcpy(dhcp.domain, none, 5);
			}

			return true;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	io	インサーネット入出力
		*/
		//-----------------------------------------------------------------//
		dhcp_client(ETHER_IO& io) : io_(io) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  DHCP サーバーから、IP アドレスを取得
			@param[out]	dhcp	取得した DHCP 情報
		*/
		//-----------------------------------------------------------------//
		bool start(dhcp_t& dhcp)
		{
			memcpy(dhcp.macaddr, io_.get_mac(), 6);
			dhcp_packet packet;

			if(!discover_(dhcp, packet)) {
				return false;
			}
			if(!wait_offer_(dhcp, packet)) {
				return false;
			}

			if(!request_(dhcp, packet)) {
				return false;
			}
			if(!wait_ack_(dhcp, packet)) {
				return false;
			}
			return true;
		}
	};
}
