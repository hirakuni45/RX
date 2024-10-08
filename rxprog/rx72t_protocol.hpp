#pragma once
//=========================================================================//
/*!	@file
	@brief	RX72T プログラミング・プロトコル・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "protocol_base.hpp"
#include <boost/format.hpp>

namespace rx72t {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RX72T プログラミング・プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class protocol : public rx::protocol_base {

		bool				verbose_ = false;

		rx::protocol::device_type	device_type_;

		uint32_t			system_clock_ = 0;
		uint32_t			device_clock_ = 0;

		uint32_t	   		baud_speed_ = 0;
		speed_t				baud_rate_ = B9600;

		bool				enable_id_ = false;

		bool				pe_turn_on_ = false;
		bool				data_area_ = false;
		bool				select_write_area_ = false;


		bool com_(uint8_t soh, uint8_t cmd, uint8_t ext, const uint8_t* src = nullptr, uint32_t len = 0) noexcept
		{
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


		bool command_(uint8_t cmd, const uint8_t* src = nullptr, uint32_t len = 0) noexcept
		{
			return com_(0x01, cmd, 0x03, src, len);
		}


		bool status_sub_(uint8_t* dst) noexcept
		{
			if(!read_(dst, 4)) {
				return false;
			}
			if(dst[0] != 0x81) {
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


		void dump_status_() noexcept
		{
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


		bool status_(uint8_t res) noexcept
		{
			uint8_t tmp[4 + 1 + 1 + 1];

			if(!status_sub_(tmp)) {
				return false;
			}

			return tmp[3] == res;
		}


		bool response_(uint8_t& res, uint8_t& err) noexcept
		{
			uint8_t tmp[4 + 1 + 1 + 1];

			if(!status_sub_(tmp)) {
				return false;
			}
			res = tmp[3];
			err = tmp[4];
			return true;
		}


		bool status_back_(uint8_t res) noexcept
		{
			uint8_t tmp[4 + 1 + 1 + 1];

			if(!status_sub_(tmp)) {
				return false;
			}

			if(tmp[3] != res) {
				return false;
			}

			if(!write_(tmp, sizeof(tmp))) {
				return false;
			}
			return true;
		}


		bool status_data_(uint8_t res, uint8_t* dst, uint32_t len) noexcept
		{
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


		std::string out_section_(uint32_t n, uint32_t num) const noexcept
		{
			return (boost::format("#%02d/%02d: ") % n % num).str();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		protocol() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	接続
			@param[in]	path	シリアルデバイスパス
			@param[in]	brate	ボーレート
			@param[in]	rx		CPU 設定
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool bind(const std::string& path, uint32_t brate, const rx::protocol::rx_t& rx) noexcept
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
			@brief	コネクションの確立（startが成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool connection() noexcept
		{
			return rx::protocol_base::connection(0xC1);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイス種別取得（connection が成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_device_type() noexcept
		{
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
		const rx::protocol::device_type& get_device_type() const noexcept { return device_type_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	エンディアン通知コマンド
			@param[in]	endian ０ならビッグ、１ならリトル
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_endian(uint8_t endian) noexcept
		{

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
		bool select_frequency() noexcept
		{

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
		bool change_speed(const rx::protocol::rx_t& rx, uint32_t speed) noexcept
		{
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
			case 230400:
				baud_rate_ = B230400;
				break;
#ifdef WIN32
			case 460800:
				baud_rate_ = B460800;
				break;
			case 500000:
				baud_rate_ = B500000;
				break;
			case 576000:
				baud_rate_ = B576000;
				break;
#endif
			default:
				return false;
			}
			baud_speed_ = speed; 

			uint8_t tmp[4];
			put32_big_(&tmp[0], speed);
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
		bool inquiry_id() noexcept
		{

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
			@brief	ページサイズを取得
			@return ページサイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_page_size() const noexcept { return 256; }


		//-----------------------------------------------------------------//
		/*!
			@brief	イレース・ページ
			@param[in]	address	アドレス
			@return イレース・ステートを返す
		*/
		//-----------------------------------------------------------------//
		rx::protocol::erase_state erase_page(uint32_t address) noexcept
		{
			if(!connection_) return rx::protocol::erase_state::ERROR;
			if(!pe_turn_on_) return rx::protocol::erase_state::ERROR;

			// ブランク・チェックを行う
			uint8_t tmp[8];
			auto org = address & 0xffffff00;
			put32_big_(&tmp[0], org);
			put32_big_(&tmp[4], org + 255);
			if(!command_(0x10, tmp, sizeof(tmp))) {
				return rx::protocol::erase_state::ERROR;
			}
			uint8_t res;
			uint8_t err;
			if(!response_(res, err)) {
				return rx::protocol::erase_state::ERROR;
			}
			if(res == 0x10) return rx::protocol::erase_state::CHECK_OK;
			else if(res != 0x90) {
				return rx::protocol::erase_state::ERROR;
			} else {
				if(err != 0xe0) { // do erase
					return rx::protocol::erase_state::ERROR;
				}
				// erase NG;
				// std::cout << boost::format("Erase NG: %08X") % address << std::endl;
				if(address >= 0xFFFF0000) {  // 8K block
					org = address & 0xFFFFE000;
				} else if(address >= 0xFFC00000) {  // 32K block
					org = address & 0xFFFF8000;
				}
				put32_big_(&tmp[0], org);
				if(!command_(0x12, tmp, 4)) {  // erase command
					return rx::protocol::erase_state::ERROR;
				}
				if(!response_(res, err)) {
					return rx::protocol::erase_state::ERROR;
				}
				if(res == 0x12) ;
				else if(res == 0x92) {
					std::cout << boost::format("Erase response: %02X") % static_cast<uint32_t>(err)
						<< std::endl;
					return rx::protocol::erase_state::ERROR;
				} else {
					return rx::protocol::erase_state::ERROR;
				}
				return rx::protocol::erase_state::ERASE_OK;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー・ブート／データ領域書き込み選択
			@param[in]	data	※常に、ユーザ／データ領域
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_write_area(bool data) noexcept
		{
			if(!connection_) return false;
			if(!pe_turn_on_) return false;

			data_area_ = data;
			select_write_area_ = true;

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
		bool write_page(uint32_t address, const uint8_t* src) noexcept
		{
			if(!connection_) return false;
			if(!pe_turn_on_) return false;
			if(!select_write_area_) return false;

			// final method to pass...
			if(address == 0xFFFFFFFF || src == nullptr) {
				return true;
			}

			uint8_t tmp[8];
			put32_big_(&tmp[0], address);
			put32_big_(&tmp[4], address + 255);
			if(!command_(0x13, tmp, sizeof(tmp))) {
				return false;
			}

			if(!status_(0x13)) {
				return false;
			}

			if(!com_(0x81, 0x13, 0x03, src, 256)) {
				return false;
			}

			uint8_t res;
			uint8_t err;
			if(!response_(res, err)) {
				return false;
			}
			if(res == 0x13) {  // write OK
				return true;
			} else if(res == 0x93) { // write error
				std::cerr << std::endl;
				std::cerr << boost::format("Write error (%08X), status: %02X")
					% address % static_cast<uint32_t>(err) << std::endl;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リード・ページ（２５６バイト）
			@param[in]	adr	アドレス
			@param[out]	dst	リード・データ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool read_page(uint32_t adr, uint8_t* dst) noexcept
		{
			if(!connection_) return false;
			if(!pe_turn_on_) return false;

			uint8_t tmp[8];
			put32_big_(&tmp[0], adr);
			put32_big_(&tmp[4], adr + 255);
			if(!command_(0x15, tmp, sizeof(tmp))) {
				return false;
			}

			if(!status_(0x15)) {
				return false;
			}

			if(!com_(0x81, 0x15, 0x03)) {
				return false;
			}
			if(!status_data_(0x15, dst, 256)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	終了
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool end() noexcept
		{
			connection_ = false;
			pe_turn_on_ = false;
			select_write_area_ = false;
			return rs232c_.close();
		}
	};

}
