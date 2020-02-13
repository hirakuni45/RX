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
 * File Name    : r_usb_hlibusbip.c
 * Description  : USB IP Host library.
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.21 usb_hstd_set_pipe_register() is fixed.
 *         : 30.09.2017 1.22 Rename "usb_hstd_buf2fifo"->"usb_hstd_buf_to_fifo" and Function move for"r_usb_hdriver.c"
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
#include "r_usb_dmac.h"
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
/******************************************************************************
 Renesas Abstracted Host Lib IP functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_set_dev_addr
 Description     : Set USB speed (Full/Hi) of the connected USB Device.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t addr    : device address
                 : uint16_t speed   : device speed
                 : uint16_t port    : root port
 Return value    : none
 ******************************************************************************/
void usb_hstd_set_dev_addr (usb_utr_t *ptr, uint16_t addr, uint16_t speed, uint16_t port)
{
    if (USB_DEVICE_0 == addr)
    {
        hw_usb_write_dcpmxps(ptr, (uint16_t) (USB_DEFPACKET + USB_DEVICE_0));
    }
    hw_usb_hset_usbspd(ptr, addr, (speed | port));
}
/******************************************************************************
 End of function usb_hstd_set_dev_addr
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_bchg_enable
 Description     : Enable BCHG interrupt for the specified USB port.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t port    : root port
 Return value    : none
 ******************************************************************************/
void usb_hstd_bchg_enable (usb_utr_t *ptr, uint16_t port)
{

    hw_usb_hclear_sts_bchg(ptr, port);
    hw_usb_hset_enb_bchge(ptr, port);

}
/******************************************************************************
 End of function usb_hstd_bchg_enable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_bchg_disable
 Description     : Disable BCHG interrupt for specified USB port.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t port    : root port
 Return value    : none
 ******************************************************************************/
void usb_hstd_bchg_disable (usb_utr_t *ptr, uint16_t port)
{

    hw_usb_hclear_sts_bchg(ptr, port);
    hw_usb_hclear_enb_bchge(ptr, port);

}
/******************************************************************************
 End of function usb_hstd_bchg_disable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_set_uact
 Description     : Start sending SOF to the connected USB device.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t port    : root port
 Return value    : none
 ******************************************************************************/
void usb_hstd_set_uact (usb_utr_t *ptr, uint16_t port)
{
    hw_usb_rmw_dvstctr(ptr, port, USB_UACT, ((USB_USBRST | USB_RESUME) | USB_UACT));
}
/******************************************************************************
 End of function usb_hstd_set_uact
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_ovrcr_enable
 Description     : Enable OVRCR interrupt of the specified USB port.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t port    : root port
 Return value    : none
 ******************************************************************************/
void usb_hstd_ovrcr_enable (usb_utr_t *ptr, uint16_t port)
{

    hw_usb_hclear_sts_ovrcr(ptr, port);
    hw_usb_hset_enb_ovrcre(ptr, port);

}
/******************************************************************************
 End of function usb_hstd_ovrcr_enable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_ovrcr_disable
 Description     : Disable OVRCR interrupt of the specified USB port.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t port    : root port
 Return value    : none
 ******************************************************************************/
void usb_hstd_ovrcr_disable (usb_utr_t *ptr, uint16_t port)
{
    /* OVRCR Clear(INT_N edge sense) */
    hw_usb_hclear_sts_ovrcr(ptr, port);

    /* Over-current disable */
    hw_usb_hclear_enb_ovrcre(ptr, port);
}
/******************************************************************************
 End of function usb_hstd_ovrcr_disable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_attch_enable
 Description     : Enable ATTCH (attach) interrupt of the specified USB port.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t port    : root port
 Return value    : none
 ******************************************************************************/
void usb_hstd_attch_enable (usb_utr_t *ptr, uint16_t port)
{

    /* ATTCH status Clear */
    hw_usb_hclear_sts_attch(ptr, port);

    /* Attach enable */
    hw_usb_hset_enb_attche(ptr, port);

}
/******************************************************************************
 End of function usb_hstd_attch_enable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_attch_disable
 Description     : Disable ATTCH (attach) interrupt of the specified USB port.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t port    : root port
 Return value    : none
 ******************************************************************************/
void usb_hstd_attch_disable (usb_utr_t *ptr, uint16_t port)
{

    /* ATTCH Clear(INT_N edge sense) */
    hw_usb_hclear_sts_attch(ptr, port);

    /* Attach disable */
    hw_usb_hclear_enb_attche(ptr, port);

}
/******************************************************************************
 End of function usb_hstd_attch_disable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_dtch_enable
 Description     : Enable DTCH (detach) interrupt of the specified USB port. 
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t port    : root port
 Return value    : none
 ******************************************************************************/
