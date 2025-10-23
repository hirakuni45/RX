//=========================================================================//
/*! @file
    @brief  MANDELBROT サンプル @n
			http://radiopench.blog96.fc2.com/blog-entry-1150.html @n
			「ラジオペンチ」さんが行っているマンデルブロベンチマークをＲＸマイコンに移植したもの @n
			- 元は Arduino のスケッチを元にしている。(mandelbrot.hpp を参照) @n
			- 部分的に自分の C++ フレームワーク都合で変更している @n
			- 時間計測は、Arduino と同等の 250KHz(4us) で行っている @n
			- RX231 では、クロックの関係で 250KHz が設定不可な為 125KHz としている @n
			基本的な接続は RXxxx/board_profile.hpp を参照の事
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"
#include "common/format.hpp"
#include "common/string_utils.hpp"
#include "mandelbrot.hpp"

namespace {

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義
	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI_IO;
	SCI_IO	sci_io_;

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT_MGR;
	CMT_MGR	cmt_mgr_;

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

	mandelbrot m_;

#if defined(SIG_RX231)
	static constexpr uint32_t TIME_RESO = 125'000;
	static constexpr uint32_t TIME_MULTI = 8;
#else
	static constexpr uint32_t TIME_RESO = 250'000;
	static constexpr uint32_t TIME_MULTI = 4;
#endif
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

	uint32_t micros()
	{
		return cmt_mgr_.get_counter() * TIME_MULTI;
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
	}

	{  // タイマー設定
		constexpr uint32_t freq = TIME_RESO;
		static_assert(CMT_MGR::probe_freq(freq), "Failed CMT rate accuracy test");
		if(!cmt_mgr_.start(freq, device::ICU::LEVEL::_4)) {
			utils::format("CMT not start!\n");
		}
	}

	{
		auto clk = device::clock_profile::ICLK / 1'000'000;
		utils::format("\nStart MANDELBROT sample for '%s' %d[MHz]\n") % system_str_ % clk;
	}

	{  // SCI/CMT の設定レポート表示
		utils::format("SCI PCLK: %u [Hz]\n") % SCI_IO::peripheral_type::PCLK;
		utils::format("SCI Baud rate (set): %u [BPS]\n") % sci_io_.get_baud_rate();
		float rate = 1.0f - static_cast<float>(sci_io_.get_baud_rate()) / sci_io_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("  Baud rate (real): %u (%3.2f [%%])\n") % sci_io_.get_baud_rate(true) % rate;
		utils::format("  SEMR_BRME: %s\n") % utils::str::get_bool_text(SCI_IO::peripheral_type::SEMR_BRME);
		utils::format("  SEMR_BGDM: %s\n") % utils::str::get_bool_text(SCI_IO::peripheral_type::SEMR_BGDM);
		utils::format("CMT Timer (set):  %d [Hz]\n") % cmt_mgr_.get_rate();
		rate = 1.0f - static_cast<float>(cmt_mgr_.get_rate()) / cmt_mgr_.get_rate(true);
		rate *= 100.0f;
		utils::format("  Timer (real): %d [Hz] (%3.2f [%%])\n") % cmt_mgr_.get_rate(true) % rate;
	}

	LED::DIR = 1;
	LED::P = 0;

	m_.setup();

	uint32_t cnt = 0;
	while(1) {

		cmt_mgr_.sync();

		++cnt;
		if(cnt >= 500'000 / TIME_MULTI) {
			cnt = 0;
		}
		if(cnt < 250'000 / TIME_MULTI) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
