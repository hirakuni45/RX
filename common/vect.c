//=====================================================================//
/*! @file
    @brief  ハードウェアー・ベクター関係
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdlib.h>
#include "vect.h"

void (*interrupt_vectors[256])(void);

// null interrupt TASK
INTERRUPT_FUNC void null_task_(void)
{
}

INTERRUPT_FUNC void _rx_priviledged_exception_handler(void)
{
}

// Exception(Supervisor Instruction)
INTERRUPT_FUNC void _rx_access_exception_handler(void)
{
}

// Exception(Undefined Instruction)
INTERRUPT_FUNC void _rx_undefined_exception_handler(void)
{
}

// Exception(Floating Point)
INTERRUPT_FUNC void _rx_floating_exception_handler(void)
{
}

// NMI
INTERRUPT_FUNC void _rx_nonmaskable_exception_handler(void)
{
}

//-----------------------------------------------------------------//
/*!
	@brief	割り込み関数の設定
	@param[in]	task	割り込み関数
	@param[in]	idx		割り込みベクター番号
 */
//-----------------------------------------------------------------//
void set_interrupt_task(void (*task)(void), uint32_t idx)
{
	if(idx < 256) {
		if(task == NULL) {
			task = null_task_;
		}
		interrupt_vectors[idx] = task;
	}
}