void usb_hstd_dtch_enable (usb_utr_t *ptr, uint16_t port)
{

    /* DTCH Clear */
    hw_usb_hclear_sts_dtch(ptr, port);

    /* Detach enable */
    hw_usb_hset_enb_dtche(ptr, port);

}
/******************************************************************************
 End of function usb_hstd_dtch_enable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_dtch_disable
 Description     : Disable DTCH (detach) interrupt of the specified USB port.  
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t port    : root port
 Return value    : none
 ******************************************************************************/
void usb_hstd_dtch_disable (usb_utr_t *ptr, uint16_t port)
{

    /* DTCH Clear(INT_N edge sense) */
    hw_usb_hclear_sts_dtch(ptr, port);

    /* Detach disable */
    hw_usb_hclear_enb_dtche(ptr, port);

}
/******************************************************************************
 End of function usb_hstd_dtch_disable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_set_pipe_register
 Description     : Set up USB registers to use specified pipe (given in infor-
                 : mation table).
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : uint16_t pipe_no     : pipe number
                 : uint16_t *tbl        : pipe information table 
 Return value    : none
 ******************************************************************************/
void usb_hstd_set_pipe_register (usb_utr_t *ptr, uint16_t pipe_no, uint16_t *tbl)
{
    uint16_t i;
    uint16_t pipe;
    uint16_t buf;

    /* PIPE USE check */
    if (USB_USEPIPE == pipe_no)
    {
        /* EP Table loop */
        for (i = 0; USB_PDTBLEND != tbl[i]; i += USB_EPL)
        {
            /* PipeNo Number */
            pipe = (uint16_t) (tbl[i + 0] & USB_CURPIPE);

            /* Current FIFO port Clear */
            buf = hw_usb_read_fifosel(ptr, USB_CUSE);
            if ((buf & USB_CURPIPE) == pipe)
            {
                usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_CUSE, USB_FALSE);
            }
            buf = hw_usb_read_fifosel( ptr, USB_D0DMA );
            if ((buf & USB_CURPIPE) == pipe)
            {
                usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_D0USE, USB_FALSE);
            }
            buf = hw_usb_read_fifosel( ptr, USB_D1DMA );
            if ((buf & USB_CURPIPE) == pipe)
            {
                usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_D1USE, USB_FALSE);
            }

            /* PIPE Setting */
            usb_cstd_pipe_init(ptr, pipe, tbl, i);
        }
    }
    else
    {
        /* Current FIFO port Clear */
        usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_CUSE, USB_FALSE);
        buf = hw_usb_read_fifosel(ptr, USB_D0USE);
        if ((buf & USB_CURPIPE) == pipe_no)
        {
            usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_D0USE, USB_FALSE);
        }
        buf = hw_usb_read_fifosel(ptr, USB_D1USE);
        if ((buf & USB_CURPIPE) == pipe_no)
        {
            usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_D1USE, USB_FALSE);
        }

        /* EP Table loop */
        for (i = 0; USB_PDTBLEND != tbl[i]; i += USB_EPL)
        {
            /* PipeNo Number */
            pipe = (uint16_t) (tbl[i + 0] & USB_CURPIPE);
            if (pipe == pipe_no)
            {
                /* PIPE Setting */
                usb_cstd_pipe_init(ptr, pipe, tbl, i);
            }
        }
    }
}
/******************************************************************************
 End of function usb_hstd_set_pipe_register
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_get_rootport
 Description     : Get USB port no. set in the USB register based on the speci-
 : fied USB Device address.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t addr    : device address
 Return value    : uint16_t         : root port number
 ******************************************************************************/
uint16_t usb_hstd_get_rootport (usb_utr_t *ptr, uint16_t addr)
{
    uint16_t buffer;

    /* Get device address configuration register from device address */
    buffer = hw_usb_hread_devadd(ptr, addr);
    if (USB_ERROR != buffer)
    {
        /* Return root port number */
        return (uint16_t) (buffer & USB_RTPORT);
    }
    return USB_ERROR;
}
/******************************************************************************
 End of function usb_hstd_get_rootport
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_chk_dev_addr
 Description     : Get USB speed set in USB register based on the specified USB 
                 : Device address and USB port no.
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : uint16_t addr        : device address
                 : uint16_t rootport    : root port
 Return value    : uint16_t             : USB speed etc
 ******************************************************************************/
uint16_t usb_hstd_chk_dev_addr (usb_utr_t *ptr, uint16_t addr, uint16_t rootport)
{
    uint16_t buffer;

    /* Get device address configuration register from device address */
    buffer = hw_usb_hread_devadd(ptr, addr);
    if (USB_ERROR != buffer)
    {
        if ((uint16_t) (buffer & USB_RTPORT) == rootport)
        {
            /* Return Address check result */
            return (uint16_t) (buffer & USB_USBSPD);
        }
    }
    return USB_NOCONNECT;
}
/******************************************************************************
 End of function usb_hstd_chk_dev_addr
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_get_dev_speed
 Description     : Get USB speed set in USB register based on the specified USB 
                 : Device address.
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : uint16_t addr        : device address
 Return value    : uint16_t             : device speed
 Note            : Use also to a connection check is possible
 ******************************************************************************/
