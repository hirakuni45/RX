//=====================================================================//
/*! @file
    @brief  RX64M/RX65N/RX72N Audio サンプル @n
			SD-CARD にある MP3、WAV 形式のサファイルを再生する。@n
			オーディオ出力として、マイコン内蔵 D/A 又は、SSIE を選択できる。@n
			※ D/A を使う場合「#define USE_DAC」@n
			※ SSIE を使う場合「#define USE_SSIE」(RX72N) @n
			※ GLCDC を使う場合「#define USE_GLCDC」(RX65N/RX72N)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/spi_io2.hpp"

#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/font.hpp"
#include "graphics/graphics.hpp"

#include "common/dir_list.hpp"
#include "common/shell.hpp"

#include "sound/sound_out.hpp"
#include "sound/dac_stream.hpp"
#include "sound/codec_mgr.hpp"

#if defined(SIG_RX65N) || defined(SIG_RX72N)
#include "audio_gui.hpp"
#endif

namespace {

	typedef device::cmt_io<device::CMT0> CMT;
	CMT			cmt_;

#if defined(SIG_RX64M)
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX64M" };

	// SDCARD 制御リソース
	typedef device::PORT<device::PORTC, device::bitpos::B3> MISO;
	typedef device::PORT<device::PORT7, device::bitpos::B6> MOSI;
	typedef device::PORT<device::PORT7, device::bitpos::B7> SPCK;
	typedef device::spi_io2<MISO, MOSI, SPCK> SDC_SPI;  ///< Soft SPI 定義
	SDC_SPI	sdc_spi_;
	typedef device::PORT<device::PORTC, device::bitpos::B2> SDC_SELECT;	///< カード選択信号
	typedef device::PORT<device::PORT8, device::bitpos::B2> SDC_POWER;	///< カード電源制御
	typedef device::PORT<device::PORT8, device::bitpos::B1> SDC_DETECT;	///< カード検出
	typedef device::NULL_PORT SDC_WPRT;  ///< カード書き込み禁止
	typedef fatfs::mmc_io<SDC_SPI, SDC_SELECT, SDC_POWER, SDC_DETECT, SDC_WPRT> SDC;
	SDC		sdc_(sdc_spi_, 25'000'000);

	// マスターバッファはでサービスできる時間間隔を考えて余裕のあるサイズとする（8192）
	// DMAC でループ転送できる最大数の２倍（1024）
	typedef sound::sound_out<int16_t, 8192, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC

#elif defined(SIG_RX71M)
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX71M" };

	// マスターバッファはでサービスできる時間間隔を考えて余裕のあるサイズとする（8192）
	// DMAC でループ転送できる最大数の２倍（1024）
	typedef sound::sound_out<int16_t, 8192, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC

#elif defined(SIG_RX65N)
	/// RX65N Envision Kit
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;
	static const char* system_str_ = { "RX65N" };

    typedef device::PORT<device::PORT6, device::bitpos::B4, 0> SDC_POWER;	///< '0'でＯＮ
    typedef device::NULL_PORT SDC_WP;		///< 書き込み禁止は使わない
    // RX65N Envision Kit の SDHI ポートは、候補３で指定できる
    typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::option::THIRD> SDC;
    SDC			sdc_;

	// マスターバッファはでサービスできる時間間隔を考えて余裕のあるサイズとする（8192）
	// DMAC でループ転送できる最大数の２倍（1024）
	typedef sound::sound_out<int16_t, 8192, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	#define USE_GLCDC

#elif defined(SIG_RX72N)
	/// RX72N Envision Kit
	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B7> SW2;
	typedef device::SCI2 SCI_CH;
	static const char* system_str_ = { "RX72N" };

    typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;	///< '1'でＯＮ
    typedef device::NULL_PORT SDC_WP;  ///< カード書き込み禁止ポート設定
    // RX72N Envision Kit の SDHI ポートは、候補３で指定できる
    typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::option::THIRD> SDC;
    SDC			sdc_;

	// マスターバッファはサービスできる時間間隔を考えて余裕のあるサイズとする（8192）
	// SSIE の FIFO サイズの２倍以上（1024）
	typedef sound::sound_out<int16_t, 8192, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x0000;

	#define USE_SSIE
	#define USE_GLCDC

#endif

	typedef utils::fixed_fifo<char, 1024> RECV_BUFF;
	typedef utils::fixed_fifo<char, 2048> SEND_BUFF;
	typedef device::sci_io<SCI_CH, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

	// コマンドライン
	typedef utils::command<256> CMD;
	CMD 		cmd_;

	// SD-CARD 操作コンテキスト
	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);

	// サウンド出力コンテキスト
	SOUND_OUT	sound_out_(ZERO_LEVEL);

    struct name_t {
        char filename_[256];
        volatile uint32_t put_;
        volatile uint32_t get_;
        name_t() : filename_{ 0 }, put_(0), get_(0) { }
    };

    name_t      name_t_;

	volatile uint32_t	audio_t_;

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

#ifdef USE_GLCDC
	// for RX65N/RX72N Envision Kit
	app::audio_gui	gui_;
#endif

	// コーデックの、リスト、制御カスタムクラス
	class list_ctrl {

		sound::def_list_ctrl	def_;

	public:
		list_ctrl() noexcept : def_() { }

		//------
		void start(const char* fn) noexcept
		{
			def_.start(fn);
#ifdef USE_GLCDC
			gui_.set_file_name(fn);
#endif
		}

		//------
		void close() noexcept
		{
			def_.close();
		}

		//------
		sound::af_play::CTRL ctrl() noexcept
		{
			auto c = def_.ctrl();
			if(sound::af_play::CTRL::NONE != c) return c;
#ifdef USE_GLCDC
			c = gui_.get_ctrl();
#endif
			return c; 
		}

		//------
		void tag(utils::file_io& fin, const sound::tag_t& t) noexcept
		{
#ifdef USE_GLCDC
			gui_.render_tag(fin, t);
#endif
			def_.tag(fin, t);
		}

		//------
		void update(uint32_t t) noexcept
		{
#ifndef USE_GLCDC
			def_.update(t);
#endif
			audio_t_ = t;
		}	
	};
	list_ctrl	list_ctrl_;

	typedef sound::codec_mgr<list_ctrl, SOUND_OUT> CODEC_MGR;
	CODEC_MGR	codec_mgr_(list_ctrl_, sound_out_);

#ifdef USE_DAC
	typedef sound::dac_stream<device::R12DA, device::TPU0, device::DMAC0, SOUND_OUT> DAC_STREAM;
	DAC_STREAM	dac_stream_(sound_out_);

	void start_audio_()
	{
		uint8_t dmac_intl = 4;
		uint8_t tpu_intl  = 5;
		if(dac_stream_.start(48'000, dmac_intl, tpu_intl)) {
			utils::format("Start D/A Stream\n");
		} else {
			utils::format("D/A Stream Not start...\n");
		}
	}
#endif

#ifdef USE_SSIE
	typedef device::ssie_io<device::SSIE1, device::DMAC1, SOUND_OUT> SSIE_IO;
	SSIE_IO		ssie_io_(sound_out_);

	void start_audio_()
	{
		{  // SSIE 設定 RX72N Envision kit では、I2S, 48KHz, 32/16 ビットフォーマット固定
			uint8_t intr = 5;
			uint32_t aclk = 24'576'000;
			uint32_t lrclk = 48'000;
			auto ret = ssie_io_.start(aclk, lrclk, SSIE_IO::BFORM::I2S_32, intr);
			if(ret) {
				ssie_io_.enable_mute(false);
				ssie_io_.enable_send();  // 送信開始
				utils::format("SSIE Start: AUDIO_CLK: %u Hz, LRCLK: %u\n") % aclk % lrclk;
			} else {
				utils::format("SSIE Not start...\n");
			}
		}
	}
#endif

	void cmd_service_()
	{
		// コマンド入力と、コマンド解析
		if(!cmd_.service()) {
			return;
		}
		if(shell_.analize()) {
			return;
		}

		auto cmdn = cmd_.get_words();
		if(cmd_.cmp_word(0, "play")) {  // play [xxx]
			if(cmdn >= 2) {
				char tmp[FF_MAX_LFN + 1];
				cmd_.get_word(1, tmp, sizeof(tmp));
				if(std::strcmp(tmp, "*") == 0) {
					codec_mgr_.play("");
				} else {
					codec_mgr_.play(tmp);
				}
			} else {
				codec_mgr_.play("");
			}
		} else if(cmd_.cmp_word(0, "help") || cmd_.cmp_word(0, "?")) {
			shell_.help();
			utils::format("    play file-name\n");
		} else {
			utils::format("Command error: '%s'\n") % cmd_.get_command();
		}
	}
}

#ifdef USE_GLCDC
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
#endif

extern "C" {

	void set_sample_rate(uint32_t freq)
	{
//		utils::format("Change Sample rate: %u Hz\n") % freq;
#ifdef USE_DAC
		dac_stream_.set_sample_rate(freq);
#endif
#ifdef USE_SSIE
		sound_out_.set_input_rate(freq);
#endif
	}


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
		return 0;
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


	void codec_task_(void *pvParameters)
	{
		// オーディオの開始
		start_audio_();

		while(1) {
			if(name_t_.get_ != name_t_.put_) {
				if(strlen(name_t_.filename_) == 0) {
					codec_mgr_.play("");
				} else {
					if(std::strcmp(name_t_.filename_, "*") == 0) {
						codec_mgr_.play("");
					} else {
						codec_mgr_.play(name_t_.filename_);
					}
				}
				++name_t_.get_;
			}
			codec_mgr_.service();

			vTaskDelay(10 / portTICK_PERIOD_MS);
		}
	}


	void main_task_(void *pvParameters)
	{
		cmd_.set_prompt("# ");

		LED::DIR = 1;
#ifdef USE_GLCDC
		gui_.start();
		gui_.setup_touch_panel();
		gui_.open();  // 標準 GUI
		volatile uint32_t audio_t = audio_t_;
#endif
		while(1) {
#ifdef USE_GLCDC
			if(gui_.update(sdc_.get_mount(), codec_mgr_.get_state())) {
				// オーディオ・タスクに、ファイル名を送る。
				strncpy(name_t_.filename_, gui_.get_filename(), sizeof(name_t_.filename_));
				name_t_.put_++;
			}
			if(audio_t != audio_t_) {
				gui_.render_time(audio_t_);
				audio_t = audio_t_;
			}
			cmd_service_();
#else
			// GLCDC を使わない場合（コンソールのみ）
			auto n = cmt_.get_counter();
			while((n + 10) <= cmt_.get_counter()) {
				vTaskDelay(1 / portTICK_PERIOD_MS);
			}
			if(codec_mgr_.get_state() != sound::af_play::STATE::PLAY) {
				cmd_service_();
			}
#endif
			sdc_.service();
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
		sdc_.start();
	}

	utils::format("\r%s Start for Audio Sample\n") % system_str_;

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

