#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600/RX700 バス定義
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
		typedef csncr_t<0x00083802> CS0CR_;
		static CS0CR_ CS0CR;
		typedef csncr_t<0x00083812> CS1CR_;
		static CS1CR_ CS1CR;
		typedef csncr_t<0x00083822> CS2CR_;
		static CS2CR_ CS2CR;
		typedef csncr_t<0x00083832> CS3CR_;
		static CS3CR_ CS3CR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csncr_t<0x00083842> CS4CR_;
		static CS4CR_ CS4CR;
		typedef csncr_t<0x00083852> CS5CR_;
		static CS5CR_ CS5CR;
		typedef csncr_t<0x00083862> CS6CR_;
		static CS6CR_ CS6CR;
		typedef csncr_t<0x00083872> CS7CR_;
		static CS7CR_ CS7CR;
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
		typedef csncr_t<0x0008380A> CS0REC_;
		static CS0REC_ CS0REC;
		typedef csncr_t<0x0008381A> CS1REC_;
		static CS1REC_ CS1REC;
		typedef csncr_t<0x0008382A> CS2REC_;
		static CS2REC_ CS2REC;
		typedef csncr_t<0x0008383A> CS3REC_;
		static CS3REC_ CS3REC;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csncr_t<0x0008384A> CS4REC_;
		static CS4REC_ CS4REC;
		typedef csncr_t<0x0008385A> CS5REC_;
		static CS5REC_ CS5REC;
		typedef csncr_t<0x0008386A> CS6REC_;
		static CS6REC_ CS6REC;
		typedef csncr_t<0x0008387A> CS7REC_;
		static CS7REC_ CS7REC;
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
		typedef csrecen_t<0x00083880> CSRECEN_;
		static CSRECEN_ CSRECEN;


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
		typedef csnmod_t<0x00083002> CS0MOD_;
		static CS0MOD_ CS0MOD;
		typedef csnmod_t<0x00083012> CS1MOD_;
		static CS1MOD_ CS1MOD;
		typedef csnmod_t<0x00083022> CS2MOD_;
		static CS2MOD_ CS2MOD;
		typedef csnmod_t<0x00083032> CS3MOD_;
		static CS3MOD_ CS3MOD;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnmod_t<0x00083042> CS4MOD_;
		static CS4MOD_ CS4MOD;
		typedef csnmod_t<0x00083052> CS5MOD_;
		static CS5MOD_ CS5MOD;
		typedef csnmod_t<0x00083062> CS6MOD_;
		static CS6MOD_ CS6MOD;
		typedef csnmod_t<0x00083072> CS7MOD_;
		static CS7MOD_ CS7MOD;
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
		typedef csnwcr1_t<0x00083004> CS0WCR1_;
		static CS0WCR1_ CS0WCR1;
		typedef csnwcr1_t<0x00083014> CS1WCR1_;
		static CS1WCR1_ CS1WCR1;
		typedef csnwcr1_t<0x00083024> CS2WCR1_;
		static CS2WCR1_ CS2WCR1;
		typedef csnwcr1_t<0x00083034> CS3WCR1_;
		static CS3WCR1_ CS3WCR1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnwcr1_t<0x00083044> CS4WCR1_;
		static CS4WCR1_ CS4WCR1;
		typedef csnwcr1_t<0x00083054> CS5WCR1_;
		static CS5WCR1_ CS5WCR1;
		typedef csnwcr1_t<0x00083064> CS6WCR1_;
		static CS6WCR1_ CS6WCR1;
		typedef csnwcr1_t<0x00083074> CS7WCR1_;
		static CS7WCR1_ CS7WCR1;
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
		typedef csnwcr2_t<0x00083008> CS0WCR2_;
		static CS0WCR2_ CS0WCR2;
		typedef csnwcr2_t<0x00083018> CS1WCR2_;
		static CS1WCR2_ CS1WCR2;
		typedef csnwcr2_t<0x00083028> CS2WCR2_;
		static CS2WCR2_ CS2WCR2;
		typedef csnwcr2_t<0x00083038> CS3WCR2_;
		static CS3WCR2_ CS3WCR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef csnwcr2_t<0x00083048> CS4WCR2_;
		static CS4WCR2_ CS4WCR2;
		typedef csnwcr2_t<0x00083058> CS5WCR2_;
		static CS5WCR2_ CS5WCR2;
		typedef csnwcr2_t<0x00083068> CS6WCR2_;
		static CS6WCR2_ CS6WCR2;
		typedef csnwcr2_t<0x00083078> CS7WCR2_;
		static CS7WCR2_ CS7WCR2;
