//=========================================================================//
/*! @file
    @brief  SCI (UART) 調歩同期モード、シリアル通信、サンプル @n
			基本的な接続は RXxxx/board_profile.hpp を参照の事 @n
			RX64M/RX71M に搭載された、SCIF を利用する場合、「scif_io」クラスを利用。 @n
			RX26T/RX671 などに搭載された、RSCI を利用する場合、「rsci_io」クラスを利用。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/scif_io.hpp"
#include "common/rsci_io.hpp"
#include "common/cmt_mgr.hpp"
#include "common/cmtw_mgr.hpp"
// #include "common/tmr_mgr.hpp"
#include "common/command.hpp"

#include "common/format.hpp"
#include "common/input.hpp"

// debug monitor を有効にする場合
// #define MEMORY_MONITOR

#ifdef MEMORY_MONITOR
#include "common/monitor.hpp"
#endif

#ifdef __TFU
// TFU の実験コードを有効にする場合
// #define TEST_TFU
#endif

namespace {

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義
	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI_IO;
// SCIF を使う場合：
//	typedef device::scif_io<device::SCIF8, RXB, TXB, board_profile::SCI_ORDER> SCI_IO;
// RSCI を使う場合：
//	typedef device::rsci_io<device::RSCI8, RXB, TXB, board_profile::SCI_ORDER> SCI_IO;
	SCI_IO	sci_io_;

// CMTW を使う場合：
//	typedef device::cmtw_mgr<device::CMTW0> CMT;
// TMR を使う場合：
//	typedef device::tmr_mgr<device::TMR0> CMT;
	typedef device::cmt_mgr<board_profile::CMT_CH> CMT_MGR;
	CMT_MGR	cmt_mgr_;

#ifdef MEMORY_MONITOR
	static constexpr uint32_t S_NUM = 64;
	typedef utils::monitor<S_NUM> MONITOR;
	MONITOR	monitor_;
#else
	typedef utils::command<256> CMD;
	CMD 	cmd_;
#endif

	void halt_()
	{
		using namespace board_profile;

		LED::DIR = 1;
		while(1) {
			LED::P = 0;
			utils::delay::milli_second(100);
			LED::P = 1;
			utils::delay::milli_second(100);
		}
	}
}

extern "C" {

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		sci_io_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_io_.puts(str);
	}

	// syscalls.c から呼ばれる、標準入力（stdin）
	char sci_getch(void)
	{
		return sci_io_.getch();
	}

	uint16_t sci_length()
	{
		return sci_io_.recv_length();
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	using namespace board_profile;

	{  // SCI の開始
		constexpr uint32_t baud = 115200;  // ボーレート（任意の整数値を指定可能）
		static_assert(SCI_IO::probe_baud(baud), "Failed baud rate accuracy test");  // 許容誤差（3%）を超える場合、コンパイルエラー
		auto intr = device::ICU::LEVEL::_2;		// 割り込みレベル（NONE を指定すると、ポーリング動作になる）
		if(!sci_io_.start(baud, intr)) {  // 標準では、８ビット、１ストップビットを自動選択
			halt_();
		}
// 通信プロトコルを設定する場合は、通信プロトコルのタイプを指定する事が出来る。
// sci_io.hpp PROTOCOL enum class のタイプを参照
//		sci_.start(baud, intr, SCI::PROTOCOL::B8_E_1S);
	}

	{  // タイマー設定（100Hz）
		constexpr uint32_t freq = 100;
		static_assert(CMT_MGR::probe_freq(freq), "Failed CMT rate accuracy test");
		if(!cmt_mgr_.start(freq, device::ICU::LEVEL::_4)) {
			utils::format("CMT not start!\n");
		}
	}

	{
		auto clk = device::clock_profile::ICLK / 1'000'000;
		utils::format("\nStart SCI (UART) sample for '%s' %d[MHz]\n") % system_str_ % clk;
	}

	{  // SCI/CMT の設定レポート表示
		utils::format("SCI PCLK: %u [Hz]\n") % SCI_IO::sci_type::PCLK;
		utils::format("SCI Baud rate (set): %u [BPS]\n") % sci_io_.get_baud_rate();
		float rate = 1.0f - static_cast<float>(sci_io_.get_baud_rate()) / sci_io_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("  Baud rate (real): %u (%3.2f [%%])\n") % sci_io_.get_baud_rate(true) % rate;
		utils::format("  SEMR_BRME: %s\n") % utils::str::get_bool_text(SCI_IO::sci_type::SEMR_BRME);
		utils::format("  SEMR_BGDM: %s\n") % utils::str::get_bool_text(SCI_IO::sci_type::SEMR_BGDM);
		utils::format("CMT Timer (set):  %d [Hz]\n") % cmt_mgr_.get_rate();
		rate = 1.0f - static_cast<float>(cmt_mgr_.get_rate()) / cmt_mgr_.get_rate(true);
		rate *= 100.0f;
		utils::format("  Timer (real): %d [Hz] (%3.2f [%%])\n") % cmt_mgr_.get_rate(true) % rate;
	}

#ifndef MEMORY_MONITOR
	cmd_.set_prompt("# ");
	utils::format("\nerror      list SCI-error count\n");
	utils::format("reset      reset SCI-error count\n");
#endif

#ifdef TEST_TFU
	{
		auto a = 3.1415926535897932384626433832795f * 0.25f;
		auto si = __builtin_rx_sinf(a);
		auto co = __builtin_rx_cosf(a);
		utils::format("%.7f, %.7f\n") % si % co;
	}
#endif

	LED::DIR = 1;
	LED::P = 0;

#if 0
	// sci_io クラスは、オペレーターをオーバーロードしているので、以下のように文字を直接入出力する事も出来る。
	sci_io_ = 'A';
	sci_io_ = "ABC\n";
	auto ch = sci_io_();
	sci_io_ = ch;
#endif

	uint8_t cnt = 0;
	while(1) {
		cmt_mgr_.sync();
#ifdef MEMORY_MONITOR
		monitor_.service();
#else
		if(cmd_.service()) {
			uint32_t cmdn = cmd_.get_words();
			uint32_t n = 0;
			while(n < cmdn) {
				if(cmd_.cmp_word(n, "error")) {
					utils::format("SCI ORER err: %d\n") % static_cast<int>(SCI_IO::get_orer_count());
					utils::format("SCI FER err: %d\n") % static_cast<int>(SCI_IO::get_fer_count());
					utils::format("SCI PER err: %d\n") % static_cast<int>(SCI_IO::get_per_count());
				} else if(cmd_.cmp_word(n, "reset")) {
					SCI_IO::reset_err_count();
				} else {
					char tmp[256];
					if(cmd_.get_word(n, tmp, sizeof(tmp))) {
						utils::format("Param%d: '%s'\n") % n % tmp;
					}
				}
				++n;
			}
		}
#endif
		++cnt;
		auto n = SCI_IO::get_orer_count() + SCI_IO::get_fer_count() + SCI_IO::get_per_count();
		uint8_t thc = 50;
		if(n > 0) {
			thc = 20;
		}
		if(cnt >= thc) {
			cnt = 0;
		}
		if(cnt < (thc / 2)) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
