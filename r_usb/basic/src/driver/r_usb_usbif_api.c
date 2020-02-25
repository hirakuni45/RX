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
* Copyright (C) 2016(2019) Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_usb_usbif_api.c
* Description  : USB Host and Peripheral Driver API code. HCD(Host Control Driver) PCD (Peripheral Control Driver)
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.09.2015 1.00 First Release
*         : 30.09.2017 1.22 Update Argument Checking
*         : 31.03.2018 1.23 Supporting Smart Configurator
*         : 16.11.2018 1.24 Supporting RTOS Thread safe
*         : 31.05.2019 1.26 Added support for GNUC and ICCRX.
*         : 30.07.2019 1.27 RX72M is added.
***********************************************************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <string.h>

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"
#include "r_usb_basic_config.h"

#if defined(USB_CFG_HCDC_USE)
#include "r_usb_hcdc_if.h"
#endif /* defined(USB_CFG_HCDC_USE) */

#if defined(USB_CFG_HHID_USE)
#include "r_usb_hhid_if.h"
#endif /* defined(USB_CFG_HHID_USE) */

#if defined(USB_CFG_HMSC_USE)
#include "r_usb_hmsc_if.h"
#endif /* defined(USB_CFG_HMSC_USE) */

#if defined(USB_CFG_PHID_USE)
#include "r_usb_phid_if.h"
#endif /* defined(USB_CFG_PHID_USE) */

#if defined(USB_CFG_PCDC_USE)
#include "r_usb_pcdc_if.h"
#endif /* defined(USB_CFG_PCDC_USE) */

/******************************************************************************
 Exported global variables (to be accessed by other files)
******************************************************************************/
#if (BSP_CFG_RTOS_USED == 0)
    usb_event_t     g_usb_cstd_event;
    uint16_t        g_usb_change_device_state[USB_NUM_USBIP];
#else /*(BSP_CFG_RTOS_USED == 0)*/
    usb_ctrl_t      g_usb_cstd_event[USB_EVENT_MAX];
    usb_callback_t  *g_usb_apl_callback;
#endif /*(BSP_CFG_RTOS_USED == 0)*/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
usb_utr_t       g_usb_hdata[USB_NUM_USBIP][USB_MAXPIPE_NUM + 1];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
usb_utr_t       g_usb_pdata[USB_MAXPIPE_NUM + 1];

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

uint16_t        g_usb_usbmode;
uint16_t        g_usb_open_class[USB_NUM_USBIP];



/******************************************************************************
 Private global variables and functions
******************************************************************************/
static uint8_t  is_init[USB_NUM_USBIP] =
{
    USB_NO,
#if USB_NUM_USBIP == 2
    USB_NO,
#endif
};

#if (BSP_CFG_RTOS_USED == 1)

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static uint8_t  gs_usb_suspend_ing[USB_NUM_USBIP] =
{
    USB_NO,
#if USB_NUM_USBIP == 2
    USB_NO,
#endif
};
#endif /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

static uint8_t  gs_usb_resume_ing[USB_NUM_USBIP] =
{
    USB_NO,
#if USB_NUM_USBIP == 2
    USB_NO,
#endif
};
#endif /*(BSP_CFG_RTOS_USED == 1)*/

/******************************************************************************
Renesas Abstracted Peripheral Driver API functions
******************************************************************************/

/*****************************************************************************
* Function Name: R_USB_GetVersion
* Description  : Returns the version of this module. The version number is
*                encoded such that the top two bytes are the major version
*                number and the bottom two bytes are the minor version number.
* Arguments    : none
* Return Value : version number
******************************************************************************/
uint32_t R_USB_GetVersion(void)
{
    uint32_t version = 0;

    version = (USB_VERSION_MAJOR << 16) | USB_VERSION_MINOR;

    return version;
}
/******************************************************************************
 End of function R_USB_GetVersion
 ******************************************************************************/

#if (BSP_CFG_RTOS_USED == 0)
/******************************************************************************
Function Name   : R_USB_GetEvent
Description     : Get event.
Arguments       : usb_ctrl_t *p_ctrl: control structure for USB API.
Return value    : event code.
******************************************************************************/
usb_status_t R_USB_GetEvent(usb_ctrl_t *p_ctrl)
{
    usb_status_t    event = USB_STS_NONE;

    usb_cstd_usb_task();
    if ( g_usb_cstd_event.write_pointer != g_usb_cstd_event.read_pointer )
    {
        *p_ctrl = g_usb_cstd_event.ctrl[g_usb_cstd_event.read_pointer];
        event = g_usb_cstd_event.code[g_usb_cstd_event.read_pointer];
        g_usb_cstd_event.read_pointer++;
        if (g_usb_cstd_event.read_pointer >= USB_EVENT_MAX)
        {
            g_usb_cstd_event.read_pointer = 0;
        }
    }
    return event;
}  /* End of function R_USB_GetEvent() */
#endif
/******************************************************************************
 End of function R_USB_GetEvent
 ******************************************************************************/

#if  (BSP_CFG_RTOS_USED == 1)
/******************************************************************************
Function Name   : R_USB_Callback
Description     : Registration of the callback function
Arguments       : usb_callback_t    *p_callback : Pointer to the callback function for the application
Return value    : None
******************************************************************************/
void    R_USB_Callback(usb_callback_t *p_callback)
{
    g_usb_apl_callback = p_callback;
} /* End of function R_USB_Callback() */
#endif /* (BSP_CFG_RTOS_USED == 1)*/

/******************************************************************************
Function Name   : R_USB_Open
Description     : Start of USB Driver.
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
                : usb_cfg_t     *cfg    : Pointer to usb_cfg_t structure
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t R_USB_Open( usb_ctrl_t *ctrl, usb_cfg_t *cfg )
{
    usb_err_t   err;

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t   utr;

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    /* Argument Checking */
    if ((USB_IP0 != ctrl->module) && (USB_IP1 != ctrl->module))
    {
        return USB_ERR_PARA;
    }

    if ((( USB_HS != cfg->usb_speed ) && ( USB_FS != cfg->usb_speed )) && ( USB_LS != cfg->usb_speed )
            && (USB_HOST != cfg->usb_mode))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* #if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

