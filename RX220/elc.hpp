#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220 グループ・ELC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
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
			@brief  イベントリンク設定レジスタ n（ELSRn） @n
					（n= 1 ～ 4、10、12、15、18、20、22、24、25）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x02>  ELSR1_;
		static  ELSR1_ ELSR1;
		typedef rw8_t<base + 0x03>  ELSR2_;
		static  ELSR2_ ELSR2;
		typedef rw8_t<base + 0x04>  ELSR3_;
		static  ELSR3_ ELSR3;
		typedef rw8_t<base + 0x05>  ELSR4_;
		static  ELSR4_ ELSR4;
	
		typedef rw8_t<base + 0x0B>  ELSR10_;
		static  ELSR10_ ELSR10;

		typedef rw8_t<base + 0x0D>  ELSR12_;
		static  ELSR12_ ELSR12;

		typedef rw8_t<base + 0x10>  ELSR15_;
		static  ELSR15_ ELSR15;

		typedef rw8_t<base + 0x13>  ELSR18_;
		static  ELSR18_ ELSR18;

		typedef rw8_t<base + 0x15>  ELSR20_;
		static  ELSR20_ ELSR20;

		typedef rw8_t<base + 0x17>  ELSR22_;
		static  ELSR22_ ELSR22;

		typedef rw8_t<base + 0x19>  ELSR24_;
		static  ELSR24_ ELSR24;
		typedef rw8_t<base + 0x1A>  ELSR25_;
		static  ELSR25_ ELSR25;


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
			@brief	ポートグループ指定レジスタ 1（PGR1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pgr1_t : public rw8_t<ofs> {
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
		typedef pgr1_t<base + 0x23> PGR1_;
		static  PGR1_ PGR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートグループコントロールレジスタ 1（PGC1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pgc1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  PGC;
			bit_rw_t <io_, bitpos::B2>     PGCOVE;

			bits_rw_t<io_, bitpos::B4, 3>  PGCO;
		};
		typedef pgc1_t<base + 0x25> PGC1_;
		static  PGC1_ PGC1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートバッファレジスタ 1（PDBF1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pdbf1_t : public rw8_t<ofs> {
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
		typedef pdbf1_t<base + 0x27> PDBF1_;
		static  PDBF1_ PDBF1;


		//-----------------------------------------------------------------//
		/*!
			@brief	イベント接続ポート指定レジスタ n（PELn）（n = 0, 1）
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
	template <uint32_t base> typename elc_t<base>::ELCR_ elc_t<base>::ELCR;
	template <uint32_t base> typename elc_t<base>::ELSR1_ elc_t<base>::ELSR1;
	template <uint32_t base> typename elc_t<base>::ELSR2_ elc_t<base>::ELSR2;
	template <uint32_t base> typename elc_t<base>::ELSR3_ elc_t<base>::ELSR3;
	template <uint32_t base> typename elc_t<base>::ELSR4_ elc_t<base>::ELSR4;
	template <uint32_t base> typename elc_t<base>::ELSR10_ elc_t<base>::ELSR10;
	template <uint32_t base> typename elc_t<base>::ELSR12_ elc_t<base>::ELSR12;
	template <uint32_t base> typename elc_t<base>::ELSR15_ elc_t<base>::ELSR15;
	template <uint32_t base> typename elc_t<base>::ELSR18_ elc_t<base>::ELSR18;
	template <uint32_t base> typename elc_t<base>::ELSR20_ elc_t<base>::ELSR20;
	template <uint32_t base> typename elc_t<base>::ELSR22_ elc_t<base>::ELSR22;
	template <uint32_t base> typename elc_t<base>::ELSR24_ elc_t<base>::ELSR24;
	template <uint32_t base> typename elc_t<base>::ELSR25_ elc_t<base>::ELSR25;
	template <uint32_t base> typename elc_t<base>::ELOPA_ elc_t<base>::ELOPA;
	template <uint32_t base> typename elc_t<base>::ELOPB_ elc_t<base>::ELOPB;
	template <uint32_t base> typename elc_t<base>::ELOPD_ elc_t<base>::ELOPD;
	template <uint32_t base> typename elc_t<base>::PGR1_ elc_t<base>::PGR1;
	template <uint32_t base> typename elc_t<base>::PGC1_ elc_t<base>::PGC1;
	template <uint32_t base> typename elc_t<base>::PDBF1_ elc_t<base>::PDBF1;
	template <uint32_t base> typename elc_t<base>::PEL0_ elc_t<base>::PEL0;
	template <uint32_t base> typename elc_t<base>::PEL1_ elc_t<base>::PEL1;
	template <uint32_t base> typename elc_t<base>::ELSEGR_ elc_t<base>::ELSEGR;

	typedef elc_t<0x0008'B100> ELC;
}
