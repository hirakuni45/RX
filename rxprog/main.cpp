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

static utils::motsx_io motsx_;

void memory_dump_()
{
#if 0
		int i = 0;
		for(auto v : mem) {
			std::cout << (boost::format("%02X, ") % static_cast<uint32_t>(v));
			++i;
			if(i >= 16) {
				i = 0;
				std::cout << std::endl;
			} 
		}
#endif
}

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
///	cout << "-d, --device=DEVICE\t\tSpecify device name" << endl;
///	cout << "-e, --erase\t\t\tPerform a device erase to a minimum" << endl;
///	cout << "    --erase-all, --erase-chip\tPerform rom and data flash erase" << endl;
///	cout << "    --erase-rom\t\t\tPerform rom flash erase" << endl;
///	cout << "    --erase-data\t\tPerform data flash erase" << endl;
//	cout << "-i, --id=xx:xx:xx:xx:xx:xx:xx\tSpecify protect ID" << endl;
	cout << "-P, --port=PORT\t\t\tSpecify serial port" << endl;
///	cout << "-a, --area=ORG,END\t\tSpecify read area" << endl;
///	cout << "-r, --read\t\t\tPerform data read" << endl;
///	cout << "-s, --speed=SPEED\t\tSpecify serial speed" << endl;
	cout << "-v, --verify\t\t\tPerform data verify" << endl;
	cout << "-w, --write\t\t\tPerform data write" << endl;
///	cout << "    --progress\t\t\tdisplay Progress output" << endl;
///	cout << "    --device-list\t\tDisplay device list" << endl;
	cout << "-V, --verbose\t\t\tVerbose output" << endl;
	cout << "-h, --help\t\t\tDisplay this" << endl;
}


struct options {
	bool verbose = false;

	std::string	inp_file;

	std::string	device;
	bool	dv = false;

	std::string	speed;
	bool	br = false;

	std::string com_path;
	std::string com_name;
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
			com_path = t;
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
			if(p == "--verbose") opts.verbose = true;
///			else if(p == "-s") opts.br = true;
///			else if(utils::string_strncmp(p, "--speed=", 8) == 0) { opts.speed = &p[8]; }
///			else if(p == "-d") opts.dv = true;
///			else if(utils::string_strncmp(p, "--device=", 9) == 0) { opts.device = &p[9]; }
			else if(p == "-P") opts.dp = true;
			else if(p.find_first_of("--port=") == 0) { opts.com_path = &p[7]; }
///			else if(p == "-a") opts.area = true;
///			else if(utils::string_strncmp(p, "--area=", 7) == 0) {
///				if(!opts.set_area_(&p[7])) {
///					opterr = true;
///				}
///			}
///			else if(p == "-r" || p == "--read") opts.read = true;
///			else if(p == "-e" || p == "--erase") opts.erase = true;
///			else if(p == "-i") opts.id = true;
///			else if(utils::string_strncmp(p, "--id=", 5) == 0) { opt.id_val = &p[5]; }
			else if(p == "-w" || p == "--write") opts.write = true;
			else if(p == "-v" || p == "--verify") opts.verify = true;
///			else if(p == "--device-list") opts.device_list = true;
			else if(p == "--progress") opts.progress = true;
///			else if(p == "--erase-rom") opts.erase_rom = true;
///			else if(p == "--erase-data") opts.erase_data = true;
///			else if(p == "--erase-all" || p == "--erase-chip") {
//				opts.erase_rom = true;
//				opts.erase_data = true;
///			} else if(p == "-h" || p == "--help") opts.help = true;
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

	if(opts.verbose) {
		motsx_.list_area_map();
	}

    // Windwos系シリアル・ポート（COMx）の変換                                                  
    if(!opts.com_path.empty() && opts.com_path[0] != '/') {
		std::string s = utils::to_lower_text(opts.com_path);
        if(s.size() > 3 && s[0] == 'c' && s[1] == 'o' && s[2] == 'm') {
            int val;
            if(utils::string_to_int(&s[3], val)) {
                if(val >= 1 ) {
                    --val;
                    opts.com_name = opts.com_path;
                    opts.com_path = "/dev/ttyS" + (boost::format("%d") % val).str();
                }
            }
        }
    }
	if(opts.com_path.empty()) {
		std::cerr << "Serial port path not found." << std::endl;
		return -1;
	}

	rx::prog prog_(opts.verbose);

	rx::protocol::rx_t rx;
	rx.master_ = 1200;
	rx.sys_div_ = 8;
	rx.ext_div_ = 4;

	if(!prog_.start(opts.com_path, 115200, rx)) {
		prog_.end();
		return -1;
	}

	if(opts.write) {  // write
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
				if(opts.progress) {
					std::cout << '#';
				}
				/// std::cout << boost::format("%08X to %08X") % adr % (adr + 255) << std::endl;
				auto mem = motsx_.get_memory(adr);
				if(!prog_.write(adr, &mem[0])) {
					prog_.end();
					return -1;
				}
				adr += 256;
				len += 256;
			}
		}
		if(opts.progress) {
			std::cout << std::endl;
		}
		if(!prog_.final_write()) {
			prog_.end();
			return -1;
		}
	}

	if(opts.verify) {  // verify
		auto areas = motsx_.create_area_map();
		for(const auto& a : areas) {
			uint32_t len = a.max_ - a.min_ + 1;
			auto mem = motsx_.get_memory(a.min_);
			if(!prog_.verify(a.min_, &mem[a.min_ & 0xff], len)) {
				return -1;
			}
		}
	}

	prog_.end();
}
