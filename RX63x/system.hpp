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
	namespace SYSTEM {

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
		static inline sckcr_t<0x0008'0020> SCKCR;


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
		static inline sckcr2_t<0x0008'0024> SCKCR2;


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
		static inline sckcr3_t<0x0008'0026> SCKCR3;


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
		static inline pllcr_t<0x0008'0028> PLLCR;


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
		static inline pllcr2_t<0x0008'002A> PLLCR2;


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
		static inline bckcr_t<0x0008'0030> BCKCR;


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
		static inline mosccr_t<0x0008'0032> MOSCCR;


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
		static inline sosccr_t<0x0008'0033> SOSCCR;


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
		static inline lococr_t<0x0008'0034> LOCOCR;


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
		static inline ilococr_t<0x0008'0035> ILOCOCR;


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
		static inline hococr_t<0x0008'0036> HOCOCR;


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
		static inline ostdcr_t<0x0008'0040> OSTDCR;


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
		static inline ostdsr_t<0x0008'0041> OSTDSR;


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
		static inline mofcr_t<0x0008'C293> MOFCR;


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
		static inline hocopcr_t<0x0008'C294> HOCOPCR;


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
		static inline sbycr_t<0x0008'000C> SBYCR;


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
		static inline mstpcra_t<0x0008'0010> MSTPCRA;


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
		static inline mstpcrb_t<0x0008'0014> MSTPCRB;


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
		static inline mstpcrc_t<0x0008'0018> MSTPCRC;


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
		static inline mstpcrd_t<0x0008'001C> MSTPCRD;


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
		static inline opccr_t<0x0008'00A0> OPCCR;


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
		static inline rstckcr_t<0x0008'00A1> RSTCKCR;


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
		static inline moscwtcr_t<0x0008'00A2> MOSCWTCR;


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
		static inline soscwtcr_t<0x0008'00A3> SOSCWTCR;


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
		static inline pllwtcr_t<0x0008'00A6> PLLWTCR;


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
		static inline dpsbycr_t<0x0008'C280> DPSBYCR;


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
		static inline dpsier0_t<0x0008'C282> DPSIER0;


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
		static inline dpsier1_t<0x0008'C283> DPSIER1;


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
		static inline dpsier2_t<0x0008'C284> DPSIER2;


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
		static inline dpsier3_t<0x0008'C285> DPSIER3;


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
		static inline dpsifr0_t<0x0008'C286> DPSIFR0;


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
		static inline dpsifr1_t<0x0008'C287> DPSIFR1;


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
		static inline dpsifr2_t<0x0008'C288> DPSIFR2;


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
		static inline dpsifr3_t<0x0008'C289> DPSIFR3;


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
		static inline dpsiegr0_t<0x0008'C28A> DPSIEGR0;


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
		static inline dpsiegr1_t<0x0008'C28B> DPSIEGR1;


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
		static inline dpsiegr2_t<0x0008'C28C> DPSIEGR2;


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
		static inline dpsiegr3_t<0x0008'C28D> DPSIEGR3;


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
		static inline dpsbkr_t<0x0008'C2A0> DPSBKR;


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
		static inline prcr_t<0x0008'03FE> PRCR;


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
		static inline rstsr0_t<0x0008'C290> RSTSR0;


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
		static inline rstsr1_t<0x0008'C291> RSTSR1;


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
		static inline rstsr2_t<0x0008'00C0> RSTSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ソフトウェアリセットレジスタ（SWRR） @n
					0xA501 を書き込むとリセットされます。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<0x0008'00C2> SWRR;


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
		static inline tscr_t<0x0008'C500> TSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサ校正データレジスタ (TSCDRH, TSCDRL)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro8_t<0xFEFF'FAD3> TSCDRH;
		static inline ro8_t<0xFEFF'FAD2> TSCDRL;
	}
}
