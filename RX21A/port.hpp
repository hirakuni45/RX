#pragma once
//=========================================================================//
/*!	@file
	@brief	I/O Ports / I/O ポート (RX21A)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/port_base.hpp"

namespace device {

	typedef portx_t<0x0008'C000, odr_ox_t<0x0008'C080> > PORT0;
	typedef portx_t<0x0008'C001, odr_oo_t<0x0008'C082> > PORT1;
	typedef portx_t<0x0008'C002, odr_oo_t<0x0008'C084> > PORT2;
	typedef portx_t<0x0008'C003, odr_oo_t<0x0008'C086> > PORT3;
	typedef portx_t<0x0008'C004, odr_xx_t<0x0008'C088> > PORT4;
	typedef portx_t<0x0008'C005, odr_oo_t<0x0008'C08A> > PORT5;
	typedef portx_t<0x0008'C00A, odr_oo_t<0x0008'C094> > PORTA;
	typedef portx_t<0x0008'C00B, odr_oo_t<0x0008'C096> > PORTB;
	typedef portx_t<0x0008'C00C, odr_oo_t<0x0008'C098> > PORTC;
	typedef portx_t<0x0008'C00E, odr_oo_t<0x0008'C09C> > PORTE;
	typedef portx_t<0x0008'C011, odr_xx_t<0x0008'C0A2> > PORTH;
	typedef portx_t<0x0008'C012, odr_xx_t<0x0008'C0A4> > PORTJ;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート機能
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	namespace PORT_FUNC {

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート切り替えレジスタ A（PSRA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct psra_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6>  PSEL6;  ///< PB6(0) / PC0(1)
			bit_rw_t<io_, bitpos::B7>  PSEL7;  ///< PB7(0) / PC1(1)
		};
		static inline psra_t<0x0008'C121> PSRA;
	};
}
