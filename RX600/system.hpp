#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
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
			@brief  エンディアン選択レジスタ（MDE）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mde_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 3> MDE;
		};
		static mde_t<0x00120064> MDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードモニタレジスタ（MDMONR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mdmonr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  MD;
		};
		static mdmonr_t<0x00080000> MDMONR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードステータスレジスタ（MDSR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mdsr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B5>  UBTS;
		};
		static mdsr_t<0x00080002> MDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムコントロールレジスタ 0（SYSCR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct syscr0_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ROME;
			bit_rw_t <io_, bitpos::B1>     EXBE;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		static syscr0_t<0x00080006> SYSCR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムコントロールレジスタ 1（SYSCR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct syscr1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  RAME;
			bit_rw_t<io_, bitpos::B6>  ECCRAME;
			bit_rw_t<io_, bitpos::B7>  SBYRAME;
		};
		static syscr1_t<0x00080008> SYSCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ（SCKCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sckcr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4> PCKD;
			bits_rw_t<io_, bitpos::B4,  4> PCKC;
			bits_rw_t<io_, bitpos::B8,  4> PCKB;
			bits_rw_t<io_, bitpos::B12, 4> PCKA;
			bits_rw_t<io_, bitpos::B16, 4> BCK;
			bit_rw_t <io_, bitpos::B22>    PSTOP0;
			bit_rw_t <io_, bitpos::B23>    PSTOP1;
			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		static sckcr_t<0x00080020> SCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct memwait_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MEMWAIT;
		};
		static memwait_t<0x00086610> MEMWAIT;


#if defined(SIG_RX65N)
  		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romwt_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> ROMWT;
		};
		static romwt_t<0x0008101C> ROMWT;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ 2（SCKCR2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sckcr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B4, 4> UCK;
		};
		static sckcr2_t<0x00080024> SCKCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ 3（SCKCR3）
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
			@brief  PLL コントロールレジスタ（PLLCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x00080028> pllcr_io;
		struct pllcr_t : public pllcr_io {
			using pllcr_io::operator =;
			using pllcr_io::operator ();
			using pllcr_io::operator |=;
			using pllcr_io::operator &=;

			bits_rw_t<pllcr_io, bitpos::B0, 2> PLIDIV;
			bit_rw_t <pllcr_io, bitpos::B4>    PLLSRCSEL;
			bits_rw_t<pllcr_io, bitpos::B8, 6> STC;
		};
		static pllcr_t PLLCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL コントロールレジスタ 2（PLLCR2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x0008002A> pllcr2_io;
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
			@brief  外部バスクロックコントロールレジスタ（BCKCR）
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
			@brief  メインクロック発振器コントロールレジスタ（MOSCCR）
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
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00080033> sosccr_io;
		struct sosccr_t : public sosccr_io {
			using sosccr_io::operator =;
			using sosccr_io::operator ();
			using sosccr_io::operator |=;
			using sosccr_io::operator &=;

			bit_rw_t<sosccr_io, bitpos::B0> SOSTP;
		};
		static sosccr_t SOSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  低速オンチップオシレータコントロールレジスタ（LOCOCR）
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
			@brief  IWDT 専用オンチップオシレータコントロールレジスタ（ILOCOCR）
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
			@brief  高速オンチップオシレータコントロールレジスタ（HOCOCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00080036> hococr_io;
		struct hococr_t : public hococr_io {
			using hococr_io::operator =;
			using hococr_io::operator ();
			using hococr_io::operator |=;
			using hococr_io::operator &=;

			bit_rw_t<hococr_io, bitpos::B0> HCSTP;
		};
		static hococr_t HOCOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	高速オンチップオシレータコントロールレジスタ 2（HOCOCR2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00080037> hococr2_io;
		struct hococr2_t : public hococr2_io {
			using hococr2_io::operator =;
			using hococr2_io::operator ();
			using hococr2_io::operator |=;
			using hococr2_io::operator &=;

			bits_rw_t<hococr2_io, bitpos::B0, 2> HCFRQ;
		};
		static hococr2_t HOCOCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振安定フラグレジスタ（OSCOVFSR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x0008003C> oscovfsr_io;
		struct oscovfsr_t : public oscovfsr_io {
			using oscovfsr_io::operator =;
			using oscovfsr_io::operator ();
			using oscovfsr_io::operator |=;
			using oscovfsr_io::operator &=;

			bit_rw_t<oscovfsr_io, bitpos::B0> MOOVF;
			bit_rw_t<oscovfsr_io, bitpos::B1> SOOVF;
			bit_rw_t<oscovfsr_io, bitpos::B2> PLOVF;
			bit_rw_t<oscovfsr_io, bitpos::B3> HCOVF;
			bit_rw_t<oscovfsr_io, bitpos::B4> ILCOVF;
		};
		static oscovfsr_t OSCOVFSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振停止検出コントロールレジスタ（OSTDCR）
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
			@brief  発振停止検出ステータスレジスタ（OSTDSR）
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
			@brief  メインクロック発振器ウェイトコントロールレジスタ（MOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<0x000800A2> MOSCWTCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<0x000800A3> SOSCWTCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器強制発振コントロールレジスタ（MOFCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mofcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>      MOFXIN;
			bits_rw_t<io_, bitpos::B4, 2>  MODRV2;
			bit_rw_t<io_, bitpos::B6>      MOSEL;
		};
		static mofcr_t<0x0008C293> MOFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  高速オンチップオシレータ電源コントロールレジスタ（HOCOPCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x0008C294> hocopcr_io;
		struct hocopcr_t : public hocopcr_io {
			using hocopcr_io::operator =;
			using hocopcr_io::operator ();
			using hocopcr_io::operator |=;
			using hocopcr_io::operator &=;

			bit_rw_t<hocopcr_io, bitpos::B0>	HOCOPCNT;
		};
		static hocopcr_t HOCOPCR;

