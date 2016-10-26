#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M プログラミング・プロトコル・クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "rs232c_io.hpp"
#include "rx_protocol.hpp"
#include <vector>
#include <boost/format.hpp>

namespace rx64m {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RX64M プログラミング・プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class protocol {

		utils::rs232c_io	rs232c_;

		bool				verbose_ = false;

		bool				connection_ = false;

		rx::protocol::device_type	device_type_;

		uint32_t			system_clock_ = 0;
		uint32_t			device_clock_ = 0;

		uint32_t	   		baud_speed_ = 0;
		speed_t				baud_rate_ = B9600;

		bool				enable_id_ = false;

		bool				pe_turn_on_ = false;
		bool				select_write_area_ = false;

		uint8_t				last_error_ = 0;

		static uint32_t get32_(const uint8_t* p) {
			uint32_t v;
			v = p[0];
			v |= static_cast<uint32_t>(p[1]) << 8;
			v |= static_cast<uint32_t>(p[2]) << 16;
			v |= static_cast<uint32_t>(p[3]) << 24;
			return v;
		}

		static uint32_t get16_big_(const uint8_t* p) {
			uint32_t v;
			v = p[1];
			v |= static_cast<uint32_t>(p[0]) << 8;
			return v;
		}

		static void put16_big_(uint8_t* p, uint32_t val) {
			p[0] = (val >> 8) & 0xff;
			p[1] = val & 0xff;
		}

		static uint32_t get32_big_(const uint8_t* p) {
			uint32_t v;
			v = p[3];
			v |= static_cast<uint32_t>(p[2]) << 8;
			v |= static_cast<uint32_t>(p[1]) << 16;
			v |= static_cast<uint32_t>(p[0]) << 24;
			return v;
		}

		static void put32_big_(uint8_t* p, uint32_t val) {
			p[0] = (val >> 24) & 0xff;
			p[1] = (val >> 16) & 0xff;
			p[2] = (val >> 8) & 0xff;
			p[3] =  val & 0xff;
		}

		static uint8_t sum_(const uint8_t* buff, uint32_t len) {
			uint16_t sum = 0;
			for(uint32_t i = 0; i < len; ++i) {
				sum += *buff++;
			}
			return (0 - sum) & 0xff;
		}

