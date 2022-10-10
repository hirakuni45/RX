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
#include "common/renesas.hpp"
#include "common/cmt_mgr.hpp"
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

	device::cmt_mgr<device::CMT0, cmt_task>  cmt_;

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
	SYSTEM_IO::boost_master_clock();

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
			utils::format("%s: ") % nmea_.get_satellite_num();
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
