//=====================================================================//
/*! @file
    @brief  RX65N Envision Kit オーディオ再生サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/sci_i2c_io.hpp"
#include "common/spi_io2.hpp"
#include "common/file_io.hpp"
#include "common/tpu_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/shell.hpp"

#include "audio_codec.hpp"
#include "audio_gui.hpp"

// ファミコン PAD での操作を有効にする場合
// #define ENABLE_FAMIPAD

namespace {

    typedef device::cmt_io<device::CMT0> CMT;
    CMT         cmt_;

	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;

#ifdef ENABLE_FAMIPAD
	// Famicon PAD (CMOS 4021B Shift Register)
	// 電源は、微小なので、接続を簡単に行う為、ポート出力を電源として利用
	typedef device::PORT<device::PORT6, device::bitpos::B0> PAD_VCC;
	typedef device::PORT<device::PORT6, device::bitpos::B1> PAD_GND;
	typedef device::PORT<device::PORT6, device::bitpos::B2> PAD_P_S;
	typedef device::PORT<device::PORT6, device::bitpos::B5> PAD_CLK;
	typedef device::PORT<device::PORT7, device::bitpos::B3> PAD_OUT;
	typedef chip::FAMIPAD<PAD_P_S, PAD_CLK, PAD_OUT> FAMIPAD;
	FAMIPAD		famipad_;

	uint8_t		pad_level_ = 0;
#endif

	typedef device::system_io<12000000> SYSTEM_IO;

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<device::SCI9, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

	// カード電源制御は使わない場合、「device::NULL_PORT」を指定する。
//	typedef device::NULL_PORT SDC_POWER;
	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;

	// 書き込み禁止は使わない
	typedef device::NULL_PORT SDC_WPRT;

	// RX65N Envision Kit の SDHI ポートは、候補３で指定できる
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WPRT,
		device::port_map::option::THIRD> SDHI;
	SDHI		sdh_;

	typedef utils::command<256> CMD;
	CMD			cmd_;

	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);

	typedef app::audio_gui GUI;
	GUI			gui_;

	typedef audio::codec<GUI::RENDER> AUDIO;
	AUDIO		audio_(gui_.at_render());

//	int16_t		touch_org_ = 0;
//	uint8_t		touch_num_ = 0;

    struct name_t {
        char filename_[256];
        volatile uint32_t put_;
        volatile uint32_t get_;
        name_t() : filename_{ 0 }, put_(0), get_(0) { }
    };

    name_t      name_t_;

	void update_led_()
	{
		static uint8_t n = 0;
		++n;
		if(n >= 30) {
			n = 0;
		}
		if(n < 10) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}


	sound::af_play::CTRL sound_ctrl_task_()
	{
		auto ctrl = sound::af_play::CTRL::NONE;
#ifdef ENABLE_FAMIPAD
		uint8_t level = famipad_.update();
		uint8_t ptrg = ~pad_level_ &  level;
		uint8_t ntrg =  pad_level_ & ~level;
		pad_level_ = level;

		if(chip::on(ptrg, chip::FAMIPAD_ST::SELECT)) {
			ctrl = sound::af_play::CTRL::PAUSE;
		}
		if(chip::on(ptrg, chip::FAMIPAD_ST::RIGHT)) {
			ctrl = sound::af_play::CTRL::STOP;
		}
		if(chip::on(ptrg, chip::FAMIPAD_ST::LEFT)) {
			ctrl = sound::af_play::CTRL::REPLAY;
		}
		if(chip::on(ptrg, chip::FAMIPAD_ST::START)) { // Cancel Play
			ctrl = sound::af_play::CTRL::STOP;
			audio_.stop();
			render_.clear(DEF_COLOR::Black);
		}
#endif

#if 0
		auto tnum = touch_.get_touch_num();
		const auto& xy = touch_.get_touch_pos(0);
		if(touch_num_ == 2 && tnum < 2) {  // pause（２点タッチが離された瞬間）
			ctrl = sound::af_play::CTRL::PAUSE;
			touch_org_ = xy.x;
		} else if(touch_num_ == 3 && tnum < 3) {  // Cancel Play（３点タッチが離れた瞬間）
			ctrl = sound::af_play::CTRL::STOP;
			audio_.stop();
			render_.clear(DEF_COLOR::Black);
			touch_org_ = xy.x;
		} else if(touch_num_ == 0 && tnum == 1) {
			touch_org_ = xy.x;
		} else if(touch_num_ == 1 && tnum == 0) {
			auto d = xy.x - touch_org_;
			if(d >= 16) {  // Next
				ctrl = sound::af_play::CTRL::STOP;
				touch_org_ = xy.x;
			} else if(d <= -16) {  // Replay
				ctrl = sound::af_play::CTRL::REPLAY;
				touch_org_ = xy.x;
			}
		}
		touch_num_ = tnum;
#endif
		return ctrl;
	}


	void command_()
	{
		if(!cmd_.service()) {
			return;
		}

		if(shell_.analize()) {
			return;
		}

		auto cmdn = cmd_.get_words();
		if(cmd_.cmp_word(0, "play")) {
			if(cmdn >= 2) {
				char tmp[128];
				cmd_.get_word(1, tmp, sizeof(tmp));
				if(std::strcmp(tmp, "*") == 0) {
///					audio_.play_loop("", "");
				} else {
///					audio_.play_file(tmp);
				}
			} else {
///				audio_.play_loop("", "");
			}
		} else if(cmd_.cmp_word(0, "clear")) {
			gui_.at_render().clear(GUI::DEF_COLOR::Black);
		} else if(cmd_.cmp_word(0, "img")) {
			if(cmdn >= 2) {
				char tmp[256];
				cmd_.get_word(1, tmp, sizeof(tmp));
				if(!audio_.at_img_in().load(tmp)) {
					utils::format("Can't load image file: '%s'\n") % tmp;
				}
			}
		} else if(cmd_.cmp_word(0, "help")) {
			shell_.help();
			utils::format("    play [filename, *]\n");
			utils::format("    clear\n");
			utils::format("    img [filename]\n");
		} else {
			utils::format("Command error: '%s'\n") % cmd_.get_command();
		}
	}
}

/// widget の登録・グローバル関数
bool insert_widget(gui::widget* w)
{
    return gui_.insert_widget(w);
}

/// widget の解除・グローバル関数
void remove_widget(gui::widget* w)
{
    gui_.remove_widget(w);
}


extern "C" {

	void set_sample_rate(uint32_t freq)
	{
		audio_.set_sample_rate(freq);
	}

#ifdef ENABLE_FAMIPAD
	uint8_t get_fami_pad()
	{
		return famipad_.update();
	}
#endif

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
		return sdh_.disk_initialize(drv);
	}


	DSTATUS disk_status(BYTE drv) {
		return sdh_.disk_status(drv);
	}


	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdh_.disk_read(drv, buff, sector, count);
	}


	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdh_.disk_write(drv, buff, sector, count);
	}


	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdh_.disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
		time_t t = 0;
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
        uint8_t intr = configKERNEL_INTERRUPT_PRIORITY;
        cmt_.start(configTICK_RATE_HZ, intr, vTickISR);

        device::icu_mgr::set_task(device::ICU::VECTOR::SWINT, vSoftwareInterruptISR);
        device::icu_mgr::set_level(device::ICU::VECTOR::SWINT, configKERNEL_INTERRUPT_PRIORITY);
    }
}


namespace {

	void codec_task_(void *pvParameters)
	{
		// オーディオの開始
///		audio_.set_ctrl_task(sound_ctrl_task_);
		audio_.start();

		while(1) {
			if(name_t_.get_ != name_t_.put_) {
				if(strlen(name_t_.filename_) == 0) {
					audio_.play_loop("", "");
				} else {
					if(std::strcmp(name_t_.filename_, "*") == 0) {
						audio_.play_loop("", "");
					} else {
						audio_.play_loop("", name_t_.filename_);
					}
				}
				++name_t_.get_;
			}
			audio_.service();

			vTaskDelay(10 / portTICK_PERIOD_MS);
		}
	}


	void main_task_(void *pvParameters)
	{
		cmd_.set_prompt("# ");

		LED::DIR = 1;

		gui_.start();
		gui_.setup_touch_panel();

		gui_.open();  // 標準 GUI

		while(1) {
			if(gui_.update(sdh_.get_mount())) {
				strncpy(name_t_.filename_, gui_.get_filename(), sizeof(name_t_.filename_));
				name_t_.put_++;
			}

			command_();
			sdh_.service();
			update_led_();
		}
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	{  // SD カード・クラスの初期化
		sdh_.start();
	}

	utils::format("RTK5RX65N Start for AUDIO sample\n");

    {
        uint32_t stack_size = 4096;
        void* param = nullptr;
        uint32_t prio = 2;
        xTaskCreate(codec_task_, "Codec", stack_size, param, prio, nullptr);
    }

    {
        uint32_t stack_size = 8192;
        void* param = nullptr;
        uint32_t prio = 1;
        xTaskCreate(main_task_, "Main", stack_size, param, prio, nullptr);
    }

	vTaskStartScheduler();
}
