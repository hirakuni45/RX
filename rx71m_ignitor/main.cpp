//=====================================================================//
/*! @file
    @brief  RX71M イグナイター
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/scif_io.hpp"
#include "common/sci_io.hpp"
#include "common/rspi_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/delay.hpp"
#include "common/command.hpp"

#include "common/sdc_io.hpp"

#include "main.hpp"
#include "http.hpp"

#include "ign_cmd.hpp"

namespace {

	typedef device::PORT<device::PORT0, device::bitpos::B2> LED0;
	typedef device::PORT<device::PORT0, device::bitpos::B3> LED1;
	typedef device::PORT<device::PORTC, device::bitpos::B0> LED2;
	typedef device::PORT<device::PORTC, device::bitpos::B1> LED3;

	class cmt_task
	{
		void (*task_10ms_)();

		volatile uint32_t millis10x_;

	public:
		cmt_task() : task_10ms_(nullptr),
			millis10x_(0) { }

		void operator() () {
			if(task_10ms_ != nullptr) (*task_10ms_)();
			++millis10x_;
		}

		void set_task_10ms(void (*task)(void)) {
			task_10ms_ = task;
		}

		volatile unsigned long get_millis() const { return millis10x_ * 10; }
	};

	typedef device::cmt_io<device::CMT0, cmt_task> CMT;
	CMT		cmt_;

	typedef utils::fifo<uint8_t, 128> RX_BUF;
	typedef utils::fifo<uint8_t, 256> TX_BUF;

	// CRM interface (SCIF10, FIRST)
	typedef device::scif_io<device::SCIF10, RX_BUF, TX_BUF> CRM;
//	CRM		crm_(false);
	CRM		sci_;

	// WDM interface (RSPI, SECOND)
	typedef device::PORT<device::PORTA, device::bitpos::B4> WDM_SEL;
	typedef device::rspi_io<device::RSPI, device::port_map::option::SECOND> WDM;
	WDM		wdm_;

	// DC2 interface (SCI2, SECOND)
	typedef device::sci_io<device::SCI2, RX_BUF, TX_BUF, device::port_map::option::SECOND> DC2;
	DC2		dc2_(false);

	// DC1 interface (SCI6, FIRST)
	typedef device::sci_io<device::SCI6, RX_BUF, TX_BUF> DC1;
	DC1		dc1_(false);

	// WGM interface (SCI7, FIRST)
	typedef device::sci_io<device::SCI7, RX_BUF, TX_BUF> WGM;
	WGM		wgm_(false);

	// ICM interface (SCI3, FIRST)
	typedef device::sci_io<device::SCI3, RX_BUF, TX_BUF> ICM;
	ICM		icm_(false);

	utils::command<256> cmd_;

	typedef utils::rtc_io RTC;
	RTC		rtc_;

//	SDC_RSPI	sdc_spi_;
//	typedef utils::sdc_io<SDC_RSPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC;
//	SDC		sdc_(sdc_spi_, 20000000);

	net::ethernet   ethernet_;
	HTTP_SERVER     https_(ethernet_);
	TELNETS			telnets_(ethernet_);

	http<HTTP_SERVER>	http_(https_);

	utils::ign_cmd<TELNETS>	ign_cmd_(telnets_);

	// 文字列表示、割り込み対応ロック／アンロック機構
	volatile bool putch_lock_ = false;
	utils::fixed_fifo<char, 1024> putch_tmp_;

	void service_putch_tmp_()
	{
		dis_int();
		while(putch_tmp_.length() > 0) {
			auto ch = putch_tmp_.get();
			sci_.putch(ch);
		}
		ena_int();
	}

	//-----------------------------------------------------------------//
	/*!
		@brief  時間の作成
		@param[in]	date	日付
		@param[in]	time	時間
	*/
	//-----------------------------------------------------------------//
	size_t make_time(const char* date, const char* time)
	{
		time_t t = get_time();
		struct tm *m = localtime(&t);
		int vs[3];
		if((utils::input("%d/%d/%d", date) % vs[0] % vs[1] % vs[2]).status()) {
			if(vs[0] >= 1900 && vs[0] < 2100) m->tm_year = vs[0] - 1900;
			if(vs[1] >= 1 && vs[1] <= 12) m->tm_mon = vs[1] - 1;
			if(vs[2] >= 1 && vs[2] <= 31) m->tm_mday = vs[2];		
		} else {
			return 0;
		}

		if((utils::input("%d:%d:%d", time) % vs[0] % vs[1] % vs[2]).status()) {
			if(vs[0] >= 0 && vs[0] < 24) m->tm_hour = vs[0];
			if(vs[1] >= 0 && vs[1] < 60) m->tm_min = vs[1];
			if(vs[2] >= 0 && vs[2] < 60) m->tm_sec = vs[2];
		} else if((utils::input("%d:%d", time) % vs[0] % vs[1]).status()) {
			if(vs[0] >= 0 && vs[0] < 24) m->tm_hour = vs[0];
			if(vs[1] >= 0 && vs[1] < 60) m->tm_min = vs[1];
			m->tm_sec = 0;
		} else {
			return 0;
		}
		return mktime(m);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の設定
		@param[in]	t	GMT 時間
	*/
	//-----------------------------------------------------------------//
	void set_time(time_t t)
	{
		if(t != 0) {
			rtc_.set_time(t);
		}
	}
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
		if(putch_lock_) {
			if((putch_tmp_.size() - putch_tmp_.length()) >= 2) {
				putch_tmp_.put(ch);
			}
			return;
		}
		putch_lock_ = true;
		sci_.putch(ch);
///		telnets_.putch(ch);
		putch_lock_ = false;
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
//		return sdc_.at_mmc().disk_initialize(drv);
		return RES_OK;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	FatFs へステータスを提供
		@param[in]	drv		Physical drive nmuber (0)
	 */
	//-----------------------------------------------------------------//
	DSTATUS disk_status(BYTE drv) {
//		return sdc_.at_mmc().disk_status(drv);
		return RES_OK;
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
//		return sdc_.at_mmc().disk_read(drv, buff, sector, count);
		return RES_OK;
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
//		return sdc_.at_mmc().disk_write(drv, buff, sector, count);
		return RES_OK;
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
//		return sdc_.at_mmc().disk_ioctl(drv, ctrl, buff);
		return RES_OK;
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
		@param[in]	dsz	文字列出力サイズ
	 */
	//-----------------------------------------------------------------//
	void utf8_to_sjis(const char* src, char* dst, uint16_t dsz) {
		utils::str::utf8_to_sjis(src, dst, dsz);
	}


	unsigned long millis(void)
	{
		return cmt_.at_task().get_millis();
	}


	void set_task_10ms(void (*task)(void)) {
		cmt_.at_task().set_task_10ms(task);
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::system_io<12000000>::setup_system_clock();

	LED0::DIR = 1;
	LED1::DIR = 1;
	LED2::DIR = 1;
	LED3::DIR = 1;

	{  // タイマー設定 (100Hz) 10ms
		uint8_t int_level = 4;
		cmt_.start(100, int_level);
	}

	{  // RTC 開始
		rtc_.start();
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);

//		crm_.start(115200, int_level);
		dc2_.start(115200, int_level);
		dc1_.start(115200, int_level);
		wgm_.start(115200, int_level);
		icm_.start(115200, int_level);
	}

	{  // RSPI (for WDM) 7.5M bps
		wdm_.start(7500000, WDM::PHASE::TYPE1, WDM::DLEN::W8);
		WDM_SEL::DIR = 1;  // select output;
	}
//  RSPI test
#if 0
	while(1) {
		WDM_SEL::P = !WDM_SEL::P();
		wdm_.xchg(0xaa);
	}
#endif
	utils::format("Start RX71M Ignitor\n");
	cmd_.set_prompt("# ");

	// SD カード・クラスの初期化
//	sdc_.start();

	device::power_cfg::turn(device::peripheral::ETHERC0);
	device::port_map::turn(device::peripheral::ETHERC0);

	set_interrupt_task(INT_Excep_ICU_GROUPAL1,
		static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));

	ethernet_.start();
	{
		static const uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
		net::ip_address ipa(192, 168, 0, 20);
		bool dhcp = true;
		if(dhcp) {
			if(ethernet_.begin(mac) == 0) {
				utils::format("Ethernet Fail: begin (DHCP)...\n");
				utils::format("Direct IP: ");
				ethernet_.begin(mac, ipa);
			} else {
				utils::format("Get DHCP: ");
			}
		} else {
			ethernet_.begin(mac, ipa);
			utils::format("Direct IP: ");
		}
		utils::format("%s\n") % ethernet_.get_local_ip().c_str();
	}

	https_.start("Graviton HTTP Server");
	telnets_.start("Graviton TELNET Server");
//	ftps_.start("Graviton FTP Server", "Renesas_RX71M", "GRAVITON", "GRAVITON");

	http_.start();

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		service_putch_tmp_();

		ethernet_.service();

		https_.service(100);
		telnets_.service(100);
//		ftps_.service(100);

		ign_cmd_.service();

//		sdc_.service();

//		if(cmd_.service()) {
//		}

		++cnt;
		if(cnt >= 32) {
			cnt = 0;
		}
		LED0::P = (((cnt + 0)  & 31) < 8) ? 1 : 0;
		LED1::P = (((cnt + 8)  & 31) < 8) ? 1 : 0;
		LED2::P = (((cnt + 16) & 31) < 8) ? 1 : 0;
		LED3::P = (((cnt + 24) & 31) < 8) ? 1 : 0;
	}
}
