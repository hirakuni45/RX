//=====================================================================//
/*! @file
    @brief  RX64M SDRAM サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include <random>

namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint16_t, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

	utils::SDRAM_128M_32W	sdram_;
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

	device::SYSTEM::PLLCR.STC = 0b010011;		// PLL 10 倍(120MHz)
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.BCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKC.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
	device::SYSTEM::SCKCR2.UCK = 0b0100;  // USB Clock: 1/5 (120/5=24)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	// SDRAM 初期化 128M/32bits bus
	sdram_();

	{
		// タイマー設定（６０Ｈｚ）
		uint8_t cmt_irq_level = 4;
		cmt_.start(60, cmt_irq_level);
	}

	{
		// SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	utils::format("RX64M SDRAM sample\n");

	device::PORT0::PDR.B7 = 1; // output

	// 乱数を書き込む
	{
		std::mt19937 mt;
		volatile uint32_t* p = (uint32_t*)0x08000000;
		uint32_t j = 0;
		for(uint32_t i = 0; i < 1024 * 1024 * 32 / 4; ++i) {
			if(j == 0) {
				utils::format("Write block: %08X\n") % (uint32_t)p;
				device::PORT0::PODR.B7 = !device::PORT0::PODR.B7();
			}
			++j;
			if(j >= 16384) j = 0;
			*p++ = mt();
		}
	}

	// 乱数を読み出す
	{
		uint32_t error = 0;
		std::mt19937 mt;
		volatile uint32_t* p = (uint32_t*)0x08000000;
		uint32_t j = 0;
		for(uint32_t i = 0; i < 1024 * 1024 * 32 / 4; ++i) {
			auto n = mt();
			if(*p != n) {
				++error;
				utils::format("Read block error: %08X\n") % (uint32_t)p;
			}
			++p;
			if(j == (16384 - 1)) {
				utils::format("Read block OK: %08X\n") % (uint32_t)p;
				device::PORT0::PODR.B7 = !device::PORT0::PODR.B7();
			}
			++j;
			if(j >= 16384) j = 0;
		}
		if(error) {
			utils::format("Read error: %d\n") % error;
		} else {
			utils::format("Write/Read All OK\n");
		}
	}

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
		device::PORT0::PODR.B7 = (cnt < 10) ? 0 : 1;
	}
}
