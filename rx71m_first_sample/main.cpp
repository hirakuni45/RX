//=====================================================================//
/*! @file
    @brief  RX71M ファースト・サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

namespace {

	typedef device::system_io<12500000> SYSTEM_IO;

	typedef device::PORT<device::PORTE, device::bitpos::B3> LED;

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
