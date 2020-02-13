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
* Copyright (C) 2015(2017) Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_usb_dma.c
* Description  : Setting code of DMA
***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 30.09.2016 1.00 First release
 *         : 26.01.2017 1.21 Support DMAC Technical Update for RX71M/RX64M USBA.
 *         : 30.09.2017 1.22    Change functions name
 *                              "usb_hstd_buf2fifo"->"usb_hstd_buf_to_fifo"
 *                              "usb_pstd_buf2fifo"->"usb_pstd_buf_to_fifo"
 *                              "usb_dma_buf2fifo_restart"->"usb_dma_buf_to_fifo_restart"
 ***********************************************************************************************************************/

/*******************************************************************************
Includes   <System Includes>, "Project Includes"
*******************************************************************************/
#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"


#if USB_CFG_DTC == USB_CFG_ENABLE
#include "r_dtc_rx_if.h"
#endif /* USB_CFG_DTC == USB_CFG_ENABLE */

#if USB_CFG_DMA == USB_CFG_ENABLE
#include "r_dmaca_rx_if.h"
#endif /* USB_CFG_DMA == USB_CFG_ENABLE */

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
#include "r_usb_dmac.h"

/******************************************************************************
Exported global functions (to be accessed by other files)
******************************************************************************/
#if USB_CFG_DTC == USB_CFG_ENABLE
dtc_transfer_data_t        g_usb_dtc_transfer_data[USB_DMA_USE_CH_MAX];

#endif  /* USB_CFG_DTC == USB_CFG_ENABLE */

usb_dma_int_t   g_usb_cstd_dma_int;         /* DMA Interrupt Info */

