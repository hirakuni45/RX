#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・GPTa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  汎用 PWM タイマ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct gpt_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマソフトウェアスタートレジスタ (GTSTR)
		*/
		//-----------------------------------------------------------------//
		struct gtstr_t : public rw16_t<0x000C2000> {
			typedef rw16_t<0x000C2000> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CST0;
			bit_rw_t<io_, bitpos::B1>  CST1;
			bit_rw_t<io_, bitpos::B2>  CST2;
			bit_rw_t<io_, bitpos::B3>  CST3;
		};
		typedef gtstr_t GTSTR_;
		static  GTSTR_ GTSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタ制御レジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		struct nfcr_t : public rw16_t<0x000C2002> {
			typedef rw16_t<0x000C2002> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_,  bitpos::B0>     NFA0EN;
			bit_rw_t<io_,  bitpos::B1>     NFB0EN;
			bit_rw_t<io_,  bitpos::B2>     NFA1EN;
			bit_rw_t<io_,  bitpos::B3>     NFB1EN;
			bit_rw_t<io_,  bitpos::B4>     NFA2EN;
			bit_rw_t<io_,  bitpos::B5>     NFB2EN;
			bit_rw_t<io_,  bitpos::B6>     NFA3EN;
			bit_rw_t<io_,  bitpos::B7>     NFB3EN;
			bits_rw_t<io_, bitpos::B8,  2> NFCS0;
			bits_rw_t<io_, bitpos::B10, 2> NFCS1;
			bits_rw_t<io_, bitpos::B12, 2> NFCS2;
			bits_rw_t<io_, bitpos::B14, 2> NFCS3;
		};
		typedef nfcr_t NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因スタート / ストップ制御レジスタ（GTHSCR）
		*/
		//-----------------------------------------------------------------//
		struct gthscr_t : public rw16_t<0x000C2004> {
			typedef rw16_t<0x000C2004> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CSHW0;
			bits_rw_t<io_, bitpos::B2, 2>  CSHW1;
			bits_rw_t<io_, bitpos::B4, 2>  CSHW2;
			bits_rw_t<io_, bitpos::B6, 2>  CSHW3;
			bits_rw_t<io_, bitpos::B8, 2>  CPHW0;
			bits_rw_t<io_, bitpos::B10, 2> CPHW1;
			bits_rw_t<io_, bitpos::B12, 2> CPHW2;
			bits_rw_t<io_, bitpos::B14, 2> CPHW3;
		};
		typedef gthscr_t GTHSCR_;
		static  GTHSCR_ GTHSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェア要因クリア制御レジスタ（GTHCCR）
		*/
		//-----------------------------------------------------------------//
		struct gthccr_t : public rw16_t<0x000C2006> {
			typedef rw16_t<0x000C2006> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CCHW0;
			bits_rw_t<io_, bitpos::B2, 2>  CCHW1;
			bits_rw_t<io_, bitpos::B4, 2>  CCHW2;
			bits_rw_t<io_, bitpos::B6, 2>  CCHW3;
			bit_rw_t< io_, bitpos::B8>     CCSW0;
			bit_rw_t< io_, bitpos::B9>     CCSW1;
			bit_rw_t< io_, bitpos::B10>    CCSW2;
			bit_rw_t< io_, bitpos::B11>    CCSW3;
		};
		typedef gthccr_t GTHCCR_;
		static  GTHCCR_ GTHCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアスタート要因セレクトレジスタ (GTHSSR)
		*/
		//-----------------------------------------------------------------//
		struct gthssr_t : public rw16_t<0x000C2008> {
			typedef rw16_t<0x000C2008> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  CSHSL0;
			bits_rw_t<io_, bitpos::B4,  4>  CSHSL1;
			bits_rw_t<io_, bitpos::B8,  4>  CSHSL2;
			bits_rw_t<io_, bitpos::B12, 4>  CSHSL3;
		};
		typedef gthssr_t GTHSSR_;
		static  GTHSSR_ GTHSSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマハードウェアストップ / クリア要因セレクトレジスタ（GTHPSR）
		*/
		//-----------------------------------------------------------------//
		struct gthpsr_t : public rw16_t<0x000C200A> {
			typedef rw16_t<0x000C200A> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4>  CSHPL0;
			bits_rw_t<io_, bitpos::B4,  4>  CSHPL1;
			bits_rw_t<io_, bitpos::B8,  4>  CSHPL2;
			bits_rw_t<io_, bitpos::B12, 4>  CSHPL3;
		};
		typedef gthpsr_t GTHPSR_;
		static  GTHPSR_ GTHPSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ書き込み保護レジスタ (GTWP)
		*/
		//-----------------------------------------------------------------//
		struct gtwp_t : public rw16_t<0x000C200C> {
			typedef rw16_t<0x000C200C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   WP0;
			bit_rw_t<io_, bitpos::B1>   WP1;
			bit_rw_t<io_, bitpos::B2>   WP2;
			bit_rw_t<io_, bitpos::B3>   WP3;
		};
		typedef gtwp_t GTWP_;
		static  GTWP_ GTWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマシンクロレジスタ (GTSYNC)
		*/
		//-----------------------------------------------------------------//
		struct gtsync_t : public rw16_t<0x000C200E> {
			typedef rw16_t<0x000C200E> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2>  SYNC0;
			bits_rw_t<io_, bitpos::B4,  2>  SYNC1;
			bits_rw_t<io_, bitpos::B8,  2>  SYNC2;
			bits_rw_t<io_, bitpos::B12, 2>  SYNC3;
		};
		typedef gtsync_t GTSYNC_;
		static  GTSYNC_ GTSYNC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ外部トリガ入力割り込みレジスタ (GTETINT)
		*/
		//-----------------------------------------------------------------//
		struct gtetint_t : public rw16_t<0x000C2010> {
			typedef rw16_t<0x000C2010> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>      ETIPEN;
			bit_rw_t< io_, bitpos::B1>      ETINEN;
			bits_rw_t<io_, bitpos::B13, 2>  GTENFCS;
			bit_rw_t< io_, bitpos::B15>     GTETRGEN;
		};
		typedef gtetint_t GTETINT_;
		static  GTETINT_ GTETINT;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファ動作禁止レジスタ (GTBDR)
		*/
		//-----------------------------------------------------------------//
		struct gtbdr_t : public rw16_t<0x000C2014> {
			typedef rw16_t<0x000C2014> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>    BD00;
			bit_rw_t<io_, bitpos::B1>    BD01;
			bit_rw_t<io_, bitpos::B2>    BD02;
			bit_rw_t<io_, bitpos::B3>    BD03;
			bit_rw_t<io_, bitpos::B4>    BD10;
			bit_rw_t<io_, bitpos::B5>    BD11;
			bit_rw_t<io_, bitpos::B6>    BD12;
			bit_rw_t<io_, bitpos::B7>    BD13;
			bit_rw_t<io_, bitpos::B8>    BD20;
			bit_rw_t<io_, bitpos::B9>    BD21;
			bit_rw_t<io_, bitpos::B10>   BD22;
			bit_rw_t<io_, bitpos::B11>   BD23;
			bit_rw_t<io_, bitpos::B12>   BD30;
			bit_rw_t<io_, bitpos::B13>   BD31;
			bit_rw_t<io_, bitpos::B14>   BD32;
			bit_rw_t<io_, bitpos::B15>   BD33;
		};
		typedef gtbdr_t GTBDR_;
		static  GTBDR_ GTBDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマスタート書き込み保護レジスタ (GTSWP)
		*/
		//-----------------------------------------------------------------//
		struct gtswp_t : public rw16_t<0x000C2018> {
			typedef rw16_t<0x000C2018> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SWP0;
			bit_rw_t<io_, bitpos::B1>  SWP1;
			bit_rw_t<io_, bitpos::B2>  SWP2;
			bit_rw_t<io_, bitpos::B3>  SWP3;
		};
		typedef gtswp_t GTSWP_;
		static  GTSWP_ GTSWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマクリア書き込み保護レジスタ（GTCWP）
		*/
		//-----------------------------------------------------------------//
		struct gtcwp_t : public rw16_t<0x000C201C> {
			typedef rw16_t<0x000C201C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CWP0;
			bit_rw_t<io_, bitpos::B1>  CWP1;
			bit_rw_t<io_, bitpos::B2>  CWP2;
			bit_rw_t<io_, bitpos::B3>  CWP3;
		};
		typedef gtcwp_t GTCWP_;
		static  GTCWP_ GTCWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ共通レジスタ書き込み保護レジスタ（GTCMNWP）
		*/
		//-----------------------------------------------------------------//
		struct gtcmnwp_t : public rw16_t<0x000C2020> {
			typedef rw16_t<0x000C2020> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMNWP;
		};
		typedef gtcmnwp_t GTCMNWP_;
		static  GTCMNWP_ GTCMNWP;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマモードレジスタ（GTMDR）
		*/
		//-----------------------------------------------------------------//
		struct gtmdr_t : public rw16_t<0x000C2024> {
			typedef rw16_t<0x000C2024> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  LWA01;
			bit_rw_t<io_, bitpos::B1>  LWA23;
		};
		typedef gtmdr_t GTMDR_;
		static  GTMDR_ GTMDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ外部クロックノイズフィルタコントロールレジスタ（GTECNFCR）
		*/
		//-----------------------------------------------------------------//
		struct gtecnfcr_t : public rw32_t<0x000C2028> {
			typedef rw32_t<0x000C2028> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>      NFENECA;
			bit_rw_t< io_, bitpos::B1>      NFENECB;
			bit_rw_t< io_, bitpos::B2>      NFENECC;
			bit_rw_t< io_, bitpos::B3>      NFENECD;

			bit_rw_t< io_, bitpos::B8>      INVECA;
			bit_rw_t< io_, bitpos::B9>      INVECB;
			bit_rw_t< io_, bitpos::B10>     INVECC;
			bit_rw_t< io_, bitpos::B11>     INVECD;

			bits_rw_t<io_, bitpos::B16, 2>  NFCSECA;
			bits_rw_t<io_, bitpos::B18, 2>  NFCSECB;
			bits_rw_t<io_, bitpos::B20, 2>  NFCSECC;
			bits_rw_t<io_, bitpos::B22, 2>  NFCSECD;
		};
		typedef gtecnfcr_t GTECNFCR_;
		static  GTECNFCR_ GTECNFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ A/D 変換開始要求信号モニタレジスタ（GTADSMR）
		*/
		//-----------------------------------------------------------------//
		struct gtadsmr_t : public rw32_t<0x000C202C> {
			typedef rw32_t<0x000C202C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   ADSMS0;
			bit_rw_t< io_, bitpos::B8>      ADSMEN0;

			bits_rw_t<io_, bitpos::B16, 4>  ADSMS1;
			bit_rw_t< io_, bitpos::B24>     ADSMEN1;
		};
		typedef gtadsmr_t GTADSMR_;
		static  GTADSMR_ GTADSMR;
	};
	typedef gpt_t<void> GPT;


	template <class _> typename gpt_t<_>::GTSTR_ gpt_t<_>::GTSTR;
	template <class _> typename gpt_t<_>::NFCR_ gpt_t<_>::NFCR;
	template <class _> typename gpt_t<_>::GTHSCR_ gpt_t<_>::GTHSCR;
	template <class _> typename gpt_t<_>::GTHCCR_ gpt_t<_>::GTHCCR;
	template <class _> typename gpt_t<_>::GTHSSR_ gpt_t<_>::GTHSSR;
	template <class _> typename gpt_t<_>::GTHPSR_ gpt_t<_>::GTHPSR;
	template <class _> typename gpt_t<_>::GTWP_ gpt_t<_>::GTWP;
	template <class _> typename gpt_t<_>::GTSYNC_ gpt_t<_>::GTSYNC;
	template <class _> typename gpt_t<_>::GTETINT_ gpt_t<_>::GTETINT;
	template <class _> typename gpt_t<_>::GTBDR_ gpt_t<_>::GTBDR;
	template <class _> typename gpt_t<_>::GTSWP_ gpt_t<_>::GTSWP;
	template <class _> typename gpt_t<_>::GTCWP_ gpt_t<_>::GTCWP;
	template <class _> typename gpt_t<_>::GTCMNWP_ gpt_t<_>::GTCMNWP;
	template <class _> typename gpt_t<_>::GTMDR_ gpt_t<_>::GTMDR;
	template <class _> typename gpt_t<_>::GTECNFCR_ gpt_t<_>::GTECNFCR;
	template <class _> typename gpt_t<_>::GTADSMR_ gpt_t<_>::GTADSMR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct gptn_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ I/O コントロールレジスタ (GTIOR)
		*/
		//-----------------------------------------------------------------//
		struct gtior_t : public rw16_t<base + 0x00> {
			typedef rw16_t<base + 0x00> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6> GTIOA;
			bit_rw_t <io_, bitpos::B6>    OADFLT;
			bit_rw_t <io_, bitpos::B7>    OAHLD;
			bits_rw_t<io_, bitpos::B8, 6> GTIOB;
			bit_rw_t <io_, bitpos::B14>   OBDFLT;
			bit_rw_t <io_, bitpos::B15>   OBHLD;
		};
		typedef gtior_t GTIOR_;
		static  GTIOR_ GTIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ 割り込み出力設定レジスタ (GTINTAD)
		*/
		//-----------------------------------------------------------------//
		struct gtintad_t : public rw16_t<base + 0x02> {
			typedef rw16_t<base + 0x02> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>    GTINTA;
			bit_rw_t< io_, bitpos::B1>    GTINTB;
			bit_rw_t< io_, bitpos::B2>    GTINTC;
			bit_rw_t< io_, bitpos::B3>    GTINTD;
			bit_rw_t< io_, bitpos::B4>    GTINTE;
			bit_rw_t< io_, bitpos::B5>    GTINTF;
			bits_rw_t<io_, bitpos::B6, 2> GTINTPR;

			bit_rw_t< io_, bitpos::B11>   EINT;
			bit_rw_t< io_, bitpos::B12>   ADTRAUEN;
			bit_rw_t< io_, bitpos::B13>   ADTRADEN;
			bit_rw_t< io_, bitpos::B14>   ADTRBUEN;
			bit_rw_t< io_, bitpos::B15>   ADTRBDEN;
		};
		typedef gtintad_t GTINTAD_;
		static  GTINTAD_ GTINTAD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマコントロールレジスタ (GTCR)
		*/
		//-----------------------------------------------------------------//
		struct gtcr_t : public rw16_t<base + 0x04> {
			typedef rw16_t<base + 0x04> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  MD;
			bits_rw_t<io_, bitpos::B8, 4>  TPCS;
			bits_rw_t<io_, bitpos::B12, 2> CCLR;
		};
		typedef gtcr_t GTCR_;
		static  GTCR_ GTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマバッファイネーブルレジスタ (GTBER)
		*/
		//-----------------------------------------------------------------//
		struct gtber_t : public rw16_t<base + 0x06> {
			typedef rw16_t<base + 0x06> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CCRA;
			bits_rw_t<io_, bitpos::B2, 2>  CCRB;
			bits_rw_t<io_, bitpos::B4, 2>  PR;
			bit_rw_t< io_, bitpos::B6>     CCRSWT;
			bits_rw_t<io_, bitpos::B8, 2>  ADTTA;
			bit_rw_t< io_, bitpos::B10>    ADTDA;
			bits_rw_t<io_, bitpos::B12, 2> ADTTB;
			bit_rw_t< io_, bitpos::B14>    ADTDB;
		};
		typedef gtber_t GTBER_;
		static  GTBER_ GTBER;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマカウント方向レジスタ (GTUDC)
		*/
		//-----------------------------------------------------------------//
		struct gtudc_t : public rw16_t<base + 0x08> {
			typedef rw16_t<base + 0x08> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     UD;
			bit_rw_t< io_, bitpos::B1>     UDF;
			bits_rw_t<io_, bitpos::B8, 2>  OADTY;
			bit_rw_t< io_, bitpos::B10>    OADTYF;
			bit_rw_t< io_, bitpos::B11>    OADTYR;
			bits_rw_t<io_, bitpos::B12, 2> OBDTY;
			bit_rw_t< io_, bitpos::B14>    OBDTYF;
			bit_rw_t< io_, bitpos::B15>    OBDTYR;
		};
		typedef gtudc_t GTUDC_;
		static  GTUDC_ GTUDC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ割り込み、A/D 変換開始要求間引き設定レジスタ (GTITC)
		*/
		//-----------------------------------------------------------------//
		struct gtitc_t : public rw16_t<base + 0x0A> {
			typedef rw16_t<base + 0x0A> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>     ITLA;
			bit_rw_t< io_, bitpos::B1>     ITLB;
			bit_rw_t< io_, bitpos::B2>     ITLC;
			bit_rw_t< io_, bitpos::B3>     ITLD;
			bit_rw_t< io_, bitpos::B4>     ITLE;
			bit_rw_t< io_, bitpos::B5>     ITLF;
			bits_rw_t<io_, bitpos::B6, 2 > IVTC;
			bits_rw_t<io_, bitpos::B8, 3 > IVTT;
			bit_rw_t< io_, bitpos::B12>    ADTAL;
			bit_rw_t< io_, bitpos::B14>    ADTBL;
		};
		typedef gtitc_t GTITC_;
		static  GTITC_ GTITC;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマステータスレジスタ (GTST)
		*/
		//-----------------------------------------------------------------//
		struct gtst_t : public rw16_t<base + 0x0C> {
			typedef rw16_t<base + 0x0C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 3> ITCNT;
			bit_rw_t< io_, bitpos::B11>   DTEF;
			bit_rw_t< io_, bitpos::B15>   TUCF;
		};
		typedef gtst_t GTST_;
		static  GTST_ GTST;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマカウンタ (GTCNT)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x0E> GTCNT_;
		static  GTCNT_ GTCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマコンペアキャプチャレジスタ m（GTCCRm）（m = A ～ F）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x10> GTCCRA_;
		static  GTCCRA_ GTCCRA;
		typedef rw16_t<base + 0x12> GTCCRB_;
		static  GTCCRB_ GTCCRB;
		typedef rw16_t<base + 0x14> GTCCRC_;
		static  GTCCRC_ GTCCRC;
		typedef rw16_t<base + 0x16> GTCCRD_;
		static  GTCCRD_ GTCCRD;
		typedef rw16_t<base + 0x18> GTCCRE_;
		static  GTCCRE_ GTCCRE;
		typedef rw16_t<base + 0x1A> GTCCRF_;
		static  GTCCRF_ GTCCRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定レジスタ (GTPR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1C> GTPR_;
		static  GTPR_ GTPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定バッファレジスタ (GTPBR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1E> GTPBR_;
		static  GTPBR_ GTPBR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ周期設定ダブルバッファレジスタ (GTPDBR)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x20> GTPDBR_;
		static  GTPDBR_ GTPDBR;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスタｍ (GTADTRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x24> GTADTRA_;
		static  GTADTRA_ GTADTRA;
		typedef rw16_t<base + 0x2C> GTADTRB_;
		static  GTADTRB_ GTADTRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングバッファレジスタｍ (GTADTBRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x26> GTADTBRA_;
		static  GTADTBRA_ GTADTBRA;
		typedef rw16_t<base + 0x2E> GTADTBRB_;
		static  GTADTBRB_ GTADTBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングダブルバッファレジスタｍ (GTADTDBRm)(m=A, B)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x28> GTADTDBRA_;
		static  GTADTDBRA_ GTADTDBRA;
		typedef rw16_t<base + 0x30> GTADTDBRB_;
		static  GTADTDBRB_ GTADTDBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力ネゲートコントロールレジスタ (GTONCR)
		*/
		//-----------------------------------------------------------------//
		struct gtoncr_t : public rw16_t<base + 0x34> {
			typedef rw16_t<base + 0x34> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>    NEA;
			bit_rw_t< io_, bitpos::B1>    NEB;
			bit_rw_t< io_, bitpos::B2>    NVA;
			bit_rw_t< io_, bitpos::B3>    NVB;
			bits_rw_t<io_, bitpos::B4, 4> NFS;
			bit_rw_t< io_, bitpos::B8>    NFV;

			bit_rw_t< io_, bitpos::B12>   SWN;

			bit_rw_t< io_, bitpos::B14>   OAE;
			bit_rw_t< io_, bitpos::B15>   OBE;
		};
		typedef gtoncr_t GTONCR_;
		static  GTONCR_ GTONCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイムコントロールレジスタ (GTDTCR)
		*/
		//-----------------------------------------------------------------//
		struct gtdtcr_t : public rw16_t<base + 0x36> {
			typedef rw16_t<base + 0x36> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t< io_, bitpos::B0>  TDE;
			bit_rw_t< io_, bitpos::B4>  TDBUE;
			bit_rw_t< io_, bitpos::B5>  TDBDE;
			bit_rw_t< io_, bitpos::B8>  TDFER;
		};
		typedef gtdtcr_t GTDTCR_;
		static  GTDTCR_ GTDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイム値レジスタｍ (GTDVm)(m=U, D)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x38> GTDVU_;
		static  GTDVU_ GTDVU;
		typedef rw16_t<base + 0x3A> GTDVD_;
		static  GTDVD_ GTDVD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマデッドタイムバッファレジスタｍ (GTDBm)(m=U, D)
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x3C> GTDBU_;
		static  GTDBU_ GTDBU;
		typedef rw16_t<base + 0x3E> GTDBD_;
		static  GTDBD_ GTDBD;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力保護機能ステータスレジスタ (GTSOS)
		*/
		//-----------------------------------------------------------------//
		struct gtsos_t : public rw16_t<base + 0x40> {
			typedef rw16_t<base + 0x40> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  SOS;
		};
		typedef gtsos_t GTSOS_;
		static  GTSOS_ GTSOS;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマ出力保護機能一時解除レジスタ (GTSOTR)
		*/
		//-----------------------------------------------------------------//
		struct gtsotr_t : public rw16_t<base + 0x42> {
			typedef rw16_t<base + 0x42> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SOTR;
		};
		typedef gtsos_t GTSOTR_;
		static  GTSOTR_ GTSOTR;
	};
	typedef gptn_t<0x000C2100, peripheral::GPT0> GPT0;
	typedef gptn_t<0x000C2180, peripheral::GPT1> GPT1;
	typedef gptn_t<0x000C2200, peripheral::GPT2> GPT2;
	typedef gptn_t<0x000C2280, peripheral::GPT3> GPT3;


	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTIOR_ gptn_t<base, per>::GTIOR;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTINTAD_ gptn_t<base, per>::GTINTAD;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTCR_ gptn_t<base, per>::GTCR;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTBER_ gptn_t<base, per>::GTBER;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTUDC_ gptn_t<base, per>::GTUDC;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTITC_ gptn_t<base, per>::GTITC;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTST_ gptn_t<base, per>::GTST;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTCNT_ gptn_t<base, per>::GTCNT;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTCCRA_ gptn_t<base, per>::GTCCRA;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTCCRB_ gptn_t<base, per>::GTCCRB;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTCCRC_ gptn_t<base, per>::GTCCRC;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTCCRD_ gptn_t<base, per>::GTCCRD;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTCCRE_ gptn_t<base, per>::GTCCRE;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTCCRF_ gptn_t<base, per>::GTCCRF;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTPR_ gptn_t<base, per>::GTPR;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTPBR_ gptn_t<base, per>::GTPBR;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTPDBR_ gptn_t<base, per>::GTPDBR;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTADTRA_ gptn_t<base, per>::GTADTRA;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTADTRB_ gptn_t<base, per>::GTADTRB;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTADTBRA_ gptn_t<base, per>::GTADTBRA;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTADTBRB_ gptn_t<base, per>::GTADTBRB;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTADTDBRA_ gptn_t<base, per>::GTADTDBRA;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTADTDBRB_ gptn_t<base, per>::GTADTDBRB;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTONCR_ gptn_t<base, per>::GTONCR;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTDTCR_ gptn_t<base, per>::GTDTCR;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTDVU_ gptn_t<base, per>::GTDVU;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTDVD_ gptn_t<base, per>::GTDVD;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTDBU_ gptn_t<base, per>::GTDBU;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTDBD_ gptn_t<base, per>::GTDBD;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTSOS_ gptn_t<base, per>::GTSOS;
	template <uint32_t base, peripheral per> typename gptn_t<base, per>::GTSOTR_ gptn_t<base, per>::GTSOTR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT 連結、定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct gptl_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワードカウンタレジスタ（GTCNTLW）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x00> GTCNTLW_;
		static  GTCNTLW_ GTCNTLW;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマロングワードコンペアキャプチャレジスタ m（GTCCRmLW）（m = A ～ F）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x04> GTCCRALW_;
		static  GTCCRALW_ GTCCRALW;
		typedef rw32_t<base + 0x08> GTCCRBLW_;
		static  GTCCRBLW_ GTCCRBLW;
		typedef rw32_t<base + 0x0C> GTCCRCLW_;
		static  GTCCRCLW_ GTCCRCLW;
		typedef rw32_t<base + 0x10> GTCCRDLW_;
		static  GTCCRDLW_ GTCCRDLW;
		typedef rw32_t<base + 0x14> GTCCRELW_;
		static  GTCCRELW_ GTCCRELW;
		typedef rw32_t<base + 0x18> GTCCRFLW_;
		static  GTCCRFLW_ GTCCRFLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワード周期設定レジスタ（GTPRLW）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x1C> GTPRLW_;
		static  GTPRLW_ GTPRLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワード周期設定バッファレジスタ（GTPBRLW）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x20> GTPBRLW_;
		static  GTPBRLW_ GTPBRLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワード周期設定ダブルバッファレジスタ（GTPDBRLW）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x24> GTPDBRLW_;
		static  GTPDBRLW_ GTPDBRLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ロングワード A/D 変換開始要求タイミングレジスタ m（GTADTRmLW）（m = A, B）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x28> GTADTRALW_;
		static  GTADTRALW_ GTADTRALW;
		typedef rw32_t<base + 0x34> GTADTRBLW_;
		static  GTADTRBLW_ GTADTRBLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ロングワード A/D 変換開始要求タイミングバッファレジスタ m（GTADTBRmLW）（m = A, B）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x2C> GTADTBRALW_;
		static  GTADTBRALW_ GTADTBRALW;
		typedef rw32_t<base + 0x38> GTADTBRBLW_;
		static  GTADTBRBLW_ GTADTBRBLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ロングワード A/D 変換開始要求タイミングダブルバッファレジスタ m（GTADTDBRmLW）（m = A, B）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x30> GTADTDBRALW_;
		static  GTADTDBRALW_ GTADTDBRALW;
		typedef rw32_t<base + 0x3C> GTADTDBRBLW_;
		static  GTADTDBRBLW_ GTADTDBRBLW;

		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワードデッドタイム値レジスタ m（GTDVmLW）（m = U, D）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x40> GTDVULW_;
		static  GTDVULW_ GTDVULW;
		typedef rw32_t<base + 0x44> GTDVDLW_;
		static  GTDVDLW_ GTDVDLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  汎用 PWM タイマロングワードデッドタイムバッファレジスタ m（GTDBmLW）（m = U, D）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x48> GTDBULW_;
		static  GTDBULW_ GTDBULW;
		typedef rw32_t<base + 0x4C> GTDBDLW_;
		static  GTDBDLW_ GTDBDLW;

	};
	typedef gptl_t<0x000C2300> GPT01;
	typedef gptl_t<0x000C2380> GPT23;


	template <uint32_t base> typename gptl_t<base>::GTCNTLW_ gptl_t<base>::GTCNTLW;
	template <uint32_t base> typename gptl_t<base>::GTCCRALW_ gptl_t<base>::GTCCRALW;
	template <uint32_t base> typename gptl_t<base>::GTCCRBLW_ gptl_t<base>::GTCCRBLW;
	template <uint32_t base> typename gptl_t<base>::GTCCRCLW_ gptl_t<base>::GTCCRCLW;
	template <uint32_t base> typename gptl_t<base>::GTCCRDLW_ gptl_t<base>::GTCCRDLW;
	template <uint32_t base> typename gptl_t<base>::GTCCRELW_ gptl_t<base>::GTCCRELW;
	template <uint32_t base> typename gptl_t<base>::GTCCRFLW_ gptl_t<base>::GTCCRFLW;
	template <uint32_t base> typename gptl_t<base>::GTPRLW_ gptl_t<base>::GTPRLW;
	template <uint32_t base> typename gptl_t<base>::GTPBRLW_ gptl_t<base>::GTPBRLW;
	template <uint32_t base> typename gptl_t<base>::GTPDBRLW_ gptl_t<base>::GTPDBRLW;
	template <uint32_t base> typename gptl_t<base>::GTADTRALW_ gptl_t<base>::GTADTRALW;
	template <uint32_t base> typename gptl_t<base>::GTADTRBLW_ gptl_t<base>::GTADTRBLW;
	template <uint32_t base> typename gptl_t<base>::GTADTBRALW_ gptl_t<base>::GTADTBRALW;
	template <uint32_t base> typename gptl_t<base>::GTADTBRBLW_ gptl_t<base>::GTADTBRBLW;
	template <uint32_t base> typename gptl_t<base>::GTADTDBRALW_ gptl_t<base>::GTADTDBRALW;
	template <uint32_t base> typename gptl_t<base>::GTADTDBRBLW_ gptl_t<base>::GTADTDBRBLW;
	template <uint32_t base> typename gptl_t<base>::GTDVULW_ gptl_t<base>::GTDVULW;
	template <uint32_t base> typename gptl_t<base>::GTDVDLW_ gptl_t<base>::GTDVDLW;
	template <uint32_t base> typename gptl_t<base>::GTDBULW_ gptl_t<base>::GTDBULW;
	template <uint32_t base> typename gptl_t<base>::GTDBDLW_ gptl_t<base>::GTDBDLW;
}
