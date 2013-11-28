//=====================================================================//
/*!	@file
	@brief	RX62N, RX621, RX63T グループ・CMT I/O 制御 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "cmt_io.hpp"

namespace device {

	void (*CMT_task[4])();
	volatile uint32_t CMT_counter[4];

	INTERRUPT_FUNC void task_CMT0()
	{
		++CMT_counter[0];
		if(CMT_task[0]) (*CMT_task[0])();
		ICU::IR.CMI0 = 0;
	}


	INTERRUPT_FUNC void task_CMT1()
	{
		++CMT_counter[1];
		if(CMT_task[1]) (*CMT_task[1])();
		ICU::IR.CMI1 = 0;
	}


	INTERRUPT_FUNC void task_CMT2()
	{
		++CMT_counter[2];
		if(CMT_task[2]) (*CMT_task[2])();
		ICU::IR.CMI2 = 0;
	}


	INTERRUPT_FUNC void task_CMT3()
	{
		++CMT_counter[3];
		if(CMT_task[3]) (*CMT_task[3])();
		ICU::IR.CMI3 = 0;
	}
}