uint16_t usb_hstd_get_dev_speed (usb_utr_t *ptr, uint16_t addr)
{
    uint16_t buffer;

    /* Get device address configuration register from device address */
    buffer = hw_usb_hread_devadd(ptr, addr);
    if (USB_ERROR != buffer)
    {
        /* Return device speed */
        return (uint16_t) (buffer & USB_USBSPD);
    }
    return USB_NOCONNECT;
}
/******************************************************************************
 End of function usb_hstd_get_dev_speed
 ******************************************************************************/
 
 /******************************************************************************
 Function Name   : usb_hstd_pipe_to_epadr
 Description     : Get the associated endpoint value of the specified pipe.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : uint8_t        : OK    : Endpoint nr + direction.
                 :                : ERROR : Error.
 ******************************************************************************/
uint8_t usb_hstd_pipe_to_epadr (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t buffer;
    uint16_t direp;

    /* Pipe select */
    hw_usb_write_pipesel(ptr, pipe);

    /* Read Pipe direction */
    buffer = hw_usb_read_pipecfg(ptr);
    direp = (uint16_t) ((((buffer & USB_DIRFIELD) ^ USB_DIRFIELD) << 3) + (buffer & USB_EPNUMFIELD));
    return (uint8_t) (direp);
}
/******************************************************************************
 End of function usb_hstd_pipe_to_epadr
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_pipe2fport
 Description     : Get port No. from the specified pipe No. by argument
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : uint16_t       : FIFO port selector.
 ******************************************************************************/
uint16_t usb_hstd_pipe2fport (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t fifo_mode = USB_CUSE;

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))

    if (USB_PIPE1 == pipe)
    {
        fifo_mode = USB_D0DMA;
    }
    if (USB_PIPE2 == pipe)
    {
        fifo_mode = USB_D1DMA;
    }

#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    return fifo_mode;
}
/******************************************************************************
 End of function usb_hstd_pipe2fport
 ******************************************************************************/

#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
/******************************************************************************
 Function Name   : usb_hstd_set_hse
 Description     : Set/clear the HSE-bit of the specified port.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t speed : HS_ENABLE/HS_DISABLE.
 Return value    : none
 ******************************************************************************/
void usb_hstd_set_hse(usb_utr_t *ptr, uint16_t port, uint16_t speed)
{
    if (speed == USB_HS_DISABLE)
    {
        /* HSE = disable */
        hw_usb_clear_hse(ptr, port);
    }
    else
    {
        /* HSE = enable */
        hw_usb_set_hse(ptr, port);
    }
}
/******************************************************************************
 End of function usb_hstd_set_hse
 ******************************************************************************/
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */


/******************************************************************************
 Function Name   : usb_hstd_berne_enable
 Description     : Enable BRDY/NRDY/BEMP interrupt.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
void usb_hstd_berne_enable (usb_utr_t *ptr)
{
    /* Enable BEMP, NRDY, BRDY */
    hw_usb_set_intenb(ptr, ((USB_BEMPE | USB_NRDYE) | USB_BRDYE));
}
/******************************************************************************
 End of function usb_hstd_berne_enable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_sw_reset
 Description     : Request USB IP software reset
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
void usb_hstd_sw_reset (usb_utr_t *ptr)
{
    /* USB Enable */
    hw_usb_set_usbe(ptr);

    /* USB Reset */
    hw_usb_clear_usbe(ptr);

    /* USB Enable */
    hw_usb_set_usbe(ptr);
}
/******************************************************************************
 End of function usb_hstd_sw_reset
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_do_sqtgl
 Description     : Toggle setting of the toggle-bit for the specified pipe by 
 : argument.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t pipe    : Pipe number.
                 : uint16_t toggle  : Current toggle status.
 Return value    : none
 ******************************************************************************/
void usb_hstd_do_sqtgl (usb_utr_t *ptr, uint16_t pipe, uint16_t toggle)
{
    /* Check toggle */
    if ((toggle & USB_SQMON) == USB_SQMON)
    {
        /* Do pipe SQSET */
        hw_usb_set_sqset(ptr, pipe);
    }
    else
    {
        /* Do pipe SQCLR */
        hw_usb_set_sqclr(ptr, pipe);
    }
}
/******************************************************************************
 End of function usb_hstd_do_sqtgl
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_get_devsel
 Description     : Get device address from pipe number
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : uint16_t DEVSEL-bit status
 ******************************************************************************/
uint16_t usb_hstd_get_devsel (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t devsel;
    uint16_t buffer;

    if (USB_PIPE0 == pipe)
    {
        buffer = hw_usb_read_dcpmaxp(ptr);
    }
    else
    {
        /* Pipe select */
        hw_usb_write_pipesel(ptr, pipe);
        buffer = hw_usb_read_pipemaxp(ptr);
    }

    /* Device address */
    devsel = (uint16_t) (buffer & USB_DEVSEL);

    return devsel;
}
/******************************************************************************
 End of function usb_hstd_get_devsel
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_get_device_address
 Description     : Get the device address associated with the specified pipe.
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     pipe    : Pipe number.
 Return value    : uint16_t     DEVSEL-bit status
 ******************************************************************************/
