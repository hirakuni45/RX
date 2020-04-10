#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX72M/RX651/RX65N/RX66T/RX72T システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2020 Kunihito Hiramatsu @n
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
	struct system_t_ {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  シリアルプログラマコマンド制御レジスタ（SPCC）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct spcc_t_ : public ro32_t<base> {
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
		struct ofs0_t_ : public ro32_t<base> {
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
		struct ofs1_t_ : public ro32_t<base> {
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
		struct mde_t_ : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 3> MDE;
		};

#if defined(SIG_RX65N)
		typedef spcc_t_<0xFE7F5D40> spcc_t;
		typedef ofs0_t_<0xFE7F5D04> ofs0_t;
		typedef ofs1_t_<0xFE7F5D08> ofs1_t;
		typedef mde_t_ <0xFE7F5D00> mde_t;
#else
		typedef spcc_t_<0x00120040> spcc_t;
		typedef ofs0_t_<0x00120068> ofs0_t;
		typedef ofs1_t_<0x0012006C> ofs1_t;
		typedef mde_t_ <0x00120064> mde_t;
#endif

		static spcc_t SPCC;
		static ofs0_t OFS0;
		static ofs1_t OFS1;
		static mde_t  MDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードモニタレジスタ（MDMONR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mdmonr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  MD;
		};
		typedef mdmonr_t_<0x00080000> mdmonr_t;
		static mdmonr_t MDMONR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードステータスレジスタ（MDSR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mdsr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B5>  UBTS;
		};
		typedef mdsr_t_<0x00080002> mdsr_t;
		static mdsr_t MDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムコントロールレジスタ 0（SYSCR0）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct syscr0_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ROME;
			bit_rw_t <io_, bitpos::B1>     EXBE;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		typedef syscr0_t_<0x00080006> syscr0_t;
		static syscr0_t SYSCR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムコントロールレジスタ 1（SYSCR1）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct syscr1_t_ : public rw16_t<base> {
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
		typedef syscr1_t_<0x00080008> syscr1_t;
		static syscr1_t SYSCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ（SCKCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sckcr_t_ : public rw32_t<base> {
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
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
			bit_rw_t <io_, bitpos::B22>    PSTOP0;
#endif
			bit_rw_t <io_, bitpos::B23>    PSTOP1;
			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		typedef sckcr_t_<0x00080020> sckcr_t;
		static sckcr_t SCKCR;


#if defined(SIG_RX71M)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct memwait_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MEMWAIT;
		};
		typedef memwait_t_<0x00086610> memwait_t;
		static memwait_t MEMWAIT;

#elif defined(SIG_RX72M) || defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX72N)
		template<uint32_t base>
		struct memwait_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MEMWAIT;
		};
		typedef memwait_t_<0x0008101C> memwait_t;
		static memwait_t MEMWAIT;
#endif


#if defined(SIG_RX65N)
  		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romwt_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> ROMWT;
		};
		typedef romwt_t_<0x0008101C> romwt_t;
		static romwt_t ROMWT;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ 2（SCKCR2）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sckcr2_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B4, 4> UCK;
		};
		typedef sckcr2_t_<0x00080024> sckcr2_t;
		static sckcr2_t SCKCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  システムクロックコントロールレジスタ 3（SCKCR3）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct sckcr3_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 3> CKSEL;
		};
		typedef sckcr3_t_<0x00080026> sckcr3_t;
		static sckcr3_t SCKCR3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL コントロールレジスタ（PLLCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pllcr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> PLIDIV;
			bit_rw_t <io_, bitpos::B4>    PLLSRCSEL;
			bits_rw_t<io_, bitpos::B8, 6> STC;
		};
		typedef pllcr_t_<0x00080028> pllcr_t;
		static pllcr_t PLLCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PLL コントロールレジスタ 2（PLLCR2）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pllcr2_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PLLEN;
		};
		typedef pllcr2_t_<0x0008002A> pllcr2_t;
		static pllcr2_t PLLCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バスクロックコントロールレジスタ（BCKCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct bckcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> BCLKDIV;
		};
		typedef bckcr_t_<0x00080030> bckcr_t;
		static bckcr_t BCKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器コントロールレジスタ（MOSCCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mosccr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MOSTP;
		};
		typedef mosccr_t_<0x00080032> mosccr_t;
		static mosccr_t MOSCCR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct sosccr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SOSTP;
		};
		typedef sosccr_t_<0x00080033> sosccr_t;
		static sosccr_t SOSCCR;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  低速オンチップオシレータコントロールレジスタ（LOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct lococr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> LCSTP;
		};
		typedef lococr_t_<0x00080034> lococr_t;
		static lococr_t LOCOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IWDT 専用オンチップオシレータコントロールレジスタ（ILOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ilococr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ILCSTP;
		};
		typedef ilococr_t_<0x00080035> ilococr_t;
		static ilococr_t ILOCOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  高速オンチップオシレータコントロールレジスタ（HOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct hococr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> HCSTP;
		};
		typedef hococr_t_<0x00080036> hococr_t;
		static hococr_t HOCOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	高速オンチップオシレータコントロールレジスタ 2（HOCOCR2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct hococr2_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> HCFRQ;
		};
		typedef hococr2_t_<0x00080037> hococr2_t;
		static hococr2_t HOCOCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振安定フラグレジスタ（OSCOVFSR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct oscovfsr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MOOVF;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
			bit_rw_t<io_, bitpos::B1> SOOVF;
