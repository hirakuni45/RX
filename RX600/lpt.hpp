#pragma once
//=========================================================================//
/*!	@file
	@brief	ローパワータイマ（LPT/LPTa）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ローパワータイマ・コア
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct lpt_core_t {

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
		static inline lptcr3_t<0x0008'00B2>  LPTCR3;


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
		static inline lptprd_t<0x0008'00B4>  LPTPRD;


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
		static inline lpcmr0_t<0x0008'00B8>  LPCMR0;


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
		static inline lpwucr_t<0x0008'00BC>  LPWUCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ローパワータイマ（LPTa）
		@param[in]	cmi1	割り込み要因
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <ICU::VECTOR cmi1>
	struct lpta_t : public lpt_core_t {

		static constexpr auto PERIPHERAL = peripheral::LPT;	///< ペリフェラル型
		static constexpr auto CMI1 = cmi1;		///< 割り込み要因

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
			bit_rw_t <io_, bitpos::B3>     LPCNTCKSEL2;
			bit_rw_t <io_, bitpos::B4>     LPCNTCKSEL;

			bit_rw_t <io_, bitpos::B6>     LPCMRE0;
			bit_rw_t <io_, bitpos::B7>     LPCMRE1;
		};
		static inline lptcr1_t<0x0008'00B0>  LPTCR1;


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

			bit_rw_t <io_, bitpos::B5>   CPOL;
			bit_rw_t <io_, bitpos::B6>   OLVL;
			bit_rw_t <io_, bitpos::B7>   PWME;
		};
		static inline lptcr2_t<0x0008'00B1>  LPTCR2;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ローパワータイマ（LPT）
		@param[in]	cmi1	割り込み要因
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <ICU::VECTOR cmi1>
	struct lpt_t : public lpt_core_t {

		static constexpr auto PERIPHERAL = peripheral::LPT;	///< ペリフェラル型
		static constexpr auto CMI1 = cmi1;		///< 割り込み要因

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
		static inline lptcr1_t<0x0008'00B0>  LPTCR1;


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
		static inline lptcr2_t<0x0008'00B1>  LPTCR2;
	};

#if defined(SIG_RX140)
	typedef lpta_t<ICU::VECTOR::LPTCMI1> LPT;
#elif defined(SIG_RX231)
	typedef lpt_t<ICU::VECTOR::NONE> LPT;
#endif
}
