#pragma once
//=====================================================================//
/*!	@file
	@brief	RX621/RX62N グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ（SCKCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sckcr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8,  4> PCK;
			bits_rw_t<io_, bitpos::B16, 4> BCK;
			bit_rw_t <io_, bitpos::B22>    PSTOP0;
			bit_rw_t <io_, bitpos::B23>    PSTOP1;
			bits_rw_t<io_, bitpos::B24, 4> ICK;
		};
		static sckcr_t<0x00080020> SCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バスクロックコントロールレジスタ（BCKCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct bckcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> BCLKDIV;
		};
		static bckcr_t<0x00080030> BCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振停止検出ステータスレジスタ（OSTDSR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ostdsr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B6>     OSTDF;
			bit_rw_t <io_, bitpos::B7>     OSTDE;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		static ostdsr_t<0x00080040> OSTDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（ SUBOSCCR ）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct subosccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>   SUBSTOP;
		};
		static subosccr_t<0x0008C28A> SUBOSCCR;


//-----------------------------------------------------------------------------//


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スタンバイコントロールレジスタ（SBYCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct sbycr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 5>  STS;
			bit_rw_t <io_, bitpos::B14>	   OPE;
			bit_rw_t <io_, bitpos::B15>	   SSBY;
		};
		static sbycr_t<0x0008000C> SBYCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ A（MSTPCRA）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mstpcra_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>	MSTPA4;
			bit_rw_t<io_, bitpos::B5>	MSTPA5;

			bit_rw_t<io_, bitpos::B8>	MSTPA8;
			bit_rw_t<io_, bitpos::B9>	MSTPA9;
			bit_rw_t<io_, bitpos::B10>	MSTPA10;
			bit_rw_t<io_, bitpos::B11>	MSTPA11;

			bit_rw_t<io_, bitpos::B14>	MSTPA14;
			bit_rw_t<io_, bitpos::B15>	MSTPA15;

			bit_rw_t<io_, bitpos::B17>	MSTPA17;

			bit_rw_t<io_, bitpos::B19>	MSTPA19;

			bit_rw_t<io_, bitpos::B22>	MSTPA22;
			bit_rw_t<io_, bitpos::B23>	MSTPA23;

			bit_rw_t<io_, bitpos::B28>	MSTPA28;
			bit_rw_t<io_, bitpos::B29>	MSTPA29;

			bit_rw_t<io_, bitpos::B31>	ACSE;
		};
		static mstpcra_t<0x00080010> MSTPCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ B（MSTPCRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mstpcrb_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>	MSTPB0;

			bit_rw_t<io_, bitpos::B15>	MSTPB15;

			bit_rw_t<io_, bitpos::B16>	MSTPB16;
			bit_rw_t<io_, bitpos::B17>	MSTPB17;
			bit_rw_t<io_, bitpos::B18>	MSTPB18;
			bit_rw_t<io_, bitpos::B19>	MSTPB19;
			bit_rw_t<io_, bitpos::B20>	MSTPB20;
			bit_rw_t<io_, bitpos::B21>	MSTPB21;

			bit_rw_t<io_, bitpos::B23>	MSTPB23;

			bit_rw_t<io_, bitpos::B25>	MSTPB25;
			bit_rw_t<io_, bitpos::B26>	MSTPB26;

			bit_rw_t<io_, bitpos::B28>	MSTPB28;
			bit_rw_t<io_, bitpos::B29>	MSTPB29;
			bit_rw_t<io_, bitpos::B30>	MSTPB30;
			bit_rw_t<io_, bitpos::B31>	MSTPB31;
		};
		static mstpcrb_t<0x00080014> MSTPCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ C（MSTPCRC）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mstpcrc_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>	MSTPC0;
			bit_rw_t<io_, bitpos::B1>	MSTPC1;
		};
		static mstpcrc_t<0x00080018> MSTPCRC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイコントロールレジスタ（DPSBYCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsbycr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  RAMCUT0;

			bit_rw_t<io_, bitpos::B4>  RAMCUT1;
			bit_rw_t<io_, bitpos::B5>  RAMCUT2;
			bit_rw_t<io_, bitpos::B6>  IOKEEP;
			bit_rw_t<io_, bitpos::B7>  DPSBY;
		};
		static dpsbycr_t<0x0008C280> DPSBYCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイウェイトコントロールレジスタ（ DPSWCR ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpswcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  WTSTS;
		};
		static dpswcr_t<0x0008C281> DPSWCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイインタラプトイネーブルレジスタ（ DPSIER ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsier_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DIRQ0E;
			bit_rw_t<io_, bitpos::B1>  DIRQ1E;
			bit_rw_t<io_, bitpos::B2>  DIRQ2E;
			bit_rw_t<io_, bitpos::B3>  DIRQ3E;
			bit_rw_t<io_, bitpos::B4>  DLVDE;
			bit_rw_t<io_, bitpos::B5>  DRTCE;
			bit_rw_t<io_, bitpos::B6>  DUSBE;
			bit_rw_t<io_, bitpos::B7>  DNMIE;
		};
		static dpsier_t<0x0008C282> DPSIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイインタラプトフラグレジスタ（ DPSIFR ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsifr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DIRQ0F;
			bit_rw_t<io_, bitpos::B1>  DIRQ1F;
			bit_rw_t<io_, bitpos::B2>  DIRQ2F;
			bit_rw_t<io_, bitpos::B3>  DIRQ3F;
			bit_rw_t<io_, bitpos::B4>  DLVDF;
			bit_rw_t<io_, bitpos::B5>  DRTCF;
			bit_rw_t<io_, bitpos::B6>  DUSBF;
			bit_rw_t<io_, bitpos::B7>  DNMIF;
		};
		static dpsifr_t<0x0008C283> DPSIFR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイインタラプトエッジレジスタ（ DPSIEGR ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsiegr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DIRQ0EG;
			bit_rw_t<io_, bitpos::B1>  DIRQ1EG;
			bit_rw_t<io_, bitpos::B2>  DIRQ2EG;
			bit_rw_t<io_, bitpos::B3>  DIRQ3EG;

			bit_rw_t<io_, bitpos::B7>  DNMIEG;
		};
		static dpsiegr_t<0x0008C284> DPSIEGR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ（ RSTSR ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct rstsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  PORF;
			bit_rw_t<io_, bitpos::B1>  LVD1F;
			bit_rw_t<io_, bitpos::B2>  LVD2F;

			bit_rw_t<io_, bitpos::B7>  DPSRSTF;
		};
		static rstsr_t<0x0008C285> RSTSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイバックアップレジスタ（ DPSBKRy ）（ y = 0 ～ 31 ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<0x0008C290>  DPSBKR0;
		static rw8_t<0x0008C291>  DPSBKR1;
		static rw8_t<0x0008C292>  DPSBKR2;
		static rw8_t<0x0008C293>  DPSBKR3;
		static rw8_t<0x0008C294>  DPSBKR4;
		static rw8_t<0x0008C295>  DPSBKR5;
		static rw8_t<0x0008C296>  DPSBKR6;
		static rw8_t<0x0008C297>  DPSBKR7;
		static rw8_t<0x0008C298>  DPSBKR8;
		static rw8_t<0x0008C299>  DPSBKR9;
		static rw8_t<0x0008C29A>  DPSBKR10;
		static rw8_t<0x0008C29B>  DPSBKR11;
		static rw8_t<0x0008C29C>  DPSBKR12;
		static rw8_t<0x0008C29D>  DPSBKR13;
		static rw8_t<0x0008C29E>  DPSBKR14;
		static rw8_t<0x0008C29F>  DPSBKR15;
		static rw8_t<0x0008C2A0>  DPSBKR16;
		static rw8_t<0x0008C2A1>  DPSBKR17;
		static rw8_t<0x0008C2A2>  DPSBKR18;
		static rw8_t<0x0008C2A3>  DPSBKR19;
		static rw8_t<0x0008C2A4>  DPSBKR20;
		static rw8_t<0x0008C2A5>  DPSBKR21;
		static rw8_t<0x0008C2A6>  DPSBKR22;
		static rw8_t<0x0008C2A7>  DPSBKR23;
		static rw8_t<0x0008C2A8>  DPSBKR24;
		static rw8_t<0x0008C2A9>  DPSBKR25;
		static rw8_t<0x0008C2AA>  DPSBKR26;
		static rw8_t<0x0008C2AB>  DPSBKR27;
		static rw8_t<0x0008C2AC>  DPSBKR28;
		static rw8_t<0x0008C2AD>  DPSBKR29;
		static rw8_t<0x0008C2AE>  DPSBKR30;
		static rw8_t<0x0008C2AF>  DPSBKR31;
}
