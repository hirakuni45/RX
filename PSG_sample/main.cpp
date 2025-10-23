//=====================================================================//
/*! @file
    @brief  PSG サンプル @n
			PSG 音源エミュレートによる音楽演奏
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
#include "sound/dac_stream_intr.hpp"
#include "sound/psg_mng.hpp"

#include "score.hpp"

namespace {

	// サンプリング周波数が 48KHz で 1/100 毎にサービスするので、
	// 1 ターンは 480 サンプルなので、その倍以上を必要とする。
	static constexpr uint32_t FIFO_NUM = 1024;

#if defined(SIG_RX140)
	// D/A 出力では、無音出力は、中間電圧とする。
	// 割り込みでの直接出力の場合、OUTSは １ 固定
	typedef sound::sound_out<int8_t, FIFO_NUM, 1> SOUND_OUT;
	static const int8_t ZERO_LEVEL = 0x80;

	// 割り込み毎に D/A 出力
	typedef device::DA DAC;

#elif defined(SIG_RX231)
	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, FIFO_NUM, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#elif defined(SIG_RX62N)
	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, FIFO_NUM, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::DA DAC;

#elif defined(SIG_RX631)
	// RX631 GR-CITRUS board
	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, FIFO_NUM, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::DA DAC;

#elif defined(SIG_RX71M)
	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, FIFO_NUM, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#elif defined(SIG_RX64M)
	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, FIFO_NUM, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#elif defined(SIG_RX65N)
	typedef device::PORT<device::PORT0, device::bitpos::B5, false> SW2;

	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, FIFO_NUM, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;
	#define USE_SW2

#elif defined(SIG_RX26T)
	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, FIFO_NUM, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#elif defined(SIG_RX66T)
	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, FIFO_NUM, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#elif defined(SIG_RX72N)
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> SW2;

	// SSIE の FIFO サイズの２倍以上（1024）
	typedef sound::sound_out<int16_t, FIFO_NUM, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x0000;

	#define USE_SSIE
	#define USE_SW2

#elif defined(SIG_RX72T)
	// D/A 出力では、無音出力は、中間電圧とする。
	typedef sound::sound_out<int16_t, FIFO_NUM, 1024> SOUND_OUT;
	static const int16_t ZERO_LEVEL = 0x8000;

	#define USE_DAC
	typedef device::R12DA DAC;

#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義
	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT;
	CMT		cmt_;

	typedef utils::command<256> CMD;
	CMD 	cmd_;

	// サウンド出力コンテキスト
	SOUND_OUT	sound_out_(ZERO_LEVEL);

	static constexpr uint16_t SAMPLE = 48'000;  // サンプリング周期
	static constexpr uint16_t TICK = 100;	// サンプルの楽曲では、１００を前提にしている。
	static constexpr uint16_t CNUM = 3;		// 同時発音数（大きくすると処理負荷が増えるので注意）
	typedef utils::psg_mng<SAMPLE, TICK, CNUM> PSG_MNG;
	PSG_MNG		psg_mng_;

#if defined(USE_DAC)
	/// DMA 転送先、DMA 起動を行うタイマー(MTU0)、DMA チャネルなどを指定
	typedef sound::dac_stream<DAC, device::MTU0, device::DMAC0, SOUND_OUT> DAC_STREAM;
	DAC_STREAM	dac_stream_(sound_out_);

	void start_audio_() noexcept
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
#elif defined(USE_SSIE)
	typedef device::ssie_io<device::SSIE1, device::DMAC1, SOUND_OUT> SSIE_IO;
	SSIE_IO		ssie_io_(sound_out_);

	void start_audio_() noexcept
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
#else
	// タイマー割り込みを使って転送
	typedef sound::dac_stream_intr<DAC, device::MTU0, SOUND_OUT> DAC_STREAM;
	DAC_STREAM	dac_stream_(sound_out_);

	void start_audio_() noexcept
	{
		auto timer_intl  = device::ICU::LEVEL::_5;
		uint32_t freq = 48'000;
		if(dac_stream_.start(freq, timer_intl)) {
			utils::format("Start D/A Stream (intr): %u Hz\n") % freq;
		} else {
			utils::format("D/A Stream not start (intr) ...\n");
		}
	}
#endif
}


extern "C" {

	void set_sample_rate(uint32_t freq)
	{
#if defined(USE_DAC)
		dac_stream_.set_sample_rate(freq);
#elif defined(USE_SSIE)
		sound_out_.set_output_rate(freq);
#else

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

	using namespace board_profile;

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
		utils::format("SCI PCLK: %u\n") % SCI::peripheral_type::PCLK;
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

	psg_mng_.set_score(0, score::_0);
	psg_mng_.set_score(1, score::_1);

#ifdef USE_SW2
	SW2::INPUT();
	bool lvl = SW2::P();
#endif

	uint8_t delay = 200;

	cmt_.sync();
	cmt_.sync();
	uint32_t avg = 0;
	uint32_t pos = sound_out_.get_sample_pos();
	uint32_t min = SOUND_OUT::OUTS_SIZE;
	uint32_t max = 0;

	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

		{  // 減った分を追加する。
			auto newpos = sound_out_.get_sample_pos();
			auto n = newpos - pos;
			n &= SOUND_OUT::OUTS_SIZE - 1;

			if(min > n) min = n;
			if(max < n) max = n;
			if(avg != n) {
				avg = n;
//				utils::format("%u (min: %u, max: %u)\n") % avg % min % max;
			}

			pos = newpos;
			int8_t tmp[n];
			psg_mng_.render(n, tmp);
			for(uint32_t i = 0; i < n; ++i) {
				auto w = tmp[i];
				typename SOUND_OUT::WAVE t;
				if(sizeof(SOUND_OUT::value_type) > 1) {
					t.set((static_cast<int16_t>(w) << 8) | ((w & 0x7f) << 1));
				} else {
					t.set(w);
				}
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
				psg_mng_.set_score(0, score::_0);
				psg_mng_.set_score(1, score::_1);
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
