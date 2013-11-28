#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・GPT 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct gpt_base_t {

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









	};
	static gpt_base_t GPT;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 定義基底クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct gpt_t {

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
	typedef gpt_t<0x000c2100> GPT0;
	typedef gpt_t<0x000c2180> GPT1;
	typedef gpt_t<0x000c2200> GPT2;
	typedef gpt_t<0x000c2280> GPT3;
	typedef gpt_t<0x000c2900> GPT4;
	typedef gpt_t<0x000c2980> GPT5;
	typedef gpt_t<0x000c2a00> GPT6;
	typedef gpt_t<0x000c2a80> GPT7;
}
