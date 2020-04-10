#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX65N/RX651/RX66T/RX72T/RX72N バス定義
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
		@brief  バス定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<typename _>
	struct bus_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn 制御レジスタ（CSnCR）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csncr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     EXENB;
			bits_rw_t<io_, bitpos::B4, 2>  BSIZE;
			bit_rw_t <io_, bitpos::B8>     EMODE;
			bit_rw_t <io_, bitpos::B12>    MPXEN;
		};
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csncr_t_<0x00083802> cs0cr_t;
		static cs0cr_t CS0CR;
		typedef csncr_t_<0x00083812> cs1cr_t;
		static cs1cr_t CS1CR;
		typedef csncr_t_<0x00083822> cs2cr_t;
		static cs2cr_t CS2CR;
		typedef csncr_t_<0x00083832> cs3cr_t;
		static cs3cr_t CS3CR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csncr_t_<0x00083842> cs4cr_t;
		static cs4cr_t CS4CR;
		typedef csncr_t_<0x00083852> cs5cr_t;
		static cs5cr_t CS5CR;
		typedef csncr_t_<0x00083862> cs6cr_t;
		static cs6cr_t CS6CR;
		typedef csncr_t_<0x00083872> cs7cr_t;
		static cs7cr_t CS7CR;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn リカバリサイクル設定レジスタ（CSnREC）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnrec_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> PRCV;
			bits_rw_t<io_, bitpos::B8, 4> WRCV;
		};
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csncr_t_<0x0008380A> cs0rec_t;
		static cs0rec_t CS0REC;
		typedef csncr_t_<0x0008381A> cs1rec_t;
		static cs1rec_t CS1REC;
		typedef csncr_t_<0x0008382A> cs2rec_t;
		static cs2rec_t CS2REC;
		typedef csncr_t_<0x0008383A> cs3rec_t;
		static cs3rec_t CS3REC;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csncr_t_<0x0008384A> cs4rec_t;
		static cs4rec_t CS4REC;
		typedef csncr_t_<0x0008385A> cs5rec_t;
		static cs5rec_t CS5REC;
		typedef csncr_t_<0x0008386A> cs6rec_t;
		static cs6rec_t CS6REC;
		typedef csncr_t_<0x0008387A> cs7rec_t;
		static cs7rec_t CS7REC;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS リカバリサイクル挿入許可レジスタ（CSRECEN）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csrecen_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> RCVEN0;
			bit_rw_t<io_, bitpos::B1> RCVEN1;
			bit_rw_t<io_, bitpos::B2> RCVEN2;
			bit_rw_t<io_, bitpos::B3> RCVEN3;
			bit_rw_t<io_, bitpos::B4> RCVEN4;
			bit_rw_t<io_, bitpos::B5> RCVEN5;
			bit_rw_t<io_, bitpos::B6> RCVEN6;
			bit_rw_t<io_, bitpos::B7> RCVEN7;

			bit_rw_t<io_, bitpos::B8>  RCVENM0;
			bit_rw_t<io_, bitpos::B9>  RCVENM1;
			bit_rw_t<io_, bitpos::B10> RCVENM2;
			bit_rw_t<io_, bitpos::B11> RCVENM3;
			bit_rw_t<io_, bitpos::B12> RCVENM4;
			bit_rw_t<io_, bitpos::B13> RCVENM5;
			bit_rw_t<io_, bitpos::B14> RCVENM6;
			bit_rw_t<io_, bitpos::B15> RCVENM7;
		};
		typedef csrecen_t_<0x00083880> csrecen_t;
		static csrecen_t CSRECEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn モードレジスタ（CSnMOD）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnmod_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  WRMOD;
			bit_rw_t<io_, bitpos::B3>  EWENB;
			bit_rw_t<io_, bitpos::B8>  PRENB;
			bit_rw_t<io_, bitpos::B9>  PWENB;
			bit_rw_t<io_, bitpos::B15> PRMOD;
		};
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnmod_t_<0x00083002> cs0mod_t;
		static cs0mod_t CS0MOD;
		typedef csnmod_t_<0x00083012> cs1mod_t;
		static cs1mod_t CS1MOD;
		typedef csnmod_t_<0x00083022> cs2mod_t;
		static cs2mod_t CS2MOD;
		typedef csnmod_t_<0x00083032> cs3mod_t;
		static cs3mod_t CS3MOD;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnmod_t_<0x00083042> cs4mod_t;
		static cs4mod_t CS4MOD;
		typedef csnmod_t_<0x00083052> cs5mod_t;
		static cs5mod_t CS5MOD;
		typedef csnmod_t_<0x00083062> cs6mod_t;
		static cs6mod_t CS6MOD;
		typedef csnmod_t_<0x00083072> cs7mod_t;
		static cs7mod_t CS7MOD;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn ウェイト制御レジスタ 1（CSnWCR1）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnwcr1_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  CSPWWAIT;
			bits_rw_t<io_, bitpos::B8, 3>  CSPRWAIT;
			bits_rw_t<io_, bitpos::B16, 5> CSWWAIT;
			bits_rw_t<io_, bitpos::B24, 5> CSRWWAIT;
		};
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnwcr1_t_<0x00083004> cs0wcr1_t;
		static cs0wcr1_t CS0WCR1;
		typedef csnwcr1_t_<0x00083014> cs1wcr1_t;
		static cs1wcr1_t CS1WCR1;
		typedef csnwcr1_t_<0x00083024> cs2wcr1_t;
		static cs2wcr1_t CS2WCR1;
		typedef csnwcr1_t_<0x00083034> cs3wcr1_t;
		static cs3wcr1_t CS3WCR1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnwcr1_t_<0x00083044> cs4wcr1_t;
		static cs4wcr1_t CS4WCR1;
		typedef csnwcr1_t_<0x00083054> cs5wcr1_t;
		static cs5wcr1_t CS5WCR1;
		typedef csnwcr1_t_<0x00083064> cs6wcr1_t;
		static cs6wcr1_t CS6WCR1;
		typedef csnwcr1_t_<0x00083074> cs7wcr1_t;
		static cs7wcr1_t CS7WCR1;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn ウェイト制御レジスタ 2（CSnWCR2）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnwcr2_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  3> CSROFF;
			bits_rw_t<io_, bitpos::B4,  3> CSWOFF;
			bits_rw_t<io_, bitpos::B8,  3> WDOFF;
			bits_rw_t<io_, bitpos::B12, 2> AWAIT;
			bits_rw_t<io_, bitpos::B16, 3> RDON;
			bits_rw_t<io_, bitpos::B20, 3> WRON;
			bits_rw_t<io_, bitpos::B24, 3> WDON;
			bits_rw_t<io_, bitpos::B28, 3> CSON;
		};
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnwcr2_t_<0x00083008> cs0wcr2_t;
		static cs0wcr2_t CS0WCR2;
		typedef csnwcr2_t_<0x00083018> cs1wcr2_t;
		static cs1wcr2_t CS1WCR2;
		typedef csnwcr2_t_<0x00083028> cs2wcr2_t;
		static cs2wcr2_t CS2WCR2;
		typedef csnwcr2_t_<0x00083038> cs3wcr2_t;
		static cs3wcr2_t CS3WCR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnwcr2_t_<0x00083048> cs4wcr2_t;
		static cs4wcr2_t CS4WCR2;
		typedef csnwcr2_t_<0x00083058> cs5wcr2_t;
		static cs5wcr2_t CS5WCR2;
		typedef csnwcr2_t_<0x00083068> cs6wcr2_t;
		static cs6wcr2_t CS6WCR2;
		typedef csnwcr2_t_<0x00083078> cs7wcr2_t;
		static cs7wcr2_t CS7WCR2;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDC 制御レジスタ（SDCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdccr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    EXENB;
			bits_rw_t<io_, bitpos::B4, 2> BSIZE;
		};
		typedef sdccr_t_<0x00083C00> sdccr_t;
		static sdccr_t SDCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDC モードレジスタ（SDCMOD）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdcmod_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> EMODE;
		};
		typedef sdcmod_t_<0x00083C01> sdcmod_t;
		static sdcmod_t SDCMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM アクセスモードレジスタ（SDAMOD）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdamod_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> BE;
		};
		typedef sdamod_t_<0x00083C02> sdamod_t;
		static sdamod_t SDAMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM セルフリフレッシュ制御レジスタ（SDSELF）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdself_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> SFEN;
		};
		typedef sdself_t_<0x00083C10> sdself_t;
		static sdself_t SDSELF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM リフレッシュ制御レジスタ（SDRFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdrfcr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0,  12> RFC;
			bits_rw_t <io_, bitpos::B12, 4>  REFW;
		};
		typedef sdrfcr_t_<0x00083C14> sdrfcr_t;
		static sdrfcr_t SDRFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM オートリフレッシュ制御レジスタ（SDRFEN）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdrfen_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> RFEN;
		};
		typedef sdrfen_t_<0x00083C16> sdrfen_t;
		static sdrfen_t SDRFEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM 初期化シーケンス制御レジスタ（SDICR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdicr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> INIRQ;
		};
		typedef sdicr_t_<0x00083C20> sdicr_t;
		static sdicr_t SDICR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM 初期化レジスタ（SDIR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdir_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 4> ARFI;
			bits_rw_t <io_, bitpos::B4, 4> ARFC;
			bits_rw_t <io_, bitpos::B8, 3> PRC;
		};
		typedef sdir_t_<0x00083C24> sdir_t;
		static sdir_t SDIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM アドレスレジスタ（SDADR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdadr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 2> MXC;
		};
		typedef sdadr_t_<0x00083C40> sdadr_t;
		static sdadr_t SDADR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM タイミングレジスタ（SDTR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdtr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  3> CL;
			bit_rw_t <io_, bitpos::B8>     WR;
			bits_rw_t<io_, bitpos::B9,  3> RP;
			bits_rw_t<io_, bitpos::B12, 2> RCD;
			bits_rw_t<io_, bitpos::B16, 3> RAS;
		};
		typedef sdtr_t_<0x00083C44> sdtr_t;
		static sdtr_t SDTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM モードレジスタ（SDMOD）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdmod_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 14> MR;
		};
		typedef sdmod_t_<0x00083C48> sdmod_t;
		static sdmod_t SDMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM ステータスレジスタ（SDSR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdsr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MRSST;
			bit_rw_t<io_, bitpos::B3> INIST;
			bit_rw_t<io_, bitpos::B4> SRFST;
		};
		typedef sdsr_t_<0x00083C50> sdsr_t;
		static sdsr_t SDSR;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラーステータスクリアレジスタ（BERCLR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct berclr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> STSCLR;
		};
		typedef berclr_t_<0x00081300> berclr_t;
		static berclr_t BERCLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラー監視許可レジスタ（BEREN）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct beren_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> IGAEN;
			bit_rw_t<io_, bitpos::B1> TOEN;
		};
		typedef beren_t_<0x00081304> beren_t;
		static beren_t BEREN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラーステータスレジスタ 1（BERSR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct bersr1_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    IA;
			bit_rw_t <io_, bitpos::B1>    TO;
			bits_rw_t<io_, bitpos::B4, 3> MST;
		};
		typedef bersr1_t_<0x00081308> bersr1_t;
		static bersr1_t BERSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラーステータスレジスタ 2（BERSR2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct bersr2_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B3, 13> ADDR;
		};
		typedef bersr2_t_<0x0008130A> bersr2_t;
		static bersr2_t BERSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスプライオリティ制御レジスタ（BUSPRI）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct buspri_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> BPRA;
			bits_rw_t<io_, bitpos::B2,  2> BPRO;
			bits_rw_t<io_, bitpos::B4,  2> BPIB;
			bits_rw_t<io_, bitpos::B6,  2> BPGB;
			bits_rw_t<io_, bitpos::B8,  2> BPHB;
			bits_rw_t<io_, bitpos::B10, 2> BPFB;
			bits_rw_t<io_, bitpos::B12, 2> BPEB;
		};
		typedef buspri_t_<0x00081310> buspri_t;
		static buspri_t BUSPRI;


