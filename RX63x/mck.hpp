#pragma once
//=====================================================================//
/*!	@file
	@brief	RX631/RX63N MCK 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX63x/peripheral.hpp"
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  周波数測定機能（MCK）クラス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<peripheral per>
	struct mck_t {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief  カウントクロック拡張レジスタ n（SCKn）(n=1、2)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sck_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  SCK;
		};
		static inline sck_t<0x0008'C880> SCK0;
		static inline sck_t<0x0008'C890> SCK1;
	};
	typedef mck_t<peripheral::MCK> MCK;
}
