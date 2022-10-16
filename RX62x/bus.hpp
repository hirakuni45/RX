#pragma once
//=============================================================================//
/*!	@file
	@brief	RX621/RX62N バス定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  バス定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		};
		typedef csncr_t<0x0008'3802> CS0CR_;
		static CS0CR_ CS0CR;
		typedef csncr_t<0x0008'3812> CS1CR_;
		static CS1CR_ CS1CR;
		typedef csncr_t<0x0008'3822> CS2CR_;
		static CS2CR_ CS2CR;
		typedef csncr_t<0x0008'3832> CS3CR_;
		static CS3CR_ CS3CR;
		typedef csncr_t<0x0008'3842> CS4CR_;
		static CS4CR_ CS4CR;
		typedef csncr_t<0x0008'3852> CS5CR_;
		static CS5CR_ CS5CR;
		typedef csncr_t<0x0008'3862> CS6CR_;
		static CS6CR_ CS6CR;
		typedef csncr_t<0x0008'3872> CS7CR_;
		static CS7CR_ CS7CR;


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
		typedef csncr_t<0x0008'380A> CS0REC_;
		static CS0REC_ CS0REC;
		typedef csncr_t<0x0008'381A> CS1REC_;
		static CS1REC_ CS1REC;
		typedef csncr_t<0x0008'382A> CS2REC_;
		static CS2REC_ CS2REC;
		typedef csncr_t<0x0008'383A> CS3REC_;
		static CS3REC_ CS3REC;
		typedef csncr_t<0x0008'384A> CS4REC_;
		static CS4REC_ CS4REC;
		typedef csncr_t<0x0008'385A> CS5REC_;
		static CS5REC_ CS5REC;
		typedef csncr_t<0x0008'386A> CS6REC_;
		static CS6REC_ CS6REC;
		typedef csncr_t<0x0008'387A> CS7REC_;
		static CS7REC_ CS7REC;


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
		typedef csnmod_t<0x0008'3002> CS0MOD_;
		static CS0MOD_ CS0MOD;
		typedef csnmod_t<0x0008'3012> CS1MOD_;
		static CS1MOD_ CS1MOD;
		typedef csnmod_t<0x0008'3022> CS2MOD_;
		static CS2MOD_ CS2MOD;
		typedef csnmod_t<0x0008'3032> CS3MOD_;
		static CS3MOD_ CS3MOD;
		typedef csnmod_t<0x0008'3042> CS4MOD_;
		static CS4MOD_ CS4MOD;
		typedef csnmod_t<0x0008'3052> CS5MOD_;
		static CS5MOD_ CS5MOD;
		typedef csnmod_t<0x0008'3062> CS6MOD_;
		static CS6MOD_ CS6MOD;
		typedef csnmod_t<0x0008'3072> CS7MOD_;
		static CS7MOD_ CS7MOD;


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
		typedef csnwcr1_t<0x0008'3004> CS0WCR1_;
		static CS0WCR1_ CS0WCR1;
		typedef csnwcr1_t<0x0008'3014> CS1WCR1_;
		static CS1WCR1_ CS1WCR1;
		typedef csnwcr1_t<0x0008'3024> CS2WCR1_;
		static CS2WCR1_ CS2WCR1;
		typedef csnwcr1_t<0x0008'3034> CS3WCR1_;
		static CS3WCR1_ CS3WCR1;
		typedef csnwcr1_t<0x0008'3044> CS4WCR1_;
		static CS4WCR1_ CS4WCR1;
		typedef csnwcr1_t<0x0008'3054> CS5WCR1_;
		static CS5WCR1_ CS5WCR1;
		typedef csnwcr1_t<0x0008'3064> CS6WCR1_;
		static CS6WCR1_ CS6WCR1;
		typedef csnwcr1_t<0x0008'3074> CS7WCR1_;
		static CS7WCR1_ CS7WCR1;


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

			bits_rw_t<io_, bitpos::B16, 3> RDON;

			bits_rw_t<io_, bitpos::B20, 3> WRON;

			bits_rw_t<io_, bitpos::B24, 3> WDON;

			bits_rw_t<io_, bitpos::B28, 3> CSON;
		};
		typedef csnwcr2_t<0x0008'3008> CS0WCR2_;
		static CS0WCR2_ CS0WCR2;
		typedef csnwcr2_t<0x0008'3018> CS1WCR2_;
		static CS1WCR2_ CS1WCR2;
		typedef csnwcr2_t<0x0008'3028> CS2WCR2_;
		static CS2WCR2_ CS2WCR2;
		typedef csnwcr2_t<0x0008'3038> CS3WCR2_;
		static CS3WCR2_ CS3WCR2;
		typedef csnwcr2_t<0x0008'3048> CS4WCR2_;
		static CS4WCR2_ CS4WCR2;
		typedef csnwcr2_t<0x0008'3058> CS5WCR2_;
		static CS5WCR2_ CS5WCR2;
		typedef csnwcr2_t<0x0008'3068> CS6WCR2_;
		static CS6WCR2_ CS6WCR2;
		typedef csnwcr2_t<0x0008'3078> CS7WCR2_;
		static CS7WCR2_ CS7WCR2;


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
		typedef sdccr_t<0x0008'3C00> SDCCR_;
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
		typedef sdcmod_t<0x0008'3C01> SDCMOD_;
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
		typedef sdamod_t<0x0008'3C02> SDAMOD_;
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
		typedef sdself_t<0x0008'3C10> SDSELF_;
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
		typedef sdrfcr_t<0x0008'3C14> SDRFCR_;
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
		typedef sdrfen_t<0x0008'3C16> SDRFEN_;
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
		typedef sdicr_t<0x0008'3C20> SDICR_;
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
		typedef sdir_t<0x0008'3C24> SDIR_;
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
		typedef sdadr_t<0x0008'3C40> SDADR_;
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
		typedef sdtr_t<0x0008'3C44> SDTR_;
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

			bits_rw_t<io_, bitpos::B0, 15> MR;
		};
		typedef sdmod_t<0x0008'3C48> SDMOD_;
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
		typedef sdsr_t<0x0008'3C50> SDSR_;
		static SDSR_ SDSR;


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
		typedef berclr_t<0x0008'1300> BERCLR_;
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
		typedef beren_t<0x0008'1304> BEREN_;
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
		typedef bersr1_t<0x0008'1308> BERSR1_;
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
		typedef bersr2_t<0x0008'130A> BERSR2_;
		static BERSR2_ BERSR2;
	};
	template <class _> typename bus_t<_>::CS0CR_   bus_t<_>::CS0CR;
	template <class _> typename bus_t<_>::CS1CR_   bus_t<_>::CS1CR;
	template <class _> typename bus_t<_>::CS2CR_   bus_t<_>::CS2CR;
	template <class _> typename bus_t<_>::CS3CR_   bus_t<_>::CS3CR;
	template <class _> typename bus_t<_>::CS4CR_   bus_t<_>::CS4CR;
	template <class _> typename bus_t<_>::CS5CR_   bus_t<_>::CS5CR;
	template <class _> typename bus_t<_>::CS6CR_   bus_t<_>::CS6CR;
	template <class _> typename bus_t<_>::CS7CR_   bus_t<_>::CS7CR;
	template <class _> typename bus_t<_>::CS0REC_  bus_t<_>::CS0REC;
	template <class _> typename bus_t<_>::CS1REC_  bus_t<_>::CS1REC;
	template <class _> typename bus_t<_>::CS2REC_  bus_t<_>::CS2REC;
	template <class _> typename bus_t<_>::CS3REC_  bus_t<_>::CS3REC;
	template <class _> typename bus_t<_>::CS4REC_  bus_t<_>::CS4REC;
	template <class _> typename bus_t<_>::CS5REC_  bus_t<_>::CS5REC;
	template <class _> typename bus_t<_>::CS6REC_  bus_t<_>::CS6REC;
	template <class _> typename bus_t<_>::CS7REC_  bus_t<_>::CS7REC;
	template <class _> typename bus_t<_>::CS0MOD_  bus_t<_>::CS0MOD;
	template <class _> typename bus_t<_>::CS1MOD_  bus_t<_>::CS1MOD;
	template <class _> typename bus_t<_>::CS2MOD_  bus_t<_>::CS2MOD;
	template <class _> typename bus_t<_>::CS3MOD_  bus_t<_>::CS3MOD;
	template <class _> typename bus_t<_>::CS4MOD_  bus_t<_>::CS4MOD;
	template <class _> typename bus_t<_>::CS5MOD_  bus_t<_>::CS5MOD;
	template <class _> typename bus_t<_>::CS6MOD_  bus_t<_>::CS6MOD;
	template <class _> typename bus_t<_>::CS7MOD_  bus_t<_>::CS7MOD;
	template <class _> typename bus_t<_>::CS0WCR1_ bus_t<_>::CS0WCR1;
	template <class _> typename bus_t<_>::CS1WCR1_ bus_t<_>::CS1WCR1;
	template <class _> typename bus_t<_>::CS2WCR1_ bus_t<_>::CS2WCR1;
	template <class _> typename bus_t<_>::CS3WCR1_ bus_t<_>::CS3WCR1;
	template <class _> typename bus_t<_>::CS4WCR1_ bus_t<_>::CS4WCR1;
	template <class _> typename bus_t<_>::CS5WCR1_ bus_t<_>::CS5WCR1;
	template <class _> typename bus_t<_>::CS6WCR1_ bus_t<_>::CS6WCR1;
	template <class _> typename bus_t<_>::CS7WCR1_ bus_t<_>::CS7WCR1;
	template <class _> typename bus_t<_>::CS0WCR2_ bus_t<_>::CS0WCR2;
	template <class _> typename bus_t<_>::CS1WCR2_ bus_t<_>::CS1WCR2;
	template <class _> typename bus_t<_>::CS2WCR2_ bus_t<_>::CS2WCR2;
	template <class _> typename bus_t<_>::CS3WCR2_ bus_t<_>::CS3WCR2;
	template <class _> typename bus_t<_>::CS4WCR2_ bus_t<_>::CS4WCR2;
	template <class _> typename bus_t<_>::CS5WCR2_ bus_t<_>::CS5WCR2;
	template <class _> typename bus_t<_>::CS6WCR2_ bus_t<_>::CS6WCR2;
	template <class _> typename bus_t<_>::CS7WCR2_ bus_t<_>::CS7WCR2;
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
	template <class _> typename bus_t<_>::BERCLR_  bus_t<_>::BERCLR;
	template <class _> typename bus_t<_>::BEREN_   bus_t<_>::BEREN;
	template <class _> typename bus_t<_>::BERSR1_  bus_t<_>::BERSR1;
	template <class _> typename bus_t<_>::BERSR2_  bus_t<_>::BERSR2;

	typedef bus_t<void> BUS;
}
