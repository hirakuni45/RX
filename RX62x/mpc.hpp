
#pragma once
//=========================================================================//
/*!	@file
	@brief	Multi-Function Pin Controller / マルチファンクションピンコントローラ @n
			Port-Function Register (RX621/RX62N)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MPC class (Port function register class)
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct mpc_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 0（PF0CSE）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf0cse_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> CS0E;
			bit_rw_t<io, bitpos::B1> CS1E;
			bit_rw_t<io, bitpos::B2> CS2E;
			bit_rw_t<io, bitpos::B3> CS3E;
			bit_rw_t<io, bitpos::B4> CS4E;
			bit_rw_t<io, bitpos::B5> CS5E;
			bit_rw_t<io, bitpos::B6> CS6E;
			bit_rw_t<io, bitpos::B7> CS7E;
		};
		static inline pf0cse_t<0x0008'C100> PF0CSE;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 1（PF1CSS）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf1css_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;


			bits_rw_t<io, bitpos::B0, 2> CS4S;
			bits_rw_t<io, bitpos::B2, 2> CS5S;
			bits_rw_t<io, bitpos::B4, 2> CS6S;
			bits_rw_t<io, bitpos::B6, 2> CS7S;
		};
		static inline pf1css_t<0x0008'C101> PF1CSS;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 2（PF2CSS）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf2css_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;


			bit_rw_t <io, bitpos::B0>    CS0S;

			bits_rw_t<io, bitpos::B2, 2> CS1S;
			bits_rw_t<io, bitpos::B4, 2> CS2S;
			bits_rw_t<io, bitpos::B6, 2> CS3S;
		};
		static inline pf2css_t<0x0008'C102> PF2CSS;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 3（PF3BUS）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf3bus_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> A16E;
			bit_rw_t<io, bitpos::B1> A17E;
			bit_rw_t<io, bitpos::B2> A18E;
			bit_rw_t<io, bitpos::B3> A19E;
			bit_rw_t<io, bitpos::B4> A20E;
			bit_rw_t<io, bitpos::B5> A21E;
			bit_rw_t<io, bitpos::B6> A22E;
			bit_rw_t<io, bitpos::B7> A23E;
		};
		static inline pf3bus_t<0x0008'C103> PF3BUS;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 4（PF4BUS）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf4bus_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B2, 2> ADRLE;
			bit_rw_t<io, bitpos::B2>     A10E;
			bit_rw_t<io, bitpos::B3>     A11E;
			bit_rw_t<io, bitpos::B4>     A12E;
			bit_rw_t<io, bitpos::B5>     A13E;
			bit_rw_t<io, bitpos::B6>     A14E;
			bit_rw_t<io, bitpos::B7>     A15E;
		};
		static inline pf4bus_t<0x0008'C104> PF4BUS;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 5（PF5BUS）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf5bus_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B1>     ADRHMS;

			bit_rw_t<io, bitpos::B4>     DHE;
			bit_rw_t<io, bitpos::B5>     DH32E;
			bit_rw_t<io, bitpos::B6>     WR1BC1E;
			bit_rw_t<io, bitpos::B7>     WR32BC32E;
		};
		static inline pf5bus_t<0x0008'C105> PF5BUS;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 6（PF6BUS）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf6bus_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 2> WAITS;

			bit_rw_t <io, bitpos::B4>    MDSDE;

			bit_rw_t <io, bitpos::B6>    DQM1E;
			bit_rw_t <io, bitpos::B7>    SDCLKE;
		};
		static inline pf6bus_t<0x0008'C106> PF6BUS;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 7（PF7DMA）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf7dma_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B4, 2> EDMA0S;
			bits_rw_t<io, bitpos::B6, 2> EDMA1S;
		};
		static inline pf7dma_t<0x0008'C107> PF7DMA;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 8（PF8IRQ）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf8irq_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> ITS8;
			bit_rw_t<io, bitpos::B1> ITS9;
			bit_rw_t<io, bitpos::B2> ITS10;
			bit_rw_t<io, bitpos::B3> ITS11;

			bit_rw_t<io, bitpos::B5> ITS13;

			bit_rw_t<io, bitpos::B7> ITS15;
		};
		static inline pf8irq_t<0x0008'C108> PF8IRQ;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 9（PF9IRQ）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf9irq_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> ITS0;
			bit_rw_t<io, bitpos::B1> ITS1;
			bit_rw_t<io, bitpos::B2> ITS2;
			bit_rw_t<io, bitpos::B3> ITS3;
			bit_rw_t<io, bitpos::B4> ITS4;
			bit_rw_t<io, bitpos::B5> ITS5;
			bit_rw_t<io, bitpos::B6> ITS6;
			bit_rw_t<io, bitpos::B7> ITS7;
		};
		static inline pf9irq_t<0x0008'C109> PF9IRQ;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ A（PFAADC）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfaadc_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> ADTRG0S;
		};
		static inline pfaadc_t<0x0008'C10A> PFAADC;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ B（PFBTMR）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfbtmr_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> TMR0S;
			bit_rw_t<io, bitpos::B1> TMR1S;
			bit_rw_t<io, bitpos::B2> TMR2S;
			bit_rw_t<io, bitpos::B3> TMR3S;
		};
		static inline pfbtmr_t<0x0008'C10B> PFBTMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ C（PFCMTU）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfcmtu_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B2> MTUS2;
			bit_rw_t<io, bitpos::B3> MTUS3;
			bit_rw_t<io, bitpos::B4> MTUS4;
			bit_rw_t<io, bitpos::B5> MTUS5;
			bit_rw_t<io, bitpos::B6> MTUS6;
			bit_rw_t<io, bitpos::B7> TCLKS;
		};
		static inline pfcmtu_t<0x0008'C10C> PFCMTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ D（PFDMTU）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfdmtu_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B6> MTUS6;
			bit_rw_t<io, bitpos::B7> TCLKS;
		};
		static inline pfdmtu_t<0x0008'C10D> PFDMTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ E（PFENET）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfenet_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> ENETE0;
			bit_rw_t<io, bitpos::B1> ENETE1;
			bit_rw_t<io, bitpos::B2> ENETE2;
			bit_rw_t<io, bitpos::B3> ENETE3;
			bit_rw_t<io, bitpos::B4> PHYMODE;

			bit_rw_t<io, bitpos::B7> EE;
		};
		static inline pfenet_t<0x0008'C10E> PFENET;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ F（PFFSCI）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pffsci_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B1> SCI1S;
			bit_rw_t<io, bitpos::B2> SCI2S;
			bit_rw_t<io, bitpos::B3> SCI3S;

			bit_rw_t<io, bitpos::B6> SCI6S;
		};
		static inline pffsci_t<0x0008'C10F> PFFSCI;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ G（PFGSPI）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfxspi_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> RSPIS;
			bit_rw_t<io, bitpos::B1> RSPCKE;
			bit_rw_t<io, bitpos::B2> MOSIE;
			bit_rw_t<io, bitpos::B3> MISOE;
			bit_rw_t<io, bitpos::B4> SSL0E;
			bit_rw_t<io, bitpos::B5> SSL1E;
			bit_rw_t<io, bitpos::B6> SSL2E;
			bit_rw_t<io, bitpos::B7> SSL3E;
		};
		static inline pfxspi_t<0x0008'C110> PFGSPI;
		static inline pfxspi_t<0x0008'C111> PFHSPI;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ J（PFJCAN）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfjcan_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> CAN0E;
		};
		static inline pfjcan_t<0x0008'C113> PFJCAN;
	};
	typedef mpc_t MPC;
}
