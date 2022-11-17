#pragma once
//=============================================================================//
/*!	@file
	@brief	RX63T バス定義
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
		typedef csncr_t<0x0008'3802> CS0CR_;
		static CS0CR_ CS0CR;
		typedef csncr_t<0x0008'3812> CS1CR_;
		static CS1CR_ CS1CR;
		typedef csncr_t<0x0008'3822> CS2CR_;
		static CS2CR_ CS2CR;
		typedef csncr_t<0x0008'3832> CS3CR_;
		static CS3CR_ CS3CR;


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

			bit_rw_t <io_, bitpos::B0>   RCVEN0;
			bit_rw_t <io_, bitpos::B1>   RCVEN1;
			bit_rw_t <io_, bitpos::B2>   RCVEN2;
			bit_rw_t <io_, bitpos::B3>   RCVEN3;
			bit_rw_t <io_, bitpos::B4>   RCVEN4;
			bit_rw_t <io_, bitpos::B5>   RCVEN5;
			bit_rw_t <io_, bitpos::B6>   RCVEN6;
			bit_rw_t <io_, bitpos::B7>   RCVEN7;
			bit_rw_t <io_, bitpos::B8>   RCVENM0;
			bit_rw_t <io_, bitpos::B9>   RCVENM1;
			bit_rw_t <io_, bitpos::B10>  RCVENM2;
			bit_rw_t <io_, bitpos::B11>  RCVENM3;
			bit_rw_t <io_, bitpos::B12>  RCVENM4;
			bit_rw_t <io_, bitpos::B13>  RCVENM5;
			bit_rw_t <io_, bitpos::B14>  RCVENM6;
			bit_rw_t <io_, bitpos::B15>  RCVENM7;
		};
		typedef csrecen_t<0x0008'3880> CSRECEN_;
		static CSRECEN_ CSRECEN;


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
		typedef csnwcr2_t<0x0008'3008> CS0WCR2_;
		static CS0WCR2_ CS0WCR2;
		typedef csnwcr2_t<0x0008'3018> CS1WCR2_;
		static CS1WCR2_ CS1WCR2;
		typedef csnwcr2_t<0x0008'3028> CS2WCR2_;
		static CS2WCR2_ CS2WCR2;
		typedef csnwcr2_t<0x0008'3038> CS3WCR2_;
		static CS3WCR2_ CS3WCR2;


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
			bits_rw_t<io_, bitpos::B12, 2>  BPEB;
		};
		typedef buspri_t<0x0008'1310> BUSPRI_;
		static BUSPRI_ BUSPRI;
	};
	template <class _> typename bus_t<_>::CS0CR_   bus_t<_>::CS0CR;
	template <class _> typename bus_t<_>::CS1CR_   bus_t<_>::CS1CR;
	template <class _> typename bus_t<_>::CS2CR_   bus_t<_>::CS2CR;
	template <class _> typename bus_t<_>::CS3CR_   bus_t<_>::CS3CR;
	template <class _> typename bus_t<_>::CS0REC_  bus_t<_>::CS0REC;
	template <class _> typename bus_t<_>::CS1REC_  bus_t<_>::CS1REC;
	template <class _> typename bus_t<_>::CS2REC_  bus_t<_>::CS2REC;
	template <class _> typename bus_t<_>::CS3REC_  bus_t<_>::CS3REC;
	template <class _> typename bus_t<_>::CSRECEN_  bus_t<_>::CSRECEN;
	template <class _> typename bus_t<_>::CS0MOD_  bus_t<_>::CS0MOD;
	template <class _> typename bus_t<_>::CS1MOD_  bus_t<_>::CS1MOD;
	template <class _> typename bus_t<_>::CS2MOD_  bus_t<_>::CS2MOD;
	template <class _> typename bus_t<_>::CS3MOD_  bus_t<_>::CS3MOD;
	template <class _> typename bus_t<_>::CS0WCR1_ bus_t<_>::CS0WCR1;
	template <class _> typename bus_t<_>::CS1WCR1_ bus_t<_>::CS1WCR1;
	template <class _> typename bus_t<_>::CS2WCR1_ bus_t<_>::CS2WCR1;
	template <class _> typename bus_t<_>::CS3WCR1_ bus_t<_>::CS3WCR1;
	template <class _> typename bus_t<_>::CS0WCR2_ bus_t<_>::CS0WCR2;
	template <class _> typename bus_t<_>::CS1WCR2_ bus_t<_>::CS1WCR2;
	template <class _> typename bus_t<_>::CS2WCR2_ bus_t<_>::CS2WCR2;
	template <class _> typename bus_t<_>::CS3WCR2_ bus_t<_>::CS3WCR2;
	template <class _> typename bus_t<_>::BERCLR_  bus_t<_>::BERCLR;
	template <class _> typename bus_t<_>::BEREN_   bus_t<_>::BEREN;
	template <class _> typename bus_t<_>::BERSR1_  bus_t<_>::BERSR1;
	template <class _> typename bus_t<_>::BERSR2_  bus_t<_>::BERSR2;
	template <class _> typename bus_t<_>::BUSPRI_  bus_t<_>::BUSPRI;

	typedef bus_t<void> BUS;
}
