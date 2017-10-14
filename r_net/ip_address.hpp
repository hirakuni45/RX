#pragma once
//=====================================================================//
/*!	@file
	@brief	IP address 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/fixed_string.hpp"
#include "common/format.hpp"
#include "common/input.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ip_address クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ip_address {

		union address_t {
			uint32_t	dword;
			uint8_t		bytes[4];  // IPv4 address
			address_t(uint32_t v = 0) : dword(v) { }
			address_t(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) {
				bytes[0] = v0;
				bytes[1] = v1;
				bytes[2] = v2;
				bytes[3] = v3;
			}
		};

		address_t	address_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	dword	32bits IP
		*/
		//-----------------------------------------------------------------//
		ip_address(uint32_t dword = 0) : address_(dword) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	first	IP 1ST
			@param[in]	second	IP 2ND
			@param[in]	third	IP 3RD
			@param[in]	fourth	IP 4TH
		*/
		//-----------------------------------------------------------------//
		ip_address(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth) :
			address_(first, second, third, fourth) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  設定
			@param[in]	first	IP 1ST
			@param[in]	second	IP 2ND
			@param[in]	third	IP 3RD
			@param[in]	fourth	IP 4TH
		*/
		//-----------------------------------------------------------------//
		void set(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth) {
			address_.bytes[0] = first;
			address_.bytes[1] = second;
			address_.bytes[2] = third;
			address_.bytes[3] = fourth;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  配列から設定
			@param[in]	address	配列
		*/
		//-----------------------------------------------------------------//
		void set(const uint8_t* address) {
			if(address == nullptr) {
				address_ = 0;
				return;
			}
			address_.bytes[0] = address[0];
			address_.bytes[1] = address[1];
			address_.bytes[2] = address[2];
			address_.bytes[3] = address[3];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  バイト列取得
			@return バイト配列
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get() const { return address_.bytes; }


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列から設定
			@param[in]	address	配列
			@return 変換が正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool from_string(const char *address) {
			if(address == nullptr) return false;
			int a, b, c, d;
			auto f = (utils::input("%d.%d.%d.%d", address) % a % b % c % d).status();
			if(f) {
				if(a >= 0 && a <= 255) address_.bytes[0] = a;
				else return false;
				if(a >= 0 && b <= 255) address_.bytes[1] = b;
				else return false;
				if(a >= 0 && c <= 255) address_.bytes[2] = c;
				else return false;
				if(a >= 0 && d <= 255) address_.bytes[3] = d;
				else return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  型変換キャスト演算子（uint32_t 型）
		*/
		//-----------------------------------------------------------------//
		operator uint32_t() const { return address_.dword; };


		bool operator==(const ip_address& addr) const {
			return address_.dword == addr.address_.dword;
		}


		bool operator == (const uint8_t* addr) const {
			if(addr == nullptr) return false;
			return (address_.bytes[0] == addr[0]
				 && address_.bytes[1] == addr[1]
				 && address_.bytes[2] == addr[2]
				 && address_.bytes[3] == addr[3]);
		}


		uint8_t operator [] (int index) const { return address_.bytes[index]; };


		uint8_t& operator [] (int index) { return address_.bytes[index]; };


		ip_address& operator = (const uint8_t* address) {
			address_.bytes[0] = address[0];
			address_.bytes[1] = address[1];
			address_.bytes[2] = address[2];
			address_.bytes[3] = address[3];
			return *this;
		}


		ip_address& operator = (uint32_t address) {
			address_.dword = address;
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列で取得
			@param[in]	spch	分離キャラクター（通常「.」）
			@return 文字列
		*/
		//-----------------------------------------------------------------//
		const char* c_str(char spch = '.') const {
			static char tmp[4*4+1];
			utils::sformat("%d%c%d%c%d%c%d", tmp, sizeof(tmp))
				% static_cast<int>(address_.bytes[0]) % spch
				% static_cast<int>(address_.bytes[1]) % spch
				% static_cast<int>(address_.bytes[2]) % spch
				% static_cast<int>(address_.bytes[3]);
			return tmp;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  エンディアン変換
			@param[in]	src	32bits エンディアン変換
			@return エンディアン変換
		*/
		//-----------------------------------------------------------------//
		static uint32_t endian_convert(uint32_t src) {
			return ((src >> 24) & 0x000000FF) | ((src >> 8 ) & 0x0000FF00)
				 | ((src << 8 ) & 0x00FF0000) | ((src << 24) & 0xFF000000);
		}
	};
}

