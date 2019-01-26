//=====================================================================//
/*! @file
    @brief  RX65N RayTrace
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
#include "graphics/font8x16.hpp"
#include "graphics/graphics.hpp"
#define CASH_KFONT
#include "graphics/kfont.hpp"
#include "common/cmt_io.hpp"

#include "../RAYTRACER_sample/raytracer.hpp"

namespace {

	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B5> SW2;

	typedef device::system_io<12000000> SYSTEM_IO;

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<device::SCI9, RECV_BUFF, SEND_BUFF> SCI;
	SCI		sci_;

	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;

	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	static void* LCD_ORG = reinterpret_cast<void*>(0x00000100);
	static const auto PIXT = device::glcdc_def::PIX_TYPE::RGB565;
	typedef device::glcdc_io<device::GLCDC, LCD_X, LCD_Y, PIXT> GLCDC_IO;
	GLCDC_IO	glcdc_io_(nullptr, LCD_ORG);

	typedef graphics::font8x16 AFONT;
#ifdef CASH_KFONT
	typedef graphics::kfont<16, 16, 64> KFONT;
#else
	typedef graphics::kfont<16, 16> KFONT;
#endif
	KFONT		kfont_;

	typedef graphics::render<uint16_t, LCD_X, LCD_Y, AFONT, KFONT> RENDER;
	RENDER		render_(LCD_ORG, kfont_);

	// カード電源制御は使わない場合、「device::NULL_PORT」を指定する。
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

	MMC		sdh_(spi_, 35000000);
#endif
	typedef utils::sdc_man SDC;
	SDC		sdc_;

	utils::command<256> cmd_;

	typedef device::cmt_io<device::CMT0> CMT;
	CMT		cmt_;

	bool	run_ = false;

	int		render_width_  = 320;
	int		render_height_ = 240;

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
			} else if(cmd_.cmp_word(0, "clear")) {
				render_.clear(0x0000);
				f = true;
			} else if(cmd_.cmp_word(0, "render")) {
				render_.clear(0x0000);
				render_width_  = 320;
				render_height_ = 240;
				run_ = false;
				f = true;
			} else if(cmd_.cmp_word(0, "full")) {
				render_.clear(0x0000);
				render_width_  = 480;
				render_height_ = 272;
				run_ = false;
				f = true;
			} else if(cmd_.cmp_word(0, "help")) {
				utils::format("    dir [path]\n");
				utils::format("    cd [path]\n");
				utils::format("    pwd\n");
				utils::format("    clear     clear screen\n");
				utils::format("    render    renderring 320x240\n");
				utils::format("    full      renderring 480x272\n");
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

	void draw_pixel(int x, int y, int r, int g, int b)
	{
		auto c = RENDER::COLOR::rgb(r, g, b);
		render_.plot(x, y, c);
	}


	void draw_text(int x, int y, const char* t)
	{
//		render_.draw_text_back(x, y, t);
		render_.fill_box(x, y, strlen(t) * 8, 16, render_.get_back_color());
		render_.draw_text(x, y, t);
	}


	uint32_t millis(void)
	{
		return cmt_.get_counter();
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

	{
		uint8_t il = 2;
		cmt_.start(1000, il);  // 
	}

	utils::format("\rRTK5RX65N Start for Ray Trace\n");

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
				utils::format("GLCDC ctrl fail...\n");
			}
		} else {
			utils::format("Fail GLCDC\n");
		}
	}

	LED::DIR = 1;
	SW2::DIR = 0;

	uint8_t n = 0;
	bool sw = false;
	uint8_t asq = 1;
	while(1) {
		glcdc_io_.sync_vpos();
		bool v = !SW2::P();
		if(!sw && v) {
			render_.clear(0x0);
			if(render_width_ == 320) {
				render_width_ = 480;
				render_height_ = 272;
			} else {
				render_width_ = 320;
				render_height_ = 240;
				++asq;
				if(asq > 4) asq = 1;
			}
			run_ = false;
		}
		sw = v;

		sdc_.service(sdh_.service());

		command_();
		if(!run_) {
//			uint32_t org = glcdc_io_.get_vpos();
			doRaytrace(asq, render_width_, render_height_);
//			uint32_t t = glcdc_io_.get_vpos() - org;
//			char tmp[32];
//			utils::sformat("%d.%d [sec]", tmp, sizeof(tmp)) % (t / 60) % ((t / 6) % 10);
//			render_.draw_text(0, 0, tmp);
//			utils::format("%s\n") % tmp;
			run_ = true;
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
