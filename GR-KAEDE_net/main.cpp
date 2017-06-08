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

#include "chip/phy_base.hpp"

// #include "net/net_core.h"

namespace {

	class cmt_task {
		volatile bool	task_enable_;
	public:
		cmt_task() : task_enable_(false) { }

		void operator() () {
			if(task_enable_) {
///				net_timer_service();
			}
		}

		void task_enable(bool f = true) { task_enable_ = f; }
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


	volatile uint32_t ethc_count_;

	// インサーネット割り込みファンクタ
	class eth_task {
	public:
		void operator() () {
			ethc_count_++;
		}
	};

	typedef device::ETHERC0 ETHERC;  // Eternet Controller
	typedef device::EDMAC0 EDMAC;    // Ethernet DMA Controller
	typedef chip::phy_base<ETHERC> PHY;  // Ethernet PHY
	typedef device::ether_io<ETHERC, EDMAC, PHY, eth_task> ETHERNET;

	ETHERNET ether_;
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


#if 0
	void OpenTimer(void)
	{
		cmt_.at_task().task_enable();
	}

	void CloseTimer(void)
	{
		cmt_.at_task().task_enable(false);
	}
#endif
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

	utils::format("Start GR-KAEDE net\n");

	// SD カード・クラスの初期化
	sdc_.start();

	// Ethernet の開始
	{
		uint8_t intr_level = 4;
		ether_.start(intr_level);
	}

	uint32_t cnt = 0;
	{
		static uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
		if(!ether_.open(mac)) {
			utils::format("Ether open NG !\n");
		} else {
			utils::format("Ether open OK !\n");
		}

		volatile uint32_t n = ethc_count_;
		while(1) {
			cmt_.sync();

			ether_.polling_link_status();
			if(ether_.link_process()) break;

			if(n != ethc_count_) {
				utils::format("Ethernet intr: %d\n") % ethc_count_;
				n = ethc_count_;
			}

			device::PORTC::PDR.B0 = 1; // output
			device::PORTC::PODR.B0 = (cnt < 10) ? 0 : 1;
			++cnt;
			if(cnt >= 50) cnt = 0;
		}
		utils::format("Ether Link UP OK\n");
	}

#if 0
	device::power_cfg::turn(device::peripheral::ETHERC0);
	device::port_map::turn(device::peripheral::ETHERC0);
	set_interrupt_task(net_entry_intr, static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));

	auto ret = net_init();
	utils::format("Net init: %d\n") % ret;
#endif

	while(1) {  // 100Hz (10ms interval)
		cmt_.sync();

///		net_service();

		ether_.polling_link_status();
		ether_.link_process();

		sdc_.service();

		device::PORTC::PDR.B0 = 1; // output
		device::PORTC::PODR.B0 = (cnt < 10) ? 0 : 1;
		++cnt;
		if(cnt >= 50) cnt = 0;
	}
}
