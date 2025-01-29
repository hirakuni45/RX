//=====================================================================//
/*! @file
    @brief  CPU 内蔵 Data Flash 操作サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
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

namespace {

	typedef utils::fixed_fifo<char, 256> RXB;  ///< SCI/RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 512> TXB;  ///< SCI/TX (SEND) バッファの定義
	typedef device::sci_io<board_profile::SCI_CH, RXB, TXB, board_profile::SCI_ORDER> SCI;
	SCI			sci_;

	typedef device::cmt_mgr<board_profile::CMT_CH> CMT;
	CMT			cmt_;

	typedef utils::command<256> COMMAND;
	COMMAND		command_;

	typedef device::flash_io FLASH_IO;
	FLASH_IO	flash_io_;


	void dump_(uint32_t org, uint32_t len) noexcept
	{
		bool adr = true;
		for(uint32_t i = 0; i < len; i += device::FLASH::DATA_WORD_SIZE) {
			if(adr) {
				utils::format("0x%04X:") % org;
				adr = false;
			}
			for(uint32_t j = 0; j < device::FLASH::DATA_WORD_SIZE; ++j) {
				uint8_t dat = flash_io_.read(org + j);
				if(j == 0) {
					utils::format(" ");
				}
				if(flash_io_.get_last_error() != FLASH_IO::ERROR::NONE) {
					utils::format("--");
				} else {
					utils::format("%02X") % static_cast<uint32_t>(dat);
				}
			}
			auto a = org;
			org += device::FLASH::DATA_WORD_SIZE;
			if(((a ^ org) & 16) != 0) {
				utils::format("\n");
				adr = true;
			}
		}
		if(!adr) {
			utils::format("\n");
		}
	}

	void shift4_(uint8_t* val) noexcept
	{
		for(uint32_t i = 0; i < device::FLASH::DATA_WORD_SIZE; ++i) {
			val[i] <<= 4;
			if(device::FLASH::DATA_WORD_SIZE <= (i + 1)) break;
			val[i] |= val[i + 1] >> 4;
		}
	}

	bool get_hex_data_(const char* inp, uint8_t* out) noexcept
	{
		for(u_int32_t i = 0; i < device::FLASH::DATA_WORD_SIZE; ++i) {
			out[i] = 0;
		}
		char ch;
		while((ch = *inp++) != 0) {
			if(ch >= 'a') ch -= 0x20;
			if(ch >= '0' && ch <= '9') {
				shift4_(out);
				out[device::FLASH::DATA_WORD_SIZE - 1] |= ch - '0';
			} else if(ch >= 'A' && ch <= 'F') {
				shift4_(out);
				out[device::FLASH::DATA_WORD_SIZE - 1] |= ch - 'A' + 10;
			} else {
				return false;
			}
		}
		return true;
	}

	void command_service_() noexcept
	{
		// コマンド入力と、コマンド解析
		if(!command_.service()) {
			return;
		}

		auto n = command_.get_words();
		if(command_.cmp_word(0, "erase") && n >= 2) {
			bool f = false;
			char buff[16];
			if(command_.get_word(1, buff, sizeof(buff))) {
				int bank = 0;
				if((utils::input("%d", buff) % bank).status()) {
					if(static_cast<uint32_t>(bank) < FLASH_IO::DATA_ERASE_NUM) {
						f = flash_io_.erase(bank);
						if(!f) {
							utils::format("Erase error: bank %d\n") % bank;
							f = true;
						} else {
							f = flash_io_.erase_check(bank);
							if(!f) {
								utils::format("Erase error: bank %d\n") % bank;
								f = true;
							} else {
								uint32_t s = bank * FLASH_IO::DATA_ERASE_SIZE;
								uint32_t e = s + FLASH_IO::DATA_ERASE_SIZE - 1;
								utils::format("Erase OK: bank %d, 0x%04X to 0x%04X\n") % bank % s % e;
							}
						}
					}
				}
			}
			if(!f) {
				utils::format("Erase param error: '%s'\n") % buff;
			}
		} else if(command_.cmp_word(0, "check") && n >= 2) {
			bool f = false;
			char buff[16];
			if(command_.get_word(1, buff, sizeof(buff))) {
				int bank = 0;
				if((utils::input("%d", buff) % bank).status()) {
					if(static_cast<uint32_t>(bank) < FLASH_IO::DATA_BLANK_NUM) {
						f = flash_io_.erase_check(bank);
						uint32_t s = bank * FLASH_IO::DATA_BLANK_SIZE;
						uint32_t e = s + FLASH_IO::DATA_BLANK_SIZE - 1;
						utils::format("Erase check: bank %d: 0x%04X to 0x%04X %s\n") % bank % s % e % (f ? "OK" : "NG");
						f = true;
					}
				}
			}
			if(!f) {
				utils::format("Erase check param error: '%s'\n") % buff;
			}
		} else if(command_.cmp_word(0, "checkw") && n >= 2) {
			bool f = false;
			char buff[16];
			if(command_.get_word(1, buff, sizeof(buff))) {
				uint32_t adrs = 0;
				if((utils::input("%x", buff) % adrs).status()) {
					if(adrs < FLASH_IO::DATA_SIZE) {
						f = flash_io_.erase_check_w(adrs);
						utils::format("Erase check word: 0x%04X %s\n") % adrs % (f ? "OK" : "NG");
						f = true;
					}
				}
			}
			if(!f) {
				utils::format("Erase check word param error: '%s'\n") % buff;
			}
		} else if((command_.cmp_word(0, "r") || command_.cmp_word(0, "read")) && n >= 2) {
			bool f = false;
			uint32_t org = 0;
			char buff[16];
			if(command_.get_word(1, buff, sizeof(buff))) {
				if((utils::input("%x", buff) % org).status()) {
					f = true;
				}
			}
			uint32_t len = device::FLASH::DATA_WORD_SIZE;
			if(f && n >= 3) {
				if(command_.get_word(2, buff, sizeof(buff))) {
					uint32_t end;
					if((utils::input("%x", buff) % end).status()) {
						if(end > org) {
							len = end - org + 1;
							len &= ~(device::FLASH::DATA_WORD_SIZE - 1);
						}
						f = true;
					}
				}
			}
			if(f) {
				dump_(org, len);
			} else {
				utils::format("Read param error: %s\n") % command_.get_command();
			}
		} else if(command_.cmp_word(0, "write") && n >= 3) {
			char buff[20];
			if(command_.get_word(1, buff, sizeof(buff))) {
				uint8_t err = 0;
				uint32_t org = 0;
				if((utils::input("%x", buff) % org).status()) {
					for(uint8_t i = 0; i < (n - 2); ++i) {
						if(command_.get_word(i + 2, buff, sizeof(buff))) {
							uint8_t tmp[device::FLASH::DATA_WORD_SIZE];
							if(get_hex_data_(buff, tmp)) {
								if(!flash_io_.write(org, tmp, device::FLASH::DATA_WORD_SIZE)) {
									utils::format("Write error: 0x%04X: '%s'\n") % org % buff;
								}
								org += device::FLASH::DATA_WORD_SIZE;								
							} else {
								++err;
							}
						} else {
							++err;
						}
						if(err > 0) break;
					}
				} else {
					++err;
				}
				if(err > 0) {
					utils::format("Write param error: '%s'\n") % command_.get_command();
				}
			}
		} else if(command_.cmp_word(0, "uid")) {
			if(FLASH_IO::get_uid_num() == 0) {
				utils::format("Unique ID not define.\n");
			} else {
				for(uint32_t i = 0; i < FLASH_IO::get_uid_num(); ++i) {
					auto id = FLASH_IO::get_uid(i);
					utils::format("Unique ID%d: %08X\n") % i % id;
				}
			}
		} else if(command_.cmp_word(0, "?") || command_.cmp_word(0, "help")) {
			utils::format("Data Flash Size: %d, Check Block Size: %d, Erase Block Size: %d, Word: %d\n")
				% FLASH_IO::DATA_SIZE % FLASH_IO::DATA_BLANK_SIZE % FLASH_IO::DATA_ERASE_SIZE % device::FLASH::DATA_WORD_SIZE;
			utils::format("erase [bank] (erase 0 to %d)\n") % (FLASH_IO::DATA_ERASE_NUM - 1);
			utils::format("check [bank] (erase check 0 to %d)\n") % (FLASH_IO::DATA_BLANK_NUM - 1);
			utils::format("checkw org (erase check word data)\n");
			utils::format("r[ead] org [end] (read)\n");
			utils::format("write org data... (write)\n");
			utils::format("uid (unique ID list)\n");
		} else {
			const char* p = command_.get_command();
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

	using namespace board_profile;

	{  // タイマー設定（100Hz）
		auto intr = device::ICU::LEVEL::_4;
		uint32_t freq = 100;
		cmt_.start(freq, intr);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	{
		auto clk = device::clock_profile::ICLK / 1'000'000;
		utils::format("Start Data Flash sample for '%s' %u [MHz]\n") % system_str_ % clk;
		auto fclk = device::clock_profile::FCLK / 1'000'000;
		utils::format("Flash drive clock: %u [MHz]\n") % fclk;
		utils::format("Data Flash total size: 0x%08X\n") % FLASH_IO::DATA_SIZE;
		utils::format("Data Flash blank size: %d bytes, %d banks\n") % FLASH_IO::DATA_BLANK_SIZE
			% FLASH_IO::DATA_BLANK_NUM;
		utils::format("Data Flash erase size: %d bytes, %d banks\n") % FLASH_IO::DATA_ERASE_SIZE
			% FLASH_IO::DATA_ERASE_NUM;
		utils::format("Data Flash word size: %d byte%c\n") % device::FLASH::DATA_WORD_SIZE
			% ((device::FLASH::DATA_WORD_SIZE > 1) ? "s" : "");
	}

	{  // DataFlash 開始
		if(!flash_io_.start()) {
			utils::format("Data Flash stat fail...\n");
		}
	}

	command_.set_prompt("# ");

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
