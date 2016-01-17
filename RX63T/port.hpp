#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63x グループ・ポート・レジスター定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート定義基底クラス（PDR, PODR, PIDR, PMR, ODR0, ODR1）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct port_t {

		typedef io8<base + 0x00>  pdr_io;
		typedef io8<base + 0x20>  podr_io;
		typedef io8<base + 0x40>  pidr_io;
		typedef io8<base + 0x60>  pmr_io;
		typedef io8<base + 0x80>  odr0_io;
		typedef io8<base + 0x85>  odr1_io;

		//-----------------------------------------------------------------//
		/*!
			@brief  PDR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pdr_t : public pdr_io {
			using pdr_io::operator =;
			using pdr_io::operator ();
			using pdr_io::operator |=;
			using pdr_io::operator &=;

			bit_t<pdr_io, 0> B0;
			bit_t<pdr_io, 1> B1;
			bit_t<pdr_io, 2> B2;
			bit_t<pdr_io, 3> B3;
			bit_t<pdr_io, 4> B4;
			bit_t<pdr_io, 5> B5;
			bit_t<pdr_io, 6> B6;
			bit_t<pdr_io, 7> B7;
		};
		static pdr_t PDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PODR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct podr_t : public podr_io {
			using podr_io::operator =;
			using podr_io::operator ();
			using podr_io::operator |=;
			using podr_io::operator &=;

			bit_t<podr_io, 0> B0;
			bit_t<podr_io, 1> B1;
			bit_t<podr_io, 2> B2;
			bit_t<podr_io, 3> B3;
			bit_t<podr_io, 4> B4;
			bit_t<podr_io, 5> B5;
			bit_t<podr_io, 6> B6;
			bit_t<podr_io, 7> B7;

		};
		static podr_t PODR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PIDR
		*/
		//-----------------------------------------------------------------//
		struct pidr_t : public pidr_io {
			using pidr_io::operator ();

			bit_ro_t<pidr_io, 0> B0;
			bit_ro_t<pidr_io, 1> B1;
			bit_ro_t<pidr_io, 2> B2;
			bit_ro_t<pidr_io, 3> B3;
			bit_ro_t<pidr_io, 4> B4;
			bit_ro_t<pidr_io, 5> B5;
			bit_ro_t<pidr_io, 6> B6;
			bit_ro_t<pidr_io, 7> B7;
		};
		static pidr_t PIDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PMR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pmr_t : public pmr_io {
			using pmr_io::operator =;
			using pmr_io::operator ();
			using pmr_io::operator |=;
			using pmr_io::operator &=;

			bit_t<pmr_io, 0> B0;
			bit_t<pmr_io, 1> B1;
			bit_t<pmr_io, 2> B2;
			bit_t<pmr_io, 3> B3;
			bit_t<pmr_io, 4> B4;
			bit_t<pmr_io, 5> B5;
			bit_t<pmr_io, 6> B6;
			bit_t<pmr_io, 7> B7;
		};
		static pmr_t PMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ODR0 レジスタ
		*/
		//-----------------------------------------------------------------//
		struct odr0_t : public odr0_io {
			using odr0_io::operator =;
			using odr0_io::operator ();
			using odr0_io::operator |=;
			using odr0_io::operator &=;

			bit_t<odr0_io, 0> B0;
			bit_t<odr0_io, 2> B2;
			bit_t<odr0_io, 4> B4;
			bit_t<odr0_io, 6> B6;
		};
		static odr0_t ODR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ODR1 レジスタ
		*/
		//-----------------------------------------------------------------//
		struct odr1_t : public odr1_io {
			using odr1_io::operator =;
			using odr1_io::operator ();
			using odr1_io::operator |=;
			using odr1_io::operator &=;

			bit_t<odr1_io, 0> B0;
			bit_t<odr1_io, 2> B2;
			bit_t<odr1_io, 4> B4;
		};
		static odr1_t ODR1;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート定義基底クラス（PIDR）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct port_ro_t {

		typedef io8<base + 0x40>  pidr_io;

		//-----------------------------------------------------------------//
		/*!
			@brief  PIDR
		*/
		//-----------------------------------------------------------------//
		struct pidr_t : public pidr_io {
			using pidr_io::operator ();

			bit_ro_t<pidr_io, 0> B0;
			bit_ro_t<pidr_io, 1> B1;
			bit_ro_t<pidr_io, 2> B2;
			bit_ro_t<pidr_io, 3> B3;
			bit_ro_t<pidr_io, 4> B4;
			bit_ro_t<pidr_io, 5> B5;
			bit_ro_t<pidr_io, 6> B6;
			bit_ro_t<pidr_io, 7> B7;
		};
		static pidr_t PIDR;
	};

	typedef port_t<0x0008c000> PORT0;
	typedef port_t<0x0008c001> PORT1;
	typedef port_t<0x0008c002> PORT2;
	typedef port_t<0x0008c003> PORT3;
	typedef port_ro_t<0x0008c004> PORT4;
	typedef port_ro_t<0x0008c005> PORT5;
	typedef port_ro_t<0x0008c006> PORT6;
	typedef port_t<0x0008c007> PORT7;
	typedef port_t<0x0008c008> PORT8;
	typedef port_t<0x0008c009> PORT9;
	typedef port_t<0x0008c00a> PORTA;
	typedef port_t<0x0008c00b> PORTB;
	typedef port_t<0x0008c00d> PORTD;
	typedef port_t<0x0008c00e> PORTE;
	typedef port_t<0x0008c00f> PORTF;
	typedef port_t<0x0008c010> PORTG;

