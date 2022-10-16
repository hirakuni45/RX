#pragma once
//=============================================================================//
/*!	@file
	@brief	RX621/RX62N 10 ビット A/D コンバータ（ADa）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<uint32_t base>
	struct ad_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  A/D データレジスタ n（ADDRn）（n = A ～ D）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x00> ADDRA_;
		static ADDRA_ ADDRA;

		typedef rw16_t<base + 0x02> ADDRB_;
		static ADDRB_ ADDRB;

		typedef rw16_t<base + 0x04> ADDRC_;
		static ADDRC_ ADDRC;

		typedef rw16_t<base + 0x06> ADDRD_;
		static ADDRD_ ADDRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コントロール／ステータスレジスタ（ADCSR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  CH;

			bit_rw_t <io_, bitpos::B5>     ADST;
			bit_rw_t <io_, bitpos::B6>     ADIE;
		};
		typedef adcsr_t<base + 0x10> ADCSR_;
		static ADCSR_ ADCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D コントロールレジスタ（ADCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct adcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  MODE;
			bits_rw_t<io_, bitpos::B2, 2>  CKS;

			bits_rw_t<io_, bitpos::B5, 3>  TRGS;
		};
		typedef adcr_t<base + 0x11> ADCR_;
		static ADCR_ ADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ADDRn フォーマット選択レジスタ（ADDPR）（n = A ～ D）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addpr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>     DPSEL;
		};
		typedef addpr_t<base + 0x12> ADDPR_;
		static ADDPR_ ADDPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D サンプリングステートレジスタ（ADSSTR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x13> ADSSTR_;
		static ADSSTR_ ADSSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 自己診断レジスタ（ADDIAGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct addiagr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  DIAG;
		};
		typedef addiagr_t<base + 0x1F> ADDIAGR_;
		static ADDIAGR_ ADDIAGR;
	};
	template <uint32_t base> typename ad_base_t<base>::ADDRA_  ad_base_t<base>::ADDRA;
	template <uint32_t base> typename ad_base_t<base>::ADDRB_  ad_base_t<base>::ADDRB;
	template <uint32_t base> typename ad_base_t<base>::ADDRC_  ad_base_t<base>::ADDRC;
	template <uint32_t base> typename ad_base_t<base>::ADDRD_  ad_base_t<base>::ADDRD;
	template <uint32_t base> typename ad_base_t<base>::ADCSR_  ad_base_t<base>::ADCSR;
	template <uint32_t base> typename ad_base_t<base>::ADCR_   ad_base_t<base>::ADCR;
	template <uint32_t base> typename ad_base_t<base>::ADDPR_  ad_base_t<base>::ADDPR;
	template <uint32_t base> typename ad_base_t<base>::ADSSTR_ ad_base_t<base>::ADSSTR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  A/D コンバータ・ベース・クラス
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	adi		割り込み番号
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR adi>
	struct ada_t : public ad_base_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto ADI = adi;

	};


	typedef ada_t<0x0008'8040, peripheral::AD0, ICU::VECTOR::ADI0> AD0;
	typedef ada_t<0x0008'8060, peripheral::AD1, ICU::VECTOR::ADI1> AD1;
}
