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
 * Copyright (C) 2014(2017) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_hmsc_if.h
 * Description  : Interface file for USB HMSC API
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Add typedef "usb_csw_result_t", Delete not use API functions.
 ***********************************************************************************************************************/

#ifndef USB_HMSC_IF_H
#define USB_HMSC_IF_H

/*****************************************************************************
Macro definitions
******************************************************************************/

/*****************************************************************************
 Enum definitions
 ******************************************************************************/
typedef enum
{
    /*--- SFF-8070i command define ---*/
    USB_ATAPI_TEST_UNIT_READY = 0x00u,
    USB_ATAPI_REQUEST_SENSE = 0x03u,
    USB_ATAPI_FORMAT_UNIT = 0x04u,
    USB_ATAPI_INQUIRY = 0x12u,
    USB_ATAPI_MODE_SELECT6 = 0x15u,
    USB_ATAPI_MODE_SENSE6 = 0x1Au,
    USB_ATAPI_START_STOP_UNIT = 0x1Bu,
    USB_ATAPI_PREVENT_ALLOW = 0x1Eu,
    USB_ATAPI_READ_FORMAT_CAPACITY = 0x23u,
    USB_ATAPI_READ_CAPACITY = 0x25u,
    USB_ATAPI_READ10 = 0x28u,
    USB_ATAPI_WRITE10 = 0x2Au,
    USB_ATAPI_SEEK = 0x2Bu,
    USB_ATAPI_WRITE_AND_VERIFY = 0x2Eu,
    USB_ATAPI_VERIFY10 = 0x2Fu,
    USB_ATAPI_MODE_SELECT10 = 0x55u,
    USB_ATAPI_MODE_SENSE10 = 0x5Au,
}usb_atapi_t;

typedef enum
{
    USB_CSW_SUCCESS = 0x00u,
    USB_CSW_FAIL    = 0x01u,
    USB_CSW_PHASE   = 0x02u,
}usb_csw_result_t;

/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/
usb_err_t       R_USB_HmscStrgCmd (usb_ctrl_t *p_ctrl, uint8_t *p_buf, uint16_t command);
usb_err_t       R_USB_HmscGetDriveNo (usb_ctrl_t *p_ctrl, uint8_t *p_drive);

#endif /* USB_HMSC_IF_H */
