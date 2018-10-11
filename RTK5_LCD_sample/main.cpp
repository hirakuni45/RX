//=====================================================================//
/*! @file
    @brief  RX65N ＬＣＤサンプル
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
#include "common/spi_io2.hpp"
#include "common/sdc_man.hpp"
#include "common/qspi_io.hpp"
#include "graphics/font8x16.hpp"

#define CASH_KFONT
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/jpeg_in.hpp"
#include "graphics/bmp_in.hpp"
#include "chip/FT5206.hpp"

// #define SOFT_I2C

#ifdef SOFT_I2C
#include "common/si2c_io.hpp"
#else
#include "common/sci_i2c_io.hpp"
#endif

namespace {

	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B5> SW2;

	typedef device::system_io<12000000> SYSTEM_IO;

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<device::SCI9, RECV_BUFF, SEND_BUFF> SCI;
	SCI		sci_;

	// ＳＤカード電源制御は使わない場合、「device::NULL_PORT」を指定する。
//	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;
	typedef device::NULL_PORT SDC_POWER;

#ifdef SDHI_IF
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER> SDHI;
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

	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	typedef device::glcdc_io<device::GLCDC, LCD_X, LCD_Y,
		device::glcdc_def::PIX_TYPE::RGB565> GLCDC_IO;
//		device::glcdc_def::PIX_TYPE::CLUT8> GLCDC_IO;
	GLCDC_IO	glcdc_io_;

	// QSPI B グループ
	typedef device::qspi_io<device::QSPI, device::port_map::option::SECOND> QSPI;
	QSPI		qspi_;

	typedef device::drw2d_mgr<device::DRW2D, LCD_X, LCD_Y> DRW2D_MGR;
	DRW2D_MGR	drw2d_mgr_;

	typedef graphics::font8x16 AFONT;
	typedef graphics::kfont<16, 16, 64> KFONT;
	KFONT		kfont_;

	typedef graphics::render<uint16_t, LCD_X, LCD_Y, AFONT, KFONT> RENDER;
	RENDER		render_(reinterpret_cast<uint16_t*>(0x00000000), kfont_);

	// FT5206, SCI6 簡易 I2C 定義
	typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
#ifdef SOFT_I2C
	typedef device::PORT<device::PORT0, device::bitpos::B0> FT5206_SDA;
	typedef device::PORT<device::PORT0, device::bitpos::B1> FT5206_SCL;
	typedef device::si2c_io<FT5206_SDA, FT5206_SCL> FT5206_I2C;
#else
	typedef utils::fixed_fifo<uint8_t, 64> RECV6_BUFF;
	typedef utils::fixed_fifo<uint8_t, 64> SEND6_BUFF;
	typedef device::sci_i2c_io<device::SCI6, RECV6_BUFF, SEND6_BUFF,
			device::port_map::option::FIRST_I2C> FT5206_I2C;
#endif
	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> FT5206;
	FT5206		ft5206_(ft5206_i2c_);

	utils::command<256> cmd_;


	bool check_mount_() {
		auto f = sdc_.get_mount();
		if(!f) {
			utils::format("SD card not mount.\n");
		}
		return f;
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
			} else if(cmd_.cmp_word(0, "help")) {
				utils::format("    dir [path]\n");
				utils::format("    cd [path]\n");
				utils::format("    pwd\n");
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


	void utf8_to_sjis(const char* src, char* dst, uint32_t len) {
		utils::str::utf8_to_sjis(src, dst, len);
	}


	int fatfs_get_mount() {
		return sdc_.get_mount();
	}


	int make_full_path(const char* src, char* dst, uint16_t len)
	{
		return sdc_.make_full_path(src, dst, len);
	}

	void gr_plot(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b)
	{
		uint16_t c =   (static_cast<uint16_t>(r & 0xf8) << 8)
              | (static_cast<uint16_t>(g & 0xfc) << 3)
              | (static_cast<uint16_t>(b & 0xf8) >> 3);
		render_.plot(x, y, c);
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

	utils::format("\rRTK5RX65N Start for LCD sample\n");

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
//		drw2d_mgr_.list_info();
		if(drw2d_mgr_.start(0x00000000)) {
			utils:: format("Start DRW2D\n");
		} else {
			utils:: format("DRW2D Fail\n");
		}
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
	SW2::DIR = 0;

	uint8_t task = 100;
	FT5206::xy	pos;

	uint8_t n = 0;
	bool render = true;
	bool sw2 = SW2::P();
	while(1) {
		glcdc_io_.sync_vpos();

		ft5206_.update();

		sdc_.service(sdh_.service());

		if(task > 0) {
			--task;
			if(task == 0) {

#if 0
				img::jpeg_in jpeg;
				utils::file_io fin;
				if(fin.open("aaaaa.jpg", "rb")) {
					if(!jpeg.load(fin)) {
						utils::format("JPEG load fail...\n");
					}
					fin.close();
				}
#endif

#if 0
				char tmp[32];
				for(int i = 0; i < 26; ++i) tmp[i] = 'A' + i;
				tmp[26] = 0;
				render_.draw_text(0, 0, tmp);
				for(int i = 0; i < 26; ++i) tmp[i] = 'a' + i;
				tmp[26] = 0;
				render_.draw_text(0, 16, tmp);
				render_.draw_text(0, 32, "金の貸し借りをしてはならない。\n金を貸せば金も友も失う。\n金を借りれば倹約が馬鹿らしくなる。");
				render_.draw_text(0, 16*5, "Graphics Image Light Bilk IgIiIrliiljkffkL\n", true);
				render_.draw_text(0, 16*6, "012:;,.(i),[i],{i},{|}.(`)\n", true);
#endif
			}
		}

		command_();

		auto tnum = ft5206_.get_touch_num();
		if(tnum == 3) {
			render_.clear(RENDER::COLOR::Black);
		}
		if(tnum > 0) {
			const auto& npos = ft5206_.get_touch_pos(0);
			if(npos.event != FT5206::EVENT::CONTACT) {
				pos.event = FT5206::EVENT::NONE;
			}
			if(pos.event == FT5206::EVENT::CONTACT) {
				render_.line(pos.x, pos.y, npos.x, npos.y, RENDER::COLOR::White);
			}
			pos = npos;
		}

		if(render) {
			int16_t x = 470 / 2;
			int16_t y = 272 / 2;
			render_.arc(x + 0, y + 100, x, y, x + 0, y - 100, RENDER::COLOR::White);
			render_.arc(x + 0, y - 100, x, y, x + 0, y + 100, RENDER::COLOR::Green);
#if 0
			render_.round_frame(20, 20, 400, 200, 16, RENDER::COLOR::Red);
//			render_.round_frame(20 + 5, 20 + 5, 400 - 10, 200 - 10, 16 - 5, RENDER::COLOR::Green);

			render_.round_frame(20 + 5, 20 + 5, 400 - 10, 200 - 10, 16 - 5, RENDER::COLOR::Red);
			render_.round_box(20 + 5, 20 + 5, 400 - 10, 200 - 10, 16 - 5, RENDER::COLOR::Green);

			render_.circle(480/2, 272/2, 100, RENDER::COLOR::Blue);
			render_.fill_circle(480/2, 272/2, 100, RENDER::COLOR::Aqua);

			render_.fill_box(5, 5, 4, 4, RENDER::COLOR::White);
			render_.frame(4, 4, 6, 6, RENDER::COLOR::Gray);
#endif
			render = false;
		}

		{  // SW2 の検出
			auto f = SW2::P();
			if(sw2 && !f) {
				utils::format("SW2: Positive\n");
				render = true;
			}
			if(!sw2 && f) {
				utils::format("SW2: Negative\n");
			}
			sw2 = f;
		}

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
}
