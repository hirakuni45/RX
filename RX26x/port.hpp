#pragma once
//=====================================================================//
/*!	@file
	@brief	RX260/RX261 グループ・ポート・レジスター定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/port_base.hpp"

namespace device {

	typedef portx_t<0x0008'C000, odr_xx_t<0x0008'C080> > PORT0;
	typedef portx_t<0x0008'C001, odr_oo_t<0x0008'C082> > PORT1;
	typedef portx_t<0x0008'C002, odr_oo_t<0x0008'C084> > PORT2;
	typedef portx_t<0x0008'C003, odr_oo_t<0x0008'C086> > PORT3;
	typedef portx_t<0x0008'C004, odr_xx_t<0x0008'C088> > PORT4;
	typedef portx_t<0x0008'C005, odr_oo_t<0x0008'C08A> > PORT5;
	typedef portx_t<0x0008'C00A, odr_oo_t<0x0008'C094> > PORTA;
	typedef portx_t<0x0008'C00B, odr_oo_t<0x0008'C096> > PORTB;
	typedef portx_t<0x0008'C00C, odr_oo_t<0x0008'C098> > PORTC;
	typedef portx_t<0x0008'C00D, odr_ox_t<0x0008'C09A> > PORTD;
	typedef portx_t<0x0008'C00E, odr_oo_t<0x0008'C09C> > PORTE;

	typedef portx_t<0x0008'C010, odr_xo_t<0x0008'C0A0> > PORTG;
	typedef portx_t<0x0008'C011, odr_xx_t<0x0008'C0A1> > PORTH;
	typedef portx_t<0x0008'C012, odr_xx_t<0x0008'C0A4> > PORTJ;

}