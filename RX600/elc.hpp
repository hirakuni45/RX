#pragma once
//=========================================================================//
/*!	@file
	@brief	Event Link Controller / イベントリンクコントローラ
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ELC class
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct elc_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

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
			@brief  イベントリンク設定レジスタ n（ELSRn） @n
					（n = 0、3、4、7、8、10 ～ 15、16、18 ～ 28、33、35 ～ 38、41 ～ 45）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x01>  ELSR0;
		static inline rw8_t<base + 0x04>  ELSR3;
		static inline rw8_t<base + 0x05>  ELSR4;
		static inline rw8_t<base + 0x08>  ELSR7;
		static inline rw8_t<base + 0x09>  ELSR8;

		static inline rw8_t<base + 0x0B>  ELSR10;
		static inline rw8_t<base + 0x0C>  ELSR11;
		static inline rw8_t<base + 0x0D>  ELSR12;
		static inline rw8_t<base + 0x0E>  ELSR13;
		static inline rw8_t<base + 0x0F>  ELSR14;
		static inline rw8_t<base + 0x10>  ELSR15;
		static inline rw8_t<base + 0x11>  ELSR16;

		static inline rw8_t<base + 0x13>  ELSR18;
		static inline rw8_t<base + 0x14>  ELSR19;
		static inline rw8_t<base + 0x15>  ELSR20;
		static inline rw8_t<base + 0x16>  ELSR21;
		static inline rw8_t<base + 0x17>  ELSR22;
		static inline rw8_t<base + 0x18>  ELSR23;
		static inline rw8_t<base + 0x19>  ELSR24;
		static inline rw8_t<base + 0x1A>  ELSR25;
		static inline rw8_t<base + 0x1B>  ELSR26;
		static inline rw8_t<base + 0x1C>  ELSR27;
		static inline rw8_t<base + 0x1D>  ELSR28;

		static inline rw8_t<base + 0x31>  ELSR33;
		static inline rw8_t<base + 0x33>  ELSR35;
		static inline rw8_t<base + 0x34>  ELSR36;
		static inline rw8_t<base + 0x35>  ELSR37;
		static inline rw8_t<base + 0x36>  ELSR38;

		static inline rw8_t<base + 0x39>  ELSR41;
		static inline rw8_t<base + 0x3A>  ELSR42;
		static inline rw8_t<base + 0x3B>  ELSR43;
		static inline rw8_t<base + 0x3C>  ELSR44;
		static inline rw8_t<base + 0x3D>  ELSR45;
		static inline rw8_t<base + 0x44>  ELSR46;
		static inline rw8_t<base + 0x45>  ELSR47;
		static inline rw8_t<base + 0x46>  ELSR48;
		static inline rw8_t<base + 0x47>  ELSR49;
		static inline rw8_t<base + 0x48>  ELSR50;
		static inline rw8_t<base + 0x49>  ELSR51;
		static inline rw8_t<base + 0x4A>  ELSR52;
		static inline rw8_t<base + 0x4B>  ELSR53;
		static inline rw8_t<base + 0x4C>  ELSR54;
		static inline rw8_t<base + 0x4D>  ELSR55;
		static inline rw8_t<base + 0x4E>  ELSR56;
		static inline rw8_t<base + 0x4F>  ELSR57;
		static inline rw8_t<base + 0x58>  ELSR58;


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
		static inline elopb_t<base + 0x20> ELOP;


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
			bits_rw_t<io_, bitpos::B2, 2>  TMR1MD;
			bits_rw_t<io_, bitpos::B4, 2>  TMR2MD;
			bits_rw_t<io_, bitpos::B6, 2>  TMR3MD;
		};
		static inline elopd_t<base + 0x22> ELOPD;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ E（ELOPE）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elope_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  MTU6MD;
			bits_rw_t<io_, bitpos::B2, 2>  MTU7MD;

			bits_rw_t<io_, bitpos::B6, 2>  MTU9MD;
		};
		static inline elope_t<base + 0x3E> ELOPE;


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
		static inline elopf_t<base + 0x3F> ELOPF;


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
		static inline eloph_t<base + 0x41> ELOPH;


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
		static inline elopi_t<base + 0x42> ELOPI;


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
		static inline elopj_t<base + 0x43> ELOPJ;


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
		static inline pgrn_t<base + 0x23> PGR1;
		static inline pgrn_t<base + 0x24> PGR2;


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
		static inline pgcn_t<base + 0x25> PGC1;
		static inline pgcn_t<base + 0x26> PGC2;


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
		static inline pdbfn_t<base + 0x27> PDBF1;
		static inline pdbfn_t<base + 0x28> PDBF2;


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
	typedef elc_t<0x0008'B100, peripheral::ELC> ELC;
}
