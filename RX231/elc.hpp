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
		typedef elcr_t<base + 0x00> ELCR_;
		static  ELCR_ ELCR;


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
		typedef elsr_t<base + 0x02> ELSR1_;
		static  ELSR1_ ELSR1;
		typedef elsr_t<base + 0x03> ELSR2_;
		static  ELSR2_ ELSR2;
		typedef elsr_t<base + 0x04> ELSR3_;
		static  ELSR3_ ELSR3;
		typedef elsr_t<base + 0x05> ELSR4_;
		static  ELSR4_ ELSR4;

		typedef elsr_t<base + 0x08> ELSR7_;
		static  ELSR7_ ELSR7;
		typedef elsr_t<base + 0x09> ELSR8_;
		static  ELSR8_ ELSR8;

		typedef elsr_t<base + 0x0B> ELSR10_;
		static  ELSR10_ ELSR10;

		typedef elsr_t<base + 0x0D> ELSR12_;
		static  ELSR12_ ELSR12;

		typedef elsr_t<base + 0x0F> ELSR14_;
		static  ELSR14_ ELSR14;
		typedef elsr_t<base + 0x10> ELSR15_;
		static  ELSR15_ ELSR15;
		typedef elsr_t<base + 0x11> ELSR16_;
		static  ELSR16_ ELSR16;

		typedef elsr_t<base + 0x13> ELSR18_;
		static  ELSR18_ ELSR18;
		typedef elsr_t<base + 0x14> ELSR19_;
		static  ELSR19_ ELSR19;
		typedef elsr_t<base + 0x15> ELSR20_;
		static  ELSR20_ ELSR20;
		typedef elsr_t<base + 0x16> ELSR21_;
		static  ELSR21_ ELSR21;
		typedef elsr_t<base + 0x17> ELSR22_;
		static  ELSR22_ ELSR22;
		typedef elsr_t<base + 0x18> ELSR23_;
		static  ELSR23_ ELSR23;
		typedef elsr_t<base + 0x19> ELSR24_;
		static  ELSR24_ ELSR24;
		typedef elsr_t<base + 0x1A> ELSR25_;
		static  ELSR25_ ELSR25;
		typedef elsr_t<base + 0x1B> ELSR26_;
		static  ELSR26_ ELSR26;
		typedef elsr_t<base + 0x1C> ELSR27_;
		static  ELSR27_ ELSR27;
		typedef elsr_t<base + 0x1D> ELSR28_;
		static  ELSR28_ ELSR28;
		typedef elsr_t<base + 0x1E> ELSR29_;
		static  ELSR29_ ELSR29;


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
		typedef elopa_t<base + 0x1F> ELOPA_;
		static  ELOPA_ ELOPA;


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
		typedef elopb_t<base + 0x20> ELOPB_;
		static  ELOPB_ ELOPB;


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
		typedef elopc_t<base + 0x21> ELOPC_;
		static  ELOPC_ ELOPC;


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
		typedef elopd_t<base + 0x22> ELOPD_;
		static  ELOPD_ ELOPD;


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
		typedef pgrn_t<base + 0x23> PGR1_;
		static  PGR1_ PGR1;
		typedef pgrn_t<base + 0x24> PGR2_;
		static  PGR2_ PGR2;


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
		typedef pgcn_t<base + 0x25> PGC1_;
		static  PGC1_ PGC1;
		typedef pgcn_t<base + 0x26> PGC2_;
		static  PGC2_ PGC2;


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
		typedef pdbfn_t<base + 0x27> PDBF1_;
		static  PDBF1_ PDBF1;
		typedef pdbfn_t<base + 0x28> PDBF2_;
		static  PDBF2_ PDBF2;


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
		typedef peln_t<base + 0x29> PEL0_;
		static  PEL0_ PEL0;
		typedef peln_t<base + 0x2A> PEL1_;
		static  PEL1_ PEL1;
		typedef peln_t<base + 0x2B> PEL2_;
		static  PEL2_ PEL2;
		typedef peln_t<base + 0x2C> PEL3_;
		static  PEL3_ PEL3;


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
		typedef elsegr_t<base + 0x2D> ELSEGR_;
		static  ELSEGR_ ELSEGR;
	};
	template <uint32_t base> typename elc_t<base>::ELCR_   elc_t<base>::ELCR;
	template <uint32_t base> typename elc_t<base>::ELSR1_  elc_t<base>::ELSR1;
	template <uint32_t base> typename elc_t<base>::ELSR2_  elc_t<base>::ELSR2;
	template <uint32_t base> typename elc_t<base>::ELSR3_  elc_t<base>::ELSR3;
	template <uint32_t base> typename elc_t<base>::ELSR4_  elc_t<base>::ELSR4;
	template <uint32_t base> typename elc_t<base>::ELSR7_  elc_t<base>::ELSR7;
	template <uint32_t base> typename elc_t<base>::ELSR8_  elc_t<base>::ELSR8;
	template <uint32_t base> typename elc_t<base>::ELSR10_ elc_t<base>::ELSR10;
	template <uint32_t base> typename elc_t<base>::ELSR12_ elc_t<base>::ELSR12;
	template <uint32_t base> typename elc_t<base>::ELSR14_ elc_t<base>::ELSR14;
	template <uint32_t base> typename elc_t<base>::ELSR15_ elc_t<base>::ELSR15;
	template <uint32_t base> typename elc_t<base>::ELSR16_ elc_t<base>::ELSR16;
	template <uint32_t base> typename elc_t<base>::ELSR18_ elc_t<base>::ELSR18;
	template <uint32_t base> typename elc_t<base>::ELSR19_ elc_t<base>::ELSR19;
	template <uint32_t base> typename elc_t<base>::ELSR20_ elc_t<base>::ELSR20;
	template <uint32_t base> typename elc_t<base>::ELSR21_ elc_t<base>::ELSR21;
	template <uint32_t base> typename elc_t<base>::ELSR22_ elc_t<base>::ELSR22;
	template <uint32_t base> typename elc_t<base>::ELSR23_ elc_t<base>::ELSR23;
	template <uint32_t base> typename elc_t<base>::ELSR24_ elc_t<base>::ELSR24;
	template <uint32_t base> typename elc_t<base>::ELSR25_ elc_t<base>::ELSR25;
	template <uint32_t base> typename elc_t<base>::ELSR26_ elc_t<base>::ELSR26;
	template <uint32_t base> typename elc_t<base>::ELSR27_ elc_t<base>::ELSR27;
	template <uint32_t base> typename elc_t<base>::ELSR28_ elc_t<base>::ELSR28;
	template <uint32_t base> typename elc_t<base>::ELSR29_ elc_t<base>::ELSR29;
	template <uint32_t base> typename elc_t<base>::ELOPA_  elc_t<base>::ELOPA;
	template <uint32_t base> typename elc_t<base>::ELOPB_  elc_t<base>::ELOPB;
	template <uint32_t base> typename elc_t<base>::ELOPC_  elc_t<base>::ELOPC;
	template <uint32_t base> typename elc_t<base>::ELOPD_  elc_t<base>::ELOPD;
	template <uint32_t base> typename elc_t<base>::PGR1_   elc_t<base>::PGR1;
	template <uint32_t base> typename elc_t<base>::PGR2_   elc_t<base>::PGR2;
	template <uint32_t base> typename elc_t<base>::PGC1_   elc_t<base>::PGC1;
	template <uint32_t base> typename elc_t<base>::PGC2_   elc_t<base>::PGC2;
	template <uint32_t base> typename elc_t<base>::PDBF1_  elc_t<base>::PDBF1;
	template <uint32_t base> typename elc_t<base>::PDBF2_  elc_t<base>::PDBF2;
	template <uint32_t base> typename elc_t<base>::PEL0_   elc_t<base>::PEL0;
	template <uint32_t base> typename elc_t<base>::PEL1_   elc_t<base>::PEL1;
	template <uint32_t base> typename elc_t<base>::PEL2_   elc_t<base>::PEL2;
	template <uint32_t base> typename elc_t<base>::PEL3_   elc_t<base>::PEL3;
	template <uint32_t base> typename elc_t<base>::ELSEGR_ elc_t<base>::ELSEGR;

	typedef elc_t<0x0008'B100> ELC;
}