uint16_t usb_hstd_get_device_address (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t buffer;
    uint16_t i;
    uint16_t md;
    usb_hcdreg_t *pdriver;

    /* Host */
    if (USB_PIPE0 == pipe)
    {
        buffer = hw_usb_read_dcpmaxp(ptr);

        /* Device address */
        return (uint16_t) (buffer & USB_DEVSEL);
    }
    else
    {
        for (md = 0; md < g_usb_hstd_device_num[ptr->ip]; md++)
        {
            if ((USB_IFCLS_NOT != g_usb_hstd_device_drv[ptr->ip][md].ifclass)
                    && (USB_NODEVICE != g_usb_hstd_device_drv[ptr->ip][md].devaddr))
            {
                pdriver = (usb_hcdreg_t*) &g_usb_hstd_device_drv[ptr->ip][md];

                /* EP table loop */
                for (i = 0; USB_PDTBLEND != pdriver->p_pipetbl[i]; i += USB_EPL)
                {
                    if (pdriver->p_pipetbl[i] == pipe)
                    {
                        buffer = pdriver->p_pipetbl[i + 3];

                        /* Device address */
                        return (uint16_t) (buffer & USB_DEVSEL);
                    }
                }
            }
        }
    }

    return USB_ERROR;
}
/******************************************************************************
 End of function usb_hstd_get_device_address
 ******************************************************************************/
 
/******************************************************************************
 Function Name   : usb_hstd_write_data
 Description     : Switch PIPE, request the USB FIFO to write data, and manage 
                 : the size of written data.
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
                 : uint16_t     pipe        : Pipe no.
                 : uint16_t     pipemode    : CUSE/D0DMA/D1DMA
 Return value    : uint16_t end_flag
 ******************************************************************************/
uint16_t usb_hstd_write_data (usb_utr_t *ptr, uint16_t pipe, uint16_t pipemode)
{
    uint16_t size;
    uint16_t count;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t end_flag;

    /* Changes FIFO port by the pipe. */
    if ((USB_CUSE == pipemode) && (USB_PIPE0 == pipe))
    {
        buffer = usb_cstd_is_set_frdy(ptr, pipe, (uint16_t) USB_CUSE, (uint16_t) USB_ISEL);
    }
    else
    {
        buffer = usb_cstd_is_set_frdy(ptr, pipe, (uint16_t) pipemode, USB_FALSE);
    }

    /* Check error */
    if (USB_FIFOERROR == buffer)
    {
        /* FIFO access error */
        return (USB_FIFOERROR);
    }

    /* Data buffer size */
    size = usb_cstd_get_buf_size(ptr, pipe);

    /* Max Packet Size */
    mxps = usb_cstd_get_maxpacket_size(ptr, pipe);

    /* Data size check */
    if (g_usb_hstd_data_cnt[ptr->ip][pipe] <= (uint32_t) size)
    {
        count = (uint16_t) g_usb_hstd_data_cnt[ptr->ip][pipe];

        /* Data count check */
        if (0 == count)
        {
            /* Null Packet is end of write */
            end_flag = USB_WRITESHRT;
        }
        else if ((count % mxps) != 0)
        {
            /* Short Packet is end of write */
            end_flag = USB_WRITESHRT;
        }
        else
        {
            if (USB_PIPE0 == pipe)
            {
                /* Just Send Size */
                end_flag = USB_WRITING;
            }
            else
            {
                /* Write continues */
                end_flag = USB_WRITEEND;
            }
        }
    }
    else
    {
        /* Write continues */
        end_flag = USB_WRITING;
        count = size;
    }

    g_p_usb_hstd_data[ptr->ip][pipe] = usb_hstd_write_fifo(ptr, count, pipemode, g_p_usb_hstd_data[ptr->ip][pipe]);

    /* Check data count to remain */
    if (g_usb_hstd_data_cnt[ptr->ip][pipe] < (uint32_t) size)
    {
        /* Clear data count */
        g_usb_hstd_data_cnt[ptr->ip][pipe] = (uint32_t) 0u;
        buffer = hw_usb_read_fifoctr(ptr, pipemode); /* Read CFIFOCTR */

        /* Check BVAL */
        if ((buffer & USB_BVAL) == 0u)
        {
            /* Short Packet */
            hw_usb_set_bval(ptr, pipemode);
        }
    }
    else
    {
        /* Total data count - count */
        g_usb_hstd_data_cnt[ptr->ip][pipe] -= count;
    }

    /* End or Err or Continue */
    return end_flag;
}
/******************************************************************************
 End of function usb_hstd_write_data
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_receive_start
 Description     : Start data reception using CPU/DMA transfer to USB Host/USB
                 : device.
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     pipe    : Pipe no.
 Return value    : none
 ******************************************************************************/
