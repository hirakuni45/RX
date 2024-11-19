//=====================================================================//
/*! @file
    @brief  FreeRTOS FatFs サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
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
#include "common/string_utils.hpp"
#include "common/spi_io2.hpp"
#include "common/rspi_io.hpp"
#include "common/command.hpp"
#include "common/file_io.hpp"
#include "common/shell.hpp"

#include "FreeRTOS.h"
#include "task.h"

// オーディオ再生を行う場合有効にする
// #define PLAY_AUDIO

#ifdef PLAY_AUDIO
#include "common/tpu_io.hpp"
#include "sound/sound_out.hpp"
#include "sound/wav_in.hpp"
#include "sound/mp3_in.hpp"
#endif

namespace {

#if defined(SIG_RX24T)
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

	static constexpr uint32_t sdc_spi_speed_ = 20'000'000;
#elif defined(SIG_RX64M)
	typedef utils::rtc_io<device::RTC> RTC;

#ifdef GR_KAEDE
#if SOFT_SPI
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

	static const uint32_t sdc_spi_speed_ = 30'000'000;
#else
	///< Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORTC, device::bitpos::B3> MISO;
	typedef device::PORT<device::PORT7, device::bitpos::B6> MOSI;
	typedef device::PORT<device::PORT7, device::bitpos::B7> SPCK;
	typedef device::spi_io2<MISO, MOSI, SPCK> SDC_SPI;

	typedef device::PORT<device::PORT8, device::bitpos::B2> SDC_POWER;	///< カード電源制御
	typedef device::PORT<device::PORTC, device::bitpos::B2> SDC_SELECT;  ///< カード選択信号
	typedef device::PORT<device::PORT8, device::bitpos::B1> SDC_DETECT;  ///< カード検出

	static constexpr uint32_t sdc_spi_speed_ = 30'000'000;
#endif

#elif defined(SIG_RX71M)

	static constexpr uint32_t sdc_spi_speed_ = 30000000;
#elif defined(SIG_RX65N)
	typedef device::PORT<device::PORT2, device::bitpos::B2> MISO;  // DAT0
	typedef device::PORT<device::PORT2, device::bitpos::B0> MOSI;  // CMD
	typedef device::PORT<device::PORT2, device::bitpos::B1> SPCK;  // CLK
	typedef device::spi_io2<MISO, MOSI, SPCK> SDC_SPI;
	typedef device::PORT<device::PORT1, device::bitpos::B7> SDC_SELECT;  // DAT3 カード選択信号
	typedef device::NULL_PORT  SDC_POWER;	///< SD カード電源制御（制御なし、常にＯＮ）
	typedef device::PORT<device::PORT2, device::bitpos::B5> SDC_DETECT;  // CD カード検出

	static constexpr uint32_t sdc_spi_speed_ = 30'000'000;
#elif defined(SIG_RX72N)
    typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;	///< '1'でＯＮ
    typedef device::NULL_PORT SDC_WP;  ///< カード書き込み禁止ポート設定
    // RX72N Envision Kit の SDHI ポートは、候補３で指定できる
    typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::option::THIRD> SDC;
    SDC			sdc_;

	static constexpr uint32_t sdc_spi_speed_ = 30'000'000;
#elif defined(SIG_RX72M)
	static constexpr uint32_t sdc_spi_speed_ = 30'000'000;
#elif defined(SIG_RX72T)
	// RSPI 定義、FIRST: P20:RSPCK, P21:MOSI, P22:MISO
	typedef device::rspi_io<device::RSPI0> SDC_SPI;

	typedef device::PORT<device::PORT3, device::bitpos::B0> SDC_SELECT;		///< カード選択信号
	typedef device::PORT<device::PORTA, device::bitpos::B2> SDC_POWER;		///< カード電源制御 MIC2076-1YM (ACTIVE-HIGH)
	typedef device::PORT<device::PORTB, device::bitpos::B4, 0> SDC_DETECT;	///< カード検出（ACTIVE-LOW）
	typedef device::NULL_PORT SDC_WPRT;										///< カード書き込み禁止ポート設定（無効）

	static constexpr uint32_t sdc_spi_speed_ = 30'000'000;
#endif

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT;
	CMT			cmt_;

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義
	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI;
	SCI			sci_;

	SemaphoreHandle_t	putch_sync_;
	SemaphoreHandle_t	puts_sync_;
	SemaphoreHandle_t	getch_sync_;

#if defined(SIG_RX64M)
	RTC			rtc_;
#endif

	// SDC ハードウェア
	SDC_SPI		sdc_spi_;

	///< FatFs MMC ドライバ（ハードウェアインスタンス、ハードウェア最大速度）
	typedef device::NULL_PORT SDC_WPRT;
	typedef fatfs::mmc_io<SDC_SPI, SDC_SELECT, SDC_POWER, SDC_DETECT, SDC_WPRT> SDC_DEV;
	SDC_DEV		sdc_dev_(sdc_spi_, sdc_spi_speed_);

	typedef utils::command<256> CMD;
	CMD			cmd_;

	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);

#ifdef PLAY_AUDIO
	volatile uint32_t	wpos_;

	/// DMAC 終了割り込み
	class dmac_term_task {
	public:
		void operator() () {
			device::DMAC0::DMCNT.DTE = 1;  // DMA を再スタート
			wpos_ = 0;
		}
	};

	typedef device::dmac_mgr<device::DMAC0, dmac_term_task> DMAC_MGR;
	DMAC_MGR	dmac_mgr_;

	uint32_t get_wave_pos_() { return (dmac_mgr_.get_count() & 0x3ff) ^ 0x3ff; }

	typedef device::R12DA DAC;
	typedef device::dac_out<DAC> DAC_OUT;
	DAC_OUT		dac_out_;

	typedef sound::sound_out<int16_t, 8192, 1024> SOUND_OUT;
	// コンストラクターで、中間レベルを指定する。
	SOUND_OUT	sound_out_(0x8000);

	class tpu_task {
	public:
		void operator() () {
			uint32_t tmp = wpos_;
			++wpos_;
			if((tmp ^ wpos_) & 64) {
				sound_out_.service(64);
			}
		}
	};

	typedef device::tpu_io<device::TPU0, tpu_task> TPU0;
	TPU0		tpu0_;	

	typedef sound::mp3_in MP3_IN;
	MP3_IN		mp3_in_;
	typedef sound::wav_in WAV_IN;
	WAV_IN		wav_in_;

	typedef utils::dir_list DLIST;
	DLIST		dlist_;


	void update_led_()
	{
		using namespace board_profile;

		static uint8_t n = 0;
		++n;
		if(n >= 30) {
			n = 0;
		}
		vTaskEnterCritical();
		if(n < 10) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
		vTaskExitCritical();
	}


	sound::af_play::CTRL sound_ctrl_task_()
	{
		auto ctrl = sound::af_play::CTRL::NONE;
#if 0
		if(sci_.recv_length() > 0) {
			auto ch = sci_.getch();
			if(ch == ' ') {			
				ctrl = sound::af_play::CTRL::PAUSE;
			} else if(ch == 0x08) {  // BS
				ctrl = sound::af_play::CTRL::REPLAY;
			} else if(ch == 0x0D) {  // RETURN
				ctrl = sound::af_play::CTRL::STOP;
			} else if(ch == 0x1b) {  // ESC
				ctrl = sound::af_play::CTRL::STOP;
				dlist_.stop();
			}
		}
#endif
		update_led_();

		return ctrl;
	}


	void sound_tag_task_(utils::file_io& fin, const sound::tag_t& tag)
	{
		utils::format("Album:  '%s'\n") % tag.get_album().c_str();
		utils::format("Title:  '%s'\n") % tag.get_title().c_str();
		utils::format("Artist: '%s'\n") % tag.get_artist().c_str();
		utils::format("Year:    %s\n") % tag.get_year().c_str();
		utils::format("Disc:    %s\n") % tag.get_disc().c_str();
		utils::format("Track:   %s\n") % tag.get_track().c_str();
	}


	void sound_update_task_(uint32_t t)
	{
		uint16_t sec = t % 60;
		uint16_t min = (t / 60) % 60;
		uint16_t hor = (t / 3600) % 24;
		utils::format("\r%02d:%02d:%02d") % hor % min % sec;
	}


	bool play_mp3_(const char* fname)
	{
		utils::file_io fin;
		if(!fin.open(fname, "rb")) {
			return false;
		}
		mp3_in_.set_ctrl_task(sound_ctrl_task_);
		mp3_in_.set_tag_task(sound_tag_task_);
		mp3_in_.set_update_task(sound_update_task_);
		bool ret = mp3_in_.decode(fin, sound_out_);
		fin.close();
		return ret;
	}


	bool play_wav_(const char* fname)
	{
		utils::file_io fin;
		if(!fin.open(fname, "rb")) {
			return false;
		}
		wav_in_.set_ctrl_task(sound_ctrl_task_);
		wav_in_.set_tag_task(sound_tag_task_);
		wav_in_.set_update_task(sound_update_task_);
		bool ret = wav_in_.decode(fin, sound_out_);
		fin.close();
		return ret;
	}


	void play_loop_(const char*, const char*);

	struct loop_t {
		const char*	start;
		bool	enable;
	};
	loop_t		loop_t_;

	void play_loop_func_(const char* name, const FILINFO* fi, bool dir, void* option)
	{
		loop_t* t = static_cast<loop_t*>(option);
		if(t->enable) {
			if(strcmp(name, t->start) != 0) {
				return;
			} else {
				t->enable = false;
			}
		}
		if(dir) {
			play_loop_(name, "");
		} else {
			const char* ext = strrchr(name, '.');
			if(ext != nullptr) {
				bool ret = true; 
				if(utils::str::strcmp_no_caps(ext, ".mp3") == 0) {
					ret = play_mp3_(name);
				} else if(utils::str::strcmp_no_caps(ext, ".wav") == 0) {
					ret = play_wav_(name);
				}
				if(!ret) {
					utils::format("Can't open audio file: '%s'\n") % name;
				}
			}
		}
	}


	void play_loop_(const char* root, const char* start)
	{
		loop_t_.start = start;
		if(strlen(start) != 0) {
			loop_t_.enable = true;
		} else {
			loop_t_.enable = false;
		}
		dlist_.start(root);
	}
#endif
}

extern "C" {

#ifdef PLAY_AUDIO
	void set_sample_rate(uint32_t freq)
	{
		uint8_t intr_level = 5;
		if(!tpu0_.start(freq, intr_level)) {
			utils::format("TPU0 start error...\n");
		}
	}
#endif

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		xSemaphoreTake(putch_sync_, (TickType_t)0 );
		sci_.putch(ch);
		xSemaphoreGive(putch_sync_);
	}


	void sci_puts(const char* str)
	{
		xSemaphoreTake(puts_sync_, (TickType_t)0 );
		sci_.puts(str);
		xSemaphoreGive(puts_sync_);
	}


	// syscalls.c から呼ばれる、標準入力（stdin）
	char sci_getch(void)
	{
		xSemaphoreTake(getch_sync_, (TickType_t)0 );
		auto ch = sci_.getch();
		xSemaphoreGive(getch_sync_);
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
		auto intr = static_cast<device::ICU::LEVEL>(configKERNEL_INTERRUPT_PRIORITY);
		cmt_.start(configTICK_RATE_HZ, intr, vTickISR);

		device::icu_mgr::set_task(device::ICU::VECTOR::SWINT, vSoftwareInterruptISR);
		device::icu_mgr::set_level(device::ICU::VECTOR::SWINT, intr);
	}
};


namespace {

	struct name_t {
		char filename_[64];
		volatile uint32_t put_;
		volatile uint32_t get_;
		name_t() : filename_{ 0 }, put_(0), get_(0) { }
	};

	name_t		name_t_;

	void cmds_()
	{
        if(!cmd_.service()) {
			return;
		}

		if(shell_.analize()) {
			return;
		}

		auto cmdn = cmd_.get_words();
		if(cmd_.cmp_word(0, "scan")) {  // scan
			if(cmdn >= 2) {
				if(name_t_.get_ != name_t_.put_) {
					utils::format("Scan task is busy !\n");
				} else {
					cmd_.get_word(1, name_t_.filename_, sizeof(name_t_.filename_));
					name_t_.put_++;
				}
			}
#ifdef PLAY_AUDIO
		} else if(cmd_.cmp_word(0, "play")) {  // play [xxx]
			if(cmdn >= 2) {
				if(name_t_.get_ != name_t_.put_) {
					utils::format("Audio task is busy !\n");
				} else {
					cmd_.get_word(1, name_t_.filename_, sizeof(name_t_.filename_));
					name_t_.put_++;
				}
			}
#endif
		} else if(cmd_.cmp_word(0, "help")) {  // help
			shell_.help();
#ifdef PLAY_AUDIO
			utils::format("    play file       play audio file (wav, mp3)\n");
#else
			utils::format("    scan [file]     scan file (read 1024 bytes after wait 25ms)\n");
#endif
		} else {
			utils::format("Command error: '%s'\n") % cmd_.get_command();
		}
	}


	void sdc_task_(void *pvParameters)
	{
		sdc_dev_.start();

		cmd_.set_prompt("# ");

		while(1) {
			sdc_dev_.service();

			cmds_();

			vTaskDelay(16 / portTICK_PERIOD_MS);
		}
	}


	void led_task_(void *pvParameters)
	{
		using namespace board_profile;

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
#ifdef PLAY_AUDIO
			while(name_t_.get_ == name_t_.put_) {
				vTaskDelay(100 / portTICK_PERIOD_MS);
				dlist_.service(1, play_loop_func_, true, &loop_t_);
			}

			if(strlen(name_t_.filename_) == 0) {
				play_loop_("", "");
			} else {
				if(std::strcmp(name_t_.filename_, "*") == 0) {
					play_loop_("", "");
				} else {
					play_loop_("", name_t_.filename_);
				}
			}
			name_t_.get_++;
#else
			while(name_t_.get_ == name_t_.put_) {
				vTaskDelay(100 / portTICK_PERIOD_MS);
			}
			utils::file_io fio;
			if(!fio.open(name_t_.filename_, "rb")) {
				utils::format("Can't open: '%s'\n") % name_t_.filename_;
				name_t_.get_++;
			} else {
				uint32_t pos = 0;
				uint8_t tmp[1024];
				while(pos < fio.get_file_size()) {
					pos += fio.read(tmp, 1024);
					utils::format("=@=");
					vTaskDelay(25 / portTICK_PERIOD_MS);
				}
				utils::format("Scan Task: %u bytes\n") % pos;
				name_t_.get_++;
				fio.close();
			}
#endif
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

	SYSTEM_IO::boost_master_clock();

	using namespace board_profile;

	LED::OUTPUT();  // LED ポートを出力に設定
	LED::P = 0;		// Off
#ifdef GR_KAEDE
	LED2::OUTPUT();
	LED2::P = 0;
#endif

	{  // SCI の開始
		putch_sync_ = xSemaphoreCreateBinary();	// putch 排他制御のリソースを作成
		puts_sync_  = xSemaphoreCreateBinary();	// puts  排他制御のリソースを作成
		getch_sync_ = xSemaphoreCreateBinary();	// getch 排他制御のリソースを作成
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

#if defined(SIG_RX64M)
	{  // RTC 開始
		rtc_.start();
	}
#endif

#ifdef PLAY_AUDIO
	{  // 内臓１２ビット D/A の設定
		bool amp_ena = true;
		dac_out_.start(DAC_OUT::output::CH0_CH1, amp_ena);
		dac_out_.out0(0x8000);
		dac_out_.out1(0x8000);
	}

	{  // 波形メモリーの無音状態初期化
		sound_out_.mute();
	}

	{  // サンプリング・タイマー設定
		set_sample_rate(44100);
	}

	{  // DMAC マネージャー開始
		uint8_t intr_level = 4;
		bool cpu_intr = true;
		auto ret = dmac_mgr_.start(tpu0_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
			reinterpret_cast<uint32_t>(sound_out_.get_wave()), DAC::DADR0.address(),
			sound_out_.size(), intr_level, cpu_intr);
		if(!ret) {
			utils::format("DMAC Not start...\n");
		}
	}
#endif

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("\nStart FreeRTOS FatFs sample for '%s' %d[MHz]\n") % system_str_ % clk;

	{
		uint32_t stack_size = 1024;
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
		uint32_t stack_size = 8192;
		void* param = nullptr;
		uint32_t prio = 1;
		xTaskCreate(scan_task_, "SCAN", stack_size, param, prio, nullptr);
	}

	vTaskStartScheduler();

	// タスクスケジューラーが正常なら実行されない
	while(1) {
	}
}
