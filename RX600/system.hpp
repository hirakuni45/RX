#pragma once
//=============================================================================//
/*!	@file
	@brief	システム定義関連 @n
			・RX64M @n
			・RX65N/RX651 @n
			・RX66N @n
			・RX660/RX671 @n
			・RX71M @n
			・RX72N/RX72M @n
			・RX66T/RX72T
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
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
	struct system_base_t {

		//
		//----  オプション設定メモリ  -------------------------------------------//
		//

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
			typedef ro32_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 2>  VDSEL;
			bit_ro_t <in_, bitpos::B2>     LVDAS;
			bit_ro_t <in_, bitpos::B8>     HOCOEN;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エンディアン選択レジスタ（MDE）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mde_t : public ro32_t<base> {
			typedef ro32_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 3> MDE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードモニタレジスタ（MDMONR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mdmonr_t : public ro16_t<base> {
			typedef ro16_t<base> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0>  MD;
		};
		static inline mdmonr_t<0x0008'0000> MDMONR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードステータスレジスタ（MDSR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct mdsr_t : public ro16_t<base> {
			typedef ro16_t<base> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B5>  UBTS;
		};


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
		static inline syscr0_t<0x0008'0006> SYSCR0;


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
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX72M) || defined(SIG_RX72N)
			bit_rw_t<io_, bitpos::B7>  SBYRAME;
#endif
		};
		static inline syscr1_t<0x0008'0008> SYSCR1;

		//
		//----  クロック発生回路  -----------------------------------------------//
		//

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

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66N) || defined(SIG_RX671) || defined(SIG_RX72M) || defined(SIG_RX72N)
			bit_rw_t <io_, bitpos::B22>    PSTOP0;
#endif
			bit_rw_t <io_, bitpos::B23>    PSTOP1;
			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		static inline sckcr_t<0x0008'0020> SCKCR;


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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT_null) ダミー
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct romwt_null_t : public rw8_null_t<base> {
			typedef rw8_null_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> ROMWT;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ 32（MEMWAIT）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct memwait32_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MEMWAIT;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ 8（MEMWAIT8）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct memwait8_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MEMWAIT;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT_null）ダミー
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct memwait_null_t : public rw8_null_t<base> {
			typedef rw8_null_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MEMWAIT;
		};


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

			bits_rw_t<io_, bitpos::B4,  4> UCK;

			bits_rw_t<io_, bitpos::B12, 4> CFDCK;
		};
		static inline sckcr2_t<0x0008'0024> SCKCR2;


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
		static inline bckcr_t<0x0008'0030> BCKCR;


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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR_null）ダミー
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct sosccr_null_t : public rw8_null_t<base> {
			typedef rw8_null_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SOSTP;
		};


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
		static inline hococr_t<0x0008'0036> HOCOCR;


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
		static inline hococr2_t<0x0008'0037> HOCOCR2;


#if defined(SIG_RX660) || defined(SIG_RX671)
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
		static inline fllcr1_t<0x0008'0039> FLLCR1;


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
		static inline fllcr2_t<0x0008'003A> FLLCR2;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発振安定フラグレジスタ（OSCOVFSR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct oscovfsr_t : public ro8_t<base> {
			typedef ro8_t<base> in_;
			using in_::operator ();

			bit_ro_t<in_, bitpos::B0> MOOVF;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72M) || defined(SIG_RX65N) || defined(SIG_RX66N) || defined(SIG_RX671) || defined(SIG_RX72N)
			bit_ro_t<in_, bitpos::B1> SOOVF;
#endif
			bit_ro_t<in_, bitpos::B2> PLOVF;
			bit_ro_t<in_, bitpos::B3> HCOVF;
			bit_ro_t<in_, bitpos::B4> ILCOVF;
#if defined(SIG_RX66N) || defined(SIG_RX72M) || defined(SIG_RX72T) || defined(SIG_RX72N)
			bit_ro_t<in_, bitpos::B5> PPLOVF;
#endif
		};
		static inline oscovfsr_t<0x0008'003C> OSCOVFSR;


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

			bits_rw_t<io_, bitpos::B0, 8> MSTS;
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

			bits_rw_t<io_, bitpos::B0, 8> SSTS;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR_null）ダミー
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct soscwtcr_null_t : public rw8_null_t<base> {
			typedef rw8_null_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> SSTS;
		};


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
		static inline mofcr_t<0x0008'C293> MOFCR;


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
		static inline hocopcr_t<0x0008'C294> HOCOPCR;


#if defined(SIG_RX66N) || defined(SIG_RX660) || defined(SIG_RX671) || defined(SIG_RX72N) || defined(SIG_RX72M)
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
		static inline ckocr_t<0x0008'003E> CKOCR;
#endif

#if defined(SIG_RX66N) || defined(SIG_RX72N) || defined(SIG_RX72M)
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
		static inline packcr_t<0x0008'0044> PACKCR;


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
		static inline ppllcr_t<0x0008'0048> PPLLCR;


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
		static inline ppllcr2_t<0x0008'004A> PPLLCR2;


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
		static inline ppllcr3_t<0x0008'004B> PPLLCR3;
#endif

#if defined(SIG_RX660) || defined(SIG_RX671)
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
		static inline sosccr2_t<0x0008'CC00> SOSCCR2;


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
		static inline bksccr_t<0x0008'CC01> BKSCCR;


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
		static inline hocotrr_t<0x007F'B0E0> HOCOTRR0;
		static inline hocotrr_t<0x007F'B0E4> HOCOTRR1;
		static inline hocotrr_t<0x007F'B0E8> HOCOTRR2;
#endif

		//
		//----  消費電力低減機能  ----------------------------------------------//
		//

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
		static inline sbycr_t<0x0008'000C> SBYCR;


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
		static inline mstpcrb_t<0x0008'0014> MSTPCRB;


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
		static inline mstpcrc_t<0x0008'0018> MSTPCRC;


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
		static inline mstpcrd_t<0x0008'001C> MSTPCRD;


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
		static inline opccr_t<0x0008'00A0> OPCCR;


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
		static inline rstckcr_t<0x0008'00A1> RSTCKCR;


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
		static inline dpsbycr_t<0x0008'C280> DPSBYCR;


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
		static inline tscr_t<0x0008'C500> TSCR;

#if defined(SIG_RX660)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサ校正データレジスタ (TSCDR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro32_t<0x007F'B17C> TSCDR;
#elif defined(SIG_RX671)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  温度センサ校正データレジスタ (TSCDR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline ro32_t<0xFE7F'7D7C> TSCDR;
#endif

		//
		//----  リセット  ------------------------------------------------------//
		//

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
			@brief  ソフトウェアリセットレジスタ（SWRR）@n
					0xA501 を書き込むとリセットされます。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<0x0008'00C2> SWRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ノンキャッシャブル領域 n アドレスレジスタ (NCRGn) (n = 0, 1)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<0x0008'1040> NCRG0;
		static inline rw32_t<0x0008'1048> NCRG1;


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
		static inline ncrcn_t<0x0008'1044> NCRC0;
		static inline ncrcn_t<0x0008'104C> NCRC1;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  バッテリバックアップ機能 RX671
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_batt_backup_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バックアップ領域電源ステータスレジスタ (BKPSR)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct bkpsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     PDDF;
		};
		static inline bkpsr_t<0x0008'CC46> BKPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タンパステータスレジスタ (TAMPSR)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct tampsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     TAMP0F;
			bit_rw_t <io_, bitpos::B1>     TAMP1F;
			bit_rw_t <io_, bitpos::B2>     TAMP2F;
		};
		static inline tampsr_t<0x0008'CC48> TAMPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タンパ制御レジスタ (TAMPCR)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct tampcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     TAMP0IE;
			bit_rw_t <io_, bitpos::B1>     TAMP1IE;
			bit_rw_t <io_, bitpos::B2>     TAMP2IE;

			bit_rw_t <io_, bitpos::B4>     TAMP0EE;
			bit_rw_t <io_, bitpos::B5>     TAMP1EE;
			bit_rw_t <io_, bitpos::B6>     TAMP2EE;
		};
		static inline tampcr_t<0x0008'CC49> TAMPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  時間キャプチャイベント制御レジスタ (TCECR)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct tcecr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     TCE0S;
			bit_rw_t <io_, bitpos::B1>     TCE1S;
			bit_rw_t <io_, bitpos::B2>     TCE2S;
		};
		static inline tcecr_t<0x0008'CC4A> TCECR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タンパ /RTCIC 入力制御レジスタ 1 (TAMPICR1)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct tampicr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CH0EN;
			bit_rw_t <io_, bitpos::B1>     CH1EN;
			bit_rw_t <io_, bitpos::B2>     CH2EN;
		};
		static inline tampicr1_t<0x0008'CC4C> TAMPICR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タンパ /RTCIC 入力制御レジスタ 2 (TAMPICR2)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct tampicr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CH0NFE;
			bit_rw_t <io_, bitpos::B1>     CH1NFE;
			bit_rw_t <io_, bitpos::B2>     CH2NFE;

			bit_rw_t <io_, bitpos::B4>     CH0TRG;
			bit_rw_t <io_, bitpos::B5>     CH1TRG;
			bit_rw_t <io_, bitpos::B6>     CH2TRG;
		};
		static inline tampicr2_t<0x0008'CC4D> TAMPICR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タンパ /RTCIC 入力モニタレジスタ (TAMPIMR)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct tampimr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CH0LVL;
			bit_rw_t <io_, bitpos::B1>     CH1LVL;
			bit_rw_t <io_, bitpos::B2>     CH2LVL;
		};
		static inline tampimr_t<0x0008'CC4E> TAMPIMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  バックアップレジスタ n (BKR[n]) (n = 0 ～ 127)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct bkr_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 127) { io_::index = j; } }

			bkr_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline bkr_t<0x0008'CE00> BKR;
	};


//-----------------------------------------------------------------------------//


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義クラス RX64M
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_64m_t : public system_base_t {

		static constexpr bool NCRGx_reg    = false;
		static constexpr bool NCRCx_reg    = false;

		// オプション設定メモリ
		static inline spcc_t<0x0012'0040> SPCC;
		static inline ofs0_t<0x0012'0068> OFS0;
		static inline ofs1_t<0x0012'006C> OFS1;
		static inline mde_t <0x0012'0064> MDE;

		static inline mdsr_t<0x0008'0002> MDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT_null）ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline memwait_null_t<0x0000'0000> MEMWAIT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT_null) ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline romwt_null_t<0x0000'0000> ROMWT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline sosccr_t<0x0008'0033> SOSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline soscwtcr_t<0x0008'00A3> SOSCWTCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義クラス RX65N/RX651
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_65x_t : public system_base_t {

		static constexpr bool NCRGx_reg    = false;
		static constexpr bool NCRCx_reg    = false;

		// オプション設定メモリ
		static inline spcc_t<0xFE7F'5D40> SPCC;
		static inline ofs0_t<0xFE7F'5D04> OFS0;
		static inline ofs1_t<0xFE7F'5D08> OFS1;
		static inline mde_t <0xFE7F'5D00> MDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT_null）ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline memwait_null_t<0x0000'0000> MEMWAIT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline romwt_t<0x0008'101C> ROMWT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline sosccr_t<0x0008'0033> SOSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline soscwtcr_t<0x0008'00A3> SOSCWTCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義クラス RX66N
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_66n_t : public system_base_t {

		static constexpr bool NCRGx_reg    = true;
		static constexpr bool NCRCx_reg    = true;

		// オプション設定メモリ
		static inline spcc_t<0xFE7F'5D40> SPCC;
		static inline ofs0_t<0xFE7F'5D04> OFS0;
		static inline ofs1_t<0xFE7F'5D08> OFS1;
		static inline mde_t <0xFE7F'5D00> MDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT_null）ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline memwait_null_t<0x0000'0000> MEMWAIT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT_null) ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline romwt_null_t<0x0000'0000> ROMWT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline sosccr_t<0x0008'0033> SOSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline soscwtcr_t<0x0008'00A3> SOSCWTCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義クラス RX660
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_660_t : public system_base_t, system_batt_backup_t {

		static constexpr bool NCRGx_reg    = false;
		static constexpr bool NCRCx_reg    = false;

		// オプション設定メモリ
		static inline spcc_t<0x0012'0040> SPCC;
		static inline ofs0_t<0x0012'0068> OFS0;
		static inline ofs1_t<0x0012'006C> OFS1;
		static inline mde_t <0x0012'0064> MDE;

		static inline mdsr_t<0x0008'0002> MDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT_null）ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline memwait_null_t<0x0000'0000> MEMWAIT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT_null) ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline romwt_null_t<0x0000'0000> ROMWT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline sosccr_t<0x0008'0033> SOSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline soscwtcr_t<0x0008'00A3> SOSCWTCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義クラス RX671
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_671_t : public system_base_t, system_batt_backup_t {

		static constexpr bool NCRGx_reg    = false;
		static constexpr bool NCRCx_reg    = false;

		// オプション設定メモリ
		static inline spcc_t<0x0012'0040> SPCC;
		static inline ofs0_t<0x0012'0068> OFS0;
		static inline ofs1_t<0x0012'006C> OFS1;
		static inline mde_t <0x0012'0064> MDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT_null）ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline memwait_null_t<0x0000'0000> MEMWAIT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline romwt_t<0x0008'101C> ROMWT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline sosccr_t<0x0008'0033> SOSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline soscwtcr_t<0x0008'00A3> SOSCWTCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義クラス RX71M
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_71m_t : public system_base_t {

		static constexpr bool NCRGx_reg    = false;
		static constexpr bool NCRCx_reg    = false;

		// オプション設定メモリ
		static inline spcc_t<0x0012'0040> SPCC;
		static inline ofs0_t<0x0012'0068> OFS0;
		static inline ofs1_t<0x0012'006C> OFS1;
		static inline mde_t <0x0012'0064> MDE;

		static inline mdsr_t<0x0008'0002> MDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ 32（MEMWAIT） @n
					※スーパーバイザモードでのみアクセス可能
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline memwait32_t<0x0008'6610> MEMWAIT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT_null) ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline romwt_null_t<0x0000'0000> ROMWT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline sosccr_t<0x0008'0033> SOSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline soscwtcr_t<0x0008'00A3> SOSCWTCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義クラス RX72N/RX72M
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_72n_72m_t : public system_base_t {

		static constexpr bool NCRGx_reg    = true;
		static constexpr bool NCRCx_reg    = true;

		// オプション設定メモリ
		static inline spcc_t<0xFE7F'5D40> SPCC;
		static inline ofs0_t<0xFE7F'5D04> OFS0;
		static inline ofs1_t<0xFE7F'5D08> OFS1;
		static inline mde_t <0xFE7F'5D00> MDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ 8（MEMWAIT）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline memwait8_t<0x0008'101C> MEMWAIT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT_null) ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline romwt_null_t<0x0000'0000> ROMWT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline sosccr_t<0x0008'0033> SOSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline soscwtcr_t<0x0008'00A3> SOSCWTCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義クラス RX66T/RX72T
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct system_66t_72t_t : public system_base_t {

		static constexpr bool NCRGx_reg    = false;
		static constexpr bool NCRCx_reg    = false;

		// オプション設定メモリ
		static inline spcc_t<0x0012'0040> SPCC;
		static inline ofs0_t<0x0012'0068> OFS0;
		static inline ofs1_t<0x0012'006C> OFS1;
		static inline mde_t <0x0012'0064> MDE;

		static inline mdsr_t<0x0008'0002> MDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  電圧レベル設定レジスタ (VOLSR)
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct volsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B2>     USBVON;

			bit_rw_t <io_, bitpos::B6>     PGAVLS;
			bit_rw_t <io_, bitpos::B7>     RICVLS;
		};
		static inline volsr_t<0x0008'C295> VOLSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ 8（MEMWAIT）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline memwait8_t<0x0008'101C> MEMWAIT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ROM ウェイトサイクル設定レジスタ (ROMWT_null) ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline romwt_null_t<0x0000'0000> ROMWT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器コントロールレジスタ（SOSCCR）ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline sosccr_null_t<0x0000'0000> SOSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）ダミー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline soscwtcr_null_t<0x0000'0000> SOSCWTCR;
	};

#if defined(SIG_RX64M)
	typedef system_64m_t SYSTEM;
#elif defined(SIG_RX65N) || defined(SIG_RX651)
	typedef system_65x_t SYSTEM;
#elif defined(SIG_RX66N)
	typedef system_66n_t SYSTEM;
#elif defined(SIG_RX660)
	typedef system_660_t SYSTEM;
#elif defined(SIG_RX671)
	typedef system_671_t SYSTEM;
#elif defined(SIG_RX71M)
	typedef system_71m_t SYSTEM;
#elif defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef system_72n_72m_t SYSTEM;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef system_66t_72t_t SYSTEM;
#endif
}
