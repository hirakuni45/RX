//=====================================================================//
/*! @file
    @brief  RX24T CNC ドライバー @n
			・ステッピングモーターパルス出力 @n
			・リミットスイッチによる制御 @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"

#include "chip/VFD.hpp"

#include "cnc_pulse.hpp"

namespace {

	static const uint16_t VERSION = 40;

    typedef device::system_io<10000000> SYSTEM_IO;

	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;

	device::cmt_io<device::CMT0, utils::null_task>  cmt_;

	// 標準シリアルポート設定
	typedef utils::fixed_fifo<char, 1024> RBF;
	typedef utils::fixed_fifo<char,  128> SBF;
	typedef device::sci_io<device::SCI1, RBF, SBF> SCI;
	SCI		sci_;

	// RS485 VFD ポート設定
	typedef utils::fixed_fifo<char, 256> RS_RBF;
	typedef utils::fixed_fifo<char, 256> RS_SBF;
	static const device::port_map::option RS_PORT = device::port_map::option::SECOND;
	typedef device::PORT<device::PORTE, device::bitpos::B1> RS_CTRL;
	typedef device::sci_io<device::SCI5, RS_RBF, RS_SBF, RS_PORT, RS_CTRL> RS485;
	RS485	rs485_;

	typedef utils::command<256> COMMAND;
	COMMAND command_;

	typedef cnc::pulse<COMMAND>	CNC;
	CNC		cnc_(command_);
	
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
	SYSTEM_IO::setup_system_clock();

	// タイマー設定（１００Ｈｚ）
	{
		uint8_t intr = 0;
		cmt_.start(100, intr);
	}

	// SCI 設定
	{
		uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	// RS485/VFD 設定
//	{
//		uint8_t sci_level = 1;
//		rs485_.start(9600, sci_level);
//	}

	utils::format("CNC Driver Version %1d.%02d\n") % (VERSION / 100) % (VERSION % 100);

	cnc_.start();

	command_.set_prompt("# ");

	LED::DIR = 1;

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		cnc_.update();

		// コマンド入力と、コマンド解析
		if(command_.service()) {
			auto f = cnc_.service_command();
			if(!f) {
				utils::format("Error: '%s'\n") % command_.get_command();
			}
		}

///		for(int i = 0; i < 10; ++i) {
///			rs485_.putch('A');
///		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
