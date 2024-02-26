//=====================================================================//
/*! @file
    @brief  関数電卓・サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"

#include "common/format.hpp"
#include "common/input.hpp"

#if defined(SIG_RX65N) | defined(SIG_RX72N)
	#define USE_GUI
#endif

#ifdef USE_GUI
#include "calc_gui.hpp"
#include "calc_graph.hpp"
#else
#include "calc_cmd.hpp"
#endif

namespace {

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

#if defined(SIG_RX65N)
    typedef device::PORT<device::PORT6, device::bitpos::B4, 0> SDC_POWER;	///< '0'でＯＮ
    typedef device::NULL_PORT SDC_WP;		///< 書き込み禁止は使わない
    // RX65N Envision Kit の SDHI ポートは、候補３で指定できる
    typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::ORDER::THIRD> SDC;
    SDC		sdc_;
#elif defined(SIG_RX72N)
    typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;	///< '1'でＯＮ
    typedef device::NULL_PORT SDC_WP;  ///< カード書き込み禁止ポート設定
    // RX72N Envision Kit の SDHI ポートは、候補３で指定できる
    typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WP, device::port_map::ORDER::THIRD> SDC;
    SDC		sdc_;
#endif

	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT;
	CMT		cmt_;

#ifdef USE_GUI
	typedef app::calc_gui GUI;
	GUI		gui_;
	typedef app::calc_graph GRAPH;
	GRAPH	graph_;

#else
	typedef app::calc_cmd CMD;
	CMD		cmd_;
#endif
}


#ifdef USE_GUI
/// widget の登録・グローバル関数
bool insert_widget(gui::widget* w)
{
    return gui_.insert_widget(w);
}

/// widget の解除・グローバル関数
void remove_widget(gui::widget* w)
{
    gui_.remove_widget(w);
}
#endif


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

#ifdef USE_GUI
	DSTATUS disk_initialize(BYTE drv) {
		return sdc_.disk_initialize(drv);
	}


	DSTATUS disk_status(BYTE drv) {
		return sdc_.disk_status(drv);
	}


	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdc_.disk_read(drv, buff, sector, count);
	}


	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdc_.disk_write(drv, buff, sector, count);
	}


	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdc_.disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
		return 0;
	}
#endif
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	using namespace board_profile;

	{  // タイマー設定（100Hz）
		auto intr = device::ICU::LEVEL::_4;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("Start CALC sample for '%s' %d[MHz]\n") % system_str_ % clk;

	LED::DIR = 1;
	LED::P = 1;

	uint8_t cnt = 0;

	LED::DIR = 1;
#ifdef USE_GUI
	gui_.start();
	gui_.setup_touch_panel();
	gui_.setup();
	graph_.start();
#else
	cmd_.start();
#endif
	while(1) {
#ifdef USE_GUI
		gui_.update();
#else
		cmt_.sync();
		cmd_.update();
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