#if defined(BSP_MCU_RX63N)
    if ((USB_IP1 == ctrl->module) && (USB_HOST == cfg->usb_mode))
    {
        return USB_ERR_PARA;
    }
#endif /* #if defined(BSP_MCU_RX63N) */

    switch (ctrl->type)
    {
        case USB_PCDC:
        case USB_PHID:
        case USB_PVND:
        case USB_PMSC:
            if (USB_PERI != cfg->usb_mode)
            {
                return USB_ERR_PARA;
            }
            if ( (USB_LS == cfg->usb_speed) || (USB_NULL == cfg->p_usb_reg) )
            {
                return USB_ERR_PARA;
            }
#if defined(BSP_MCU_RX71M)
  #if USB_IP0 == USB_CFG_USE_USBIP
            if (USB_HS == cfg->usb_speed)
            {
                return USB_ERR_PARA;
            }
  #endif  /* USB_IP0 == USB_CFG_USE_USBIP */
#else   /* defined(BSP_MCU_RX71M) */
            if ( USB_HS == cfg->usb_speed )
            {
                return USB_ERR_PARA;
            }
#endif  /* defined(BSP_MCU_RX71M) */
        break;

        /* Host */
        case USB_HCDC:
        case USB_HHID:
        case USB_HVND:
        case USB_HMSC:
#if defined(BSP_MCU_RX630)
            return USB_ERR_PARA;
#else  /* defined(BSP_MCU_RX630) */
            if (USB_HOST != cfg->usb_mode)
            {
                return USB_ERR_PARA;
            }
  #if defined(BSP_MCU_RX71M)
            if ((USB_HS == cfg->usb_speed) && (USB_IP1 != ctrl->module))
            {
                return USB_ERR_PARA;
            }
  #else  /* defined(BSP_MCU_RX71M) */
            if ( USB_HS == cfg->usb_speed )
            {
                return USB_ERR_PARA;
            }
  #endif /* defined(BSP_MCU_RX71M) */
#endif  /* defined(BSP_MCU_RX630) */
        break;

        default:
            return USB_ERR_PARA;
        break;
    }
#endif /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    if (USB_YES == is_init[ctrl->module])
    {
        return USB_ERR_BUSY;
    }

#if USB_NUM_USBIP == 2
    if ((USB_NO == is_init[USB_IP0]) && (USB_NO == is_init[USB_IP1]))
    {
#endif /* USB_NUM_USBIP == 2 */

    memset((void *)&g_usb_cstd_event, 0, sizeof(g_usb_cstd_event));

#if USB_NUM_USBIP == 2
    }
#endif /* USB_NUM_USBIP == 2 */

    is_init[ctrl->module] = USB_YES;

    g_usb_open_class[ctrl->module] = 0;

#if (BSP_CFG_RTOS_USED == 0)
    g_usb_change_device_state[ctrl->module] = 0;
#endif /* BSP_CFG_RTOS_USED == 0 */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    g_usb_hstd_use_pipe[ctrl->module] = 0;
    memset((void *)&g_usb_hdata[ctrl->module], 0, sizeof(usb_utr_t));
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    memset((void *)&g_usb_pdata, 0, ((USB_MAXPIPE_NUM+1) * sizeof(usb_utr_t)));
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

    if (USB_HOST == cfg->usb_mode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        g_usb_usbmode = USB_HOST;

        utr.ip  = ctrl->module;
        utr.ipp = usb_hstd_get_usb_ip_adr( (uint8_t)ctrl->module  );    /* Get the USB IP base address. */

        err = usb_module_start( (uint8_t)utr.ip );
        if (USB_SUCCESS == err)
        {
            /* USB driver initialization */
            usb_hdriver_init( &utr, cfg );

            /* Setting MCU(USB interrupt init) register */
            usb_cpu_usbint_init((uint8_t)utr.ip);

            /* Setting USB relation register  */
            hw_usb_hmodule_init(ctrl); /* MCU */

#if defined(USB_CFG_HHID_USE)
            if (USB_HHID == ctrl->type)
            {
                hw_usb_hset_trnensel(&utr);
            }
#endif  /* defined(USB_CFG_HHID_USE) */

#if USB_CFG_TYPEC == USB_CFG_DISABLE
            usb_hstd_vbus_control(&utr, (uint16_t)USB_VBON);

  #if USB_CFG_BC == USB_CFG_DISABLE
            usb_cpu_delay_xms((uint16_t)100);    /* 100ms wait */

  #endif /*  USB_CFG_BC == USB_CFG_DISABLE */
#else   /*  USB_CFG_TYPEC == USB_CFG_DISABLE */
            usb_hstd_vbus_control(&utr, (uint16_t)USB_VBOFF);

#endif /*  USB_CFG_TYPEC == USB_CFG_DISABLE */
        }

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        g_usb_usbmode = USB_PERI;
        ctrl->module = USB_CFG_USE_USBIP;

        /* USB module start setting */
        err = usb_module_start(USB_CFG_USE_USBIP);
        if (USB_SUCCESS == err)
        {
            /* USB driver initialization */
            usb_pdriver_init( ctrl, cfg );

            /* Setting MCU(USB interrupt init) register */
            usb_cpu_usbint_init(USB_CFG_USE_USBIP);

            /* Setting USB relation register  */
            hw_usb_pmodule_init();

#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
            if (USB_HS == cfg->usb_speed)
            {
                hw_usb_set_hse(USB_NULL);
            }
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            if ( USB_ATTACH == usb_pstd_chk_vbsts() )
            {
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
                hw_usb_set_cnen();
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
                usb_cpu_delay_xms((uint16_t)10);
                hw_usb_pset_dprpu();
            }
        }
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    if (USB_SUCCESS == err)
    {
        g_usb_open_class[ctrl->module] |= (1 << ctrl->type);      /* Set USB Open device class */
        if (USB_PCDC == ctrl->type)
        {
            g_usb_open_class[ctrl->module] |= (1 << USB_PCDCC);   /* Set USB Open device class */
        }
        if (USB_HCDC == ctrl->type)
        {
            g_usb_open_class[ctrl->module] |= (1 << USB_HCDCC);   /* Set USB Open device class */
        }
    }

    return err;
}
/******************************************************************************
 End of function R_USB_Open
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_Close
Description     : End of USB Driver.
Arguments       : usb_ctrl_t *p_ctrl    : Pointer to usb_ctrl_t structure
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t R_USB_Close(usb_ctrl_t *p_ctrl)
{
    usb_err_t   ret_code;
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t   utr;
    uint8_t     class_code;
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_NULL == p_ctrl)
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif  /* #if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */
    
