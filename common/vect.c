//=====================================================================//
/*! @file
    @brief  ハードウェアー・ベクター関係
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <stdlib.h>
#include "common/vect.h"

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
	@brief	割り込みの初期化
 */
//-----------------------------------------------------------------//
void init_interrupt(void)
{
	// 割り込みベクターテーブルの初期化
	for(int i = 0; i < 256; ++i) {
		interrupt_vectors[i] = null_task_;
	}
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
