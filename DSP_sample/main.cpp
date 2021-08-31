//=====================================================================//
/*! @file
    @brief  RX DSP サンプル @n
			RX64M, RX71M: @n
					12MHz のベースクロックを使用する @n
			　　　　P07 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX65N (Renesas Envision kit RX65N): @n
					12MHz のベースクロックを使用する @n
			　　　　P70 に接続された LED を利用する @n
					SCI9 を使用する @n
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
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
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
#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T" };
	typedef device::PORT<device::PORT0, device::bitpos::B1> LED;
	typedef device::SCI1 SCI_CH;
#endif
// クロックの定義は、「RXxxx/clock_profile.hpp」を参照。
	typedef device::system_io<> SYSTEM_IO;

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
// SCI ポートの第二候補を選択する場合
//	typedef device::sci_io<SCI_CH, RXB, TXB, device::port_map::ORDER::SECOND> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

	const uint32_t PARAM_SIZE = 1024;
	int32_t	parama_[PARAM_SIZE];
	int32_t	paramb_[PARAM_SIZE];

	int32_t dsp_opr_(uint32_t loop)
	{
#ifdef __RXV3__
		__mvtacgu_a0(0);
#endif
		__mvtachi_a0(0);
		__mvtaclo_a0(0);
		for(uint32_t i = 0; i < loop; ++i) {
			auto a = parama_[i % PARAM_SIZE];
			auto b = paramb_[i % PARAM_SIZE];
			__emaca_a0(a, b);
		}
		return __mvfaclo_s0_a0();
	}


	int32_t cpu_opr_(uint32_t loop)
	{
		int32_t sum = 0;
		for(uint32_t i = 0; i < loop; ++i) {
			auto a = parama_[i % PARAM_SIZE];
			auto b = paramb_[i % PARAM_SIZE];
			sum += a * b;
		}
		return sum;
	}
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

	{  // タイマー設定（1000Hz）
		uint8_t intr = 4;
		cmt_.start(1000, intr);
	}

	{  // SCI の開始
		uint8_t intr = 2;        // 割り込みレベル（０を指定すると、ポーリング動作になる）
		uint32_t baud = 115200;  // ボーレート（任意の整数値を指定可能）
		sci_.start(baud, intr);  // 標準では、８ビット、１ストップビットを選択
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("Start DSP sample for '%s' %d[MHz]\n") % system_str_ % clk;

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

	cmt_.sync();

	for(uint32_t i = 0; i < PARAM_SIZE; ++i) {
		parama_[i] = rand() & 0x8fffffff;
		paramb_[i] = rand() & 0x8fffffff;
	}

	uint32_t loop = 50000000;
	{
		auto st = cmt_.get_counter();
		auto a = dsp_opr_(loop);
		auto et = cmt_.get_counter();
		utils::format("DSP %d loops: ans = %d, (%u [ms])\n") % loop % a % (et - st); 
	}

	{
		auto st = cmt_.get_counter();
		auto a = cpu_opr_(loop);
		auto et = cmt_.get_counter();
		utils::format("CPU %d loops: ans = %d, (%u [ms])\n") % loop % a % (et - st); 
	}

	uint16_t cnt = 0;
	while(1) {
		cmt_.sync();

		++cnt;
		if(cnt >= (50 * 10)) {
			cnt = 0;
		}
		if(cnt < (25 * 10)) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
