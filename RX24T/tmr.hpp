#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・8 ビットタイマ（TMR）定義 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX24T/peripheral.hpp"
#include "RX24T/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  8 ビットタイマ（TMR）
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct tmr_t {

		//-----------------------------------------------------------------//
		/*!
			@brie	タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0x08> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ A（TCORA）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0x04> TCORA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ B（TCORB）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0x06> TCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマコントロールレジスタ（TCR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B3, 2>  CCLR;
			bit_rw_t <io_, bitpos::B5>     OVIE;
			bit_rw_t <io_, bitpos::B6>     CMIEA;
			bit_rw_t <io_, bitpos::B7>     CMIEB;
		};
		static tcr_t<base + 0x00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマカウンタコントロールレジスタ（TCCR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tccr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  CKS;
			bits_rw_t<io_, bitpos::B3, 2>  CSS;
			bit_rw_t <io_, bitpos::B7>     TMRIS;
		};
		static tccr_t<base + 0x0A> TCCR;

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  8 ビットタイマ（TMR）偶数版
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct tmr0246_t : public tmr_t<base> {

		//-----------------------------------------------------------------//
		/*!
			@brie	タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x08> TCNT16;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ A（TCORA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x04> TCORA16;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ B（TCORB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x06> TCORB16;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマコントロール／ステータスレジスタ（TCSR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  OSA;
			bits_rw_t<io_, bitpos::B2, 2>  OSB;
			bit_rw_t <io_, bitpos::B4>     ADTE;
		};
		static tcsr_t<base + 0x02> TCSR;

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  8 ビットタイマ（TMR）奇数版
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct tmr1357_t : public tmr_t<base> {

		//-----------------------------------------------------------------//
		/*!
			@brief	タイマコントロール／ステータスレジスタ（TCSR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  OSA;
			bits_rw_t<io_, bitpos::B2, 2>  OSB;
		};
		static tcsr_t<base + 0x02> TCSR;

	};


	typedef tmr0246_t<0x00088200> TMR0;
	typedef tmr1357_t<0x00088201> TMR1;
	typedef tmr0246_t<0x00088210> TMR2;
	typedef tmr1357_t<0x00088211> TMR3;
	typedef tmr0246_t<0x00088220> TMR4;
	typedef tmr1357_t<0x00088221> TMR5;
	typedef tmr0246_t<0x00088230> TMR6;
	typedef tmr1357_t<0x00088231> TMR7;
}
