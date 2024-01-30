//=====================================================================//
/*! @file
    @brief  PSG サンプル @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"
#include "common/command.hpp"

#include "common/format.hpp"
#include "common/input.hpp"

#include "sound/sound_out.hpp"
#include "sound/dac_stream.hpp"
#include "sound/psg_mng.hpp"

namespace {

#if defined(SIG_RX231)
	static const char* system_str_ = { "RX231 DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT4, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::SECOND;

	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, 4096, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#elif defined(SIG_RX62N)
  #if defined(CQ_FRK)
    // FRK-RX62N(CQ 出版社)
	static const char* system_str_ = { "RX62N FRK-RX62N" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT1, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::FIRST;
  #else
    // BlueBoard-RX62N_100pin
	static const char* system_str_ = { "RX62N BlueBoard-RX62N_100pin" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::FIRST;
  #endif

	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, 4096, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::DA DAC;

#elif defined(SIG_RX631)
	// RX631 GR-CITRUS board
	static const char* system_str_ = { "RX631 GR-CITRUS" };
	// GR-CITRUS
	static constexpr bool LED_ACTIVE = 1;
	typedef device::PORT<device::PORTA, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::SECOND;

	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, 4096, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::DA DAC;

#elif defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> LED;
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::FIRST;

	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, 4096, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> LED;
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::FIRST;

	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, 4096, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N DIY" };
	typedef device::PORT<device::PORT7, device::bitpos::B0, false> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B5, false> SW2;
	typedef device::SCI9 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::FIRST;

	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, 4096, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;
	#define USE_SW2

#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::FIRST;

#elif defined(SIG_RX26T)
	static const char* system_str_ = { "RX26T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::FIRST;

	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, 4096, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::FIRST;

	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, 4096, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N DIY" };
	typedef device::PORT<device::PORT4, device::bitpos::B0, false> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> SW2;
	typedef device::SCI2 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::FIRST;

	// SSIE の FIFO サイズの２倍以上（1024）
	typedef sound::sound_out<int16_t, 4096, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x0000;

	#define USE_SSIE
	#define USE_SW2

#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B1, false> LED;
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_PORT = device::port_map::ORDER::FIRST;

	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, 4096, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB, SCI_PORT> SCI;

	SCI		sci_;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

	typedef utils::command<256> CMD;
	CMD 	cmd_;

	// サウンド出力コンテキスト
	SOUND_OUT	sound_out_(ZERO_LEVEL);

	static constexpr uint16_t SAMPLE = 48'000;  // サンプリング周期
	static constexpr uint16_t TICK = 100;	// サンプルの楽曲では、１００を前提にしている。
	static constexpr uint16_t CNUM = 3;		// 同時発音数（大きくすると処理負荷が増えるので注意）
	typedef utils::psg_base PSG;
	typedef utils::psg_mng<SAMPLE, TICK, CNUM> PSG_MNG;
	PSG_MNG		psg_mng_;


#ifdef USE_DAC
	typedef sound::dac_stream<DAC, device::MTU0, device::DMAC0, SOUND_OUT> DAC_STREAM;
	DAC_STREAM	dac_stream_(sound_out_);

	void start_audio_()
	{
		auto dmac_intl = device::ICU::LEVEL::_4;
		auto timer_intl  = device::ICU::LEVEL::_5;
		uint32_t freq = 48'000;
		if(dac_stream_.start(freq, dmac_intl, timer_intl)) {
			utils::format("Start D/A Stream: %u Hz\n") % freq;
		} else {
			utils::format("D/A Stream not start...\n");
		}
	}
#endif

#ifdef USE_SSIE
	typedef device::ssie_io<device::SSIE1, device::DMAC1, SOUND_OUT> SSIE_IO;
	SSIE_IO		ssie_io_(sound_out_);

	void start_audio_()
	{
		{  // SSIE 設定 RX72N Envision kit では、I2S, 48KHz, 32/16 ビットフォーマット固定
			auto intr = device::ICU::LEVEL::_5;
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

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	// syscalls.c から呼ばれる、標準入力（stdin）
	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length()
	{
		return sci_.recv_length();
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	{
		auto intr = device::ICU::LEVEL::_4;
		cmt_.start(TICK, intr);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 115200;  // ボーレート（任意の整数値を指定可能）
		sci_.start(baud, intr);  // 標準では、８ビット、１ストップビットを選択
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("Start PSG sample for '%s' %d[MHz]\n") % system_str_ % clk;

	LED::DIR = 1;
	LED::P = 0;

	{
		utils::format("SCI PCLK: %u\n") % SCI_CH::PCLK;
		utils::format("SCI Baud rate (set):  %u\n") % sci_.get_baud_rate();
		float rate = 1.0f - static_cast<float>(sci_.get_baud_rate()) / sci_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("SCI Baud rate (real): %u (%3.2f [%%])\n") % sci_.get_baud_rate(true) % rate;
		utils::format("CMT rate (set):  %d [Hz]\n") % cmt_.get_rate();
		rate = 1.0f - static_cast<float>(cmt_.get_rate()) / cmt_.get_rate(true);
		rate *= 100.0f;
		utils::format("CMT rate (real): %d [Hz] (%3.2f [%%])\n") % cmt_.get_rate(true) % rate;
	}

	cmd_.set_prompt("# ");

	start_audio_();

	{  // サンプリング周期設定
		set_sample_rate(SAMPLE);
	}

	psg_mng_.set_score(0, score0_);
	psg_mng_.set_score(1, score1_);

#ifdef USE_SW2
	SW2::INPUT();
	bool lvl = SW2::P();
#endif

	uint8_t delay = 200;

	cmt_.sync();
	cmt_.sync();
	uint32_t avg = 0;
	uint32_t pos = sound_out_.get_sample_pos();
	uint32_t min = sound_out_.get_sample_size();
	uint32_t max = 0;

	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

		{  // 減った分を追加する。
			auto newpos = sound_out_.get_sample_pos();
			auto n = newpos - pos;
			n &= sound_out_.get_sample_size() - 1;

			if(min > n) min = n;
			if(max < n) max = n;
			if(avg != n) {
				avg = n;
//				utils::format("%u (min: %u, max: %u)\n") % avg % min % max;
			}

			pos = newpos;
			int8_t tmp[n];
			psg_mng_.render(n, tmp);
			typename SOUND_OUT::WAVE t;
			for(uint32_t i = 0; i < n; ++i) {
				auto w = tmp[i];
				t.l_ch = t.r_ch = (static_cast<int16_t>(w) << 8) | ((w & 0x7f) << 1);
				sound_out_.at_fifo().put(t);
			}

			if(delay > 0) {
				delay--;
			} else {
				psg_mng_.service();
			}
		}

#ifdef USE_SW2
		{
			auto tmp = SW2::P();
			if(!lvl && tmp) {
				utils::format("Music restart\n");
				psg_mng_.set_score(0, score0_);
				psg_mng_.set_score(1, score1_);
				delay = 100;
			}
			lvl = tmp;
		}
#endif

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
			avg = 0;
		}
		if(cnt < 25) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
