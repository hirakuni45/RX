
#include "T4_src/t4define.h"
#include <string.h>
#include <stdio.h>

#include "r_byteq_v1.30/r_byteq_if.h"
#include "Ethernet.h"

#include "common/format.hpp"

EthernetClass Ethernet;
EthernetClient resClient;
CEP cep[ARDUINO_TCP_CEP];
UW tcpudp_work[TCPUDP_WORK];
static uint8_t _hostIP[IP_ALEN] = {0};                   /* type C-language use(extern "C"). out of Class */
static T_IPV4EP g_remoteIPV4EP;                     /*remort host ip,port*/
static char g_UDPrecvBuf[UDP_RCV_DAT_DATAREAD_MAXIMUM];         /*UDP recv buffer*/

#define RING_SIZ            (1<<10)                 /*exsample 1024 = 1<<10*/
#define RING_SIZ_forSize    (RING_SIZ>>2)
static uint8_t byteq_buf[RING_SIZ]={0};             /*QueBody*/
static byteq_hdl_t hdl,hdl_forSize;
static uint8_t byteq_buf_forSize[RING_SIZ_forSize]={0};    /*sizeQueBody 1024>>2=256*/


/// #define ETHER_DEBUG


/***********************************************************************************************************************
* Function Name: main
* Description  : Provides examples for some of the BYTEQ module API calls.
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void EthernetClass::maininit(void){
    byteq_err_t byteq_err;
    /* Open and initialize a byte queue with a size of BUFSIZE bytes. */
#if defined(T4_ETHER_DEBUG) || defined(T4_UT_TEST) || defined(T4_IT_TEST)
    setup_print();
    setup_terminal_wait();
#endif
    byteq_err = R_BYTEQ_Open(byteq_buf, RING_SIZ, &hdl);                                /*udp data*/
    if (BYTEQ_SUCCESS != byteq_err){
        while(1);
    }
    byteq_err = R_BYTEQ_Open(byteq_buf_forSize, RING_SIZ_forSize, &hdl_forSize);        /*size memory only*/
    if (BYTEQ_SUCCESS != byteq_err){
        while(1);
    }
}

