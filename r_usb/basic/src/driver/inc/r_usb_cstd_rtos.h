/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.    
*******************************************************************************/
/*******************************************************************************
* File Name    : r_usb_cstd_rtos.h
* Version      : 1.0
* Description  : Header file of USB with freeRTOS.
******************************************************************************/
/*****************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.06.2016 1.00     First Release
*         : 16.11.2018 1.24     Supporting RTOS Thread safe
******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#ifndef FREERTOS_USB_TASK_H_
#define FREERTOS_USB_TASK_H_

/******************************************************************************
Macro definitions
******************************************************************************/
/** Size of a queue **/
#define QUEUE_SIZE              (10)

/** USB task's priority **/
#define HCD_TSK_PRI             (11)
#define HUB_TSK_PRI             (9)
#define MGR_TSK_PRI             (10)
#define PCD_TSK_PRI             (11)
#define PMSC_TSK_PRI            (8)
#define HCDC_TSK_PRI            (8)
#define HHID_TSK_PRI            (8)

/** USB task stack size in words **/
#define HCD_STACK_SIZE          (512)
#define HUB_STACK_SIZE          (512)
#define MGR_STACK_SIZE          (512)
#define PCD_STACK_SIZE          (512)
#define PMSC_STACK_SIZE         (512)
#define HCDC_STACK_SIZE         (512)
#define HHID_STACK_SIZE         (512)


/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum e_usb_rtos_err
{
    UsbRtos_Success = 0,        // Successful
    UsbRtos_Err_Init_Mbx,       // Failure of Mailbox Creation
    UsbRtos_Err_Init_Mpl,       // Failure of Memory Pool Creation
    UsbRtos_Err_Init_Tsk,       // Failure of Task Creation
} usb_rtos_err_t;

/******************************************************************************
Exported global variables
******************************************************************************/
extern QueueHandle_t *g_mbx_table[];
extern QueueHandle_t *g_mpl_table[];

/******************************************************************************
Exported global functions (to be accessed by other files)
******************************************************************************/
usb_rtos_err_t usb_rtos_configuration(void);

extern void usb_hstd_hcd_task(usb_vp_int_t);
extern void usb_hhub_task(usb_vp_int_t);
extern void usb_hstd_mgr_task(usb_vp_int_t);

extern void usb_pstd_pcd_task(void);

#endif /* FREERTOS_USB_TASK_H_ */
