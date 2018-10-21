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

	// タイマー設定（１００Ｈｚ）
	{
		uint8_t intr = 3;
		cmt_.start(100, intr);
	}

	// SCI 設定
	{
		uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	// RS485/VFD 設定
	{
		uint8_t sci_level = 1;
		rs485_.start(9600, sci_level);
	}

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

		for(int i = 0; i < 10; ++i) {
			rs485_.putch('A');
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
