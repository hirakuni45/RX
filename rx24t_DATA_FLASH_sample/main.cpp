//=====================================================================//
/*! @file
    @brief  RX24T EEPROM サンプル @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"

namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 128> fifo128;
	device::sci_io<device::SCI1, fifo128, fifo128> sci_;

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
	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MEMWAIT = 0b10; // 80MHz 動作 wait 設定

	while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");
	device::SYSTEM::OPCCR = 0;  // 高速モード選択
	while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");

	// clock osc 10MHz
	device::SYSTEM::MOSCWTCR = 9;	// 4ms wait
	// メインクロック・ドライブ能力設定、内部発信
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV21.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;  // メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	device::SYSTEM::PLLCR.STC = 0b001111;		// PLL input: 1, PLL 8 倍(80MHz)
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/4 (80/4=20)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (80/1=80)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (80/1=80)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (80/2=40)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (80/2=40)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

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

	utils::format("RX24T DataFlash sample\n");

	command_.set_prompt("# ");

	device::PORT0::PDR.B0 = 1; // output

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		// コマンド入力と、コマンド解析
		if(command_.service()) {
			auto n = command_.get_words();
			if(command_.cmp_word(0, "erase") && n >= 2) {
				bool f = false;
				char buff[8];
				if(command_.get_word(1, buff, sizeof(buff))) {
					char nb = buff[4];
					if(buff[5] == 0 && std::strncmp(buff, "bank", 4) == 0 && nb >= '0' && nb <= '7') {
						f = flash_.erase(static_cast<FLASH::data_area>(nb - '0'));
						if(!f) {
							utils::format("Erase error: bank%c\n") % nb;
							f = true;
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
				sci_puts("erase bank0..7 (erase bank0 to bank7)\n");
				sci_puts("r org [end] (read)\n");
				sci_puts("write org data... (write)\n");
			} else {
				const char* p = command_.get_command();
				if(p[0]) {
					sci_puts("command error: ");
					sci_puts(p);
					sci_puts("\n");
				}
			}
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B0 = (cnt < 10) ? 0 : 1;
	}
}
