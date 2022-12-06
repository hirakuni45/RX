//=====================================================================//
/*! @file
    @brief  CNC プロジェクト
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
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

	static const char* system_str_ = { "RX72T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B1, 0> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::SCI11 RS485_CH;


	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 512> TXB;  // TX (送信) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

	typedef utils::command<256> CMD;
	CMD 	cmd_;

// RS-485 ポートの定義
	typedef utils::fixed_fifo<char, 1024> RS485_RXB;  // RS-485/RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 512>  RS485_TXB;  // RS-485/TX (送信) バッファの定義

	// PA0: TXD11, PA1: RXD11 for RX72T
	// P32: MAX3485 /RE, P33: MAX3485 DE
	typedef device::PORT<device::PORT3, device::bitpos::B2> RS485_NRE;  // for MAX3485 /RE
	typedef device::PORT<device::PORT3, device::bitpos::B3> RS485_DE;   // for MAX3485 DE
	typedef device::sci_io<RS485_CH, RS485_RXB, RS485_TXB, device::port_map::ORDER::SECOND, device::sci_io_base::FLOW_CTRL::RS485, RS485_DE> RS485;
	RS485	rs485_;
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
		auto intr = device::ICU::LEVEL::_4;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_3;
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	{  // RS-485 の開始
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 9600;
		rs485_.start(baud, intr);
		RS485_NRE::DIR = 1;
		RS485_NRE::P = 0;  // NRE enable
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("Start CNC sample for '%s' %d [MHz]\n") % system_str_ % clk;

	LED::DIR = 1;

	{
		utils::format("SCI PCLK: %u [Hz]\n") % SCI_CH::PCLK;

		utils::format("SCI Baud rate (set): %u [BPS]\n") % sci_.get_baud_rate();
		float rate = 1.0f - static_cast<float>(sci_.get_baud_rate()) / sci_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("  SEMR_BRME: %s\n") % utils::str::get_bool_text(SCI_CH::SEMR_BRME);
		utils::format("  SEMR_BGDM: %s\n") % utils::str::get_bool_text(SCI_CH::SEMR_BGDM);
		utils::format("SCI Baud rate (real): %u (%3.2f [%%])\n") % sci_.get_baud_rate(true) % rate;

		utils::format("RS-485 Baud rate (set): %u [BPS]\n") % rs485_.get_baud_rate();
		rate = 1.0f - static_cast<float>(rs485_.get_baud_rate()) / rs485_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("RS-485 Baud rate (real): %u (%3.2f [%%])\n") % rs485_.get_baud_rate(true) % rate;
		utils::format("  SEMR_BRME: %s\n") % utils::str::get_bool_text(RS485_CH::SEMR_BRME);
		utils::format("  SEMR_BGDM: %s\n") % utils::str::get_bool_text(RS485_CH::SEMR_BGDM);

		utils::format("CMT rate (set):  %d [Hz]\n") % cmt_.get_rate();
		rate = 1.0f - static_cast<float>(cmt_.get_rate()) / cmt_.get_rate(true);
		rate *= 100.0f;
		utils::format("CMT rate (real): %d [Hz] (%3.2f [%%])\n") % cmt_.get_rate(true) % rate;
	}

	cmd_.set_prompt("# ");

	uint8_t cnt = 0;
	while(1) {

		cmt_.sync();

		bool org = true;
		auto rn = rs485_.recv_length();
		while(rs485_.recv_length() > 0) {
			if(org) {
				sci_.puts("RS-485 Recv: '");
				org = false;
			}
			auto ch = rs485_.getch();
			sci_.putch(ch);
		}
		if(rn > 0) {
			sci_.puts("'\n");
		}

		if(cmd_.service()) {
			uint32_t cmdn = cmd_.get_words();
			uint32_t n = 0;
			while(n < cmdn) {
				char tmp[256];
				if(cmd_.get_word(n, tmp, sizeof(tmp))) {
					utils::format("RS-485 Send: '%s'\n") % tmp;
					rs485_.puts(tmp);
				}
				++n;
			}
		}

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
		}
		if(cnt < 25) {
			LED::P = 1;
		} else {
			LED::P = 0;
		}
	}
}
