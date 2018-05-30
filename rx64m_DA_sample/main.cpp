//=====================================================================//
/*! @file
    @brief  RX64M D/A 出力サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する。@n
			・DA0(P03)、DA1(P05) からアナログ出力する。@n
			・サンプリング間隔は 48KHz
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/sci_io.hpp"
#include "common/cmt_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/delay.hpp"
#include "common/command.hpp"
#include "common/tpu_io.hpp"
#include "common/intmath.hpp"

// ソフトウェアー（タイマー割り込みタスク）で転送を行う場合に有効にする。
// ※無効にした場合、ＤＭＡ転送で行われる。
// #define SOFT_TRANS

namespace {

	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;

	typedef device::cmt_io<device::CMT0> CMT;
	CMT		cmt_;

	typedef utils::fixed_fifo<char, 128> BUFFER;
	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
	SCI		sci_;

	utils::command<256> cmd_;

	/// DMAC 終了割り込み
	class dmac_task {
		volatile uint32_t	count_;
	public:
		dmac_task() : count_(0) { }

		void operator() () {
			++count_;
		}

		uint32_t get_count() const { return count_; }
	};


	typedef device::dmac_mgr<device::DMAC0, dmac_task> DMAC_MGR;
	DMAC_MGR	dmac_mgr_;

	typedef device::R12DA DAC;
	typedef device::dac_out<DAC> DAC_OUT;
	DAC_OUT		dac_out_;

	struct wave_t {
		uint16_t	l;	///< D/A CH0
		uint16_t	r;	///< D/A CH1
	};
	static const uint32_t WAVE_NUM = 2048;
	wave_t	wave_[WAVE_NUM];

	// 48KHz サンプリング割り込み
	class timer_task {

		uint16_t	pos_;

	public:
		timer_task() : pos_(0) { }

		void operator() () {
			const wave_t& w = wave_[pos_];
			dac_out_.out0(w.l);
			dac_out_.out1(w.r);
			++pos_;
			pos_ &= WAVE_NUM - 1;
		}

		uint16_t get_pos() const { return pos_; }
	};
#ifdef SOFT_TRANS
	typedef device::tpu_io<device::TPU0, timer_task> TPU0;
#else
	typedef device::tpu_io<device::TPU0, utils::null_task> TPU0;
#endif
	TPU0		tpu0_;
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

	void sci_puts(const char *str)
	{
		sci_.puts(str);
	}

	uint16_t sci_length(void)
	{
		return sci_.recv_length();
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::system_io<12000000>::setup_system_clock();

	{  // タイマー設定（６０Ｈｚ）
		uint8_t int_level = 4;
		cmt_.start(60, int_level);
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}

	utils::format("RX64M Internal D/A sample start\n");

	cmd_.set_prompt("# ");

	LED::DIR = 1;

	{  // タイマー設定
		uint8_t intr_level = 5;
		if(!tpu0_.start(48000, intr_level)) {
///		if(!tpu0_.start(100, intr_level)) {
			utils::format("TPU0 start error...\n");
		}
	}

	{  // 内臓１２ビット D/A の設定
		bool amp_ena = true;
		dac_out_.start(DAC_OUT::output::CH0_CH1, amp_ena);
		dac_out_.out0(32767);
		dac_out_.out1(32767);

		for(uint32_t i = 0; i < WAVE_NUM; ++i) {
			wave_t w;
			if(i & 1) {
				w.l = 0xffff;
				w.r = 0x0000;
			} else {
				w.l = 0x0000;
				w.r = 0xffff;
			}
			wave_[i] = w;
		}
//		imath::build_sin<int16_t>(wave_ch0_, 128, 32767, 0x8000, 2048);
//		imath::build_sin<int16_t>(wave_ch1_, 128, 32767, 0x8000, 2048);
	}

#ifndef SOFT_TRANS
	{  // DMAC マネージャー開始
		uint8_t intr_level = 4;
		bool rept = true;
		auto ret = dmac_mgr_.start(DMAC_MGR::trans_type::SP_DN_32,
			reinterpret_cast<uint32_t>(wave_), DAC::DADR0.address(), 1024,
			tpu0_.get_intr_vec(), rept, intr_level);
		if(!ret) {
			utils::format("DMAC Not start...\n");
		}
	}
#endif

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		if(cmd_.service()) {

		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
