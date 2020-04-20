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
	template<class _>
	struct bus_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn 制御レジスタ（CSnCR）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csncr_t : public rw16_t<base> {
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
		typedef csncr_t<0x00083802> CS0CR_t;
		static CS0CR_t CS0CR;
		typedef csncr_t<0x00083812> CS1CR_t;
		static CS1CR_t CS1CR;
		typedef csncr_t<0x00083822> CS2CR_t;
		static CS2CR_t CS2CR;
		typedef csncr_t<0x00083832> CS3CR_t;
		static CS3CR_t CS3CR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csncr_t<0x00083842> CS4CR_t;
		static CS4CR_t CS4CR;
		typedef csncr_t<0x00083852> CS5CR_t;
		static CS5CR_t CS5CR;
		typedef csncr_t<0x00083862> CS6CR_t;
		static CS6CR_t CS6CR;
		typedef csncr_t<0x00083872> CS7CR_t;
		static CS7CR_t CS7CR;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn リカバリサイクル設定レジスタ（CSnREC）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnrec_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> PRCV;
			bits_rw_t<io_, bitpos::B8, 4> WRCV;
		};
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csncr_t<0x0008380A> CS0REC_t;
		static CS0REC_t CS0REC;
		typedef csncr_t<0x0008381A> CS1REC_t;
		static CS1REC_t CS1REC;
		typedef csncr_t<0x0008382A> CS2REC_t;
		static CS2REC_t CS2REC;
		typedef csncr_t<0x0008383A> CS3REC_t;
		static CS3REC_t CS3REC;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csncr_t<0x0008384A> CS4REC_t;
		static CS4REC_t CS4REC;
		typedef csncr_t<0x0008385A> CS5REC_t;
		static CS5REC_t CS5REC;
		typedef csncr_t<0x0008386A> CS6REC_t;
		static CS6REC_t CS6REC;
		typedef csncr_t<0x0008387A> CS7REC_t;
		static CS7REC_t CS7REC;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS リカバリサイクル挿入許可レジスタ（CSRECEN）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csrecen_t : public rw16_t<base> {
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
		typedef csrecen_t<0x00083880> CSRECEN_t;
		static CSRECEN_t CSRECEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn モードレジスタ（CSnMOD）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnmod_t : public rw16_t<base> {
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
		typedef csnmod_t<0x00083002> CS0MOD_t;
		static CS0MOD_t CS0MOD;
		typedef csnmod_t<0x00083012> CS1MOD_t;
		static CS1MOD_t CS1MOD;
		typedef csnmod_t<0x00083022> CS2MOD_t;
		static CS2MOD_t CS2MOD;
		typedef csnmod_t<0x00083032> CS3MOD_t;
		static CS3MOD_t CS3MOD;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnmod_t<0x00083042> CS4MOD_t;
		static CS4MOD_t CS4MOD;
		typedef csnmod_t<0x00083052> CS5MOD_t;
		static CS5MOD_t CS5MOD;
		typedef csnmod_t<0x00083062> CS6MOD_t;
		static CS6MOD_t CS6MOD;
		typedef csnmod_t<0x00083072> CS7MOD_t;
		static CS7MOD_t CS7MOD;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn ウェイト制御レジスタ 1（CSnWCR1）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnwcr1_t : public rw32_t<base> {
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
		typedef csnwcr1_t<0x00083004> CS0WCR1_t;
		static CS0WCR1_t CS0WCR1;
		typedef csnwcr1_t<0x00083014> CS1WCR1_t;
		static CS1WCR1_t CS1WCR1;
		typedef csnwcr1_t<0x00083024> CS2WCR1_t;
		static CS2WCR1_t CS2WCR1;
		typedef csnwcr1_t<0x00083034> CS3WCR1_t;
		static CS3WCR1_t CS3WCR1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnwcr1_t<0x00083044> CS4WCR1_t;
		static CS4WCR1_t CS4WCR1;
		typedef csnwcr1_t<0x00083054> CS5WCR1_t;
		static CS5WCR1_t CS5WCR1;
		typedef csnwcr1_t<0x00083064> CS6WCR1_t;
		static CS6WCR1_t CS6WCR1;
		typedef csnwcr1_t<0x00083074> CS7WCR1_t;
		static CS7WCR1_t CS7WCR1;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn ウェイト制御レジスタ 2（CSnWCR2）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnwcr2_t : public rw32_t<base> {
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
		typedef csnwcr2_t<0x00083008> CS0WCR2_t;
		static CS0WCR2_t CS0WCR2;
		typedef csnwcr2_t<0x00083018> CS1WCR2_t;
		static CS1WCR2_t CS1WCR2;
		typedef csnwcr2_t<0x00083028> CS2WCR2_t;
		static CS2WCR2_t CS2WCR2;
		typedef csnwcr2_t<0x00083038> CS3WCR2_t;
		static CS3WCR2_t CS3WCR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnwcr2_t<0x00083048> CS4WCR2_t;
		static CS4WCR2_t CS4WCR2;
		typedef csnwcr2_t<0x00083058> CS5WCR2_t;
		static CS5WCR2_t CS5WCR2;
		typedef csnwcr2_t<0x00083068> CS6WCR2_t;
		static CS6WCR2_t CS6WCR2;
		typedef csnwcr2_t<0x00083078> CS7WCR2_t;
		static CS7WCR2_t CS7WCR2;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDC 制御レジスタ（SDCCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    EXENB;
			bits_rw_t<io_, bitpos::B4, 2> BSIZE;
		};
		typedef sdccr_t<0x00083C00> SDCCR_t;
		static SDCCR_t SDCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDC モードレジスタ（SDCMOD）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdcmod_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> EMODE;
		};
		typedef sdcmod_t<0x00083C01> SDCMOD_t;
		static SDCMOD_t SDCMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM アクセスモードレジスタ（SDAMOD）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdamod_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> BE;
		};
		typedef sdamod_t<0x00083C02> SDAMOD_t;
		static SDAMOD_t SDAMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM セルフリフレッシュ制御レジスタ（SDSELF）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdself_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> SFEN;
		};
		typedef sdself_t<0x00083C10> SDSELF_t;
		static SDSELF_t SDSELF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM リフレッシュ制御レジスタ（SDRFCR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdrfcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0,  12> RFC;
			bits_rw_t <io_, bitpos::B12, 4>  REFW;
		};
		typedef sdrfcr_t<0x00083C14> SDRFCR_t;
		static SDRFCR_t SDRFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM オートリフレッシュ制御レジスタ（SDRFEN）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdrfen_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> RFEN;
		};
		typedef sdrfen_t<0x00083C16> SDRFEN_t;
		static SDRFEN_t SDRFEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM 初期化シーケンス制御レジスタ（SDICR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdicr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> INIRQ;
		};
		typedef sdicr_t<0x00083C20> SDICR_t;
		static SDICR_t SDICR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM 初期化レジスタ（SDIR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdir_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 4> ARFI;
			bits_rw_t <io_, bitpos::B4, 4> ARFC;
			bits_rw_t <io_, bitpos::B8, 3> PRC;
		};
		typedef sdir_t<0x00083C24> SDIR_t;
		static SDIR_t SDIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM アドレスレジスタ（SDADR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdadr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 2> MXC;
		};
		typedef sdadr_t<0x00083C40> SDADR_t;
		static SDADR_t SDADR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM タイミングレジスタ（SDTR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdtr_t : public rw32_t<base> {
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
		typedef sdtr_t<0x00083C44> SDTR_t;
		static SDTR_t SDTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM モードレジスタ（SDMOD）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdmod_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 14> MR;
		};
		typedef sdmod_t<0x00083C48> SDMOD_t;
		static SDMOD_t SDMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM ステータスレジスタ（SDSR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MRSST;
			bit_rw_t<io_, bitpos::B3> INIST;
			bit_rw_t<io_, bitpos::B4> SRFST;
		};
		typedef sdsr_t<0x00083C50> SDSR_t;
		static SDSR_t SDSR;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラーステータスクリアレジスタ（BERCLR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct berclr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> STSCLR;
		};
		typedef berclr_t<0x00081300> BERCLR_t;
		static BERCLR_t BERCLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラー監視許可レジスタ（BEREN）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct beren_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> IGAEN;
			bit_rw_t<io_, bitpos::B1> TOEN;
		};
		typedef beren_t<0x00081304> BEREN_t;
		static BEREN_t BEREN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラーステータスレジスタ 1（BERSR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct bersr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    IA;
			bit_rw_t <io_, bitpos::B1>    TO;
			bits_rw_t<io_, bitpos::B4, 3> MST;
		};
		typedef bersr1_t<0x00081308> BERSR1_t;
		static BERSR1_t BERSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラーステータスレジスタ 2（BERSR2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct bersr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B3, 13> ADDR;
		};
		typedef bersr2_t<0x0008130A> BERSR2_t;
		static BERSR2_t BERSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスプライオリティ制御レジスタ（BUSPRI）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct buspri_t : public rw16_t<base> {
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
		typedef buspri_t<0x00081310> BUSPRI_t;
		static BUSPRI_t BUSPRI;


#if defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N) || defined(SIG_RX66N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  拡張バスマスタ優先度制御レジスタ (EBMAPCR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct ebmapcr_t : public rw32_t<base> {
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
#if defined(SIG_RX65N)
			bit_rw_t <io_, bitpos::B29>     RPSTOP;
#endif
			bit_rw_t <io_, bitpos::B31>     PRERR;
		};
		typedef ebmapcr_t<0x000C5800> EBMAPCR_t;
		static EBMAPCR_t EBMAPCR;