#if defined(BSP_MCU_RX63N)
    if ((USB_IP1 == p_ctrl->module) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX63N) */

    if (USB_HOST == g_usb_usbmode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        switch(p_ctrl->type)
        {
            case USB_HCDC:
                class_code = (uint8_t)USB_IFCLS_CDC;
            break;
            
            case USB_HHID:
                class_code = (uint8_t)USB_IFCLS_HID;
            break;
            
            case USB_HMSC:
                class_code = (uint8_t)USB_IFCLS_MAS;
            break;
            
            case USB_HVND:
                class_code = (uint8_t)USB_IFCLS_VEN;
            break;
            
            default:
                return USB_ERR_PARA;
            break;
        }
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    ret_code = usb_module_stop(p_ctrl->module);
    if (USB_SUCCESS == ret_code)
    {
        is_init[p_ctrl->module] = USB_NO;

        if (USB_HOST == g_usb_usbmode)
        {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
            utr.ip = p_ctrl->module;
            utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

            usb_hstd_driver_release(&utr, class_code);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

            usb_pstd_driver_release();   /* Clear the information registered in the structure usb_pcdreg_t. */
            usb_pstd_clr_pipe_table();

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
        }

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        g_usb_open_class[p_ctrl->module] &= (~(1 << p_ctrl->type));     /* Clear USB Open device class */
        if (USB_PCDC == p_ctrl->type)
        {
            g_usb_open_class[p_ctrl->module] &= (~(1 << USB_PCDCC));    /* Clear USB Open device class */
        }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_HCDC == p_ctrl->type)
        {
            g_usb_open_class[p_ctrl->module] &= (~(1 << USB_HCDCC));    /* Clear USB Open device class */
        }
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    }
    else
    {
        ret_code = USB_ERR_NOT_OPEN;
    }

    return ret_code;
}
/******************************************************************************
 End of function R_USB_Close
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_Read
Description     : USB Data Receive process.
Arguments       : usb_ctrl_t    *p_ctrl     : Pointer to usb_ctrl_t structure
                : uint8_t       *buf        : Pointer to the data buffer areatransfer data address
                : uint32_t      size        : Read size
Return value    : usb_err_t error code      : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t R_USB_Read(usb_ctrl_t *p_ctrl, uint8_t *buf, uint32_t size)
{
    usb_info_t  info;
    usb_er_t    err;
    usb_err_t   result = USB_ERR_NG;

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (((USB_NULL == p_ctrl) || (USB_NULL == buf)) || (USB_NULL == size))
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

#if defined(BSP_MCU_RX63N)
    if (USB_IP1 == p_ctrl->module && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif

    if ((USB_PCDCC == p_ctrl->type) || (USB_PVND == p_ctrl->type) || (USB_HVND == p_ctrl->type)
        || (USB_HMSC == p_ctrl->type) || (USB_PMSC == p_ctrl->type))
    {
        return USB_ERR_PARA;
    }

    if (USB_REQUEST != p_ctrl->type)
    {
        if (USB_NULL == (g_usb_open_class[p_ctrl->module] & (1 << p_ctrl->type))) /* Check USB Open device class */
        {
            return USB_ERR_PARA;
        }
    }

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED == info.status)
    {
        if (USB_REQUEST == p_ctrl->type)
        {
            err = usb_ctrl_read( p_ctrl, buf, size );
        }
        else
        {
            err = usb_data_read( p_ctrl, buf, size );
        }

        if (USB_OK == err)
        {
            result = USB_SUCCESS;
        }
        else if (USB_QOVR == err)
        {
            result = USB_ERR_BUSY;
        }
        else
        {
            /* Noting */
        }
    }
    return result;
}
/******************************************************************************
 End of function R_USB_Read
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_Write
Description     : USB Data send process.
Arguments       : usb_ctrl_t    *p_ctrl     : Pointer to usb_ctrl_t structure
                : uint8_t       *buf        : Pointer to the data buffer areatransfer data address
                : uint32_t      size        : Write size
Return value    : usb_err_t error code      : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t R_USB_Write(usb_ctrl_t *p_ctrl, uint8_t *buf, uint32_t size)
{
    usb_info_t  info;
    usb_er_t    err;
    usb_err_t   result = USB_ERR_NG;

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if ((USB_NULL == p_ctrl) || ((USB_NULL == buf) && (0 != size)))
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

#if defined(BSP_MCU_RX63N)
    if (USB_IP1 == p_ctrl->module && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif

    if ((USB_HCDCC == p_ctrl->type) || (USB_PVND == p_ctrl->type) || (USB_HVND == p_ctrl->type)
        || (USB_HMSC == p_ctrl->type) || (USB_PMSC == p_ctrl->type))
    {
        return USB_ERR_PARA;
    }

    if (USB_REQUEST != p_ctrl->type)
    {
        if (USB_NULL == (g_usb_open_class[p_ctrl->module] & (1 << p_ctrl->type)))      /* Check USB Open device class */
        {
            return USB_ERR_PARA;
        }
    }

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED == info.status)
    {
        if (USB_REQUEST == p_ctrl->type)
        {
            err = usb_ctrl_write( p_ctrl, buf, size );
        }
        else
        {
            err = usb_data_write( p_ctrl, buf, size );
        }

        if (USB_OK == err)
        {
            result = USB_SUCCESS;
        }
        else if (USB_QOVR == err)
        {
            result = USB_ERR_BUSY;
        }
        else
        {
            /* error */
        }
    }
    return result;
}
/******************************************************************************
 End of function R_USB_Write
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_Stop
Description     : USB Transfer stop
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
                : uint16_t      type    : Read(0)/Write(1)
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t    R_USB_Stop(usb_ctrl_t *p_ctrl, uint16_t type)
{
    usb_info_t  info;
    usb_er_t    err;

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_NULL == p_ctrl)
    {
        return USB_ERR_PARA;
    }

    if ((USB_WRITE != type) && (USB_READ != type))
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

#if defined(BSP_MCU_RX63N)
    if (USB_IP1 == p_ctrl->module && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif

    if ((USB_PVND == p_ctrl->type) || (USB_HVND == p_ctrl->type)
        || (USB_HMSC == p_ctrl->type) || (USB_PMSC == p_ctrl->type))
    {
        return USB_ERR_PARA;
    }
    
    if (((USB_HCDCC == p_ctrl->type) && (USB_WRITE == type))   ||
        ((USB_PCDCC == p_ctrl->type ) && (USB_READ == type)))
    {
        return USB_ERR_PARA;
    }

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    err = R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED != info.status)
    {
        return USB_ERR_NG;
    }

    if (USB_REQUEST == p_ctrl->type)
    {
        err = usb_ctrl_stop( p_ctrl);
    }
    else
    {
        err = usb_data_stop( p_ctrl, type);
    }

    if (USB_OK == err)
    {
        return USB_SUCCESS;
    }
    else if (USB_QOVR == err)
    {
        return USB_ERR_BUSY;
    }
    else
    {
        /* error */
    }

    return USB_ERR_NG;
}
/******************************************************************************
 End of function R_USB_Stop
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_Suspend
Description     : USB Suspend process for USB Host.
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t    R_USB_Suspend(usb_ctrl_t *p_ctrl)
{
#if USB_CFG_MODE == USB_CFG_PERI
    return USB_ERR_NG;              /* Support Host only. */

