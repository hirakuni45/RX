//=====================================================================//
/*! @file
    @brief  GR-KAEDE_net (RX64M) メイン @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/rspi_io.hpp"
#include "common/sdc_io.hpp"
#include "common/fifo.hpp"
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/fixed_string.hpp"

#include "chip/phy_base.hpp"
#include "net/net_core.hpp"

#include "r_t4_itcpip.h"

namespace {

	typedef device::ETHERC0 ETHERC;      // Eternet Controller
	typedef device::EDMAC0 EDMAC;        // Ethernet DMA Controller
	typedef chip::phy_base<ETHERC> PHY;  // Ethernet PHY
	typedef device::ether_io<ETHERC, EDMAC, PHY> ETHER_IO;
	ETHER_IO 	ether_;

	volatile bool tcpip_flag_ = false;

	volatile uint32_t net_int_cnt_ = 0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT タスク
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class cmt_task {

		volatile uint16_t	wait_timer_;
		volatile uint16_t	tcpudp_time_cnt_;

		volatile bool		open_timer_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		cmt_task() : wait_timer_(0), tcpudp_time_cnt_(0),
			open_timer_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  オペレーター ()
		*/
		//-----------------------------------------------------------------//
		void operator() () {
			if(open_timer_) {
				if(tcpip_flag_) {
					_process_tcpip();
					tcpudp_time_cnt_++;
				}

				// for wait function
				if(wait_timer_ < 0xFFFF) {
					wait_timer_++;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマーを有効、又は無効にする
			@param[in]	f	「false」なら無効
		*/
		//-----------------------------------------------------------------//
		void enable_timer(bool f = true) { open_timer_ = f; }


		//-----------------------------------------------------------------//
		/*!
			@brief  tcpudp のタイムカウントを取得
			@param[in]	tcpudp のタイムカウント
		*/
		//-----------------------------------------------------------------//
		uint16_t get_tcpudp_time() const { return tcpudp_time_cnt_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  カウントの設定
			@param[in]	v	カウント値
		*/
		//-----------------------------------------------------------------//
		void set_wait_timer(uint16_t v = 0) { wait_timer_ = v; }


		//-----------------------------------------------------------------//
		/*!
			@brief  カウントの取得
			@return カウント値
		*/
		//-----------------------------------------------------------------//
		uint32_t get_wait_timer() const { return wait_timer_; }
	};


	typedef device::cmt_io<device::CMT0, cmt_task> CMT0;
	CMT0	cmt_;

	typedef utils::fifo<uint8_t, 2048> BUFFER;
	typedef device::sci_io<device::SCI7, BUFFER, BUFFER> SCI;
	SCI		sci_;

	// SDC 用　SPI 定義（RSPI）
	typedef device::rspi_io<device::RSPI> SPI;
	SPI		spi_;

	typedef device::PORT<device::PORTC, device::bitpos::B4> SDC_SELECT;	///< カード選択信号
	typedef device::NULL_PORT  SDC_POWER;	///< カード電源制御（常に電源ＯＮ）
	typedef device::PORT<device::PORTB, device::bitpos::B7> SDC_DETECT;	///< カード検出

	typedef utils::sdc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;
	SDC		sdc_(spi_, 20000000);

	typedef utils::rtc_io RTC;
	RTC		rtc_;

	typedef net::net_core<ETHER_IO> NET_CORE;
	NET_CORE	net_(ether_);
}

extern "C" {

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


	//-----------------------------------------------------------------//
	/*!
		@brief	タイマーカウンターをリセット
	 */
	//-----------------------------------------------------------------//
	void reset_timer(void)
	{
		cmt_.at_task().set_wait_timer(0);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	タイマーカウンターを取得
		@return	タイマーカウント
	 */
	//-----------------------------------------------------------------//
	uint16_t get_timer(void)
	{
		return cmt_.at_task().get_wait_timer();
	}


	uint16_t get_tcpudp_time(void)
	{
		return cmt_.at_task().get_tcpudp_time();
	}


	/////////////////////////////////////////////////////////////////////
	//
	//  renesas ip-stack interface
	//
	/////////////////////////////////////////////////////////////////////
	void lan_inthdr(void)
	{
///		InterruptsEnable();
		if(tcpip_flag_) {
			_process_tcpip();
			++net_int_cnt_;
		}
	}


	void ena_int(void)
	{
		tcpip_flag_ = true;
utils::format("TCPIP Enable\n");
	}


	void dis_int(void)
	{
		tcpip_flag_ = false;
utils::format("TCPIP Disable\n");
	}


	void tcp_api_slp(int16_t cepid)
	{
		// same as udp_api_slp(). ->
		ether_.enable_interrupt(false);
		// check LAN link stat
		ether_.link_process();
		ether_.enable_interrupt();
		/*<-*/

		// If user uses "Real time OS", user may define "sleep task" here.
	}


	void udp_api_slp(int16_t cepid)
	{
		// R_ETHER_LinkProcess() is used in timer_interrupt(). It isn't necessary here. ->
		ether_.enable_interrupt(false);
		// check LAN link stat
		ether_.link_process();
		ether_.enable_interrupt();
		// If user uses "Real time OS", user may define "sleep task" here.
	}


	void udp_api_wup(int16_t cepid)
	{
	}


	void tcp_api_wup(int16_t cepid)
	{
		// If user uses "Real time OS", user may define "wake up task" here.
	}


	uint16_t tcpudp_get_time(void)
	{
		return cmt_.at_task().get_tcpudp_time();
	}


	void tcpudp_act_cyc(uint8_t cycact)
	{
		switch (cycact) {
		case 0:
			dis_int();
			cmt_.at_task().enable_timer(false);
			break;
		case 1:
			ena_int();
			cmt_.at_task().enable_timer();
			break;
		default:
			break;
		}
	}


	void lan_reset(uint8_t lan_port_no)
	{
		utils::format("EterC: close\n");
		ether_.close();
		// R_ETHER_Control(CONTROL_POWER_OFF, param);
		utils::format("lan_reset\n");
	}


	int16_t lan_read(uint8_t lan_port_no, void **buf)
	{
		auto ret = ether_.recv(buf);
		int16_t rc;
		if(ret > 0) {
			rc = ret;
/// utils::format("lan_read: %d\n") % static_cast<int>(rc);
		} else if(ret == 0) {
			rc = -1;
		} else {
			rc = -2;
		}

//		rc = lan_read_for_test(buf, rc);

		return rc;
	}


	int16_t rcv_buff_release(uint8_t lan_port_no)
	{
		ether_.recv_buff_release();
		return 0;
	}


	int16_t lan_write(uint8_t lan_port_no, const void* hsrc, int16_t hlen, const void* bsrc, int16_t blen)
	{
utils::format("lan_write: %d, %d\n") % static_cast<int>(hlen) % static_cast<int>(blen);
		return ether_.write(hsrc, hlen, bsrc, blen);
	}


	void report_error(uint8_t lan_port_no, int16_t err_code, const void* err_data)
	{
/// utils::format("report_error: %d\n") % err_code;
		device::ether_stat_t::error_type t = device::ether_stat_t::error_type::none;
		switch (err_code) {
		case RE_LEN:
			t = device::ether_stat_t::error_type::LEN;
			break;
		case RE_NETWORK_LAYER:
			t = device::ether_stat_t::error_type::NETWORK_LAYER;
			break;
		case RE_TRANSPORT_LAYER:
			t = device::ether_stat_t::error_type::TRANSPORT_LAYER;
			break;
		case RE_ARP_HEADER1:
			t = device::ether_stat_t::error_type::ARP_HEADER1;
			break;
		case RE_ARP_HEADER2:
			t = device::ether_stat_t::error_type::ARP_HEADER2;
			break;
		case RE_IP_HEADER1:
			t = device::ether_stat_t::error_type::IP_HEADER1;
			break;
		case RE_IP_HEADER2:
			t = device::ether_stat_t::error_type::IP_HEADER2;
			break;
		case RE_IP_HEADER3:
			t = device::ether_stat_t::error_type::IP_HEADER3;
			break;
		case RE_IP_HEADER4:
			t = device::ether_stat_t::error_type::IP_HEADER4;
			break;
		case RE_IP_HEADER5:
			t = device::ether_stat_t::error_type::IP_HEADER5;
			break;
		case RE_IP_HEADER6:
			t = device::ether_stat_t::error_type::IP_HEADER6;
			break;
		case RE_IP_HEADER7:
			t = device::ether_stat_t::error_type::IP_HEADER7;
			break;
		case RE_IP_HEADER8:
			t = device::ether_stat_t::error_type::IP_HEADER8;
			break;
		case RE_IP_HEADER9:
			t = device::ether_stat_t::error_type::IP_HEADER9;
			break;
		case RE_TCP_HEADER1:
			t = device::ether_stat_t::error_type::TCP_HEADER1;
			break;
		case RE_TCP_HEADER2:
			t = device::ether_stat_t::error_type::TCP_HEADER2;
			break;
		case RE_UDP_HEADER1:
			t = device::ether_stat_t::error_type::UDP_HEADER1;
			break;
		case RE_UDP_HEADER2:
			t = device::ether_stat_t::error_type::UDP_HEADER2;
			break;
		case RE_UDP_HEADER3:
			t = device::ether_stat_t::error_type::UDP_HEADER3;
			break;
		case RE_ICMP_HEADER1:
			t = device::ether_stat_t::error_type::ICMP_HEADER1;
			break;
		default:
			break;
		}
		ether_.report_error(t, err_data);
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	// NMI input pull-up
	device::PORT3::PCR.B5 = 1; // P35(NMI) pull-up

	{  // GR-KAEDE の SPI 端子のハードバグ回避
	   // ※PC3 から、PC7 へ １K オームで接続
		device::PORTC::PDR.B3 = 1; // output
		device::PORTC::PODR.B3 = 1;
	}

	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	// Base Clock 12MHz
	// PLLDIV: 1/1, STC: 16 倍(198MHz)
	device::SYSTEM::PLLCR = device::SYSTEM::PLLCR.PLIDIV.b(0) |
							device::SYSTEM::PLLCR.STC.b(0b011111);
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/2 (198/4=48)
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2 (198/2=96)
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/2 (198/4=48)
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2 (198/2=96)
						  | device::SYSTEM::SCKCR.PCKB.b(2)		// 1/4 (198/4=48)
						  | device::SYSTEM::SCKCR.PCKC.b(2)		// 1/4 (198/4=48)
						  | device::SYSTEM::SCKCR.PCKD.b(2);	// 1/4 (198/4=48)
	device::SYSTEM::SCKCR2 = device::SYSTEM::SCKCR2.UCK.b(0b0011) | 1;  // USB Clock: 1/4 (198/4=48)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	{  // タイマー設定、１００Ｈｚ（１０ｍｓ）
		uint8_t int_level = 1;
		cmt_.start(100, int_level);
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}

	utils::format("\nStart GR-KAEDE Ethernet Sample\n");

	// SD カード・クラスの初期化
	sdc_.start();

	{  // Ethernet の開始
		ether_.set_intr_task(lan_inthdr);
		uint8_t intr_level = 4;
		ether_.start(intr_level);

		static uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
		net_.start(mac);
	}

	uint32_t cnt = 0;
	volatile uint32_t nnn = 0;
	while(1) {  // 100Hz (10ms interval)
		cmt_.sync();

		net_.service();

#if 0
		if(nnn != net_int_cnt_) {
			nnn = net_int_cnt_;
			utils::format("Net intr: %u\n") % net_int_cnt_;
		}
#endif

		sdc_.service();

		device::PORTC::PDR.B0 = 1; // output
		device::PORTC::PODR.B0 = (cnt < 10) ? 0 : 1;
		++cnt;
		if(cnt >= 50) cnt = 0;
	}
}
