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
#include "common/cmt_io.hpp"

#include "common/fixed_string.hpp"

/// #include <iostream>

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
#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
// SCI ポートの第二候補を選択する場合
//	typedef device::sci_io<SCI_CH, RXB, TXB, device::port_map::option::SECOND> SCI;
	SCI		sci_;

	device::cmt_io<device::CMT0, utils::null_task>  cmt_;
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
		cmt_.start(850, intr);
	}


	{  // SCI の開始
		uint8_t intr = 2;        // 割り込みレベル
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	auto iclk = F_ICLK / 1000000;
	utils::format("Start test for '%s' %d[MHz]\n") % system_str_ % iclk;


#if 0
	utils::STR16 str;

	str = "asdfg";

	for(const auto ch : str) {
		utils::format("%c") % ch;
	}
	utils::format("\n");


	utils::STR16 a("012");
	utils::STR16 b("013");

	utils::format("a: '%s'\n") % a.c_str();
	utils::format("b: '%s'\n") % b.c_str();
	{
		int a_eq_b = a == b;
		utils::format("a.EQ.b: %d\n") % a_eq_b;
	}
	{
		int a_eq_b = a == "013";
		utils::format("a.EQ.\"013\": %d\n") % a_eq_b;
	}

	int a_lt_b = a < b;
	utils::format("a.LT.b: %d\n") % a_lt_b;

	int a_gt_b = a > b;
	utils::format("a.GT.b: %d\n") % a_gt_b;

//	if(a > b) utils::format("a < b: %d\n") % (a > b);
#endif

///	std::cout << "Hello!" << std::endl;
///	utils::format("Hello!\n");
///	printf("Hello!\n");

	LED::OUTPUT();  // LED ポートを出力に設定
	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

		if(sci_.recv_length() > 0) {
			if(sci_.getch() == ' ') {
				utils::format("Freq  (set): %u Hz\n") % cmt_.get_rate();
				utils::format("Freq (real): %u Hz\n") % cmt_.get_rate(true);
			}
		}

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
