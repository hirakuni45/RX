#pragma once
//=====================================================================//
/*!	@file
	@brief	ドライバー @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <stdint.h>

#if defined(__cplusplus)
extern "C"{
#endif
	void open_timer(void);
	void close_timer(void);
	void reset_timer(void);
	uint16_t get_timer(void);
#if defined(__cplusplus)
};
#endif



#if 0

/******************************************************************************
Macro definitions
******************************************************************************/
typedef enum tagWaitTimerStatus {
	IS_NOT_OVER,
	IS_OVER
} WAIT_STATUS;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
#if defined(__cplusplus)
extern "C"{
#endif
extern void OpenTimer(void);
extern void CloseTimer(void);

extern WAIT_STATUS CheckTimer(void);
extern void api_timeoutstart(unsigned long);
extern void api_timeoutstop(void);
extern unsigned char api_timeoutchk(void);
//extern void WaitTimer(unsigned long ms);
#if defined(__cplusplus)
};
#endif

#endif
