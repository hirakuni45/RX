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
		};

	private:
		utils::rs232c_io	rs232c_;

		bool				connection_ = false;

		device				device_;

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
///					std::cout << "OK: " << i << std::endl;
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

			// サポート・デバイスの取得
			if(!command_(0x20)) {
				return false;
			}

			uint8_t buff[3];
			if(!read_(buff, 3)) {
				return false;
			}
			if(buff[0] != 0x30) {
				return false;
			}
			uint32_t total = buff[1];
///			std::cout << "Total len: " << total << std::endl;
///			uint32_t num = buff[2];
///			std::cout << "device num: " << num << std::endl;

			char tmp[256 + 16];
			if(!read_(tmp, total)) {
				return false;
			}

			device_.code_ = get32_((const uint8_t*)&tmp[1]);
//			std::cout << (boost::format("Code: %08X") % d.code_) << std::endl; 
			tmp[static_cast<uint8_t>(tmp[0]) + 1] = 0;
			device_.name_ = &tmp[5];
//			std::cout << d.name_ << std::endl;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const device& get_device() const { return device_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを選択
			@param[in]	code	デバイス・コード
		*/
		//-----------------------------------------------------------------//
		bool select_device(uint32_t code) {
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
				last_error_ = res[0];
				read_(res, 1);
			}
			return false;
		}


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief	接続速度を変更する
			@param[in]	brate	ボーレート
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool change_speed(speed_t brate) {
			if(!connection_) return false;

			int cmd;
			switch(brate) {
			case B9600:
				cmd = 0xB0;
				baud_rate_ = 9600;
				break;
			case B19200:
				cmd = 0xB1;
				baud_rate_ = 19200;
				break;
			case B38400:
				cmd = 0xB2;
				baud_rate_ = 38400;
				break;
			case B57600:
				cmd = 0xB3;
				baud_rate_ = 57600;
				break;
			case B115200:
				cmd = 0xB4;
				baud_rate_ = 115200;
				break;
			default:
				return false;
			}
			if(!command_(cmd)) {
				return false;
			}
			int ch = rs232c_.recv(tv_);
			if(ch != cmd) {
				return false;
			}

			if(!rs232c_.change_speed(brate)) {
				return false;
			}

			return true;
		}


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
