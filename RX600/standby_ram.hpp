#pragma once
//========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ Standby RAM 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"
#include "common/delay.hpp"
#include "common/format.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  スタンバイＲＡＭアクセス・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t size>
	class standby_ram {
	public:

		static constexpr uint32_t TOP  = 0x000A'4000;  ///< RAM 開始アドレス
		static constexpr uint32_t SIZE = size;  	   ///< RAM サイズ

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
			device::power_mgr::turn(peripheral::STBRAM);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込み（８ビット）
			@param[in]	pos		位置
			@param[in]	data	データ
		 */
		//-----------------------------------------------------------------//
		static bool put8(uint32_t pos, uint8_t data) noexcept
		{
			if(pos >= SIZE) {
				return false;
			}
			device::wr8_(TOP + pos, data);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込み（１６ビット）
			@param[in]	pos		位置
			@param[in]	data	データ
		 */
		//-----------------------------------------------------------------//
		static bool put16(uint32_t pos, uint16_t data) noexcept
		{
			if(pos >= SIZE) {
				return false;
			}
			device::wr16_(TOP + pos, data);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込み（３２ビット）
			@param[in]	pos		位置
			@param[in]	data	データ
		 */
		//-----------------------------------------------------------------//
		static bool put32(uint32_t pos, uint32_t data) noexcept
		{
			if(pos >= SIZE) {
				return false;
			}
			device::wr32_(TOP + pos, data);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コピー（SRAM へ書き込み）
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
			@brief	読み出し（８ビット）
			@param[in]	pos		位置
			@param[out]	data	データ
		 */
		//-----------------------------------------------------------------//
		static bool get8(uint32_t pos, uint8_t& data) noexcept
		{
			if(pos >= SIZE) {
				return false;
			}
			data = device::rd8_(TOP + pos);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	読み出し（１６ビット）
			@param[in]	pos		位置
			@param[out]	data	データ
		 */
		//-----------------------------------------------------------------//
		static bool get16(uint32_t pos, uint16_t& data) noexcept
		{
			if(pos >= SIZE) {
				return false;
			}
			data = device::rd16_(TOP + pos);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	読み出し（３２ビット）
			@param[in]	pos		位置
			@param[out]	data	データ
		 */
		//-----------------------------------------------------------------//
		static bool get32(uint32_t pos, uint32_t& data) noexcept
		{
			if(pos >= SIZE) {
				return false;
			}
			data = device::rd32_(TOP + pos);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コピー（SRAM から読み出し）
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
#if defined(SIG_RX671)
	typedef standby_ram<4096> STANDBY_RAM;
#else
	typedef standby_ram<8192> STANDBY_RAM;
#endif
}
