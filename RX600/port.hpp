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

		static const uint32_t base_address_ = base;


		//-----------------------------------------------------------------//
		/*!
			@brief  PDR レジスタ
		*/
		//-----------------------------------------------------------------//
		static basic_rw_t<rw8_t<base + 0x00> > PDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PODR レジスタ
		*/
		//-----------------------------------------------------------------//
		static basic_rw_t<rw8_t<base + 0x20> > PODR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PIDR
		*/
		//-----------------------------------------------------------------//
		static basic_ro_t<rw8_t<base + 0x40> > PIDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PMR レジスタ
		*/
		//-----------------------------------------------------------------//
		static basic_rw_t<rw8_t<base + 0x60> > PMR;


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
		static odr0_t ODR0;


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
		static odr1_t ODR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  PCR レジスタ
		*/
		//-----------------------------------------------------------------//
		static basic_rw_t<rw8_t<base + 0xC0> > PCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DSCR レジスタ
		*/
		//-----------------------------------------------------------------//
		static basic_rw_t<rw8_t<base + 0xE0> > DSCR;

	};

	typedef port_t<0x0008C000> PORT0;
	typedef port_t<0x0008C001> PORT1;
	typedef port_t<0x0008C002> PORT2;
	typedef port_t<0x0008C003> PORT3;
	typedef port_t<0x0008C004> PORT4;
	typedef port_t<0x0008C005> PORT5;
	typedef port_t<0x0008C006> PORT6;
	typedef port_t<0x0008C007> PORT7;
	typedef port_t<0x0008C008> PORT8;
	typedef port_t<0x0008C009> PORT9;
	typedef port_t<0x0008C00a> PORTA;
	typedef port_t<0x0008C00b> PORTB;
	typedef port_t<0x0008C00d> PORTD;
	typedef port_t<0x0008C00e> PORTE;
	typedef port_t<0x0008C00f> PORTF;
	typedef port_t<0x0008C010> PORTG;
	typedef port_t<0x0008C012> PORTJ;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  単ポート定義テンプレート
		@param[in]	PORTx	ポート・クラス
		@param[in]	bpos	ビット位置	
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PORTx, bitpos bpos>
	struct PORT {

		//-----------------------------------------------------------------//
		/*!
			@brief  方向・レジスタ
		*/
		//-----------------------------------------------------------------//
		static bit_rw_t<rw8_t<PORTx::base_address_ + 0x00>, bpos> DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ
		*/
		//-----------------------------------------------------------------//
		static bit_rw_t<rw8_t<PORTx::base_address_ + 0x20>, bpos> P;

	};
}