#else /* USB_CFG_MODE == USB_CFG_PERI */

    usb_err_t   ret_code = USB_SUCCESS;
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

    usb_utr_t   utr;
    usb_info_t  info;
    usb_er_t    err;

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    if (USB_PERI == g_usb_usbmode)
    {
        return USB_ERR_NG;              /* Support Host only. */
    }

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

#if defined(BSP_MCU_RX63N)
    if ((USB_IP1 == p_ctrl->module) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE

    if (USB_NULL == p_ctrl)
    {
        return USB_ERR_PARA;
    }

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    p_ctrl->address = USB_DEVICEADDR;

    R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED != info.status)
    {
        return USB_ERR_NG;
    }

    utr.ip = p_ctrl->module;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

#if (BSP_CFG_RTOS_USED == 0)
    if (USB_NULL != (g_usb_change_device_state[p_ctrl->module] & (1 << USB_STS_SUSPEND)))
    {
        return USB_ERR_BUSY;
    }

    err = usb_hstd_change_device_state(&utr, (usb_cb_t)&usb_hstd_suspend_complete,
                                       USB_DO_GLOBAL_SUSPEND, USB_DEVICEADDR);

    if (USB_OK == err)
    {
        g_usb_change_device_state[p_ctrl->module] |= (1 << USB_STS_SUSPEND);
    }
    else
    {
        ret_code = USB_ERR_NG;
    }
#else   /* (BSP_CFG_RTOS_USED == 0) */
    if (USB_YES == gs_usb_suspend_ing[p_ctrl->module])
    {
        return USB_ERR_BUSY;
    }
    else
    {
        gs_usb_suspend_ing[p_ctrl->module] = USB_YES;
    }

    err = usb_hstd_change_device_state(&utr, (usb_cb_t)&usb_hstd_suspend_complete,
                                       USB_DO_GLOBAL_SUSPEND, USB_DEVICEADDR);

    if (USB_OK != err)
    {
        ret_code = USB_ERR_NG;
    }

    gs_usb_suspend_ing[p_ctrl->module] = USB_NO;
#endif  /* (BSP_CFG_RTOS_USED == 0) */

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    return ret_code;
#endif /* USB_CFG_MODE == USB_CFG_PERI */
}
/******************************************************************************
 End of function R_USB_Suspend
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_Resume
Description     : USB Resume process(Host) and Remote wakeup process(Peri).
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t    R_USB_Resume(usb_ctrl_t *p_ctrl)
{
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t   utr;
    usb_er_t    err;

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    usb_err_t   ret_code = USB_SUCCESS;
    usb_info_t  info;

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_NULL == p_ctrl)
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

#if defined(BSP_MCU_RX63N)
    if ((USB_IP1 == p_ctrl->module) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif

    if (USB_HOST == g_usb_usbmode)
    {
        p_ctrl->address = USB_DEVICEADDR;
    }
    else
    {
        if (USB_PHID != p_ctrl->type)
        {
            return USB_ERR_PARA;
        }
    }

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_SUSPEND != info.status)
    {
        return USB_ERR_NOT_SUSPEND;
    }

    if (USB_HOST == g_usb_usbmode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ip = p_ctrl->module;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

#if (BSP_CFG_RTOS_USED == 0)
        if (USB_NULL != (g_usb_change_device_state[p_ctrl->module] & (1 << USB_STS_RESUME)))
        {
            return USB_ERR_BUSY;
        }

        err = usb_hstd_change_device_state(&utr, (usb_cb_t)&usb_hstd_resume_complete,
                                         USB_DO_GLOBAL_RESUME, p_ctrl->address);
        if (USB_OK == err)
        {
            g_usb_change_device_state[p_ctrl->module] |= (1 << USB_STS_RESUME);
        }
        else
        {
            ret_code = USB_ERR_NG;
        }
#else   /* (BSP_CFG_RTOS_USED == 0) */
        if (USB_YES == gs_usb_resume_ing[p_ctrl->module])
        {
            return USB_ERR_BUSY;
        }
        else
        {
            gs_usb_resume_ing[p_ctrl->module] = USB_YES;
        }

        err = usb_hstd_change_device_state(&utr, (usb_cb_t)&usb_hstd_resume_complete,
                                         USB_DO_GLOBAL_RESUME, p_ctrl->address);
        if (USB_OK != err)
        {
            ret_code = USB_ERR_NG;
        }

        gs_usb_resume_ing[p_ctrl->module] = USB_NO;

#endif  /* (BSP_CFG_RTOS_USED == 0) */

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

#if (BSP_CFG_RTOS_USED == 0)

        /* Support remote wakeup ? */
        if (USB_TRUE == g_usb_pstd_remote_wakeup)
        {
            usb_pstd_change_device_state(USB_DO_REMOTEWAKEUP, USB_NULL, (usb_cb_t)usb_pstd_dummy_function);
            switch (g_usb_pstd_remote_wakeup_state)
            {
                case USB_OK:
                    ret_code = USB_SUCCESS;
                break;

                case USB_QOVR:
                    ret_code = USB_ERR_NOT_SUSPEND;
                break;

                case USB_ERROR:
                default:
                    ret_code = USB_ERR_NG;
                break;
            }
        }
        else
        {
            ret_code = USB_ERR_NG;
        }

