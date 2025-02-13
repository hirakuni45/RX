#pragma once
//=========================================================================//
/*!	@file
	@brief	RX210 グループ・CMPB 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  コンパレータ B（CMPB）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct cmpb_t {

		static constexpr auto PERIPHERAL = peripheral::CMPB;	///< ペリフェラル型
		static constexpr auto CMP0 = ICU::VECTOR::CMPB0;		///< 割り込みベクター０
		static constexpr auto CMP1 = ICU::VECTOR::CMPB1;		///< 割り込みベクター１

		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B 制御レジスタ 1（CPBCNT1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbcnt_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0INI;

			bit_rw_t <io_, bitpos::B4>     CPB1INI;
		};
		static inline cpbcnt_t<0x0008'C580> CPBCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B フラグレジスタ（CPBFLG）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbflg_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0OUT;

			bit_rw_t <io_, bitpos::B1>     CPB1OUT;
		};
		static inline cpbflg_t<0x0008'C582> CPBFLG;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B 割り込み制御レジスタ（CPBINT）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbint_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0INTEN;
			bit_rw_t <io_, bitpos::B1>     CPB0INTEG;
			bit_rw_t <io_, bitpos::B2>     CPB0INTPL;

			bit_rw_t <io_, bitpos::B4>     CPB1INTEN;
			bit_rw_t <io_, bitpos::B5>     CPB1INTEG;
			bit_rw_t <io_, bitpos::B6>     CPB1INTPL;
		};
		static inline cpbint_t<0x0008'C583> CPBINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  コンパレータ B フィルタ選択レジスタ（CPBF）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct cpbf_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPB0FEN;

			bits_rw_t<io_, bitpos::B2, 2>  CPB0F;
			bit_rw_t <io_, bitpos::B4>     CPB1FEN;

			bits_rw_t<io_, bitpos::B6, 2>  CPB1F;
		};
		static inline cpbf_t<0x0008'C584> CPBF;
	};
	typedef cmpb_t CMPB;
}
