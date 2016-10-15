#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・ポート・レジスター定義 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート定義基底クラス（PDR, PODR, PIDR, PMR, ODR0, ODR1, PCR, DSCR）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct port_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  PDR レジスタ
		*/
		//-----------------------------------------------------------------//
		basic_rw_t<rw8_t<base + 0x00> > PDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PODR レジスタ
		*/
		//-----------------------------------------------------------------//
		basic_rw_t<rw8_t<base + 0x20> > PODR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PIDR
		*/
		//-----------------------------------------------------------------//
		basic_ro_t<rw8_t<base + 0x40> > PIDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PMR レジスタ
		*/
		//-----------------------------------------------------------------//
		basic_rw_t<rw8_t<base + 0x60> > PMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ODR0 レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x80>  odr0_io;
		struct odr0_t : public odr0_io {
			using odr0_io::operator =;
			using odr0_io::operator ();
			using odr0_io::operator |=;
			using odr0_io::operator &=;

			bit_rw_t<odr0_io, bitpos::B0> B0;
			bit_rw_t<odr0_io, bitpos::B2> B2;
			bit_rw_t<odr0_io, bitpos::B3> B3;
			bit_rw_t<odr0_io, bitpos::B4> B4;
			bit_rw_t<odr0_io, bitpos::B6> B6;
		};
		odr0_t ODR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ODR1 レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x81>  odr1_io;
		struct odr1_t : public odr1_io {
			using odr1_io::operator =;
			using odr1_io::operator ();
			using odr1_io::operator |=;
			using odr1_io::operator &=;

			bit_rw_t<odr1_io, bitpos::B0> B0;
			bit_rw_t<odr1_io, bitpos::B2> B2;
			bit_rw_t<odr1_io, bitpos::B4> B4;
			bit_rw_t<odr1_io, bitpos::B6> B6;
		};
		odr1_t ODR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  PCR レジスタ
		*/
		//-----------------------------------------------------------------//
		basic_rw_t<rw8_t<base + 0xC0> > PCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DSCR レジスタ
		*/
		//-----------------------------------------------------------------//
		basic_rw_t<rw8_t<base + 0xE0> > DSCR;
	};

	static port_t<0x0008C000> PORT0;
	static port_t<0x0008C001> PORT1;
	static port_t<0x0008C002> PORT2;
	static port_t<0x0008C003> PORT3;
	static port_t<0x0008C004> PORT4;
	static port_t<0x0008C005> PORT5;
	static port_t<0x0008C006> PORT6;
	static port_t<0x0008C007> PORT7;
	static port_t<0x0008C008> PORT8;
	static port_t<0x0008C009> PORT9;
	static port_t<0x0008C00a> PORTA;
	static port_t<0x0008C00b> PORTB;
	static port_t<0x0008C00d> PORTD;
	static port_t<0x0008C00e> PORTE;
	static port_t<0x0008C00f> PORTF;
	static port_t<0x0008C010> PORTG;
	static port_t<0x0008C012> PORTJ;
}
