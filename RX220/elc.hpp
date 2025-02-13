#pragma once
//=========================================================================//
/*!	@file
	@brief	RX210/RX220 グループ・ELC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
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
			@brief  イベントリンク設定レジスタ n（ELSRn） @n
					RX210:（n= 1 ～ 4、7、10、12、15、16、18 ～ 29） @n
					RX220:（n= 1 ～ 4、   10、12、15、   18、20、22、24、25）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x02>  ELSR1;
		static inline rw8_t<base + 0x03>  ELSR2;
		static inline rw8_t<base + 0x04>  ELSR3;
		static inline rw8_t<base + 0x05>  ELSR4;
#if defined(SIG_RX210)
		static inline rw8_t<base + 0x07>  ELSR7;
#endif
		static inline rw8_t<base + 0x0B>  ELSR10;

		static inline rw8_t<base + 0x0D>  ELSR12;

		static inline rw8_t<base + 0x10>  ELSR15;
#if defined(SIG_RX210)
		static inline rw8_t<base + 0x11>  ELSR16;
#endif
		static inline rw8_t<base + 0x13>  ELSR18;
#if defined(SIG_RX210)
		static inline rw8_t<base + 0x14>  ELSR19;
#endif
		static inline rw8_t<base + 0x15>  ELSR20;
#if defined(SIG_RX210)
		static inline rw8_t<base + 0x16>  ELSR21;
#endif
		static inline rw8_t<base + 0x17>  ELSR22;
#if defined(SIG_RX210)
		static inline rw8_t<base + 0x18>  ELSR23;
#endif
		static inline rw8_t<base + 0x19>  ELSR24;
		static inline rw8_t<base + 0x1A>  ELSR25;
#if defined(SIG_RX210)
		static inline rw8_t<base + 0x1B>  ELSR26;
		static inline rw8_t<base + 0x1C>  ELSR27;
		static inline rw8_t<base + 0x1D>  ELSR28;
		static inline rw8_t<base + 0x1E>  ELSR29;
#endif

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

#if defined(SIG_RX210)
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
		static inline elopc_t<base + 0x21> ELOPC;
#endif

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
		static inline pgr1_t<base + 0x23> PGR1;
#if defined(SIG_RX210)
		static inline pgr1_t<base + 0x24> PGR2;
#endif

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
		static inline pgc1_t<base + 0x25> PGC1;
#if defined(SIG_RX210)
		static inline pgc1_t<base + 0x26> PGC2;
#endif

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
		static inline pdbf1_t<base + 0x27> PDBF1;
#if defined(SIG_RX210)
		static inline pdbf1_t<base + 0x28> PDBF2;
#endif

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
		static inline peln_t<base + 0x29> PEL0;
		static inline peln_t<base + 0x2A> PEL1;
#if defined(SIG_RX210)
		static inline peln_t<base + 0x2B> PEL2;
		static inline peln_t<base + 0x2C> PEL3;
#endif

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
	typedef elc_t<0x0008'B100> ELC;
}
