#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX72M/RX651/RX65N/RX66T グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2019 Kunihito Hiramatsu @n
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
#if defined(SIG_RX65N)
		static spcc_t<0xFE7F5D40> SPCC;
		static ofs0_t<0xFE7F5D04> OFS0;
		static ofs1_t<0xFE7F5D08> OFS1;
		static mde_t <0xFE7F5D00> MDE;
#else
		static spcc_t<0x00120040> SPCC;
		static ofs0_t<0x00120068> OFS0;
		static ofs1_t<0x0012006C> OFS1;
		static mde_t <0x00120064> MDE;
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
		static mdmonr_t<0x00080000> MDMONR;


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
		static mdsr_t<0x00080002> MDSR;


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
		static syscr0_t<0x00080006> SYSCR0;


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
			bit_rw_t<io_, bitpos::B7>  SBYRAME;
		};
		static syscr1_t<0x00080008> SYSCR1;


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
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
			bit_rw_t <io_, bitpos::B22>    PSTOP0;
#endif
			bit_rw_t <io_, bitpos::B23>    PSTOP1;
			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		static sckcr_t<0x00080020> SCKCR;


#if defined(SIG_RX71M)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT）
			@param[in]	base	ベース・アドレス
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
#elif defined(SIG_RX72M) || defined(SIG_RX66T)
		template<uint32_t base>
		struct memwait_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MEMWAIT;
		};
		static memwait_t<0x0008101C> MEMWAIT;
#endif


#if defined(SIG_RX65N)
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
		static romwt_t<0x0008101C> ROMWT;
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
		static sckcr2_t<0x00080024> SCKCR2;


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
		static sckcr3_t<0x00080026> SCKCR3;


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
		static pllcr_t<0x00080028> PLLCR;


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
		static pllcr2_t<0x0008002A> PLLCR2;


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
		static mosccr_t<0x00080032> MOSCCR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N)
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
		static sosccr_t<0x00080033> SOSCCR;
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
		static lococr_t<0x00080034> LOCOCR;


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
		static ilococr_t<0x00080035> ILOCOCR;


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
		static hococr_t<0x00080036> HOCOCR;


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
		static hococr2_t<0x00080037> HOCOCR2;


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
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N)
			bit_rw_t<io_, bitpos::B1> SOOVF;
#endif
			bit_rw_t<io_, bitpos::B2> PLOVF;
			bit_rw_t<io_, bitpos::B3> HCOVF;
			bit_rw_t<io_, bitpos::B4> ILCOVF;
		};
		static oscovfsr_t<0x0008003C> OSCOVFSR;


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
		static ostdcr_t<0x00080040> OSTDCR;


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
		static ostdsr_t<0x00080041> OSTDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器ウェイトコントロールレジスタ（MOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<0x000800A2> MOSCWTCR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<0x000800A3> SOSCWTCR;
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

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N)
			bit_rw_t <io_, bitpos::B0>     MOFXIN;
#endif
			bits_rw_t<io_, bitpos::B4, 2>  MODRV2;
			bit_rw_t <io_, bitpos::B6>     MOSEL;
		};
		static mofcr_t<0x0008C293> MOFCR;


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
		static hocopcr_t<0x0008C294> HOCOPCR;

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

			bit_rw_t<io_, bitpos::B14>	OPE;
			bit_rw_t<io_, bitpos::B15>	SSBY;
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
			bit_rw_t<io_, bitpos::B1>	MSTPB1;
			bit_rw_t<io_, bitpos::B2>	MSTPB2;

			bit_rw_t<io_, bitpos::B4>	MSTPB4;

			bit_rw_t<io_, bitpos::B6>	MSTPB6;

			bit_rw_t<io_, bitpos::B8>	MSTPB8;
			bit_rw_t<io_, bitpos::B9>	MSTPB9;
			bit_rw_t<io_, bitpos::B10>	MSTPB10;
#if defined(SIG_RX72M)
			bit_rw_t<io_, bitpos::B11>	MSTPB11;