#endif
			bit_rw_t<io_, bitpos::B2> PLOVF;
			bit_rw_t<io_, bitpos::B3> HCOVF;
			bit_rw_t<io_, bitpos::B4> ILCOVF;
#if defined(SIG_RX72M)
			bit_rw_t<io_, bitpos::B5> PPLOVF;
#endif
		};
		typedef oscovfsr_t_<0x0008003C> oscovfsr_t;
		static oscovfsr_t OSCOVFSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振停止検出コントロールレジスタ（OSTDCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ostdcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OSTDIE;

			bit_rw_t<io_, bitpos::B7> OSTDE;
		};
		typedef ostdcr_t_<0x00080040> ostdcr_t;
		static ostdcr_t OSTDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振停止検出ステータスレジスタ（OSTDSR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ostdsr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OSTDF;
		};
		typedef ostdsr_t_<0x00080041> ostdsr_t;
		static ostdsr_t OSTDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器ウェイトコントロールレジスタ（MOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x000800A2> moscwtcr_t;
		static moscwtcr_t MOSCWTCR;


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x000800A3> soscwtcr_t;
		static soscwtcr_t SOSCWTCR;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メインクロック発振器強制発振コントロールレジスタ（MOFCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mofcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
			bit_rw_t <io_, bitpos::B0>     MOFXIN;
#endif
			bits_rw_t<io_, bitpos::B4, 2>  MODRV2;
			bit_rw_t <io_, bitpos::B6>     MOSEL;
		};
		typedef mofcr_t_<0x0008C293> mofcr_t;
		static mofcr_t MOFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  高速オンチップオシレータ電源コントロールレジスタ（HOCOPCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct hocopcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>	HOCOPCNT;
		};
		typedef hocopcr_t_<0x0008C294> hocopcr_t;
		static hocopcr_t HOCOPCR;


#if defined(SIG_RX72M) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CLKOUT 出力コントロールレジスタ (CKOCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ckocr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8,  3>  CKOSEL;

			bits_rw_t<io_, bitpos::B12, 3>  CKODIV;
			bit_rw_t <io_, bitpos::B15>     CKOSTP;
		};
		typedef ckocr_t_<0x0008003E> ckocr_t;
		static ckocr_t CKOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  特定用途向けクロック制御レジスタ (PACKCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct packcr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>   OUTCKSEL;

			bit_rw_t<io_, bitpos::B8>   EPLLSEL;

			bit_rw_t<io_, bitpos::B12>  UPLLSEL;
		};
		typedef packcr_t_<0x00080044> packcr_t;
		static packcr_t PACKCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PPLL コントロールレジスタ (PPLLCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ppllcr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  PPLIDIV;

			bits_rw_t<io_, bitpos::B8, 6>  PPLSTC;
		};
		typedef ppllcr_t_<0x00080048> ppllcr_t;
		static ppllcr_t PPLLCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PPLL コントロールレジスタ 2 (PPLLCR2)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ppllcr2_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  PPLLEN;
		};
		typedef ppllcr2_t_<0x0008004A> ppllcr2_t;
		static ppllcr2_t PPLLCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PPLL コントロールレジスタ 3 (PPLLCR3)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct ppllcr3_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  PPLCK;
		};
		typedef ppllcr3_t_<0x0008004B> ppllcr3_t;
		static ppllcr3_t PPLLCR3;