#endif
	};
	typedef bus_t<void> BUS;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS0CR_t   bus_t<_>::CS0CR;
	template <class _> typename bus_t<_>::CS1CR_t   bus_t<_>::CS1CR;
	template <class _> typename bus_t<_>::CS2CR_t   bus_t<_>::CS2CR;
	template <class _> typename bus_t<_>::CS3CR_t   bus_t<_>::CS3CR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS4CR_t   bus_t<_>::CS4CR;
	template <class _> typename bus_t<_>::CS5CR_t   bus_t<_>::CS5CR;
	template <class _> typename bus_t<_>::CS6CR_t   bus_t<_>::CS6CR;
	template <class _> typename bus_t<_>::CS7CR_t   bus_t<_>::CS7CR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS0REC_t  bus_t<_>::CS0REC;
	template <class _> typename bus_t<_>::CS1REC_t  bus_t<_>::CS1REC;
	template <class _> typename bus_t<_>::CS2REC_t  bus_t<_>::CS2REC;
	template <class _> typename bus_t<_>::CS3REC_t  bus_t<_>::CS3REC;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS4REC_t  bus_t<_>::CS4REC;
	template <class _> typename bus_t<_>::CS5REC_t  bus_t<_>::CS5REC;
	template <class _> typename bus_t<_>::CS6REC_t  bus_t<_>::CS6REC;
	template <class _> typename bus_t<_>::CS7REC_t  bus_t<_>::CS7REC;
