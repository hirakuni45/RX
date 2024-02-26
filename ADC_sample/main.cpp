//=====================================================================//
/*! @file
    @brief  A/D 入力サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/fixed_fifo.hpp"
#include "common/cmt_mgr.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "RX600/adc_in.hpp"

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
		static_assert(SCI_IO::probe_baud(baud), "Failed baud rate accuracy test");  // 許容誤差（3%）を超える場合、コンパイルエラー
		auto intr = device::ICU::LEVEL::_2;		// 割り込みレベル（NONE を指定すると、ポーリング動作になる）
		sci_io_.start(baud, intr);  // 標準では、８ビット、１ストップビットを選択
// 通信プロトコルを設定する場合は、通信プロトコルのタイプを指定する事が出来る。
// sci_io.hpp PROTOCOL enum class のタイプを参照
//		sci_.start(baud, intr, SCI::PROTOCOL::B8_E_1S);
	}

	// A/D 変換設定
	{
		auto intr_level = device::ICU::LEVEL::_3;
		if(!adc_in_.start(ADC::ANALOG::AN000, intr_level)) {
			utils::format("A/D start fail AN000\n");
		}
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