void usb_hstd_receive_start (usb_utr_t *ptr, uint16_t pipe)
{
    usb_utr_t *pp;
    uint32_t length;
    uint16_t mxps;
    uint16_t useport;
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint16_t dma_ch;
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    /* Evacuation pointer */
    pp = g_p_usb_hstd_pipe[ptr->ip][pipe];
    length = pp->tranlen;

    /* Check transfer count */
    if (USB_TRAN_CONT == pp->segment)
    {
        /* Sequence toggle */
        usb_hstd_do_sqtgl(ptr, pipe, pp->pipectr);
    }

    /* Select NAK */
    usb_cstd_select_nak(ptr, pipe);
    g_usb_hstd_data_cnt[ptr->ip][pipe] = length; /* Set data count */
    g_p_usb_hstd_data[ptr->ip][pipe] = (uint8_t*) pp->p_tranadr; /* Set data pointer */

    /* Ignore count clear */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0u;

    /* Pipe number to FIFO port select */
    useport = usb_hstd_pipe2fport(ptr, pipe);

    /* Check use FIFO access */
    switch (useport)
    {
        /* D0FIFO use */
        case USB_D0USE :

            /* D0 FIFO access is NG */
            USB_PRINTF1("### USB-ITRON is not support(RCV-D0USE:pipe%d)\n", pipe);
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);
        break;

            /* CFIFO use */
        case USB_CUSE :

            /* continue */

            /* D1FIFO use */
        case USB_D1USE :

            /* Changes the FIFO port by the pipe. */
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
            mxps = usb_cstd_get_maxpacket_size(ptr, pipe); /* Max Packet Size */
            if ((uint32_t) 0u != length)
            {
                /* Data length check */
                if ((length % mxps) == (uint32_t) 0u)
                {
                    /* Set Transaction counter */
                    usb_cstd_set_transaction_counter(ptr, pipe, (uint16_t) (length / mxps));
                }
                else
                {
                    /* Set Transaction counter */
                    usb_cstd_set_transaction_counter(ptr, pipe, (uint16_t) ((length / mxps) + (uint32_t) 1u));
                }
            }

            usb_cstd_set_buf(ptr, pipe); /* Set BUF */

            /* Enable Ready Interrupt */
            hw_usb_set_brdyenb(ptr, pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(ptr, pipe);
        break;

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
            /* D1FIFO DMA */
            case USB_D1DMA:
            /* D0FIFO DMA */
            case USB_D0DMA:
            if (USB_IP0 == ptr->ip)
            {
                dma_ch = USB_CFG_USB0_DMA_RX;
            }
            else
            {
                dma_ch = USB_CFG_USB1_DMA_RX;
            }

            usb_dma_set_ch_no(ptr->ip, useport, dma_ch);

            /* Setting for use PIPE number */
            g_usb_cstd_dma_pipe[ptr->ip][dma_ch] = pipe;
            /* Buffer size */
            g_usb_cstd_dma_fifo[ptr->ip][dma_ch] = usb_cstd_get_buf_size(ptr, pipe);

            /* Transfer data size */
            g_usb_cstd_dma_size[ptr->ip][dma_ch] = g_usb_hstd_data_cnt[ptr->ip][pipe];
            usb_cstd_dxfifo2buf_start_dma( ptr, pipe, useport, length );

            break;

#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        default :
            USB_PRINTF1("### USB-ITRON is not support(RCV-else:pipe%d)\n", pipe);
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);
        break;
    }
}
/******************************************************************************
 End of function usb_hstd_receive_start
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_read_data
 Description     : Request to read data from USB FIFO, and manage the size of 
                 : the data read.
 Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
                 : uint16_t     pipe        : Pipe no.
                 : uint16_t     pipemode    : Pipe mode (CFIFO/D0FIFO/D1FIFO)
 Return value    : USB_READING / USB_READEND / USB_READSHRT / USB_READOVER
 ******************************************************************************/
