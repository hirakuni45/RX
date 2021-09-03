//=====================================================================//
/*! @file
    @brief  I2C サンプル @n
			対話形式で接続された I2C デバイスを操作する。@n
			RX24T: @n
					RX24T/clock_profile.hpp を参照 @n
					P00 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX66T: @n
					RX66T/clock_profile.hpp を参照 @n
					P00 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX72T: @n
					RX72T/clock_profile.hpp を参照 @n
					P01 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX64M: @n
					RX64M/clock_profile.hpp を参照 @n
					P07 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX71M: @n
					RX71M/clock_profile.hpp を参照 @n
					P07 ピンにLEDを接続する @n
					SCI1 を使用する @n
			RX65N (RX65N Envision kit): @n
					RX65x/clock_profile.hpp を参照 @n
					P70 に接続された LED を利用する @n
					SCI9 を使用する @n
			RX72N: (RX72N Envision kit) @n
					RX72N/clock_profile.hpp を参照 @n
					P40 ピンにLEDを接続する @n
					SCI2 を使用する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"
#include "common/command.hpp"
#include "common/iica_io.hpp"
#include "common/sci_i2c_io.hpp"

#include "chip/FT5206.hpp"

#include "common/format.hpp"
#include "common/input.hpp"

#include "common/string_utils.hpp"

namespace {

#if defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
#ifdef SOFT_I2C
	typedef device::PORT<device::PORTB, device::bitpos::B2> SDA;
	typedef device::PORT<device::PORTB, device::bitpos::B1> SCL;
	typedef device::si2c_io<SDA, SCL> I2C_IO;
#else
	typedef device::iica_io<device::RIIC0> I2C_IO;
#endif
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N" };
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N" };
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;
	typedef device::SCI4 I2C_CH;
	typedef utils::fixed_fifo<char, 512> RBF;
	typedef utils::fixed_fifo<char, 512> SBF;
	typedef device::sci_i2c_io<I2C_CH, RBF, SBF> I2C_IO;

	typedef utils::fixed_fifo<uint8_t, 64> RB64;
	typedef utils::fixed_fifo<uint8_t, 64> SB64;
	// タッチセンサー「RESET」制御ポート
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	// タッチセンサー I2C ポート設定
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::THIRD_I2C> FT5206_I2C;
	#define TOUCH_I2C
#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T" };
	typedef device::PORT<device::PORT0, device::bitpos::B1> LED;
	typedef device::SCI1 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;
#endif

//  環境コンテキスト
	typedef device::system_io<> SYSTEM_IO;

	typedef utils::fixed_fifo<char, 512> SCI_RXB;  // SCI RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> SCI_TXB;  // SCI TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, SCI_RXB, SCI_TXB> SCI_IO;
	SCI_IO		sci_io_;

#ifdef TOUCH_I2C
	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> TOUCH;
	TOUCH		touch_(ft5206_i2c_);
#endif

	typedef device::cmt_mgr<device::CMT0> CMT;
	CMT			cmt_;

	I2C_IO		i2c_io_;

	typedef utils::command<256> CMD;
	CMD 		cmd_;

	uint16_t	i2c_adr_ = 0;
	uint16_t	i2c_num_ = 0;
	uint8_t		i2c_data_[256] = { 0 };

	void scan_(uint32_t s, uint32_t e)
	{
		uint32_t n = 0;
		for(uint32_t i = s; i <= e; ++i) {
			uint8_t tmp[1];
			if(i2c_io_.recv(i, tmp, sizeof(tmp))) {
				utils::format("Ditect I2C address: 0x%02X (%3u, 0b%07b)\n") % i % i % i;
				++n;
			}
		}
		utils::format("  Ditect I2C Device(s): %d\n") % n;
	}

	void recv_()
	{
		if(i2c_num_ == 0) {
			utils::format("I2C: No data recv (skip)\n");
			return;
		}

		if(!i2c_io_.recv(i2c_adr_, i2c_data_, i2c_num_)) {
			auto sub = i2c_io_.get_error_str();
			utils::format("I2C I/O recv error: '%s'\n") % sub;
		} else {
			utils::str::dump_hex(i2c_data_, i2c_num_, 16);
		}
	}

	void send_()
	{
		if(i2c_num_ == 0) {
			utils::format("I2C: No data send (skip)\n");
			return;
		}

		if(!i2c_io_.send(i2c_adr_, i2c_data_, i2c_num_)) {
			auto sub = i2c_io_.get_error_str();
			utils::format("I2C I/O send error: '%s'\n") % sub;
		}
	}

	void command_()
	{
		if(cmd_.service()) {
			uint32_t cmdn = cmd_.get_words();
			const char* err = nullptr;
			if(cmdn >= 1) {
				if(cmd_.cmp_word(0, "-help")) {
					utils::format("I2C Monitor command\n");
					utils::format("    scan [start] [end]   scan I2C address\n");
					utils::format("    adr [X]              set I2C address X\n");
					utils::format("    r [num=1]            recv data [num] bytes\n");
					utils::format("    s data...            send data bytes\n");
					utils::format("    -help                help\n");
					utils::format("\n");
				} else if(cmd_.cmp_word(0, "scan")) {
					if(cmdn >= 2) {
						int32_t s_adr = 0;
						int32_t e_adr = 127;
						if(!cmd_.get_integer(1, s_adr, true)) {
							err = "start address invalid";
						}
						if(!cmd_.get_integer(2, e_adr, true)) {
							err = "end address invalid";
						}
						if(err == nullptr) {
							scan_(s_adr, e_adr);
						}
					} else {
						scan_(0, 127);
					}
				} else if(cmd_.cmp_word(0, "adr")) {
					if(cmdn < 2) {
						utils::format("I2C address: 0x%02X (%3u, 0b%07b)\n") % i2c_adr_ % i2c_adr_ % i2c_adr_;
					} else {
						int32_t val = 0;
						if(cmd_.get_integer(1, val, true)) {
							i2c_adr_ = val;
						} else {
							err = "I2C Address invalid";
						}
					}
				} else if(cmd_.cmp_word(0, "r")) {
					if(cmdn <= 1) {
						i2c_num_ = 1;
					} else {
						int32_t val = 1;
						if(cmd_.get_integer(1, val, true)) {
							i2c_num_ = val;
						} else {
							err = "I2C Recv num invalid";
						}
					}
					if(err == nullptr) {
						recv_();
						utils::format("\n");
					}
				} else if(cmd_.cmp_word(0, "s")) {
					if(cmdn > 1) {
						uint32_t l = 1;
						i2c_num_ = 0;
						while(l < cmdn) {
							int32_t val = 1;
							if(cmd_.get_integer(l, val, true)) {
								i2c_data_[i2c_num_] = val;
								++i2c_num_;
							} else {
								err = "I2C Send data invalid";
								break;
							}
							++l;
						}
						if(err == nullptr) {
							send_();
						}
					} else {
						err = "";
					}
				} else {
					err = "Command";
				}
			}
			if(err != nullptr) {
				char tmp[256];
				tmp[0] = 0;
				cmd_.get_word(0, tmp, sizeof(tmp));
				utils::format("%s error: '%s'\n") % err % tmp;
			}
		}
	}
}


extern "C" {
	// syscalls.c から呼ばれる、標準出力をシリアル入出力にバインド（stdout, stderr）
	void sci_putch(char ch)
	{
		sci_io_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_io_.puts(str);
	}

	// syscalls.c から呼ばれる、標準出力をシリアル入出力にバインド（stdin）
	char sci_getch(void)
	{
		return sci_io_.getch();
	}

	uint16_t sci_length()
	{
		return sci_io_.recv_length();
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	{  // タイマー設定（100Hz）
		uint8_t intr = 1;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		uint8_t intr = 2;        // 割り込みレベル
		uint32_t baud = 115200;  // ボーレート
		sci_io_.start(baud, intr);
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("Start I2C sample for '%s' %d[MHz]\n") % system_str_ % clk;

	{
		utils::format("SCI Baud rate (set):  %d\n") % sci_io_.get_baud_rate();
		float rate = 1.0f - static_cast<float>(sci_io_.get_baud_rate()) / sci_io_.get_baud_rate(true);
		rate *= 100.0f;
		utils::format("SCI Baud rate (real): %d (%3.2f [%%])\n") % sci_io_.get_baud_rate(true) % rate;
		utils::format("CMT rate (set):  %d [Hz]\n") % cmt_.get_rate();
		rate = 1.0f - static_cast<float>(cmt_.get_rate()) / cmt_.get_rate(true);
		rate *= 100.0f;
		utils::format("CMT rate (real): %d [Hz] (%3.2f [%%])\n") % cmt_.get_rate(true) % rate;
	}

	{  // I2C の開始
		uint8_t intr_lvl = 0;
		if(!i2c_io_.start(I2C_IO::MODE::MASTER, I2C_IO::SPEED::STANDARD, intr_lvl)) {
			utils::format("I2C Start fail...\n");
		} else {
			utils::format("I2C Start ok: (intrrupt level = %d)\n") % static_cast<int>(intr_lvl);
		}
	}

#ifdef TOUCH_I2C
	{  // FT5206 touch screen controller
		TOUCH::reset<FT5206_RESET>();
		uint8_t intr_lvl = 0;
		if(!ft5206_i2c_.start(FT5206_I2C::MODE::MASTER, FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
			utils::format("FT5206 I2C Start Fail...\n");
		} else {
			utils::format("FT5206/SCI-I2C Start\n");
		}
		if(!touch_.start()) {
			utils::format("FT5206 Start Fail...\n");
		} else {
			utils::format("FT5206 Start\n");
		}
	}
#endif

	LED::OUTPUT();
	LED::P = 0;

	cmd_.set_prompt("# ");

	uint8_t cnt = 0;
	while(1) {
		cmt_.sync();

#ifdef TOUCH_I2C
		touch_.update();
		{
			auto n = touch_.get_touch_num();
			if(n > 0) {
				utils::format("Touch: %d") % static_cast<int>(n);
				auto t = touch_.get_touch_pos(0);
				utils::format(", (%d, %d)") % t.pos.x % t.pos.y;
				utils::format("\n");
			}
		}
#endif
		command_();

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
