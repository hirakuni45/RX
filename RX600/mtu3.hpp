#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・MTU3x 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU 全体定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct mtu_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> TPSC;
			bits_rw_t<io_, bitpos::B3, 2> CKEG;
			bits_rw_t<io_, bitpos::B5, 3> CCLR;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> TPSC2;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2x）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tcr2x_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> TPSC2;
			bits_rw_t<io_, bitpos::B3, 2> PCB;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1x）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmdr1x_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MD;
			bit_rw_t <io_, bitpos::B4>    BFA;
			bit_rw_t <io_, bitpos::B5>    BFB;
			bit_rw_t <io_, bitpos::B6>    BFE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1y）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmdr1y_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MD;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1z）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmdr1z_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> MD;
			bit_rw_t <io_, bitpos::B4>    BFA;
			bit_rw_t <io_, bitpos::B5>    BFB;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマモードレジスタ 2（TMDR2A, TMDR2B）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tmdr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  DRS;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 2（TMDR2A）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x000C1270> TMDR2A_;
		static  TMDR2A_ TMDR2A;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 2（TMDR2B）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t<0x000C1A70> TMDR2B_;
		static  TMDR2B_ TMDR2B;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tiorh_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> IOA;
			bits_rw_t<io_, bitpos::B4, 4> IOB;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tiorl_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> IOC;
			bits_rw_t<io_, bitpos::B4, 4> IOD;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIERx）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tierx_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIEA;
			bit_rw_t<io_, bitpos::B1> TGIEB;

			bit_rw_t<io_, bitpos::B4> TCIEV;
			bit_rw_t<io_, bitpos::B5> TCIEU;

			bit_rw_t<io_, bitpos::B7> TTGE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIERy）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tiery_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIEA;
			bit_rw_t<io_, bitpos::B1> TGIEB;
			bit_rw_t<io_, bitpos::B2> TGIEC;
			bit_rw_t<io_, bitpos::B3> TGIED;
			bit_rw_t<io_, bitpos::B4> TCIEV;

			bit_rw_t<io_, bitpos::B7> TTGE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIERz）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tierz_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIEA;
			bit_rw_t<io_, bitpos::B1> TGIEB;
			bit_rw_t<io_, bitpos::B2> TGIEC;
			bit_rw_t<io_, bitpos::B3> TGIED;
			bit_rw_t<io_, bitpos::B4> TCIEV;

			bit_rw_t<io_, bitpos::B6> TTGE2;
			bit_rw_t<io_, bitpos::B7> TTGE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIER8）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tier8_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIEA;
			bit_rw_t<io_, bitpos::B1> TGIEB;
			bit_rw_t<io_, bitpos::B2> TGIEC;
			bit_rw_t<io_, bitpos::B3> TGIED;
			bit_rw_t<io_, bitpos::B4> TCIEV;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマインタラプトイネーブルレジスタ（TIER2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tier2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIEE;
			bit_rw_t<io_, bitpos::B1> TGIEF;

			bit_rw_t<io_, bitpos::B7> TTGE2;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマステータスレジスタ（TSR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7> TCFD;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマバッファ動作転送モードレジスタ（TBTMx）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tbtmx_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TTSA;
			bit_rw_t<io_, bitpos::B1> TTSB;
			bit_rw_t<io_, bitpos::B2> TTSE;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマバッファ動作転送モードレジスタ（TBTMy）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tbtmy_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TTSA;
			bit_rw_t<io_, bitpos::B1> TTSB;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTRA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstra_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CST0;
			bit_rw_t<io_, bitpos::B1> CST1;
			bit_rw_t<io_, bitpos::B2> CST2;
			bit_rw_t<io_, bitpos::B3> CST8;
			bit_rw_t<io_, bitpos::B4> CST9;

			bit_rw_t<io_, bitpos::B6> CST3;
			bit_rw_t<io_, bitpos::B7> CST4;
		};
		typedef tstra_t<0x000C1280> TSTRA_;
		static  TSTRA_ TSTRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTRB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstrb_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> CST6;
			bit_rw_t<io_, bitpos::B7> CST7;
		};
		typedef tstrb_t<0x000C1A80> TSTRB_;
		static  TSTRB_ TSTRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CSW5;
			bit_rw_t<io_, bitpos::B1> CSV5;
			bit_rw_t<io_, bitpos::B2> CSU5;
		};
		typedef tstr_t<0x000C1CB4> TSTR_;
		static  TSTR_ TSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマシンクロレジスタ（TSYRA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tsyra_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SYNC0;
			bit_rw_t<io_, bitpos::B1> SYNC1;
			bit_rw_t<io_, bitpos::B2> SYNC2;
			bit_rw_t<io_, bitpos::B3> SYNC9;

			bit_rw_t<io_, bitpos::B6> SYNC3;
			bit_rw_t<io_, bitpos::B7> SYNC4;
		};
		typedef tsyra_t<0x000C1281> TSYRA_;
		static  TSYRA_ TSYRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマシンクロレジスタ（TSYRB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tsyrb_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> SYNC6;
			bit_rw_t<io_, bitpos::B7> SYNC7;
		};
		typedef tsyrb_t<0x000C1A81> TSYRB_;
		static  TSYRB_ TSYRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマカウンタシンクロスタートレジスタ（TCSYSTR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tcsystr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SCH7;
			bit_rw_t<io_, bitpos::B1> SCH6;
			bit_rw_t<io_, bitpos::B2> SCH9;
			bit_rw_t<io_, bitpos::B3> SCH4;
			bit_rw_t<io_, bitpos::B4> SCH3;
			bit_rw_t<io_, bitpos::B5> SCH2;
			bit_rw_t<io_, bitpos::B6> SCH1;
			bit_rw_t<io_, bitpos::B7> SCH0;
		};
		typedef tcsystr_t<0x000C1282> TCSYSTR_;
		static  TCSYSTR_ TCSYSTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマリードライトイネーブルレジスタ（TRWER）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct trwer_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> RWE;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマリードライトイネーブルレジスタ（TRWERA）
		*/
		//-----------------------------------------------------------------//
		typedef trwer_t<0x000C1284> TRWERA_;
		static  TRWERA_ TRWERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマリードライトイネーブルレジスタ（TRWERB）
		*/
		//-----------------------------------------------------------------//
		typedef trwer_t<0x000C1A84> TRWERB_;
		static  TRWERB_ TRWERB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットマスタイネーブルレジスタ（TOERA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct toera_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OE3B;
			bit_rw_t<io_, bitpos::B1> OE4A;
			bit_rw_t<io_, bitpos::B2> OE4B;
			bit_rw_t<io_, bitpos::B3> OE3D;
			bit_rw_t<io_, bitpos::B4> OE4C;
			bit_rw_t<io_, bitpos::B5> OE4D;
		};
		typedef toera_t<0x000C120A> TOERA_;
		static  TOERA_ TOERA; 


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットマスタイネーブルレジスタ（TOERB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct toerb_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OE6B;
			bit_rw_t<io_, bitpos::B1> OE7A;
			bit_rw_t<io_, bitpos::B2> OE7B;
			bit_rw_t<io_, bitpos::B3> OE6D;
			bit_rw_t<io_, bitpos::B4> OE7C;
			bit_rw_t<io_, bitpos::B5> OE7D;
		};
		typedef toerb_t<0x000C120A> TOERB_;
		static  TOERB_ TOERB; 


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 1（TOCR1A, TOCR1B）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tocr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OLSP;
			bit_rw_t<io_, bitpos::B1> OLSN;
			bit_rw_t<io_, bitpos::B2> TOCS;
			bit_rw_t<io_, bitpos::B3> TOCL;

			bit_rw_t<io_, bitpos::B6> PSYE;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 1（TOCR1A）
		*/
		//-----------------------------------------------------------------//
		typedef tocr1_t<0x000C120E> TOCR1A_;
		static  TOCR1A_ TOCR1A; 


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 1（TOCR1B）
		*/
		//-----------------------------------------------------------------//
		typedef tocr1_t<0x000C1A0E> TOCR1B_;
		static  TOCR1B_ TOCR1B; 


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 2（TOCR2A, TOCR2B）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tocr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    OLS1P;
			bit_rw_t <io_, bitpos::B1>    OLS1N;
			bit_rw_t <io_, bitpos::B2>    OLS2P;
			bit_rw_t <io_, bitpos::B3>    OLS2N;
			bit_rw_t <io_, bitpos::B4>    OLS3P;
			bit_rw_t <io_, bitpos::B5>    OLS3N;
			bits_rw_t<io_, bitpos::B6, 2> BF;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 2（TOCR2A）
		*/
		//-----------------------------------------------------------------//
		typedef tocr2_t<0x000C120F> TOCR2A_;
		static  TOCR2A_ TOCR2A; 


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 2（TOCR2B）
		*/
		//-----------------------------------------------------------------//
		typedef tocr2_t<0x000C1A0F> TOCR2B_;
		static  TOCR2B_ TOCR2B; 


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマアウトプットレベルバッファレジスタ（TOLBRA, TOLBRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tolbr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    OLS1P;
			bit_rw_t <io_, bitpos::B1>    OLS1N;
			bit_rw_t <io_, bitpos::B2>    OLS2P;
			bit_rw_t <io_, bitpos::B3>    OLS2N;
			bit_rw_t <io_, bitpos::B4>    OLS3P;
			bit_rw_t <io_, bitpos::B5>    OLS3N;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットレベルバッファレジスタ（TOLBRA）
		*/
		//-----------------------------------------------------------------//
		typedef tolbr_t<0x000C1236> TOLBRA_;
		static  TOLBRA_ TOLBRA; 


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットレベルバッファレジスタ（TOLBRB）
		*/
		//-----------------------------------------------------------------//
		typedef tolbr_t<0x000C1A36> TOLBRB_;
		static  TOLBRB_ TOLBRB; 


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマゲートコントロールレジスタ（TGCRA, TGCRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tgcra_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  UF;
			bit_rw_t <io_, bitpos::B1>  VF;
			bit_rw_t <io_, bitpos::B2>  WF;
			bit_rw_t <io_, bitpos::B3>  FB;
			bit_rw_t <io_, bitpos::B4>  P;
			bit_rw_t <io_, bitpos::B5>  N;
			bit_rw_t <io_, bitpos::B6>  BDC;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマゲートコントロールレジスタ（TGCRA）
		*/
		//-----------------------------------------------------------------//
		typedef tgcra_t<0x000C120D> TGCRA_;
		static  TGCRA_ TGCRA; 


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマゲートコントロールレジスタ（TGCRB）
		*/
		//-----------------------------------------------------------------//
		typedef tgcra_t<0x000C1A0D> TGCRB_;
		static  TGCRB_ TGCRB; 


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマサブカウンタ（TCNTSA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1220> TCNTSA_;
		static  TCNTSA_ TCNTSA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマサブカウンタ（TCNTSB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A20> TCNTSB_;
		static  TCNTSB_ TCNTSB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期データレジスタ（TCDRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1214> TCDRA_;
		static  TCDRA_ TCDRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期データレジスタ（TCDRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A14> TCDRB_;
		static  TCDRB_ TCDRB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期バッファレジスタ（TCBRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1222> TCBRA_;
		static  TCBRA_ TCBRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期バッファレジスタ（TCBRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A22> TCBRB_;
		static  TCBRB_ TCBRB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマデッドタイムデータレジスタ（TDDRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1216> TDDRA_;
		static  TDDRA_ TDDRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマデッドタイムデータレジスタ（TDDRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A16> TDDRB_;
		static  TDDRB_ TDDRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマデッドタイムイネーブルレジスタ（TDERA, TDERB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tder_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  TDER;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマデッドタイムイネーブルレジスタ（TDERA）
		*/
		//-----------------------------------------------------------------//
		typedef tder_t<0x000C1234> TDERA_;
		static  TDERA_ TDERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマデッドタイムイネーブルレジスタ（TDERB）
		*/
		//-----------------------------------------------------------------//
		typedef tder_t<0x000C1A34> TDERB_;
		static  TDERB_ TDERB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマバッファ転送設定レジスタ（TBTERA, TBTERB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tbter_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 2>  BTE;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマバッファ転送設定レジスタ（TBTERA）
		*/
		//-----------------------------------------------------------------//
		typedef tbter_t<0x000C1232> TBTERA_;
		static  TBTERA_ TBTERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマバッファ転送設定レジスタ（TBTERB）
		*/
		//-----------------------------------------------------------------//
		typedef tbter_t<0x000C1A32> TBTERB_;
		static  TBTERB_ TBTERB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ波形コントロールレジスタ（TWCRA, TWCRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct twcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  WRE;
			bit_rw_t <io_, bitpos::B1>  SCC;

			bit_rw_t <io_, bitpos::B7>  CCE;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ波形コントロールレジスタ（TWCRA）
		*/
		//-----------------------------------------------------------------//
		typedef twcr_t<0x000C1260> TWCRA_;
		static  TWCRA_ TWCRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ波形コントロールレジスタ（TWCRB）
		*/
		//-----------------------------------------------------------------//
		typedef twcr_t<0x000C1A60> TWCRB_;
		static  TWCRB_ TWCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ノイズフィルタコントロールレジスタ n（NFCRn）（n = 0 ～ 4, 6, 7, 9）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct nfcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     NFAEN;
			bit_rw_t <io_, bitpos::B1>     NFBEN;
			bit_rw_t <io_, bitpos::B2>     NFCEN;
			bit_rw_t <io_, bitpos::B3>     NFDEN;

			bits_rw_t<io_, bitpos::B4, 2>  NFCS;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ割り込み間引きモードレジスタ（TITMRA, TITMRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct titmr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  TITM;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引きモードレジスタ（TITMRA）
		*/
		//-----------------------------------------------------------------//
		typedef titmr_t<0x000C123A> TITMRA_;
		static  TITMRA_ TITMRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引きモードレジスタ（TITMRB）
		*/
		//-----------------------------------------------------------------//
		typedef titmr_t<0x000C1A3A> TITMRB_;
		static  TITMRB_ TITMRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 1（TITCR1A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr1a_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T4VCOR;
			bit_rw_t <io_, bitpos::B3>     T4VEN;
			bits_rw_t<io_, bitpos::B4, 3>  T3ACOR;
			bit_rw_t <io_, bitpos::B7>     T3AEN;
		};
		typedef titcr1a_t<0x000C1230> TITCR1A_;
		static  TITCR1A_ TITCR1A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 1（TITCR1B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr1b_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T7VCOR;
			bit_rw_t <io_, bitpos::B3>     T7VEN;
			bits_rw_t<io_, bitpos::B4, 3>  T6ACOR;
			bit_rw_t <io_, bitpos::B7>     T6AEN;
		};
		typedef titcr1b_t<0x000C1230> TITCR1B_;
		static  TITCR1B_ TITCR1B;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 1（TITCNT1A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt1a_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T4VCNT;
			bits_rw_t<io_, bitpos::B4, 3>  T3ACNT;
		};
		typedef titcnt1a_t<0x000C1231> TITCNT1A_;
		static  TITCNT1A_ TITCNT1A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 1（TITCNT1B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt1b_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T7VCNT;
			bits_rw_t<io_, bitpos::B4, 3>  T6ACNT;
		};
		typedef titcnt1b_t<0x000C1A31> TITCNT1B_;
		static  TITCNT1B_ TITCNT1B;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 2（TITCR2A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr2a_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG4COR;
		};
		typedef titcr2a_t<0x000C123B> TITCR2A_;
		static  TITCR2A_ TITCR2A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 2（TITCR2B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr2b_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG7COR;
		};
		typedef titcr2b_t<0x000C1A3B> TITCR2B_;
		static  TITCR2B_ TITCR2B;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 2（TITCNT2A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt2a_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG4CNT;
		};
		typedef titcnt2a_t<0x000C123C> TITCNT2A_;
		static  TITCNT2A_ TITCNT2A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 2（TITCNT2B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt2b_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG7CNT;
		};
		typedef titcnt2b_t<0x000C1A3C> TITCNT2B_;
		static  TITCNT2B_ TITCNT2B;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求選択レジスタ 0（TADSTRGR0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadstrgr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  TADSTRS0;
		};
		typedef tadstrgr0_t<0x000C1D30> TADSTRGR0_;
		static  TADSTRGR0_ TADSTRGR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求選択レジスタ 1（TADSTRGR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadstrgr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  TADSTRS1;
		};
		typedef tadstrgr1_t<0x000C1D32> TADSTRGR1_;
		static  TADSTRGR1_ TADSTRGR1;

	};
	typedef mtu_t<void> MTU;


	template <class _> typename mtu_t<_>::TMDR2A_ mtu_t<_>::TMDR2A;
	template <class _> typename mtu_t<_>::TMDR2B_ mtu_t<_>::TMDR2B;
	template <class _> typename mtu_t<_>::TSTRA_ mtu_t<_>::TSTRA;
	template <class _> typename mtu_t<_>::TSTRB_ mtu_t<_>::TSTRB;
	template <class _> typename mtu_t<_>::TSTR_ mtu_t<_>::TSTR;
	template <class _> typename mtu_t<_>::TSYRA_ mtu_t<_>::TSYRA;
	template <class _> typename mtu_t<_>::TSYRB_ mtu_t<_>::TSYRB;
	template <class _> typename mtu_t<_>::TCSYSTR_ mtu_t<_>::TCSYSTR;
	template <class _> typename mtu_t<_>::TRWERA_ mtu_t<_>::TRWERA;
	template <class _> typename mtu_t<_>::TRWERB_ mtu_t<_>::TRWERB;
	template <class _> typename mtu_t<_>::TOERA_ mtu_t<_>::TOERA; 
	template <class _> typename mtu_t<_>::TOERB_ mtu_t<_>::TOERB; 
	template <class _> typename mtu_t<_>::TOCR1A_ mtu_t<_>::TOCR1A; 
	template <class _> typename mtu_t<_>::TOCR1B_ mtu_t<_>::TOCR1B; 
	template <class _> typename mtu_t<_>::TOCR2A_ mtu_t<_>::TOCR2A; 
	template <class _> typename mtu_t<_>::TOCR2B_ mtu_t<_>::TOCR2B; 
	template <class _> typename mtu_t<_>::TOLBRA_ mtu_t<_>::TOLBRA; 
	template <class _> typename mtu_t<_>::TOLBRB_ mtu_t<_>::TOLBRB; 
	template <class _> typename mtu_t<_>::TGCRA_ mtu_t<_>::TGCRA; 
	template <class _> typename mtu_t<_>::TGCRB_ mtu_t<_>::TGCRB; 
	template <class _> typename mtu_t<_>::TCNTSA_ mtu_t<_>::TCNTSA;
	template <class _> typename mtu_t<_>::TCNTSB_ mtu_t<_>::TCNTSB;
	template <class _> typename mtu_t<_>::TCDRA_ mtu_t<_>::TCDRA;
	template <class _> typename mtu_t<_>::TCDRB_ mtu_t<_>::TCDRB;
	template <class _> typename mtu_t<_>::TCBRA_ mtu_t<_>::TCBRA;
	template <class _> typename mtu_t<_>::TCBRB_ mtu_t<_>::TCBRB;
	template <class _> typename mtu_t<_>::TDDRA_ mtu_t<_>::TDDRA;
	template <class _> typename mtu_t<_>::TDDRB_ mtu_t<_>::TDDRB;
	template <class _> typename mtu_t<_>::TDERA_ mtu_t<_>::TDERA;
	template <class _> typename mtu_t<_>::TDERB_ mtu_t<_>::TDERB;
	template <class _> typename mtu_t<_>::TBTERA_ mtu_t<_>::TBTERA;
	template <class _> typename mtu_t<_>::TBTERB_ mtu_t<_>::TBTERB;
	template <class _> typename mtu_t<_>::TWCRA_ mtu_t<_>::TWCRA;
	template <class _> typename mtu_t<_>::TWCRB_ mtu_t<_>::TWCRB;
	template <class _> typename mtu_t<_>::TITMRA_ mtu_t<_>::TITMRA;
	template <class _> typename mtu_t<_>::TITMRB_ mtu_t<_>::TITMRB;
	template <class _> typename mtu_t<_>::TITCR1A_ mtu_t<_>::TITCR1A;
	template <class _> typename mtu_t<_>::TITCR1B_ mtu_t<_>::TITCR1B;
	template <class _> typename mtu_t<_>::TITCNT1A_ mtu_t<_>::TITCNT1A;
	template <class _> typename mtu_t<_>::TITCNT1B_ mtu_t<_>::TITCNT1B;
	template <class _> typename mtu_t<_>::TITCR2A_ mtu_t<_>::TITCR2A;
	template <class _> typename mtu_t<_>::TITCR2B_ mtu_t<_>::TITCR2B;
	template <class _> typename mtu_t<_>::TITCNT2A_ mtu_t<_>::TITCNT2A;
	template <class _> typename mtu_t<_>::TITCNT2B_ mtu_t<_>::TITCNT2B;
	template <class _> typename mtu_t<_>::TADSTRGR0_ mtu_t<_>::TADSTRGR0;
	template <class _> typename mtu_t<_>::TADSTRGR1_ mtu_t<_>::TADSTRGR1;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU0 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu0_t : public MTU {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース(MTU0)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class clock_source : uint8_t {
			PCLKA      = 0b000000,	///< PCLKA / 1
			PCLKA_4    = 0b000001,	///< PCLKA / 4
			PCLKA_16   = 0b000010,	///< PCLKA / 16
			PCLKA_64   = 0b000011,	///< PCLKA / 64
			MTCLKA     = 0b000100,	///< MTCLKA
			MTCLKB     = 0b000101,	///< MTCLKB
			MTCLKC     = 0b000110,	///< MTCLKC
			MTCLKD     = 0b000111,	///< MTCLKD
			PCLKA_2    = 0b001000,	///< PCLKA / 2
			PCLKA_8    = 0b010000,	///< PCLKA / 8
			PCLKA_32   = 0b011000,	///< PCLKA / 32
			PCLKA_256  = 0b100000,	///< PCLKA / 256
			PCLKA_1024 = 0b101000,	///< PCLKA / 1024
			MTIOC1A    = 0b111000,	///< MTIOC1A
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU0)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,  ///< PB3 / MTIOC0A (LFQFP100:32)
			B,  ///< PB2 / MTIOC0B (LFQFP100:33)
			C,  ///< PB1 / MTIOC0C (LFQFP100:34)
			D,  ///< PB0 / MTIOC0D (LFQFP100:35)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要因(MTU0)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class interrupt : uint8_t {
			A,		///< TGIA
			B,		///< TGIB
			C,		///< TGIC
			D,		///< TGID
			OVF,	///< TCIV オーバーフロー
			E,		///< TGIE
			F,		///< TGIF
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU0)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST0 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(channel ch)
		{
			auto ret = port_map_mtu::channel::NONE;
			switch(ch) {
			case channel::A:
				ret = port_map_mtu::channel::A;
				break;
			case channel::B:
				ret = port_map_mtu::channel::B;
				break;
			case channel::C:
				ret = port_map_mtu::channel::C;
				break;
			case channel::D:
				ret = port_map_mtu::channel::D;
				break;
			default:
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1300> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t<0x000C1328> TCR2_;
		static  TCR2_ TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1x_t<0x000C1301> TMDR1_;
		static  TMDR1_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C1302> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C1303> TIORL_;
		static  TIORL_ TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	MTU0 タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(channel ch, uint8_t val)
			{
				switch(ch) {
				case channel::A:
					TIORH.IOA = val;
					break;
				case channel::B:
					TIORH.IOB = val;
					break;
				case channel::C:
					TIORL.IOC = val;
					break;
				case channel::D:
					TIORL.IOD = val;
					break;
				default:
					return false;
				}
				return true;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(channel ch)
			{
				switch(ch) {
				case channel::A:
					return TIORH.IOA();
					break;
				case channel::B:
					return TIORH.IOB();
					break;
				case channel::C:
					return TIORL.IOC();
					break;
				case channel::D:
					return TIORL.IOD();
					break;
				default:
					return 0x00;
				}
			}
		};
		typedef tior_t TIOR_;
		static  TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tiery_t<0x000C1304> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER2）
		*/
		//-----------------------------------------------------------------//
		typedef tier2_t<0x000C1324> TIER2_;
		static  TIER2_ TIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmx_t<0x000C1326> TBTM_;
		static  TBTM_ TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1306> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1308> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C130A> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C130C> TGRC_;
		static  TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C130E> TGRD_;
		static  TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1320> TGRE_;
		static  TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1322> TGRF_;
		static  TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t<0x000C1290> NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタクロック（NFCRC）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t<0x000C1299> NFCRC_;
		static  NFCRC_ NFCRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static INT get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return INT::TGIA0;
			case interrupt::B:   return INT::TGIB0;
			case interrupt::C:   return INT::TGIC0;
			case interrupt::D:   return INT::TGID0;
			case interrupt::OVF: return INT::TCIV0;
			case interrupt::E:   return INT::TGIE0;
			case interrupt::F:   return INT::TGIF0;
			}
			return INT::NONE;
		}
	};
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TCR_ mtu0_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TCR2_ mtu0_t<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TMDR1_ mtu0_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TIORH_ mtu0_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TIORL_ mtu0_t<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TIOR_ mtu0_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TIER_ mtu0_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TIER2_ mtu0_t<per, INT>::TIER2;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TBTM_ mtu0_t<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TCNT_ mtu0_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRA_ mtu0_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRB_ mtu0_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRC_ mtu0_t<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRD_ mtu0_t<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRE_ mtu0_t<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::TGRF_ mtu0_t<per, INT>::TGRF;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::NFCR_ mtu0_t<per, INT>::NFCR;
	template <peripheral per, typename INT> typename mtu0_t<per, INT>::NFCRC_ mtu0_t<per, INT>::NFCRC;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU1 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu1_t : public MTU {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース(MTU1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class clock_source : uint8_t {
			PCLKA      = 0b000000,	///< PCLKA / 1
			PCLKA_4    = 0b000001,	///< PCLKA / 4
			PCLKA_16   = 0b000010,	///< PCLKA / 16
			PCLKA_64   = 0b000011,	///< PCLKA / 64
			MTCLKA     = 0b000100,	///< MTCLKA
			MTCLKB     = 0b000101,	///< MTCLKB
			PCLKA_256  = 0b000110,	///< PCLKA / 256
			MTU2_TCNT  = 0b000111,	///< PCLKA / 256
			PCLKA_2    = 0b001000,	///< PCLKA / 2
			PCLKA_8    = 0b010000,	///< PCLKA / 8
			PCLKA_32   = 0b011000,	///< PCLKA / 32
			PCLKA_1024 = 0b100000,	///< PCLKA / 1024
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,  ///< MTIOC1A
			B,  ///< MTIOC1B
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要因(MTU1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class interrupt : uint8_t {
			A,		///< TGIA
			B,		///< TGIB
			OVF,	///< TCIV オーバーフロー
			UDF,	///< TCIU アンダーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU1)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST1 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(channel ch)
		{
			auto ret = port_map_mtu::channel::NONE;
			switch(ch) {
			case channel::A:
				ret = port_map_mtu::channel::A;
				break;
			case channel::B:
				ret = port_map_mtu::channel::B;
				break;
			default:
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1380> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2x_t<0x000C1394> TCR2_;
		static  TCR2_ TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1y_t<0x000C1381> TMDR1_;
		static  TMDR1_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 3（TMDR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tmdr3_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> LWA;
			bit_rw_t<io_, bitpos::B1> PHCKSEL;
		};
		typedef tmdr3_t<0x000C1391> TMDR3_;
		static  TMDR3_ TMDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C1382> TIORH_;
		static  TIORH_ TIORH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	MTU1 タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(channel ch, uint8_t val)
			{
				switch(ch) {
				case channel::A:
					TIORH.IOA = val;
					break;
				case channel::B:
					TIORH.IOB = val;
					break;
				default:
					return false;
				}
				return true;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(channel ch)
			{
				switch(ch) {
				case channel::A:
					return TIORH.IOA();
					break;
				case channel::B:
					return TIORH.IOB();
					break;
				default:
					return 0x00;
				}
			}
		};
		typedef tior_t TIOR_;
		static  TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tierx_t<0x000C1384> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x000C1385> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインプットキャプチャコントロールレジスタ（TICCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ticcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> I1AE;
			bit_rw_t<io_, bitpos::B1> I1BE;
			bit_rw_t<io_, bitpos::B2> I2AE;
			bit_rw_t<io_, bitpos::B3> I2BE;
		};
		typedef ticcr_t<0x000C1390> TICCR_;
		static  TICCR_ TICCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1386> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマロングワードカウンタ（TCNTLW）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C13A0> TCNTLW_;
		static  TCNTLW_ TCNTLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1388> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C138A> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマロングワードジェネラルレジスタ（TGRALW）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C13A4> TGRALW_;
		static  TGRALW_ TGRALW;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマロングワードジェネラルレジスタ（TGRBLW）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C13A8> TGRBLW_;
		static  TGRBLW_ TGRBLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t<0x000C1291> NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static INT get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return INT::TGIA1;
			case interrupt::B:   return INT::TGIB1;
			case interrupt::OVF: return INT::TCIV1;
			case interrupt::UDF: return INT::TCIU1;
			}
			return INT::NONE;
		}
	};
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TCR_ mtu1_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TCR2_ mtu1_t<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TMDR1_ mtu1_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TMDR3_ mtu1_t<per, INT>::TMDR3;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TIORH_ mtu1_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TIOR_ mtu1_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TIER_ mtu1_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TSR_ mtu1_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TICCR_ mtu1_t<per, INT>::TICCR;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TCNT_ mtu1_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TCNTLW_ mtu1_t<per, INT>::TCNTLW;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TGRA_ mtu1_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TGRB_ mtu1_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TGRALW_ mtu1_t<per, INT>::TGRALW;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::TGRBLW_ mtu1_t<per, INT>::TGRBLW;
	template <peripheral per, typename INT> typename mtu1_t<per, INT>::NFCR_ mtu1_t<per, INT>::NFCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU2 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu2_t : public MTU {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース(MTU2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class clock_source : uint8_t {
			PCLKA      = 0b000000,	///< PCLKA / 1
			PCLKA_4    = 0b000001,	///< PCLKA / 4
			PCLKA_16   = 0b000010,	///< PCLKA / 16
			PCLKA_64   = 0b000011,	///< PCLKA / 64
			MTCLKA     = 0b000100,	///< MTCLKA
			MTCLKB     = 0b000101,	///< MTCLKB
			MTCLKC     = 0b000110,	///< MTCLKC
			PCLKA_1024 = 0b000111,	///< PCLKA / 1024
			PCLKA_2    = 0b001000,	///< PCLKA / 2
			PCLKA_8    = 0b010000,	///< PCLKA / 8
			PCLKA_32   = 0b011000,	///< PCLKA / 32
			PCLKA_256  = 0b100000,	///< PCLKA / 256
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,  ///< PA3 / MTIOC2A (LFQFP100:38)
			B,  ///< PA2 / MTIOC2B (LFQFP100:39)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要因(MTU2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class interrupt : uint8_t {
			A,		///< TGIA
			B,		///< TGIB
			OVF,	///< TCIV オーバーフロー
			UDF,	///< TCIU アンダーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU2)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST2 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(channel ch)
		{
			auto ret = port_map_mtu::channel::NONE;
			switch(ch) {
			case channel::A:
				ret = port_map_mtu::channel::A;
				break;
			case channel::B:
				ret = port_map_mtu::channel::B;
				break;
			default:
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1400> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2x_t<0x000C140C> TCR2_;
		static  TCR2_ TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1y_t<0x000C1401> TMDR1_;
		static  TMDR1_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C1402> TIORH_;
		static  TIORH_ TIORH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	MTU2 タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(channel ch, uint8_t val)
			{
				switch(ch) {
				case channel::A:
					TIORH.IOA = val;
					break;
				case channel::B:
					TIORH.IOB = val;
					break;
				default:
					return false;
				}
				return true;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(channel ch)
			{
				switch(ch) {
				case channel::A:
					return TIORH.IOA();
					break;
				case channel::B:
					return TIORH.IOB();
					break;
				default:
					return 0x00;
				}
			}
		};
		typedef tior_t TIOR_;
		static  TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tierx_t<0x000C1404> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x000C1405> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1406> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1408> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C140A> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t<0x000C1292> NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static INT get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return INT::TGIA2;
			case interrupt::B:   return INT::TGIB2;
			case interrupt::OVF: return INT::TCIV2;
			case interrupt::UDF: return INT::TCIU2;
			}
			return INT::NONE;
		}
	};
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TCR_ mtu2_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TCR2_ mtu2_t<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TMDR1_ mtu2_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TIORH_ mtu2_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TIOR_ mtu2_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TIER_ mtu2_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TSR_ mtu2_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TCNT_ mtu2_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TGRA_ mtu2_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::TGRB_ mtu2_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu2_t<per, INT>::NFCR_ mtu2_t<per, INT>::NFCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU3 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu3_t : public MTU {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース(MTU3)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class clock_source : uint8_t {
			PCLKA      = 0b000000,	///< PCLKA / 1
			PCLKA_4    = 0b000001,	///< PCLKA / 4
			PCLKA_16   = 0b000010,	///< PCLKA / 16
			PCLKA_64   = 0b000011,	///< PCLKA / 64
			PCLKA_256  = 0b000100,	///< PCLKA / 256
			PCLKA_1024 = 0b000101,	///< PCLKA / 1024
			MTCLKA     = 0b000110,	///< MTCLKA
			MTCLKB     = 0b000111,	///< MTCLKB
			PCLKA_2    = 0b001000,	///< PCLKA / 2
			PCLKA_8    = 0b010000,	///< PCLKA / 8
			PCLKA_32   = 0b011000,	///< PCLKA / 32
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU3)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,  ///< P33 / MTIOC3A (LFQFP100:58)
			B,  ///< P71 / MTIOC3B (LFQFP100:56)
			C,  ///< P32 / MTIOC3C (LFQFP100:59)
			D,  ///< P74 / MTIOC3D (LFQFP100:53)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要因(MTU3)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class interrupt : uint8_t {
			A,		///< TGIA
			B,		///< TGIB
			C,		///< TGIC
			D,		///< TGID
			OVF,	///< TCIV オーバーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU3)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST3 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(channel ch)
		{
			auto ret = port_map_mtu::channel::NONE;
			switch(ch) {
			case channel::A:
				ret = port_map_mtu::channel::A;
				break;
			case channel::B:
				ret = port_map_mtu::channel::B;
				break;
			case channel::C:
				ret = port_map_mtu::channel::C;
				break;
			case channel::D:
				ret = port_map_mtu::channel::D;
				break;
			default:
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1200> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t<0x000C124C> TCR2_;
		static  TCR2_ TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1z_t<0x000C1202> TMDR1_;
		static  TMDR1_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C1204> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C1205> TIORL_;
		static  TIORL_ TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	MTU3 タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(channel ch, uint8_t val)
			{
				switch(ch) {
				case channel::A:
					TIORH.IOA = val;
					break;
				case channel::B:
					MTU::TOERA.OE3B = 1;
					TIORH.IOB = val;
					break;
				case channel::C:
					TIORL.IOC = val;
					break;
				case channel::D:
					MTU::TOERA.OE3D = 1;
					TIORL.IOD = val;
					break;
				default:
					return false;
				}
				return true;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(channel ch)
			{
				switch(ch) {
				case channel::A:
					return TIORH.IOA();
					break;
				case channel::B:
					return TIORH.IOB();
					break;
				case channel::C:
					return TIORL.IOC();
					break;
				case channel::D:
					return TIORL.IOD();
					break;
				default:
					return 0x00;
				}
			}
		};
		typedef tior_t TIOR_;
		static  TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tiery_t<0x000C1208> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x000C122C> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmy_t<0x000C1238> TBTM_;
		static  TBTM_ TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1210> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1218> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C121A> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1224> TGRC_;
		static  TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1226> TGRD_;
		static  TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1272> TGRE_;
		static  TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t<0x000C1293> NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  MTU3 割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static INT get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return INT::TGIA3;
			case interrupt::B:   return INT::TGIB3;
			case interrupt::C:   return INT::TGIC3;
			case interrupt::D:   return INT::TGID3;
			case interrupt::OVF: return INT::TCIV3;
			}
			return INT::NONE;
		}
	};
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TCR_ mtu3_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TCR2_ mtu3_t<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TMDR1_ mtu3_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TIORH_ mtu3_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TIORL_ mtu3_t<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TIOR_ mtu3_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TIER_ mtu3_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TSR_ mtu3_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TBTM_ mtu3_t<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TCNT_ mtu3_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TGRA_ mtu3_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TGRB_ mtu3_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TGRC_ mtu3_t<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TGRD_ mtu3_t<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::TGRE_ mtu3_t<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu3_t<per, INT>::NFCR_ mtu3_t<per, INT>::NFCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU4 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu4_t : public MTU {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース(MTU4)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class clock_source : uint8_t {
			PCLKA      = 0b000000,	///< PCLKA / 1
			PCLKA_4    = 0b000001,	///< PCLKA / 4
			PCLKA_16   = 0b000010,	///< PCLKA / 16
			PCLKA_64   = 0b000011,	///< PCLKA / 64
			PCLKA_256  = 0b000100,	///< PCLKA / 256
			PCLKA_1024 = 0b000101,	///< PCLKA / 1024
			MTCLKA     = 0b000110,	///< MTCLKA
			MTCLKB     = 0b000111,	///< MTCLKB
			PCLKA_2    = 0b001000,	///< PCLKA / 2
			PCLKA_8    = 0b010000,	///< PCLKA / 8
			PCLKA_32   = 0b011000,	///< PCLKA / 32
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU4)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,  ///< P72 / MTIOC4A (LFQFP100:55)
			B,  ///< P73 / MTIOC4B (LFQFP100:54)
			C,  ///< P75 / MTIOC4C (LFQFP100:52)
			D,  ///< P76 / MTIOC4D (LFQFP100:51)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要因(MTU4)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class interrupt : uint8_t {
			A,		///< TGIA
			B,		///< TGIB
			C,		///< TGIC
			D,		///< TGID
			OVF,	///< TCIV オーバーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU4)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST4 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(channel ch)
		{
			auto ret = port_map_mtu::channel::NONE;
			switch(ch) {
			case channel::A:
				ret = port_map_mtu::channel::A;
				break;
			case channel::B:
				ret = port_map_mtu::channel::B;
				break;
			case channel::C:
				ret = port_map_mtu::channel::C;
				break;
			case channel::D:
				ret = port_map_mtu::channel::D;
				break;
			default:
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1201> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t<0x000C124D> TCR2_;
		static  TCR2_ TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1z_t<0x000C1203> TMDR1_;
		static  TMDR1_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C1206> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C1207> TIORL_;
		static  TIORL_ TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	MTU4 タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(channel ch, uint8_t val)
			{
				switch(ch) {
				case channel::A:
					MTU::TOERA.OE4A = 1;
					TIORH.IOA = val;
					break;
				case channel::B:
					MTU::TOERA.OE4B = 1;
					TIORH.IOB = val;
					break;
				case channel::C:
					MTU::TOERA.OE4C = 1;
					TIORL.IOC = val;
					break;
				case channel::D:
					MTU::TOERA.OE4D = 1;
					TIORL.IOD = val;
					break;
				default:
					return false;
				}
				return true;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(channel ch)
			{
				switch(ch) {
				case channel::A:
					return TIORH.IOA();
					break;
				case channel::B:
					return TIORH.IOB();
					break;
				case channel::C:
					return TIORL.IOC();
					break;
				case channel::D:
					return TIORL.IOD();
					break;
				default:
					return 0x00;
				}
			}
		};
		typedef tior_t TIOR_;
		static  TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tierz_t<0x000C1209> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x000C122D> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmy_t<0x000C1239> TBTM_;
		static  TBTM_ TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1212> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C121C> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C121E> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1228> TGRC_;
		static  TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C122A> TGRD_;
		static  TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1274> TGRE_;
		static  TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1276> TGRF_;
		static  TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t<0x000C1294> NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ITB4VE;
			bit_rw_t<io_, bitpos::B1> ITB3AE;
			bit_rw_t<io_, bitpos::B2> ITA4VE;
			bit_rw_t<io_, bitpos::B3> ITA3AE;
			bit_rw_t<io_, bitpos::B4> DT4BE;
			bit_rw_t<io_, bitpos::B5> UT4BE;
			bit_rw_t<io_, bitpos::B6> DT4AE;
			bit_rw_t<io_, bitpos::B7> UT4AE;

			bits_rw_t<io_, bitpos::B14, 2> BF;
		};
		typedef tadcr_t<0x000C1240> TADCR_;
		static  TADCR_ TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1244> TADCORA_;
		static  TADCORA_ TADCORA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1246> TADCORB_;
		static  TADCORB_ TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1248> TADCOBRA_;
		static  TADCOBRA_ TADCOBRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C124A> TADCOBRB_;
		static  TADCOBRB_ TADCOBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  MTU4 割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static INT get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return INT::TGIA4;
			case interrupt::B:   return INT::TGIB4;
			case interrupt::C:   return INT::TGIC4;
			case interrupt::D:   return INT::TGID4;
			case interrupt::OVF: return INT::TCIV4;
			}
			return INT::NONE;
		}
	};
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TCR_ mtu4_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TCR2_ mtu4_t<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TMDR1_ mtu4_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TIORH_ mtu4_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TIORL_ mtu4_t<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TIOR_ mtu4_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TIER_ mtu4_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TSR_ mtu4_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TBTM_ mtu4_t<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TCNT_ mtu4_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGRA_ mtu4_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGRB_ mtu4_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGRC_ mtu4_t<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGRD_ mtu4_t<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGRE_ mtu4_t<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TGRF_ mtu4_t<per, INT>::TGRF;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::NFCR_ mtu4_t<per, INT>::NFCR;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TADCR_ mtu4_t<per, INT>::TADCR;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TADCORA_ mtu4_t<per, INT>::TADCORA;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TADCORB_ mtu4_t<per, INT>::TADCORB;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TADCOBRA_ mtu4_t<per, INT>::TADCOBRA;
	template <peripheral per, typename INT> typename mtu4_t<per, INT>::TADCOBRB_ mtu4_t<per, INT>::TADCOBRB;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU5 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu5_t {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース(MTU5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class clock_source : uint8_t {
			PCLKA      = 0b000000,	///< PCLKA / 1
			PCLKA_4    = 0b000001,	///< PCLKA / 4
			PCLKA_16   = 0b000010,	///< PCLKA / 16
			PCLKA_64   = 0b000011,	///< PCLKA / 64
			PCLKA_2    = 0b001000,	///< PCLKA / 2
			PCLKA_8    = 0b010000,	///< PCLKA / 8
			PCLKA_32   = 0b011000,	///< PCLKA / 32
			PCLKA_256  = 0b100000,	///< PCLKA / 256
			PCLKA_1024 = 0b101000,	///< PCLKA / 1024
			MTIOC1A    = 0b111000,	///< MTIOC1A
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			U,   ///< P24 / MTIOC5U (LFQFP100:64)
			V,   ///< P23 / MTIOC5V (LFQFP100:65)
			W,   ///< P22 / MTIOC5W (LFQFP100:66)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要因(MTU5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class interrupt : uint8_t {
			U,		///< TGIU
			V,		///< TGIV
			W,		///< TGIW
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(channel ch)
		{
			auto ret = port_map_mtu::channel::NONE;
			switch(ch) {
			case channel::U:
				ret = port_map_mtu::channel::U;
				break;
			case channel::V:
				ret = port_map_mtu::channel::V;
				break;
			case channel::W:
				ret = port_map_mtu::channel::W;
				break;
			default:
				break;
			}
			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ（TCR[UVW]）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> TPSC;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCRU）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1C84> TCRU_;
		static  TCRU_ TCRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCRV）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1C94> TCRV_;
		static  TCRV_ TCRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCRW）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1CA4> TCRW_;
		static  TCRW_ TCRW;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIOR[UVW]）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tior_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> IOC;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORU）
		*/
		//-----------------------------------------------------------------//
		typedef tior_t<0x000C1C86> TIORU_;
		static  TIORU_ TIORU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORV）
		*/
		//-----------------------------------------------------------------//
		typedef tior_t<0x000C1C96> TIORV_;
		static  TIORV_ TIORV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORW）
		*/
		//-----------------------------------------------------------------//
		typedef tior_t<0x000C1CA6> TIORW_;
		static  TIORW_ TIORW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコンペアマッチクリアレジスタ（TCNTCMPCLR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tcntcmpclr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPCLR5W;
			bit_rw_t<io_, bitpos::B1> CMPCLR5V;
			bit_rw_t<io_, bitpos::B2> CMPCLR5U;
		};
		typedef tcntcmpclr_t<0x000C1CB6> TCNTCMPCLR_;
		static  TCNTCMPCLR_ TCNTCMPCLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tier_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIE5W;
			bit_rw_t<io_, bitpos::B1> TGIE5V;
			bit_rw_t<io_, bitpos::B2> TGIE5U;
		};
		typedef tier_t<0x000C1CB2> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTU）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1C80> TCNTU_;
		static  TCNTU_ TCNTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTV）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1C90> TCNTV_;
		static  TCNTV_ TCNTV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1CA0> TCNTW_;
		static  TCNTW_ TCNTW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRU）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1C82> TGRU_;
		static  TGRU_ TGRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRV）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1C92> TGRV_;
		static  TGRV_ TGRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRW）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1CA2> TGRW_;
		static  TGRW_ TGRW;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CSTW5;
			bit_rw_t<io_, bitpos::B1> CSTV5;
			bit_rw_t<io_, bitpos::B2> CSTU5;
		};
		typedef tstr_t<0x000C1CB4> TSTR_;
		static  TSTR_ TSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ノイズフィルタコントロールレジスタ（NFCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct nfcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      NFUEN;
			bit_rw_t <io_, bitpos::B1>      NFVEN;
			bit_rw_t <io_, bitpos::B2>      NFWEN;

			bits_rw_t <io_, bitpos::B4, 2>  NFCS;
		};
		typedef nfcr_t<0x000C1A95> NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static INT get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::U:   return INT::TGIU5;
			case interrupt::V:   return INT::TGIV5;
			case interrupt::W:   return INT::TGIW5;
			}
			return INT::NONE;
		}
	};
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCRU_ mtu5_t<per, INT>::TCRU;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCRV_ mtu5_t<per, INT>::TCRV;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCRW_ mtu5_t<per, INT>::TCRW;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TIORU_ mtu5_t<per, INT>::TIORU;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TIORV_ mtu5_t<per, INT>::TIORV;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TIORW_ mtu5_t<per, INT>::TIORW;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCNTCMPCLR_ mtu5_t<per, INT>::TCNTCMPCLR;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TIER_ mtu5_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCNTU_ mtu5_t<per, INT>::TCNTU;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCNTV_ mtu5_t<per, INT>::TCNTV;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TCNTW_ mtu5_t<per, INT>::TCNTW;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TGRU_ mtu5_t<per, INT>::TGRU;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TGRV_ mtu5_t<per, INT>::TGRV;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TGRW_ mtu5_t<per, INT>::TGRW;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::TSTR_ mtu5_t<per, INT>::TSTR;
	template <peripheral per, typename INT> typename mtu5_t<per, INT>::NFCR_ mtu5_t<per, INT>::NFCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU6 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu6_t : public MTU {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース(MTU6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class clock_source : uint8_t {
			PCLKA      = 0b000000,	///< PCLKA / 1
			PCLKA_4    = 0b000001,	///< PCLKA / 4
			PCLKA_16   = 0b000010,	///< PCLKA / 16
			PCLKA_64   = 0b000011,	///< PCLKA / 64
			PCLKA_256  = 0b000100,	///< PCLKA / 256
			PCLKA_1024 = 0b000101,	///< PCLKA / 1024
			MTCLKA     = 0b000110,	///< MTCLKA
			MTCLKB     = 0b000111,	///< MTCLKB
			PCLKA_2    = 0b001000,	///< PCLKA / 2
			PCLKA_8    = 0b010000,	///< PCLKA / 8
			PCLKA_32   = 0b011000,	///< PCLKA / 32
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,  ///< PA1 / MTIOC6A (LFQFP100:40)
			B,  ///< P95 / MTIOC6B (LFQFP100:45)
			C,  ///< PA0 / MTIOC6C (LFQFP100:41)
			D,  ///< P92 / MTIOC6D (LFQFP100:48)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要因(MTU6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class interrupt : uint8_t {
			A,		///< TGIA
			B,		///< TGIB
			C,		///< TGIC
			D,		///< TGID
			OVF,	///< TCIV オーバーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU6)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRB.CST6 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(channel ch)
		{
			auto ret = port_map_mtu::channel::NONE;
			switch(ch) {
			case channel::A:
				ret = port_map_mtu::channel::A;
				break;
			case channel::B:
				ret = port_map_mtu::channel::B;
				break;
			case channel::C:
				ret = port_map_mtu::channel::C;
				break;
			case channel::D:
				ret = port_map_mtu::channel::D;
				break;
			default:
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1A00> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t<0x000C1A4C> TCR2_;
		static  TCR2_ TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1z_t<0x000C1A02> TMDR1_;
		static  TMDR1_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C1A04> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C1A05> TIORL_;
		static  TIORL_ TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(channel ch, uint8_t val)
			{
				switch(ch) {
				case channel::A:
					TIORH.IOA = val;
					break;
				case channel::B:
					TIORH.IOB = val;
					break;
				case channel::C:
					TIORL.IOC = val;
					break;
				case channel::D:
					TIORL.IOD = val;
					break;
				default:
					return false;
				}
				return true;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(channel ch)
			{
				switch(ch) {
				case channel::A:
					return TIORH.IOA();
					break;
				case channel::B:
					return TIORH.IOB();
					break;
				case channel::C:
					return TIORL.IOC();
					break;
				case channel::D:
					return TIORL.IOD();
					break;
				default:
					return 0x00;
				}
			}
		};
		typedef tior_t TIOR_;
		static  TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tiery_t<0x000C1A08> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x000C1A2C> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmy_t<0x000C1A38> TBTM_;
		static  TBTM_ TBTM;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマシンクロクリアレジスタ（TSYCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tsycr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CE2B;
			bit_rw_t<io_, bitpos::B1> CE2A;
			bit_rw_t<io_, bitpos::B2> CE1B;
			bit_rw_t<io_, bitpos::B3> CE1A;
			bit_rw_t<io_, bitpos::B4> CE0C;
			bit_rw_t<io_, bitpos::B5> CE0D;
			bit_rw_t<io_, bitpos::B6> CE0B;
			bit_rw_t<io_, bitpos::B7> CE0A;
		};
		typedef tsycr_t<0x000C1A50> TSYCR_;
		static  TSYCR_ TSYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A10> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A18> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A1A> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A24> TGRC_;
		static  TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A26> TGRD_;
		static  TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A72> TGRE_;
		static  TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t<0x000C1A93> NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  MTU6 割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static INT get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return INT::TGIA6;
			case interrupt::B:   return INT::TGIB6;
			case interrupt::C:   return INT::TGIC6;
			case interrupt::D:   return INT::TGID6;
			case interrupt::OVF: return INT::TCIV6;
			}
			return INT::NONE;
		}
	};
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TCR_ mtu6_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TCR2_ mtu6_t<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TMDR1_ mtu6_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TIORH_ mtu6_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TIORL_ mtu6_t<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TIOR_ mtu6_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TIER_ mtu6_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TSR_ mtu6_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TBTM_ mtu6_t<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TSYCR_ mtu6_t<per, INT>::TSYCR;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TCNT_ mtu6_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TGRA_ mtu6_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TGRB_ mtu6_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TGRC_ mtu6_t<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TGRD_ mtu6_t<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::TGRE_ mtu6_t<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu6_t<per, INT>::NFCR_ mtu6_t<per, INT>::NFCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU7 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu7_t : public MTU {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース(MTU7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class clock_source : uint8_t {
			PCLKA      = 0b000000,	///< PCLKA / 1
			PCLKA_4    = 0b000001,	///< PCLKA / 4
			PCLKA_16   = 0b000010,	///< PCLKA / 16
			PCLKA_64   = 0b000011,	///< PCLKA / 64
			PCLKA_256  = 0b000100,	///< PCLKA / 256
			PCLKA_1024 = 0b000101,	///< PCLKA / 1024
			MTCLKA     = 0b000110,	///< MTCLKA
			MTCLKB     = 0b000111,	///< MTCLKB
			PCLKA_2    = 0b001000,	///< PCLKA / 2
			PCLKA_8    = 0b010000,	///< PCLKA / 8
			PCLKA_32   = 0b011000,	///< PCLKA / 32
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,  ///< P94 / MTIOC7A (LFQFP100:46)
			B,  ///< P93 / MTIOC7B (LFQFP100:47)
			C,  ///< P91 / MTIOC7C (LFQFP100:49)
			D,  ///< P90 / MTIOC7D (LFQFP100:50)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要因(MTU7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class interrupt : uint8_t {
			A,		///< TGIA
			B,		///< TGIB
			C,		///< TGIC
			D,		///< TGID
			OVF,	///< TCIV オーバーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU7)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRB.CST7 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(channel ch)
		{
			auto ret = port_map_mtu::channel::NONE;
			switch(ch) {
			case channel::A:
				ret = port_map_mtu::channel::A;
				break;
			case channel::B:
				ret = port_map_mtu::channel::B;
				break;
			case channel::C:
				ret = port_map_mtu::channel::C;
				break;
			case channel::D:
				ret = port_map_mtu::channel::D;
				break;
			default:
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1A01> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t<0x000C1A4D> TCR2_;
		static  TCR2_ TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1z_t<0x000C1A03> TMDR1_;
		static  TMDR1_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C1A06> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C1A07> TIORL_;
		static  TIORL_ TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(channel ch, uint8_t val)
			{
				switch(ch) {
				case channel::A:
					TIORH.IOA = val;
					break;
				case channel::B:
					TIORH.IOB = val;
					break;
				case channel::C:
					TIORL.IOC = val;
					break;
				case channel::D:
					TIORL.IOD = val;
					break;
				default:
					return false;
				}
				return true;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(channel ch)
			{
				switch(ch) {
				case channel::A:
					return TIORH.IOA();
					break;
				case channel::B:
					return TIORH.IOB();
					break;
				case channel::C:
					return TIORL.IOC();
					break;
				case channel::D:
					return TIORL.IOD();
					break;
				default:
					return 0x00;
				}
			}
		};
		typedef tior_t TIOR_;
		static  TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tierz_t<0x000C1A09> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t<0x000C1A2D> TSR_;
		static  TSR_ TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmy_t<0x000C1A39> TBTM_;
		static  TBTM_ TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A12> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A1C> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A1E> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A28> TGRC_;
		static  TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A2A> TGRD_;
		static  TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A74> TGRE_;
		static  TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A76> TGRF_;
		static  TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t<0x000C1A94> NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ITB7VE;
			bit_rw_t<io_, bitpos::B1> ITB6AE;
			bit_rw_t<io_, bitpos::B2> ITA7VE;
			bit_rw_t<io_, bitpos::B3> ITA6AE;
			bit_rw_t<io_, bitpos::B4> DT7BE;
			bit_rw_t<io_, bitpos::B5> UT7BE;
			bit_rw_t<io_, bitpos::B6> DT7AE;
			bit_rw_t<io_, bitpos::B7> UT7AE;

			bits_rw_t<io_, bitpos::B14, 2> BF;
		};
		typedef tadcr_t<0x000C1A40> TADCR_;
		static  TADCR_ TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A44> TADCORA_;
		static  TADCORA_ TADCORA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A46> TADCORB_;
		static  TADCORB_ TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A48> TADCOBRA_;
		static  TADCOBRA_ TADCOBRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A4A> TADCOBRB_;
		static  TADCOBRB_ TADCOBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  MTU7 割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static INT get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return INT::TGIA7;
			case interrupt::B:   return INT::TGIB7;
			case interrupt::C:   return INT::TGIC7;
			case interrupt::D:   return INT::TGID7;
			case interrupt::OVF: return INT::TCIV7;
			}
			return INT::NONE;
		}
	};
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TCR_ mtu7_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TCR2_ mtu7_t<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TMDR1_ mtu7_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TIORH_ mtu7_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TIORL_ mtu7_t<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TIOR_ mtu7_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TIER_ mtu7_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TSR_ mtu7_t<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TBTM_ mtu7_t<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TCNT_ mtu7_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TGRA_ mtu7_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TGRB_ mtu7_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TGRC_ mtu7_t<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TGRD_ mtu7_t<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TGRE_ mtu7_t<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TGRF_ mtu7_t<per, INT>::TGRF;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::NFCR_ mtu7_t<per, INT>::NFCR;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TADCR_ mtu7_t<per, INT>::TADCR;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TADCORA_ mtu7_t<per, INT>::TADCORA;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TADCORB_ mtu7_t<per, INT>::TADCORB;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TADCOBRA_ mtu7_t<per, INT>::TADCOBRA;
	template <peripheral per, typename INT> typename mtu7_t<per, INT>::TADCOBRB_ mtu7_t<per, INT>::TADCOBRB;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU8 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu8_t : public MTU {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース(MTU8)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class clock_source : uint8_t {
			PCLKA      = 0b000000,	///< PCLKA / 1
			PCLKA_4    = 0b000001,	///< PCLKA / 4
			PCLKA_16   = 0b000010,	///< PCLKA / 16
			PCLKA_64   = 0b000011,	///< PCLKA / 64
			PCLKA_256  = 0b000100,	///< PCLKA / 256
			PCLKA_1024 = 0b000101,	///< PCLKA / 1024
			MTCLKA     = 0b000110,	///< MTCLKA
			MTCLKB     = 0b000111,	///< MTCLKB
			PCLKA_2    = 0b001000,	///< PCLKA / 2
			PCLKA_8    = 0b010000,	///< PCLKA / 8
			PCLKA_32   = 0b011000,	///< PCLKA / 32
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,  ///< P94 / MTIOC7A (LFQFP100:46)
			B,  ///< P93 / MTIOC7B (LFQFP100:47)
			C,  ///< P91 / MTIOC7C (LFQFP100:49)
			D,  ///< P90 / MTIOC7D (LFQFP100:50)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要因(MTU7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class interrupt : uint8_t {
			A,		///< TGIA
			B,		///< TGIB
			C,		///< TGIC
			D,		///< TGID
			OVF,	///< TCIV オーバーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU7)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST8 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(channel ch)
		{
			auto ret = port_map_mtu::channel::NONE;
			switch(ch) {
			case channel::A:
				ret = port_map_mtu::channel::A;
				break;
			case channel::B:
				ret = port_map_mtu::channel::B;
				break;
			case channel::C:
				ret = port_map_mtu::channel::C;
				break;
			case channel::D:
				ret = port_map_mtu::channel::D;
				break;
			default:
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1600> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t<0x000C1606> TCR2_;
		static  TCR2_ TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1z_t<0x000C1601> TMDR1_;
		static  TMDR1_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C1602> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C1603> TIORL_;
		static  TIORL_ TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(channel ch, uint8_t val)
			{
				switch(ch) {
				case channel::A:
					TIORH.IOA = val;
					break;
				case channel::B:
					TIORH.IOB = val;
					break;
				case channel::C:
					TIORL.IOC = val;
					break;
				case channel::D:
					TIORL.IOD = val;
					break;
				default:
					return false;
				}
				return true;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(channel ch)
			{
				switch(ch) {
				case channel::A:
					return TIORH.IOA();
					break;
				case channel::B:
					return TIORH.IOB();
					break;
				case channel::C:
					return TIORL.IOC();
					break;
				case channel::D:
					return TIORL.IOD();
					break;
				default:
					return 0x00;
				}
			}
		};
		typedef tior_t TIOR_;
		static  TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tier8_t<0x000C1604> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C1608> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C160C> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1610> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1614> TGRC_;
		static  TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1618> TGRD_;
		static  TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t<0x000C1298> NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  MTU8 割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static INT get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return INT::TGIA8;
			case interrupt::B:   return INT::TGIB8;
			case interrupt::C:   return INT::TGIC8;
			case interrupt::D:   return INT::TGID8;
			case interrupt::OVF: return INT::TCIV8;
			}
			return INT::NONE;
		}
	};
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TCR_ mtu8_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TCR2_ mtu8_t<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TMDR1_ mtu8_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TIORH_ mtu8_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TIORL_ mtu8_t<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TIOR_ mtu8_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TIER_ mtu8_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TCNT_ mtu8_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TGRA_ mtu8_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TGRB_ mtu8_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TGRC_ mtu8_t<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::TGRD_ mtu8_t<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu8_t<per, INT>::NFCR_ mtu8_t<per, INT>::NFCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU9 定義クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu9_t : public MTU {

		static const auto PERIPHERAL = per;		///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックソース(MTU9)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class clock_source : uint8_t {
			PCLKA      = 0b000000,	///< PCLKA / 1
			PCLKA_4    = 0b000001,	///< PCLKA / 4
			PCLKA_16   = 0b000010,	///< PCLKA / 16
			PCLKA_64   = 0b000011,	///< PCLKA / 64
			MTCLKA     = 0b000100,	///< MTCLKA
			MTCLKB     = 0b000101,	///< MTCLKB
			MTCLKC     = 0b000110,	///< MTCLKC
			MTCLKD     = 0b000111,	///< MTCLKD
			PCLKA_2    = 0b001000,	///< PCLKA / 2
			PCLKA_8    = 0b010000,	///< PCLKA / 8
			PCLKA_32   = 0b011000,	///< PCLKA / 32
			PCLKA_256  = 0b100000,	///< PCLKA / 256
			PCLKA_1024 = 0b101000,	///< PCLKA / 1024
			MTIOC1A    = 0b111000,	///< MTIOC1A
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入出力チャネル(MTU9)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class channel : uint8_t {
			A,  ///< PD7 / MTIOC9A (LFQFP100:18)
			B,  ///< PE0 / MTIOC9B (LFQFP100:17)
			C,  ///< PD6 / MTIOC9C (LFQFP100:19)
			D,  ///< PE1 / MTIOC9D (LFQFP100:16)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要因(MTU9)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class interrupt : uint8_t {
			A,		///< TGIA
			B,		///< TGIB
			C,		///< TGIC
			D,		///< TGID
			OVF,	///< TCIV オーバーフロー
			E,		///< TGIE
			F,		///< TGIF
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU9)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST9 = ena;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートマッピングチャネルを取得
			@param[in]	ch	チャネル
			@return ポート・マッピング・チャネル
		*/
		//-----------------------------------------------------------------//
		static auto get_port_map_channel(channel ch)
		{
			auto ret = port_map_mtu::channel::NONE;
			switch(ch) {
			case channel::A:
				ret = port_map_mtu::channel::A;
				break;
			case channel::B:
				ret = port_map_mtu::channel::B;
				break;
			case channel::C:
				ret = port_map_mtu::channel::C;
				break;
			case channel::D:
				ret = port_map_mtu::channel::D;
				break;
			default:
				break;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t<0x000C1580> TCR_;
		static  TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t<0x000C15A8> TCR2_;
		static  TCR2_ TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1x_t<0x000C1581> TMDR1_;
		static  TMDR1_ TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t<0x000C1582> TIORH_;
		static  TIORH_ TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t<0x000C1583> TIORL_;
		static  TIORL_ TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の設定
				@param[in]	ch	チャネル
				@param[in]	val	設定値
			*/
			//-------------------------------------------------------------//
			bool set(channel ch, uint8_t val)
			{
				switch(ch) {
				case channel::A:
					TIORH.IOA = val;
					break;
				case channel::B:
					TIORH.IOB = val;
					break;
				case channel::C:
					TIORL.IOC = val;
					break;
				case channel::D:
					TIORL.IOD = val;
					break;
				default:
					return false;
				}
				return true;
			}


			//-------------------------------------------------------------//
			/*!
				@brief  TIOR の取得
				@param[in]	ch	チャネル
			*/
			//-------------------------------------------------------------//
			uint8_t get(channel ch)
			{
				switch(ch) {
				case channel::A:
					return TIORH.IOA();
					break;
				case channel::B:
					return TIORH.IOB();
					break;
				case channel::C:
					return TIORL.IOC();
					break;
				case channel::D:
					return TIORL.IOD();
					break;
				default:
					return 0x00;
				}
			}
		};
		typedef tior_t TIOR_;
		static  TIOR_ TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tiery_t<0x000C1584> TIER_;
		static  TIER_ TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER2）
		*/
		//-----------------------------------------------------------------//
		typedef tier2_t<0x000C15A4> TIER2_;
		static  TIER2_ TIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmx_t<0x000C15A6> TBTM_;
		static  TBTM_ TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1586> TCNT_;
		static  TCNT_ TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1588> TGRA_;
		static  TGRA_ TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C158A> TGRB_;
		static  TGRB_ TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C158C> TGRC_;
		static  TGRC_ TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C158E> TGRD_;
		static  TGRD_ TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C15A0> TGRE_;
		static  TGRE_ TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C15A2> TGRF_;
		static  TGRF_ TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t<0x000C1296> NFCR_;
		static  NFCR_ NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  MTU9 割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static INT get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return INT::TGIA9;
			case interrupt::B:   return INT::TGIB9;
			case interrupt::C:   return INT::TGIC9;
			case interrupt::D:   return INT::TGID9;
			case interrupt::OVF: return INT::TCIV9;
			case interrupt::E:   return INT::TGIE9;
			case interrupt::F:   return INT::TGIF9;
			}
			return INT::NONE;
		}
	};
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TCR_ mtu9_t<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TCR2_ mtu9_t<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TMDR1_ mtu9_t<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TIORH_ mtu9_t<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TIORL_ mtu9_t<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TIOR_ mtu9_t<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TIER_ mtu9_t<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TIER2_ mtu9_t<per, INT>::TIER2;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TBTM_ mtu9_t<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TCNT_ mtu9_t<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TGRA_ mtu9_t<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TGRB_ mtu9_t<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TGRC_ mtu9_t<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TGRD_ mtu9_t<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TGRE_ mtu9_t<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::TGRF_ mtu9_t<per, INT>::TGRF;
	template <peripheral per, typename INT> typename mtu9_t<per, INT>::NFCR_ mtu9_t<per, INT>::NFCR;

#if defined(SIG_RX24T)
	typedef mtu0_t<peripheral::MTU0, ICU::VECTOR> MTU0;
	typedef mtu1_t<peripheral::MTU1, ICU::VECTOR> MTU1;
	typedef mtu2_t<peripheral::MTU2, ICU::VECTOR> MTU2;
	typedef mtu3_t<peripheral::MTU3, ICU::VECTOR> MTU3;
	typedef mtu4_t<peripheral::MTU4, ICU::VECTOR> MTU4;
	typedef mtu5_t<peripheral::MTU5, ICU::VECTOR> MTU5;
	typedef mtu6_t<peripheral::MTU6, ICU::VECTOR> MTU6;
	typedef mtu7_t<peripheral::MTU7, ICU::VECTOR> MTU7;
	typedef mtu9_t<peripheral::MTU9, ICU::VECTOR> MTU9;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	typedef mtu0_t<peripheral::MTU0, ICU::VECTOR_SELA> MTU0;
	typedef mtu1_t<peripheral::MTU1, ICU::VECTOR_SELA> MTU1;
	typedef mtu2_t<peripheral::MTU2, ICU::VECTOR_SELA> MTU2;
	typedef mtu3_t<peripheral::MTU3, ICU::VECTOR_SELA> MTU3;
	typedef mtu4_t<peripheral::MTU4, ICU::VECTOR_SELA> MTU4;
	typedef mtu5_t<peripheral::MTU5, ICU::VECTOR_SELA> MTU5;
	typedef mtu6_t<peripheral::MTU6, ICU::VECTOR_SELA> MTU6;
	typedef mtu7_t<peripheral::MTU7, ICU::VECTOR_SELA> MTU7;
	typedef mtu8_t<peripheral::MTU8, ICU::VECTOR_SELA> MTU8;
#elif defined(SIG_RX66T)
	typedef mtu0_t<peripheral::MTU0, ICU::VECTOR_SELA> MTU0;
	typedef mtu1_t<peripheral::MTU1, ICU::VECTOR_SELA> MTU1;
	typedef mtu2_t<peripheral::MTU2, ICU::VECTOR_SELA> MTU2;
	typedef mtu3_t<peripheral::MTU3, ICU::VECTOR_SELA> MTU3;
	typedef mtu4_t<peripheral::MTU4, ICU::VECTOR_SELA> MTU4;
	typedef mtu5_t<peripheral::MTU5, ICU::VECTOR_SELA> MTU5;
	typedef mtu6_t<peripheral::MTU6, ICU::VECTOR_SELA> MTU6;
	typedef mtu7_t<peripheral::MTU7, ICU::VECTOR_SELA> MTU7;
	typedef mtu9_t<peripheral::MTU9, ICU::VECTOR_SELA> MTU9;
#endif
}
