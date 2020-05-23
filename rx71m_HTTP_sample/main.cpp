//=====================================================================//
/*! @file
    @brief  RX71M http サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/cmt_mgr.hpp"
#include "common/sci_io.hpp"
#include "common/rspi_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/delay.hpp"
#include "common/command.hpp"

#include "http.hpp"

namespace {

	static const int MAIN_VERSION = 85;

	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	static const char* system_str_ = { "RX71M" };


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

	typedef device::cmt_mgr<device::CMT0, cmt_task> CMT;
	CMT			cmt_;

	typedef utils::fixed_fifo<char, 1024> RX_SCI;
	typedef utils::fixed_fifo<char, 4096> TX_SCI;

	typedef device::sci_io<device::SCI1, RX_SCI, TX_SCI> SCI;
	SCI			sci_;

	utils::command<256> cmd_;

	typedef utils::rtc_io RTC;
	RTC			rtc_;

	net::ethernet   ethernet_;
	HTTP_SERVER     https_(ethernet_);
//	TELNETS			telnets_(ethernet_, false);

	http<HTTP_SERVER>	http_(https_);


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
}

extern "C" {

	//-----------------------------------------------------------------//
	/*!
		@brief  時間の作成
		@param[in]	date	日付
		@param[in]	time	時間
		@return GMT 時間
	*/
	//-----------------------------------------------------------------//
	size_t make_time(const char* date, const char* time)
	{
		time_t t = get_time();
		struct tm *m = localtime(&t);
		int vs[3];
		if(date == nullptr) {
			m->tm_year = 0;  // 1900
			m->tm_mon = 0;  // Jan
			m->tm_mday = 1; // day of 1
		} else if((utils::input("%d/%d/%d", date) % vs[0] % vs[1] % vs[2]).status()) {
			if(vs[0] >= 1900 && vs[0] < 2100) m->tm_year = vs[0] - 1900;
			if(vs[1] >= 1 && vs[1] <= 12) m->tm_mon = vs[1] - 1;
			if(vs[2] >= 1 && vs[2] <= 31) m->tm_mday = vs[2];		
		} else {
			return 0;
		}

		if(time == nullptr) {
			m->tm_hour = 0;
			m->tm_min = 0;
			m->tm_sec = 0;
		} else if((utils::input("%d:%d:%d", time) % vs[0] % vs[1] % vs[2]).status()) {
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


	unsigned long millis(void)
	{
		return cmt_.at_task().get_millis();
	}


	void set_task_10ms(void (*task)(void)) {
		cmt_.at_task().set_task_10ms(task);
	}


	void vApplicationMallocFailedHook(void)
	{
		/* Called if a call to pvPortMalloc() fails because there is insufficient
		free memory available in the FreeRTOS heap.  pvPortMalloc() is called
		internally by FreeRTOS API functions that create tasks, queues, software
		timers, and semaphores.  The size of the FreeRTOS heap is set by the
		configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
		taskDISABLE_INTERRUPTS();
		for( ;; );
	}


	void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
	{
		( void ) pcTaskName;
		( void ) pxTask;

		/* Run time stack overflow checking is performed if
		configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
		function is called if a stack overflow is detected. */
		taskDISABLE_INTERRUPTS();
		for( ;; );
	}


	void vApplicationIdleHook(void)
	{
///		volatile size_t xFreeHeapSpace;

		/* This is just a trivial example of an idle hook.  It is called on each
		cycle of the idle task.  It must *NOT* attempt to block.  In this case the
		idle task just queries the amount of FreeRTOS heap that remains.  See the
		memory management section on the http://www.FreeRTOS.org web site for memory
		management options.  If there is a lot of heap memory free then the
		configTOTAL_HEAP_SIZE value in FreeRTOSConfig.h can be reduced to free up
		RAM. */
///		xFreeHeapSpace = xPortGetFreeHeapSize();

		/* Remove compiler warning about xFreeHeapSpace being set but never used. */
///		( void ) xFreeHeapSpace;
	}


	void vApplicationTickHook(void)
	{
	}


	void vAssertCalled(void)
	{
		volatile unsigned long ul = 0;

		taskENTER_CRITICAL();
		{
			/* Use the debugger to set ul to a non-zero value in order to step out
			of this function to determine why it was called. */
			while( ul == 0 )
			{
				portNOP();
			}
		}
		taskEXIT_CRITICAL();
	}

	extern void vTickISR(void);
	extern void vSoftwareInterruptISR(void);

	void vApplicationSetupTimerInterrupt(void)
	{
		uint8_t intr = configKERNEL_INTERRUPT_PRIORITY;
		cmt_.start(configTICK_RATE_HZ, intr, vTickISR);

		device::icu_mgr::set_task(device::ICU::VECTOR::SWINT, vSoftwareInterruptISR);
		device::icu_mgr::set_level(device::ICU::VECTOR::SWINT, configKERNEL_INTERRUPT_PRIORITY);
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	LED::DIR = 1;

	{  // タイマー設定 (100Hz) 10ms
		uint8_t int_level = 4;
		cmt_.start(100, int_level);
	}

	{  // RTC 開始
		rtc_.start();
	}

	{  // SCI 設定
		uint8_t intr_level = 2;
		sci_.start(115200, intr_level);
	}

	auto clk = F_ICLK / 1000000;
	utils::format("Start TCP/UDP Net sample for '%s' %d[MHz]\n") % system_str_ % clk;

	cmd_.set_prompt("# ");

	device::power_mgr::turn(device::peripheral::ETHERC0);
	device::port_map::turn(device::peripheral::ETHERC0);

	set_interrupt_task(INT_Excep_ICU_GROUPAL1,
		static_cast<uint32_t>(device::ICU::VECTOR::GROUPAL1));

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

	https_.start("RX HTTP Server");
//	telnets_.start("Graviton TELNET Server");
//	ftps_.start("Graviton FTP Server", "Renesas_RX71M", "GRAVITON", "GRAVITON");

	http_.start();

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		service_putch_tmp_();

		ethernet_.service();

		https_.service(100);

//		telnets_.service(100);
//		ftps_.service(100);

		if(cmd_.service()) {
			auto n = cmd_.get_words();
			if(n == 0) ;
			else if(cmd_.cmp_word(0, "date")) {
				if(n <= 1) {
					auto gt = get_time();
					utils::str::print_date_time(gt);
				} else if(n <= 2) {

				} else {

				}
			} else if(cmd_.cmp_word(0, "help")) {
				utils::format("    date [yyyy/mm/dd]\n");
			} else {
				utils::format("command error: '%s'\n") % cmd_.get_command();
			}
		}

		++cnt;
		if(cnt >= 32) {
			cnt = 0;
		}
		LED::P = (((cnt + 0)  & 31) < 8) ? 1 : 0;
	}
}
