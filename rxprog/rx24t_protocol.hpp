#pragma once
//=========================================================================//
/*!	@file
	@brief	RX24T プログラミング・プロトコル・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "protocol_base.hpp"

namespace rx24t {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RX24T プログラミング・プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class protocol : public rx::protocol_base {

		bool				verbose_ = false;

		bool				connection_ = false;

		rx::protocol::devices		devices_;
		uint8_t						data_ = 0;
		rx::protocol::areas			areas_;
		rx::protocol::areas			data_areas_;
		rx::protocol::blocks		blocks_;
		bool						id_protect_ = false;
		bool						pe_turn_on_ = false;
		bool						select_write_area_ = false;

		uint32_t	   				baud_speed_ = 0;
		speed_t						baud_rate_ = B9600;

		uint8_t						last_error_ = 0;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		protocol() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const auto& get_device() const noexcept { return devices_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー領域を取得
			@return ユーザー領域
		*/
		//-----------------------------------------------------------------//
		const auto& get_area() const noexcept { return areas_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域有無取得
			@return データ量域有無（通常、０ｘ１Ｄ）
		*/
		//-----------------------------------------------------------------//
		uint8_t get_data() const noexcept { return data_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域情報を取得
			@return データ量域情報
		*/
		//-----------------------------------------------------------------//
		const auto& get_data_area() const noexcept { return data_areas_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ブロック情報を取得
			@return ブロック情報
		*/
		//-----------------------------------------------------------------//
		const auto& get_block() const noexcept { return blocks_; }


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

			// サポート・デバイス問い合わせ
			{
				if(!inquiry_device()) {
					std::cerr << "Inquiry device error." << std::endl;
					return false;
				}
				const auto& dv = get_device();
				if(verbose_) {
					int i = 0;
					for(auto t : dv) {
						++i;
						t.info(out_section_(i, dv.size()));
					}
				}
			}

			// データ量域の有無問い合わせ
			{
				if(!inquiry_data()) {
					std::cerr << "Inquiry data error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect << "Data area: ";
					std::cout << boost::format("%02X") % static_cast<uint32_t>(data_) << std::endl;
				}
			}

			// ユーザー領域問い合わせ
			{
				if(!inquiry_area()) {
					std::cerr << "Inquiry area error." << std::endl;
					return false;
				}
				if(verbose_) {
					const auto& as = get_area();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()) + "User ");
					}				
				}
			}

			// データ量域情報問い合わせ
			{
				if(!inquiry_data_area()) {
					std::cerr << "Inquiry data-area error." << std::endl;
					return false;
				}
				if(verbose_) {
					const auto& as = get_data_area();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()) + "Data ");
					}				
				}
			}

			// ブロック情報問い合わせ
			{
				if(!inquiry_block()) {
					std::cerr << "Inquiry block error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_block();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
			}

			//--- select device

			// デバイス選択
			{
				auto as = get_device();
				if(!select_device(as[0].code_)) {
					std::cerr << "Select device error." << std::endl;
					return false;
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

			// P/E ステータスに移行
			{
				if(!turn_pe_status()) {
					std::cerr << "P/E status error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect << "ID Protect: ";
					if(get_protect()) {
						std::cout << "Enable" << std::endl;
					} else {
						std::cout << "Disable" << std::endl;
					}					
				}
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	path	シリアルデバイスパス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(const std::string& path) noexcept
		{
			return rx::protocol_base::start(path);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コネクションの確立（startが成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool connection() noexcept
		{
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
		bool inquiry_device() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x20)) {
				return false;
			}
			uint8_t tmp[2 + 256 + 16];
			if(!read_(tmp, 2)) {
				return false;
			}
			if(tmp[0] != 0x30) {
				return false;
			}
			uint32_t total = tmp[1] + 1;

			if(!read_(&tmp[2], total)) {
				return false;
			}
			auto sum = sum_(tmp, tmp[1] + 2);
			if(sum != tmp[2 + total - 1]) {
				return false;
			}

			rx::protocol::device d;
			d.code_ = get32_(&tmp[3 + 1]);
			tmp[3 + 1 + tmp[3]] = 0;
			d.name_ = reinterpret_cast<const char*>(&tmp[3 + 1 + 4]);
			devices_.push_back(d);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー領域問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_area() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x25)) {
				return false;
			}

			uint8_t tmp[256];
			if(!read_(tmp, 2)) {
				return false;
			}
			if(tmp[0] != 0x35) {
				return false;
			}
			uint32_t total = tmp[1] + 1;
			if(!read_(&tmp[2], total)) {
				return false;
			}

			auto sum = sum_(tmp, tmp[1] + 2);
			if(sum != tmp[2 + total - 1]) {
				return false;
			}

			auto num = tmp[2];
			const uint8_t* p = &tmp[3];
			for(uint8_t i = 0; i < num; ++i) {
				rx::protocol::area a;
				a.org_ = get32_big_(p);
				p += 4;
				a.end_ = get32_big_(p);
				p += 4;
				areas_.push_back(a);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域有無問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_data() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x2A)) {
				return false;
			}

			uint8_t tmp[4];
			if(!read_(tmp, 4)) {
				return false;
			}
			if(tmp[0] != 0x3A) {
				return false;
			}

			if(sum_(tmp, 3) != tmp[4 - 1]) {
				return false;
			}

			data_ = tmp[2];

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域情報問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_data_area() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x2B)) {
				return false;
			}

			uint8_t tmp[256];
			if(!read_(tmp, 2)) {
				return false;
			}
			if(tmp[0] != 0x3B) {
				return false;
			}
			uint32_t total = tmp[1] + 1;
			if(!read_(&tmp[2], total)) {
				return false;
			}

			auto sum = sum_(tmp, tmp[1] + 2);
			if(sum != tmp[2 + total - 1]) {
				return false;
			}

			auto num = tmp[2];
			const uint8_t* p = &tmp[3];
			for(uint8_t i = 0; i < num; ++i) {
				rx::protocol::area a;
				a.org_ = get32_big_(p);
				p += 4;
				a.end_ = get32_big_(p);
				p += 4;
				data_areas_.push_back(a);			
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ブロック情報問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_block() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x26)) {
				return false;
			}

			uint8_t tmp[256 + 1];
			if(!read_(tmp, 3)) {
				return false;
			}
			if(tmp[0] != 0x36) {
				return false;
			}
			uint32_t total = get16_big_(&tmp[1]) + 1;
			if(!read_(&tmp[3], total)) {
				return false;
			}

			auto sum = sum_(tmp, 3 + total - 1);
			if(sum != tmp[3 + total - 1]) {
				return false;
			}

			const uint8_t* p = &tmp[4];
			for(uint32_t i = 0; i < 2; ++i) {
				rx::protocol::block a;
				a.org_ = get32_big_(p);
				p += 4;
				a.size_ = get32_big_(p);
				p += 4;
				a.num_ = get32_big_(p);
				p += 4;
				blocks_.push_back(a);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを選択
			@param[in]	code	デバイス・コード
		*/
		//-----------------------------------------------------------------//
		bool select_device(uint32_t code) noexcept
		{
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
			if(res[0] == 0x46) {
				return true;
			} else if(res[0] == 0x90) {
				read_(res, 1);
				last_error_ = res[0];
			}
			return false;
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

			uint32_t nbr;
			switch(speed) {
			case 19200:
				nbr = 192;
				baud_rate_ = B19200;
				break;
			case 38400:
				nbr = 384;
				baud_rate_ = B38400;
				break;
			case 57600:
				nbr = 576;
				baud_rate_ = B57600;
				break;
			case 115200:
				nbr = 1152;
				baud_rate_ = B115200;
				break;
			case 230400:
				nbr = 2304;
				baud_rate_ = B230400;
				break;
			default:
				return false;
			}
			baud_speed_ = speed; 

			uint8_t cmd[10];
			cmd[0] = 0x3F;
			cmd[1] = 7;
			put16_big_(&cmd[2], nbr);
			cmd[4] = 0x00;  // dummy
			cmd[5] = 0x00;  // dummy
			cmd[6] = 0x02;
			cmd[7] = 0x01;
			cmd[8] = 0x01;
			cmd[9] = sum_(cmd, 9);
			if(!write_(cmd, 10)) {
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] == 0xBF) {
				read_(res, 1);
				last_error_ = res[0];
				return false;
			} else if(res[0] != 0x06) {
				return false;
			}

			usleep(25000);	// 25[ms]

			if(!rs232c_.change_speed(baud_rate_)) {
				return false;
			}

			if(!command_(0x06)) {  // 通信確認
				return false;
			}
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] != 0x06) {  // 通信確認レスポンス
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	P/E ステータス遷移
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool turn_pe_status() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x40)) {
				return false;
			}

			timeval tv;
			tv.tv_sec  = 5;
			tv.tv_usec = 0;
			uint8_t head[1];
			if(!read_(head, 1, tv)) {
				return false;
			}
			if(head[0] == 0x26) {
				id_protect_ = false;
///				std::cout << "Return: 0x26" << std::endl;
			} else if(head[0] == 0x16) {
				id_protect_ = true;
///				std::cout << "Return: 0x16" << std::endl;
			} else if(head[0] == 0xC0) {
				if(!read_(head, 1, tv)) {
					return false;
				}
				last_error_ = head[0];
				return false;
			}

			pe_turn_on_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	プロテクト状態を取得
			@return プロテクト状態
		*/
		//-----------------------------------------------------------------//
		bool get_protect() const noexcept { return id_protect_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ページサイズを取得
			@return ページサイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_page_size() const { return 256; }


		//-----------------------------------------------------------------//
		/*!
			@brief	イレース・ページ
			@param[in]	address	アドレス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool erase_page(uint32_t address) noexcept
		{
			return true;
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

			return true;
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

			uint8_t cmd[12];
			cmd[0] = 0x52;
			cmd[1] = 9;
			cmd[2] = 0x01;  // user-area, data-area
			put32_big_(&cmd[3], adr);
			put32_big_(&cmd[7], 256);
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
				tv.tv_sec  = 5;
				tv.tv_usec = 0;
				if(!read_(dst, rs, tv)) {
//					std::cout << "Read error #0" << std::endl;
					return false;
				}
			}
			{
				timeval tv;
				tv.tv_sec  = 5;
				tv.tv_usec = 0;
				uint8_t sum[1];
				if(!read_(sum, 1, tv)) {
//					std::cout << "Read error #1" << std::endl;
					return false;
				}
			}
			return true;
		}


#if 0
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
		bool end() noexcept
		{
			connection_ = false;
			pe_turn_on_ = false;
			select_write_area_ = false;
			return  rx::protocol_base::close();
		}
	};
}
