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
		struct elcr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7>  ELCON;
		};
		typedef elcr_t_<base + 0x00> ercr_t;
		static ercr_t ERCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  イベントリンク設定レジスタ n（ELSRn）@n
					（n = 0、3、4、7、10 ～ 13、15、16、18 ～ 28、33、35 ～ 38、41 ～ 45）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x01> elsr0_t;
		static elsr0_t ELSR0;
		typedef rw8_t<base + 0x04> elsr3_t;
		static elsr3_t ELSR3;
		typedef rw8_t<base + 0x05> elsr4_t;
		static elsr4_t ELSR4;
		typedef rw8_t<base + 0x08> elsr7_t;
		static elsr7_t ELSR7;
		typedef rw8_t<base + 0x0B> elsr10_t;
		static elsr10_t ELSR10;
		typedef rw8_t<base + 0x0C> elsr11_t;
		static elsr11_t ELSR11;
		typedef rw8_t<base + 0x0D> elsr12_t;
		static elsr12_t ELSR12;
		typedef rw8_t<base + 0x0E> elsr13_t;
		static elsr13_t ELSR13;
		typedef rw8_t<base + 0x10> elsr15_t;
		static elsr15_t ELSR15;
		typedef rw8_t<base + 0x11> elsr16_t;
		static elsr16_t ELSR16;
		typedef rw8_t<base + 0x13> elsr18_t;
		static elsr18_t ELSR18;
		typedef rw8_t<base + 0x14> elsr19_t;
		static elsr19_t ELSR19;
		typedef rw8_t<base + 0x15> elsr20_t;
		static elsr20_t ELSR20;
		typedef rw8_t<base + 0x16> elsr21_t;
		static elsr21_t ELSR21;
		typedef rw8_t<base + 0x17> elsr22_t;
		static elsr22_t ELSR22;
		typedef rw8_t<base + 0x18> elsr23_t;
		static elsr23_t ELSR23;
		typedef rw8_t<base + 0x19> elsr24_t;
		static elsr24_t ELSR24;
		typedef rw8_t<base + 0x1A> elsr25_t;
		static elsr25_t ELSR25;
		typedef rw8_t<base + 0x1B> elsr26_t;
		static elsr26_t ELSR26;
		typedef rw8_t<base + 0x1C> elsr27_t;
		static elsr27_t ELSR27;
		typedef rw8_t<base + 0x1D> elsr28_t;
		static elsr28_t ELSR28;
		typedef rw8_t<base + 0x31> elsr33_t;
		static elsr33_t ELSR33;
		typedef rw8_t<base + 0x33> elsr35_t;
		static elsr35_t ELSR35;
		typedef rw8_t<base + 0x34> elsr36_t;
		static elsr36_t ELSR36;
		typedef rw8_t<base + 0x35> elsr37_t;
		static elsr37_t ELSR37;
		typedef rw8_t<base + 0x36> elsr38_t;
		static elsr38_t ELSR38;
		typedef rw8_t<base + 0x39> elsr41_t;
		static elsr41_t ELSR41;
		typedef rw8_t<base + 0x3A> elsr42_t;
		static elsr42_t ELSR42;
		typedef rw8_t<base + 0x3B> elsr43_t;
		static elsr43_t ELSR43;
		typedef rw8_t<base + 0x3C> elsr44_t;
		static elsr44_t ELSR44;
		typedef rw8_t<base + 0x3D> elsr45_t;
		static elsr45_t ELSR45;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ A（ELOPA）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopa_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  MTU0MD;
			bits_rw_t<io_, bitpos::B6, 2>  MTU3MD;
		};
		typedef elopa_t_<base + 0x1F> elopa_t;
		static elopa_t ELOPA;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ B（ELOPB）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopb_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  MTU4MD;
		};
		typedef elopb_t_<base + 0x20> elopb_t;
		static elopb_t ELOPB;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ C（ELOPC）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopc_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B2, 2>  CMT1MD;
		};
		typedef elopc_t_<base + 0x21> elopc_t;
		static elopc_t ELOPC;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ D（ELOPD）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopd_t_ : public rw8_t<ofs> {
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
		typedef elopd_t_<base + 0x22> elopd_t;
		static elopd_t ELOPD;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ F（ELOPF）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopf_t_ : public rw8_t<ofs> {
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
		typedef elopf_t_<base + 0x3F> elopf_t;
		static elopf_t ELOPF;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ H（ELOPH）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct eloph_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  CMTW0MD;
		};
		typedef eloph_t_<base + 0x41> eloph_t;
		static eloph_t ELOPH;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ I（ELOPI）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopi_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  GPT0MD;
			bits_rw_t<io_, bitpos::B4, 3>  GPT1MD;
		};
		typedef elopi_t_<base + 0x42> elopi_t;
		static elopi_t ELOPI;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクオプション設定レジスタ J（ELOPJ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elopj_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  GPT2MD;
			bits_rw_t<io_, bitpos::B4, 3>  GPT3MD;
		};
		typedef elopj_t_<base + 0x43> elopj_t;
		static elopj_t ELOPJ;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートグループ指定レジスタ n（PGRn）（n = 1、2）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pgrn_t_ : public rw8_t<ofs> {
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
		typedef pgrn_t_<base + 0x23> pgr1_t;
		static pgr1_t PGR1;
		typedef pgrn_t_<base + 0x24> pgr2_t;
		static pgr2_t PGR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートグループコントロールレジスタ n（PGCn）（n = 1、2）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pgcn_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  PGC;
			bit_rw_t <io_, bitpos::B2>     PGCOVE;
			bits_rw_t<io_, bitpos::B4, 3>  PGCO;
		};
		typedef pgcn_t_<base + 0x25> pgc1_t;
		static pgc1_t PGC1;
		typedef pgcn_t_<base + 0x26> pgc2_t;
		static pgc2_t PGC2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートバッファレジスタ n（PDBFn）（n = 1、2）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pdbfn_t_ : public rw8_t<ofs> {
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
		typedef pdbfn_t_<base + 0x27> pdbf1_t;
		static pdbf1_t PDBF1;
		typedef pdbfn_t_<base + 0x28> pdbf2_t;
		static pdbf2_t PDBF2;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベント接続ポート指定レジスタ n（PELn）（n = 0 ～ 3）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct peln_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  PSB;
			bits_rw_t<io_, bitpos::B3, 2>  PSP;
			bits_rw_t<io_, bitpos::B5, 2>  PSM;
		};
		typedef peln_t_<base + 0x29> pel0_t;
		static pel0_t PEL0;
		typedef peln_t_<base + 0x2A> pel1_t;
		static pel1_t PEL1;
		typedef peln_t_<base + 0x2B> pel2_t;
		static pel2_t PEL2;
		typedef peln_t_<base + 0x2C> pel3_t;
		static pel3_t PEL3;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベントリンクソフトウェアイベント発生レジスタ（ELSEGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct elsegr_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SEG;	// write-only
			bit_rw_t<io_, bitpos::B6>  WE;
			bit_rw_t<io_, bitpos::B7>  WI;	// write-only
		};
		typedef elsegr_t_<base + 0x2D> elsegr_t;
		static elsegr_t ELSEGR;
	};
	typedef elc_t<0x0008B100> ELC;

	template<uint32_t base> typename elc_t<base>::ercr_t elc_t<base>::ERCR;
	template<uint32_t base> typename elc_t<base>::elsr0_t elc_t<base>::ELSR0;
	template<uint32_t base> typename elc_t<base>::elsr3_t elc_t<base>::ELSR3;
	template<uint32_t base> typename elc_t<base>::elsr4_t elc_t<base>::ELSR4;
	template<uint32_t base> typename elc_t<base>::elsr7_t elc_t<base>::ELSR7;
	template<uint32_t base> typename elc_t<base>::elsr10_t elc_t<base>::ELSR10;
	template<uint32_t base> typename elc_t<base>::elsr11_t elc_t<base>::ELSR11;
	template<uint32_t base> typename elc_t<base>::elsr12_t elc_t<base>::ELSR12;
	template<uint32_t base> typename elc_t<base>::elsr13_t elc_t<base>::ELSR13;
	template<uint32_t base> typename elc_t<base>::elsr15_t elc_t<base>::ELSR15;
	template<uint32_t base> typename elc_t<base>::elsr16_t elc_t<base>::ELSR16;
	template<uint32_t base> typename elc_t<base>::elsr18_t elc_t<base>::ELSR18;
	template<uint32_t base> typename elc_t<base>::elsr19_t elc_t<base>::ELSR19;
	template<uint32_t base> typename elc_t<base>::elsr20_t elc_t<base>::ELSR20;
	template<uint32_t base> typename elc_t<base>::elsr21_t elc_t<base>::ELSR21;
	template<uint32_t base> typename elc_t<base>::elsr22_t elc_t<base>::ELSR22;
	template<uint32_t base> typename elc_t<base>::elsr23_t elc_t<base>::ELSR23;
	template<uint32_t base> typename elc_t<base>::elsr24_t elc_t<base>::ELSR24;
	template<uint32_t base> typename elc_t<base>::elsr25_t elc_t<base>::ELSR25;
	template<uint32_t base> typename elc_t<base>::elsr26_t elc_t<base>::ELSR26;
	template<uint32_t base> typename elc_t<base>::elsr27_t elc_t<base>::ELSR27;
	template<uint32_t base> typename elc_t<base>::elsr28_t elc_t<base>::ELSR28;
	template<uint32_t base> typename elc_t<base>::elsr33_t elc_t<base>::ELSR33;
	template<uint32_t base> typename elc_t<base>::elsr35_t elc_t<base>::ELSR35;
	template<uint32_t base> typename elc_t<base>::elsr36_t elc_t<base>::ELSR36;
	template<uint32_t base> typename elc_t<base>::elsr37_t elc_t<base>::ELSR37;
	template<uint32_t base> typename elc_t<base>::elsr38_t elc_t<base>::ELSR38;
	template<uint32_t base> typename elc_t<base>::elsr41_t elc_t<base>::ELSR41;
	template<uint32_t base> typename elc_t<base>::elsr42_t elc_t<base>::ELSR42;
	template<uint32_t base> typename elc_t<base>::elsr43_t elc_t<base>::ELSR43;
	template<uint32_t base> typename elc_t<base>::elsr44_t elc_t<base>::ELSR44;
	template<uint32_t base> typename elc_t<base>::elsr45_t elc_t<base>::ELSR45;
	template<uint32_t base> typename elc_t<base>::elopa_t elc_t<base>::ELOPA;
	template<uint32_t base> typename elc_t<base>::elopb_t elc_t<base>::ELOPB;
	template<uint32_t base> typename elc_t<base>::elopc_t elc_t<base>::ELOPC;
	template<uint32_t base> typename elc_t<base>::elopd_t elc_t<base>::ELOPD;
	template<uint32_t base> typename elc_t<base>::elopf_t elc_t<base>::ELOPF;
	template<uint32_t base> typename elc_t<base>::eloph_t elc_t<base>::ELOPH;
	template<uint32_t base> typename elc_t<base>::elopi_t elc_t<base>::ELOPI;
	template<uint32_t base> typename elc_t<base>::elopj_t elc_t<base>::ELOPJ;
	template<uint32_t base> typename elc_t<base>::pgr1_t elc_t<base>::PGR1;
	template<uint32_t base> typename elc_t<base>::pgr2_t elc_t<base>::PGR2;
	template<uint32_t base> typename elc_t<base>::pgc1_t elc_t<base>::PGC1;
	template<uint32_t base> typename elc_t<base>::pgc2_t elc_t<base>::PGC2;
	template<uint32_t base> typename elc_t<base>::pdbf1_t elc_t<base>::PDBF1;
	template<uint32_t base> typename elc_t<base>::pdbf2_t elc_t<base>::PDBF2;
	template<uint32_t base> typename elc_t<base>::pel0_t elc_t<base>::PEL0;
	template<uint32_t base> typename elc_t<base>::pel1_t elc_t<base>::PEL1;
	template<uint32_t base> typename elc_t<base>::pel2_t elc_t<base>::PEL2;
	template<uint32_t base> typename elc_t<base>::pel3_t elc_t<base>::PEL3;
	template<uint32_t base> typename elc_t<base>::elsegr_t elc_t<base>::ELSEGR;
}