#endif

//-----------------------------------------------------------------------------//

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スタンバイコントロールレジスタ（SBYCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct sbycr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B14>	OPE;
			bit_rw_t<io_, bitpos::B15>	SSBY;
		};
		typedef sbycr_t_<0x0008000C> sbycr_t;
		static sbycr_t SBYCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ A（MSTPCRA）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mstpcra_t_ : public rw32_t<base> {
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
		typedef mstpcra_t_<0x00080010> mstpcra_t;
		static mstpcra_t MSTPCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ B（MSTPCRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mstpcrb_t_ : public rw32_t<base> {
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
#if defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
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
		typedef mstpcrb_t_<0x00080014> mstpcrb_t;
		static mstpcrb_t MSTPCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ C（MSTPCRC）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mstpcrc_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>	MSTPC0;
#if defined(SIG_RX72M) || defined(SIG_RX72N)
			bit_rw_t<io_, bitpos::B2>	MSTPC2;	///< 拡張 RAM
#endif
			bit_rw_t<io_, bitpos::B6>	MSTPC6;
			bit_rw_t<io_, bitpos::B7>	MSTPC7;

			bit_rw_t<io_, bitpos::B17>	MSTPC17;

			bit_rw_t<io_, bitpos::B19>	MSTPC19;
#if defined(SIG_RX72M) || defined(SIG_RX72N)
			bit_rw_t<io_, bitpos::B22>	MSTPC22;	///< RSPI2
#endif
			bit_rw_t<io_, bitpos::B23>	MSTPC23;
			bit_rw_t<io_, bitpos::B24>	MSTPC24;
			bit_rw_t<io_, bitpos::B25>	MSTPC25;
			bit_rw_t<io_, bitpos::B26>	MSTPC26;
			bit_rw_t<io_, bitpos::B27>	MSTPC27;
#if defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
			bit_rw_t<io_, bitpos::B28>	MSTPC28;	///< DRW2D
			bit_rw_t<io_, bitpos::B29>	MSTPC29;	///< GLCDC
#endif
		};
		typedef mstpcrc_t_<0x00080018> mstpcrc_t;
		static mstpcrc_t MSTPCRC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モジュールストップコントロールレジスタ D（MSTPCRD）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct mstpcrd_t_ : public rw32_t<base> {
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
#if defined(SIG_RX65N)
			bit_rw_t<io_, bitpos::B11>	MSTPD13;
#endif
			bit_rw_t<io_, bitpos::B14>	MSTPD14;
			bit_rw_t<io_, bitpos::B15>	MSTPD15;

			bit_rw_t<io_, bitpos::B19>	MSTPD19;

			bit_rw_t<io_, bitpos::B21>	MSTPD21;

			bit_rw_t<io_, bitpos::B23>	MSTPD23;
		};
		typedef mstpcrd_t_<0x0008001C> mstpcrd_t;
		static mstpcrd_t MSTPCRD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作電力コントロールレジスタ（OPCCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct opccr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>	OPCM;
			bit_rw_t <io_, bitpos::B4>		OPCMTSF;
		};
		typedef opccr_t_<0x000800A0> opccr_t;
		static opccr_t OPCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スリープモード復帰クロックソース切り替えレジスタ（RSTCKCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstckcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>	RSTCKSEL;
			bit_rw_t <io_, bitpos::B4>		RSTCKEN;
		};
		typedef rstckcr_t_<0x000800A1> rstckcr_t;
		static rstckcr_t RSTCKCR;


