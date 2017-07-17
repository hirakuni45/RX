#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・システム定義
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
		@brief  システム定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  システムクロックコントロールレジスタ（SCKCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sckcr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4> PCKD;
			bits_rw_t<io_, bitpos::B8,  4> PCKB;
			bits_rw_t<io_, bitpos::B12, 4> PCKA;
			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		static sckcr_t<0x00080020> SCKCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  システムクロックコントロールレジスタ 3（SCKCR3）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sckcr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 3> CKSEL;
		};
		static sckcr3_t<0x00080026> SCKCR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL コントロールレジスタ（PLLCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pllcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> PLIDIV;
			bits_rw_t<io_, bitpos::B8, 6> STC;
		};
		static pllcr_t<0x00080028> PLLCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL コントロールレジスタ 2（PLLCR2）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pllcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PLLEN;
		};
		static pllcr2_t<0x0008002A> PLLCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  メインクロック発振器コントロールレジスタ（MOSCCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mosccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MOSTP;
		};
		static mosccr_t<0x00080032> MOSCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  低速オンチップオシレータコントロールレジスタ（LOCOCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lococr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> LCSTP;
		};
		static lococr_t<0x00080034> LOCOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  IWDT 専用オンチップオシレータコントロールレジスタ（ILOCOCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ilococr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ILCSTP;
		};
		static ilococr_t<0x00080035> ILOCOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振安定フラグレジスタ（OSCOVFSR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct oscovfsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t<ro8_t<base>, bitpos::B0> MOOVF;
			bit_ro_t<ro8_t<base>, bitpos::B2> PLOVF;
		};
		static oscovfsr_t<0x0008003C> OSCOVFSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振停止検出コントロールレジスタ（OSTDCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ostdcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OSTDIE;
			bit_rw_t<io_, bitpos::B7> OSTDE;
		};
		static ostdcr_t<0x00080040> OSTDCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振停止検出ステータスレジスタ（OSTDSR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ostdsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OSTDF;
		};
		static ostdsr_t<0x00080041> OSTDSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  メインクロック発振器ウェイトコントロールレジスタ（MOSCWTCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct moscwtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> MSTS;
		};
		static moscwtcr_t<0x000800A2> MOSCWTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	メインクロック発振器強制発振コントロールレジスタ（MOFCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mofcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B5> MODRV21;
			bit_rw_t<io_, bitpos::B6> MOSEL;
		};
		static mofcr_t<0x0008C293> MOFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<0x00080031> MEMWAIT;


		//-----------------------------------------------------------------//
		/*!
			@brief  スタンバイコントロールレジスタ（SBYCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sbycr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B15>	SSBY;
		};
		static sbycr_t<0x0008000C> SBYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ A（MSTPCRA）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcra_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>  MSTPA2;
			bit_rw_t<io_, bitpos::B3>  MSTPA3;
			bit_rw_t<io_, bitpos::B4>  MSTPA4;
			bit_rw_t<io_, bitpos::B5>  MSTPA5;

			bit_rw_t<io_, bitpos::B9>  MSTPA9;

			bit_rw_t<io_, bitpos::B14> MSTPA14;
			bit_rw_t<io_, bitpos::B15> MSTPA15;
			bit_rw_t<io_, bitpos::B16> MSTPA16;
			bit_rw_t<io_, bitpos::B17> MSTPA17;

			bit_rw_t<io_, bitpos::B19> MSTPA19;

			bit_rw_t<io_, bitpos::B23> MSTPA23;

			bit_rw_t<io_, bitpos::B28> MSTPA28;
		};
		static mstpcra_t<0x00080010> MSTPCRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ B（MSTPCRB）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcrb_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6>  MSTPB6;

			bit_rw_t<io_, bitpos::B10> MSTPB10;

			bit_rw_t<io_, bitpos::B17> MSTPB17;

			bit_rw_t<io_, bitpos::B21> MSTPB21;

			bit_rw_t<io_, bitpos::B23> MSTPB23;

			bit_rw_t<io_, bitpos::B25> MSTPB25;
			bit_rw_t<io_, bitpos::B26> MSTPB26;

			bit_rw_t<io_, bitpos::B30> MSTPB30;
		};
		static mstpcrb_t<0x00080014> MSTPCRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ C（MSTPCRC）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcrc_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6>  MSTPC0;

			bit_rw_t<io_, bitpos::B19> MSTPC19;

			bit_rw_t<io_, bitpos::B31> DSLPE;
		};
		static mstpcrb_t<0x00080018> MSTPCRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  動作電力コントロールレジスタ（OPCCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct opccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> OPCM;

			bit_rw_t <io_, bitpos::B4>    OPCMTSF;
		};
		static opccr_t<0x000800A0> OPCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プロテクトレジスタ（PRCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct prcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    PRC0;
			bit_rw_t <io_, bitpos::B1>    PRC1;
			bit_rw_t <io_, bitpos::B3>    PRC3;
			bits_rw_t<io_, bitpos::B8, 8> PRKEY;
		};
		static prcr_t<0x000803FE> PRCR;
	};

	typedef system_t SYSTEM;
}