#endif
			bit_rw_t<io_, bitpos::B12>	MSTPB12;

			bit_rw_t<io_, bitpos::B14>	MSTPB14;
			bit_rw_t<io_, bitpos::B15>	MSTPB15;
			bit_rw_t<io_, bitpos::B16>	MSTPB16;
			bit_rw_t<io_, bitpos::B17>	MSTPB17;

			bit_rw_t<io_, bitpos::B19>	MSTPB19;
#if defined(SIG_RX65N) || defined(SIG_RX72M)
			bit_rw_t<io_, bitpos::B20>	MSTPB20;
#endif
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
#if defined(SIG_RX72M)
			bit_rw_t<io_, bitpos::B2>	MSTPC2;
#endif
			bit_rw_t<io_, bitpos::B6>	MSTPC6;
			bit_rw_t<io_, bitpos::B7>	MSTPC7;

			bit_rw_t<io_, bitpos::B17>	MSTPC17;

			bit_rw_t<io_, bitpos::B19>	MSTPC19;
#if defined(SIG_RX72M)
			bit_rw_t<io_, bitpos::B22>	MSTPC22;
#endif
			bit_rw_t<io_, bitpos::B23>	MSTPC23;
			bit_rw_t<io_, bitpos::B24>	MSTPC24;
			bit_rw_t<io_, bitpos::B25>	MSTPC25;
			bit_rw_t<io_, bitpos::B26>	MSTPC26;
			bit_rw_t<io_, bitpos::B27>	MSTPC27;
#if defined(SIG_RX65N) || defined(SIG_RX72M)
			bit_rw_t<io_, bitpos::B28>	MSTPC28;
			bit_rw_t<io_, bitpos::B29>	MSTPC29;
#endif
		};
		static mstpcrc_t<0x00080018> MSTPCRC;


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

#if defined(SIG_RX72M)
			bit_rw_t<io_, bitpos::B11>	MSTPD11;
#endif
			bit_rw_t<io_, bitpos::B14>	MSTPD14;
			bit_rw_t<io_, bitpos::B15>	MSTPD15;

			bit_rw_t<io_, bitpos::B19>	MSTPD19;

			bit_rw_t<io_, bitpos::B21>	MSTPD21;

			bit_rw_t<io_, bitpos::B23>	MSTPD23;
		};
		static mstpcrd_t<0x0008001C> MSTPCRD;


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
		static opccr_t<0x000800A0> OPCCR;


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
		static rstckcr_t<0x000800A1> RSTCKCR;


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

			bit_rw_t <io_, bitpos::B0>	   PRC0;
			bit_rw_t <io_, bitpos::B1>	   PRC1;
			bit_rw_t <io_, bitpos::B3>     PRC3;
			bits_rw_t<io_, bitpos::B8, 8>  PRKEY;
		};
		static prcr_t<0x000803FE> PRCR;


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
		static tscr_t<0x0008C500> TSCR;


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
		static rstsr0_t<0x0008C290> RSTSR0;


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
		static rstsr1_t<0x0008C291> RSTSR1;


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
		static rstsr2_t<0x000800C0> RSTSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ソフトウェアリセットレジスタ（SWRR）@n
					0xA501 を書き込むとリセットされます。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw16_t<0x000800C2> SWRR;


#if defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM キャッシュ許可レジスタ（ ROMCE ）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romce_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  ROMCEN;
		};
		static romce_t<0x00081000> ROMCE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM キャッシュ無効化レジスタ（ ROMCIV ）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romciv_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  ROMCIV;
		};
		static romciv_t<0x00081004> ROMCIV;
#endif


#if defined(SIG_RX72M)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ノンキャッシャブル領域 n アドレスレジスタ (NCRGn) (n = 0, 1)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw32_t<0x00081040> NCRG0;
		static rw32_t<0x00081048> NCRG1;


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
		static ncrcn_t<0x00081044> NCRC0;
		static ncrcn_t<0x0008104C> NCRC1;
#endif
	};
	typedef system_t SYSTEM;
}
