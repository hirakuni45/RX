#pragma once
//=============================================================================//
/*!	@file
	@brief	RX210/RX230/RX231/RX23W バス定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
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
	struct BUS {

#if defined(SIG_RX210) || defined(SIG_RX230) || defined(SIG_RX231)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn 制御レジスタ（CSnCR）（n = 0 ～ 3）
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
		static inline csncr_t<0x0008'3802> CS0CR;
		static inline csncr_t<0x0008'3812> CS1CR;
		static inline csncr_t<0x0008'3822> CS2CR;
		static inline csncr_t<0x0008'3832> CS3CR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn リカバリサイクル設定レジスタ（CSnREC）（n = 0 ～ 3）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnrec_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  PRCV;

			bits_rw_t<io_, bitpos::B8, 4>  WRCV;
		};
		static inline csnrec_t<0x0008'380A> CS0REC;
		static inline csnrec_t<0x0008'381A> CS1REC;
		static inline csnrec_t<0x0008'382A> CS2REC;
		static inline csnrec_t<0x0008'383A> CS3REC;


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

			bit_rw_t <io_, bitpos::B0>     RCVEN0;
			bit_rw_t <io_, bitpos::B1>     RCVEN1;
			bit_rw_t <io_, bitpos::B2>     RCVEN2;
			bit_rw_t <io_, bitpos::B3>     RCVEN3;
			bit_rw_t <io_, bitpos::B4>     RCVEN4;
			bit_rw_t <io_, bitpos::B5>     RCVEN5;
			bit_rw_t <io_, bitpos::B6>     RCVEN6;
			bit_rw_t <io_, bitpos::B7>     RCVEN7;
			bit_rw_t <io_, bitpos::B8>     RCVENM0;
			bit_rw_t <io_, bitpos::B9>     RCVENM1;
			bit_rw_t <io_, bitpos::B10>    RCVENM2;
			bit_rw_t <io_, bitpos::B11>    RCVENM3;
			bit_rw_t <io_, bitpos::B12>    RCVENM4;
			bit_rw_t <io_, bitpos::B13>    RCVENM5;
			bit_rw_t <io_, bitpos::B14>    RCVENM6;
			bit_rw_t <io_, bitpos::B15>    RCVENM7;
		};
		static inline csrecen_t<0x0008'3880> CSRECEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn モードレジスタ（CSnMOD）（n = 0 ～ 3）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnmod_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     WRMOD;

			bit_rw_t <io_, bitpos::B3>     EWENB;

			bit_rw_t <io_, bitpos::B8>     PRENB;
			bit_rw_t <io_, bitpos::B9>     PWENB;

			bit_rw_t <io_, bitpos::B15>    PRMOD;
		};
		static inline csnmod_t<0x0008'3002> CS0MOD;
		static inline csnmod_t<0x0008'3012> CS1MOD;
		static inline csnmod_t<0x0008'3022> CS2MOD;
		static inline csnmod_t<0x0008'3032> CS3MOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn ウェイト制御レジスタ 1（CSnWCR1）（n = 0 ～ 3）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnwcr1_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  3> CSPWWAIT;

			bits_rw_t<io_, bitpos::B8,  3> CSPRWAIT;

			bits_rw_t<io_, bitpos::B16, 5> CSWWAIT;

			bits_rw_t<io_, bitpos::B24, 5> CSRWAIT;
		};
		static inline csnwcr1_t<0x0008'3004> CS0WCR1;
		static inline csnwcr1_t<0x0008'3014> CS1WCR1;
		static inline csnwcr1_t<0x0008'3024> CS2WCR1;
		static inline csnwcr1_t<0x0008'3034> CS3WCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn ウェイト制御レジスタ 2（CSnWCR2）（n = 0 ～ 3）
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
		static inline csnwcr2_t<0x0008'3008> CS0WCR2;
		static inline csnwcr2_t<0x0008'3018> CS1WCR2;
		static inline csnwcr2_t<0x0008'3028> CS2WCR2;
		static inline csnwcr2_t<0x0008'3038> CS3WCR2;
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
		struct bersr1_t : public ro8_t<base> {
			typedef ro8_t<base> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>    IA;
			bit_ro_t <in_, bitpos::B1>    TO;

			bits_ro_t<in_, bitpos::B4, 3> MST;
		};
		static inline bersr1_t<0x0008'1308> BERSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラーステータスレジスタ 2（BERSR2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct bersr2_t : public ro16_t<base> {
			typedef ro16_t<base> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B3, 13> ADDR;
		};
		static inline bersr2_t<0x0008'130A> BERSR2;


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

			bits_rw_t<io_, bitpos::B0,  2>  BPRA;
			bits_rw_t<io_, bitpos::B2,  2>  BPRO;
			bits_rw_t<io_, bitpos::B4,  2>  BPIB;
			bits_rw_t<io_, bitpos::B6,  2>  BPGB;
			bits_rw_t<io_, bitpos::B8,  2>  BPHB;
			bits_rw_t<io_, bitpos::B10, 2>  BPFB;
#if defined(SIG_RX210) || defined(SIG_RX230) || defined(SIG_RX231)
			bits_rw_t<io_, bitpos::B12, 2>  BPEB;
#endif
		};
		static inline buspri_t<0x0008'1310> BUSPRI;
	};
}
