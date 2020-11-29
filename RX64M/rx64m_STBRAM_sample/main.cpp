//=====================================================================//
/*! @file
    @brief  RX64M RTC サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/log_man.hpp"

namespace {

	typedef device::cmt_mgr<device::CMT0, utils::null_task> CMT;
	CMT		cmt_;

	typedef utils::fixed_fifo<char, 256> BUFFER;
	typedef device::sci_io<device::SCI1, BUFFER, BUFFER> SCI;
	SCI		sci_;

	utils::command<64> command_;

	typedef utils::log_man<device::standby_ram> LOG_MAN;
	LOG_MAN		log_man_;
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
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::system_io<12000000>::setup_system_clock();

	{  // タイマー設定（６０Ｈｚ）
		uint8_t cmt_irq_level = 4;
		cmt_.start(60, cmt_irq_level);
	}

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	utils::format("RX64M StadbyRAM/LOG sample\n");

	log_man_.start();

	device::PORT0::PDR.B7 = 1; // output

	command_.set_prompt("# ");

	uint32_t cnt = 0;
	bool loge = false;
	while(1) {
		cmt_.sync();

		// コマンド入力と、コマンド解析
		bool f = command_.service();
		if(loge) {	
			if(f) {
				const char* p = command_.get_command();
				char ch;
				while((ch = *p++) != 0) {
					if(ch == ('C' - 0x40)) {
						utils::format("Stop LOG\n");
						command_.set_prompt("# ");
						loge = false;
						break;
					}
					log_man_.putch(ch);
				}
				if(loge) {
					log_man_.putch('\n');
				}
			}
		} else if(f) {
			uint8_t cmdn = command_.get_words();
			if(cmdn >= 1) {
				if(command_.cmp_word(0, "log")) {
					auto len = log_man_.get_length();
					utils::format("LOG length: %d\n") % len;
					uint16_t pos = 0;
					while(pos < len) {
						char ch = log_man_.getch(pos);
						if(ch == '\n') {
							sci_putch('\r');
						}
						sci_putch(ch);
						++pos;
					}
				} else if(command_.cmp_word(0, "start")) {
					utils::format("Start LOG\n");
					loge = true;
					command_.set_prompt("");
				} else if(command_.cmp_word(0, "clear")) {
					log_man_.clear();
				} else if(command_.cmp_word(0, "help") || command_.cmp_word(0, "?")) {
					utils::format("start\n");
					utils::format("clear\n");
					utils::format("log\n");
				} else {
					char buff[32];
					if(command_.get_word(0, buff, sizeof(buff))) {
						utils::format("Command error: '%s'\n") % buff;
					}
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