#else   /* (BSP_CFG_RTOS_USED == 0) */

        if (USB_YES == gs_usb_resume_ing[USB_CFG_USE_USBIP])
        {
            return USB_ERR_BUSY;
        }
        else
        {
            gs_usb_resume_ing[USB_CFG_USE_USBIP] = USB_YES;
        }
        /* Support remote wakeup ? */
        if (USB_TRUE == g_usb_pstd_remote_wakeup)
        {
            usb_pstd_change_device_state(USB_DO_REMOTEWAKEUP, USB_NULL, (usb_cb_t)usb_pstd_dummy_function);
            switch (g_usb_pstd_remote_wakeup_state)
            {
                case USB_OK:
                    ret_code = USB_SUCCESS;
                break;

                case USB_QOVR:
                    ret_code = USB_ERR_NOT_SUSPEND;
                break;

                case USB_ERROR:
                default:
                    ret_code = USB_ERR_NG;
                break;
            }
        }
        else
        {
            ret_code = USB_ERR_NG;
        }
        gs_usb_resume_ing[USB_CFG_USE_USBIP] = USB_NO;

#endif  /* (BSP_CFG_RTOS_USED == 0) */

#else   /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
        ret_code = USB_ERR_NG;
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }

    return ret_code;
}
/******************************************************************************
 End of function R_USB_Resume
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_VbusSetting
Description     : Contol of USB VBUS.(USB Host only)
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
                : uint16_t      state   : HI/LOW assertion
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t   R_USB_VbusSetting( usb_ctrl_t *p_ctrl, uint16_t state )
{

#if (USB_CFG_MODE == USB_CFG_PERI)
    return USB_ERR_NG;
#else
    usb_utr_t   utr;

    if (USB_PERI == g_usb_usbmode) 
    {
        return USB_ERR_NG;              /* Support Host only. */
    }

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE

    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63N)  || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63N)  || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)  */

    if (USB_NULL == p_ctrl)
    {
        return USB_ERR_PARA;
    }
    
    if ((USB_ON != state) && (USB_OFF != state))
    {
       return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX63N)
    if (USB_IP1 == p_ctrl->module && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    utr.ip = p_ctrl->module;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

    if (USB_ON == state)
    {
        usb_hstd_vbus_control(&utr, (uint16_t)USB_VBON);
    }
    else
    {
        usb_hstd_vbus_control(&utr, (uint16_t)USB_VBOFF);
    }

    return USB_SUCCESS;
#endif /* (USB_CFG_MODE == USB_CFG_PERI) */
}
/******************************************************************************
 End of function R_USB_VbusSetting
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_GetInformation
Description     : Get USB Informatio.(Device class,Connect speed,Device status)
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
                : usb_info_t    *p_info : Pointer to usb_info_t structure
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t   R_USB_GetInformation( usb_ctrl_t *p_ctrl, usb_info_t *p_info)
{
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t   utr;

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    uint16_t    status;

    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

    if (0 == g_usb_open_class[p_ctrl->module])
    {
        return USB_ERR_NG;
    }

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE

    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

#if defined(BSP_MCU_RX63N)
    if ((USB_IP1 == p_ctrl->module) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif
    
    if (USB_NULL == p_info)
    {
        return USB_ERR_PARA;
    }

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    if (USB_HOST == g_usb_usbmode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
        if (USB_NULL == p_ctrl)
        {
            return USB_ERR_PARA;
        }

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

        utr.ip = p_ctrl->module;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

        /* Set USB Device class */
        switch (g_usb_hstd_device_info[utr.ip][p_ctrl->address][3])
        {
            case USB_IFCLS_CDC:
                p_info->type   = USB_PCDC;
                break;
            case USB_IFCLS_HID:
                p_info->type   = USB_PHID;
                break;
            case USB_IFCLS_MAS:
                p_info->type   = USB_PMSC;
                break;
            case USB_IFCLS_VEN:
                p_info->type   = USB_PVND;
                break;
            default:
                p_info->type   = USB_NULL;
                break;
        }

        /* Set USB connect speed */
        switch(g_usb_hstd_device_info[utr.ip][p_ctrl->address][4])
        {
            case USB_NOCONNECT:
                p_info->speed  = USB_NULL;
                break;
            case USB_HSCONNECT:
                p_info->speed  = USB_HS;
                break;
            case USB_FSCONNECT:
                p_info->speed  = USB_FS;
                break;
            case USB_LSCONNECT:
                p_info->speed  = USB_LS;
                break;
            default:
                p_info->speed  = USB_NULL;
                break;
        }

        /* Set USB device state */
        switch (g_usb_hstd_device_info[utr.ip][p_ctrl->address][1])
        {
            case USB_POWERED:                           /* Power state  */
                p_info->status = USB_STS_POWERED;
                break;
            case USB_DEFAULT:                           /* Default state  */
                p_info->status = USB_STS_DEFAULT;
                break;
            case USB_ADDRESS:                           /* Address state  */
                p_info->status = USB_STS_ADDRESS;
                break;
            case USB_CONFIGURED:                        /* Configured state  */
                p_info->status = USB_STS_CONFIGURED;
                break;
            case USB_SUSPENDED:                         /* Suspend state */
                p_info->status = USB_STS_SUSPEND;
                break;
            case USB_DETACHED:                          /* Disconnect(VBUSon) state */
                p_info->status = USB_STS_DETACH;
                break;
            default:                                    /* Error */
                p_info->status = USB_NULL;
                break;
        }

        /* Set USB Peri BC port state */
#if USB_CFG_BC == USB_CFG_ENABLE
        if (USB_DEVICEADDR == p_ctrl->address)          /* Check Root port address */
        {
            if (USB_BC_STATE_CDP == g_usb_hstd_bc[utr.ip].state)
            {
                p_info->port   = USB_CDP;
            }
            else
            {
                p_info->port   = USB_SDP;               /* USB_SDP/USB_CDP/USB_DCP */
            }
        }
        else
        {
            p_info->port   = USB_SDP;                   /* USB_SDP/USB_CDP/USB_DCP */
        }

