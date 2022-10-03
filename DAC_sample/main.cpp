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
	@copyright	Copyright (C) 2019, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/command.hpp"
#include "common/intmath.hpp"
#include "common/mtu_io.hpp"
// #include "common/tpu_io.hpp"

namespace {

#if defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::R12DA DAC;
#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::R12DA DAC;
#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N" };
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;
	typedef device::R12DA DAC;
#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::DA DAC;
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::R12DA DAC;
#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T" };
	typedef device::PORT<device::PORT0, device::bitpos::B1> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::R12DA DAC;
#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
	SCI			sci_;

	typedef device::cmt_mgr<device::CMT0> CMT;
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
//	typedef device::tpu_io<device::TPU0> MTU_IO;
	MTU_IO		mtu_io_;

	uint32_t	sample_ = 100'000;
	uint32_t	freq_ = 100;
	uint32_t	wavidx_ = 0;
	static constexpr int32_t gain_shift_ = 16;

// オーバーフローに備えて -50 する。
	intmath::sincos_t sico_(static_cast<int64_t>(32767 - 64) << gain_shift_, 0);

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
					utils::format("Freq: %d [Hz]\n") % freq;
					freq_ = freq;
					sico_.x = static_cast<int64_t>(32767 -64) << gain_shift_;
					sico_.y = 0;
				}
			}
		} else if(cmd_.cmp_word(0, "sample")) {


		} else if(cmd_.cmp_word(0, "?") || cmd_.cmp_word(0, "help")) {
			utils::format("freq xxxx    set frequency [Hz]\n");
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
	SYSTEM_IO::boost_master_clock();

	{  // タイマー設定（200Hz）
		uint8_t intr = 4;
		cmt_.start(200, intr);
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
		uint8_t intr = 4;
		auto ret = mtu_io_.start(sample_, intr);
		if(!ret) {
			utils::format("MTU0 Not start...\n");
		}
	}

	{  // DMAC マネージャー開始
		uint8_t intr_level = 4;
		bool cpu_intr = false;
		auto ret = dmac_mgr_.start(mtu_io_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
			reinterpret_cast<uint32_t>(wave_), DAC::DADR0.address,
			DMAC_MGR::BLOCK_SIZE_MAX, intr_level, cpu_intr);
		if(!ret) {
			utils::format("DMAC Not start...\n");
		}
	}

	cmd_.set_prompt("# ");

	{
		auto clk = device::clock_profile::ICLK / 1'000'000;
		utils::format("Start D/A sample for '%s' %u [MHz]\n") % system_str_ % clk;
	}

	LED::DIR = 1;
	uint8_t cnt = 0;
	auto dmapos = 1023 - (dmac_mgr_.get_count() & 0x3ff);
	wavidx_ = dmapos / 2;

	while(1) {
		cmt_.sync();

		{
			auto tmp = 1023 - (dmac_mgr_.get_count() & 0x3ff);
			auto n = (tmp - dmapos) & 0x3ff;
			dmapos = tmp;
			for(uint32_t i = 0; i < n; ++i) {
				wave_[wavidx_].l = (sico_.x >> gain_shift_) + 32768;
				wave_[wavidx_].r = (sico_.y >> gain_shift_) + 32768;
				++wavidx_;
				wavidx_ &= 0x3ff;
				intmath::build_sincos(sico_, sample_ / freq_);
			}
		}

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
