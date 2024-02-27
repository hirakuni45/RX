//=========================================================================//
/*! @file
    @brief  RX65N/RX72N Envision kit ロガーメイン
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
// 漢字フォントをキャッシュする場合
#define CASH_KFONT

#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/shell.hpp"
#include "common/spi_io2.hpp"

#include "scenes.hpp"

namespace {

    typedef device::cmt_mgr<board_profile::CMT_CH> CMT;
    CMT         cmt_;

#if defined(SIG_RX65N)
	typedef device::PORT<device::PORT6, device::bitpos::B4, 0> SDC_POWER;  ///< '0'でＯＮ
	typedef device::NULL_PORT SDC_WPRT;  ///< カード書き込み禁止ポート設定
	// RX65N Envision Kit の SDHI ポートは、候補３で指定できる。
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WPRT, device::port_map::ORDER::THIRD> SDC;
#elif defined(SIG_RX72N)
	typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;  ///< '1'でＯＮ
	typedef device::NULL_PORT SDC_WP;  ///< カード書き込み禁止ポート設定
	// RX72N Envision Kit の SDHI ポートは、候補３で指定できる
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::ORDER::THIRD> SDC;
#endif

	typedef utils::fixed_fifo<char, 512>  REB;
	typedef utils::fixed_fifo<char, 1024> SEB;
	typedef device::sci_io<board_profile::SCI_CH, REB, SEB, board_profile::SCI_ORDER> SCI;
	SCI			sci_;

	SDC			sdc_;

	typedef utils::command<256> CMD;
	CMD			cmd_;
	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);

	typedef app::scenes	SCENES;
	SCENES		scenes_;


//  StaticSemaphore を使う場合、「configSUPPORT_STATIC_ALLOCATION」を「1」にする必要がある。
//	StaticSemaphore_t	putch_semaphore_;
	SemaphoreHandle_t	putch_sync_;
//	StaticSemaphore_t	puts_semaphore_;
	SemaphoreHandle_t	puts_sync_;
//	StaticSemaphore_t	getch_semaphore_;
	SemaphoreHandle_t	getch_sync_;


	void command_()
	{
		if(!cmd_.service()) {
			return;
		}
		if(shell_.analize()) {
			return;
		}

		auto cmdn = cmd_.get_words();
		if(cmd_.cmp_word(0, "gui")) {
			at_scenes_base().at_widget_director().list_all();
		} else if(cmd_.cmp_word(0, "help")) {
			shell_.help();
			utils::format("    gui\n");
		} else {
			utils::format("Command error: '%s'\n") % cmd_.get_command();
		}
	}
}


bool get_mount()
{
	return sdc_.get_mount();
}


void change_scene(app::scene_id id)
{
	scenes_.change(id);
}


app::scenes_base& at_scenes_base()
{
	return scenes_.at_base();
}

/// widget の登録
bool insert_widget(gui::widget* w)
{
	return at_scenes_base().at_widget_director().insert(w);
}

/// widget の解除
void remove_widget(gui::widget* w)
{
	at_scenes_base().at_widget_director().remove(w);
}


extern "C" {

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


	DSTATUS disk_initialize(BYTE drv) {
		return sdc_.disk_initialize(drv);
	}


	DSTATUS disk_status(BYTE drv) {
		return sdc_.disk_status(drv);
	}


	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdc_.disk_read(drv, buff, sector, count);
	}


	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdc_.disk_write(drv, buff, sector, count);
	}


	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdc_.disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
///		time_t t = 0;
///		rtc_.get_time(t);
		// GPS モジュールから GMT 時間を取得
		auto t = scenes_.at_base().at_nmea().get_gmtime();		
		return utils::str::get_fattime(t);
	}


    void vApplicationMallocFailedHook(void)
    {
        taskDISABLE_INTERRUPTS();
        for( ;; );
    }


    void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
    {
        ( void ) pcTaskName;
        ( void ) pxTask;

        taskDISABLE_INTERRUPTS();
        for( ;; );
    }


    void vApplicationIdleHook(void) { }


    void vApplicationTickHook(void) { }


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


	void main_task_(void* param)
	{
		using namespace board_profile;

		cmd_.set_prompt("# ");

		// シーン初期化
		scenes_.at_base().init();

		LED::DIR = 1;

		uint8_t n = 0;
		while(1) {
			scenes_.at_base().sync();

			scenes_.at_base().update();

			scenes_.service();

			sdc_.service();

			command_();

			++n;
			if(n >= 30) n = 0;
			if(n < 10) {
				LED::P = 0;
			} else {
				LED::P = 1;
			}
		}
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	using namespace board_profile;

	{  // SCI 設定
		putch_sync_ = xSemaphoreCreateBinary();	// putch 排他制御のリソースを作成
		puts_sync_  = xSemaphoreCreateBinary();	// puts  排他制御のリソースを作成
		getch_sync_ = xSemaphoreCreateBinary();	// getch 排他制御のリソースを作成
		auto intr = device::ICU::LEVEL::_2;
		sci_.start(115200, intr);
	}

	{  // SD カード・クラスの初期化
		sdc_.start();
	}

	utils::format("\rStart '%s' Data Logger\n") % system_str_;

    {
        uint32_t stack_size = 8192;
        void* param = nullptr;
        uint32_t prio = 1;
        xTaskCreate(main_task_, "Main", stack_size, param, prio, nullptr);
    }

    vTaskStartScheduler();
}
