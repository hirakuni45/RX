#pragma once

#include "IPAddress.h"
#include "T4_src/type.h"
#include "T4_src/r_t4_itcpip.h"
#include "T4_src/r_t4_dhcp_client_rx_if.h"
#include "T4_src/r_dhcp_client.h"
#include "T4_src/r_t4_dns_client_rx_if.h"
#include "T4_src/r_dns_client.h"
#include "T4_src/ether.h"
#include "T4_src/ip.h"
#include "T4_src/tcp.h"
#include "driver/driver.h"
#include "driver/r_ether.h"

extern "C" {
	unsigned long millis(void);
	void delay(unsigned long ms);
};

/******************************************************************************
Macro definitions
******************************************************************************/
#define ARDUINO_TCP_CEP          1
#define ARDUINO_UDP_CEP          1
#define T4_CLOSED               0
#define T4_TCPS_ESTABLISHED     2
#define T4_TCPS_CLOSE_WAIT      4
#define T4_TCPS_CLOSED          0
#define DHCP_NOTHING_HAPPEND    0
#define DHCP_RENEW_SUCCESS      2
#define TCPUDP_WORK                     1780/sizeof(UW)     /*20150520 wed review*/
#define UDP_RCV_DAT_DATAREAD_MAXIMUM    1472
#define UDP_RCV_BUFFER_SIZE             1024
#define TCP_MSS                         1460
#define UDP_TX_PACKET_MAX_SIZE          24                  /*Along with Arduino original code*/

typedef struct _CEP{
    uint32_t    status;
    T_IPV4EP    dst_addr;
    T_IPV4EP    src_addr;
    int32_t     current_rcv_data_len;
    int32_t     total_rcv_len;
    UB          rcv_buf[TCP_MSS];
    UB          snd_buf[TCP_MSS];
    int32_t     _1sec_counter;
    int32_t     _1sec_timer;
    int32_t     pre_1sec_timer;
}CEP;

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
extern UW tcpudp_work[TCPUDP_WORK];
extern TCPUDP_ENV tcpudp_env;
extern volatile UH wait_timer;
extern uint8_t     cepid_max;
extern NAME_TABLE  name_table;
extern DNS_MNG     dns_mng;

void setup_terminal_wait();

class EthernetClass;
class EthernetClient;
extern class EthernetClass Ethernet;

class EthernetClass {
	private:
        uint32_t    dhcpIPAddressLeaseTime_sec;
        uint32_t    dhcpUse;
        bool        tcp_acp_cep_call_flg;

        void dhcpSuccess(DHCP *tmpDhcpPt) {
            memcpy(tcpudp_env.ipaddr, tmpDhcpPt->ipaddr, 4);
#ifdef T4_ETHER_DEBUG
            Serial.print("ip = ");
            Serial.println(localIP());
#endif
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
            dhcpUse = true;
            Ethernet.dhcpIPuse_sec = 0;                 /*dhcp lease time local countup start*/
            Ethernet.fromSystemGetLastTime = millis();
            dhcpIPAddressLeaseTime_sec = tmpDhcpPt->dhcpIPAddressLeaseTime;     /*ip lease limit from dhcpSv*/
#ifdef T4_ETHER_DEBUG
            Serial.print("dhcpIPAddressLeaseTime_sec = ");
            Serial.println(dhcpIPAddressLeaseTime_sec);
#endif
        }
        void dhcpLeaseTimeCopy(DHCP *);
        int32_t dhcp_release(DHCP *dhcp, DHCP_PACKET *dhcp_packet);
        void startLANController(void){
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
        void initialize_TCP_IP(void){
            UW          size;
            int         ercd;

            size = tcpudp_get_ramsize();
#ifdef T4_ETHER_DEBUG
            Serial.print("tcpudp_get_ramsize() = ");
            Serial.println(size);
#endif
            if (size > (sizeof(tcpudp_work))){
                while(1);
            }
            ercd = tcpudp_open(tcpudp_work);
#ifdef T4_ETHER_DEBUG
            Serial.print("tcpudp_open() = ");
            Serial.println(ercd);
#endif
            if (ercd != E_OK){
                while(1);
            }
        }

	public:
        EthernetClass(){
            dhcpIPAddressLeaseTime_sec = 0;
            dhcpUse = false;
            dhcpIPuse_sec = 0;
            fromSystemGetLastTime = 0;
            tcp_acp_cep_call_flg = 0;
		}
        virtual ~EthernetClass(){}
        int  begin(const uint8_t* mac);
		void begin(const uint8_t* mac, const IPAddress& local_ip);
		void begin(const uint8_t* mac, const IPAddress& local_ip, IPAddress dns_server);
		void begin(const uint8_t* mac, const IPAddress& local_ip, IPAddress dns_server, IPAddress gateway);
		void begin(const uint8_t* mac, const IPAddress& local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);
		IPAddress localIP(void);
		IPAddress subnetMask(void);
		IPAddress gatewayIP(void);
		IPAddress dnsServerIP(void);
		int maintain(void);
		void maininit(void);
        void mainloop(void){
            R_ETHER_LinkProcess();
            if(dhcpUse){
                uint32_t    sec,ms;
                ms = millis();
                sec = (ms - Ethernet.fromSystemGetLastTime)/1000;
                if(sec){
                    Ethernet.fromSystemGetLastTime = ms;
                    Ethernet.dhcpIPuse_sec += sec;
                }
            }
        }

        size_t write(uint8_t) {
            return 1;
        }

        size_t write(const uint8_t *buffer, size_t size) {
            return 1;
        }

        uint32_t    dhcpIPuse_sec;
        uint32_t    fromSystemGetLastTime;

	protected:
        union _dhcp_sv_ip{
            uint8_t bytes[IP_ALEN];
            uint32_t dword;
        } dhcpSvIp;

        union _dhcp_sv_mac{
                uint8_t bytes[EP_ALEN+2];
                uint64_t lword;
        } dhcpSvMac;
        void stop(void);
        bool get_tcp_acp_cep_call_flg(){
            return Ethernet.tcp_acp_cep_call_flg;
        }
        void set_tcp_acp_cep_call_flg(){
            Ethernet.tcp_acp_cep_call_flg = true;
        }
        void clr_tcp_acp_cep_call_flg(){
            Ethernet.tcp_acp_cep_call_flg = false;
        }
};

class EthernetServer : public EthernetClass {
	uint16_t port_;
	
