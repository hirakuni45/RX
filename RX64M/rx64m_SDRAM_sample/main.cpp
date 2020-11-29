//=====================================================================//
/*! @file
    @brief  RX64M SDRAM サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include <random>

namespace {

	typedef device::cmt_mgr<device::CMT0, utils::null_task> CMT;
	CMT		cmt_;

	typedef utils::fixed_fifo<char, 128> BUFFER;
	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
	SCI		sci_;

	utils::SDRAM_128M_32W	sdram_;
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
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::system_io<12000000>::setup_system_clock();

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
		volatile uint32_t* p = reinterpret_cast<uint32_t*>(0x08000000);
		uint32_t j = 0;
		for(uint32_t i = 0; i < 1024 * 1024 * 32 / 4; ++i) {
			if(j == 0) {
				utils::format("Write block:  0x%08X\n") % reinterpret_cast<uint32_t>(p);
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
		volatile uint32_t* p = reinterpret_cast<uint32_t*>(0x08000000);
		uint32_t j = 0;
		uint32_t all = 1024 * 1024 * 32;
		for(uint32_t i = 0; i < all / 4; ++i) {
			auto n = mt();
			if(*p != n) {
				++error;
				utils::format("Read block error: 0x%08X\n") % reinterpret_cast<uint32_t>(p);
			}
			++p;
			if(j == (16384 - 1)) {
				utils::format("Read block OK: 0x%08X\n") % (reinterpret_cast<uint32_t>(p) - 16384);
				device::PORT0::PODR.B7 = !device::PORT0::PODR.B7();
			}
			++j;
			if(j >= 16384) j = 0;
		}
		if(error) {
			utils::format("Read error: %d bytes\n") % (error * 4);
		} else {
			utils::format("Write/Read All OK: %d bytes\n") % all;
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
