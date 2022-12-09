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
