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


// #ifdef TFU
// #define OUT_TPU
#define OUT_MTU

#ifdef OUT_TPU
#include "common/tpu_io.hpp"
#endif

#ifdef OUT_MTU
#include "common/mtu_io.hpp"
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
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX71M" };
#elif defined(SIG_RX64M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX64M" };
#elif defined(SIG_RX65N)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;
	static const char* system_str_ = { "RX65N" };
#elif defined(SIG_RX24T)
	typedef device::system_io<10000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX24T" };
#elif defined(SIG_RX66T)
	typedef device::system_io<10000000, 160000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX66T" };
#elif defined(SIG_RX72N)
	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;
	static const char* system_str_ = { "RX72N" };
#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
// SCI ポートの第二候補を選択する場合
//	typedef device::sci_io<SCI_CH, RXB, TXB, device::port_map::option::SECOND> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

#ifdef OUT_TPU
	typedef device::tpu_io<device::TPU4> TPU;
	TPU		tpu_;
#endif

#ifdef OUT_MTU
	typedef device::MTU4 MTU;
	typedef device::mtu_io<MTU> MTU_IO;
	MTU_IO	mtu_io_;
#endif

//	typedef device::PORT<device::PORTD, device::bitpos::B1> PD1;
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
	SYSTEM_IO::setup_system_clock();

	{  // タイマー設定
		uint8_t intr = 4;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		uint8_t intr = 2;        // 割り込みレベル
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	auto iclk = F_ICLK / 1000000;
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
		if(!mtu_io_.start_normal(MTU::channel::B, MTU_IO::OUTPUT_TYPE::TOGGLE, freq)) {
			utils::format("MTU4 not start...\n");
		} else {
			utils::format("MTU rate (set):  %d [Hz]\n") % mtu_io_.get_rate();
			auto rate = 1.0f - static_cast<float>(mtu_io_.get_rate()) / mtu_io_.get_rate(true);
			rate *= 100.0f;
			utils::format("MTU rate (real): %d [Hz] (%3.2f [%%])\n")
				% mtu_io_.get_rate(true) % rate;
		}
	}
#endif

	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

		if(sci_.recv_length() > 0) {
#ifdef TFU
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
#endif
		}

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
