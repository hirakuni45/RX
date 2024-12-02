//=====================================================================//
/*! @file
    @brief  RX24T Step Tacho @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/bitset.hpp"
#include "common/switch_man.hpp"

namespace {

	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;

	uint32_t adc_cnt_;

	class adc_task {
	public:
		void operator() () {
			++adc_cnt_;
		}
	};

	device::cmt_mgr<device::CMT0>  cmt_;

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義
	typedef device::SCI1 SCI_CH;
	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
	SCI		sci_;

	typedef device::S12AD ADC;
	typedef device::adc_in<ADC, adc_task> ADC_IN;
	ADC_IN	adc_in_;
}

extern "C" {

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	char sci_getch(void)
	{
		return sci_.getch();
	}

}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	LED::OUTPUT();  // LED ポートを出力に設定

	// タイマー設定（６０Ｈｚ）
	auto cmt_irq_level = device::ICU::LEVEL::_4;
	cmt_.start(60, cmt_irq_level);

	// SCI 設定
	auto sci_level = device::ICU::LEVEL::_2;
	sci_.start(115200, sci_level);

	utils::format("RX24T Step Tacho Start\n");

	// A/D 設定
	{
		auto intr_level = device::ICU::LEVEL::_1;
		adc_in_.start(ADC_IN::SCAN_MODE::SINGLE, intr_level);
		adc_in_.enable(ADC::ANALOG::AN000);
		adc_in_.enable(ADC::ANALOG::AN001);
	}

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		adc_in_.scan();
		adc_in_.sync();

		// ４つのスイッチ判定（排他的）
//		auto val = adc_in_.get(adc::analog::AIN000);
//		auto a1 = adc_in_.get(adc::analog::AIN001);
//		utils::format("Analog AIN001: %d (%d)\n") % a1 % adc_cnt_;

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
