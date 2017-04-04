#pragma once
/************************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY
* DISCLAIMED.


* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this
* software and to discontinue the availability of this software.
* By using this software, you agree to the additional terms and
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
************************************************************************************/

/* 	Copyright (C) 2010 Renesas Electronics Corporation All rights reserved.  */

/*""FILE COMMENT""******************************************************************************
 * System Name	: ether driver
 * File Name	: timer.h
 * Version		: 1.00
 * Contents		: timer driver
 * Customer		: Standard
 * Model		: None
 * CPU			: RX610
 * Compiler		: 
 * OS			: ---
 * Programmer	: 
 * Note			: 
 ***********************************************************************************************/
/* ***********************************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 21.06.2010 1.00 First Release
 *""FILE COMMENT END""**************************************************************************/

#include <stdint.h>

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
extern void reset_timer(void);
extern uint16_t get_timer(void);
extern WAIT_STATUS CheckTimer(void);
extern void api_timeoutstart(unsigned long);
extern void api_timeoutstop(void);
extern unsigned char api_timeoutchk(void);
//extern void WaitTimer(unsigned long ms);
#if defined(__cplusplus)
};
#endif
