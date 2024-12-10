//=====================================================================//
/*! @file
    @brief  MTU サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"
#include "common/command.hpp"

#include "common/mtu_io.hpp"
#include "common/format.hpp"
#include "common/input.hpp"

namespace {

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義
	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT;
	CMT		cmt_;

	typedef device::mtu_io<board_profile::MTU_CH, utils::null_task, utils::null_task, board_profile::MTU_ORDER> MTU;
	typedef device::port_map_mtu::ORDER MTU_ORDER;
	MTU		mtu_;

	typedef utils::command<256> CMD;
	CMD 	cmd_;

	enum class COMMAND : uint8_t {
		NONE,
		FREQ,
		PWM_C,
		PWM_D
	};

	uint32_t	freq_;
	float		pwm_duty_c_;
	float		pwm_duty_d_;

	void command_analize_()
	{
		if(!cmd_.service()) {
			return;
		}

		uint32_t cmdn = cmd_.get_words();
		uint32_t n = 0;
		auto command = COMMAND::NONE;
		while(n < cmdn) {
			char tmp[256];
			switch(command) {
			case COMMAND::FREQ:
				if(cmd_.get_word(n, tmp, sizeof(tmp))) {
					if((utils::input(tmp, "%d") % freq_).status()) {
						if(freq_ < 1) freq_ = 1;
						mtu_.set_freq(MTU::CHANNEL::A, freq_);
					}
				}
				command = COMMAND::NONE;
				break;
			case COMMAND::PWM_C:
				if(cmd_.get_word(n, tmp, sizeof(tmp))) {
					if((utils::input(tmp, "%f") % pwm_duty_c_).status()) {
						if(pwm_duty_c_ < 0.0f) pwm_duty_c_ = 0.0f;
						else if(pwm_duty_c_ > 1.0f) pwm_duty_c_ = 1.0f;
						auto d = static_cast<int32_t>(pwm_duty_c_ * 65535.0f);
						mtu_.set_pwm_duty(MTU::CHANNEL::A, d);
					}
				}
				command = COMMAND::NONE;
				break;
			case COMMAND::PWM_D:
				if(cmd_.get_word(n, tmp, sizeof(tmp))) {
					if((utils::input(tmp, "%f") % pwm_duty_d_).status()) {
						if(pwm_duty_d_ < 0.0f) pwm_duty_d_ = 0.0f;
						else if(pwm_duty_d_ > 1.0f) pwm_duty_d_ = 1.0f;
						auto d = static_cast<int32_t>(pwm_duty_d_ * 65535.0f);
						mtu_.set_pwm_duty(MTU::CHANNEL::A, d);
					}
				}
				command = COMMAND::NONE;
				break;
			default:
				if(cmd_.cmp_word(n, "set") == 0) {
					utils::format("Frequency: %u Hz\n") % freq_;
					utils::format("PWM duty C: %3.2f\n") % pwm_duty_c_;
					utils::format("PWM duty D: %3.2f\n") % pwm_duty_d_;
				} else if(cmd_.cmp_word(n, "freq") == 0) {
					command = COMMAND::FREQ;
				} else if(cmd_.cmp_word(n, "pwm-c") == 0) {
					command = COMMAND::PWM_C;
				} else if(cmd_.cmp_word(n, "pwm-d") == 0) {
					command = COMMAND::PWM_D;
				} else if(cmd_.cmp_word(n, "help") == 0) {
					utils::format("Report setting: set\n");
					utils::format("Set refarence frequency: freq x (1 to n Hz)\n");
					utils::format("Set PWM duty C: pwm-c y (0.0 to 1.0)\n");
					utils::format("Set PWM duty D: pwm-d y (0.0 to 1.0)\n");
				}
				break;
			}
			++n;
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

	using namespace board_profile;

	LED::DIR = 1;
	LED::P = 0;

	{  // タイマー設定（100Hz）
		auto intr = device::ICU::LEVEL::_4;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 115200;
		sci_.start(baud, intr);  // 標準では、８ビット、１ストップビットを選択
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("\nStart MTU sample for '%s' %d[MHz]\n") % system_str_ % clk;

	{  // MTU の開始
		freq_ = 10'000;  // 10KHz
#if 0
		// PWM2 2 output C(H->L), D(L->H) 出力
		static constexpr MTU::port_t out[2] = {
			{ MTU::CHANNEL::B, MTU::OUTPUT::H_TO_L, MTU_ORDER::FIRST },
			{ MTU::CHANNEL::C, MTU::OUTPUT::L_TO_H, MTU_ORDER::FIRST }
		};
#else
		// PWM2 3 output B(H->L), C(L->H), D(H->L) 出力
		static constexpr MTU::port_t out[3] = {
			{ MTU::CHANNEL::B, MTU::OUTPUT::H_TO_L, MTU_ORDER::FIRST },
			{ MTU::CHANNEL::C, MTU::OUTPUT::L_TO_H, MTU_ORDER::FIRST },
			{ MTU::CHANNEL::D, MTU::OUTPUT::H_TO_L, MTU_ORDER::FIRST }
		};
#endif
		if(!mtu_.start_pwm2(MTU::CHANNEL::A, freq_, out)) {
			utils::format("MTU can't start...\n");
		}
	}
	pwm_duty_c_ = 0.25f;
	mtu_.set_pwm_duty(MTU::CHANNEL::C, 16384);
	pwm_duty_d_ = 0.25f;
	mtu_.set_pwm_duty(MTU::CHANNEL::D, 16384);


	{  // SCI/CMT/MTU の設定レポート表示
		utils::format("SCI PCLK: %u\n") % SCI_CH::PCLK;
		utils::format("SCI Baud rate (set):  %u\n") % sci_.get_baud_rate();
		float rate = 1.0f - static_cast<float>(sci_.get_baud_rate()) / sci_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("  Baud rate (real): %u (%3.2f [%%])\n") % sci_.get_baud_rate(true) % rate;
		utils::format("  SEMR_BRME: %s\n") % utils::str::get_bool_text(SCI_CH::SEMR_BRME);
		utils::format("  SEMR_BGDM: %s\n") % utils::str::get_bool_text(SCI_CH::SEMR_BGDM);

		utils::format("CMT Timer (set):  %d [Hz]\n") % cmt_.get_rate();
		rate = 1.0f - static_cast<float>(cmt_.get_rate()) / cmt_.get_rate(true);
		rate *= 100.0f;
		utils::format("  Timer (real): %d [Hz] (%3.2f [%%])\n") % cmt_.get_rate(true) % rate;

		utils::format("MTU Interval Timer (set):  %d [Hz]\n") % mtu_.get_rate();
		rate = 1.0f - static_cast<float>(mtu_.get_rate()) / mtu_.get_rate(true);
		rate *= 100.0f;
		utils::format("  Interval Timer (real): %d [Hz] (%3.2f [%%])\n") % mtu_.get_rate(true) % rate;
	}

	cmd_.set_prompt("# ");

	uint8_t cnt = 0;
	while(1) {

		cmt_.sync();

		command_analize_();

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
