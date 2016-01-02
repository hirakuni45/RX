//=====================================================================//
/*!	@file
	@brief	Renesas RX Series Programmer (Flash Writer)
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <iostream>
#include "rx_prog.hpp"

rx::prog prog_;

int main(int argc, char* argv[])
{
	prog_.start("/dev/ttyS8", "9600");




	prog_.end();
}
