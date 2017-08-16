#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・MTU3d 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX24T/peripheral.hpp"
#include "RX24T/icu.hpp"
#include "RX24T/mpc.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU 全体定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static tmdr_t<0x000C1270> TMDR2A;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 2（TMDR2B）
		*/
		//-----------------------------------------------------------------//
		static tmdr_t<0x000C1A70> TMDR2B;


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

			bit_rw_t<io_, bitpos::B4> CST9;

			bit_rw_t<io_, bitpos::B6> CST3;
			bit_rw_t<io_, bitpos::B7> CST4;
		};
		static tstra_t<0x000C1280> TSTRA;


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
		static tstrb_t<0x000C1A80> TSTRB;


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
		static tsyra_t<0x000C1281> TSYRA;


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
		static tsyrb_t<0x000C1A81> TSYRB;


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
		static tcsystr_t<0x000C1282> TCSYSTR;


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
		static trwer_t<0x000C1284> TRWERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマリードライトイネーブルレジスタ（TRWERB）
		*/
		//-----------------------------------------------------------------//
		static trwer_t<0x000C1A84> TRWERB;


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
		static toera_t<0x000C120A> TOERA; 


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
		static toerb_t<0x000C120A> TOERB; 


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
		static tocr1_t<0x000C120E> TOCR1A; 


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 1（TOCR1B）
		*/
		//-----------------------------------------------------------------//
		static tocr1_t<0x000C1A0E> TOCR1B; 


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
		static tocr2_t<0x000C120F> TOCR2A; 


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 2（TOCR2B）
		*/
		//-----------------------------------------------------------------//
		static tocr2_t<0x000C1A0F> TOCR2B; 


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
		static tolbr_t<0x000C1236> TOLBRA; 


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットレベルバッファレジスタ（TOLBRB）
		*/
		//-----------------------------------------------------------------//
		static tolbr_t<0x000C1A36> TOLBRB; 


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
		static tgcra_t<0x000C120D> TGCRA; 


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマゲートコントロールレジスタ（TGCRB）
		*/
		//-----------------------------------------------------------------//
		static tgcra_t<0x000C1A0D> TGCRB; 


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマサブカウンタ（TCNTSA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1220> TCNTSA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマサブカウンタ（TCNTSB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A20> TCNTSB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期データレジスタ（TCDRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1214> TCDRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期データレジスタ（TCDRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A14> TCDRB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期バッファレジスタ（TCBRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1222> TCBRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期バッファレジスタ（TCBRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A22> TCBRB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマデッドタイムデータレジスタ（TDDRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1216> TDDRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマデッドタイムデータレジスタ（TDDRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A16> TDDRB;


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
		static tder_t<0x000C1234> TDERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマデッドタイムイネーブルレジスタ（TDERB）
		*/
		//-----------------------------------------------------------------//
		static tder_t<0x000C1A34> TDERB;


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
		static tbter_t<0x000C1232> TBTERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマバッファ転送設定レジスタ（TBTERB）
		*/
		//-----------------------------------------------------------------//
		static tbter_t<0x000C1A32> TBTERB;


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
		static twcr_t<0x000C1260> TWCRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ波形コントロールレジスタ（TWCRB）
		*/
		//-----------------------------------------------------------------//
		static twcr_t<0x000C1A60> TWCRB;


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

			bit_rw_t <io_, bitpos::B0>      NFAEN;
			bit_rw_t <io_, bitpos::B1>      NFBEN;
			bit_rw_t <io_, bitpos::B2>      NFCEN;
			bit_rw_t <io_, bitpos::B3>      NFDEN;

			bits_rw_t <io_, bitpos::B4, 2>  NFCS;
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
		static titmr_t<0x000C123A> TITMRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引きモードレジスタ（TITMRB）
		*/
		//-----------------------------------------------------------------//
		static titmr_t<0x000C1A3A> TITMRB;


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
		static titcr1a_t<0x000C1230> TITCR1A;


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
		static titcr1b_t<0x000C1230> TITCR1B;


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
		static titcnt1a_t<0x000C1231> TITCNT1A;


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
		static titcnt1b_t<0x000C1A31> TITCNT1B;


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
		static titcr2a_t<0x000C123B> TITCR2A;


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
		static titcr2b_t<0x000C1A3B> TITCR2B;


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
		static titcnt2a_t<0x000C123C> TITCNT2A;


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
		static titcnt2b_t<0x000C1A3C> TITCNT2B;


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
		static tadstrgr0_t<0x000C1D30> TADSTRGR0;


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
		static tadstrgr1_t<0x000C1D32> TADSTRGR1;

	};
	typedef mtu_t MTU;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU0 定義基底クラス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral t>
	struct mtu0_t : public mtu_t {

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
			MTU::TSTRA.CST0 = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static tcr_t<0x000C1300> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static tcr2_t<0x000C1328> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static tmdr1x_t<0x000C1301> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		static tiorh_t<0x000C1302> TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		static tiorl_t<0x000C1303> TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

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

		};
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static tiery_t<0x000C1304> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER2）
		*/
		//-----------------------------------------------------------------//
		static tier2_t<0x000C1324> TIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static tbtmx_t<0x000C1326> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1306> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1308> TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C130A> TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C130C> TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C130E> TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1320> TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1322> TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static nfcr_t<0x000C1290> NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return ICU::VECTOR::TGIA0;
			case interrupt::B:   return ICU::VECTOR::TGIB0;
			case interrupt::C:   return ICU::VECTOR::TGIC0;
			case interrupt::D:   return ICU::VECTOR::TGID0;
			case interrupt::OVF: return ICU::VECTOR::TCIV0;
			case interrupt::E:   return ICU::VECTOR::TGIE0;
			case interrupt::F:   return ICU::VECTOR::TGIF0;
			}
			return ICU::VECTOR::NONE;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU1 定義基底クラス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral t>
	struct mtu1_t : public mtu_t {

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
			A,  ///< PA5 / MTIOC1A (LFQFP100:36)
			B,  ///< PA4 / MTIOC1B (LFQFP100:37)
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
			MTU::TSTRA.CST1 = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static tcr_t<0x000C1380> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static tcr2x_t<0x000C1394> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static tmdr1y_t<0x000C1381> TMDR1;


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
		static tmdr3_t<0x000C1391> TMDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		static tiorh_t<0x000C1382> TIORH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

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

		};
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static tierx_t<0x000C1384> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static tsr_t<0x000C1385> TSR;


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
		static ticcr_t<0x000C1390> TICCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1386> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマロングワードカウンタ（TCNTLW）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C13A0> TCNTLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1388> TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C138A> TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマロングワードジェネラルレジスタ（TGRALW）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C13A4> TGRALW;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマロングワードジェネラルレジスタ（TGRBLW）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<0x000C13A8> TGRBLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static nfcr_t<0x000C1291> NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return ICU::VECTOR::TGIA1;
			case interrupt::B:   return ICU::VECTOR::TGIB1;
			case interrupt::OVF: return ICU::VECTOR::TCIV1;
			case interrupt::UDF: return ICU::VECTOR::TCIU1;
			}
			return ICU::VECTOR::NONE;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU2 定義基底クラス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral t>
	struct mtu2_t : public mtu_t {

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
			MTU::TSTRA.CST2 = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static tcr_t<0x000C1400> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static tcr2x_t<0x000C140C> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static tmdr1y_t<0x000C1401> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		static tiorh_t<0x000C1402> TIORH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

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

		};
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static tierx_t<0x000C1404> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static tsr_t<0x000C1405> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1406> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1408> TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C140A> TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static nfcr_t<0x000C1292> NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return ICU::VECTOR::TGIA2;
			case interrupt::B:   return ICU::VECTOR::TGIB2;
			case interrupt::OVF: return ICU::VECTOR::TCIV2;
			case interrupt::UDF: return ICU::VECTOR::TCIU2;
			}
			return ICU::VECTOR::NONE;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU3 定義基底クラス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral t>
	struct mtu3_t : public mtu_t {

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
			OVR,	///< TCIV オーバーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU3)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST3 = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static tcr_t<0x000C1200> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static tcr2_t<0x000C124C> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static tmdr1z_t<0x000C1202> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		static tiorh_t<0x000C1204> TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		static tiorl_t<0x000C1205> TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

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

		};
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static tiery_t<0x000C1208> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static tsr_t<0x000C122C> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static tbtmy_t<0x000C1238> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1210> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1218> TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C121A> TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1224> TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1226> TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1272> TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static nfcr_t<0x000C1293> NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return ICU::VECTOR::TGIA3;
			case interrupt::B:   return ICU::VECTOR::TGIB3;
			case interrupt::C:   return ICU::VECTOR::TGIC3;
			case interrupt::D:   return ICU::VECTOR::TGID3;
			case interrupt::OVF: return ICU::VECTOR::TCIV3;
			}
			return ICU::VECTOR::NONE;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU4 定義基底クラス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral t>
	struct mtu4_t : public mtu_t {

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
			OVR,	///< TCIV オーバーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU4)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST4 = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static tcr_t<0x000C1201> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static tcr2_t<0x000C124D> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static tmdr1z_t<0x000C1203> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		static tiorh_t<0x000C1206> TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		static tiorl_t<0x000C1207> TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

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

		};
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static tierz_t<0x000C1209> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static tsr_t<0x000C122D> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static tbtmy_t<0x000C1239> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1212> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C121C> TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C121E> TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1228> TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C122A> TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1274> TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1276> TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static nfcr_t<0x000C1294> NFCR;


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
		static tadcr_t<0x000C1240> TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1244> TADCORA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1246> TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1248> TADCOBRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C124A> TADCOBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return ICU::VECTOR::TGIA4;
			case interrupt::B:   return ICU::VECTOR::TGIB4;
			case interrupt::C:   return ICU::VECTOR::TGIC4;
			case interrupt::D:   return ICU::VECTOR::TGID4;
			case interrupt::OVF: return ICU::VECTOR::TCIV4;
			}
			return ICU::VECTOR::NONE;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU5 定義基底クラス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral t>
	struct mtu5_t {

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
			U2,  ///< P82 / MTIOC5U (LFQFP100:96)
			V2,  ///< P81 / MTIOC5V (LFQFP100:97)
			W2,  ///< P80 / MTIOC5W (LFQFP100:98)
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


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU5)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRA.CST5 = 1;
		}
