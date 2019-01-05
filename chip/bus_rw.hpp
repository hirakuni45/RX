#pragma once
//=====================================================================//
/*!	@file
	@brief	BUS R/W テンプレート・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/delay.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  BUS R/W テンプレート・クラス
		@param[in]	CS	チップ選択
		@param[in]	RS	レジスタ選択
		@param[in]	RD	リード
		@param[in]	WR	ライト
		@param[in]	DL	データパスＬ（DB0 - DB7）
		@param[in]	DH	データパスＨ（DB8 - DB15）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CS, class RS, class RD, class WR, class DL, class DH> 
	class bus_rw {

		static void write16_(uint16_t val) noexcept {
			DH::P = val >> 8;
			DL::P = val & 0xff;
			WR::P = 0;
			CS::P = 0;
			utils::delay::loop(10);
			WR::P = 1;
			CS::P = 1;
		}

		static uint16_t read16_() noexcept {
			RD::P = 0;
			CS::P = 0;
			utils::delay::micro_second(1);
			uint16_t val = static_cast<uint16_t>(DH::P());
			val <<= 8;
			val |= static_cast<uint16_t>(DL::P());
			CS::P = 1;
			RD::P = 1;
			return val;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		static void start() noexcept
		{
			RS::DIR = 1;
			RD::DIR = 1;
			WR::DIR = 1;
			CS::DIR = 1;

			CS::P = 1;
			RS::P = 0;
			RD::P = 1;
			WR::P = 1;

			DL::DIR = 0xff;
			DH::DIR = 0xff;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込み
			@param[in]	rs		レジスタ選択
			@param[in]	val		書き込みデータ
		 */
		//-----------------------------------------------------------------//
		static void write(bool rs, uint16_t val) noexcept {
			RS::P = rs;
			write16_(val);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	読み込み @n
					※あらかじめ、リードアドレスを設定しておく
			@param[in]	rs		レジスタ選択
			@return	読み出しデータ
		 */
		//-----------------------------------------------------------------//
		static uint16_t read(bool rs) noexcept {
			RS::P = rs;
			DL::DIR = 0x00;
			DH::DIR = 0x00;
			auto dat = read16_();
			DL::DIR = 0xff;
			DH::DIR = 0xff;
			return dat;
		}
	};
}