#else   /* #if USB_CFG_BC == USB_CFG_ENABLE */
        p_info->port   = USB_SDP;  /* USB_SDP/USB_CDP/USB_DCP */

#endif  /* #if USB_CFG_BC == USB_CFG_ENABLE */
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

        p_info->type   = USB_NULL;              /* Device class */
        switch(usb_cstd_port_speed(USB_NULL))
        {
            case USB_NOCONNECT:
                p_info->speed  = USB_NULL;
            break;
            case USB_HSCONNECT:
                p_info->speed  = USB_HS;
            break;
            case USB_FSCONNECT:
                p_info->speed  = USB_FS;
            break;
            case USB_LSCONNECT:
                p_info->speed  = USB_LS;
            break;
            default:
                p_info->speed  = USB_NULL;
            break;
        }
        status = hw_usb_read_intsts();
        switch ((uint16_t)(status & USB_DVSQ))
        {
            case USB_DS_POWR:                           /* Power state  */
                p_info->status = USB_STS_DETACH;
            break;
            case USB_DS_DFLT:                           /* Default state  */
                p_info->status = USB_STS_DEFAULT;
            break;
            case USB_DS_ADDS:                           /* Address state  */
                p_info->status = USB_STS_ADDRESS;
            break;
            case USB_DS_CNFG:                           /* Configured state  */
                p_info->status = USB_STS_CONFIGURED;
            break;
            case USB_DS_SPD_POWR:                       /* Power suspend state */
            case USB_DS_SPD_DFLT:                       /* Default suspend state */
            case USB_DS_SPD_ADDR:                       /* Address suspend state */
            case USB_DS_SPD_CNFG:                       /* Configured Suspend state */
                p_info->status = USB_STS_SUSPEND;
            break;
            default:                                    /* Error */
            break;                                  /* p_info->status = USB_STS_ERROR; */
        }
#if USB_CFG_BC == USB_CFG_ENABLE
        p_info->port   = g_usb_bc_detect;           /* USB_SDP/USB_CDP/USB_DCP */
#else   /* USB_CFG_BC == USB_CFG_ENABLE */
        p_info->port   = USB_SDP;                   /* USB_SDP */
#endif  /* USB_CFG_BC == USB_CFG_ENABLE */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    return USB_SUCCESS;
}
/******************************************************************************
 End of function R_USB_GetInformation
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_PipeRead
Description     : USB Data receive process for Vendor class.
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
                : uint8_t       *buf    : Pointer to the data buffer area
                : uint32_t      size    : Read size
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t  R_USB_PipeRead(usb_ctrl_t *p_ctrl, uint8_t *buf, uint32_t size)
{
#if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE)
    return USB_ERR_NG;
#else   /* !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */

    usb_err_t   ret_code = USB_ERR_NG;
    usb_utr_t   *p_tran_data;
#if (BSP_CFG_RTOS_USED == 1)
    usb_utr_t   tran_data;
#endif /* BSP_CFG_RTOS_USED == 1 */

    usb_er_t    err;
    usb_info_t  info;

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (((USB_NULL == p_ctrl) || (USB_PIPE0 == p_ctrl->pipe)) || (USB_MAXPIPE_NUM < p_ctrl->pipe))
    {
        return USB_ERR_PARA;
    }

    if ((USB_NULL == buf) || (USB_NULL == size))
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T)\
    || defined(BSP_MCU_RX72T) || defined (BSP_MCU_RX72M)
    if ((USB_IP1 == p_ctrl->module) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif /* #if defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T)\
    || defined(BSP_MCU_RX72T) || defined (BSP_MCU_RX72M)   */

    if (USB_NULL == (g_usb_open_class[p_ctrl->module] & (1 << p_ctrl->type)))      /* Check USB Open device class */
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX63N)
    if (USB_IP1 == p_ctrl->module && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED == info.status)
    {
        /* PIPE Transfer set */
        if (USB_HOST == g_usb_usbmode)
        {
    #if defined(USB_CFG_HVND_USE)
      #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

#if (BSP_CFG_RTOS_USED == 1)
            p_tran_data = (usb_utr_t *)&tran_data;
#else  /* BSP_CFG_RTOS_USED == 1 */
            p_tran_data = (usb_utr_t *)&g_usb_hdata[p_ctrl->module][p_ctrl->pipe];
#endif /* BSP_CFG_RTOS_USED == 1 */

            p_tran_data->ip = p_ctrl->module;
            p_tran_data->ipp = usb_hstd_get_usb_ip_adr(p_tran_data->ip);
            p_tran_data->keyword     = p_ctrl->pipe;             /* Pipe No */
            p_tran_data->p_tranadr   = buf;                      /* Data address */
            p_tran_data->tranlen     = size;                     /* Data Size */
            p_tran_data->p_setup     = 0;
            p_tran_data->complete    = usb_hvnd_read_complete;   /* Callback function */
            p_tran_data->segment     = USB_TRAN_END;
            *(uint32_t *)p_tran_data->p_usr_data = p_ctrl->address;
            p_tran_data->read_req_len= size;                     /* Data Size */

            err = usb_hstd_transfer_start(p_tran_data);        /* USB Transfer Start */
            if (USB_OK == err)
            {
                ret_code = USB_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = USB_ERR_BUSY;
            }
            else
            {
            }
      #endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    #endif /* #if defined(USB_CFG_HVND_USE) */
        }
        else
        {
    #if defined(USB_CFG_PVND_USE)
      #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

#if (BSP_CFG_RTOS_USED == 1)
            p_tran_data = (usb_utr_t *)&tran_data;
#else  /* BSP_CFG_RTOS_USED == 1 */
            p_tran_data = (usb_utr_t *)&g_usb_pdata[p_ctrl->pipe];
#endif /* BSP_CFG_RTOS_USED == 1 */

            p_tran_data->keyword    = p_ctrl->pipe;        /* Pipe No */
            p_tran_data->p_tranadr  = buf;                 /* Data address */
            p_tran_data->tranlen    = size;                /* Data Size */
            p_tran_data->complete   = (usb_cb_t)&usb_pvnd_read_complete;   /* Callback function */
            p_tran_data->read_req_len= size;                     /* Data Size */
            err = usb_pstd_transfer_start(p_tran_data);   /* USB Transfer Start */
            if (USB_OK == err)
            {
                ret_code = USB_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = USB_ERR_BUSY;
            }
            else
            {
            }
      #endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    #endif  /* defined(USB_CFG_PVND_USE) */
        }
    }

    return ret_code;
