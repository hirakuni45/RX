#pragma once
//=============================================================================//
/*!	@file
	@brief	システム定義（クロック発生回路、） @n
			・RX64M/RX71M @n
			・RX651/RX65N @n
			・RX671 @n
			・RX66T @n
			・RX72M/RX72T/RX72N
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2023 Kunihito Hiramatsu @n
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
	template<class _>
	struct system_t {

		//----  オプション設定メモリ  -------------------------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  シリアルプログラマコマンド制御レジスタ（SPCC）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct spcc_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B24>    IDE;
			bit_ro_t <io_, bitpos::B27>    SPE;
			bit_ro_t <io_, bitpos::B29>    SEPR;
			bit_ro_t <io_, bitpos::B30>    SWRPR;
			bit_ro_t <io_, bitpos::B31>    RDPR;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  オプション機能選択レジスタ 0（OFS0）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct ofs0_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B1>      IWDTSTRT;
			bits_ro_t<io_, bitpos::B2,  2>  IWDTTOPS;
			bits_ro_t<io_, bitpos::B4,  4>  IWDTCKS;
			bits_ro_t<io_, bitpos::B8,  2>  IWDTRPES;
			bits_ro_t<io_, bitpos::B10, 2>  IWDTRPSS;
			bit_ro_t <io_, bitpos::B12>     IWDTRSTIRQS;

			bit_ro_t <io_, bitpos::B14>     IWDTSLCSTP;

			bit_ro_t <io_, bitpos::B17>     WDTSTRT;
			bits_ro_t<io_, bitpos::B18, 2>  WDTTOPS;
			bits_ro_t<io_, bitpos::B20, 4>  WDTCKS;
			bits_ro_t<io_, bitpos::B24, 2>  WDTRPES;
			bits_ro_t<io_, bitpos::B26, 2>  WDTRPSS;
			bit_ro_t <io_, bitpos::B28>     WDTRSTIRQS;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  オプション機能選択レジスタ 1（OFS1）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct ofs1_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 2>  VDSEL;
			bit_ro_t <io_, bitpos::B2>     LVDAS;
			bit_ro_t <io_, bitpos::B8>     HOCOEN;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エンディアン選択レジスタ（MDE）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mde_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 3> MDE;
		};
#if defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef spcc_t<0xFE7F'5D40> SPCC_;
		static SPCC_ SPCC;
		typedef ofs0_t<0xFE7F'5D04> OFS0_;
		static OFS0_ OFS0;
		typedef ofs1_t<0xFE7F'5D08> OFS1_;
		static OFS1_ OFS1;
		typedef mde_t <0xFE7F'5D00> MDE_;
		static MDE_ MDE;
#else
		typedef spcc_t<0x0012'0040> SPCC_;
		static SPCC_ SPCC;
		typedef ofs0_t<0x0012'0068> OFS0_;
		static OFS0_ OFS0;
		typedef ofs1_t<0x0012'006C> OFS1_;
		static OFS1_ OFS1;
		typedef mde_t <0x0012'0064> MDE_;
		static MDE_ MDE;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードモニタレジスタ（MDMONR）
			@param[in]	base	ベース・アドレス
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
		typedef mdmonr_t<0x0008'0000> MDMONR_;
		static MDMONR_ MDMONR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードステータスレジスタ（MDSR）
			@param[in]	base	ベース・アドレス
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
		typedef mdsr_t<0x0008'0002> MDSR_;
		static MDSR_ MDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムコントロールレジスタ 0（SYSCR0）
			@param[in]	base	ベース・アドレス
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
		typedef syscr0_t<0x0008'0006> SYSCR0_;
		static SYSCR0_ SYSCR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムコントロールレジスタ 1（SYSCR1）
			@param[in]	base	ベース・アドレス
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
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
			bit_rw_t<io_, bitpos::B7>  SBYRAME;
#endif
		};
		typedef syscr1_t<0x0008'0008> SYSCR1_;
		static SYSCR1_ SYSCR1;

		//----  クロック発生回路  -----------------------------------------------//

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

			bits_rw_t<io_, bitpos::B0,  4> PCKD;
			bits_rw_t<io_, bitpos::B4,  4> PCKC;
			bits_rw_t<io_, bitpos::B8,  4> PCKB;
			bits_rw_t<io_, bitpos::B12, 4> PCKA;
			bits_rw_t<io_, bitpos::B16, 4> BCK;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX671) || defined(SIG_RX72M) || defined(SIG_RX72N)
			bit_rw_t <io_, bitpos::B22>    PSTOP0;
#endif
			bit_rw_t <io_, bitpos::B23>    PSTOP1;
			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		typedef sckcr_t<0x0008'0020> SCKCR_;
		static SCKCR_ SCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#if defined(SIG_RX71M)
		template<uint32_t base>
		struct memwait_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MEMWAIT;
		};
		typedef memwait_t<0x0008'6610> MEMWAIT_;
		static MEMWAIT_ MEMWAIT;

#elif defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72T) || defined(SIG_RX72N)
		template<uint32_t base>
		struct memwait_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MEMWAIT;
		};
		typedef memwait_t<0x0008'101C> MEMWAIT_;
		static MEMWAIT_ MEMWAIT;
#endif


#if defined(SIG_RX65N) || defined(SIG_RX671)
  		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT)
			@param[in]	base	ベース・アドレス
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
		typedef romwt_t<0x0008'101C> ROMWT_;
		static ROMWT_ ROMWT;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ 2（SCKCR2）
			@param[in]	base	ベース・アドレス
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
		typedef sckcr2_t<0x0008'0024> SCKCR2_;
		static SCKCR2_ SCKCR2;


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
		typedef sckcr3_t<0x0008'0026> SCKCR3_;
		static SCKCR3_ SCKCR3;


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

			bit_rw_t <io_, bitpos::B4>    PLLSRCSEL;

			bits_rw_t<io_, bitpos::B8, 6> STC;
		};
		typedef pllcr_t<0x0008'0028> PLLCR_;
		static PLLCR_ PLLCR;


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
		typedef pllcr2_t<0x0008'002A> PLLCR2_;
		static PLLCR2_ PLLCR2;


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
		typedef bckcr_t<0x0008'0030> BCKCR_;
		static BCKCR_ BCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器コントロールレジスタ（MOSCCR）
			@param[in]	base	ベース・アドレス
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
		typedef mosccr_t<0x0008'0032> MOSCCR_;
		static MOSCCR_ MOSCCR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX671) || defined(SIG_RX72N)
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
		typedef sosccr_t<0x0008'0033> SOSCCR_;
		static SOSCCR_ SOSCCR;
#endif


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
		typedef lococr_t<0x0008'0034> LOCOCR_;
		static LOCOCR_ LOCOCR;


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
		typedef ilococr_t<0x0008'0035> ILOCOCR_;
		static ILOCOCR_ ILOCOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  高速オンチップオシレータコントロールレジスタ（HOCOCR）
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
		typedef hococr_t<0x0008'0036> HOCOCR_;
		static HOCOCR_ HOCOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	高速オンチップオシレータコントロールレジスタ 2（HOCOCR2）
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
		typedef hococr2_t<0x0008'0037> HOCOCR2_;
		static HOCOCR2_ HOCOCR2;


#if defined(SIG_RX671)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	FLL コントロールレジスタ 1 (FLLCR1)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct fllcr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> FLLEN;
		};
		typedef fllcr1_t<0x0008'0039> FLLCR1_;
		static FLLCR1_ FLLCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	FLL コントロールレジスタ 2 (FLLCR2)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct fllcr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11> MPY;
		};
		typedef fllcr2_t<0x0008'003A> FLLCR2_;
		static FLLCR2_ FLLCR2;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振安定フラグレジスタ（OSCOVFSR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct oscovfsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MOOVF;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX671) || defined(SIG_RX72N)
			bit_rw_t<io_, bitpos::B1> SOOVF;
#endif
			bit_rw_t<io_, bitpos::B2> PLOVF;
			bit_rw_t<io_, bitpos::B3> HCOVF;
			bit_rw_t<io_, bitpos::B4> ILCOVF;
#if defined(SIG_RX72M) || defined(SIG_RX72T) || defined(SIG_RX72N)
			bit_rw_t<io_, bitpos::B5> PPLOVF;
#endif
		};
		typedef oscovfsr_t<0x0008'003C> OSCOVFSR_;
		static OSCOVFSR_ OSCOVFSR;


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
		typedef ostdcr_t<0x0008'0040> OSTDCR_;
		static OSTDCR_ OSTDCR;


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
		typedef ostdsr_t<0x0008'0041> OSTDSR_;
		static OSTDSR_ OSTDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器ウェイトコントロールレジスタ（MOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct moscwtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> MSTS;
		};
		typedef moscwtcr_t<0x0008'00A2> MOSCWTCR_;
		static MOSCWTCR_ MOSCWTCR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX671) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct soscwtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> SSTS;
		};
		typedef soscwtcr_t<0x0008'00A3> SOSCWTCR_;
		static SOSCWTCR_ SOSCWTCR;
#endif


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

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX671) || defined(SIG_RX72N)
			bit_rw_t <io_, bitpos::B0>     MOFXIN;
#endif

			bits_rw_t<io_, bitpos::B4, 2>  MODRV2;
			bit_rw_t <io_, bitpos::B6>     MOSEL;
		};
		typedef mofcr_t<0x0008'C293> MOFCR_;
		static MOFCR_ MOFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  高速オンチップオシレータ電源コントロールレジスタ（HOCOPCR）
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

			bit_rw_t<io_, bitpos::B0>	HOCOPCNT;
		};
		typedef hocopcr_t<0x0008'C294> HOCOPCR_;
		static HOCOPCR_ HOCOPCR;


#if defined(SIG_RX671) || defined(SIG_RX72M) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CLKOUT 出力コントロールレジスタ (CKOCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ckocr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8,  3>  CKOSEL;

			bits_rw_t<io_, bitpos::B12, 3>  CKODIV;
			bit_rw_t <io_, bitpos::B15>     CKOSTP;
		};
		typedef ckocr_t<0x0008'003E> CKOCR_;
		static CKOCR_ CKOCR;
#endif

#if defined(SIG_RX72M) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  特定用途向けクロック制御レジスタ (PACKCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct packcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>   OUTCKSEL;
#if defined (SIG_RX72M)
			bit_rw_t<io_, bitpos::B8>   EPLLSEL;
#endif
			bit_rw_t<io_, bitpos::B12>  UPLLSEL;
		};
		typedef packcr_t<0x0008'0044> PACKCR_;
		static PACKCR_ PACKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PPLL コントロールレジスタ (PPLLCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ppllcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  PPLIDIV;

			bits_rw_t<io_, bitpos::B8, 6>  PPLSTC;
		};
		typedef ppllcr_t<0x0008'0048> PPLLCR_;
		static PPLLCR_ PPLLCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PPLL コントロールレジスタ 2 (PPLLCR2)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ppllcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  PPLLEN;
		};
		typedef ppllcr2_t<0x0008'004A> PPLLCR2_;
		static PPLLCR2_ PPLLCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PPLL コントロールレジスタ 3 (PPLLCR3)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ppllcr3_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  PPLCK;
		};
		typedef ppllcr3_t<0x0008'004B> PPLLCR3_;
		static PPLLCR3_ PPLLCR3;
#endif

#if defined(SIG_RX671)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ 2 (SOSCCR2)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct sosccr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SOSTP2;
		};
		typedef sosccr2_t<0x0008'CC00> SOSCCR2_;
		static SOSCCR2_ SOSCCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バックアップ領域サブクロック制御レジスタ (BKSCCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct bksccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6>  SOSEL;
		};
		typedef bksccr_t<0x0008'CC01> BKSCCR_;
		static BKSCCR_ BKSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  高速オンチップオシレータトリミングレジスタ n (HOCOTRRn) (n = 0 ～ 2)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct hocotrr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>  HOCOTRD;
		};
		typedef hocotrr_t<0x007F'B0E0> HOCOTRR0_;
		static HOCOTRR0_ HOCOTRR0;
		typedef hocotrr_t<0x007F'B0E4> HOCOTRR1_;
		static HOCOTRR1_ HOCOTRR1;
		typedef hocotrr_t<0x007F'B0E8> HOCOTRR2_;
		static HOCOTRR2_ HOCOTRR2;
#endif

		//----  消費電力低減機能  ----------------------------------------------//

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

			bit_rw_t<io_, bitpos::B14>	OPE;
			bit_rw_t<io_, bitpos::B15>	SSBY;
		};
		typedef sbycr_t<0x0008'000C> SBYCR_;
		static SBYCR_ SBYCR;


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

			bit_rw_t<io_, bitpos::B0>	MSTPA0;
			bit_rw_t<io_, bitpos::B1>	MSTPA1;
			bit_rw_t<io_, bitpos::B2>	MSTPA2;
			bit_rw_t<io_, bitpos::B3>	MSTPA3;
			bit_rw_t<io_, bitpos::B4>	MSTPA4;
			bit_rw_t<io_, bitpos::B5>	MSTPA5;

			bit_rw_t<io_, bitpos::B7>	MSTPA7;

			bit_rw_t<io_, bitpos::B9>	MSTPA9;
			bit_rw_t<io_, bitpos::B10>	MSTPA10;
			bit_rw_t<io_, bitpos::B11>	MSTPA11;

			bit_rw_t<io_, bitpos::B13>	MSTPA13;
			bit_rw_t<io_, bitpos::B14>	MSTPA14;
			bit_rw_t<io_, bitpos::B15>	MSTPA15;
			bit_rw_t<io_, bitpos::B16>	MSTPA16;
			bit_rw_t<io_, bitpos::B17>	MSTPA17;

			bit_rw_t<io_, bitpos::B19>	MSTPA19;

			bit_rw_t<io_, bitpos::B23>	MSTPA23;
			bit_rw_t<io_, bitpos::B24>	MSTPA24;

			bit_rw_t<io_, bitpos::B27>	MSTPA27;
			bit_rw_t<io_, bitpos::B28>	MSTPA28;
			bit_rw_t<io_, bitpos::B29>	MSTPA29;

			bit_rw_t<io_, bitpos::B31>	ACSE;
		};
		typedef mstpcra_t<0x0008'0010> MSTPCRA_;
		static MSTPCRA_ MSTPCRA;


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
			bit_rw_t<io_, bitpos::B1>	MSTPB1;
			bit_rw_t<io_, bitpos::B2>	MSTPB2;

			bit_rw_t<io_, bitpos::B4>	MSTPB4;

			bit_rw_t<io_, bitpos::B6>	MSTPB6;

			bit_rw_t<io_, bitpos::B8>	MSTPB8;
			bit_rw_t<io_, bitpos::B9>	MSTPB9;
			bit_rw_t<io_, bitpos::B10>	MSTPB10;
			bit_rw_t<io_, bitpos::B11>	MSTPB11;
			bit_rw_t<io_, bitpos::B12>	MSTPB12;
			bit_rw_t<io_, bitpos::B13>	MSTPB13;

			bit_rw_t<io_, bitpos::B14>	MSTPB14;
			bit_rw_t<io_, bitpos::B15>	MSTPB15;
			bit_rw_t<io_, bitpos::B16>	MSTPB16;
			bit_rw_t<io_, bitpos::B17>	MSTPB17;
			bit_rw_t<io_, bitpos::B18>	MSTPB18;
			bit_rw_t<io_, bitpos::B19>	MSTPB19;
			bit_rw_t<io_, bitpos::B20>	MSTPB20;
			bit_rw_t<io_, bitpos::B21>	MSTPB21;
			bit_rw_t<io_, bitpos::B22>	MSTPB22;
			bit_rw_t<io_, bitpos::B23>	MSTPB23;
			bit_rw_t<io_, bitpos::B24>	MSTPB24;
			bit_rw_t<io_, bitpos::B25>	MSTPB25;
			bit_rw_t<io_, bitpos::B26>	MSTPB26;
			bit_rw_t<io_, bitpos::B27>	MSTPB27;
			bit_rw_t<io_, bitpos::B28>	MSTPB28;
			bit_rw_t<io_, bitpos::B29>	MSTPB29;
			bit_rw_t<io_, bitpos::B30>	MSTPB30;
			bit_rw_t<io_, bitpos::B31>	MSTPB31;
		};
		typedef mstpcrb_t<0x0008'0014> MSTPCRB_;
		static MSTPCRB_ MSTPCRB;


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

			bit_rw_t<io_, bitpos::B2>	MSTPC2;	///< 拡張 RAM

			bit_rw_t<io_, bitpos::B6>	MSTPC6;
			bit_rw_t<io_, bitpos::B7>	MSTPC7;

			bit_rw_t<io_, bitpos::B17>	MSTPC17;

			bit_rw_t<io_, bitpos::B19>	MSTPC19;
			bit_rw_t<io_, bitpos::B22>	MSTPC22;	///< RSPI2
			bit_rw_t<io_, bitpos::B23>	MSTPC23;
			bit_rw_t<io_, bitpos::B24>	MSTPC24;
			bit_rw_t<io_, bitpos::B25>	MSTPC25;
			bit_rw_t<io_, bitpos::B26>	MSTPC26;
			bit_rw_t<io_, bitpos::B27>	MSTPC27;
			bit_rw_t<io_, bitpos::B28>	MSTPC28;	///< DRW2D
			bit_rw_t<io_, bitpos::B29>	MSTPC29;	///< GLCDC
		};
		typedef mstpcrc_t<0x0008'0018> MSTPCRC_;
		static MSTPCRC_ MSTPCRC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ D（MSTPCRD）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mstpcrd_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>	MSTPD0;
			bit_rw_t<io_, bitpos::B1>	MSTPD1;
			bit_rw_t<io_, bitpos::B2>	MSTPD2;
			bit_rw_t<io_, bitpos::B3>	MSTPD3;
			bit_rw_t<io_, bitpos::B4>	MSTPD4;
			bit_rw_t<io_, bitpos::B5>	MSTPD5;
			bit_rw_t<io_, bitpos::B6>	MSTPD6;
			bit_rw_t<io_, bitpos::B7>	MSTPD7;

			bit_rw_t<io_, bitpos::B10>	MSTPD10;
			bit_rw_t<io_, bitpos::B11>	MSTPD11;
			bit_rw_t<io_, bitpos::B12>	MSTPD12;
			bit_rw_t<io_, bitpos::B11>	MSTPD13;
			bit_rw_t<io_, bitpos::B14>	MSTPD14;
			bit_rw_t<io_, bitpos::B15>	MSTPD15;

			bit_rw_t<io_, bitpos::B19>	MSTPD19;

			bit_rw_t<io_, bitpos::B21>	MSTPD21;

			bit_rw_t<io_, bitpos::B23>	MSTPD23;

			bit_rw_t<io_, bitpos::B26>	MSTPD26;
			bit_rw_t<io_, bitpos::B27>	MSTPD27;
		};
		typedef mstpcrd_t<0x0008'001C> MSTPCRD_;
		static MSTPCRD_ MSTPCRD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作電力コントロールレジスタ（OPCCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct opccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>	OPCM;

			bit_rw_t <io_, bitpos::B4>		OPCMTSF;
		};
		typedef opccr_t<0x0008'00A0> OPCCR_;
		static OPCCR_ OPCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スリープモード復帰クロックソース切り替えレジスタ（RSTCKCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstckcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>	RSTCKSEL;

			bit_rw_t <io_, bitpos::B4>		RSTCKEN;
		};
		typedef rstckcr_t<0x0008'00A1> RSTCKCR_;
		static RSTCKCR_ RSTCKCR;


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
		typedef dpsbycr_t<0x0008'C280> DPSBYCR_;
		static DPSBYCR_ DPSBYCR;








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

			bit_rw_t<io_, bitpos::B4>	TSOE;
			bit_rw_t<io_, bitpos::B7>	TSEN;
		};
		typedef tscr_t<0x0008'C500> TSCR_;
		static TSCR_ TSCR;


		//----  リセット  ------------------------------------------------------//

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
			@brief  ソフトウェアリセットレジスタ（SWRR）@n
					0xA501 を書き込むとリセットされます。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x0008'00C2> SWRR_;
		static SWRR_ SWRR;


#if defined(SIG_RX72M) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ノンキャッシャブル領域 n アドレスレジスタ (NCRGn) (n = 0, 1)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x0008'1040> NCRG0_;
		static NCRG0_ NCRG0;
		typedef rw32_t<0x0008'1048> NCRG1_;
		static NCRG1_ NCRG1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ノンキャッシャブル領域 n 設定レジスタ (NCRCn) (n = 0, 1)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct ncrcn_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B1>      NC1E;
			bit_rw_t <io_, bitpos::B2>      NC2E;
			bit_rw_t <io_, bitpos::B3>      NC3E;
			bits_rw_t<io_, bitpos::B4, 17>  NCSZ;
		};
		typedef ncrcn_t<0x0008'1044> NCRC0_;
		static NCRC0_ NCRC0;
		typedef ncrcn_t<0x0008'104C> NCRC1_;
		static NCRC1_ NCRC1;
#endif
	};
	template<class _> typename system_t<_>::SPCC_ system_t<_>::SPCC;
	template<class _> typename system_t<_>::OFS0_ system_t<_>::OFS0;
	template<class _> typename system_t<_>::OFS1_ system_t<_>::OFS1;
	template<class _> typename system_t<_>::MDE_ system_t<_>::MDE;

	template<class _> typename system_t<_>::MDMONR_ system_t<_>::MDMONR;
	template<class _> typename system_t<_>::MDSR_ system_t<_>::MDSR;
	template<class _> typename system_t<_>::SYSCR0_ system_t<_>::SYSCR0;
	template<class _> typename system_t<_>::SYSCR1_ system_t<_>::SYSCR1;
	template<class _> typename system_t<_>::SCKCR_ system_t<_>::SCKCR;
#if defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX72N)
	template<class _> typename system_t<_>::MEMWAIT_ system_t<_>::MEMWAIT;
#endif
#if defined(SIG_RX65N)
	template<class _> typename system_t<_>::ROMWT_ system_t<_>::ROMWT;
#endif
	template<class _> typename system_t<_>::SCKCR2_ system_t<_>::SCKCR2;
	template<class _> typename system_t<_>::SCKCR3_ system_t<_>::SCKCR3;
	template<class _> typename system_t<_>::PLLCR_ system_t<_>::PLLCR;
	template<class _> typename system_t<_>::PLLCR2_ system_t<_>::PLLCR2;
	template<class _> typename system_t<_>::BCKCR_ system_t<_>::BCKCR;
	template<class _> typename system_t<_>::MOSCCR_ system_t<_>::MOSCCR;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
	template<class _> typename system_t<_>::SOSCCR_ system_t<_>::SOSCCR;
#endif
	template<class _> typename system_t<_>::LOCOCR_ system_t<_>::LOCOCR;
	template<class _> typename system_t<_>::ILOCOCR_ system_t<_>::ILOCOCR;
	template<class _> typename system_t<_>::HOCOCR_ system_t<_>::HOCOCR;
	template<class _> typename system_t<_>::HOCOCR2_ system_t<_>::HOCOCR2;
	template<class _> typename system_t<_>::OSCOVFSR_ system_t<_>::OSCOVFSR;
	template<class _> typename system_t<_>::OSTDCR_ system_t<_>::OSTDCR;
	template<class _> typename system_t<_>::OSTDSR_ system_t<_>::OSTDSR;
	template<class _> typename system_t<_>::MOSCWTCR_ system_t<_>::MOSCWTCR;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
	template<class _> typename system_t<_>::SOSCWTCR_ system_t<_>::SOSCWTCR;
#endif
	template<class _> typename system_t<_>::MOFCR_ system_t<_>::MOFCR;
	template<class _> typename system_t<_>::HOCOPCR_ system_t<_>::HOCOPCR;

#if defined(SIG_RX72M) || defined(SIG_RX72N)
	template<class _> typename system_t<_>::CKOCR_ system_t<_>::CKOCR;
	template<class _> typename system_t<_>::PACKCR_ system_t<_>::PACKCR;
	template<class _> typename system_t<_>::PPLLCR_ system_t<_>::PPLLCR;
	template<class _> typename system_t<_>::PPLLCR2_ system_t<_>::PPLLCR2;
	template<class _> typename system_t<_>::PPLLCR3_ system_t<_>::PPLLCR3;
#endif

	template<class _> typename system_t<_>::SBYCR_ system_t<_>::SBYCR;
	template<class _> typename system_t<_>::MSTPCRA_ system_t<_>::MSTPCRA;
	template<class _> typename system_t<_>::MSTPCRB_ system_t<_>::MSTPCRB;
	template<class _> typename system_t<_>::MSTPCRC_ system_t<_>::MSTPCRC;
	template<class _> typename system_t<_>::MSTPCRD_ system_t<_>::MSTPCRD;
	template<class _> typename system_t<_>::OPCCR_ system_t<_>::OPCCR;
	template<class _> typename system_t<_>::RSTCKCR_ system_t<_>::RSTCKCR;
	template<class _> typename system_t<_>::DPSBYCR_ system_t<_>::DPSBYCR;
	template<class _> typename system_t<_>::PRCR_ system_t<_>::PRCR;
	template<class _> typename system_t<_>::TSCR_ system_t<_>::TSCR;
	template<class _> typename system_t<_>::RSTSR0_ system_t<_>::RSTSR0;
	template<class _> typename system_t<_>::RSTSR1_ system_t<_>::RSTSR1;
	template<class _> typename system_t<_>::RSTSR2_ system_t<_>::RSTSR2;
	template<class _> typename system_t<_>::SWRR_ system_t<_>::SWRR;

#if defined(SIG_RX72M) || defined(SIG_RX72N)
	template<class _> typename system_t<_>::NCRG0_ system_t<_>::NCRG0;
	template<class _> typename system_t<_>::NCRG1_ system_t<_>::NCRG1;
	template<class _> typename system_t<_>::NCRC0_ system_t<_>::NCRC0;
	template<class _> typename system_t<_>::NCRC1_ system_t<_>::NCRC1;
#endif

	typedef system_t<void> SYSTEM;
}
