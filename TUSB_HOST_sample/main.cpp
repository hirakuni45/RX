//=====================================================================//
/*! @file
    @brief  TinyUSB/Host サンプル
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

#include "usb/tinyusb_mng.hpp"

namespace {

#if defined(SIG_RX65N)
	// EX65N Envision Kit: FIRST order -> USB0_VBUSEN, USB0_OVERCURA
	typedef device::tinyusb_mng<device::USB0, device::port_map::ORDER::FIRST> TINYUSB;
#elif defined(SIG_RX72N)
	// RX72N Envision Kit: SECOND order -> USB0_VBUSEN, USB0_OVERCURB
	typedef device::tinyusb_mng<device::USB0, device::port_map::ORDER::SECOND> TINYUSB;
#elif defined(SIG_RX72T)
	// RX72T hirakuni45 board: VBUSEN, OVERCURA
	typedef device::tinyusb_mng<device::USB0, device::port_map::ORDER::FIRST> TINYUSB;
#endif

	typedef utils::fixed_fifo<char, 1024> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 2048> TXB;  // TX (送信) バッファの定義
	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT;
	CMT		cmt_;

	TINYUSB	tinyusb_;
	typedef usb::keyboard KEYBOARD;
	typedef usb::mouse MOUSE;
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

	{  // TinyUSB/Host のタスクを動かす Tick を 1000Hz とする。
		auto intr = device::ICU::LEVEL::_4;
		cmt_.start(1000, intr);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 115200;  // ボーレート（任意の整数値を指定可能）
		sci_.start(baud, intr);  // 標準では、８ビット、１ストップビットを選択
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("Start TinyUSB/Host sample for '%s' %d[MHz]\n") % system_str_ % clk;

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

	{  // TinyUSB マネージャーの開始
		auto intr = device::ICU::LEVEL::_5;
		if(tinyusb_.start(intr)) {
			utils::format("Start TinyUSB: OK!\n");
		} else {
			utils::format("Start TinyUSB: fail...\n");
		}
	}

	LED::DIR = 1;
	LED::P = 0;

	uint16_t cnt = 0;
	while(1) {

		cmt_.sync();

		tinyusb_.service();

		// キーボードに対するサービス
		auto& k = tinyusb_.at_keyboard();
		if(k.get_num() > 0) {
			auto t = k.get_key();
			if(t.code == 0x0d) {
				utils::format("\n");
			} else {
				utils::format("%c") % t.code;
				utils::format::flush();
			}
		}

		// マウスに対するサービス
		static vtx::ipos pos;
		tinyusb_.at_mouse().at_max() = vtx::ipos(4096 * 100);  // 最大領域の設定
		const auto& m = tinyusb_.at_mouse();
		if(m.get_state().mount) {
			auto t = m.get_state();
			if(t.positive & MOUSE::LEFT_BUTTON) {
				utils::format("Mouse Left button\n");
			}
			if(t.positive & MOUSE::RIGHT_BUTTON) {
				utils::format("Mouse Right button\n");
			}
			vtx::ipos tmp = t.pos / 100;
			if(tmp != pos) {
				utils::format("Mouse pos: %d, %d\n") % tmp.x % tmp.y;
				pos = tmp;
			}
		}

		++cnt;
		if(cnt >= 500) {
			cnt = 0;
		}
		if(cnt < 250) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
