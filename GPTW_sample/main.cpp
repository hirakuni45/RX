//=========================================================================//
/*! @file
    @brief  GPTW サンプル @n
			RX24T: @n
					10MHz のベースクロックを使用する @n
					P00 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX66T: @n
					10MHz のベースクロックを使用する @n
					P00 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX72N: (Renesas Envision kit RX72N) @n
					16MHz のベースクロックを使用する @n
					P40 ピンにLEDを接続する @n
					SCI2 を使用する @n
			RX72T: @n
					16MHz のベースクロックを使用する @n
					P01 ピンにLEDを接続する @n
					SCI1 を使用する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"
#include "common/command.hpp"

#include "common/format.hpp"
#include "common/input.hpp"

#include "common/gptw_mgr.hpp"
#include "common/hrpwm_mgr.hpp"

namespace {

#if defined(SIG_RX66T)
	typedef device::GPTW0 GPTW_CH;
	const auto ORDER_A = device::port_map_gptw::ORDER::FIRST;
	const auto ORDER_B = device::port_map_gptw::ORDER::FIRST;
#elif defined(SIG_RX72N)
	/// PMOD Connector: PD0(CN6-7), PD1(CN6-8)
	typedef device::GPTW1 GPTW_CH;
	const auto ORDER_A = device::port_map_gptw::ORDER::FOURTH;
	const auto ORDER_B = device::port_map_gptw::ORDER::FOURTH;
#elif defined(SIG_RX72T)
	typedef device::GPTW0 GPTW_CH;
	const auto ORDER_A = device::port_map_gptw::ORDER::FIRST;
	const auto ORDER_B = device::port_map_gptw::ORDER::FIRST;

	#define USE_HRPWM
#endif

	// 位相計数モードの実験を行う場合有効にする
	#define INPUT_PHASE

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義
	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT;
	CMT		cmt_;

	typedef utils::command<256> CMD;
	CMD 	cmd_;

	typedef device::gptw_mgr<GPTW_CH, utils::null_task> GPTW;
	GPTW	gptw_;

#ifndef INPUT_PHASE
#ifdef USE_HRPWM
	typedef device::hrpwm_mgr<device::HRPWM> HRPWM;
	HRPWM	hrpwm_;
#endif
#endif

	float	duty_a_;
	float	duty_b_;

	int32_t	phase_cnt_;
}


extern "C" {

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

	{  // タイマー設定（100Hz）
		auto intr = device::ICU::LEVEL::_4;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 115'200;  // ボーレート（任意の整数値を指定可能）
		sci_.start(baud, intr);  // 標準では、８ビット、１ストップビットを選択
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("Start GPTW sample for '%s' %d[MHz]\n") % system_str_ % clk;

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

	{  // GPTW の開始
#ifdef INPUT_PHASE
		// input phase A/B
		if(gptw_.start(GPTW::PHASE_MODE::AB_ENC, ORDER_A, ORDER_B)) {
			utils::format("GPTW%d start: input phase\n") % GPTW::value_type::CHANNEL_NO;
			phase_cnt_ = gptw_.get_cnt();
		} else {
			utils::format("GPTW%d start fail...\n") % GPTW::value_type::CHANNEL_NO;
		}
#else
		//  PWM / AB 出力、割り込みは使わない、バッファー動作
		uint32_t freq = 100'000;  // 100KHz
		if(gptw_.start(GPTW::MODE::PWM_S_HL, GPTW::OUTPUT::AB, freq, ORDER_A, ORDER_B)) {
			utils::format("GPTW%d start: freq: %u [Hz]\n") % GPTW::value_type::CHANNEL_NO % freq;
			duty_a_ = 0.33f;
			gptw_.set_duty_a(duty_a_);
			duty_b_ = 0.66f;
			gptw_.set_duty_b(duty_b_);
		} else {
			utils::format("GPTW%d start fail...\n") % GPTW::value_type::CHANNEL_NO;
		}
#endif
	}

#ifndef INPUT_PHASE
#ifdef USE_HRPWM
	{  // HRPWM の開始 (Enable: GPTW0, Disable: GPTW1, GPTW2, GPTW3)
		if(hrpwm_.start(true, false, false, false)) {
			utils::format("HRPWM start: \n");
		} else {
			utils::format("HRPWM start fail...\n");
		}
	}
#endif
#endif

#ifndef INPUT_PHASE
	cmd_.set_prompt("# ");
#endif

	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

#ifdef INPUT_PHASE
		auto v = gptw_.get_cnt();
		if(v != phase_cnt_) {
			phase_cnt_ = v;
			utils::format("%d\n") % phase_cnt_;
		}
#else
		if(cmd_.service()) {
			uint32_t cmdn = cmd_.get_words();
			if(cmdn > 0) {
				if(cmd_.cmp_word(0, "a")) {
					if(cmdn >= 2) {
						char tmp[64];
						cmd_.get_word(1, tmp, sizeof(tmp));
						float v = 0.0f;
						if((utils::input("%f", tmp) % v).status()) {
							if(v >= 0.0f && v <= 1.0f) {
								duty_a_ = v;
								gptw_.set_duty_a(duty_a_);
							} else {
								utils::format("A: Over range: %4.3f\n") % v;
							}
						}
					} else {
						utils::format("A: duty: %4.3f\n") % duty_a_;
					}
				} else if(cmd_.cmp_word(0, "b")) {
					if(cmdn >= 2) {
						char tmp[64];
						cmd_.get_word(1, tmp, sizeof(tmp));
						float v = 0.0f;
						if((utils::input("%f", tmp) % v).status()) {
							if(v >= 0.0f && v <= 1.0f) {
								duty_b_ = v;
								gptw_.set_duty_b(duty_b_);
							} else {
								utils::format("B: Over range: %4.3f\n") % v;
							}
						}
					} else {
						utils::format("B: duty: %4.3f\n") % duty_b_;
					}
				} else if(cmd_.cmp_word(0, "help")) {
					utils::format("    a [duty]     list duty A [set duty A (0 to 1.0)]\n");
					utils::format("    b [duty]     list duty B [set duty B (0 to 1.0)]\n");
					utils::format("    help\n");
				} else {
					char tmp[256];
					cmd_.get_word(0, tmp, sizeof(tmp));
					utils::format("Command error: '%s'\n") % tmp;
				}
			}
		}
#endif

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
		}
		if(cnt < 25) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
