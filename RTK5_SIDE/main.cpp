//=====================================================================//
/*! @file
    @brief  RX65N Space InvaDers Emulator
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
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
#include "graphics/dialog.hpp"

#include "chip/FAMIPAD.hpp"

#include "spinv.hpp"

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

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;
	typedef device::sci_io<device::SCI9, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	// LCD のフレームメモリーの開始アドレスは、nullptr と区別する為 0x00000000 から始められない
	// 0x000100 から 255K バイト (480x272x2)
	static void* LCD_ORG = reinterpret_cast<void*>(0x00000100);
	static const auto PIX = graphics::pixel::TYPE::RGB565;
	typedef device::glcdc_io<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC_IO;
	GLCDC_IO	glcdc_io_(nullptr, LCD_ORG);

	typedef graphics::font8x16 AFONT;
	AFONT		afont_;
	typedef graphics::kfont_null KFONT;
	KFONT		kfont_;
	typedef graphics::font<AFONT, KFONT> FONT;
	FONT		font_(afont_, kfont_);

	typedef graphics::render<GLCDC_IO, FONT> RENDER;
	RENDER		render_(glcdc_io_, font_);

	typedef gui::dialog<RENDER, FAMIPAD> DIALOG;
	DIALOG		dialog_(render_, famipad_);

	// カード電源制御は使わない場合、「device::NULL_PORT」を指定する。
	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;
//	typedef device::NULL_PORT SDC_POWER;

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

	typedef utils::sound_out<1024, 256> SOUND_OUT;
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

	typedef emu::spinv SPINV;
	SPINV		spinv_;

	typedef utils::command<256> CMD;
	CMD			cmd_;

	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);

	void command_()
	{
		if(!cmd_.service()) {
			return;
		}

		if(shell_.analize()) {
			return;
		}

		if(cmd_.cmp_word(0, "help")) {
			shell_.help();
		} else {
			utils::format("Command error: '%s'\n") % cmd_.get_command();
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
///		rtc_.get_time(t);
		return utils::str::get_fattime(t);
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

	{  // SD カード・クラスの初期化
		sdh_.start();
	}

	// 波形メモリーの無音状態初期化
	sound_out_.mute();

	{  // サンプリング・タイマー設定
		set_sample_rate(11127);
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

	utils::format("\rRTK5RX65N Start for Space Invaders Emulator\n");

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

	{
		PAD_VCC::DIR = 1;
		PAD_VCC::P = 1;
		PAD_GND::DIR = 1;
		PAD_GND::P = 0;
		famipad_.start();
	}

	uint32_t delay_inv = 120;
	uint8_t n = 0;
	bool inv_ok_ = false;
	while(1) {
		glcdc_io_.sync_vpos();

		if(delay_inv > 0) {
			--delay_inv;
			if(delay_inv == 0) {
				if(sdh_.get_mount()) {
					if(spinv_.start("/inv_roms", "/inv_wavs")) {
						utils::format("Space Invaders start...\n");
						inv_ok_ = true;
						render_.clear(graphics::def_color::Black);
					} else {
						delay_inv = 30;
						utils::format("Space Invaders not start...(fail)\n");
						dialog_.modal(vtx::spos(400, 60),
							"Invaders ROM Can't find...\n/inv_roms/*, /inv_wavs/*");
					}
				} else {
					delay_inv = 60;
					utils::format("SD card not mount\n");
					dialog_.modal(vtx::spos(400, 60), "SD Card not mount...");
				}
			}
		}

		if(inv_ok_) {
			spinv_.service(LCD_ORG, GLCDC_IO::width, GLCDC_IO::height);

			SPINV::SND_MGR& snd = spinv_.at_sound();
			uint32_t len = snd.get_length();
			const int16_t* wav = snd.get_buffer();
			for(uint32_t i = 0; i < len; ++i) {
				while((sound_out_.at_fifo().size() - sound_out_.at_fifo().length()) < 8) {
				}
				sound::wave_t t;
				t.l_ch = t.r_ch = *wav++;
				sound_out_.at_fifo().put(t);
			}
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
	}
}
