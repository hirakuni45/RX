#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・8 ビットタイマ（TMR）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2020 Kunihito Hiramatsu @n
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
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	cmia	CMIA 型割り込みベクター
		@param[in]	cmib	CMIB 型割り込みベクター
		@param[in]	ovi		OVI 型割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
	struct tmr_t {

		static const auto PERIPHERAL = per;		///< ペリフェラル型
		static const auto CMIA_VEC = cmia;		///< CMIA 割り込みベクタ
		static const auto CMIB_VEC = cmib;		///< CMIB 割り込みベクタ
		static const auto OVI_VEC  = ovi;		///< OVI 割り込みベクタ
		static const uint32_t PCLK = F_PCLKB;	///< PCLK 周波数

		//-----------------------------------------------------------------//
		/*!
			@brie	タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x08> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ A（TCORA）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x04> TCORA_;
		static  TCORA_ TCORA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ B（TCORB）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x06> TCORB_;
		static  TCORB_ TCORB;


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
		typedef tcr_t<base + 0x00> TCR_;
		static  TCR_ TCR;


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
		typedef tccr_t<base + 0x0A> TCCR_;
		static  TCCR_ TCCR;
	};
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
		typename tmr_t<base, per, INT, cmia, cmib, ovi>::TCNT_ tmr_t<base, per, INT, cmia, cmib, ovi>::TCNT;
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
		typename tmr_t<base, per, INT, cmia, cmib, ovi>::TCORA_ tmr_t<base, per, INT, cmia, cmib, ovi>::TCORA;
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
		typename tmr_t<base, per, INT, cmia, cmib, ovi>::TCORB_ tmr_t<base, per, INT, cmia, cmib, ovi>::TCORB;
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
		typename tmr_t<base, per, INT, cmia, cmib, ovi>::TCR_ tmr_t<base, per, INT, cmia, cmib, ovi>::TCR;
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
		typename tmr_t<base, per, INT, cmia, cmib, ovi>::TCCR_ tmr_t<base, per, INT, cmia, cmib, ovi>::TCCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  8 ビットタイマ（TMR）偶数版
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	cmia	CMIA 型割り込みベクター
		@param[in]	cmib	CMIB 型割り込みベクター
		@param[in]	ovi		OVI 型割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
	struct tmr0246_t : public tmr_t<base, per, INT, cmia, cmib, ovi> {

		//-----------------------------------------------------------------//
		/*!
			@brie	タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x08> TCNT16_;
		static  TCNT16_ TCNT16;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ A（TCORA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x04> TCORA16_;
		static  TCORA16_ TCORA16;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ B（TCORB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x06> TCORB16_;
		static  TCORB16_ TCORB16;


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
		typedef tcsr_t<base + 0x02> TCSR_;
		static  TCSR_ TCSR;
	};
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
		typename tmr0246_t<base, per, INT, cmia, cmib, ovi>::TCNT16_ tmr0246_t<base, per, INT, cmia, cmib, ovi>::TCNT16;
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
		typename tmr0246_t<base, per, INT, cmia, cmib, ovi>::TCORA16_ tmr0246_t<base, per, INT, cmia, cmib, ovi>::TCORA16;
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
		typename tmr0246_t<base, per, INT, cmia, cmib, ovi>::TCORB16_ tmr0246_t<base, per, INT, cmia, cmib, ovi>::TCORB16;
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
		typename tmr0246_t<base, per, INT, cmia, cmib, ovi>::TCSR_ tmr0246_t<base, per, INT, cmia, cmib, ovi>::TCSR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  8 ビットタイマ（TMR）奇数版
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	cmia	CMIA 型割り込みベクター
		@param[in]	cmib	CMIB 型割り込みベクター
		@param[in]	ovi		OVI 型割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
	struct tmr1357_t : public tmr_t<base, per, INT, cmia, cmib, ovi> {

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
		typedef tcsr_t<base + 0x02> TCSR_;
		static  TCSR_ TCSR;
	};
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi>
		typename tmr1357_t<base, per, INT, cmia, cmib, ovi>::TCSR_ tmr1357_t<base, per, INT, cmia, cmib, ovi>::TCSR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M)
	typedef tmr0246_t<0x00088200, peripheral::TMR0, ICU::VECTOR_SELB,
		ICU::VECTOR_SELB::CMIA0, ICU::VECTOR_SELB::CMIB0, ICU::VECTOR_SELB::OVI0> TMR0;
	typedef tmr1357_t<0x00088201, peripheral::TMR1, ICU::VECTOR_SELB,
		ICU::VECTOR_SELB::CMIA1, ICU::VECTOR_SELB::CMIB1, ICU::VECTOR_SELB::OVI1> TMR1;
	typedef tmr0246_t<0x00088210, peripheral::TMR2, ICU::VECTOR_SELB,
		ICU::VECTOR_SELB::CMIA2, ICU::VECTOR_SELB::CMIB2, ICU::VECTOR_SELB::OVI2> TMR2;
	typedef tmr1357_t<0x00088211, peripheral::TMR3, ICU::VECTOR_SELB,
		ICU::VECTOR_SELB::CMIA3, ICU::VECTOR_SELB::CMIB3, ICU::VECTOR_SELB::OVI3> TMR3;
#endif

#if defined(SIG_RX24T) || defined(SIG_RX66T)
	typedef tmr0246_t<0x00088200, peripheral::TMR0, ICU::VECTOR,
		ICU::VECTOR::CMIA0, ICU::VECTOR::CMIB0, ICU::VECTOR::OVI0> TMR0;
	typedef tmr1357_t<0x00088201, peripheral::TMR1, ICU::VECTOR,
		ICU::VECTOR::CMIA1, ICU::VECTOR::CMIB1, ICU::VECTOR::OVI1> TMR1;
	typedef tmr0246_t<0x00088210, peripheral::TMR2, ICU::VECTOR,
		ICU::VECTOR::CMIA2, ICU::VECTOR::CMIB2, ICU::VECTOR::OVI2> TMR2;
	typedef tmr1357_t<0x00088211, peripheral::TMR3, ICU::VECTOR,
		ICU::VECTOR::CMIA3, ICU::VECTOR::CMIB3, ICU::VECTOR::OVI3> TMR3;
	typedef tmr0246_t<0x00088220, peripheral::TMR4, ICU::VECTOR,
		ICU::VECTOR::CMIA4, ICU::VECTOR::CMIB4, ICU::VECTOR::OVI4> TMR4;
	typedef tmr1357_t<0x00088221, peripheral::TMR5, ICU::VECTOR,
		ICU::VECTOR::CMIA5, ICU::VECTOR::CMIB5, ICU::VECTOR::OVI5> TMR5;
	typedef tmr0246_t<0x00088230, peripheral::TMR6, ICU::VECTOR,
		ICU::VECTOR::CMIA6, ICU::VECTOR::CMIB6, ICU::VECTOR::OVI6> TMR6;
	typedef tmr1357_t<0x00088231, peripheral::TMR7, ICU::VECTOR,
		ICU::VECTOR::CMIA7, ICU::VECTOR::CMIB7, ICU::VECTOR::OVI7> TMR7;
#endif
}
