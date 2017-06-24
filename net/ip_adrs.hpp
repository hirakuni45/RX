#pragma once
//=====================================================================//
/*!	@file
	@brief	IP アドレス・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "common/fixed_string.hpp"
#include "common/format.hpp"
#include "common/input.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ip_adrs クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class ip_adrs {

		union adrs_t {
			uint32_t	dw;
			uint8_t		bs[4];  // IPv4 address
			adrs_t(uint32_t v = 0) : dw(v) { }
			adrs_t(const uint8_t* src) {
				if(src == nullptr) {
					dw = 0;
					return;
				}
				bs[0] = src[0];
				bs[1] = src[1];
				bs[2] = src[2];
				bs[3] = src[3];
			}
			adrs_t(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) {
				bs[0] = v0;
				bs[1] = v1;
				bs[2] = v2;
				bs[3] = v3;
			}
		};

		adrs_t	adrs_;


		static uint32_t ec_(uint32_t src)
		{
			return ((src >> 24) & 0x000000FF) | ((src >> 8 ) & 0x0000FF00)
				 | ((src << 8 ) & 0x00FF0000) | ((src << 24) & 0xFF000000);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	dw	32bits IP
		*/
		//-----------------------------------------------------------------//
		ip_adrs(uint32_t dw = 0) : adrs_(dw) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	adr	バイト列（nullptrの場合無効）
		*/
		//-----------------------------------------------------------------//
		ip_adrs(const uint8_t* adr) : adrs_(adr) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	first	IP 1ST
			@param[in]	second	IP 2ND
			@param[in]	third	IP 3RD
			@param[in]	fourth	IP 4TH
		*/
		//-----------------------------------------------------------------//
		ip_adrs(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth) :
			adrs_(first, second, third, fourth) { }


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
			adrs_.bs[0] = first;
			adrs_.bs[1] = second;
			adrs_.bs[2] = third;
			adrs_.bs[3] = fourth;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  配列から設定
			@param[in]	address	配列
		*/
		//-----------------------------------------------------------------//
		void set(const uint8_t* adrs) {
			if(adrs == nullptr) {
				adrs_.dw = 0;
				return;
			}
			adrs_.bs[0] = adrs[0];
			adrs_.bs[1] = adrs[1];
			adrs_.bs[2] = adrs[2];
			adrs_.bs[3] = adrs[3];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  バイト列取得
			@return バイト配列
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get() const { return adrs_.bs; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ワード値取得
			@return ワード値
		*/
		//-----------------------------------------------------------------//
		uint32_t getw() const { return adrs_.dw; }


		//-----------------------------------------------------------------//
		/*!
			@brief  0.0.0.0 (Any)アドレスか検査
			@return Any なら「true」
		*/
		//-----------------------------------------------------------------//
		bool is_any() const { return adrs_.dw == 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief  文字列から設定
			@param[in]	address	配列
		*/
		//-----------------------------------------------------------------//
		bool from_string(const char *adrs) {
			if(adrs == nullptr) return false;
			int a, b, c, d;
			auto f = (utils::input("%d.%d.%d.%d", adrs) % a % b % c % d).status();
			if(f) {
				if(a >= 0 && a <= 255) adrs_.bs[0] = a;
				if(a >= 0 && b <= 255) adrs_.bs[1] = b;
				if(a >= 0 && c <= 255) adrs_.bs[2] = c;
				if(a >= 0 && d <= 255) adrs_.bs[3] = d;
			}
			return f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  型変換キャスト演算子（uint32_t 型）
		*/
		//-----------------------------------------------------------------//
		operator uint32_t() const { return adrs_.dw; };


		//-----------------------------------------------------------------//
		/*!
			@brief  比較（自分と同じ型）
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator==(const ip_adrs& ipa) const {
			return adrs_.dw == ipa.adrs_.dw;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  比較（自分と同じ型）
			@return 同じなら「true」
		*/
		//-----------------------------------------------------------------//
		bool operator == (const uint8_t* addr) const {
			if(addr == nullptr) return false;
			return (adrs_.bs[0] == addr[0]
				 && adrs_.bs[1] == addr[1]
				 && adrs_.bs[2] == addr[2]
				 && adrs_.bs[3] == addr[3]);
		}


		uint8_t operator [] (int index) const { return adrs_.bs[index]; };


		uint8_t& operator [] (int index) { return adrs_.bs[index]; };


		ip_adrs& operator = (const uint8_t* adrs) {
			adrs_.bs[0] = adrs[0];
			adrs_.bs[1] = adrs[1];
			adrs_.bs[2] = adrs[2];
			adrs_.bs[3] = adrs[3];
			return *this;
		}


		ip_adrs& operator = (uint32_t adrs) {
			adrs_.dw = adrs;
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
				% static_cast<int>(adrs_.bs[0]) % spch
				% static_cast<int>(adrs_.bs[1]) % spch
				% static_cast<int>(adrs_.bs[2]) % spch
				% static_cast<int>(adrs_.bs[3]);
			return tmp;
		}
	};
}

