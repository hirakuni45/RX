#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX65N/RX651/RX66T バス定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
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
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
		static csncr_t<0x00083802> CS0CR;
		static csncr_t<0x00083812> CS1CR;
		static csncr_t<0x00083822> CS2CR;
		static csncr_t<0x00083832> CS3CR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) 
		static csncr_t<0x00083842> CS4CR;
		static csncr_t<0x00083852> CS5CR;
		static csncr_t<0x00083862> CS6CR;
		static csncr_t<0x00083872> CS7CR;
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
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
		static csncr_t<0x0008380A> CS0REC;
		static csncr_t<0x0008381A> CS1REC;
		static csncr_t<0x0008382A> CS2REC;
		static csncr_t<0x0008383A> CS3REC;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
		static csncr_t<0x0008384A> CS4REC;
		static csncr_t<0x0008385A> CS5REC;
		static csncr_t<0x0008386A> CS6REC;
		static csncr_t<0x0008387A> CS7REC;
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
		static csrecen_t<0x00083880> CSRECEN;


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
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
		static csnmod_t<0x00083002> CS0MOD;
		static csnmod_t<0x00083012> CS1MOD;
		static csnmod_t<0x00083022> CS2MOD;
		static csnmod_t<0x00083032> CS3MOD;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
		static csnmod_t<0x00083042> CS4MOD;
		static csnmod_t<0x00083052> CS5MOD;
		static csnmod_t<0x00083062> CS6MOD;
		static csnmod_t<0x00083072> CS7MOD;
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
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
		static csnwcr1_t<0x00083004> CS0WCR1;
		static csnwcr1_t<0x00083014> CS1WCR1;
		static csnwcr1_t<0x00083024> CS2WCR1;
		static csnwcr1_t<0x00083034> CS3WCR1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
		static csnwcr1_t<0x00083044> CS4WCR1;
		static csnwcr1_t<0x00083054> CS5WCR1;
		static csnwcr1_t<0x00083064> CS6WCR1;
		static csnwcr1_t<0x00083074> CS7WCR1;
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
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
		static csnwcr2_t<0x00083008> CS0WCR2;
		static csnwcr2_t<0x00083018> CS1WCR2;
		static csnwcr2_t<0x00083028> CS2WCR2;
		static csnwcr2_t<0x00083038> CS3WCR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
		static csnwcr2_t<0x00083048> CS4WCR2;
		static csnwcr2_t<0x00083058> CS5WCR2;
		static csnwcr2_t<0x00083068> CS6WCR2;
		static csnwcr2_t<0x00083078> CS7WCR2;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
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
		static sdccr_t<0x00083C00> SDCCR;


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
		static sdcmod_t<0x00083C01> SDCMOD;


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
		static sdamod_t<0x00083C02> SDAMOD;


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
		static sdself_t<0x00083C10> SDSELF;


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
		static sdrfcr_t<0x00083C14> SDRFCR;


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
		static sdrfen_t<0x00083C16> SDRFEN;


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
		static sdicr_t<0x00083C20> SDICR;


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
		static sdir_t<0x00083C24> SDIR;


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
		static sdadr_t<0x00083C40> SDADR;


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
		static sdtr_t<0x00083C44> SDTR;


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
		static sdmod_t<0x00083C48> SDMOD;


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
		static sdsr_t<0x00083C50> SDSR;
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
		static berclr_t<0x00081300> BERCLR;


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
		static beren_t<0x00081304> BEREN;


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
		static bersr1_t<0x00081308> BERSR1;


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
		static bersr2_t<0x0008130A> BERSR2;


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
		static buspri_t<0x00081310> BUSPRI;


#if defined(SIG_RX65N)
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

			bit_rw_t <io_, bitpos::B29>     RPSTOP;

			bit_rw_t <io_, bitpos::B31>     PRERR;
		};
		static ebmapcr_t<0x000C5800> EBMAPCR;
#endif
	};
	
	typedef bus_t BUS;
}
