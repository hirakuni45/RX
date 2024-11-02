#pragma once
//=========================================================================//
/*!	@file
	@brief	RX65N/RX651 プログラミング・プロトコル・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "protocol_base.hpp"
#include <boost/format.hpp>
#include <set>

namespace rx65x {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RX651/RX65N プログラミング・プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class protocol : public rx::protocol_base {

		static constexpr uint8_t CONNECTION_ID = 0xC2;

		bool	data_area_;
		bool	select_write_area_;

		typedef std::set<uint32_t> ERASE_SET;
		ERASE_SET				erase_set_;

		static auto erase_page_block_(uint32_t org) noexcept
		{
			if(org >= 0xFFFF'0000) {  // 8K block
				org &= 0xFFFF'E000;
			} else {  // 32K block
				org &= 0xFFFF'8000;
			}
			return org;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		protocol() noexcept :
			data_area_(false), select_write_area_(false), erase_set_()
		{ }


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
			return rx::protocol_base::bind_RX6xx(path, brate, CONNECTION_ID, rx);
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

			if(erase_set_.find(erase_page_block_(address)) != erase_set_.end()) {
				return rx::protocol::erase_state::CHECK_OK;
			}

			// ブランク・チェックを行う
			uint8_t tmp[8];
			auto org = address & 0xffff'ff00;
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

				org = erase_page_block_(org);
				if(erase_set_.find(org) != erase_set_.end()) {
					return rx::protocol::erase_state::CHECK_OK;
				} else {
					erase_set_.insert(org);
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
			if(address == 0xFFFF'FFFF || src == nullptr) {
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