#endif
	template <class _> typename bus_t<_>::CSRECEN_t bus_t<_>::CSRECEN;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS0MOD_t  bus_t<_>::CS0MOD;
	template <class _> typename bus_t<_>::CS1MOD_t  bus_t<_>::CS1MOD;
	template <class _> typename bus_t<_>::CS2MOD_t  bus_t<_>::CS2MOD;
	template <class _> typename bus_t<_>::CS3MOD_t  bus_t<_>::CS3MOD;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS4MOD_t  bus_t<_>::CS4MOD;
	template <class _> typename bus_t<_>::CS5MOD_t  bus_t<_>::CS5MOD;
	template <class _> typename bus_t<_>::CS6MOD_t  bus_t<_>::CS6MOD;
	template <class _> typename bus_t<_>::CS7MOD_t  bus_t<_>::CS7MOD;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS0WCR1_t bus_t<_>::CS0WCR1;
	template <class _> typename bus_t<_>::CS1WCR1_t bus_t<_>::CS1WCR1;
	template <class _> typename bus_t<_>::CS2WCR1_t bus_t<_>::CS2WCR1;
	template <class _> typename bus_t<_>::CS3WCR1_t bus_t<_>::CS3WCR1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS4WCR1_t bus_t<_>::CS4WCR1;
	template <class _> typename bus_t<_>::CS5WCR1_t bus_t<_>::CS5WCR1;
	template <class _> typename bus_t<_>::CS6WCR1_t bus_t<_>::CS6WCR1;
	template <class _> typename bus_t<_>::CS7WCR1_t bus_t<_>::CS7WCR1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS0WCR2_t bus_t<_>::CS0WCR2;
	template <class _> typename bus_t<_>::CS1WCR2_t bus_t<_>::CS1WCR2;
	template <class _> typename bus_t<_>::CS2WCR2_t bus_t<_>::CS2WCR2;
	template <class _> typename bus_t<_>::CS3WCR2_t bus_t<_>::CS3WCR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS4WCR2_t bus_t<_>::CS4WCR2;
	template <class _> typename bus_t<_>::CS5WCR2_t bus_t<_>::CS5WCR2;
	template <class _> typename bus_t<_>::CS6WCR2_t bus_t<_>::CS6WCR2;
	template <class _> typename bus_t<_>::CS7WCR2_t bus_t<_>::CS7WCR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::SDCCR_t   bus_t<_>::SDCCR;
	template <class _> typename bus_t<_>::SDCMOD_t  bus_t<_>::SDCMOD;
	template <class _> typename bus_t<_>::SDAMOD_t  bus_t<_>::SDAMOD;
	template <class _> typename bus_t<_>::SDSELF_t  bus_t<_>::SDSELF;
	template <class _> typename bus_t<_>::SDRFCR_t  bus_t<_>::SDRFCR;
	template <class _> typename bus_t<_>::SDRFEN_t  bus_t<_>::SDRFEN;
	template <class _> typename bus_t<_>::SDICR_t   bus_t<_>::SDICR;
	template <class _> typename bus_t<_>::SDIR_t    bus_t<_>::SDIR;
	template <class _> typename bus_t<_>::SDADR_t   bus_t<_>::SDADR;
	template <class _> typename bus_t<_>::SDTR_t    bus_t<_>::SDTR;
	template <class _> typename bus_t<_>::SDMOD_t   bus_t<_>::SDMOD;
	template <class _> typename bus_t<_>::SDSR_t    bus_t<_>::SDSR;
#endif
	template <class _> typename bus_t<_>::BERCLR_t  bus_t<_>::BERCLR;
	template <class _> typename bus_t<_>::BEREN_t   bus_t<_>::BEREN;
	template <class _> typename bus_t<_>::BERSR1_t  bus_t<_>::BERSR1;
	template <class _> typename bus_t<_>::BERSR2_t  bus_t<_>::BERSR2;
	template <class _> typename bus_t<_>::BUSPRI_t  bus_t<_>::BUSPRI;

#if defined(SIG_RX65N)
	template <class _> typename bus_t<_>::EBMAPCR_t bus_t<_>::EBMAPCR;
#endif
}
