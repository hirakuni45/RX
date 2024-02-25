//=====================================================================//
/*! @file
    @brief  FreeRTOS sample（Flash LED, Output SCI）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"

#include "common/format.hpp"
#include "common/input.hpp"

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#ifdef SIG_RX64M
// RX64Mで、GR-KAEDE の場合有効にする
// #define GR_KAEDE
#endif

namespace {

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

#if defined(SIG_RX220)
	// 秋月 RX220 ボード
	static const char* system_str_ = { "AE-RX220" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B3, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB, device::port_map::ORDER::SECOND> SCI;
#elif defined(SIG_RX231)
	static const char* system_str_ = { "RX231 DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT4, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB, device::port_map::ORDER::SECOND> SCI;
#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX26T)
	static const char* system_str_ = { "RX26T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX62N)
  #if defined(CQ_FRK)
    // FRK-RX62N(CQ 出版社)
	static const char* system_str_ = { "RX62N FRK-RX62N" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT1, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
  #else
    // BlueBoard-RX62N_100pin
	static const char* system_str_ = { "RX62N BlueBoard-RX62N_100pin" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
  #endif
#elif defined(SIG_RX631)
	// RX631 GR-CITRUS board
	static const char* system_str_ = { "RX631 GR-CITRUS" };
	// GR-CITRUS
	static constexpr bool LED_ACTIVE = 1;
	typedef device::PORT<device::PORTA, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB, device::port_map::ORDER::SECOND> SCI;
#elif defined(SIG_RX64M)
#ifdef GR_KAEDE
	static const char* system_str_ = { "GR-KAEDE" };
	typedef device::PORT<device::PORTC, device::bitpos::B1> LED;
	typedef device::PORT<device::PORTC, device::bitpos::B0> LED2;
	typedef device::sci_io<device::SCI7, RXB, TXB> SCI;
#else
	static const char* system_str_ = { "RX64M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB, device::port_map::ORDER::THIRD> SCI;
#endif
#elif defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB, device::port_map::ORDER::THIRD> SCI;
#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N Envision Kit" };
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::sci_io<device::SCI9, RXB, TXB> SCI;
#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N Envision Kit" };
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::sci_io<device::SCI2, RXB, TXB> SCI;
#elif defined(SIG_RX72M)
	static const char* system_str_ = { "RX72M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB, device::port_map::ORDER::THIRD> SCI;
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B1> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#endif

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT			cmt_;

	SCI			sci_;

//  StaticSemaphore を使う場合、「configSUPPORT_STATIC_ALLOCATION」を「1」にする必要がある。
//	StaticSemaphore_t	putch_semaphore_;
	SemaphoreHandle_t	putch_sync_;
//	StaticSemaphore_t	puts_semaphore_;
	SemaphoreHandle_t	puts_sync_;
//	StaticSemaphore_t	getch_semaphore_;
	SemaphoreHandle_t	getch_sync_;

}

extern "C" {

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		xSemaphoreTake(putch_sync_, (TickType_t)0 );  // ポーリング 
		sci_.putch(ch);
		xSemaphoreGive(putch_sync_);
	}


	void sci_puts(const char* str)
	{
		xSemaphoreTake(puts_sync_, (TickType_t)0 );  // ポーリング 
		sci_.puts(str);
		xSemaphoreGive(puts_sync_);
	}


	// syscalls.c から呼ばれる、標準入力（stdin）
	char sci_getch(void)
	{
		xSemaphoreTake(getch_sync_, (TickType_t)0 );  // ポーリング
		auto ch = sci_.getch();
		xSemaphoreGive(getch_sync_);
		return ch;
	}


	uint16_t sci_length()
	{
		return sci_.recv_length();
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
		auto intr = static_cast<device::ICU::LEVEL>(configKERNEL_INTERRUPT_PRIORITY);
		cmt_.start(configTICK_RATE_HZ, intr, vTickISR);

		device::icu_mgr::set_task(device::ICU::VECTOR::SWINT, vSoftwareInterruptISR);
		device::icu_mgr::set_level(device::ICU::VECTOR::SWINT, intr);
	}
};


namespace {

	void vTask1(void *pvParameters)
	{
		uint32_t loop = 0;
		uint32_t cnt = 0;
		while(1) {
			vTaskEnterCritical();
			LED::P = !LED::P();
			vTaskExitCritical();
			vTaskDelay(500 / portTICK_PERIOD_MS);
			++loop;
			if(loop >= 10) {
				loop = 0;
				utils::format("Task1: %u\n") % cnt;
				++cnt;
			}
		}
	}


	void vTask2(void *pvParameters)
	{
		uint32_t loop = 0;
		uint32_t cnt = 0;
		while(1) {
			vTaskEnterCritical();
#ifdef GR_KAEDE
			LED2::P = !LED2::P();
#else
			LED::P = !LED::P();
#endif
			vTaskExitCritical();
			vTaskDelay(100 / portTICK_PERIOD_MS);
			++loop;
			if(loop >= 12) {
				loop = 0;
				utils::format("Task2: %u\n") % cnt;
				++cnt;
			}
		}
	}


	void vTask3(void *pvParameters)
	{
		uint32_t cnt = 0;
		while(1) {
			utils::format("Task3: %u\n") % cnt;
			++cnt;
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	LED::OUTPUT();  // LED ポートを出力に設定
	LED::P = 1;		// Off
#ifdef GR_KAEDE
	LED2::OUTPUT();
	LED2::P = 1;
#endif

	{  // SCI の開始
		putch_sync_ = xSemaphoreCreateBinary();	// putch 排他制御のリソースを作成
		puts_sync_  = xSemaphoreCreateBinary();	// puts  排他制御のリソースを作成
		getch_sync_ = xSemaphoreCreateBinary();	// getch 排他制御のリソースを作成
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	auto clk = device::clock_profile::ICLK / 1000000;
	utils::format("Start FreeRTOS %s, sample for '%s' %d[MHz]\n")
		% tskKERNEL_VERSION_NUMBER % system_str_ % clk;

	{
		uint32_t stack_size = 512;
		void* param = nullptr;
		uint32_t prio = 1;
		xTaskCreate(vTask1, "Task1", stack_size, param, prio, nullptr);
		xTaskCreate(vTask2, "Task2", stack_size, param, prio, nullptr);
		xTaskCreate(vTask3, "Task3", stack_size, param, prio, nullptr);
	}

	vTaskStartScheduler();

	// タスクスケジューラーが正常なら実行されない
	utils::format("FreeRTOS Stalled...\n");
	while(1) {
		utils::delay::milli_second(250);
		LED::P = !LED::P();
		utils::delay::milli_second(250);
		LED::P = !LED::P();
	}
}
