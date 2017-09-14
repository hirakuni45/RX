//=====================================================================//
/*! @file
    @brief  RX24T ファースト・サンプル @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/command.hpp"

namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint16_t, 64> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

	utils::command<128> command_;
}

extern "C" {

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

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
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	{  // タイマー設定（６０Ｈｚ）
		uint8_t intr_level = 4;
		cmt_.start(60, intr_level);
	}

	{  // SCI 設定
		uint8_t intr_level = 2;
		sci_.start(115200, intr_level);
	}

	utils::format("RX24T SCI sample\n");

	command_.set_prompt("# ");

	{
		int a;
		int n = (utils::input("%d") % a).num();
		utils::format("stdin... N: %d, V: %d\n") % n % a;
	}

	device::PORT0::PDR.B0 = 1; // output

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		if(command_.service()) {
			uint8_t cmdn = command_.get_words();
			if(cmdn >= 1) {
				char tmp[128];
				if(command_.get_word(0, sizeof(tmp), tmp)) {
#if 0
					float a = 0.0f;
					int n = (utils::input("%f", tmp) % a).num();
					if(n == 1) {
						utils::format("Value: %10.5f\n") % a;
					} else {
						utils::format("Input decimal ?\n");
					}
#else
					int a = 0;
					int n = (utils::input("%d", tmp) % a).num();
					if(n == 1) {
						utils::format("Value: %d\n") % a;
					} else {
						utils::format("Input decimal ?\n");
					}
#endif
				}
			}
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B0 = (cnt < 10) ? 0 : 1;
	}
}
