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
 * File Name    : r_usb_hhid_api.c
 * Description  : Host HID class driver code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 "R_USB_HhidDriverRelease","R_USB_HhidTransferEnd","R_USB_HhidChangeDeviceState"
 *                           "R_USB_HhidGetReportLength","R_USB_HhidClassRequest","R_USB_HhidPipeTransfer" is deleted.
 *         : 31.03.2018 1.23 Supporting Smart Configurator 
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_reg_access.h"

#include "r_usb_hhid_if.h"
#include "r_usb_hhid.h"

/******************************************************************************
 Renesas Abstracted USB Driver functions
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_HhidGetType
Description     : Get HID protocol.(USB Mouse/USB Keyboard/Protocon non.)
Arguments       : usb_ctrl_t *p_ctrl    : Pointer to usb_ctrl_t structure
                : uint8_t *p_type       : Address for stored HID protocol value.
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t R_USB_HhidGetType(usb_ctrl_t *p_ctrl, uint8_t *p_type)
{
    usb_err_t   err;
    usb_info_t  info;
    usb_utr_t   utr;

    utr.ip = p_ctrl->module;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if ((USB_NULL == p_ctrl) || (USB_NULL == p_type))
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if( (USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) )
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)
    if( USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T) */
#endif /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    err = R_USB_GetInformation(p_ctrl, &info);
    if ((USB_SUCCESS != err) || (USB_STS_CONFIGURED != info.status))
    {
        return USB_ERR_NG;
    }
    *p_type = usb_hhid_get_hid_protocol( p_ctrl->module, p_ctrl->address );
    return USB_SUCCESS;

}
/******************************************************************************
 End of function R_USB_HhidGetType
 ******************************************************************************/


/******************************************************************************
Function Name   : R_USB_HhidGetMxps
Description     : Obtains max packet size for the connected HID device
                : The max packet size is set to the area
                : Set the direction (USB_IN/USB_OUT)
Arguments       : usb_ctrl_t *p_ctrl    : Pointer to usb_ctrl_t structure area
                : uint16_t *p_mxps      : Pointer to the area to store the max package size
                : uint8_t dir           : Transfer direction
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t R_USB_HhidGetMxps(usb_ctrl_t *p_ctrl, uint16_t *p_mxps, uint8_t dir)
{
    usb_err_t   err;
    usb_info_t  info;
    usb_utr_t   utr;
    uint16_t    pipe;
    uint16_t    pipe_bit_map;

    utr.ip = p_ctrl->module;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if ((USB_NULL == p_ctrl) || (USB_NULL == p_mxps))
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if( (USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) )
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)
    if( USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T) */
#endif /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    err = R_USB_GetInformation(p_ctrl, &info);
    if ((USB_SUCCESS != err) || (USB_STS_CONFIGURED != info.status))
    {
        return USB_ERR_NG;
    }

    if (USB_IN == dir)
    {
        pipe = usb_hstd_get_pipe_no (p_ctrl->module, p_ctrl->address, USB_HHID, USB_EP_INT, USB_PIPE_DIR_IN);

    }
    else if (USB_OUT == dir)
    {
        pipe = usb_hstd_get_pipe_no (p_ctrl->module, p_ctrl->address, USB_HHID, USB_EP_INT, USB_PIPE_DIR_OUT);

    }
    else
    {
#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
        return USB_ERR_PARA;
#else  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */
        return USB_ERR_NG;
#endif /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */
    }

    err = R_USB_GetUsePipe (p_ctrl, &pipe_bit_map);
    if (USB_SUCCESS != err)
    {
        return USB_ERR_NG;
    }

    if (0 == ((1 << pipe) & pipe_bit_map))
    {
        return USB_ERR_NG;
    }

    *p_mxps = usb_cstd_get_maxpacket_size(&utr, pipe);
    return USB_SUCCESS;

}
/******************************************************************************
 End of function R_USB_HhidGetMxps
 ******************************************************************************/



/******************************************************************************
 End  Of File
 ******************************************************************************/
