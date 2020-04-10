#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・8 ビットタイマ（TMR）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

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
		typedef rw8_t<base + 0x08> tcnt_t;
		static tcnt_t TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ A（TCORA）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x04> tcora_t;
		static tcora_t TCORA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ B（TCORB）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x06> tcorb_t;
		static tcorb_t TCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマコントロールレジスタ（TCR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcr_t_ : public rw8_t<ofs> {
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
		typedef tcr_t_<base + 0x00> tcr_t;
		static tcr_t TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマカウンタコントロールレジスタ（TCCR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tccr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  CKS;
			bits_rw_t<io_, bitpos::B3, 2>  CSS;
			bit_rw_t <io_, bitpos::B7>     TMRIS;
		};
		typedef tccr_t_<base + 0x0A> tccr_t;
		static tccr_t TCCR;

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
		typedef rw16_t<base + 0x08> tcnt16_t;
		static tcnt16_t TCNT16;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ A（TCORA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x04> tcora16_t;
		static tcora16_t TCORA16;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ B（TCORB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x06> tcorb16_t;
		static tcorb16_t TCORB16;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマコントロール／ステータスレジスタ（TCSR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcsr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  OSA;
			bits_rw_t<io_, bitpos::B2, 2>  OSB;
			bit_rw_t <io_, bitpos::B4>     ADTE;
		};
		typedef tcsr_t_<base + 0x02> tcsr_t;
		static tcsr_t TCSR;

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
		struct tcsr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  OSA;
			bits_rw_t<io_, bitpos::B2, 2>  OSB;
		};
		typedef tcsr_t_<base + 0x02> tcsr_t;
		static tcsr_t TCSR;

	};

	typedef tmr0246_t<0x00088200> TMR0;
	typedef tmr1357_t<0x00088201> TMR1;
	typedef tmr0246_t<0x00088210> TMR2;
	typedef tmr1357_t<0x00088211> TMR3;
#if defined(SIG_RX24T) || defined(SIG_RX66T)
	typedef tmr0246_t<0x00088220> TMR4;
	typedef tmr1357_t<0x00088221> TMR5;
	typedef tmr0246_t<0x00088230> TMR6;
	typedef tmr1357_t<0x00088231> TMR7;
#endif

	template <uint32_t base> typename tmr_t<base>::tcnt_t tmr_t<base>::TCNT;
	template <uint32_t base> typename tmr_t<base>::tcora_t tmr_t<base>::TCORA;
	template <uint32_t base> typename tmr_t<base>::tcorb_t tmr_t<base>::TCORB;
	template <uint32_t base> typename tmr_t<base>::tcr_t tmr_t<base>::TCR;
	template <uint32_t base> typename tmr_t<base>::tccr_t tmr_t<base>::TCCR;

	template <uint32_t base> typename tmr0246_t<base>::tcnt16_t tmr0246_t<base>::TCNT16;
	template <uint32_t base> typename tmr0246_t<base>::tcora16_t tmr0246_t<base>::TCORA16;
	template <uint32_t base> typename tmr0246_t<base>::tcorb16_t tmr0246_t<base>::TCORB16;
	template <uint32_t base> typename tmr0246_t<base>::tcsr_t tmr0246_t<base>::TCSR;

	template <uint32_t base> typename tmr1357_t<base>::tcsr_t tmr1357_t<base>::TCSR;
}