uint16_t usb_hstd_read_data (usb_utr_t *ptr, uint16_t pipe, uint16_t pipemode)
{
    uint16_t count;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t dtln;
    uint16_t end_flag;

    /* Changes FIFO port by the pipe. */
    buffer = usb_cstd_is_set_frdy(ptr, pipe, (uint16_t) pipemode, USB_FALSE);
    if (USB_FIFOERROR == buffer)
    {
        /* FIFO access error */
        return (USB_FIFOERROR);
    }
    dtln = (uint16_t) (buffer & USB_DTLN);

    /* Max Packet Size */
    mxps = usb_cstd_get_maxpacket_size(ptr, pipe);

    if (g_usb_hstd_data_cnt[ptr->ip][pipe] < dtln)
    {
        /* Buffer Over ? */
        end_flag = USB_READOVER;
        usb_cstd_set_nak(ptr, pipe); /* Set NAK */
        count = (uint16_t) g_usb_hstd_data_cnt[ptr->ip][pipe];
        g_usb_hstd_data_cnt[ptr->ip][pipe] = dtln;
    }
    else if (g_usb_hstd_data_cnt[ptr->ip][pipe] == dtln)
    {
        /* Just Receive Size */
        count = dtln;
        end_flag = USB_READEND;
        usb_cstd_select_nak(ptr, pipe); /* Set NAK */
    }
    else
    {
        /* Continus Receive data */
        count = dtln;
        end_flag = USB_READING;
        if ((0 == count) || (0 != (count % mxps)))
        {
            /* Null Packet receive */
            end_flag = USB_READSHRT;
            usb_cstd_select_nak(ptr, pipe); /* Select NAK */
        }
    }

    if (0 == dtln)
    {
        /* 0 length packet */
        /* Clear BVAL */
        hw_usb_set_bclr(ptr, pipemode);
    }
    else
    {
        g_p_usb_hstd_data[ptr->ip][pipe] = usb_hstd_read_fifo(ptr, count, pipemode,
                g_p_usb_hstd_data[ptr->ip][pipe]);
    }
    g_usb_hstd_data_cnt[ptr->ip][pipe] -= count;

    /* End or Err or Continue */
    return (end_flag);
}
/******************************************************************************
 End of function usb_hstd_read_data
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_data_end
 Description     : Set USB registers as appropriate after data transmission/re-
                 : ception, and call the callback function as transmission/recep-
                 : tion is complete.
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     pipe    : Pipe no.
                 : uint16_t     status  : Transfer status type.
 Return value    : none
 ******************************************************************************/