//-----------------------------------------------------------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スタンバイコントロールレジスタ（SBYCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x0008000C> sbycr_io;
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
			@brief  モジュールストップコントロールレジスタ A（MSTPCRA）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00080010> mstpcra_io;
		struct mstpcra_t : public mstpcra_io {
			using mstpcra_io::operator =;
			using mstpcra_io::operator ();
			using mstpcra_io::operator |=;
			using mstpcra_io::operator &=;

			bit_rw_t<mstpcra_io, bitpos::B0>	MSTPA0;
			bit_rw_t<mstpcra_io, bitpos::B1>	MSTPA1;

			bit_rw_t<mstpcra_io, bitpos::B4>	MSTPA4;
			bit_rw_t<mstpcra_io, bitpos::B5>	MSTPA5;

			bit_rw_t<mstpcra_io, bitpos::B7>	MSTPA7;

			bit_rw_t<mstpcra_io, bitpos::B9>	MSTPA9;
			bit_rw_t<mstpcra_io, bitpos::B10>	MSTPA10;
			bit_rw_t<mstpcra_io, bitpos::B11>	MSTPA11;

			bit_rw_t<mstpcra_io, bitpos::B13>	MSTPA13;
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
			@brief  モジュールストップコントロールレジスタ B（MSTPCRB）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00080014> mstpcrb_io;
		struct mstpcrb_t : public mstpcrb_io {
			using mstpcrb_io::operator =;
			using mstpcrb_io::operator ();
			using mstpcrb_io::operator |=;
			using mstpcrb_io::operator &=;

			bit_rw_t<mstpcrb_io, bitpos::B0>	MSTPB0;
			bit_rw_t<mstpcrb_io, bitpos::B1>	MSTPB1;
			bit_rw_t<mstpcrb_io, bitpos::B2>	MSTPB2;

			bit_rw_t<mstpcrb_io, bitpos::B4>	MSTPB4;

			bit_rw_t<mstpcrb_io, bitpos::B6>	MSTPB6;

			bit_rw_t<mstpcrb_io, bitpos::B8>	MSTPB8;
			bit_rw_t<mstpcrb_io, bitpos::B9>	MSTPB9;

			bit_rw_t<mstpcrb_io, bitpos::B12>	MSTPB12;

			bit_rw_t<mstpcrb_io, bitpos::B14>	MSTPB14;
			bit_rw_t<mstpcrb_io, bitpos::B15>	MSTPB15;

			bit_rw_t<mstpcrb_io, bitpos::B17>	MSTPB17;

			bit_rw_t<mstpcrb_io, bitpos::B19>	MSTPB19;

			bit_rw_t<mstpcrb_io, bitpos::B21>	MSTPB21;
			bit_rw_t<mstpcrb_io, bitpos::B22>	MSTPB22;
			bit_rw_t<mstpcrb_io, bitpos::B23>	MSTPB23;
			bit_rw_t<mstpcrb_io, bitpos::B24>	MSTPB24;
			bit_rw_t<mstpcrb_io, bitpos::B25>	MSTPB25;
			bit_rw_t<mstpcrb_io, bitpos::B26>	MSTPB26;
			bit_rw_t<mstpcrb_io, bitpos::B27>	MSTPB27;
			bit_rw_t<mstpcrb_io, bitpos::B28>	MSTPB28;
			bit_rw_t<mstpcrb_io, bitpos::B29>	MSTPB29;
			bit_rw_t<mstpcrb_io, bitpos::B30>	MSTPB30;
			bit_rw_t<mstpcrb_io, bitpos::B31>	MSTPB31;
		};
		static mstpcrb_t MSTPCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ C（MSTPCRC）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00080018> mstpcrc_io;
		struct mstpcrc_t : public mstpcrc_io {
			using mstpcrc_io::operator =;
			using mstpcrc_io::operator ();
			using mstpcrc_io::operator |=;
			using mstpcrc_io::operator &=;

			bit_rw_t<mstpcrc_io, bitpos::B0>	MSTPC0;

			bit_rw_t<mstpcrc_io, bitpos::B6>	MSTPC6;
			bit_rw_t<mstpcrc_io, bitpos::B7>	MSTPC7;

			bit_rw_t<mstpcrc_io, bitpos::B17>	MSTPC17;

			bit_rw_t<mstpcrc_io, bitpos::B19>	MSTPC19;

			bit_rw_t<mstpcrc_io, bitpos::B23>	MSTPC23;
			bit_rw_t<mstpcrc_io, bitpos::B24>	MSTPC24;
			bit_rw_t<mstpcrc_io, bitpos::B25>	MSTPC25;
			bit_rw_t<mstpcrc_io, bitpos::B26>	MSTPC26;
			bit_rw_t<mstpcrc_io, bitpos::B27>	MSTPC27;
		};
		static mstpcrc_t MSTPCRC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ D（MSTPCRD）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x0008001C> mstpcrd_io;
		struct mstpcrd_t : public mstpcrd_io {
			using mstpcrd_io::operator =;
			using mstpcrd_io::operator ();
			using mstpcrd_io::operator |=;
			using mstpcrd_io::operator &=;

			bit_rw_t<mstpcrd_io, bitpos::B0>	MSTPD0;
			bit_rw_t<mstpcrd_io, bitpos::B1>	MSTPD1;
			bit_rw_t<mstpcrd_io, bitpos::B2>	MSTPD2;
			bit_rw_t<mstpcrd_io, bitpos::B3>	MSTPD3;
			bit_rw_t<mstpcrd_io, bitpos::B4>	MSTPD4;
			bit_rw_t<mstpcrd_io, bitpos::B5>	MSTPD5;
			bit_rw_t<mstpcrd_io, bitpos::B6>	MSTPD6;
			bit_rw_t<mstpcrd_io, bitpos::B7>	MSTPD7;

			bit_rw_t<mstpcrd_io, bitpos::B14>	MSTPD14;
			bit_rw_t<mstpcrd_io, bitpos::B15>	MSTPD15;

			bit_rw_t<mstpcrd_io, bitpos::B19>	MSTPD19;

			bit_rw_t<mstpcrd_io, bitpos::B21>	MSTPD21;

			bit_rw_t<mstpcrd_io, bitpos::B23>	MSTPD23;
		};
		static mstpcrd_t MSTPCRD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作電力コントロールレジスタ（OPCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x000800A0> opccr_io;
		struct opccr_t : public opccr_io {
			using opccr_io::operator =;
			using opccr_io::operator ();
			using opccr_io::operator |=;
			using opccr_io::operator &=;

			bits_rw_t<opccr_io, bitpos::B0, 3>	OPCM;
			bit_rw_t <opccr_io, bitpos::B4>		OPCMTSF;
		};
		static opccr_t OPCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スリープモード復帰クロックソース切り替えレジスタ（RSTCKCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x000800A1> rstckcr_io;
		struct rstckcr_t : public rstckcr_io {
			using rstckcr_io::operator =;
			using rstckcr_io::operator ();
			using rstckcr_io::operator |=;
			using rstckcr_io::operator &=;

			bits_rw_t<rstckcr_io, bitpos::B0, 3>	RSTCKSEL;
			bit_rw_t <rstckcr_io, bitpos::B4>		RSTCKEN;
		};
		static rstckcr_t RSTCKCR;


//-----------------------------------------------------------------------------//


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

			bits_rw_t<io_, bitpos::B0, 2>  DEEPCUT;
			bit_rw_t <io_, bitpos::B6>	   IOKEEP;
			bit_rw_t <io_, bitpos::B7>	   DPSBY;
		};
		static dpsbycr_t<0x0008C280> DPSBYCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  プロテクトレジスタ（PRCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct prcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>	   PRC0;
			bit_rw_t<io_, bitpos::B1>	   PRC1;
			bit_rw_t<io_, bitpos::B3>      PRC3;
			bits_rw_t<io_, bitpos::B8, 8>  PRKEY;
		};
		static prcr_t<0x000803FE> PRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサコントロールレジスタ（TSCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tscr_t : public  rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>	TSOE;
			bit_rw_t<io_, bitpos::B7>	TSEN;
		};
		static tscr_t<0x0008C500> TSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 0（RSTSR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstsr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  PORF;
			bit_rw_t <io_, bitpos::B1>  LVD0RF;
			bit_rw_t <io_, bitpos::B2>  LVD1RF;
			bit_rw_t <io_, bitpos::B3>  LVD2RF;

			bit_rw_t <io_, bitpos::B7>  DPSRSTF;
		};
		static rstsr0_t<0x0008C290> RSTSR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 1（RSTSR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstsr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CWSF;
		};
		static rstsr1_t<0x0008C291> RSTSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 2（RSTSR2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstsr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  IWDTRF;
			bit_rw_t <io_, bitpos::B1>  WDTRF;
			bit_rw_t <io_, bitpos::B2>  SWRF;
		};
		static rstsr2_t<0x000800C0> RSTSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ソフトウェアリセットレジスタ（SWRR）@n
					0xA501 を書き込むとリセットされます。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw16_t<0x000800C2> SWRR;
	};
	typedef system_t SYSTEM;

	rw8_t<0x000800A2>   		  system_t::MOSCWTCR;
	system_t::mofcr_t<0x0008C293> system_t::MOFCR;
	system_t::sckcr_t<0x00080020> system_t::SCKCR;
	system_t::prcr_t<0x000803FE>  system_t::PRCR;
}
