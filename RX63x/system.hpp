#pragma once
//=====================================================================//
/*!	@file
	@brief	RX631/RX63N グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
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
	template<class _>
	struct system_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  システムクロックコントロールレジスタ（SCKCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sckcr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4> PCKD_;
			bits_rw_t<io_, bitpos::B4,  4> PCKC_;
			bits_rw_t<io_, bitpos::B8,  4> PCKB;
			bits_rw_t<io_, bitpos::B12, 4> PCKA;
			bits_rw_t<io_, bitpos::B16, 4> BCK;

			bit_rw_t <io_, bitpos::B22>    PSTOP0;
			bit_rw_t <io_, bitpos::B23>    PSTOP1;
			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		typedef sckcr_t<0x0008'0020> SCKCR_;
		static SCKCR_ SCKCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  システムクロックコントロールレジスタ 2（SCKCR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sckcr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> IEBCK;
			bits_rw_t<io_, bitpos::B4, 4> UCK;
		};
		typedef sckcr2_t<0x0008'0024> SCKCR2_;
		static SCKCR2_ SCKCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  システムクロックコントロールレジスタ 3（SCKCR3）
			@param[in]	base	ベースアドレス
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
		typedef sckcr3_t<0x0008'0026> SCKCR3_;
		static SCKCR3_ SCKCR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL コントロールレジスタ（PLLCR）
			@param[in]	base	ベースアドレス
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
		typedef pllcr_t<0x0008'0028> PLLCR_;
		static PLLCR_ PLLCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL コントロールレジスタ 2（PLLCR2）
			@param[in]	base	ベースアドレス
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
		typedef pllcr2_t<0x0008'002A> PLLCR2_;
		static PLLCR2_ PLLCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  外部バスクロックコントロールレジスタ（BCKCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct bckcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PLLEN;
		};
		typedef bckcr_t<0x0008'0030> BCKCR_;
		static BCKCR_ BCKCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  メインクロック発振器コントロールレジスタ（MOSCCR）
			@param[in]	base	ベースアドレス
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
		typedef mosccr_t<0x0008'0032> MOSCCR_;
		static MOSCCR_ MOSCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sosccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SOSTP;
		};
		typedef sosccr_t<0x0008'0033> SOSCCR_;
		static SOSCCR_ SOSCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  低速オンチップオシレータコントロールレジスタ（LOCOCR）
			@param[in]	base	ベースアドレス
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
		typedef lococr_t<0x0008'0034> LOCOCR_;
		static LOCOCR_ LOCOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  IWDT 専用オンチップオシレータコントロールレジスタ（ILOCOCR）
			@param[in]	base	ベースアドレス
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
		typedef ilococr_t<0x0008'0035> ILOCOCR_;
		static ILOCOCR_ ILOCOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  高速オンチップオシレータコントロールレジスタ（HOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hococr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> HCSTP;
		};
		typedef hococr_t<0x0008'0036> HOCOCR_;
		static HOCOCR_ HOCOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振停止検出コントロールレジスタ（OSTDCR）
			@param[in]	base	ベースアドレス
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
		typedef ostdcr_t<0x0008'0040> OSTDCR_;
		static OSTDCR_ OSTDCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振停止検出ステータスレジスタ（OSTDSR）
			@param[in]	base	ベースアドレス
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
		typedef ostdsr_t<0x0008'0041> OSTDSR_;
		static OSTDSR_ OSTDSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	メインクロック発振器強制発振コントロールレジスタ（MOFCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mofcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MOFXIN;
		};
		typedef mofcr_t<0x0008'C293> MOFCR_;
		static MOFCR_ MOFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	高速オンチップオシレータ電源コントロールレジスタ（HOCOPCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hocopcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> HOCOPCNT;
		};
		typedef hocopcr_t<0x0008'C294> HOCOPCR_;
		static HOCOPCR_ HOCOPCR;


		//----  消費電力低減機能  ---------------------------------------------//

		//-----------------------------------------------------------------//
		/*!
			@brief  スタンバイコントロールレジスタ（SBYCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sbycr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B14>	OPE;
			bit_rw_t<io_, bitpos::B15>	SSBY;
		};
		typedef sbycr_t<0x0008'000C> SBYCR_;
		static SBYCR_ SBYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ A（MSTPCRA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcra_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>  MSTPA4;
			bit_rw_t<io_, bitpos::B5>  MSTPA5;

			bit_rw_t<io_, bitpos::B9>  MSTPA9;
			bit_rw_t<io_, bitpos::B10> MSTPA10;
			bit_rw_t<io_, bitpos::B11> MSTPA11;
			bit_rw_t<io_, bitpos::B12> MSTPA12;
			bit_rw_t<io_, bitpos::B13> MSTPA13;
			bit_rw_t<io_, bitpos::B14> MSTPA14;
			bit_rw_t<io_, bitpos::B15> MSTPA15;

			bit_rw_t<io_, bitpos::B17> MSTPA17;

			bit_rw_t<io_, bitpos::B19> MSTPA19;

			bit_rw_t<io_, bitpos::B23> MSTPA23;
			bit_rw_t<io_, bitpos::B24> MSTPA24;

			bit_rw_t<io_, bitpos::B27> MSTPA27;
			bit_rw_t<io_, bitpos::B28> MSTPA28;
			bit_rw_t<io_, bitpos::B29> MSTPA29;

			bit_rw_t<io_, bitpos::B31> ACSE;
		};
		typedef mstpcra_t<0x0008'0010> MSTPCRA_;
		static MSTPCRA_ MSTPCRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ B（MSTPCRB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcrb_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MSTPB0;
			bit_rw_t<io_, bitpos::B1>  MSTPB1;
			bit_rw_t<io_, bitpos::B2>  MSTPB2;

			bit_rw_t<io_, bitpos::B4>  MSTPB4;

			bit_rw_t<io_, bitpos::B8>  MSTPB8;

			bit_rw_t<io_, bitpos::B15> MSTPB15;
			bit_rw_t<io_, bitpos::B16> MSTPB16;
			bit_rw_t<io_, bitpos::B17> MSTPB17;
			bit_rw_t<io_, bitpos::B18> MSTPB18;
			bit_rw_t<io_, bitpos::B19> MSTPB19;
			bit_rw_t<io_, bitpos::B20> MSTPB20;
			bit_rw_t<io_, bitpos::B21> MSTPB21;
			bit_rw_t<io_, bitpos::B22> MSTPB22;
			bit_rw_t<io_, bitpos::B23> MSTPB23;
			bit_rw_t<io_, bitpos::B24> MSTPB24;
			bit_rw_t<io_, bitpos::B25> MSTPB25;
			bit_rw_t<io_, bitpos::B26> MSTPB26;
			bit_rw_t<io_, bitpos::B27> MSTPB27;
			bit_rw_t<io_, bitpos::B28> MSTPB28;
			bit_rw_t<io_, bitpos::B29> MSTPB29;
			bit_rw_t<io_, bitpos::B30> MSTPB30;
			bit_rw_t<io_, bitpos::B31> MSTPB31;
		};
		typedef mstpcrb_t<0x0008'0014> MSTPCRB_;
		static MSTPCRB_ MSTPCRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ C（MSTPCRC）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcrc_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MSTPC0;
			bit_rw_t<io_, bitpos::B1>  MSTPC1;

			bit_rw_t<io_, bitpos::B16> MSTPC16;
			bit_rw_t<io_, bitpos::B17> MSTPC17;
			bit_rw_t<io_, bitpos::B18> MSTPC18;
			bit_rw_t<io_, bitpos::B19> MSTPC19;

			bit_rw_t<io_, bitpos::B22> MSTPC22;

			bit_rw_t<io_, bitpos::B24> MSTPC24;
			bit_rw_t<io_, bitpos::B25> MSTPC25;
			bit_rw_t<io_, bitpos::B26> MSTPC26;
			bit_rw_t<io_, bitpos::B27> MSTPC27;
		};
		typedef mstpcrc_t<0x0008'0018> MSTPCRC_;
		static MSTPCRC_ MSTPCRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ D（MSTPCRD）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcrd_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B31> MSTPC31;
		};
		typedef mstpcrd_t<0x0008'001C> MSTPCRD_;
		static MSTPCRD_ MSTPCRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  動作電力コントロールレジスタ（OPCCR）
			@param[in]	base	ベースアドレス
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
		typedef opccr_t<0x0008'00A0> OPCCR_;
		static OPCCR_ OPCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  スリープモード復帰クロックソース切り替えレジスタ（RSTCKCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rstckcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> RSTCKSEL;

			bit_rw_t <io_, bitpos::B4>    RSTCKEN;
		};
		typedef rstckcr_t<0x0008'00A1> RSTCKCR_;
		static RSTCKCR_ RSTCKCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  メインクロック発振器ウェイトコントロールレジスタ（MOSCWTCR）
			@param[in]	base	ベースアドレス
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
		typedef moscwtcr_t<0x0008'00A2> MOSCWTCR_;
		static MOSCWTCR_ MOSCWTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct soscwtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> SSTS;
		};
		typedef soscwtcr_t<0x0008'00A3> SOSCWTCR_;
		static SOSCWTCR_ SOSCWTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL ウェイトコントロールレジスタ（PLLWTCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pllwtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> MSTS;
		};
		typedef pllwtcr_t<0x0008'00A6> PLLWTCR_;
		static PLLWTCR_ PLLWTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイコントロールレジスタ（DPSBYCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsbycr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> DEEPCUT;

			bit_rw_t <io_, bitpos::B6>    IOKEEP;
			bit_rw_t <io_, bitpos::B7>    DPSBY;
		};
		typedef dpsbycr_t<0x0008'C280> DPSBYCR_;
		static DPSBYCR_ DPSBYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトイネーブルレジスタ 0（DPSIER0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsier0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DIRQ0E;
			bit_rw_t<io_, bitpos::B1> DIRQ1E;
			bit_rw_t<io_, bitpos::B2> DIRQ2E;
			bit_rw_t<io_, bitpos::B3> DIRQ3E;
			bit_rw_t<io_, bitpos::B4> DIRQ4E;
			bit_rw_t<io_, bitpos::B5> DIRQ5E;
			bit_rw_t<io_, bitpos::B6> DIRQ6E;
			bit_rw_t<io_, bitpos::B7> DIRQ7E;
		};
		typedef dpsier0_t<0x0008'C282> DPSIER0_;
		static DPSIER0_ DPSIER0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトイネーブルレジスタ 1（DPSIER1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsier1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DIRQ8E;
			bit_rw_t<io_, bitpos::B1> DIRQ9E;
			bit_rw_t<io_, bitpos::B2> DIRQ10E;
			bit_rw_t<io_, bitpos::B3> DIRQ11E;
			bit_rw_t<io_, bitpos::B4> DIRQ12E;
			bit_rw_t<io_, bitpos::B5> DIRQ13E;
			bit_rw_t<io_, bitpos::B6> DIRQ14E;
			bit_rw_t<io_, bitpos::B7> DIRQ15E;
		};
		typedef dpsier1_t<0x0008'C283> DPSIER1_;
		static DPSIER1_ DPSIER1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトイネーブルレジスタ 2（DPSIER2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsier2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DLVD1IE;
			bit_rw_t<io_, bitpos::B1> DLVD2IE;
			bit_rw_t<io_, bitpos::B2> DRTCIIE;
			bit_rw_t<io_, bitpos::B3> DRTCAIE;
			bit_rw_t<io_, bitpos::B4> DNMIE;
			bit_rw_t<io_, bitpos::B5> DRIICDIE;
			bit_rw_t<io_, bitpos::B6> DRIICCIE;
			bit_rw_t<io_, bitpos::B7> DUSBIE;
		};
		typedef dpsier2_t<0x0008'C284> DPSIER2_;
		static DPSIER2_ DPSIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトイネーブルレジスタ 3（DPSIER3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsier3_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DCANIE;
		};
		typedef dpsier3_t<0x0008'C285> DPSIER3_;
		static DPSIER3_ DPSIER3;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトフラグレジスタ 0（DPSIFR0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsifr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DIRQ0F;
			bit_rw_t<io_, bitpos::B1> DIRQ1F;
			bit_rw_t<io_, bitpos::B2> DIRQ2F;
			bit_rw_t<io_, bitpos::B3> DIRQ3F;
			bit_rw_t<io_, bitpos::B4> DIRQ4F;
			bit_rw_t<io_, bitpos::B5> DIRQ5F;
			bit_rw_t<io_, bitpos::B6> DIRQ6F;
			bit_rw_t<io_, bitpos::B7> DIRQ7F;
		};
		typedef dpsifr0_t<0x0008'C286> DPSIFR0_;
		static DPSIFR0_ DPSIFR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトフラグレジスタ 1（DPSIFR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsifr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DIRQ8F;
			bit_rw_t<io_, bitpos::B1> DIRQ9F;
			bit_rw_t<io_, bitpos::B2> DIRQ10F;
			bit_rw_t<io_, bitpos::B3> DIRQ11F;
			bit_rw_t<io_, bitpos::B4> DIRQ12F;
			bit_rw_t<io_, bitpos::B5> DIRQ13F;
			bit_rw_t<io_, bitpos::B6> DIRQ14F;
			bit_rw_t<io_, bitpos::B7> DIRQ15F;
		};
		typedef dpsifr1_t<0x0008'C287> DPSIFR1_;
		static DPSIFR1_ DPSIFR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトフラグレジスタ 2（DPSIFR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsifr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DLVD1IF;
			bit_rw_t<io_, bitpos::B1> DLVD2IF;
			bit_rw_t<io_, bitpos::B2> DRTCIIF;
			bit_rw_t<io_, bitpos::B3> DRTCAIF;
			bit_rw_t<io_, bitpos::B4> DNMIF;
			bit_rw_t<io_, bitpos::B5> DRIICDIF;
			bit_rw_t<io_, bitpos::B6> DRIICCIF;
			bit_rw_t<io_, bitpos::B7> DUSBIF;
		};
		typedef dpsifr2_t<0x0008'C288> DPSIFR2_;
		static DPSIFR2_ DPSIFR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトフラグレジスタ 3（DPSIFR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsifr3_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DCANIF;
		};
		typedef dpsifr3_t<0x0008'C289> DPSIFR3_;
		static DPSIFR3_ DPSIFR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトエッジレジスタ 0（DPSIEGR0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsiegr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DIRQ0EG;
			bit_rw_t<io_, bitpos::B1> DIRQ1EG;
			bit_rw_t<io_, bitpos::B2> DIRQ2EG;
			bit_rw_t<io_, bitpos::B3> DIRQ3EG;
			bit_rw_t<io_, bitpos::B4> DIRQ4EG;
			bit_rw_t<io_, bitpos::B5> DIRQ5EG;
			bit_rw_t<io_, bitpos::B6> DIRQ6EG;
			bit_rw_t<io_, bitpos::B7> DIRQ7EG;
		};
		typedef dpsiegr0_t<0x0008'C28A> DPSIEGR0_;
		static DPSIEGR0_ DPSIEGR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトエッジレジスタ 1（DPSIEGR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsiegr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DIRQ8EG;
			bit_rw_t<io_, bitpos::B1> DIRQ9EG;
			bit_rw_t<io_, bitpos::B2> DIRQ10EG;
			bit_rw_t<io_, bitpos::B3> DIRQ11EG;
			bit_rw_t<io_, bitpos::B4> DIRQ12EG;
			bit_rw_t<io_, bitpos::B5> DIRQ13EG;
			bit_rw_t<io_, bitpos::B6> DIRQ14EG;
			bit_rw_t<io_, bitpos::B7> DIRQ15EG;
		};
		typedef dpsiegr1_t<0x0008'C28B> DPSIEGR1_;
		static DPSIEGR1_ DPSIEGR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトエッジレジスタ 2（DPSIEGR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsiegr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DLVD1IEG;
			bit_rw_t<io_, bitpos::B1> DLVD2IEG;

			bit_rw_t<io_, bitpos::B4> DNMIEG;
			bit_rw_t<io_, bitpos::B5> DRIICDEG;
			bit_rw_t<io_, bitpos::B6> DRIICCEG;
		};
		typedef dpsiegr2_t<0x0008'C28C> DPSIEGR2_;
		static DPSIEGR2_ DPSIEGR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトエッジレジスタ 3（DPSIEGR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsiegr3_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DCANIEG;
		};
		typedef dpsiegr3_t<0x0008'C28D> DPSIEGR3_;
		static DPSIEGR3_ DPSIEGR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイバックアップレジスタ（DPSBKRy）（y=0 ～ 31）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsbkr_t {
			uint8_t& operator[] (uint32_t idx) {
				idx &= 31;
				return *reinterpret_cast<uint8_t*>(base + idx);
			}
		};
		typedef dpsbkr_t<0x0008'C2A0> DPSBKR_;
		static DPSBKR_ DPSBKR;


		//-------- レジスタライトプロテクション機能

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

			bit_rw_t <io_, bitpos::B0>	   PRC0;
			bit_rw_t <io_, bitpos::B1>	   PRC1;

			bit_rw_t <io_, bitpos::B3>     PRC3;

			bits_rw_t<io_, bitpos::B8, 8>  PRKEY;
		};
		typedef prcr_t<0x0008'03FE> PRCR_;
		static PRCR_ PRCR;


		//-------- リセット機能

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 0（RSTSR0）
			@param[in]	base	ベースアドレス
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
		typedef rstsr0_t<0x0008'C290> RSTSR0_;
		static RSTSR0_ RSTSR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 1（RSTSR1）
			@param[in]	base	ベースアドレス
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
		typedef rstsr1_t<0x0008'C291> RSTSR1_;
		static RSTSR1_ RSTSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 2（RSTSR2）
			@param[in]	base	ベースアドレス
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
		typedef rstsr2_t<0x0008'00C0> RSTSR2_;
		static RSTSR2_ RSTSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ソフトウェアリセットレジスタ（SWRR） @n
					0xA501 を書き込むとリセットされます。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x0008'00C2> SWRR_;
		static SWRR_ SWRR;


		//=========================== 温度センサ =================================

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサコントロールレジスタ (TSCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct tscr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B4>  TSOE;

			bit_rw_t <io_, bitpos::B7>  TSEN;
		};
		typedef tscr_t<0x0008'C500> TSCR_;
		static TSCR_ TSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサ校正データレジスタ (TSCDRH, TSCDRL)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef ro8_t<0xFEFF'FAD3> TSCDRH_;
		static TSCDRH_ TSCDRH;

		typedef ro8_t<0xFEFF'FAD2> TSCDRL_;
		static TSCDRL_ TSCDRL;
	};
	template<class _> typename system_t<_>::SCKCR_ system_t<_>::SCKCR;
	template<class _> typename system_t<_>::SCKCR2_ system_t<_>::SCKCR2;
	template<class _> typename system_t<_>::SCKCR3_ system_t<_>::SCKCR3;
	template<class _> typename system_t<_>::PLLCR_ system_t<_>::PLLCR;
	template<class _> typename system_t<_>::PLLCR2_ system_t<_>::PLLCR2;
	template<class _> typename system_t<_>::MOSCCR_ system_t<_>::MOSCCR;
	template<class _> typename system_t<_>::SOSCCR_ system_t<_>::SOSCCR;
	template<class _> typename system_t<_>::LOCOCR_ system_t<_>::LOCOCR;
	template<class _> typename system_t<_>::ILOCOCR_ system_t<_>::ILOCOCR;
	template<class _> typename system_t<_>::HOCOCR_ system_t<_>::HOCOCR;
	template<class _> typename system_t<_>::OSTDCR_ system_t<_>::OSTDCR;
	template<class _> typename system_t<_>::OSTDSR_ system_t<_>::OSTDSR;
	template<class _> typename system_t<_>::MOFCR_ system_t<_>::MOFCR;
	template<class _> typename system_t<_>::HOCOPCR_ system_t<_>::HOCOPCR;
	template<class _> typename system_t<_>::SBYCR_ system_t<_>::SBYCR;
	template<class _> typename system_t<_>::MSTPCRA_ system_t<_>::MSTPCRA;
	template<class _> typename system_t<_>::MSTPCRB_ system_t<_>::MSTPCRB;
	template<class _> typename system_t<_>::MSTPCRC_ system_t<_>::MSTPCRC;
	template<class _> typename system_t<_>::MSTPCRD_ system_t<_>::MSTPCRD;
	template<class _> typename system_t<_>::OPCCR_ system_t<_>::OPCCR;
	template<class _> typename system_t<_>::RSTCKCR_ system_t<_>::RSTCKCR;
	template<class _> typename system_t<_>::MOSCWTCR_ system_t<_>::MOSCWTCR;
	template<class _> typename system_t<_>::SOSCWTCR_ system_t<_>::SOSCWTCR;
	template<class _> typename system_t<_>::PLLWTCR_ system_t<_>::PLLWTCR;
	template<class _> typename system_t<_>::DPSBYCR_ system_t<_>::DPSBYCR;
	template<class _> typename system_t<_>::DPSIER0_ system_t<_>::DPSIER0;
	template<class _> typename system_t<_>::DPSIER1_ system_t<_>::DPSIER1;
	template<class _> typename system_t<_>::DPSIER2_ system_t<_>::DPSIER2;
	template<class _> typename system_t<_>::DPSIER3_ system_t<_>::DPSIER3;
	template<class _> typename system_t<_>::DPSIFR0_ system_t<_>::DPSIFR0;
	template<class _> typename system_t<_>::DPSIFR1_ system_t<_>::DPSIFR1;
	template<class _> typename system_t<_>::DPSIFR2_ system_t<_>::DPSIFR2;
	template<class _> typename system_t<_>::DPSIFR3_ system_t<_>::DPSIFR3;
	template<class _> typename system_t<_>::DPSIEGR0_ system_t<_>::DPSIEGR0;
	template<class _> typename system_t<_>::DPSIEGR1_ system_t<_>::DPSIEGR1;
	template<class _> typename system_t<_>::DPSIEGR2_ system_t<_>::DPSIEGR2;
	template<class _> typename system_t<_>::DPSIEGR3_ system_t<_>::DPSIEGR3;
	template<class _> typename system_t<_>::DPSBKR_ system_t<_>::DPSBKR;
	template<class _> typename system_t<_>::PRCR_ system_t<_>::PRCR;
	template<class _> typename system_t<_>::RSTSR0_ system_t<_>::RSTSR0;
	template<class _> typename system_t<_>::RSTSR1_ system_t<_>::RSTSR1;
	template<class _> typename system_t<_>::RSTSR2_ system_t<_>::RSTSR2;
	template<class _> typename system_t<_>::SWRR_ system_t<_>::SWRR;
	template<class _> typename system_t<_>::TSCR_ system_t<_>::TSCR;
	template<class _> typename system_t<_>::TSCDRH_ system_t<_>::TSCDRH;
	template<class _> typename system_t<_>::TSCDRL_ system_t<_>::TSCDRL;

	typedef system_t<void> SYSTEM;
}
