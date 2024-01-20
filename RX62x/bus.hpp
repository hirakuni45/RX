#pragma once
//=============================================================================//
/*!	@file
	@brief	RX621/RX62N バス定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
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
		static inline csncr_t<0x0008'3802> CS0CR;
		static inline csncr_t<0x0008'3812> CS1CR;
		static inline csncr_t<0x0008'3822> CS2CR;
		static inline csncr_t<0x0008'3832> CS3CR;
		static inline csncr_t<0x0008'3842> CS4CR;
		static inline csncr_t<0x0008'3852> CS5CR;
		static inline csncr_t<0x0008'3862> CS6CR;
		static inline csncr_t<0x0008'3872> CS7CR;


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
		static inline csncr_t<0x0008'380A> CS0REC;
		static inline csncr_t<0x0008'381A> CS1REC;
		static inline csncr_t<0x0008'382A> CS2REC;
		static inline csncr_t<0x0008'383A> CS3REC;
		static inline csncr_t<0x0008'384A> CS4REC;
		static inline csncr_t<0x0008'385A> CS5REC;
		static inline csncr_t<0x0008'386A> CS6REC;
		static inline csncr_t<0x0008'387A> CS7REC;


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
		static inline csnmod_t<0x0008'3002> CS0MOD;
		static inline csnmod_t<0x0008'3012> CS1MOD;
		static inline csnmod_t<0x0008'3022> CS2MOD;
		static inline csnmod_t<0x0008'3032> CS3MOD;
		static inline csnmod_t<0x0008'3042> CS4MOD;
		static inline csnmod_t<0x0008'3052> CS5MOD;
		static inline csnmod_t<0x0008'3062> CS6MOD;
		static inline csnmod_t<0x0008'3072> CS7MOD;


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
		static inline csnwcr1_t<0x0008'3004> CS0WCR1;
		static inline csnwcr1_t<0x0008'3014> CS1WCR1;
		static inline csnwcr1_t<0x0008'3024> CS2WCR1;
		static inline csnwcr1_t<0x0008'3034> CS3WCR1;
		static inline csnwcr1_t<0x0008'3044> CS4WCR1;
		static inline csnwcr1_t<0x0008'3054> CS5WCR1;
		static inline csnwcr1_t<0x0008'3064> CS6WCR1;
		static inline csnwcr1_t<0x0008'3074> CS7WCR1;


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
		static inline csnwcr2_t<0x0008'3008> CS0WCR2;
		static inline csnwcr2_t<0x0008'3018> CS1WCR2;
		static inline csnwcr2_t<0x0008'3028> CS2WCR2;
		static inline csnwcr2_t<0x0008'3038> CS3WCR2;
		static inline csnwcr2_t<0x0008'3048> CS4WCR2;
		static inline csnwcr2_t<0x0008'3058> CS5WCR2;
		static inline csnwcr2_t<0x0008'3068> CS6WCR2;
		static inline csnwcr2_t<0x0008'3078> CS7WCR2;


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
		static inline sdccr_t<0x0008'3C00> SDCCR;


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
		static inline sdcmod_t<0x0008'3C01> SDCMOD;


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
		static inline sdamod_t<0x0008'3C02> SDAMOD;


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
		static inline sdself_t<0x0008'3C10> SDSELF;


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
		static inline sdrfcr_t<0x0008'3C14> SDRFCR;


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
		static inline sdrfen_t<0x0008'3C16> SDRFEN;


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
		static inline sdicr_t<0x0008'3C20> SDICR;


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
		static inline sdir_t<0x0008'3C24> SDIR;


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
		static inline sdadr_t<0x0008'3C40> SDADR;


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
		static inline sdtr_t<0x0008'3C44> SDTR;


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
		static inline sdmod_t<0x0008'3C48> SDMOD;


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
		static inline sdsr_t<0x0008'3C50> SDSR;


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
		static inline berclr_t<0x0008'1300> BERCLR;


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
		static inline beren_t<0x0008'1304> BEREN;


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
		static inline bersr1_t<0x0008'1308> BERSR1;


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
		static inline bersr2_t<0x0008'130A> BERSR2;
	};
	typedef bus_t BUS;
}
