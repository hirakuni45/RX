//=====================================================================//
/*! @file
    @brief  RX65N NESEMU @n
			・NES Emulator（NES Emulator のソースは GPL）@n
			・SD カードを使えるようにする必要がある。@n
			・オーディオとして、DA0、DA1 出力を繋ぐ必要がある。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/shell.hpp"
#include "common/spi_io2.hpp"
#include "common/tpu_io.hpp"
#include "sound/sound_out.hpp"
#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/font.hpp"
#include "graphics/graphics.hpp"
#include "graphics/filer.hpp"
#include "graphics/dialog.hpp"

#include "chip/FAMIPAD.hpp"

#include "nesemu.hpp"

namespace {

	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
// オーディオの D/A として使用
//	typedef device::PORT<device::PORT0, device::bitpos::B5> SW2;

	// Famicon PAD (CMOS 4021B Shift Register)
	// 電源は、微小なので、接続を簡単に行う為、ポートを使う
	typedef device::PORT<device::PORT6, device::bitpos::B0> PAD_VCC;
	typedef device::PORT<device::PORT6, device::bitpos::B1> PAD_GND;
	typedef device::PORT<device::PORT6, device::bitpos::B2> PAD_P_S;
	typedef device::PORT<device::PORT6, device::bitpos::B5> PAD_CLK;
	typedef device::PORT<device::PORT7, device::bitpos::B3> PAD_OUT;
	typedef chip::FAMIPAD<PAD_P_S, PAD_CLK, PAD_OUT> FAMIPAD;
	FAMIPAD		famipad_;

	typedef device::system_io<12000000> SYSTEM_IO;

	typedef utils::fixed_fifo<char, 256> RECV_BUFF;
	typedef utils::fixed_fifo<char, 256> SEND_BUFF;
	typedef device::sci_io<device::SCI9, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	static const uint16_t LCD_X = 480;
	static const uint16_t LCD_Y = 272;
	static const graphics::pixel::TYPE PIX = graphics::pixel::TYPE::RGB565;
	static void* LCD_ORG = reinterpret_cast<void*>(0x00000100);
	typedef device::glcdc_io<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC_IO;
	GLCDC_IO	glcdc_io_(nullptr, LCD_ORG);

	// カード電源制御は使わない場合、「device::NULL_PORT」を指定する。
//	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;
	typedef device::NULL_PORT SDC_POWER;

#ifdef SDHI_IF
	// RX65N Envision Kit の SDHI ポートは、候補３になっている
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, device::port_map::option::THIRD> SDHI;
	SDHI		sdh_;
#else
	// Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORT2, device::bitpos::B2> MISO;  // DAT0
	typedef device::PORT<device::PORT2, device::bitpos::B0> MOSI;  // CMD
	typedef device::PORT<device::PORT2, device::bitpos::B1> SPCK;  // CLK

	typedef device::spi_io2<MISO, MOSI, SPCK> SPI;  ///< Soft SPI 定義

	SPI			spi_;

	typedef device::PORT<device::PORT1, device::bitpos::B7> SDC_SELECT;  // DAT3 カード選択信号
	typedef device::PORT<device::PORT2, device::bitpos::B5> SDC_DETECT;  // CD   カード検出

	typedef fatfs::mmc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> MMC;   // ハードウェアー定義

	MMC			sdh_(spi_, 35000000);
#endif

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

	typedef utils::sound_out<1024, 512> SOUND_OUT;
	SOUND_OUT	sound_out_;

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

	typedef graphics::font8x16 AFONT;
	AFONT		afont_;
	typedef graphics::kfont<16, 16> KFONT;
	KFONT		kfont_;
	typedef graphics::font<AFONT, KFONT> FONT;
	FONT		font_(afont_, kfont_);

	typedef graphics::render<GLCDC_IO, FONT> RENDER;
	RENDER		render_(glcdc_io_, font_);

	typedef gui::dialog<RENDER, FAMIPAD> DIALOG;
	DIALOG		dialog_(render_, famipad_);

	typedef gui::filer<RENDER> FILER;
	FILER		filer_(render_);

	time_t		rtc_time_ = 0;

	emu::nesemu	nesemu_;

	typedef utils::command<256> CMD;
	CMD			cmd_;
	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);

	uint8_t		fami_pad_data_;
	bool		monitor_ = false;

	void command_()
	{
		if(!cmd_.service()) {
			return;
		}

		if(shell_.analize()) {
			return;
		}

		if(monitor_) {
			auto n = cmd_.get_words();
			if(n == 0) return;
			if(cmd_.cmp_word(0, "exit")) {
				cmd_.set_prompt("# ");
				monitor_ = false;
			} else {
				nesemu_.monitor(cmd_.get_command());
			}
			return;
		}

		auto cmdn = cmd_.get_words();
		if(cmdn == 0) return;

		if(cmd_.cmp_word(0, "nes")) {
			if(cmdn >= 2) {
				char tmp[FF_MAX_LFN + 1];
				cmd_.get_word(1, tmp, sizeof(tmp));
				if(!nesemu_.open(tmp)) {
					utils::format("Open error: '%s'\n") % tmp;
				}
			}
		} else if(cmd_.cmp_word(0, "reset")) {
			nesemu_.reset();
		} else if(cmd_.cmp_word(0, "pause")) {
			nesemu_.enable_pause(!nesemu_.get_pause());
		} else if(cmd_.cmp_word(0, "save")) {
			int slot = 0;
			if(cmdn >= 2) {
				char tmp[32];
				cmd_.get_word(1, tmp, sizeof(tmp));
				utils::input("%d", tmp) % slot;
			}
			if(!nesemu_.save_state(slot)) {
				utils::format("Save state error: slot = %d\n") % slot;
			}
		} else if(cmd_.cmp_word(0, "load")) {
			int slot = 0;
			if(cmdn >= 2) {
				char tmp[32];
				cmd_.get_word(1, tmp, sizeof(tmp));
				utils::input("%d", tmp) % slot;
			}
			if(!nesemu_.load_state(slot)) {
				utils::format("Load state error: slot = %d\n") % slot;
			}
		} else if(cmd_.cmp_word(0, "info")) {
			const char* str = nesemu_.get_info();
			utils::format("%s\n") % str;
		} else if(cmd_.cmp_word(0, "call-151")) {
			if(nesemu_.probe()) {
				cmd_.set_prompt("$");
				monitor_ = true;
			} else {
				utils::format("Not Ready To Cartridge (NESEMU)\n");
			}
		} else if(cmd_.cmp_word(0, "help")) {
			shell_.help();
			utils::format("    nes filename\n");
			utils::format("    pause\n");
			utils::format("    reset\n");
			utils::format("    save [slot-no]\n");
			utils::format("    load [slot-no]\n");
			utils::format("    info\n");
			utils::format("    call-151\n");
		} else {
			utils::format("Command error: '%s'\n") % cmd_.get_command();
		}
	}

	void update_nesemu_()
	{
		nesemu_.service(LCD_ORG, GLCDC_IO::width, GLCDC_IO::height);

		uint32_t len = nesemu_.get_audio_len();
		const uint16_t* wav = nesemu_.get_audio_buf();
		for(uint32_t i = 0; i < len; ++i) {
			while((sound_out_.at_fifo().size() - sound_out_.at_fifo().length()) < 8) {
			}
			sound::wave_t t;
			t.l_ch = t.r_ch = *wav++;
			sound_out_.at_fifo().put(t);
		}
	}
}


extern "C" {

	uint8_t get_fami_pad()
	{
		return fami_pad_data_;
	}


	void set_sample_rate(uint32_t freq)
	{
		uint8_t intr_level = 5;
		if(!tpu0_.start(freq, intr_level)) {
			utils::format("TPU0 start error...\n");
		}
	}


    int emu_log(const char* text)
    {
		sci_puts(text);
        return 0;
    }


	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}


	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}


	char sci_getch(void)
	{
		return sci_.getch();
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
//		time_t t = 0;
//		rtc_.get_time(t);
		return utils::str::get_fattime(rtc_time_);
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	{  // 内臓１２ビット D/A の設定
		bool amp_ena = true;
		dac_out_.start(DAC_OUT::output::CH0_CH1, amp_ena);
		dac_out_.out0(0x8000);
		dac_out_.out1(0x8000);
	}

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	{  // 時計の初期時刻(2019/9/1 12:00:00)
		struct tm m;
		m.tm_year = 2019 - 1900;
		m.tm_mon  = 9 - 1;
		m.tm_mday = 1;
		m.tm_hour = 12;
		m.tm_min  = 0;
		m.tm_sec  = 0;
		rtc_time_ = mktime(&m);
	}

	{  // SD カード・クラスの初期化
		sdh_.start();
	}

	// 波形メモリーの無音状態初期化
	sound_out_.mute();

	{  // サンプリング・タイマー設定（初期 22.05KHz ）
		set_sample_rate(22050);
	}

	{  // サウンドストリーム DMAC マネージャー開始
		uint8_t intr_level = 4;
		bool cpu_intr = true;
		auto ret = dmac_mgr_.start(tpu0_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
			reinterpret_cast<uint32_t>(sound_out_.get_wave()), DAC::DADR0.address(),
			sound_out_.size(), intr_level, cpu_intr);
		if(!ret) {
			utils::format("DMAC Not start...\n");
		}
	}

	utils::format("\rRTK5RX65N Start for NES Emulator\n");
	cmd_.set_prompt("# ");

	{  // GLCDC 初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 0;  // DISP Disable
		LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
		if(glcdc_io_.start()) {
			utils::format("Start GLCDC\n");
			LCD_DISP::P  = 1;  // DISP Enable
			LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
			if(!glcdc_io_.control(GLCDC_IO::CONTROL_CMD::START_DISPLAY)) {
				utils::format("GLCDC Ctrl Fail\n");
			}
		} else {
			utils::format("GLCDC Fail\n");
		}
	}

	LED::DIR = 1;

	{
		PAD_VCC::DIR = 1;
		PAD_VCC::P = 1;
		PAD_GND::DIR = 1;
		PAD_GND::P = 0;
		bool pullup = true;
		famipad_.start(pullup);
	}

	nesemu_.start();

	uint8_t n = 0;
	uint8_t flt = 0;
	uint8_t	sec = 0;
	bool filer = false;
	bool mount = sdh_.get_mount();
	while(1) {
		render_.sync_frame();
		fami_pad_data_ = famipad_.update();

		uint8_t data = fami_pad_data_;
		if(chip::on(data, chip::FAMIPAD_ST::SELECT) && chip::on(data, chip::FAMIPAD_ST::START)) {
			++flt;
		} else {
			flt = 0;
		}

		bool m = sdh_.get_mount();
		uint32_t ctrl = 0;
		if(m) {
			gui::set(gui::filer_ctrl::MOUNT, ctrl);
		}
		if(flt >= 120) {
			sound_out_.mute();
			gui::set(gui::filer_ctrl::OPEN, ctrl);
			filer = true;
			flt = 0;
		}

		{
			if(!mount && m) {
				render_.set_fore_color(graphics::def_color::Black);
				render_.fill_box(vtx::srect(480-24, 0, 24, 16));
			}
			if(mount && !m) {
				render_.set_fore_color(graphics::def_color::White);
				render_.draw_text(vtx::spos(480-24, 0), "?SD");
				filer = false;
			}
			mount = m;
		}

		if(filer) {
			if(chip::on(data, chip::FAMIPAD_ST::B)) {
				gui::set(gui::filer_ctrl::CLOSE, ctrl);
				filer = false;
			}
			if(chip::on(data, chip::FAMIPAD_ST::A)) {
				gui::set(gui::filer_ctrl::INFO, ctrl);
			}
			if(chip::on(data, chip::FAMIPAD_ST::UP)) {
				gui::set(gui::filer_ctrl::UP, ctrl);
			}
			if(chip::on(data, chip::FAMIPAD_ST::DOWN)) {
				gui::set(gui::filer_ctrl::DOWN, ctrl);
			}
			if(chip::on(data, chip::FAMIPAD_ST::LEFT)) {
				gui::set(gui::filer_ctrl::BACK, ctrl);
			}
			if(chip::on(data, chip::FAMIPAD_ST::RIGHT)) {
				gui::set(gui::filer_ctrl::SELECT, ctrl);
			}
			char path[256];
			if(filer_.update(ctrl, path, sizeof(path))) {
				char tmp[256];
				utils::file_io::make_full_path(path, tmp, sizeof(tmp));
				nesemu_.close();
				if(nesemu_.open(tmp)) {
					filer = false;
				} else {
					dialog_.modal(vtx::spos(400, 80), "Not NES file");
				}
			}
		} else {
			update_nesemu_();
		}

		sdh_.service();

		command_();

		++n;
		if(n >= 30) {
			n = 0;
		}
		if(n < 10) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
		++sec;
		if(sec >= 60) {
			sec = 0;
			++rtc_time_;
		}
	}
}
