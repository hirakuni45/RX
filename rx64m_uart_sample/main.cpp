//=====================================================================//
/*! @file
    @brief  RX64M UART(SCI1)サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/sci_io.hpp"
#include "common/cmt_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"

#include "RX64M/rtc.hpp"
#include "common/delay.hpp"

namespace {

	void wait_delay_(uint32_t n)
	{
		// とりあえず無駄ループ
		for(uint32_t i = 0; i < n; ++i) {
			asm("nop");
		}
	}

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;
}

extern "C" {
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b();
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	wait_delay_(5000);

	device::SYSTEM::PLLCR.STC = 0b010011;		// PLL 10 倍(120MHz)
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	wait_delay_(5000);

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.BCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKC.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
	device::SYSTEM::SCKCR2.UCK = 0b0100;  // USB Clock: 1/5 (120/5=24)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	// タイマー設定（６０Ｈｚ）
	cmt_.set_clock(F_PCKB);
	uint8_t cmt_irq_level = 4;
	cmt_.start(60, cmt_irq_level);

	// SCI 設定
	static const uint8_t sci_level = 2;
	sci_.start(115200, sci_level);

	utils::format("RX64M start\n");

	device::PORT0::PDR.B5 = 1;
	device::PORT0::PDR.B7 = 1;

	uint32_t cnt = 0;
	uint32_t n = 0;
	while(1) {
		cmt_.sync();

		if(sci_.length()) {
			auto ch = sci_.getch();
			sci_.putch(ch);
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B7 = (cnt < 10) ? 0 : 1;

		utils::delay::micro_second(1);
		device::PORT0::PODR.B5 = 0;
		utils::delay::micro_second(1);
		device::PORT0::PODR.B5 = 1;

		if((n % 60) == 0) {
			utils::format("%d\n") % (n / 60);
		}
		++n;
	}
}