#if 0
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・ファンクション定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct ioport_t {

		typedef io8<0x0008c100> pf0cse_io;
		typedef io8<0x0008c103> pf3bus_io;
		typedef io8<0x0008c104> pf4bus_io;
		typedef io8<0x0008c105> pf5bus_io;
		typedef io8<0x0008c106> pf6bus_io;
		typedef io8<0x0008c108> pf8irq_io;
		typedef io8<0x0008c109> pf9irq_io;
		typedef io8<0x0008c10a> pfaadc_io;
		typedef io8<0x0008c10c> pfcmtu_io;
		typedef io8<0x0008c10d> pfdmtu_io;
		typedef io8<0x0008c10e> pfenet_io;
		typedef io8<0x0008c10f> pffsci_io;
		typedef io8<0x0008c110> pfgspi_io;
		typedef io8<0x0008c111> pfhspi_io;
		typedef io8<0x0008c113> pfjcan_io;
		typedef io8<0x0008c114> pfkusb_io;
		typedef io8<0x0008c116> pfmpoe_io;
		typedef io8<0x0008c117> pfnpoe_io;

		//-----------------------------------------------------------------//
		/*!
			@brief  PF0CSE レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pf0cse_t : public pf0cse_io {
			using pf0cse_io::operator =;
			using pf0cse_io::operator ();
			using pf0cse_io::operator |=;
			using pf0cse_io::operator &=;

			bit_t<pf0cse_io, 0> CS0E;
			bit_t<pf0cse_io, 1> CS1E;
			bit_t<pf0cse_io, 2> CS2E;
			bit_t<pf0cse_io, 3> CS3E;
			bit_t<pf0cse_io, 4> CS4E;
			bit_t<pf0cse_io, 5> CS5E;
			bit_t<pf0cse_io, 6> CS6E;
			bit_t<pf0cse_io, 7> CS7E;
		};
		static pf0cse_t PF0CSE;


		//-----------------------------------------------------------------//
		/*!
			@brief  PF3BUS レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pf3bus_t : public pf3bus_io {
			using pf3bus_io::operator =;
			using pf3bus_io::operator ();
			using pf3bus_io::operator |=;
			using pf3bus_io::operator &=;

			bit_t<pf3bus_io, 0> A16E;
			bit_t<pf3bus_io, 1> A17E;
			bit_t<pf3bus_io, 2> A18E;
			bit_t<pf3bus_io, 3> A19E;
			bit_t<pf3bus_io, 4> A20E;
			bit_t<pf3bus_io, 5> A21E;
			bit_t<pf3bus_io, 6> A22E;
			bit_t<pf3bus_io, 7> A23E;
		};
		static pf3bus_t PF3BUS;


		//-----------------------------------------------------------------//
		/*!
			@brief  PF4BUS レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pf4bus_t : public pf4bus_io {
			using pf4bus_io::operator =;
			using pf4bus_io::operator ();
			using pf4bus_io::operator |=;
			using pf4bus_io::operator &=;

			bit_t<pf4bus_io, 0> ADRLE;
			bit_t<pf4bus_io, 2> A10E;
			bit_t<pf4bus_io, 3> A11E;
			bit_t<pf4bus_io, 4> A12E;
			bit_t<pf4bus_io, 5> A13E;
			bit_t<pf4bus_io, 6> A14E;
			bit_t<pf4bus_io, 7> A15E;
		};
		static pf4bus_t PF4BUS;


		//-----------------------------------------------------------------//
		/*!
			@brief  PF5BUS レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pf5bus_t : public pf5bus_io {
			using pf5bus_io::operator =;
			using pf5bus_io::operator ();
			using pf5bus_io::operator |=;
			using pf5bus_io::operator &=;

			bit_t<pf5bus_io, 4> DHE;
			bit_t<pf5bus_io, 6> WR1BC1E;
		};
		static pf5bus_t PF5BUS;


		//-----------------------------------------------------------------//
		/*!
			@brief  PF6BUS レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pf6bus_t : public pf6bus_io {
			using pf6bus_io::operator =;
			using pf6bus_io::operator ();
			using pf6bus_io::operator |=;
			using pf6bus_io::operator &=;

			bits_t<pf6bus_io, 0, 2> WAITS;
		};
		static pf6bus_t PF6BUS;


		//-----------------------------------------------------------------//
		/*!
			@brief  PF8IRQ レジスタ
		*/
		//-----------------------------------------------------------------//
		class pf8irq_t : public pf8irq_io {
			using pf8irq_io::operator =;
			using pf8irq_io::operator ();
			using pf8irq_io::operator |=;
			using pf8irq_io::operator &=;

			bit_t<pf8irq_io, 5> ITS13;
			bit_t<pf8irq_io, 7> ITS15;
		};
		static pf8irq_t PF8IRQ;


		//-----------------------------------------------------------------//
		/*!
			@brief  PF9IRQ レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pf9irq_t : public pf9irq_io {
			using pf9irq_io::operator =;
			using pf9irq_io::operator ();
			using pf9irq_io::operator |=;
			using pf9irq_io::operator &=;

			bit_t<pf9irq_io, 2> ITS2;
			bit_t<pf9irq_io, 3> ITS3;
			bit_t<pf9irq_io, 4> ITS4;
			bit_t<pf9irq_io, 6> ITS6;
		};
		static pf9irq_t PF9IRQ;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFAADC レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pfaadc_t : public pfaadc_io {
			using pfaadc_io::operator =;
			using pfaadc_io::operator ();
			using pfaadc_io::operator |=;
			using pfaadc_io::operator &=;

			bit_t<pfaadc_io, 0> ADTRG0S;
		};
		static pfaadc_t PFAADC;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFCMTU レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pfcmtu_t : public pfcmtu_io {
			using pfcmtu_io::operator =;
			using pfcmtu_io::operator ();
			using pfcmtu_io::operator |=;
			using pfcmtu_io::operator &=;

			bit_t<pfcmtu_io, 5> MTUS5;
			bit_t<pfcmtu_io, 7> TCLKS;
		};
		static pfcmtu_t PFCMTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFDMTU レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pfdmtu_t : public pfdmtu_io {
			using pfdmtu_io::operator =;
			using pfdmtu_io::operator ();
			using pfdmtu_io::operator |=;
			using pfdmtu_io::operator &=;

			bit_t<pfdmtu_io, 6> MTUS6;
			bit_t<pfdmtu_io, 7> TCLKS;
		};
		static pfdmtu_t PFDMTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFENET レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pfenet_t : public pfenet_io {
			using pfenet_io::operator =;
			using pfenet_io::operator ();
			using pfenet_io::operator |=;
			using pfenet_io::operator &=;

			bit_t<pfenet_io, 0> ENETE0;
			bit_t<pfenet_io, 1> ENETE1;
			bit_t<pfenet_io, 2> ENETE2;
			bit_t<pfenet_io, 3> ENETE3;
			bit_t<pfenet_io, 4> PHYMODE;
			bit_t<pfenet_io, 7> EE;
		};
		static pfenet_t PFENET;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFFSCI レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pffsci_t : public pffsci_io {
			using pffsci_io::operator =;
			using pffsci_io::operator ();
			using pffsci_io::operator |=;
			using pffsci_io::operator &=;

			bit_t<pffsci_io, 2> SCI2S;
		};
		static pffsci_t PFFSCI;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFGSPI レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pfgspi_t : public pfgspi_io {
			using pfgspi_io::operator =;
			using pfgspi_io::operator ();
			using pfgspi_io::operator |=;
			using pfgspi_io::operator &=;

			bit_t<pfgspi_io, 0> RSPIS;
			bit_t<pfgspi_io, 1> RSPCKE;
			bit_t<pfgspi_io, 2> MOSIE;
			bit_t<pfgspi_io, 3> MISOE;
			bit_t<pfgspi_io, 4> SSL0E;
			bit_t<pfgspi_io, 5> SSL1E;
			bit_t<pfgspi_io, 6> SSL2E;
			bit_t<pfgspi_io, 7> SSL3E;
		};
		static pfgspi_t PFGSPI;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFHSPI レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pfhspi_t : public pfhspi_io {
			using pfhspi_io::operator =;
			using pfhspi_io::operator ();
			using pfhspi_io::operator |=;
			using pfhspi_io::operator &=;

			bit_t<pfhspi_io, 0> RSPIS;
			bit_t<pfhspi_io, 1> RSPCKE;
			bit_t<pfhspi_io, 2> MOSIE;
			bit_t<pfhspi_io, 3> MISOE;
			bit_t<pfhspi_io, 4> SSL0E;
			bit_t<pfhspi_io, 5> SSL1E;
			bit_t<pfhspi_io, 6> SSL2E;
			bit_t<pfhspi_io, 7> SSL3E;
		};
		static pfhspi_t PFHSPI;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFJCAN レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pfjcan_t : public pfjcan_io {
			using pfjcan_io::operator =;
			using pfjcan_io::operator ();
			using pfjcan_io::operator |=;
			using pfjcan_io::operator &=;

			bit_t<pfjcan_io, 0> CAN0E;
		};
		static pfjcan_t PFJCAN;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFKUSB レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pfkusb_t : public pfkusb_io {
			using pfkusb_io::operator =;
			using pfkusb_io::operator ();
			using pfkusb_io::operator |=;
			using pfkusb_io::operator &=;

			bits_t<pfkusb_io, 0, 2> USBMD;
			bit_t<pfkusb_io, 1> PUPHZS;
			bit_t<pfkusb_io, 2> PDHZS;
			bit_t<pfkusb_io, 3> USBE;
		};
		static pfkusb_t PFKUSB;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFMPOE レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pfmpoe_t : public pfmpoe_io {
			using pfmpoe_io::operator =;
			using pfmpoe_io::operator ();
			using pfmpoe_io::operator |=;
			using pfmpoe_io::operator &=;

			bit_t<pfmpoe_io, 0> POE0E;
			bit_t<pfmpoe_io, 1> POE1E;
			bit_t<pfmpoe_io, 2> POE2E;
			bit_t<pfmpoe_io, 3> POE3E;
			bit_t<pfmpoe_io, 4> POE4E;
			bit_t<pfmpoe_io, 5> POE5E;
			bit_t<pfmpoe_io, 6> POE6E;
			bit_t<pfmpoe_io, 7> POE7E;
		};
		static pfmpoe_t PFMPOE;


		//-----------------------------------------------------------------//
		/*!
			@brief  PFNPOE レジスタ
		*/
		//-----------------------------------------------------------------//
		struct pfnpoe_t : public pfnpoe_io {
			using pfnpoe_io::operator =;
			using pfnpoe_io::operator ();
			using pfnpoe_io::operator |=;
			using pfnpoe_io::operator &=;

			bit_t<pfnpoe_io, 0> POE8E;
			bit_t<pfnpoe_io, 1> POE9E;
		};
		static pfnpoe_t PFNPOE;
	};
	typedef ioport_t IOPORT;
#endif
}
