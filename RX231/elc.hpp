#pragma once
//=========================================================================//
/*!	@file
	@brief	RX231 グループ・ELC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  イベントリンクコントローラ（ELC）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct elc_t {

		static constexpr auto PERIPHERAL = peripheral::ELC;	///< ペリフェラル型

		//-----------------------------------------------------------------//
		/*!
			@brief  イベントリンクコントロールレジスタ（ELCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7>  ELCON;
		};
		static inline elcr_t<base + 0x00> ELCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  イベントリンク設定レジスタ n (ELSRn) @n
					(n = 1 ～ 4, 7, 8, 10, 12, 14 ～ 16, 18 ～ 29)
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8> ELS;
		};
		static inline elsr_t<base + 0x02> ELSR1;
		static inline elsr_t<base + 0x03> ELSR2;
		static inline elsr_t<base + 0x04> ELSR3;
		static inline elsr_t<base + 0x05> ELSR4;

		static inline elsr_t<base + 0x08> ELSR7;
		static inline elsr_t<base + 0x09> ELSR8;

		static inline elsr_t<base + 0x0B> ELSR10;

		static inline elsr_t<base + 0x0D> ELSR12;

		static inline elsr_t<base + 0x0F> ELSR14;
		static inline elsr_t<base + 0x10> ELSR15;
		static inline elsr_t<base + 0x11> ELSR16;

		static inline elsr_t<base + 0x13> ELSR18;
		static inline elsr_t<base + 0x14> ELSR19;
		static inline elsr_t<base + 0x15> ELSR20;
		static inline elsr_t<base + 0x16> ELSR21;
		static inline elsr_t<base + 0x17> ELSR22;
		static inline elsr_t<base + 0x18> ELSR23;
		static inline elsr_t<base + 0x19> ELSR24;
		static inline elsr_t<base + 0x1A> ELSR25;
		static inline elsr_t<base + 0x1B> ELSR26;
		static inline elsr_t<base + 0x1C> ELSR27;
		static inline elsr_t<base + 0x1D> ELSR28;
		static inline elsr_t<base + 0x1E> ELSR29;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ A（ELOPA）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopa_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B2, 2>  MTU1MD;
			bits_rw_t<io_, bitpos::B4, 2>  MTU2MD;
			bits_rw_t<io_, bitpos::B6, 2>  MTU3MD;
		};
		static inline elopa_t<base + 0x1F> ELOPA;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ B（ELOPB）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopb_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  MTU4MD;
		};
		static inline elopb_t<base + 0x20> ELOPB;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ C（ELOPC）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopc_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B2, 2>  CMT1MD;
			bits_rw_t<io_, bitpos::B4, 2>  LPTMD;
		};
		static inline elopc_t<base + 0x21> ELOPC;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ D（ELOPD）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopd_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  TMR0MD;

			bits_rw_t<io_, bitpos::B4, 2>  TMR2MD;
		};
		static inline elopd_t<base + 0x22> ELOPD;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートグループ指定レジスタ n (PGRn) (n = 1, 2)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pgrn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  PGR0;
			bit_rw_t<io_, bitpos::B1>  PGR1;
			bit_rw_t<io_, bitpos::B2>  PGR2;
			bit_rw_t<io_, bitpos::B3>  PGR3;
			bit_rw_t<io_, bitpos::B4>  PGR4;
			bit_rw_t<io_, bitpos::B5>  PGR5;
			bit_rw_t<io_, bitpos::B6>  PGR6;
			bit_rw_t<io_, bitpos::B7>  PGR7;
		};
		static inline pgrn_t<base + 0x23> PGR1;
		static inline pgrn_t<base + 0x24> PGR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートグループコントロールレジスタ n (PGCn) (n = 1, 2)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pgcn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  PGC;
			bit_rw_t <io_, bitpos::B2>     PGCOVE;

			bits_rw_t<io_, bitpos::B4, 3>  PGCO;
		};
		static inline pgcn_t<base + 0x25> PGC1;
		static inline pgcn_t<base + 0x26> PGC2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートバッファレジスタ n (PDBFn) (n = 1, 2)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pdbfn_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  PDBF0;
			bit_rw_t<io_, bitpos::B1>  PDBF1;
			bit_rw_t<io_, bitpos::B2>  PDBF2;
			bit_rw_t<io_, bitpos::B3>  PDBF3;
			bit_rw_t<io_, bitpos::B4>  PDBF4;
			bit_rw_t<io_, bitpos::B5>  PDBF5;
			bit_rw_t<io_, bitpos::B6>  PDBF6;
			bit_rw_t<io_, bitpos::B7>  PDBF7;
		};
		static inline pdbfn_t<base + 0x27> PDBF1;
		static inline pdbfn_t<base + 0x28> PDBF2;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベント接続ポート指定レジスタ m (PELm) (m = 0 ～ 3)
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct peln_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  PSB;
			bits_rw_t<io_, bitpos::B3, 2>  PSP;
			bits_rw_t<io_, bitpos::B5, 2>  PSM;
		};
		static inline peln_t<base + 0x29> PEL0;
		static inline peln_t<base + 0x2A> PEL1;
		static inline peln_t<base + 0x2B> PEL2;
		static inline peln_t<base + 0x2C> PEL3;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクソフトウェアイベント発生レジスタ（ELSEGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elsegr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SEG;	// write-only
			bit_rw_t<io_, bitpos::B6>  WE;

			bit_rw_t<io_, bitpos::B7>  WI;	// write-only
		};
		static inline elsegr_t<base + 0x2D> ELSEGR;
	};

	static inline elc_t<0x0008'B100> ELC;
}
