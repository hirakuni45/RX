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

#if defined(SIG_RX62N)
  #if defined(CQ_FRK)
    // FRK-RX62N(CQ 出版社)
	static const char* system_str_ = { "RX62N FRK-RX62N" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT1, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::SCI1 SCI_CH;
  #else
    // BlueBoard-RX62N_100pin
	static const char* system_str_ = { "RX62N BlueBoard-RX62N_100pin" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::SCI1 SCI_CH;
  #endif
	// See 'RX62x/port_map_mtu.hpp' J6_6
	typedef device::MTU0 MTU_CH;
	static constexpr auto MTU_ORDER = device::port_map_mtu::ORDER::FIRST;
#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::MTU0 MTU_CH;
	static constexpr auto MTU_ORDER = device::port_map_mtu::ORDER::FIRST;
#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::MTU0 MTU_CH;
	static constexpr auto MTU_ORDER = device::port_map_mtu::ORDER::FIRST;
#elif defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::MTU0 MTU_CH;
	static constexpr auto MTU_ORDER = device::port_map_mtu::ORDER::FIRST;
#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N Envision Kit" };
	typedef device::PORT<device::PORT7, device::bitpos::B0, false> LED;
	typedef device::SCI9 SCI_CH;
	// CN13 (1): PD1_AN109_IRQ1 (MTIOC4B)
	typedef device::MTU4 MTU_CH;
	static constexpr auto MTU_ORDER = device::port_map_mtu::ORDER::FIFTH;
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::MTU0 MTU_CH;
	static constexpr auto MTU_ORDER = device::port_map_mtu::ORDER::FIRST;
#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N Envision Kit" };
	typedef device::PORT<device::PORT4, device::bitpos::B0, false> LED;
	typedef device::SCI2 SCI_CH;
	// Pmod2 (8): PD1_RESET (MTIOC4B)
	typedef device::MTU4 MTU_CH;
	static constexpr auto MTU_ORDER = device::port_map_mtu::ORDER::FIFTH;
#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B1, false> LED;
	typedef device::SCI1 SCI_CH;
	typedef device::MTU0 MTU_CH;
	static constexpr auto MTU_ORDER = device::port_map_mtu::ORDER::FIRST;
#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
// SCI ポートの第二候補を選択する場合
//	typedef device::sci_io<SCI_CH, RXB, TXB, device::port_map::ORDER::SECOND> SCI;
	SCI		sci_;

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT		cmt_;

	typedef device::mtu_io<MTU_CH, utils::null_task, utils::null_task, MTU_ORDER> MTU;
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
//		if(!mtu_.start_normal(MTU::CHANNEL::A, MTU::OUTPUT::TOGGLE, freq)) {

		// PWM2 C(H->L), D(L->H) 出力
		static constexpr MTU::pwm_port_t pwmout[2] = {
			{ MTU::CHANNEL::C, MTU::OUTPUT::HIGH_TO_LOW },
			{ MTU::CHANNEL::D, MTU::OUTPUT::LOW_TO_HIGH }
		};
		if(!mtu_.start_pwm2(MTU::CHANNEL::A, freq_, pwmout[0], pwmout[1])) {
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
