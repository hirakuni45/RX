//=====================================================================//
/*! @file
    @brief  I2C サンプル @n
			対話形式で接続された I2C デバイスを操作する。 @n
			接続想定デバイス： @n
					・24C32 (EEPROM, DS3231 ボードに内蔵) @n
					・DS3231 (RTC) @n
					・BMP280 (温度、圧力センサ)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2022 Kunihito Hiramatsu @n
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
#include "common/si2c_io.hpp"

#include "chip/FT5206.hpp"

#include "common/format.hpp"
#include "common/input.hpp"

#include "common/string_utils.hpp"

#include <functional>

#include "exec_cmd.hpp"

#include "chip/DS3231.hpp"
#include "chip/bmp280.hpp"
#include "chip/AS5600.hpp"

namespace {

	static constexpr int VERSION = 50;

#if defined(SIG_RX62N)
	static const char* system_str_ = { "RX62N BlueBoard-RX62N_100pin" };
	typedef device::PORT<device::PORT0, device::bitpos::B5, false> LED;
	typedef device::SCI0 SCI_CH;

// #define SOFT_I2C
#ifdef SOFT_I2C
	typedef device::PORT<device::PORTB, device::bitpos::B2> SDA;
	typedef device::PORT<device::PORTB, device::bitpos::B1> SCL;
	typedef device::si2c_io<SDA, SCL> I2C_IO;
#else
	typedef device::iica_io<device::RIIC0> I2C_IO;
#endif
#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;
#ifdef SOFT_I2C
	typedef device::PORT<device::PORTB, device::bitpos::B2> SDA;
	typedef device::PORT<device::PORTB, device::bitpos::B1> SCL;
	typedef device::si2c_io<SDA, SCL> I2C_IO;
#else
	typedef device::iica_io<device::RIIC0> I2C_IO;
#endif
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> LED;
	typedef device::SCI1 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> LED;
	typedef device::SCI1 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N Envision Kit" };
	typedef device::PORT<device::PORT7, device::bitpos::B0, false> LED;
	typedef device::SCI9 SCI_CH;

	typedef device::iica_io<device::RIIC0> I2C_IO;

#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N Envision Kit" };
	typedef device::PORT<device::PORT4, device::bitpos::B0, false> LED;
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
	static const char* system_str_ = { "RX72T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B1, false> LED;
	typedef device::SCI1 SCI_CH;

//	#define SOFT_I2C

#ifdef SOFT_I2C
	typedef device::PORT<device::PORTB, device::bitpos::B2> SDA;
	typedef device::PORT<device::PORTB, device::bitpos::B1> SCL;
	typedef device::si2c_io<SDA, SCL> I2C_IO;
#else
	typedef device::iica_io<device::RIIC0> I2C_IO;
#endif
#endif

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


//	typedef chip::AS5600<I2C_IO> AS5600;
//	AS5600		as5600_(i2c_io_);


	typedef std::function<void()> I2C_TASK;

	int			i2c_dev_idx_ = -1;

	typedef utils::exec_cmd<I2C_IO, CMD> EXEC_CMD;
	EXEC_CMD	exec_cmd_(i2c_io_, cmd_);

	struct i2c_dev {
		bool		ena_;
		uint8_t		adr_;
		const char*	name_;
		const char*	opts_;
		utils::exec_base::DEV	dev_;
		i2c_dev(uint8_t adr, const char* name, const char* opts, utils::exec_base::DEV dev) noexcept :
			ena_(false),
			adr_(adr),
			name_(name),
			opts_(opts),
			dev_(dev)
		{ }
	};


	bool exec_common_(bool exit = false)
	{
		if(exit || cmd_.cmp_word(0, "exit")) {
			cmd_.set_prompt("# ");
			i2c_dev_idx_ = -1;
//			start_i2c_dev_ = false;
			return true;
		} else {
			return false;
		}
	}


	static constexpr int I2C_DEV_NUM = 11;
	i2c_dev		i2c_dev_[I2C_DEV_NUM] = {
		{ 0x36, "AS5600",  "(Contactless Potentiometer)", utils::exec_base::DEV::AS5600 },
		{ 0x50, "EEPROM0", "ID=0", utils::exec_base::DEV::EEPROM },
		{ 0x51, "EEPROM1", "ID=1", utils::exec_base::DEV::EEPROM },
		{ 0x52, "EEPROM2", "ID=2", utils::exec_base::DEV::EEPROM },
		{ 0x53, "EEPROM3", "ID=3", utils::exec_base::DEV::EEPROM },
		{ 0x54, "EEPROM4", "ID=4", utils::exec_base::DEV::EEPROM },
		{ 0x55, "EEPROM5", "ID=5", utils::exec_base::DEV::EEPROM },
		{ 0x56, "EEPROM6", "ID=6", utils::exec_base::DEV::EEPROM },
		{ 0x57, "EEPROM7", "ID=7", utils::exec_base::DEV::EEPROM },
		{ 0x68, "DS3231",  "(RTC)", utils::exec_base::DEV::DS3231 },
		{ 0x77, "BMP280",  "(Pressure Sensor)", utils::exec_base::DEV::BMP280 },
	};


	void list_()
	{
		utils::format("Exec support device:\n");
		for(uint32_t i = 0; i < I2C_DEV_NUM; ++i) {
			utils::format("  I2C Device 0x%02X: '%s' (%s)\n")
				% static_cast<uint16_t>(i2c_dev_[i].adr_) % i2c_dev_[i].name_ % i2c_dev_[i].opts_;
		}
	}


	int find_i2c_(uint8_t adr)
	{
		for(uint32_t i = 0; i < I2C_DEV_NUM; ++i) {
			if(i2c_dev_[i].adr_ == adr) {
				return i;
			}
		}
		return -1;
	}


	void scan_(uint32_t s, uint32_t e)
	{
		uint32_t num = 0;
		for(uint32_t i = s; i <= e; ++i) {
			uint8_t tmp[1];
			if(i2c_io_.recv(i, tmp, sizeof(tmp))) {
				auto n = find_i2c_(i);
				const char* name = "";
				const char* opts = "";
				if(n >= 0 && n < I2C_DEV_NUM) {
					name = i2c_dev_[n].name_;
					opts = i2c_dev_[n].opts_;
					i2c_dev_[n].ena_ = true;
				}
				utils::format("Ditect %s: 0x%02X (%3u, 0b%07b), '%s'\n") % name % i % i % i % opts;
				++num;
			}
		}
		if(num == 0) {
			utils::format("  No Ditect I2C Device\n");
		} else {
			utils::format("  Ditect I2C Device(s): %d\n") % num;
		}
	}


	void exec_(const char* name)
	{
		for(int i = 0; i < I2C_DEV_NUM; ++i) {
			if(strcmp(i2c_dev_[i].name_, name) == 0) {
				if(!i2c_dev_[i].ena_) {
					uint8_t tmp[1];
					if(i2c_io_.recv(i2c_dev_[i].adr_, tmp, sizeof(tmp))) {
						i2c_dev_[i].ena_ = true;
					} else {
						utils::format("Device is not ditect: '%s'\n") % name;
						return;
					}
				}
				if(exec_cmd_.start(i2c_dev_[i].adr_, i2c_dev_[i].dev_)) {
					i2c_dev_idx_ = i;
					static char tmp[16];
					strcpy(tmp, i2c_dev_[i].name_);
					strcat(tmp, " $ ");
					cmd_.set_prompt(tmp);
				}
				return;
			}
		}
		utils::format("No match I2C device name: '%s'\n") % name;
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
		if(i2c_dev_idx_ >= 0) {
			exec_cmd_.service();
		}

		if(cmd_.service()) {
			if(i2c_dev_idx_ >= 0) {
				if(exec_cmd_.analize()) {
					i2c_dev_idx_ = -1;
					cmd_.set_prompt("# ");
				}
				return;
			}

			uint32_t cmdn = cmd_.get_words();
			const char* err = nullptr;
			if(cmdn >= 1) {
				if(cmd_.cmp_word(0, "--help") || cmd_.cmp_word(0, "-help") || cmd_.cmp_word(0, "?")) {
					utils::format("I2C Monitor command version %d.%02d\n")
						% static_cast<int>(VERSION / 100) % static_cast<int>(VERSION % 100);
					utils::format("    list                       list for exec device\n");
					utils::format("    scan [start=0] [end=127]   scan I2C address\n");
					utils::format("    exec I2C-name              exec I2C operations\n");
					utils::format("    adr [X]                    set I2C address X\n");
					utils::format("    r [num=1]                  recv data [num] bytes\n");
					utils::format("    s data...                  send data bytes\n");
					utils::format("    --help -help ?             help\n");
					utils::format("\n");
				} else if(cmd_.cmp_word(0, "list")) {
					list_();
				} else if(cmd_.cmp_word(0, "scan")) {
					if(cmdn >= 3) {
						int32_t s_adr = 0;
						int32_t e_adr = 127;
						if(!cmd_.get_integer(1, s_adr, true)) {
							err = "I2C start address invalid";
						}
						if(!cmd_.get_integer(2, e_adr, true)) {
							err = "I2C end address invalid";
						}
						if(err == nullptr) {
							scan_(s_adr, e_adr);
						}
					} else {
						scan_(0, 127);
					}
				} else if(cmd_.cmp_word(0, "exec")) {
					if(cmdn >= 2) {
						char tmp[256];
						tmp[0] = 0;
						cmd_.get_word(1, tmp, sizeof(tmp));
						exec_(tmp);
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
		auto intr = device::ICU::LEVEL::_1;
		cmt_.start(100, intr);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_2;
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
		auto intr_lvl = device::ICU::LEVEL::_4;
		if(!i2c_io_.start(I2C_IO::MODE::MASTER, I2C_IO::SPEED::STANDARD, intr_lvl)) {
			utils::format("I2C Start fail...\n");
		} else {
			utils::format("I2C Start OK: (intrrupt level = %d)\n") % static_cast<int>(intr_lvl);
		}
	}

#ifdef TOUCH_I2C
	{  // FT5206 touch screen controller
		TOUCH::reset<FT5206_RESET>();
		auto intr_lvl = device::ICU::LEVEL::_2;
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
//			auto a = as5600_.get_raw_angle();
//			utils::format("A: %4u\n") % a;
		}
		if(cnt < 25) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
