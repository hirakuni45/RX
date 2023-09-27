#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・RSCI 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSCI 定義基底クラス (rsci_base_t)
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct rsci_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  製品機能選択肢 @n
					「製品機能選択レジスタ０」は、'system.hpp' に定義がある。
		*/
		//-----------------------------------------------------------------//
		enum class RXDSEL : uint8_t {
			RXD,	///< RXD 端子からの入力信号
			COMP3,	///< COMP3 レベル検出信号
			COMP4	///< COMP4 レベル検出信号
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  受信データレジスタ (RDR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rdr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>  RDAT;
			bit_rw_t <io_, bitpos::B9>	   MPB;
			bit_rw_t <io_, bitpos::B10>	   DR;
			bit_rw_t <io_, bitpos::B11>	   PER;
			bit_rw_t <io_, bitpos::B12>	   FER;

			bit_rw_t <io_, bitpos::B24>    ORER;

			bit_rw_t <io_, bitpos::B27>    APER;
			bit_rw_t <io_, bitpos::B28>    AFER;
		};
		typedef rdr_t<base + 0x00> RDR_;
		static  RDR_ RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信データレジスタ (TDR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tdr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>  TDAT;
			bit_rw_t <io_, bitpos::B9>	   MPBT;

			bit_rw_t <io_, bitpos::B12>	   SYNC;
		};
		typedef tdr_t<base + 0x04> TDR_;
		static  TDR_ TDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  制御レジスタ 0 (SCR0)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scr0_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     RE;

			bit_rw_t <io_, bitpos::B4>     TE;

			bit_rw_t <io_, bitpos::B8>     MPIE;
			bit_rw_t <io_, bitpos::B9>     DCME;
			bit_rw_t <io_, bitpos::B10>    IDSEL;

			bit_rw_t <io_, bitpos::B16>    RIE;

			bit_rw_t <io_, bitpos::B20>    TIE;
			bit_rw_t <io_, bitpos::B21>    TEIE;

			bit_rw_t <io_, bitpos::B24>    SSE;
		};
		typedef scr0_t<base + 0x08> SCR0_;
		static  SCR0_ SCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  制御レジスタ 1 (SCR1)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scr1_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CTSE;
			bit_rw_t <io_, bitpos::B1>     CRSEP;

			bit_rw_t <io_, bitpos::B4>     SPB2DT;
			bit_rw_t <io_, bitpos::B5>     SPB2IO;

			bit_rw_t <io_, bitpos::B8>     PE;
			bit_rw_t <io_, bitpos::B9>     PM;

			bit_rw_t <io_, bitpos::B12>    TINV;
			bit_rw_t <io_, bitpos::B13>    RINV;

			bit_rw_t <io_, bitpos::B16>    LOOP;

			bit_rw_t <io_, bitpos::B20>    HDSEL;

			bits_rw_t<io_, bitpos::B24, 3> NFCS;

			bit_rw_t <io_, bitpos::B28>    NFEN;
		};
		typedef scr1_t<base + 0x0C> SCR1_;
		static  SCR1_ SCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  制御レジスタ 2 (SCR2)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scr2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  BCP;

			bit_rw_t <io_, bitpos::B4>     BGDM;
			bit_rw_t <io_, bitpos::B5>     ABCS;
			bit_rw_t <io_, bitpos::B6>     ABCSE;

			bits_rw_t<io_, bitpos::B8, 8>  BRR;

			bit_rw_t <io_, bitpos::B16>    BRME;

			bits_rw_t<io_, bitpos::B20, 2> CKS;

			bits_rw_t<io_, bitpos::B24, 8> MDDR;
		};
		typedef scr2_t<base + 0x18> SCR2_;
		static  SCR2_ SCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  制御レジスタ 3 (SCR3)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scr3_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     CPHA;
			bit_rw_t <io_, bitpos::B1>     CPOL;

			bit_rw_t <io_, bitpos::B7>     SYNDIS;

			bits_rw_t<io_, bitpos::B8, 2>  CHR;

			bit_rw_t <io_, bitpos::B12>    DDIR;
			bit_rw_t <io_, bitpos::B13>    DINV;
			bit_rw_t <io_, bitpos::B14>    STOP;
			bit_rw_t <io_, bitpos::B15>    RXDESEL;
			bits_rw_t<io_, bitpos::B16, 3> MOD;
			bit_rw_t <io_, bitpos::B19>    MP;
			bit_rw_t <io_, bitpos::B20>    FM;
			bit_rw_t <io_, bitpos::B21>    DEEN;

			bits_rw_t<io_, bitpos::B24, 2> CKE;

			bit_rw_t <io_, bitpos::B28>    GM;
			bit_rw_t <io_, bitpos::B29>    BLK;
		};
		typedef scr3_t<base + 0x14> SCR3_;
		static  SCR3_ SCR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  制御レジスタ 4 (SCR4)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scr4_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>  CMPD;

			bit_rw_t <io_, bitpos::B16>    RTADJ;
			bit_rw_t <io_, bitpos::B17>    TTADJ;

			bits_rw_t<io_, bitpos::B24, 4> RTMG;
			bits_rw_t<io_, bitpos::B28, 4> TTMG;
		};
		typedef scr4_t<base + 0x18> SCR4_;
		static  SCR4_ SCR4;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ (SIMR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct simr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  IICDL;

			bit_rw_t <io_, bitpos::B8>     IICINTM;
			bit_rw_t <io_, bitpos::B9>     IICCSC;

			bit_rw_t <io_, bitpos::B13>    IICACKT;

			bit_rw_t <io_, bitpos::B16>    IICSTAREQ;
			bit_rw_t <io_, bitpos::B17>    IICRSTAREQ;
			bit_rw_t <io_, bitpos::B18>    IICSTPREQ;

			bits_rw_t<io_, bitpos::B20, 2> IICSDAS;
			bits_rw_t<io_, bitpos::B22, 2> IICSCLS;
		};
		typedef simr_t<base + 0x20> SIMR_;
		static  SIMR_ SIMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DE 信号制御レジスタ (DECR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct decr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     DELVL;

			bits_rw_t<io_, bitpos::B8,  5> DESU;

			bits_rw_t<io_, bitpos::B16, 5> DEHLD;
		};
		typedef decr_t<base + 0x30> DECR_;
		static  DECR_ DECR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスレジスタ (SSR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssr_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B4>   ERS;

			bit_ro_t <io_, bitpos::B15>  RXDMON;
			bit_ro_t <io_, bitpos::B16>  DCMF;
			bit_ro_t <io_, bitpos::B17>  DPER;
			bit_ro_t <io_, bitpos::B18>  DFER;

			bit_ro_t <io_, bitpos::B24>  ORER;

			bit_ro_t <io_, bitpos::B26>  MFF;
			bit_ro_t <io_, bitpos::B27>  APER;
			bit_ro_t <io_, bitpos::B28>  AFER;
			bit_ro_t <io_, bitpos::B29>  TDRE;
			bit_ro_t <io_, bitpos::B30>  TEND;
			bit_ro_t <io_, bitpos::B31>  RDRF;
		};
		typedef ssr_t<base + 0x48> SSR_;
		static  SSR_ SSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C ステータスレジスタ (SISR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sisr_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>   IICACKR;

			bit_ro_t <io_, bitpos::B3>   IICSTIF;
		};
		typedef sisr_t<base + 0x4C> SISR_;
		static  SISR_ SISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスクリアレジスタ (SSCR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sscr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B4>     ERSC;

			bit_rw_t <io_, bitpos::B16>    DCMFC;
			bit_rw_t <io_, bitpos::B17>    DPERC;
			bit_rw_t <io_, bitpos::B18>    DFERC;

			bit_rw_t <io_, bitpos::B24>    ORERC;

			bit_rw_t <io_, bitpos::B26>    MFFC;
			bit_rw_t <io_, bitpos::B27>    APERC;
			bit_rw_t <io_, bitpos::B28>    AFERC;
			bit_rw_t <io_, bitpos::B29>    TDREC;

			bit_rw_t <io_, bitpos::B31>    RDRFC;
		};
		typedef sscr_t<base + 0x68> SSCR_;
		static  SSCR_ SSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C ステータスクリアレジスタ (SISCR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct siscr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B3>     IICSTIFC;
		};
		typedef siscr_t<base + 0x6C> SISCR_;
		static  SISCR_ SISCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  HBS サポートモード制御レジスタ (HBSCR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct hbscr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     HBSE;

			bit_rw_t <io_, bitpos::B2>     AOE;
			bit_rw_t <io_, bitpos::B3>     LPS;
		};
		typedef hbscr_t<base + 0x1E> HBSCR_;
		static  HBSCR_ HBSCR;
	};
	template <uint32_t base> typename rsci_base_t<base>::RDR_   rsci_base_t<base>::RDR;
	template <uint32_t base> typename rsci_base_t<base>::TDR_   rsci_base_t<base>::TDR;
	template <uint32_t base> typename rsci_base_t<base>::SCR0_  rsci_base_t<base>::SCR0;
	template <uint32_t base> typename rsci_base_t<base>::SCR1_  rsci_base_t<base>::SCR1;
	template <uint32_t base> typename rsci_base_t<base>::SCR2_  rsci_base_t<base>::SCR2;
	template <uint32_t base> typename rsci_base_t<base>::SCR3_  rsci_base_t<base>::SCR3;
	template <uint32_t base> typename rsci_base_t<base>::SCR4_  rsci_base_t<base>::SCR4;
	template <uint32_t base> typename rsci_base_t<base>::SIMR_  rsci_base_t<base>::SIMR;
	template <uint32_t base> typename rsci_base_t<base>::DECR_  rsci_base_t<base>::DECR;
	template <uint32_t base> typename rsci_base_t<base>::SSR_   rsci_base_t<base>::SSR;
	template <uint32_t base> typename rsci_base_t<base>::SISR_  rsci_base_t<base>::SISR;
	template <uint32_t base> typename rsci_base_t<base>::SSCR_  rsci_base_t<base>::SSCR;
	template <uint32_t base> typename rsci_base_t<base>::SISCR_ rsci_base_t<base>::SISCR;
	template <uint32_t base> typename rsci_base_t<base>::HBSCR_ rsci_base_t<base>::HBSCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSCI9/RSCI11 定義クラス (RSCI)
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct rsci_9b_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  マンチェスタモード制御レジスタ (MMCR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mmcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     DECS;
			bit_rw_t <io_, bitpos::B1>     ENCS;
			bit_rw_t <io_, bitpos::B2>     SADJE;

			bit_rw_t <io_, bitpos::B4>     SBPTN;
			bit_rw_t <io_, bitpos::B5>     SYNCE;
			bit_rw_t <io_, bitpos::B6>     SBLEN;

			bits_rw_t<io_, bitpos::B8,  4> TPLEN;
			bits_rw_t<io_, bitpos::B12, 2> TPPAT;

			bits_rw_t<io_, bitpos::B16, 4> RPLEN;
			bits_rw_t<io_, bitpos::B20, 2> RPPAT;

			bit_rw_t <io_, bitpos::B24>    PFERIE;
			bit_rw_t <io_, bitpos::B25>    SYERIE;
			bit_rw_t <io_, bitpos::B26>    SBERIE;
		};
		typedef mmcr_t<base + 0x2C> MMCR_;
		static  MMCR_ MMCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  拡張シリアルモード制御レジスタ 0 (XCR0)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct xcr0_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> TCSS;

			bit_rw_t <io_, bitpos::B8>     BFE;
			bit_rw_t <io_, bitpos::B9>     CF0RE;
			bits_rw_t<io_, bitpos::B10, 2> CF1DS;
			bit_rw_t <io_, bitpos::B12>    PIBE;
			bits_rw_t<io_, bitpos::B13, 3> PIBS;
			bit_rw_t <io_, bitpos::B16>    BFOIE;
			bit_rw_t <io_, bitpos::B17>    BCDIE;

			bit_rw_t <io_, bitpos::B20>    BFDIE;
			bit_rw_t <io_, bitpos::B21>    COFIE;
			bit_rw_t <io_, bitpos::B22>    AEDIE;

			bits_rw_t<io_, bitpos::B24, 2> BCCS;
		};
		typedef xcr0_t<base + 0x34> XCR0_;
		static  XCR0_ XCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  拡張シリアルモード制御レジスタ 1 (XCR1)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct xcr1_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     TCST;

			bit_rw_t <io_, bitpos::B4>     SDST;
			bit_rw_t <io_, bitpos::B5>     BRME;

			bits_rw_t<io_, bitpos::B8,  8> PCF1D;
			bits_rw_t<io_, bitpos::B16, 8> SCF1D;
			bits_rw_t<io_, bitpos::B24, 8> CF1CE;
		};
		typedef xcr1_t<base + 0x38> XCR1_;
		static  XCR1_ XCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  拡張シリアルモード制御レジスタ 2 (XCR2)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct xcr2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  CF0D;
			bits_rw_t<io_, bitpos::B8,  8>  CF0CE;
			bits_rw_t<io_, bitpos::B16, 16> BFLW;
		};
		typedef xcr2_t<base + 0x3C> XCR2_;
		static  XCR2_ XCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  マンチェスタモードステータスレジスタ (MMSR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mmsr_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0>  PFER;
			bit_ro_t<io_, bitpos::B1>  SYER;
			bit_ro_t<io_, bitpos::B2>  SBER;

			bit_ro_t<io_, bitpos::B4>  MCER;

			bit_ro_t<io_, bitpos::B6>  RSYNC;
		};
		typedef mmsr_t<base + 0x58> MMSR_;
		static  MMSR_ MMSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  拡張シリアルモードステータスレジスタ 0 (XSR0)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct xsr0_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>     SFSF;
			bit_ro_t <io_, bitpos::B1>     RXDSF;

			bit_ro_t <io_, bitpos::B8>     BFOF;
			bit_ro_t <io_, bitpos::B9>     BCDF;
			bit_ro_t <io_, bitpos::B10>    BFDF;
			bit_ro_t <io_, bitpos::B11>    CF0MF;
			bit_ro_t <io_, bitpos::B12>    CF1MF;
			bit_ro_t <io_, bitpos::B13>    PIBDF;
			bit_ro_t <io_, bitpos::B14>    COF;
			bit_ro_t <io_, bitpos::B15>    AEDF;

			bits_ro_t<io_, bitpos::B16, 8> CF0RD;
			bits_ro_t<io_, bitpos::B24, 8> CF1RD;
		};
		typedef xsr0_t<base + 0x5C> XSR0_;
		static  XSR0_ XSR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  拡張シリアルモードステータスレジスタ 1 (XSR1)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct xsr1_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 16> CCV;
		};
		typedef xsr1_t<base + 0x60> XSR1_;
		static  XSR1_ XSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  マンチェスタモードステータスクリアレジスタ (MMSCR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct mmscr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     PFERC;
			bit_rw_t <io_, bitpos::B1>     SYERC;
			bit_rw_t <io_, bitpos::B2>     SBERC;

			bit_rw_t <io_, bitpos::B4>     MCERC;
		};
		typedef mmscr_t<base + 0x74> MMSCR_;
		static  MMSCR_ MMSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  拡張シリアルモードステータスクリアレジスタ (XSCR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct xscr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>     BFOC;
			bit_rw_t <io_, bitpos::B9>     BCDCL;
			bit_rw_t <io_, bitpos::B10>    BFDCL;
			bit_rw_t <io_, bitpos::B11>    CF0MCL;
			bit_rw_t <io_, bitpos::B12>    CF1MCL;
			bit_rw_t <io_, bitpos::B13>    PIBDCL;
			bit_rw_t <io_, bitpos::B14>    COFC;
			bit_rw_t <io_, bitpos::B15>    AEDCL;
		};
		typedef xscr_t<base + 0x78> XSCR_;
		static  XSCR_ XSCR;
	};
	template <uint32_t base> typename rsci_9b_t<base>::MMCR_  rsci_9b_t<base>::MMCR;
	template <uint32_t base> typename rsci_9b_t<base>::XCR0_  rsci_9b_t<base>::XCR0;
	template <uint32_t base> typename rsci_9b_t<base>::XCR1_  rsci_9b_t<base>::XCR1;
	template <uint32_t base> typename rsci_9b_t<base>::XCR2_  rsci_9b_t<base>::XCR2;
	template <uint32_t base> typename rsci_9b_t<base>::MMSR_  rsci_9b_t<base>::MMSR;
	template <uint32_t base> typename rsci_9b_t<base>::XSR0_  rsci_9b_t<base>::XSR0;
	template <uint32_t base> typename rsci_9b_t<base>::XSR1_  rsci_9b_t<base>::XSR1;
	template <uint32_t base> typename rsci_9b_t<base>::MMSCR_ rsci_9b_t<base>::MMSCR;
	template <uint32_t base> typename rsci_9b_t<base>::XSCR_  rsci_9b_t<base>::XSCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSCI8 定義クラス (RSCI)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込み
		@param[in]	rxi		受信割り込み
		@param[in]	tei		送信終了割り込み
		@param[in]	eri		エラー割り込み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::GROUPBL1 tei, ICU::GROUPBL1 eri>
	struct rsci8_t : public rsci_base_t<base> {

		typedef rsci_base_t<base> RSCI_BASE;

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLKB;	///< PCLK 周波数


		//-----------------------------------------------------------------//
		/*!
			@brief  製品機能選択
			@param[in]	sel	製品機能選択肢
		*/
		//-----------------------------------------------------------------//
		static void set_prdfr(typename RSCI_BASE::RXDSEL sel) noexcept
		{
			SYSTEM::PRDFR0.SCI8RXD = static_cast<uint8_t>(sel);
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSCI9 定義クラス (RSCI)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込み
		@param[in]	rxi		受信割り込み
		@param[in]	tei		送信終了割り込み
		@param[in]	eri		エラー割り込み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::GROUPBL1 tei, ICU::GROUPBL1 eri>
	struct rsci9_t : public rsci_base_t<base>, rsci_9b_t<base> {

		typedef rsci_base_t<base> RSCI_BASE;

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLKB;	///< PCLK 周波数


		//-----------------------------------------------------------------//
		/*!
			@brief  製品機能選択
			@param[in]	sel	製品機能選択肢
		*/
		//-----------------------------------------------------------------//
		static void set_prdfr(typename RSCI_BASE::RXDSEL sel) noexcept
		{
			SYSTEM::PRDFR0.SCI9RXD = static_cast<uint8_t>(sel);
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSCI11 定義クラス (RSCI)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込み
		@param[in]	rxi		受信割り込み
		@param[in]	tei		送信終了割り込み
		@param[in]	eri		エラー割り込み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::GROUPAL0 tei, ICU::GROUPAL0 eri>
	struct rscib_t : public rsci_base_t<base>, rsci_9b_t<base> {

		typedef rsci_base_t<base> RSCI_BASE;

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLKA;	///< PCLK 周波数


		//-----------------------------------------------------------------//
		/*!
			@brief  製品機能選択
			@param[in]	sel	製品機能選択肢
		*/
		//-----------------------------------------------------------------//
		static void set_prdfr(typename RSCI_BASE::RXDSEL sel) noexcept
		{
			SYSTEM::PRDFR0.SCI11RXD = static_cast<uint8_t>(sel);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO 制御レジスタ (FCR) RSCI11
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     DRES;

			bits_rw_t<io_, bitpos::B8, 5>  TTRG;

			bit_rw_t <io_, bitpos::B15>    TFRST;

			bits_rw_t<io_, bitpos::B16, 5> RTRG;

			bit_rw_t <io_, bitpos::B23>    RFRST;
			bits_rw_t<io_, bitpos::B24, 5> RSTRG;
		};
		typedef fcr_t<base + 0x24> FCR_;
		static  FCR_ FCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO ステータスレジスタ (RFSR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfsr_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>     DR;

			bits_ro_t<io_, bitpos::B8,  6> R;

			bits_ro_t<io_, bitpos::B16, 6> PEC;

			bits_ro_t<io_, bitpos::B24, 6> FEC;
		};
		typedef rfsr_t<base + 0x50> RFSR_;
		static  RFSR_ RFSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信 FIFO ステータスレジスタ (TFSR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tfsr_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0,  6> T;
		};
		typedef tfsr_t<base + 0x54> TFSR_;
		static  TFSR_ TFSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO ステータスクリアレジスタ (RFSCR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct rfscr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     DRC;
		};
		typedef rfscr_t<base + 0x70> RFSCR_;
		static  RFSCR_ RFSCR;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::GROUPAL0 tei, ICU::GROUPAL0 eri>
		typename rscib_t<base, per, txi, rxi, tei, eri>::FCR_   rscib_t<base, per, txi, rxi, tei, eri>::FCR;
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::GROUPAL0 tei, ICU::GROUPAL0 eri>
		typename rscib_t<base, per, txi, rxi, tei, eri>::RFSR_  rscib_t<base, per, txi, rxi, tei, eri>::RFSR;
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::GROUPAL0 tei, ICU::GROUPAL0 eri>
		typename rscib_t<base, per, txi, rxi, tei, eri>::TFSR_  rscib_t<base, per, txi, rxi, tei, eri>::TFSR;
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::GROUPAL0 tei, ICU::GROUPAL0 eri>
		typename rscib_t<base, per, txi, rxi, tei, eri>::RFSCR_ rscib_t<base, per, txi, rxi, tei, eri>::RFSCR;


	typedef rsci8_t<0x000A'1400, peripheral::RSCI8,  ICU::VECTOR::TXI8, ICU::VECTOR::RXI8,
		ICU::GROUPBL1::TEI8, ICU::GROUPBL1::ERI8>  RSCI8;
	typedef rsci9_t<0x000A'1480, peripheral::RSCI9,  ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::GROUPBL1::TEI9, ICU::GROUPBL1::ERI9>  RSCI9;
	typedef rscib_t<0x000E'2080, peripheral::RSCI11,  ICU::VECTOR::TXI11, ICU::VECTOR::RXI11,
		ICU::GROUPAL0::TEI11, ICU::GROUPAL0::ERI11>  RSCI11;
}
