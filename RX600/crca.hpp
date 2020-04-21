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
		@param[in]	per		ペリフェラル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct crca_t {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

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
		typedef crccr_t<base + 0x00> CRCCR_;
		static CRCCR_ CRCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CRC データ入力レジスタ（CRCDIRxx）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x04> CRCDIR32_;
		static CRCDIR32_ CRCDIR32;
		typedef rw16_t<base + 0x04> CRCDIR16_;
		static CRCDIR16_ CRCDIR16;
		typedef rw8_t<base + 0x04> CRCDIR8_;
		static CRCDIR8_ CRCDIR8;


		//-----------------------------------------------------------------//
		/*!
			@brief  CRC データ出力レジスタ（CRCDORxx）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x08> CRCDOR32_;
		static CRCDOR32_ CRCDOR32;
		typedef rw16_t<base + 0x08> CRCDOR16_;
		static CRCDOR16_ CRCDOR16;
		typedef rw8_t<base + 0x08> CRCDOR8_;
		static CRCDOR8_ CRCDOR8;
	};
	template <uint32_t base, peripheral per>
		typename crca_t<base, per>::CRCCR_    crca_t<base, per>::CRCCR;
	template <uint32_t base, peripheral per>
		typename crca_t<base, per>::CRCDIR32_ crca_t<base, per>::CRCDIR32;
	template <uint32_t base, peripheral per>
		typename crca_t<base, per>::CRCDIR16_ crca_t<base, per>::CRCDIR16;
	template <uint32_t base, peripheral per>
		typename crca_t<base, per>::CRCDIR8_  crca_t<base, per>::CRCDIR8;
	template <uint32_t base, peripheral per>
		typename crca_t<base, per>::CRCDOR32_ crca_t<base, per>::CRCDOR32;
	template <uint32_t base, peripheral per>
		typename crca_t<base, per>::CRCDOR16_ crca_t<base, per>::CRCDOR16;
	template <uint32_t base, peripheral per>
		typename crca_t<base, per>::CRCDOR8_  crca_t<base, per>::CRCDOR8;


	typedef crca_t<0x00088280, peripheral::CRC> CRCA;
}