		bool read_(void* buff, uint32_t len, const timeval& tv) {
			return rs232c_.recv(buff, len, tv) == len;
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

		bool com_(uint8_t soh, uint8_t cmd, uint8_t ext, const uint8_t* src = nullptr, uint32_t len = 0) {
			uint8_t tmp[1 + 2 + 1 + len + 1 + 1];
			tmp[0] = soh;
			put16_big_(&tmp[1], 1 + len);
			tmp[3] = cmd;
			if(len > 0) {
				std::memcpy(&tmp[4], src, len);
			}
			tmp[4 + len] = sum_(&tmp[1], 3 + len);
			tmp[4 + len + 1] = ext;
			uint32_t l = rs232c_.send(tmp, sizeof(tmp));
			rs232c_.sync_send();
			return l == sizeof(tmp);
		}


		bool command_(uint8_t cmd, const uint8_t* src = nullptr, uint32_t len = 0) {
			return com_(0x01, cmd, 0x03, src, len);
		}


		bool status_sub_(uint8_t res, uint8_t* dst) {
			if(!read_(dst, 4)) {
				return false;
			}
			if(dst[0] != 0x81) {
				return false;
			}
			if(dst[3] != res) {
				return false;
			}
			auto l = get16_big_(&dst[1]);
			if(l == 1 || l == 2) ;
			else {
				return false;
			}
			--l;
			if(!read_(&dst[4], l + 2)) {
				return false;
			}
			auto sum = sum_(&dst[1], 3 + l);
			if(sum != dst[4 + l]) {
				return false;
			}
			if(dst[4 + l + 1] != 0x03) {
				return false;
			}
			return true;
		}


		void dump_status_() {
			uint8_t tmp[4 + 1024 + 2];
			if(!read_(tmp, 4)) {
				return;
			}
			auto l = get16_big_(&tmp[1]);
			if(!read_(&tmp[4], l + 1)) {
				return;
			}

			std::cout << boost::format("SOD: %02X") % static_cast<uint32_t>(tmp[0]) << std::endl;
			std::cout << boost::format("LEN: %d") % l << std::endl;
			std::cout << boost::format("RES: %02X") % static_cast<uint32_t>(tmp[3]) << std::endl;
			--l;
			if(l > 0) std::cout << "Dat: ";
			for(uint32_t i = 0; i < l; ++i) {
				boost::format(" %02X,") % static_cast<uint32_t>(tmp[4 + i]);
			}
			if(l > 0) std::cout << std::endl;
			std::cout << boost::format("SUM: %02X") % static_cast<uint32_t>(tmp[4 + l]) << std::endl;
			std::cout << boost::format("EXT: %02X") % static_cast<uint32_t>(tmp[4 + l + 1]) << std::endl;
		}


		bool status_(uint8_t res) {
			uint8_t tmp[4 + 1 + 1];

			if(!status_sub_(res, tmp)) {
				return false;
			}
			return true;
		}


		bool status_back_(uint8_t res) {
			uint8_t tmp[4 + 1 + 1];

			if(!status_sub_(res, tmp)) {
				return false;
			}

			if(!write_(tmp, sizeof(tmp))) {
				return false;
			}			
			return true;
		}


		bool status_data_(uint8_t res, uint8_t* dst, uint32_t len) {
			uint8_t tmp[4 + len + 2];
			if(!read_(tmp, 4)) {
				return false;
			}
			if(tmp[0] != 0x81) {
				return false;
			}
			if(tmp[3] != res) {
				return false;
			}
			auto l = get16_big_(&tmp[1]);
			if(l != (len + 1)) {
				return false;
			}
			if(!read_(&tmp[4], len + 2)) {
				return false;
			}
			auto sum = sum_(&tmp[1], len + 3);
			if(sum != tmp[4 + len]) {
				return false;
			}
			if(len > 0) {
				std::memcpy(dst, &tmp[4], len);
			}
			return true;
		}

		std::string out_section_(uint32_t n, uint32_t num) const {
			return (boost::format("#%02d/%02d: ") % n % num).str();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		protocol() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	接続
			@param[in]	path	シリアルデバイスパス
			@param[in]	brate	ボーレート
			@param[in]	rx		CPU 設定
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool bind(const std::string& path, uint32_t brate, const rx::protocol::rx_t& rx)
		{
			verbose_ = rx.verbose_;

			if(!start(path)) {
				std::cerr << "Can't open path: '" << path << "'" << std::endl;
				return false;
			}

			// コネクション
			if(!connection()) {
				std::cerr << "Can't connection." << std::endl;
				return false;
			}
			if(verbose_) {
				std::cout << "# Connection OK." << std::endl;
			}

			// デバイスタイプ取得
			{
				if(!inquiry_device_type()) {
					std::cerr << "Inquiry device type error." << std::endl;
					return false;
				}
				auto a = get_device_type();
				if(verbose_) {
					a.info(out_section_(1, 1));
				}
			}

			// エンディアン通知コマンド
			{
				uint8_t endian = 0x01;
				if(!select_endian(endian)) {
					std::cerr << "Select endian error." << std::endl;
				}
				if(verbose_) {
					std::cout << out_section_(1, 1) << "Endian is "
						<< (endian != 0 ? "little." : "big.") << std::endl;
				}
			}

			// 周波数設定コマンド
			{
				if(!select_frequency()) {
					std::cerr << "Select frequency error." << std::endl;
				}
				if(verbose_) {
					auto s = out_section_(1, 1);
					std::cout << s << boost::format("System clock: %d") % system_clock_ << std::endl; 
					std::cout << s << boost::format("Device clock: %d") % device_clock_ << std::endl; 
				}
			}

			// ボーレート変更
			{
				if(!change_speed(rx, brate)) {
					std::cerr << "Can't change speed." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect << boost::format("Change baud rate: %d") % brate << std::endl;
				}
			}

			// ID 認証確認
			{
				if(!inquiry_id()) {
					std::cerr << "Inquiry ID error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect
						<< boost::format("ID: %s") % (enable_id_ ? "Enable" : "Disable") << std::endl;
				}
			}

			// ID 認証が有効なら、ID コードチェックを行う
			if(enable_id_) {
			}

			pe_turn_on_ = true;			

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	path	シリアルデバイスパス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(const std::string& path) {
			if(!rs232c_.open(path, B9600)) {
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
				if(!rs232c_.send(0x00)) {
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

			if(!rs232c_.send(0x55)) {
				return false;
			}

			timeval tv;
			tv.tv_sec  = 1;
			tv.tv_usec = 0;
			int ch = rs232c_.recv(tv);
			if(ch == 0xC1) {
				connection_ = true;
				return true;
			}

			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイス種別取得（connection が成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_device_type() {
			if(!connection_) return false;

			if(!command_(0x38)) {
				return false;
			}

			if(!status_back_(0x38)) {
				return false;
			}

			uint8_t tmp[24];
			if(!status_data_(0x38, tmp, sizeof(tmp))) {
				return false;
			}

			std::memcpy(device_type_.TYP, &tmp[0], 8);
			device_type_.OSA = get32_big_(&tmp[8]);
			device_type_.OSI = get32_big_(&tmp[8 + 4]);
			device_type_.CPA = get32_big_(&tmp[8 + 4 + 4]);
			device_type_.CPI = get32_big_(&tmp[8 + 4 + 4 + 4]);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイス種別を取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::device_type& get_device_type() const { return device_type_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	エンディアン通知コマンド
			@param[in]	endian ０ならビッグ、１ならリトル
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_endian(uint8_t endian) {

			if(!connection_) return false;

			uint8_t tmp[1];
			tmp[0] = endian;
			if(!command_(0x36, tmp, 1)) {
				return false;
			}

			if(!status_(0x36)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	周波数設定コマンド
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_frequency() {

			if(!connection_) return false;

			uint8_t tmp[8];
			put32_big_(&tmp[0],  16000000);
			put32_big_(&tmp[4], 120000000);
			if(!command_(0x32, tmp, sizeof(tmp))) {
				return false;
			}

			if(!status_back_(0x32)) {
				return false;
			}

			if(!status_data_(0x32, tmp, sizeof(tmp))) {
				return false;
			}

			system_clock_ = get32_big_(&tmp[0]);
			device_clock_ = get32_big_(&tmp[4]);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	新ビットレート選択
			@param[in]	rx		マイコン設定
			@param[in]	spped	シリアル速度
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool change_speed(const rx::protocol::rx_t& rx, uint32_t speed) {
			if(!connection_) return false;

			switch(speed) {
			case 19200:
				baud_rate_ = B19200;
				break;
			case 38400:
				baud_rate_ = B38400;
				break;
			case 57600:
				baud_rate_ = B57600;
				break;
			case 115200:
				baud_rate_ = B115200;
				break;
			default:
				return false;
			}
			baud_speed_ = speed; 

			uint8_t tmp[4];
			put32_big_(&tmp[0],  speed);
			if(!command_(0x34, tmp, sizeof(tmp))) {
				return false;
			}

			if(!status_(0x34)) {
				return false;
			}

			usleep(1000);	// 1[ms]

			if(!rs232c_.change_speed(baud_rate_)) {
				return false;
			}

			// 同期コマンド
			if(!command_(0x00)) {
				return false;
			}
			if(!status_(0x00)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ID 認証モード取得コマンド
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_id() {

			if(!connection_) return false;

			if(!command_(0x2C)) {
				return false;
			}

			if(!status_back_(0x2C)) {
				return false;
			}

			uint8_t tmp[1];
			if(!status_data_(0x2C, tmp, sizeof(tmp))) {
				return false;
			}

			if(tmp[0] == 0x00) enable_id_ = true;
			else if(tmp[0] == 0xFF) enable_id_ = false;
			else {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	イレース・ページ
			@param[in]	address	アドレス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool erase_page(uint32_t address) {
			return true;
		}







		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー・ブート／データ領域書き込み選択
			@param[in]	data	※常に、ユーザ／データ領域
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_write_area(bool data) {
			if(!connection_) return false;
			if(!pe_turn_on_) return false;

#if 0
			// ユーザ／データ領域プログラム準備
			if(!command_(0x43)) {
				return false;
			}

			timeval tv;
			tv.tv_sec  = 1;
			tv.tv_usec = 0;
			uint8_t head[1];
			if(!read_(head, 1, tv)) {
				return false;
			}
			if(head[0] != 0x06) {
				return false;
			}

			select_write_area_ = true;
#endif
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ライト・ページ（２５６バイト）
			@param[in]	address	アドレス
			@param[in]	src	ライト・データ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool write_page(uint32_t address, const uint8_t* src) {
			if(!connection_) return false;
			if(!pe_turn_on_) return false;
			if(!select_write_area_) return false;
#if 0
			uint8_t cmd[5 + 256 + 1];
			cmd[0] = 0x50;
///			std::cout << boost::format("Address: %08X") % address << std::endl;			
			if(address != 0xffffffff) {
				put32_big_(&cmd[1], address);
				std::memcpy(&cmd[5], src, 256);
				cmd[5 + 256] = sum_(cmd, 5 + 256);

				if(!write_(cmd, 5)) {
					select_write_area_ = false;
					return false;
				}
				for(uint32_t i = 0; i < 16; ++i) {
					if(!write_(&cmd[5 + i * 16], 16)) {
						select_write_area_ = false;
						return false;
					}
				}
				if(!write_(&cmd[5 + 256], 1)) {  // SUM
				  	select_write_area_ = false;
					return false;
				}
			} else {
				put32_big_(&cmd[1], address);
				select_write_area_ = false;
				cmd[5] = sum_(cmd, 5);
				if(!write_(cmd, 6)) {
					return false;
				}
			}

			// レスポンス
			timeval tv;
			tv.tv_sec  = 10;
			tv.tv_usec = 0;
			uint8_t head[1];
			if(!read_(head, 1, tv)) {
				select_write_area_ = false;
				return false;
			}
			if(head[0] != 0x06) {
				std::cout << "Respons error" << std::endl;
				select_write_area_ = false;
				if(head[0] != 0xd0) {
					return false;
				}
				if(!read_(head, 1, tv)) {
					return false;
				}
				last_error_ = head[0];
///				std::cout << boost::format("Write error code: %02X") % static_cast<uint32_t>(head[0]) << std::endl;
				return false;
			}
#endif
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リード・ページ
			@param[in]	adr	アドレス
			@param[out]	dst	リード・データ
			@param[in]	len	読み出しサイズ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool read(uint32_t adr, uint8_t* dst, uint32_t len) {
			if(!connection_) return false;
			if(!pe_turn_on_) return false;
#if 0
			uint8_t cmd[12];
			cmd[0] = 0x52;
			cmd[1] = 9;
			cmd[2] = 0x01;  // user-area, data-area
			put32_big_(&cmd[3], adr);
			put32_big_(&cmd[7], len);
			cmd[11] = sum_(cmd, 11);
			if(!write_(cmd, 12)) {
				return false;
			}

			{
				timeval tv;
				tv.tv_sec  = 10;
				tv.tv_usec = 0;
				uint8_t head[5];
				if(!read_(head, 5, tv)) {
					return false;
				}
				if(head[0] != 0x52) {
					return false;
				}
				auto rs = get32_big_(&head[1]);
				/// std::cout << "Read size: " << rs << std::endl;
				tv.tv_sec  = 20;
				tv.tv_usec = 0;
				if(!read_(dst, rs, tv)) {
//					std::cout << "Read error #0" << std::endl;
					return false;
				}
			}
			{
				timeval tv;
				tv.tv_sec  = 10;
				tv.tv_usec = 0;
				uint8_t sum[1];
				if(!read_(sum, 1, tv)) {
//					std::cout << "Read error #1" << std::endl;
					return false;
				}
			}
#endif
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	終了
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool end() {
			connection_ = false;
			pe_turn_on_ = false;
			select_write_area_ = false;
			return rs232c_.close();
		}

	};

}