/******************************************************************************
* ID                : 1.0
* Outline           : t4_udp_callback
* Include           : r_t4_itcpip.h
* Declaration       : ER t4_udp_callback(ID cepid, FN fncd , VP p_parblk)
* Function Name     : t4_udp_callback
* Description       : Callback function.
* Argument          : ID        cepid   ;    Communication endpoint ID
*                   : FN        fncd    ;    Event code
*                   : VP        p_parblk;    Parameter block
* Return Value      : ER                ;    always 0 (not in use)
******************************************************************************/
extern "C" ER t4_udp_callback(ID cepid, FN fncd , void *p_parblk){
    union _recvSiz{
            ER  dword;          /*typedef int32_t W;typedef W ER*/
            uint8_t bytes[4];
    } recvSiz;
    union _dhcp_sv_ip{
        uint8_t bytes[IP_ALEN];
        uint32_t dword;
    } ip;
    int     i;
    byteq_err_t byteq_err;
    uint16_t count;

    if(cepid == ARDUINO_UDP_CEP){
        switch (fncd){
            case TEV_UDP_RCV_DAT:   /* UDP data received             */
                /* queue filled with data by R_BYTEQ_Put()elsewhere */
                byteq_err = R_BYTEQ_Unused(hdl_forSize, &count);
                if(count < 2){  /*can not record any more DATA SIZE QUE*/
#if defined(T4_ETHER_DEBUG)
                    Serial.print("<T4:t4_udp_callback:dataSizeQue:can not record any more DATA SIZE QUE>");
#endif
                    break;
                }
                recvSiz.dword = udp_rcv_dat(cepid,
                                    &g_remoteIPV4EP,                    /*IP address and port number acquisition of opponent*/
                                    g_UDPrecvBuf,                       /*Start address of the area for storing the received data*/
                                    UDP_RCV_DAT_DATAREAD_MAXIMUM,       /*work size*/
                                    TMO_POL);                           /*polling*/
                /* queue filled with data by R_BYTEQ_Put()elsewhere */
                byteq_err = R_BYTEQ_Unused(hdl, &count);
                if(count < recvSiz.dword){  /*can not record any more UDP PACKET SIZE QUE*/
#if defined(T4_ETHER_DEBUG)
                    Serial.print("<T4:t4_udp_callback:UDP PACKET Que:can not record any more UDP PACKET SIZE QUE>");
#endif
                    break;
                }
                if(recvSiz.dword > 0){                                  /*reveive success*/
                    byteq_err = R_BYTEQ_Put(hdl_forSize, recvSiz.bytes[1]);     /*udp packet size upper*/
                    if (BYTEQ_SUCCESS != byteq_err){
                        printf("<t4:size memory Que ERROR>");
                        break;
                    }
                    byteq_err = R_BYTEQ_Put(hdl_forSize, recvSiz.bytes[0]);     /*udp packet size lower*/
                    if (BYTEQ_SUCCESS != byteq_err){
                        printf("<t4:size memory Que ERROR>");
                        break;
                    }

                    /* Put characters in to the queue. */
                    for (i=0; i<recvSiz.dword; i++){                    /*ring buffer que_ing*/
                        byteq_err = R_BYTEQ_Put(hdl, g_UDPrecvBuf[i]);
                        if (BYTEQ_SUCCESS != byteq_err){
                            printf("<t4:enQueue ERROR>");
                            break;
                        }
                    }
                    ip.dword = g_remoteIPV4EP.ipaddr;
                    g_remoteIPV4EP.ipaddr = ((uint32_t)ip.bytes[0]<<24)
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
/******************************************************************************
Description:
    DNS resolve use call-back func.
    When it was called back, copy the IP address of the host to the local work
Syntax:
    void dnsCallback(ercd, name_table)
Parameters:
    ercd : error code
    name_table : resolve result
Returns:
    none
******************************************************************************/
extern "C" void dnsResolveCallback(int32_t ercd, NAME_TABLE *name_table){
#ifdef T4_ETHER_DEBUG
    Serial.print("t4:dnsResolveCallback:");
#endif
    if (E_OK == ercd){
        memcpy(_hostIP, name_table->ipaddr, IP_ALEN);
#ifdef T4_ETHER_DEBUG
        Serial.print("E_OK:getIPaddress:");
        Serial.print(_hostIP[0]);
        Serial.print(".");
        Serial.print(_hostIP[1]);
        Serial.print(".");
        Serial.print(_hostIP[2]);
        Serial.print(".");
        Serial.println(_hostIP[3]);
#endif
    }
    else{
#ifdef T4_ETHER_DEBUG
        Serial.println("fail");
#endif
    }
}

/******************************************************************************
Description:
    Initializes the ethernet library and network settings.
    With version 1.0, the library supports DHCP. Using Ethernet.begin(mac) with the proper network setup,
    the Ethernet shield will automatically obtain an IP address. This increases the sketch size significantly.
Syntax:
    Ethernet.begin(mac);
    Ethernet.begin(mac, ip);
    Ethernet.begin(mac, ip, dns);
    Ethernet.begin(mac, ip, dns, gateway);
    Ethernet.begin(mac, ip, dns, gateway, subnet);
Parameters:
    mac: the MAC (Media access control) address for the device (array of 6 bytes). this is the Ethernet hardware address of your shield. Newer Arduino Ethernet Shields include a sticker with the device's MAC address. For older shields, choose your own.
    ip: the IP address of the device (array of 4 bytes)
    dns: the IP address of the DNS server (array of 4 bytes). optional: defaults to the device IP address with the last octet set to 1
    gateway: the IP address of the network gateway (array of 4 bytes). optional: defaults to the device IP address with the last octet set to 1
    subnet: the subnet mask of the network (array of 4 bytes). optional: defaults to 255.255.255.0
Returns:
    The DHCP version of this function, Ethernet.begin(mac), returns an int: 1 on a successful DHCP connection,
    0 on failure. The other versions don't return anything.
******************************************************************************/
int EthernetClass::begin(const uint8_t *mac){
    DHCP        tmpDhcp;

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
#ifdef T4_ETHER_DEBUG
    Serial.println("OpenTimer()");
#endif
    OpenTimer();
    while(g_ether_TransferEnableFlag != ETHER_FLAG_ON){
        R_ETHER_LinkProcess();
    }
#ifdef T4_ETHER_DEBUG
    Serial.print("r_dhcp_open:");
#endif
    if(r_dhcp_open(&tmpDhcp, (uint8_t *)tcpudp_work, mac) == -1){
#ifdef T4_ETHER_DEBUG
    Serial.println("fail");
#endif
        CloseTimer();                           /* 150518 review */
        return 0;                               /* 0 on failure */
    }
    else{
#ifdef T4_ETHER_DEBUG
    Serial.println("dhcpSuccess");
#endif
        dhcpSuccess(&tmpDhcp);
    }
#ifdef T4_ETHER_DEBUG
    Serial.println("CloseTimer()");
#endif
    CloseTimer();
    initialize_TCP_IP();
    clr_tcp_acp_cep_call_flg();                         /* 20150609 tue */
    return 1;                                    /* returns an int: 1 on a successful DHCP connection */
}

void EthernetClass::begin(const uint8_t *mac_address, const IPAddress& local_ip){
#ifdef T4_ETHER_DEBUG
    Serial.println("t4:EthernetClass::begin(mac,ip)");
#endif
    IPAddress dns_server = local_ip;
    dns_server[3] = 1;
    begin(mac_address, local_ip, dns_server);
}

void EthernetClass::begin(const uint8_t *mac_address, const IPAddress& local_ip, IPAddress dns_server){
#ifdef T4_ETHER_DEBUG
    Serial.println("t4:EthernetClass::begin(mac,ip,dns)");
#endif
    IPAddress gateway = local_ip;
    gateway[3] = 1;
    begin(mac_address, local_ip, dns_server, gateway);
}

void EthernetClass::begin(const uint8_t *mac_address, const IPAddress& local_ip, IPAddress dns_server, IPAddress gateway){
#ifdef T4_ETHER_DEBUG
    Serial.println("t4:EthernetClass::begin(mac,ip,dns,gw)");
#endif
    IPAddress subnet(255, 255, 255, 0);
    begin(mac_address, local_ip, dns_server, gateway, subnet);
}

void EthernetClass::begin(const uint8_t *mac_address, const IPAddress& local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet){
    memcpy(_myethaddr, mac_address, EP_ALEN);
    memcpy(tcpudp_env.ipaddr, local_ip._address.bytes, IP_ALEN);
    memcpy(dnsaddr1, dns_server._address.bytes, IP_ALEN);
    memcpy(tcpudp_env.gwaddr, gateway._address.bytes, IP_ALEN);
    memcpy(tcpudp_env.maskaddr, subnet._address.bytes, IP_ALEN);
    dhcpUse = false;
    clr_tcp_acp_cep_call_flg();                         /* 20150609 tue */
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
    while(g_ether_TransferEnableFlag != ETHER_FLAG_ON){
        R_ETHER_LinkProcess();
    }
#if defined(T4_ETHER_DEBUG)
    Serial.print("R_ETHER_LinkProcess while finish");
#endif
}

/******************************************************************************
Description:
    Obtains the IP address of the Ethernet shield. Useful when the address is auto assigned through DHCP.
Syntax:
    Ethernet.localIP();
Parameters:
    none
Returns:
    the IP address
******************************************************************************/
IPAddress EthernetClass::localIP(void){
    return tcpudp_env.ipaddr;
}

/******************************************************************************
Description:
    Obtains the subnetmask address of the Ethernet shield.
Syntax:
    Ethernet.subnetMaskIP();
Parameters:
    none
Returns:
    the subnet IP address
******************************************************************************/
IPAddress EthernetClass::subnetMask(void){
    return tcpudp_env.maskaddr;
}

/******************************************************************************
Description:
    Obtains the gateway address of the Ethernet shield.
Syntax:
    Ethernet.gatewayIP();
Parameters:
    none
Returns:
    the gateway IP address
******************************************************************************/
IPAddress EthernetClass::gatewayIP(void){
    return tcpudp_env.gwaddr;
}

/******************************************************************************
Description:
    Obtains the dnsServer address of the Ethernet shield.
Syntax:
    Ethernet.dnsServerIP();
Parameters:
    none
Returns:
    the dnsServer IP address
******************************************************************************/
IPAddress EthernetClass::dnsServerIP(void){
    return dnsaddr1;
}

/******************************************************************************
Description:
    Allows for the renewal of DHCP leases. When assigned an IP address via DHCP,
    ethernet devices are given a lease on the address for an amount of time.
    With Ethernet.maintain(), it is possible to request a renewal from the DHCP server.
    Depending on the server's configuration, you may receive the same address, a new one, or none at all.
    Ethernet.maintain() was added to Arduino 1.0.1.
Syntax:
    Ethernet.maintain();
Parameters:
    none
Returns:
    byte:
        0: nothing happened
        2: renew success
note:
    DHCP    RFC2131
******************************************************************************/
int EthernetClass::maintain(void){
    int         res = DHCP_NOTHING_HAPPEND;

    if(dhcpUse == true){
        if(dhcpIPuse_sec < dhcpIPAddressLeaseTime_sec){
            return res;
        }
        else{
            stop();
            while(tcpudp_close() != E_OK);
        }
    }
    res = begin((uint8_t*)&_myethaddr);
    if(res == true){
        res = DHCP_RENEW_SUCCESS;
    }
    else{

    }
    return res;
}

/******************************************************************************
Description:
    
Syntax:
    
Parameters:
    
Returns:
    None
******************************************************************************/
void EthernetClass::stop(void){
    if(resClient){
        while(tcp_sht_cep(ARDUINO_TCP_CEP) != E_OK){        /* 20150522 fri */
            delay(1);
        }
    }
    tcp_cls_cep(ARDUINO_TCP_CEP, TMO_FEVR);             /* 20150522 fri */
    clr_tcp_acp_cep_call_flg();                         /* 20150609 tue */
    dhcpUse = false;
#if defined(T4_ETHER_DEBUG)
    Serial.println("EthernetClass::stop():");
    Serial.print("tcp_sht_cep():");
    Serial.print("tcp_cls_cep():");
    Serial.println("clr_tcp_acp_cep_call_flg()");
#endif
}


/******************************************************************************
Description:
    Tells the server to begin listening for incoming connections.
Syntax:
    server.begin()
Parameters:
    None
Returns:
    None
******************************************************************************/
void EthernetServer::begin(uint16_t port)
{
	port_ = port;

#ifdef ETHER_DEBUG
	utils::format("t4:EthernetServer::begin:");
#endif
    if(port_ > 0){
        /* initialize cep status */
        cep[0].status = T4_CLOSED;
        /* Initialize TCP reception point */
#ifdef ETHER_DEBUG
        utils::format("t4_set_tcp_crep():");
#endif
        if(t4_set_tcp_crep(ARDUINO_TCP_CEP, port_) != E_OK) {                    /* 20150522 fri */
			utils::format("t4_set_tcp_crep(): halt...\n");
            while(1);       //error trap
        }
        /* Initialize TCP communication end point */
#ifdef ETHER_DEBUG
        utils::format("t4_set_tcp_ccep():\n");
#endif
        if(t4_set_tcp_ccep(ARDUINO_TCP_CEP, 0, TCP_MSS) != E_OK) {                  /* 20150522 fri */
			utils::format("t4_set_tcp_ccep(): halt...\n");
            while(1);       //error trap
        }
	} else {
#ifdef ETHER_DEBUG
        utils::format("port == 0\n");
#endif
    }
}

/******************************************************************************
Description:
    Gets a client that is connected to the server and has data available for reading.
    The connection persists when the returned client object goes out of scope; you can close it by calling client.stop().
    available() inherits from the Stream utility class.
Syntax:
    server.available()
Parameters:
    None
Returns:
    a Client object; if no Client has data available for reading,
    this object will evaluate to false in an if-statement (see the example below)
******************************************************************************/
EthernetClient& EthernetServer::available() {
    ER  ercd;

    ercd = tcp_read_stat(ARDUINO_TCP_CEP);      /* 20150609 tue */
#if defined(T4_ETHER_DEBUG)
        Serial.print("t4:EthernetServer::available():tcp_read_stat()=");
        Serial.print(ercd);
        Serial.println(":");
        Serial.print("get_tcp_acp_cep_call_flg()=");
        Serial.print(get_tcp_acp_cep_call_flg());
        Serial.println();
#endif
    if(ercd == T4_TCPS_CLOSED && get_tcp_acp_cep_call_flg() == 0){                 /* 20150609 tue */
        ercd = tcp_acp_cep(ARDUINO_TCP_CEP, ARDUINO_TCP_CEP, &cep[0].dst_addr, TMO_NBLK);      /* 20150522 fri 20150609 tue return this position*/
#if defined(T4_ETHER_DEBUG)
        Serial.print("t4:EthernetServer::available():tcp_acp_cep(TMO_NBLK)=");
        Serial.print(ercd);
        Serial.print(":");
        if(ercd == E_WBLK){
            Serial.println("E_WBLK(success)");
        }
        else{
            Serial.print("fail:");
            Serial.println(ercd);
        }
#endif
        set_tcp_acp_cep_call_flg();           /*one time call flag is on*/
    }
    return resClient;               /* EthernetClient::connected() value is returned, it is the same process 20150522*/
}


/******************************************************************************
Description:
    Write data to all the clients connected to a server. This data is sent as a byte or series of bytes.
Syntax:
    server.write(val)
    server.write(buf, len)
Parameters:
    val: a value to send as a single byte (byte or char)
    buf: an array to send as a series of bytes (byte or char)
    len: the length of the buffer
Returns:
    byte
    write() returns the number of bytes written. It is not necessary to read this.
******************************************************************************/
size_t EthernetServer::write(uint8_t b){
    int32_t  ercd;

    ercd = tcp_snd_dat(ARDUINO_TCP_CEP, &b, 1, TMO_FEVR);       /* 20150522 fri */
    return ercd;
}
/*
size_t EthernetServer::write(const uint8_t *buffer, size_t size){
    int32_t  ercd;

    ercd = tcp_snd_dat(ARDUINO_TCP_CEP, (void*)buffer, size, TMO_FEVR);    //20150522 fri
    return ercd;
}
*/
size_t EthernetServer::write(const void* buffer, size_t size)
{
	int32_t ercd;
	size_t current_send_size = 0;

	const uint8_t* p = static_cast<const uint8_t*>(buffer);
	if (size <= 0x7fff) {
		ercd = tcp_snd_dat(ARDUINO_TCP_CEP, (void*)p, size, TMO_FEVR); /* 20150522 fri */
	} else {
		while (size > current_send_size) {
			if ((size - current_send_size) > 0x7fff) {
                ercd = tcp_snd_dat(ARDUINO_TCP_CEP, (void*)(p + current_send_size), 0x7fff,
                        TMO_FEVR);
            }
            else {
                ercd = tcp_snd_dat(ARDUINO_TCP_CEP, (void*) (p + current_send_size),
                        (size - current_send_size), TMO_FEVR);
            }

            if(ercd < 0){
                break; // error
            }

            current_send_size += (size_t)ercd;
        }
    }
    return current_send_size;
}

/******************************************************************************
Description:
    Whether or not the client is connected.
    Note that a client is considered connected if the connection has been closed but there is still unread data.
Syntax:
    client.connected()
Parameters:
    none
Returns:
    Returns true if the client is connected, false if not.
******************************************************************************/
int8_t EthernetClient::connected(void){
    ER  ercd;
    int8_t  res;

    ercd = tcp_read_stat(ARDUINO_TCP_CEP);       /* 20150522 fri */
#if defined(T4_ETHER_DEBUG)
        Serial.print("t4:EthernetClient::connected():tcp_read_stat=");
        Serial.print(ercd);
        Serial.print(":");
#endif
    if(ercd == T4_TCPS_ESTABLISHED || ercd == T4_TCPS_CLOSE_WAIT){   /*2015_0603 wed*/
        res = true;
#if defined(T4_ETHER_DEBUG)
        Serial.println(":return true");
#endif
    }
    else{
        res = false;
#if defined(T4_ETHER_DEBUG)
        Serial.println(":return false");
#endif
    }
    return res;
}

/******************************************************************************
Description:
    Connects to a specified IP address and port.
    The return value indicates success or failure. Also supports DNS lookups when using a domain name.
Syntax:
    client.connect(ip, port)
    client.connect(URL, port)
Parameters:
    ip: the IP address that the client will connect to (array of 4 bytes)
    URL: the domain name the client will connect to (string, ex.:"arduino.cc")
    port: the port that the client will connect to (int)
Returns:
    Returns an int (1,-1,-2,-3,-4) indicating connection status :
    SUCCESS 1
    TIMED_OUT -1
    INVALID_RESPONSE -4
******************************************************************************/
int EthernetClient::connect(IPAddress distip, uint16_t distport){
    ER  ercd;
    T_IPV4EP    distAdr;
    int         res = false;

#ifdef T4_ETHER_DEBUG
        Serial.println("EthernetClient::connect(ip,port):");
#endif
    distAdr.ipaddr = distip._address.bytes[0]<<24 | distip._address.bytes[1]<<16 | distip._address.bytes[2]<<8 | distip._address.bytes[3];
    distAdr.portno = distport;
    if(!connected()){
#ifdef T4_ETHER_DEBUG
        Serial.print("tcp_con_cep(");
        Serial.print(ARDUINO_TCP_CEP);
        Serial.print(",");
        Serial.print("NADR,");
        Serial.print(distAdr.ipaddr,HEX);
        Serial.print(" & ");
        Serial.print(distAdr.portno);
        Serial.print("TMO_FEVR):");
#endif
        ercd = tcp_con_cep(ARDUINO_TCP_CEP, NADR,  &distAdr, 3000);       /* 20150522 fri 20150615 mon*/
        if(ercd == E_OK){
#ifdef T4_ETHER_DEBUG
        Serial.println("E_OK");
#endif
            res = 1;
        }
        else{
#ifdef T4_ETHER_DEBUG
        Serial.println(ercd);
#endif
            res = -1;
        }
    }
    else{
#ifdef T4_ETHER_DEBUG
        Serial.println("already connected. double call");
#endif
        res = 1;    /* already connect */
    }
    return res;
}

int EthernetClient::connect(const char *host, uint16_t port){
    ER  ercd;   /* 20150527 */
    int res = false;

#ifdef T4_ETHER_DEBUG
    Serial.println("t4:EthernetClient::connect(name,port)");
#endif
    udp_ccep[0].callback = (ER(*)(ID, FN, void *))dns_callback;      /* DNS resolve use */
    R_dns_init();
#ifdef T4_ETHER_DEBUG
    Serial.print("R_dns_resolve_name(");
    Serial.print(host);
    Serial.print(",dnsResolveCallback)=");
#endif
    res = R_dns_resolve_name((char *)host, (DNS_CB_FUNC)dnsResolveCallback);
#ifdef T4_ETHER_DEBUG
    Serial.println(res);
#endif
    if(res != E_OK){
        res = false;
    }
    else{
#ifdef T4_ETHER_DEBUG
        Serial.println("host ip initial");
#endif
        _hostIP[0] = 0;      /* ip 0,0,0,0 initial */
        _hostIP[1] = 0;
        _hostIP[2] = 0;
        _hostIP[3] = 0;
        do{                         /* 20150527 review */
            ercd = R_dns_process();
#ifdef T4_ETHER_DEBUG
        Serial.print("R_dns_process = ");
        Serial.print(ercd);
        Serial.print("\t dns_mng.proc = ");
        Serial.print(dns_mng.proc);
        Serial.print(" : ");
        switch(dns_mng.proc){
        case 0:
            Serial.println("DNS_PROC_UNRECEIVED_REQUEST");
            break;
        case 1:
            Serial.println("DNS_PROC_INIT");
            break;
        case 2:
            Serial.println("DNS_PROC_START_SENDING");
            break;
        case 3:
            Serial.println("DNS_PROC_SENDING_REQUEST_WAIT");
            break;
        case 4:
            Serial.println("DNS_PROC_RECEIVEING_REQUEST_WAIT");
            break;
        case 5:
            Serial.println("DNS_PROC_FINISH");
            break;
        case 6:
            Serial.println("DNS_PROC_CANCELLING");
            break;
        case 7:
            Serial.println("DNS_PROC_CANCELLING_WAIT");
            break;
        case 8:
            Serial.println("DNS_PROC_CANCELLED\n");
            break;
        case 9:
            Serial.println("DNS_PROC_NUM");
            break;
        default:
            Serial.println("other");
            break;
        }
#endif
        }while(dns_mng.proc != DNS_PROC_UNRECEIVED_REQUEST);
        if(ercd >= 0){          /* E_OK */
            res = connect(_hostIP, port);
#ifdef T4_ETHER_DEBUG
            Serial.print("connect(");
            Serial.print(_hostIP[0]);
            Serial.print(".");
            Serial.print(_hostIP[1]);
            Serial.print(".");
            Serial.print(_hostIP[2]);
            Serial.print(".");
            Serial.print(_hostIP[3]);
            Serial.print(",");
            Serial.print(" / dns_mng.proc = ");
            Serial.println(dns_mng.proc);
#endif
        }
        else if(ercd == E_DNS_TIMEOUT){
#ifdef T4_ETHER_DEBUG
            Serial.println("timeout");
#endif
            res = -1;
        }
        else{
#ifdef T4_ETHER_DEBUG
            Serial.println("fail");
#endif
            res = -4;
        }
    }
    return res;
}

/******************************************************************************
Description:
    Returns the number of bytes available for reading
    (that is, the amount of data that has been written to the client by the server it is connected to).
    available() inherits from the Stream utility class.
Syntax:
    client.available()
Parameters:
    none
Returns:
    The number of bytes available.
******************************************************************************/
int EthernetClient::available(void){
    int res = 0;
    ER  ercd;

    if(connected() == true){
        res =  head_tcb[0].rdsize;
        ercd = tcp_read_stat(ARDUINO_TCP_CEP);
        if(res == 0 && ercd == T4_TCPS_CLOSE_WAIT){
            tcp_sht_cep(ARDUINO_TCP_CEP);
        }
    }
    return res;
}

/******************************************************************************
Description:
    Read the next byte received from the server the client is connected to (after the last call to read()).
    read() inherits from the Stream utility class.
Syntax:
    client.read()
Parameters:
    none
Returns:
    The next byte (or character), or -1 if none is available.
******************************************************************************/
int EthernetClient::read()
{
    int32_t  ercd;
    int      rcv_data;
#if defined(ETHER_DEBUG)
    utils::format("t4:EthernetClinet::read()");
    utils::format("%u : ") % static_cast<uint32_t>(millis());
#endif
    ercd = tcp_rcv_dat(ARDUINO_TCP_CEP, cep[0].rcv_buf, 1, TMO_FEVR);       /* 20150522 fri */
#if defined(ETHER_DEBUG)
    utils::format("%u\n") % static_cast<uint32_t>(millis());
#endif
    if(ercd <= 0){      /* 20150527 */
        rcv_data= -1;
    }
    else{
        rcv_data = (int)cep[0].rcv_buf[0];
    }
    return rcv_data;
}

int EthernetClient::read(void* buf, size_t size) {
    int32_t  ercd;

    ercd = tcp_rcv_dat(ARDUINO_TCP_CEP, buf, size, TMO_FEVR);
    if(ercd <= 0) {      /* 20150527 */
        ercd = -1;
    } else {
        /* nothing to do */
    }
    return ercd;
}


/******************************************************************************
Descriptions:
    Discard any bytes that have been written to the client but not yet read.
    flush() inherits from the Stream utility class.
Syntax:
    client.flush()
Parameters:
    none
Returns:
    none
******************************************************************************/
void EthernetClient::flush(void)
{
	/* mothing to do 20150527 review */
}


/******************************************************************************
Description:
    Disconnect from the server.
Syntax:
    client.stop()
Parameters:
    none
Returns:
    none
******************************************************************************/
void EthernetClient::stop(void){
#if defined(T4_ETHER_DEBUG)
    Serial.print("t4:EthernetClient::stop():");
#endif
	EthernetClass::stop();
}

/******************************************************************************
Description:
    Initializes the ethernet UDP library and network settings.
Syntax:
    EthernetUDP.begin(localPort);
Parameters:
    localPort: the local port to listen on (int)
Returns:
    1 if successful, 0 if there are no sockets available to use.
******************************************************************************/
uint8_t EthernetUDP::begin(uint16_t port)
{
    uint8_t res;

    if(port){
        udp_ccep[0].myaddr.portno = port;
        udp_ccep[0].callback = (ER(*)(ID, FN, void *))t4_udp_callback;
        res = 1;
    }
    else{
        res = 0;
    }
    return res;
}

/******************************************************************************
Description:
    Reads UDP data from the specified buffer. If no arguments are given, it will return the next character in the buffer.
    This function can only be successfully called after UDP.parsePacket().
Syntax:
    UDP.read();
    UDP.read(packetBuffer, MaxSize);
Parameters:
    packetBuffer: buffer to hold incoming packets (char)
    MaxSize: maximum size of the buffer (int)
Returns:
    char : returns the characters in the buffer
******************************************************************************/
int EthernetUDP::read()
{
  int   res;
  uint8_t byteq_char;
  byteq_err_t byteq_err;

  byteq_err = R_BYTEQ_Get(hdl, &byteq_char);
  if(byteq_err == BYTEQ_SUCCESS){
      res = (int)((uint32_t)byteq_char);
      remaining_ -= 1;
  }
  else{
      res = -1;
#ifdef T4_ETHER_DEBUG
      Serial.print("T4:EthUDP:parsePacket:R_BYTEQ_Get()=");
      Serial.println(byteq_err);
#endif
  }
  return res;
}

int EthernetUDP::read(void* dst, size_t len)
{
    int res = 0;
    uint8_t byteq_char, i;
    byteq_err_t byteq_err;

    /* Get characters from the queue and print to virtual console. */
	uint8_t* buffer = static_cast<uint8_t*>(dst);
    for (i=0; i<len; i++) {
        byteq_err = R_BYTEQ_Get(hdl, &byteq_char);
        if(byteq_err == BYTEQ_SUCCESS){
            *buffer++ = byteq_char;
            res++;
            remaining_ -= 1;
        }
        else {
#ifdef T4_ETHER_DEBUG
            Serial.print("T4:EthUDP:parsePacket:R_BYTEQ_Get()=");
            Serial.println(byteq_err);
#endif
            if(res == 0){
                res = -1;
            }
            break;
        }
    }
    return res;
}

/******************************************************************************
Description:
    Writes UDP data to the remote connection. Must be wrapped between beginPacket() and endPacket().
    beginPacket() initializes the packet of data, it is not sent until endPacket() is called.
Syntax:
    UDP.write(message);
    UDP.write(buffer, size);
Parameters:
    message: the outgoing message (char)
    buffer: an array to send as a series of bytes (byte or char)
    size: the length of the buffer
Returns:
    byte : returns the number of characters sent. This does not have to be read
******************************************************************************/
size_t EthernetUDP::write(uint8_t byte){
  if(offset_ + 1 > UDP_RCV_DAT_DATAREAD_MAXIMUM){
      return 0;
  }
  else{
      sendBuf_[offset_++] = byte;
  }
  return 1;
}

size_t EthernetUDP::write(const void* buffer, size_t size) {
    if(buffer == nullptr || size == 0) {
        return 0;
    }
    if(offset_ + size > UDP_RCV_DAT_DATAREAD_MAXIMUM){
        return 0;
    }
    else {
        memcpy(&sendBuf_[offset_], buffer, size);
        offset_ += size;
    }
    return size;
}

/******************************************************************************
Description:
    Starts a connection to write UDP data to the remote connection
Syntax:
    UDP.beginPacket(remoteIP, remotePort);
Parameters:
    remoteIP: the IP address of the remote connection (4 bytes)
    remotePort: the port of the remote connection (int)
Returns:
    Returns an int: 1 if successful, 0 if there was a problem resolving the hostname or port.
******************************************************************************/
int EthernetUDP::beginPacket(const IPAddress& ip, uint16_t port){
    int res;

    if(!uint32_t(ip) || !port){
        res =  0;
    }
    else{
        sendIPV4EP_.ipaddr = ((int)ip._address.bytes[0]<<24) | ((int)ip._address.bytes[1]<<16) |((int)ip._address.bytes[2]<<8) | ((int)ip._address.bytes[3]);
        sendIPV4EP_.portno = port;
        offset_ = 0;
        res = 1;
    }
    return res;
}

/******************************************************************************
Description:
    Called after writing UDP data to the remote connection.
Syntax:
    UDP.endPacket();
Parameters:
    None
Returns:
    Returns an int: 1 if the packet was sent successfully, 0 if there was an error
******************************************************************************/
int EthernetUDP::endPacket(void){
    ER  ercd;
    int res;

    ercd = udp_snd_dat(ARDUINO_UDP_CEP, &sendIPV4EP_, sendBuf_, offset_, TMO_FEVR);       /* 20150522 fri */
    if(ercd > 0){
        res = 1;
        offset_ = 0;
    }
    else{
        res = 0;
    }
    return res;
}

/******************************************************************************
Description:
    Checks for the presence of a UDP packet, and reports the size.
    parsePacket() must be called before reading the buffer with UDP.read().
Syntax:
    UDP.parsePacket();
Parameters:
    None
Returns:
    int: the size of a received UDP packet
******************************************************************************/
int EthernetUDP::parsePacket(void) {
    byteq_err_t byteq_err;
    union{
            uint16_t    word;
            uint8_t     byte[2];
    }recvSiz;

    while(remaining_) {
        read();             /*drop data until _remaining==0*/
    }

    byteq_err = R_BYTEQ_Get(hdl_forSize, &recvSiz.byte[1]);     /*que size upper read*/
    if(byteq_err != BYTEQ_SUCCESS){
#ifdef T4_ETHER_DEBUG
        Serial.print("T4:EthUDP:parsePacket:R_BYTEQ_Get(que_size_upper)=");
        Serial.println(byteq_err);
#endif
    }
    else{
        byteq_err = R_BYTEQ_Get(hdl_forSize, &recvSiz.byte[0]);     /*que size lower read*/
        if(byteq_err != BYTEQ_SUCCESS){
#ifdef T4_ETHER_DEBUG
            Serial.print("T4:EthUDP:parsePacket:R_BYTEQ_Get(que_size_lower)=");
            Serial.println(byteq_err);
#endif
        }
        else{
               remaining_ = (int)recvSiz.word;
        }
    }
    return remaining_;
}



/******************************************************************************
Description:
    Gets the IP address of the remote connection.
    This function must be called after UDP.parsePacket().
Syntax:
    UDP.remoteIP();
Parameters:
    None
Returns:
    4 bytes : the IP address of the remote connection
******************************************************************************/
IPAddress EthernetUDP::remoteIP() {
    IPAddress ip((uint32_t)g_remoteIPV4EP.ipaddr);
    return ip;
}

/******************************************************************************
Description:
    Gets the port of the remote UDP connection.
    This function must be called after UDP.parsePacket().
Syntax:
    UDP.remotePort();
Parameters:
    None
Returns:
    int : the port of the UDP connection to a remote host
******************************************************************************/
uint16_t EthernetUDP::remotePort()
{
   	return g_remoteIPV4EP.portno;
}

