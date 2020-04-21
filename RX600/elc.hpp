#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・ELC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  イベントリンクコントローラ（ELC）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct elc_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型

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
		typedef elcr_t<base + 0x00> ERCR_;
		static  ERCR_ ERCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  イベントリンク設定レジスタ n（ELSRn）@n
					（n = 0、3、4、7、10 ～ 13、15、16、18 ～ 28、33、35 ～ 38、41 ～ 45）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x01>  ELSR0_;
		static  ELSR0_ ELSR0;
		typedef rw8_t<base + 0x04>  ELSR3_;
		static  ELSR3_ ELSR3;
		typedef rw8_t<base + 0x05>  ELSR4_;
		static  ELSR4_ ELSR4;
		typedef rw8_t<base + 0x08>  ELSR7_;
		static  ELSR7_ ELSR7;
		typedef rw8_t<base + 0x0B>  ELSR10_;
		static  ELSR10_ ELSR10;
		typedef rw8_t<base + 0x0C>  ELSR11_;
		static  ELSR11_ ELSR11;
		typedef rw8_t<base + 0x0D>  ELSR12_;
		static  ELSR12_ ELSR12;
		typedef rw8_t<base + 0x0E>  ELSR13_;
		static  ELSR13_ ELSR13;
		typedef rw8_t<base + 0x10>  ELSR15_;
		static  ELSR15_ ELSR15;
		typedef rw8_t<base + 0x11>  ELSR16_;
		static  ELSR16_ ELSR16;
		typedef rw8_t<base + 0x13>  ELSR18_;
		static  ELSR18_ ELSR18;
		typedef rw8_t<base + 0x14>  ELSR19_;
		static  ELSR19_ ELSR19;
		typedef rw8_t<base + 0x15>  ELSR20_;
		static  ELSR20_ ELSR20;
		typedef rw8_t<base + 0x16>  ELSR21_;
		static  ELSR21_ ELSR21;
		typedef rw8_t<base + 0x17>  ELSR22_;
		static  ELSR22_ ELSR22;
		typedef rw8_t<base + 0x18>  ELSR23_;
		static  ELSR23_ ELSR23;
		typedef rw8_t<base + 0x19>  ELSR24_;
		static  ELSR24_ ELSR24;
		typedef rw8_t<base + 0x1A>  ELSR25_;
		static  ELSR25_ ELSR25;
		typedef rw8_t<base + 0x1B>  ELSR26_;
		static  ELSR26_ ELSR26;
		typedef rw8_t<base + 0x1C>  ELSR27_;
		static  ELSR27_ ELSR27;
		typedef rw8_t<base + 0x1D>  ELSR28_;
		static  ELSR28_ ELSR28;
		typedef rw8_t<base + 0x31>  ELSR33_;
		static  ELSR33_ ELSR33;
		typedef rw8_t<base + 0x33>  ELSR35_;
		static  ELSR35_ ELSR35;
		typedef rw8_t<base + 0x34>  ELSR36_;
		static  ELSR36_ ELSR36;
		typedef rw8_t<base + 0x35>  ELSR37_;
		static  ELSR37_ ELSR37;
		typedef rw8_t<base + 0x36>  ELSR38_;
		static  ELSR38_ ELSR38;
		typedef rw8_t<base + 0x39>  ELSR41_;
		static  ELSR41_ ELSR41;
		typedef rw8_t<base + 0x3A>  ELSR42_;
		static  ELSR42_ ELSR42;
		typedef rw8_t<base + 0x3B>  ELSR43_;
		static  ELSR43_ ELSR43;
		typedef rw8_t<base + 0x3C>  ELSR44_;
		static  ELSR44_ ELSR44;
		typedef rw8_t<base + 0x3D>  ELSR45_;
		static  ELSR45_ ELSR45;


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

			bits_rw_t<io_, bitpos::B0, 2>  MTU0MD;
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
			bits_rw_t<io_, bitpos::B2, 2>  TMR1MD;
			bits_rw_t<io_, bitpos::B4, 2>  TMR2MD;
			bits_rw_t<io_, bitpos::B6, 2>  TMR3MD;
		};
		typedef elopd_t<base + 0x22> ELOPD_;
		static  ELOPD_ ELOPD;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ F（ELOPF）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopf_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  TPU0MD;
			bits_rw_t<io_, bitpos::B2, 2>  TPU1MD;
			bits_rw_t<io_, bitpos::B4, 2>  TPU2MD;
			bits_rw_t<io_, bitpos::B6, 2>  TPU3MD;
		};
		typedef elopf_t<base + 0x3F> ELOPF_;
		static  ELOPF_ ELOPF;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ H（ELOPH）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct eloph_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CMTW0MD;
		};
		typedef eloph_t<base + 0x41> ELOPH_;
		static  ELOPH_ ELOPH;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ I（ELOPI）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopi_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  GPT0MD;
			bits_rw_t<io_, bitpos::B4, 3>  GPT1MD;
		};
		typedef elopi_t<base + 0x42> ELOPI_;
		static  ELOPI_ ELOPI;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ J（ELOPJ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopj_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  GPT2MD;
			bits_rw_t<io_, bitpos::B4, 3>  GPT3MD;
		};
		typedef elopj_t<base + 0x43> ELOPJ_;
		static  ELOPJ_ ELOPJ;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートグループ指定レジスタ n（PGRn）（n = 1、2）
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
			@brief	ポートグループコントロールレジスタ n（PGCn）（n = 1、2）
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
			@brief	ポートバッファレジスタ n（PDBFn）（n = 1、2）
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
			@brief	イベント接続ポート指定レジスタ n（PELn）（n = 0 ～ 3）
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
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ERCR_ elc_t<base, per>::ERCR;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR0_ elc_t<base, per>::ELSR0;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR3_ elc_t<base, per>::ELSR3;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR4_ elc_t<base, per>::ELSR4;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR7_ elc_t<base, per>::ELSR7;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR10_ elc_t<base, per>::ELSR10;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR11_ elc_t<base, per>::ELSR11;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR12_ elc_t<base, per>::ELSR12;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR13_ elc_t<base, per>::ELSR13;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR15_ elc_t<base, per>::ELSR15;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR16_ elc_t<base, per>::ELSR16;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR18_ elc_t<base, per>::ELSR18;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR19_ elc_t<base, per>::ELSR19;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR20_ elc_t<base, per>::ELSR20;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR21_ elc_t<base, per>::ELSR21;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR22_ elc_t<base, per>::ELSR22;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR23_ elc_t<base, per>::ELSR23;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR24_ elc_t<base, per>::ELSR24;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR25_ elc_t<base, per>::ELSR25;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR26_ elc_t<base, per>::ELSR26;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR27_ elc_t<base, per>::ELSR27;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR28_ elc_t<base, per>::ELSR28;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR33_ elc_t<base, per>::ELSR33;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR35_ elc_t<base, per>::ELSR35;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR36_ elc_t<base, per>::ELSR36;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR37_ elc_t<base, per>::ELSR37;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR38_ elc_t<base, per>::ELSR38;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR41_ elc_t<base, per>::ELSR41;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR42_ elc_t<base, per>::ELSR42;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR43_ elc_t<base, per>::ELSR43;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR44_ elc_t<base, per>::ELSR44;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSR45_ elc_t<base, per>::ELSR45;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELOPA_ elc_t<base, per>::ELOPA;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELOPB_ elc_t<base, per>::ELOPB;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELOPC_ elc_t<base, per>::ELOPC;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELOPD_ elc_t<base, per>::ELOPD;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELOPF_ elc_t<base, per>::ELOPF;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELOPH_ elc_t<base, per>::ELOPH;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELOPI_ elc_t<base, per>::ELOPI;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELOPJ_ elc_t<base, per>::ELOPJ;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::PGR1_ elc_t<base, per>::PGR1;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::PGR2_ elc_t<base, per>::PGR2;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::PGC1_ elc_t<base, per>::PGC1;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::PGC2_ elc_t<base, per>::PGC2;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::PDBF1_ elc_t<base, per>::PDBF1;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::PDBF2_ elc_t<base, per>::PDBF2;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::PEL0_ elc_t<base, per>::PEL0;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::PEL1_ elc_t<base, per>::PEL1;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::PEL2_ elc_t<base, per>::PEL2;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::PEL3_ elc_t<base, per>::PEL3;
	template <uint32_t base, peripheral per> typename elc_t<base, per>::ELSEGR_ elc_t<base, per>::ELSEGR;


	typedef elc_t<0x0008B100, peripheral::ELC> ELC;
}