#endif  /* !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */
}
/******************************************************************************
 End of function R_USB_PipeRead
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_PipeWrite
Description     : USB Data send process for Vendor class.
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
                : uint8_t       *buf    : Pointer to the data buffer area
                : uint32_t      size    : Write size
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t  R_USB_PipeWrite(usb_ctrl_t *p_ctrl, uint8_t *buf, uint32_t size)
{
#if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE)
    return USB_ERR_NG;
#else   /* !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */

    usb_er_t    err;
    usb_err_t   ret_code = USB_ERR_NG;
    usb_info_t  info;
    usb_utr_t   *p_tran_data;
#if (BSP_CFG_RTOS_USED == 1)
    usb_utr_t   tran_data;
#endif /* BSP_CFG_RTOS_USED == 1 */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
        /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T)\
    || defined(BSP_MCU_RX72T) || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T)\
    || defined(BSP_MCU_RX72T) || defined (BSP_MCU_RX72M) */

    if (((USB_NULL == p_ctrl) || (USB_NULL == buf) || (USB_PIPE0 == p_ctrl->pipe)) || (USB_MAXPIPE_NUM < p_ctrl->pipe))
    {
        return USB_ERR_PARA;
    }

    if (USB_NULL == (g_usb_open_class[p_ctrl->module] & (1 << p_ctrl->type)))      /* Check USB Open device class */
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX63N)
    if (USB_IP1 == p_ctrl->module && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED == info.status)
    {
        /* PIPE Transfer set */
        if (USB_HOST == g_usb_usbmode)
        {
    #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
      #if defined(USB_CFG_HVND_USE)

#if (BSP_CFG_RTOS_USED == 1)
            p_tran_data = (usb_utr_t *)&tran_data;
#else  /* BSP_CFG_RTOS_USED == 1 */
            p_tran_data = (usb_utr_t *)&g_usb_hdata[p_ctrl->module][p_ctrl->pipe];
#endif /* BSP_CFG_RTOS_USED == 1 */

            p_tran_data->ip                                     = p_ctrl->module;
            p_tran_data->ipp                                    = usb_hstd_get_usb_ip_adr((uint8_t) p_ctrl->module);
            p_tran_data->keyword                                = p_ctrl->pipe;                 /* Pipe No */
            p_tran_data->p_tranadr                              = buf;                          /* Data address */
            p_tran_data->tranlen                                = size;                         /* Data Size */
            p_tran_data->complete                               = usb_hvnd_write_complete;   /* Callback function */
            p_tran_data->segment                                = USB_TRAN_END;
            err = usb_hstd_transfer_start(p_tran_data);
            if (USB_OK == err)
            {
                ret_code = USB_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = USB_ERR_BUSY;
            }
            else
            {
            }
      #endif  /* defined(USB_CFG_HVND_USE) */
    #endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
    #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        #if defined(USB_CFG_PVND_USE)

#if (BSP_CFG_RTOS_USED == 1)
            p_tran_data = (usb_utr_t *)&tran_data;
#else  /* BSP_CFG_RTOS_USED == 1 */
            p_tran_data = (usb_utr_t *)&g_usb_pdata[p_ctrl->pipe];
#endif /* BSP_CFG_RTOS_USED == 1 */

            p_tran_data->keyword                = p_ctrl->pipe;                         /* Pipe No */
            p_tran_data->p_tranadr              = buf;                                  /* Data address */
            p_tran_data->tranlen                = size;                                 /* Data Size */
            p_tran_data->complete               = usb_pvnd_write_complete;              /* Callback function */
            err = usb_pstd_transfer_start(p_tran_data);

            if (USB_OK == err)
            {
                ret_code = USB_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = USB_ERR_BUSY;
            }
            else
            {
            }
        #endif  /* defined(USB_CFG_PVND_USE) */
    #endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
        }
    }

    return ret_code;
#endif /* #if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */

}
/******************************************************************************
 End of function R_USB_PipeWrite
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_PipeStop
Description     : USB transfer stop process for Vendor class.
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t    R_USB_PipeStop(usb_ctrl_t *p_ctrl)
{
#if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE)
    return USB_ERR_NG;
#else
    
    usb_er_t    err = USB_ERR_NG;
    usb_err_t   ret_code = USB_ERR_NG;
    usb_info_t  info;

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t   utr;

    if (USB_HOST == g_usb_usbmode)
    {
        utr.ip = p_ctrl->module;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
    }

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) && ( USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif  /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

#if defined(BSP_MCU_RX63N)
    if ((USB_IP1 == p_ctrl->module) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif

    if ((USB_NULL == p_ctrl) || (USB_PIPE0 == p_ctrl->pipe) || (USB_MAXPIPE_NUM < p_ctrl->pipe))
    {
        return USB_ERR_PARA;
    }

    if (USB_NULL == (g_usb_open_class[p_ctrl->module] & (1 << p_ctrl->type)))      /* Check USB Open device class */
    {
        return USB_ERR_PARA;
    }

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    err = R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED != info.status)
    {
        return USB_ERR_NG;
    }

    if (USB_HOST == g_usb_usbmode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        err = usb_hstd_transfer_end(&utr, p_ctrl->pipe, (uint16_t)USB_DATA_STOP);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        err = usb_pstd_transfer_end(p_ctrl->pipe);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    if (USB_OK == err)
    {
        ret_code = USB_SUCCESS;
    }

    return ret_code;
#endif /* !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */
}
/******************************************************************************
 End of function R_USB_PipeStop
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_GetUsePipe
Description     : Get Information for Use pipe.
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
                : uint16_t      *p_pipe : Pointer to the area to store the used pipe bitmap
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t    R_USB_GetUsePipe(usb_ctrl_t *p_ctrl, uint16_t *p_pipe)
{
    usb_info_t  info;
    uint16_t    pipe_no;

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t   utr;
#endif /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_NULL == p_pipe)
    {
        return USB_ERR_PARA;
    }

    if ((USB_NULL == p_ctrl) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /*defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

#if defined(BSP_MCU_RX63N)
    if ((USB_IP1 == p_ctrl->module) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX63N)   */