#endif

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 空間クラス
			@param[in]	base	レジスタ・ベース・アドレス
			@param[in]	org		CS 空間開始アドレス
			@param[in]	end		CS 空間終了アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base, uint32_t org, uint32_t end>
		class cs_t {
		public:
			static const auto ORG = org;			///< CS 空間開始アドレス
			static const auto END = end;			///< CS 空間終了アドレス
			static const auto LEN = end - org + 1;	///< CS 空間長さ


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS 制御レジスタ
				@param[in]	base	レジスタ・ベース・アドレス
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static csncr_t<base + 0x0802>  CSCR;


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS リカバリサイクル設定レジスタ
				@param[in]	base	レジスタ・ベース・アドレス
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static csnrec_t<base + 0x080A> CSREC;			


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS セパレートバスリカバリサイクル挿入許可
				@param[in]	ena		不許可なら「false」
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static void enable_sep_CSREC(bool ena = true) {
				if(ena) CSRECEN |= 1 << ((base & 0x70) >> 4);
				else CSRECEN &= ~(1 << ((base & 0x70) >> 4));
			}


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS マルチプレックスバスリカバリサイクル挿入許可
				@param[in]	ena		不許可なら「false」
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static void enable_mux_CSREC(bool ena = true) {
				if(ena) CSRECEN |= 0x80 << ((base & 0x70) >> 4);
				else CSRECEN &= ~(0x80 << ((base & 0x70) >> 4));
			}


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS モードレジスタ
				@param[in]	base	レジスタ・ベース・アドレス
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static csnmod_t<base + 0x0002> CSMOD;


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS ウェイト制御レジスタ 1
				@param[in]	base	レジスタ・ベース・アドレス
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static csnwcr1_t<base + 0x0004> CSWCR1;


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS ウェイト制御レジスタ 2
				@param[in]	base	レジスタ・ベース・アドレス
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static csnwcr1_t<base + 0x0008> CSWCR2;
		};

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef cs_t<0x0008'3000, 0xFF00'0000, 0xFFFF'FFFF> CS0;
		typedef cs_t<0x0008'3010, 0x0700'0000, 0x07FF'FFFF> CS1;
		typedef cs_t<0x0008'3020, 0x0600'0000, 0x06FF'FFFF> CS2;
		typedef cs_t<0x0008'3030, 0x0500'0000, 0x05FF'FFFF> CS3;
#endif

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
		typedef cs_t<0x0008'3040, 0x0400'0000, 0x04FF'FFFF> CS4;
		typedef cs_t<0x0008'3050, 0x0300'0000, 0x03FF'FFFF> CS5;
		typedef cs_t<0x0008'3060, 0x0200'0000, 0x02FF'FFFF> CS6;
		typedef cs_t<0x0008'3070, 0x0100'0000, 0x01FF'FFFF> CS7;
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
		typedef sdccr_t<0x00083C00> SDCCR_;
		static SDCCR_ SDCCR;


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
		typedef sdcmod_t<0x00083C01> SDCMOD_;
		static SDCMOD_ SDCMOD;


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
		typedef sdamod_t<0x00083C02> SDAMOD_;
		static SDAMOD_ SDAMOD;


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
		typedef sdself_t<0x00083C10> SDSELF_;
		static SDSELF_ SDSELF;


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
		typedef sdrfcr_t<0x00083C14> SDRFCR_;
		static SDRFCR_ SDRFCR;


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
		typedef sdrfen_t<0x00083C16> SDRFEN_;
		static SDRFEN_ SDRFEN;


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
		typedef sdicr_t<0x00083C20> SDICR_;
		static SDICR_ SDICR;


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
		typedef sdir_t<0x00083C24> SDIR_;
		static SDIR_ SDIR;


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
		typedef sdadr_t<0x00083C40> SDADR_;
		static SDADR_ SDADR;


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
		typedef sdtr_t<0x00083C44> SDTR_;
		static SDTR_ SDTR;


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
		typedef sdmod_t<0x00083C48> SDMOD_;
		static SDMOD_ SDMOD;


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
		typedef sdsr_t<0x00083C50> SDSR_;
		static SDSR_ SDSR;
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
		typedef berclr_t<0x00081300> BERCLR_;
		static BERCLR_ BERCLR;


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
		typedef beren_t<0x00081304> BEREN_;
		static BEREN_ BEREN;


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
		typedef bersr1_t<0x00081308> BERSR1_;
		static BERSR1_ BERSR1;


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
		typedef bersr2_t<0x0008130A> BERSR2_;
		static BERSR2_ BERSR2;


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
		typedef buspri_t<0x00081310> BUSPRI_;
		static BUSPRI_ BUSPRI;


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
		typedef ebmapcr_t<0x000C5800> EBMAPCR_;
		static EBMAPCR_ EBMAPCR;