#if defined(SIG_RX65N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  拡張バスマスタ優先度制御レジスタ (EBMAPCR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct ebmapcr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  3>  PR1SEL;
			bits_rw_t<io_, bitpos::B4,  3>  PR2SEL;
			bits_rw_t<io_, bitpos::B8,  3>  PR3SEL;
			bits_rw_t<io_, bitpos::B12, 3>  PR4SEL;
			bits_rw_t<io_, bitpos::B16, 3>  PR5SEL;

			bit_rw_t <io_, bitpos::B29>     RPSTOP;

			bit_rw_t <io_, bitpos::B31>     PRERR;
		};
		typedef ebmapcr_t_<0x000C5800> ebmapcr_t;
		static ebmapcr_t EBMAPCR;
#endif
	};
	typedef bus_t<void> BUS;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::cs0cr_t   bus_t<_>::CS0CR;
	template <typename _> typename bus_t<_>::cs1cr_t   bus_t<_>::CS1CR;
	template <typename _> typename bus_t<_>::cs2cr_t   bus_t<_>::CS2CR;
	template <typename _> typename bus_t<_>::cs3cr_t   bus_t<_>::CS3CR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::cs4cr_t   bus_t<_>::CS4CR;
	template <typename _> typename bus_t<_>::cs5cr_t   bus_t<_>::CS5CR;
	template <typename _> typename bus_t<_>::cs6cr_t   bus_t<_>::CS6CR;
	template <typename _> typename bus_t<_>::cs7cr_t   bus_t<_>::CS7CR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::cs0rec_t  bus_t<_>::CS0REC;
	template <typename _> typename bus_t<_>::cs1rec_t  bus_t<_>::CS1REC;
	template <typename _> typename bus_t<_>::cs2rec_t  bus_t<_>::CS2REC;
	template <typename _> typename bus_t<_>::cs3rec_t  bus_t<_>::CS3REC;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::cs4rec_t  bus_t<_>::CS4REC;
	template <typename _> typename bus_t<_>::cs5rec_t  bus_t<_>::CS5REC;
	template <typename _> typename bus_t<_>::cs6rec_t  bus_t<_>::CS6REC;
	template <typename _> typename bus_t<_>::cs7rec_t  bus_t<_>::CS7REC;