#endif


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
		static tcr_t<0x000C1C84> TCRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCRV）
		*/
		//-----------------------------------------------------------------//
		static tcr_t<0x000C1C94> TCRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCRW）
		*/
		//-----------------------------------------------------------------//
		static tcr_t<0x000C1CA4> TCRW;


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
		static tior_t<0x000C1C86> TIORU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORV）
		*/
		//-----------------------------------------------------------------//
		static tior_t<0x000C1C96> TIORV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORW）
		*/
		//-----------------------------------------------------------------//
		static tior_t<0x000C1CA6> TIORW;


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
		static tcntcmpclr_t<0x000C1CB6> TCNTCMPCLR;


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
		static tier_t<0x000C1CB2> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTU）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1C80> TCNTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTV）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1C90> TCNTV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1CA0> TCNTW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRU）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1C82> TGRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRV）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1C92> TGRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRW）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1CA2> TGRW;


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
		static tstr_t<0x000C1CB4> TSTR;


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
		static nfcr_t<0x000C1A95> NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::U:   return ICU::VECTOR::TGIU5;
			case interrupt::V:   return ICU::VECTOR::TGIV5;
			case interrupt::W:   return ICU::VECTOR::TGIW5;
			}
			return ICU::VECTOR::NONE;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU6 定義基底クラス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral t>
	struct mtu6_t : public mtu_t {

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
			OVR,	///< TCIV オーバーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU6)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRB.CST6 = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static tcr_t<0x000C1A00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static tcr2_t<0x000C1A4C> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static tmdr1z_t<0x000C1A02> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		static tiorh_t<0x000C1A04> TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		static tiorl_t<0x000C1A05> TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

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

		};
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static tiery_t<0x000C1A08> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static tsr_t<0x000C1A2C> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static tbtmy_t<0x000C1A38> TBTM;


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
		static tsycr_t<0x000C1A50> TSYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A10> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A18> TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A1A> TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A24> TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A26> TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A72> TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static nfcr_t<0x000C1A93> NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return ICU::VECTOR::TGIA6;
			case interrupt::B:   return ICU::VECTOR::TGIB6;
			case interrupt::C:   return ICU::VECTOR::TGIC6;
			case interrupt::D:   return ICU::VECTOR::TGID6;
			case interrupt::OVF: return ICU::VECTOR::TCIV6;
			}
			return ICU::VECTOR::NONE;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU7 定義基底クラス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral t>
	struct mtu7_t : public mtu_t {

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
			OVR,	///< TCIV オーバーフロー
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  有効にする(MTU7)
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true)
		{
			MTU::TSTRB.CST7 = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static tcr_t<0x000C1A01> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static tcr2_t<0x000C1A4D> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static tmdr1z_t<0x000C1A03> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		static tiorh_t<0x000C1A06> TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		static tiorl_t<0x000C1A07> TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

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

		};
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static tierz_t<0x000C1A09> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		static tsr_t<0x000C1A2D> TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static tbtmy_t<0x000C1A39> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A12> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A1C> TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A1E> TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A28> TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A2A> TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A74> TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A76> TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static nfcr_t<0x000C1A94> NFCR;


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
		static tadcr_t<0x000C1A40> TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A44> TADCORA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A46> TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A48> TADCOBRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1A4A> TADCOBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return ICU::VECTOR::TGIA7;
			case interrupt::B:   return ICU::VECTOR::TGIB7;
			case interrupt::C:   return ICU::VECTOR::TGIC7;
			case interrupt::D:   return ICU::VECTOR::TGID7;
			case interrupt::OVF: return ICU::VECTOR::TCIV7;
			}
			return ICU::VECTOR::NONE;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU9 定義基底クラス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral t>
	struct mtu9_t : public mtu_t {

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
			OVR,	///< TCIV オーバーフロー
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
			@brief  タイマコントロールレジスタ（TCR）
		*/
		//-----------------------------------------------------------------//
		static tcr_t<0x000C1580> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		static tcr2_t<0x000C15A8> TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		static tmdr1x_t<0x000C1581> TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		static tiorh_t<0x000C1582> TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		static tiorl_t<0x000C1583> TIORL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIOR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct tior_t {

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

		};
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		static tiery_t<0x000C1584> TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER2）
		*/
		//-----------------------------------------------------------------//
		static tier2_t<0x000C15A4> TIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		static tbtmx_t<0x000C15A6> TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1586> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C1588> TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C158A> TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C158C> TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C158E> TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C15A0> TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<0x000C15A2> TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		static nfcr_t<0x000C1296> NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@param[in]	intr	割り込み要因
			@return 割り込みベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_vec(interrupt intr) {
			switch(intr) {
			case interrupt::A:   return ICU::VECTOR::TGIA9;
			case interrupt::B:   return ICU::VECTOR::TGIB9;
			case interrupt::C:   return ICU::VECTOR::TGIC9;
			case interrupt::D:   return ICU::VECTOR::TGID9;
			case interrupt::OVF: return ICU::VECTOR::TCIV9;
			case interrupt::E:   return ICU::VECTOR::TGIE9;
			case interrupt::F:   return ICU::VECTOR::TGIF9;
			}
			return ICU::VECTOR::NONE;
		}
	};

	typedef mtu0_t<peripheral::MTU0> MTU0;
	typedef mtu1_t<peripheral::MTU1> MTU1;
	typedef mtu2_t<peripheral::MTU2> MTU2;
	typedef mtu3_t<peripheral::MTU3> MTU3;
	typedef mtu4_t<peripheral::MTU4> MTU4;
	typedef mtu5_t<peripheral::MTU5> MTU5;
	typedef mtu6_t<peripheral::MTU6> MTU6;
	typedef mtu7_t<peripheral::MTU7> MTU7;
	typedef mtu9_t<peripheral::MTU9> MTU9;
}
