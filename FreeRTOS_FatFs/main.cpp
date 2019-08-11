//=====================================================================//
/*! @file
    @brief  FreeRTOS FatFs サンプル @n
			RX64M, RX71M, RX72M: @n
					12MHz のベースクロックを使用する @n
			　　　　P07 ピンにLEDを接続する @n
			RX65N (Renesas Envision kit RX65N): @n
					12MHz のベースクロックを使用する @n
			　　　　P70 に接続された LED を利用する @n
			RX63T @n
					12MHz のベースクロックを使用する @n
					PB7 に接続された LED を利用する @n
			RX24T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する @n
			RX66T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_io.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/string_utils.hpp"
#include "common/spi_io2.hpp"
#include "common/rspi_io.hpp"
#include "ff13c/mmc_io.hpp"
#include "common/sdc_man.hpp"
#include "common/command.hpp"
#include "common/file_io.hpp"

#include "FreeRTOS.h"
#include "task.h"

#ifdef SIG_RX64M
// RX64Mで、GR-KAEDE の場合有効にする
// #define GR_KAEDE
#endif

namespace {

/// ベースクリスタルの定義
/// LED 接続ポートの定義
#if defined(SIG_RX71M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX71M" };

#elif defined(SIG_RX72M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX72M" };

#elif defined(SIG_RX64M)
	typedef device::system_io<12000000> SYSTEM_IO;

	typedef utils::rtc_io RTC;

#ifdef GR_KAEDE
	typedef device::PORT<device::PORTC, device::bitpos::B0> LED;
	typedef device::PORT<device::PORTC, device::bitpos::B1> LED2;
	typedef device::SCI7 SCI_CH;

#if 0
	// Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORTC, device::bitpos::B7> MISO;
	typedef device::PORT<device::PORTC, device::bitpos::B6> MOSI;
	typedef device::PORT<device::PORTC, device::bitpos::B5> SPCK;
	typedef device::spi_io2<MISO, MOSI, SPCK> SDC_SPI;
#else
	///< Hard SPI 定義
	typedef device::rspi_io<device::RSPI> SDC_SPI;
#endif

	///< SDC インターフェースの定義
	typedef device::PORT<device::PORTC, device::bitpos::B4> SDC_SELECT;	///< SD カード選択信号
	typedef device::NULL_PORT  SDC_POWER;	///< SD カード電源制御（制御なし、常にＯＮ）
	typedef device::PORT<device::PORTB, device::bitpos::B7> SDC_DETECT;	///< SD カード検出

	static const char* system_str_ = { "GR-KAEDE" };
#else
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;

	///< Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORTC, device::bitpos::B3> MISO;
	typedef device::PORT<device::PORT7, device::bitpos::B6> MOSI;
	typedef device::PORT<device::PORT7, device::bitpos::B7> SPCK;
	typedef device::spi_io2<MISO, MOSI, SPCK> SDC_SPI;

	typedef device::PORT<device::PORT8, device::bitpos::B2> SDC_POWER;	///< カード電源制御
	typedef device::PORT<device::PORTC, device::bitpos::B2> SDC_SELECT;  ///< カード選択信号
	typedef device::PORT<device::PORT8, device::bitpos::B1> SDC_DETECT;  ///< カード検出

	static const char* system_str_ = { "RX64M" };
#endif

#elif defined(SIG_RX65N)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;
	static const char* system_str_ = { "RX65N" };

#elif defined(SIG_RX63T)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORTB, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX63T" };

#elif defined(SIG_RX24T)
	typedef device::system_io<10000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;

#ifdef SOFT_SPI
	// Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORT2, device::bitpos::B2> MISO;
	typedef device::PORT<device::PORT2, device::bitpos::B3> MOSI;
	typedef device::PORT<device::PORT2, device::bitpos::B4> SPCK;
	typedef device::spi_io<MISO, MOSI, SPCK> SPI;
#else
	// RSPI SDC 用　SPI 定義（RSPI0）
	typedef device::rspi_io<device::RSPI0> SDC_SPI;
#endif

	typedef device::PORT<device::PORT6, device::bitpos::B5> SDC_SELECT;	///< カード選択信号
	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;	///< カード電源制御
	typedef device::PORT<device::PORT6, device::bitpos::B3> SDC_DETECT;	///< カード検出

	static const char* system_str_ = { "RX24T" };

#elif defined(SIG_RX66T)
	typedef device::system_io<10000000, 160000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX66T" };
#endif

	typedef device::cmt_io<device::CMT0> CMT;
	CMT			cmt_;

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
	SCI			sci_;

#if defined(SIG_RX64M)
	RTC			rtc_;
#endif

	// SDC ハードウェア
	SDC_SPI		sdc_spi_;

	///< FatFs MMC ドライバ（ハードウェアインスタンス、ハードウェア最大速度）
	typedef fatfs::mmc_io<SDC_SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> SDC_DEV;
	SDC_DEV		sdc_dev_(sdc_spi_, 35000000);

	typedef utils::command<256> CMD_LINE;
	CMD_LINE	cmd_;
}

extern "C" {

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
	   	static volatile bool lock_ = false;
		while(lock_) ;
		lock_ = true;
		sci_.putch(ch);
		lock_ = false;
	}


	void sci_puts(const char* str)
	{
		static volatile bool lock_ = false;
		while(lock_) ;
		lock_ = true;
		sci_.puts(str);
		lock_ = false;
	}


	// syscalls.c から呼ばれる、標準入力（stdin）
	char sci_getch(void)
	{
		static volatile bool lock_ = false;
		while(lock_) ;
		lock_ = true;
		auto ch = sci_.getch();
		lock_ = false;
		return ch;
	}


	uint16_t sci_length()
	{
		return sci_.recv_length();
	}


	DSTATUS disk_initialize(BYTE drv) {
		return sdc_dev_.disk_initialize(drv);
	}


	DSTATUS disk_status(BYTE drv) {
		return sdc_dev_.disk_status(drv);
	}


	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdc_dev_.disk_read(drv, buff, sector, count);
	}


	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdc_dev_.disk_write(drv, buff, sector, count);
	}


	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdc_dev_.disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
		time_t t = 0;
#if defined(SIG_RX64M)
		rtc_.get_time(t);
#endif
		return utils::str::get_fattime(t);
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
};


namespace {

	struct scan_t {
		char filename_[64];
		volatile uint32_t put_;
		volatile uint32_t get_;
		scan_t() : filename_{ 0 }, put_(0), get_(0) { }
	};

	scan_t		scan_t_;

	void shell_()
	{
        if(cmd_.service()) {
            uint8_t cmdn = cmd_.get_words();
            if(cmdn >= 1) {
                if(cmd_.cmp_word(0, "dir")) {  // dir [xxx]
					char tmp[FF_MAX_LFN + 1];
					if(cmdn == 1) {
						strcpy(tmp, utils::file_io::pwd());
					} else {
						cmd_.get_word(1, tmp, sizeof(tmp));
					}
					if(!utils::file_io::dir(tmp)) {
						utils::format("Directory path fail: '%s'\n") % tmp;
					}
				} else if(cmd_.cmp_word(0, "pwd")) {  // pwd
					const char* path = utils::file_io::pwd();
					if(path == nullptr) {
						utils::format("pwd fail\n");
					} else {
						utils::format("%s\n") % path;
					}
				} else if(cmd_.cmp_word(0, "cd")) {  // cd [xxx]
					char tmp[FF_MAX_LFN + 1];
					if(cmdn == 1) {
						strcpy(tmp, "/");
					} else {
						cmd_.get_word(1, tmp, sizeof(tmp));
					}
					if(!utils::file_io::cd(tmp)) {
						utils::format("Change directory fail: '%s'\n") % tmp;
					}
				} else if(cmd_.cmp_word(0, "scan")) {  // scan
					if(cmdn >= 1) {
						if(scan_t_.get_ != scan_t_.put_) {
							utils::format("Scan task is busy !\n");
						} else {
							cmd_.get_word(1, scan_t_.filename_, sizeof(scan_t_.filename_));
							scan_t_.put_++;
						}
					}
				} else if(cmd_.cmp_word(0, "help")) {  // help
					utils::format("    pwd           list current path\n");
					utils::format("    cd [path]     change current directory\n");
					utils::format("    dir [path]    list current directory\n");
					utils::format("    scan [file]   scan file (read 1024 bytes after wait 100ms)\n");
				} else {
					char tmp[256];
					cmd_.get_word(0, tmp, sizeof(tmp));
					utils::format("Fail: '%s'\n") % tmp; 
				}
			}
		}
	}


	void sdc_task_(void *pvParameters)
	{
		sdc_dev_.start();

		cmd_.set_prompt("# ");

		while(1) {
			sdc_dev_.service();

			shell_();

			vTaskDelay(16 / portTICK_PERIOD_MS);
		}
	}


	void led_task_(void *pvParameters)
	{
		while(1) {
			vTaskEnterCritical();
			LED::P = !LED::P();
			vTaskExitCritical();
			vTaskDelay(100 / portTICK_PERIOD_MS);
		}
	}


	void scan_task_(void *pvParameters)
	{
		while(1) {
			while(scan_t_.get_ == scan_t_.put_) {
				vTaskDelay(100 / portTICK_PERIOD_MS);
			}
			utils::file_io fio;
			if(!fio.open(scan_t_.filename_, "rb")) {
				utils::format("Can't open: '%s'\n") % scan_t_.filename_;
				scan_t_.get_++;
			} else {
				uint32_t pos = 0;
				uint8_t tmp[1024];
				while(pos < fio.get_file_size()) {
					pos += fio.read(tmp, 1024);
					vTaskDelay(25 / portTICK_PERIOD_MS);
				}
				utils::format("Scan Task: %u bytes\n") % pos;
				scan_t_.get_++;
				fio.close();
			}
		}
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
#ifdef GR_KAEDE
	// GR-KAEDE の SPI 端子のハードバグ回避
	// ※PC3 から、PC7 へ １K オームで接続
	device::PORTC::PDR.B3  = 1; // output
	device::PORTC::PODR.B3 = 1;
#endif

	SYSTEM_IO::setup_system_clock();

	LED::OUTPUT();  // LED ポートを出力に設定
	LED::P = 0;		// Off
#ifdef GR_KAEDE
	LED2::OUTPUT();
	LED2::P = 0;
#endif

	{  // SCI の開始
		uint8_t intr = 2;        // 割り込みレベル
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

#if defined(SIG_RX64M)
	{  // RTC 開始
		rtc_.start();
	}
#endif

	auto clk = F_ICLK / 1000000;
	utils::format("\nStart FreeRTOS FatFs sample for '%s' %d[MHz]\n") % system_str_ % clk;

	{
		uint32_t stack_size = 2048;
		void* param = nullptr;
		uint32_t prio = 1;
		xTaskCreate(sdc_task_, "SD_MAN", stack_size, param, prio, nullptr);
	}
	{
		uint32_t stack_size = 256;
		void* param = nullptr;
		uint32_t prio = 1;
		xTaskCreate(led_task_, "LED", stack_size, param, prio, nullptr);
	}
	{
		uint32_t stack_size = 2048;
		void* param = nullptr;
		uint32_t prio = 1;
		xTaskCreate(scan_task_, "SCAN", stack_size, param, prio, nullptr);
	}

	vTaskStartScheduler();

	// タスクスケジューラーが正常なら実行されない
	while(1) {
	}
}
