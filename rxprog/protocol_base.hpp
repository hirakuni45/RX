#pragma once
//=========================================================================//
/*!	@file
	@brief	RX マイコン、プロトコル・ベース・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "rs232c_io.hpp"
#include "rx_protocol.hpp"
#include <vector>
#include <boost/format.hpp>

namespace rx {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	プロトコル・ベース
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct protocol_base {

		utils::rs232c_io	rs232c_;

		bool				connection_;
		uint8_t				last_error_;

		static uint32_t get32_(const uint8_t* p) noexcept
		{
			uint32_t v;
			v  = p[0];
			v |= p[1] << 8;
			v |= p[2] << 16;
			v |= p[3] << 24;
			return v;
		}

		static uint32_t get16_big_(const uint8_t* p) noexcept
		{
			uint32_t v;
			v  = p[1];
			v |= p[0] << 8;
			return v;
		}

		static uint32_t get32_big_(const uint8_t* p) noexcept
		{
			uint32_t v;
			v  = p[3];
			v |= p[2] << 8;
			v |= p[1] << 16;
			v |= p[0] << 24;
			return v;
		}

		static void put16_big_(uint8_t* p, uint32_t val) noexcept
		{
			p[0] = (val >> 8) & 0xff;
			p[1] = val & 0xff;
		}

		static void put32_big_(uint8_t* p, uint32_t val) noexcept
		{
			p[0] = (val >> 24) & 0xff;
			p[1] = (val >> 16) & 0xff;
			p[2] = (val >> 8) & 0xff;
			p[3] =  val & 0xff;
		}

		static uint8_t sum_(const uint8_t* buff, uint32_t len) noexcept
		{
			uint16_t sum = 0;
			for(uint32_t i = 0; i < len; ++i) {
				sum += *buff++;
			}
			return 0x100 - sum;
		}

		static std::string out_section_(uint32_t n, uint32_t num) noexcept
		{
			return (boost::format("#%02d/%02d: ") % n % num).str();
		}


		bool command_(uint8_t cmd) noexcept
		{
			bool f = rs232c_.send(static_cast<char>(cmd));
			rs232c_.sync_send();
			return f;
		}


		bool read_(void* buff, uint32_t len, const timeval& tv) noexcept
		{
			return rs232c_.recv(buff, len, tv) == len;
		}

		bool read_(void* buff, uint32_t len) noexcept
		{
			timeval tv;
			tv.tv_sec  = 5;
			tv.tv_usec = 0;
			return rs232c_.recv(buff, len, tv) == len;
		}

		bool write_(const void* buff, uint32_t len) noexcept
		{
			uint32_t wr = rs232c_.send(buff, len);
			rs232c_.sync_send();
			return wr == len;
		}

		enum class BLANK_STATE {
			ERROR,
			BLANK_OK,
			BLANK_NG
		};

		enum class RX_GROUP {
			RX2xx,
			RX6xx
		};

		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		protocol_base() :
			rs232c_(), connection_(false), last_error_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	path	シリアルデバイスパス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(const std::string& path) noexcept
		{
			if(!rs232c_.open(path, B9600)) {
				std::cerr << boost::format("Can't open '%s'") % path << std::endl;
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
			@brief	コネクションの確立（start が成功したら呼ぶ）
			@param[in]	id	コネクション確率 ID
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool connection(uint8_t id) noexcept
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

			uint8_t tmp[1];
			if(!read_(tmp, 1)) {
				return false;
			}
			if(tmp[0] == 0xff) {
				return false;
			}
			if(tmp[0] != id) {
				return false;
			}

			connection_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー領域、ブランクチェック
			@return ブランクチェック後の状態を返す 
		*/
		//-----------------------------------------------------------------//
		BLANK_STATE user_blank_check() noexcept
		{
			if(!command_(0x4D)) {
				return BLANK_STATE::ERROR;
			}
			uint8_t tmp[1];
			if(!read_(tmp, 1)) {  // レスポンス
				return BLANK_STATE::ERROR;
			}
			if(tmp[0] == 0x06) {
				return BLANK_STATE::BLANK_OK;
			} else if(tmp[0] == 0xCD) {
				if(!read_(tmp, 1)) {  // エラーコード
					return BLANK_STATE::ERROR;
				} else if(tmp[0] == 0x52) {
					return BLANK_STATE::BLANK_NG;
				} else {
					return BLANK_STATE::ERROR;
				}
			} else {
				return BLANK_STATE::ERROR;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	消去選択
			@param[in]	grp		RX マイコン・グループ型
			@param[in]	ena		消去選択を解除する場合「false」
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool enable_erase_select(RX_GROUP grp, bool ena = true) noexcept
		{
			if(ena) {
				if(!command_(0x48)) {  // 消去選択
					return false;
				}
				uint8_t tmp[1];
				if(!read_(tmp, 1)) {  // レスポンス
					return false;
				}
				if(tmp[0] != 0x06) {
					return false;
				}
				return true;
			} else {
				if(grp == RX_GROUP::RX2xx) {
					uint8_t tmp[7];
					tmp[0] = 0x59;
					tmp[1] = 0x04;
					tmp[2] = 0xff;
					tmp[3] = 0xff;
					tmp[4] = 0xff;
					tmp[5] = 0xff;
					tmp[6] = 0xa7;
					if(!write_(tmp, 7)) {
						return false;
					}

					if(!read_(tmp, 1)) {  // レスポンス
						return false;
					}
					if(tmp[0] == 0x06) {
						return true;
					} else if(tmp[0] == 0xD9) {
						if(!read_(tmp, 1)) {  // エラーコード
							return false;
						}
						// 0x11: サムチェックエラー
						last_error_ = tmp[0];  // エラーコード
					}
					return false;
				} else if(grp == RX_GROUP::RX6xx) {
					uint8_t tmp[4];
					tmp[0] = 0x58;
					tmp[1] = 0x01;  // size 固定値１
					tmp[2] = 0xff;
					tmp[3] = sum_(tmp, 3);
					if(!write_(tmp, 4)) {
						return false;
					}

					if(!read_(tmp, 1)) {  // レスポンス
						return false;
					}
					if(tmp[0] == 0x06) {
						return true;
					} else if(tmp[0] == 0xD8) {
						if(!read_(tmp, 1)) {  // エラーコード
							return false;
						}
						// 0x11: サムチェックエラー
						last_error_ = tmp[0];  // エラーコード
					}
					return false;
				} else {
					return false;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	クローズ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool close() noexcept
		{
			return rs232c_.close();
		}
	};
}
