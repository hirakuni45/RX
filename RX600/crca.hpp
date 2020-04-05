#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・CRCA 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CRCA 演算器クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct crca_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  CRC コントロールレジスタ（CRCCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct crccr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  GPS;
			bit_rw_t <io_, bitpos::B6>     LMS;

			bit_rw_t <io_, bitpos::B7>     DORCLR;
		};
		static crccr_t<base + 0x00> CRCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CRC データ入力レジスタ（CRCDIRxx）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x04> CRCDIR32;
		static rw16_t<base + 0x04> CRCDIR16;
		static rw8_t<base + 0x04> CRCDIR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  CRC データ出力レジスタ（CRCDORxx）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x08> CRCDOR32;
		static rw16_t<base + 0x08> CRCDOR16;
		static rw8_t<base + 0x08> CRCDOR8;

	};
	typedef crca_t<0x00088280> CRCA;
}
