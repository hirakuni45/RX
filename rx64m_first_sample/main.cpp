//=====================================================================//
/*! @file
    @brief  RX64M メイン
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
// #include "RX64M/system.hpp"
#include "RX600/port.hpp"

namespace {

	void wait_delay_(uint32_t n)
	{
		// とりあえず無駄ループ
		for(uint32_t i = 0; i < n; ++i) {
			asm("nop");
		}
	}

}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::PORT0.PDR.B7 = 1; // output
	while(1) {
		wait_delay_(1000000);
		device::PORT0.PODR.B7 = 0;
		wait_delay_(1000000);
		device::PORT0.PODR.B7 = 1;
	}
}
