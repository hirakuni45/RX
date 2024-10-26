#pragma once
//=========================================================================//
/*!	@file
	@brief	RX260/RX261 システム定義（クロック発生回路、）
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

		// ---- リセット ---------------------------------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 0（RSTSR0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 1（RSTSR1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 2（RSTSR2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ソフトウェアリセットレジスタ（SWRR）@n
					0xA501 を書き込むとリセットされます。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<0x0008'00C2> SWRR;


		// ---- オプション設定メモリ (OFSM)　--------------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  オプション機能選択レジスタ 0 (OFS0)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct ofs0_t : public ro32_t<base> {
			typedef ro32_t<base> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B1>     IWDTSTRT;
			bits_ro_t<in_, bitpos::B2,  2> IWDTTOPS;
			bits_ro_t<in_, bitpos::B4,  4> IWDTCKS;
			bits_ro_t<in_, bitpos::B8,  2> IWDTRPES;
			bits_ro_t<in_, bitpos::B10, 2> IWDTRPSS;
			bit_ro_t <in_, bitpos::B12>    IWDTRSTIRQS;

			bit_ro_t <in_, bitpos::B14>    IWDTSLCSTP;

			bit_ro_t <in_, bitpos::B17>    WDTSTRT;
			bits_ro_t<in_, bitpos::B18, 2> WDTTOPS;
			bits_ro_t<in_, bitpos::B20, 4> WDTCKS;
			bits_ro_t<in_, bitpos::B24, 2> WDTRPES;
			bits_ro_t<in_, bitpos::B26, 2> WDTRPSS;
			bit_ro_t <in_, bitpos::B28>    WDTRSTIRQS;
		};
		static inline ofs0_t<0xFFFF'FF8C> OFS0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  オプション機能選択レジスタ 1 (OFS1)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct ofs1_t : public ro32_t<base> {
			typedef ro32_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0,  2> VDSEL;
			bit_ro_t <in_, bitpos::B2>     LVDAS;
			bit_ro_t <in_, bitpos::B3>     FASTSTUP;
			bit_ro_t <in_, bitpos::B4>     VDSEL2;

			bit_ro_t <in_, bitpos::B8>     HOCOEN;

			bits_ro_t<in_, bitpos::B12, 2> HOCOFRQ;
		};
		static inline ofs1_t<0xFFFF'FF88> OFS1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エンディアン選択レジスタ (MDE)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mde_t : public ro32_t<base> {
			typedef ro32_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0,  2> MDE;
		};
		static inline mde_t<0xFFFF'FF80> MDE;


		//----  クロック発生回路  -------------------------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ（SCKCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
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
		static inline sckcr_t<0x0008'0020> SCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ 3（SCKCR3）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
			@brief  PLL2 コントロールレジスタ (PLL2CR)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pll2cr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  PLIDIV;
			bits_rw_t<io_, bitpos::B8, 6>  STC;
		};
		static inline pll2cr_t<0x0008'002C> PLL2CR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL2 コントロールレジスタ 2（PLL2CR2）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pll2cr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PLL2EN;
		};
		static inline pll2cr2_t<0x0008'002E> PLL2CR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器コントロールレジスタ（MOSCCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ (SOSCCR)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  低速オンチップオシレータコントロールレジスタ（LOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IWDT 専用オンチップオシレータコントロールレジスタ（ILOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  高速オンチップオシレータコントロールレジスタ（HOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	高速オンチップオシレータコントロールレジスタ 2（HOCOCR2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振安定フラグレジスタ（OSCOVFSR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct oscovfsr_t : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0> MOOVF;

			bit_ro_t<io_, bitpos::B2> PLOVF;
			bit_ro_t<io_, bitpos::B3> HCOVF;

			bit_ro_t<io_, bitpos::B5> PL2OVF;
		};
		static inline oscovfsr_t<0x0008'003C> OSCOVFSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	CLKOUT 出力コントロールレジスタ (CKOCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ckocr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8,  4>  CKOSEL;
			bits_rw_t<io_, bitpos::B12, 3>  CKODIV;
			bit_rw_t <io_, bitpos::B15>     CKOSTP;
		};
		static inline ckocr_t<0x0008'003E> CKOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振停止検出コントロールレジスタ（OSTDCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振停止検出ステータスレジスタ（OSTDSR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  低速オンチップオシレータ強制発振コントロールレジスタ (LOFCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct lofcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> LOFXIN;
		};
		static inline lofcr_t<0x0008'0043> LOFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  低速オンチップオシレータトリミングレジスタ 2 (LOCOTRR2)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct locotrr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> LOCOTRD;
		};
		static inline locotrr2_t<0x0008'0061> LOCOTRR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IWDT 専用オンチップオシレータトリミングレジスタ (ILOCOTRR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ilocotrr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> ILOCOTRD;
		};
		static inline ilocotrr_t<0x0008'0064> ILOCOTRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  高速オンチップオシレータトリミングレジスタ 0 (HOCOTRR0)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct hocotrr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6> HOCOTRD;
		};
		static inline hocotrr0_t<0x0008'0068> HOCOTRR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CANFD クロック分周コントロールレジスタ (CANFDCKDIVCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct canfdckdivcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> CANFDCKDIV;
		};
		static inline canfdckdivcr_t<0x0008'006E> CANFDCKDIVCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  USB クロックコントロールレジスタ (USBCKCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct usbckcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> USBCKSEL;

			bit_rw_t <io_, bitpos::B6>    USBCKSREQ;
			bit_ro_t <io_, bitpos::B7>    USBCKSRDY;
		};
		static inline usbckcr_t<0x0008'0074> USBCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CANFD クロックコントロールレジスタ (CANFDCKCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct canfdckcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> CANFDCKSEL;

			bit_rw_t <io_, bitpos::B6>    CANFDCKSREQ;
			bit_ro_t <io_, bitpos::B7>    CANFDCKSRDY;
		};
		static inline canfdckcr_t<0x0008'0076> CANFDCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器モードコントロールレジスタ (SOMCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct somcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SODRV;

			bit_rw_t <io_, bitpos::B7>    SOSEL;
		};
		static inline somcr_t<0x0008'0083> SOMCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器ウェイトコントロールレジスタ（MOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器強制発振コントロールレジスタ（MOFCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mofcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B4, 2>  MODRV2;
			bit_rw_t <io_, bitpos::B6>     MOSEL;
		};
		static inline mofcr_t<0x0008'C293> MOFCR;


		//----  消費電力低減機能  -------------------------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スタンバイコントロールレジスタ（SBYCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ A（MSTPCRA）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mstpcra_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>	MSTPA4;
			bit_rw_t<io_, bitpos::B5>	MSTPA5;

			bit_rw_t<io_, bitpos::B7>	MSTPA7;

			bit_rw_t<io_, bitpos::B14>	MSTPA14;
			bit_rw_t<io_, bitpos::B15>	MSTPA15;

			bit_rw_t<io_, bitpos::B17>	MSTPA17;

			bit_rw_t<io_, bitpos::B19>	MSTPA19;

			bit_rw_t<io_, bitpos::B28>	MSTPA28;
		};
		static inline mstpcra_t<0x0008'0010> MSTPCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ B（MSTPCRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mstpcrb_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>	MSTPB4;

			bit_rw_t<io_, bitpos::B6>	MSTPB6;

			bit_rw_t<io_, bitpos::B9>	MSTPB9;
			bit_rw_t<io_, bitpos::B10>	MSTPB10;

			bit_rw_t<io_, bitpos::B17>	MSTPB17;

			bit_rw_t<io_, bitpos::B19>	MSTPB19;

			bit_rw_t<io_, bitpos::B21>	MSTPB21;

			bit_rw_t<io_, bitpos::B23>	MSTPB23;

			bit_rw_t<io_, bitpos::B25>	MSTPB25;
			bit_rw_t<io_, bitpos::B26>	MSTPB26;

			bit_rw_t<io_, bitpos::B30>	MSTPB30;
			bit_rw_t<io_, bitpos::B31>	MSTPB31;
		};
		static inline mstpcrb_t<0x0008'0014> MSTPCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ C（MSTPCRC）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mstpcrc_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>	MSTPC0;

			bit_rw_t<io_, bitpos::B19>	MSTPC19;

			bit_rw_t<io_, bitpos::B26>	MSTPC26;
			bit_rw_t<io_, bitpos::B27>	MSTPC27;

			bit_rw_t<io_, bitpos::B29>	MSTPC29;

			bit_rw_t<io_, bitpos::B31>	DSLPE;
		};
		static inline mstpcrc_t<0x0008'0018> MSTPCRC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ D（MSTPCRD）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mstpcrd_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B9>	MSTPD9;
			bit_rw_t<io_, bitpos::B10>	MSTPD10;

			bit_rw_t<io_, bitpos::B31>	MSTPD31;
		};
		static inline mstpcrd_t<0x0008'001C> MSTPCRD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作電力コントロールレジスタ (OPCCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct opccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>	OPCM;

			bit_ro_t <io_, bitpos::B4>		OPCMTSF;
		};
		static inline opccr_t<0x0008'00A0> OPCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブ動作電力コントロールレジスタ (SOPCCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sopccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		SOPCM;

			bit_ro_t <io_, bitpos::B4>		SOPCMTSF;
		};
		static inline sopccr_t<0x0008'00AA> SOPCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スリープモード復帰クロックソース切り替えレジスタ (RSTCKCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstckcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>   RSTCKSEL;

			bit_ro_t <io_, bitpos::B7>		RSTCKEN;
		};
		static inline rstckcr_t<0x0008'00A1> RSTCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スヌーズコントロールレジスタ (SNZCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct snzcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  SCISNZSEL;
			bits_rw_t<io_, bitpos::B2,  2>  LPTSNZSEL;
			bits_rw_t<io_, bitpos::B4,  2>  ADCSNZSEL;
			bits_rw_t<io_, bitpos::B6,  2>  CTSUSNZSEL;
			bits_rw_t<io_, bitpos::B8,  2>  REMCSNZSEL;
			bits_rw_t<io_, bitpos::B10, 2>  ADCSNZ2SEL;
			bits_rw_t<io_, bitpos::B12, 2>  ADCSNZ3SEL;

			bit_rw_t <io_, bitpos::B15>     SNZDTCE;
		};
		static inline snzcr_t<0x0008'00AE> SNZCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スヌーズコントロールレジスタ 2 (SNZCR2)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct snzcr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      SCIERE;

			bits_rw_t<io_, bitpos::B2,  2>  SCIRXE;
			bits_rw_t<io_, bitpos::B4,  2>  LPTCM1E;
			bits_rw_t<io_, bitpos::B6,  2>  ADE;
			bits_rw_t<io_, bitpos::B8,  2>  CTSUFNE;

			bit_rw_t <io_, bitpos::B10>     ADE2;

			bit_rw_t <io_, bitpos::B12>     ADE3;
		};
		static inline snzcr2_t<0x0008'00AC> SNZCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  RAM 省電力制御レジスタ (RPSCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rpscr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>		PSA0;
			bit_rw_t <io_, bitpos::B1>		PSA1;
			bit_rw_t <io_, bitpos::B2>		PSA2;
			bit_rw_t <io_, bitpos::B3>		PSA3;
		};
		static inline rpscr_t<0x0008'009F> RPSCR;


		//----  レジスタライトプロテクション機能  ----------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  プロテクトレジスタ（PRCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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


		//----  TEMPS  ----------------------------------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサ校正データレジスタ (TSCDR) 
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<0x007F'C228> TSCDR;
	}
}
