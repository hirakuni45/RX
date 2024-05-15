//=====================================================================//
/*! @file
    @brief  RX64M D/A 出力サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する。@n
			・DA0(P03)、DA1(P05) からアナログ出力する。@n
			・サンプリング間隔は 48KHz @n
			・コンソールから、周波数を入力すると、その周波数で sin/cos @n
			を出力する。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/delay.hpp"
#include "common/command.hpp"
#include "common/tpu_io.hpp"
#include "common/mtu_io.hpp"
#include "common/intmath.hpp"

// ソフトウェアー（タイマー割り込みタスク）で転送を行う場合に有効にする。
// ※無効にした場合、ＤＭＡ転送で行われる。
// #define SOFT_TRANS

namespace {

	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

	typedef utils::fixed_fifo<char, 128> BUFFER;
	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
	SCI		sci_;

	utils::command<256> cmd_;

	/// DMAC 終了割り込み
	class dmac_term_task {
		volatile uint32_t	count_;
	public:
		dmac_term_task() : count_(0) { }

		void operator() () {
			// DMA を再スタート
			device::DMAC0::DMCNT.DTE = 1;  // DMA 再開
			++count_;
		}

		uint32_t get_count() const { return count_; }
	};


	typedef device::dmac_mgr<device::DMAC0, dmac_term_task> DMAC_MGR;
	DMAC_MGR	dmac_mgr_;

	typedef device::R12DA DAC;
	typedef device::dac_out<DAC> DAC_OUT;
	DAC_OUT		dac_out_;

	struct wave_t {
		uint16_t	l;	///< D/A CH0
		uint16_t	r;	///< D/A CH1
	};
	static const uint32_t WAVE_NUM = 1024;
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
			pos_ %= WAVE_NUM;
		}

		uint16_t get_pos() const { return pos_; }
	};
#ifdef SOFT_TRANS
//	typedef device::tpu_io<device::TPU0, timer_task> ITVT;
//	typedef device::mtu_io<device::MTU0, timer_task> ITVT;
//	typedef device::cmt_mgr<device::CMT1, timer_task> ITVT;
#else
//	typedef device::tpu_io<device::TPU0, utils::null_task> ITVT;
	typedef device::mtu_io<device::MTU0, utils::null_task> ITVT;
//	typedef device::cmt_mgr<device::CMT1, utils::null_task> ITVT;
#endif
	ITVT		itvt_;

	bool		init_ = false;
	float		freq_ = 100.0f;
	uint32_t	wpos_ = 0;
	intmath::sincos_t sico_(0);
	void service_sin_cos_()
	{
#ifdef SOFT_TRANS
		uint32_t pos = itvt_.at_task().get_pos();
#else
		uint32_t pos = (dmac_mgr_.get_count() & 0x3ff) ^ 0x3ff;
#endif
		int32_t gain_shift = 16; 
		if(!init_) {
			sico_.x = static_cast<int64_t>(32767) << gain_shift;
			sico_.y = 0;
			wpos_ = pos & 0x3ff;
			init_ = true;
		}

		int32_t dt = static_cast<int32_t>(48000.0f / freq_);

		uint32_t d = pos - wpos_;
		if(d >= WAVE_NUM) d += WAVE_NUM;
		for(uint32_t i = 0; i < d; ++i) {
			wave_t w;
			w.l = (sico_.x >> gain_shift) + 32768;
			w.r = (sico_.y >> gain_shift) + 32768;
			wave_[(wpos_ + (WAVE_NUM / 2)) & (WAVE_NUM - 1)] = w;
			++wpos_;
			wpos_ &= WAVE_NUM - 1;
			intmath::build_sincos(sico_, dt);
		}
	}
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
	SYSTEM_IO::boost_master_clock();

	{  // タイマー設定（１００Ｈｚ）
		auto intr_level = device::ICU::LEVEL::_4;
		cmt_.start(100, intr_level);
	}

	{  // SCI 設定
		auto intr_level = device::ICU::LEVEL::_2;
		sci_.start(115200, intr_level);
	}

	{  // インターバル・タイマー設定
		auto intr_level = device::ICU::LEVEL::_5;
		if(!itvt_.start(48'000, intr_level)) {
			utils::format("TPU0 start error...\n");
		}
	}

	{  // 内臓１２ビット D/A の設定
		bool amp_ena = true;
		dac_out_.start(DAC_OUT::output::CH0_CH1, amp_ena);
		dac_out_.out0(32767);
		dac_out_.out1(32767);
#if 0
		int32_t gain_shift = 16; 
		intmath::sincos_t sico(static_cast<int64_t>(32767) << gain_shift);
		for(uint32_t i = 0; i < WAVE_NUM; ++i) {
			wave_t w;
#if 0
			if(i & 1) {
				w.l = 0xffff;
				w.r = 0x0000;
			} else {
				w.l = 0x0000;
				w.r = 0xffff;
			}
#else
			w.l = (sico.x >> gain_shift) + 32768;
			w.r = (sico.y >> gain_shift) + 32768;
			intmath::build_sincos(sico, WAVE_NUM / 4);
#endif
			wave_[i] = w;
		}
#endif
	}

#ifndef SOFT_TRANS
	{  // DMAC マネージャー開始
		auto intr_level = device::ICU::LEVEL::_4;
		bool cpu_intr = true;
		auto ret = dmac_mgr_.start(DMAC_MGR::TRANS_MODE::REPEAT, DMAC_MGR::TRANS_TYPE::SP_DN_32, itvt_.get_intr_vec(),
			reinterpret_cast<uint32_t>(wave_), DAC::DADR0.address, 1024, WAVE_NUM,
			intr_level, cpu_intr);
		if(!ret) {
			utils::format("DMAC Not start...\n");
		}
	}
#endif

	utils::format("RX64M Internal D/A stream sample start\n");

	cmd_.set_prompt("# ");

	LED::DIR = 1;

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		service_sin_cos_();

//		uint32_t pos = dmac_mgr_.get_count() & 0x3ff;
//		utils::format("WP: %d\n") % pos;

		if(cmd_.service()) {
			char tmp[32];
			if(cmd_.get_word(0, tmp, sizeof(tmp))) {
				float freq = 0.0f;
				if((utils::input("%f", tmp) % freq).status()) {
					freq_ = freq;
					init_ = false;
				}
			}
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
