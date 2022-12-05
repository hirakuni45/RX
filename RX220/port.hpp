#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220 グループ・ポート・レジスター定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/port_base.hpp"

namespace device {

	typedef port_t<0x0008'C000, odr_xx_t<0x0008'C080> > PORT0;
	typedef port_t<0x0008'C001, odr_oo_t<0x0008'C082> > PORT1;
	typedef port_t<0x0008'C002, odr_xx_t<0x0008'C084> > PORT2;
	typedef port_t<0x0008'C003, odr_oo_t<0x0008'C086> > PORT3;
	typedef port_t<0x0008'C004, odr_xx_t<0x0008'C088> > PORT4;
	typedef port_t<0x0008'C005, odr_xx_t<0x0008'C08A> > PORT5;
	typedef port_t<0x0008'C00A, odr_oo_t<0x0008'C094> > PORTA;
	typedef port_t<0x0008'C00B, odr_oo_t<0x0008'C096> > PORTB;
	typedef port_t<0x0008'C00C, odr_oo_t<0x0008'C098> > PORTC;
	typedef port_t<0x0008'C00D, odr_xx_t<0x0008'C09A> > PORTD;
	typedef port_t<0x0008'C00E, odr_oo_t<0x0008'C09C> > PORTE;
	typedef port_t<0x0008'C011, odr_xx_t<0x0008'C0A2> > PORTH;
	typedef port_t<0x0008'C012, odr_xx_t<0x0008'C0A4> > PORTJ;

}
