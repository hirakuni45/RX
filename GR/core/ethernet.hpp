#pragma once
//=====================================================================//
/*!	@file
	@brief	ethernet class @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include <cstring>

#include "ip_address.hpp"

#include "T4_src/type.h"
#include "T4_src/r_t4_itcpip.h"
#include "T4_src/r_t4_dhcp_client_rx_if.h"
#include "T4_src/r_dhcp_client.h"
#include "T4_src/r_t4_dns_client_rx_if.h"
#include "T4_src/r_dns_client.h"
#include "T4_src/ether.h"
#include "T4_src/ip.h"
#include "T4_src/tcp.h"
#include "T4_src/tcp_api.h"
#include "driver/driver.h"
#include "driver/r_ether.h"
#include "r_byteq_v1.30/r_byteq_if.h"

#include "common/format.hpp"
#include "common/input.hpp"

extern "C" {
	unsigned long millis(void);
	void delay(unsigned long ms);
};


#ifndef DEBUG
// デバッグ以外で出力を無効にする
struct null_chaout {
	null_chaout(char* out = nullptr, uint16_t len = 0) { } 
	void operator() (char ch) {
	}
};

typedef utils::basic_format<null_chaout> debug_format;
#else
typedef utils::basic_format<utils::def_chaout> debug_format;
#endif

/******************************************************************************
Macro definitions
******************************************************************************/
#define T4_CLOSED               0

#define T4_TCPS_CLOSED          0
#define T4_TCPS_ESTABLISHED     2
#define T4_TCPS_CLOSE_WAIT      4

#define DHCP_NOTHING_HAPPEND    0
#define DHCP_RENEW_SUCCESS      2
#define UDP_RCV_BUFFER_SIZE     1024
#define UDP_TX_PACKET_MAX_SIZE  24

extern _TCB   *head_tcb;
extern UB _t4_channel_num;
extern T_TCP_CREP tcp_crep[];
extern T_TCP_CCEP tcp_ccep[];
extern T_UDP_CCEP udp_ccep[];
extern const H __tcprepn;
extern const H __tcpcepn;
extern const H __udpcepn;
extern uint8_t dnsaddr1[];
extern uint8_t dnsaddr2[];
extern TCPUDP_ENV tcpudp_env;
extern volatile UH wait_timer;
extern uint8_t     cepid_max;
extern NAME_TABLE  name_table;
extern DNS_MNG     dns_mng;

