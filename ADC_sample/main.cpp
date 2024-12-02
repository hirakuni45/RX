//=====================================================================//
/*! @file
    @brief  A/D 入力サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/fixed_fifo.hpp"
#include "common/cmt_mgr.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"

namespace {

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義

	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI_IO;
	SCI_IO	sci_io_;

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT_MGR;
	CMT_MGR	cmt_mgr_;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

	volatile uint32_t ad_count_ = 0;

	class ad_task {
	public:
		void operator() ()
		{
			++ad_count_;
		}
	};

	typedef device::S12AD ADC;
	typedef device::adc_in<ADC, ad_task> ADC_IN;
	ADC_IN	adc_in_;
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

	{  // タイマー設定（100Hz）
		constexpr uint32_t freq = 100;
		static_assert(CMT_MGR::probe_freq(freq), "Failed CMT rate accuracy test");
		cmt_mgr_.start(freq, device::ICU::LEVEL::_4);
	}

	{  // SCI の開始
		constexpr uint32_t baud = 115200;  // ボーレート（任意の整数値を指定可能）
		static_assert(SCI_IO::probe_baud(baud), "Failed baud rate accuracy test");
		auto intr = device::ICU::LEVEL::_2;		// 割り込みレベル（NONE を指定すると、ポーリング動作になる）
		sci_io_.start(baud, intr);  // 標準では、８ビット、１ストップビットを選択
	}

	{  // A/D 変換設定
		auto intr_level = device::ICU::LEVEL::_3;
		adc_in_.start(ADC_IN::SCAN_MODE::SINGLE, intr_level);
		adc_in_.enable(ADC::ANALOG::AN000);
	}

	{
		auto clk = device::clock_profile::ICLK / 1'000'000;
		utils::format("\nStart A/D sample for '%s' %d[MHz]\n") % system_str_ % clk;
	}

	if(0) {  // SCI/CMT の設定レポート表示
		utils::format("SCI PCLK: %u [Hz]\n") % SCI_IO::sci_type::PCLK;
		utils::format("SCI Baud rate (set): %u [BPS]\n") % sci_io_.get_baud_rate();
		float rate = 1.0f - static_cast<float>(sci_io_.get_baud_rate()) / sci_io_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("  Baud rate (real): %u (%3.2f [%%])\n") % sci_io_.get_baud_rate(true) % rate;
		utils::format("CMT Timer (set):  %d [Hz]\n") % cmt_mgr_.get_rate();
		rate = 1.0f - static_cast<float>(cmt_mgr_.get_rate()) / cmt_mgr_.get_rate(true);
		rate *= 100.0f;
		utils::format("  Timer (real): %d [Hz] (%3.2f [%%])\n") % cmt_mgr_.get_rate(true) % rate;
	}

	LED::OUTPUT();

	uint32_t cnt = 0;
	uint32_t msg = 0;
	while(1) {
		cmt_.sync();

		adc_in_.scan();
		adc_in_.sync();

		++msg;
		if(msg >= 100) {
			msg = 0;
			auto v = adc_in_.get(ADC::ANALOG::AN000);
			utils::format("AN000: %d (%d)\n") % v % ad_count_;
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
