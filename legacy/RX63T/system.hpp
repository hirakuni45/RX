#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2017 Kunihito Hiramatsu @n
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
			@brief  SCKCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00080020> sckcr_io;
		struct sckcr_t : public sckcr_io {
			using sckcr_io::operator =;
			using sckcr_io::operator ();
			using sckcr_io::operator |=;
			using sckcr_io::operator &=;

			bits_rw_t<sckcr_io, bitpos::B0, 4>	PCKD;
			bits_rw_t<sckcr_io, bitpos::B4, 4>	PCKC;
			bits_rw_t<sckcr_io, bitpos::B8, 4>	PCKB;
			bits_rw_t<sckcr_io, bitpos::B12, 4>	PCKA;
			bits_rw_t<sckcr_io, bitpos::B16, 4>	BCK;
			bit_rw_t<sckcr_io, bitpos::B23>	    PSTOP1;
			bits_rw_t<sckcr_io, bitpos::B24, 4>	ICK;
			bits_rw_t<sckcr_io, bitpos::B28, 4>	FCK;
		};
		static sckcr_t SCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SCKCR2 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x00080024> sckcr2_io;
		struct sckcr2_t : public sckcr2_io {
			using sckcr2_io::operator =;
			using sckcr2_io::operator ();
			using sckcr2_io::operator |=;
			using sckcr2_io::operator &=;

			bits_rw_t<sckcr2_io, bitpos::B4, 4>	UCK;
		};
		static sckcr2_t SCKCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SCKCR3 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x00080026> sckcr3_io;
		struct sckcr3_t : public sckcr3_io {
			using sckcr3_io::operator =;
			using sckcr3_io::operator ();
			using sckcr3_io::operator |=;
			using sckcr3_io::operator &=;

			bits_rw_t<sckcr3_io, bitpos::B8, 3> CKSEL;
		};
		static sckcr3_t SCKCR3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLLCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x00080028> pllcr_io;
		struct pllcr_t : public pllcr_io {
			using pllcr_io::operator =;
			using pllcr_io::operator ();
			using pllcr_io::operator |=;
			using pllcr_io::operator &=;

			bits_rw_t<pllcr_io, bitpos::B0, 2> PLIDIV;
			bits_rw_t<pllcr_io, bitpos::B8, 6> STC;
		};
		static pllcr_t PLLCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLLCR2 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x0008002a> pllcr2_io;
		struct pllcr2_t : public pllcr2_io {
			using pllcr2_io::operator =;
			using pllcr2_io::operator ();
			using pllcr2_io::operator |=;
			using pllcr2_io::operator &=;

			bit_rw_t<pllcr2_io, bitpos::B0> PLLEN;
		};
		static pllcr2_t PLLCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  BCKCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00080030> bckcr_io;
		struct bckcr_t : public bckcr_io {
			using bckcr_io::operator =;
			using bckcr_io::operator ();
			using bckcr_io::operator |=;
			using bckcr_io::operator &=;

			bit_rw_t<bckcr_io, bitpos::B0> BCLKDIV;
		};
		static bckcr_t BCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MOSCCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00080032> mosccr_io;
		struct mosccr_t : public mosccr_io {
			using mosccr_io::operator =;
			using mosccr_io::operator ();
			using mosccr_io::operator |=;
			using mosccr_io::operator &=;

			bit_rw_t<mosccr_io, bitpos::B0> MOSTP;
		};
		static mosccr_t MOSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  LOCOCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00080034> lococr_io;
		struct lococr_t : public lococr_io {
			using lococr_io::operator =;
			using lococr_io::operator ();
			using lococr_io::operator |=;
			using lococr_io::operator &=;

			bit_rw_t<lococr_io, bitpos::B0> LCSTP;
		};
		static lococr_t LOCOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ILOCOCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00080035> ilococr_io;
		struct ilococr_t : public ilococr_io {
			using ilococr_io::operator =;
			using ilococr_io::operator ();
			using ilococr_io::operator |=;
			using ilococr_io::operator &=;

			bit_rw_t<ilococr_io, bitpos::B0> ILCSTP;
		};
		static ilococr_t ILOCOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  OSTDCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00080040> ostdcr_io;
		struct ostdcr_t : public ostdcr_io {
			using ostdcr_io::operator =;
			using ostdcr_io::operator ();
			using ostdcr_io::operator |=;
			using ostdcr_io::operator &=;

			bit_rw_t<ostdcr_io, bitpos::B0> OSTDIE;
			bit_rw_t<ostdcr_io, bitpos::B7> OSTDE;
		};
		static ostdcr_t OSTDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  OSTDSR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00080041> ostdsr_io;
		struct ostdsr_t : public ostdsr_io {
			using ostdsr_io::operator =;
			using ostdsr_io::operator ();
			using ostdsr_io::operator |=;
			using ostdsr_io::operator &=;

			bit_rw_t<ostdsr_io, bitpos::B0> OSTDF;
		};
		static ostdsr_t OSTDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MOFCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x0008c293> mofcr_io;
		struct mofcr_t : public mofcr_io {
			using mofcr_io::operator =;
			using mofcr_io::operator ();
			using mofcr_io::operator |=;
			using mofcr_io::operator &=;

			bit_rw_t<mofcr_io, bitpos::B0> MOFXIN;
		};
		static mofcr_t MOFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SBYCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x0008000c> sbycr_io;
		struct sbycr_t : public sbycr_io {
			using sbycr_io::operator =;
			using sbycr_io::operator ();
			using sbycr_io::operator |=;
			using sbycr_io::operator &=;

			bit_rw_t<sbycr_io, bitpos::B14>	OPE;
			bit_rw_t<sbycr_io, bitpos::B15>	SSBY;
		};
		static sbycr_t SBYCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MSTPCRA レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00080010> mstpcra_io;
		struct mstpcra_t : public mstpcra_io {
			using mstpcra_io::operator =;
			using mstpcra_io::operator ();
			using mstpcra_io::operator |=;
			using mstpcra_io::operator &=;

			bit_rw_t<mstpcra_io, bitpos::B6>	MSTPA6;
			bit_rw_t<mstpcra_io, bitpos::B7>	MSTPA7;
			bit_rw_t<mstpcra_io, bitpos::B9>	MSTPA9;
			bit_rw_t<mstpcra_io, bitpos::B14>	MSTPA14;
			bit_rw_t<mstpcra_io, bitpos::B15>	MSTPA15;
			bit_rw_t<mstpcra_io, bitpos::B16>	MSTPA16;
			bit_rw_t<mstpcra_io, bitpos::B17>	MSTPA17;
			bit_rw_t<mstpcra_io, bitpos::B19>	MSTPA19;
			bit_rw_t<mstpcra_io, bitpos::B24>	MSTPA24;
			bit_rw_t<mstpcra_io, bitpos::B27>	MSTPA27;
			bit_rw_t<mstpcra_io, bitpos::B28>	MSTPA28;
			bit_rw_t<mstpcra_io, bitpos::B29>	MSTPA29;
			bit_rw_t<mstpcra_io, bitpos::B31>	ACSE;
		};
		static mstpcra_t MSTPCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MSTPCRB レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00080014> mstpcrb_io;
		struct mstpcrb_t : public mstpcrb_io {
			using mstpcrb_io::operator =;
			using mstpcrb_io::operator ();
			using mstpcrb_io::operator |=;
			using mstpcrb_io::operator &=;

			bit_rw_t<mstpcrb_io, bitpos::B1>	MSTPB1;
			bit_rw_t<mstpcrb_io, bitpos::B4>	MSTPB4;
			bit_rw_t<mstpcrb_io, bitpos::B6>	MSTPB6;
			bit_rw_t<mstpcrb_io, bitpos::B16>	MSTPB16;
			bit_rw_t<mstpcrb_io, bitpos::B17>	MSTPB17;
			bit_rw_t<mstpcrb_io, bitpos::B19>	MSTPB19;
			bit_rw_t<mstpcrb_io, bitpos::B20>	MSTPB20;
			bit_rw_t<mstpcrb_io, bitpos::B21>	MSTPB21;
			bit_rw_t<mstpcrb_io, bitpos::B23>	MSTPB23;
			bit_rw_t<mstpcrb_io, bitpos::B28>	MSTPB28;
			bit_rw_t<mstpcrb_io, bitpos::B29>	MSTPB29;
			bit_rw_t<mstpcrb_io, bitpos::B30>	MSTPB30;
			bit_rw_t<mstpcrb_io, bitpos::B31>	MSTPB31;
		};
		static mstpcrb_t MSTPCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MSTPCRC レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00080018> mstpcrc_io;
		struct mstpcrc_t : public mstpcrc_io {
			using mstpcrc_io::operator =;
			using mstpcrc_io::operator ();
			using mstpcrc_io::operator |=;
			using mstpcrc_io::operator &=;

			bit_rw_t<mstpcrc_io, bitpos::B0>	MSTPC0;
			bit_rw_t<mstpcrc_io, bitpos::B19>	MSTPC19;
		};
		static mstpcrc_t MSTPCRC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PRCR レジスタ（プロテクト）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x000803fe> prcr_io;
		struct prcr_t : public prcr_io {
			using prcr_io::operator =;
			using prcr_io::operator ();
			using prcr_io::operator |=;
			using prcr_io::operator &=;

			bit_rw_t<prcr_io, bitpos::B0>	PRC0;
			bit_rw_t<prcr_io, bitpos::B1>	PRC1;
			bit_rw_t<prcr_io, bitpos::B3>	PRC3;
			bits_rw_t<prcr_io, bitpos::B8, 8>	PRKEY;
		};
		static prcr_t PRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器ウェイトコントロールレジスタ (MOSCWTCR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x000800a2> moscwtcr_io;
		struct moscwtcr_t : public moscwtcr_io {
			using moscwtcr_io::operator =;
			using moscwtcr_io::operator ();
			using moscwtcr_io::operator |=;
			using moscwtcr_io::operator &=;

			bits_rw_t<moscwtcr_io, bitpos::B0, 5> MSTS;
		};
		static moscwtcr_t MOSCWTCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL ウェイトコントロールレジスタ (PLLWTCR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x000800a6> pllwtcr_io;
		struct pllwtcr_t : public pllwtcr_io {
			using pllwtcr_io::operator =;
			using pllwtcr_io::operator ();
			using pllwtcr_io::operator |=;
			using pllwtcr_io::operator &=;

			bits_rw_t<pllwtcr_io, bitpos::B0, 5> PSTS;
		};
		static pllwtcr_t PLLWTCR;

	};

	typedef system_t SYSTEM;
}
