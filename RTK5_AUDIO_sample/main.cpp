//=====================================================================//
/*! @file
    @brief  RX65N オーディオファイル再生サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/sci_i2c_io.hpp"
#include "common/spi_io2.hpp"
#include "common/sdc_man.hpp"
#include "common/tpu_io.hpp"
#include "common/qspi_io.hpp"
#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/filer.hpp"
#include "graphics/dialog.hpp"
#include "common/format.hpp"
#include "common/command.hpp"

#include "chip/FAMIPAD.hpp"
#include "chip/FT5206.hpp"

#include "audio_codec.hpp"

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

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<device::SCI9, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

	// カード電源制御は使わないので、「device::NULL_PORT」を指定する。
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
	typedef utils::sdc_man SDC;
	SDC			sdc_;

	utils::command<256> cmd_;

	// GLCDC
	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	static void* LCD_ORG = reinterpret_cast<void*>(0x00000100);
	static const auto PIX = graphics::pixel::TYPE::RGB565;
	typedef device::glcdc_io<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC_IO;
	GLCDC_IO	glcdc_io_(nullptr, LCD_ORG);

	typedef graphics::font8x16 AFONT;
	AFONT		afont_;
//  for cash into SD card /kfont16.bin
//	typedef graphics::kfont<16, 16, 64> KFONT;
	typedef graphics::kfont<16, 16> KFONT;
	KFONT		kfont_;
	typedef graphics::font<AFONT, KFONT> FONT;
	FONT		font_(afont_, kfont_);

//	typedef device::drw2d_mgr<GLCDC_IO, FONT> RENDER;
	typedef graphics::render<GLCDC_IO, FONT> RENDER;
	RENDER		render_(glcdc_io_, font_);

	typedef graphics::def_color DEF_COLOR;

	// FT5206, SCI6 簡易 I2C 定義
	typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
	typedef utils::fixed_fifo<uint8_t, 64> RB6;
	typedef utils::fixed_fifo<uint8_t, 64> SB6;
	typedef device::sci_i2c_io<device::SCI6, RB6, SB6,
		device::port_map::option::FIRST_I2C> FT5206_I2C;

	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> FT5206;
	FT5206		ft5206_(ft5206_i2c_);
	// INT to P02(IRQ10)

	typedef gui::dialog<RENDER, FT5206> DIALOG;
	DIALOG		dialog_(render_, ft5206_); 

	// QSPI B グループ
	typedef device::qspi_io<device::QSPI, device::port_map::option::SECOND> QSPI;
	QSPI		qspi_;

	typedef gui::filer<RENDER, SDC> FILER;
	FILER		filer_(render_, sdc_);

	typedef audio::codec<RENDER, SDC> AUDIO;
	AUDIO		audio_(render_, sdc_);

	uint8_t		pad_level_ = 0;
	uint8_t		touch_num_ = 0;
	int16_t		touch_org_ = 0;


	bool check_mount_() {
		auto f = sdc_.get_mount();
		if(!f) {
			utils::format("SD card not mount.\n");
		}
		return f;
	}


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
			render_.clear(DEF_COLOR::Black);
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

		return ctrl;
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
						cmd_.get_word(1, tmp, sizeof(tmp));
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
						cmd_.get_word(1, tmp, sizeof(tmp));
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
					cmd_.get_word(1, tmp, sizeof(tmp));
					if(std::strcmp(tmp, "*") == 0) {
						audio_.play_loop("", "");
					} else {
						audio_.play_file(tmp);
					}
				} else {
					audio_.play_loop("", "");
				}
				f = true;
			} else if(cmd_.cmp_word(0, "jpeg")) {
				if(cmdn >= 2) {
					char tmp[128];
					cmd_.get_word(1, tmp, sizeof(tmp));
					audio_.at_scaling().set_offset();
					audio_.at_scaling().set_scale();
					if(!audio_.at_jpeg_in().load(tmp)) {
						utils::format("Can't load JPEG file: '%s'\n") % tmp;
					}
				}
				f = true;
			} else if(cmd_.cmp_word(0, "help")) {
				utils::format("    dir [path]\n");
				utils::format("    cd [path]\n");
				utils::format("    pwd\n");
				utils::format("    play [filename, *]\n");
				utils::format("    jpeg [filename]\n");
				f = true;
			}
			if(!f) {
				char tmp[128];
				if(cmd_.get_word(0, tmp, sizeof(tmp))) {
					utils::format("Command error: '%s'\n") % tmp;
				}
			}
		}
	}
}


extern "C" {

	void set_sample_rate(uint32_t freq)
	{
		audio_.set_sample_rate(freq);
	}


	uint8_t get_fami_pad()
	{
		return famipad_.update();
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

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	{  // SD カード・クラスの初期化
		sdh_.start();
		sdc_.start();
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
			if(!glcdc_io_.control(GLCDC_IO::CONTROL_CMD::START_DISPLAY)) {
				utils::format("GLCDC ctrl fail...\n");
			}
		} else {
			utils::format("GLCDC Fail\n");
		}
	}

	{  // DRW2D 初期化
		auto ver = render_.get_version();
		utils::format("DRW2D Version: %04X\n") % ver;
		if(render_.start()) {
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

	// オーディオの開始
	{
		audio_.set_ctrl_task(sound_ctrl_task_);
		audio_.start();
	}

#if 1
	// タッチパネルの安定待ち
	{
		render_.sync_frame();
		dialog_.modal(vtx::spos(400, 60),
			"Touch panel device wait...\nPlease touch it with some screen.");
		uint8_t nnn = 0;
		while(1) {
			render_.sync_frame();
			ft5206_.update();
			auto num = ft5206_.get_touch_num();
			if(num == 0) {
				++nnn;
				if(nnn >= 60) break;
			} else {
				nnn = 0;
			}
			update_led_();
		}
	}
#endif

	while(1) {
		render_.sync_frame();

		ft5206_.update();
		command_();

		{
			auto data = get_fami_pad();
			uint32_t ctrl = 0;
			if(chip::on(data, chip::FAMIPAD_ST::SELECT)) {
				gui::set(gui::filer_ctrl::OPEN, ctrl);
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

			auto tnum = ft5206_.get_touch_num();
			const auto& xy = ft5206_.get_touch_pos(0);
			filer_.set_touch(tnum, xy.x, xy.y); 
			char path[256];
			if(filer_.update(ctrl, path, sizeof(path))) {
				render_.sync_frame();
				audio_.play_loop("", path);
			}
		}

		sdc_.service(sdh_.service());

		update_led_();
	}
}
