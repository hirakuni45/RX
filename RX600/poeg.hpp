#pragma once
//=========================================================================//
/*!	@file
	@brief	GPTW 用ポートアウトプットイネーブル (POEG)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
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
		static inline poegg_t<base + 0x0000> POEGGA;
		static inline poegg_t<base + 0x0100> POEGGB;
		static inline poegg_t<base + 0x0200> POEGGC;
		static inline poegg_t<base + 0x0300> POEGGD;

#if defined(SIG_RX260) || defined(SIG_RX261)
#else
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
		static inline gtoncwpn_t<base + 0x0040> GTONCWPA;
		static inline gtoncwpn_t<base + 0x0140> GTONCWPB;
		static inline gtoncwpn_t<base + 0x0240> GTONCWPC;
		static inline gtoncwpn_t<base + 0x0340> GTONCWPD;


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
		static inline gtonccrn_t<base + 0x0044> GTONCCRA;
		static inline gtonccrn_t<base + 0x0144> GTONCCRB;
		static inline gtonccrn_t<base + 0x0244> GTONCCRC;
		static inline gtonccrn_t<base + 0x0344> GTONCCRD;
#endif
	};
	typedef poeg_t<0x0009'E000, peripheral::POEG> POEG;
}
