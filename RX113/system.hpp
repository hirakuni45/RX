#pragma once
//=========================================================================//
/*!	@file
	@brief	RX110/RX111/RX113 グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	namespace SYSTEM {

		//----  動作モード  ------------------------------------------------//

		//-----------------------------------------------------------------//
		/*!
			@brief  モードモニタレジスタ (MDMONR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mdmonr_t : public ro16_t<base> {
			typedef ro16_t<base> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>     MD;
		};
		static inline mdmonr_t<0x0008'0000> MDMONR;


		//-----------------------------------------------------------------//
		/*!
			@brief  システムコントロールレジスタ 1 (SYSCR1)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct syscr1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     RAME;
		};
		static inline syscr1_t<0x0008'0008> SYSCR1;

		//----  リセット  --------------------------------------------------//

		//-----------------------------------------------------------------//
		/*!
			@brief  リセットステータスレジスタ 0 (RSTSR0)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rstsr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    PORF;

			bit_rw_t <io_, bitpos::B2>    LVD1RF;
			bit_rw_t <io_, bitpos::B3>    LVD2RF;
		};
		static inline rstsr0_t<0x0008'C290> RSTSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	リセットステータスレジスタ 1 (RSTSR1)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rstsr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    CWWSF;
		};
		static inline rstsr1_t<0x0008'C291> RSTSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	リセットステータスレジスタ 2 (RSTSR2)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rstsr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    IWDTRF;

			bit_rw_t <io_, bitpos::B2>    SWRF;
		};
		static inline rstsr2_t<0x0008'00C0> RSTSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ソフトウェアリセットレジスタ (SWRR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'00C2> SWRR;


		//----  クロック発生回路  -------------------------------------------//

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

			bits_rw_t<io_, bitpos::B0,  4> PCKD;

			bits_rw_t<io_, bitpos::B8,  4> PCKB;

			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		typedef sckcr_t<0x0008'0020> SCKCR_;
		static inline SCKCR_ SCKCR;


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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL コントロールレジスタ（PLLCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL コントロールレジスタ 2（PLLCR2）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  USB 専用 PLL コントロールレジスタ（UPLLCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct upllcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> UPLIDIV;

			bit_rw_t <io_, bitpos::B4>    UCKUPLLSEL;

			bits_rw_t<io_, bitpos::B8, 6> USTC;
		};
		static inline upllcr_t<0x0008'002C> UPLLCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  USB 専用 PLL コントロールレジスタ 2（UPLLCR2）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct upllcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> UPLLEN;
		};
		static inline upllcr2_t<0x0008'002E> UPLLCR2;


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
			@brief  高速オンチップオシレータコントロールレジスタ (HOCOCR)
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
			@brief  発振安定フラグレジスタ（OSCOVFSR）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct oscovfsr_t : public ro8_t<base> {
			typedef ro8_t<base> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0> MOOVF;

			bit_ro_t<in_, bitpos::B2> PLOVF;
			bit_ro_t<in_, bitpos::B3> HCOVF;

			bit_ro_t<in_, bitpos::B5> UPLOVF;
		};
		static inline oscovfsr_t<0x0008'003C> OSCOVFSR;


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
			@brief  LCD ソースクロックコントロールレジスタ（LCDSCLKCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lcdsclkcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> LCDSCLKSEL;
		};
		static inline lcdsclkcr_t<0x0008'0050> LCDSCLKCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  LCD ソースクロックコントロールレジスタ 2（LCDSCLKCR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lcdsclkcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> LCDSCLKSTP;
		};
		static inline lcdsclkcr2_t<0x0008'0051> LCDSCLKCR2;


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
			@brief  高速オンチップオシレータウェイトコントロールレジスタ（HOCOWTCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hocowtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> HSTS;
		};
		static inline hocowtcr_t<0x0008'00A5> HOCOWTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  CLKOUT 出力コントロールレジスタ（CKOCR）
			@param[in]	base	ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ckocr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8,  3> CKOSEL;

			bits_rw_t<io_, bitpos::B12, 3> CKODIV;
			bit_rw_t <io_, bitpos::B15>    CKOSTP;
		};
		static inline ckocr_t<0x0008'003E> CKOCR;


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

			bit_rw_t <io_, bitpos::B5>    MODRV21;
			bit_rw_t <io_, bitpos::B6>    MOSEL;
		};
		static inline mofcr_t<0x0008'C293> MOFCR;

		//----  消費電力低減機能  -------------------------------------------//

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

			bit_rw_t<io_, bitpos::B4>   MSTPA4;
			bit_rw_t<io_, bitpos::B5>   MSTPA5;

			bit_rw_t<io_, bitpos::B9>   MSTPA9;

			bit_rw_t<io_, bitpos::B14>  MSTPA14;
			bit_rw_t<io_, bitpos::B15>  MSTPA15;

			bit_rw_t<io_, bitpos::B17>  MSTPA17;
			bit_rw_t<io_, bitpos::B18>  MSTPA18;

			bit_rw_t<io_, bitpos::B28>  MSTPA28;
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

			bit_rw_t<io_, bitpos::B4>   MSTPB4;

			bit_rw_t<io_, bitpos::B6>   MSTPB6;

			bit_rw_t<io_, bitpos::B9>   MSTPB9;
			bit_rw_t<io_, bitpos::B10>  MSTPB10;

			bit_rw_t<io_, bitpos::B17>  MSTPB17;

			bit_rw_t<io_, bitpos::B19>  MSTPB19;

			bit_rw_t<io_, bitpos::B21>  MSTPB21;

			bit_rw_t<io_, bitpos::B23>  MSTPB23;

			bit_rw_t<io_, bitpos::B25>  MSTPB25;
			bit_rw_t<io_, bitpos::B26>  MSTPB26;

			bit_rw_t<io_, bitpos::B29>  MSTPB29;
			bit_rw_t<io_, bitpos::B30>  MSTPB30;
			bit_rw_t<io_, bitpos::B31>  MSTPB31;
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

			bit_rw_t<io_, bitpos::B6>  MSTPC0;

			bit_rw_t<io_, bitpos::B19> MSTPC19;
			bit_rw_t<io_, bitpos::B20> MSTPC20;

			bit_rw_t<io_, bitpos::B26> MSTPC26;
			bit_rw_t<io_, bitpos::B27> MSTPC27;

			bit_rw_t<io_, bitpos::B31> DSLPE;
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

			bit_rw_t<io_, bitpos::B10> MSTPD10;
			bit_rw_t<io_, bitpos::B11> MSTPD11;

			bit_rw_t<io_, bitpos::B15> MSTPD15;
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
			@brief  サブ動作電力コントロールレジスタ（SOPCCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sopccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    SOPCM;

			bit_rw_t <io_, bitpos::B4>    SOPCMTSF;
		};
		static inline sopccr_t<0x0008'00AA> SOPCCR;


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

			bit_rw_t <io_, bitpos::B7>    RSTCKEN;
		};
		static inline rstckcr_t<0x0008'00A1> RSTCKCR;

		//----  レジスタライトプロテクション機能  ----------------------------//

		//-----------------------------------------------------------------//
		/*!
			@brief  プロテクトレジスタ（PRCR）
			@param[in]	base	ベースアドレス
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
			bit_rw_t <io_, bitpos::B2>    PRC2;
			bit_rw_t <io_, bitpos::B3>    PRC3;

			bits_rw_t<io_, bitpos::B8, 8> PRKEY;
		};
		static inline prcr_t<0x0008'03FE> PRCR;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  温度センサ (TEMPS)
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct temps_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサ校正データレジスタ (TSCDRH)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		ro8_t<0x007F'C0AC> TSCDRH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサ校正データレジスタ (TSCDRL)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		ro8_t<0x007F'C0AD> TSCDRL;
	};
	static inline temps_t TEMPS;
}