uint32_t    g_usb_cstd_dma_size[USB_NUM_USBIP][USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 buffer size */
uint16_t    g_usb_cstd_dma_fifo[USB_NUM_USBIP][USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 FIFO buffer size */
uint16_t    g_usb_cstd_dma_pipe[USB_NUM_USBIP][USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 pipe number */

uint8_t     g_usb_cstd_dma_ch[USB_NUM_USBIP][USB_FIFO_ACCESS_NUM_MAX];  /* DMA ch no. table */

uint8_t     g_usb_cstd_dma_fraction_size[USB_NUM_USBIP][USB_DMA_USE_CH_MAX];   /* fraction size(1-3) */
uint32_t    g_usb_cstd_dma_fraction_adr[USB_NUM_USBIP][USB_DMA_USE_CH_MAX];    /* fraction data address */
uint32_t  g_fifo_address[USB_NUM_USBIP][USB_DMA_FIFO_TYPE_NUM][USB_FIFO_ACCSESS_TYPE_NUM] =
{
  {
    /* IP0 */
    /* 32bit            16bit               8bit */
    {(uint32_t)0,                 (uint32_t)&USB_M0.D0FIFO.WORD,  (uint32_t)&USB_M0.D0FIFO.BYTE.L},   /* USB0 D0FIFO address */
    {(uint32_t)0,                 (uint32_t)&USB_M0.D1FIFO.WORD,  (uint32_t)&USB_M0.D1FIFO.BYTE.L},
  },
#if USB_NUM_USBIP == 2
  {
    /* IP1 */
#if defined(BSP_MCU_RX63N)
    {(uint32_t)0,                 (uint32_t)&USB_M1.D0FIFO.WORD,  (uint32_t)&USB_M1.D0FIFO.BYTE.L},   /* USB0 D0FIFO address */
    {(uint32_t)0,                 (uint32_t)&USB_M1.D1FIFO.WORD,  (uint32_t)&USB_M1.D1FIFO.BYTE.L},

#endif  /* defined(BSP_MCU_RX63N) */

#if defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX64M)

    /* Little */
#if USB_CFG_ENDIAN == USB_CFG_LITTLE
    {(uint32_t)&USB_M1.D0FIFO.LONG, (uint32_t)&USB_M1.D0FIFO.WORD.H,(uint32_t)&USB_M1.D0FIFO.BYTE.HH}, /* USBA D0FIFO adr Little */
    {(uint32_t)&USB_M1.D1FIFO.LONG, (uint32_t)&USB_M1.D1FIFO.WORD.H,(uint32_t)&USB_M1.D1FIFO.BYTE.HH}  /* USBA D1FIFO adr Little */

#endif  /* USB_CFG_ENDIAN == USB_CFG_LITTLE */

    /* Big */
#if USB_CFG_ENDIAN == USB_CFG_BIG
    {(uint32_t)&USB_M1.D0FIFO.LONG, (uint32_t)&USB_M1.D0FIFO.WORD.L,(uint32_t)&USB_M1.D0FIFO.BYTE.LL}, /* USBA D0FIFO adr Big */
    {(uint32_t)&USB_M1.D1FIFO.LONG, (uint32_t)&USB_M1.D1FIFO.WORD.L,(uint32_t)&USB_M1.D1FIFO.BYTE.LL}  /* USBA D1FIFO adr Big */

#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */
#endif  /* defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX64M) */
  }

#endif  /* USB_NUM_USBIP == 2 */
};

extern uint16_t g_usb_usbmode;      /* USB mode HOST/PERI */

/******************************************************************************
Function Name   : usb_cstd_buf2dxfifo_start_dma
Description     : Start transfer using DMA. If transfer size is 0, write
                : more data to buffer.
Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure
                : uint16_t pipe   : Pipe number
                : uint16_t useport: FIFO select
Return value    : none
******************************************************************************/
void usb_cstd_buf2dxfifo_start_dma(usb_utr_t *ptr, uint16_t pipe, uint16_t useport)
{
    uint32_t    dma_size;
    uint32_t    fifo_size;
    uint8_t     *p_data_ptr;
    uint16_t    ip;
    uint16_t    ch;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        p_data_ptr = g_p_usb_hstd_data[ptr->ip][pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */

#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        p_data_ptr = g_p_usb_pstd_data[pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    ch = usb_dma_ref_ch_no(ip, useport);

    dma_size = g_usb_cstd_dma_size[ip][ch];
    fifo_size = g_usb_cstd_dma_fifo[ip][ch];

     if (USB_IP0 == ip)
     {
        dma_size &= ~USB_BIT_MBW16;
     }
     else
     {
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        dma_size &= ~USB_BIT_MBW32;
#else
        dma_size &= ~USB_BIT_MBW16;
#endif
     }

    if (0u != dma_size)
    {
        hw_usb_clear_dreqe(ptr, useport);       /* DMA Transfer request disable */

        usb_dma_clear_dxfifo_ir(ptr, useport);

        if (dma_size >= fifo_size)
        {
            /* Fifosize block transfer */
            dma_size = (dma_size - (dma_size % fifo_size));
        }
        else
        {
            if (USB_IP0 == ip)
            {
                /* fraction size(1-3) */
                g_usb_cstd_dma_fraction_size[ip][ch] = g_usb_cstd_dma_size[ip][ch] & USB_BIT_MBW16;
            }
            else
            {
    #if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
                /* fraction size(1-3) */
                g_usb_cstd_dma_fraction_size[ip][ch] = g_usb_cstd_dma_size[ip][ch] & USB_BIT_MBW32;
    #else
                /* fraction size(1-3) */
                g_usb_cstd_dma_fraction_size[ip][ch] = g_usb_cstd_dma_size[ip][ch] & USB_BIT_MBW16;
    #endif
            }

            g_usb_cstd_dma_fraction_adr[ip][ch]  = (uint32_t)(p_data_ptr + dma_size);  /* fraction data address */
        }

        g_usb_cstd_dma_size[ip][ch] = dma_size;

        usb_dma_buf2dxfifo_setting(ptr, (uint32_t)p_data_ptr, useport, dma_size);

        /* Changes the FIFO port by the pipe. */
        if (false == usb_check_use_usba_module(ptr))
        {
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
        }

        hw_usb_set_dreqe(ptr, useport);

        if (true == usb_check_use_usba_module(ptr))
        {
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
        }
    }
    else
    {
        if (USB_D0DMA == useport)
        {
            useport = USB_D0USE;
        }
        else
        {
            useport = USB_D1USE;
        }
        if (USB_HOST == g_usb_usbmode)
        {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
            usb_hstd_buf_to_fifo(ptr, pipe, useport);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
            usb_pstd_buf_to_fifo(pipe, useport);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
        }
    }
}
/******************************************************************************
End of function usb_cstd_buf2dxfifo_start_dma
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dxfifo2buf_start_dma
Description     : Start transfer using DMA. If transfer size is 0, clear DMA.
Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
                : uint16_t pipe     : Pipe number
                : uint16_t useport  : FIFO select
                : uint32_t length   : Data length
Return value    : none
******************************************************************************/
void usb_cstd_dxfifo2buf_start_dma(usb_utr_t *ptr, uint16_t pipe, uint16_t useport, uint32_t length)
{
    uint16_t mxps;

    uint32_t dma_size;
    uint32_t transfer_size;
    uint8_t     *p_data_ptr;
    uint16_t    ip;
    uint16_t    ch;

    if (USB_NULL != ptr)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        p_data_ptr = g_p_usb_hstd_data[ptr->ip][pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        p_data_ptr = g_p_usb_pstd_data[pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    ch = usb_dma_ref_ch_no(ip, useport);

    dma_size = g_usb_cstd_dma_size[ip][ch];
    transfer_size = g_usb_cstd_dma_size[ip][ch];


    /* Data size check */
    if (0u != dma_size)
    {
        hw_usb_clear_dreqe(ptr, useport);       /* DMA Transfer request disable */

        usb_dma_clear_dxfifo_ir(ptr, useport);

        usb_dma_dxfifo2buf_setting(ptr, (uint32_t)p_data_ptr, useport, transfer_size);

        /* Changes the FIFO port by the pipe. */
        if (false == usb_check_use_usba_module(ptr))
        {
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
        }

        /* Max Packet Size */
        mxps = usb_cstd_get_maxpacket_size(ptr, pipe);

        /* Set Transaction counter */
        usb_cstd_set_transaction_counter(ptr, pipe, (uint16_t)(((length - (uint32_t)1u)/ mxps) + (uint32_t)1u));

        /* Set BUF */
        usb_cstd_set_buf(ptr, pipe);

        /* Enable Ready Interrupt */
        hw_usb_set_brdyenb(ptr, pipe);

        /* Enable Not Ready Interrupt */
        usb_cstd_nrdy_enable(ptr, pipe);

        /* usb fifo set automatic clear mode  */
        hw_usb_clear_dclrm(ptr, useport);

        /* Set DREQ enable */
        hw_usb_set_dreqe(ptr, useport);

        if (true == usb_check_use_usba_module(ptr))
        {
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
        }

    }
    else
    {
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);

        /* DMA buffer clear mode set */
        hw_usb_set_dclrm(ptr, useport);

        /* Set BUF */
        usb_cstd_set_buf(ptr, pipe);

        /* Enable Ready Interrupt */
        hw_usb_set_brdyenb(ptr, pipe);

        /* Enable Not Ready Interrupt */
        usb_cstd_nrdy_enable(ptr, pipe);
    }
}
/******************************************************************************
End of function usb_cstd_dxfifo2buf_start_dma
******************************************************************************/


/******************************************************************************
Function Name   : usb_cstd_dxfifo_stop
Description     : Setup external variables used for USB data transfer; to reg-
                : ister if you want to stop the transfer of DMA.
Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
                : uint16_t useport  : FIFO select
Return value    : none
******************************************************************************/
void usb_cstd_dxfifo_stop(usb_utr_t *ptr, uint16_t useport)
{
    uint16_t    pipe;
    uint16_t    ip;
    uint32_t    *p_data_cnt;
    uint16_t    mbw_setting;
    uint16_t    channel;

    if (USB_NULL == ptr)
    {
#if USB_CFG_USE_USBIP == USB_CFG_IP0
        ip = USB_IP0;

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        ip = USB_IP1;

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }
    else
    {
        ip = ptr->ip;
    }

    channel = usb_dma_ref_ch_no(ip, useport);
    pipe = g_usb_cstd_dma_pipe[ip][channel];

    if (USB_NULL == ptr)
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        p_data_cnt = &g_usb_pstd_data_cnt[pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        p_data_cnt = &g_usb_hstd_data_cnt[ptr->ip][pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    if (USB_D0DMA == useport)
    {
        if (USB_IP0 == ip)
        {
            mbw_setting = USB0_D0FIFO_MBW;
        }
        else
        {
            mbw_setting = USB1_D0FIFO_MBW;
        }
    }
    else
    {
        if (USB_IP0 == ip)
        {
            mbw_setting = USB0_D1FIFO_MBW;
        }
        else
        {
            mbw_setting = USB1_D1FIFO_MBW;
        }
    }

    hw_usb_set_mbw( ptr, useport, mbw_setting );

    /* received data size */
    *p_data_cnt = (*p_data_cnt) - g_usb_cstd_dma_size[ip][channel];
}
/******************************************************************************
End of function usb_cstd_dxfifo_stop
******************************************************************************/

/******************************************************************************
Function Name   : usb_dma_driver
Description     : USB DMA transfer complete process.
Arguments       : none
Return value    : none
******************************************************************************/
void usb_dma_driver(void)
{
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    usb_utr_t   utr;

#endif  /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

    if (g_usb_cstd_dma_int.wp != g_usb_cstd_dma_int.rp)
    {
        if (USB_HOST == g_usb_usbmode)
        {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
            utr.ip = g_usb_cstd_dma_int.buf[g_usb_cstd_dma_int.rp].ip;
            utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

            usb_dma_stop_dxfifo(utr.ip, g_usb_cstd_dma_int.buf[g_usb_cstd_dma_int.rp].fifo_type);  /* Stop DMA,FIFO access */

            usb_dma_buf2dxfifo_complete(&utr, g_usb_cstd_dma_int.buf[g_usb_cstd_dma_int.rp].fifo_type);

#endif  /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
        }
        else
        {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )

            usb_dma_stop_dxfifo(USB_CFG_USE_USBIP, g_usb_cstd_dma_int.buf[g_usb_cstd_dma_int.rp].fifo_type);  /* Stop DMA,FIFO access */

            usb_dma_buf2dxfifo_complete(USB_NULL, g_usb_cstd_dma_int.buf[g_usb_cstd_dma_int.rp].fifo_type);

#endif  /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
        }

        /* Read countup */
        g_usb_cstd_dma_int.rp = ((g_usb_cstd_dma_int.rp+1) % USB_INT_BUFSIZE);
    }
}
/******************************************************************************
End of function usb_dma_driver
******************************************************************************/

/******************************************************************************
Function Name   : usb_dma_buf_to_fifo_restart
Description     : Start transfer using DMA0. accsess size 32bytes.
Arguments       : usb_utr_t *ptr     : Pointer to usb_utr_t structure
                : uint32_t src       : transfer data pointer
                : uint32_t data_size : transfer data size
                : uint16_t pipe      : Pipe number
Return value    : none
******************************************************************************/
void usb_dma_buf_to_fifo_restart(usb_utr_t *ptr, uint32_t src, uint32_t data_size, uint8_t pipe)
{
    uint16_t useport;

    if (USB_PIPE1 == pipe)
    {
        useport = USB_D0DMA;
    }
    else
    {
        useport = USB_D1DMA;
    }

    /* Changes the FIFO port by the pipe. */
    if (false == usb_check_use_usba_module(ptr))
    {
        usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
    }

    hw_usb_clear_dreqe(ptr, useport);       /* DMA Transfer request disable */

    usb_dma_clear_dxfifo_ir(ptr, useport);

    /* dma trans setting Divisible by FIFO buffer size  */
    usb_dma_buf2dxfifo_setting(ptr, src, useport, data_size);

    /* Set DREQ enable */
    hw_usb_set_dreqe(ptr, useport);

    if (true == usb_check_use_usba_module(ptr))
    {
        usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
    }
}
/******************************************************************************
End of function usb_dma_buf_to_fifo_restart
******************************************************************************/

/******************************************************************************
Function Name   : usb_dma_buf2dxfifo_complete
Description     : Set end of DMA transfer. Set to restart DMA trans-
                : fer according to data size of remaining functions to be pro-
                : cessed.
Arguments       : usb_utr_t *ptr     : Pointer to usb_utr_t structure
                : uint16_t useport   : FIFO select
Return value    : none
******************************************************************************/
void usb_dma_buf2dxfifo_complete(usb_utr_t *ptr, uint16_t useport)
{
    uint8_t     *p_src_adr;
    uint16_t    pipe;
    uint32_t    *p_data_cnt;
    uint8_t     *p_data_ptr;
    uint16_t    ip;
    uint16_t    channel;
    uint16_t    dma_size;
    bool        cpu_write = false;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    channel = usb_dma_ref_ch_no(ip, useport);
    pipe = g_usb_cstd_dma_pipe[ip][channel];

    if (USB_NULL != ptr)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        p_data_cnt = &g_usb_hstd_data_cnt[ptr->ip][pipe];
        p_data_ptr = g_p_usb_hstd_data[ptr->ip][pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        p_data_cnt = &g_usb_pstd_data_cnt[pipe];
        p_data_ptr = g_p_usb_pstd_data[pipe];
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    /* trans data smaller than Buffer size */
    /*  equal all data transfer end  */
    if ((*p_data_cnt) < g_usb_cstd_dma_fifo[ip][channel])
    {
        if (g_usb_cstd_dma_fraction_size[ip][channel] > 0)  /* fraction size(1-3) */
        {
            cpu_write = true;           /* Set flag for CPU FIFO Write */
        }
        else
        {
            /* FIFO buffer empty flag clear */
            hw_usb_clear_status_bemp(ptr, pipe);

            /* bval control for transfer enable fifo 2 usb control */
            hw_usb_set_bval(ptr, useport);

            /* FIFO bufer empty interrupt enable */
            hw_usb_set_bempenb(ptr, pipe);
        }
    }
    else
    {
        /* update remaining transfer data size */
        (*p_data_cnt) -= g_usb_cstd_dma_size[ip][channel];

        /* check transfer remaining data */
        if (0u == (*p_data_cnt))
        {
            /* FIFO buffer empty flag clear */
            hw_usb_clear_status_bemp(ptr, pipe);

            /* check FIFO_EMPTY / INBUF bit */
            if ((hw_usb_read_pipectr(ptr,  pipe ) & USB_INBUFM) != USB_INBUFM)
            {
                /* DMA transfer function end. call callback function */

                if (USB_NULL != ptr)
                {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
                    usb_hstd_data_end(ptr, pipe, (uint16_t)USB_DATA_NONE);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
                }
                else
                {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
                    usb_pstd_data_end(pipe, (uint16_t)USB_DATA_NONE);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
                }
            }
            else
            {
                /* FIFO bufer empty interrupt enable */
                hw_usb_set_bempenb(ptr, pipe);
            }
        }
        else
        {
            /* dma trans remaining data */
            /* DMA source address update */
            p_src_adr = (uint8_t *)((uint32_t)p_data_ptr + g_usb_cstd_dma_size[ip][channel]);

            /* DMA Transfer size update */
            g_usb_cstd_dma_size[ip][channel] = *p_data_cnt;

            dma_size = g_usb_cstd_dma_size[ip][channel];

            if (USB_IP0 == ip)
            {
                g_usb_cstd_dma_fraction_size[ip][channel] = g_usb_cstd_dma_size[ip][channel] & USB_BIT_MBW16;   /* fraction size(1-3) */
                dma_size &= ~USB_BIT_MBW16;
            }
            else
            {
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
                g_usb_cstd_dma_fraction_size[ip][channel] = g_usb_cstd_dma_size[ip][channel] & USB_BIT_MBW32;   /* fraction size(1-3) */
                dma_size &= ~USB_BIT_MBW32;
#else
                g_usb_cstd_dma_fraction_size[ip][channel] = g_usb_cstd_dma_size[ip][channel] & USB_BIT_MBW16;   /* fraction size(1-3) */
                dma_size &= ~USB_BIT_MBW16;
#endif
            }
            g_usb_cstd_dma_fraction_adr[ip][channel]  = (uint32_t)(p_src_adr + dma_size);   /* fraction data address */

            if (dma_size != 0)
            {
                g_usb_cstd_dma_size[ip][channel] = dma_size;

                /* DMA0 1byte trans */
                usb_dma_buf_to_fifo_restart(ptr, (uint32_t)p_src_adr, dma_size, pipe);
            }
            else
            {
                cpu_write = true;           /* Set flag for CPU FIFO Write */
            }
        }
    }

    if (true == cpu_write)
    {
        if (USB_D0DMA == useport)
        {
            useport = USB_D0USE;
        }
        else
        {
            useport = USB_D1USE;
        }

        if (USB_HOST == g_usb_usbmode)
        {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
            g_usb_hstd_data_cnt[ptr->ip][pipe] = (uint32_t)g_usb_cstd_dma_fraction_size[ip][channel]; /* fraction size(1-3) */
            g_p_usb_hstd_data[ptr->ip][pipe] = (uint8_t *)g_usb_cstd_dma_fraction_adr[ip][channel];    /* fraction data address */
            usb_hstd_buf_to_fifo(ptr, pipe, useport);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
            g_usb_pstd_data_cnt[pipe] = (uint32_t)g_usb_cstd_dma_fraction_size[ip][channel];          /* fraction size(1-3) */
            g_p_usb_pstd_data[pipe] = (uint8_t *)g_usb_cstd_dma_fraction_adr[ip][channel];             /* fraction data address */
            usb_pstd_buf_to_fifo(pipe, useport);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
        }
        g_usb_cstd_dma_fraction_size[ip][channel] = 0;
    }
}
/******************************************************************************
End of function usb_dma_buf2dxfifo_complete
******************************************************************************/

#if USB_CFG_DTC == USB_CFG_ENABLE
/******************************************************************************
Function Name   : usb_dma_dxfifo2buf_setting
Description     : FIFO to Buffer data read DMA start
Arguments       : usb_utr_t *ptr         : Pointer to usb_utr_t structure
                : uint32_t des_addr      : Source address
                : uint16_t useport       : FIFO Access mode
                : uint32_t transfer_size : Transfer size
Return value    : void
******************************************************************************/
void usb_dma_dxfifo2buf_setting(usb_utr_t *ptr, uint32_t des_addr, uint16_t useport, uint32_t transfer_size)
{
    dtc_transfer_data_cfg_t     td_cfg;
    dtc_stat_t                  dmac_status;
    dtc_cmd_arg_t               args;
    uint32_t                    fifo_address;
    uint8_t                     dma_ch;
    uint16_t                    vect;
    uint16_t                    fifo_mode;
    uint16_t                    ip;
    uint16_t                    transfer_count;
    uint16_t                    block_size;

    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DTC_START, USB_NULL, 0);

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DATA_READ_SKIP_DISABLE, USB_NULL, 0);

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DATA_READ_SKIP_ENABLE, USB_NULL, 0);

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    dma_ch = usb_dma_ref_ch_no(ip, useport);

    if (USB_D0DMA == useport)
    {
        fifo_mode = USB_FIFO_TYPE_D0DMA;
    }
    else
    {
        fifo_mode = USB_FIFO_TYPE_D1DMA;
    }

    transfer_count  = ((transfer_size -1) / g_usb_cstd_dma_fifo[ip][dma_ch]) +1;
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    if (USB_IP1 == ip)
    {
        td_cfg.data_size    = DTC_DATA_SIZE_LWORD;
        block_size      = ((g_usb_cstd_dma_fifo[ip][dma_ch] -1) /4) +1;
        fifo_address    = hw_usb_get_dxfifo_adr(ptr, fifo_mode, USB_FIFO_ACCESS_TYPE_32BIT);

        if (transfer_size < g_usb_cstd_dma_fifo[ip][dma_ch])
        {
            block_size      = ((transfer_size -1) /4) +1;
        }
    }
    else
    {

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
        td_cfg.data_size    = DTC_DATA_SIZE_WORD;
        block_size      = ((g_usb_cstd_dma_fifo[ip][dma_ch] -1) /2) +1;
        fifo_address    = hw_usb_get_dxfifo_adr(ptr, fifo_mode, USB_FIFO_ACCESS_TYPE_16BIT);

        if (transfer_size < g_usb_cstd_dma_fifo[ip][dma_ch])
        {
            block_size      = ((transfer_size -1) /2) +1;
        }
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    }

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

    vect = usb_dma_get_dxfifo_ir_vect(ptr, useport);

    /* Wait for Complete of DMA transfer. */
    do
    {
        R_DTC_Control(DTC_CMD_STATUS_GET, &dmac_status, &args);
    }
    while(true ==dmac_status.in_progress);

/* DMA test code start */
    /* Operation - No Extended Repeat Area Function and No Offset Subtraction */
    /* Source address is fixed
    * Transfer data size is 32-bit (long word).
    * DMAC transfer mode is Repeat mode & Source side is repeat area
    * At the beginning of transfer, clear the interrupt flag of the activation source
    to 0.
    * Transfer Request source is software. */
    /* Set Transfer data configuration. */
    td_cfg.transfer_mode  = DTC_TRANSFER_MODE_BLOCK;
    td_cfg.repeat_block_side = DTC_REPEAT_BLOCK_SOURCE;
    td_cfg.src_addr_mode  = DTC_SRC_ADDR_FIXED;
    td_cfg.dest_addr_mode = DTC_DES_ADDR_INCR;
    td_cfg.source_addr    = fifo_address;
    td_cfg.dest_addr      = des_addr;
    td_cfg.transfer_count = transfer_count;
    td_cfg.block_size     = block_size;
    td_cfg.chain_transfer_enable = DTC_CHAIN_TRANSFER_DISABLE;
    td_cfg.chain_transfer_mode  = DTC_CHAIN_TRANSFER_CONTINUOUSLY;
    td_cfg.response_interrupt = DTC_INTERRUPT_AFTER_ALL_COMPLETE;
#if defined(BSP_MCU_RX65N)
    td_cfg.writeback_disable = DTC_WRITEBACK_ENABLE;     /* Write-back disable or enable */
    td_cfg.sequence_end = DTC_SEQUENCE_TRANSFER_CONTINUE;          /* Sequence transfer end or continue */
    td_cfg.refer_index_table_enable = DTC_REFER_INDEX_TABLE_DISABLE; /* Index table refer or not refer */
    td_cfg.disp_add_enable = DTC_SRC_ADDR_DISP_ADD_DISABLE;       /* The displacement value is added or not added */
#endif /* defined(BSP_MCU_RX65N) */

    /* Call R_DTC_Create(). */
    R_DTC_Create((dtc_activation_source_t)vect, &g_usb_dtc_transfer_data[dma_ch], &td_cfg, 0);

    if ((USB_IP0 == ip) && (USB_D0DMA == useport))
    {
        /* DTC start enable register (USB0 D0FIFO transfer enable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        DTCE( USB0, D0FIFO0 ) = 1;
    }
    else if ((USB_IP0 == ip) && (USB_D1DMA == useport))
    {
        /* DTC start enable register (USBA D0FIFO transfer enable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        DTCE( USB0, D1FIFO0 ) = 1;
    }
    else if ((USB_IP1 == ip) && (USB_D0DMA == useport))
    {
        /* DTC start enable register (USBA D0FIFO transfer enable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        DTCE( USBA, D0FIFO2 ) = 1;

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
        DTCE( USB1, D0FIFO1 ) = 1;

#endif  /* defined(BSP_MCU_RX63N) */
    }
    else if ((USB_IP1 == ip) && (USB_D1DMA == useport))
    {
        /* DTC start enable register (USBA D0FIFO transfer enable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        DTCE( USBA, D1FIFO2 ) = 1;

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
        DTCE( USB1, D1FIFO1 ) = 1;

#endif  /* defined(BSP_MCU_RX63N) */
    }
    else
    {
    }
}
/******************************************************************************
End of function usb_dma_dxfifo2buf_setting
******************************************************************************/

/******************************************************************************
Function Name   : usb_dma_buf2dxfifo_setting
Description     : Buffer to FIFO data write DMA start
Arguments       : usb_utr_t *ptr            : Pointer to usb_utr_t structure
                : uint32_t  src_adr         : Source address
                : uint16_t  useport         : FIFO Access mode
                : uint32_t  transfer_size   : Transfer size
Return value    : none
******************************************************************************/
void usb_dma_buf2dxfifo_setting(usb_utr_t *ptr, uint32_t src_adr, uint16_t useport, uint32_t transfer_size)
{
    dtc_transfer_data_cfg_t     td_cfg;
    dtc_stat_t                  dmac_status;
    dtc_cmd_arg_t               args;
    uint32_t                    fifo_address;
    uint16_t                    fifo_mode;
    uint16_t                    bit_width;
    uint8_t                     dma_ch;
    uint16_t                    vect;
    uint16_t                    ip;
    uint16_t                    transfer_count;
    uint16_t                    block_size;

    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    R_DTC_Control( DTC_CMD_DTC_START, USB_NULL, 0 );

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control( DTC_CMD_DATA_READ_SKIP_DISABLE, USB_NULL, 0 );

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DATA_READ_SKIP_ENABLE, USB_NULL, 0);

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    dma_ch = usb_dma_ref_ch_no(ip, useport);

    if (USB_D0DMA == useport)
    {
        fifo_mode = USB_FIFO_TYPE_D0DMA;
    }
    else
    {
        fifo_mode = USB_FIFO_TYPE_D1DMA;
    }

    if (g_usb_cstd_dma_fifo[ip][dma_ch] > transfer_size)
    {
        block_size       = transfer_size;
    }
    else
    {
        block_size       = g_usb_cstd_dma_fifo[ip][dma_ch];
    }

    transfer_count  = ((transfer_size -1) / g_usb_cstd_dma_fifo[ip][dma_ch]) +1;
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    if ((0 == (transfer_size & 0x03)) && (USB_IP1 == ip))
    {
        block_size       = ((block_size -1) /4) +1;
        bit_width        = USB_FIFO_ACCESS_TYPE_32BIT;
        td_cfg.data_size = DTC_DATA_SIZE_LWORD;
        fifo_address     = hw_usb_get_dxfifo_adr(ptr, fifo_mode, USB_FIFO_ACCESS_TYPE_32BIT);
    }
    else
    {

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
        if (0 == (transfer_size & 0x01))
        {
            block_size       = ((block_size -1) /2) +1;
            bit_width        = USB_FIFO_ACCESS_TYPE_16BIT;
            td_cfg.data_size = DTC_DATA_SIZE_WORD;
            fifo_address     = hw_usb_get_dxfifo_adr(ptr, fifo_mode, USB_FIFO_ACCESS_TYPE_16BIT);
        }
        else
        {
            bit_width        = USB_FIFO_ACCESS_TYPE_8BIT;
            td_cfg.data_size = DTC_DATA_SIZE_BYTE;
            fifo_address     = hw_usb_get_dxfifo_adr(ptr, fifo_mode, USB_FIFO_ACCESS_TYPE_8BIT);
        }
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    }

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

    vect = usb_dma_get_dxfifo_ir_vect(ptr, useport);
    fifo_address = hw_usb_get_dxfifo_adr(ptr, fifo_mode, bit_width);

    /* Wait for Complete of DMA transfer. */
    do
    {
        R_DTC_Control(DTC_CMD_STATUS_GET, &dmac_status, &args);
    }
    while(true ==dmac_status.in_progress);

/* DMA test code start */
    /* Operation - No Extended Repeat Area Function and No Offset Subtraction */
    /* Source address is fixed
    * Transfer data size is 32-bit (long word).
    * DMAC transfer mode is Repeat mode & Source side is repeat area
    * At the beginning of transfer, clear the interrupt flag of the activation source
    to 0.
    * Transfer Request source is software. */
    /* Set Transfer data configuration. */
    td_cfg.transfer_mode        = DTC_TRANSFER_MODE_BLOCK;
    td_cfg.repeat_block_side    = DTC_REPEAT_BLOCK_DESTINATION;
    td_cfg.src_addr_mode        = DTC_SRC_ADDR_INCR;
    td_cfg.dest_addr_mode       = DTC_DES_ADDR_FIXED;
    td_cfg.source_addr          = src_adr;
    td_cfg.dest_addr            = fifo_address;
    td_cfg.transfer_count       = transfer_count;
    td_cfg.block_size           = block_size;
    td_cfg.chain_transfer_enable = DTC_CHAIN_TRANSFER_DISABLE;
    td_cfg.chain_transfer_mode  = DTC_CHAIN_TRANSFER_CONTINUOUSLY;
    td_cfg.response_interrupt   = DTC_INTERRUPT_AFTER_ALL_COMPLETE;
#if defined(BSP_MCU_RX65N)
    td_cfg.writeback_disable = DTC_WRITEBACK_ENABLE;     /* Write-back disable or enable */
    td_cfg.sequence_end = DTC_SEQUENCE_TRANSFER_CONTINUE;          /* Sequence transfer end or continue */
    td_cfg.refer_index_table_enable = DTC_REFER_INDEX_TABLE_DISABLE; /* Index table refer or not refer */
    td_cfg.disp_add_enable = DTC_SRC_ADDR_DISP_ADD_DISABLE;       /* The displacement value is added or not added */
#endif /* defined(BSP_MCU_RX65N) */

    /* Call R_DTC_Create(). */
    R_DTC_Create((dtc_activation_source_t)vect, &g_usb_dtc_transfer_data[dma_ch], &td_cfg, 0);

    if ((USB_IP0 == ip) && (USB_D0DMA == useport))
    {
        /* DTC start enable register (USB0 D0FIFO transfer enable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        DTCE( USB0, D0FIFO0 ) = 1;
        IPR (USB0, D0FIFO0) = 4u;                   /* D0FIFO0 Enable */
    }
    else if ((USB_IP0 == ip) && (USB_D1DMA == useport))
    {
        /* DTC start enable register (USBA D0FIFO transfer enable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        DTCE( USB0, D1FIFO0 ) = 1;
        IPR (USB0, D1FIFO0) = 4u;                   /* D0FIFO0 Enable */
    }
    else if ((USB_IP1 == ip) && (USB_D0DMA == useport))
    {
        /* DTC start enable register (USBA D0FIFO transfer enable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        DTCE( USBA, D0FIFO2 ) = 1;
        IPR (USBA, D0FIFO2) = 4u;                   /* D0FIFO0 Enable */

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
        DTCE( USB1, D0FIFO1 ) = 1;
        IPR (USB1, D0FIFO1) = 4u;                   /* D0FIFO0 Enable */

#endif  /* defined(BSP_MCU_RX63N) */
    }
    else if ((USB_IP1 == ip) && (USB_D1DMA == useport))
    {
        /* DTC start enable register (USBA D0FIFO transfer enable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        DTCE( USBA, D1FIFO2 ) = 1;
        IPR (USBA, D1FIFO2) = 4u;                   /* D0FIFO0 Enable */

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
        DTCE( USB1, D1FIFO1 ) = 1;
        IPR (USB1, D1FIFO1) = 4u;                   /* D0FIFO0 Enable */

#endif  /* defined(BSP_MCU_RX63N) */
    }
    else
    {
    }
}
/******************************************************************************
End of function usb_dma_buf2dxfifo_setting
******************************************************************************/
#endif /* USB_CFG_DTC == USB_CFG_ENABLE */

#if USB_CFG_DMA == USB_CFG_ENABLE
/******************************************************************************
Function Name   : usb_dma_dxfifo2buf_setting
Description     : FIFO to Buffer data read DMA start
Arguments       : usb_utr_t *ptr         : Pointer to usb_utr_t structure
                : uint32_t des_addr      : Source address
                : uint16_t useport       : FIFO Access mode
                : uint32_t transfer_size : Transfer size
Return value    : void
******************************************************************************/
void usb_dma_dxfifo2buf_setting(usb_utr_t *ptr, uint32_t des_addr, uint16_t useport, uint32_t transfer_size)
{
    volatile dmaca_return_t     ret;
    dmaca_transfer_data_cfg_t   td_cfg;
    dmaca_stat_t                dmac_status;
    uint32_t                    fifo_address;
    uint8_t                     dma_ch;
    uint16_t                    vect;
    uint16_t                    fifo_mode;
    uint16_t                    ip;
    uint16_t                    transfer_count;
    uint16_t                    block_size;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    dma_ch = usb_dma_ref_ch_no(ip, useport);

    if (USB_D0DMA == useport)
    {
        fifo_mode = USB_FIFO_TYPE_D0DMA;
    }
    else
    {
        fifo_mode = USB_FIFO_TYPE_D1DMA;
    }

    transfer_count  = ((transfer_size -1) / g_usb_cstd_dma_fifo[ip][dma_ch]) +1;
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    if (USB_IP1 == ip)
    {
        td_cfg.data_size    = DMACA_DATA_SIZE_LWORD;
        block_size      = ((g_usb_cstd_dma_fifo[ip][dma_ch] -1) /4) +1;
        fifo_address    = hw_usb_get_dxfifo_adr(ptr, fifo_mode, USB_FIFO_ACCESS_TYPE_32BIT);

        if (transfer_size < g_usb_cstd_dma_fifo[ip][dma_ch])
        {
            block_size      = ((transfer_size -1) /4) +1;
        }    }
    else
    {

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
        td_cfg.data_size    = DMACA_DATA_SIZE_WORD;
        block_size      = ((g_usb_cstd_dma_fifo[ip][dma_ch] -1) /2) +1;
        fifo_address    = hw_usb_get_dxfifo_adr(ptr, fifo_mode, USB_FIFO_ACCESS_TYPE_16BIT);

        if (transfer_size < g_usb_cstd_dma_fifo[ip][dma_ch])
        {
            block_size      = ((transfer_size -1) /2) +1;
        }
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    }

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

    vect = usb_dma_get_dxfifo_ir_vect(ptr, useport);

    /* Wait for Complete of DMA transfer. */
    do
    {
        R_DMACA_Control(dma_ch, DMACA_CMD_STATUS_GET, &dmac_status);
    }
    while(true ==dmac_status.act_stat);

    R_DMACA_Control(dma_ch, DMACA_CMD_DTIF_STATUS_CLR, &dmac_status);

/* DMA test code start */
    /* Operation - No Extended Repeat Area Function and No Offset Subtraction */
    /* Source address is fixed
    * Transfer data size is 32-bit (long word).
    * DMAC transfer mode is Repeat mode & Source side is repeat area
    * At the beginning of transfer, clear the interrupt flag of the activation source
    to 0.
    * Transfer Request source is software. */
    /* Set Transfer data configuration. */
    td_cfg.transfer_mode  = DMACA_TRANSFER_MODE_BLOCK;
    td_cfg.repeat_block_side = DMACA_REPEAT_BLOCK_DISABLE;
    td_cfg.act_source     = (dmaca_activation_source_t)vect;
    td_cfg.request_source = DMACA_TRANSFER_REQUEST_PERIPHERAL;
    td_cfg.dtie_request   = DMACA_TRANSFER_END_INTERRUPT_DISABLE;
    td_cfg.esie_request   = DMACA_TRANSFER_ESCAPE_END_INTERRUPT_DISABLE;
    td_cfg.rptie_request  = DMACA_REPEAT_SIZE_END_INTERRUPT_DISABLE;
    td_cfg.sarie_request  = DMACA_SRC_ADDR_EXT_REP_AREA_OVER_INTERRUPT_DISABLE;
    td_cfg.darie_request  = DMACA_DES_ADDR_EXT_REP_AREA_OVER_INTERRUPT_DISABLE;
    td_cfg.src_addr_mode  = DMACA_SRC_ADDR_FIXED;
    td_cfg.src_addr_repeat_area = DMACA_SRC_ADDR_EXT_REP_AREA_NONE;
    td_cfg.des_addr_mode  = DMACA_DES_ADDR_INCR;
    td_cfg.des_addr_repeat_area = DMACA_DES_ADDR_EXT_REP_AREA_NONE;
    td_cfg.offset_value   = 0x00000000;
    td_cfg.interrupt_sel  = DMACA_CLEAR_INTERRUPT_FLAG_BEGINNING_TRANSFER;
    td_cfg.p_src_addr     = (void *)fifo_address;
    td_cfg.p_des_addr     = (void *)des_addr;
    td_cfg.transfer_count = transfer_count;
    td_cfg.block_size     = block_size;

    /* Call R_DMACA_Create(). */
    ret = R_DMACA_Create(dma_ch, &td_cfg);

    ret = R_DMACA_Int_Enable(dma_ch, USB_DMA_CH_PRI);
    if (DMACA_SUCCESS != ret)
    {
        /* do something */
    }

    /* Call R_DMACA_Control().
    Enable DMAC transfer. */
    ret = R_DMACA_Control(dma_ch, DMACA_CMD_ENABLE, &dmac_status);
}
/******************************************************************************
End of function usb_dma_dxfifo2buf_setting
******************************************************************************/

/******************************************************************************
Function Name   : usb_dma_buf2dxfifo_setting
Description     : Buffer to FIFO data write DMA start
Arguments       : usb_utr_t *ptr            : Pointer to usb_utr_t structure
                : uint32_t  src_adr         : Source address
                : uint16_t  useport         : FIFO Access mode
                : uint32_t  transfer_size   : Transfer size
Return value    : none
******************************************************************************/
void usb_dma_buf2dxfifo_setting(usb_utr_t *ptr, uint32_t src_adr, uint16_t useport, uint32_t transfer_size)
{
    volatile dmaca_return_t     ret;
    dmaca_transfer_data_cfg_t   td_cfg;
    dmaca_stat_t                dmac_status;
    uint32_t                    fifo_address;
    uint16_t                    vect;
    uint16_t                    fifo_mode;
    uint16_t                    bit_width;
    uint8_t                     dma_ch;
    uint16_t                    ip;
    uint16_t                    transfer_count;
    uint16_t                    block_size;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    dma_ch = usb_dma_ref_ch_no(ip, useport);

    if (USB_D0DMA == useport)
    {
        fifo_mode = USB_FIFO_TYPE_D0DMA;
        if (USB_IP0 == ip)
        {
            ret = R_DMACA_Int_Callback(dma_ch, (void *) usb_ip0_d0fifo_callback);
        }
        else
        {
            ret = R_DMACA_Int_Callback(dma_ch, (void *) usb_ip1_d0fifo_callback);
        }
    }
    else
    {
        fifo_mode = USB_FIFO_TYPE_D1DMA;
        if (USB_IP0 == ip)
        {
            ret = R_DMACA_Int_Callback(dma_ch, (void *) usb_ip0_d1fifo_callback);
        }
        else
        {
            ret = R_DMACA_Int_Callback(dma_ch, (void *) usb_ip1_d1fifo_callback);
        }
    }

    if (g_usb_cstd_dma_fifo[ip][dma_ch] > transfer_size)
    {
        block_size       = transfer_size;
    }
    else
    {
        block_size       = g_usb_cstd_dma_fifo[ip][dma_ch];
    }

    transfer_count  = ((transfer_size -1) / g_usb_cstd_dma_fifo[ip][dma_ch]) +1;
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    if ((0 == (transfer_size & 0x03)) && (USB_IP1 == ip))
    {
        block_size       = ((block_size -1) /4) +1;
        bit_width        = USB_FIFO_ACCESS_TYPE_32BIT;
        td_cfg.data_size = DMACA_DATA_SIZE_LWORD;
        fifo_address     = hw_usb_get_dxfifo_adr(ptr, fifo_mode, USB_FIFO_ACCESS_TYPE_32BIT);
    }
    else
    {

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
        if (0 == (transfer_size & 0x01))
        {
            block_size       = ((block_size -1) /2) +1;
            bit_width        = USB_FIFO_ACCESS_TYPE_16BIT;
            td_cfg.data_size = DMACA_DATA_SIZE_WORD;
            fifo_address     = hw_usb_get_dxfifo_adr(ptr, fifo_mode, USB_FIFO_ACCESS_TYPE_16BIT);
        }
        else
        {
            bit_width        = USB_FIFO_ACCESS_TYPE_8BIT;
            td_cfg.data_size = DMACA_DATA_SIZE_BYTE;
            fifo_address     = hw_usb_get_dxfifo_adr(ptr, fifo_mode, USB_FIFO_ACCESS_TYPE_8BIT);
        }
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    }

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

    vect = usb_dma_get_dxfifo_ir_vect(ptr, useport);
    fifo_address = hw_usb_get_dxfifo_adr(ptr, fifo_mode, bit_width);

    /* Wait for Complete of DMA transfer. */
    do
    {
        R_DMACA_Control(dma_ch, DMACA_CMD_STATUS_GET, &dmac_status);
    }
    while(true ==dmac_status.act_stat);

    R_DMACA_Control(dma_ch, DMACA_CMD_DTIF_STATUS_CLR, &dmac_status);

/* DMA test code start */
    /* Operation - No Extended Repeat Area Function and No Offset Subtraction */
    /* Source address is fixed
    * Transfer data size is 32-bit (long word).
    * DMAC transfer mode is Repeat mode & Source side is repeat area
    * At the beginning of transfer, clear the interrupt flag of the activation source
    to 0.
    * Transfer Request source is software. */
    /* Set Transfer data configuration. */
    td_cfg.transfer_mode        = DMACA_TRANSFER_MODE_BLOCK;
    td_cfg.repeat_block_side    = DMACA_REPEAT_BLOCK_DISABLE;
    td_cfg.act_source           = (dmaca_activation_source_t)vect;
    td_cfg.request_source       = DMACA_TRANSFER_REQUEST_PERIPHERAL;
    td_cfg.dtie_request         = DMACA_TRANSFER_END_INTERRUPT_ENABLE;
    td_cfg.esie_request         = DMACA_TRANSFER_ESCAPE_END_INTERRUPT_DISABLE;
    td_cfg.rptie_request        = DMACA_REPEAT_SIZE_END_INTERRUPT_DISABLE;
    td_cfg.sarie_request        = DMACA_SRC_ADDR_EXT_REP_AREA_OVER_INTERRUPT_DISABLE;
    td_cfg.darie_request        = DMACA_DES_ADDR_EXT_REP_AREA_OVER_INTERRUPT_DISABLE;
    td_cfg.src_addr_mode        = DMACA_SRC_ADDR_INCR;
    td_cfg.src_addr_repeat_area = DMACA_SRC_ADDR_EXT_REP_AREA_NONE;
    td_cfg.des_addr_mode        = DMACA_DES_ADDR_FIXED;
    td_cfg.des_addr_repeat_area = DMACA_DES_ADDR_EXT_REP_AREA_NONE;
    td_cfg.offset_value         = 0x00000000;
    td_cfg.interrupt_sel        = DMACA_CLEAR_INTERRUPT_FLAG_BEGINNING_TRANSFER;
    td_cfg.p_src_addr           = (void *)src_adr;
    td_cfg.p_des_addr           = (void *)fifo_address;
    td_cfg.transfer_count       = transfer_count;
    td_cfg.block_size           = block_size;

    /* Call R_DMACA_Create(). */
    ret = R_DMACA_Create(dma_ch, &td_cfg);

    ret = R_DMACA_Int_Enable(dma_ch, USB_DMA_CH2_PRI);
    if (DMACA_SUCCESS != ret)
    {
        /* do something */
    }

    /* Call R_DMACA_Control().
    Enable DMAC transfer. */
    ret = R_DMACA_Control(dma_ch, DMACA_CMD_ENABLE, &dmac_status);

}
/******************************************************************************
End of function usb_dma_buf2dxfifo_setting
******************************************************************************/
#endif /* USB_CFG_DMA == USB_CFG_ENABLE */

/******************************************************************************
Function Name   : usb_dma_get_dxfifo_ir_vect
Description     : Get vector no. of USB DxFIFO
Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure
                : uint16_t  useport     : FIFO select
Return value    : Vector no.
******************************************************************************/
uint16_t    usb_dma_get_dxfifo_ir_vect(usb_utr_t *ptr, uint16_t use_port)
{
    uint16_t    ip;
    uint16_t    vect;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    if (USB_USBIP_0 == ip)
    {
        if (USB_D0DMA == use_port)
        {
            vect = IR_USB0_D0FIFO0;
        }
        else if (USB_D1DMA == use_port)
        {
            vect = IR_USB0_D1FIFO0;
        }
        else
        {
            /* none */
        }
    }
#if USB_NUM_USBIP == 2
    else
    {
        if (USB_D0DMA == use_port)
        {
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
            vect = IR_USBA_D0FIFO2;

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
            vect = IR_USB1_D0FIFO1;

#endif  /* defined(BSP_MCU_RX63N) */
        }
        else if (USB_D1DMA == use_port)
        {
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
            vect = IR_USBA_D1FIFO2;

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
            vect = IR_USB1_D1FIFO1;

#endif  /* defined(BSP_MCU_RX63N) */
        }
        else
        {
            /* none */
        }
    }

#endif /* USB_NUM_USBIP == 2 */

    return vect;
}
/******************************************************************************
End of function usb_dma_get_dxfifo_ir_vect
******************************************************************************/

/******************************************************************************
Function Name   : usb_dma_clear_dxfifo_ir
Description     : Clear Interrupt status of USB DxFIFO.
Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure
                : uint16_t  useport     : FIFO select
Return value    : none
******************************************************************************/
void    usb_dma_clear_dxfifo_ir(usb_utr_t *ptr, uint16_t use_port)
{
    uint16_t    ip;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    if (USB_USBIP_0 == ip)
    {
        if (USB_D0DMA == use_port)
        {
            IR(USB0,D0FIFO0) = 0;
        }
        else if (USB_D1DMA == use_port)
        {
            IR(USB0,D1FIFO0) = 0;
        }
        else
        {
            /* none */
        }
    }
#if USB_NUM_USBIP == 2
    else
    {
        if (USB_D0DMA == use_port)
        {
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
            IR(USBA,D0FIFO2) = 0;

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
            IR(USB1,D0FIFO1) = 0;

#endif  /* defined(BSP_MCU_RX63N) */
        }
        else if (USB_D1DMA == use_port)
        {
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
            IR(USBA,D1FIFO2) = 0;

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
            IR(USB1,D1FIFO1) = 0;

#endif  /* defined(BSP_MCU_RX63N) */
        }
        else
        {
            /* None */
        }
    }

#endif /* USB_NUM_USBIP == 2 */
}
/******************************************************************************
End of function usb_dma_clear_dxfifo_ir
******************************************************************************/

/******************************************************************************
Function Name   : usb_dma_stop_dxfifo
Description     : DMA stop
Arguments       : uint8_t   ip_type     : USB_IP0/USB_IP1
                : uint16_t  use_port    : FIFO select
Return value    : void
******************************************************************************/
void usb_dma_stop_dxfifo(uint8_t ip_type, uint16_t use_port)
{
#if USB_CFG_DTC == USB_CFG_ENABLE
    dtc_stat_t      stat;
    dtc_cmd_arg_t   args;
    usb_utr_t       utr;

    /* Wait for Complete of DTC transfer. */
    do
    {
        R_DTC_Control(DTC_CMD_STATUS_GET, &stat, &args);
    }
    while(true ==stat.in_progress);

    R_DTC_Control(DTC_CMD_DTC_STOP, &stat, &args); /* Clear DTC stop*/

    if (USB_IP0 == ip_type)
    {
        /* DTC start enable register (USB0 D0FIFO transfer disable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        if (USB_D0DMA == use_port)
        {
            DTCE( USB0, D0FIFO0 ) = 0;
            IPR (USB0, D0FIFO0) = 0u;                   /* D0FIFO0 Disable */
        }
        else
        {
            DTCE( USB0, D1FIFO0 ) = 0;
            IPR (USB0, D1FIFO0) = 0u;                   /* D0FIFO0 Disable */
        }
    }
    else
    {
        /* DTC start enable register (USBA D0FIFO transfer disable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        if (USB_D0DMA == use_port)
        {
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
            DTCE( USBA, D0FIFO2 ) = 0;
            IPR (USBA, D0FIFO2) = 0u;                   /* D0FIFO0 Disable */

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
            DTCE( USB1, D0FIFO1 ) = 0;
            IPR (USB1, D0FIFO1) = 0u;                   /* D0FIFO0 Disable */

#endif  /* defined(BSP_MCU_RX63N) */
        }
        else
        {
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
            DTCE( USBA, D1FIFO2 ) = 0;
            IPR (USBA, D1FIFO2) = 0u;                   /* D0FIFO0 Disable */

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#if defined(BSP_MCU_RX63N)
            DTCE( USB1, D1FIFO1 ) = 0;
            IPR (USB1, D1FIFO1) = 0u;                   /* D0FIFO0 Disable */

#endif  /* defined(BSP_MCU_RX63N) */
        }
    }

    utr.ip = ip_type;
    usb_dma_clear_dxfifo_ir(&utr, use_port);

#endif  /* USB_CFG_DTC == USB_CFG_ENABLE */

#if USB_CFG_DMA == USB_CFG_ENABLE
    dmaca_stat_t                dmac_status;
    uint8_t                     dma_ch;

    dma_ch = usb_dma_ref_ch_no(ip_type, use_port);  /* Get DMA channel no. */

    /* Wait for Complete of DMA transfer. */
    do
    {
        R_DMACA_Control(dma_ch, DMACA_CMD_STATUS_GET, &dmac_status);
    }
    while(true ==dmac_status.act_stat);

    R_DMACA_Control(dma_ch, DMACA_CMD_DTIF_STATUS_CLR, &dmac_status); /* Clear DMA status */

#endif  /* USB_CFG_DMA == USB_CFG_ENABLE */

}
/******************************************************************************
End of function usb_dma_stop_dxfifo
******************************************************************************/

/******************************************************************************
Function Name   : usb_dma_set_ch_no
Description     : Set DMA channel no.
Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
                : uint16_t useport  : FIFO select
                : uint8_t dma_ch_no : DMA channel no.
Return value    : none
******************************************************************************/
void        usb_dma_set_ch_no(uint16_t ip_no, uint16_t use_port, uint8_t dma_ch_no)
{
    g_usb_cstd_dma_ch[ip_no][use_port] = dma_ch_no;  /* DMA ch no. table */
}
/******************************************************************************
End of function usb_dma_set_ch_no
******************************************************************************/

/******************************************************************************
Function Name   : usb_dma_ref_ch_no
Description     : Get DMA channel no.
Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
                : uint16_t  useport : FIFO select
Return value    : DMA channel no.
******************************************************************************/
uint8_t     usb_dma_ref_ch_no(uint16_t ip_no, uint16_t use_port)
{
    return g_usb_cstd_dma_ch[ip_no][use_port];  /* DMA ch no. table */
}
/******************************************************************************
End of function usb_dma_ref_ch_no
******************************************************************************/

/******************************************************************************
Function Name   : usb_dma_buf2dxfifo_complete_event_set
Description     : Set event for DMA transfer complete of Buffer to DxFIFO.
Arguments       : uint16_t ip_no  : IP no.(USB_IP0/USB_IP1)
                : uint16_t useport: FIFO select(USB_D0DMA/USB_D1DMA)
Return value    : none
******************************************************************************/
void usb_dma_buf2dxfifo_complete_event_set(uint16_t ip_no, uint16_t use_port)
{
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    usb_utr_t   utr;

#endif  /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

    g_usb_cstd_dma_int.buf[g_usb_cstd_dma_int.wp].ip = ip_no;
    g_usb_cstd_dma_int.buf[g_usb_cstd_dma_int.wp].fifo_type = use_port;
    g_usb_cstd_dma_int.wp = ((g_usb_cstd_dma_int.wp+1) % USB_INT_BUFSIZE);

    if (USB_HOST == g_usb_usbmode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        utr.ip = ip_no;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

        hw_usb_clear_dreqe(&utr, use_port);       /* DMA Transfer request disable */

#endif  /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        hw_usb_clear_dreqe(USB_NULL, use_port);       /* DMA Transfer request disable */

#endif  /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
    }
}
/******************************************************************************
End of function usb_dma_buf2dxfifo_complete_event_set
******************************************************************************/

/*******************************************************************************
* Function Name: usb_ip0_d0fifo_callback
* Description  : Interrupt service routine of D0FIFO
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb_ip0_d0fifo_callback (void)
{
    usb_dma_buf2dxfifo_complete_event_set(USB_IP0, USB_D0DMA);
}
/******************************************************************************
End of function usb_ip0_d0fifo_callback
******************************************************************************/

/*******************************************************************************
* Function Name: usb_ip0_d1fifo_callback
* Description  : Interrupt service routine of D1FIFO
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb_ip0_d1fifo_callback (void)
{
    usb_dma_buf2dxfifo_complete_event_set(USB_IP0, USB_D1DMA);
}
/******************************************************************************
End of function usb_ip1_d0fifo_callback
******************************************************************************/

/*******************************************************************************
* Function Name: usb_ip1_d0fifo_callback
* Description  : Interrupt service routine of D0FIFO
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb_ip1_d0fifo_callback (void)
{
    usb_dma_buf2dxfifo_complete_event_set(USB_IP1, USB_D0DMA);
}
/******************************************************************************
End of function usb_ip1_d0fifo_callback
******************************************************************************/

/*******************************************************************************
* Function Name: usb_ip1_d1fifo_callback
* Description  : Interrupt service routine of D1FIFO
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb_ip1_d1fifo_callback (void)
{
    usb_dma_buf2dxfifo_complete_event_set(USB_IP1, USB_D1DMA);
}
/******************************************************************************
End of function usb_ip1_d1fifo_callback
******************************************************************************/


/******************************************************************************
Function Name   : hw_usb_get_dxfifo_adr
Description     : Get FIFO port address of DMA/DTC.
Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure
                : uint16_t  use_port    : FIFO select
                : uint16_t  bit_width   : Access bit size of USB DxFIFO
Return          : Address of FIFO port.
******************************************************************************/
uint32_t hw_usb_get_dxfifo_adr(usb_utr_t *ptr, uint16_t use_port, uint16_t bit_width)
{
    uint32_t    address;
    uint8_t     ip;
    


    if (USB_NULL != ptr)
    {
        /* Host mode */
        if (USB_IP0 == ptr->ip)
        {
            ip = USB_IP0;
        }
        else
        {
            ip = USB_IP1;
        }
    }
    else
    {
        /* Peri mode */
#if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;
#else
        /* USB1/USBA */
        ip = USB_IP1;
#endif
    }

    address = g_fifo_address[ip][use_port][bit_width];      /* Set address of FIFO port */
    return address;
}
/******************************************************************************
End of function hw_usb_get_dxfifo_adr
******************************************************************************/


/******************************************************************************
Function Name   : usb_dma_get_crtb
Description     : Get DMA Current Transaction Byte reg B(CRTB).
Arguments       : uint16_t dma_ch : DMA Channel no.
Return value    : DMA Current Transaction Byte reg B(CRTB)
******************************************************************************/
uint16_t usb_dma_get_crtb(uint16_t dma_ch)
{
#if USB_CFG_DTC == USB_CFG_ENABLE
    uint16_t value;
    uint16_t status_reg = 0;

    /* Wait Complete DTC Transfer */
    do
    {
        status_reg = DTC.DTCSTS.WORD;
    }
    while( 0 != ( status_reg & 0x8000 ) );  /* DTC is not active */
 
    /* Read DTC transfer count (CRB) */
    value = (uint16_t)(g_usb_dtc_transfer_data[dma_ch].lw4 & 0xffff);
    
    return value;

#endif  /* USB_CFG_DTC == USB_CFG_ENABLE */

#if USB_CFG_DMA == USB_CFG_ENABLE
    dmaca_stat_t                dmac_status;

    R_DMACA_Control(dma_ch, DMACA_CMD_STATUS_GET, &dmac_status);

    return dmac_status.transfer_count;

#endif  /* USB_CFG_DTC == USB_CFG_ENABLE */
}
/******************************************************************************
End of function usb_dma_get_crtb
******************************************************************************/


#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

/******************************************************************************
End of file
******************************************************************************/
