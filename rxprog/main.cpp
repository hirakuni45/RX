//=====================================================================//
/*!	@file
	@brief	Renesas RX Series Programmer (Flash Writer)
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <iostream>
#include "rx_prog.hpp"
#include "motsx_io.hpp"
#include "string_utils.hpp"
#include "area.hpp"

static const std::string version_ = "0.01b";

static rx::prog prog_;
static utils::motsx_io motsx_;

static void title_(const std::string& cmd)
{
	using namespace std;

	std::string c = utils::get_file_base(cmd);

	cout << "Renesas RX Series Programmer Version " << version_ << endl;
	cout << "Copyright (C) 2016, Hiramatsu Kunihito (hira@rvf-rc45.net)" << endl;
	cout << "usage:" << endl;
	cout << c << "[options] [mot file] ..." << endl;
	cout << endl;
	cout << "Options :" << endl;
	cout << "-d, --device=DEVICE\t\tSpecify device name" << endl;
	cout << "-e, --erase\t\t\tPerform a device erase to a minimum" << endl;
	cout << "    --erase-all, --erase-chip\tPerform rom and data flash erase" << endl;
	cout << "    --erase-rom\t\t\tPerform rom flash erase" << endl;
	cout << "    --erase-data\t\tPerform data flash erase" << endl;
//	cout << "-i, --id=xx:xx:xx:xx:xx:xx:xx\tSpecify protect ID" << endl;
	cout << "-P, --port=PORT\t\t\tSpecify serial port" << endl;
	cout << "-a, --area=ORG,END\t\tSpecify read area" << endl;
	cout << "-r, --read\t\t\tPerform data read" << endl;
	cout << "-s, --speed=SPEED\t\tSpecify serial speed" << endl;
	cout << "-v, --verify\t\t\tPerform data verify" << endl;
	cout << "    --device-list\t\tDisplay device list" << endl;
	cout << "-V, --verbose\t\t\tVerbose output" << endl;
	cout << "-w, --write\t\t\tPerform data write" << endl;
	cout << "    --progress\t\t\tdisplay Progress output" << endl;
	cout << "-h, --help\t\t\tDisplay this" << endl;
}


struct options {
	bool verbose = false;

	std::string	inp_file;

	std::string	device;
	bool	dv = false;

	std::string	speed;
	bool	br = false;

	std::string dev_path;
	std::string dev_comx;
	bool	dp = false;

	std::string id_val;
	bool	id = false;

	utils::areas area_val;
	bool	area = false;

	bool	read = false;
	bool	erase = false;
	bool	write = false;
	bool	verify = false;
	bool	device_list = false;
	bool	progress = false;
	bool	erase_data = false;
	bool	erase_rom = false;
	bool	help = false;


	bool set_area_(const std::string& s) {
		utils::strings ss = utils::split_text(s, ",");
		std::string t;
		if(ss.empty()) t = s;
		else if(ss.size() >= 1) t = ss[0];
		uint32_t org = 0;
		bool err = false;
		if(!utils::string_to_hex(t, org)) {
			err = true;
		}
		uint32_t end = org + 256;
		if(ss.size() >= 2) {
			if(!utils::string_to_hex(ss[1], end)) {
				err = true;
			}
		}
		if(err) {
			return false;
		}
		area_val.emplace_back(org, end);
		return true;
	}


	bool set_str(const std::string& t) {
		bool ok = true;
		if(br) {
			speed = t;
			br = false;
		} else if(dv) {
			device = t;
			dv = false;
		} else if(dp) {
			dev_path = t;
			dp = false;
		} else if(id) {
			id_val = t;
			id = false;
		} else if(area) {
			if(!set_area_(t)) {
				ok = false;
			}
			area = false;
		} else {
			inp_file = t;
		}
		return ok;
	}
};


int main(int argc, char* argv[])
{
	if(argc == 1) {
		title_(argv[0]);
		return 0;
	}

	options	opts;

   	// コマンドラインの解析
	bool opterr = false;
	for(int i = 1; i < argc; ++i) {
		const std::string p = argv[i];
		if(p[0] == '-') {
			if(p == "-V" || p == "-verbose") opts.verbose = true;
			else if(p == "-s") opts.br = true;
			else if(utils::string_strncmp(p, "--speed=", 8) == 0) { opts.speed = &p[8]; }
			else if(p == "-d") opts.dv = true;
			else if(utils::string_strncmp(p, "--device=", 9) == 0) { opts.device = &p[9]; }
			else if(p == "-P") opts.dp = true;
			else if(utils::string_strncmp(p, "--port=", 7) == 0) { opts.dev_path = &p[7]; }
			else if(p == "-a") opts.area = true;
///			else if(utils::string_strncmp(p, "--area=", 7) == 0) {
///				if(!opts.set_area_(&p[7])) {
///					opterr = true;
///				}
///			}
			else if(p == "-r" || p == "--read") opts.read = true;
			else if(p == "-e" || p == "--erase") opts.erase = true;
///			else if(p == "-i") opts.id = true;
///			else if(utils::string_strncmp(p, "--id=", 5) == 0) { opt.id_val = &p[5]; }
			else if(p == "-w" || p == "--write") opts.write = true;
			else if(p == "-v" || p == "--verify") opts.verify = true;
///			else if(p == "--device-list") opts.device_list = true;
			else if(p == "--progress") opts.progress = true;
			else if(p == "--erase-rom") opts.erase_rom = true;
			else if(p == "--erase-data") opts.erase_data = true;
			else if(p == "--erase-all" || p == "--erase-chip") {
				opts.erase_rom = true;
				opts.erase_data = true;
			} else if(p == "-h" || p == "--help") opts.help = true;
			else {
				opterr = true;
			}
		} else {
			if(!opts.set_str(p)) {
				opterr = true;
			}
		}
		if(opterr) {
			std::cerr << "Option error: '" << p << "'" << std::endl;
			opts.help = true;
		}
	}

	if(!motsx_.load(opts.inp_file)) {
		std::cerr << "Can't open input file: '" << opts.inp_file << "'" << std::endl;
		return -1;
	}

	motsx_.list_area_map();

//	return 0;

	rx::protocol::rx_t rx;
	rx.master_ = 1200;
	rx.sys_div_ = 8;
	rx.ext_div_ = 4;

	if(!prog_.start("/dev/ttyS8", 115200, rx)) {
		prog_.end();
		return -1;
	}

	if(1) {  // write
		auto areas = motsx_.create_area_map();
		if(!areas.empty()) {
			if(!prog_.start_write(true)) {
				prog_.end();
				return -1;
			}
		}
		
		for(const auto& a : areas) {
			uint32_t adr = a.min_ & 0xffffff00;
			uint32_t len = 0;
			while(len < (a.max_ - a.min_ + 1)) {
				std::cout << boost::format("%08X to %08X") % adr % (adr + 255) << std::endl;
				auto mem = motsx_.get_memory(adr);
				if(!prog_.write(adr, 256, &mem[0])) {
					prog_.end();
					return -1;
				}
				adr += 256;
				len += 256;
			}
		}
		if(!prog_.final_write()) {
			prog_.end();
			return -1;
		}
	}


	if(1) {  // read
		std::vector<uint8_t> mem;
		mem.resize(256);
		prog_.read(0xffff0100, mem.size(), &mem[0]);

		int i = 0;
		for(auto v : mem) {
			std::cout << (boost::format("%02X, ") % static_cast<uint32_t>(v));
			++i;
			if(i >= 16) {
				i = 0;
				std::cout << std::endl;
			} 
		}
	}

	prog_.end();
}