#endif
	};
	typedef bus_t<void> BUS;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS0CR_   bus_t<_>::CS0CR;
	template <class _> typename bus_t<_>::CS1CR_   bus_t<_>::CS1CR;
	template <class _> typename bus_t<_>::CS2CR_   bus_t<_>::CS2CR;
	template <class _> typename bus_t<_>::CS3CR_   bus_t<_>::CS3CR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS4CR_   bus_t<_>::CS4CR;
	template <class _> typename bus_t<_>::CS5CR_   bus_t<_>::CS5CR;
	template <class _> typename bus_t<_>::CS6CR_   bus_t<_>::CS6CR;
	template <class _> typename bus_t<_>::CS7CR_   bus_t<_>::CS7CR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS0REC_  bus_t<_>::CS0REC;
	template <class _> typename bus_t<_>::CS1REC_  bus_t<_>::CS1REC;
	template <class _> typename bus_t<_>::CS2REC_  bus_t<_>::CS2REC;
	template <class _> typename bus_t<_>::CS3REC_  bus_t<_>::CS3REC;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS4REC_  bus_t<_>::CS4REC;
	template <class _> typename bus_t<_>::CS5REC_  bus_t<_>::CS5REC;
	template <class _> typename bus_t<_>::CS6REC_  bus_t<_>::CS6REC;
	template <class _> typename bus_t<_>::CS7REC_  bus_t<_>::CS7REC;
#endif
	template <class _> typename bus_t<_>::CSRECEN_ bus_t<_>::CSRECEN;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS0MOD_  bus_t<_>::CS0MOD;
	template <class _> typename bus_t<_>::CS1MOD_  bus_t<_>::CS1MOD;
	template <class _> typename bus_t<_>::CS2MOD_  bus_t<_>::CS2MOD;
	template <class _> typename bus_t<_>::CS3MOD_  bus_t<_>::CS3MOD;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS4MOD_  bus_t<_>::CS4MOD;
	template <class _> typename bus_t<_>::CS5MOD_  bus_t<_>::CS5MOD;
	template <class _> typename bus_t<_>::CS6MOD_  bus_t<_>::CS6MOD;
	template <class _> typename bus_t<_>::CS7MOD_  bus_t<_>::CS7MOD;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS0WCR1_ bus_t<_>::CS0WCR1;
	template <class _> typename bus_t<_>::CS1WCR1_ bus_t<_>::CS1WCR1;
	template <class _> typename bus_t<_>::CS2WCR1_ bus_t<_>::CS2WCR1;
	template <class _> typename bus_t<_>::CS3WCR1_ bus_t<_>::CS3WCR1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS4WCR1_ bus_t<_>::CS4WCR1;
	template <class _> typename bus_t<_>::CS5WCR1_ bus_t<_>::CS5WCR1;
	template <class _> typename bus_t<_>::CS6WCR1_ bus_t<_>::CS6WCR1;
	template <class _> typename bus_t<_>::CS7WCR1_ bus_t<_>::CS7WCR1;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS0WCR2_ bus_t<_>::CS0WCR2;
	template <class _> typename bus_t<_>::CS1WCR2_ bus_t<_>::CS1WCR2;
	template <class _> typename bus_t<_>::CS2WCR2_ bus_t<_>::CS2WCR2;
	template <class _> typename bus_t<_>::CS3WCR2_ bus_t<_>::CS3WCR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::CS4WCR2_ bus_t<_>::CS4WCR2;
	template <class _> typename bus_t<_>::CS5WCR2_ bus_t<_>::CS5WCR2;
	template <class _> typename bus_t<_>::CS6WCR2_ bus_t<_>::CS6WCR2;
	template <class _> typename bus_t<_>::CS7WCR2_ bus_t<_>::CS7WCR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	template <class _> typename bus_t<_>::SDCCR_   bus_t<_>::SDCCR;
	template <class _> typename bus_t<_>::SDCMOD_  bus_t<_>::SDCMOD;
	template <class _> typename bus_t<_>::SDAMOD_  bus_t<_>::SDAMOD;
	template <class _> typename bus_t<_>::SDSELF_  bus_t<_>::SDSELF;
	template <class _> typename bus_t<_>::SDRFCR_  bus_t<_>::SDRFCR;
	template <class _> typename bus_t<_>::SDRFEN_  bus_t<_>::SDRFEN;
	template <class _> typename bus_t<_>::SDICR_   bus_t<_>::SDICR;
	template <class _> typename bus_t<_>::SDIR_    bus_t<_>::SDIR;
	template <class _> typename bus_t<_>::SDADR_   bus_t<_>::SDADR;
	template <class _> typename bus_t<_>::SDTR_    bus_t<_>::SDTR;
	template <class _> typename bus_t<_>::SDMOD_   bus_t<_>::SDMOD;
	template <class _> typename bus_t<_>::SDSR_    bus_t<_>::SDSR;
#endif
	template <class _> typename bus_t<_>::BERCLR_  bus_t<_>::BERCLR;
	template <class _> typename bus_t<_>::BEREN_   bus_t<_>::BEREN;
	template <class _> typename bus_t<_>::BERSR1_  bus_t<_>::BERSR1;
	template <class _> typename bus_t<_>::BERSR2_  bus_t<_>::BERSR2;
	template <class _> typename bus_t<_>::BUSPRI_  bus_t<_>::BUSPRI;

#if defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N) || defined(SIG_RX66N)
	template <class _> typename bus_t<_>::EBMAPCR_ bus_t<_>::EBMAPCR;
#endif
}
