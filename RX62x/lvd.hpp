#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N LVD 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  電圧検出回路（LVD）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct lvd_t {

		// リセットステータスレジスタ（RSTSR）
		// system クラスで定義されている。

		//-----------------------------------------------------------------//
		/*!
			@brief  低電圧検出コントロールレジスタ用キーコードレジスタ（LVDKEYR）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'C28C> LVDKEYR;


		//-----------------------------------------------------------------//
		/*!
			@brief  低電圧検出コントロールレジスタ（LVDCR）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lvdcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>  LVD1RI;
			bit_rw_t<io_, bitpos::B3>  LVD1E;

			bit_rw_t<io_, bitpos::B6>  LVD2RI;
			bit_rw_t<io_, bitpos::B7>  LVD2E;
		};
		static inline lvdcr_t<0x0008'C28D>  LVDCR;
	};
	typedef lvd_t LVD;
}
