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

// Exception(Supervisor Instruction)
INTERRUPT_FUNC void super_visor_inst_(void)
{
}

// Exception(Undefined Instruction)
INTERRUPT_FUNC void undefined_inst_(void)
{
}

// Exception(Floating Point)
INTERRUPT_FUNC void floating_point_(void)
{
}

// NMI
INTERRUPT_FUNC void non_maskable_interrupt_(void)
{
}


INTERRUPT_FUNC void power_on_reset(void);


#define FIXEDVECT_SECTION __attribute__ ((section (".fvectors")))

void (*Fixed_Vectors[])(void) FIXEDVECT_SECTION = {
//;0xffffffd0  Exception(Supervisor Instruction)
    super_visor_inst_,
//;0xffffffd4  Reserved
    null_task_,
//;0xffffffd8  Reserved
    null_task_,
//;0xffffffdc  Exception(Undefined Instruction)
    undefined_inst_,
//;0xffffffe0  Reserved
    null_task_,
//;0xffffffe4  Exception(Floating Point)
    floating_point_,
//;0xffffffe8  Reserved
    null_task_,
//;0xffffffec  Reserved
    null_task_,
//;0xfffffff0  Reserved
    null_task_,
//;0xfffffff4  Reserved
    null_task_,
//;0xfffffff8  NMI
    non_maskable_interrupt_,
//;0xfffffffc  RESET
	power_on_reset
};

