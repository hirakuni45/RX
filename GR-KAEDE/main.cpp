//=====================================================================//
/*! @file
    @brief  GR-KAEDE(RX64M) サンプル @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/cmt_io.hpp"
#include "common/fifo.hpp"
#include "common/sci_io.hpp"

#include "common/ether_io.hpp"

#include "common/format.hpp"

namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 128> buffer;
	device::sci_io<device::SCI7, buffer, buffer> sci_;

	device::ether_io<device::ETHERC0, device::EDMAC0> eth_;
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

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);			
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	// Base Clock 12MHz
	// PLLDIV: 1/2, STC: 16 倍(96MHz)
	device::SYSTEM::PLLCR = device::SYSTEM::PLLCR.PLIDIV.b(1) |
							device::SYSTEM::PLLCR.STC.b(0b011111);
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(1)		// 1/2 (96/2=48)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (96/1=96)
						  | device::SYSTEM::SCKCR.BCK.b(1)		// 1/2 (96/2=48)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (96/1=96)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (96/2=48)
						  | device::SYSTEM::SCKCR.PCKC.b(1)		// 1/2 (96/2=48)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (96/2=48)
	device::SYSTEM::SCKCR2.UCK = 0b0011;  // USB Clock: 1/4 (96/4=24)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	{  // タイマー設定（６０Ｈｚ）
		uint8_t int_level = 4;
		cmt_.start(60, int_level);
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}

	{  // Ethernet 設定
		uint8_t int_level = 7;
		eth_.start(int_level);
	}

	utils::format("Start GR-KAEDE\n");

	device::PORTC::PDR.B0 = 1; // output

	uint32_t cnt = 0;

	while(1) {
		cmt_.sync();

		if(sci_.recv_length()) {
			auto ch = sci_.getch();
			sci_.putch(ch);
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORTC::PODR.B0 = (cnt < 10) ? 0 : 1;
	}
}
