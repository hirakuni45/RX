#pragma once
//=========================================================================//
/*!	@file
	@brief	I/O Ports / I/O ポート (RX13T)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/port_base.hpp"

namespace device {

//  ODR0  -  o  o  o  x  x  x  o  o  o  o  o  x  o  o  -  -  -
//  ODR1  -  o  o  o  x  x  x  o  o  o  o  o  x  o  o  -  -  -
	typedef portx_t<0x0008'C001, odr_oo_t<0x0008'C082> > PORT1;
	typedef portx_t<0x0008'C002, odr_oo_t<0x0008'C084> > PORT2;
	typedef portx_t<0x0008'C003, odr_oo_t<0x0008'C086> > PORT3;
	typedef portx_t<0x0008'C004, odr_xx_t<0x0008'C088> > PORT4;

	typedef portx_t<0x0008'C007, odr_oo_t<0x0008'C08E> > PORT7;

	typedef portx_t<0x0008'C009, odr_oo_t<0x0008'C092> > PORT9;
	typedef portx_t<0x0008'C00A, odr_oo_t<0x0008'C094> > PORTA;
	typedef portx_t<0x0008'C00B, odr_oo_t<0x0008'C096> > PORTB;
	typedef portx_t<0x0008'C00D, odr_oo_t<0x0008'C09A> > PORTD;
	typedef portx_t<0x0008'C00E, odr_oo_t<0x0008'C09C> > PORTE;

}
