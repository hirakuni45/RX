//=====================================================================//
/*! @file
    @brief  D/A Converter サンプル @n
			RX64M, RX71M: @n
				12MHz のベースクロックを使用する @n
		　　　　PORT (P07:LQFP176-176) にLEDを接続する @n
				DA0 (P03:LQFP176-4)、DA1 (P05:LQFP176-2) からアナログ出力（１２ビット）する。@n
			RX65N (Renesas Envision kit RX65N): @n
				12MHz のベースクロックを使用する @n
		　　　　PORT (P70) に接続された青色 LED を利用する @n
				DA0 (P03:LQFP144-4)、DA1 (P05:LQFP144-2) からアナログ出力（１２ビット）する。@n
			RX66T: @n
				10MHz のベースクロックを使用する @n
		　　　　PORT (P00:LQFP100-4) にLEDを接続する @n
				DA0 (P64:LQFP100-70)、DA1 (P65:LQFP100-69) からアナログ出力（１２ビット）する。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/mtu_io.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/command.hpp"
#include "common/intmath.hpp"

namespace {

#if defined(SIG_RX71M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::R12DA DAC;
	static const char* system_str_ = { "RX71M" };
#elif defined(SIG_RX64M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::R12DA DAC;
	static const char* system_str_ = { "RX64M" };
#elif defined(SIG_RX65N)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;
	typedef device::R12DA DAC;
	static const char* system_str_ = { "RX65N" };
#elif defined(SIG_RX24T)
	typedef device::system_io<10000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::DA DAC;
	static const char* system_str_ = { "RX24T" };
#elif defined(SIG_RX66T)
	typedef device::system_io<10000000, 160000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::R12DA DAC;
	static const char* system_str_ = { "RX66T" };
#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
// SCI ポートの第二候補を選択する場合
//	typedef device::sci_io<SCI_CH, RXB, TXB, device::port_map::option::SECOND> SCI;
	SCI			sci_;

	typedef device::cmt_io<device::CMT0, utils::null_task> CMT;
	CMT			cmt_;

	typedef utils::command<256> COMMAND;
	COMMAND		cmd_;


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

	typedef device::dac_out<DAC> DAC_OUT;
	DAC_OUT		dac_out_;

	struct wave_t {
		uint16_t	l;	///< D/A CH0
		uint16_t	r;	///< D/A CH1
	};
	wave_t		wave_[DMAC_MGR::BLOCK_SIZE_MAX];


	typedef device::mtu_io<device::MTU0> MTU_IO;
	MTU_IO		mtu_io_;


	void calc_sico_(int div)
	{
		int32_t gain_shift = 16;
		intmath::sincos_t sico(static_cast<int32_t>(32767) << gain_shift);
		for(uint32_t i = 0; i < DMAC_MGR::BLOCK_SIZE_MAX; ++i) {
			wave_[i].l = (sico.x >> gain_shift) + 32768;
			wave_[i].r = (sico.y >> gain_shift) + 32768;
			intmath::build_sincos(sico,  DMAC_MGR::BLOCK_SIZE_MAX / div);
		}
	}

	void command_service_()
	{
		// コマンド入力と、コマンド解析
		if(!cmd_.service()) {
			return;
		}

		auto n = cmd_.get_words();
		if(cmd_.cmp_word(0, "freq") && n >= 2) {
			char tmp[16];
			if(cmd_.get_word(1, tmp, sizeof(tmp))) {
				int freq = 0;
				if((utils::input("%d", tmp) % freq).status()) {
					mtu_io_.set_freq(MTU_IO::mtu_type::channel::A, freq);
					utils::format("Freq: %d [Hz]\n") % freq;
				}
			}
		} else if(cmd_.cmp_word(0, "step")) {
			char tmp[16];
			if(cmd_.get_word(1, tmp, sizeof(tmp))) {
				int step = 0;
				if((utils::input("%d", tmp) % step).status()) {
					calc_sico_(step);
					utils::format("Step: %d\n") % step;
				}
			}
		} else if(cmd_.cmp_word(0, "clear")) {
			device::ICU::PIAR0.PIR0 = 0;
		} else if(cmd_.cmp_word(0, "?") || cmd_.cmp_word(0, "help")) {
		} else {
			const char* p = cmd_.get_command();
			if(p[0]) {
				utils::format("command error: '%s'\n") % p;
			}
		}
	}
}


extern "C" {

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	// syscalls.c から呼ばれる、標準入力（stdin）
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
	SYSTEM_IO::setup_system_clock();

	{  // タイマー設定（100Hz）
		uint8_t intr = 4;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		uint8_t intr = 2;        // 割り込みレベル
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}


	{  // 内臓 D/A の初期化
		bool amp_ena = true;  // without RX66T
		dac_out_.start(DAC_OUT::output::CH0_CH1, amp_ena);
		dac_out_.out0(32767);
		dac_out_.out1(32767);
	}


	{  // MTU0 の初期化
		uint32_t frq = 96000;
		uint8_t intr = 4;
		auto ret = mtu_io_.start_normal(MTU_IO::mtu_type::channel::A, MTU_IO::OUTPUT_TYPE::NONE, frq, intr);
		if(!ret) {
			utils::format("MTU0 Not start...\n");
		}
	}

	{  // DMAC マネージャー開始
		uint8_t intr_level = 4;
		bool cpu_intr = false;
		auto ret = dmac_mgr_.start(mtu_io_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
			reinterpret_cast<uint32_t>(wave_), DAC::DADR0.address(),
			DMAC_MGR::BLOCK_SIZE_MAX, intr_level, cpu_intr);
		if(!ret) {
			utils::format("DMAC Not start...\n");
		}
	}

	cmd_.set_prompt("# ");

	{
		auto clk = F_ICLK / 1000000;
		utils::format("Start D/A sample for '%s' %u [MHz]\n") % system_str_ % clk;
	}



	{
		calc_sico_(4);
//		for(uint32_t i = 0; i < DMAC_MGR::BLOCK_SIZE_MAX; ++i) {
//			wave_[i].l = i << 6;
//			wave_[i].r = (i << 6) + 32768;
//		}
	}


	LED::DIR = 1;
	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

		command_service_();

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
