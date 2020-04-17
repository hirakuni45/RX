//=====================================================================//
/*! @file
    @brief  RX65N/RX72N Space InvaDers Emulator
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

#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/font.hpp"
#include "graphics/graphics.hpp"
#include "graphics/dialog.hpp"

#include "chip/FAMIPAD.hpp"

#include "spinv.hpp"

namespace {

#if defined(SIG_RX65N)

	const char* sys_msg_ = { "RX65N Envision kit" };

	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;

	// Famicon PAD (CMOS 4021B Shift Register)
	// 電源は、微小なので、接続を簡単に行う為、ポートを使う
	typedef device::PORT<device::PORT6, device::bitpos::B0> PAD_VCC;  // CN2(2)
	typedef device::PORT<device::PORT6, device::bitpos::B1> PAD_GND;  // CN2(4)
	typedef device::PORT<device::PORT6, device::bitpos::B2> PAD_P_S;  // CN2(6)
	typedef device::PORT<device::PORT6, device::bitpos::B5> PAD_CLK;  // CN2(8)
	typedef device::PORT<device::PORT7, device::bitpos::B3> PAD_OUT;  // CN2(10)
	typedef chip::FAMIPAD<PAD_P_S, PAD_CLK, PAD_OUT> FAMIPAD;
	FAMIPAD		famipad_;

	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	// LCD のフレームメモリーの開始アドレスは、nullptr と区別する為 0x00000000 から始められない
	// 0x000100 から 255K バイト (480x272x2)
	static void* LCD_ORG = reinterpret_cast<void*>(0x00000100);

	// カード電源制御は使わない場合、「device::NULL_PORT」を指定する。
	typedef device::PORT<device::PORT6, device::bitpos::B4, 0> SDC_POWER;  // Low Active

	// 書き込み禁止は使わない
	typedef device::NULL_PORT SDC_WPRT;
	// RX65N Envision Kit の SDHI ポートは、候補３になっている
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WPRT,
		device::port_map::option::THIRD> SDHI;

	// マスターバッファはでサービスできる時間間隔を考えて余裕のあるサイズとする（8192）
	// DMAC でループ転送できる最大数の２倍（1024）
	typedef sound::sound_out<int16_t, 8192, 1024> SOUND_OUT;

	#define USE_DAC

#elif defined(SIG_RX72N)

	const char* sys_msg_ = { "RX72N Envision kit" };

	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;

	// Famicon PAD (CMOS 4021B Shift Register)
	// PMOD1                                                PAD_3V3:     Pmod1-6
	// PMOD1                                                PAD_GND:     Pmod1-5 
	typedef device::PORT<device::PORT5, device::bitpos::B1> PAD_P_S;  // Pmod1-4
	typedef device::PORT<device::PORT5, device::bitpos::B2> PAD_CLK;  // Pmod1-3
	typedef device::PORT<device::PORT5, device::bitpos::B0> PAD_OUT;  // Pmod1-2
	typedef chip::FAMIPAD<PAD_P_S, PAD_CLK, PAD_OUT, 40> FAMIPAD;
	FAMIPAD		famipad_;

	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	static void* LCD_ORG = reinterpret_cast<void*>(0x0080'0000);

	// カード電源制御は使わない場合、「device::NULL_PORT」を指定する。
	typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;
	// 書き込み禁止は使わない
	typedef device::NULL_PORT SDC_WPRT;
	// RX72N Envision Kit の SDHI ポートは、候補３になっている
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WPRT,
		device::port_map::option::THIRD> SDHI;

	// マスターバッファはサービスできる時間間隔を考えて余裕のあるサイズとする（8192）
	// SSIE の FIFO サイズの２倍以上（256）
	typedef sound::sound_out<int16_t, 8192, 256> SOUND_OUT;

	#define USE_SSIE

#endif

	typedef utils::fixed_fifo<char, 512>  RECV_BUFF;
	typedef utils::fixed_fifo<char, 1024> SEND_BUFF;

	typedef device::sci_io<SCI_CH, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

	static const auto PIX = graphics::pixel::TYPE::RGB565;
	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC_MGR;
	GLCDC_MGR	glcdc_mgr_(nullptr, LCD_ORG);

	typedef graphics::font8x16 AFONT;
	AFONT		afont_;
	typedef graphics::kfont_null KFONT;
	KFONT		kfont_;
	typedef graphics::font<AFONT, KFONT> FONT;
	FONT		font_(afont_, kfont_);

	typedef graphics::render<GLCDC_MGR, FONT> RENDER;
	RENDER		render_(glcdc_mgr_, font_);

	typedef gui::dialog<RENDER, FAMIPAD> DIALOG;
	DIALOG		dialog_(render_, famipad_);

	SDHI		sdh_;

	// サウンド出力コンテキスト
	SOUND_OUT	sound_out_;

	typedef emu::spinv SPINV;
	SPINV		spinv_;

	typedef utils::command<256> CMD;
	CMD			cmd_;

	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);

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
				utils::format("SSIE Start: AUDIO_CLK: %u Hz, LRCLK: %u\n") % aclk % lrclk;
			} else {
				utils::format("SSIE Not start...\n");
			}
		}
	}
#endif

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
#ifdef USE_DAC
		dac_stream_.set_sample_rate(freq);
#endif
#ifdef USE_SSIE
		sound_out_.set_output_rate(freq);
#endif
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

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	utils::format("\r%s Start Space Invaders Emulator\n") % sys_msg_;

	{  // SD カード・クラスの初期化
		sdh_.start();
	}

	// 波形メモリーの無音状態初期化
	sound_out_.mute();

	start_audio_();

	{  // サンプリング・タイマー設定
		set_sample_rate(11127);
	}

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
				utils::format("GLCDC ctrl fail...\n");
			}
		} else {
			utils::format("Fail GLCDC\n");
		}
	}

	LED::DIR = 1;

	famipad_.start();

	uint32_t delay_inv = 120;
	uint8_t n = 0;
	bool inv_ok_ = false;
	while(1) {
		glcdc_mgr_.sync_vpos();

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
			spinv_.service(LCD_ORG, GLCDC_MGR::width, GLCDC_MGR::height);

			SPINV::SND_MGR& snd = spinv_.at_sound();
			uint32_t len = snd.get_length();
			const int16_t* wav = snd.get_buffer();
			for(uint32_t i = 0; i < len; ++i) {
				while((sound_out_.at_fifo().size() - sound_out_.at_fifo().length()) < 8) {
				}
				typename SOUND_OUT::WAVE t;
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
