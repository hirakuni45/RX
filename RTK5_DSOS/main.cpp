//=====================================================================//
/*! @file
    @brief  RX65N デジタル・ストレージ・オシロスコープ @n
			マイコン内臓１２ビットＡ／Ｄ変換を使って、波形を観測するガジェット
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
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/spi_io2.hpp"
#include "common/sdc_man.hpp"
#include "common/tpu_io.hpp"
#include "common/qspi_io.hpp"
#include "sound/sound_out.hpp"
#include "sound/mp3_in.hpp"
#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/filer.hpp"

#include "chip/FAMIPAD.hpp"

#include "capture.hpp"

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

	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	typedef device::glcdc_io<device::GLCDC, 480, 272,
		device::glcdc_def::PIX_TYPE::RGB565> GLCDC_IO;
	GLCDC_IO	glcdc_io_;

	typedef device::drw2d_mgr<device::DRW2D, 480, 272> DRW2D_MGR;
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

	uint8_t		pad_level_;

//	utils::command<256> cmd_;

	bool check_mount_() {
		return sdc_.get_mount();
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


#if 0
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
#endif
}

extern "C" {

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
///		rtc_.get_time(t);
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
//	cmd_.set_prompt("# ");

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
		auto ver = drw2d_mgr_.get_version();
		utils::format("DRW2D Version: %04X\n") % ver;

		if(drw2d_mgr_.start(0x00000000)) {
			utils:: format("Start DRW2D\n");
		} else {
			utils:: format("DRW2D Fail\n");
		}
	}

	{  // QSPI の初期化（Flash Memory Read/Write Interface)
		if(!qspi_.start(1000000, QSPI::PHASE::TYPE1, QSPI::DLEN::W8)) {
			utils::format("QSPI not start.\n");
		}
	}

	{
		PAD_VCC::DIR = 1;
		PAD_VCC::P = 1;
		PAD_GND::DIR = 1;
		PAD_GND::P = 0;
		famipad_.start();
	}

	LED::DIR = 1;

	while(1) {
		glcdc_io_.sync_vpos();
		{
#if 0
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
			char path[256];
			if(filer_.update(ctrl, path, sizeof(path))) {
			}
#endif
		}

		sdc_.service(sdh_.service());

		update_led_();
//		command_();
	}
}
