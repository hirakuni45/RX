#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63x グループ・GPT 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "../io_utils.hpp"

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
		typedef io16<0x000c2000> gtstr_io;
		struct gtstr_t : public gtstr_io {
			using gtstr_io::operator =;
			using gtstr_io::operator ();
			using gtstr_io::operator |=;
			using gtstr_io::operator &=;

			bit_t<gtstr_io, 0>  CST0;
			bit_t<gtstr_io, 1>  CST1;
			bit_t<gtstr_io, 2>  CST2;
			bit_t<gtstr_io, 3>  CST3;
		};
		static gtstr_t GTSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因スタートコントロールレジスタ (GTHSCR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2004> gthscr_io;
		struct gthscr_t : public gthscr_io {
			using gthscr_io::operator =;
			using gthscr_io::operator ();
			using gthscr_io::operator |=;
			using gthscr_io::operator &=;

			bits_t<gthscr_io,  0, 2>  CSHW0;
			bits_t<gthscr_io,  2, 2>  CSHW1;
			bits_t<gthscr_io,  4, 2>  CSHW2;
			bits_t<gthscr_io,  6, 2>  CSHW3;
			bits_t<gthscr_io,  8, 2>  CPHW0;
			bits_t<gthscr_io, 10, 2>  CPHW1;
			bits_t<gthscr_io, 12, 2>  CPHW2;
			bits_t<gthscr_io, 14, 2>  CPHW3;
		};
		static gthscr_t GTHSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因クリアコントロールレジスタ (GTHCCR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2006> gthccr_io;
		struct gthccr_t : public gthccr_io {
			using gthccr_io::operator =;
			using gthccr_io::operator ();
			using gthccr_io::operator |=;
			using gthccr_io::operator &=;

			bits_t<gthccr_io,  0, 2>  CCHW0;
			bits_t<gthccr_io,  2, 2>  CCHW1;
			bits_t<gthccr_io,  4, 2>  CCHW2;
			bits_t<gthccr_io,  6, 2>  CCHW3;
			bit_t< gthccr_io,  8>     CCSW0;
			bit_t< gthccr_io,  9>     CCSW1;
			bit_t< gthccr_io, 10>     CCSW2;
			bit_t< gthccr_io, 11>     CCSW3;
		};
		static gthccr_t GTHCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアスタート要因セレクトレジスタ (GTHSSR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2008> gthssr_io;
		struct gthssr_t : public gthssr_io {
			using gthssr_io::operator =;
			using gthssr_io::operator ();
			using gthssr_io::operator |=;
			using gthssr_io::operator &=;

			bits_t<gthssr_io,  0, 2>  CSHSL0;
			bits_t<gthssr_io,  4, 2>  CSHSL1;
			bits_t<gthssr_io,  8, 2>  CSHSL2;
			bits_t<gthssr_io, 12, 2>  CSHSL3;
		};
		static gthssr_t GTHSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアストップ・クリア要因セレクトレジスタ (GTHPSR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c200a> gthpsr_io;
		struct gthpsr_t : public gthpsr_io {
			using gthpsr_io::operator =;
			using gthpsr_io::operator ();
			using gthpsr_io::operator |=;
			using gthpsr_io::operator &=;

			bits_t<gthpsr_io,  0, 2>  CSHPL0;
			bits_t<gthpsr_io,  4, 2>  CSHPL1;
			bits_t<gthpsr_io,  8, 2>  CSHPL2;
			bits_t<gthpsr_io, 12, 2>  CSHPL3;
		};
		static gthpsr_t GTHPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ書き込み保護レジスタ (GTWP)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c200c> gtwp_io;
		struct gtwp_t : public gtwp_io {
			using gtwp_io::operator =;
			using gtwp_io::operator ();
			using gtwp_io::operator |=;
			using gtwp_io::operator &=;

			bit_t<gtwp_io, 0>    WP0;
			bit_t<gtwp_io, 1>    WP1;
			bit_t<gtwp_io, 2>    WP2;
			bit_t<gtwp_io, 3>    WP3;
		};
		static gtwp_t GTWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマシンクロレジスタ (GTSYNC)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c200e> gtsync_io;
		struct gtsync_t : public gtsync_io {
			using gtsync_io::operator =;
			using gtsync_io::operator ();
			using gtsync_io::operator |=;
			using gtsync_io::operator &=;

			bits_t<gtsync_io,  0, 2>  SYNC0;
			bits_t<gtsync_io,  4, 2>  SYNC1;
			bits_t<gtsync_io,  8, 2>  SYNC2;
			bits_t<gtsync_io, 12, 2>  SYNC3;
		};
		static gtsync_t GTSYNC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ外部トリガ入力割り込みレジスタ (GTETINT)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2010> gtetint_io;
		struct gtetint_t : public gtetint_io {
			using gtetint_io::operator =;
			using gtetint_io::operator ();
			using gtetint_io::operator |=;
			using gtetint_io::operator &=;

			bit_t<gtetint_io, 0>    ETIPEN;
			bit_t<gtetint_io, 1>    ETINEN;
			bit_t<gtetint_io, 8>    ETIPF;
			bit_t<gtetint_io, 9>    ETINF;
		};
		static gtetint_t GTETINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファ動作禁止レジスタ (GTBDR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2014> gtbdr_io;
		struct gtbdr_t : public gtbdr_io {
			using gtbdr_io::operator =;
			using gtbdr_io::operator ();
			using gtbdr_io::operator |=;
			using gtbdr_io::operator &=;

			bit_t<gtbdr_io,  0>    BD0_0;
			bit_t<gtbdr_io,  1>    BD0_1;
			bit_t<gtbdr_io,  2>    BD0_2;
			bit_t<gtbdr_io,  3>    BD0_3;
			bit_t<gtbdr_io,  4>    BD1_0;
			bit_t<gtbdr_io,  5>    BD1_1;
			bit_t<gtbdr_io,  6>    BD1_2;
			bit_t<gtbdr_io,  7>    BD1_3;
			bit_t<gtbdr_io,  8>    BD2_0;
			bit_t<gtbdr_io,  9>    BD2_1;
			bit_t<gtbdr_io, 10>    BD2_2;
			bit_t<gtbdr_io, 11>    BD2_3;
			bit_t<gtbdr_io, 12>    BD3_0;
			bit_t<gtbdr_io, 13>    BD3_1;
			bit_t<gtbdr_io, 14>    BD3_2;
			bit_t<gtbdr_io, 15>    BD3_3;
		};
		static gtbdr_t GTBDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマスタート書き込み保護レジスタ (GTSWP)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2018> gtswp_io;
		struct gtswp_t : public gtswp_io {
			using gtswp_io::operator =;
			using gtswp_io::operator ();
			using gtswp_io::operator |=;
			using gtswp_io::operator &=;

			bit_t<gtswp_io, 0>    SWP0;
			bit_t<gtswp_io, 1>    SWP1;
			bit_t<gtswp_io, 2>    SWP2;
			bit_t<gtswp_io, 3>    SWP3;
		};
		static gtswp_t GTSWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントコントロールレジスタ (LCCR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2080> lccr_io;
		struct lccr_t : public lccr_io {
			using lccr_io::operator =;
			using lccr_io::operator ();
			using lccr_io::operator |=;
			using lccr_io::operator &=;

			bit_t< lccr_io,  0>    LCNTE;
			bit_t< lccr_io,  1>    LCNTCR;
			bit_t< lccr_io,  2>    LCNTS;
			bit_t< lccr_io,  4>    LCINTC;
			bit_t< lccr_io,  5>    LCINTD;
			bit_t< lccr_io,  6>    LCINTO;
			bits_t<lccr_io,  8, 3> LCTO;
			bit_t< lccr_io, 11>    LCNTAT;
			bits_t<lccr_io, 12, 2> TPSC;
			bits_t<lccr_io, 14, 2> LPSC;
		};
		static lccr_t LCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントステータスレジスタ (LCCR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2082> lcst_io;
		struct lcst_t : public lcst_io {
			using lcst_io::operator =;
			using lcst_io::operator ();
			using lcst_io::operator |=;
			using lcst_io::operator &=;

			bit_t< lcst_io,  0>    LISC;
			bit_t< lcst_io,  1>    LISD;
			bit_t< lcst_io,  2>    LISO;
		};
		static lcst_t LCST;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント値レジスタ (LCNT)
		*/
		//-----------------------------------------------------------------//
		static io16<0x000c2084> LCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果平均レジスタ (LCNTA)
		*/
		//-----------------------------------------------------------------//
		static io16<0x000c2086> LCNTA;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果レジスタｎ (LCNTn)(n=00..15)
		*/
		//-----------------------------------------------------------------//
		static io16<0x000c2088> LCNT00;
		static io16<0x000c208a> LCNT01;
		static io16<0x000c208c> LCNT02;
		static io16<0x000c208e> LCNT03;
		static io16<0x000c2090> LCNT04;
		static io16<0x000c2092> LCNT05;
		static io16<0x000c2094> LCNT06;
		static io16<0x000c2096> LCNT07;
		static io16<0x000c2098> LCNT08;
		static io16<0x000c209a> LCNT09;
		static io16<0x000c209c> LCNT10;
		static io16<0x000c209e> LCNT11;
		static io16<0x000c20a0> LCNT12;
		static io16<0x000c20a2> LCNT13;
		static io16<0x000c20a4> LCNT14;
		static io16<0x000c20a6> LCNT15;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント上限／下限許容偏差レジスタ (LCNTDU, LCNTDL)
		*/
		//-----------------------------------------------------------------//
		static io16<0x000c20a8> LCNTDU;
		static io16<0x000c20aa> LCNTDL;

	};
	static gpt_t GPT;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct gptb_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ書き込み保護レジスタ (GTWP)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c280c> gtwp_io;
		struct gtwp_t : public gtwp_io {
			using gtwp_io::operator =;
			using gtwp_io::operator ();
			using gtwp_io::operator |=;
			using gtwp_io::operator &=;

			bit_t<gtwp_io, 0>    WP4;
			bit_t<gtwp_io, 1>    WP5;
			bit_t<gtwp_io, 2>    WP6;
			bit_t<gtwp_io, 3>    WP7;
		};
		static gtwp_t GTWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマスタート書き込み保護レジスタ (GTSWP)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2818> gtswp_io;
		struct gtswp_t : public gtswp_io {
			using gtswp_io::operator =;
			using gtswp_io::operator ();
			using gtswp_io::operator |=;
			using gtswp_io::operator &=;

			bit_t<gtswp_io, 0>    SWP4;
			bit_t<gtswp_io, 1>    SWP5;
			bit_t<gtswp_io, 2>    SWP6;
			bit_t<gtswp_io, 3>    SWP7;
		};
		static gtswp_t GTSWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントコントロールレジスタ (LCCR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2880> lccr_io;
		struct lccr_t : public lccr_io {
			using lccr_io::operator =;
			using lccr_io::operator ();
			using lccr_io::operator |=;
			using lccr_io::operator &=;

			bit_t< lccr_io,  0>    LCNTE;
			bit_t< lccr_io,  1>    LCNTCR;
			bit_t< lccr_io,  2>    LCNTS;
			bit_t< lccr_io,  4>    LCINTC;
			bit_t< lccr_io,  5>    LCINTD;
			bit_t< lccr_io,  6>    LCINTO;
			bits_t<lccr_io,  8, 3> LCTO;
			bit_t< lccr_io, 11>    LCNTAT;
			bits_t<lccr_io, 12, 2> TPSC;
			bits_t<lccr_io, 14, 2> LPSC;
		};
		static lccr_t LCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウントステータスレジスタ (LCCR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<0x000c2882> lcst_io;
		struct lcst_t : public lcst_io {
			using lcst_io::operator =;
			using lcst_io::operator ();
			using lcst_io::operator |=;
			using lcst_io::operator &=;

			bit_t< lcst_io,  0>    LISC;
			bit_t< lcst_io,  1>    LISD;
			bit_t< lcst_io,  2>    LISO;
		};
		static lcst_t LCST;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント値レジスタ (LCNT)
		*/
		//-----------------------------------------------------------------//
		static io16<0x000c2884> LCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果平均レジスタ (LCNTA)
		*/
		//-----------------------------------------------------------------//
		static io16<0x000c2886> LCNTA;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント結果レジスタｎ (LCNTn)(n=00..15)
		*/
		//-----------------------------------------------------------------//
		static io16<0x000c2888> LCNT00;
		static io16<0x000c288a> LCNT01;
		static io16<0x000c288c> LCNT02;
		static io16<0x000c288e> LCNT03;
		static io16<0x000c2890> LCNT04;
		static io16<0x000c2892> LCNT05;
		static io16<0x000c2894> LCNT06;
		static io16<0x000c2896> LCNT07;
		static io16<0x000c2898> LCNT08;
		static io16<0x000c289a> LCNT09;
		static io16<0x000c289c> LCNT10;
		static io16<0x000c289e> LCNT11;
		static io16<0x000c28a0> LCNT12;
		static io16<0x000c28a2> LCNT13;
		static io16<0x000c28a4> LCNT14;
		static io16<0x000c28a6> LCNT15;


		//-----------------------------------------------------------------//
		/*!
			@brief  LOCO カウント上限／下限許容偏差レジスタ (LCNTDU, LCNTDL)
		*/
		//-----------------------------------------------------------------//
		static io16<0x000c28a8> LCNTDU;
		static io16<0x000c28aa> LCNTDL;

	};
	static gptb_t GPTB;


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
		typedef io16<base + 0x00> gtior_io;
		struct gtior_t : public gtior_io {
			using gtior_io::operator =;
			using gtior_io::operator ();
			using gtior_io::operator |=;
			using gtior_io::operator &=;

			bits_t<gtior_io,  0, 5> GTIOA;
			bit_t< gtior_io,  6>    OADFLT;
			bit_t< gtior_io,  7>    OAHLD;
			bits_t<gtior_io,  8, 6> GTIOB;
			bit_t< gtior_io, 14>    OBDFLT;
			bit_t< gtior_io, 15>    OBHLD;
		};
		static gtior_t GTIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ 割り込み出力設定レジスタ (GTINTAD)
		*/
		//-----------------------------------------------------------------//
		typedef io16<base + 0x02> gtintad_io;
		struct gtintad_t : public gtintad_io {
			using gtintad_io::operator =;
			using gtintad_io::operator ();
			using gtintad_io::operator |=;
			using gtintad_io::operator &=;

			bit_t< gtintad_io,  0>    GTINTA;
			bit_t< gtintad_io,  1>    GTINTB;
			bit_t< gtintad_io,  2>    GTINTC;
			bit_t< gtintad_io,  3>    GTINTD;
			bit_t< gtintad_io,  4>    GTINTE;
			bit_t< gtintad_io,  5>    GTINTF;
			bits_t<gtintad_io,  6, 2> GTINTPR;
			bit_t< gtintad_io, 11>    EINT;
			bit_t< gtintad_io, 12>    ADTRAUEN;
			bit_t< gtintad_io, 13>    ADTRADEN;
			bit_t< gtintad_io, 14>    ADTRBUEN;
			bit_t< gtintad_io, 15>    ADTRBDEN;
		};
		static gtintad_t GTINTAD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマコントロールレジスタ (GTCR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<base + 0x04> gtcr_io;
		struct gtcr_t : public gtcr_io {
			using gtcr_io::operator =;
			using gtcr_io::operator ();
			using gtcr_io::operator |=;
			using gtcr_io::operator &=;

			bits_t<gtcr_io,  0, 3> MD;
			bits_t<gtcr_io,  8, 2> TPCS;
			bits_t<gtcr_io, 12, 2> CCLR;
		};
		static gtcr_t GTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファイネーブルレジスタ (GTBER)
		*/
		//-----------------------------------------------------------------//
		typedef io16<base + 0x06> gtber_io;
		struct gtber_t : public gtber_io {
			using gtber_io::operator =;
			using gtber_io::operator ();
			using gtber_io::operator |=;
			using gtber_io::operator &=;

			bits_t<gtber_io,  0, 2> CCRA;
			bits_t<gtber_io,  2, 2> CCRB;
			bits_t<gtber_io,  4, 2> PR;
			bit_t< gtber_io,  6>    CCRSWT;
			bits_t<gtber_io,  8, 2> ADTTA;
			bit_t< gtber_io, 10>    ADTDA;
			bits_t<gtber_io, 12, 2> ADTTB;
			bit_t< gtber_io, 14>    ADTDB;
		};
		static gtber_t GTBER;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマカウント方向レジスタ (GTUDC)
		*/
		//-----------------------------------------------------------------//
		typedef io16<base + 0x08> gtudc_io;
		struct gtudc_t : public gtudc_io {
			using gtudc_io::operator =;
			using gtudc_io::operator ();
			using gtudc_io::operator |=;
			using gtudc_io::operator &=;

			bit_t< gtudc_io,  0>    UD;
			bit_t< gtudc_io,  1>    UDF;
		};
		static gtudc_t GTUDC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ割り込み、A/D 変換開始要求間引き設定レジスタ (GTITC)
		*/
		//-----------------------------------------------------------------//
		typedef io16<base + 0x0a> gtitc_io;
		struct gtitc_t : public gtitc_io {
			using gtitc_io::operator =;
			using gtitc_io::operator ();
			using gtitc_io::operator |=;
			using gtitc_io::operator &=;

			bit_t< gtitc_io,  0>    ITLA;
			bit_t< gtitc_io,  1>    ITLB;
			bit_t< gtitc_io,  2>    ITLC;
			bit_t< gtitc_io,  3>    ITLD;
			bit_t< gtitc_io,  4>    ITLE;
			bit_t< gtitc_io,  5>    ITLF;
			bits_t<gtitc_io,  6, 2> IVTC;
			bits_t<gtitc_io,  8, 3> IVTT;
			bit_t< gtitc_io, 12>    ADTAL;
			bit_t< gtitc_io, 14>    ADTBL;
		};
		static gtitc_t GTITC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマステータスレジスタ (GTST)
		*/
		//-----------------------------------------------------------------//
		typedef io16<base + 0x0c> gtst_io;
		struct gtst_t : public gtst_io {
			using gtst_io::operator =;
			using gtst_io::operator ();
			using gtst_io::operator |=;
			using gtst_io::operator &=;

			bit_t< gtst_io,  0>    TCFA;
			bit_t< gtst_io,  1>    TCFB;
			bit_t< gtst_io,  2>    TCFC;
			bit_t< gtst_io,  3>    TCFD;
			bit_t< gtst_io,  4>    TCFE;
			bit_t< gtst_io,  5>    TCFF;
			bit_t< gtst_io,  6>    TCFPO;
			bit_t< gtst_io,  7>    TCFPU;
			bits_t<gtst_io,  8, 3> ITCNT;
			bit_t< gtst_io, 11>    DTEF;
			bit_t< gtst_io, 15>    TUCF;
		};
		static gtst_t GTST;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマカウンタ (GTCNT)
		*/
		//-----------------------------------------------------------------//
		static io16<base + 0x0e> GTCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマコンペアキャプチャレジスタ (GTCCRm)(m=A..F)
		*/
		//-----------------------------------------------------------------//
		static io16<base + 0x10> GTCCRA;
		static io16<base + 0x12> GTCCRB;
		static io16<base + 0x14> GTCCRC;
		static io16<base + 0x16> GTCCRD;
		static io16<base + 0x18> GTCCRE;
		static io16<base + 0x1a> GTCCRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定レジスタ (GTPR)
		*/
		//-----------------------------------------------------------------//
		static io16<base + 0x1c> GTPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定バッファレジスタ (GTPBR)
		*/
		//-----------------------------------------------------------------//
		static io16<base + 0x1e> GTPBR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定ダブルバッファレジスタ (GTPDBR)
		*/
		//-----------------------------------------------------------------//
		static io16<base + 0x20> GTPDBR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスタｍ (GTADTRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		static io16<base + 0x24> GTADTRA;
		static io16<base + 0x2c> GTADTRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングバッファレジスタｍ (GTADTBRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		static io16<base + 0x26> GTADTBRA;
		static io16<base + 0x2e> GTADTBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングダブルバッファレジスタｍ (GTADTDBRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		static io16<base + 0x28> GTADTDBRA;
		static io16<base + 0x30> GTADTDBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力ネゲートコントロールレジスタ (GTONCR) @n
					※GPT0, GPT1, GPT2, GPT3
		*/
		//-----------------------------------------------------------------//
		typedef io16<base + 0x34> gtoncr_io;
		struct gtoncr_t : public gtoncr_io {
			using gtoncr_io::operator =;
			using gtoncr_io::operator ();
			using gtoncr_io::operator |=;
			using gtoncr_io::operator &=;

			bit_t< gtoncr_io,  0>    NEA;
			bit_t< gtoncr_io,  1>    NEB;
			bit_t< gtoncr_io,  2>    NVA;
			bit_t< gtoncr_io,  3>    NVB;
			bits_t<gtoncr_io,  4, 4> NFS;
			bit_t< gtoncr_io,  8>    NFV;
			bit_t< gtoncr_io, 12>    SWN;
			bit_t< gtoncr_io, 14>    OAE;
			bit_t< gtoncr_io, 15>    OBE;
		};
		static gtoncr_t GTONCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイムコントロールレジスタ (GTDTCR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<base + 0x36> gtdtcr_io;
		struct gtdtcr_t : public gtdtcr_io {
			using gtdtcr_io::operator =;
			using gtdtcr_io::operator ();
			using gtdtcr_io::operator |=;
			using gtdtcr_io::operator &=;

			bit_t< gtdtcr_io,  0>    TDE;
			bit_t< gtdtcr_io,  4>    TDBUE;
			bit_t< gtdtcr_io,  5>    TDBDE;
			bit_t< gtdtcr_io,  8>    TDFER;
		};
		static gtdtcr_t GTDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイム値レジスタｍ (GTDVm)(m=U, D)
		*/
		//-----------------------------------------------------------------//
		static io16<base + 0x38> GTDVU;
		static io16<base + 0x3a> GTDVD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイムバッファレジスタｍ (GTDBm)(m=U, D)
		*/
		//-----------------------------------------------------------------//
		static io16<base + 0x3c> GTDBU;
		static io16<base + 0x3e> GTDBD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力保護機能ステータスレジスタ (GTSOS)
		*/
		//-----------------------------------------------------------------//
		typedef io16<base + 0x40> gtsos_io;
		struct gtsos_t : public gtsos_io {
			using gtsos_io::operator =;
			using gtsos_io::operator ();
			using gtsos_io::operator |=;
			using gtsos_io::operator &=;

			bits<gtsos_io, 0, 2>  SOS;
		};
		static gtsos_t GTSOS;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力保護機能一時解除レジスタ (GTSOTR)
		*/
		//-----------------------------------------------------------------//
		typedef io16<base + 0x42> gtsotr_io;
		struct gtsotr_t : public gtsotr_io {
			using gtsotr_io::operator =;
			using gtsotr_io::operator ();
			using gtsotr_io::operator |=;
			using gtsotr_io::operator &=;

			bit<gtsotr_io, 0>  SOTR;
		};
		static gtsos_t GTSOTR;

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
