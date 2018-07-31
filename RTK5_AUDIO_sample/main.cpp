//=====================================================================//
/*! @file
    @brief  RX65N オーディオファイル再生サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
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
#include "common/sdc_man.hpp"
#include "common/tpu_io.hpp"
#include "common/qspi_io.hpp"
#include "sound/sound_out.hpp"
#include "sound/mp3_in.hpp"
#include "sound/wav_in.hpp"
#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/filer.hpp"
#include "common/format.hpp"
#include "common/command.hpp"

#include "chip/FAMIPAD.hpp"
#include "chip/FT5206.hpp"

namespace {

	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;

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

	device::cmt_io<device::CMT0, utils::null_task>  cmt_;

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<device::SCI9, RECV_BUFF, SEND_BUFF> SCI;
	SCI		sci_;

	// カード電源制御は使わないので、「device::NULL_PORT」を指定する。
//	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;
	typedef device::NULL_PORT SDC_POWER;

#ifdef SDHI_IF
	// RX65N Envision Kit の SDHI ポートは、候補３になっている
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, device::port_map::option::THIRD> SDHI;
	SDHI	sdh_;
#else
	// Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORT2, device::bitpos::B2> MISO;  // DAT0
	typedef device::PORT<device::PORT2, device::bitpos::B0> MOSI;  // CMD
	typedef device::PORT<device::PORT2, device::bitpos::B1> SPCK;  // CLK

	typedef device::spi_io2<MISO, MOSI, SPCK> SPI;  ///< Soft SPI 定義

	SPI		spi_;

	typedef device::PORT<device::PORT1, device::bitpos::B7> SDC_SELECT;  // DAT3 カード選択信号
	typedef device::PORT<device::PORT2, device::bitpos::B5> SDC_DETECT;  // CD   カード検出

	typedef fatfs::mmc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> MMC;   // ハードウェアー定義

	MMC		sdh_(spi_, 20000000);
#endif
	typedef utils::sdc_man SDC;
	SDC		sdc_;

	utils::command<256> cmd_;

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

	typedef utils::sound_out<8192, 1024> SOUND_OUT;
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

	// GLCDC
	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	typedef device::glcdc_io<device::GLCDC, LCD_X, LCD_Y, device::PIX_TYPE::RGB565> GLCDC_IO;
	GLCDC_IO	glcdc_io_;

	// DRW2D
	typedef device::drw2d_mgr<device::DRW2D, LCD_X, LCD_Y> DRW2D_MGR;
	DRW2D_MGR	drw2d_mgr_;

	// QSPI B グループ
	typedef device::qspi_io<device::QSPI, device::port_map::option::SECOND> QSPI;
	QSPI		qspi_;

	typedef graphics::font8x16 AFONT;
	typedef graphics::kfont<16, 16, 64> KFONT;
	KFONT		kfont_;

	typedef graphics::render<uint16_t, 480, 272, AFONT, KFONT> RENDER;
	RENDER		render_(reinterpret_cast<uint16_t*>(0x00000000), kfont_);

	typedef graphics::filer<SDC, RENDER> FILER;
	FILER		filer_(sdc_, render_);

	typedef sound::mp3_in MP3_IN;
	MP3_IN		mp3_in_;
	typedef sound::wav_in WAV_IN;
	WAV_IN		wav_in_;

	uint8_t		pad_level_;

	// FT5206, SCI6 簡易 I2C 定義
	typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
	typedef utils::fixed_fifo<uint8_t, 64> RB6;
	typedef utils::fixed_fifo<uint8_t, 64> SB6;
	typedef device::sci_i2c_io<device::SCI6, RB6, SB6,
		device::port_map::option::FIRST_I2C> FT5206_I2C;

	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> FT5206;
	FT5206		ft5206_(ft5206_i2c_);


	bool check_mount_() {
		auto f = sdc_.get_mount();
		if(!f) {
			utils::format("SD card not mount.\n");
		}
		return f;
	}

	uint8_t		touch_num_ = 0;
	int16_t		touch_org_ = 0;

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
		ft5206_.update();

		auto ctrl = sound::af_play::CTRL::NONE;

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
			sdc_.stall_dir_list();
			render_.clear(RENDER::COLOR::Black);
		}

		update_led_();

		auto tnum = ft5206_.get_touch_num();
		const auto& xy = ft5206_.get_touch_pos(0);
		if(touch_num_ == 2 && tnum < 2) {  // pause（２点タッチが離された瞬間）
			ctrl = sound::af_play::CTRL::PAUSE;
			touch_org_ = xy.x;
		} else if(touch_num_ == 3 && tnum < 3) {  // Cancel Play（３点タッチが離れた瞬間）
			ctrl = sound::af_play::CTRL::STOP;
			sdc_.stall_dir_list();
			render_.clear(RENDER::COLOR::Black);
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

		return ctrl;
	}


	void sound_tag_task_(const sound::tag_t& tag)
	{
		render_.clear(RENDER::COLOR::Black);
		utils::format("Album:  '%s'\n") % tag.album_.c_str();
		render_.draw_text(0, 0 * 20, tag.album_.c_str());
		utils::format("Title:  '%s'\n") % tag.title_.c_str();
		render_.draw_text(0, 1 * 20, tag.title_.c_str());
		utils::format("Artist: '%s'\n") % tag.artist_.c_str();
		render_.draw_text(0, 2 * 20, tag.artist_.c_str());
		utils::format("Year:    %s\n") % tag.year_.c_str();
		render_.draw_text(0, 3 * 20, tag.year_.c_str());
		utils::format("Disc:    %s\n") % tag.disc_.c_str();
		auto x = render_.draw_text(0, 4 * 20, tag.disc_.c_str());
		if(x > 0) x += 8;
		utils::format("Track:   %s\n") % tag.track_.c_str();
		render_.draw_text(x, 4 * 20, tag.track_.c_str());
	}


	void sound_update_task_(uint32_t t)
	{
		uint16_t sec = t % 60;
		uint16_t min = (t / 60) % 60;
		uint16_t hor = (t / 3600) % 24;
		char tmp[16];
		utils::sformat("%02d:%02d:%02d", tmp, sizeof(tmp)) % hor % min % sec;
		render_.fill(0, 5 * 20, 8 * 8, 16, RENDER::COLOR::Black);
		render_.draw_text(0, 5 * 20, tmp);
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
				if(strcmp(ext, ".mp3") == 0) {
					play_mp3_(name);
				} else if(strcmp(ext, ".wav") == 0) {
					play_wav_(name);
				}
			}
		}
	}


	void play_loop_(const char* root, const char* start)
	{
		loop_t t;
		t.start = start;
		if(strlen(start) != 0) {
			t.enable = true;
		} else {
			t.enable = false;
		}
		sdc_.set_dir_list_limit(1);
		sdc_.start_dir_list(root, play_loop_func_, true, &t);
	}


	void command_()
	{
		if(!cmd_.service()) {
			return;
		}

		uint8_t cmdn = cmd_.get_words();
		if(cmdn >= 1) {
			bool f = false;
			if(cmd_.cmp_word(0, "dir")) {  // dir [xxx]
				if(check_mount_()) {
					if(cmdn >= 2) {
						char tmp[128];
						cmd_.get_word(1, sizeof(tmp), tmp);
						sdc_.dir(tmp);
					} else {
						sdc_.dir("");
					}
				}
				f = true;
			} else if(cmd_.cmp_word(0, "cd")) {  // cd [xxx]
				if(check_mount_()) {
					if(cmdn >= 2) {
						char tmp[128];
						cmd_.get_word(1, sizeof(tmp), tmp);
						sdc_.cd(tmp);						
					} else {
						sdc_.cd("/");
					}
				}
				f = true;
			} else if(cmd_.cmp_word(0, "pwd")) { // pwd
				utils::format("%s\n") % sdc_.get_current();
				f = true;
			} else if(cmd_.cmp_word(0, "play")) {
				if(cmdn >= 2) {
					char tmp[128];
					cmd_.get_word(1, sizeof(tmp), tmp);
					if(std::strcmp(tmp, "*") == 0) {
						play_loop_("", "");
					} else {
						play_mp3_(tmp);
					}
				} else {
					play_loop_("", "");
				}
				f = true;
			} else if(cmd_.cmp_word(0, "help")) {
				utils::format("    dir [path]\n");
				utils::format("    cd [path]\n");
				utils::format("    pwd\n");
				utils::format("    play [filename, *]\n");
				f = true;
			}
			if(!f) {
				char tmp[128];
				if(cmd_.get_word(0, sizeof(tmp), tmp)) {
					utils::format("Command error: '%s'\n") % tmp;
				}
			}
		}
	}
}

extern "C" {

	uint8_t get_fami_pad()
	{
		return famipad_.update();
	}


	void set_sample_rate(uint32_t freq)
	{
		uint8_t intr_level = 5;
		if(!tpu0_.start(freq, intr_level)) {
			utils::format("TPU0 start error...\n");
		}
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
		time_t t = 0;
		return utils::str::get_fattime(t);
	}


	// for syscalls API (POSIX API)
	void utf8_to_sjis(const char* src, char* dst, uint32_t len) {
		utils::str::utf8_to_sjis(src, dst, len);
	}


	int fatfs_get_mount() {
		return check_mount_();
	}


	int make_full_path(const char* src, char* dst, uint16_t len)
	{
		return sdc_.make_full_path(src, dst, len);
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	{  // タイマー設定（６０Ｈｚ）
		uint8_t cmt_irq_level = 4;
		cmt_.start(60, cmt_irq_level);
	}

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	{  // 内臓１２ビット D/A の設定
		bool amp_ena = true;
		dac_out_.start(DAC_OUT::output::CH0_CH1, amp_ena);
		dac_out_.out0(0x8000);
		dac_out_.out1(0x8000);
	}

	{  // SD カード・クラスの初期化
		sdh_.start();
		sdc_.start();
	}

	// 波形メモリーの無音状態初期化
	sound_out_.mute();

	{  // サンプリング・タイマー設定
		set_sample_rate(44100);
	}

	{  // DMAC マネージャー開始
		uint8_t intr_level = 4;
		auto ret = dmac_mgr_.start(tpu0_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
			reinterpret_cast<uint32_t>(sound_out_.get_wave()), DAC::DADR0.address(),
			sound_out_.size(), intr_level);
		if(!ret) {
			utils::format("DMAC Not start...\n");
		}
	}

	utils::format("RTK5RX65N Start for AUDIO sample\n");
	cmd_.set_prompt("# ");

	{  // QSPI の初期化（Flash Memory Read/Write Interface)
		if(!qspi_.start(1000000, QSPI::PHASE::TYPE1, QSPI::DLEN::W8)) {
			utils::format("QSPI not start.\n");
		}
	}

	{  // GLCDC の初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 0;  // DISP Disable
		LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
		if(glcdc_io_.start()) {
			utils::format("Start GLCDC\n");
			LCD_DISP::P  = 1;  // DISP Enable
			LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
			if(!glcdc_io_.control(GLCDC_IO::control_cmd::START_DISPLAY)) {
				utils::format("GLCDC ctrl fail...\n");
			}
		} else {
			utils::format("GLCDC Fail\n");
		}
	}

	{  // DRW2D 初期化
		auto ver = drw2d_mgr_.get_version();
		utils::format("DRW2D Version: %04X\n") % ver;

		if(drw2d_mgr_.start(0x00000000)) {
			utils:: format("Start DRW2D\n");
		} else {
			utils:: format("DRW2D Fail\n");
		}
	}

	{  // ファミコンパッド初期化
		PAD_VCC::DIR = 1;
		PAD_VCC::P = 1;
		PAD_GND::DIR = 1;
		PAD_GND::P = 0;
		famipad_.start();
	}

	{  // FT5206 touch screen controller
		FT5206::reset<FT5206_RESET>();
		uint8_t intr_lvl = 1;
		if(!ft5206_i2c_.start(FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
			utils::format("FT5206 I2C Start Fail...\n");
		}
		if(!ft5206_.start()) {
			utils::format("FT5206 Start Fail...\n");
		}
	}

	LED::DIR = 1;

	while(1) {
		glcdc_io_.sync_vpos();

		ft5206_.update();
		command_();

		{
			auto data = get_fami_pad();
			uint32_t ctrl = 0;
			if(chip::on(data, chip::FAMIPAD_ST::SELECT)) {
				graphics::set(graphics::filer_ctrl::OPEN, ctrl);
			}
			if(chip::on(data, chip::FAMIPAD_ST::UP)) {
				graphics::set(graphics::filer_ctrl::UP, ctrl);
			}
			if(chip::on(data, chip::FAMIPAD_ST::DOWN)) {
				graphics::set(graphics::filer_ctrl::DOWN, ctrl);
			}
			if(chip::on(data, chip::FAMIPAD_ST::LEFT)) {
				graphics::set(graphics::filer_ctrl::BACK, ctrl);
			}
			if(chip::on(data, chip::FAMIPAD_ST::RIGHT)) {
				graphics::set(graphics::filer_ctrl::SELECT, ctrl);
			}

			auto tnum = ft5206_.get_touch_num();
			const auto& xy = ft5206_.get_touch_pos(0);
			filer_.set_touch(tnum, xy.x, xy.y); 
			char path[256];
			if(filer_.update(ctrl, path, sizeof(path))) {
				glcdc_io_.sync_vpos();
				play_loop_("", path);
			}
		}

		sdc_.service(sdh_.service());

		update_led_();
	}
}
