//=====================================================================//
/*! @file
    @brief  RX65N/RX72N Envision Kit NES Emulator @n
			・NES Emulator のソース、ライセンスは GPL @n
			・(RX65N) SD カードを使えるようにする必要がある。@n
			・(RX65N) オーディオとして、DA0、DA1 出力を繋ぐ必要がある。@n
			・ファミコン互換パッドを繋ぐ必要がある。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/shell.hpp"
#include "sound/dac_stream.hpp"
#include "sound/sound_out.hpp"
#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/font.hpp"
#include "graphics/graphics.hpp"
#include "graphics/filer.hpp"
#include "graphics/dialog.hpp"
#include "graphics/root_menu.hpp"

#include "chip/FAMIPAD.hpp"

#include "nesemu.hpp"

namespace {

#if defined(SIG_RX65N)

	static const char* sys_msg_ = { "RX65N Envision Kit" };

	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;

	static const uint32_t AUDIO_SAMPLE_RATE = 22'050;

	// Famicon PAD (CMOS 4021B Shift Register)
	// 電源は、微小なので、接続を簡単に行う為、ポート出力を使う
	typedef device::PORT<device::PORT6, device::bitpos::B0> PAD_VCC;
	typedef device::PORT<device::PORT6, device::bitpos::B1> PAD_GND;
	typedef device::PORT<device::PORT6, device::bitpos::B2> PAD_P_S;
	typedef device::PORT<device::PORT6, device::bitpos::B5> PAD_CLK;
	typedef device::PORT<device::PORT7, device::bitpos::B3> PAD_OUT;
	typedef chip::FAMIPAD<PAD_P_S, PAD_CLK, PAD_OUT> FAMIPAD;

	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	// フレームバッファ開始アドレスは、100 番地から開始とする。
	// ※０～ＦＦは未使用領域
	static void* LCD_ORG = reinterpret_cast<void*>(0x00000100);

	// カード電源制御を使わない場合、「device::NULL_PORT」を指定する。
	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;
	// 書き込み禁止は使わない
	typedef device::NULL_PORT SDC_WP;

	// マスターバッファはでサービスできる時間間隔を考えて余裕のあるサイズとする（8192）
	// DMAC でループ転送できる最大数の２倍（1024）
	typedef sound::sound_out<int16_t, 8192, 1024> SOUND_OUT;

	#define USE_DAC

#elif defined(SIG_RX72N)

	static const char* sys_msg_ = { "RX72N Envision Kit" };

	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;

	static const uint32_t AUDIO_SAMPLE_RATE = 48'000;

	// Famicon PAD (CMOS 4021B Shift Register)
	// RX72N では、Pmod1 に接続する。
	// PMOD1                                                PAD_3V3:     Pmod1-6
	// PMOD1                                                PAD_GND:     Pmod1-5 
	typedef device::PORT<device::PORT5, device::bitpos::B1> PAD_P_S;  // Pmod1-4
	typedef device::PORT<device::PORT5, device::bitpos::B2> PAD_CLK;  // Pmod1-3
	typedef device::PORT<device::PORT5, device::bitpos::B0> PAD_OUT;  // Pmod1-2
	typedef chip::FAMIPAD<PAD_P_S, PAD_CLK, PAD_OUT, 40> FAMIPAD;

	// GLCDC の制御関係
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	static void* LCD_ORG = reinterpret_cast<void*>(0x0080'0000);

	// SD-CARD の制御関係
	typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;
	// 書き込み禁止は使わない
	typedef device::NULL_PORT SDC_WP;

	// マスターバッファはサービスできる時間間隔を考えて余裕のあるサイズとする（2048）
	// SSIE の FIFO サイズの２倍以上（256）
	typedef sound::sound_out<int16_t, 2048, 256> SOUND_OUT;

	#define USE_SSIE

#endif

	FAMIPAD		famipad_;

	typedef utils::fixed_fifo<char, 256> RECV_BUFF;
	typedef utils::fixed_fifo<char, 512> SEND_BUFF;
	typedef device::sci_io<SCI_CH, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

	static const uint16_t LCD_X = 480;
	static const uint16_t LCD_Y = 272;
	static const graphics::pixel::TYPE PIX = graphics::pixel::TYPE::RGB565;
	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC_MGR;
	GLCDC_MGR	glcdc_mgr_(nullptr, LCD_ORG);

	// RX65N/RX72N Envision Kit の SDHI は、候補３になっている
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::option::THIRD> SDHI;
	SDHI		sdh_;

	// サウンド出力コンテキスト
	SOUND_OUT	sound_out_;

	typedef emu::nesemu<AUDIO_SAMPLE_RATE> NESEMU;

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
		{  // SSIE 設定 RX72N Envision kit では、I2S, 48KHz, 32/24 ビットフォーマット固定
			uint8_t intr = 5;
			uint32_t aclk = 24'576'000;
			uint32_t lrclk = 48'000;
			auto ret = ssie_io_.start(aclk, lrclk, SSIE_IO::BFORM::I2S_32, intr);
			if(ret) {
				ssie_io_.enable_mute(false);
				ssie_io_.enable_send();  // 送信開始
				utils::format("SSIE Start: AUDIO_CLK: %uHz, LRCLK: %uHz\n") % aclk % lrclk;
			} else {
				utils::format("SSIE Not start...\n");
			}
		}
	}
#endif

	typedef graphics::font8x16 AFONT;
	AFONT		afont_;
	typedef graphics::kfont<16, 16> KFONT;
	KFONT		kfont_;
	typedef graphics::font<AFONT, KFONT> FONT;
	FONT		font_(afont_, kfont_);

	typedef graphics::render<GLCDC_MGR, FONT> RENDER;
	RENDER		render_(glcdc_mgr_, font_);

	typedef gui::dialog<RENDER, FAMIPAD> DIALOG;
	DIALOG		dialog_(render_, famipad_);

	typedef gui::filer<RENDER> FILER;
	FILER		filer_(render_);

	typedef gui::back_btn<RENDER> BACK_BTN;
	typedef gui::root_menu<RENDER, BACK_BTN, 5> ROOTM;

	BACK_BTN	back_btn_(render_);
	ROOTM		rootm_(render_, back_btn_);

	// RX65N/RX72N Envision Kit では、内臓 RTC は利用出来ない為、簡易的な時計を用意する。
	time_t		rtc_time_ = 0;

	NESEMU		nesemu_;

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
			utils::format("    nes filename    Emulations for NES\n");
			utils::format("    pause           Pause Emulation (toggle)\n");
			utils::format("    reset           Reset NES Machine\n");
			utils::format("    save [slot-no]  Save NES State (slot-no:0 to 9)\n");
			utils::format("    load [slot-no]  Load NES State (slot-no:0 to 9)\n");
			utils::format("    info            Cartrige Infomations\n");
			utils::format("    call-151        Goto Monitor\n");
		} else {
			utils::format("Command error: '%s'\n") % cmd_.get_command();
		}
	}


	void update_nesemu_()
	{
		nesemu_.service(LCD_ORG, GLCDC_MGR::width, GLCDC_MGR::height);

		uint32_t len = nesemu_.get_audio_len();
		const uint16_t* wav = nesemu_.get_audio_buf();
		for(uint32_t i = 0; i < len; ++i) {
			while((sound_out_.at_fifo().size() - sound_out_.at_fifo().length()) < 8) {
			}
			typename SOUND_OUT::WAVE t;
			t.l_ch = t.r_ch = *wav++;
			sound_out_.at_fifo().put(t);
		}
	}


	void make_state_str_(int slot) {
		static char tmp1[16];
		utils::sformat("Load State %d", tmp1, sizeof(tmp1)) % slot;
		rootm_.set(1, tmp1);
		static char tmp2[16];
		utils::sformat("Save State %d", tmp2, sizeof(tmp2)) % slot;
		rootm_.set(2, tmp2);
	}
}


extern "C" {

	uint8_t get_fami_pad()
	{
		return fami_pad_data_;
	}


	void set_sample_rate(uint32_t freq)
	{
#ifdef USE_DAC
		dac_stream_.set_sample_rate(freq);
#endif
#ifdef USE_SSIE
		sound_out_.set_output_rate(freq);
#endif
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

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	{  // 時計の初期時刻(2020/4/1 12:00:00)
		struct tm m;
		m.tm_year = 2020 - 1900;
		m.tm_mon  = 4 - 1;
		m.tm_mday = 1;
		m.tm_hour = 12;
		m.tm_min  = 0;
		m.tm_sec  = 0;
		rtc_time_ = mktime(&m);
	}

	{  // SD カード・クラスの初期化
		sdh_.start();
	}

	start_audio_();

	utils::format("\r%s Start for NES Emulator\n") % sys_msg_;
	cmd_.set_prompt("# ");

	{  // GLCDC 初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 0;  // DISP Disable
		LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
		if(glcdc_mgr_.start()) {
			utils::format("Start GLCDC\n");
			LCD_DISP::P  = 1;  // DISP Enable
			LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
			if(!glcdc_mgr_.control(GLCDC_MGR::CONTROL_CMD::START_DISPLAY)) {
				utils::format("GLCDC Ctrl Fail\n");
			}
		} else {
			utils::format("GLCDC Fail\n");
		}
	}

	{  // サンプリング・タイマー周期設定
		set_sample_rate(AUDIO_SAMPLE_RATE);
	}

	LED::DIR = 1;

	{
#if defined( SIG_RX65N)
		PAD_VCC::DIR = 1;
		PAD_VCC::P = 1;
		PAD_GND::DIR = 1;
		PAD_GND::P = 0;
#endif
		bool pullup = true;
		famipad_.start(pullup);
	}

	nesemu_.start();

	// メニューの設定
	rootm_.clear();
	rootm_.set_gap(20);
	rootm_.set_space(vtx::spos(12, 8));
	rootm_.add("Select NES File");
	rootm_.add("Load State 0");
	rootm_.add("Save State 0");
	rootm_.add("Reset");
	rootm_.add("Close Menu");

	uint8_t n = 0;
	uint8_t flt = 0;
	uint8_t	sec = 0;
	uint8_t lvl = 0;
	uint8_t trg = 0;
	uint8_t slot = 0;
	bool menu = false;
	bool filer = false;
	bool mount = sdh_.get_mount();
	bool error = false;
	while(1) {
		render_.sync_frame();
		fami_pad_data_ = famipad_.update();

		trg = fami_pad_data_ & ~lvl;
		lvl = fami_pad_data_;

		if(chip::on(lvl, chip::FAMIPAD_ST::SELECT) && chip::on(lvl, chip::FAMIPAD_ST::START)) {
			++flt;
		} else {
			flt = 0;
		}

		bool m = sdh_.get_mount();
		uint32_t ctrl = 0;
		if(m) {
			gui::set(gui::filer_ctrl::MOUNT, ctrl);
		}
		if(!menu && flt >= 120) {
			flt = 0;
			sound_out_.mute();
			menu = true;
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

		if(menu) {
			render_.clear(graphics::def_color::Black);

			if(chip::on(trg, chip::FAMIPAD_ST::UP)) {
				rootm_.prev_focus();
			}
			if(chip::on(trg, chip::FAMIPAD_ST::DOWN)) {
				rootm_.next_focus();
			}

			auto idx = rootm_.get_pos();
			if(idx == 1 || idx == 2) {
				if(chip::on(trg, chip::FAMIPAD_ST::LEFT)) {
					if(slot > 0) slot--;
				}
				if(chip::on(trg, chip::FAMIPAD_ST::RIGHT)) {
					if(slot < 9) ++slot;
				}
			}

			make_state_str_(slot);

			auto pos = rootm_.get_org(idx);
			rootm_.render(pos, true);

			if(chip::on(trg, chip::FAMIPAD_ST::A)) {
				switch(idx) {
				case 0:
					gui::set(gui::filer_ctrl::OPEN, ctrl);
					filer = true;
					break;
				case 1:
					if(!nesemu_.load_state(slot)) {
						dialog_.modal(vtx::spos(400, 80), "Load state error");
						error = true;
					}
					break;
				case 2:
					if(!nesemu_.save_state(slot)) {
						dialog_.modal(vtx::spos(400, 80), "Save state error");
						error = true;
					}
					break;
				case 3:
					nesemu_.reset();
					break;
				case 4:
					break;
				}
				fami_pad_data_ = 0;
				render_.clear(graphics::def_color::Black);
				menu = false;
			}
		}

		if(filer) {
			if(chip::on(lvl, chip::FAMIPAD_ST::B)) {
				gui::set(gui::filer_ctrl::CLOSE, ctrl);
				filer = false;
			}
			if(chip::on(lvl, chip::FAMIPAD_ST::A)) {
				gui::set(gui::filer_ctrl::INFO, ctrl);
			}
			if(chip::on(lvl, chip::FAMIPAD_ST::UP)) {
				gui::set(gui::filer_ctrl::UP, ctrl);
			}
			if(chip::on(lvl, chip::FAMIPAD_ST::DOWN)) {
				gui::set(gui::filer_ctrl::DOWN, ctrl);
			}
			if(chip::on(lvl, chip::FAMIPAD_ST::LEFT)) {
				gui::set(gui::filer_ctrl::BACK, ctrl);
			}
			if(chip::on(lvl, chip::FAMIPAD_ST::RIGHT)) {
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
					error = true;
				}
			}
		}

		if(error) {
			if(chip::on(trg, chip::FAMIPAD_ST::A) || chip::on(trg, chip::FAMIPAD_ST::B)) {
				render_.clear(graphics::def_color::Black);
				error = false;
				fami_pad_data_ = 0;
			}
		}

		if(!menu && !filer && !error) {
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