void usb_hstd_data_end (usb_utr_t *ptr, uint16_t pipe, uint16_t status)
{
    uint16_t useport;
    uint16_t ip;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
#if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

#else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

#endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
#else   /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
        ip = USB_NULL;

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    /* PID = NAK */
    /* Set NAK */
    usb_cstd_select_nak(ptr, pipe);

    /* Pipe number to FIFO port select */
    useport = usb_hstd_pipe2fport(ptr, pipe);

    /* Disable Interrupt */
    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(ptr, pipe);

    /* Disable Not Ready Interrupt */
    hw_usb_clear_nrdyenb(ptr, pipe);

    /* Disable Empty Interrupt */
    hw_usb_clear_bempenb(ptr, pipe);

    /* Disable Transaction count */
    usb_cstd_clr_transaction_counter(ptr, pipe);

    /* Check use FIFO */
    switch (useport)
    {
        /* CFIFO use */
        case USB_CUSE :
        break;

            /* D0FIFO use */
        case USB_D0USE :
        break;

            /* D1FIFO use */
        case USB_D1USE :
        break;

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
            /* D0FIFO DMA */
            case USB_D0DMA:
                /* DMA buffer clear mode clear */
                hw_usb_clear_dclrm( ptr, USB_D0DMA );
                if (USB_USBIP_0 == ip)
                {
                    hw_usb_set_mbw( ptr, USB_D0DMA, USB0_D0FIFO_MBW );
                }
                else if (USB_USBIP_1 == ip)
                {
                    hw_usb_set_mbw( ptr, USB_D0DMA, USB1_D0FIFO_MBW );
                }
                else
                {
                    /* None */
                }
            break;
            /* D1FIFO DMA */
            case USB_D1DMA:
                /* DMA buffer clear mode clear */
                hw_usb_clear_dclrm( ptr, USB_D1DMA );
                if (USB_USBIP_0 == ip)
                {
                    hw_usb_set_mbw( ptr, USB_D1DMA, USB0_D1FIFO_MBW );
                }
                else if (USB_USBIP_1 == ip)
                {
                    hw_usb_set_mbw( ptr, USB_D1DMA, USB1_D1FIFO_MBW );
                }
                else
                {
                    /* None */
                }
            break;
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        default :
        break;
    }

    /* Call Back */
    if (USB_NULL != g_p_usb_hstd_pipe[ip][pipe])
    {
        /* Check PIPE TYPE */
        if (USB_TYPFIELD_ISO != usb_cstd_get_pipe_type(ptr, pipe))
        {
            /* Transfer information set */
            g_p_usb_hstd_pipe[ip][pipe]->tranlen = g_usb_hstd_data_cnt[ip][pipe];
            g_p_usb_hstd_pipe[ip][pipe]->status = status;
            g_p_usb_hstd_pipe[ip][pipe]->pipectr = hw_usb_read_pipectr(ptr, pipe);
            g_p_usb_hstd_pipe[ip][pipe]->errcnt = (uint8_t) g_usb_hstd_ignore_cnt[ip][pipe];
            g_p_usb_hstd_pipe[ip][pipe]->ipp = usb_hstd_get_usb_ip_adr(ip);
            g_p_usb_hstd_pipe[ip][pipe]->ip = ip;
            if (USB_NULL == g_p_usb_hstd_pipe[ip][pipe]->complete)   /* Chack Callback function */
            {
                while(1)
                {
                    /* Error Stop */
                }
            }
            (g_p_usb_hstd_pipe[ip][pipe]->complete)(g_p_usb_hstd_pipe[ip][pipe], 0, 0);
            g_p_usb_hstd_pipe[ip][pipe] = (usb_utr_t*) USB_NULL;
        }
        else
        {
            /* Transfer information set */
            g_p_usb_hstd_pipe[ip][pipe]->tranlen = g_usb_hstd_data_cnt[ip][pipe];
            g_p_usb_hstd_pipe[ip][pipe]->pipectr = hw_usb_read_pipectr(ptr, pipe);
            g_p_usb_hstd_pipe[ip][pipe]->errcnt = (uint8_t) g_usb_hstd_ignore_cnt[ip][pipe];
            g_p_usb_hstd_pipe[ip][pipe]->ipp = usb_hstd_get_usb_ip_adr(ip);
            g_p_usb_hstd_pipe[ip][pipe]->ip = ip;

            /* Data Transfer (restart) */
            if (usb_cstd_get_pipe_dir(ptr, pipe) == USB_BUF2FIFO)
            {
                /* OUT Transfer */
                g_p_usb_hstd_pipe[ip][pipe]->status = USB_DATA_WRITING;
                if (USB_NULL == g_p_usb_hstd_pipe[ip][pipe]->complete)   /* Chack Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (g_p_usb_hstd_pipe[ip][pipe]->complete)(g_p_usb_hstd_pipe[ip][pipe], 0, 0);
            }
            else
            {
                /* IN Transfer */
                g_p_usb_hstd_pipe[ip][pipe]->status = USB_DATA_READING;
                if (USB_NULL == g_p_usb_hstd_pipe[ip][pipe]->complete)   /* Chack Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (g_p_usb_hstd_pipe[ip][pipe]->complete)(g_p_usb_hstd_pipe[ip][pipe], 0, 0);
            }
        }
    }
}
/******************************************************************************
 End of function usb_hstd_data_end
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_brdy_pipe_process
 Description     : Search for the PIPE No. that BRDY interrupt occurred, and 
                 : request data transmission/reception from the PIPE
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     bitsts  : BRDYSTS Register & BRDYENB Register
 Return value    : none
 ******************************************************************************/
void usb_hstd_brdy_pipe_process (usb_utr_t *ptr, uint16_t bitsts)
{
    uint16_t useport;
    uint16_t i;
    uint16_t ip;

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint16_t buffer;
    uint16_t maxps;
    uint16_t set_dtc_brock_cnt;
    uint16_t trans_dtc_block_cnt;
    uint16_t dma_ch;
    uint16_t status;

#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    ip = ptr->ip;
    for (i = USB_PIPE1; i <= USB_MAX_PIPE_NO; i++)
    {
        if ((bitsts & USB_BITSET(i)) != 0)
        {
            /* Interrupt check */
            hw_usb_clear_status_bemp(ptr, i);

            if (USB_NULL != g_p_usb_hstd_pipe[ip][i])
            {
                /* Pipe number to FIFO port select */
                useport = usb_hstd_pipe2fport(ptr, i);
                if ((USB_D0DMA == useport) || (USB_D1DMA == useport))
                {
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
                    dma_ch = usb_dma_ref_ch_no(ip, useport);

                    maxps = g_usb_cstd_dma_fifo[ip][dma_ch];

                    /* DMA Transfer request disable */
                    hw_usb_clear_dreqe( ptr, useport );

                    /* DMA stop */
                    usb_dma_stop_dxfifo(ptr->ip, useport);

                    /* Changes FIFO port by the pipe. */
                    buffer = usb_cstd_is_set_frdy(ptr, i, useport, USB_FALSE);

                    set_dtc_brock_cnt = (uint16_t)((g_usb_hstd_data_cnt[ip][g_usb_cstd_dma_pipe[ip][dma_ch]] -1)
                            / g_usb_cstd_dma_fifo[ip][dma_ch]) +1;

                    trans_dtc_block_cnt = usb_dma_get_crtb(dma_ch);

                    /* Get D0fifo Receive Data Length */
                    g_usb_cstd_dma_size[ip][dma_ch]
                    = (uint32_t)(buffer & USB_DTLN) + ((set_dtc_brock_cnt - (trans_dtc_block_cnt + 1)) * maxps);

                    /* Check data count */
                    if (g_usb_cstd_dma_size[ip][dma_ch] == g_usb_hstd_data_cnt[ptr->ip][i])
                    {
                        status = USB_DATA_OK;
                    }
                    else if (g_usb_cstd_dma_size[ip][dma_ch] > g_usb_hstd_data_cnt[ip][i])
                    {
                        status = USB_DATA_OVR;
                    }
                    else
                    {
                        status = USB_DATA_SHT;
                    }
                    /* D0FIFO access DMA stop */
                    usb_cstd_dxfifo_stop(ptr, useport);
                    /* End of data transfer */
                    usb_hstd_data_end(ptr, i, status);
                    /* Set BCLR */
                    hw_usb_set_bclr( ptr, useport );

#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
                }
                else
                {
                    if (usb_cstd_get_pipe_dir(ptr, i) == USB_BUF2FIFO)
                    {
                        /* Buffer to FIFO data write */
                        usb_hstd_buf_to_fifo(ptr, i, useport);
                    }
                    else
                    {
                        /* FIFO to Buffer data read */
                        usb_hstd_fifo_to_buf(ptr, i, useport);
                    }
                }
            }
        }
    }
}/* End of function usb_hstd_brdy_pipe_process() */

/******************************************************************************
 Function Name   : usb_hstd_nrdy_pipe_process
 Description     : Search for PIPE No. that occurred NRDY interrupt, and execute 
                 : the process for PIPE when NRDY interrupt occurred
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     bitsts  : NRDYSTS Register & NRDYENB Register
 Return value    : none
 ******************************************************************************/
void usb_hstd_nrdy_pipe_process (usb_utr_t *ptr, uint16_t bitsts)
{
    uint16_t buffer;
    uint16_t i;

    for (i = USB_MIN_PIPE_NO; i <= USB_MAX_PIPE_NO; i++)
    {
        if ((bitsts & USB_BITSET(i)) != 0)
        {
            /* Interrupt check */
            if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][i])
            {
                if (usb_cstd_get_pipe_type(ptr, i) == USB_TYPFIELD_ISO)
                {
                    /* Wait for About 60ns */
                    buffer = hw_usb_read_frmnum(ptr);
                    if ((buffer & USB_OVRN) == USB_OVRN)
                    {
                        /* @1 */
                        /* End of data transfer */
                        usb_hstd_forced_termination(ptr, i, (uint16_t) USB_DATA_OVR);
                        USB_PRINTF1("###ISO OVRN %d\n", g_usb_hstd_data_cnt[ptr->ip][i]);
                    }
                    else
                    {
                        /* @2 */
                        /* End of data transfer */
                        usb_hstd_forced_termination(ptr, i, (uint16_t) USB_DATA_ERR);
                    }
                }
                else
                {
                    usb_hstd_nrdy_endprocess(ptr, i);
                }
            }
        }
    }
}
/******************************************************************************
 End of function usb_hstd_nrdy_pipe_process
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_bemp_pipe_process
 Description     : Search for PIPE No. that BEMP interrupt occurred, and complete data transmission for the PIPE
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     bitsts  : BEMPSTS Register & BEMPENB Register
 Return value    : none
 ******************************************************************************/
void usb_hstd_bemp_pipe_process (usb_utr_t *ptr, uint16_t bitsts)
{
    uint16_t buffer;
    uint16_t i;
    uint16_t useport;

    for (i = USB_MIN_PIPE_NO; i <= USB_PIPE5; i++)
    {
        if ((bitsts & USB_BITSET(i)) != 0)
        {
            /* Interrupt check */
            if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][i])
            {
                buffer = usb_cstd_get_pid(ptr, i);

                /* MAX packet size error ? */
                if ((buffer & USB_PID_STALL) == USB_PID_STALL)
                {
                    USB_PRINTF1("### STALL Pipe %d\n", i);
                    usb_hstd_forced_termination(ptr, i, (uint16_t) USB_DATA_STALL);
                }
                else
                {
                    if ((hw_usb_read_pipectr(ptr, i) & USB_INBUFM) != USB_INBUFM)
                    {
                        /* Pipe number to FIFO port select */
                        useport = usb_hstd_pipe2fport(ptr, i);

                        if (USB_D0DMA == useport)
                        {
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
                            hw_usb_clear_status_bemp( ptr, i );
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
                        }

                        /* End of data transfer */
                        usb_hstd_data_end(ptr, i, (uint16_t) USB_DATA_NONE);
                    }
                }
            }
        }
    }
    for (i = USB_PIPE6; i <= USB_MAX_PIPE_NO; i++)
    {
        /* Interrupt check */
        if ((bitsts & USB_BITSET(i)) != 0)
        {
            if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][i])
            {
                buffer = usb_cstd_get_pid(ptr, i);

                /* MAX packet size error ? */
                if ((buffer & USB_PID_STALL) == USB_PID_STALL)
                {
                    /*USB_PRINTF1("### STALL Pipe %d\n", i);*/
                    usb_hstd_forced_termination(ptr, i, (uint16_t) USB_DATA_STALL);
                }
                else
                {
                    /* End of data transfer */
                    usb_hstd_data_end(ptr, i, (uint16_t) USB_DATA_NONE);
                }
            }
        }
    }
}
/******************************************************************************
 End of function usb_hstd_bemp_pipe_process
 ******************************************************************************/

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 End  Of File
 ******************************************************************************/
