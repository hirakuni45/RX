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
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct elc_t {

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
		static elcr_t<base + 0x00> ERCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  イベントリンク設定レジスタ n（ELSRn）@n
					（n = 0、3、4、7、10 ～ 13、15、16、18 ～ 28、33、35 ～ 38、41 ～ 45）
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0x01>  ELSR0;
		static rw8_t<base + 0x04>  ELSR3;
		static rw8_t<base + 0x05>  ELSR4;
		static rw8_t<base + 0x08>  ELSR7;
		static rw8_t<base + 0x0B>  ELSR10;
		static rw8_t<base + 0x0C>  ELSR11;
		static rw8_t<base + 0x0D>  ELSR12;
		static rw8_t<base + 0x0E>  ELSR13;
		static rw8_t<base + 0x10>  ELSR15;
		static rw8_t<base + 0x11>  ELSR16;
		static rw8_t<base + 0x13>  ELSR18;
		static rw8_t<base + 0x14>  ELSR19;
		static rw8_t<base + 0x15>  ELSR20;
		static rw8_t<base + 0x16>  ELSR21;
		static rw8_t<base + 0x17>  ELSR22;
		static rw8_t<base + 0x18>  ELSR23;
		static rw8_t<base + 0x19>  ELSR24;
		static rw8_t<base + 0x1A>  ELSR25;
		static rw8_t<base + 0x1B>  ELSR26;
		static rw8_t<base + 0x1C>  ELSR27;
		static rw8_t<base + 0x1D>  ELSR28;
		static rw8_t<base + 0x31>  ELSR33;
		static rw8_t<base + 0x33>  ELSR35;
		static rw8_t<base + 0x34>  ELSR36;
		static rw8_t<base + 0x35>  ELSR37;
		static rw8_t<base + 0x36>  ELSR38;
		static rw8_t<base + 0x39>  ELSR41;
		static rw8_t<base + 0x3A>  ELSR42;
		static rw8_t<base + 0x3B>  ELSR43;
		static rw8_t<base + 0x3C>  ELSR44;
		static rw8_t<base + 0x3D>  ELSR45;


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
		static elopa_t<base + 0x1F> ELOPA;


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
		static elopb_t<base + 0x20> ELOPB;


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
		static elopc_t<base + 0x21> ELOPC;


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
		static elopd_t<base + 0x22> ELOPD;


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
		static elopf_t<base + 0x3F> ELOPF;


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
		static eloph_t<base + 0x41> ELOPH;


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
		static elopi_t<base + 0x42> ELOPI;


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
		static elopj_t<base + 0x43> ELOPJ;


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
		static pgrn_t<base + 0x23> PGR1;
		static pgrn_t<base + 0x24> PGR2;


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
		static pgcn_t<base + 0x25> PGC1;
		static pgcn_t<base + 0x26> PGC2;


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
		static pdbfn_t<base + 0x27> PDBF1;
		static pdbfn_t<base + 0x28> PDBF2;


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
		static peln_t<base + 0x29> PEL0;
		static peln_t<base + 0x2A> PEL1;
		static peln_t<base + 0x2B> PEL2;
		static peln_t<base + 0x2C> PEL3;


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
		static elsegr_t<base + 0x2D> ELSEGR;
	};
	typedef elc_t<0x0008B100> ELC;
}
