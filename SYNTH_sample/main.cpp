//=====================================================================//
/*! @file
    @brief  RX65N/RX72N Envision Kit SYNTH sample
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/sci_i2c_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/shell.hpp"
#include "sound/dac_stream.hpp"
#include "sound/sound_out.hpp"

#include "sound/synth/synth_unit.h"

#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/font.hpp"
#include "graphics/graphics.hpp"
#include "graphics/filer.hpp"
#include "graphics/simple_dialog.hpp"

#include "chip/FT5206.hpp"

#include "synth_gui.hpp"

#include "sound/smf/MD_MIDIFile.h"

#include "sound/psg_mng.hpp"

namespace {

	static const char* SOUND_COLOR_FILE = { "DX7_0628.SYX" };

	typedef utils::fixed_fifo<uint8_t, 64> RB64;
	typedef utils::fixed_fifo<uint8_t, 64> SB64;

#if defined(SIG_RX65N)

	static const char* sys_msg_ = { "RX65N Envision Kit" };

	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;

	static constexpr uint32_t AUDIO_SAMPLE_RATE = 48'000;

	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	// フレームバッファ開始アドレスは、100 番地から開始とする。
	// ※０～ＦＦは未使用領域
	static void* LCD_ORG = reinterpret_cast<void*>(0x00000100);

	// カード電源制御を使わない場合、「device::NULL_PORT」を指定する。
	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;
	// 書き込み禁止は使わない
	typedef device::NULL_PORT SDC_WP;

	// タッチセンサー「RESET」制御ポート
	typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
	// タッチセンサー I2C ポート設定
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::FIRST_I2C> FT5206_I2C;

	// マスターバッファはでサービスできる時間間隔を考えて余裕のあるサイズとする（8192）
	// DMAC でループ転送できる最大数の２倍（1024）
	typedef sound::sound_out<int16_t, 8192, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	#define USE_GRAPHICS

#elif defined(SIG_RX72N)

	static const char* sys_msg_ = { "RX72N Envision Kit" };

	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;

//	typedef device::PORT<device::PORT0, device::bitpos::B7, false> SW2;

	static constexpr uint32_t AUDIO_SAMPLE_RATE = 48'000;

	// GLCDC の制御関係
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	static void* LCD_ORG = reinterpret_cast<void*>(0x0080'0000);

	// SD-CARD の制御関係
	typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;
	// 書き込み禁止は使わない
	typedef device::NULL_PORT SDC_WP;

	// タッチセンサー「RESET」制御ポート
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	// タッチセンサー I2C ポート設定
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::THIRD_I2C> FT5206_I2C;

	// マスターバッファはサービスできる時間間隔を考えて余裕のあるサイズとする（2048）
	// SSIE の FIFO サイズの２倍以上（256）
	typedef sound::sound_out<int16_t, 2048, 256> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x0000;

	#define USE_SSIE
	#define USE_GRAPHICS

#elif defined(SIG_RX72T)

	static const char* sys_msg_ = { "RX72T" };

	typedef device::PORT<device::PORT0, device::bitpos::B1> LED;
	typedef device::SCI1 SCI_CH;

	static constexpr uint32_t AUDIO_SAMPLE_RATE = 48'000;

	// マスターバッファはでサービスできる時間間隔を考えて余裕のあるサイズとする（8192）
	// DMAC でループ転送できる最大数の２倍（1024）
	typedef sound::sound_out<int16_t, 8192, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC

#endif
	typedef device::system_io<> SYSTEM_IO;

	typedef utils::fixed_fifo<char, 256> RECV_BUFF;
	typedef utils::fixed_fifo<char, 512> SEND_BUFF;
	typedef device::sci_io<SCI_CH, RECV_BUFF, SEND_BUFF> SCI;
	SCI			sci_;

#ifdef USE_GRAPHICS
	static const uint16_t LCD_X = 480;
	static const uint16_t LCD_Y = 272;
	static const graphics::pixel::TYPE PIX = graphics::pixel::TYPE::RGB565;
	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC_MGR;
	GLCDC_MGR	glcdc_mgr_(nullptr, LCD_ORG);

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

	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> TOUCH;
	TOUCH		touch_(ft5206_i2c_);

//	typedef graphics::render<GLCDC_MGR, FONT> RENDER;
	typedef device::drw2d_mgr<GLCDC_MGR, FONT> RENDER;
	RENDER		render_(glcdc_mgr_, font_);

	// 標準カラーインスタンス
	typedef graphics::def_color DEF_COLOR;

	typedef gui::simple_dialog<RENDER, TOUCH> DIALOG;
	DIALOG      dialog_(render_, touch_);

	typedef synth::synth_gui<RENDER, TOUCH> SYNTH_GUI;
	SYNTH_GUI	synth_gui_(render_, touch_);
#endif

	// RX65N/RX72N Envision Kit の SDHI は、候補３になっている
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::ORDER::THIRD> SDHI;
	SDHI		sdh_;

	// サウンド出力コンテキスト
	SOUND_OUT	sound_out_(ZERO_LEVEL);

	// シンセサイザー・コンテキスト
	static const int32_t SYNTH_SAMPLE_RATE = 48'000;
	RingBuffer	ring_buffer_;
	SynthUnit	synth_unit_(ring_buffer_);
	char		synth_color_name_[16 * 32];

#ifdef USE_DAC
	typedef sound::dac_stream<device::R12DA, device::MTU0, device::DMAC0, SOUND_OUT> DAC_STREAM;
	DAC_STREAM	dac_stream_(sound_out_);

	void start_audio_()
	{
		uint8_t dmac_intl = 4;
		uint8_t mtu_intl  = 5;
		if(dac_stream_.start(48'000, dmac_intl, mtu_intl)) {
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

	// RX65N/RX72N Envision Kit では、内臓 RTC は利用出来ない為、簡易的な時計を用意する。
	time_t		rtc_time_ = 0;

	typedef utils::command<256> CMD;
	CMD			cmd_;
	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);

	uint32_t	file_id_ = 0;

	uint32_t	microsec_ = 0;
	bool		midifile_ = false;
	MD_MIDIFile	mdf_;


	void service_note_() noexcept
	{
		for(int i = 0; i < 21; ++i) {
			const auto& key = synth_gui_.get_keyboard().get(static_cast<SYNTH_GUI::KEYBOARD::key>(i));
			if(key.positive_) {
				uint8_t tmp[3];
				tmp[0] = 0x90;
				tmp[1] = 0x24 + synth_gui_.get_octave() * 12 + i;
				tmp[2] = 0x7f;
				ring_buffer_.Write(tmp, 3);
			}
			if(key.negative_) {
				uint8_t tmp[3];
				tmp[0] = 0x80;
				tmp[1] = 0x24 + synth_gui_.get_octave() * 12 + i;
				tmp[2] = 0x7f;
				ring_buffer_.Write(tmp, 3);
			}
		}
	}


    void setup_touch_panel_() noexcept
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


	// 音色の読み込み、３２個
	bool read_synth_color_(const char* filename) noexcept
	{
		utils::file_io fin;
		if(fin.open(filename, "rb")) {
			uint8_t tmp[4096 + 8];
			if(fin.read(tmp, sizeof(tmp)) == sizeof(tmp)) {
				ring_buffer_.Write(tmp, sizeof(tmp));
				{  // データを処理させる為、エンジンを動かす。
					const uint32_t len = SYNTH_SAMPLE_RATE / 60;
					int16_t tmp[len];
					synth_unit_.GetSamples(len, tmp);
				}
				for(int i = 0; i < 32; ++i) {
					char tmp[12];
					synth_unit_.get_patch_name(i, tmp, 12 - 1);
					tmp[11] = 0;
					utils::sformat(" %2d: %s", &synth_color_name_[i * 16], 16) % (i + 1) % tmp;
				}
			}
			return true;
		} else {
			return false;
		}
	}


	// 音色の切り替え
	void select_synth_color_(uint32_t no) noexcept
	{
		uint8_t tmp[2];
		tmp[0] = 0xc0;
		tmp[1] = no & 31;
		ring_buffer_.Write(tmp, sizeof(tmp));
	}


	void midiCallback_(midi_event *pev)
	{
		if((pev->data[0] >= 0x80) && (pev->data[0] <= 0xe0)) {
			uint8_t tmp = pev->data[0] | pev->channel;
			ring_buffer_.Write(&tmp, 1);
			ring_buffer_.Write(&pev->data[1], pev->size - 1);
		} else {
			ring_buffer_.Write(pev->data, pev->size);
		}
#if 0
		utils::format("T: %d") % static_cast<int>(pev->track);
		utils::format(", Ch: %d\n") % static_cast<int>(pev->channel+1);
		for (uint8_t i=0; i<pev->size; i++) {
			if(i == 0) {
				utils::format("  %d") % static_cast<uint8_t>(pev->data[i]);
			} else {
				utils::format(", %d") % static_cast<uint8_t>(pev->data[i]);
			}
		}
		utils::format("\n");
#endif
	}


	void sysexCallback_(sysex_event *pev)
	{
#if 0
		utils::format("T: %d") % static_cast<int>(pev->track);
		for (uint8_t i=0; i<pev->size; i++) {
			utils::format("%d,") % static_cast<int>(pev->data[i]);
		}
		utils::format("\n");
#endif
	}

	typedef utils::psg_base PSG;

	// ドラゴンクエスト１・ラダトーム城（Dragon Quest 1 Chateau Ladutorm）
	constexpr PSG::SCORE score0_[] = {
		PSG::CTRL::VOLUME, 128,
		PSG::CTRL::SQ50,
		PSG::CTRL::TEMPO, 80,
		PSG::CTRL::ATTACK, 175,
		// 1
		PSG::KEY::Q,   8,
		PSG::KEY::E_5, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::E_5, 8,
		// 2
		PSG::KEY::A_4, 8*3,
		PSG::KEY::Q,   8*5,
		// 3
		PSG::KEY::Q,   8,
		PSG::KEY::F_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::F_5, 8,
		// 4
		PSG::KEY::B_4, 8*3,
		PSG::KEY::Q,   8*5,
		// 5
		PSG::KEY::Q,   8,
		PSG::KEY::G_5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::G_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::G_5, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::G_5, 8,
		// 6
		PSG::KEY::F_5, 16,
		PSG::KEY::G_5, 16,
		PSG::KEY::A_5, 16,
		PSG::KEY::G_5, 8,
		PSG::KEY::F_5, 8,
		// 7
		PSG::KEY::E_5, 16,
		PSG::KEY::C_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::D_5, 16,
		PSG::KEY::Eb5, 16,
		// 8
		PSG::KEY::E_5, 8*8,
		// 9
		PSG::KEY::Q,   8,
		PSG::KEY::A_5, 4,
		PSG::KEY::Gs5, 4,
		PSG::KEY::A_5, 8,
		PSG::KEY::E_5, 4,
		PSG::KEY::Eb5, 4,
		PSG::KEY::E_5, 8,
		PSG::KEY::C_5, 4,
		PSG::KEY::B_4, 4,
		PSG::KEY::C_5, 8,
		PSG::KEY::A_4, 8,
		// 10
		PSG::KEY::Q,   8,
		PSG::KEY::A_5, 4,
		PSG::KEY::Gs5, 4,
		PSG::KEY::A_5, 8,
		PSG::KEY::E_5, 4,
		PSG::KEY::Eb5, 4,
		PSG::KEY::E_5, 8,
		PSG::KEY::C_5, 4,
		PSG::KEY::B_4, 4,
		PSG::KEY::C_5, 8,
		PSG::KEY::A_4, 8,
		// 11
		PSG::KEY::B_4, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::A_4, 8,
		// 12
		PSG::KEY::E_5, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::E_5, 8,
		// 13
		PSG::KEY::Q,   8,
		PSG::KEY::A_5, 4,
		PSG::KEY::Gs5, 4,
		PSG::KEY::A_5, 8,
		PSG::KEY::F_5, 4,
		PSG::KEY::E_5, 4,
		PSG::KEY::F_5, 8,
		PSG::KEY::D_5, 4,
		PSG::KEY::Cs5, 4,
		PSG::KEY::D_5, 8,
		PSG::KEY::A_4, 8,
		// 14
		PSG::KEY::Q,   8,
		PSG::KEY::A_5, 4,
		PSG::KEY::Gs5, 4,
		PSG::KEY::A_5, 8,
		PSG::KEY::F_5, 4,
		PSG::KEY::E_5, 4,
		PSG::KEY::F_5, 8,
		PSG::KEY::D_5, 4,
		PSG::KEY::Cs5, 4,
		PSG::KEY::D_5, 8,
		PSG::KEY::A_4, 8,
		// 15
		PSG::KEY::B_4, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::F_5, 8,
		// 16
		PSG::KEY::E_5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::F_4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::C_4, 8,
		PSG::KEY::B_3, 8,
		// 17
		PSG::KEY::Q,   8,
		PSG::KEY::E_5, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::E_5, 8,
		// 18
		PSG::KEY::A_4, 8*3,
		PSG::KEY::Q,   8*5,
		// 19
		PSG::KEY::Q,   8,
		PSG::KEY::F_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::F_5, 8,
		// 20
		PSG::KEY::B_4, 8*3,
		PSG::KEY::Q,   8*5,
		// 21
		PSG::KEY::Q,   8,
		PSG::KEY::G_5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::G_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::G_5, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::G_5, 8,
		// 22
		PSG::KEY::F_5, 16,
		PSG::KEY::G_5, 16,
		PSG::KEY::A_5, 16,
		PSG::KEY::G_5, 8,
		PSG::KEY::F_5, 8,
		// 23
		PSG::KEY::E_5, 16,
		PSG::KEY::C_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::D_5, 16,
		PSG::KEY::Eb5, 16,
		// 24
		PSG::KEY::E_5, 8*8,
		// 25
		PSG::KEY::Q   ,8,
		PSG::KEY::A_5, 4,
		PSG::KEY::Gs5, 4,
		PSG::KEY::A_5, 8,
		PSG::KEY::E_5, 4,
		PSG::KEY::Eb5, 4,
		PSG::KEY::E_5, 8,
		PSG::KEY::C_5, 4,
		PSG::KEY::B_4, 4,
		PSG::KEY::C_5, 8,
		PSG::KEY::A_4, 8,
		// 26
		PSG::KEY::Q   ,8,
		PSG::KEY::A_5, 4,
		PSG::KEY::Gs5, 4,
		PSG::KEY::A_5, 8,
		PSG::KEY::E_5, 4,
		PSG::KEY::Eb5, 4,
		PSG::KEY::E_5, 8,
		PSG::KEY::C_5, 4,
		PSG::KEY::B_4, 4,
		PSG::KEY::C_5, 8,
		PSG::KEY::A_4, 8,
		// 27
		PSG::KEY::B_4, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::A_4, 8,
		// 28
		PSG::KEY::E_5, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::E_5, 8,
		// 29
		PSG::KEY::Q,   8,
		PSG::KEY::A_5, 4,
		PSG::KEY::Gs5, 4,
		PSG::KEY::A_5, 8,
		PSG::KEY::F_5, 4,
		PSG::KEY::E_5, 4,
		PSG::KEY::F_5, 8,
		PSG::KEY::D_5, 4,
		PSG::KEY::Cs5, 4,
		PSG::KEY::D_5, 8,
		PSG::KEY::A_4, 8,
		// 30
		PSG::KEY::Q,   8,
		PSG::KEY::A_5, 4,
		PSG::KEY::Gs5, 4,
		PSG::KEY::A_5, 8,
		PSG::KEY::F_5, 4,
		PSG::KEY::E_5, 4,
		PSG::KEY::F_5, 8,
		PSG::KEY::D_5, 4,
		PSG::KEY::Cs5, 4,
		PSG::KEY::D_5, 8,
		PSG::KEY::A_4, 8,
		// 31
		PSG::KEY::B_4, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::F_5, 8,
		// 32
		PSG::KEY::E_5, 8,
		PSG::KEY::A_4, 8,  // F_4, 8
		PSG::KEY::Gs4, 8,  // E_4, 8
		PSG::KEY::F_4, 8,  // D_4, 8
		PSG::KEY::E_4, 8,  // C_4, 8
		PSG::KEY::D_4, 8,  // B_3, 8
		PSG::KEY::C_4, 8,  // A_3, 8
		PSG::KEY::B_3, 8,  // G_3, 8
		// 33
		PSG::KEY::Q,   8,
		PSG::KEY::E_5, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::E_5, 8,
		// 34
		PSG::KEY::A_4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::Cs5, 8,
		// 35
		PSG::KEY::D_5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::E_5, 8,  // Cs5, 8 
		PSG::KEY::F_5, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::A_5, 8,  // C_5, 8
		PSG::KEY::F_5, 8,
		// 36
		PSG::KEY::Gs5, 8,
		PSG::KEY::Fs5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::Fs5, 8,
		PSG::KEY::Gs5, 8,
		PSG::KEY::A_5, 8,
		PSG::KEY::B_5, 8,
		PSG::KEY::Gs5, 8,
		// 37
		PSG::KEY::Bb5, 8,
		PSG::KEY::Fs5, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::Fs5, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::Fs5, 8,
		PSG::KEY::Cs5, 8,
		// 38
		PSG::KEY::Gs5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::D_5, 8,
		// 39
		PSG::KEY::Fs5, 8,
		PSG::KEY::Eb5, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Eb5, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Eb5, 8,
		PSG::KEY::Bb4, 8,
		// 40
		PSG::KEY::E_5, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Fs4, 8,
		// 41
		PSG::KEY::B_4, 16,
		PSG::KEY::Bb4, 16,
		PSG::KEY::B_4, 16,
		PSG::KEY::Fs5, 16,  // PSG::KEY::Fs4, 16,
		// 42
		PSG::KEY::Eb4, 8,
		PSG::KEY::Cs4, 8,
		PSG::KEY::Eb4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::Fs4, 8,
		// 43
		PSG::KEY::Q,   8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::Eb4, 8,
		PSG::KEY::Fs4, 8,
		// 44
		PSG::KEY::E_4, 8,
		PSG::KEY::Eb4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::Gs4, 8,
		// 45
		PSG::KEY::Cs5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::A_4, 8,
		// 46
		PSG::KEY::Eb5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::Eb5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::A_4, 8,
		// 47
		PSG::KEY::E_5, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::B_4, 8,
		// 48
		PSG::KEY::E_5, 8,
		PSG::KEY::E_6, 8,  // PSG::KEY::Gs5, 8,
		PSG::KEY::D_6, 8,  // PSG::KEY::F_5, 8,
		PSG::KEY::C_6, 8,  // PSG::KEY::E_5, 8,
		PSG::KEY::B_5, 8,  // PSG::KEY::D_5, 8,
		PSG::KEY::A_5, 8,  // PSG::KEY::C_5, 8,
		PSG::KEY::Gs5, 8,  // PSG::KEY::B_4, 8,
		PSG::KEY::E_5, 8,  // PSG::KEY::Gs4, 8,
		// 49
		PSG::KEY::Cs5, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::Eb4, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::Eb4, 8,
		PSG::KEY::G_4, 8,
		PSG::KEY::Bb4, 8,
		// 50
		PSG::KEY::D_5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::F_4, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::F_4, 8,
		PSG::KEY::A_4, 8,
		// 51
		PSG::KEY::Eb5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::Eb5, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::A_4, 8,
		// 52
		PSG::KEY::E_5, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::B_4, 8,
		// 53
		PSG::KEY::F_5, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::F_5, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::Cs5, 8,
		// 54
		PSG::KEY::Fs5, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::Fs5, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Cs5, 8,
		// 55
		PSG::KEY::G_5, 8,  // KEY::Bb4, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::G_5, 8,  // KEY::Bb4, 8,
		PSG::KEY::Cs5, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Cs5, 8,
		// 56
		PSG::KEY::Gs5, 8,  // KEY::C_5, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::Eb4, 8,
		PSG::KEY::Cs4, 8,
		PSG::KEY::C_4, 8,
		PSG::KEY::Gs3, 8,
		// 57
		PSG::KEY::Q,   8,
		PSG::KEY::Gs5, 8,
		PSG::KEY::Fs5, 8,
		PSG::KEY::Gs5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::Gs5, 8,
		PSG::KEY::Eb5, 8,
		PSG::KEY::Gs5, 8,
		// 58
		PSG::KEY::Cs5, 8,
		PSG::KEY::Bb5, 8,
		PSG::KEY::Gs5, 8,
		PSG::KEY::Bb5, 8,
		PSG::KEY::Fs5, 8,
		PSG::KEY::Bb5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::Bb5, 8,
		// 59
		PSG::KEY::Eb5, 8,
		PSG::KEY::B_5, 8,
		PSG::KEY::A_5, 8,
		PSG::KEY::B_5, 8,
		PSG::KEY::Gb5, 8,
		PSG::KEY::B_5, 8,
		PSG::KEY::Fs5, 8,
		PSG::KEY::B_5, 8,
		// 60
		PSG::KEY::E_5, 8,
		PSG::KEY::Eb5, 8,
		PSG::KEY::E_5, 8,
		PSG::KEY::Fs5, 8,
		PSG::KEY::Gs5, 8,
		PSG::KEY::A_5, 8,
		PSG::KEY::B_5, 8,
		PSG::KEY::Gs5, 8,

		PSG::CTRL::END
	};

	constexpr PSG::SCORE score1_[] = {
		PSG::CTRL::VOLUME, 128,
		PSG::CTRL::SQ50,
		PSG::CTRL::TEMPO, 80,
		PSG::CTRL::ATTACK, 175,
		// 1
		PSG::KEY::A_2, 8,
		PSG::KEY::Q,   8*7,
		// 2
		PSG::KEY::Q,   8,
		PSG::KEY::A_2, 8,
		PSG::KEY::C_3, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::G_3, 8,
		PSG::KEY::F_3, 8,
		PSG::KEY::E_3, 8,
		// 3
		PSG::KEY::D_3, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::C_4, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::D_4, 8,
		// 4
		PSG::KEY::Gs3, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::Gs3, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::Fs3, 8,
		PSG::KEY::Gs3, 8,
		// 5
		PSG::KEY::A_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::Cs4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::E_4, 8,
		// 6
		PSG::KEY::D_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::F_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::D_4, 8,
		// 7
		PSG::KEY::C_4, 8,
		PSG::KEY::G_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::G_3, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::F_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::Fs4, 8,
		// 8
		PSG::KEY::Gs4, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::Gs3, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::C_4, 8,
		PSG::KEY::B_3, 8,
		// 9
		PSG::KEY::A_3, 8,
		PSG::KEY::C_4, 4,
		PSG::KEY::B_3, 4,
		PSG::KEY::C_4, 8,
		PSG::KEY::C_4, 4,
		PSG::KEY::B_3, 4,
		PSG::KEY::C_4, 8,
		PSG::KEY::Eb4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::E_4, 8,
		PSG::KEY::C_4, 8,
		// 10
		PSG::KEY::G_3, 8,
		PSG::KEY::C_4, 4,
		PSG::KEY::B_3, 4,
		PSG::KEY::C_4, 8,
		PSG::KEY::C_4, 4,
		PSG::KEY::B_3, 4,
		PSG::KEY::E_4, 8, // PSG::KEY::Fs3, 8,
		PSG::KEY::Eb4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::E_4, 8,
		PSG::KEY::C_4, 8,
		// 11
		PSG::KEY::F_3, 16,
		PSG::KEY::E_3, 16,
		PSG::KEY::D_3, 16,
		PSG::KEY::Eb3, 16,
		// 12
		PSG::KEY::E_3, 16*2,
		PSG::KEY::A_3, 16*2,
		// 13
		PSG::KEY::D_3, 8,
		PSG::KEY::F_4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::F_4, 8,
		PSG::KEY::D_4, 4,
		PSG::KEY::Cs4, 4,
		PSG::KEY::Ds4, 8,
		PSG::KEY::F_4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::F_4, 8,
		PSG::KEY::D_4, 8,
		// 14
		PSG::KEY::C_4, 8,
		PSG::KEY::F_4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::F_4, 8,
		PSG::KEY::D_4, 4,
		PSG::KEY::Cs4, 4,
		PSG::KEY::D_4, 8,  // B_3, 8
		PSG::KEY::F_4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::F_4, 8,
		PSG::KEY::D_4, 8,
		// 15
		PSG::KEY::F_3, 16,
		PSG::KEY::E_3, 16,
		PSG::KEY::D_3, 32,
		// 16
		PSG::KEY::E_3, 16,
		PSG::KEY::Q,   8*6,
		// 17
		PSG::KEY::A_2, 16,
		PSG::KEY::Q,   8*6,
		// 18
		PSG::KEY::Q,   8,
		PSG::KEY::A_2, 8,
		PSG::KEY::C_3, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::G_3, 8,
		PSG::KEY::F_3, 8,
		PSG::KEY::E_3, 8,
		// 19
		PSG::KEY::D_3, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::C_4, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::D_4, 8,
		// 20
		PSG::KEY::Gs3, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::Gs3, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::Fs3, 8,
		PSG::KEY::Gs3, 8,
		// 21
		PSG::KEY::A_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::Cs4, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::E_4, 8,
		// 22
		PSG::KEY::D_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::F_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::D_4, 8,
		// 23
		PSG::KEY::C_4, 8,
		PSG::KEY::G_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::G_3, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::F_4, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::Fs4, 8,
		// 24
		PSG::KEY::Gs4, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::Gs3, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::E_4, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::C_4, 8,
		PSG::KEY::B_3, 8,
		// 25
		PSG::KEY::A_3, 8,
		PSG::KEY::C_4, 4,
		PSG::KEY::B_3, 4,
		PSG::KEY::C_4, 8,
		PSG::KEY::C_4, 4,
		PSG::KEY::B_3, 4,
		PSG::KEY::C_4, 8,
		PSG::KEY::Eb4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::E_4, 8,
		PSG::KEY::C_3, 8,
		// 26
		PSG::KEY::A_3, 8,
		PSG::KEY::C_4, 4,
		PSG::KEY::B_3, 4,
		PSG::KEY::C_4, 8,
		PSG::KEY::C_4, 4,
		PSG::KEY::B_3, 4,
		PSG::KEY::C_4, 8,  // Fs3, 8
		PSG::KEY::Eb4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::E_4, 8,
		PSG::KEY::C_3, 8,
		// 27
		PSG::KEY::F_3, 16,
		PSG::KEY::E_3, 16,
		PSG::KEY::D_3, 16,
		PSG::KEY::Eb3, 16,
		// 28
		PSG::KEY::E_3, 32,
		PSG::KEY::A_3, 32,
		// 29
		PSG::KEY::D_3, 8,
		PSG::KEY::F_4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::F_4, 8,
		PSG::KEY::D_4, 4,
		PSG::KEY::Cs4, 4,
		PSG::KEY::D_4, 8,
		PSG::KEY::F_4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::F_4, 8,
		PSG::KEY::D_4, 8,
		// 30
		PSG::KEY::C_4, 8,
		PSG::KEY::F_4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::F_4, 8,
		PSG::KEY::D_4, 4,
		PSG::KEY::Cs4, 4,
		PSG::KEY::D_4, 8,  // B_3, 8
		PSG::KEY::F_4, 4,
		PSG::KEY::E_4, 4,
		PSG::KEY::F_4, 8,
		PSG::KEY::D_4, 8,
		// 31
		PSG::KEY::F_3, 16,
		PSG::KEY::E_3, 16,
		PSG::KEY::D_3, 32,
		// 32
		PSG::KEY::E_3, 16,
		PSG::KEY::Q,   16*3,
		// 33
		PSG::KEY::A_3, 16,
		PSG::KEY::Q,   16*3,
		// 34
		PSG::KEY::Q,   8*8,
		// 35
		PSG::KEY::Q,   8*8,
		// 36
		PSG::KEY::B_4, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::Gs4, 8,
		PSG::KEY::A_4, 8,
		PSG::KEY::B_4, 8,
		PSG::KEY::C_5, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::B_4, 8,
		// 37
		PSG::KEY::Cs5, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Cs4, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Bb4, 8,
		// 38
		PSG::KEY::F_4, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::F_4, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::D_5, 8,
		PSG::KEY::Bb4, 8,
		// 39
		PSG::KEY::Eb4, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Eb4, 8,
		PSG::KEY::Bb4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Bb4, 8,
		// 40
		PSG::KEY::Cs4, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Bb3, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Cs4, 8,
		PSG::KEY::Bb3, 8,
		PSG::KEY::Fs4, 8,
		PSG::KEY::Bb3, 8,
		// 41
		PSG::KEY::B_3, 8,
		PSG::KEY::Fs3, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::Fs3, 8,
		PSG::KEY::Eb3, 8,
		PSG::KEY::Fs3, 8,
		PSG::KEY::Cs3, 8,
		PSG::KEY::Fs3, 8,
		// 42
		PSG::KEY::B_2, 8,
		PSG::KEY::Bb2, 8,
		PSG::KEY::B_2, 8,
		PSG::KEY::C_3, 8,
		PSG::KEY::Eb3, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::Fs3, 8,
		PSG::KEY::E_3, 8,
		// 43
		PSG::KEY::E_3, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::Gs3, 8,  // PSG::KEY::E_3, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::Fs3, 8,  // PSG::KEY::B_2, 8,
		PSG::KEY::B_3, 8,
		// 44
		PSG::KEY::Gs3, 8,  // PSG::KEY::E_3, 8,
		PSG::KEY::Fs3, 8,
		PSG::KEY::Gs3, 8,
		PSG::KEY::A_3, 8,
		PSG::KEY::B_3, 8,
		PSG::KEY::Cs4, 8,
		PSG::KEY::D_4, 8,
		PSG::KEY::B_3, 8,
		// 45
		PSG::KEY::A_3, 16,
		PSG::KEY::A_2, 16,
		PSG::KEY::A_3, 16,
		PSG::KEY::A_2, 16,
		// 46
		PSG::KEY::Fs3, 16,
		PSG::KEY::Fs2, 16,
		PSG::KEY::B_2, 16,
		PSG::KEY::B_2, 16,
		// 47
		PSG::KEY::E_3, 16,
		PSG::KEY::E_2, 16,
		PSG::KEY::E_3, 16,
		PSG::KEY::E_2, 16,
		// 48
		PSG::KEY::E_3, 16,
		PSG::KEY::Q,   16*3,
		// 49
		PSG::KEY::E_4, 16,
		PSG::KEY::E_4, 16,
		PSG::KEY::E_4, 16,
		PSG::KEY::E_4, 16,
		// 50
		PSG::KEY::D_4, 16,
		PSG::KEY::D_4, 16,
		PSG::KEY::D_4, 16,
		PSG::KEY::D_4, 16,
		// 51
		PSG::KEY::C_4, 16,
		PSG::KEY::C_4, 16,
		PSG::KEY::C_4, 16,
		PSG::KEY::C_4, 16,
		// 52
		PSG::KEY::B_3, 16,
		PSG::KEY::B_3, 16,
		PSG::KEY::B_3, 16,
		PSG::KEY::B_3, 16,
		// 53
		PSG::KEY::B_3, 16,
		PSG::KEY::B_3, 16,
		PSG::KEY::B_3, 16,
		PSG::KEY::B_3, 16,
		// 54
		PSG::KEY::A_3, 16,
		PSG::KEY::A_3, 16,
		PSG::KEY::A_3, 16,
		PSG::KEY::A_3, 16,
		// 55
		PSG::KEY::Eb3, 16,
		PSG::KEY::Eb3, 16,  //  PSG::KEY::Eb2, 16, 
		PSG::KEY::Eb3, 16,
		PSG::KEY::Eb3, 16,  //  PSG::KEY::Eb2, 16, 
		// 56
		PSG::KEY::Gs2, 8,
		PSG::KEY::Gs3, 8,
		PSG::KEY::Fs3, 8,
		PSG::KEY::E_3, 8,
		PSG::KEY::Eb3, 8,
		PSG::KEY::Cs3, 8,
		PSG::KEY::C_3, 8,
		PSG::KEY::Gs2, 8,
		// 57
		PSG::KEY::Cs3, 16,
		PSG::KEY::Q,   16*3,
		// 58
		PSG::KEY::Q,   16*4,
		// 59
		PSG::KEY::Q,   16*4,
		// 60
		PSG::KEY::Q,   16*4,



		PSG::CTRL::END
	};
}


/// widget の登録・グローバル関数
bool insert_widget(gui::widget* w)
{
	return 	synth_gui_.at_widd().insert(w);
}

/// widget の解除・グローバル関数
void remove_widget(gui::widget* w)
{
	synth_gui_.at_widd().remove(w);
}

/// 音色を設定
void select_synth_color(uint32_t no)
{
	select_synth_color_(no);
}


uint32_t micros()
{
	return microsec_;
}


extern "C" {

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
//		time_t t = 0;
//		rtc_.get_time(t);
		return utils::str::get_fattime(rtc_time_);
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	{  // 時計の初期時刻(2021/2/1 12:00:00)
		struct tm m;
		m.tm_year = 2021 - 1900;
		m.tm_mon  = 2 - 1;
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

	SynthUnit::Init(SYNTH_SAMPLE_RATE);

	{  // サンプリング・タイマー周期設定
		set_sample_rate(AUDIO_SAMPLE_RATE);
	}

	utils::format("\r%s Start for SYNTH sample\n") % sys_msg_;
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

	{  // DRW2D start
		if(render_.start()) {
			utils::format("DRW2D Start OK\n");
		} else {
			utils::format("DRW2D Start Fail\n");
		}
	}

	{  // FT5206 touch screen controller
		TOUCH::reset<FT5206_RESET>();
		uint8_t intr_lvl = 1;
		if(!ft5206_i2c_.start(FT5206_I2C::MODE::MASTER, FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
			utils::format("FT5206 I2C Start Fail...\n");
		}
		if(!touch_.start()) {
			utils::format("FT5206 Start Fail...\n");
		}
	}

	setup_touch_panel_();

	synth_gui_.start(synth_color_name_);

	{  // SMF プレイヤーの設定
		mdf_.begin(nullptr);
		mdf_.setMidiHandler(midiCallback_);
		mdf_.setSysexHandler(sysexCallback_);
	}

	LED::DIR = 1;
//	SW2::DIR = 0;

	uint8_t n = 0;
	uint8_t sec = 0;
	synth_color_name_[0] = 0;
	bool load_stall = false;
	while(1) {
		render_.sync_frame();

		touch_.update();

		synth_gui_.update(sdh_.get_mount());

		{  // シンセサイザー・サービス
			uint32_t n = SYNTH_SAMPLE_RATE / 60;
			int16_t tmp[n];
			synth_unit_.GetSamples(n, tmp);

			typename SOUND_OUT::WAVE t;
			for(uint32_t i = 0; i < n; ++i) {
				t.l_ch = t.r_ch = tmp[i];
				sound_out_.at_fifo().put(t);
			}

			service_note_();
		}

		if(sdh_.get_mount()) {
			if(!load_stall) {
				if(!read_synth_color_(SOUND_COLOR_FILE)) {
					utils::format("Synth sound color load fail: '%s'\n") % SOUND_COLOR_FILE;
				}
				load_stall = true;
			}
		}

		{
			uint32_t id;
			auto fn = synth_gui_.get_file_name(id);
			if(id != file_id_) {
				auto state = mdf_.load(fn);
				if(state == MD_MIDIFile::E_OK) {
					midifile_ = true;
				}
				file_id_ = id;
			}
		}

		sdh_.service();

///		command_();

		if(midifile_) {
		    if(!mdf_.isEOF()) {
				if(mdf_.getNextEvent()) {
       				// tickMetronome(mdf_.getTempo());
   				}
			} else {
				mdf_.close();
				midifile_ = false;
			}
		}
		microsec_ += 16667;

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