	public:
	/******************************************************************************
	Description:
		Create a server that listens for incoming connections on the specified port.
	Syntax:
    	Server(port);
	Parameters:
    	port: the port to listen on (int)
	Returns:
    	None
	******************************************************************************/
	EthernetServer(uint16_t port = 0) : port_(port) { }

	virtual ~EthernetServer(){}

	size_t write() { return 0; };

	size_t write(uint8_t byte);

	size_t write(const void* buffer, size_t size);

	void begin(uint16_t port = 0);

	EthernetClient& available(void);

		size_t print(const char* t = nullptr) {
			if(t == nullptr) return 0;

			size_t  l = strlen(t);
			return write(t, l);
		}

		/* get the length of the string * s return. '\ 0' is not included in length. */
        size_t println(const char* t = nullptr) {
			size_t l = print(t);
			l += print("\r\n");
            return l;
        }

	protected:
        int16_t t4_set_tcp_crep(ID repid, UH portno){
            if (repid == 0 || repid > __tcprepn){
                return -1;
            }
            tcp_crep[repid-1].myaddr.portno = portno;
            return 0;
        }
        int16_t t4_set_tcp_ccep(ID cepid, UB ch, int rbufsz) {
            if (cepid == 0 || cepid > __tcpcepn){
                return -1;
            }
            tcp_ccep[cepid-1].cepatr = ch;
            tcp_ccep[cepid-1].rbufsz = rbufsz;
            return 0;
        }
};

class EthernetClient : public EthernetServer {
    public:
      EthernetClient() { }

      virtual ~EthernetClient(){}

      int read();

      int read(void* buf, size_t size);

      int8_t connected();

      int connect(IPAddress ip, uint16_t port);

      int connect(const char *host, uint16_t port);

      int available();

      void flush();

      void stop();

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

      bool operator == (const EthernetClient& rhs) {
#ifdef T4_ETHER_DEBUG
          Serial.println("t4:EthernetClient:==:true");
#endif
          return true;
      }
      bool operator != (const EthernetClient& rhs) {
#ifdef T4_ETHER_DEBUG
          Serial.print("t4:EthernetClient:!=:");
          Serial.println(!this->operator==(rhs));
#endif
          return !this->operator==(rhs);
      }
};

class EthernetUDP : public EthernetClass {
	uint16_t  port_;
	uint16_t  offset_;
	int       remaining_;

	T_IPV4EP  sendIPV4EP_;
	uint8_t   sendBuf_[UDP_RCV_DAT_DATAREAD_MAXIMUM+1];
	uint8_t   recvBuf_[UDP_RCV_BUFFER_SIZE];

	public:
	EthernetUDP() : port_(0), offset_(0), remaining_(0) {
		sendIPV4EP_.ipaddr = 0;
		sendIPV4EP_.portno = 0;
	}
	virtual ~EthernetUDP() { }

	uint8_t begin(uint16_t);

	/******************************************************************************
	Description:
    	Get the number of bytes (characters) available for reading from the buffer. This is data that's already arrived.
    	This function can only be successfully called after UDP.parsePacket().
    	available() inherits from the Stream utility class.
	Syntax:
    	UDP.available()
	Parameters:
    	None
	Returns:
    	the number of bytes available to read
	******************************************************************************/
	int available() const {
		return remaining_;
	}


	/******************************************************************************
	Description:
	    Disconnect from the server. Release any resource being used during the UDP session.
	Syntax:
	    EthernetUDP.stop()
	Parameters:
	    none
	Returns:
	    none
	******************************************************************************/
	void stop() { }

	int beginPacket(const IPAddress& ip, uint16_t port);
	int endPacket();

	size_t write(uint8_t byte);

	size_t write(const void* buffer, size_t size);

	int parsePacket();
	int available();

	int read();
	int read(void* buffer, size_t len);

	IPAddress remoteIP();
	uint16_t remotePort();
};
