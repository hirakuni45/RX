#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・LCD コントローラ / ドライバ（LCDC） 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  LCDC 定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct lcdc_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  LCD モードレジスタ 0（LCDM0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lcdm0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  LBAS;
			bits_rw_t<io_, bitpos::B2, 3>  LDTY;
			bit_rw_t <io_, bitpos::B5>     LWAVE;
			bits_rw_t<io_, bitpos::B6, 2>  MDSET;
		};
		static inline lcdm0_t<0x000A'0800> LCDM0;


		//-----------------------------------------------------------------//
		/*!
			@brief  LCD モードレジスタ 1（LCDM1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lcdm1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     LCDVLM;

			bit_rw_t <io_, bitpos::B3>     LCDSEL;
			bit_rw_t <io_, bitpos::B4>     BLON;
			bit_rw_t <io_, bitpos::B5>     VLCON;
			bit_rw_t <io_, bitpos::B6>     SCOC;
			bit_rw_t <io_, bitpos::B7>     LCDON;
		};
		static inline lcdm1_t<0x000A'0801> LCDM1;


		//-----------------------------------------------------------------//
		/*!
			@brief  LCD クロック制御レジスタ 0（LCDC0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lcdc0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  LCDC0;
		};
		static inline lcdc0_t<0x000A'0802> LCDC0;


		//-----------------------------------------------------------------//
		/*!
			@brief  LCD 昇圧レベル制御レジスタ（VLCD）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct vlcd_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  VLCD;
		};
		static inline vlcd_t<0x000A'0803> VLCD;
	};
}
