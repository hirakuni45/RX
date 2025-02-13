#pragma once
//=============================================================================//
/*!	@file
	@brief	RX210 グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_t {

		//---------------------- クロック発生回路 ------------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ（SCKCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct sckcr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4> PCKD;

			bits_rw_t<io_, bitpos::B8,  4> PCKB;

			bits_rw_t<io_, bitpos::B16, 4> BCK;

			bit_rw_t <io_, bitpos::B23>    PSTOP1;
			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		static inline sckcr_t<0x0008'0020> SCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ 3（SCKCR3）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  電圧レギュレータ制御レジスタ（VRCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<0x0008'0200> VRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL コントロールレジスタ（PLLCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL コントロールレジスタ 2（PLLCR2）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バスクロックコントロールレジスタ（BCKCR）
			@param[in]	base	ベース・アドレス
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
		static inline bckcr_t<0x0008'0030> BCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器コントロールレジスタ（MOSCCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  低速オンチップオシレータコントロールレジスタ（LOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IWDT 専用オンチップオシレータコントロールレジスタ（ILOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  高速オンチップオシレータコントロールレジスタ (HOCOCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  高速オンチップオシレータコントロールレジスタ 2 (HOCOCR2)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct hococr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> HCFRQ;
		};
		static inline hococr2_t<0x0008'0037> HOCOCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振停止検出コントロールレジスタ（OSTDCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振停止検出ステータスレジスタ（OSTDSR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	メインクロック発振器強制発振コントロールレジスタ（MOFCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mofcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B1, 3> MODRV;
			bits_rw_t<io_, bitpos::B4, 2> MODRV2;
			bit_rw_t <io_, bitpos::B6>    MOSEL;
		};
		static inline mofcr_t<0x0008'C293> MOFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	高速オンチップオシレータ電源コントロールレジスタ（HOCOPCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct hocopcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  HOCOPCNT;
		};
		static inline hocopcr_t<0x0008'C294> HOCOPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL 電源コントロールレジスタ（PLLPCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pllpcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PLLPCNT;
		};
		static inline pllpcr_t<0x0008'C295> PLLPCR;

		//---------------------- 消費電力低減機能 ------------------------------//

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

			bit_rw_t<io_, bitpos::B15>	SSBY;
		};
		static inline sbycr_t<0x0008'000C> SBYCR;


		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ A（MSTPCRA）
			@param[in]	base	ベースアドレス
		*/
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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

			bit_rw_t<io_, bitpos::B13> MSTPA13;
			bit_rw_t<io_, bitpos::B14> MSTPA14;
			bit_rw_t<io_, bitpos::B15> MSTPA15;

			bit_rw_t<io_, bitpos::B17> MSTPA17;

			bit_rw_t<io_, bitpos::B19> MSTPA19;

			bit_rw_t<io_, bitpos::B24> MSTPA24;

			bit_rw_t<io_, bitpos::B27> MSTPA27;
			bit_rw_t<io_, bitpos::B28> MSTPA28;
			bit_rw_t<io_, bitpos::B29> MSTPA29;

			bit_rw_t<io_, bitpos::B31> ACSE;
		};
		static inline mstpcra_t<0x0008'0010> MSTPCRA;


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

			bit_rw_t<io_, bitpos::B4>  MSTPB4;

			bit_rw_t<io_, bitpos::B6>  MSTPB6;

			bit_rw_t<io_, bitpos::B8>  MSTPB8;
			bit_rw_t<io_, bitpos::B9>  MSTPB9;
			bit_rw_t<io_, bitpos::B10> MSTPB10;

			bit_rw_t<io_, bitpos::B17> MSTPB17;

			bit_rw_t<io_, bitpos::B21> MSTPB21;

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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ C（MSTPCRC）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mstpcrc_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MSTPC0;
			bit_rw_t<io_, bitpos::B1>  MSTPC1;

			bit_rw_t<io_, bitpos::B19> MSTPC19;

			bit_rw_t<io_, bitpos::B24> MSTPC24;
			bit_rw_t<io_, bitpos::B25> MSTPC25;
			bit_rw_t<io_, bitpos::B26> MSTPC26;
			bit_rw_t<io_, bitpos::B27> MSTPC27;
		};
		static inline mstpcrc_t<0x0008'0018> MSTPCRC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作電力コントロールレジスタ（OPCCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スリープモード復帰クロックソース切り替えレジスタ（RSTCKCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct rstckcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> RSTCKSEL;

			bit_rw_t <io_, bitpos::B7>    RSTCKEN;
		};
		static inline rstckcr_t<0x0008'00A1> RSTCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器ウェイトコントロールレジスタ（MOSCWTCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL ウェイトコントロールレジスタ（PLLWTCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pllwtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> PSTS;
		};
		static inline pllwtcr_t<0x0008'00A6> PLLWTCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  HOCO ウェイトコントロールレジスタ 2（HOCOWTCR2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct hocowtcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> HSTS2;
		};
		static inline hocowtcr2_t<0x0008'00A9> HOCOWTCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイコントロールレジスタ（DPSBYCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsbycr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DEEPCUT1;

			bit_rw_t<io_, bitpos::B6>   IOKEEP;
			bit_rw_t<io_, bitpos::B7>   DPSBY;
		};
		static inline dpsbycr_t<0x0008'C280> DPSBYCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイインタラプトイネーブルレジスタ 0（DPSIER0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsier0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DIRQ0E;
			bit_rw_t<io_, bitpos::B1>   DIRQ1E;
			bit_rw_t<io_, bitpos::B2>   DIRQ2E;
			bit_rw_t<io_, bitpos::B3>   DIRQ3E;
			bit_rw_t<io_, bitpos::B4>   DIRQ4E;
			bit_rw_t<io_, bitpos::B5>   DIRQ5E;
			bit_rw_t<io_, bitpos::B6>   DIRQ6E;
			bit_rw_t<io_, bitpos::B7>   DIRQ7E;
		};
		static inline dpsier0_t<0x0008'C282> DPSIER0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイインタラプトイネーブルレジスタ 2（DPSIER2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsier2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DLVD1IE;
			bit_rw_t<io_, bitpos::B1>   DLVD2IE;
			bit_rw_t<io_, bitpos::B2>   DRTCIIE;
			bit_rw_t<io_, bitpos::B3>   DRTCAIE;
			bit_rw_t<io_, bitpos::B4>   DNMIE;
			bit_rw_t<io_, bitpos::B5>   DRIICDIE;
			bit_rw_t<io_, bitpos::B6>   DRIICCIE;
		};
		static inline dpsier2_t<0x0008'C284> DPSIER2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイインタラプトフラグレジスタ 0（DPSIFR0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsifr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DIRQ0F;
			bit_rw_t<io_, bitpos::B1>   DIRQ1F;
			bit_rw_t<io_, bitpos::B2>   DIRQ2F;
			bit_rw_t<io_, bitpos::B3>   DIRQ3F;
			bit_rw_t<io_, bitpos::B4>   DIRQ4F;
			bit_rw_t<io_, bitpos::B5>   DIRQ5F;
			bit_rw_t<io_, bitpos::B6>   DIRQ6F;
			bit_rw_t<io_, bitpos::B7>   DIRQ7F;
		};
		static inline dpsifr0_t<0x0008'C286> DPSIFR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイインタラプトフラグレジスタ 2（DPSIFR2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsifr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DLVD1IF;
			bit_rw_t<io_, bitpos::B1>   DLVD2IF;
			bit_rw_t<io_, bitpos::B2>   DRTCIIF;
			bit_rw_t<io_, bitpos::B3>   DRTCAIF;
			bit_rw_t<io_, bitpos::B4>   DNMIF;
			bit_rw_t<io_, bitpos::B5>   DRIICDIF;
			bit_rw_t<io_, bitpos::B6>   DRIICCIF;
		};
		static inline dpsifr2_t<0x0008'C288> DPSIFR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイインタラプトエッジレジスタ 0（DPSIEGR0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsiegr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DIRQ0EG;
			bit_rw_t<io_, bitpos::B1>   DIRQ1EG;
			bit_rw_t<io_, bitpos::B2>   DIRQ2EG;
			bit_rw_t<io_, bitpos::B3>   DIRQ3EG;
			bit_rw_t<io_, bitpos::B4>   DIRQ4EG;
			bit_rw_t<io_, bitpos::B5>   DIRQ5EG;
			bit_rw_t<io_, bitpos::B6>   DIRQ6EG;
			bit_rw_t<io_, bitpos::B7>   DIRQ7EG;
		};
		static inline dpsiegr0_t<0x0008'C28A> DPSIEGR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイインタラプトエッジレジスタ 2（DPSIEGR2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsiegr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DLVD1EG;
			bit_rw_t<io_, bitpos::B1>   DLVD2EG;

			bit_rw_t<io_, bitpos::B4>   DNMIEG;
			bit_rw_t<io_, bitpos::B5>   DRIICDEG;
			bit_rw_t<io_, bitpos::B6>   DRIICCEG;
		};
		static inline dpsiegr2_t<0x0008'C28C> DPSIEGR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  フラッシュ HOCO ソフトウェアスタンバイコントロールレジスタ（FHSSBYCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct fhssbycr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SOFTCUT;
		};
		static inline fhssbycr_t<0x0008'C28F> FHSSBYCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイバックアップレジスタ（DPSBKR[y]）（y=0 ～ 31）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsbkr_t : public rw8_index_t<base> {
			typedef rw8_index_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 32) { io_::index = j; } }

			auto& operator [] (uint32_t idx)
			{
				set_index(idx);
				return *this;
			}
		};
		static inline dpsbkr_t<0x0008'C2A0> DPSBKR;

		//------------------ レジスタライトプロテクション機能 --------------------//

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

			bit_rw_t <io_, bitpos::B0>    PRC0;
			bit_rw_t <io_, bitpos::B1>    PRC1;
			bit_rw_t <io_, bitpos::B2>    PRC2;
			bit_rw_t <io_, bitpos::B3>    PRC3;

			bits_rw_t<io_, bitpos::B8, 8> PRKEY;
		};
		static inline prcr_t<0x0008'03FE> PRCR;

		//----  温度センサ (TEMPS)  --------------------------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサコントロールレジスタ（TSCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tscr_t : public  rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  PGAGAIN;

			bit_rw_t <io_, bitpos::B6>     PGAEN;
			bit_rw_t <io_, bitpos::B7>     TSEN;
		};
		static inline tscr_t<0x0008'C500> TSCR;
	};
	typedef system_t SYSTEM;
}