#endif
	template <typename _> typename bus_t<_>::csrecen_t bus_t<_>::CSRECEN;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::cs0mod_t  bus_t<_>::CS0MOD;
	template <typename _> typename bus_t<_>::cs1mod_t  bus_t<_>::CS1MOD;
	template <typename _> typename bus_t<_>::cs2mod_t  bus_t<_>::CS2MOD;
	template <typename _> typename bus_t<_>::cs3mod_t  bus_t<_>::CS3MOD;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::cs4mod_t  bus_t<_>::CS4MOD;
	template <typename _> typename bus_t<_>::cs5mod_t  bus_t<_>::CS5MOD;
	template <typename _> typename bus_t<_>::cs6mod_t  bus_t<_>::CS6MOD;
	template <typename _> typename bus_t<_>::cs7mod_t  bus_t<_>::CS7MOD;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::cs0wcr1_t bus_t<_>::CS0WCR1;
	template <typename _> typename bus_t<_>::cs1wcr1_t bus_t<_>::CS1WCR1;
	template <typename _> typename bus_t<_>::cs2wcr1_t bus_t<_>::CS2WCR1;
	template <typename _> typename bus_t<_>::cs3wcr1_t bus_t<_>::CS3WCR1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::cs4wcr1_t bus_t<_>::CS4WCR1;
	template <typename _> typename bus_t<_>::cs5wcr1_t bus_t<_>::CS5WCR1;
	template <typename _> typename bus_t<_>::cs6wcr1_t bus_t<_>::CS6WCR1;
	template <typename _> typename bus_t<_>::cs7wcr1_t bus_t<_>::CS7WCR1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::cs0wcr2_t bus_t<_>::CS0WCR2;
	template <typename _> typename bus_t<_>::cs1wcr2_t bus_t<_>::CS1WCR2;
	template <typename _> typename bus_t<_>::cs2wcr2_t bus_t<_>::CS2WCR2;
	template <typename _> typename bus_t<_>::cs3wcr2_t bus_t<_>::CS3WCR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::cs4wcr2_t bus_t<_>::CS4WCR2;
	template <typename _> typename bus_t<_>::cs5wcr2_t bus_t<_>::CS5WCR2;
	template <typename _> typename bus_t<_>::cs6wcr2_t bus_t<_>::CS6WCR2;
	template <typename _> typename bus_t<_>::cs7wcr2_t bus_t<_>::CS7WCR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <typename _> typename bus_t<_>::sdccr_t   bus_t<_>::SDCCR;
	template <typename _> typename bus_t<_>::sdcmod_t  bus_t<_>::SDCMOD;
	template <typename _> typename bus_t<_>::sdamod_t  bus_t<_>::SDAMOD;
	template <typename _> typename bus_t<_>::sdself_t  bus_t<_>::SDSELF;
	template <typename _> typename bus_t<_>::sdrfcr_t  bus_t<_>::SDRFCR;
	template <typename _> typename bus_t<_>::sdrfen_t  bus_t<_>::SDRFEN;
	template <typename _> typename bus_t<_>::sdicr_t   bus_t<_>::SDICR;
	template <typename _> typename bus_t<_>::sdir_t    bus_t<_>::SDIR;
	template <typename _> typename bus_t<_>::sdadr_t   bus_t<_>::SDADR;
	template <typename _> typename bus_t<_>::sdtr_t    bus_t<_>::SDTR;
	template <typename _> typename bus_t<_>::sdmod_t   bus_t<_>::SDMOD;
	template <typename _> typename bus_t<_>::sdsr_t    bus_t<_>::SDSR;
#endif
	template <typename _> typename bus_t<_>::berclr_t  bus_t<_>::BERCLR;
	template <typename _> typename bus_t<_>::beren_t   bus_t<_>::BEREN;
	template <typename _> typename bus_t<_>::bersr1_t  bus_t<_>::BERSR1;
	template <typename _> typename bus_t<_>::bersr2_t  bus_t<_>::BERSR2;
	template <typename _> typename bus_t<_>::buspri_t  bus_t<_>::BUSPRI;

#if defined(SIG_RX65N)
	template <typename _> typename bus_t<_>::ebmapcr_t bus_t<_>::EBMAPCR;
#endif
}
