//=====================================================================//
/*! @file
    @brief  ファースト・サンプル（LED 点滅） @n
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

#include "FreeRTOS.h"
#include "task.h"

extern "C" {
	void vTickISR(void);
	void vSoftwareInterruptISR(void);
};

namespace {

/// ベースクリスタルの定義
/// LED 接続ポートの定義
#if defined(SIG_RX71M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX72M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX64M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX65N)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
#elif defined(SIG_RX63T)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORTB, device::bitpos::B7> LED;
#elif defined(SIG_RX24T)
	typedef device::system_io<10000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#elif defined(SIG_RX66T)
	typedef device::system_io<10000000, 160000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#endif

	typedef device::cmt_io<device::CMT0> CMT;
	CMT			cmt_;
}

extern "C" {

	void vApplicationMallocFailedHook( void )
	{
		/* Called if a call to pvPortMalloc() fails because there is insufficient
		free memory available in the FreeRTOS heap.  pvPortMalloc() is called
		internally by FreeRTOS API functions that create tasks, queues, software
		timers, and semaphores.  The size of the FreeRTOS heap is set by the
		configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
		taskDISABLE_INTERRUPTS();
		for( ;; );
	}


	void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
	{
		( void ) pcTaskName;
		( void ) pxTask;

		/* Run time stack overflow checking is performed if
		configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
		function is called if a stack overflow is detected. */
		taskDISABLE_INTERRUPTS();
		for( ;; );
	}


	void vApplicationIdleHook( void )
	{
		/// volatile size_t xFreeHeapSpace;

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


	void vApplicationTickHook( void )
	{
	}


	void vAssertCalled( void )
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


	void vApplicationSetupTimerInterrupt( void )
	{
		uint8_t intr = configKERNEL_INTERRUPT_PRIORITY;
		cmt_.start(configTICK_RATE_HZ, intr, vTickISR);

		device::icu_mgr::set_task(device::ICU::VECTOR::SWINT, vSoftwareInterruptISR);
		device::icu_mgr::set_level(device::ICU::VECTOR::SWINT, configKERNEL_INTERRUPT_PRIORITY);
	}
};


namespace {

	void vTask1(void *pvParameters)
	{
		while(1) {
			LED::P = !LED::P();
			vTaskDelay(500 / portTICK_PERIOD_MS);
		}
	}


	void vTask2(void *pvParameters)
	{
		while(1) {
			LED::P = !LED::P();
			vTaskDelay(100 / portTICK_PERIOD_MS);
		}
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	LED::OUTPUT();  // LED ポートを出力に設定
	LED::P = 1;		// Off

	{
		uint32_t stack_size = 512;
		void* param = nullptr;
		uint32_t prio = 1;
		xTaskCreate(vTask1, "Task1", stack_size, param, prio, nullptr);
		xTaskCreate(vTask2, "Task2", stack_size, param, prio, nullptr);
	}

	vTaskStartScheduler();

	// タスクスケジューラーが正常なら実行されない
	while(1) {
		utils::delay::milli_second(250);
		LED::P = !LED::P();
		utils::delay::milli_second(250);
		LED::P = !LED::P();
	}
}
