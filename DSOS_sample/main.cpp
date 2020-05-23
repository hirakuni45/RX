//=====================================================================//
/*! @file
    @brief  RX65N/RX72N Envision Kit デジタル・ストレージ・オシロスコープ @n
			マイコン内臓１２ビットＡ／Ｄ変換を使って、波形を観測するガジェット
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#define CASH_KFONT

#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/sci_i2c_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/shell.hpp"
#include "common/spi_io2.hpp"
#include "common/tpu_io.hpp"
#include "common/qspi_io.hpp"
#include "graphics/font8x16.hpp"
#include "graphics/graphics.hpp"
#include "graphics/filer.hpp"
#include "graphics/kfont.hpp"
#include "graphics/font.hpp"

#include "chip/FT5206.hpp"

#include "capture.hpp"
#include "render_wave.hpp"

namespace {

	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	static const auto PIX = graphics::pixel::TYPE::RGB565;

	typedef utils::fixed_fifo<uint8_t, 64> RB64;
	typedef utils::fixed_fifo<uint8_t, 64> SB64;

#if defined(SIG_RX65N)

	static const char* sys_msg_ = { "RX65N Envision Kit" };

	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;

	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	// フレームバッファ開始アドレスは、100 番地から開始とする。
	// ※０～ＦＦは未使用領域
	static void* LCD_ORG = reinterpret_cast<void*>(0x00000100);

	// カード電源制御を使わない場合、「device::NULL_PORT」を指定する。
	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;
	// 書き込み禁止は使わない
	typedef device::NULL_PORT SDC_WP;

	typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::option::FIRST_I2C> FT5206_I2C;

#elif defined(SIG_RX72N)

	static const char* sys_msg_ = { "RX72N Envision Kit" };

	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;

	// GLCDC の制御関係
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	static void* LCD_ORG = reinterpret_cast<void*>(0x0080'0000);

	// SD-CARD の制御関係
	typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;
	// 書き込み禁止は使わない
	typedef device::NULL_PORT SDC_WP;

	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::option::THIRD_I2C> FT5206_I2C;

#endif

	typedef device::cmt_mgr<device::CMT0, utils::null_task> CMT;
	CMT			cmt_;

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<SCI_CH, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC_MGR;
	GLCDC_MGR	glcdc_mgr_(nullptr, LCD_ORG);

	// RX65N/RX72N Envision Kit の SDHI は、候補３になっている
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::option::THIRD> SDHI;
	SDHI		sdh_;

	typedef graphics::font8x16 AFONT;
	AFONT		afont_;
#ifdef CASH_KFONT
	typedef graphics::kfont<16, 16, 64> KFONT;
#else
	typedef graphics::kfont<16, 16> KFONT;
#endif
	KFONT		kfont_;
	typedef graphics::font<AFONT, KFONT> FONT;
	FONT		font_(afont_, kfont_);

	typedef graphics::render<GLCDC_MGR, FONT> RENDER;
	RENDER		render_(glcdc_mgr_, font_);

	typedef utils::capture<2048> CAPTURE;
	CAPTURE		capture_;

	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> FT5206;
	FT5206		ft5206_(ft5206_i2c_);

	typedef utils::render_wave<RENDER, CAPTURE, FT5206> RENDER_WAVE;
	RENDER_WAVE	render_wave_(render_, capture_, ft5206_);

	typedef utils::command<256> CMD;
	CMD			cmd_;
	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);

	utils::capture_trigger	trigger_ = utils::capture_trigger::NONE;


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


	void command_()
	{
		if(!cmd_.service()) {
			return;
		}
		if(shell_.analize()) {
			return;
		}
		if(cmd_.cmp_word(0, "cap")) { // capture
			trigger_ = utils::capture_trigger::SINGLE;
			capture_.set_trigger(trigger_);			
		} else if(cmd_.cmp_word(0, "help")) {
			shell_.help();
			utils::format("    cap        single trigger\n");
		} else {
			utils::format("Command error: '%s'\n") % cmd_.get_command();
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

	{  // キャプチャー開始
		uint32_t freq = 2000000;  // 2 MHz
//		uint32_t freq = 100000;  // 100 KHz
		if(!capture_.start(freq)) {
			utils::format("Capture not start...\n");
		}
	}

	utils::format("\r%s Start for Digital Storage Oscilloscope\n") % sys_msg_;

	cmd_.set_prompt("# ");

	{  // GLCDC の初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 0;  // DISP Disable
		LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
		if(glcdc_mgr_.start()) {
			utils::format("Start GLCDC\n");
			LCD_DISP::P  = 1;  // DISP Enable
			LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
			if(!glcdc_mgr_.control(GLCDC_MGR::CONTROL_CMD::START_DISPLAY)) {
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

#if 0
	{
		render_.sync_frame();
		dialog_.modal(vtx::spos(400, 60),
			"Touch panel device wait...\nPlease touch it with some screen.");
		uint8_t nnn = 0;
		while(1) {
			render_.sync_frame();
			touch_.update();
			auto num = touch_.get_touch_num();
			if(num == 0) {
				++nnn;
				if(nnn >= 60) break;
			} else {
				nnn = 0;
			}
		}
		render_.clear(DEF_COLOR::Black);
	}
#endif

	while(1) {
		glcdc_mgr_.sync_vpos();

		ft5206_.update();

		sdh_.service();

		command_();

		// タッチ操作による画面更新が必要か？
		bool f = render_wave_.ui_service();

		// 波形をキャプチャーしたら描画
		if(f || (trigger_ != utils::capture_trigger::NONE
			&& capture_.get_trigger() == utils::capture_trigger::NONE)) {
			trigger_ = utils::capture_trigger::NONE;
			render_wave_.update();
		}

		update_led_();
	}
}