#define UDP_RCV_DAT_DATAREAD_MAXIMUM    1472
#define RING_SIZ            (1 << 10)           /* exsample 1024 = 1<<10 */
#define RING_SIZ_forSize    (RING_SIZ >> 2)

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ethernet class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ethernet {

	public:
		static const uint32_t max_connection = 4;
		static const uint32_t TCP_MSS = 1460;

		struct CEP {
			uint32_t    status;
			T_IPV4EP    dst_addr;
			T_IPV4EP    src_addr;
			int32_t     current_recv_data_len;
			int32_t     total_rcv_len;
			uint8_t     recv_buf[TCP_MSS];
			uint8_t     send_buf[TCP_MSS];
			int32_t     sec_counter;
			int32_t     sec_timer;
			int32_t     pre_sec_timer;
			bool		enable;
			bool		call_flag;
			CEP() : enable(false), call_flag(false) { }
		};

		static const uint32_t TCPUDP_WORK = 1780 / sizeof(uint32_t);
		uint32_t	tcpudp_work[TCPUDP_WORK];

	private:
		CEP			cep_[max_connection];

        uint32_t    dhcpIPAddressLeaseTime_sec;
        uint32_t    dhcpIPuse_sec;
        uint32_t    fromSystemGetLastTime;
        bool		dhcp_use_;
///        bool		tcp_acp_cep_call_flg;

		static T_IPV4EP remoteIPV4EP_;
		static char UDPrecvBuf_[UDP_RCV_DAT_DATAREAD_MAXIMUM];
		static uint8_t byteq_buf[RING_SIZ];
		static byteq_hdl_t	hdl_;
		static byteq_hdl_t	hdl_forSize_;
		static uint8_t byteq_buf_forSize_[RING_SIZ_forSize];    /* sizeQueBody 1024 >> 2 = 256 */

        void dhcpSuccess(DHCP *tmpDhcpPt) {
            memcpy(tcpudp_env.ipaddr, tmpDhcpPt->ipaddr, 4);
            debug_format("ip = %08X\n") % get_local_ip();

            memcpy(tcpudp_env.maskaddr, tmpDhcpPt->maskaddr, 4);
#ifdef T4_ETHER_DEBUG
            Serial.print("snm = ");
            Serial.println(subnetMask());
#endif
            memcpy(tcpudp_env.gwaddr, tmpDhcpPt->gwaddr, 4);
#ifdef T4_ETHER_DEBUG
            Serial.print("gw = ");
            Serial.println(gatewayIP());
#endif
            memcpy((char *)dnsaddr1, (char *)tmpDhcpPt->dnsaddr, 4);
#ifdef T4_ETHER_DEBUG
            Serial.print("dns = ");
            Serial.println(dnsServerIP());
#endif
            memcpy(dhcpSvMac.bytes, ((DHCP_PACKET*)tcpudp_work)->ether.source_address, EP_ALEN);
#ifdef T4_ETHER_DEBUG
            Serial.print("dhcpSvmac = ");
            Serial.print(dhcpSvMac.bytes[0],HEX);
            Serial.print(":");
            Serial.print(dhcpSvMac.bytes[1],HEX);
            Serial.print(":");
            Serial.print(dhcpSvMac.bytes[2],HEX);
            Serial.print(":");
            Serial.print(dhcpSvMac.bytes[3],HEX);
            Serial.print(":");
            Serial.print(dhcpSvMac.bytes[4],HEX);
            Serial.print(":");
            Serial.println(dhcpSvMac.bytes[5],HEX);
#endif
            memcpy(dhcpSvIp.bytes, ((DHCP_PACKET*)tcpudp_work)->ipv4.source_ip, IP_ALEN);
#ifdef T4_ETHER_DEBUG
            Serial.print("dhcpSvIP = ");
            Serial.println(dhcpSvIp.dword,HEX);
#endif
            dhcp_use_ = true;

			dhcpIPuse_sec = 0;                 /*dhcp lease time local countup start*/
            fromSystemGetLastTime = millis();
            dhcpIPAddressLeaseTime_sec = tmpDhcpPt->dhcpIPAddressLeaseTime;     /*ip lease limit from dhcpSv*/
#ifdef T4_ETHER_DEBUG
            Serial.print("dhcpIPAddressLeaseTime_sec = ");
            Serial.println(dhcpIPAddressLeaseTime_sec);
#endif
        }

///        void dhcpLeaseTimeCopy(DHCP *);
///		int32_t dhcp_release(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
        

		void startLANController()
		{
            int  ercd;
            ercd = lan_open();
#ifdef T4_ETHER_DEBUG
            Serial.print("lan_open() = ");
            Serial.println(ercd);
#endif
            if (ercd != E_OK){
                while(1);
            }
        }


        void initialize_TCP_IP()
		{
			UW	size;
            int	ercd;

            size = tcpudp_get_ramsize();
#ifdef T4_ETHER_DEBUG
            Serial.print("tcpudp_get_ramsize() = ");
            Serial.println(size);
#endif
            if (size > (sizeof(tcpudp_work))){
                while(1);
            }

            tcpudp_open(tcpudp_work);
#ifdef T4_ETHER_DEBUG
            Serial.print("tcpudp_open() = ");
            Serial.println(ercd);
#endif
        }

	public:

        union _dhcp_sv_ip{
            uint8_t bytes[IP_ALEN];
            uint32_t dword;
        } dhcpSvIp;

        union _dhcp_sv_mac{
                uint8_t bytes[EP_ALEN+2];
                uint64_t lword;
        } dhcpSvMac;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
        ethernet() : dhcpIPAddressLeaseTime_sec(0),
			dhcpIPuse_sec(0),
			fromSystemGetLastTime(0),
			dhcp_use_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  デストラクター
		*/
		//-----------------------------------------------------------------//
        ~ethernet() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  新規コネクションの作成（最大４つ）
			@return コネクションID（１～４）０なら失敗
		*/
		//-----------------------------------------------------------------//
		uint32_t new_connection()
		{
			for(uint32_t i = 0; i < max_connection; ++i) {
				if(!cep_[i].enable) {
					cep_[i].enable = true;
					return i + 1;
				}
			}
			return 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コネクションの終了
			@param[in]	cepid	コネクション ID
		*/
		//-----------------------------------------------------------------//
		void end_connection(uint32_t cepid)
		{
			if(cepid > 0 && cepid <= max_connection) {
				cep_[cepid - 1].call_flag = false;
				cep_[cepid - 1].enable = false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コネクション・リソースへの参照
			@param[in]	cepid	コネクション ID
			@return コネクション・リソース
		*/
		//-----------------------------------------------------------------//
		CEP& at_cep(uint32_t cepid) { return cep_[cepid - 1]; }


		//-----------------------------------------------------------------//
		/*!
			@brief  イーサネット開始
		*/
		//-----------------------------------------------------------------//
		void start()
		{
			byteq_err_t byteq_err;
			/* Open and initialize a byte queue with a size of BUFSIZE bytes. */
			byteq_err = R_BYTEQ_Open(byteq_buf, RING_SIZ, &hdl_);
			if(BYTEQ_SUCCESS != byteq_err) {
				utils::format("start: step 0 halt...");
				while(1) ;
			}
			byteq_err = R_BYTEQ_Open(byteq_buf_forSize_, RING_SIZ_forSize, &hdl_forSize_);
			if(BYTEQ_SUCCESS != byteq_err) {
				utils::format("start: step 1 halt...");
				while(1);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	mac	インサーネット・ＭＡＣアドレス
		*/
		//-----------------------------------------------------------------//
        int begin(const uint8_t* mac) {
			DHCP tmpDhcp;

#ifdef T4_ETHER_DEBUG
			Serial.print("t4:EthernetClass::begin(mac:");
			Serial.print((uchar)mac[0],HEX);
			Serial.print(":");
			Serial.print((uchar)mac[1],HEX);
			Serial.print(":");
			Serial.print((uchar)mac[2],HEX);
			Serial.print(":");
			Serial.print((uchar)mac[3],HEX);
			Serial.print(":");
			Serial.print((uchar)mac[4],HEX);
			Serial.print(":");
			Serial.print((uchar)(mac[5]),HEX);
			Serial.println(")");
#endif
			memcpy(_myethaddr, mac, EP_ALEN);           /*use from the beginning only 6byte*/
			startLANController();
#ifdef ETHER_DEBUG
			utils::format("open_timer()\n");
#endif
			open_timer();
			while(g_ether_TransferEnableFlag != ETHER_FLAG_ON) {
				R_ETHER_LinkProcess();
			}

#ifdef ETHER_DEBUG
			utils::format("r_dhcp_open:\n");
#endif
			if(r_dhcp_open(&tmpDhcp, (uint8_t *)tcpudp_work, mac) == -1) {
#ifdef ETHER_DEBUG
				utils::format("fail...\n");
#endif
				close_timer();
				return 0;	/* 0 on failure */
			} else {
#ifdef T4_ETHER_DEBUG
				Serial.println("dhcpSuccess");
#endif
				dhcpSuccess(&tmpDhcp);
			}
#ifdef ETHER_DEBUG
			utils::format("close_timer()\n");
#endif
			close_timer();
			initialize_TCP_IP();
///			clr_tcp_acp_cep_call_flg();
			return 1;	/* returns an int: 1 on a successful DHCP connection */
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	mac	インサーネット・ＭＡＣアドレス
			@param[in]	local_ip	ローカルＩＰ
		*/
		//-----------------------------------------------------------------//
		void begin(const uint8_t* mac, const ip_address& local_ip)
		{
#ifdef T4_ETHER_DEBUG
			Serial.println("t4:EthernetClass::begin(mac,ip)");
#endif
			ip_address dns_server = local_ip;
			dns_server[3] = 1;
			begin(mac, local_ip, dns_server);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	mac	インサーネット・ＭＡＣアドレス
			@param[in]	local_ip	ローカルＩＰ
			@param[in]	dns_server	ＤＮＳサーバー
		*/
		//-----------------------------------------------------------------//
		void begin(const uint8_t* mac, const ip_address& local_ip, const ip_address& dns_server)
		{
#ifdef T4_ETHER_DEBUG
			Serial.println("t4:EthernetClass::begin(mac,ip,dns)");
#endif
			ip_address gateway = local_ip;
			gateway[3] = 1;
			begin(mac, local_ip, dns_server, gateway);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	mac	インサーネット・ＭＡＣアドレス
			@param[in]	local_ip	ローカルＩＰ
			@param[in]	dns_server	ＤＮＳサーバー
			@param[in]	gateway		ゲートウェイ
		*/
		//-----------------------------------------------------------------//
		void begin(const uint8_t* mac, const ip_address& local_ip, const ip_address& dns_server,
			const ip_address& gateway)
		{
#ifdef T4_ETHER_DEBUG
			Serial.println("t4:EthernetClass::begin(mac,ip,dns,gw)");
#endif
			ip_address subnet(255, 255, 255, 0);
			begin(mac, local_ip, dns_server, gateway, subnet);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	mac	インサーネット・ＭＡＣアドレス
			@param[in]	local_ip	ローカルＩＰ
			@param[in]	dns_server	ＤＮＳサーバー
			@param[in]	gateway		ゲートウェイ
			@param[in]	
		*/
		//-----------------------------------------------------------------//
		void begin(const uint8_t* mac, const ip_address& local_ip, const ip_address& dns_server,
			const ip_address& gateway, const ip_address& subnet)
		{
			memcpy(_myethaddr, mac, EP_ALEN);
			memcpy(tcpudp_env.ipaddr, local_ip.get(), IP_ALEN);
			memcpy(dnsaddr1, dns_server.get(), IP_ALEN);
			memcpy(tcpudp_env.gwaddr, gateway.get(), IP_ALEN);
			memcpy(tcpudp_env.maskaddr, subnet.get(), IP_ALEN);
			dhcp_use_ = false;
			/// clr_tcp_acp_cep_call_flg();
#ifdef T4_ETHER_DEBUG
			Serial.print("t4:EthernetClass::begin(mac:");
			Serial.print((uchar)mac_address[0],HEX);
			Serial.print(":");
			Serial.print((uchar)mac_address[1],HEX);
			Serial.print(":");
			Serial.print((uchar)mac_address[2],HEX);
			Serial.print(":");
			Serial.print((uchar)mac_address[3],HEX);
			Serial.print(":");
			Serial.print((uchar)mac_address[4],HEX);
			Serial.print(":");
			Serial.print((uchar)(mac_address[5]),HEX);
			Serial.print(",ip:");
			Serial.print(localIP());
			Serial.print(",dns:");
			Serial.println(dnsServerIP());
			Serial.print(",gw:");
			Serial.print(gatewayIP());
			Serial.print(",snm:");
			Serial.print(subnetMask());
			Serial.println(")");
#endif
			startLANController();
			initialize_TCP_IP();
#if defined(T4_ETHER_DEBUG)
			Serial.print("R_ETHER_LinkProcess while start");
#endif
			while(g_ether_TransferEnableFlag != ETHER_FLAG_ON) {
				R_ETHER_LinkProcess();
			}
#if defined(T4_ETHER_DEBUG)
			Serial.print("R_ETHER_LinkProcess while finish");
#endif
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  IP アドレスの取得
			@return IP アドレス
		*/
		//-----------------------------------------------------------------//
		static ip_address get_local_ip() {
			ip_address adr;
			adr.set(tcpudp_env.ipaddr);
			return adr;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サブネット・マスクの取得
			@return サブネット・マスク
		*/
		//-----------------------------------------------------------------//
		static ip_address get_subnet_mask() {
			ip_address adr;
			adr.set(tcpudp_env.maskaddr);
			return adr;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ゲートウェイの取得
			@return ゲートウェイ
		*/
		//-----------------------------------------------------------------//
		static ip_address get_gateway_ip() {
			ip_address adr;
			adr.set(tcpudp_env.gwaddr);
			return adr;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  DNS の IP 取得
			@return DNS の IP
		*/
		//-----------------------------------------------------------------//
		static ip_address get_dns_ip() {
			ip_address adr;
			adr.set(dnsaddr1);
			return adr;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（メイン・ループ）
		*/
		//-----------------------------------------------------------------//
        void service()
		{
            R_ETHER_LinkProcess();

            if(dhcp_use_) {
                uint32_t    sec,ms;
                ms = millis();
                sec = (ms - fromSystemGetLastTime) / 1000;
                if(sec){
                    fromSystemGetLastTime = ms;
                    dhcpIPuse_sec += sec;
                }
            }
        }


		static int t4_udp_callback(ID cepid, FN fncd , void *p_parblk)
		{
			union _recvSiz {
				int  dword;          /*typedef int32_t W;typedef W ER*/
				uint8_t bytes[4];
			} recvSiz;

			union _dhcp_sv_ip {
				uint8_t bytes[IP_ALEN];
				uint32_t dword;
			} ip;
			byteq_err_t byteq_err;
			uint16_t count;

///			if(cepid == ARDUINO_UDP_CEP) {
			if(cepid > 0 && cepid <= static_cast<ID>(max_connection)) { 
				switch (fncd){
				/// UDP data received
				case TEV_UDP_RCV_DAT:
					/* queue filled with data by R_BYTEQ_Put()elsewhere */
					byteq_err = R_BYTEQ_Unused(hdl_forSize_, &count);
					if(count < 2) {  /*can not record any more DATA SIZE QUE*/
#if defined(T4_ETHER_DEBUG)
						Serial.print("<T4:t4_udp_callback:dataSizeQue:can not record any more DATA SIZE QUE>");
#endif
						break;
					}
					recvSiz.dword = udp_rcv_dat(cepid,
						&remoteIPV4EP_, /*IP address and port number acquisition of opponent*/
						UDPrecvBuf_,    /*Start address of the area for storing the received data*/
						UDP_RCV_DAT_DATAREAD_MAXIMUM,       /*work size*/
						TMO_POL);                           /*polling*/
						/* queue filled with data by R_BYTEQ_Put()elsewhere */
					byteq_err = R_BYTEQ_Unused(hdl_, &count);
					if(count < recvSiz.dword) {  /*can not record any more UDP PACKET SIZE QUE*/
#if defined(T4_ETHER_DEBUG)
						Serial.print("<t4_udp_callback:UDP PACKET Que:can not record any more UDP PACKET SIZE QUE>");
#endif
						break;
					}
					if(recvSiz.dword > 0) {
						byteq_err = R_BYTEQ_Put(hdl_forSize_, recvSiz.bytes[1]);     /*udp packet size upper*/
						if(BYTEQ_SUCCESS != byteq_err) {
                        	printf("<size memory Que ERROR>");
							break;
						}
						byteq_err = R_BYTEQ_Put(hdl_forSize_, recvSiz.bytes[0]);     /*udp packet size lower*/
						if(BYTEQ_SUCCESS != byteq_err) {
							printf("<size memory Que ERROR>");
							break;
						}
						/* Put characters in to the queue. */
						for(int i = 0; i < recvSiz.dword; i++) {
							byteq_err = R_BYTEQ_Put(hdl_, UDPrecvBuf_[i]);
							if(BYTEQ_SUCCESS != byteq_err) {
								printf("<t4:enQueue ERROR>");
								break;
							}
						}
						ip.dword = remoteIPV4EP_.ipaddr;
						remoteIPV4EP_.ipaddr = ((uint32_t)ip.bytes[0] << 24)
								| ((uint32_t)ip.bytes[1]<<16)
								| ((uint32_t)ip.bytes[2]<<8)
								| ((uint32_t)ip.bytes[3]);
					}
					break;
				default:
					break;
        		}
    		}
	    	return 0;
		}
	};
}