#endif /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    utr.ip = p_ctrl->module;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
#endif /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

    R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED != info.status)
    {
        return USB_ERR_NG;
    }

    /* Get PIPE Number from Endpoint address */
    *p_pipe = ((uint16_t)1 << USB_PIPE0);
    if (USB_HOST == g_usb_usbmode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        /* WAIT_LOOP */
        for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO +1); pipe_no++)
        {
            if (USB_TRUE == g_usb_pipe_table[utr.ip][pipe_no].use_flag)
            {
                if ((p_ctrl->address << USB_DEVADDRBIT) == (g_usb_pipe_table[utr.ip][pipe_no].pipe_maxp & USB_DEVSEL))
                {
                    (*p_pipe) |= ((uint16_t)1 << pipe_no);
                }
            }
        }

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        /* WAIT_LOOP */
        for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO +1); pipe_no++)
        {
            if (USB_TRUE == g_usb_pipe_table[USB_CFG_USE_USBIP][pipe_no].use_flag)
            {
                (*p_pipe) |= ((uint16_t)1 << pipe_no);
            }
        }

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }

    return USB_SUCCESS;
}
/******************************************************************************
 End of function R_USB_GetUsePipe
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_GetPipeInfo
Description     : Get Infomation for pipe setting.(DIR,Transfer Type,MAXPS)
Arguments       : usb_ctrl_t    *p_ctrl : Pointer to usb_ctrl_t structure
                : usb_pipe_t    *p_info : Pointer to the area to store the pipe information
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t    R_USB_GetPipeInfo(usb_ctrl_t *p_ctrl, usb_pipe_t *p_info)
{
    usb_info_t  info;
    uint16_t    pipe_type;

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t   utr;
#endif /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    /* Argument Checking */
    if ((USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }

    if (((USB_NULL == p_ctrl) || (0 == p_ctrl->pipe)) || (USB_MAXPIPE_NUM < p_ctrl->pipe))
    {
        return USB_ERR_PARA;
    }


#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M)
    if (USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif  /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX630) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)\
    || defined (BSP_MCU_RX72M) */

#if defined(BSP_MCU_RX63N)
    if ((USB_IP1 == p_ctrl->module) && (USB_HOST == g_usb_usbmode))
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX63N)   */

#endif  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */


#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

    if (USB_HOST == g_usb_usbmode)
    {
        utr.ip = p_ctrl->module;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
    }

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */


    R_USB_GetInformation(p_ctrl, &info);
    if (USB_STS_CONFIGURED != info.status)
    {
        return USB_ERR_NG;
    }

    if (USB_HOST == g_usb_usbmode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_info->ep = usb_hstd_pipe_to_epadr(&utr, p_ctrl->pipe);
        pipe_type = usb_cstd_get_pipe_type(&utr, p_ctrl->pipe);

        switch (pipe_type)
        {
            case USB_TYPFIELD_ISO: 
                p_info->type = USB_ISO;                              /* Set Isochronous */
            break;            
            case USB_TYPFIELD_BULK:
                p_info->type = USB_BULK;                             /* Set Bulk */
            break;            
            case USB_TYPFIELD_INT:
                p_info->type = USB_INT;                              /* Set Interrupt */
            break;
            default:
                return USB_ERR_NG;
            break;
        }
        p_info->mxps = usb_cstd_get_maxpacket_size(&utr, p_ctrl->pipe);     /* Set Max packet size */
        return USB_SUCCESS;

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        /* Get PIPE Number from Endpoint address */
        p_info->ep   = (uint8_t)(g_usb_pipe_table[USB_CFG_USE_USBIP][p_ctrl->pipe].pipe_cfg & USB_EPNUMFIELD);  /* Set EP num. */
        if (USB_DIR_P_IN == (g_usb_pipe_table[USB_CFG_USE_USBIP][p_ctrl->pipe].pipe_cfg & USB_DIRFIELD))        /* Check dir */
        {
            p_info->ep |= USB_EP_DIR_IN;                            /* Set DIR IN */
        }
        pipe_type = usb_cstd_get_pipe_type(USB_NULL, p_ctrl->pipe);
        switch (pipe_type)
        {
            case USB_TYPFIELD_ISO:
                p_info->type = USB_ISO;                                 /* Set Isochronous */
            break;
            
            case USB_TYPFIELD_BULK:
                p_info->type = USB_BULK;                                /* Set Bulk */
            break;
            
            case USB_TYPFIELD_INT:
                p_info->type = USB_INT;                                 /* Set Interrupt */
            break;
            
            default:
                return USB_ERR_NG;
            break;
        }
        p_info->mxps = usb_cstd_get_maxpacket_size(USB_NULL, p_ctrl->pipe); /* Set Max packet size */
        return USB_SUCCESS;

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    return USB_ERR_NG;
}
/******************************************************************************
 End of function R_USB_GetPipeInfo
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_PullUp
Description     : Contol of USB D+/D- line pull-up.(USB Peripheral only)
Arguments       : uint16_t      state   : USB_ON(Enable)/USB_OFF(Disable)
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
******************************************************************************/
usb_err_t   R_USB_PullUp(uint8_t state)
{

#if (USB_CFG_MODE == USB_CFG_HOST)
    return USB_ERR_NG;
#else /* USB_CFG_MODE == USB_CFG_HOST */

    if (USB_HOST == g_usb_usbmode) 
    {
        return USB_ERR_NG;              /* Support Host only. */
    }

    /* Argument Checking */

    if ((USB_ON != state) && (USB_OFF != state))
    {
       return USB_ERR_PARA;
    }

    if (USB_ON == state)
    {
        hw_usb_pset_dprpu();
    }
    else
    {
        hw_usb_pclear_dprpu();
    }

    return USB_SUCCESS;
#endif /* USB_CFG_MODE == USB_CFG_HOST */
} /* End of function R_USB_GetPipeInfo */
/******************************************************************************
 End of function R_USB_PullUp
 ******************************************************************************/

/******************************************************************************
End  Of File
******************************************************************************/
