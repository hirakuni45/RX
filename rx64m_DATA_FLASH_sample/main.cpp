//=====================================================================//
/*! @file
    @brief  RX64M Data Flash サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/command.hpp"

namespace {

	device::cmt_io<device::CMT0, utils::null_task>  cmt_;

	typedef utils::fixed_fifo<char, 256> BUFFER;
	device::sci_io<device::SCI1, BUFFER, BUFFER> sci_;

	utils::command<256> command_;

	typedef device::flash_io FLASH;
	FLASH flash_;
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

	uint16_t sci_length()
	{
		return sci_.recv_length();
	}


	uint16_t get_hexadecimal_(const char* str)
	{
		uint16_t v = 0;
		char ch;
		while((ch = *str++) != 0) {
			v <<= 4;
			if(ch >= '0' && ch <= '9') v |= ch - '0';
			else if(ch >= 'A' && ch <= 'F') v |= ch - 'A' + 10;
			else if(ch >= 'a' && ch <= 'f') v |= ch - 'a' + 10;
			else return 0;
		}
		return v;
	}


	void dump_(uint16_t org, uint16_t len)
	{
		bool adr = true;
		for(uint16_t i = 0; i < len; ++i) {
			if(adr) {
				utils::format("0x%04X:") % static_cast<uint32_t>(org);
				adr = false;
			}
			uint8_t dat = flash_.read(org);
			utils::format(" %02X%") % static_cast<uint32_t>(dat);
			uint16_t a = org;
			++org;
			if(((a ^ org) & 16) != 0) {
				utils::format("\n");
				adr = true;
			}
		}
		if(!adr) {
			utils::format("\n");
		}
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::system_io<12000000>::setup_system_clock();

	// タイマー設定（６０Ｈｚ）
	uint8_t cmt_irq_level = 4;
	cmt_.start(60, cmt_irq_level);

	{  // SCI 開始
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	{  // DataFlash 開始
		flash_.start();
	}

	utils::format("RX64M Data Flash sample\n");
	utils::format("Data Flash size: %08X\n") % FLASH::data_flash_size;

	command_.set_prompt("# ");

	device::PORT0::PDR.B7 = 1; // output

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		// コマンド入力と、コマンド解析
		if(command_.service()) {
			auto n = command_.get_words();
			if(command_.cmp_word(0, "erase") && n >= 2) {
				bool f = false;
				char buff[16];
				if(command_.get_word(1, buff, sizeof(buff))) {
					int bank = 0;
					if((utils::input("%d", buff) % bank).status()) {
						if(static_cast<uint32_t>(bank) < FLASH::data_flash_bank) {
							f = flash_.erase(bank);
							if(!f) {
								utils::format("Erase error: bank %d\n") % bank;
								f = true;
							} else {
								f = flash_.erase_check(bank);
								if(!f) {
									utils::format("Erase Check error: bank %d\n") % bank;
									f = true;
								}
							}
						}
					}
				}
				if(!f) {
					utils::format("Erase param error: '%s'\n") % buff;
				}
			} else if(command_.cmp_word(0, "r") && n >= 2) {
				bool f = true;
				uint16_t org = 0;
				char buff[8];
				if(command_.get_word(1, buff, sizeof(buff))) {
					org = get_hexadecimal_(buff);
				} else {
					f = false;
				}
				uint16_t len = 1;
				if(n >= 3) {
					if(command_.get_word(2, buff, sizeof(buff))) {
						len = get_hexadecimal_(buff);
					} else {
						f = false;
					}
				}
				if(f) {
					dump_(org, len);
				} else {
					utils::format("Read param error: %s\n") % command_.get_command();
				}
			} else if(command_.cmp_word(0, "write") && n >= 3) {
				char buff[8];
				if(command_.get_word(1, buff, sizeof(buff))) {
					uint16_t org = get_hexadecimal_(buff);
					for(uint8_t i = 2; i < n; ++i) {
						if(command_.get_word(i, buff, sizeof(buff))) {
							uint16_t data = get_hexadecimal_(buff);
							if(!flash_.write(org, data)) {
								utils::format("Write error: %04X: %02X\n")
									% static_cast<uint32_t>(org) % static_cast<uint32_t>(data);
							}
							++org;
						}
					}
				}
			} else if(command_.cmp_word(0, "?") || command_.cmp_word(0, "help")) {
				utils::format("erase [bank] (erase 0 to %d)\n") % FLASH::data_flash_bank;
				utils::format("r org [end] (read)\n");
				utils::format("write org data... (write)\n");
			} else {
				const char* p = command_.get_command();
				if(p[0]) {
					utils::format("command error: '%s'\n") % p;
				}
			}
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B7 = (cnt < 10) ? 0 : 1;
	}
}
