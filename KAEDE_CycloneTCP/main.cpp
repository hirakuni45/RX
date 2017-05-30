//=====================================================================//
/*! @file
    @brief  GR-KAEDE (RX64M) メイン @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/cmt_io.hpp"
#include "common/rspi_io.hpp"
#include "common/sci_io.hpp"
#include "common/sdc_io.hpp"

#include "common/fifo.hpp"
#include "common/command.hpp"
#include "common/format.hpp"

#include "net/common/debug.h"
#include "net/cyclone_tcp/core/net.h"
#include "net/RX64M/rx64m_eth.h"
#include "net/drivers/lan8720.h"
#include "net/RX64M/ext_int_driver.h"

#include "dhcp/dhcp_client.h"


#define APP_USE_DHCP ENABLED


namespace {

	void (*nic_task_)(void);

	class cmt_task {

		void (*task_)(void);

	public:
		cmt_task() : task_(nullptr) { }

		void operator() () {
			systemTicks += 10;

//			if(task_ != nullptr) {
//				(*task_)();
//			}
		}

		void set_task(void (*task)()) { task_ = task; }

	};

	typedef device::cmt_io<device::CMT0, cmt_task> CMT0;
	CMT0	cmt_;

	typedef utils::fifo<uint8_t, 2048> BUFFER;
	typedef device::sci_io<device::SCI7, BUFFER, BUFFER> SCI;

	SCI		sci_;

	// SDC 用　SPI 定義（RSPI）
	typedef device::rspi_io<device::RSPI> SPI;
	typedef device::PORT<device::PORTC, device::bitpos::B4> SDC_SELECT;	///< カード選択信号
	typedef device::NULL_PORT  SDC_POWER;	///< カード電源制御（常に電源ＯＮ）
	typedef device::PORT<device::PORTB, device::bitpos::B7> SDC_DETECT;	///< カード検出
	typedef utils::sdc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;

	SPI		spi_;
	SDC		sdc_(spi_, 20000000);


	typedef utils::rtc_io RTC;
	RTC		rtc_;

	void main_init_()
	{

		{  // タイマー設定、１００Ｈｚ（１０ｍｓ）
			uint8_t int_level = 1;
			cmt_.start(100, int_level);
		}

		{  // SCI 設定
			uint8_t int_level = 2;
			sci_.start(115200, int_level);
		}

		// RTC 設定
		rtc_.start();

		{  // GR-KAEDE の SPI 端子のハードバグ回避
		   // ※PC3 から、PC7 へ １K オームで接続
			device::PORTC::PDR.B3  = 1; // output
			device::PORTC::PODR.B3 = 1;
		}

		// SD カード・クラスの初期化
		sdc_.start();
	}


	DhcpClientSettings dhcpClientSettings_;
	DhcpClientContext dhcpClientContext_;

}

extern "C" {

	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の取得
		@return GMT 時間
	*/
	//-----------------------------------------------------------------//
	time_t get_time()
	{
		time_t t = 0;
		rtc_.get_time(t);
		return t;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字出力
		@param[in]	ch	文字
	*/
	//-----------------------------------------------------------------//
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列出力
		@param[in]	s	文字列
	*/
	//-----------------------------------------------------------------//
	void sci_puts(const char* s)
	{
		sci_.puts(s);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字入力
		@return	文字
	*/
	//-----------------------------------------------------------------//
	char sci_getch(void)
	{
		return sci_.getch();
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  システム・文字列長の取得
		@return	文字列長
	*/
	//-----------------------------------------------------------------//
	uint16_t sci_length(void)
	{
		return sci_.recv_length();
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へ初期化関数を提供
		@param[in]	drv		Physical drive nmuber (0)
		@return ステータス
	 */
	//-----------------------------------------------------------------//
	DSTATUS disk_initialize(BYTE drv) {
		return sdc_.at_mmc().disk_initialize(drv);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へステータスを提供
		@param[in]	drv		Physical drive nmuber (0)
	 */
	//-----------------------------------------------------------------//
	DSTATUS disk_status(BYTE drv) {
		return sdc_.at_mmc().disk_status(drv);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へリード・セクターを提供
		@param[in]	drv		Physical drive nmuber (0)
		@param[out]	buff	Pointer to the data buffer to store read data
		@param[in]	sector	Start sector number (LBA)
		@param[in]	count	Sector count (1..128)
		@return リザルト
	 */
	//-----------------------------------------------------------------//
	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdc_.at_mmc().disk_read(drv, buff, sector, count);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へライト・セクターを提供
		@param[in]	drv		Physical drive nmuber (0)
		@param[in]	buff	Pointer to the data to be written	
		@param[in]	sector	Start sector number (LBA)
		@param[in]	count	Sector count (1..128)
		@return リザルト
	 */
	//-----------------------------------------------------------------//
	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdc_.at_mmc().disk_write(drv, buff, sector, count);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へI/O コントロールを提供
		@param[in]	drv		Physical drive nmuber (0)
		@param[in]	ctrl	Control code
		@param[in]	buff	Buffer to send/receive control data
		@return リザルト
	 */
	//-----------------------------------------------------------------//
	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdc_.at_mmc().disk_ioctl(drv, ctrl, buff);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へ時間を提供
		@return FatFs 時間
	 */
	//-----------------------------------------------------------------//
	DWORD get_fattime(void) {
		auto t = get_time();
		return utils::str::get_fattime(t);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	UTF-8 から ShiftJIS への変換
		@param[in]	src	UTF-8 文字列ソース
		@param[out]	dst	ShiftJIS 文字列出力
	 */
	//-----------------------------------------------------------------//
	void utf8_to_sjis(const char* src, char* dst) {
		utils::str::utf8_to_sjis(src, dst);
	}


	void install_timer_task(void (*task)(void))
	{
//		cmt_.at_task().set_task(task);
		nic_task_ = task;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	Ethernet コントローラー０ PHY との制御ライン設定
	 */
	//-----------------------------------------------------------------//
	void rx64mEthInitGpio(NetInterface* interface)
	{
		device::port_map::turn(device::peripheral::ETHERC0);
	}

// extIntHandler
	extern void rx64mEthIrqHandler(void);


	void system_sleep(uint32_t delay)
	{
		utils::delay::milli_second(delay);
	}

	void system_usleep(uint32_t delay)
	{
		utils::delay::micro_second(delay);
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::PORT3::PCR.B5 = 1; // P35(NMI) pull-up

	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);			
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	device::SYSTEM::PLLCR.STC = 0b010011;		// PLL 10 倍(120MHz)
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.BCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKC.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
	device::SYSTEM::SCKCR2.UCK = 0b0100;  // USB Clock: 1/5 (120/5=24)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	main_init_();

	utils::format("\nStart CyclonTCP sample\n");

	set_interrupt_task(rx64mEthIrqHandler, static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));

#if 1
	//TCP/IP stack initialization
	device::power_cfg::turn(device::peripheral::ETHERC0);
	auto error = netInit();
	//Any error to report?
	if(error) {
		//Debug message
		TRACE_ERROR("Failed to initialize TCP/IP stack!\r\n");
	}

	//Configure the first Ethernet interface
	NetInterface* interface = &netInterface[0];

	//Set interface name
	netSetInterfaceName(interface, "eth0");

	//Set host name
	netSetHostname(interface, "GR_KAEDE");
	//Select the relevant network adapter
	netSetDriver(interface, &rx64mEthDriver);
	netSetPhyDriver(interface, &lan8720PhyDriver);
	//Set external interrupt line driver
///	netSetExtIntDriver(interface, &extIntDriver);
	//Set host MAC address
	MacAddr macAddr = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//	macStringToAddr(APP_MAC_ADDR, &macAddr);
	netSetMacAddr(interface, &macAddr);

	//Initialize network interface
	error = netConfigInterface(interface);
	if(error) {  // Any error to report?
		//Debug message
		TRACE_ERROR("Failed to configure interface %s!\r\n", interface->name);
	}

#if (IPV4_SUPPORT == ENABLED)
#if (APP_USE_DHCP == ENABLED)
	// Get default settings
	dhcpClientGetDefaultSettings(&dhcpClientSettings_);
	// Set the network interface to be configured by DHCP
	dhcpClientSettings_.interface = interface;
	// Disable rapid commit option
	dhcpClientSettings_.rapidCommit = FALSE;

	// DHCP client initialization
	error = dhcpClientInit(&dhcpClientContext_, &dhcpClientSettings_);
	if(error) {  // Failed to initialize DHCP client?
		// Debug message
		TRACE_ERROR("Failed to initialize DHCP client!\r\n");
	}

	// Start DHCP client
	error = dhcpClientStart(&dhcpClientContext_);
	// Failed to start DHCP client?
	if(error) {
		// Debug message
		TRACE_ERROR("Failed to start DHCP client!\r\n");
	}
#else
	//Set IPv4 host address
	ipv4StringToAddr(APP_IPV4_HOST_ADDR, &ipv4Addr);
	ipv4SetHostAddr(interface, ipv4Addr);

	//Set subnet mask
	ipv4StringToAddr(APP_IPV4_SUBNET_MASK, &ipv4Addr);
	ipv4SetSubnetMask(interface, ipv4Addr);

	//Set default gateway
	ipv4StringToAddr(APP_IPV4_DEFAULT_GATEWAY, &ipv4Addr);
	ipv4SetDefaultGateway(interface, ipv4Addr);

	//Set primary and secondary DNS servers
	ipv4StringToAddr(APP_IPV4_PRIMARY_DNS, &ipv4Addr);
	ipv4SetDnsServer(interface, 0, ipv4Addr);
	ipv4StringToAddr(APP_IPV4_SECONDARY_DNS, &ipv4Addr);
	ipv4SetDnsServer(interface, 1, ipv4Addr);
#endif
#endif

#endif

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		if(nic_task_ != nullptr) {
			(*nic_task_)();
		}


		sdc_.service();

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}

		{
			device::PORTC::PDR.B0 = 1; // output
			device::PORTC::PODR.B0 = (cnt < 10) ? 0 : 1;
		}
	}
}
