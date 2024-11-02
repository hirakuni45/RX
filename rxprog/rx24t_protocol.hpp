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
#include <set>

namespace rx24t {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RX24T プログラミング・プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class protocol : public rx::protocol_base {

		static constexpr uint32_t LIMIT_BAUDRATE = 230400;
		static constexpr uint8_t SEL_DEV_RES = 0x46;

		uint8_t					data_;
		rx::protocol::areas		data_areas_;
		rx::protocol::blocks	blocks_;
		bool					id_protect_;
		bool					pe_turn_on_;
		bool					blank_check_;
		bool					blank_all_;
		bool					erase_select_;
		bool					select_write_area_;

		typedef std::set<uint32_t> ERASE_SET;
		ERASE_SET				erase_set_;

		static auto erase_page_block_(uint32_t org) noexcept
		{
			return org & 0xffff'f800; // erase block (2K)
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		protocol() noexcept :
			data_(0), data_areas_(), blocks_(),
			id_protect_(false), pe_turn_on_(false), blank_check_(false),
			blank_all_(false), erase_select_(false), select_write_area_(false),
			erase_set_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	コネクションの確立（startが成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool connection() noexcept
		{
			return rx::protocol_base::connection(0xE6);
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
			return rx::protocol_base::change_speed_legacy(rx, speed, LIMIT_BAUDRATE);
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

			if(!command1_(0x26)) {
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
			@brief	ブロック情報を取得
			@return ブロック情報
		*/
		//-----------------------------------------------------------------//
		const auto& get_block() const noexcept { return blocks_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域有無問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_data() noexcept
		{
			if(!connection_) return false;

			if(!command1_(0x2A)) {
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
			@brief	データ量域有無取得
			@return データ量域有無（通常、０ｘ１Ｄ）
		*/
		//-----------------------------------------------------------------//
		uint8_t get_data() const noexcept { return data_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域情報問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_data_area() noexcept
		{
			if(!connection_) return false;

			if(!command1_(0x2B)) {
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
			@brief	データ量域情報を取得
			@return データ量域情報
		*/
		//-----------------------------------------------------------------//
		const auto& get_data_area() const noexcept { return data_areas_; }


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
				if(!select_device(as[0].code_, SEL_DEV_RES)) {
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
			@brief	P/E ステータス遷移
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool turn_pe_status() noexcept
		{
			if(!connection_) return false;

			if(!command1_(0x40)) {
				return false;
			}

			uint8_t head[1];
			if(!read_(head, 1)) {
				return false;
			}
			if(head[0] == 0x26) {
				id_protect_ = false;
///				std::cout << "Return: 0x26" << std::endl;
			} else if(head[0] == 0x16) {
				id_protect_ = true;
///				std::cout << "Return: 0x16" << std::endl;
			} else if(head[0] == 0xC0) {
				if(!read_(head, 1)) {
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

			if(!blank_check_) {  // ブランク・チェック
				switch(user_blank_check()) {
				case BLANK_STATE::ERROR:
					return rx::protocol::erase_state::ERROR;
				case BLANK_STATE::BLANK_OK:
					blank_all_ = true;
					break;
				case BLANK_STATE::BLANK_NG:
					blank_all_ = false;
					break;
				}
				blank_check_ = true;
			}
			if(blank_all_) {
				return rx::protocol::erase_state::CHECK_OK;
			}

			if(!erase_select_) {  // 消去選択
				if(!enable_erase_select(RX_GROUP::RX2xx)) {
					return rx::protocol::erase_state::ERROR;
				}
				erase_select_ = true;
			}

			// ブロック消去コマンド発行
			auto org = erase_page_block_(address);
			if(erase_set_.find(org) != erase_set_.end()) {
				return rx::protocol::erase_state::CHECK_OK;
			} else {
				erase_set_.insert(org);
			}
			uint8_t cmd[7];
			cmd[0] = 0x59;
			cmd[1] = 0x04;  // size 固定値 4
			put32_big_(&cmd[2], org);
			cmd[6] = sum_(cmd, 6);
			if(!write_(cmd, 7)) {
				return rx::protocol::erase_state::ERROR;
			}
//		std::cout << std::endl << boost::format("Erase org: %08X") % org << std::endl;

			{
				uint8_t tmp[1];
				if(!read_(tmp, 1)) {  // レスポンス
					return rx::protocol::erase_state::ERROR;
				}
				if(tmp[0] == 0xD9) {
					if(!read_(tmp, 1)) {  // エラーコード
						return rx::protocol::erase_state::ERROR;
					}
					// 0x11: サムチェックエラー
					// 0x29: ブロック番号エラー
					// 0x51: 消去エラーが発生
					last_error_ = tmp[0];  // エラーコード
					return rx::protocol::erase_state::ERROR;
				} else if(tmp[0] != 0x06) {
					return rx::protocol::erase_state::ERROR;
				}
			}
			return rx::protocol::erase_state::ERASE_OK;
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

			if(erase_select_) {  // erase-select を解除
				if(!enable_erase_select(RX_GROUP::RX2xx, false)) {
					return false;
				}
				erase_select_ = false;
			}

			// ユーザ／データ領域プログラム準備
			if(!command1_(0x43)) {
				return false;
			}
			uint8_t head[1];
			if(!read_(head, 1)) {
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
			if(address != 0xffff'ffff) {
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
			uint8_t head[1];
			if(!read_(head, 1)) {
				select_write_area_ = false;
				return false;
			}
			if(head[0] != 0x06) {
				std::cout << "Respons error" << std::endl;
				select_write_area_ = false;
				if(head[0] != 0xd0) {
					return false;
				}
				if(!read_(head, 1)) {
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
				uint8_t head[5];
				if(!read_(head, 5)) {
					return false;
				}
				if(head[0] != 0x52) {
					return false;
				}
				auto rs = get32_big_(&head[1]);
				/// std::cout << "Read size: " << rs << std::endl;
				if(!read_(dst, rs)) {
//					std::cout << "Read error #0" << std::endl;
					return false;
				}
			}
			{
				uint8_t sum[1];
				if(!read_(sum, 1)) {
//					std::cout << "Read error #1" << std::endl;
					return false;
				}
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
			return  rx::protocol_base::close();
		}
	};
}