//-----------------------------------------------------------------------------//


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ディープスタンバイコントロールレジスタ（DPSBYCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct dpsbycr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  DEEPCUT;
			bit_rw_t <io_, bitpos::B6>	   IOKEEP;
			bit_rw_t <io_, bitpos::B7>	   DPSBY;
		};
		typedef dpsbycr_t_<0x0008C280> dpsbycr_t;
		static dpsbycr_t DPSBYCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  プロテクトレジスタ（PRCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct prcr_t_ : public rw16_t<base> {
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
		typedef prcr_t_<0x000803FE> prcr_t;
		static prcr_t PRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサコントロールレジスタ（TSCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tscr_t_ : public  rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>	TSOE;
			bit_rw_t<io_, bitpos::B7>	TSEN;
		};
		typedef tscr_t_<0x0008C500> tscr_t;
		static tscr_t TSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 0（RSTSR0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstsr0_t_ : public rw8_t<base> {
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
		typedef rstsr0_t_<0x0008C290> rstsr0_t;
		static rstsr0_t RSTSR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 1（RSTSR1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstsr1_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CWSF;
		};
		typedef rstsr1_t_<0x0008C291> rstsr1_t;
		static rstsr1_t RSTSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 2（RSTSR2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstsr2_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  IWDTRF;
			bit_rw_t <io_, bitpos::B1>  WDTRF;
			bit_rw_t <io_, bitpos::B2>  SWRF;
		};
		typedef rstsr2_t_<0x000800C0> rstsr2_t;
		static rstsr2_t RSTSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ソフトウェアリセットレジスタ（SWRR）@n
					0xA501 を書き込むとリセットされます。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x000800C2> swrr_t;
		static swrr_t SWRR;


#if defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX72M) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM キャッシュ許可レジスタ（ ROMCE ）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romce_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  ROMCEN;
		};
		typedef romce_t_<0x00081000> romce_t;
		static romce_t ROMCE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM キャッシュ無効化レジスタ（ ROMCIV ）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romciv_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  ROMCIV;
		};
		typedef romciv_t_<0x00081004> romciv_t;
		static romciv_t ROMCIV;
#endif


#if defined(SIG_RX72M) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ノンキャッシャブル領域 n アドレスレジスタ (NCRGn) (n = 0, 1)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00081040> ncrg0_t;
		static ncrg0_t NCRG0;
		typedef rw32_t<0x00081048> ncrg1_t;
		static ncrg1_t NCRG1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ノンキャッシャブル領域 n 設定レジスタ (NCRCn) (n = 0, 1)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct ncrcn_t_ : public rw32_t<base> {
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
		typedef ncrcn_t_<0x00081044> ncrc0_t;
		static ncrc0_t NCRC0;
		typedef ncrcn_t_<0x0008104C> ncrc1_t;
		static ncrc1_t NCRC1;
#endif
	};
	typedef system_t_<void> SYSTEM;

	template<class _> typename system_t_<_>::spcc_t     system_t_<_>::SPCC;
	template<class _> typename system_t_<_>:: ofs0_t     system_t_<_>::OFS0;
	template<class _> typename system_t_<_>:: ofs1_t     system_t_<_>::OFS1;
	template<class _> typename system_t_<_>:: mde_t      system_t_<_>::MDE;
	template<class _> typename system_t_<_>:: mdmonr_t   system_t_<_>::MDMONR;
	template<class _> typename system_t_<_>:: mdsr_t     system_t_<_>::MDSR;
	template<class _> typename system_t_<_>:: syscr0_t   system_t_<_>::SYSCR0;
	template<class _> typename system_t_<_>:: syscr1_t   system_t_<_>::SYSCR1;
	template<class _> typename system_t_<_>:: sckcr_t    system_t_<_>::SCKCR;
#if defined(SIG_RX72M) | defined(SIG_RX72M) || defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX72N)
	template<class _> typename system_t_<_>:: memwait_t  system_t_<_>::MEMWAIT;
#endif
#if defined(SIG_RX65N)
	template<class _> typename system_t_<_>:: romwt_t    system_t_<_>::ROMWT;
#endif
	template<class _> typename system_t_<_>:: sckcr2_t   system_t_<_>::SCKCR2;
	template<class _> typename system_t_<_>:: sckcr3_t   system_t_<_>::SCKCR3;
	template<class _> typename system_t_<_>:: pllcr_t    system_t_<_>::PLLCR;
	template<class _> typename system_t_<_>:: pllcr2_t   system_t_<_>::PLLCR2;
	template<class _> typename system_t_<_>:: bckcr_t    system_t_<_>::BCKCR;
	template<class _> typename system_t_<_>:: mosccr_t   system_t_<_>::MOSCCR;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
	template<class _> typename system_t_<_>:: sosccr_t   system_t_<_>::SOSCCR;
