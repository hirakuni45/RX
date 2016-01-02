#pragma once
//=====================================================================//
/*!	@file
	@brief	RX programmer クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "rx_protocol.hpp"
#include <boost/format.hpp>

namespace rx {
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	rx_prog クラス
	 */
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class prog {
		bool		verbose_ = true;
		protocol	proto_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	接続速度を変更する
			@param[in]	brate	ボーレート
			@return エラー無ければ「true」
		*/
		//-------------------------------------------------------------//
		bool start(const std::string& path, const std::string& brate) {

			// 開始
			if(!proto_.start(path)) {
				std::cerr << "Can't open path: '" << path << "'" << std::endl;
				return false;
			}

			// コネクション
			if(!proto_.connection()) {
				proto_.end();
				std::cerr << "Can't connection." << std::endl;
				return false;
			}
			if(verbose_) {
				std::cout << "Connection OK." << std::endl;
			}

			// 問い合わせ開始
			if(!proto_.inquiry_device()) {
				proto_.end();
				std::cerr << "Inquiry device error." << std::endl;
				return false;
			}
			auto dev = proto_.get_device();
			if(verbose_) {
				std::cout << (boost::format("Device: %s") % dev.name_) << std::endl;
				std::cout << (boost::format("Device ID: 0x%0X") % dev.code_) << std::endl;
			}
			// デバイス選択
			if(!proto_.select_device(dev.code_)) {
				proto_.end();
				std::cerr << "Select device error." << std::endl;
				return false;
			}




#if 0
			// ボーレート変更
			int val;
			if(!utils::string_to_int(brate, val)) {
				std::cerr << "Baud rate conversion error: '" << brate << std::endl;
				return false;
			}
			speed_t speed;
			switch(val) {
			case 9600:   speed = B9600;   break;
			case 19200:  speed = B19200;  break;
			case 38400:  speed = B38400;  break;
			case 57600:  speed = B57600;  break;
			case 115200: speed = B115200; break;
			default:
				proto_.end();
				std::cerr << "Baud rate error: " << brate << std::endl;
				return false;
			}

			if(!proto_.change_speed(speed)) {
				proto_.end();
				std::cerr << "Change speed error: " << brate << std::endl;
				return false;
			}
			if(verbose_) {
				std::cout << "Change speed OK: " << brate << " [bps]" << std::endl;
			}

			// バージョンの取得
			ver_ = proto_.get_version();
			if(ver_.empty()) {
				proto_.end();
				std::cerr << "Get version error..." << std::endl;
				return false;
			}
			if(verbose_) {
				std::cout << "Version: '" << ver_ << "'" << std::endl;
			}

			// ID チェック認証
			if(!proto_.id_inspection(id_)) {
				std::cerr << "ID error: ";
				for(int i = 0; i < 7; ++i) {
					std::cerr << std::hex << std::setw(2) << std::uppercase << std::setfill('0')
							  << "0x" << static_cast<int>(id_.buff[i]) << ' ';
				}
				proto_.end();
				std::cerr << std::dec << std::endl;
				return false;
			}
			if(verbose_) {
				std::cout << "ID OK: ";
				for(int i = 0; i < 7; ++i) {
					std::cout << std::hex << std::setw(2) << std::uppercase << std::setfill('0')
							  << "0x" << static_cast<int>(id_.buff[i]) << ' ';
				}
				std::cout << std::endl;
			}

			set_.clear();
#endif
			return true;
		}



#if 0
	bool read(uint32_t top, uint8_t* data) {
		if(!proto_.read_page(top, data)) {
			std::cerr << "Read error: " << std::hex << std::setw(6)
					  << static_cast<int>(top) << " to " << static_cast<int>(top + 255)
					  << std::endl;
			return false;
		}
		return true;
	}


	bool erase(uint32_t top) {
		uint32_t area = 1024;
		if(top >= 0x8000) area = 4096;

		uint32_t adr = top & ~(area - 1);
		if(set_.find(adr) != set_.end()) {
			return true;
		}
		set_.insert(adr);

		// イレース
		if(!proto_.erase_page(top)) {
			std::cerr << "Erase error: " << std::hex << std::setw(6)
					  << static_cast<int>(top) << " to " << static_cast<int>(top + 255)
					  << std::endl;
			return false;
		}
		return true;
	}


	bool write(uint32_t top, const uint8_t* data) {
		using namespace r8c;
		// ページ書き込み
		if(!proto_.write_page(top, data)) {
   			std::cerr << "Write error: " << std::hex << std::setw(6)
					  << static_cast<int>(top) << " to " << static_cast<int>(top + 255)
					  << std::endl;
			return false;
		}
		return true;
   	}


	bool verify(uint32_t top, const uint8_t* data) {
		// ページ読み込み
		uint8_t tmp[256];
   		if(!proto_.read_page(top, tmp)) {
   			std::cerr << "Read error: " << std::hex << std::setw(6)
					  << static_cast<int>(top) << " to " << static_cast<int>(top + 255)
					  << std::endl;
   			return false;
   		}

		for(int i = 0; i < 256; ++i) {
			if(data[i] != tmp[i]) {
   			std::cerr << "Verify error: " << std::hex << std::setw(6)
					  << "0x" << static_cast<int>(top)
					  << std::setw(2) << static_cast<int>(data[top + i]) << " -> "
					  << static_cast<int>(tmp[i])
					  << std::endl;
				return false;
			}
		}
		return true;
	}
#endif

		//-------------------------------------------------------------//
		/*!
			@brief	終了
		*/
		//-------------------------------------------------------------//
		void end() {
			proto_.end();
		}
	};
}
