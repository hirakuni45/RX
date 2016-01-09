//=====================================================================//
/*!	@file
	@brief	Renesas RX Series Programmer (Flash Writer)
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <iostream>
#include "rx_prog.hpp"
#include "motsx_io.hpp"

rx::prog prog_;

int main(int argc, char* argv[])
{
	utils::motsx_io motsx;

	std::string inpath = "chager.mot";
	if(!motsx.load(inpath)) {
		std::cerr << "Can't open input file: '" << inpath << "'" << std::endl;
		return -1;
	}

	motsx.list_area_map();

	return 0;

	if(!prog_.start("/dev/ttyS8", "9600")) {
		prog_.end();
		return -1;
	}

	std::vector<uint8_t> mem;
	mem.resize(256);
	prog_.read(0xffffff00, mem.size(), &mem[0]);

	int i = 0;
	for(auto v : mem) {
		std::cout << (boost::format("%02X, ") % static_cast<uint32_t>(v));
		++i;
		if(i >= 16) {
			i = 0;
			std::cout << std::endl;
		} 
	}

	prog_.end();
}
