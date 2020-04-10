#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・MTU3d 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
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
	template<class _>
	struct mtu_t_ {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tcr_t_ : public rw8_t<base> {
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
		struct tcr2_t_ : public rw8_t<base> {
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
		struct tcr2x_t_ : public rw8_t<base> {
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
		struct tmdr1x_t_ : public rw8_t<base> {
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
		struct tmdr1y_t_ : public rw8_t<base> {
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
		struct tmdr1z_t_ : public rw8_t<base> {
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
		struct tmdr_t_ : public rw8_t<base> {
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
		typedef tmdr_t_<0x000C1270> tmdr2a_t;
		static tmdr2a_t TMDR2A;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 2（TMDR2B）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr_t_<0x000C1A70> tmdr2b_t;
		static tmdr2b_t TMDR2B;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tiorh_t_ : public rw8_t<base> {
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
		struct tiorl_t_ : public rw8_t<base> {
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
		struct tierx_t_ : public rw8_t<base> {
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
		struct tiery_t_ : public rw8_t<base> {
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
		struct tierz_t_ : public rw8_t<base> {
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
		struct tier2_t_ : public rw8_t<base> {
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
		struct tsr_t_ : public rw8_t<base> {
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
		struct tbtmx_t_ : public rw8_t<base> {
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
		struct tbtmy_t_ : public rw8_t<base> {
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
		struct tstra_t_ : public rw8_t<base> {
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
		typedef tstra_t_<0x000C1280> tstra_t;
		static tstra_t TSTRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTRB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstrb_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> CST6;
			bit_rw_t<io_, bitpos::B7> CST7;
		};
		typedef tstrb_t_<0x000C1A80> tstrb_t;
		static tstrb_t TSTRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CSW5;
			bit_rw_t<io_, bitpos::B1> CSV5;
			bit_rw_t<io_, bitpos::B2> CSU5;
		};
		typedef tstr_t_<0x000C1CB4> tstr_t;
		static tstr_t TSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマシンクロレジスタ（TSYRA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tsyra_t_ : public rw8_t<base> {
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
		typedef tsyra_t_<0x000C1281> tsyra_t;
		static tsyra_t TSYRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマシンクロレジスタ（TSYRB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tsyrb_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> SYNC6;
			bit_rw_t<io_, bitpos::B7> SYNC7;
		};
		typedef tsyrb_t_<0x000C1A81> tsyrb_t;
		static tsyrb_t TSYRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマカウンタシンクロスタートレジスタ（TCSYSTR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tcsystr_t_ : public rw8_t<base> {
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
		typedef tcsystr_t_<0x000C1282> tcsystr_t;
		static tcsystr_t TCSYSTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマリードライトイネーブルレジスタ（TRWER）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct trwer_t_ : public rw8_t<base> {
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
		typedef trwer_t_<0x000C1284> trwera_t;
		static trwera_t TRWERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマリードライトイネーブルレジスタ（TRWERB）
		*/
		//-----------------------------------------------------------------//
		typedef trwer_t_<0x000C1A84> trwerb_t;
		static trwerb_t TRWERB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットマスタイネーブルレジスタ（TOERA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct toera_t_ : public rw8_t<base> {
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
		typedef toera_t_<0x000C120A> toera_t;
		static toera_t TOERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットマスタイネーブルレジスタ（TOERB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct toerb_t_ : public rw8_t<base> {
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
		typedef toerb_t_<0x000C120A> toerb_t;
		static toerb_t TOERB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 1（TOCR1A, TOCR1B）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tocr1_t_ : public rw8_t<base> {
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
		typedef tocr1_t_<0x000C120E> tocr1a_t;
		static tocr1a_t TOCR1A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 1（TOCR1B）
		*/
		//-----------------------------------------------------------------//
		typedef tocr1_t_<0x000C1A0E> tocr1b_t;
		static tocr1b_t TOCR1B;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 2（TOCR2A, TOCR2B）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tocr2_t_ : public rw8_t<base> {
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
		typedef tocr2_t_<0x000C120F> tocr2a_t;
		static tocr2a_t TOCR2A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットコントロールレジスタ 2（TOCR2B）
		*/
		//-----------------------------------------------------------------//
		typedef tocr2_t_<0x000C1A0F> tocr2b_t;
		static tocr2b_t TOCR2B;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマアウトプットレベルバッファレジスタ（TOLBRA, TOLBRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tolbr_t_ : public rw8_t<base> {
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
		typedef tolbr_t_<0x000C1236> tolbra_t;
		static tolbra_t TOLBRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマアウトプットレベルバッファレジスタ（TOLBRB）
		*/
		//-----------------------------------------------------------------//
		typedef tolbr_t_<0x000C1A36> tolbrb_t;
		static tolbrb_t TOLBRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマゲートコントロールレジスタ（TGCRA, TGCRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tgcra_t_ : public rw8_t<base> {
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
		typedef tgcra_t_<0x000C120D> tgcra_t;
		static tgcra_t TGCRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマゲートコントロールレジスタ（TGCRB）
		*/
		//-----------------------------------------------------------------//
		typedef tgcra_t_<0x000C1A0D> tgcrb_t;
		static tgcrb_t TGCRB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマサブカウンタ（TCNTSA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1220> tcntsa_t;
		static tcntsa_t TCNTSA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマサブカウンタ（TCNTSB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A20> tcntsb_t;
		static tcntsb_t TCNTSB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期データレジスタ（TCDRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1214> tcdra_t;
		static tcdra_t TCDRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期データレジスタ（TCDRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A14> tcdrb_t;
		static tcdrb_t TCDRB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期バッファレジスタ（TCBRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1222> tcbra_t;
		static tcbra_t TCBRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマ周期バッファレジスタ（TCBRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A22> tcbrb_t;
		static tcbrb_t TCBRB;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマデッドタイムデータレジスタ（TDDRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1216> tddra_t;
		static tddra_t TDDRA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイマデッドタイムデータレジスタ（TDDRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A16> tddrb_t;
		static tddrb_t TDDRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマデッドタイムイネーブルレジスタ（TDERA, TDERB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tder_t_ : public rw8_t<base> {
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
		typedef tder_t_<0x000C1234> tdera_t;
		static tdera_t TDERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマデッドタイムイネーブルレジスタ（TDERB）
		*/
		//-----------------------------------------------------------------//
		typedef tder_t_<0x000C1A34> tderb_t;
		static tderb_t TDERB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマバッファ転送設定レジスタ（TBTERA, TBTERB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tbter_t_ : public rw8_t<base> {
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
		typedef tbter_t_<0x000C1232> tbtera_t;
		static tbtera_t TBTERA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマバッファ転送設定レジスタ（TBTERB）
		*/
		//-----------------------------------------------------------------//
		typedef tbter_t_<0x000C1A32> tbterb_t;
		static tbterb_t TBTERB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイマ波形コントロールレジスタ（TWCRA, TWCRB）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct twcr_t_ : public rw8_t<base> {
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
		typedef twcr_t_<0x000C1260> twcra_t;
		static twcra_t TWCRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ波形コントロールレジスタ（TWCRB）
		*/
		//-----------------------------------------------------------------//
		typedef twcr_t_<0x000C1A60> twcrb_t;
		static twcrb_t TWCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ノイズフィルタコントロールレジスタ n（NFCRn）（n = 0 ～ 4, 6, 7, 9）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct nfcr_t_ : public rw8_t<base> {
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
		struct titmr_t_ : public rw8_t<base> {
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
		typedef titmr_t_<0x000C123A> titmra_t;
		static titmra_t TITMRA;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引きモードレジスタ（TITMRB）
		*/
		//-----------------------------------------------------------------//
		typedef titmr_t_<0x000C1A3A> titmrb_t;
		static titmrb_t TITMRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 1（TITCR1A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr1a_t_ : public rw8_t<base> {
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
		typedef titcr1a_t_<0x000C1230> titcr1a_t;
		static titcr1a_t TITCR1A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 1（TITCR1B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr1b_t_ : public rw8_t<base> {
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
		typedef titcr1b_t_<0x000C1230> titcr1b_t;
		static titcr1b_t TITCR1B;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 1（TITCNT1A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt1a_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T4VCNT;
			bits_rw_t<io_, bitpos::B4, 3>  T3ACNT;
		};
		typedef titcnt1a_t_<0x000C1231> titcnt1a_t;
		static titcnt1a_t TITCNT1A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 1（TITCNT1B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt1b_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  T7VCNT;
			bits_rw_t<io_, bitpos::B4, 3>  T6ACNT;
		};
		typedef titcnt1b_t_<0x000C1A31> titcnt1b_t;
		static titcnt1b_t TITCNT1B;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 2（TITCR2A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr2a_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG4COR;
		};
		typedef titcr2a_t_<0x000C123B> titcr2a_t;
		static titcr2a_t TITCR2A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き設定レジスタ 2（TITCR2B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcr2b_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG7COR;
		};
		typedef titcr2b_t_<0x000C1A3B> titcr2b_t;
		static titcr2b_t TITCR2B;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 2（TITCNT2A）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt2a_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG4CNT;
		};
		typedef titcnt2a_t_<0x000C123C> titcnt2a_t;
		static titcnt2a_t TITCNT2A;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ割り込み間引き回数カウンタ 2（TITCNT2B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct titcnt2b_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  TRG7CNT;
		};
		typedef titcnt2b_t_<0x000C1A3C> titcnt2b_t;
		static titcnt2b_t TITCNT2B;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求選択レジスタ 0（TADSTRGR0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadstrgr0_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  TADSTRS0;
		};
		typedef tadstrgr0_t_<0x000C1D30> tadstrgr0_t;
		static tadstrgr0_t TADSTRGR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	A/D 変換開始要求選択レジスタ 1（TADSTRGR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadstrgr1_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  TADSTRS1;
		};
		typedef tadstrgr1_t_<0x000C1D32> tadstrgr1_t;
		static tadstrgr1_t TADSTRGR1;

	};
	typedef mtu_t_<void> MTU;
	typedef mtu_t_<void> mtu_t;

	template<class _> typename mtu_t_<_>::tmdr2a_t    mtu_t_<_>::TMDR2A;
	template<class _> typename mtu_t_<_>::tmdr2b_t    mtu_t_<_>::TMDR2B;
	template<class _> typename mtu_t_<_>::tstra_t     mtu_t_<_>::TSTRA;
	template<class _> typename mtu_t_<_>::tstrb_t     mtu_t_<_>::TSTRB;
	template<class _> typename mtu_t_<_>::tstr_t      mtu_t_<_>::TSTR;
	template<class _> typename mtu_t_<_>::tsyra_t     mtu_t_<_>::TSYRA;
	template<class _> typename mtu_t_<_>::tsyrb_t     mtu_t_<_>::TSYRB;
	template<class _> typename mtu_t_<_>::tcsystr_t   mtu_t_<_>::TCSYSTR;
	template<class _> typename mtu_t_<_>::trwera_t    mtu_t_<_>::TRWERA;
	template<class _> typename mtu_t_<_>::trwerb_t    mtu_t_<_>::TRWERB;
	template<class _> typename mtu_t_<_>::toera_t     mtu_t_<_>::TOERA;
	template<class _> typename mtu_t_<_>::toerb_t     mtu_t_<_>::TOERB;
	template<class _> typename mtu_t_<_>::tocr1a_t    mtu_t_<_>::TOCR1A;
	template<class _> typename mtu_t_<_>::tocr1b_t    mtu_t_<_>::TOCR1B;
	template<class _> typename mtu_t_<_>::tocr2a_t    mtu_t_<_>::TOCR2A;
	template<class _> typename mtu_t_<_>::tocr2b_t    mtu_t_<_>::TOCR2B;
	template<class _> typename mtu_t_<_>::tolbra_t    mtu_t_<_>::TOLBRA;
	template<class _> typename mtu_t_<_>::tolbrb_t    mtu_t_<_>::TOLBRB;
	template<class _> typename mtu_t_<_>::tgcra_t     mtu_t_<_>::TGCRA;
	template<class _> typename mtu_t_<_>::tgcrb_t     mtu_t_<_>::TGCRB;
	template<class _> typename mtu_t_<_>::tcntsa_t    mtu_t_<_>::TCNTSA;
	template<class _> typename mtu_t_<_>::tcntsb_t    mtu_t_<_>::TCNTSB;
	template<class _> typename mtu_t_<_>::tcdra_t     mtu_t_<_>::TCDRA;
	template<class _> typename mtu_t_<_>::tcdrb_t     mtu_t_<_>::TCDRB;
	template<class _> typename mtu_t_<_>::tcbra_t     mtu_t_<_>::TCBRA;
	template<class _> typename mtu_t_<_>::tcbrb_t     mtu_t_<_>::TCBRB;
	template<class _> typename mtu_t_<_>::tddra_t     mtu_t_<_>::TDDRA;
	template<class _> typename mtu_t_<_>::tddrb_t     mtu_t_<_>::TDDRB;
	template<class _> typename mtu_t_<_>::tdera_t     mtu_t_<_>::TDERA;
	template<class _> typename mtu_t_<_>::tderb_t     mtu_t_<_>::TDERB;
	template<class _> typename mtu_t_<_>::tbtera_t    mtu_t_<_>::TBTERA;
	template<class _> typename mtu_t_<_>::tbterb_t    mtu_t_<_>::TBTERB;
	template<class _> typename mtu_t_<_>::twcra_t     mtu_t_<_>::TWCRA;
	template<class _> typename mtu_t_<_>::twcrb_t     mtu_t_<_>::TWCRB;
	template<class _> typename mtu_t_<_>::titmra_t    mtu_t_<_>::TITMRA;
	template<class _> typename mtu_t_<_>::titmrb_t    mtu_t_<_>::TITMRB;
	template<class _> typename mtu_t_<_>::titcr1a_t   mtu_t_<_>::TITCR1A;
	template<class _> typename mtu_t_<_>::titcr1b_t   mtu_t_<_>::TITCR1B;
	template<class _> typename mtu_t_<_>::titcnt1a_t  mtu_t_<_>::TITCNT1A;
	template<class _> typename mtu_t_<_>::titcnt1b_t  mtu_t_<_>::TITCNT1B;
	template<class _> typename mtu_t_<_>::titcr2a_t   mtu_t_<_>::TITCR2A;
	template<class _> typename mtu_t_<_>::titcr2b_t   mtu_t_<_>::TITCR2B;
	template<class _> typename mtu_t_<_>::titcnt2a_t  mtu_t_<_>::TITCNT2A;
	template<class _> typename mtu_t_<_>::titcnt2b_t  mtu_t_<_>::TITCNT2B;
	template<class _> typename mtu_t_<_>::tadstrgr0_t mtu_t_<_>::TADSTRGR0;
	template<class _> typename mtu_t_<_>::tadstrgr1_t mtu_t_<_>::TADSTRGR1;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU0 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu0_t_ : public mtu_t {

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
		typedef tcr_t_<0x000C1300> tcr_t;
		static tcr_t TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t_<0x000C1328> tcr2_t;
		static tcr2_t TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1x_t_<0x000C1301> tmdr1_t;
		static tmdr1_t TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t_<0x000C1302> tiorh_t;
		static tiorh_t TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t_<0x000C1303> tiorl_t;
		static tiorl_t TIORL;


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
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tiery_t_<0x000C1304> tier_t;
		static tier_t TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER2）
		*/
		//-----------------------------------------------------------------//
		typedef tier2_t_<0x000C1324> tier2_t;
		static tier2_t TIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmx_t_<0x000C1326> tbtm_t;
		static tbtm_t TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1306> tcnt_t;
		static tcnt_t TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1308> tgra_t;
		static tgra_t TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C130A> tgrb_t;
		static tgrb_t TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C130C> tgrc_t;
		static tgrc_t TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C130E> tgrd_t;
		static tgrd_t TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1320> tgre_t;
		static tgre_t TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1322> tgrf_t;
		static tgrf_t TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t_<0x000C1290> nfcr_t;
		static nfcr_t NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタクロック（NFCRC）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t_<0x000C1299> nfcrc_t;
		static nfcrc_t NFCRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


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

	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tcr_t   mtu0_t_<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tcr2_t  mtu0_t_<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tmdr1_t mtu0_t_<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tiorh_t mtu0_t_<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tiorl_t mtu0_t_<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tior_t  mtu0_t_<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tier_t  mtu0_t_<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tier2_t mtu0_t_<per, INT>::TIER2;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tbtm_t  mtu0_t_<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tcnt_t  mtu0_t_<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tgra_t  mtu0_t_<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tgrb_t  mtu0_t_<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tgrc_t  mtu0_t_<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tgrd_t  mtu0_t_<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tgre_t  mtu0_t_<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::tgrf_t  mtu0_t_<per, INT>::TGRF;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::nfcr_t  mtu0_t_<per, INT>::NFCR;
	template <peripheral per, typename INT> typename mtu0_t_<per, INT>::nfcrc_t mtu0_t_<per, INT>::NFCRC;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU1 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu1_t_ : public mtu_t {

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
		typedef tcr_t_<0x000C1380> tcr_t;
		static tcr_t TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2x_t_<0x000C1394> tcr2_t;
		static tcr2_t TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1y_t_<0x000C1381> tmdr1_t;
		static tmdr1_t TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 3（TMDR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tmdr3_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> LWA;
			bit_rw_t<io_, bitpos::B1> PHCKSEL;
		};
		typedef tmdr3_t_<0x000C1391> tmdr3_t;
		static tmdr3_t TMDR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t_<0x000C1382> tiorh_t;
		static tiorh_t TIORH;


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
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tierx_t_<0x000C1384> tier_t;
		static tier_t TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t_<0x000C1385> tsr_t;
		static tsr_t TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインプットキャプチャコントロールレジスタ（TICCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ticcr_t_ : public rw8_t<base> {
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
		typedef ticcr_t_<0x000C1390> ticcr_t;
		static ticcr_t TICCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1386> tcnt_t;
		static tcnt_t TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマロングワードカウンタ（TCNTLW）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C13A0> tcntlw_t;
		static tcntlw_t TCNTLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1388> tgra_t;
		static tgra_t TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C138A> tgrb_t;
		static tgrb_t TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマロングワードジェネラルレジスタ（TGRALW）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C13A4> tgralw_t;
		static tgralw_t TGRALW;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマロングワードジェネラルレジスタ（TGRBLW）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000C13A8> tgrblw_t;
		static tgrblw_t TGRBLW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t_<0x000C1291> nfcr_t;
		static nfcr_t NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


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

	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tcr_t    mtu1_t_<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tcr2_t   mtu1_t_<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tmdr1_t  mtu1_t_<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tmdr3_t  mtu1_t_<per, INT>::TMDR3;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tiorh_t  mtu1_t_<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tior_t   mtu1_t_<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tier_t   mtu1_t_<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tsr_t    mtu1_t_<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::ticcr_t  mtu1_t_<per, INT>::TICCR;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tcnt_t   mtu1_t_<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tcntlw_t mtu1_t_<per, INT>::TCNTLW;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tgra_t   mtu1_t_<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tgrb_t   mtu1_t_<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tgralw_t mtu1_t_<per, INT>::TGRALW;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::tgrblw_t mtu1_t_<per, INT>::TGRBLW;
	template <peripheral per, typename INT> typename mtu1_t_<per, INT>::nfcr_t   mtu1_t_<per, INT>::NFCR;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU2 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu2_t_ : public mtu_t {

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
		typedef tcr_t_<0x000C1400> tcr_t;
		static tcr_t TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2x_t_<0x000C140C> tcr2_t;
		static tcr2_t TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1y_t_<0x000C1401> tmdr1_t;
		static tmdr1_t TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t_<0x000C1402> tiorh_t;
		static tiorh_t TIORH;


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
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tierx_t_<0x000C1404> tier_t;
		static tier_t TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t_<0x000C1405> tsr_t;
		static tsr_t TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1406> tcnt_t;
		static tcnt_t TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1408> tgra_t;
		static tgra_t TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C140A> tgrb_t;
		static tgrb_t TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t_<0x000C1292> nfcr_t;
		static nfcr_t NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


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
	template <peripheral per, typename INT> typename mtu2_t_<per, INT>::tcr2_t  mtu2_t_<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu2_t_<per, INT>::tmdr1_t mtu2_t_<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu2_t_<per, INT>::tiorh_t mtu2_t_<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu2_t_<per, INT>::tior_t  mtu2_t_<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu2_t_<per, INT>::tier_t  mtu2_t_<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu2_t_<per, INT>::tsr_t   mtu2_t_<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu2_t_<per, INT>::tcnt_t  mtu2_t_<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu2_t_<per, INT>::tgra_t  mtu2_t_<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu2_t_<per, INT>::tgrb_t  mtu2_t_<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu2_t_<per, INT>::nfcr_t  mtu2_t_<per, INT>::NFCR;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU3 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu3_t_ : public mtu_t {

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
		typedef tcr_t_<0x000C1200> tcr_t;
		static tcr_t TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t_<0x000C124C> tcr2_t;
		static tcr2_t TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1z_t_<0x000C1202> tmdr1_t;
		static tmdr1_t TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t_<0x000C1204> tiorh_t;
		static tiorh_t TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t_<0x000C1205> tiorl_t;
		static tiorl_t TIORL;


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
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tiery_t_<0x000C1208> tier_t;
		static tier_t TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t_<0x000C122C> tsr_t;
		static tsr_t TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmy_t_<0x000C1238> tbtm_t;
		static tbtm_t TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1210> tcnt_t;
		static tcnt_t TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1218> tgra_t;
		static tgra_t TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C121A> tgrb_t;
		static tgrb_t TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1224> tgrc_t;
		static tgrc_t TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1226> tgrd_t;
		static tgrd_t TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1272> tgre_t;
		static tgre_t TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t_<0x000C1293> nfcr_t;
		static nfcr_t NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
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
	template <peripheral per, typename INT> typename mtu3_t_<per, INT>::tcr2_t  mtu3_t_<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu3_t_<per, INT>::tmdr1_t mtu3_t_<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu3_t_<per, INT>::tiorh_t mtu3_t_<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu3_t_<per, INT>::tior_t  mtu3_t_<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu3_t_<per, INT>::tier_t  mtu3_t_<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu3_t_<per, INT>::tsr_t   mtu3_t_<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu3_t_<per, INT>::tcnt_t  mtu3_t_<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu3_t_<per, INT>::tgra_t  mtu3_t_<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu3_t_<per, INT>::tgrb_t  mtu3_t_<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu3_t_<per, INT>::nfcr_t  mtu3_t_<per, INT>::NFCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU4 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu4_t_ : public mtu_t {

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
		typedef tcr_t_<0x000C1201> tcr_t;
		static tcr_t TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t_<0x000C124D> tcr2_t;
		static tcr2_t TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1z_t_<0x000C1203> tmdr1_t;
		static tmdr1_t TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t_<0x000C1206> tiorh_t;
		static tiorh_t TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t_<0x000C1207> tiorl_t;
		static tiorl_t TIORL;


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
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tierz_t_<0x000C1209> tier_t;
		static tier_t TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t_<0x000C122D> tsr_t;
		static tsr_t TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmy_t_<0x000C1239> tbtm_t;
		static tbtm_t TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1212> tcnt_t;
		static tcnt_t TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C121C> tgra_t;
		static tgra_t TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C121E> tgrb_t;
		static tgrb_t TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1228> tgrc_t;
		static tgrc_t TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C122A> tgrd_t;
		static tgrd_t TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1274> tgre_t;
		static tgre_t TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1276> tgrf_t;
		static tgrf_t TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t_<0x000C1294> nfcr_t;
		static nfcr_t NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadcr_t_ : public rw16_t<base> {
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
		typedef tadcr_t_<0x000C1240> tadcr_t;
		static tadcr_t TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1244> tadcora_t;
		static tadcora_t TADCORA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1246> tadcorb_t;
		static tadcorb_t TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1248> tadcobra_t;
		static tadcobra_t TADCOBRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C124A> tadcobrb_t;
		static tadcobrb_t TADCOBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
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
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tcr_t   mtu4_t_<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tcr2_t  mtu4_t_<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tmdr1_t mtu4_t_<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tiorh_t mtu4_t_<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tiorl_t mtu4_t_<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tior_t  mtu4_t_<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tier_t  mtu4_t_<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tsr_t   mtu4_t_<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tbtm_t  mtu4_t_<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tcnt_t  mtu4_t_<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tgra_t  mtu4_t_<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tgrb_t  mtu4_t_<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tgrc_t  mtu4_t_<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tgrd_t  mtu4_t_<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::tgre_t  mtu4_t_<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu4_t_<per, INT>::nfcr_t  mtu4_t_<per, INT>::NFCR;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU5 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu5_t_ {

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
		struct tcr_t_ : public rw8_t<base> {
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
		typedef tcr_t_<0x000C1C84> tcru_t;
		static tcru_t TCRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCRV）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t_<0x000C1C94> tcrv_t;
		static tcrv_t TCRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCRW）
		*/
		//-----------------------------------------------------------------//
		typedef tcr_t_<0x000C1CA4> tcrw_t;
		static tcrw_t TCRW;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIOR[UVW]）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tior_t_ : public rw8_t<base> {
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
		typedef tior_t_<0x000C1C86> tioru_t;
		static tioru_t TIORU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORV）
		*/
		//-----------------------------------------------------------------//
		typedef tior_t_<0x000C1C96> tiorv_t;
		static tiorv_t TIORV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ I/O コントロールレジスタ（TIORW）
		*/
		//-----------------------------------------------------------------//
		typedef tior_t_<0x000C1CA6> tiorw_t;
		static tiorw_t TIORW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコンペアマッチクリアレジスタ（TCNTCMPCLR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tcntcmpclr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CMPCLR5W;
			bit_rw_t<io_, bitpos::B1> CMPCLR5V;
			bit_rw_t<io_, bitpos::B2> CMPCLR5U;
		};
		typedef tcntcmpclr_t_<0x000C1CB6> tcntcmpclr_t;
		static tcntcmpclr_t TCNTCMPCLR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tier_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TGIE5W;
			bit_rw_t<io_, bitpos::B1> TGIE5V;
			bit_rw_t<io_, bitpos::B2> TGIE5U;
		};
		typedef tier_t_<0x000C1CB2> tier_t;
		static tier_t TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTU）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1C80> tcntu_t;
		static tcntu_t TCNTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTV）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1C90> tcntv_t;
		static tcntv_t TCNTV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1CA0> tcntw_t;
		static tcntw_t TCNTW;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRU）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1C82> tgru_t;
		static tgru_t TGRU;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRV）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1C92> tgrv_t;
		static tgrv_t TGRV;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRW）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1CA2> tgrw_t;
		static tgrw_t TGRW;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマスタートレジスタ（TSTR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tstr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> CSTW5;
			bit_rw_t<io_, bitpos::B1> CSTV5;
			bit_rw_t<io_, bitpos::B2> CSTU5;
		};
		typedef tstr_t_<0x000C1CB4> tstr_t;
		static tstr_t TSTR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ノイズフィルタコントロールレジスタ（NFCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct nfcr_t_ : public rw8_t<base> {
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
		typedef nfcr_t_<0x000C1A95> nfcr_t;
		static nfcr_t NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


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
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tcru_t       mtu5_t_<per, INT>::TCRU;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tcrv_t       mtu5_t_<per, INT>::TCRV;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tcrw_t       mtu5_t_<per, INT>::TCRW;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tioru_t      mtu5_t_<per, INT>::TIORU;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tiorv_t      mtu5_t_<per, INT>::TIORV;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tiorw_t      mtu5_t_<per, INT>::TIORW;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tcntcmpclr_t mtu5_t_<per, INT>::TCNTCMPCLR;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tier_t       mtu5_t_<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tcntu_t      mtu5_t_<per, INT>::TCNTU;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tcntv_t      mtu5_t_<per, INT>::TCNTV;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tcntw_t      mtu5_t_<per, INT>::TCNTW;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tgru_t       mtu5_t_<per, INT>::TGRU;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tgrv_t       mtu5_t_<per, INT>::TGRV;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tgrw_t       mtu5_t_<per, INT>::TGRW;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::tstr_t       mtu5_t_<per, INT>::TSTR;
	template <peripheral per, typename INT> typename mtu5_t_<per, INT>::nfcr_t       mtu5_t_<per, INT>::NFCR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU6 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu6_t_ : public mtu_t {

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
		typedef tcr_t_<0x000C1A00> tcr_t;
		static tcr_t TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t_<0x000C1A4C> tcr2_t;
		static tcr2_t TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1z_t_<0x000C1A02> tmdr1_t;
		static tmdr1_t TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t_<0x000C1A04> tiorh_t;
		static tiorh_t TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t_<0x000C1A05> tiorl_t;
		static tiorl_t TIORL;


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
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tiery_t_<0x000C1A08> tier_t;
		static tier_t TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t_<0x000C1A2C> tsr_t;
		static tsr_t TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmy_t_<0x000C1A38> tbtm_t;
		static tbtm_t TBTM;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイマシンクロクリアレジスタ（TSYCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct tsycr_t_ : public rw8_t<base> {
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
		typedef tsycr_t_<0x000C1A50> tsycr_t;
		static tsycr_t TSYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A10> tcnt_t;
		static tcnt_t TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A18> tgra_t;
		static tgra_t TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A1A> tgrb_t;
		static tgrb_t TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A24> tgrc_t;
		static tgrc_t TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A26> tgrd_t;
		static tgrd_t TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A72> tgre_t;
		static tgre_t TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t_<0x000C1A93> nfcr_t;
		static nfcr_t NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
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
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tcr_t   mtu6_t_<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tcr2_t  mtu6_t_<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tmdr1_t mtu6_t_<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tiorh_t mtu6_t_<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tiorl_t mtu6_t_<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tior_t  mtu6_t_<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tier_t  mtu6_t_<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tsr_t   mtu6_t_<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tbtm_t  mtu6_t_<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tsycr_t mtu6_t_<per, INT>::TSYCR;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tcnt_t  mtu6_t_<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tgra_t  mtu6_t_<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tgrb_t  mtu6_t_<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tgrc_t  mtu6_t_<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tgrd_t  mtu6_t_<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::tgre_t  mtu6_t_<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu6_t_<per, INT>::nfcr_t  mtu6_t_<per, INT>::NFCR;




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU7 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu7_t_ : public mtu_t {

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
		typedef tcr_t_<0x000C1A01> tcr_t;
		static tcr_t TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t_<0x000C1A4D> tcr2_t;
		static tcr2_t TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1z_t_<0x000C1A03> tmdr1_t;
		static tmdr1_t TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t_<0x000C1A06> tiorh_t;
		static tiorh_t TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t_<0x000C1A07> tiorl_t;
		static tiorl_t TIORL;


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
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tierz_t_<0x000C1A09> tier_t;
		static tier_t TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマステータスレジスタ（TSR）
		*/
		//-----------------------------------------------------------------//
		typedef tsr_t_<0x000C1A2D> tsr_t;
		static tsr_t TSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmy_t_<0x000C1A39> tbtm_t;
		static tbtm_t TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A12> tcnt_t;
		static tcnt_t TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A1C> tgra_t;
		static tgra_t TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A1E> tgrb_t;
		static tgrb_t TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A28> tgrc_t;
		static tgrc_t TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A2A> tgrd_t;
		static tgrd_t TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A74> tgre_t;
		static tgre_t TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A76> tgrf_t;
		static tgrf_t TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t_<0x000C1A94> nfcr_t;
		static nfcr_t NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求コントロールレジスタ（TADCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct tadcr_t_ : public rw16_t<base> {
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
		typedef tadcr_t_<0x000C1A40> tadcr_t;
		static tadcr_t TADCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A44> tadcora_t;
		static tadcora_t TADCORA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定レジスタ（TADCORB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A46> tadcorb_t;
		static tadcorb_t TADCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A48> tadcobra_t;
		static tadcobra_t TADCOBRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマ A/D 変換開始要求周期設定バッファレジスタ（TADCOBRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1A4A> tadcobrb_t;
		static tadcobrb_t TADCOBRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
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
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tcr_t      mtu7_t_<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tcr2_t     mtu7_t_<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tmdr1_t    mtu7_t_<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tiorh_t    mtu7_t_<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tiorl_t    mtu7_t_<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tior_t     mtu7_t_<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tier_t     mtu7_t_<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tsr_t      mtu7_t_<per, INT>::TSR;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tbtm_t     mtu7_t_<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tcnt_t     mtu7_t_<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tgra_t     mtu7_t_<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tgrb_t     mtu7_t_<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tgrc_t     mtu7_t_<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tgrd_t     mtu7_t_<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tgre_t     mtu7_t_<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tgrf_t     mtu7_t_<per, INT>::TGRF;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::nfcr_t     mtu7_t_<per, INT>::NFCR;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tadcr_t    mtu7_t_<per, INT>::TADCR;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tadcora_t  mtu7_t_<per, INT>::TADCORA;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tadcorb_t  mtu7_t_<per, INT>::TADCORB;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tadcobra_t mtu7_t_<per, INT>::TADCOBRA;
	template <peripheral per, typename INT> typename mtu7_t_<per, INT>::tadcobrb_t mtu7_t_<per, INT>::TADCOBRB;


#if defined(SIG_RX24T) || defined(SIG_RX66T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU9 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename INT>
	struct mtu9_t_ : public mtu_t {

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
		typedef tcr_t_<0x000C1580> tcr_t;
		static tcr_t TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ 2（TCR2）
		*/
		//-----------------------------------------------------------------//
		typedef tcr2_t_<0x000C15A8> tcr2_t;
		static tcr2_t TCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ 1（TMDR1）
		*/
		//-----------------------------------------------------------------//
		typedef tmdr1x_t_<0x000C1581> tmdr1_t;
		static tmdr1_t TMDR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORH）
		*/
		//-----------------------------------------------------------------//
		typedef tiorh_t_<0x000C1582> tiorh_t;
		static tiorh_t TIORH;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマ I/O コントロールレジスタ（TIORL）
		*/
		//-----------------------------------------------------------------//
		typedef tiorl_t_<0x000C1583> tiorl_t;
		static tiorl_t TIORL;


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
		static tior_t TIOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER）
		*/
		//-----------------------------------------------------------------//
		typedef tiery_t_<0x000C1584> tier_t;
		static tier_t TIER;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマインタラプトイネーブルレジスタ（TIER2）
		*/
		//-----------------------------------------------------------------//
		typedef tier2_t_<0x000C15A4> tier2_t;
		static tier2_t TIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマバッファ動作転送モードレジスタ（TBTM）
		*/
		//-----------------------------------------------------------------//
		typedef tbtmx_t_<0x000C15A6> tbtm_t;
		static tbtm_t TBTM;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1586> tcnt_t;
		static tcnt_t TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRA）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C1588> tgra_t;
		static tgra_t TGRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRB）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C158A> tgrb_t;
		static tgrb_t TGRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRC）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C158C> tgrc_t;
		static tgrc_t TGRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRD）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C158E> tgrd_t;
		static tgrd_t TGRD;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C15A0> tgre_t;
		static tgre_t TGRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマジェネラルレジスタ（TGRF）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x000C15A2> tgrf_t;
		static tgrf_t TGRF;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタコントロールレジスタ（NFCR）
		*/
		//-----------------------------------------------------------------//
		typedef nfcr_t_<0x000C1296> nfcr_t;
		static nfcr_t NFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
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
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tcr_t   mtu9_t_<per, INT>::TCR;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tcr2_t  mtu9_t_<per, INT>::TCR2;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tmdr1_t mtu9_t_<per, INT>::TMDR1;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tiorh_t mtu9_t_<per, INT>::TIORH;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tiorl_t mtu9_t_<per, INT>::TIORL;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tior_t  mtu9_t_<per, INT>::TIOR;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tier_t  mtu9_t_<per, INT>::TIER;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tier2_t mtu9_t_<per, INT>::TIER2;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tbtm_t  mtu9_t_<per, INT>::TBTM;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tcnt_t  mtu9_t_<per, INT>::TCNT;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tgra_t  mtu9_t_<per, INT>::TGRA;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tgrb_t  mtu9_t_<per, INT>::TGRB;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tgrc_t  mtu9_t_<per, INT>::TGRC;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tgrd_t  mtu9_t_<per, INT>::TGRD;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tgre_t  mtu9_t_<per, INT>::TGRE;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::tgrf_t  mtu9_t_<per, INT>::TGRF;
	template <peripheral per, typename INT> typename mtu9_t_<per, INT>::nfcr_t  mtu9_t_<per, INT>::NFCR;
#endif


#if defined(SIG_RX24T)
	typedef mtu0_t_<peripheral::MTU0, ICU::VECTOR> MTU0;
	typedef mtu1_t_<peripheral::MTU1, ICU::VECTOR> MTU1;
	typedef mtu2_t_<peripheral::MTU2, ICU::VECTOR> MTU2;
	typedef mtu3_t_<peripheral::MTU3, ICU::VECTOR> MTU3;
	typedef mtu4_t_<peripheral::MTU4, ICU::VECTOR> MTU4;
	typedef mtu5_t_<peripheral::MTU5, ICU::VECTOR> MTU5;
	typedef mtu6_t_<peripheral::MTU6, ICU::VECTOR> MTU6;
	typedef mtu7_t_<peripheral::MTU7, ICU::VECTOR> MTU7;
	typedef mtu9_t_<peripheral::MTU9, ICU::VECTOR> MTU9;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	typedef mtu0_t_<peripheral::MTU0, ICU::VECTOR_SELA> MTU0;
	typedef mtu1_t_<peripheral::MTU1, ICU::VECTOR_SELA> MTU1;
	typedef mtu2_t_<peripheral::MTU2, ICU::VECTOR_SELA> MTU2;
	typedef mtu3_t_<peripheral::MTU3, ICU::VECTOR_SELA> MTU3;
	typedef mtu4_t_<peripheral::MTU4, ICU::VECTOR_SELA> MTU4;
	typedef mtu5_t_<peripheral::MTU5, ICU::VECTOR_SELA> MTU5;
	typedef mtu6_t_<peripheral::MTU6, ICU::VECTOR_SELA> MTU6;
	typedef mtu7_t_<peripheral::MTU7, ICU::VECTOR_SELA> MTU7;
#elif defined(SIG_RX66T)
	typedef mtu0_t_<peripheral::MTU0, ICU::VECTOR_SELA> MTU0;
	typedef mtu1_t_<peripheral::MTU1, ICU::VECTOR_SELA> MTU1;
	typedef mtu2_t_<peripheral::MTU2, ICU::VECTOR_SELA> MTU2;
	typedef mtu3_t_<peripheral::MTU3, ICU::VECTOR_SELA> MTU3;
	typedef mtu4_t_<peripheral::MTU4, ICU::VECTOR_SELA> MTU4;
	typedef mtu5_t_<peripheral::MTU5, ICU::VECTOR_SELA> MTU5;
	typedef mtu6_t_<peripheral::MTU6, ICU::VECTOR_SELA> MTU6;
	typedef mtu7_t_<peripheral::MTU7, ICU::VECTOR_SELA> MTU7;
	typedef mtu9_t_<peripheral::MTU9, ICU::VECTOR_SELA> MTU9;
#endif
}
