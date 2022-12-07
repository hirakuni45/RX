#pragma once
//=========================================================================//
/*!	@file
	@brief	RX72N/RX72M/RX66T/RX72T 汎用 PWM タイマ（GPTW）定義 @n
			RX72N/RX72M: GPTW0 - GPTW3 @n
			RX66T/RX72T: GPTW0 - GPTW9
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  汎用 PWM タイマ・クラス
		@param[in]	base	ベースアドレス
		@param[in]	peri	ペリフェラル型
		@param[in]	gtcia	GTCIAn GTCCRAレジスタのインプットキャプチャ /コンペアマッチ
		@param[in]	gtcib	GTCIBn GTCCRBレジスタのインプットキャプチャ /コンペアマッチ
		@param[in]	gtcic	GTCICn GTCCRCレジスタのコンペアマッチ
		@param[in]	gtcid	GTCIDn GTCCRDレジスタのコンペアマッチ
		@param[in]	gdte	GDTEn  デッドタイムエラー
		@param[in]	gtcie	GTCIEn GTCCREレジスタのコンペアマッチ
		@param[in]	gtcif	GTCIFn GTCCRFレジスタのコンペアマッチ
		@param[in]	gtciu	GTCIUn GTCNTカウンタのアンダフロー
		@param[in]	gtciv	GTCIVn GTCNTカウンタのオーバフロー (GTPRレジスタのコンペアマッチ)
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	struct gptw_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto CHANNEL_NO = static_cast<uint8_t>(per) - static_cast<uint8_t>(peripheral::GPTW0);	///< チャネル番号
		static constexpr auto GTCIA = gtcia;	///< GTCIAn 割り込みベクタ
		static constexpr auto GTCIB = gtcib;	///< GTCIBn 割り込みベクタ
		static constexpr auto GTCIC = gtcic;	///< GTCICn 割り込みベクタ
		static constexpr auto GTCID = gtcid;	///< GTCIDn 割り込みベクタ
		static constexpr auto GDTE  = gdte;		///< GDTEn  割り込みベクタ
		static constexpr auto GTCIE = gtcie;	///< GTCIEn 割り込みベクタ
		static constexpr auto GTCIF = gtcif;	///< GTCIFn 割り込みベクタ
		static constexpr auto GTCIU = gtciu;	///< GTCIUn 割り込みベクタ
		static constexpr auto GTCIV = gtciv;	///< GTCIVn 割り込みベクタ

#if defined(SIG_RX66T) || defined(SIG_RX72T)
		static constexpr uint32_t PCLK = clock_profile::PCLKC;	///< カウント基準クロック
#elif defined(SIG_RX72N) || defined(SIG_RX72M)
		static constexpr uint32_t PCLK = clock_profile::PCLKA;	///< カウント基準クロック
#endif


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
			bits_rw_t<io_, bitpos::B8, 8>  PRKEY;
		};
		typedef gtwp_t<base + 0x00> GTWP_;
		static GTWP_ GTWP;


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
		typedef gtstr_t<base + 0x04> GTSTR_;
		static GTSTR_ GTSTR;


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
		typedef gtstp_t<base + 0x08> GTSTP_;
		static GTSTP_ GTSTP;


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
		typedef gtclr_t<base + 0x0C> GTCLR_;
		static GTCLR_ GTCLR;


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
		typedef gtssr_t<base + 0x10> GTSSR_;
		static GTSSR_ GTSSR;


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
		typedef gtpsr_t<base + 0x14> GTPSR_;
		static GTPSR_ GTPSR;


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
		typedef gtcsr_t<base + 0x18> GTCSR_;
		static GTCSR_ GTCSR;


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
		typedef gtupsr_t<base + 0x1C> GTUPSR_;
		static GTUPSR_ GTUPSR;


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
		typedef gtdnsr_t<base + 0x20> GTDNSR_;
		static GTDNSR_ GTDNSR;


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
		typedef gticasr_t<base + 0x24> GTICASR_;
		static GTICASR_ GTICASR;


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
		typedef gticbsr_t<base + 0x28> GTICBSR_;
		static GTICBSR_ GTICBSR;


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
		typedef gtcr_t<base + 0x2C> GTCR_;
		static GTCR_ GTCR;


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
		typedef gtuddtyc_t<base + 0x30> GTUDDTYC_;
		static GTUDDTYC_ GTUDDTYC;


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

			bits_rw_t<io_, bitpos::B0, 5>   GTIOA;

			bit_rw_t <io_, bitpos::B6>      OADFLT;
			bit_rw_t <io_, bitpos::B7>      OAHLD;
			bit_rw_t <io_, bitpos::B8>      OAE;
			bits_rw_t<io_, bitpos::B9, 2>   OADF;

			bit_rw_t <io_, bitpos::B13>     NFAEN;
			bits_rw_t<io_, bitpos::B14, 2>  NFCSA;

			bits_rw_t<io_, bitpos::B16, 5>  GTIOB;

			bit_rw_t <io_, bitpos::B22>     OBDFLT;
			bit_rw_t <io_, bitpos::B23>     OBHLD;
			bit_rw_t <io_, bitpos::B24>     OBE;
			bits_rw_t<io_, bitpos::B25, 2>  OBDF;

			bit_rw_t <io_, bitpos::B29>     NFBEN;
			bits_rw_t<io_, bitpos::B30, 2>  NFCSB;
		};
		typedef gtior_t<base + 0x34> GTIOR_;
		static GTIOR_ GTIOR;


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
		typedef gtintad_t<base + 0x38> GTINTAD_;
		static GTINTAD_ GTINTAD;


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
		typedef gtst_t<base + 0x3C> GTST_;
		static GTST_ GTST;


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
		typedef gtber_t<base + 0x40> GTBER_;
		static GTBER_ GTBER;


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
		typedef gtitc_t<base + 0x44> GTITC_;
		static GTITC_ GTITC;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマカウンタ (GTCNT)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x48>  GTCNT_;
		static GTCNT_ GTCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマコンペアキャプチャレジスタ m (GTCCRm) (m = A ～ F)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x4C>  GTCCRA_;
		static GTCCRA_ GTCCRA;
		typedef rw32_t<base + 0x50>  GTCCRB_;
		static GTCCRB_ GTCCRB;
		typedef rw32_t<base + 0x54>  GTCCRC_;
		static GTCCRC_ GTCCRC;
		typedef rw32_t<base + 0x58>  GTCCRE_;
		static GTCCRE_ GTCCRE;
		typedef rw32_t<base + 0x5C>  GTCCRD_;
		static GTCCRD_ GTCCRD;
		typedef rw32_t<base + 0x60>  GTCCRF_;
		static GTCCRF_ GTCCRF;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ周期設定レジスタ (GTPR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x64>  GTPR_;
		static GTPR_ GTPR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ周期設定バッファレジスタ (GTPBR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x68>  GTPBR_;
		static GTPBR_ GTPBR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマ周期設定ダブルバッファレジスタ (GTPDBR)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x6C>  GTPDBR_;
		static GTPDBR_ GTPDBR;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求タイミングレジスタ m (GTADTRm) (m = A, B)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x70>  GTADTRA_;
		static GTADTRA_ GTADTRA;
		typedef rw32_t<base + 0x7C>  GTADTRB_;
		static GTADTRB_ GTADTRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求タイミングバッファレジスタ m (GTADTBRm) (m = A, B)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x74>  GTADTBRA_;
		static GTADTBRA_ GTADTBRA;
		typedef rw32_t<base + 0x80>  GTADTBRB_;
		static GTADTBRB_ GTADTBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求タイミングダブルバッファレジスタ m (GTADTDBRm)(m = A, B)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x78>  GTADTDBRA_;
		static GTADTDBRA_ GTADTDBRA;
		typedef rw32_t<base + 0x84>  GTADTDBRB_;
		static GTADTDBRB_ GTADTDBRB;


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
		typedef gtdtcr_t<base + 0x88> GTDTCR_;
		static GTDTCR_ GTDTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマデッドタイム値レジスタ m (GTDVm) (m = U, D)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x8C>  GTDVU_;
		static GTDVU_ GTDVU;
		typedef rw32_t<base + 0x90>  GTDVD_;
		static GTDVD_ GTDVD;


		//-----------------------------------------------------------------//
		/*!
			@brief	汎用 PWM タイマデッドタイムバッファレジスタ m (GTDBm) (m = U, D)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x94>  GTDBU_;
		static GTDBU_ GTDBU;
		typedef rw32_t<base + 0x98>  GTDBD_;
		static GTDBD_ GTDBD;


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
		typedef gtsos_t<base + 0x9C> GTSOS_;
		static GTSOS_ GTSOS;


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
		typedef gtsotr_t<base + 0xA0> GTSOTR_;
		static GTSOTR_ GTSOTR;


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
		typedef gtadsmr_t<base + 0xA4> GTADSMR_;
		static GTADSMR_ GTADSMR;


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
		typedef gteitc_t<base + 0xA8> GTEITC_;
		static GTEITC_ GTEITC;


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
		typedef gteitli1_t<base + 0xAC> GTEITLI1_;
		static GTEITLI1_ GTEITLI1;


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
		typedef gteitli2_t<base + 0xB0> GTEITLI2_;
		static GTEITLI2_ GTEITLI2;


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
		typedef gteitlb_t<base + 0xB4> GTEITLB_;
		static GTEITLB_ GTEITLB;


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
		typedef gtsecsr_t<base + 0xD0> GTSECSR_;
		static GTSECSR_ GTSECSR;


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
		typedef gtsecr_t<base + 0xD4> GTSECR_;
		static GTSECR_ GTSECR;
	};
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTWP_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTWP; 
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSTR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSTR; 
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSTP_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSTP; 
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCLR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCLR; 
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSSR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSSR; 
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTPSR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTPSR; 
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCSR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCSR;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTUPSR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTUPSR; 
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDNSR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDNSR; 
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTICASR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTICASR; 
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTICBSR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTICBSR; 
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCR;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTUDDTYC_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTUDDTYC;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTIOR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTIOR;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTINTAD_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTINTAD;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTST_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTST;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTBER_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTBER;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTITC_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTITC;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCNT_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCNT;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRA_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRA;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRB_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRB;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRC_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRC;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRD_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRD;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRE_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRE;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRF_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTCCRF;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTPR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTPR;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTPBR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTPBR;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTPDBR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTPDBR;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTRA_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTRA;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTRB_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTRB;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTBRA_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTBRA;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTBRB_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTBRB;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTDBRA_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTDBRA;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTDBRB_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADTDBRB;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDTCR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDTCR;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDVU_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDVU;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDVD_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDVD;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDBU_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDBU;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDBD_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTDBD;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSOS_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSOS;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSOTR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSOTR;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADSMR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTADSMR;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTEITC_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTEITC;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTEITLI1_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTEITLI1;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTEITLI2_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTEITLI2;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTEITLB_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTEITLB;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSECSR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSECSR;
	template <uint32_t base, peripheral per,
		ICU::SELECTA gtcia, ICU::SELECTA gtcib, ICU::SELECTA gtcic,
		ICU::SELECTA gtcid, ICU::SELECTA gdte,  ICU::SELECTA gtcie,
		ICU::SELECTA gtcif, ICU::SELECTA gtciu, ICU::SELECTA gtciv>
	typename gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSECR_
		gptw_t<base, per, gtcia, gtcib, gtcic, gtcid, gdte, gtcie, gtcif, gtciu, gtciv>::GTSECR;

#if defined(SIG_RX72N) || defined(SIG_RX66T) || defined(SIG_RX72T) || defined(SIG_RX72M) 
	typedef gptw_t<0x000C'2000, peripheral::GPTW0,
		ICU::SELECTA::GTCIA0, ICU::SELECTA::GTCIB0, ICU::SELECTA::GTCIC0,
		ICU::SELECTA::GTCID0, ICU::SELECTA::GDTE0,  ICU::SELECTA::GTCIE0,
		ICU::SELECTA::GTCIF0, ICU::SELECTA::GTCIV0, ICU::SELECTA::GTCIU0> GPTW0;
	typedef gptw_t<0x000C'2100, peripheral::GPTW1,
		ICU::SELECTA::GTCIA1, ICU::SELECTA::GTCIB1, ICU::SELECTA::GTCIC1,
		ICU::SELECTA::GTCID1, ICU::SELECTA::GDTE1,  ICU::SELECTA::GTCIE1,
		ICU::SELECTA::GTCIF1, ICU::SELECTA::GTCIV1, ICU::SELECTA::GTCIU1> GPTW1;
	typedef gptw_t<0x000C'2200, peripheral::GPTW2,
		ICU::SELECTA::GTCIA2, ICU::SELECTA::GTCIB2, ICU::SELECTA::GTCIC2,
		ICU::SELECTA::GTCID2, ICU::SELECTA::GDTE2,  ICU::SELECTA::GTCIE2,
		ICU::SELECTA::GTCIF2, ICU::SELECTA::GTCIV2, ICU::SELECTA::GTCIU2> GPTW2;
	typedef gptw_t<0x000C'2300, peripheral::GPTW3,
		ICU::SELECTA::GTCIA3, ICU::SELECTA::GTCIB3, ICU::SELECTA::GTCIC3,
		ICU::SELECTA::GTCID3, ICU::SELECTA::GDTE3,  ICU::SELECTA::GTCIE3,
		ICU::SELECTA::GTCIF3, ICU::SELECTA::GTCIV3, ICU::SELECTA::GTCIU3> GPTW3;
#endif

#if defined(SIG_RX66T) || defined(SIG_RX72T) 
	typedef gptw_t<0x000C'2400, peripheral::GPTW4,
		ICU::SELECTA::GTCIA4, ICU::SELECTA::GTCIB4, ICU::SELECTA::GTCIC4,
		ICU::SELECTA::GTCID4, ICU::SELECTA::GDTE4,  ICU::SELECTA::GTCIE4,
		ICU::SELECTA::GTCIF4, ICU::SELECTA::GTCIV4, ICU::SELECTA::GTCIU4> GPTW4;
	typedef gptw_t<0x000C'2500, peripheral::GPTW5,
		ICU::SELECTA::GTCIA5, ICU::SELECTA::GTCIB5, ICU::SELECTA::GTCIC5,
		ICU::SELECTA::GTCID5, ICU::SELECTA::GDTE5,  ICU::SELECTA::GTCIE5,
		ICU::SELECTA::GTCIF5, ICU::SELECTA::GTCIV5, ICU::SELECTA::GTCIU5> GPTW5;
	typedef gptw_t<0x000C'2600, peripheral::GPTW6,
		ICU::SELECTA::GTCIA6, ICU::SELECTA::GTCIB6, ICU::SELECTA::GTCIC6,
		ICU::SELECTA::GTCID6, ICU::SELECTA::GDTE6,  ICU::SELECTA::GTCIE6,
		ICU::SELECTA::GTCIF6, ICU::SELECTA::GTCIV6, ICU::SELECTA::GTCIU6> GPTW6;
	typedef gptw_t<0x000C'2700, peripheral::GPTW7,
		ICU::SELECTA::GTCIA7, ICU::SELECTA::GTCIB7, ICU::SELECTA::GTCIC7,
		ICU::SELECTA::GTCID7, ICU::SELECTA::GDTE7,  ICU::SELECTA::GTCIE7,
		ICU::SELECTA::GTCIF7, ICU::SELECTA::GTCIV7, ICU::SELECTA::GTCIU7> GPTW7;
	typedef gptw_t<0x000C'2800, peripheral::GPTW8,
		ICU::SELECTA::GTCIA8, ICU::SELECTA::GTCIB8, ICU::SELECTA::GTCIC8,
		ICU::SELECTA::GTCID8, ICU::SELECTA::GDTE8,  ICU::SELECTA::GTCIE8,
		ICU::SELECTA::GTCIF8, ICU::SELECTA::GTCIV8, ICU::SELECTA::GTCIU8> GPTW8;
	typedef gptw_t<0x000C'2900, peripheral::GPTW9,
		ICU::SELECTA::GTCIA9, ICU::SELECTA::GTCIB9, ICU::SELECTA::GTCIC9,
		ICU::SELECTA::GTCID9, ICU::SELECTA::GDTE9,  ICU::SELECTA::GTCIE9,
		ICU::SELECTA::GTCIF9, ICU::SELECTA::GTCIV9, ICU::SELECTA::GTCIU9> GPTW9;
#endif
}
