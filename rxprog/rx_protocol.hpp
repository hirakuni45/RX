#pragma once
//=====================================================================//
/*!	@file
	@brief	RX プログラミング・プロトコル・クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "rs232c_io.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <boost/format.hpp>

namespace rx {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RX プログラミング・プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class protocol {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	device 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct device {
			uint32_t	code_ = 0;
			std::string	name_;

			void info(const std::string& head = "") const {
				std::cout << head << (boost::format("Device: %s") % name_) << std::endl;
				std::cout << head << (boost::format("Device ID: 0x%0X") % code_) << std::endl;
			}
		};
		typedef std::vector<device> devices;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	clock_mode 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct clock_mode {
			uint8_t	type_ = 0;

			void info(const std::string& head = "") const {
				std::cout << head << (boost::format("Clock Mode: 0x%02X") % static_cast<int>(type_))
					<< std::endl;
			}
		};
		typedef std::vector<clock_mode> clock_modes;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	multiplier 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct multiplier {
			typedef std::vector<uint8_t> list;
			list	list_;

			void info(const std::string& head = "") const {
				std::cout << head << "Multiplier: ";
				uint32_t i = 0;
				for(auto v : list_) {
					std::cout << static_cast<int>(v);
					++i;
					if(i < list_.size()) {
						std::cout << ", ";
					}
				}
				std::cout << std::endl;
			}
		};
		typedef std::vector<multiplier> multipliers;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	frequency 構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct frequency {
			uint16_t	min_ = 0;
			uint16_t	max_ = 0;

			void info(const std::string& head = "") const {
				std::cout << head << "Frequency Min: "
					<< (static_cast<float>(min_) / 100.0f) << " MHz, Max: "
					<< (static_cast<float>(max_) / 100.0f) << " MHz"
					<< std::endl;
			}
		};
		typedef std::vector<frequency> frequencies;


	private:
		utils::rs232c_io	rs232c_;

		bool				connection_ = false;

		devices				devices_;
		clock_modes			clock_modes_;
		uint8_t				clock_num_ = 0;
		multipliers			multipliers_;
		frequencies			frequencies_;

		uint32_t	   		baud_rate_;

		uint8_t				last_error_ = 0;

		bool command_(uint8_t cmd) {
			bool f = rs232c_.send(static_cast<char>(cmd));
			rs232c_.sync_send();
			return f;
		}

		bool read_(void* buff, uint32_t len) {
			timeval tv;
			tv.tv_sec  = 5;
			tv.tv_usec = 0;
			return rs232c_.recv(buff, len, tv) == len;
		}

		bool write_(const void* buff, uint32_t len) {
			uint32_t wr = rs232c_.send(buff, len);
			rs232c_.sync_send();
			return wr == len;
		} 

		uint32_t get32_(const uint8_t* p) {
			uint32_t v;
			v = p[0];
			v |= p[1] << 8;
			v |= p[2] << 16;
			v |= p[3] << 24;
			return v;
		}

		uint8_t sum_(const uint8_t* buff, uint32_t len) {
			uint16_t sum = 0;
			for(uint32_t i = 0; i < len; ++i) {
				sum += *buff++;
			}
			return 0x100 - sum;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	path	シリアルデバイスパス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(const std::string& path) {
			if(!rs232c_.open(path, B19200)) {
				return false;
			}
			if(!rs232c_.enable_RTS(false)) {
				return false;
			}
			if(!rs232c_.enable_DTR(false)) {
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コネクションの確立（startが成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool connection() {
			bool ok = false;
			for(int i = 0; i < 30; ++i) {
				if(!command_(0x00)) {
					return false;
				}
				timeval tv;
				tv.tv_sec  = 0;
				tv.tv_usec = 10000;  // 10ms
				int ch = rs232c_.recv(tv);
				if(ch == 0x00) {
					ok =  true;
					break;
				}
			}
			if(!ok) return false;

			if(!command_(0x55)) {
				return false;
			}

			timeval tv;
			tv.tv_sec  = 1;
			tv.tv_usec = 0;
			int ch = rs232c_.recv(tv);
			if(ch == 0xff || ch != 0xE6) {
				return false;
			}

			connection_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サポートデバイス問い合わせ（connection が成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_device() {
			if(!connection_) return false;

			if(!command_(0x20)) {
				return false;
			}
			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x30) {
				return false;
			}
			uint32_t total = head[1];

			char tmp[256 + 16];
			if(!read_(tmp, total)) {
				return false;
			}

			device d;
			d.code_ = get32_((const uint8_t*)&tmp[1]);
			tmp[static_cast<uint8_t>(tmp[0]) + 1] = 0;
			d.name_ = &tmp[5];
			devices_.push_back(d);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const devices& get_device() const { return devices_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを選択
			@param[in]	code	デバイス・コード
		*/
		//-----------------------------------------------------------------//
		bool select_device(uint32_t code) {
			if(!connection_) return false;

			uint8_t tmp[7];
			tmp[0] = 0x10;
			tmp[1] = 4;
			tmp[2] = code & 0xff;
			tmp[3] = (code >> 8) & 0xff;
			tmp[4] = (code >> 16) & 0xff;
			tmp[5] = (code >> 24) & 0xff;
			tmp[6] = sum_(tmp, 6);
			if(!write_(tmp, 7)) {
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] == 0x06) {
				return true;
			} else if(res[0] == 0x90) {
				read_(res, 1);
				last_error_ = res[0];
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	クロック・モード問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_clock_mode() {
			if(!connection_) return false;

			if(!command_(0x21)) {
				return false;
			}

			uint8_t head[2];
			if(!read_(head, 2)) {
				return false;
			}
			if(head[0] != 0x31) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1] + 1)) {
				return false;
			}
			for(int i = 0; i < static_cast<int>(head[1]); ++i) {
				clock_mode cm;
				cm.type_ = tmp[i];
				clock_modes_.push_back(cm);
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const clock_modes& get_clock_mode() const { return clock_modes_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	クロック・モードを選択
			@param[in]	cm	クロック・モード
		*/
		//-----------------------------------------------------------------//
		bool select_clock_mode(const clock_mode& cm) {
			if(!connection_) return false;

			uint8_t tmp[4];
			tmp[0] = 0x11;
			tmp[1] = 1;
			tmp[2] = cm.type_;
			tmp[3] = sum_(tmp, 3);
			if(!write_(tmp, 4)) {
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] == 0x06) {
				return true;
			} else if(res[0] == 0x91) {
				read_(res, 1);
				last_error_ = res[0];
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	逓倍比問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_multiplier() {
			if(!connection_) return false;

			if(!command_(0x22)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x32) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1])) {
				return false;
			}

			clock_num_ = head[2];
			uint8_t i = 0;
			const uint8_t* p = tmp;
			while(i < (head[1] - 1)) {
				auto n = *p++;
				multiplier mp;
				mp.list_.resize(n);
				for(int j = 0; j < n; ++j) mp.list_[j] = *p++;
				multipliers_.push_back(mp);
				i += n + 1;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	逓倍比を取得
			@return 逓倍比
		*/
		//-----------------------------------------------------------------//
		const multipliers& get_multiplier() const { return multipliers_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	動作周波数問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_frequency() {
			if(!connection_) return false;

			if(!command_(0x23)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x33) {
				return false;
			}
///			std::cout << "Total: " << (int)head[1] << std::endl;
			uint8_t tmp[256];
			if(!read_(tmp, head[1])) {
				return false;
			}

			auto num = head[2];
			const uint8_t* p = tmp;
			for(uint8_t i = 0; i < num; ++i) {
				frequency q;
				q.min_ = static_cast<uint16_t>(p[1]) | (static_cast<uint16_t>(p[0]) << 8);
				p += 2;
				q.max_ = static_cast<uint16_t>(p[1]) | (static_cast<uint16_t>(p[0]) << 8);
				p += 2;
//				std::cout << (int)q.min_ << std::endl;
//				std::cout << (int)q.max_ << std::endl;
				frequencies_.push_back(q);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	動作周波数を取得
			@return 動作周波数
		*/
		//-----------------------------------------------------------------//
		const frequencies& get_frequency() const { return frequencies_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	新ビットレート選択
			@param[in]	mclock	マスタークロック（MHz単位で、小数点第２位までを１００倍）
			@param[in]	brate	ボーレート
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool change_speed(uint16_t mclock, speed_t brate) {
			if(!connection_) return false;

			uint32_t nbr;
			switch(brate) {
			case B19200:
				nbr = 192;
				baud_rate_ = 19200;
				break;
			case B38400:
				nbr = 384;
				baud_rate_ = 38400;
				break;
			case B57600:
				nbr = 576;
				baud_rate_ = 57600;
				break;
			case B115200:
				nbr = 1152;
				baud_rate_ = 115200;
				break;
			default:
				return false;
			}

			uint8_t cmd[10];
			cmd[0] = 0x3f;
			cmd[1] = 7;
			cmd[2] = (nbr >> 8) & 0xff;
			cmd[3] = nbr & 0xff;
			cmd[4] = (mclock >> 8) & 0xff;
			cmd[5] = mclock & 0xff;
			cmd[6] = 0x02;
			cmd[7] = 0x08;  // 96MHz
			cmd[8] = 0x04;  // 48MHz
			cmd[9] = sum_(cmd, 9);
			if(!write_(cmd, 10)) {
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] == 0xbf) {
				read_(res, 1);
				last_error_ = res[0];
				return false;
			} else if(res[0] != 0x06) {
				return false;
			}

			usleep(25000);	// 25[ms]

			if(!rs232c_.change_speed(brate)) {
				return false;
			}

			if(!command_(0x06)) {
				return false;
			}
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] != 0x06) {
				return false;
			}
			return true;
		}


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief	バージョン情報の取得
			@return バージョンを返す（エラーならempty）
		*/
		//-----------------------------------------------------------------//
		std::string get_version() {
			if(!connection_) return std::string();

			if(!command_(0xFB)) {
				return std::string();
			}
			char buff[9];
			if(!read_(buff, 8)) {
				return std::string();
			}
			buff[8] = 0;
			return std::string(buff);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータス情報の取得
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool get_status(status& st) {
			if(!connection_) return false;

			if(!command_(0x70)) {
				return false;
			}

			char buff[2];
			if(!read_(buff, 2)) {
				return false;
			}

			st.SRD  = buff[0];
			st.SRD1 = buff[1];

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータス情報のクリア
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool clear_status() {
			if(!connection_) return false;

			if(!command_(0x50)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ID 検査
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool id_inspection(const id_t& t) {
			if(!connection_) return false;

			uint8_t buff[12];
			buff[0] = 0xF5;
			buff[1] = 0xDF;
			buff[2] = 0xFF;
			buff[3] = 0x00;
			buff[4] = 0x07;
			for(int i = 0; i < 7; ++i) buff[5 + i] = t.buff[i];
			if(rs232c_.send(buff, 12) != 12) {
				return false;
			}
			rs232c_.sync_send();

			status st;
			if(!get_status(st)) {
				return false;
			}
			if(st.get_id_state() != 3) {
				return false;
			}

			verification_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リード・ページ
			@param[in]	address	アドレス
			@param[out]	dst	リード・データ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool read_page(uint32_t address, uint8_t* dst) {
			if(!connection_) return false;
			if(!verification_) return false;

			uint8_t buff[3];
			buff[0] = 0xFF;
			buff[1] = (address >> 8) & 0xff;
			buff[2] = (address >> 16) & 0xff;
			if(rs232c_.send(buff, 3) != 3) {
				return false;
			}
			rs232c_.sync_send();

			// ボーレートから想定される実時間の２倍
			// 1.0f / static_cast<float>(baud_rate) * 10.0f * 256.0f / 1e-6 * 2.0f;
			return read_(dst, 256);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ライト・ページ
			@param[in]	address	アドレス
			@param[in]	src	ライト・データ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool write_page(uint32_t address, const uint8_t* src) {
			if(!connection_) return false;
			if(!verification_) return false;

			char buff[3];
			buff[0] = 0x41;
			buff[1] = (address >> 8) & 0xff;
			buff[2] = (address >> 16) & 0xff;
			if(rs232c_.send(buff, 3) != 3) {
				return false;
			}
			rs232c_.sync_send();

			if(rs232c_.send(src, 256) != 256) {
				return false;
			}
			rs232c_.sync_send();

			status st;
			if(!get_status(st)) {
				return false;
			}
			if(st.get_SR4() != 0) {
				return false;
			}

			return clear_status();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	イレース・ページ
			@param[in]	address	アドレス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool erase_page(uint32_t address) {
			if(!connection_) return false;
			if(!verification_) return false;

			char buff[4];
			buff[0] = 0x20;
			buff[1] = (address >> 8) & 0xff;
			buff[2] = (address >> 16) & 0xff;
			buff[3] = 0xD0;
			if(rs232c_.send(buff, 4) != 4) {
				return false;
			}
			rs232c_.sync_send();

			status st;
			if(!get_status(st)) {
				return false;
			}
			if(st.get_SR5() != 0) {
				return false;
			}

			return clear_status();
		}

#endif
		//-----------------------------------------------------------------//
		/*!
			@brief	終了
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool end() {
			connection_ = false;
///			verification_ = false;
			return rs232c_.close();
		}

	};

}
