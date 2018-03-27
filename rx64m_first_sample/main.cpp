//=====================================================================//
/*! @file
    @brief  RX64M ファースト・サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

namespace {

	typedef device::system_io<12000000> SYSTEM_IO;

	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;

}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	LED::DIR = 1;
	while(1) {
		utils::delay::milli_second(250);
		LED::P = 0;
		utils::delay::milli_second(250);
		LED::P = 1;
	}
}
