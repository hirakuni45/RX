//=====================================================================//
/*! @file
    @brief  SCI (UART) サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2022 Kunihito Hiramatsu @n
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

#include "common/monitor.hpp"

// debug monitor を有効にする場合
// #define MEMORY_MONITOR

namespace {

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義

#if defined(SIG_RX220)
	// 秋月 RX220 ボード
	static const char* system_str_ = { "AE-RX220" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B3, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB, device::port_map::ORDER::SECOND> SCI;
#elif defined(SIG_RX63T)
	// DIY RX63T board
	static const char* system_str_ = { "RX63T DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORTB, device::bitpos::B7, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX62N)
  #if defined(CQ_FRK)
    // FRK-RX62N(CQ 出版社)
	static const char* system_str_ = { "RX62N FRK-RX62N" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT1, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
  #else
    // BlueBoard-RX62N_100pin
	static const char* system_str_ = { "RX62N BlueBoard-RX62N_100pin" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
  #endif
#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N Envision Kit" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT7, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI9, RXB, TXB> SCI;
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T DIY" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B1, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI1, RXB, TXB> SCI;
#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N Envision Kit" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT4, device::bitpos::B0, LED_ACTIVE> LED;
	typedef device::sci_io<device::SCI2, RXB, TXB> SCI;
#endif

	SCI		sci_;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

#ifdef MEMORY_MONITOR
	static constexpr uint32_t S_NUM = 64;
	typedef utils::monitor<S_NUM> MONITOR;
	MONITOR	monitor_;
#else
	typedef utils::command<256> CMD;
	CMD 	cmd_;
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

	{  // タイマー設定（100Hz）
		cmt_.start(100, device::ICU::LEVEL::_4);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_2;		// 割り込みレベル（０を指定すると、ポーリング動作になる）
		uint32_t baud = 115200;  // ボーレート（任意の整数値を指定可能）
		sci_.start(baud, intr);  // 標準では、８ビット、１ストップビットを選択
// 通信プロトコルを設定する場合は、通信プロトコルのタイプを指定する事が出来る。
// sci_io.hpp PROTOCOL enum class のタイプを参照
//		sci_.start(baud, intr, SCI::PROTOCOL::B8_E_1S);
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("\nStart SCI (UART) sample for '%s' %d[MHz]\n") % system_str_ % clk;
	{  // SCI/CMT の設定レポート表示
		utils::format("SCI PCLK: %u [Hz]\n") % SCI::sci_type::PCLK;
		utils::format("SCI Baud rate (set): %u [BPS]\n") % sci_.get_baud_rate();
		float rate = 1.0f - static_cast<float>(sci_.get_baud_rate()) / sci_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("  Baud rate (real): %u (%3.2f [%%])\n") % sci_.get_baud_rate(true) % rate;
		utils::format("  SEMR_BRME: %s\n") % utils::str::get_bool_text(SCI::sci_type::SEMR_BRME);
		utils::format("  SEMR_BGDM: %s\n") % utils::str::get_bool_text(SCI::sci_type::SEMR_BGDM);
		utils::format("CMT Timer (set):  %d [Hz]\n") % cmt_.get_rate();
		rate = 1.0f - static_cast<float>(cmt_.get_rate()) / cmt_.get_rate(true);
		rate *= 100.0f;
		utils::format("  Timer (real): %d [Hz] (%3.2f [%%])\n") % cmt_.get_rate(true) % rate;
	}

#ifndef MEMORY_MONITOR
	cmd_.set_prompt("# ");
#endif

	LED::DIR = 1;
	LED::P = 0;

	uint8_t cnt = 0;
	while(1) {

		cmt_.sync();
#ifdef MEMORY_MONITOR
		monitor_.service();
#else
		if(cmd_.service()) {
			uint32_t cmdn = cmd_.get_words();
			uint32_t n = 0;
			while(n < cmdn) {
				char tmp[256];
				if(cmd_.get_word(n, tmp, sizeof(tmp))) {
					utils::format("Param%d: '%s'\n") % n % tmp;
				}
				++n;
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
