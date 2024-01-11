#pragma once
//=========================================================================//
/*!	@file
	@brief	ローパワータイマ（LPT）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ローパワータイマ（LPT）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct lpt_t {

		static constexpr auto PERIPHERAL = peripheral::LPT;	///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief  ローパワータイマコントロールレジスタ 1（LPTCR1）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lptcr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  LPCNTPSSEL;

			bit_rw_t <io_, bitpos::B4>     LPCNTCKSEL;

			bit_rw_t <io_, bitpos::B6>     LPCMRE0;
		};
		typedef lptcr1_t<0x0008'00B0>  LPTCR1_;
		static  LPTCR1_ LPTCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ローパワータイマコントロールレジスタ 2（LPTCR2）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lptcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>   LPCNTSTP;
		};
		typedef lptcr2_t<0x0008'00B1>  LPTCR2_;
		static  LPTCR2_ LPTCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ローパワータイマコントロールレジスタ 3（LPTCR3）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lptcr3_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>   LPCNTEN;
			bit_rw_t <io_, bitpos::B1>   LPCNTRST;
		};
		typedef lptcr3_t<0x0008'00B2>  LPTCR3_;
		static  LPTCR3_ LPTCR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  ローパワータイマ周期設定レジスタ（LPTPRD）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lptprd_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  LPCNTPRD;
		};
		typedef lptprd_t<0x0008'00B4>  LPTPRD_;
		static  LPTPRD_ LPTPRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  ローパワータイマコンペアレジスタ 0（LPCMR0）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lpcmr0_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  LPCNTPRD;
		};
		typedef lpcmr0_t<0x0008'00B8>  LPCMR0_;
		static  LPCMR0_ LPCMR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ローパワータイマスタンバイ復帰許可レジスタ（LPWUCR）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lpwucr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B15>		LPWKUPEN;
		};
		typedef lpwucr_t<0x0008'00BC>  LPWUCR_;
		static  LPWUCR_ LPWUCR;
	};
	template <class _> typename lpt_t<_>::LPTCR1_ lpt_t<_>::LPTCR1;
	template <class _> typename lpt_t<_>::LPTCR2_ lpt_t<_>::LPTCR2;
	template <class _> typename lpt_t<_>::LPTCR3_ lpt_t<_>::LPTCR3;
	template <class _> typename lpt_t<_>::LPTPRD_ lpt_t<_>::LPTPRD;
	template <class _> typename lpt_t<_>::LPCMR0_ lpt_t<_>::LPCMR0;
	template <class _> typename lpt_t<_>::LPWUCR_ lpt_t<_>::LPWUCR;

	typedef lpt_t<void> LPT;
}
