#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・データトランスファコントローラ（DTCa）定義 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  データトランスファコントローラ（DTCa）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct dtc_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  DTC コントロールレジスタ（DTCCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dtccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4> RRS;
		};
		static dtccr_t<0x00082400> DTCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DTC アドレスモードレジスタ（DTCADMOD）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dtcadmod_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SHORT;
		};
		static dtcadmod_t<0x00082408> DTCADMOD;


		//-----------------------------------------------------------------//
		/*!
			@brief  DTC モジュール起動レジスタ（DTCST）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dtcst_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DTCST;
		};
		static dtcst_t<0x0008240C> DTCST;


		//-----------------------------------------------------------------//
		/*!
			@brief  DTC ステータスレジスタ（DTCSTS）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dtcsts_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> VECN;
			bit_rw_t <io_, bitpos::B15>   ACT;
		};
		static dtcsts_t<0x0008240E> DTCSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return peripheral::DTC; }
	};
	typedef dtc_t DTC;
}
