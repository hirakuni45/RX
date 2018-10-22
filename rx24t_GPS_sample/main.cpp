//=====================================================================//
/*! @file
    @brief  RX24T GPS サンプル @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
			・PB6/RXD5(27) <--- GPS-TX @n
			・PB5/TXD5(28) ---> GPS-RX
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/nmea_dec.hpp"

namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fixed_fifo<char, 256> fifo256;
	typedef utils::fixed_fifo<char, 512> fifo512;
	device::sci_io<device::SCI1, fifo256, fifo256> sci1_;
	typedef device::sci_io<device::SCI5, fifo512, fifo256> SCI5;
	SCI5	sci5_;

	utils::nmea_dec<SCI5> nmea_(sci5_);
}

extern "C" {

	void sci_putch(char ch)
	{
		sci1_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci1_.puts(str);
	}

	char sci_getch(void)
	{
		return sci1_.getch();
	}

	uint16_t sci_length()
	{
		return sci1_.recv_length();
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
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	{
		// タイマー設定（６０Ｈｚ）
		uint8_t cmt_level = 4;
		cmt_.start(60, cmt_level);
	}

	{
		// SCI1 設定
		uint8_t sci_level = 2;
		sci1_.start(115200, sci_level);
	}

	{
		// SCI5 設定 (GPS)
		uint8_t sci_level = 2;
		sci5_.start(9600, sci_level);
	}

	utils::format("RX24T GPS sample\n");

	device::PORT0::PDR.B0 = 1; // output

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		auto f = nmea_.service();
		if(f) {
			utils::format("%s: ") % nmea_.get_satellite();
			utils::format("D/T: %s %s, ") % nmea_.get_date() % nmea_.get_time();
			utils::format("Lat: %s, ") % nmea_.get_lat();
			utils::format("Lon: %s, ") % nmea_.get_lon();
			utils::format("Alt: %s [%s]\n") % nmea_.get_altitude() % nmea_.get_altitude_unit();
		};

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B0 = (cnt < 10) ? 0 : 1;
	}
}
