#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63x グループ・GPT 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct gpt_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマソフトウェアスタートレジスタ (GTSTR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2000> gtstr_io;
		struct gtstr_t : public gtstr_io {
			using gtstr_io::operator =;
			using gtstr_io::operator ();
			using gtstr_io::operator |=;
			using gtstr_io::operator &=;

			bit_rw_t<gtstr_io, bitpos::B0>  CST0;
			bit_rw_t<gtstr_io, bitpos::B1>  CST1;
			bit_rw_t<gtstr_io, bitpos::B2>  CST2;
			bit_rw_t<gtstr_io, bitpos::B3>  CST3;
		};
		static gtstr_t GTSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因スタートコントロールレジスタ (GTHSCR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2004> gthscr_io;
		struct gthscr_t : public gthscr_io {
			using gthscr_io::operator =;
			using gthscr_io::operator ();
			using gthscr_io::operator |=;
			using gthscr_io::operator &=;

			bits_rw_t<gthscr_io, bitpos::B0, 2>  CSHW0;
			bits_rw_t<gthscr_io, bitpos::B2, 2>  CSHW1;
			bits_rw_t<gthscr_io, bitpos::B4, 2>  CSHW2;
			bits_rw_t<gthscr_io, bitpos::B6, 2>  CSHW3;
			bits_rw_t<gthscr_io, bitpos::B8, 2>  CPHW0;
			bits_rw_t<gthscr_io, bitpos::B10, 2>  CPHW1;
			bits_rw_t<gthscr_io, bitpos::B12, 2>  CPHW2;
			bits_rw_t<gthscr_io, bitpos::B14, 2>  CPHW3;
		};
		static gthscr_t GTHSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因クリアコントロールレジスタ (GTHCCR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2006> gthccr_io;
		struct gthccr_t : public gthccr_io {
			using gthccr_io::operator =;
			using gthccr_io::operator ();
			using gthccr_io::operator |=;
			using gthccr_io::operator &=;

			bits_rw_t<gthccr_io, bitpos::B0, 2>  CCHW0;
			bits_rw_t<gthccr_io, bitpos::B2, 2>  CCHW1;
			bits_rw_t<gthccr_io, bitpos::B4, 2>  CCHW2;
			bits_rw_t<gthccr_io, bitpos::B6, 2>  CCHW3;
			bit_rw_t< gthccr_io, bitpos::B8>     CCSW0;
			bit_rw_t< gthccr_io, bitpos::B9>     CCSW1;
			bit_rw_t< gthccr_io, bitpos::B10>     CCSW2;
			bit_rw_t< gthccr_io, bitpos::B11>     CCSW3;
		};
		static gthccr_t GTHCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアスタート要因セレクトレジスタ (GTHSSR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2008> gthssr_io;
		struct gthssr_t : public gthssr_io {
			using gthssr_io::operator =;
			using gthssr_io::operator ();
			using gthssr_io::operator |=;
			using gthssr_io::operator &=;

			bits_rw_t<gthssr_io, bitpos::B0, 4>  CSHSL0;
			bits_rw_t<gthssr_io, bitpos::B4, 4>  CSHSL1;
			bits_rw_t<gthssr_io, bitpos::B8, 4>  CSHSL2;
			bits_rw_t<gthssr_io, bitpos::B12, 4>  CSHSL3;
		};
		static gthssr_t GTHSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアストップ・クリア要因セレクトレジスタ (GTHPSR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c200a> gthpsr_io;
		struct gthpsr_t : public gthpsr_io {
			using gthpsr_io::operator =;
			using gthpsr_io::operator ();
			using gthpsr_io::operator |=;
			using gthpsr_io::operator &=;

			bits_rw_t<gthpsr_io, bitpos::B0, 4>  CSHPL0;
			bits_rw_t<gthpsr_io, bitpos::B4, 4>  CSHPL1;
			bits_rw_t<gthpsr_io, bitpos::B8, 4>  CSHPL2;
			bits_rw_t<gthpsr_io, bitpos::B12, 4>  CSHPL3;
		};
		static gthpsr_t GTHPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ書き込み保護レジスタ (GTWP)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c200c> gtwp_io;
		struct gtwp_t : public gtwp_io {
			using gtwp_io::operator =;
			using gtwp_io::operator ();
			using gtwp_io::operator |=;
			using gtwp_io::operator &=;

			bit_rw_t<gtwp_io, bitpos::B0>    WP0;
			bit_rw_t<gtwp_io, bitpos::B1>    WP1;
			bit_rw_t<gtwp_io, bitpos::B2>    WP2;
			bit_rw_t<gtwp_io, bitpos::B3>    WP3;
		};
		static gtwp_t GTWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマシンクロレジスタ (GTSYNC)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c200e> gtsync_io;
		struct gtsync_t : public gtsync_io {
			using gtsync_io::operator =;
			using gtsync_io::operator ();
			using gtsync_io::operator |=;
			using gtsync_io::operator &=;

			bits_rw_t<gtsync_io, bitpos::B0, 2>  SYNC0;
			bits_rw_t<gtsync_io, bitpos::B4, 2>  SYNC1;
			bits_rw_t<gtsync_io, bitpos::B8, 2>  SYNC2;
			bits_rw_t<gtsync_io, bitpos::B12, 2>  SYNC3;
		};
		static gtsync_t GTSYNC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ外部トリガ入力割り込みレジスタ (GTETINT)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2010> gtetint_io;
		struct gtetint_t : public gtetint_io {
			using gtetint_io::operator =;
			using gtetint_io::operator ();
			using gtetint_io::operator |=;
			using gtetint_io::operator &=;

			bit_rw_t<gtetint_io, bitpos::B0>    ETIPEN;
			bit_rw_t<gtetint_io, bitpos::B1>    ETINEN;
			bit_rw_t<gtetint_io, bitpos::B8>    ETIPF;
			bit_rw_t<gtetint_io, bitpos::B9>    ETINF;
		};
		static gtetint_t GTETINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファ動作禁止レジスタ (GTBDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2014> gtbdr_io;
		struct gtbdr_t : public gtbdr_io {
			using gtbdr_io::operator =;
			using gtbdr_io::operator ();
			using gtbdr_io::operator |=;
			using gtbdr_io::operator &=;

			bit_rw_t<gtbdr_io, bitpos::B0>    BD0_0;
			bit_rw_t<gtbdr_io, bitpos::B1>    BD0_1;
			bit_rw_t<gtbdr_io, bitpos::B2>    BD0_2;
			bit_rw_t<gtbdr_io, bitpos::B3>    BD0_3;
			bit_rw_t<gtbdr_io, bitpos::B4>    BD1_0;
			bit_rw_t<gtbdr_io, bitpos::B5>    BD1_1;
			bit_rw_t<gtbdr_io, bitpos::B6>    BD1_2;
			bit_rw_t<gtbdr_io, bitpos::B7>    BD1_3;
			bit_rw_t<gtbdr_io, bitpos::B8>    BD2_0;
			bit_rw_t<gtbdr_io, bitpos::B9>    BD2_1;
			bit_rw_t<gtbdr_io, bitpos::B10>    BD2_2;
			bit_rw_t<gtbdr_io, bitpos::B11>    BD2_3;
			bit_rw_t<gtbdr_io, bitpos::B12>    BD3_0;
			bit_rw_t<gtbdr_io, bitpos::B13>    BD3_1;
			bit_rw_t<gtbdr_io, bitpos::B14>    BD3_2;
			bit_rw_t<gtbdr_io, bitpos::B15>    BD3_3;
		};
		static gtbdr_t GTBDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマスタート書き込み保護レジスタ (GTSWP)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2018> gtswp_io;
		struct gtswp_t : public gtswp_io {
			using gtswp_io::operator =;
			using gtswp_io::operator ();
			using gtswp_io::operator |=;
			using gtswp_io::operator &=;

			bit_rw_t<gtswp_io, bitpos::B0>    SWP0;
			bit_rw_t<gtswp_io, bitpos::B1>    SWP1;
			bit_rw_t<gtswp_io, bitpos::B2>    SWP2;
			bit_rw_t<gtswp_io, bitpos::B3>    SWP3;
		};
		static gtswp_t GTSWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントコントロールレジスタ (LCCR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2080> lccr_io;
		struct lccr_t : public lccr_io {
			using lccr_io::operator =;
			using lccr_io::operator ();
			using lccr_io::operator |=;
			using lccr_io::operator &=;

			bit_rw_t< lccr_io, bitpos::B0>    LCNTE;
			bit_rw_t< lccr_io, bitpos::B1>    LCNTCR;
			bit_rw_t< lccr_io, bitpos::B2>    LCNTS;
			bit_rw_t< lccr_io, bitpos::B4>    LCINTC;
			bit_rw_t< lccr_io, bitpos::B5>    LCINTD;
			bit_rw_t< lccr_io, bitpos::B6>    LCINTO;
			bits_rw_t<lccr_io, bitpos::B8, 3> LCTO;
			bit_rw_t< lccr_io, bitpos::B11>    LCNTAT;
			bits_rw_t<lccr_io, bitpos::B12, 2> TPSC;
			bits_rw_t<lccr_io, bitpos::B14, 2> LPSC;
		};
		static lccr_t LCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントステータスレジスタ (LCCR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2082> lcst_io;
		struct lcst_t : public lcst_io {
			using lcst_io::operator =;
			using lcst_io::operator ();
			using lcst_io::operator |=;
			using lcst_io::operator &=;

			bit_rw_t< lcst_io, bitpos::B0>    LISC;
			bit_rw_t< lcst_io, bitpos::B1>    LISD;
			bit_rw_t< lcst_io, bitpos::B2>    LISO;
		};
		static lcst_t LCST;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント値レジスタ (LCNT)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000c2084> LCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果平均レジスタ (LCNTA)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000c2086> LCNTA;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果レジスタｎ (LCNTn)(n=00..15)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000c2088> LCNT00;
		static rw16_t<0x000c208a> LCNT01;
		static rw16_t<0x000c208c> LCNT02;
		static rw16_t<0x000c208e> LCNT03;
		static rw16_t<0x000c2090> LCNT04;
		static rw16_t<0x000c2092> LCNT05;
		static rw16_t<0x000c2094> LCNT06;
		static rw16_t<0x000c2096> LCNT07;
		static rw16_t<0x000c2098> LCNT08;
		static rw16_t<0x000c209a> LCNT09;
		static rw16_t<0x000c209c> LCNT10;
		static rw16_t<0x000c209e> LCNT11;
		static rw16_t<0x000c20a0> LCNT12;
		static rw16_t<0x000c20a2> LCNT13;
		static rw16_t<0x000c20a4> LCNT14;
		static rw16_t<0x000c20a6> LCNT15;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント上限／下限許容偏差レジスタ (LCNTDU, LCNTDL)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000c20a8> LCNTDU;
		static rw16_t<0x000c20aa> LCNTDL;

	};
	typedef gpt_t GPT;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct gptb_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマソフトウェアスタートレジスタ (GTSTR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2800> gtstr_io;
		struct gtstr_t : public gtstr_io {
			using gtstr_io::operator =;
			using gtstr_io::operator ();
			using gtstr_io::operator |=;
			using gtstr_io::operator &=;

			bit_rw_t<gtstr_io, bitpos::B0>  CST4;
			bit_rw_t<gtstr_io, bitpos::B1>  CST5;
			bit_rw_t<gtstr_io, bitpos::B2>  CST6;
			bit_rw_t<gtstr_io, bitpos::B3>  CST7;
		};
		static gtstr_t GTSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ書き込み保護レジスタ (GTWP)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c280c> gtwp_io;
		struct gtwp_t : public gtwp_io {
			using gtwp_io::operator =;
			using gtwp_io::operator ();
			using gtwp_io::operator |=;
			using gtwp_io::operator &=;

			bit_rw_t<gtwp_io, bitpos::B0>    WP4;
			bit_rw_t<gtwp_io, bitpos::B1>    WP5;
			bit_rw_t<gtwp_io, bitpos::B2>    WP6;
			bit_rw_t<gtwp_io, bitpos::B3>    WP7;
		};
		static gtwp_t GTWP;

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファ動作禁止レジスタ (GTBDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2814> gtbdr_io;
		struct gtbdr_t : public gtbdr_io {
			using gtbdr_io::operator =;
			using gtbdr_io::operator ();
			using gtbdr_io::operator |=;
			using gtbdr_io::operator &=;

			bit_rw_t<gtbdr_io, bitpos::B0>    BD4_0;
			bit_rw_t<gtbdr_io, bitpos::B1>    BD4_1;
			bit_rw_t<gtbdr_io, bitpos::B2>    BD4_2;
			bit_rw_t<gtbdr_io, bitpos::B3>    BD4_3;
			bit_rw_t<gtbdr_io, bitpos::B4>    BD5_0;
			bit_rw_t<gtbdr_io, bitpos::B5>    BD5_1;
			bit_rw_t<gtbdr_io, bitpos::B6>    BD5_2;
			bit_rw_t<gtbdr_io, bitpos::B7>    BD5_3;
			bit_rw_t<gtbdr_io, bitpos::B8>    BD6_0;
			bit_rw_t<gtbdr_io, bitpos::B9>    BD6_1;
			bit_rw_t<gtbdr_io, bitpos::B10>    BD6_2;
			bit_rw_t<gtbdr_io, bitpos::B11>    BD6_3;
			bit_rw_t<gtbdr_io, bitpos::B12>    BD7_0;
			bit_rw_t<gtbdr_io, bitpos::B13>    BD7_1;
			bit_rw_t<gtbdr_io, bitpos::B14>    BD7_2;
			bit_rw_t<gtbdr_io, bitpos::B15>    BD7_3;
		};
		static gtbdr_t GTBDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマスタート書き込み保護レジスタ (GTSWP)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2818> gtswp_io;
		struct gtswp_t : public gtswp_io {
			using gtswp_io::operator =;
			using gtswp_io::operator ();
			using gtswp_io::operator |=;
			using gtswp_io::operator &=;

			bit_rw_t<gtswp_io, bitpos::B0>    SWP4;
			bit_rw_t<gtswp_io, bitpos::B1>    SWP5;
			bit_rw_t<gtswp_io, bitpos::B2>    SWP6;
			bit_rw_t<gtswp_io, bitpos::B3>    SWP7;
		};
		static gtswp_t GTSWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントコントロールレジスタ (LCCR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2880> lccr_io;
		struct lccr_t : public lccr_io {
			using lccr_io::operator =;
			using lccr_io::operator ();
			using lccr_io::operator |=;
			using lccr_io::operator &=;

			bit_rw_t< lccr_io, bitpos::B0>    LCNTE;
			bit_rw_t< lccr_io, bitpos::B1>    LCNTCR;
			bit_rw_t< lccr_io, bitpos::B2>    LCNTS;
			bit_rw_t< lccr_io, bitpos::B4>    LCINTC;
			bit_rw_t< lccr_io, bitpos::B5>    LCINTD;
			bit_rw_t< lccr_io, bitpos::B6>    LCINTO;
			bits_rw_t<lccr_io, bitpos::B8, 3> LCTO;
			bit_rw_t< lccr_io, bitpos::B11>    LCNTAT;
			bits_rw_t<lccr_io, bitpos::B12, 2> TPSC;
			bits_rw_t<lccr_io, bitpos::B14, 2> LPSC;
		};
		static lccr_t LCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントステータスレジスタ (LCCR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000c2882> lcst_io;
		struct lcst_t : public lcst_io {
			using lcst_io::operator =;
			using lcst_io::operator ();
			using lcst_io::operator |=;
			using lcst_io::operator &=;

			bit_rw_t< lcst_io, bitpos::B0>    LISC;
			bit_rw_t< lcst_io, bitpos::B1>    LISD;
			bit_rw_t< lcst_io, bitpos::B2>    LISO;
		};
		static lcst_t LCST;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント値レジスタ (LCNT)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000c2884> LCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果平均レジスタ (LCNTA)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000c2886> LCNTA;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果レジスタｎ (LCNTn)(n=00..15)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000c2888> LCNT00;
		static rw16_t<0x000c288a> LCNT01;
		static rw16_t<0x000c288c> LCNT02;
		static rw16_t<0x000c288e> LCNT03;
		static rw16_t<0x000c2890> LCNT04;
		static rw16_t<0x000c2892> LCNT05;
		static rw16_t<0x000c2894> LCNT06;
		static rw16_t<0x000c2896> LCNT07;
		static rw16_t<0x000c2898> LCNT08;
		static rw16_t<0x000c289a> LCNT09;
		static rw16_t<0x000c289c> LCNT10;
		static rw16_t<0x000c289e> LCNT11;
		static rw16_t<0x000c28a0> LCNT12;
		static rw16_t<0x000c28a2> LCNT13;
		static rw16_t<0x000c28a4> LCNT14;
		static rw16_t<0x000c28a6> LCNT15;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント上限／下限許容偏差レジスタ (LCNTDU, LCNTDL)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000c28a8> LCNTDU;
		static rw16_t<0x000c28aa> LCNTDL;

	};
	typedef gptb_t GPTB;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 定義基底クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct gptn_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ I/O コントロールレジスタ (GTIOR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x00> gtior_io;
		struct gtior_t : public gtior_io {
			using gtior_io::operator =;
			using gtior_io::operator ();
			using gtior_io::operator |=;
			using gtior_io::operator &=;

			bits_rw_t<gtior_io, bitpos::B0, 6> GTIOA;
			bit_rw_t< gtior_io, bitpos::B6>    OADFLT;
			bit_rw_t< gtior_io, bitpos::B7>    OAHLD;
			bits_rw_t<gtior_io, bitpos::B8, 6> GTIOB;
			bit_rw_t< gtior_io, bitpos::B14>    OBDFLT;
			bit_rw_t< gtior_io, bitpos::B15>    OBHLD;
		};
		static gtior_t GTIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ 割り込み出力設定レジスタ (GTINTAD)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x02> gtintad_io;
		struct gtintad_t : public gtintad_io {
			using gtintad_io::operator =;
			using gtintad_io::operator ();
			using gtintad_io::operator |=;
			using gtintad_io::operator &=;

			bit_rw_t< gtintad_io, bitpos::B0>    GTINTA;
			bit_rw_t< gtintad_io, bitpos::B1>    GTINTB;
			bit_rw_t< gtintad_io, bitpos::B2>    GTINTC;
			bit_rw_t< gtintad_io, bitpos::B3>    GTINTD;
			bit_rw_t< gtintad_io, bitpos::B4>    GTINTE;
			bit_rw_t< gtintad_io, bitpos::B5>    GTINTF;
			bits_rw_t<gtintad_io, bitpos::B6, 2> GTINTPR;
			bit_rw_t< gtintad_io, bitpos::B11>    EINT;
			bit_rw_t< gtintad_io, bitpos::B12>    ADTRAUEN;
			bit_rw_t< gtintad_io, bitpos::B13>    ADTRADEN;
			bit_rw_t< gtintad_io, bitpos::B14>    ADTRBUEN;
			bit_rw_t< gtintad_io, bitpos::B15>    ADTRBDEN;
		};
		static gtintad_t GTINTAD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマコントロールレジスタ (GTCR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x04> gtcr_io;
		struct gtcr_t : public gtcr_io {
			using gtcr_io::operator =;
			using gtcr_io::operator ();
			using gtcr_io::operator |=;
			using gtcr_io::operator &=;

			bits_rw_t<gtcr_io, bitpos::B0, 3> MD;
			bits_rw_t<gtcr_io, bitpos::B8, 2> TPCS;
			bits_rw_t<gtcr_io, bitpos::B12, 2> CCLR;
		};
		static gtcr_t GTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファイネーブルレジスタ (GTBER)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x06> gtber_io;
		struct gtber_t : public gtber_io {
			using gtber_io::operator =;
			using gtber_io::operator ();
			using gtber_io::operator |=;
			using gtber_io::operator &=;

			bits_rw_t<gtber_io, bitpos::B0, 2> CCRA;
			bits_rw_t<gtber_io, bitpos::B2, 2> CCRB;
			bits_rw_t<gtber_io, bitpos::B4, 2> PR;
			bit_rw_t< gtber_io, bitpos::B6>    CCRSWT;
			bits_rw_t<gtber_io, bitpos::B8, 2> ADTTA;
			bit_rw_t< gtber_io, bitpos::B10>    ADTDA;
			bits_rw_t<gtber_io, bitpos::B12, 2> ADTTB;
			bit_rw_t< gtber_io, bitpos::B14>    ADTDB;
		};
		static gtber_t GTBER;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマカウント方向レジスタ (GTUDC)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x08> gtudc_io;
		struct gtudc_t : public gtudc_io {
			using gtudc_io::operator =;
			using gtudc_io::operator ();
			using gtudc_io::operator |=;
			using gtudc_io::operator &=;

			bit_rw_t< gtudc_io, bitpos::B0>    UD;
			bit_rw_t< gtudc_io, bitpos::B1>    UDF;
		};
		static gtudc_t GTUDC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ割り込み、A/D 変換開始要求間引き設定レジスタ (GTITC)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0a> gtitc_io;
		struct gtitc_t : public gtitc_io {
			using gtitc_io::operator =;
			using gtitc_io::operator ();
			using gtitc_io::operator |=;
			using gtitc_io::operator &=;

			bit_rw_t< gtitc_io, bitpos::B0>    ITLA;
			bit_rw_t< gtitc_io, bitpos::B1>    ITLB;
			bit_rw_t< gtitc_io, bitpos::B2>    ITLC;
			bit_rw_t< gtitc_io, bitpos::B3>    ITLD;
			bit_rw_t< gtitc_io, bitpos::B4>    ITLE;
			bit_rw_t< gtitc_io, bitpos::B5>    ITLF;
			bits_rw_t<gtitc_io, bitpos::B6, 2> IVTC;
			bits_rw_t<gtitc_io, bitpos::B8, 3> IVTT;
			bit_rw_t< gtitc_io, bitpos::B12>    ADTAL;
			bit_rw_t< gtitc_io, bitpos::B14>    ADTBL;
		};
		static gtitc_t GTITC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマステータスレジスタ (GTST)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0c> gtst_io;
		struct gtst_t : public gtst_io {
			using gtst_io::operator =;
			using gtst_io::operator ();
			using gtst_io::operator |=;
			using gtst_io::operator &=;

			bit_rw_t< gtst_io, bitpos::B0>    TCFA;
			bit_rw_t< gtst_io, bitpos::B1>    TCFB;
			bit_rw_t< gtst_io, bitpos::B2>    TCFC;
			bit_rw_t< gtst_io, bitpos::B3>    TCFD;
			bit_rw_t< gtst_io, bitpos::B4>    TCFE;
			bit_rw_t< gtst_io, bitpos::B5>    TCFF;
			bit_rw_t< gtst_io, bitpos::B6>    TCFPO;
			bit_rw_t< gtst_io, bitpos::B7>    TCFPU;
			bits_rw_t<gtst_io, bitpos::B8, 3> ITCNT;
			bit_rw_t< gtst_io, bitpos::B11>    DTEF;
			bit_rw_t< gtst_io, bitpos::B15>    TUCF;
		};
		static gtst_t GTST;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマカウンタ (GTCNT)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x0e> GTCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマコンペアキャプチャレジスタ (GTCCRm)(m=A..F)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x10> GTCCRA;
		static rw16_t<base + 0x12> GTCCRB;
		static rw16_t<base + 0x14> GTCCRC;
		static rw16_t<base + 0x16> GTCCRD;
		static rw16_t<base + 0x18> GTCCRE;
		static rw16_t<base + 0x1a> GTCCRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定レジスタ (GTPR)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x1c> GTPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定バッファレジスタ (GTPBR)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x1e> GTPBR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定ダブルバッファレジスタ (GTPDBR)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x20> GTPDBR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスタｍ (GTADTRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x24> GTADTRA;
		static rw16_t<base + 0x2c> GTADTRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングバッファレジスタｍ (GTADTBRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x26> GTADTBRA;
		static rw16_t<base + 0x2e> GTADTBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングダブルバッファレジスタｍ (GTADTDBRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x28> GTADTDBRA;
		static rw16_t<base + 0x30> GTADTDBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力ネゲートコントロールレジスタ (GTONCR) @n
					※GPT0, GPT1, GPT2, GPT3
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x34> gtoncr_io;
		struct gtoncr_t : public gtoncr_io {
			using gtoncr_io::operator =;
			using gtoncr_io::operator ();
			using gtoncr_io::operator |=;
			using gtoncr_io::operator &=;

			bit_rw_t< gtoncr_io, bitpos::B0>    NEA;
			bit_rw_t< gtoncr_io, bitpos::B1>    NEB;
			bit_rw_t< gtoncr_io, bitpos::B2>    NVA;
			bit_rw_t< gtoncr_io, bitpos::B3>    NVB;
			bits_rw_t<gtoncr_io, bitpos::B4, 4> NFS;
			bit_rw_t< gtoncr_io, bitpos::B8>    NFV;
			bit_rw_t< gtoncr_io, bitpos::B12>    SWN;
			bit_rw_t< gtoncr_io, bitpos::B14>    OAE;
			bit_rw_t< gtoncr_io, bitpos::B15>    OBE;
		};
		static gtoncr_t GTONCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイムコントロールレジスタ (GTDTCR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x36> gtdtcr_io;
		struct gtdtcr_t : public gtdtcr_io {
			using gtdtcr_io::operator =;
			using gtdtcr_io::operator ();
			using gtdtcr_io::operator |=;
			using gtdtcr_io::operator &=;

			bit_rw_t< gtdtcr_io, bitpos::B0>    TDE;
			bit_rw_t< gtdtcr_io, bitpos::B4>    TDBUE;
			bit_rw_t< gtdtcr_io, bitpos::B5>    TDBDE;
			bit_rw_t< gtdtcr_io, bitpos::B8>    TDFER;
		};
		static gtdtcr_t GTDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイム値レジスタｍ (GTDVm)(m=U, D)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x38> GTDVU;
		static rw16_t<base + 0x3a> GTDVD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイムバッファレジスタｍ (GTDBm)(m=U, D)
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x3c> GTDBU;
		static rw16_t<base + 0x3e> GTDBD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力保護機能ステータスレジスタ (GTSOS)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x40> gtsos_io;
		struct gtsos_t : public gtsos_io {
			using gtsos_io::operator =;
			using gtsos_io::operator ();
			using gtsos_io::operator |=;
			using gtsos_io::operator &=;

			bits_rw_t<gtsos_io, bitpos::B0, 2>  SOS;
		};
		static gtsos_t GTSOS;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力保護機能一時解除レジスタ (GTSOTR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x42> gtsotr_io;
		struct gtsotr_t : public gtsotr_io {
			using gtsotr_io::operator =;
			using gtsotr_io::operator ();
			using gtsotr_io::operator |=;
			using gtsotr_io::operator &=;

			bit_rw_t<gtsotr_io, bitpos::B0>  SOTR;
		};
		static gtsos_t GTSOTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルを返す
			@return チャネル（０、１、２、３、４、５、６、７）
		*/
		//-----------------------------------------------------------------//
		static uint32_t get_chanel() {
			
			return ((base >> 7) & 1) | ((base >> 8) & 2) | ((base >> 9) & 4);
		}

	};
	typedef gptn_t<0x000c2100> GPT0;
	typedef gptn_t<0x000c2180> GPT1;
	typedef gptn_t<0x000c2200> GPT2;
	typedef gptn_t<0x000c2280> GPT3;
	typedef gptn_t<0x000c2900> GPT4;
	typedef gptn_t<0x000c2980> GPT5;
	typedef gptn_t<0x000c2a00> GPT6;
	typedef gptn_t<0x000c2a80> GPT7;
}
