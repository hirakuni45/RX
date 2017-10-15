#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ Standby RAM 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstring>
#include "RX64M/power_cfg.hpp"
#include "common/io_utils.hpp"
#include "common/delay.hpp"
#include "common/format.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  スタンバイＲＡＭアクセス・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class standby_ram {
	public:

		static const uint32_t TOP  = 0x000A4000;  ///< RAM 開始アドレス
		static const uint32_t SIZE = 8192;  	  ///< RAM サイズ

		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		standby_ram() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		static void start() noexcept
		{
			device::power_cfg::turn(peripheral::STBRAM);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込み
			@param[in]	pos		位置
			@param[in]	data	データ
		 */
		//-----------------------------------------------------------------//
		static bool put(uint32_t pos, uint8_t data) noexcept
		{
			if(pos >= SIZE) {
				return false;
			}
			device::wr8_(TOP + pos, data);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コピー書き込み
			@param[in]	src		ソース
			@param[in]	len		長さ
			@param[in]	dst		書き込み先
			@return コピー数
		 */
		//-----------------------------------------------------------------//
		static uint32_t copy(const void* src, uint32_t len, uint32_t dst) noexcept
		{
			if(dst >= SIZE || len > SIZE || src == nullptr) return 0;

			if((dst + len) >= SIZE) len = SIZE - dst;
			std::memcpy(reinterpret_cast<void*>(TOP + dst), src, len);
			return len;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	読み出し
			@param[in]	pos		位置
			@param[out]	data	データ
		 */
		//-----------------------------------------------------------------//
		static bool get(uint32_t pos, uint8_t& data) noexcept
		{
			if(pos >= SIZE) {
				return false;
			}
			data = device::rd8_(TOP + pos);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コピー書き込み
			@param[in]	src		ソース
			@param[in]	len		長さ
			@param[in]	dst		書き込み先
			@return コピー数
		 */
		//-----------------------------------------------------------------//
		static uint32_t copy(uint32_t src, uint32_t len, void* dst) noexcept
		{
			if(dst == nullptr || src >= SIZE || len > SIZE) return 0;

			if((src + len) >= SIZE) len = SIZE - src;
			std::memcpy(dst, reinterpret_cast<void*>(TOP + src), len);
			return len;
		}
	};
}
