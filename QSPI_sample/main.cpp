//=========================================================================//
/*! @file
    @brief  QSPI サンプル @n
			RX65N Envision kit, RX72N Envision kit に内蔵 @n
			QSPI 接続フラッシュメモリの読み書き等
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"
#include "common/qspi_io.hpp"
#include "common/command.hpp"

#include "common/format.hpp"
#include "common/input.hpp"

namespace {

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義
	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI_IO;
	SCI_IO	sci_io_;

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT_MGR;
	CMT_MGR	cmt_mgr_;

	typedef device::qspi_io<device::QSPI> QSPI_IO;
	QSPI_IO	qspi_io_(device::port_map_order::qspi_port_t(board_profile::QSPI_PORT));

	typedef utils::command<256> CMD;
	CMD 	cmd_;

}

extern "C" {

	void sci_putch(char ch)
	{
		sci_io_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_io_.puts(str);
	}

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

	{  // タイマー設定（100Hz）
		constexpr uint32_t freq = 100;
		static_assert(CMT_MGR::probe_freq(freq), "Failed CMT rate accuracy test");
		cmt_mgr_.start(freq, device::ICU::LEVEL::_4);
	}

	{  // SCI の開始
		constexpr uint32_t baud = 115200;
		static_assert(SCI_IO::probe_baud(baud), "Failed baud rate accuracy test");
		auto intr = device::ICU::LEVEL::_2;
		sci_io_.start(baud, intr);
	}

	{  // QSPI の開始
//		qspi_io_.start();
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("\nStart QSPI sample for '%s' %d[MHz]\n") % system_str_ % clk;
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

	cmd_.set_prompt("# ");

	LED::DIR = 1;
	LED::P = 0;

	uint8_t cnt = 0;
	while(1) {

		cmt_mgr_.sync();

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
