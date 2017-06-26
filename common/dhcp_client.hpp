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
#include "common/net_tools.hpp"

#if defined(BIG_ENDIAN)
#elif defined(LITTLE_ENDIAN)
#else
#error "dhcp_client.hpp requires BIG_ENDIAN or LITTLE_ENDIAN be defined."
#endif

// #define DHCP_DEBUG

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DHCP_INFO 情報 クラス 
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct DHCP_INFO {

		enum class state_t : uint8_t {
			idle,		///< アイドル
			run,		///< 動作中
			collect,	///< 完了（有効な情報）
			timeout,	///< タイムアウト
			error,		///< エラー
		};

		uint8_t	ipaddr[4];
		uint8_t	maskaddr[4];
		uint8_t	gwaddr[4];
		uint8_t	dnsaddr[4];
		uint8_t	dnsaddr2[4];
		char	domain[20];
		uint8_t	macaddr[6];

		uint32_t	lease_time;
		uint32_t	renewal_time;
		uint32_t	rebinding_time;

		state_t		state;

		DHCP_INFO() :
			ipaddr { 0 },
			maskaddr { 0 },
			gwaddr { 0 },
			dnsaddr { 0 },
			dnsaddr2 { 0 },
			domain { 0 },
			macaddr { 0 },
			lease_time(0), renewal_time(0), rebinding_time(0),
			state(state_t::idle)
		{ }

		void list_adr(const char* head, const uint8_t* a) const
		{
			utils::format("%s%d.%d.%d.%d\n") % head
				% static_cast<int>(a[0]) % static_cast<int>(a[1])
				% static_cast<int>(a[2]) % static_cast<int>(a[3]);
		}

		void list() const
		{
			list_adr("IP:   ", ipaddr);
			list_adr("MASK: ", maskaddr);
			list_adr("GW:   ", gwaddr);
			list_adr("DNS:  ", dnsaddr);
			list_adr("DNS2: ", dnsaddr2);
			utils::format("DOMAIN: '%s'\n") % domain;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DHCP Client テンプレート・クラス
		@param[in]	ETHER_IO	インサーネット入出力・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHER_IO>
	class dhcp_client {

#ifndef DHCP_DEBUG
		typedef utils::null_format debug_format;
#else
		typedef utils::format debug_format;
#endif

		static const uint8_t DOMAIN_GET = 0x01;

		static const uint32_t EXPANSION_DHCP_PACKET_SIZE  = 300;
		static const uint32_t TRANSACTION_ID = 0x12345678;


		enum class task : uint8_t {
			none,
			discover,
			wait_offer,
			request,
			wait_ack,
			final,
		};


		struct dv_options {
			uint32_t	magic_cookie;
			uint16_t	message_type1;
			uint8_t		message_type2;
			uint16_t	client_id1;
			uint8_t		client_id2;
			uint8_t		client_mac[6];
			uint8_t		dummy[48 + EXPANSION_DHCP_PACKET_SIZE];
		} __attribute__((__packed__));


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
		} __attribute__((__packed__));


		struct udp_packet {
			uint16_t	source_port;
			uint16_t	destination_port;
			uint16_t	length;
			uint16_t	checksum;
		} __attribute__((__packed__));


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
		} __attribute__((__packed__));


		struct ether_packet {
			uint8_t  destination_address[6];
			uint8_t  source_address[6];
			uint16_t packet_type;
		} __attribute__((__packed__));


		struct dhcp_packet {
			ether_packet	ether;
			ipv4_packet		ipv4;
			udp_packet		udp;
			dhcp_data		dhcp;
		} __attribute__((__packed__));


		ETHER_IO&	io_;
		DHCP_INFO	info_;

		dhcp_packet	packet_;

		uint32_t	timeout_;
		uint32_t	count_;
		task		task_;


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
				const uint8_t* p = reinterpret_cast<const uint8_t*>(data);
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
				const uint8_t* p = reinterpret_cast<const uint8_t*>(data);
				sum += *p;
			}

			while(sum >> 16) {
				sum = (sum & 0xffff) + (sum >> 16);
			}
			return ~sum;
		}


		bool discover_(DHCP_INFO& dhcp, dhcp_packet& packet)
		{
			const uint8_t broadcast[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
			const uint8_t blank_ip[] = { 0, 0, 0, 0 };

			debug_format("DHCP MAC: %02X:%02X:%02X:%02X:%02X:%02X\n")
				% static_cast<uint32_t>(dhcp.macaddr[0])
				% static_cast<uint32_t>(dhcp.macaddr[1])
				% static_cast<uint32_t>(dhcp.macaddr[2])
				% static_cast<uint32_t>(dhcp.macaddr[3])
				% static_cast<uint32_t>(dhcp.macaddr[4])
				% static_cast<uint32_t>(dhcp.macaddr[5]);

			memcpy(packet.ether.destination_address, broadcast, 6);
			memcpy(packet.ether.source_address, dhcp.macaddr, 6);
			packet.ether.packet_type = tools::htons(0x0800);

			packet.ipv4.version_and_length            = 0x45;
			packet.ipv4.differentiated_services_field = 0x00;
			packet.ipv4.total_length                  = tools::htons(0x0148);
			packet.ipv4.identification                = tools::htons(0x1234);
			packet.ipv4.flags_and_fragment_offset     = tools::htons(0x0000);
			packet.ipv4.time_to_live                  = 0x80;
			packet.ipv4.protocol                      = 0x11;
			packet.ipv4.checksum                      = tools::htons(0x0000);
			memcpy(packet.ipv4.source_ip, blank_ip, 4);
			memcpy(packet.ipv4.destination_ip, broadcast, 4);

			packet.udp.source_port                    = tools::htons(68);
			packet.udp.destination_port               = tools::htons(67);
			packet.udp.length                         = tools::htons(0x0134);
			packet.udp.checksum                       = tools::htons(0x0000);

			packet.dhcp.opecode                       = 0x01;
			packet.dhcp.hard_addr                     = 0x01;
			packet.dhcp.hard_addr_len                 = 0x06;
			packet.dhcp.hop_count                     = 0x00;
			packet.dhcp.transaction_id                = tools::htonl(TRANSACTION_ID);
			packet.dhcp.second                        = tools::htons(0x0000);
			packet.dhcp.dummy                         = tools::htons(0x0000);
			memcpy(packet.dhcp.client_hard_addr, dhcp.macaddr, 6);

			packet.dhcp.options.magic_cookie          = tools::htonl(0x63825363);
			packet.dhcp.options.message_type1         = tools::htons(0x3501);
			packet.dhcp.options.message_type2         = 0x01;
			packet.dhcp.options.client_id1            = tools::htons(0x3d07);
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

			// DHCP write: 14, 628 (sum: 29223, udpsum: 5473)
			int head_len = sizeof(packet.ether);
			int body_len = sizeof(dhcp_packet) - sizeof(packet.ether);
			debug_format("DHCP write: %d, %d (sum: %d, udpsum: %d)\n")
				% head_len % body_len % (int)packet.ipv4.checksum % (int)packet.udp.checksum;

			auto wl = io_.write(&packet.ether, head_len, &packet.ipv4, body_len);
			debug_format("DHCP write: %d\n") % wl;

			return true;
		}


		bool wait_offer_(DHCP_INFO& dhcp, dhcp_packet& packet)
		{
			uint32_t all = sizeof(packet.ether) + sizeof(packet.ipv4)
						 + sizeof(packet.udp) + sizeof(packet.dhcp);
			auto len = io_.read(&packet, all);
			if(len > 0) {
				debug_format("DHCP Read: %d (%d)\n") % len % all;
				if(packet.udp.source_port == tools::htons(0x0043)
					&& packet.udp.destination_port == tools::htons(0x0044)
					&& packet.dhcp.transaction_id == tools::htonl(TRANSACTION_ID)
				 	&& packet.dhcp.options.message_type1 == tools::htons(0x3501)
				 	&& packet.dhcp.options.message_type2 == 0x02) {
					memcpy(dhcp.ipaddr, packet.dhcp.user_ip, 4);
					return true;
				}
			}
			return false;
		}


		bool request_(DHCP_INFO& dhcp, dhcp_packet& packet)
		{
			const uint8_t broadcast[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
			const uint8_t blank_ip[] = { 0, 0, 0, 0 };
			const uint8_t request_ip[] = { 0x32, 0x04 };
			uint8_t tmp_header[12];

			memset(&packet, 0, sizeof(dhcp_packet));

			memcpy(packet.ether.destination_address, broadcast, 6);
			memcpy(packet.ether.source_address, dhcp.macaddr, 6);
			packet.ether.packet_type = tools::htons(0x0800);

			packet.ipv4.version_and_length            = 0x45;
			packet.ipv4.differentiated_services_field = 0x00;
			packet.ipv4.total_length                  = tools::htons(0x0148);
			packet.ipv4.identification                = tools::htons(0x1234);
			packet.ipv4.flags_and_fragment_offset     = tools::htons(0x0000);
			packet.ipv4.time_to_live                  = 0x80;
			packet.ipv4.protocol                      = 0x11;
			packet.ipv4.checksum                      = tools::htons(0x0000);
			memcpy(packet.ipv4.source_ip, blank_ip, 4);
			memcpy(packet.ipv4.destination_ip, broadcast, 4);

			packet.udp.source_port                    = tools::htons(68);
			packet.udp.destination_port               = tools::htons(67);
			packet.udp.length                         = tools::htons(0x0134);
			packet.udp.checksum                       = tools::htons(0x0000);

			packet.dhcp.opecode                       = 0x01;
			packet.dhcp.hard_addr                     = 0x01;
			packet.dhcp.hard_addr_len                 = 0x06;
			packet.dhcp.hop_count                     = 0x00;
			packet.dhcp.transaction_id                = tools::htonl(TRANSACTION_ID);
			packet.dhcp.second                        = tools::htons(0x0000);
			packet.dhcp.dummy                         = tools::htons(0x0000);
			memcpy(packet.dhcp.client_hard_addr, dhcp.macaddr, 6);

			packet.dhcp.options.magic_cookie          = tools::htonl(0x63825363);
			packet.dhcp.options.message_type1         = tools::htons(0x3501);
			packet.dhcp.options.message_type2         = 0x03;
			*(&packet.dhcp.options.message_type2 + 1) = 0x00;
			packet.dhcp.options.client_id1            = tools::htons(0x3d07);
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

			int hds = sizeof(packet.ether);
			int bds = sizeof(dhcp_packet) - sizeof(packet.ether);
			uint8_t tmp[hds + bds];
			memcpy(tmp, &packet.ether, hds);
			memcpy(&tmp[hds], &packet.ipv4, bds);
			io_.write(tmp, hds + bds);
//			io_.write(&packet.ether, sizeof(packet.ether), &packet.ipv4,
//				sizeof(dhcp_packet) - sizeof(packet.ether));
			return true;
		}


		bool wait_ack_(DHCP_INFO& dhcp, dhcp_packet& packet)
		{
			int all = sizeof(packet.ether) + sizeof(packet.ipv4)
					+ sizeof(packet.udp) + sizeof(packet.dhcp);
			auto len = io_.read(&packet, all);
			if(len > 0) {
				if((packet.udp.source_port == tools::htons(0x0043))
					&& (packet.udp.destination_port == tools::htons(0x0044))
					&& (packet.dhcp.transaction_id == tools::htonl(TRANSACTION_ID))
					&& (packet.dhcp.options.message_type1 == tools::htons(0x3501))
					&& (packet.dhcp.options.message_type2 == 0x05)) {
					return true;
				}
			}
			return false;
		}


		static void final_(DHCP_INFO& dhcp, dhcp_packet& packet)
		{
			const uint8_t* option = reinterpret_cast<const uint8_t*>(&packet.dhcp.options.message_type1);
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
					{
						const uint32_t* p = reinterpret_cast<const uint32_t*>(option + 2);
				    	dhcp.lease_time = tools::htonl(*p);
					}
					break;
				case 53:   // OPTION No.53 : DHCP Message Type
				case 54:   // OPTION No.54 : Server Identiffer
				case 58:   // OPTION No.58 : Renewal Time Value
					{
						const uint32_t* p = reinterpret_cast<const uint32_t*>(option + 2);
				    	dhcp.renewal_time = tools::htonl(*p);
					}
					break;
				case 59:   // OPTION No.59 : Rebinding Time Value
					{
						const uint32_t* p = reinterpret_cast<const uint32_t*>(option + 2);
				    	dhcp.rebinding_time = tools::htonl(*p);
					}
					break;
				default:
					break;
				}
				option += *(option + 1) + 2;
			}

			if(!(flag & DOMAIN_GET)) {
				strcpy(dhcp.domain, "none");
			}
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	io	インサーネット入出力
		*/
		//-----------------------------------------------------------------//
		dhcp_client(ETHER_IO& io) : io_(io), info_(), timeout_(0), count_(0), task_(task::none) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  DHCP サーバーから、IP アドレスを取得
			@param[in]	timeout	DHCP 取得最大時間（10ms 単位）@n
						※通常２秒
		*/
		//-----------------------------------------------------------------//
		void start(uint32_t timeout = 2 * (1000 / 10))
		{
			memcpy(info_.macaddr, io_.get_mac(), 6);

			memset(&packet_, 0, sizeof(dhcp_packet));

			timeout_ = timeout;
			count_ = 0;
			task_ = task::discover;
			info_.state = DHCP_INFO::state_t::run;
			debug_format("DHCP discover\n");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  DHCP クライアント・サービス @n
					※1/100 秒間隔で呼び出す
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			switch(task_) {
			case task::discover:
				if(discover_(info_, packet_)) {
					memset(&packet_, 0, sizeof(dhcp_packet));
					count_ = 0;
					task_ = task::wait_offer;
					debug_format("DHCP wait_offer\n");
				} else {
					task_ = task::none;
					info_.state = DHCP_INFO::state_t::error;
				}
				break;

			case task::wait_offer:
				if(count_ >= timeout_) {
					task_ = task::none;
					info_.state = DHCP_INFO::state_t::timeout;
					debug_format("DHCP timeout\n");
				}
				++count_;
				if(wait_offer_(info_, packet_)) {
					task_ = task::request;
					debug_format("DHCP request\n");
				}
				break;

			case task::request:
				if(request_(info_, packet_)) {
					task_ = task::wait_ack;
					debug_format("DHCP wait_ack\n");
					count_ = 0;
				} else {
					task_ = task::none;
					info_.state = DHCP_INFO::state_t::error;
				}
				break;

			case task::wait_ack:
				if(count_ >= timeout_) {
					task_ = task::none;
					info_.state = DHCP_INFO::state_t::timeout;
				}
				++count_;

				if(wait_ack_(info_, packet_)) {
					debug_format("DHCP final\n");
					task_ = task::final;
				}
				break;

			case task::final:
				final_(info_, packet_);
				task_ = task::none;
				info_.state = DHCP_INFO::state_t::collect;
				break;

			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  DHCP 情報の取得
			@return DHCP 情報
		*/
		//-----------------------------------------------------------------//
		const DHCP_INFO& get_info() const { return info_; }
	};
}
