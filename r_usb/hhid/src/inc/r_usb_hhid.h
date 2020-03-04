/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2014(2018) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_hhid.h
 * Description  : USB Host HID class driver header
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.21 hid_class_request_complete is deleted.
 *         : 30.09.2017 1.22 Change function name ""->""
 *                           "hid_suspended"->"usb_hid_suspended"
 *                           "hid_configured"->"usb_hid_configured"
 *                           "hid_detach"->"usb_hid_detach"
 *                           "hid_resume_complete"->"usb_hid_resume_complete"
 *                           "hid_class_request" is deleted
 *                           "usb_hhid_get_pipetbl" is added.
 *                           "usb_hhid_get_hid_protocol" is added.
 *                           "usb_hhid_set_pipe_registration" is added.
 *                           "usb_hhid_class_check" is added.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 16.11.2018 1.24 Supporting RTOS
 ***********************************************************************************************************************/
#ifndef R_USB_HHID_H
#define R_USB_HHID_H

#include "r_usb_typedef.h"

/*****************************************************************************
 Macro definitions
 ******************************************************************************/
/* ----- DESCRIPTOR Types ----- */
#define USB_HID_DT_TYPE_GETREPORT           ((uint8_t)0x01)     /* Report Type Input */
#define USB_HID_DT_TYPE_SETREPORT           ((uint8_t)0x02)     /* Report Type Output */
#define USB_HID_DT_TYPE_HIDDESCRIPTOR       ((uint8_t)0x21)     /* HID descriptor type */
#define USB_HID_DT_TYPE_RPTDESCRIPTOR       ((uint8_t)0x22)     /* Report descriptor type */

/* ----- Subclass Codes ----- */
#define USB_HID_IFSUB_NONE                  ((uint8_t)0x00)     /* No Subclass */
#define USB_HID_IFSUB_BOOT                  ((uint8_t)0x01)     /* Boot Interface Subclass */

/* Report Type set */
#define USB_HID_SET_DT_TYPE(v)              ((v) << 8)

#define USB_HHID_CLSDATASIZE                (512)
#define USB_MAX_DEVICE                      (3)                 /* 1-3 */

#if (BSP_CFG_RTOS_USED)
/* Host HID Task */
#define USB_HHID_TSK                        (USB_TID_9)         /* Task ID */
#define USB_HHID_MBX                        (USB_HHID_TSK)      /* Mailbox ID */
#define USB_HHID_MPL                        (USB_HHID_TSK)      /* Memorypool ID */
#else /* (BSP_CFG_RTOS_USED) */
/* Host HID Task */
#define USB_HHID_TSK                        (USB_TID_7)         /* Task ID */
#define USB_HHID_MBX                        (USB_HHID_TSK)      /* Mailbox ID */
#define USB_HHID_MPL                        (USB_HHID_TSK)      /* Memorypool ID */
#endif /* (BSP_CFG_RTOS_USED) */

#define USB_B_INTERFACE_PROTOCOL            (7)                 /* Interface Descriptor bInterfaceProtocol */

/*****************************************************************************
 Enumerated Types
 ******************************************************************************/
/* Host HID Task Command */
typedef enum
{
    USB_HHID_TCMD_OPEN
} usb_hhid_tcmd_t;

/* Enumeration Sequence */
typedef enum
{
    /* Enumeration Sequence Complete */
    USB_HHID_ENUM_COMPLETE = 0,

    /* Enumeration Sequence String Descriptor #0 receive request */
    USB_HHID_ENUM_STR_DT0_REQ,

    /* Enumeration Sequence String Descriptor #0 Receive complete */
    USB_HHID_ENUM_STR_DT0_WAIT,

    /* StringDescriptor iProduct Receive complete */
    USB_HHID_ENUM_STR_IPRODUCT_WAIT
} usb_hhid_enum_seq_t;

/*****************************************************************************
 Struct definition
 ******************************************************************************/

/******************************************************************************
 Exported global variables
 ******************************************************************************/
extern uint16_t g_usb_hhid_protocol[USB_NUM_USBIP][USB_MAXDEVADDR];         /* HID Device protocol(Mouse/Keyboard) */
extern uint16_t g_usb_hhid_num_endpoint[USB_NUM_USBIP][USB_MAXDEVADDR];     /* Num Endpoints */
extern uint16_t g_usb_hhid_outpipe_support[USB_NUM_USBIP][USB_MAXDEVADDR];  /* OUT pipe support */
extern uint16_t g_usb_hhid_devaddr[];                                       /* Device Address */
extern uint16_t g_usb_hhid_speed[];                                         /* Device speed */
extern uint16_t g_usb_hhid_enum_seq[];                                      /* Enumeration Sequence */
extern uint8_t *g_p_usb_hhid_interface_table[];                             /* Interface Descriptor Table */
extern uint8_t *g_p_usb_hhid_device_table[];                                /* Device Descriptor Table */
extern uint8_t *g_p_usb_hhid_config_table[];                                /* Configuration Descriptor Table */


/*****************************************************************************
 Public Functions
 ******************************************************************************/
/* Functions */
void        usb_hhid_task (usb_vp_int_t stacd);
uint16_t    usb_hhid_pipe_info (usb_utr_t *ptr, uint8_t *table, uint16_t speed, uint16_t length);
uint16_t    usb_hhid_get_string_desc (usb_utr_t *ptr, uint16_t addr, uint16_t string, usb_cb_t complete);
void        usb_hid_suspended (usb_utr_t *ptr, uint16_t devadr);
void        usb_hid_configured (usb_utr_t *ptr, uint16_t dev_addr, uint16_t data2);
void        usb_hid_detach (usb_utr_t *ptr, uint16_t devadr, uint16_t data2);
void        usb_hid_resume_complete (usb_utr_t *ptr, uint16_t devadr, uint16_t data2);

uint8_t     usb_hhid_get_hid_protocol (uint16_t ipno, uint16_t devadr);
void        usb_hhid_set_pipe_registration (usb_utr_t *ptr, uint16_t devadr);
void        usb_hhid_class_check (usb_utr_t *ptr, uint16_t **table);

#endif  /* R_USB_HHID_H */

/******************************************************************************
 End  Of File
 ******************************************************************************/
