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

/* 	Copyright (C) 2012 Renesas Electronics Corporation All rights reserved.  */

/*""FILE COMMENT""******************************************************************************
 * System Name	: ether driver
 * File Name	: timer.c
 * Version		: 1.00
 * Contents		: timer driver
 * Customer		: Standard
 * Model		: None
 * CPU			: RX63N
 * Compiler		: 
 * OS			: ---
 * Programmer	: 
 * Note			: 
 ***********************************************************************************************
 ***********************************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 30.09.2012 1.00 First Release
*""FILE COMMENT END""**************************************************************************/

/******************************************************************************
Includes <System Includes> , ÅgProject IncludesÅh
******************************************************************************/
#if defined(__GNUC__) || defined(GRSAKURA)
#include "../T4_src/t4define.h"
#endif
#include "rx64m/iodefine.h"
#include "timer.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define ICU_PRIORITY_LEVEL_TIMER 1

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
void OpenTimer(void);
void CloseTimer(void);
void StartTimer(void);
void StopTimer(void);

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
* Function Name	: OpenTimer
* Declaration	: void OpenTimer(void)
* Description	: This function starts with the setting of the Timer interrupt
* Arguments		: none
* Return value	: none
******************************************************************************/
void OpenTimer(void)
{
#ifndef GRSAKURA
	SYSTEM.PRCR.WORD = 0xA500;          /* protect off */
	SYSTEM.PRCR.WORD = 0xA502;          /* protect off */
#endif
	SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;
#ifndef GRSAKURA
	SYSTEM.PRCR.WORD = 0xA500;          /* protect on */
#endif
	/* ICU */
#if defined(__GNUC__) || defined(GRSAKURA)
	ICU.IER[03].BYTE |= 0x20;					/* IER03.IEN5=1 interrupt request is enabled */
    ICU.IPR[05].BYTE = ICU_PRIORITY_LEVEL_TIMER;    // set priority level
#else
	ICU.IER[03].BYTE |= 0x10;					// IER03.IEN4=1 interrupt request is enabled
    ICU.IPR[04].BYTE = ICU_PRIORITY_LEVEL_TIMER;    // set priority level
#endif

#if defined(__GNUC__) || defined(GRSAKURA)
    /* CMT1 */
    /*  5ms@48MHz : 6000/(48MHz/8)=6000/6MHz=1ms */
    CMT.CMSTR0.BIT.STR1 = 0;         // CMT1.CMCNT count is stopped
    CMT1.CMCR.WORD = 0x0040;          // CKS=00b,CMIE=1; PCLK/8,Compare match interrupt (CMIn) enabled
    CMT1.CMCOR = (F_PCKB / 8 / 100) - 1;       // (10ms)
#else
	/* CMT0 */
	/*	5ms@50MHz : 6250/(50MHz/8)=6250/6.25MHz=1ms	*/
	CMT.CMSTR0.WORD &= ~0x0001;				// CMT0.CMCNT count is stopped
	CMT0.CMCR.WORD = 0x0040;				// CKS=00b,CMIE=1; PCLK/8,Compare match interrupt (CMIn) enabled
	CMT0.CMCOR = 6250 * 10 - 1;					// (6250*10)-1 (10ms)
#endif
	StartTimer();
}

/******************************************************************************
* Function Name	: CloseTimer
* Declaration	: void CloseTimer(void)
* Description	: This function finishes a Timer interrupt
* Arguments		: none
* Return value	: none
******************************************************************************/
void CloseTimer(void)
{
#if defined(__GNUC__) || defined(GRSAKURA)
    /* ICU */
    ICU.IER[03].BYTE &= ~0x20;              // IER03.IEN5=0 interrupt request is disabled
    ICU.IPR[05].BYTE = 0;                   // interrupt prohibited
    /* CMT0 */
    CMT.CMSTR0.BIT.STR1 = 0;               // CMT1.CMCNT count is stopped
#else
    /* ICU */
    ICU.IER[03].BYTE &= ~0x10;              // IER03.IEN4=0 interrupt request is disabled
	ICU.IPR[04].BYTE = 0;						// interrupt prohibited
    /* CMT0 */
    CMT.CMSTR0.WORD &= ~0x0001;             // CMT0.CMCNT count is stopped
#endif
}

/******************************************************************************
* Function Name	: StartTimer
* Declaration	: void StartTimer(void)
* Description	: This function starts a Timer interrupt
* Arguments		: none
* Return value	: none
******************************************************************************/
void StartTimer(void)
{
#if defined(__GNUC__) || defined(GRSAKURA)
    CMT1.CMCNT = 0;                     // clear counter
    CMT.CMSTR0.BIT.STR1 = 1;           // CMT1.CMCNT count is started
#else
	CMT0.CMCNT = 0;						// clear counter
	CMT.CMSTR0.WORD |= 0x0001;			// CMT0.CMCNT count is started
#endif
}

/******************************************************************************
* Function Name	: StopTimer
* Declaration	: void StopTimer(void)
* Description	: This function stops a Timer interrupt
* Arguments		: none
* Return value	: none
******************************************************************************/
void StopTimer(void)
{
#if defined(__GNUC__) || defined(GRSAKURA)
	CMT.CMSTR0.BIT.STR1 = 0;			// CMT1.CMCNT count is stopped
#else
    CMT.CMSTR0.WORD &= ~0x0001;         // CMT0.CMCNT count is stopped
#endif
}

/* FILE END*/
