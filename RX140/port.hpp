#pragma once
//=========================================================================//
/*!	@file
	@brief	RX140 グループ・ポート・レジスター定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/port_base.hpp"

namespace device {

	typedef portx_t<0x0008'C000, odr_xx_t<0x0008'C080> > PORT0;
	typedef portx_t<0x0008'C001, odr_oo_t<0x0008'C082> > PORT1;
	typedef portx_t<0x0008'C002, odr_oo_t<0x0008'C084> > PORT2;
	typedef portx_t<0x0008'C003, odr_oo_t<0x0008'C086> > PORT3;
	typedef portx_t<0x0008'C004, odr_xx_t<0x0008'C088> > PORT4;
	typedef portx_t<0x0008'C005, odr_xx_t<0x0008'C08A> > PORT5;
	typedef portx_t<0x0008'C00A, odr_oo_t<0x0008'C094> > PORTA;
	typedef portx_t<0x0008'C00B, odr_oo_t<0x0008'C096> > PORTB;
	typedef portx_t<0x0008'C00C, odr_oo_t<0x0008'C098> > PORTC;
	typedef portx_t<0x0008'C00D, odr_oo_t<0x0008'C09A> > PORTD;
	typedef portx_t<0x0008'C00E, odr_oo_t<0x0008'C09C> > PORTE;
	typedef portx_t<0x0008'C010, odr_xx_t<0x0008'C0A0> > PORTG;
	typedef portx_t<0x0008'C011, odr_xx_t<0x0008'C0A2> > PORTH;
	typedef portx_t<0x0008'C012, odr_xx_t<0x0008'C0A4> > PORTJ;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct PORT_CTRL {

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート切り替えレジスタ A (PSRA)
			@param[in] base		ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct psra_t : public rw8_t<base> {
			typedef rw8_t<base>  io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> PSEL6;
			bit_rw_t<io_, bitpos::B7> PSEL7;
		};
		static inline psra_t<0x0008'C121> PSRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートリードウェイト制御レジスタ (PRWCNTR)
			@param[in] base		ベース・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct prwcntr_t : public rw8_t<base> {
			typedef rw8_t<base>  io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> WAIT;
		};
		static inline prwcntr_t<0x0008'C120> PRWCNTR;
	};
}
