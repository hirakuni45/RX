//=====================================================================//
/*! @file
    @brief  ファースト・サンプル（LED 点滅） @n
			RX64M, RX71M: @n
					12MHz のベースクロックを使用する @n
			　　　　P07 ピンにLEDを接続する @n
			RX65N (Renesas Envision kit RX65N): @n
					12MHz のベースクロックを使用する @n
			　　　　P70 に接続された LED を利用する @n
			RX63T @n
					12MHz のベースクロックを使用する @n
					PB7 に接続された LED を利用する @n
			RX24T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する @n
			RX66T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する
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
#include "common/cmt_mgr.hpp"
#include "common/vtx.hpp"
#include "common/command.hpp"
#include "common/input.hpp"

// #ifdef TFU
// #define OUT_TPU
// #define OUT_MTU
#define SCI_I2C

#ifdef OUT_TPU
#include "common/tpu_io.hpp"
#endif

#ifdef OUT_MTU
#include "common/mtu_io.hpp"
#endif

#ifdef SCI_I2C
#include "common/sci_i2c_io.hpp"
#include "chip/FT5206.hpp"
#endif

#if 0
extern "C" {
	void __init_tfu(void);
	void __builtin_rx_sincosf(float, float*, float*);
	void __builtin_rx_atan2hypotf(float, float, float*, float*);
	float __builtin_rx_sinf(float);
	float __builtin_rx_cosf(float);
	float __builtin_rx_atan2f(float, float);
	float __builtin_rx_hypotf(float, float);
};
#endif

namespace {

#if defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N" };
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;
#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N" };
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;
#endif
	typedef device::system_io<> SYSTEM_IO;

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

#ifdef OUT_TPU
	typedef device::tpu_io<device::TPU4> TPU;
	TPU		tpu_;
#endif

#ifdef OUT_MTU
	typedef device::MTU4 MTU;
	static const auto PSEL = device::port_map_mtu::ORDER::FIFTH;
	typedef device::mtu_io<MTU, utils::null_task, utils::null_task, PSEL> MTU_IO;
	MTU_IO	mtu_io_;
//	typedef device::PORT<device::PORTD, device::bitpos::B1> PD1;
#endif

#ifdef SCI_I2C
	// RX72N Envision kit touch panel
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	typedef utils::fixed_fifo<uint8_t, 64> RB64;
	typedef utils::fixed_fifo<uint8_t, 64> SB64;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::THIRD_I2C> FT5206_I2C;
	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> TOUCH;
	TOUCH	touch_(ft5206_i2c_);
#endif

	typedef utils::command<256> CMD;
	CMD		cmd_;

#ifdef OUT_MTU
	void list_mtu_freq_()
	{
		utils::format("MTU rate (set):  %d [Hz]\n") % mtu_io_.get_rate();
		auto rate = 1.0f - static_cast<float>(mtu_io_.get_rate()) / mtu_io_.get_rate(true);
		rate *= 100.0f;
		utils::format("MTU rate (real): %d [Hz] (%3.2f [%%])\n")
			% mtu_io_.get_rate(true) % rate;
	}
#endif
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

	{  // タイマー設定
		uint8_t intr = 4;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		uint8_t intr = 2;        // 割り込みレベル
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	auto iclk = device::clock_profile::ICLK / 1'000'000;
	utils::format("Start test for '%s' %d[MHz]\n") % system_str_ % iclk;

	{
		utils::format("SCI Baud rate (set):  %d\n") % sci_.get_baud_rate();
		float rate = 1.0f - static_cast<float>(sci_.get_baud_rate()) / sci_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("SCI Baud rate (real): %d (%3.2f [%%])\n") % sci_.get_baud_rate(true) % rate;
		utils::format("CMT rate (set):  %d [Hz]\n") % cmt_.get_rate();
		rate = 1.0f - static_cast<float>(cmt_.get_rate()) / cmt_.get_rate(true);
		rate *= 100.0f;
		utils::format("CMT rate (real): %d [Hz] (%3.2f [%%])\n") % cmt_.get_rate(true) % rate;
	}

	LED::OUTPUT();  // LED ポートを出力に設定

#ifdef TFU
	__init_tfu();
#endif

#ifdef OUT_TPU
	{
		// RX72N Envision Kit Pmod2.8(PD1)
		// MTIOC4B(TPU4,B)
		uint8_t intr = 0;
//		uint32_t freq = 10'000 * 2;  // トグル出力なので２倍
		uint32_t freq = 100;  // トグル出力なので２倍
		if(!tpu_.start(TPU::TYPE::MATCH_B, freq, intr, TPU::OUTPUT::IH_MT)) {
			utils::format("TPU4 not start...\n");
		} else {
			utils::format("TPU rate (set):  %d [Hz]\n") % tpu_.get_rate();
			auto rate = 1.0f - static_cast<float>(tpu_.get_rate()) / tpu_.get_rate(true);
			rate *= 100.0f;
			utils::format("TPU rate (real): %d [Hz] (%3.2f [%%])\n") % tpu_.get_rate(true) % rate;
		}
	}
//	PD1::OUTPUT();
#endif

#ifdef OUT_MTU
	{
		uint32_t freq = 10'000;
		if(!mtu_io_.start_normal(MTU::channel::B, MTU_IO::OUTPUT::TOGGLE, freq)) {
			utils::format("MTU4 not start...\n");
		} else {
			list_mtu_freq_();
		}
	}
#endif

#ifdef SCI_I2C
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
#endif

	cmd_.set_prompt("# ");


	if(0) {
		float a = 1.999999f;
		// printf("Value: %5.4f\n", (double)a);
		utils::format("Value: %8.7f\n") % a;
	}


	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

#ifdef TFU
		if(sci_.recv_length() > 0) {
			if(sci_.getch() == ' ') {
				float a = vtx::get_pi<float>() * 0.25f;
				float si, co;
				__builtin_rx_sincosf(a, &si, &co);
				utils::format("%8.7f: %8.7f, %8.7f\n") % a % si % co;
				a = vtx::get_pi<float>() * 1.75f;
				si = __builtin_rx_sinf(a);
				co = __builtin_rx_cosf(a);
				utils::format("%8.7f: %8.7f, %8.7f\n") % a % si % co;
			}
		}
#endif

#ifdef OUT_MTU
		if(cmd_.service()) {
			auto cmdn = cmd_.get_words();
			if(cmdn >= 2 && cmd_.cmp_word(0, "freq")) {
				char tmp[32];
				cmd_.get_word(1, tmp, sizeof(tmp));
				int freq = 100;
				if((utils::input("%d", tmp) % freq).status()) {
					if(freq < 100) {
						utils::format("Error Limit under 100[Hz]\n");
					} else {
						mtu_io_.set_freq(freq);
						list_mtu_freq_();
					}
				} else {
					utils::format("input error: '%s'\n") % tmp;
				}
			} else if(cmdn >= 1 && cmd_.cmp_word(0, "help")) {
				utils::format("freq FREQ[Hz]\n");
			} else if(cmdn >= 1) {
				char tmp[32];
				cmd_.get_word(0, tmp, sizeof(tmp));
				utils::format("Command error: '%s'") % tmp;
			}
		}
#endif

#ifdef SCI_I2C
touch_.update();
		{
			auto num = touch_.get_touch_num();
			if(num > 0) {
				utils::format("Touch num: %d\n") % num;
			}
		}
#endif
//		PD1::P = cnt & 1;

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
