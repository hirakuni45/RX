#pragma once
//=========================================================================//
/*!	@file
	@brief	プログラマブルゲインアンプ (PGA) @n
			RX14T
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  PGA class
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct pga_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  プログラマブルゲインアンプコントロールレジスタ (PGACR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pgacr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>   PGA0EN;

			bit_rw_t<io_, bitpos::B6>   PGA1EN;

			bit_rw_t<io_, bitpos::B10>  PGA2EN;

			bit_rw_t<io_, bitpos::B12>  PGA0GND;
			bit_rw_t<io_, bitpos::B13>  PGA1GND;
			bit_rw_t<io_, bitpos::B14>  PGA2GND;
		};
		static inline pgacr_t<base + 0x00> PGACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プログラマブルゲインアンプゲイン設定レジスタ 0 (PGAGS0)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pgags0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  PGA0GAIN;

			bits_rw_t<io_, bitpos::B4, 2>  PGA1GAIN;

			bits_rw_t<io_, bitpos::B8, 2>  PGA2GAIN;
		};
		static inline pgags0_t<base + 0x02> PGAGS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  プログラマブルゲインアンプモニタ出力コントロールレジスタ (PGAMONCR)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pgamoncr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     PGAMON;

			bits_rw_t<io_, bitpos::B4, 4>  MONSEL;
		};
		static inline pgamoncr_t<base + 0x40> PGAMONCR;
	};
	typedef pga_t<0x0008'91A0> PGA;
}
