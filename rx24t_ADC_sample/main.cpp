//=====================================================================//
/*! @file
    @brief  RX24T A/D サンプル @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
			・P40(91)、P41(90) をアナログ入力として使用 @n
			・P40/ANI000 ４つのスイッチ（排他）@n
                      P40                           @n
                       |                            @n
			VDD - 10K -+- 3.3K -+- 6.8K -+- 20K -+  @n
                       |        |        |       |  @n
			         RIGHT     UP      DOWN    LEFT @n
                       |        |        |       |  @n
                      VSS      VSS      VSS     VSS
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/bitset.hpp"
#include "common/switch_man.hpp"

namespace {

	uint32_t adc_cnt_;

	class adc_task {
	public:
		void operator() () {
			++adc_cnt_;
		}
	};

	device::cmt_io<device::CMT0>  cmt_;

	typedef utils::fixed_fifo<char, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

	typedef device::S12AD adc;
	typedef device::adc_in<adc, adc_task> ADC_IN;
	ADC_IN adc_in_;

	enum class SWITCH : uint8_t {
		RIGHT,
		UP,
		DOWN,
		LEFT,
		A,
		B
	};

	typedef utils::bitset<uint32_t, SWITCH> switch_bits;
	utils::switch_man<switch_bits> switch_man_;
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
	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MEMWAIT = 0b10; // 80MHz 動作 wait 設定

	while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");
	device::SYSTEM::OPCCR = 0;  // 高速モード選択
	while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");

	// clock osc 10MHz
	device::SYSTEM::MOSCWTCR = 9;	// 4ms wait
	// メインクロック・ドライブ能力設定、内部発信
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV21.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;  // メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	device::SYSTEM::PLLCR.STC = 0b001111;		// PLL input: 1, PLL 8 倍(80MHz)
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/4 (80/4=20)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (80/1=80)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (80/1=80)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (80/2=40)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (80/2=40)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	// タイマー設定（６０Ｈｚ）
	uint8_t cmt_irq_level = 4;
	cmt_.start(60, cmt_irq_level);

	// SCI 設定
	static const uint8_t sci_level = 2;
	sci_.start(115200, sci_level);

	utils::format("RX24T start\n");

	device::PORT0::PDR.B0 = 1; // output

	// A/D 設定
	{
		uint8_t intr_level = 1;
		if(!adc_in_.start(adc::analog::AIN000, intr_level)) {
			utils::format("A/D start fail AIN000\n");
		}
		if(!adc_in_.start(adc::analog::AIN001, intr_level)) {
			utils::format("A/D start fail AIN001\n");
		}
	}

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		adc_in_.scan();
		adc_in_.sync();

		// ４つのスイッチ判定（排他的）
		auto val = adc_in_.get(adc::analog::AIN000);
		val += 512;  // 閾値のオフセット（4096 / 4(SWITCH) / 2）
		val /= 1024;  // デコード（4096 / 4(SWITCH）

		switch_bits tmp;
		if(val < 4) {
			tmp.set(static_cast<SWITCH>(val));
		}

		switch_man_.service(tmp);

		bool f = false;
		if(switch_man_.get_positive().get(SWITCH::UP)) {
			utils::format("UP   : on\n");
			f = true;
		}
		if(switch_man_.get_positive().get(SWITCH::DOWN)) {
			utils::format("DOWN : on\n");
			f = true;
		}
		if(switch_man_.get_positive().get(SWITCH::LEFT)) {
			utils::format("LEFT : on\n");
			f = true;
		}
		if(switch_man_.get_positive().get(SWITCH::RIGHT)) {
			utils::format("RIGHT: on\n");
			f = true;
		}

		if(f) {
			auto a1 = adc_in_.get(adc::analog::AIN001);
			utils::format("Analog AIN001: %d (%d)\n") % a1 % adc_cnt_;
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B0 = (cnt < 10) ? 0 : 1;
	}
}
