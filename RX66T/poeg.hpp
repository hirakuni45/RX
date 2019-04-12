#pragma once
//=====================================================================//
/*!	@file
	@brief	RX66T グループ・POEG 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief   GPTW 用ポートアウトプットイネーブル (POEG)
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct poeg_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  POEG グループ n 設定レジスタ (POEGGn) (n = A ～ D)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poeggn_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      PIDF;
			bit_rw_t <io_, bitpos::B1>      IOCF;
			bit_rw_t <io_, bitpos::B2>      OSTPF;
			bit_rw_t <io_, bitpos::B3>      SSF;
			bit_rw_t <io_, bitpos::B4>      PIDE;
			bit_rw_t <io_, bitpos::B5>      IOCE;
			bit_rw_t <io_, bitpos::B6>      OSTPE;

			bit_rw_t <io_, bitpos::B8>      CDRE0;
			bit_rw_t <io_, bitpos::B9>      CDRE1;
			bit_rw_t <io_, bitpos::B10>     CDRE2;
			bit_rw_t <io_, bitpos::B11>     CDRE3;
			bit_rw_t <io_, bitpos::B12>     CDRE4;
			bit_rw_t <io_, bitpos::B13>     CDRE5;

			bit_rw_t <io_, bitpos::B28>     INV;
			bit_rw_t <io_, bitpos::B29>     NFEN;
			bits_rw_t<io_, bitpos::B30, 2>  NFCS;
		};
		static poeggn_t<0x0009E000> POEGGA;
		static poeggn_t<0x0009E100> POEGGB;
		static poeggn_t<0x0009E200> POEGGC;
		static poeggn_t<0x0009E300> POEGGD;


		//-----------------------------------------------------------------//
		/*!
			@brief  GPTW 出力停止制御グループ n 書き込み保護レジスタ (GTONCWPn)(n = A~D)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct gtoncwpn_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      WP;

			bits_rw_t<io_, bitpos::B8, 8>   PRKEY;
		};
		static gtoncwpn_t<0x0009E040> GTONCWPA;
		static gtoncwpn_t<0x0009E140> GTONCWPB;
		static gtoncwpn_t<0x0009E240> GTONCWPC;
		static gtoncwpn_t<0x0009E340> GTONCWPD;


		//-----------------------------------------------------------------//
		/*!
			@brief  GPTW 出力停止制御グループ n コントロールレジスタ (GTONCCRn)(n = A~D)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct gtonccrn_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     NE;

			bits_rw_t<io_, bitpos::B4, 4>  NFS;
			bit_rw_t <io_, bitpos::B8>     NFV;
		};
		static gtonccrn_t<0x0009E044> GTONCCRA;
		static gtonccrn_t<0x0009E144> GTONCCRB;
		static gtonccrn_t<0x0009E244> GTONCCRC;
		static gtonccrn_t<0x0009E344> GTONCCRD;
	};

	typedef poeg_t POEG;
}
