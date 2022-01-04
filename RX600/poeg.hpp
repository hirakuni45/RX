#pragma once
//=====================================================================//
/*!	@file
	@brief	GPTW 用ポートアウトプットイネーブル (POEG)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPTW 用ポートアウトプットイネーブル (POEG)
		@param[in]	base	モジュール先頭アドレス
		@param[in]	per	ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct poeg_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief	POEG グループ n 設定レジスタ (POEGGn) (n = A ～ D)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct poegg_t : public rw32_t<addr> {
			typedef rw32_t<addr> io_;
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

			bit_rw_t <io_, bitpos::B16>     ST;

			bit_rw_t <io_, bitpos::B28>     INV;
			bit_rw_t <io_, bitpos::B29>     NFEN;
			bits_rw_t<io_, bitpos::B30, 2>  NFCS;
		};
		typedef poegg_t<base + 0x0000> POEGGA_;
		static POEGGA_ POEGGA;
		typedef poegg_t<base + 0x0100> POEGGB_;
		static POEGGB_ POEGGB;
		typedef poegg_t<base + 0x0200> POEGGC_;
		static POEGGC_ POEGGC;
		typedef poegg_t<base + 0x0300> POEGGD_;
		static POEGGD_ POEGGD;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW 出力停止制御グループ n 書き込み保護レジスタ (GTONCWPn)(n = A~D)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtoncwpn_t : public rw16_t<addr> {
			typedef rw16_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      WP;

			bits_rw_t<io_, bitpos::B8, 8>   KEY;
		};
		typedef gtoncwpn_t<base + 0x0040> GTONCWPA_;
		static GTONCWPA_ GTONCWPA;
		typedef gtoncwpn_t<base + 0x0140> GTONCWPB_;
		static GTONCWPB_ GTONCWPB;
		typedef gtoncwpn_t<base + 0x0240> GTONCWPC_;
		static GTONCWPC_ GTONCWPC;
		typedef gtoncwpn_t<base + 0x0340> GTONCWPD_;
		static GTONCWPD_ GTONCWPD;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW 出力停止制御グループ n コントロールレジスタ (GTONCCRn)(n = A~D)
			@param[in]	addr	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t addr>
		struct gtonccrn_t : public rw16_t<addr> {
			typedef rw16_t<addr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      NE;

			bits_rw_t<io_, bitpos::B4, 4>   NFS;
			bit_rw_t <io_, bitpos::B8>      NFV;
		};
		typedef gtonccrn_t<base + 0x0044> GTONCCRA_;
		static GTONCCRA_ GTONCCRA;
		typedef gtonccrn_t<base + 0x0144> GTONCCRB_;
		static GTONCCRB_ GTONCCRB;
		typedef gtonccrn_t<base + 0x0244> GTONCCRC_;
		static GTONCCRC_ GTONCCRC;
		typedef gtonccrn_t<base + 0x0344> GTONCCRD_;
		static GTONCCRD_ GTONCCRD;
	};
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::POEGGA_ poeg_t<base, per>::POEGGA;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::POEGGB_ poeg_t<base, per>::POEGGB;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::POEGGC_ poeg_t<base, per>::POEGGC;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::POEGGD_ poeg_t<base, per>::POEGGD;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::GTONCWPA_ poeg_t<base, per>::GTONCWPA;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::GTONCWPB_ poeg_t<base, per>::GTONCWPB;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::GTONCWPC_ poeg_t<base, per>::GTONCWPC;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::GTONCWPD_ poeg_t<base, per>::GTONCWPD;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::GTONCCRA_ poeg_t<base, per>::GTONCCRA;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::GTONCCRB_ poeg_t<base, per>::GTONCCRB;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::GTONCCRC_ poeg_t<base, per>::GTONCCRC;
	template <uint32_t base, peripheral per> typename poeg_t<base, per>::GTONCCRD_ poeg_t<base, per>::GTONCCRD;

	typedef poeg_t<0x0009E000, peripheral::POEG> POEG;
}