#endif
	template<class _> typename system_t_<_>:: lococr_t   system_t_<_>::LOCOCR;
	template<class _> typename system_t_<_>:: ilococr_t  system_t_<_>::ILOCOCR;
	template<class _> typename system_t_<_>:: hococr_t   system_t_<_>::HOCOCR;
	template<class _> typename system_t_<_>:: hococr2_t  system_t_<_>::HOCOCR2;
	template<class _> typename system_t_<_>:: oscovfsr_t system_t_<_>::OSCOVFSR;
	template<class _> typename system_t_<_>:: ostdcr_t   system_t_<_>::OSTDCR;
	template<class _> typename system_t_<_>:: ostdsr_t   system_t_<_>::OSTDSR;
	template<class _> typename system_t_<_>:: moscwtcr_t system_t_<_>::MOSCWTCR;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX72N)
	template<class _> typename system_t_<_>:: soscwtcr_t system_t_<_>::SOSCWTCR;
#endif
	template<class _> typename system_t_<_>:: mofcr_t    system_t_<_>::MOFCR;
	template<class _> typename system_t_<_>:: hocopcr_t  system_t_<_>::HOCOPCR;
#if defined(SIG_RX72M) || defined(SIG_RX72N)
	template<class _> typename system_t_<_>:: ckocr_t    system_t_<_>::CKOCR;
#endif
#if defined(SIG_RX72M) || defined(SIG_RX72N)
	template<class _> typename system_t_<_>:: packcr_t   system_t_<_>::PACKCR;
	template<class _> typename system_t_<_>:: ppllcr_t   system_t_<_>::PPLLCR;
	template<class _> typename system_t_<_>:: ppllcr2_t  system_t_<_>::PPLLCR2;
	template<class _> typename system_t_<_>:: ppllcr3_t  system_t_<_>::PPLLCR3;
#endif
	template<class _> typename system_t_<_>:: sbycr_t   system_t_<_>::SBYCR;
	template<class _> typename system_t_<_>:: mstpcra_t system_t_<_>::MSTPCRA;
	template<class _> typename system_t_<_>:: mstpcrb_t system_t_<_>::MSTPCRB;
	template<class _> typename system_t_<_>:: mstpcrc_t system_t_<_>::MSTPCRC;
	template<class _> typename system_t_<_>:: mstpcrd_t system_t_<_>::MSTPCRD;
	template<class _> typename system_t_<_>:: opccr_t   system_t_<_>::OPCCR;
	template<class _> typename system_t_<_>:: rstckcr_t system_t_<_>::RSTCKCR;
	template<class _> typename system_t_<_>:: dpsbycr_t system_t_<_>::DPSBYCR;
	template<class _> typename system_t_<_>:: prcr_t    system_t_<_>::PRCR;
	template<class _> typename system_t_<_>:: tscr_t    system_t_<_>::TSCR;
	template<class _> typename system_t_<_>:: rstsr0_t  system_t_<_>::RSTSR0;
	template<class _> typename system_t_<_>:: rstsr1_t  system_t_<_>::RSTSR1;
	template<class _> typename system_t_<_>:: rstsr2_t  system_t_<_>::RSTSR2;
	template<class _> typename system_t_<_>:: swrr_t    system_t_<_>::SWRR;
#if defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template<class _> typename system_t_<_>:: romce_t   system_t_<_>::ROMCE;
	template<class _> typename system_t_<_>:: romciv_t  system_t_<_>::ROMCIV;
#endif
#if defined(SIG_RX72M) || defined(SIG_RX72N)
	template<class _> typename system_t_<_>:: ncrg0_t    system_t_<_>::NCRG0;
	template<class _> typename system_t_<_>:: ncrg1_t    system_t_<_>::NCRG1;
	template<class _> typename system_t_<_>:: ncrc0_t   system_t_<_>::NCRC0;
	template<class _> typename system_t_<_>:: ncrc1_t   system_t_<_>::NCRC1;
#endif

}
