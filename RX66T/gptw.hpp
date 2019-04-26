#pragma once
//=====================================================================//
/*!	@file
	@brief	RX66T GPTW 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  汎用 PWM タイマ・クラス
		@param[in]	base	ベースアドレス
		@param[in]	peri	ペリフェラル型
		@param[in]	gtcia	GTCIAn 割り込みベクタ
		@param[in]	gtcib	GTCIBn 割り込みベクタ
		@param[in]	gtcic	GTCICn 割り込みベクタ
		@param[in]	gtcid	GTCIDn 割り込みベクタ
		@param[in]	gdte	GDTEn  割り込みベクタ
		@param[in]	gtcie	GTCIEn 割り込みベクタ
		@param[in]	gtcif	GTCIFn 割り込みベクタ
		@param[in]	gtciu	GTCIUn 割り込みベクタ
		@param[in]	gtciv	GTCIVn 割り込みベクタ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral peri,
		ICU::VECTOR_SELA gtcia, ICU::VECTOR_SELA gtcib, ICU::VECTOR_SELA gtcic,
		ICU::VECTOR_SELA gtcid, ICU::VECTOR_SELA gdte,  ICU::VECTOR_SELA gtcie,
		ICU::VECTOR_SELA gtcif, ICU::VECTOR_SELA gtciu, ICU::VECTOR_SELA gtciv>
	struct gptw_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ書き込み保護レジスタ (GTWP)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtwp_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     WP;
			bit_rw_t <io_, bitpos::B1>     STRWP;
			bit_rw_t <io_, bitpos::B2>     STPWP;
			bit_rw_t <io_, bitpos::B3>     CLRWP;
			bit_rw_t <io_, bitpos::B4>     CMNWP;
			bits_rw_t<io_, bitpos::B8, 8>  KEY;
		};
		static gtwp_t<base + 0x00> GTWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマソフトウェアスタートレジスタ (GTSTR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtstr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CSTRT0;
			bit_rw_t <io_, bitpos::B1>  CSTRT1;
			bit_rw_t <io_, bitpos::B2>  CSTRT2;
			bit_rw_t <io_, bitpos::B3>  CSTRT3;
			bit_rw_t <io_, bitpos::B4>  CSTRT4;
			bit_rw_t <io_, bitpos::B5>  CSTRT5;
			bit_rw_t <io_, bitpos::B6>  CSTRT6;
			bit_rw_t <io_, bitpos::B7>  CSTRT7;
			bit_rw_t <io_, bitpos::B8>  CSTRT8;
			bit_rw_t <io_, bitpos::B9>  CSTRT9;
		};
		static gtstr_t<base + 0x04> GTSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマソフトウェアストップレジスタ (GTSTP)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtstp_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CSTOP0;
			bit_rw_t <io_, bitpos::B1>  CSTOP1;
			bit_rw_t <io_, bitpos::B2>  CSTOP2;
			bit_rw_t <io_, bitpos::B3>  CSTOP3;
			bit_rw_t <io_, bitpos::B4>  CSTOP4;
			bit_rw_t <io_, bitpos::B5>  CSTOP5;
			bit_rw_t <io_, bitpos::B6>  CSTOP6;
			bit_rw_t <io_, bitpos::B7>  CSTOP7;
			bit_rw_t <io_, bitpos::B8>  CSTOP8;
			bit_rw_t <io_, bitpos::B9>  CSTOP9;
		};
		static gtstp_t<base + 0x08> GTSTP;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマソフトウェアクリアレジスタ (GTCLR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtclr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CCLR0;
			bit_rw_t <io_, bitpos::B1>  CCLR1;
			bit_rw_t <io_, bitpos::B2>  CCLR2;
			bit_rw_t <io_, bitpos::B3>  CCLR3;
			bit_rw_t <io_, bitpos::B4>  CCLR4;
			bit_rw_t <io_, bitpos::B5>  CCLR5;
			bit_rw_t <io_, bitpos::B6>  CCLR6;
			bit_rw_t <io_, bitpos::B7>  CCLR7;
			bit_rw_t <io_, bitpos::B8>  CCLR8;
			bit_rw_t <io_, bitpos::B9>  CCLR9;
		};
		static gtclr_t<base + 0x0C> GTCLR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマスタート要因セレクトレジスタ (GTSSR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtssr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  SSGTRGAR;
			bit_rw_t <io_, bitpos::B1>  SSGTRGAF;
			bit_rw_t <io_, bitpos::B2>  SSGTRGBR;
			bit_rw_t <io_, bitpos::B3>  SSGTRGBF;
			bit_rw_t <io_, bitpos::B4>  SSGTRGCR;
			bit_rw_t <io_, bitpos::B5>  SSGTRGCF;
			bit_rw_t <io_, bitpos::B6>  SSGTRGDR;
			bit_rw_t <io_, bitpos::B7>  SSGTRGDF;
			bit_rw_t <io_, bitpos::B8>  SSCARBL;
			bit_rw_t <io_, bitpos::B9>  SSCARBH;
			bit_rw_t <io_, bitpos::B10> SSCAFBL;
			bit_rw_t <io_, bitpos::B11> SSCAFBH;
			bit_rw_t <io_, bitpos::B12> SSCBRAL;
			bit_rw_t <io_, bitpos::B13> SSCBRAH;
			bit_rw_t <io_, bitpos::B14> SSCBFAL;
			bit_rw_t <io_, bitpos::B15> SSCBFAH;
			bit_rw_t <io_, bitpos::B16> SSELCA;
			bit_rw_t <io_, bitpos::B17> SSELCB;
			bit_rw_t <io_, bitpos::B18> SSELCC;
			bit_rw_t <io_, bitpos::B19> SSELCD;
			bit_rw_t <io_, bitpos::B20> SSELCE;
			bit_rw_t <io_, bitpos::B21> SSELCF;
			bit_rw_t <io_, bitpos::B22> SSELCG;
			bit_rw_t <io_, bitpos::B23> SSELCH;

			bit_rw_t <io_, bitpos::B31> CSTRT;
		};
		static gtssr_t<base + 0x10> GTSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマストップ要因セレクトレジスタ (GTPSR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtpsr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  PSGTRGAR;
			bit_rw_t <io_, bitpos::B1>  PSGTRGAF;
			bit_rw_t <io_, bitpos::B2>  PSGTRGBR;
			bit_rw_t <io_, bitpos::B3>  PSGTRGBF;
			bit_rw_t <io_, bitpos::B4>  PSGTRGCR;
			bit_rw_t <io_, bitpos::B5>  PSGTRGCF;
			bit_rw_t <io_, bitpos::B6>  PSGTRGDR;
			bit_rw_t <io_, bitpos::B7>  PSGTRGDF;
			bit_rw_t <io_, bitpos::B8>  PSCARBL;
			bit_rw_t <io_, bitpos::B9>  PSCARBH;
			bit_rw_t <io_, bitpos::B10> PSCAFBL;
			bit_rw_t <io_, bitpos::B11> PSCAFBH;
			bit_rw_t <io_, bitpos::B12> PSCBRAL;
			bit_rw_t <io_, bitpos::B13> PSCBRAH;
			bit_rw_t <io_, bitpos::B14> PSCBFAL;
			bit_rw_t <io_, bitpos::B15> PSCBFAH;
			bit_rw_t <io_, bitpos::B16> PSELCA;
			bit_rw_t <io_, bitpos::B17> PSELCB;
			bit_rw_t <io_, bitpos::B18> PSELCC;
			bit_rw_t <io_, bitpos::B19> PSELCD;
			bit_rw_t <io_, bitpos::B20> PSELCE;
			bit_rw_t <io_, bitpos::B21> PSELCF;
			bit_rw_t <io_, bitpos::B22> PSELCG;
			bit_rw_t <io_, bitpos::B23> PSELCH;

			bit_rw_t <io_, bitpos::B31> CSTOP;
		};
		static gtpsr_t<base + 0x14> GTPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマクリア要因セレクトレジスタ (GTCSR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtcsr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CSGTRGAR;
			bit_rw_t <io_, bitpos::B1>  CSGTRGAF;
			bit_rw_t <io_, bitpos::B2>  CSGTRGBR;
			bit_rw_t <io_, bitpos::B3>  CSGTRGBF;
			bit_rw_t <io_, bitpos::B4>  CSGTRGCR;
			bit_rw_t <io_, bitpos::B5>  CSGTRGCF;
			bit_rw_t <io_, bitpos::B6>  CSGTRGDR;
			bit_rw_t <io_, bitpos::B7>  CSGTRGDF;
			bit_rw_t <io_, bitpos::B8>  CSCARBL;
			bit_rw_t <io_, bitpos::B9>  CSCARBH;
			bit_rw_t <io_, bitpos::B10> CSCAFBL;
			bit_rw_t <io_, bitpos::B11> CSCAFBH;
			bit_rw_t <io_, bitpos::B12> CSCBRAL;
			bit_rw_t <io_, bitpos::B13> CSCBRAH;
			bit_rw_t <io_, bitpos::B14> CSCBFAL;
			bit_rw_t <io_, bitpos::B15> CSCBFAH;
			bit_rw_t <io_, bitpos::B16> CSELCA;
			bit_rw_t <io_, bitpos::B17> CSELCB;
			bit_rw_t <io_, bitpos::B18> CSELCC;
			bit_rw_t <io_, bitpos::B19> CSELCD;
			bit_rw_t <io_, bitpos::B20> CSELCE;
			bit_rw_t <io_, bitpos::B21> CSELCF;
			bit_rw_t <io_, bitpos::B22> CSELCG;
			bit_rw_t <io_, bitpos::B23> CSELCH;

			bit_rw_t <io_, bitpos::B31> CCLR;
		};
		static gtcsr_t<base + 0x18> GTCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマカウントアップ要因セレクトレジスタ (GTUPSR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtupsr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  USGTRGAR;
			bit_rw_t <io_, bitpos::B1>  USGTRGAF;
			bit_rw_t <io_, bitpos::B2>  USGTRGBR;
			bit_rw_t <io_, bitpos::B3>  USGTRGBF;
			bit_rw_t <io_, bitpos::B4>  USGTRGCR;
			bit_rw_t <io_, bitpos::B5>  USGTRGCF;
			bit_rw_t <io_, bitpos::B6>  USGTRGDR;
			bit_rw_t <io_, bitpos::B7>  USGTRGDF;
			bit_rw_t <io_, bitpos::B8>  USCARBL;
			bit_rw_t <io_, bitpos::B9>  USCARBH;
			bit_rw_t <io_, bitpos::B10> USCAFBL;
			bit_rw_t <io_, bitpos::B11> USCAFBH;
			bit_rw_t <io_, bitpos::B12> USCBRAL;
			bit_rw_t <io_, bitpos::B13> USCBRAH;
			bit_rw_t <io_, bitpos::B14> USCBFAL;
			bit_rw_t <io_, bitpos::B15> USCBFAH;
			bit_rw_t <io_, bitpos::B16> USELCA;
			bit_rw_t <io_, bitpos::B17> USELCB;
			bit_rw_t <io_, bitpos::B18> USELCC;
			bit_rw_t <io_, bitpos::B19> USELCD;
			bit_rw_t <io_, bitpos::B20> USELCE;
			bit_rw_t <io_, bitpos::B21> USELCF;
			bit_rw_t <io_, bitpos::B22> USELCG;
			bit_rw_t <io_, bitpos::B23> USELCH;
		};
		static gtupsr_t<base + 0x1C> GTUPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマカウントダウン要因セレクトレジスタ (GTDNSR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtdnsr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  DSGTRGAR;
			bit_rw_t <io_, bitpos::B1>  DSGTRGAF;
			bit_rw_t <io_, bitpos::B2>  DSGTRGBR;
			bit_rw_t <io_, bitpos::B3>  DSGTRGBF;
			bit_rw_t <io_, bitpos::B4>  DSGTRGCR;
			bit_rw_t <io_, bitpos::B5>  DSGTRGCF;
			bit_rw_t <io_, bitpos::B6>  DSGTRGDR;
			bit_rw_t <io_, bitpos::B7>  DSGTRGDF;
			bit_rw_t <io_, bitpos::B8>  DSCARBL;
			bit_rw_t <io_, bitpos::B9>  DSCARBH;
			bit_rw_t <io_, bitpos::B10> DSCAFBL;
			bit_rw_t <io_, bitpos::B11> DSCAFBH;
			bit_rw_t <io_, bitpos::B12> DSCBRAL;
			bit_rw_t <io_, bitpos::B13> DSCBRAH;
			bit_rw_t <io_, bitpos::B14> DSCBFAL;
			bit_rw_t <io_, bitpos::B15> DSCBFAH;
			bit_rw_t <io_, bitpos::B16> DSELCA;
			bit_rw_t <io_, bitpos::B17> DSELCB;
			bit_rw_t <io_, bitpos::B18> DSELCC;
			bit_rw_t <io_, bitpos::B19> DSELCD;
			bit_rw_t <io_, bitpos::B20> DSELCE;
			bit_rw_t <io_, bitpos::B21> DSELCF;
			bit_rw_t <io_, bitpos::B22> DSELCG;
			bit_rw_t <io_, bitpos::B23> DSELCH;
		};
		static gtdnsr_t<base + 0x20> GTDNSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマインプットキャプチャ要因セレクトレジスタ A (GTICASR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gticasr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  ASGTRGAR;
			bit_rw_t <io_, bitpos::B1>  ASGTRGAF;
			bit_rw_t <io_, bitpos::B2>  ASGTRGBR;
			bit_rw_t <io_, bitpos::B3>  ASGTRGBF;
			bit_rw_t <io_, bitpos::B4>  ASGTRGCR;
			bit_rw_t <io_, bitpos::B5>  ASGTRGCF;
			bit_rw_t <io_, bitpos::B6>  ASGTRGDR;
			bit_rw_t <io_, bitpos::B7>  ASGTRGDF;
			bit_rw_t <io_, bitpos::B8>  ASCARBL;
			bit_rw_t <io_, bitpos::B9>  ASCARBH;
			bit_rw_t <io_, bitpos::B10> ASCAFBL;
			bit_rw_t <io_, bitpos::B11> ASCAFBH;
			bit_rw_t <io_, bitpos::B12> ASCBRAL;
			bit_rw_t <io_, bitpos::B13> ASCBRAH;
			bit_rw_t <io_, bitpos::B14> ASCBFAL;
			bit_rw_t <io_, bitpos::B15> ASCBFAH;
			bit_rw_t <io_, bitpos::B16> ASELCA;
			bit_rw_t <io_, bitpos::B17> ASELCB;
			bit_rw_t <io_, bitpos::B18> ASELCC;
			bit_rw_t <io_, bitpos::B19> ASELCD;
			bit_rw_t <io_, bitpos::B20> ASELCE;
			bit_rw_t <io_, bitpos::B21> ASELCF;
			bit_rw_t <io_, bitpos::B22> ASELCG;
			bit_rw_t <io_, bitpos::B23> ASELCH;
		};
		static gticasr_t<base + 0x24> GTICASR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマインプットキャプチャ要因セレクトレジスタ B (GTICBSR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gticbsr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  BSGTRGAR;
			bit_rw_t <io_, bitpos::B1>  BSGTRGAF;
			bit_rw_t <io_, bitpos::B2>  BSGTRGBR;
			bit_rw_t <io_, bitpos::B3>  BSGTRGBF;
			bit_rw_t <io_, bitpos::B4>  BSGTRGCR;
			bit_rw_t <io_, bitpos::B5>  BSGTRGCF;
			bit_rw_t <io_, bitpos::B6>  BSGTRGDR;
			bit_rw_t <io_, bitpos::B7>  BSGTRGDF;
			bit_rw_t <io_, bitpos::B8>  BSCARBL;
			bit_rw_t <io_, bitpos::B9>  BSCARBH;
			bit_rw_t <io_, bitpos::B10> BSCAFBL;
			bit_rw_t <io_, bitpos::B11> BSCAFBH;
			bit_rw_t <io_, bitpos::B12> BSCBRAL;
			bit_rw_t <io_, bitpos::B13> BSCBRAH;
			bit_rw_t <io_, bitpos::B14> BSCBFAL;
			bit_rw_t <io_, bitpos::B15> BSCBFAH;
			bit_rw_t <io_, bitpos::B16> BSELCA;
			bit_rw_t <io_, bitpos::B17> BSELCB;
			bit_rw_t <io_, bitpos::B18> BSELCC;
			bit_rw_t <io_, bitpos::B19> BSELCD;
			bit_rw_t <io_, bitpos::B20> BSELCE;
			bit_rw_t <io_, bitpos::B21> BSELCF;
			bit_rw_t <io_, bitpos::B22> BSELCG;
			bit_rw_t <io_, bitpos::B23> BSELCH;
		};
		static gticbsr_t<base + 0x28> GTICBSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ制御レジスタ (GTCR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtcr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      CST;
			bit_rw_t <io_, bitpos::B8>      ICDS;
			bits_rw_t<io_, bitpos::B16, 3>  MD;
			bits_rw_t<io_, bitpos::B23, 4>  TPCS;
		};
		static gtcr_t<base + 0x2C> GTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマカウント方向、デューティ設定レジスタ (GTUDDTYC)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtuddtyc_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      UD;
			bit_rw_t <io_, bitpos::B1>      UDF;

			bits_rw_t<io_, bitpos::B16, 2>  OADTY;
			bit_rw_t <io_, bitpos::B18>     OADTYF;
			bit_rw_t <io_, bitpos::B19>     OADTYR;

			bits_rw_t<io_, bitpos::B24, 2>  OBDTY;
			bit_rw_t <io_, bitpos::B26>     OBDTYF;
			bit_rw_t <io_, bitpos::B27>     OBDTYR;
		};
		static gtuddtyc_t<base + 0x30> GTUDDTYC;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ I/O 制御レジスタ (GTIOR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtior_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>   OAIOA;

			bit_rw_t <io_, bitpos::B6>      OADFLT;
			bit_rw_t <io_, bitpos::B7>      OAHLD;
			bit_rw_t <io_, bitpos::B8>      OAE;
			bits_rw_t<io_, bitpos::B9, 2>   OADF;

			bit_rw_t <io_, bitpos::B13>     NFAEN;
			bits_rw_t<io_, bitpos::B14, 2>  NFCSA;

			bits_rw_t<io_, bitpos::B16, 5>  OAIOB;

			bit_rw_t <io_, bitpos::B22>     OBDFLT;
			bit_rw_t <io_, bitpos::B23>     OBHLD;
			bit_rw_t <io_, bitpos::B24>     OBE;
			bits_rw_t<io_, bitpos::B25, 2>  OBDF;

			bit_rw_t <io_, bitpos::B29>     NFBEN;
			bits_rw_t<io_, bitpos::B30, 2>  NFCSB;
		};
		static gtior_t<base + 0x34> GTIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ割り込み出力設定レジスタ (GTINTAD)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtintad_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      GTINTA;
			bit_rw_t <io_, bitpos::B1>      GTINTB;
			bit_rw_t <io_, bitpos::B2>      GTINTC;
			bit_rw_t <io_, bitpos::B3>      GTINTD;
			bit_rw_t <io_, bitpos::B4>      GTINTE;
			bit_rw_t <io_, bitpos::B5>      GTINTF;
			bits_rw_t<io_, bitpos::B6, 2>   GTINTPR;

			bit_rw_t <io_, bitpos::B16>     ADTRAUEN;
			bit_rw_t <io_, bitpos::B17>     ADTRADEN;
			bit_rw_t <io_, bitpos::B18>     ADTRBUEN;
			bit_rw_t <io_, bitpos::B19>     ADTRBDEN;

			bits_rw_t<io_, bitpos::B24, 2>  GRP;

			bit_rw_t <io_, bitpos::B28>     GRPDTE;
			bit_rw_t <io_, bitpos::B29>     GRPABH;
			bit_rw_t <io_, bitpos::B30>     GRPABL;
		};
		static gtintad_t<base + 0x38> GTINTAD;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマステータスレジスタ (GTST)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtst_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B8, 3>   ITCNT;

			bit_ro_t <io_, bitpos::B15>     TUCF;

			bit_rw_t <io_, bitpos::B16>     ADTRAUF;
			bit_rw_t <io_, bitpos::B17>     ADTRADF;
			bit_rw_t <io_, bitpos::B18>     ADTRBUF;
			bit_rw_t <io_, bitpos::B19>     ADTRBDF;

			bit_ro_t <io_, bitpos::B24>     ODF;

			bit_ro_t <io_, bitpos::B28>     DTEF;
			bit_ro_t <io_, bitpos::B29>     OABHF;
			bit_ro_t <io_, bitpos::B30>     OABLF;
		};
		static gtst_t<base + 0x3C> GTST;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマバッファイネーブルレジスタ (GTBER)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtber_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      BD0;
			bit_rw_t <io_, bitpos::B1>      BD1;
			bit_rw_t <io_, bitpos::B2>      BD2;
			bit_rw_t <io_, bitpos::B3>      BD3;

			bit_rw_t <io_, bitpos::B8>      DBRTECA;

			bit_rw_t <io_, bitpos::B10>     DBRTECB;

			bits_rw_t<io_, bitpos::B16, 2>  CCRA;
			bits_rw_t<io_, bitpos::B18, 2>  CCRB;
			bits_rw_t<io_, bitpos::B20, 2>  PR;
			bit_rw_t <io_, bitpos::B22>     CCRSWT;

			bits_rw_t<io_, bitpos::B24, 2>  ADTTA;
			bit_rw_t <io_, bitpos::B26>     ADTDA;

			bits_rw_t<io_, bitpos::B28, 2>  ADTTB;
			bit_rw_t <io_, bitpos::B30>     ADTDB;
		};
		static gtber_t<base + 0x40> GTBER;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ割り込み、 A/D 変換開始要求間引き設定レジスタ (GTITC)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtitc_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      ITLA;
			bit_rw_t <io_, bitpos::B1>      ITLB;
			bit_rw_t <io_, bitpos::B2>      ITLC;
			bit_rw_t <io_, bitpos::B3>      ITLD;
			bit_rw_t <io_, bitpos::B4>      ITLE;
			bit_rw_t <io_, bitpos::B5>      ITLF;
			bits_rw_t<io_, bitpos::B6, 2>   IVTC;
			bits_rw_t<io_, bitpos::B8, 3>   IVTT;

			bit_rw_t <io_, bitpos::B12>     ADTAL;

			bit_rw_t <io_, bitpos::B14>     ADTBL;
		};
		static gtitc_t<base + 0x44> GTITC;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマカウンタ (GTCNT)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x48>  GTCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマコンペアキャプチャレジスタ m (GTCCRm) (m = A ～ F)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x4C>  GTCCRA;
		static rw32_t<base + 0x50>  GTCCRB;
		static rw32_t<base + 0x54>  GTCCRC;
		static rw32_t<base + 0x58>  GTCCRD;
		static rw32_t<base + 0x5C>  GTCCRE;
		static rw32_t<base + 0x60>  GTCCRF;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ周期設定レジスタ (GTPR)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x64>  GTPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ周期設定バッファレジスタ (GTPBR)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x68>  GTPBR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ周期設定ダブルバッファレジスタ (GTPDBR)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x6C>  GTPDBR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求タイミングレジスタ m (GTADTRm) (m = A, B)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x70>  GTADTRA;
		static rw32_t<base + 0x7C>  GTADTRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求タイミングバッファレジスタ m (GTADTBRm) (m = A, B)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x74>  GTADTBRA;
		static rw32_t<base + 0x80>  GTADTBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求タイミングダブルバッファレジスタ m (GTADTDBRm)(m = A, B)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x78>  GTADTDBRA;
		static rw32_t<base + 0x84>  GTADTDBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマデッドタイム制御レジスタ (GTDTCR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtdtcr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      TDE;

			bit_rw_t <io_, bitpos::B4>      TDBUE;
			bit_rw_t <io_, bitpos::B5>      TDBDE;

			bit_rw_t <io_, bitpos::B8>      TDFER;
		};
		static gtdtcr_t<base + 0x88> GTDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマデッドタイム値レジスタ m (GTDVm) (m = U, D)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x8C>  GTDVU;
		static rw32_t<base + 0x90>  GTDVD;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマデッドタイムバッファレジスタ m (GTDBm) (m = U, D)
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x94>  GTDBU;
		static rw32_t<base + 0x98>  GTDBD;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ出力保護機能ステータスレジスタ (GTSOS)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtsos_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   SOS;
		};
		static gtsos_t<base + 0x9C> GTSOS;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ出力保護機能一時解除レジスタ (GTSOTR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtsotr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   SOTR;
		};
		static gtsotr_t<base + 0xA0> GTSOTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ A/D 変換開始要求信号モニタレジスタ (GTADSMR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtadsmr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   ADSMS0;

			bit_rw_t <io_, bitpos::B8>      ADSMEN0;

			bits_rw_t<io_, bitpos::B16, 2>  ADSMS1;

			bit_rw_t <io_, bitpos::B24>     ADSMEN1;
		};
		static gtadsmr_t<base + 0xA4> GTADSMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ拡張割り込み間引きカウンタ制御レジスタ (GTEITC)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gteitc_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   EIVTC1;

			bits_rw_t<io_, bitpos::B4, 4>   EIVTT1;

			bits_rw_t<io_, bitpos::B12, 4>  EITCNT1;

			bits_rw_t<io_, bitpos::B16, 2>  EIVTC2;

			bits_rw_t<io_, bitpos::B20, 4>  EIVTT2;
			bits_rw_t<io_, bitpos::B24, 4>  EITCNT2IV;
			bits_rw_t<io_, bitpos::B28, 4>  EITCNT2;
		};
		static gteitc_t<base + 0xA8> GTEITC;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ拡張割り込み間引き設定レジスタ 1 (GTEITLI1)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gteitli1_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>   EITLA;

			bits_rw_t<io_, bitpos::B4, 3>   EITLB;

			bits_rw_t<io_, bitpos::B8, 3>   EITLC;

			bits_rw_t<io_, bitpos::B12, 3>  EITLD;

			bits_rw_t<io_, bitpos::B16, 3>  EITLE;

			bits_rw_t<io_, bitpos::B20, 3>  EITLF;

			bits_rw_t<io_, bitpos::B24, 3>  EITLV;

			bits_rw_t<io_, bitpos::B28, 3>  EITLU;
		};
		static gteitli1_t<base + 0xAC> GTEITLI1;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ拡張割り込み間引き設定レジスタ 2 (GTEITLI2)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gteitli2_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>   EADTAL;

			bits_rw_t<io_, bitpos::B4, 3>   EADTBL;
		};
		static gteitli2_t<base + 0xB0> GTEITLI2;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ拡張バッファ転送間引き設定レジスタ (GTEITLB)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gteitlb_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>   EBTLCA;

			bits_rw_t<io_, bitpos::B4, 3>   EBTLCB;

			bits_rw_t<io_, bitpos::B8, 3>   EBTLPR;

			bits_rw_t<io_, bitpos::B16, 3>  EBTLADA;

			bits_rw_t<io_, bitpos::B20, 3>  EBTLADB;

			bits_rw_t<io_, bitpos::B24, 3>  EBTLDVU;

			bits_rw_t<io_, bitpos::B28, 3>  EBTLDVD;
		};
		static gteitlb_t<base + 0xB4> GTEITLB;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ動作許可ビット同時制御チャネル選択レジスタ (GTSECSR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtsecsr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      SECSEL0;
			bit_rw_t <io_, bitpos::B1>      SECSEL1;
			bit_rw_t <io_, bitpos::B2>      SECSEL2;
			bit_rw_t <io_, bitpos::B3>      SECSEL3;
			bit_rw_t <io_, bitpos::B4>      SECSEL4;
			bit_rw_t <io_, bitpos::B5>      SECSEL5;
			bit_rw_t <io_, bitpos::B6>      SECSEL6;
			bit_rw_t <io_, bitpos::B7>      SECSEL7;
			bit_rw_t <io_, bitpos::B8>      SECSEL8;
			bit_rw_t <io_, bitpos::B9>      SECSEL9;
		};
		static gtsecsr_t<base + 0xD0> GTSECSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ動作許可ビット同時制御レジスタ (GTSECR)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtsecr_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      SBDCE;
			bit_rw_t <io_, bitpos::B1>      SBDPE;
			bit_rw_t <io_, bitpos::B2>      SBDAE;
			bit_rw_t <io_, bitpos::B3>      SBDDE;

			bit_rw_t <io_, bitpos::B8>      SBDCD;
			bit_rw_t <io_, bitpos::B9>      SBDPD;
			bit_rw_t <io_, bitpos::B10>     SBDAD;
			bit_rw_t <io_, bitpos::B11>     SBDDD;
		};
		static gtsecr_t<base + 0xD4> GTSECR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return peri; }


		//-----------------------------------------------------------------//
		/*!
			@brief  GTCIA 割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELA get_gtcia_vec() { return gtcia; }


		//-----------------------------------------------------------------//
		/*!
			@brief  GTCIB 割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELA get_gtcib_vec() { return gtcib; }


		//-----------------------------------------------------------------//
		/*!
			@brief  GTCIC 割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELA get_gtcic_vec() { return gtcic; }


		//-----------------------------------------------------------------//
		/*!
			@brief  GTCID 割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELA get_gtcid_vec() { return gtcid; }


		//-----------------------------------------------------------------//
		/*!
			@brief  GDTE 割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELA get_gdte_vec() { return gdte; }


		//-----------------------------------------------------------------//
		/*!
			@brief  GTCIE 割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELA get_gtcie_vec() { return gtcie; }


		//-----------------------------------------------------------------//
		/*!
			@brief  GTCIF 割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELA get_gtcif_vec() { return gtcif; }


		//-----------------------------------------------------------------//
		/*!
			@brief  GTCIU 割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELA get_gtciu_vec() { return gtciu; }


		//-----------------------------------------------------------------//
		/*!
			@brief  GTCIV 割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELA get_gtciv_vec() { return gtciv; }
	};

	typedef gptw_t<0x000C2000, peripheral::GPTW0,
		ICU::VECTOR_SELA::GTCIA0, ICU::VECTOR_SELA::GTCIB0, ICU::VECTOR_SELA::GTCIC0,
		ICU::VECTOR_SELA::GTCID0, ICU::VECTOR_SELA::GDTE0,  ICU::VECTOR_SELA::GTCIE0,
		ICU::VECTOR_SELA::GTCIF0, ICU::VECTOR_SELA::GTCIV0, ICU::VECTOR_SELA::GTCIU0> GPTW0;
	typedef gptw_t<0x000C2100, peripheral::GPTW1,
		ICU::VECTOR_SELA::GTCIA1, ICU::VECTOR_SELA::GTCIB1, ICU::VECTOR_SELA::GTCIC1,
		ICU::VECTOR_SELA::GTCID1, ICU::VECTOR_SELA::GDTE1,  ICU::VECTOR_SELA::GTCIE1,
		ICU::VECTOR_SELA::GTCIF1, ICU::VECTOR_SELA::GTCIV1, ICU::VECTOR_SELA::GTCIU1> GPTW1;
	typedef gptw_t<0x000C2200, peripheral::GPTW2,
		ICU::VECTOR_SELA::GTCIA2, ICU::VECTOR_SELA::GTCIB2, ICU::VECTOR_SELA::GTCIC2,
		ICU::VECTOR_SELA::GTCID2, ICU::VECTOR_SELA::GDTE2,  ICU::VECTOR_SELA::GTCIE2,
		ICU::VECTOR_SELA::GTCIF2, ICU::VECTOR_SELA::GTCIV2, ICU::VECTOR_SELA::GTCIU2> GPTW2;
	typedef gptw_t<0x000C2300, peripheral::GPTW3,
		ICU::VECTOR_SELA::GTCIA3, ICU::VECTOR_SELA::GTCIB3, ICU::VECTOR_SELA::GTCIC3,
		ICU::VECTOR_SELA::GTCID3, ICU::VECTOR_SELA::GDTE3,  ICU::VECTOR_SELA::GTCIE3,
		ICU::VECTOR_SELA::GTCIF3, ICU::VECTOR_SELA::GTCIV3, ICU::VECTOR_SELA::GTCIU3> GPTW3;
	typedef gptw_t<0x000C2400, peripheral::GPTW4,
		ICU::VECTOR_SELA::GTCIA4, ICU::VECTOR_SELA::GTCIB4, ICU::VECTOR_SELA::GTCIC4,
		ICU::VECTOR_SELA::GTCID4, ICU::VECTOR_SELA::GDTE4,  ICU::VECTOR_SELA::GTCIE4,
		ICU::VECTOR_SELA::GTCIF4, ICU::VECTOR_SELA::GTCIV4, ICU::VECTOR_SELA::GTCIU4> GPTW4;
	typedef gptw_t<0x000C2500, peripheral::GPTW5,
		ICU::VECTOR_SELA::GTCIA5, ICU::VECTOR_SELA::GTCIB5, ICU::VECTOR_SELA::GTCIC5,
		ICU::VECTOR_SELA::GTCID5, ICU::VECTOR_SELA::GDTE5,  ICU::VECTOR_SELA::GTCIE5,
		ICU::VECTOR_SELA::GTCIF5, ICU::VECTOR_SELA::GTCIV5, ICU::VECTOR_SELA::GTCIU5> GPTW5;
	typedef gptw_t<0x000C2600, peripheral::GPTW6,
		ICU::VECTOR_SELA::GTCIA6, ICU::VECTOR_SELA::GTCIB6, ICU::VECTOR_SELA::GTCIC6,
		ICU::VECTOR_SELA::GTCID6, ICU::VECTOR_SELA::GDTE6,  ICU::VECTOR_SELA::GTCIE6,
		ICU::VECTOR_SELA::GTCIF6, ICU::VECTOR_SELA::GTCIV6, ICU::VECTOR_SELA::GTCIU6> GPTW6;
	typedef gptw_t<0x000C2700, peripheral::GPTW7,
		ICU::VECTOR_SELA::GTCIA7, ICU::VECTOR_SELA::GTCIB7, ICU::VECTOR_SELA::GTCIC7,
		ICU::VECTOR_SELA::GTCID7, ICU::VECTOR_SELA::GDTE7,  ICU::VECTOR_SELA::GTCIE7,
		ICU::VECTOR_SELA::GTCIF7, ICU::VECTOR_SELA::GTCIV7, ICU::VECTOR_SELA::GTCIU7> GPTW7;
	typedef gptw_t<0x000C2800, peripheral::GPTW8,
		ICU::VECTOR_SELA::GTCIA8, ICU::VECTOR_SELA::GTCIB8, ICU::VECTOR_SELA::GTCIC8,
		ICU::VECTOR_SELA::GTCID8, ICU::VECTOR_SELA::GDTE8,  ICU::VECTOR_SELA::GTCIE8,
		ICU::VECTOR_SELA::GTCIF8, ICU::VECTOR_SELA::GTCIV8, ICU::VECTOR_SELA::GTCIU8> GPTW8;
	typedef gptw_t<0x000C2900, peripheral::GPTW9,
		ICU::VECTOR_SELA::GTCIA9, ICU::VECTOR_SELA::GTCIB9, ICU::VECTOR_SELA::GTCIC9,
		ICU::VECTOR_SELA::GTCID9, ICU::VECTOR_SELA::GDTE9,  ICU::VECTOR_SELA::GTCIE9,
		ICU::VECTOR_SELA::GTCIF9, ICU::VECTOR_SELA::GTCIV9, ICU::VECTOR_SELA::GTCIU9> GPTW9;
}
